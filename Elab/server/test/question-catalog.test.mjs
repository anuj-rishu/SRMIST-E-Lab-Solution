import assert from "node:assert/strict";
import { createHash } from "node:crypto";
import { test } from "node:test";
import mongoose from "mongoose";
import { QuestionCatalog } from "../dist/src/models/question-catalog.model.js";
import { Solution } from "../dist/src/models/solution.model.js";
import { SolutionBinding } from "../dist/src/models/solution-binding.model.js";
import { SolutionSearchService } from "../dist/src/services/solution-search.service.js";
import { questionFingerprint } from "../dist/src/utils/question-fingerprint.js";
import { sourceTokenHash } from "../dist/src/utils/mandatory-code.js";

const config = {
  mongodbUri: "mongodb://127.0.0.1/test",
  embedding: {
    model: "test",
    revision: "test",
    indexName: "test",
    minScore: 0.85,
    minMargin: 0.04,
  },
};
const requirements = {
  complexity: [2, 200, 30],
  testcases: [{ INPUT: "1", OUTPUT: "1" }],
};
const source = {
  _id: "source-1",
  courseId: 26,
  title: "Same introduction",
  filename: "source.c",
  solution: "int main(){return 0;}",
};
const sha = (code) => createHash("sha256").update(code).digest("hex");
function fixture(t, question) {
  const calls = { catalog: 0, embedding: 0, vector: 0 };
  t.mock.method(mongoose, "connect", async () => mongoose);
  t.mock.method(QuestionCatalog, "aggregate", (pipeline) => {
    calls.catalog++;
    return { exec: async () => question(pipeline[0].$match) };
  });
  t.mock.method(Solution, "findOne", () => ({
    select: () => ({ lean: () => ({ exec: async () => null }) }),
  }));
  t.mock.method(SolutionBinding, "findOne", () => ({
    lean: () => ({ exec: async () => null }),
  }));
  t.mock.method(Solution, "aggregate", () => {
    calls.vector++;
    return { exec: async () => [{ ...source, score: 0.99 }] };
  });
  const service = new SolutionSearchService(config, {
    normalize: (text) => text.trim().toLowerCase(),
    hash: (text) => text,
    embed: async () => {
      calls.embedding++;
      return [[1, 0]];
    },
    version: "test",
  });
  return { service, calls };
}
const entry = (description, mandatory = [], src = source) => ({
  fingerprint: questionFingerprint(description, mandatory, requirements),
  sourceHash: sha(src.solution),
  source: src,
});

test("exact Q_ID resolves existing source without embeddings or name search", async (t) => {
  const { service, calls } = fixture(t, (filter) => {
    assert.deepEqual(filter, { courseId: 26, Q_ID: "DS_REGULAR_SET1_273" });
    return [entry("A roads problem")];
  });
  const result = await service.find(
    "A roads problem",
    26,
    [],
    "DS_REGULAR_SET1_273",
    requirements,
  );
  assert.equal(result.id, source._id);
  assert.equal(calls.embedding, 0);
  assert.equal(calls.vector, 0);
});

test("repeated lookups for the same Q_ID share a cached result across accounts", async (t) => {
  const { service, calls } = fixture(t, () => [entry("Question")]);
  const a = await service.find("Question", 26, [], "Q1", requirements);
  a.solution = "mutated caller object";
  const b = await service.find("Question", 26, [], "Q1", requirements);
  assert.equal(b.solution, source.solution);
  assert.equal(calls.catalog, 1);
});

test("different Q_IDs with the same introduction keep separate source links", async (t) => {
  const other = {
    ...source,
    _id: "source-2",
    solution: "int main(){return 1;}",
  };
  const { service } = fixture(t, (f) => [
    entry("Same introduction", [], f.Q_ID === "Q1" ? source : other),
  ]);
  assert.equal(
    (await service.find("Same introduction", 26, [], "Q1", requirements)).id,
    "source-1",
  );
  assert.equal(
    (await service.find("Same introduction", 26, [], "Q2", requirements)).id,
    "source-2",
  );
});

test("a changed requirement for a known Q_ID is blocked instead of merged", async (t) => {
  const { service, calls } = fixture(t, () => [entry("Question")]);
  await assert.rejects(
    service.find("Question", 26, ["struct node"], "Q1", requirements),
    (e) => e.status === 409,
  );
  assert.equal(calls.embedding, 0);
  assert.equal(calls.vector, 0);
});

test("known Q_ID without a confirmed link never falls back to a similar name", async (t) => {
  const { service, calls } = fixture(t, () => [
    { fingerprint: questionFingerprint("Question", [], requirements) },
  ]);
  await assert.rejects(
    service.find("Question", 26, [], "Q1", requirements),
    (e) => e.status === 422,
  );
  assert.equal(calls.vector, 0);
});

test("a modified source checksum invalidates its Q_ID link", async (t) => {
  const doc = entry("Question");
  doc.sourceHash = "old-source";
  const { service, calls } = fixture(t, () => [doc]);
  await assert.rejects(
    service.find("Question", 26, [], "Q1", requirements),
    (e) => e.status === 409,
  );
  assert.equal(calls.vector, 0);
});

test("a Q_ID link cannot cross course boundaries", async (t) => {
  const { service } = fixture(t, () => [
    entry("Question", [], { ...source, courseId: 11 }),
  ]);
  await assert.rejects(
    service.find("Question", 26, [], "Q1", requirements),
    (e) => e.status === 422,
  );
});

test("unknown IDs retain the legacy search fallback", async (t) => {
  const { service, calls } = fixture(t, () => []);
  assert.equal(
    (await service.find("Question", 26, [], "Q-new", requirements)).id,
    source._id,
  );
  assert.equal(calls.embedding, 1);
  assert.equal(calls.vector, 1);
});

test("source identity preserves literals and compound operators", () => {
  assert.equal(
    sourceTokenHash("int main(){ /*comment*/ return 0; }"),
    sourceTokenHash("int main() {return 0;}"),
  );
  assert.notEqual(sourceTokenHash("x++;"), sourceTokenHash("x+ +x;"));
  assert.notEqual(
    sourceTokenHash('puts("a b");'),
    sourceTokenHash('puts("ab");'),
  );
});
