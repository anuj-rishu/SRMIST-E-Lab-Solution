export interface Profile {
  USER_ID: string;
  FIRST_NAME?: string;
  LAST_NAME?: string;
  MAIL_ID?: string;
  MOBILE?: string;
  REGISTER_NUMBER?: string;
  DEPARTMENT?: string;
  ROLE?: string;
}

export interface Course extends Record<string, unknown> {
  _id: string;
  USER_ID: string;
  COURSE_ID: number;
  COURSE_NAME: string;
  TITLE?: string;
  LEVEL1: number;
  LEVEL2: number;
  LEVEL3: number;
  BATCH_NAME?: string;
  FACULTY_NAME?: string;
}

export interface Rank {
  RANK: number;
  TOTAL: number;
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

export interface CourseRequestCatalog {
  Status: number;
  academicCourses: RequestableCourse[];
  certificationCourses: RequestableCourse[];
}

export interface Question {
  SEQUENCE_ID: number;
  level: number;
  status: number;
}

export interface CourseSession {
  id: number;
  name: string;
  totalQuestions: number;
  questions: Question[];
}

export interface CourseInfo {
  Status: number;
  courseId: number;
  totalSessions: number;
  totalQuestions: number;
  sessions: CourseSession[];
}

export interface TestCase {
  _id: number;
  INPUT: string;
  OUTPUT: string;
}

export interface QuestionInfo {
  Status: number;
  studentData: {
    Q_ID: string;
    SEQUENCE_ID: number;
    STATUS: number;
  };
  questionData: {
    Q_DESC: string;
    SESSION_NAME?: string;
    LEVEL?: number;
    TESTCASES?: TestCase[];
    MANDATORY?: string[];
    TAGS?: string[];
  };
}

export interface Evaluation {
  language?: "c" | "cpp";
  Status: number;
  msg?: string;
  result?: {
    evalPercentage?: number | string;
    exeTime?: number | string;
    statusArray?: { msg: string; color: string }[];
  };
  matchedSolution?: {
    id: string;
    title: string;
    filename: string;
    score: number;
  };
}
