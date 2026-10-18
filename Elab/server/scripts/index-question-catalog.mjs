import { existsSync, mkdirSync, readFileSync, writeFileSync } from "node:fs";
import { resolve } from "node:path";
import { parseEnv } from "node:util";
import { createHash } from "node:crypto";
import mongoose from "mongoose";
import { EMBEDDING_CONFIG } from "../dist/src/config/settings.js";
import { EmbeddingService } from "../dist/src/services/embedding.service.js";
import { questionFingerprint } from "../dist/src/utils/question-fingerprint.js";
import {
  prepareMandatoryCode,
  sourceTokenHash,
} from "../dist/src/utils/mandatory-code.js";

const write = process.argv.includes("--write");
const paths = [
  process.env.ELAB_CATALOG_ACCOUNT1_FILE,
  process.env.ELAB_CATALOG_ACCOUNT2_FILE,
];
if (paths.some((path) => !path))
  throw new Error(
    "Set ELAB_CATALOG_ACCOUNT1_FILE and ELAB_CATALOG_ACCOUNT2_FILE to the private account snapshots.",
  );
const snapshots = paths.map((path) => JSON.parse(readFileSync(path, "utf8")));
const env = Object.assign(
  {},
  ...[".env", ".env.local"]
    .filter(existsSync)
    .map((path) => parseEnv(readFileSync(path, "utf8"))),
);
const embedding = {
  ...EMBEDDING_CONFIG,
  cacheDir: resolve(EMBEDDING_CONFIG.cacheDir),
};
const embeddings = new EmbeddingService(embedding);
const reportFolder = "reports/question-catalog";
mkdirSync(reportFolder, { recursive: true });
const hash = (value) => createHash("sha256").update(value).digest("hex");
const report = {
  startedAt: new Date().toISOString(),
  mode: write ? "write" : "dry-run",
  accounts: [],
  conflicts: [],
  unresolved: [],
  linked: [],
  sourceChanges: 0,
};
const save = () =>
  writeFileSync(
    `${reportFolder}/summary.json`,
    JSON.stringify(report, null, 2) + "\n",
  );
