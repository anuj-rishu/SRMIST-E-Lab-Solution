import { createQuestionController } from "../controllers/question.controller.js";
import { requireAuth } from "../middleware/auth.middleware.js";
import { parseJson } from "../middleware/json.middleware.js";
import type { SolutionMatcher } from "../services/solution-search.service.js";
import type { ElabService } from "../services/elab.service.js";
import type { Route } from "../types/http.js";

export function questionRoutes(
  service: ElabService,
  solutions: SolutionMatcher,
): Route[] {
  const controller = createQuestionController(service, solutions);
  return [
    {
      paths: ["/solve"],
      method: "POST",
      middleware: [requireAuth, parseJson],
      controller: controller.solve,
    },
    {
      paths: ["/getinfo"],
      method: "POST",
      middleware: [requireAuth, parseJson],
      controller: controller.getInfo,
    },
  ];
}
