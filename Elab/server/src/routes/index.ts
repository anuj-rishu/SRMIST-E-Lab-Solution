import type { SolutionMatcher } from "../services/solution-search.service.js";
import type { ElabService } from "../services/elab.service.js";
import type { Route } from "../types/http.js";
import { authRoutes } from "./auth.routes.js";
import { courseRoutes } from "./course.routes.js";
import { courseRequestRoutes } from "./course-request.routes.js";
import { profileRoutes } from "./profile.routes.js";
import { questionRoutes } from "./question.routes.js";
import { studentRoutes } from "./student.routes.js";

export function createRoutes(
  service: ElabService,
  solutions: SolutionMatcher,
): Route[] {
  const routes: Route[] = [
    {
      paths: ["/health"],
      method: "GET",
      middleware: [],
      controller: () => ({ status: 200, data: { status: "ok" } }),
    },
    ...authRoutes(service),
    ...courseRoutes(service),
    ...courseRequestRoutes(service),
    ...profileRoutes(service),
    ...questionRoutes(service, solutions),
    ...studentRoutes(service),
  ];
  return routes.map((route) => ({
    ...route,
    paths: route.paths.map((path) => `/api/v1${path}`),
  }));
}
