import type { Middleware } from "../types/http.js";
import { HttpError } from "../utils/http-error.js";
import { isObject } from "../utils/validation.js";

export const parseJson: Middleware = async (context) => {
  const { request } = context;
  if (
    request.headers["content-type"]?.split(";")[0]?.trim().toLowerCase() !==
    "application/json"
  ) {
    throw new HttpError(415, "Content-Type must be application/json.");
  }
  const chunks: Buffer[] = [];
  let size = 0;
  for await (const chunk of request) {
    const buffer = Buffer.isBuffer(chunk) ? chunk : Buffer.from(chunk);
    size += buffer.length;
    if (size > 65536) throw new HttpError(413, "Request body exceeds 64 KiB.");
    chunks.push(buffer);
  }
  let body: unknown;
  try {
    body = JSON.parse(Buffer.concat(chunks).toString("utf8"));
  } catch {
    throw new HttpError(400, "Request body must be valid JSON.");
  }
  if (!isObject(body))
    throw new HttpError(400, "Request body must be a JSON object.");
  context.body = body;
};
