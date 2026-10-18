import type { ElabConfig, EmbeddingConfig } from "./env.js";

export const ELAB_CONFIG: Readonly<ElabConfig> = {
  key: "john",
  baseUrl: "https://dld.srmist.edu.in/ktretelab2025/elabserver",
  origin: "https://dld.srmist.edu.in",
  referer: "https://dld.srmist.edu.in/ktretelab2025/",
  timeoutMs: 15000,
  compilerUrl: "https://dld.srmist.edu.in/compilez/compiler",
  compilerApiKey: "transtar",
};

export const EMBEDDING_CONFIG: Readonly<EmbeddingConfig> = {
  model: "Xenova/all-MiniLM-L6-v2",
  revision: "751bff37182d3f1213fa05d7196b954e230abad9",
  dimensions: 384,
  cacheDir: ".cache/embeddings",
  textLength: 50,
  batchSize: 16,
  indexName: "solutions_question_vector_v1",
  minScore: 0.85,
  minMargin: 0.04,
};
