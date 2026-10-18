import type { ElabService } from "../services/elab.service.js";
import type { Controller } from "../types/http.js";
import { parseStudentInfo } from "../utils/validation.js";

export function createStudentController(service: ElabService): {
  getTest: Controller;
  registeredCourses: Controller;
  rank: Controller;
} {
  return {
    getTest: ({ studentInfo, authorization }) =>
      service.getTest(parseStudentInfo(studentInfo), authorization),
    registeredCourses: ({ studentInfo, authorization }) =>
      service.registeredCourses(parseStudentInfo(studentInfo), authorization),
    rank: ({ studentInfo, authorization }) =>
      service.rank(parseStudentInfo(studentInfo), authorization),
  };
}
