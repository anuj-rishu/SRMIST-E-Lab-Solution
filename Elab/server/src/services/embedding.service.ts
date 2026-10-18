import { pipeline } from "@huggingface/transformers";
import type { FeatureExtractionPipeline } from "@huggingface/transformers";
import { createHash } from "node:crypto";
import type { EmbeddingConfig } from "../config/env.js";
import { embeddingText } from "../utils/question-text.js";
import { logger } from "../utils/logger.js";

export class EmbeddingService {
  private extractor: Promise<FeatureExtractionPipeline> | undefined;
  readonly version: string;

  constructor(readonly config: EmbeddingConfig) {
    this.version = `intro-${config.textLength}-q8-v1`;
  }

  normalize(text: string): string {
    return embeddingText(text, this.config.textLength);
  }

  hash(text: string): string {
    return createHash("sha256")
      .update(
        JSON.stringify([
          this.config.model,
          this.config.revision,
          this.config.dimensions,
          this.version,
          text,
        ]),
      )
      .digest("hex");
  }

  private async getExtractor(): Promise<FeatureExtractionPipeline> {
    if (!this.extractor) {
      logger.info(
        { model: this.config.model },
        "Loading local embedding model",
      );
      this.extractor = pipeline("feature-extraction", this.config.model, {
        dtype: "q8",
        device: "cpu",
        cache_dir: this.config.cacheDir,
        revision: this.config.revision,
        session_options: { intraOpNumThreads: 2 },
      }).catch((error: unknown) => {
        this.extractor = undefined;
        throw error;
      });
    }
    return this.extractor;
  }

  async embed(texts: string[]): Promise<number[][]> {
    if (!texts.length) return [];
    if (texts.some((text) => !text.trim()))
      throw new Error("Cannot embed empty question text.");
    const extractor = await this.getExtractor();
    const tensor = await extractor(texts, { pooling: "mean", normalize: true });
    const vectors: unknown = tensor.tolist();
    if (!Array.isArray(vectors) || vectors.length !== texts.length) {
      throw new Error("Embedding model returned an invalid batch.");
    }
    return vectors.map((vector: unknown) => {
      if (
        !Array.isArray(vector) ||
        vector.length !== this.config.dimensions ||
        !vector.every(
          (value: unknown) =>
            typeof value === "number" && Number.isFinite(value),
        )
      ) {
        throw new Error("Embedding dimensions do not match configuration.");
      }
      return vector as number[];
    });
  }
}
