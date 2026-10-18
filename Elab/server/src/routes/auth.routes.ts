import { createAuthController } from "../controllers/auth.controller.js";
import { parseJson } from "../middleware/json.middleware.js";
import type { ElabService } from "../services/elab.service.js";
import type { Route } from "../types/http.js";

export function authRoutes(service: ElabService): Route[] {
  const controller = createAuthController(service);
  return [
    {
      paths: ["/login"],
      method: "POST",
      middleware: [parseJson],
      controller: controller.login,
    },
  ];
}
