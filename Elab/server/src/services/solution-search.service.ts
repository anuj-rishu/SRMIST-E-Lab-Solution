import {
  questionFingerprint,
  type QuestionRequirements,
} from "../utils/question-fingerprint.js";
import type { ServerConfig } from "../config/env.js";
import { connectDatabase } from "../config/database.js";
import { QuestionCatalog } from "../models/question-catalog.model.js";
import { SolutionBinding } from "../models/solution-binding.model.js";
import { Solution } from "../models/solution.model.js";
import { HttpError } from "../utils/http-error.js";
import { logger } from "../utils/logger.js";
import { createHash } from "node:crypto";
import { prepareMandatoryCode } from "../utils/mandatory-code.js";
import type { EmbeddingService } from "./embedding.service.js";

export interface SolutionMatch {
  id: string;
  title: string;
  filename: string;
  solution: string;
  score: number;
}

export interface SolutionMatcher {
  find(
    description: string,
    courseId: number,
    mandatory?: readonly string[],
    questionId?: string,
    requirements?: QuestionRequirements,
  ): Promise<SolutionMatch>;
}

interface SearchResult {
  _id: { toString(): string };
  title: string;
  filename: string;
  solution: string;
  score: number;
  verifiedFingerprint?: string;
}

export class SolutionSearchService implements SolutionMatcher {
  // Cache solution matches only; student profiles, tokens, and evaluations stay uncached.
  private readonly cache = new Map<
    string,
    { match: SolutionMatch; expires: number; bytes: number }
  >();
  private cacheBytes = 0;
  private readonly inFlight = new Map<string, Promise<SolutionMatch>>();

  constructor(
    private readonly config: ServerConfig,
    private readonly embeddings: EmbeddingService,
  ) {}

  async find(
    description: string,
    courseId: number,
    mandatory: readonly string[] = [],
    questionId?: string,
    requirements?: QuestionRequirements,
  ): Promise<SolutionMatch> {
    const key = `${courseId}:${createHash("sha256")
      .update(
        JSON.stringify([description, mandatory, questionId, requirements]),
      )
      .digest("hex")}`;
    const cached = this.cache.get(key);
    if (cached) {
      if (cached.expires > Date.now()) {
        this.cache.delete(key);
        this.cache.set(key, cached);
        return { ...cached.match };
      }
      this.cache.delete(key);
      this.cacheBytes -= cached.bytes;
    }
    const existing = this.inFlight.get(key);
    if (existing) return { ...(await existing) };
    const pending = this.lookup(
      description,
      courseId,
      mandatory,
      questionId,
      requirements,
    );
    this.inFlight.set(key, pending);
    try {
      const match = await pending;
      const bytes = Buffer.byteLength(JSON.stringify(match));
      if (bytes <= 2 * 1024 * 1024) {
        while (
          this.cache.size >= 128 ||
          this.cacheBytes + bytes > 2 * 1024 * 1024
        ) {
          const oldest = this.cache.keys().next().value;
          if (oldest === undefined) break;
          this.cacheBytes -= this.cache.get(oldest)!.bytes;
          this.cache.delete(oldest);
        }
        this.cache.set(key, {
          match: { ...match },
          expires: Date.now() + 60_000,
          bytes,
        });
        this.cacheBytes += bytes;
      }
      return { ...match };
    } finally {
      this.inFlight.delete(key);
    }
  }

