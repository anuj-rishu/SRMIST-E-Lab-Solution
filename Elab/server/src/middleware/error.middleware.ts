import type { ServerResponse } from "node:http";
import { HttpError } from "../utils/http-error.js";
import { sendJson } from "../utils/response.js";

export function handleError(error: unknown, response: ServerResponse): void {
  if (response.destroyed || response.writableEnded) return;
  if (response.headersSent) {
    response.end();
    return;
  }
  sendJson(response, error instanceof HttpError ? error.status : 500, {
    error:
      error instanceof HttpError ? error.message : "Internal server error.",
  });
}
