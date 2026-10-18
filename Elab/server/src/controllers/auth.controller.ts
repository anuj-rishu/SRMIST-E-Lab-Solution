import type { ElabService } from "../services/elab.service.js";
import type { Controller } from "../types/http.js";
import { parseLogin } from "../utils/validation.js";

export function createAuthController(service: ElabService): {
  login: Controller;
} {
  return { login: ({ body }) => service.login(parseLogin(body)) };
}
