import { createCourseController } from "../controllers/course.controller.js";
import { requireAuth } from "../middleware/auth.middleware.js";
import { parseJson } from "../middleware/json.middleware.js";
import type { ElabService } from "../services/elab.service.js";
import type { Route } from "../types/http.js";

export function courseRoutes(service: ElabService): Route[] {
  const controller = createCourseController(service);
  return [
    {
      paths: ["/getcourseinfo"],
      method: "POST",
      middleware: [requireAuth, parseJson],
      controller: controller.getCourseInfo,
    },
  ];
}
