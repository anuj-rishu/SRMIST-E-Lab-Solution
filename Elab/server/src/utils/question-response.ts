import { questionPlainText } from "./question-text.js";
import { isObject } from "./validation.js";

export function formatQuestionInfo(data: unknown): unknown {
  if (
    !isObject(data) ||
    data.Status !== 1 ||
    !isObject(data.questionData) ||
    typeof data.questionData.Q_DESC !== "string"
  ) {
    return data;
  }
  const description = questionPlainText(data.questionData.Q_DESC);
  return {
    ...data,
    questionData: {
      ...data.questionData,
      Q_DESC: description,
    },
  };
}
