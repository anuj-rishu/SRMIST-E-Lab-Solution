import { readFileSync, writeFileSync } from "node:fs";
import { parseEnv } from "node:util";
import mongoose from "mongoose";
import { EMBEDDING_CONFIG } from "../dist/src/config/settings.js";
import { SolutionSearchService } from "../dist/src/services/solution-search.service.js";
const env = {
  ...parseEnv(readFileSync(".env", "utf8")),
  ...parseEnv(readFileSync(".env.local", "utf8")),
};
const snapshots = [
  process.env.ELAB_CATALOG_ACCOUNT1_FILE,
  process.env.ELAB_CATALOG_ACCOUNT2_FILE,
].map((path) => JSON.parse(readFileSync(path, "utf8")));
let embeddingCalls = 0;
const service = new SolutionSearchService(
  { mongodbUri: env.MONGODB_URI, embedding: EMBEDDING_CONFIG },
  {
    normalize: (text) => text.trim(),
    hash: (text) => text,
    embed: async () => {
      embeddingCalls++;
      throw Error("Known Q_ID must not use embeddings");
    },
    version: "unused",
  },
);
try {
  await mongoose.connect(env.MONGODB_URI, { serverSelectionTimeoutMS: 10000 });
  const docs = await mongoose.connection
    .collection("question_catalog")
    .find({ courseId: 26 })
    .toArray();
  const byId = new Map(docs.map((doc) => [doc.Q_ID, doc]));
  if (docs.length !== 437 || byId.size !== 437)
    throw Error("Unexpected catalog ID count");
  if (
    docs.some(
      (doc) =>
        doc.embedding?.length !== EMBEDDING_CONFIG.dimensions ||
        doc.embedding.some((v) => !Number.isFinite(v)),
    )
  )
    throw Error("Invalid embedding");
  const report = {
    checkedAt: new Date().toISOString(),
    catalogEntries: docs.length,
    validEmbeddings: docs.length,
    accounts: [],
    embeddingCalls: 0,
    problems: [],
  };
  const rows = [];
  for (let account = 0; account < snapshots.length; account++) {
    const counts = {
      account: account + 1,
      checked: 0,
      matched: 0,
      unlinkedBlocked: 0,
    };
    for (const observation of Object.values(snapshots[account].questions)) {
      counts.checked++;
      const q = observation.questionData,
        doc = byId.get(observation.Q_ID);
      try {
        const match = await service.find(
          q.Q_DESC,
          26,
          q.MANDATORY,
          observation.Q_ID,
          { complexity: q.COMPLEXITY, testcases: q.TESTCASES },
        );
        if (!doc.solutionId || match.id !== String(doc.solutionId))
          throw Error("Wrong solution selected");
        counts.matched++;
      } catch (error) {
        if (!doc.solutionId && error.status === 422) counts.unlinkedBlocked++;
        else
          report.problems.push({
            account: account + 1,
            sequenceId: observation.sequenceId,
            Q_ID: observation.Q_ID,
            error: error.status ? error.message : error.name,
          });
      }
    }
    report.accounts.push(counts);
  }
  for (const doc of docs) {
    const entry = {
      Q_ID: doc.Q_ID,
      solutionId: doc.solutionId ? String(doc.solutionId) : null,
      evidence: doc.evidence || null,
      sequences: {},
    };
    for (let account = 0; account < snapshots.length; account++) {
      const match = Object.values(snapshots[account].questions).find(
        (q) => q.Q_ID === doc.Q_ID,
      );
      if (match) entry.sequences[`account${account + 1}`] = match.sequenceId;
    }
    rows.push(entry);
  }
  report.embeddingCalls = embeddingCalls;
  writeFileSync(
    "reports/question-catalog/verification.json",
    JSON.stringify(report, null, 2) + "\n",
  );
  writeFileSync(
    "reports/question-catalog/qid-map.json",
    JSON.stringify(rows, null, 2) + "\n",
  );
  console.log(JSON.stringify(report));
  if (report.problems.length || embeddingCalls) process.exitCode = 1;
} finally {
  await mongoose.disconnect();
}
