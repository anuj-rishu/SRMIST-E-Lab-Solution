import { createServer } from "node:http";
import type { ServerConfig } from "./config/env.js";
import { createRequestHandler } from "./handlers/request.handler.js";
import { cors } from "./middleware/cors.middleware.js";
import { createRoutes } from "./routes/index.js";
import { EmbeddingService } from "./services/embedding.service.js";
import { SolutionSearchService } from "./services/solution-search.service.js";
import type { SolutionMatcher } from "./services/solution-search.service.js";
import { ElabService } from "./services/elab.service.js";
import type { FetchClient } from "./types/http.js";

export interface AppOptions {
  fetchImpl?: FetchClient;
  config: ServerConfig;
  solutionMatcher?: SolutionMatcher;
}

export function createApp({
  fetchImpl = globalThis.fetch,
  config,
  solutionMatcher,
}: AppOptions) {
  const service = new ElabService(config.elab, fetchImpl);
  const solutions =
    solutionMatcher ||
    new SolutionSearchService(config, new EmbeddingService(config.embedding));
  return createServer(
    createRequestHandler(createRoutes(service, solutions), [
      cors(config.allowedOrigins),
    ]),
  );
}
