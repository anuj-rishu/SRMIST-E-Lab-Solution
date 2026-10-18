export interface LoginInput {
  USER_ID: string;
  PASSWORD: string;
}

export interface StudentInfo extends Record<string, unknown> {
  USER_ID: string;
}

export interface CourseInfo extends Record<string, unknown> {
  _id: string;
  USER_ID: string;
  COURSE_ID: number;
}

export interface RequestableCourse {
  COURSE_NAME: string;
  COURSE_ID: number;
  ENABLED: number;
  TITLE: string;
  DESCRIPTION: string;
  TYPE: string;
  SET: string;
  MODE: string;
}

export interface SolveQuestionInput {
  course: CourseInfo;
  sequenceId: number;
  input: string;
}

export interface StudentQuestionData extends Record<string, unknown> {
  _id: string;
  COURSE_ID: number;
  Q_ID: string;
  SEQUENCE_ID: number;
}
