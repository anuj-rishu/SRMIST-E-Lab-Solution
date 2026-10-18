import { readFileSync, writeFileSync, existsSync, mkdirSync } from "node:fs";
import { tmpdir } from "node:os";
import { resolve } from "node:path";
import { createHash } from "node:crypto";
import { ElabService } from "../dist/src/services/elab.service.js";
import { ELAB_CONFIG } from "../dist/src/config/settings.js";
import { parseElabToken } from "../dist/src/utils/elab-token.js";
const api = new ElabService(ELAB_CONFIG);
const cache = resolve(
  process.env.ELAB_CATALOG_CACHE_DIR ||
    resolve(tmpdir(), "elab-question-catalog"),
);
mkdirSync(cache, { recursive: true, mode: 0o700 });
if (
  !process.env.ELAB_ACCOUNT1_TOKEN_FILE ||
  !process.env.ELAB_ACCOUNT2_TOKEN_FILE
)
  throw Error("Set ELAB_ACCOUNT1_TOKEN_FILE and ELAB_ACCOUNT2_TOKEN_FILE.");
for (const [account, file] of [
  [1, process.env.ELAB_ACCOUNT1_TOKEN_FILE],
  [2, process.env.ELAB_ACCOUNT2_TOKEN_FILE],
]) {
  const path = resolve(cache, `elab-qid-account${account}.json`);
  const { studentInfo, authorization } = parseElabToken(
    readFileSync(file, "utf8").trim(),
  );
  const accountHash = createHash("sha256")
    .update(String(studentInfo.USER_ID))
    .digest("hex");
  const previous = existsSync(path)
    ? JSON.parse(readFileSync(path, "utf8"))
    : null;
  const saved =
    previous?.accountHash === accountHash
      ? previous
      : { account, accountHash, questions: {} };
  const response = await api.registeredCourses(studentInfo, authorization);
  const course = response.data.courses.find((c) => c.COURSE_ID === 26);
  let next = 1;
  const errors = [];
  await Promise.all(
    Array.from({ length: 3 }, async () => {
      while (next <= 300) {
        const seq = next++;
        if (saved.questions[seq]) continue;
        try {
          const result = await api.getQuestionInfo(
            studentInfo,
            course,
            seq,
            "S",
            authorization,
          );
          const d = result.data;
          if (
            d.Status !== 1 ||
            !d.studentData?.Q_ID ||
            d.studentData.SEQUENCE_ID !== seq ||
            !d.questionData
          )
            throw Error("Invalid question response");
          saved.questions[seq] = {
            sequenceId: seq,
            Q_ID: d.studentData.Q_ID,
            questionData: d.questionData,
            storedCode: d.studentData.CODE,
            status: d.studentData.STATUS,
          };
          writeFileSync(path, JSON.stringify(saved), { mode: 0o600 });
          if (Object.keys(saved.questions).length % 50 === 0)
            console.log(
              JSON.stringify({
                account,
                collected: Object.keys(saved.questions).length,
              }),
            );
        } catch (e) {
          errors.push({
            sequenceId: seq,
            error: e.status ? e.message : e.name,
          });
        }
      }
    }),
  );
  console.log(
    JSON.stringify({
      account,
      complete: Object.keys(saved.questions).length,
      errors,
    }),
  );
  if (Object.keys(saved.questions).length !== 300)
    throw Error("Collection incomplete; rerun to resume before indexing.");
}
