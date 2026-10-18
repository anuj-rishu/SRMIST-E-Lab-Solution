import type { IncomingMessage, ServerResponse } from "node:http";
import type { StudentInfo } from "./elab.js";

export interface RequestContext {
  request: IncomingMessage;
  response: ServerResponse;
  body: Record<string, unknown>;
  authorization: string;
  studentInfo?: StudentInfo;
}

export interface ApiResult {
  status: number;
  data: unknown;
}

export type Middleware = (context: RequestContext) => void | Promise<void>;
export type Controller = (
  context: RequestContext,
) => ApiResult | Promise<ApiResult>;

export interface Route {
  paths: readonly string[];
  method: "GET" | "POST";
  middleware: Middleware[];
  controller: Controller;
}

export interface UpstreamRequest {
  method: "POST";
  headers: Record<string, string>;
  body: string;
  signal: AbortSignal;
  redirect: "error";
}

export type FetchClient = (
  url: string,
  options: UpstreamRequest,
) => Promise<Response>;
