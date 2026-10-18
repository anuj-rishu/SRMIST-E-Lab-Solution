"use client";

import { useCallback, useEffect, useRef, useState } from "react";
import {
  ArrowLeft,
  ArrowRight,
  CheckCircle2,
  CircleDot,
  Clock3,
  Terminal,
} from "lucide-react";
import { ApiError, apiRequest, errorMessage } from "@/lib/api";
import { scoreOf } from "@/lib/format";
import type { Course, Evaluation, Question, QuestionInfo } from "@/lib/types";
import { useSession } from "../providers/session-provider";
import { Button } from "../ui/button";
import { ErrorState, Feedback } from "../ui/feedback";
import { QuestionSkeleton } from "../ui/skeleton";
import { ProblemStatement } from "./problem-statement";

interface Props {
  course: Course;
  question: Question & { sessionName: string };
  nextQuestion: Question | null;
  onBack: () => void;
  onNext: () => void;
  onCompleted: (sequenceId: number) => void;
}

export function QuestionWorkspace({
  course,
  question,
  nextQuestion,
  onBack,
  onNext,
  onCompleted,
}: Props) {
  const { token } = useSession();
  const [data, setData] = useState<QuestionInfo | null>(null);
  const [error, setError] = useState<string | null>(null);
  const [submitError, setSubmitError] = useState<string | null>(null);
  const [submitting, setSubmitting] = useState(false);
  const [solutionUnavailable, setSolutionUnavailable] = useState(false);
  const [evaluation, setEvaluation] = useState<Evaluation | null>(null);
  const [attempt, setAttempt] = useState(0);
  const live = useRef(true);
  const submissionPending = useRef(false);

  useEffect(() => {
    live.current = true;
    const controller = new AbortController();
    // Let development effect replay finish before issuing the network request.
    const startRequest = setTimeout(() => {
      if (token) {
        void apiRequest<QuestionInfo>("getinfo", {
          token,
          body: { course, SEQUENCE_ID: question.SEQUENCE_ID },
          signal: controller.signal,
        })
          .then((result) => {
            if (live.current && !controller.signal.aborted) {
              if (
                !result.questionData ||
                typeof result.questionData.Q_DESC !== "string"
              ) {
                throw new Error(
                  "Question details are unavailable. Please refresh and try again.",
                );
              }
              setData(result);
              setError(null);
            }
          })
          .catch((issue) => {
            if (!controller.signal.aborted && live.current)
              setError(errorMessage(issue));
          });
      }
    }, 0);
    return () => {
      live.current = false;
      clearTimeout(startRequest);
      controller.abort();
    };
  }, [token, course, question.SEQUENCE_ID, attempt]);

  const submit = useCallback(async () => {
    if (!token || submissionPending.current) return;
    submissionPending.current = true;
    setSubmitting(true);
    setSubmitError(null);
    setSolutionUnavailable(false);
    setEvaluation(null);
    try {
      const result = await apiRequest<Evaluation>("solve", {
        token,
        body: { course, SEQUENCE_ID: question.SEQUENCE_ID },
      });
      if (!live.current) return;
      setEvaluation(result);
      if (scoreOf(result.result?.evalPercentage) === 100)
        onCompleted(question.SEQUENCE_ID);
    } catch (issue) {
      if (live.current) {
        const unavailable =
          issue instanceof ApiError &&
          ((issue.status === 409 &&
            issue.message.includes("No confident, unique solution match")) ||
            (issue.status === 404 &&
              issue.message.includes("No indexed solutions")) ||
            (issue.status === 422 &&
              issue.message.includes("does not contain source code")));
        if (unavailable) setSolutionUnavailable(true);
        else setSubmitError(errorMessage(issue));
      }
    } finally {
      submissionPending.current = false;
      if (live.current) setSubmitting(false);
    }
  }, [token, course, question.SEQUENCE_ID, onCompleted]);

  const score = scoreOf(evaluation?.result?.evalPercentage);
  const passed = score === 100;
  const primaryAction = useCallback(() => {
    if (!data || error || submitting || submissionPending.current) return;
    if (passed || solutionUnavailable) {
      if (nextQuestion) onNext();
      else onBack();
    } else {
      void submit();
    }
  }, [
    data,
    error,
    submitting,
    passed,
    solutionUnavailable,
    nextQuestion,
    onNext,
    onBack,
    submit,
  ]);

  useEffect(() => {
    function handleShortcut(event: KeyboardEvent) {
      if (
        event.key.toLowerCase() !== "n" ||
        event.repeat ||
        event.isComposing ||
        event.defaultPrevented ||
        event.ctrlKey ||
        event.metaKey ||
        event.altKey
      )
        return;
      const target = event.target;
      if (
        target instanceof HTMLElement &&
        (target.isContentEditable ||
          target.closest("input, textarea, select, [role='textbox']"))
      )
        return;
      event.preventDefault();
      primaryAction();
    }
    window.addEventListener("keydown", handleShortcut);
    return () => window.removeEventListener("keydown", handleShortcut);
  }, [primaryAction]);

  const nextQuestionButton = (
    <Button
      variant="secondary"
      onClick={nextQuestion ? onNext : onBack}
      disabled={submitting}
      className="next-question"
    >
      {nextQuestion ? (
        <>
          Next question <ArrowRight size={16} />
        </>
      ) : (
        "Back to all questions"
      )}
    </Button>
  );

  return (
    <div className="page-enter question-workspace">
      <button className="back-link" onClick={onBack} disabled={submitting}>
        <ArrowLeft size={16} />
        Back to questions
      </button>
      <div className="page-heading question-page-heading">
        <div>
          <h1>
            Question {question.SEQUENCE_ID}
            <span className="blue-text">.</span>
          </h1>
          <p>{question.sessionName}</p>
        </div>
        <span
          className={`question-state-label ${question.status === 2 ? "completed" : "available"}`}
        >
          {question.status === 2 ? (
            <CheckCircle2 size={15} />
          ) : (
            <CircleDot size={15} />
          )}
          {question.status === 2 ? "Completed" : "Ready to solve"}
        </span>
      </div>
      {error ? (
        <>
          <ErrorState
            message={error}
            onRetry={() => {
              setError(null);
              setData(null);
              setAttempt((value) => value + 1);
            }}
          />
          {nextQuestionButton}
        </>
      ) : !data ? (
        <QuestionSkeleton />
      ) : (
        <div className="question-layout">
          <article className="statement-card">
            <div className="statement-card-title">
              <Terminal size={17} />
              <h2>Problem statement</h2>
              <span>C</span>
            </div>
            <div className="statement-card-body">
              <ProblemStatement text={data.questionData.Q_DESC} />
            </div>
            {!!data.questionData.TESTCASES?.length && (
              <div className="testcases">
                <h3>Example test cases</h3>
                {data.questionData.TESTCASES.map((test, index) => (
                  <div className="testcase" key={test._id || index}>
                    <span className="testcase-label">EXAMPLE {index + 1}</span>
                    <div className="testcase-columns">
                      <div>
                        <span>Input</span>
                        <pre>{test.INPUT || "No input"}</pre>
                      </div>
                      <div>
                        <span>Expected output</span>
                        <pre>{test.OUTPUT}</pre>
                      </div>
                    </div>
                  </div>
                ))}
              </div>
            )}
            {!!data.questionData.MANDATORY?.length && (
              <div className="mandatory">
                <h3>Required concepts</h3>
                <div>
                  {data.questionData.MANDATORY.map((item, index) => (
                    <code key={index}>{item}</code>
                  ))}
                </div>
              </div>
            )}
          </article>
          <aside className="submission-column">
            <section className="submission-card">
              <span className="eyebrow">YOUR NEXT STEP</span>
              <h2>
                {passed ? "A little further ahead." : "Ready when you are."}
              </h2>
              <div className="submission-details">
                <span>
                  Language
                  <strong>
                    {evaluation?.language === "cpp"
                      ? "C++"
                      : evaluation?.language === "c"
                        ? "C"
                        : "Auto"}
                  </strong>
                </span>
                <span>
                  Question<strong>#{question.SEQUENCE_ID}</strong>
                </span>
                <span>
                  Level<strong>0{question.level}</strong>
                </span>
              </div>
              <Button
                loading={submitting}
                onClick={primaryAction}
                aria-keyshortcuts="n"
                title="Shortcut: N"
                className="submit-solution"
              >
                {submitting
                  ? "Evaluating solution…"
                  : passed || solutionUnavailable
                    ? nextQuestion
                      ? "Next question"
                      : "Back to all questions"
                    : "Submit solution"}
                {!submitting && <ArrowRight size={16} />}
              </Button>
              {!submitting && (
                <p className="submission-help">
                  Press <kbd>N</kbd> to{" "}
                  {passed || solutionUnavailable
                    ? nextQuestion
                      ? "open the next question"
                      : "return to all questions"
                    : "submit solution"}
                  .
                </p>
              )}
              {submitting && (
                <p className="submission-help" role="status">
                  Finding the solution and running test cases. This may take a
                  moment.
                </p>
              )}
              {solutionUnavailable && (
                <p className="solution-unavailable" role="status">
                  Oh no, we don’t have a solution for this question 😔
                </p>
              )}
              {submitError && <Feedback>{submitError}</Feedback>}
              {evaluation && (
                <div
                  className={`evaluation-result ${passed ? "evaluation-passed" : ""}`}
                  role="status"
                >
                  <div>
                    <CheckCircle2 size={20} />
                    <strong>
                      {passed
                        ? "All checks passed."
                        : score !== null
                          ? "Evaluation complete."
                          : "Submission received."}
                    </strong>
                  </div>
                  {score !== null && (
                    <span className="evaluation-score">
                      {score}
                      <small>%</small>
                    </span>
                  )}
                  <p>
                    {passed
                      ? "This question is now marked complete."
                      : evaluation.msg ||
                        "Review your evaluation results below."}
                  </p>
                  {evaluation.result?.exeTime !== undefined && (
                    <span className="execution-time">
                      <Clock3 size={12} />
                      {evaluation.result.exeTime} ms execution time
                    </span>
                  )}
                </div>
              )}
              {!passed &&
                !submitting &&
                (evaluation || submitError || solutionUnavailable) &&
                nextQuestionButton}
            </section>
          </aside>
        </div>
      )}
    </div>
  );
}
