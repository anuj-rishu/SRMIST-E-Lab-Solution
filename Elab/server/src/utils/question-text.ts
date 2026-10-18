import { convert } from "html-to-text";

export function questionPlainText(value: string): string {
  return convert(value, {
    wordwrap: false,
    selectors: [
      { selector: "a", options: { ignoreHref: true } },
      { selector: "img", format: "skip" },
      { selector: "h1", options: { uppercase: false } },
      { selector: "h2", options: { uppercase: false } },
      { selector: "h3", options: { uppercase: false } },
    ],
  })
    .replace(/\u00a0/g, " ")
    .trim();
}

export function embeddingText(value: string, maxLength: number): string {
  let text = questionPlainText(value);
  const label =
    /^(?:(?:problem|question)\s+(?:description|statement)\s*[:：]?\s*|(?:problem|question)\s*[:：]\s*)/i;
  while (label.test(text)) text = text.replace(label, "").trim();
  return text
    .replace(/[^a-zA-Z0-9]/g, "_")
    .replace(/_+/g, "_")
    .replace(/^_|_$/g, "")
    .slice(0, maxLength)
    .replace(/_+$/, "")
    .replace(/_/g, " ")
    .toLowerCase()
    .trim();
}
