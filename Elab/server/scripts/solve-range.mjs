import {
  existsSync,
  mkdirSync,
  readFileSync,
  writeFileSync,
  renameSync,
  unlinkSync,
} from "node:fs";
import { resolve } from "node:path";
import { parseEnv } from "node:util";
import { fileURLToPath } from "node:url";
import { createHash } from "node:crypto";
import mongoose from "mongoose";
import { ELAB_CONFIG, EMBEDDING_CONFIG } from "../dist/src/config/settings.js";
import { ElabService } from "../dist/src/services/elab.service.js";
import { EmbeddingService } from "../dist/src/services/embedding.service.js";
import { SolutionSearchService } from "../dist/src/services/solution-search.service.js";
import { QuestionService } from "../dist/src/services/question.service.js";
import { parseElabToken } from "../dist/src/utils/elab-token.js";

const root = fileURLToPath(new URL("../", import.meta.url));
const start = Number(process.argv[2] || 86),
  end = Number(process.argv[3] || 300);
if (
  !Number.isSafeInteger(start) ||
  !Number.isSafeInteger(end) ||
  start < 1 ||
  end < start
)
  throw new Error("Use: node scripts/solve-range.mjs START END");
const token = process.env.ELAB_TOKEN_FILE
  ? readFileSync(process.env.ELAB_TOKEN_FILE, "utf8").trim()
  : process.env.ELAB_TOKEN;
const { studentInfo, authorization } = parseElabToken(token);
const base = parseEnv(readFileSync(resolve(root, ".env"), "utf8"));
const local = existsSync(resolve(root, ".env.local"))
  ? parseEnv(readFileSync(resolve(root, ".env.local"), "utf8"))
  : {};
const embedding = {
  ...EMBEDDING_CONFIG,
  cacheDir: resolve(root, EMBEDDING_CONFIG.cacheDir),
};
const matcher = new SolutionSearchService(
  {
    mongodbUri:
      process.env.MONGODB_URI || local.MONGODB_URI || base.MONGODB_URI,
    embedding,
  },
  new EmbeddingService(embedding),
);
const elab = new ElabService(ELAB_CONFIG);
const folder = resolve(
  root,
  process.env.ELAB_REPORT_DIR || `info/course-26-${start}-${end}`,
);
mkdirSync(folder, { recursive: true });
const manifestPath = resolve(folder, "summary.json");
const manifest = existsSync(manifestPath)
  ? JSON.parse(readFileSync(manifestPath, "utf8"))
  : { courseId: 26, start, end, results: {} };
const accountHash = createHash("sha256")
  .update(String(studentInfo.USER_ID))
  .digest("hex");
if (manifest.accountHash && manifest.accountHash !== accountHash)
  throw new Error(
    "Report folder belongs to another account. Use a different ELAB_REPORT_DIR.",
  );
manifest.accountHash = accountHash;
function save(path, value) {
  writeFileSync(path + ".tmp", JSON.stringify(value, null, 2) + "\n", {
    mode: 0o600,
  });
  renameSync(path + ".tmp", path);
}
let stopped = false;
process.on("SIGINT", () => {
  stopped = true;
});
process.on("SIGTERM", () => {
  stopped = true;
});
try {
  const courses = await elab.registeredCourses(studentInfo, authorization);
  const course = courses.data?.courses?.find((c) => c.COURSE_ID === 26);
  if (!course) throw new Error("Registered DS course not found. Check token.");
  for (let sequenceId = start; sequenceId <= end && !stopped; sequenceId++) {
    if (
      process.env.ELAB_RETRY_TIMEOUTS_ONLY === "1" &&
      !/timed out/i.test(manifest.results[sequenceId]?.error || "")
    )
      continue;
    if (
      manifest.results[sequenceId]?.status === "passed" ||
      manifest.results[sequenceId]?.status === "already-complete"
    )
      continue;
    let question;
    let entry;
    try {
      parseElabToken(authorization); // Stop when this login expires.
      question = await elab.getQuestionInfo(
        studentInfo,
        course,
        sequenceId,
        "S",
        authorization,
      );
      if (
        question.status !== 200 ||
        question.data?.Status !== 1 ||
        question.data.studentData?.SEQUENCE_ID !== sequenceId ||
        typeof question.data.questionData?.Q_DESC !== "string"
      ) {
        const error = new Error(
          "Question details unavailable or identity mismatch.",
        );
        error.status = question.status;
        throw error;
      }
      if (
        question.data.studentData.STATUS === 2 &&
        process.env.ELAB_RECHECK_COMPLETE !== "1"
      ) {
        entry = {
          status: "already-complete",
          questionId: question.data.studentData.Q_ID,
        };
      } else {
        // Reuse the details already fetched for this question; no second getinfo.
        const service = new QuestionService(
          {
            getQuestionInfo: async () => question,
            saveQuestionLogs: (...args) => elab.saveQuestionLogs(...args),
            evaluateQuestion: (...args) => elab.evaluateQuestion(...args),
          },
          matcher,
        );
        const response = await service.solve(
          studentInfo,
          { course, sequenceId, input: "0" },
          authorization,
        );
        const result = response.data?.result;
        const score = Number(result?.evalPercentage);
        const passed =
          response.status === 200 &&
          response.data?.Status === 1 &&
          result?.statusCode === "200" &&
          score === 100;
        entry = {
          status: passed ? "passed" : "needs-review",
          questionId: question.data.studentData.Q_ID,
          score: Number.isFinite(score) ? score : null,
          language: response.data?.language,
          result,
          matchedSolution: response.data?.matchedSolution,
          stage: response.data?.stage,
        };
      }
    } catch (error) {
      entry = {
        status: "error",
        httpStatus: error.status,
        error: error.status ? error.message : error.name,
      };
      if (error.status === 401 || error.status === 403) stopped = true;
    }
    entry.updatedAt = new Date().toISOString();
    manifest.results[sequenceId] = entry;
    const questionPath = resolve(folder, `question-${sequenceId}.json`);
    if (entry.status !== "passed" && entry.status !== "already-complete") {
      const student = question?.data?.studentData;
      save(questionPath, {
        sequenceId,
        courseId: 26,
        studentData: student
          ? {
              Q_ID: student.Q_ID,
              SEQUENCE_ID: student.SEQUENCE_ID,
              STATUS: student.STATUS,
              COURSE_ID: student.COURSE_ID,
            }
          : undefined,
        questionData: question?.data?.questionData,
        evaluation: entry,
      });
    } else if (existsSync(questionPath)) {
      unlinkSync(questionPath);
    }
    save(manifestPath, manifest);
    console.log(
      JSON.stringify({
        sequenceId,
        status: entry.status,
        score: entry.score,
        error: entry.error,
      }),
    );
  }
} finally {
  manifest.finishedAt = new Date().toISOString();
  manifest.stopped = stopped;
  save(manifestPath, manifest);
  await mongoose.disconnect();
  console.log(
    JSON.stringify({
      reportFolder: folder,
      counts: Object.values(manifest.results).reduce((a, r) => {
        a[r.status] = (a[r.status] || 0) + 1;
        return a;
      }, {}),
    }),
  );
}
