import { readFileSync, writeFileSync, mkdirSync, readdirSync } from "node:fs";
import { parseEnv } from "node:util";
import { resolve } from "node:path";
import mongoose from "mongoose";
import { EMBEDDING_CONFIG } from "../dist/src/config/settings.js";
import { EmbeddingService } from "../dist/src/services/embedding.service.js";
import { SolutionSearchService } from "../dist/src/services/solution-search.service.js";
import { prepareMandatoryCode } from "../dist/src/utils/mandatory-code.js";

// Read-only audit: no question submissions and no database writes.
const env = {
  ...parseEnv(readFileSync(".env", "utf8")),
  ...parseEnv(readFileSync(".env.local", "utf8")),
};
const config = {
  mongodbUri: env.MONGODB_URI,
  embedding: {
    ...EMBEDDING_CONFIG,
    cacheDir: resolve(EMBEDDING_CONFIG.cacheDir),
  },
};
const service = new SolutionSearchService(
  config,
  new EmbeddingService(config.embedding),
);
const summary = JSON.parse(readFileSync("info2/summary.json", "utf8"));
const report = {
  generatedAt: new Date().toISOString(),
  submissions: 0,
  databaseWrites: 0,
  results: [],
};
try {
  await mongoose.connect(config.mongodbUri, {
    serverSelectionTimeoutMS: 10000,
  });
  const records = await mongoose.connection
    .collection("solutions")
    .find({ courseId: 26 }, { projection: { solution: 1 } })
    .toArray();
  for (const [key, original] of Object.entries(summary.results)) {
    if (original.status !== "error") continue;
    const saved = JSON.parse(
      readFileSync(`info2/question-${key}.json`, "utf8"),
    );
    const q = saved.questionData;
    let compatibleRecords = 0;
    for (const record of records) {
      try {
        prepareMandatoryCode(record.solution, q.MANDATORY);
        compatibleRecords++;
      } catch {}
    }
    const entry = {
      sequenceId: Number(key),
      questionId: saved.studentData.Q_ID,
      compatibleRecords,
    };
    try {
      const match = await service.find(
        q.Q_DESC,
        26,
        q.MANDATORY,
        entry.questionId,
        { complexity: q.COMPLEXITY, testcases: q.TESTCASES },
      );
      entry.status = "matched";
      entry.match = {
        id: match.id,
        title: match.title,
        filename: match.filename,
        score: match.score,
      };
    } catch (error) {
      entry.status =
        compatibleRecords === 0
          ? "no-compatible-stored-source"
          : "no-confident-match";
      entry.error = error.status ? error.message : error.name;
    }
    report.results.push(entry);
    console.log(JSON.stringify(entry));
    mkdirSync("info2/matching", { recursive: true });
    writeFileSync(
      "info2/matching/audit.json",
      JSON.stringify(report, null, 2) + "\n",
    );
  }
  report.firstAccount = [];
  const firstFolder = "info/course-26-86-300";
  for (const name of readdirSync(`${firstFolder}/fixes`).filter((name) =>
    /^question-\d+\.json$/.test(name),
  )) {
    const previous = JSON.parse(
      readFileSync(`${firstFolder}/fixes/${name}`, "utf8"),
    );
    if (
      !previous.savedToDatabase ||
      Number(previous.result?.evalPercentage) !== 100
    )
      continue;
    const q = JSON.parse(
      readFileSync(`${firstFolder}/${name}`, "utf8"),
    ).questionData;
    const entry = { sequenceId: previous.sequenceId };
    try {
      const match = await service.find(
        q.Q_DESC,
        26,
        q.MANDATORY,
        `DS_REGULAR_SET1_${q.key}`,
        { complexity: q.COMPLEXITY, testcases: q.TESTCASES },
      );
      entry.status = "matched";
      entry.solutionId = match.id;
      entry.sameVerifiedRecord =
        match.filename ===
        `verified_DS_REGULAR_SET1_${q.key}.${previous.language}`;
    } catch (error) {
      entry.status = "error";
      entry.error = error.status ? error.message : error.name;
    }
    report.firstAccount.push(entry);
  }
  writeFileSync(
    "info2/matching/audit.json",
    JSON.stringify(report, null, 2) + "\n",
  );
  console.log(
    JSON.stringify({
      firstAccountChecked: report.firstAccount.length,
      firstAccountRetained: report.firstAccount.filter(
        (x) => x.sameVerifiedRecord,
      ).length,
    }),
  );
} finally {
  await mongoose.disconnect();
}
