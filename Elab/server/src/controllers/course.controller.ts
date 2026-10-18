import type { ElabService } from "../services/elab.service.js";
import type { Controller } from "../types/http.js";
import { parseCourse, parseStudentInfo } from "../utils/validation.js";

export function createCourseController(service: ElabService): {
  getCourseInfo: Controller;
} {
  return {
    getCourseInfo: ({ body, studentInfo, authorization }) => {
      const info = parseStudentInfo(studentInfo);
      const courseInput = body.course === undefined ? body : body.course;
      const course = parseCourse(courseInput, info.USER_ID);
      return service.getCourseInfo(info, course, authorization);
    },
  };
}