  private async lookup(
    description: string,
    courseId: number,
    mandatory: readonly string[],
    questionId?: string,
    requirements?: QuestionRequirements,
  ): Promise<SolutionMatch> {
    if (courseId !== 11 && courseId !== 26) {
      throw new HttpError(
        404,
        "No indexed solutions were found for this course.",
      );
    }
    const text = this.embeddings.normalize(description);
    if (!text)
      throw new HttpError(
        422,
        "Question description is empty after removing its heading.",
      );
    const fingerprint = questionFingerprint(
      description,
      mandatory,
      requirements,
    );
    let results: SearchResult[];
    try {
      await connectDatabase(this.config.mongodbUri);
      if (questionId) {
        const [question] = await QuestionCatalog.aggregate<{
          fingerprint: string;
          sourceHash?: string;
          source?: SearchResult & { courseId: number };
        }>([
          { $match: { courseId, Q_ID: questionId } },
          {
            $lookup: {
              from: "solutions",
              localField: "solutionId",
              foreignField: "_id",
              pipeline: [
                {
                  $project: { title: 1, filename: 1, solution: 1, courseId: 1 },
                },
              ],
              as: "sources",
            },
          },
          {
            $project: {
              fingerprint: 1,
              sourceHash: 1,
              source: { $arrayElemAt: ["$sources", 0] },
            },
          },
        ]).exec();
        if (question) {
          if (question.fingerprint !== fingerprint)
            throw new HttpError(
              409,
              "This Q_ID has different recorded requirements. No code was submitted.",
            );
          const source = question.source;
          if (
            !source ||
            source.courseId !== courseId ||
            typeof source.solution !== "string"
          )
            throw new HttpError(
              422,
              "This Q_ID is indexed but has no confirmed solution link. No code was submitted.",
            );
          if (
            createHash("sha256").update(source.solution).digest("hex") !==
            question.sourceHash
          )
            throw new HttpError(
              409,
              "The source linked to this Q_ID has changed and needs review. No code was submitted.",
            );
          prepareMandatoryCode(source.solution, mandatory);
          return {
            id: source._id.toString(),
            title: source.title,
            filename: source.filename,
            solution: source.solution,
            score: 1,
          };
        }
      }
      // Verified question IDs distinguish renamed questions and variants with
      // identical introductions, and avoid embedding work for proven matches.
      if (questionId) {
        const verified = await Solution.findOne({
          courseId,
          verifiedQuestionId: questionId,
          verifiedPercentage: 100,
          $or: [
            { verifiedFingerprint: fingerprint },
            {
              verifiedFingerprint: { $exists: false },
              embeddingHash: this.embeddings.hash(text),
            },
          ],
        })
          .select("title filename solution")
          .lean()
          .exec();
        if (
          verified &&
          typeof verified.solution === "string" &&
          verified.solution.trim()
        ) {
          try {
            prepareMandatoryCode(verified.solution, mandatory);
            return {
              id: verified._id.toString(),
              title: verified.title,
              filename: verified.filename,
              solution: verified.solution,
              score: 1,
            };
          } catch (error) {
            if (!(error instanceof HttpError) || error.status !== 422)
              throw error;
          }
        }
      }
      if (questionId) {
        const binding = await SolutionBinding.findOne({
          courseId,
          questionId,
          fingerprint,
        })
          .lean()
          .exec();
        if (binding) {
          const linked = await Solution.findOne({
            _id: binding.solutionId,
            courseId,
          })
            .select("title filename solution")
            .lean()
            .exec();
          if (
            linked &&
            typeof linked.solution === "string" &&
            createHash("sha256").update(linked.solution).digest("hex") ===
              binding.sourceHash
          ) {
            try {
              prepareMandatoryCode(linked.solution, mandatory);
              return {
                id: linked._id.toString(),
                title: linked.title,
                filename: linked.filename,
                solution: linked.solution,
                score: 1,
              };
            } catch (error) {
              if (!(error instanceof HttpError) || error.status !== 422)
                throw error;
            }
          }
        }
      }
      const [vector] = await this.embeddings.embed([text]);
      if (!vector) throw new Error("Missing query embedding.");
      const retrieve = (limit: number) =>
        Solution.aggregate<SearchResult>([
          {
            $vectorSearch: {
              index: this.config.embedding.indexName,
              path: "embedding",
              queryVector: vector,
              exact: true,
              limit,
              filter: {
                courseId,
                embeddingModel: this.config.embedding.model,
                embeddingRevision: this.config.embedding.revision,
                embeddingVersion: this.embeddings.version,
              },
            },
          },
          {
            $project: {
              title: 1,
              filename: 1,
              solution: 1,
              verifiedFingerprint: 1,
              score: { $meta: "vectorSearchScore" },
            },
          },
        ]).exec();
      results = await retrieve(5);
      // Preserve successful existing lookups. Expand only when the short list
      // contains no compatible variant, reusing the same query embedding.
      if (
        results.length === 5 &&
        !results.some((candidate) => {
          if (
            candidate.verifiedFingerprint &&
            candidate.verifiedFingerprint !== fingerprint
          )
            return false;
          if (
            typeof candidate.solution !== "string" ||
            !candidate.solution.trim()
          )
            return false;
          try {
            prepareMandatoryCode(candidate.solution, mandatory);
            return true;
          } catch (error) {
            if (error instanceof HttpError && error.status === 422)
              return false;
            throw error;
          }
        })
      )
        results = await retrieve(50);
    } catch (error) {
      if (error instanceof HttpError) throw error;
      logger.error("Solution lookup failed");
      throw new HttpError(
        503,
        "Solution search is unavailable. Check the embedding model and MongoDB vector index.",
      );
    }
    results = results.filter(
      (candidate) =>
        !candidate.verifiedFingerprint ||
        candidate.verifiedFingerprint === fingerprint,
    );
    const compatible = mandatory.length
      ? results.filter((candidate) => {
          if (
            typeof candidate.solution !== "string" ||
            !candidate.solution.trim()
          )
            return false;
          try {
            prepareMandatoryCode(candidate.solution, mandatory);
            return true;
          } catch (error) {
            if (error instanceof HttpError && error.status === 422)
              return false;
            throw error;
          }
        })
      : results;
    if (results.length && !compatible.length) {
      throw new HttpError(
        422,
        "None of the matched database solutions satisfies this question's mandatory requirements. No code was submitted.",
      );
    }
    const first = compatible[0];
    if (!first)
      throw new HttpError(
        404,
        "No indexed solutions were found for this course.",
      );
    if (typeof first.solution !== "string" || !first.solution.trim()) {
      throw new HttpError(
        422,
        "The matched solution does not contain source code.",
      );
    }
    const score = 2 * first.score - 1;
    const second = compatible.find(
      (item) =>
        typeof item.solution === "string" &&
        item.solution.trim() !== first.solution.trim(),
    );
    const margin = second ? score - (2 * second.score - 1) : 1;
    if (
      !Number.isFinite(score) ||
      !Number.isFinite(margin) ||
      score < this.config.embedding.minScore ||
      margin < this.config.embedding.minMargin
    ) {
      throw new HttpError(
        409,
        "No confident, unique solution match was found. No code was submitted.",
      );
    }
    return {
      id: first._id.toString(),
      title: first.title,
      filename: first.filename,
      solution: first.solution,
      score,
    };
  }
}
