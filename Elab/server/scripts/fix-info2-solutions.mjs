import { existsSync, readFileSync, writeFileSync, mkdirSync } from "node:fs";
import { resolve } from "node:path";
import { parseEnv } from "node:util";
import mongoose from "mongoose";
import { ELAB_CONFIG, EMBEDDING_CONFIG } from "../dist/src/config/settings.js";
import { ElabService } from "../dist/src/services/elab.service.js";
import { EmbeddingService } from "../dist/src/services/embedding.service.js";
import { parseElabToken } from "../dist/src/utils/elab-token.js";
import { prepareSubmissionCode } from "../dist/src/utils/mandatory-code.js";
import { questionFingerprint } from "../dist/src/utils/question-fingerprint.js";
import { submissionLanguage } from "../dist/src/utils/submission-language.js";
const { studentInfo, authorization } = parseElabToken(
  readFileSync(process.env.ELAB_TOKEN_FILE, "utf8").trim(),
);
const elab = new ElabService(ELAB_CONFIG);
const courses = await elab.registeredCourses(studentInfo, authorization);
const course = courses.data.courses.find((c) => c.COURSE_ID === 26);
const a = parseEnv(readFileSync(".env", "utf8")),
  b = parseEnv(readFileSync(".env.local", "utf8"));
const config = {
  ...EMBEDDING_CONFIG,
  cacheDir: resolve(EMBEDDING_CONFIG.cacheDir),
};
const embeddings = new EmbeddingService(config);
const folder = "info2/fixes";
mkdirSync(folder, { recursive: true });
try {
  await mongoose.connect(b.MONGODB_URI || a.MONGODB_URI, {
    serverSelectionTimeoutMS: 10000,
  });
  for (const value of process.argv.slice(2)) {
    const seq = Number(value);
    let report;
    try {
      parseElabToken(authorization);
      const file = ["c", "cpp"]
        .map((ext) => `solutions/account2/question-${seq}.${ext}`)
        .find(existsSync);
      const question = JSON.parse(
        readFileSync(`info2/question-${seq}.json`, "utf8"),
      ).questionData;
      const code = prepareSubmissionCode(
        readFileSync(file, "utf8"),
        question.MANDATORY,
        question.COMPLEXITY[2],
      );
      const current = await elab.getQuestionInfo(
        studentInfo,
        course,
        seq,
        "S",
        authorization,
      );
      if (current.data.studentData?.Q_ID !== `DS_REGULAR_SET1_${question.key}`)
        throw new Error("Question mismatch");
      const language = submissionLanguage(code);
      const logs = await elab.saveQuestionLogs(
        studentInfo,
        code,
        "0",
        authorization,
        language,
      );
      if (logs.data.Status !== 1) throw new Error("Logs failed");
      const evaluation = await elab.evaluateQuestion(
        studentInfo,
        current.data.studentData,
        code,
        authorization,
        language,
      );
      report = {
        sequenceId: seq,
        language,
        result: evaluation.data.result,
        updatedAt: new Date().toISOString(),
      };
      if (
        Number(report.result?.evalPercentage) === 100 &&
        report.result?.statusCode === "200"
      ) {
        const fingerprint = questionFingerprint(question.Q_DESC, question.MANDATORY, { complexity: question.COMPLEXITY, testcases: question.TESTCASES });
        const filename = `variant_DS_REGULAR_SET1_${question.key}_${fingerprint.slice(0,16)}.` + language;
        const text = embeddings.normalize(question.Q_DESC);
        const [embedding] = await embeddings.embed([text]);
        const collection = mongoose.connection.collection("solutions");
        const existing = await collection.findOne({
          category: "dsa",
          filename,
        });
        const doc = {
          filename,
          title: question.Q_DESC.replace(
            /^(?:problem|question)\s+(?:description|statement)\s*:?\s*/i,
            "",
          ).slice(0, 100),
          category: "dsa",
          categoryLabel: "Data Structures",
          courseId: 26,
          tags: ["Data Structures"],
          solution: code,
          embedding,
          embeddingText: text,
          embeddingModel: config.model,
          embeddingRevision: config.revision,
          embeddingVersion: embeddings.version,
          embeddingHash: embeddings.hash(text),
          embeddingUpdatedAt: new Date(),
          verifiedQuestionId: current.data.studentData.Q_ID,
          verifiedPercentage: 100,
          verifiedFingerprint: fingerprint,
        };
        if (existing && existing.solution !== code)
          throw new Error("Existing variant has different source; refusing to overwrite");
        if (!existing) await collection.insertOne(doc);
        report.questionId = current.data.studentData.Q_ID;
        report.fingerprint = fingerprint;
        report.solutionId = (existing?._id || doc._id)?.toString();
        report.savedToDatabase = true;
      }
    } catch (e) {
      report = {
        sequenceId: seq,
        error: e.status ? e.message : e.name,
        status: e.status,
      };
    }
    writeFileSync(
      `${folder}/question-${seq}.json`,
      JSON.stringify(report, null, 2) + "\n",
      { mode: 0o600 },
    );
    console.log(
      JSON.stringify({
        sequenceId: seq,
        score: report.result?.evalPercentage,
        saved: report.savedToDatabase,
        error: report.error,
      }),
    );
  }
} finally {
  await mongoose.disconnect();
}
