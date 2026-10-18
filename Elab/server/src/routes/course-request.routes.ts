import { createCourseRequestController } from "../controllers/course-request.controller.js";
import { requireAuth } from "../middleware/auth.middleware.js";
import { parseJson } from "../middleware/json.middleware.js";
import type { ElabService } from "../services/elab.service.js";
import type { Route } from "../types/http.js";

export function courseRequestRoutes(service: ElabService): Route[] {
  const controller = createCourseRequestController(service);
  return [
    {
      paths: ["/courserequest/allcourses"],
      method: "POST",
      middleware: [requireAuth, parseJson],
      controller: controller.allCourses,
    },
    {
      paths: ["/courserequest/send"],
      method: "POST",
      middleware: [requireAuth, parseJson],
      controller: controller.send,
    },
  ];
}
