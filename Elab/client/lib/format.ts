import type { Course, Question } from "./types";

export function displayName(value?: string): string {
  return (
    value
      ?.trim()
      .toLowerCase()
      .replace(/\b\w/g, (letter) => letter.toUpperCase()) || "Student"
  );
}

export function initials(first?: string, last?: string): string {
  return `${first?.trim()[0] || "S"}${last?.trim()[0] || ""}`.toUpperCase();
}

export function solvedInCourse(course: Course): number {
  return (
    Number(course.LEVEL1 || 0) +
    Number(course.LEVEL2 || 0) +
    Number(course.LEVEL3 || 0)
  );
}

export function courseTitle(course: Course): string {
  return displayName(course.TITLE || course.COURSE_NAME);
}

export function questionState(
  question: Question,
): "completed" | "available" | "unopened" {
  return question.status === 2
    ? "completed"
    : question.status === 1
      ? "available"
      : "unopened";
}

export function scoreOf(value: number | string | undefined): number | null {
  if (value === undefined || value === null || value === "") return null;
  const score = Number(value);
  return Number.isFinite(score) ? Math.max(0, Math.min(100, score)) : null;
}