try {
  await mongoose.connect(process.env.MONGODB_URI || env.MONGODB_URI, {
    serverSelectionTimeoutMS: 10000,
  });
  const solutions = mongoose.connection.collection("solutions");
  const records = await solutions
    .find({ courseId: 26 }, { projection: { embedding: 0 } })
    .toArray();
  const baseline = new Map(
    records.map((record) => [String(record._id), hash(record.solution)]),
  );
  const byId = new Map(records.map((record) => [String(record._id), record]));
  const byCode = new Map();
  for (const record of records) {
    const key = sourceTokenHash(record.solution);
    const group = byCode.get(key) || [];
    group.push(record);
    byCode.set(key, group);
  }
  const aliases = await mongoose.connection
    .collection("solution_bindings")
    .find({ courseId: 26 })
    .toArray();
  const observations = new Map();
  for (let account = 0; account < snapshots.length; account++) {
    for (const observation of Object.values(snapshots[account].questions)) {
      const q = observation.questionData;
      observation.fingerprint = questionFingerprint(q.Q_DESC, q.MANDATORY, {
        complexity: q.COMPLEXITY,
        testcases: q.TESTCASES,
      });
      const list = observations.get(observation.Q_ID) || [];
      list.push({ ...observation, account: account + 1 });
      observations.set(observation.Q_ID, list);
    }
  }
  const collection = mongoose.connection.collection("question_catalog");
  if (write)
    await collection.createIndex({ courseId: 1, Q_ID: 1 }, { unique: true });
  const existing = new Map(
    (
      await collection
        .find(
          { courseId: 26 },
          { projection: { Q_ID: 1, fingerprint: 1, solutionId: 1 } },
        )
        .toArray()
    ).map((q) => [q.Q_ID, q]),
  );
  const seen = new Map();
  const pending = [];
  const compatible = (record, q) => {
    try {
      prepareMandatoryCode(record.solution, q.MANDATORY);
      return true;
    } catch {
      return false;
    }
  };
  for (let account = 0; account < snapshots.length; account++) {
    const counts = {
      account: account + 1,
      scanned: 0,
      added: 0,
      duplicatesSkipped: 0,
      alreadyIndexed: 0,
      linked: 0,
      unlinked: 0,
    };
    for (const observation of Object.values(snapshots[account].questions).sort(
      (a, b) => a.sequenceId - b.sequenceId,
    )) {
      counts.scanned++;
      const { Q_ID, fingerprint, questionData: q } = observation;
      const earlier = seen.get(Q_ID) || existing.get(Q_ID);
      if (earlier) {
        if (earlier.fingerprint !== fingerprint)
          report.conflicts.push({
            Q_ID,
            account: account + 1,
            sequenceId: observation.sequenceId,
            reason:
              "Same Q_ID has different requirements; original entry preserved.",
          });
        if (seen.has(Q_ID)) counts.duplicatesSkipped++;
        else counts.alreadyIndexed++;
        seen.set(Q_ID, earlier);
        continue;
      }
      seen.set(Q_ID, { fingerprint });
      let selected, evidence;
      const verified = records.filter(
        (record) =>
          record.verifiedQuestionId === Q_ID &&
          record.verifiedPercentage === 100 &&
          (!record.verifiedFingerprint ||
            record.verifiedFingerprint === fingerprint) &&
          compatible(record, q),
      );
      if (verified.length) {
        selected = verified[0];
        evidence = "existing-verified-100";
      }
      if (!selected) {
        const alias = aliases.find(
          (alias) =>
            alias.questionId === Q_ID && alias.fingerprint === fingerprint,
        );
        const record = alias && byId.get(String(alias.solutionId));
        if (
          record &&
          hash(record.solution) === alias.sourceHash &&
          compatible(record, q)
        ) {
          selected = record;
          evidence = "existing-reviewed-binding";
        }
      }
      if (!selected) {
        // A byte/token identity with the account's stored submission is evidence
        // of identity, not a claim that every judge check passed.
        for (const other of observations.get(Q_ID)) {
          if (other.fingerprint !== fingerprint) continue;
          for (const code of other.storedCode || []) {
            if (typeof code.value !== "string" || !code.value.trim()) continue;
            const matches = (
              byCode.get(sourceTokenHash(code.value)) || []
            ).filter((record) => compatible(record, q));
            if (matches.length) {
              selected = matches[0];
              evidence = `account-${other.account}-stored-source`;
              break;
            }
          }
          if (selected) break;
        }
      }
      const text = `Required constructs: ${(q.MANDATORY || []).join("; ")}\n${q.Q_DESC}`;
      const doc = {
        courseId: 26,
        Q_ID,
        fingerprint,
        description: q.Q_DESC,
        mandatory: q.MANDATORY,
        complexity: q.COMPLEXITY,
        testcases: q.TESTCASES,
        discoveredAccount: account + 1,
        firstSequence: observation.sequenceId,
        embeddingText: text,
        embeddingModel: embedding.model,
        embeddingRevision: embedding.revision,
        embeddingVersion: "question-catalog-full-v1",
        embeddingHash: hash(
          JSON.stringify([
            embedding.model,
            embedding.revision,
            "question-catalog-full-v1",
            text,
          ]),
        ),
        createdAt: new Date(),
      };
      if (selected) {
        doc.solutionId = selected._id;
        doc.sourceHash = hash(selected.solution);
        doc.evidence = evidence;
        counts.linked++;
        report.linked.push({
          Q_ID,
          solutionId: String(selected._id),
          evidence,
        });
      } else {
        counts.unlinked++;
        report.unresolved.push({
          Q_ID,
          account: account + 1,
          sequenceId: observation.sequenceId,
          title: q.Q_DESC.replace(
            /^(question|problem)\s+description\s*:?\s*/i,
            "",
          ).slice(0, 150),
          reason:
            "No verified or source-identical existing solution link; no name-based guess was recorded.",
        });
      }
      pending.push(doc);
      counts.added++;
    }
    report.accounts.push(counts);
  }
  report.uniqueQuestions = seen.size;
  report.newEntries = pending.length;
  save();
  console.log(
    JSON.stringify({
      phase: "plan",
      accounts: report.accounts,
      uniqueQuestions: report.uniqueQuestions,
      conflicts: report.conflicts.length,
    }),
  );
  if (write) {
    let completed = 0;
    for (let i = 0; i < pending.length; i += 8) {
      const batch = pending.slice(i, i + 8);
      const vectors = await embeddings.embed(
        batch.map((doc) => doc.embeddingText),
      );
      for (let j = 0; j < batch.length; j++) batch[j].embedding = vectors[j];
      await collection.insertMany(batch, { ordered: true });
      completed += batch.length;
      report.inserted = completed;
      save();
      console.log(
        JSON.stringify({
          phase: "index",
          inserted: completed,
          total: pending.length,
        }),
      );
    }
  }
  const current = await solutions
    .find({ courseId: 26 }, { projection: { solution: 1 } })
    .toArray();
  report.sourceChanges =
    current.filter(
      (record) => baseline.get(String(record._id)) !== hash(record.solution),
    ).length +
    records.filter(
      (record) =>
        !current.some((now) => String(now._id) === String(record._id)),
    ).length;
  report.finishedAt = new Date().toISOString();
  save();
  console.log(
    JSON.stringify({
      complete: true,
      uniqueQuestions: report.uniqueQuestions,
      linked: report.linked.length,
      unresolved: report.unresolved.length,
      sourceChanges: report.sourceChanges,
    }),
  );
} finally {
  await mongoose.disconnect();
}
