import type {
  CourseInfo,
  LoginInput,
  RequestableCourse,
  SolveQuestionInput,
  StudentInfo,
} from "../types/elab.js";
import { HttpError } from "./http-error.js";

export function isObject(value: unknown): value is Record<string, unknown> {
  return value !== null && typeof value === "object" && !Array.isArray(value);
}

export function parseLogin(body: Record<string, unknown>): LoginInput {
  if (
    typeof body.USER_ID !== "string" ||
    !body.USER_ID.trim() ||
    typeof body.PASSWORD !== "string" ||
    !body.PASSWORD
  ) {
    throw new HttpError(400, "USER_ID and PASSWORD must be nonempty strings.");
  }
  return { USER_ID: body.USER_ID, PASSWORD: body.PASSWORD };
}

export function parseStudentInfo(value: unknown): StudentInfo {
  if (
    !isObject(value) ||
    typeof value.USER_ID !== "string" ||
    !value.USER_ID.trim()
  ) {
    throw new HttpError(
      400,
      "info must be the logged-in user's profile with USER_ID.",
    );
  }
  return { ...value, USER_ID: value.USER_ID };
}

export function parseCourse(value: unknown, userId: string): CourseInfo {
  if (
    !isObject(value) ||
    typeof value._id !== "string" ||
    !value._id.trim() ||
    typeof value.USER_ID !== "string" ||
    !value.USER_ID.trim() ||
    typeof value.COURSE_ID !== "number" ||
    !Number.isInteger(value.COURSE_ID) ||
    value.COURSE_ID < 1
  ) {
    throw new HttpError(
      400,
      "course must include _id, USER_ID, and a positive integer COURSE_ID. Send the complete course object from registeredcourses.",
    );
  }
  if (value.USER_ID !== userId) {
    throw new HttpError(
      400,
      "The selected course must belong to the logged-in user.",
    );
  }
  return {
    ...value,
    _id: value._id,
    USER_ID: value.USER_ID,
    COURSE_ID: value.COURSE_ID,
  };
}

export function parseSequenceId(value: unknown): number {
  if (typeof value !== "number" || !Number.isSafeInteger(value) || value < 1) {
    throw new HttpError(400, "SEQUENCE_ID must be a positive integer.");
  }
  return value;
}

export function parseRequestableCourse(value: unknown): RequestableCourse {
  if (
    !isObject(value) ||
    typeof value.COURSE_ID !== "number" ||
    !Number.isSafeInteger(value.COURSE_ID) ||
    value.COURSE_ID < 1 ||
    value.ENABLED !== 1 ||
    !["COURSE_NAME", "TITLE", "TYPE", "SET", "MODE"].every(
      (key) => typeof value[key] === "string" && value[key].trim(),
    ) ||
    typeof value.DESCRIPTION !== "string"
  ) {
    throw new HttpError(
      400,
      "Select an enabled course from the course request catalog.",
    );
  }
  return {
    COURSE_NAME: value.COURSE_NAME as string,
    COURSE_ID: value.COURSE_ID,
    ENABLED: 1,
    TITLE: value.TITLE as string,
    DESCRIPTION: value.DESCRIPTION,
    TYPE: value.TYPE as string,
    SET: value.SET as string,
    MODE: value.MODE as string,
  };
}

export function parseStudentRole(info: StudentInfo): string {
  if (typeof info.ROLE !== "string" || !info.ROLE.trim()) {
    throw new HttpError(
      401,
      "Login token does not contain a role. Please log in again.",
    );
  }
  return info.ROLE;
}

export function parseSolveQuestion(
  body: Record<string, unknown>,
  userId: string,
): SolveQuestionInput {
  const course = parseCourse(body.course, userId);
  const sequenceId = parseSequenceId(body.SEQUENCE_ID);
  if (body.language !== undefined && body.language !== "c") {
    throw new HttpError(400, "Only C language is supported.");
  }
  if (body.input !== undefined && typeof body.input !== "string") {
    throw new HttpError(400, "input must be a string.");
  }
  return {
    course,
    sequenceId,
    input: body.input === undefined ? "0" : body.input,
  };
}
