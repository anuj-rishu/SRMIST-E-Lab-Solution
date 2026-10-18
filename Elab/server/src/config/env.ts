import { existsSync } from "node:fs";
import { dirname, join, resolve } from "node:path";
import { loadEnvFile } from "node:process";
import { fileURLToPath } from "node:url";
import { ELAB_CONFIG, EMBEDDING_CONFIG } from "./settings.js";

export interface ElabConfig {
  key: string;
  baseUrl: string;
  origin: string;
  referer: string;
  timeoutMs: number;
  compilerUrl: string;
  compilerApiKey: string;
}

export interface EmbeddingConfig {
  model: string;
  revision: string;
  dimensions: number;
  cacheDir: string;
  textLength: number;
  batchSize: number;
  indexName: string;
  minScore: number;
  minMargin: number;
}

export interface ServerConfig {
  port: number;
  mongodbUri: string;
  embedding: EmbeddingConfig;
  logLevel: "info" | "error";
  allowedOrigins: string[];
  elab: ElabConfig;
}

function required(name: string): string {
  const value = process.env[name];
  if (!value?.trim())
    throw new Error(`${name} is required in the environment.`);
  return value;
}

function integer(name: string, maximum: number): number {
  const value = Number(required(name));
  if (!Number.isInteger(value) || value < 1 || value > maximum) {
    throw new Error(`${name} must be an integer between 1 and ${maximum}.`);
  }
  return value;
}

function clientOrigins(): string[] {
  try {
    const origins = required("CLIENT_ORIGIN")
      .split(",")
      .map((value) => {
        const url = new URL(value.trim());
        if (
          !["http:", "https:"].includes(url.protocol) ||
          url.username ||
          url.password ||
          url.pathname !== "/" ||
          url.search ||
          url.hash
        )
          throw new Error("Invalid origin");
        return url.origin;
      });
    return [...new Set(origins)];
  } catch {
    throw new Error(
      "CLIENT_ORIGIN must contain full HTTP(S) origins separated by commas, for example http://localhost:3000,https://e-lab-solver.vercel.app.",
    );
  }
}

export function loadConfig(): ServerConfig {
  let directory = dirname(fileURLToPath(import.meta.url));
  while (!existsSync(join(directory, "package.json"))) {
    const parent = dirname(directory);
    if (parent === directory)
      throw new Error("Server package.json was not found.");
    directory = parent;
  }
  if (process.env.NODE_ENV !== "production") {
    for (const filename of [".env.local", ".env"]) {
      const path = join(directory, filename);
      if (existsSync(path)) loadEnvFile(path);
    }
  }
  const nodeEnv = required("NODE_ENV");
  if (!["development", "production", "test"].includes(nodeEnv)) {
    throw new Error("NODE_ENV must be development, production, or test.");
  }
  return {
    port: integer("PORT", 65535),
    mongodbUri: required("MONGODB_URI"),
    embedding: {
      ...EMBEDDING_CONFIG,
      cacheDir: resolve(directory, EMBEDDING_CONFIG.cacheDir),
    },
    logLevel: "info",
    allowedOrigins: clientOrigins(),
    elab: { ...ELAB_CONFIG },
  };
}
