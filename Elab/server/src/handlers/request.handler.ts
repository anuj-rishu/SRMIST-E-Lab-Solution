import type { RequestListener } from "node:http";
import { handleError } from "../middleware/error.middleware.js";
import type { Middleware, RequestContext, Route } from "../types/http.js";
import { HttpError } from "../utils/http-error.js";
import { sendJson } from "../utils/response.js";

export function createRequestHandler(
  routes: Route[],
  middleware: Middleware[],
): RequestListener {
  const byPath = new Map(
    routes.flatMap((route) =>
      route.paths.map((path) => [path, route] as const),
    ),
  );
  return async (request, response) => {
    const context: RequestContext = {
      request,
      response,
      body: {},
      authorization: "",
    };
    try {
      for (const run of middleware) await run(context);
      const path = new URL(request.url || "/", "http://localhost").pathname;
      const route = byPath.get(path);
      if (!route) throw new HttpError(404, "Endpoint not found.");
      if (request.method === "OPTIONS") {
        response.writeHead(204);
        response.end();
        return;
      }
      if (request.method !== route.method) {
        response.setHeader("Allow", `${route.method}, OPTIONS`);
        throw new HttpError(405, `Use ${route.method} for this endpoint.`);
      }
      for (const run of route.middleware) await run(context);
      const { status, data } = await route.controller(context);
      sendJson(response, status, data);
    } catch (error) {
      handleError(error, response);
    }
  };
}
