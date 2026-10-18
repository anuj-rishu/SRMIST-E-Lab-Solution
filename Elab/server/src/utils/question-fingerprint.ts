import { createHash } from "node:crypto";

export interface QuestionRequirements {
  complexity?: unknown;
  testcases?: unknown;
}

export function questionFingerprint(
  description: string,
  mandatory: readonly string[] = [],
  requirements: QuestionRequirements = {},
): string {
  return createHash("sha256")
    .update(
      JSON.stringify([
        description.replace(/\s+/g, " ").trim(),
        mandatory.map((value) => value.trim()),
        requirements.complexity ?? null,
        requirements.testcases ?? null,
      ]),
    )
    .digest("hex");
}
