import { HttpError } from "./http-error.js";
import { createHash } from "node:crypto";

interface Token {
  value: string;
  start: number;
  end: number;
  protected: boolean;
}

// Keep literals, comments, preprocessing lines, and compound operators intact.
// In particular, '+' '+' must never be mistaken for '++'.
function tokens(source: string): Token[] {
  const pattern =
    /^[\t ]*#(?:[^\n]*\\\r?\n)*[^\n]*|\/\/(?:[^\n]*\\\r?\n)*[^\n]*|\/\*[\s\S]*?\*\/|(?:u8|[LuU])?"(?:\\[\s\S]|[^"\\])*"|(?:[LuU])?'(?:\\[\s\S]|[^'\\])*'|[A-Za-z_][A-Za-z_0-9]*|(?:0[xX][0-9a-fA-F]+(?:\.[0-9a-fA-F]*)?(?:[pP][+-]?\d+)?|(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][+-]?\d+)?)[fFlLuU]*|%:%:|<:|:>|<%|%>|%:|>>=|<<=|\.\.\.|->|\+\+|--|<<|>>|<=|>=|==|!=|&&|\|\||\*=|\/=|%=|\+=|-=|&=|\^=|\|=|##|[^\S\r\n]+|\r?\n|[^\s]/gm;
  return [...source.matchAll(pattern)]
    .filter(([value]) => value.trim())
    .map((match) => ({
      value: match[0],
      start: match.index,
      end: match.index + match[0].length,
      protected: /^\s*#|^\/\/|^\/\*/.test(match[0]),
    }));
}

export function prepareMandatoryCode(
  source: string,
  mandatory: readonly string[],
): string {
  let code = source;
  for (const required of mandatory) {
    if (!required.trim()) continue;
    // Preserve requirements already present verbatim. The upstream evaluator
    // decides whether their placement is acceptable; don't impose stricter rules.
    if (code.includes(required)) continue;
    const expected = tokens(required);
    const actual = tokens(code);
    const start = actual.findIndex(
      (_, index) =>
        expected.length > 0 &&
        expected.every((token, offset) => {
          const candidate = actual[index + offset];
          return (
            !token.protected &&
            candidate &&
            !candidate.protected &&
            candidate.value === token.value
          );
        }),
    );
    const first = actual[start];
    const last = actual[start + expected.length - 1];
    if (!first || !last) {
      throw new HttpError(
        422,
        `The matched solution does not contain the required mandatory construct ${JSON.stringify(required.slice(0, 200))}. No code was submitted.`,
      );
    }
    code = code.slice(0, first.start) + required + code.slice(last.end);
  }
  // Overlapping requirements with conflicting formatting cannot both be met.
  if (
    mandatory.some((required) => required.trim() && !code.includes(required))
  ) {
    throw new HttpError(
      422,
      "The matched solution cannot satisfy all mandatory formatting requirements. No code was submitted.",
    );
  }
  return code;
}

// Compare stored submissions without treating whitespace or comments as logic.
// Literal contents and compound operators remain distinct.
export function sourceTokenHash(source: string): string {
  return createHash("sha256")
    .update(
      JSON.stringify(
        tokens(source)
          .filter((token) => !/^\/\/|^\/\*/.test(token.value))
          .map((token) => token.value.trim()),
      ),
    )
    .digest("hex");
}

export function prepareSubmissionCode(
  source: string,
  mandatory: readonly string[],
  maximumLines?: number,
): string {
  const code = prepareMandatoryCode(source, mandatory);
  if (!maximumLines || !Number.isSafeInteger(maximumLines) || maximumLines < 1)
    return code;
  let excess =
    code.split(/\r?\n/).filter((line) => line.trim()).length - maximumLines;
  if (excess <= 0) return code;
  const originalTokens = tokens(code);
  // Joining lines would change the meaning of line-sensitive compiler macros.
  if (
    originalTokens.some((token) =>
      /\b(?:__LINE__|__builtin_LINE|__builtin_source_location)\b/.test(
        token.value,
      ),
    )
  ) {
    throw new HttpError(
      422,
      "The matched solution exceeds the line limit and uses line-sensitive code. No code was submitted.",
    );
  }
  const requiredSpans: { start: number; end: number }[] = [];
  for (const required of mandatory.filter((item) => item.includes("\n"))) {
    for (
      let start = code.indexOf(required);
      start !== -1;
      start = code.indexOf(required, start + required.length)
    ) {
      requiredSpans.push({ start, end: start + required.length });
    }
  }
  const parts: string[] = [];
  let copied = 0;
  for (let index = 1; index < originalTokens.length && excess > 0; index++) {
    const previous = originalTokens[index - 1]!;
    const current = originalTokens[index]!;
    const gap = code.slice(previous.end, current.start);
    if (
      previous.protected ||
      current.protected ||
      !gap.includes("\n") ||
      !/^\s+$/.test(gap) ||
      requiredSpans.some(
        (span) => span.start < current.start && span.end > previous.end,
      )
    )
      continue;
    parts.push(code.slice(copied, previous.end), " ");
    copied = current.start;
    excess--;
  }
  if (excess > 0) {
    throw new HttpError(
      422,
      "The matched solution exceeds the line limit and cannot be compacted safely. No code was submitted.",
    );
  }
  parts.push(code.slice(copied));
  const compacted = parts.join("");
  const finalTokens = tokens(compacted);
  if (
    finalTokens.length !== originalTokens.length ||
    finalTokens.some(
      (token, index) => token.value !== originalTokens[index]!.value,
    ) ||
    mandatory.some(
      (required) => required.trim() && !compacted.includes(required),
    )
  ) {
    throw new HttpError(
      422,
      "The matched solution cannot be compacted without changing its tokens or mandatory requirements. No code was submitted.",
    );
  }
  return compacted;
}
