import type { ElabConfig } from "../config/env.js";
import type {
  CourseInfo,
  LoginInput,
  RequestableCourse,
  StudentInfo,
  StudentQuestionData,
} from "../types/elab.js";
import type { ApiResult, FetchClient } from "../types/http.js";
import { HttpError } from "../utils/http-error.js";
import { parseElabToken } from "../utils/elab-token.js";
import { isObject } from "../utils/validation.js";
import { formatCourseInfo } from "../utils/course-response.js";
import { formatQuestionInfo } from "../utils/question-response.js";
import {
  submissionLanguage,
  type SubmissionLanguage,
} from "../utils/submission-language.js";

export class ElabService {
  constructor(
    private readonly config: ElabConfig,
    private readonly fetchImpl: FetchClient = globalThis.fetch,
  ) {}

  private async post(
    path: string,
    body: Record<string, unknown>,
    authorization?: string,
    options: { includeKey?: boolean } = {},
  ): Promise<ApiResult> {
    const headers: Record<string, string> = {
      Accept: "application/json, text/plain, */*",
      "Content-Type": "application/json;charset=UTF-8",
      Origin: this.config.origin,
      Referer: this.config.referer,
    };
    if (authorization) headers.Authorization = authorization;
    let response: Response;
    try {
      response = await this.fetchImpl(`${this.config.baseUrl}${path}`, {
        method: "POST",
        headers,
        body: JSON.stringify({
          ...body,
          ...(options.includeKey === false ? {} : { KEY: this.config.key }),
        }),
        signal: AbortSignal.timeout(this.config.timeoutMs),
        redirect: "error",
      });
    } catch (error) {
      const timedOut =
        error instanceof Error &&
        ["TimeoutError", "AbortError"].includes(error.name);
      throw new HttpError(
        timedOut ? 504 : 502,
        timedOut
          ? "E-Lab request timed out."
          : "Could not reach the E-Lab server.",
      );
    }
    try {
      const data: unknown = await response.json();
      return { status: response.status, data };
    } catch (error) {
      if (
        error instanceof Error &&
        ["TimeoutError", "AbortError"].includes(error.name)
      ) {
        throw new HttpError(504, "E-Lab request timed out.");
      }
      throw new HttpError(502, "E-Lab returned an invalid JSON response.");
    }
  }

  login(input: LoginInput): Promise<ApiResult> {
    return this.post("/ict/login", { ...input });
  }

  async profile(info: StudentInfo, authorization: string): Promise<ApiResult> {
    const response = await this.post(
      "/ict/gettoken",
      { INFO: info },
      authorization,
    );
    if (
      response.status < 200 ||
      response.status >= 300 ||
      !isObject(response.data) ||
      response.data.Status !== 1
    ) {
      return response;
    }
    try {
      if (typeof response.data.result !== "string")
        throw new Error("Missing profile token.");
      const { studentInfo } = parseElabToken(response.data.result);
      if (studentInfo.USER_ID !== info.USER_ID)
        throw new Error("Profile identity mismatch.");
      return {
        status: response.status,
        data: { Status: 1, profile: studentInfo },
      };
    } catch {
      throw new HttpError(502, "E-Lab returned an invalid profile response.");
    }
  }

  registeredCourses(
    info: StudentInfo,
    authorization: string,
  ): Promise<ApiResult> {
    return this.post(
      "/ict/student/home/registeredcourses",
      { info },
      authorization,
    );
  }

  requestableCourses(
    info: StudentInfo,
    authorization: string,
  ): Promise<ApiResult> {
    return this.post(
      "/ict/student/courserequest/allcourses",
      { info },
      authorization,
    );
  }

  requestCourse(
    info: StudentInfo,
    course: RequestableCourse,
    authorization: string,
  ): Promise<ApiResult> {
    return this.post(
      "/ict/student/courserequest/send",
      {
        info,
        course,
        type: `${course.COURSE_NAME}_${course.MODE}_${course.SET}`,
      },
      authorization,
    );
  }

  async getCourseInfo(
    info: StudentInfo,
    course: CourseInfo,
    authorization: string,
  ): Promise<ApiResult> {
    const response = await this.post(
      "/ict/student/courseview/getcourseinfo",
      { info, course },
      authorization,
    );
    if (response.status < 200 || response.status >= 300) return response;
    return {
      status: response.status,
      data: formatCourseInfo(response.data, course.COURSE_ID),
    };
  }

  async getQuestionInfo(
    info: StudentInfo,
    course: CourseInfo,
    sequenceId: number,
    role: string,
    authorization: string,
  ): Promise<ApiResult> {
    const response = await this.post(
      "/ict/student/questionview/getinfo",
      { ROLE: role, info, course, SEQUENCE_ID: sequenceId },
      authorization,
    );
    if (response.status < 200 || response.status >= 300) return response;
    return { status: response.status, data: formatQuestionInfo(response.data) };
  }

  saveQuestionLogs(
    info: StudentInfo,
    code: string,
    input: string,
    authorization: string,
    language: SubmissionLanguage = submissionLanguage(code),
  ): Promise<ApiResult> {
    return this.post(
      "/ict/student/questionview/savelogs",
      {
        language,
        input,
        code,
        type: "regular",
        compileType: "evaluate",
        "api-key": this.config.compilerApiKey,
        student_id: `Class${info.USER_ID}`,
        student_name: info.FIRST_NAME,
        userid: info.USER_ID,
      },
      authorization,
      { includeKey: false },
    );
  }

  evaluateQuestion(
    info: StudentInfo,
    studentData: StudentQuestionData,
    code: string,
    authorization: string,
    language: SubmissionLanguage = submissionLanguage(code),
  ): Promise<ApiResult> {
    return this.post(
      "/ict/student/questionview/evaluate",
      {
        info,
        studentData,
        tempCode: code,
        code: [{ value: code, mode: 0 }],
        compilez: this.config.compilerUrl,
        language,
        student_id: `Class${info.USER_ID}`,
        ictserver: this.config.baseUrl,
      },
      authorization,
    );
  }

  getTest(info: StudentInfo, authorization: string): Promise<ApiResult> {
    return this.post("/ict/test/student/gettest", { info }, authorization);
  }

  rank(info: StudentInfo, authorization: string): Promise<ApiResult> {
    return this.post("/ict/student/home/rank", { info }, authorization);
  }
}
