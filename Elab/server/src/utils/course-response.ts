import { HttpError } from "./http-error.js";
import { isObject, parseSequenceId } from "./validation.js";

interface CourseQuestion {
  SEQUENCE_ID: number;
  level: number;
  status: number;
}

interface CourseSession {
  id: number;
  name: string;
  totalQuestions: number;
  questions: CourseQuestion[];
}

function invalidResponse(): never {
  throw new HttpError(502, "E-Lab returned an invalid course-info response.");
}

function collectQuestions(nodes: unknown): CourseQuestion[] {
  if (!Array.isArray(nodes)) return invalidResponse();
  const questions: CourseQuestion[] = [];
  for (const node of nodes) {
    if (!isObject(node)) return invalidResponse();
    let sequenceId: number;
    try {
      sequenceId = parseSequenceId(node.name);
    } catch {
      return invalidResponse();
    }
    const level =
      typeof node.level === "string" ? Number(node.level) : node.level;
    if (
      typeof level !== "number" ||
      !Number.isSafeInteger(level) ||
      level < 1 ||
      typeof node.status !== "number" ||
      !Number.isInteger(node.status)
    ) {
      return invalidResponse();
    }
    questions.push({ SEQUENCE_ID: sequenceId, level, status: node.status });
    if (node.children !== undefined)
      questions.push(...collectQuestions(node.children));
  }
  return questions;
}

export function formatCourseInfo(data: unknown, courseId: number): unknown {
  if (!isObject(data) || data.Status !== 1) return data;
  if (!isObject(data.flare) || !Array.isArray(data.flare.children)) {
    return invalidResponse();
  }
  const sessions: CourseSession[] = data.flare.children.map(
    (session: unknown) => {
      if (
        !isObject(session) ||
        typeof session.id !== "number" ||
        !Number.isSafeInteger(session.id) ||
        typeof session.name !== "string"
      ) {
        return invalidResponse();
      }
      const questions = collectQuestions(session.children).sort(
        (a, b) => a.level - b.level || a.SEQUENCE_ID - b.SEQUENCE_ID,
      );
      return {
        id: session.id,
        name: session.name,
        totalQuestions: questions.length,
        questions,
      };
    },
  );
  return {
    Status: 1,
    courseId,
    totalSessions: sessions.length,
    totalQuestions: sessions.reduce(
      (total, session) => total + session.totalQuestions,
      0,
    ),
    sessions,
  };
}
