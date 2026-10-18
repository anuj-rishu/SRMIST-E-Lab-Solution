import { createProfileController } from "../controllers/profile.controller.js";
import { requireAuth } from "../middleware/auth.middleware.js";
import type { ElabService } from "../services/elab.service.js";
import type { Route } from "../types/http.js";

export function profileRoutes(service: ElabService): Route[] {
  const controller = createProfileController(service);
  return [
    {
      paths: ["/profile"],
      method: "POST",
      middleware: [requireAuth],
      controller: controller.profile,
    },
  ];
}
