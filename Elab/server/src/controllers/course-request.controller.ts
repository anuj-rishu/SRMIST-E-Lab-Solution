import type { ElabService } from "../services/elab.service.js";
import type { Controller } from "../types/http.js";
import {
  parseRequestableCourse,
  parseStudentInfo,
} from "../utils/validation.js";

export function createCourseRequestController(service: ElabService): {
  allCourses: Controller;
  send: Controller;
} {
  return {
    allCourses: ({ studentInfo, authorization }) =>
      service.requestableCourses(parseStudentInfo(studentInfo), authorization),
    send: ({ body, studentInfo, authorization }) =>
      service.requestCourse(
        parseStudentInfo(studentInfo),
        parseRequestableCourse(body.course),
        authorization,
      ),
  };
}
