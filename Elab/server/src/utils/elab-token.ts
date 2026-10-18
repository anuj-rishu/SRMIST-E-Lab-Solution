import type { StudentInfo } from "../types/elab.js";
import { HttpError } from "../utils/http-error.js";
import { isObject, parseStudentInfo } from "../utils/validation.js";

export function parseElabToken(authorization: string | undefined): {
  authorization: string;
  studentInfo: StudentInfo;
} {
  const match = authorization?.match(
    /^Bearer\s+:?([A-Za-z0-9_-]+\.[A-Za-z0-9_-]+\.[A-Za-z0-9_-]+)$/i,
  );
  const token = match?.[1];
  if (!token) {
    throw new HttpError(
      401,
      "A valid E-Lab login token is required in the Authorization header.",
    );
  }

  let claims: unknown;
  try {
    const payload = token.split(".")[1];
    if (!payload) throw new Error("Missing token payload.");
    claims = JSON.parse(Buffer.from(payload, "base64url").toString("utf8"));
  } catch {
    throw new HttpError(401, "Invalid E-Lab login token. Please log in again.");
  }

  if (
    !isObject(claims) ||
    typeof claims.USER_ID !== "string" ||
    !claims.USER_ID.trim()
  ) {
    throw new HttpError(
      401,
      "Login token does not contain a student profile. Please log in again.",
    );
  }
  if (
    typeof claims.exp !== "number" ||
    !Number.isFinite(claims.exp) ||
    claims.exp * 1000 <= Date.now()
  ) {
    throw new HttpError(
      401,
      "Login token has expired or has no valid expiry. Please log in again.",
    );
  }

  return {
    studentInfo: parseStudentInfo(claims),
    authorization: `Bearer :${token}`,
  };
}
