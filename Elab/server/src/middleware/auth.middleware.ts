import type { Middleware } from "../types/http.js";
import { parseElabToken } from "../utils/elab-token.js";

export const requireAuth: Middleware = (context) => {
  const token = parseElabToken(context.request.headers.authorization);
  context.studentInfo = token.studentInfo;
  context.authorization = token.authorization;
};
