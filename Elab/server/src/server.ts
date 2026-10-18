import mongoose from "mongoose";
import { createApp } from "./app.js";
import { loadConfig } from "./config/env.js";
import { logger } from "./utils/logger.js";

const config = loadConfig();
logger.level = config.logLevel;
const server = createApp({ config });
server.on("error", (error: NodeJS.ErrnoException) => {
  logger.error({ code: error.code }, "API server failed");
  process.exitCode = 1;
});
server.listen(config.port, "0.0.0.0", () => {
  logger.info({ port: config.port }, "E-Lab API listening");
});
let shuttingDown = false;
for (const signal of ["SIGINT", "SIGTERM"] as const) {
  process.on(signal, () => {
    if (shuttingDown) return;
    shuttingDown = true;
    logger.info({ signal }, "Shutting down API server");
    const timeout = setTimeout(() => {
      logger.error("Graceful shutdown timed out");
      server.closeAllConnections();
      process.exit(1);
    }, 10000);
    timeout.unref();
    server.close(() => {
      void mongoose
        .disconnect()
        .catch(() => {
          logger.error("Database disconnect failed");
          process.exitCode = 1;
        })
        .finally(() => clearTimeout(timeout));
    });
  });
}
