import { pino } from "pino";

export const logger = pino({
  redact: [
    "password",
    "PASSWORD",
    "token",
    "authorization",
    "headers.authorization",
  ],
});
