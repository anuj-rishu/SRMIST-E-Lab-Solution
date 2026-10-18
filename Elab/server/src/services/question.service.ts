import type {
  SolveQuestionInput,
  StudentInfo,
  StudentQuestionData,
} from "../types/elab.js";
import type { ApiResult } from "../types/http.js";
import { HttpError } from "../utils/http-error.js";
import { prepareSubmissionCode } from "../utils/mandatory-code.js";
import { submissionLanguage } from "../utils/submission-language.js";
import { logger } from "../utils/logger.js";
import { isObject, parseStudentRole } from "../utils/validation.js";
import type { SolutionMatcher } from "./solution-search.service.js";
import type { ElabService } from "./elab.service.js";

function succeeded(response: ApiResult): boolean {
  return (
    response.status >= 200 &&
    response.status < 300 &&
    isObject(response.data) &&
    response.data.Status === 1
  );
}

async function measured<T>(
  timings: Record<string, number>,
  stage: string,
  action: () => Promise<T>,
): Promise<T> {
  const started = performance.now();
  try {
    return await action();
  } finally {
    timings[stage] = Math.round(performance.now() - started);
  }
}

function failedStage(stage: string, response: ApiResult): ApiResult {
  return {
    status: response.status,
    data: { Status: 0, stage, response: response.data },
  };
}

function questionData(
  value: unknown,
  input: SolveQuestionInput,
): StudentQuestionData {
  if (
    !isObject(value) ||
    typeof value._id !== "string" ||
    !value._id.trim() ||
    typeof value.Q_ID !== "string" ||
    !value.Q_ID.trim() ||
    value.COURSE_ID !== input.course.COURSE_ID ||
    value.SEQUENCE_ID !== input.sequenceId
  ) {
    throw new HttpError(
      502,
      "E-Lab returned invalid or mismatched question data. No code was submitted.",
    );
  }
  return {
    ...value,
    _id: value._id,
    Q_ID: value.Q_ID,
    COURSE_ID: input.course.COURSE_ID,
    SEQUENCE_ID: input.sequenceId,
  };
}

export class QuestionService {
  constructor(
    private readonly elab: ElabService,
    private readonly solutions: SolutionMatcher,
  ) {}

  async solve(
    info: StudentInfo,
    input: SolveQuestionInput,
    authorization: string,
  ): Promise<ApiResult> {
    const started = performance.now();
    const timings: Record<string, number> = {};
    try {
      return await this.solveTimed(info, input, authorization, timings);
    } finally {
      logger.info(
        {
          courseId: input.course.COURSE_ID,
          sequenceId: input.sequenceId,
          timingsMs: timings,
          totalMs: Math.round(performance.now() - started),
        },
        "Question submission timing",
      );
    }
  }

  private async solveTimed(
    info: StudentInfo,
    input: SolveQuestionInput,
    authorization: string,
    timings: Record<string, number>,
  ): Promise<ApiResult> {
    const role = parseStudentRole(info);
    if (typeof info.FIRST_NAME !== "string" || !info.FIRST_NAME.trim()) {
      throw new HttpError(
        401,
        "Login token does not contain a student name. Please log in again.",
      );
    }
    const question = await measured(timings, "getinfo", () =>
      this.elab.getQuestionInfo(
        info,
        input.course,
        input.sequenceId,
        role,
        authorization,
      ),
    );
    if (!succeeded(question)) return failedStage("getinfo", question);
    const studentData = questionData(
      isObject(question.data) ? question.data.studentData : undefined,
      input,
    );

    const description =
      isObject(question.data) && isObject(question.data.questionData)
        ? question.data.questionData.Q_DESC
        : undefined;
    if (typeof description !== "string" || !description.trim()) {
      throw new HttpError(
        502,
        "E-Lab did not return a question description. No code was submitted.",
      );
    }
    const mandatory =
      isObject(question.data) && isObject(question.data.questionData)
        ? question.data.questionData.MANDATORY
        : undefined;
    if (
      mandatory !== undefined &&
      (!Array.isArray(mandatory) ||
        mandatory.some((item) => typeof item !== "string"))
    ) {
      throw new HttpError(
        502,
        "E-Lab returned invalid mandatory requirements. No code was submitted.",
      );
    }
    const match = await measured(timings, "solutionLookup", () =>
      this.solutions.find(
        description,
        input.course.COURSE_ID,
        mandatory ?? [],
        studentData.Q_ID,
        {
          complexity:
            isObject(question.data) && isObject(question.data.questionData)
              ? question.data.questionData.COMPLEXITY
              : undefined,
          testcases:
            isObject(question.data) && isObject(question.data.questionData)
              ? question.data.questionData.TESTCASES
              : undefined,
        },
      ),
    );
    const complexity =
      isObject(question.data) && isObject(question.data.questionData)
        ? question.data.questionData.COMPLEXITY
        : undefined;
    const maximumLines =
      Array.isArray(complexity) && typeof complexity[2] === "number"
        ? complexity[2]
        : undefined;
    const prepareStarted = performance.now();
    const code = prepareSubmissionCode(
      match.solution,
      mandatory ?? [],
      maximumLines,
    );
    timings.prepareCode = Math.round(performance.now() - prepareStarted);
    const language = submissionLanguage(code);
    const logs = await measured(timings, "savelogs", () =>
      this.elab.saveQuestionLogs(
        info,
        code,
        input.input,
        authorization,
        language,
      ),
    );
    if (!succeeded(logs)) return failedStage("savelogs", logs);

    const evaluation = await measured(timings, "evaluate", () =>
      this.elab.evaluateQuestion(
        info,
        studentData,
        code,
        authorization,
        language,
      ),
    );
    if (!succeeded(evaluation)) return failedStage("evaluate", evaluation);
    return {
      status: evaluation.status,
      data: {
        ...(isObject(evaluation.data) ? evaluation.data : {}),
        courseId: input.course.COURSE_ID,
        SEQUENCE_ID: input.sequenceId,
        logsSaved: true,
        language,
        matchedSolution: {
          id: match.id,
          title: match.title,
          filename: match.filename,
          score: match.score,
        },
      },
    };
  }
}
