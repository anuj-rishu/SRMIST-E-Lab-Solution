import type { Middleware } from "../types/http.js";
import { HttpError } from "../utils/http-error.js";

export function cors(allowedOrigins: readonly string[]): Middleware {
  const origins = new Set(allowedOrigins);
  return ({ request, response }) => {
    response.setHeader("Cache-Control", "no-store");
    response.setHeader("X-Content-Type-Options", "nosniff");
    response.setHeader("Vary", "Origin");
    if (!request.headers.origin) return;
    if (!origins.has(request.headers.origin))
      throw new HttpError(403, "Origin is not allowed.");
    response.setHeader("Access-Control-Allow-Origin", request.headers.origin);
    response.setHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
    response.setHeader(
      "Access-Control-Allow-Headers",
      "Content-Type, Authorization",
    );
  };
}
