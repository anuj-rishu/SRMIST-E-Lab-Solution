export class ApiError extends Error {
  constructor(
    message: string,
    public readonly status: number,
  ) {
    super(message);
    this.name = "ApiError";
  }
}

interface RequestOptions {
  token?: string;
  body?: unknown;
  signal?: AbortSignal;
}

function isRecord(value: unknown): value is Record<string, unknown> {
  return value !== null && typeof value === "object" && !Array.isArray(value);
}

function messageFrom(data: unknown): string {
  if (!isRecord(data))
    return "The request could not be completed. Please try again.";
  for (const key of ["error", "msg", "message"]) {
    if (typeof data[key] === "string") return data[key];
  }
  if (isRecord(data.response)) return messageFrom(data.response);
  return "E-Lab could not complete this request. Please try again.";
}

export async function apiRequest<T>(
  endpoint: string,
  options: RequestOptions = {},
): Promise<T> {
  const headers: Record<string, string> = {
    Accept: "application/json",
    "Content-Type": "application/json",
  };
  if (options.token) {
    headers.Authorization = /^Bearer\s/i.test(options.token)
      ? options.token
      : `Bearer ${options.token}`;
  }
  let response: Response;
  try {
    response = await fetch(`/api/v1/${endpoint}`, {
      method: "POST",
      headers,
      body: JSON.stringify(options.body ?? {}),
      signal: options.signal
        ? AbortSignal.any([options.signal, AbortSignal.timeout(120000)])
        : AbortSignal.timeout(120000),
      cache: "no-store",
    });
  } catch (error) {
    if (error instanceof Error && error.name === "AbortError") throw error;
    throw new ApiError(
      "Unable to reach E-Lab. Check your connection and try again.",
      0,
    );
  }
  let data: unknown;
  try {
    data = await response.json();
  } catch {
    throw new ApiError(
      "The server returned an unexpected response. Please try again.",
      response.status,
    );
  }
  if (!response.ok || (isRecord(data) && data.Status === 0)) {
    if (response.status === 401 && options.token)
      window.dispatchEvent(new Event("elab:session-expired"));
    throw new ApiError(messageFrom(data), response.status);
  }
  return data as T;
}

export function errorMessage(error: unknown): string {
  return error instanceof Error
    ? error.message
    : "Something went wrong. Please try again.";
}
