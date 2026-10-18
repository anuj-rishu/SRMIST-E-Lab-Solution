import { QuestionService } from "../services/question.service.js";
import type { SolutionMatcher } from "../services/solution-search.service.js";
import type { ElabService } from "../services/elab.service.js";
import type { Controller } from "../types/http.js";
import {
  parseCourse,
  parseSequenceId,
  parseSolveQuestion,
  parseStudentRole,
  parseStudentInfo,
} from "../utils/validation.js";

export function createQuestionController(
  service: ElabService,
  solutions: SolutionMatcher,
): {
  getInfo: Controller;
  solve: Controller;
} {
  const questions = new QuestionService(service, solutions);
  return {
    getInfo: ({ body, studentInfo, authorization }) => {
      const info = parseStudentInfo(studentInfo);
      const role = parseStudentRole(info);
      const course = parseCourse(body.course, info.USER_ID);
      const sequenceId = parseSequenceId(body.SEQUENCE_ID);
      return service.getQuestionInfo(
        info,
        course,
        sequenceId,
        role,
        authorization,
      );
    },
    solve: ({ body, studentInfo, authorization }) => {
      const info = parseStudentInfo(studentInfo);
      const input = parseSolveQuestion(body, info.USER_ID);
      return questions.solve(info, input, authorization);
    },
  };
}
