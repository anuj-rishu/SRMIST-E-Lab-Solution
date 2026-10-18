import { createStudentController } from "../controllers/student.controller.js";
import { requireAuth } from "../middleware/auth.middleware.js";
import { parseJson } from "../middleware/json.middleware.js";
import type { ElabService } from "../services/elab.service.js";
import type { Route } from "../types/http.js";

export function studentRoutes(service: ElabService): Route[] {
  const controller = createStudentController(service);
  return [
    {
      paths: ["/gettest"],
      method: "POST",
      middleware: [requireAuth, parseJson],
      controller: controller.getTest,
    },
    {
      paths: ["/registeredcourses"],
      method: "POST",
      middleware: [requireAuth],
      controller: controller.registeredCourses,
    },
    {
      paths: ["/rank"],
      method: "POST",
      middleware: [requireAuth],
      controller: controller.rank,
    },
  ];
}
