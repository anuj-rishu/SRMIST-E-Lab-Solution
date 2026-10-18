import type { ElabService } from "../services/elab.service.js";
import type { Controller } from "../types/http.js";
import { parseStudentInfo } from "../utils/validation.js";

export function createProfileController(service: ElabService): {
  profile: Controller;
} {
  return {
    profile: ({ studentInfo, authorization }) =>
      service.profile(parseStudentInfo(studentInfo), authorization),
  };
}
