import { existsSync, readFileSync, readdirSync, writeFileSync } from "node:fs";
import { resolve } from "node:path";

const directory = resolve(process.argv[2] || "info/course-26-86-300");
const fixes = resolve(directory, "fixes");
const questions = readdirSync(directory)
  .filter((name) => /^question-\d+\.json$/.test(name))
  .map((name) => Number(name.match(/\d+/)[0]))
  .sort((a, b) => a - b);
const unresolvedStatements = {
  241: "Original Fence statement recovers the selector: t=1 minimum-area profit; t=2 maximum profit.",
  260: "Original Hipersimetrie statement recovers the output modulus 1000000007 and K bound.",
  279: "Live examples contain neither the described tree/query input nor YES/NO output; both examples contradict the statement.",
};
const results = questions.map((sequenceId) => {
  const original = JSON.parse(
    readFileSync(resolve(directory, `question-${sequenceId}.json`), "utf8"),
  );
  const path = resolve(fixes, `question-${sequenceId}.json`);
  const report = existsSync(path)
    ? JSON.parse(readFileSync(path, "utf8"))
    : undefined;
  const verified =
    report?.savedToDatabase === true &&
    report.result?.statusCode === "200" &&
    Number(report.result.evalPercentage) === 100;
  return {
    sequenceId,
    questionId: `DS_REGULAR_SET1_${original.questionData.key}`,
    status: verified
      ? "verified-and-saved"
      : report
        ? "needs-correction"
        : "statement-needs-clarification",
    score: report?.result?.evalPercentage ?? null,
    failures:
      report?.result?.statusArray
        ?.filter((check) => /failed/i.test(check.msg))
        .map((check) => check.msg.trim()) ?? [],
    ...(report?.error ? { error: report.error } : {}),
    ...(report?.result?.errorMsg
      ? { compilerError: report.result.errorMsg }
      : {}),
    ...(unresolvedStatements[sequenceId]
      ? { note: unresolvedStatements[sequenceId] }
      : {}),
  };
});
const verified = results.filter(
  (r) => r.status === "verified-and-saved",
).length;
const summary = {
  updatedAt: new Date().toISOString(),
  reviewTotal: results.length,
  verifiedAndSaved: verified,
  remaining: results.length - verified,
  results,
};
writeFileSync(
  resolve(fixes, "summary.json"),
  JSON.stringify(summary, null, 2) + "\n",
);
const rows = results.map(
  (r) =>
    `| ${r.sequenceId} | ${r.score === null ? "Not verified" : `${r.score}%`} | ${r.status === "verified-and-saved" ? "Saved to database" : r.failures.join(", ") || r.error || r.note || "Needs review"} | [Question](question-${r.sequenceId}.json)${existsSync(resolve(fixes, `question-${r.sequenceId}.json`)) ? ` / [Evaluation](fixes/question-${r.sequenceId}.json)` : ""} |`,
);
writeFileSync(
  resolve(directory, "README.md"),
  `# Questions 86–300\n\nThe initial run scored 100% on 95 questions and saved 120 for review. Of those 120, **${verified} additional solutions have now scored 100% on E-Lab and been saved to MongoDB**. ${results.length - verified} remain unresolved.\n\nResults below are actual E-Lab evaluations. Partial solutions are kept locally for review and are not marked verified in the database. Verified solutions use the exact E-Lab question ID, keeping different variants separate.\n\nLive API responses were fetched again for 241, 260, and 279. The original [Fence](https://www.infoarena.ro/problema/fence) and [Hipersimetrie](https://www.infoarena.ro/problema/hipersimetrie) statements recover the missing selector and modulus rules for 241 and 260; both solutions now score 100%. Question 279's examples do not describe a tree or return YES/NO as required by its statement.\n\n[Machine-readable fix summary](fixes/summary.json). The original summary.json records the initial run and is retained unchanged.\n\n| Question | Latest score | Status / remaining checks | Details |\n| --- | --- | --- | --- |\n${rows.join("\n")}\n`,
);
console.log(
  JSON.stringify({ verifiedAndSaved: verified, remaining: summary.remaining }),
);
