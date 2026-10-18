"use client";

import Link from "next/link";
import { useCallback, useEffect, useRef, useState } from "react";
import { ArrowLeft, Check, ChevronDown } from "lucide-react";
import { apiRequest, errorMessage } from "@/lib/api";
import { courseTitle, displayName, questionState } from "@/lib/format";
import type { CourseInfo } from "@/lib/types";
import { useSession } from "../providers/session-provider";
import { useWorkspace } from "../providers/workspace-provider";
import { PageSkeleton } from "../ui/skeleton";
import { ErrorState } from "../ui/feedback";
import { QuestionWorkspace } from "../questions/question-workspace";

export function CourseWorkspace({ courseId }: { courseId: number }) {
  const { token } = useSession();
  const { courses, loading: workspaceLoading } = useWorkspace();
  const course = courses.find((item) => item.COURSE_ID === courseId);
  const [info, setInfo] = useState<CourseInfo | null>(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);
  const [level, setLevel] = useState(1);
  const [selectedId, setSelectedId] = useState<number | null>(null);
  const requestId = useRef(0);

  useEffect(() => {
    const title = course ? courseTitle(course) : "Course";
    document.title =
      selectedId === null
        ? `${title} · E-Lab`
        : `Question ${selectedId} · ${title} · E-Lab`;
  }, [course, selectedId]);

  const loadCourse = useCallback(async () => {
    if (!token || !course) return;
    const id = ++requestId.current;
    setLoading(true);
    try {
      const result = await apiRequest<CourseInfo>("getcourseinfo", {
        token,
        body: { course },
      });
      if (id !== requestId.current) return;
      if (!Array.isArray(result.sessions))
        throw new Error("The course response is incomplete. Please refresh.");
      setInfo(result);
      setError(null);
    } catch (issue) {
      if (id === requestId.current) setError(errorMessage(issue));
    } finally {
      if (id === requestId.current) setLoading(false);
    }
  }, [token, course]);

  useEffect(() => {
    void loadCourse();
    return () => {
      requestId.current++;
    };
  }, [loadCourse]);

  if (workspaceLoading) return <PageSkeleton variant="course" />;
  if (!course)
    return (
      <div className="empty-state">
        <h2>Course not found.</h2>
        <p>Choose one of your registered courses to continue.</p>
        <Link href="/dashboard" className="button button-secondary">
          Back to overview
        </Link>
      </div>
    );
  if (!info && error)
    return <ErrorState message={error} onRetry={() => void loadCourse()} />;
  if (!info) return <PageSkeleton variant="course" />;

  const allQuestions = info.sessions
    .flatMap((session) =>
      session.questions.map((question) => ({
        ...question,
        sessionName: session.name,
      })),
    )
    .sort((a, b) => a.level - b.level || a.SEQUENCE_ID - b.SEQUENCE_ID);
  const levels = [
    ...new Set(allQuestions.map((question) => question.level)),
  ].sort((a, b) => a - b);
  const selected = allQuestions.find(
    (question) => question.SEQUENCE_ID === selectedId,
  );
  const completed = allQuestions.filter(
    (question) => question.status === 2,
  ).length;
  const progress = allQuestions.length
    ? Math.round((completed / allQuestions.length) * 100)
    : 0;
  const nextQuestion = selected
    ? allQuestions
        .slice(
          allQuestions.findIndex(
            (question) => question.SEQUENCE_ID === selectedId,
          ) + 1,
        )
        .find((question) => question.status !== 2) || null
    : null;

  function openQuestion(sequenceId: number | null) {
    setSelectedId(sequenceId);
    window.scrollTo({ top: 0, behavior: "instant" });
  }

  function markCompleted(sequenceId: number) {
    setInfo((current) =>
      current
        ? {
            ...current,
            sessions: current.sessions.map((session) => ({
              ...session,
              questions: session.questions.map((question) =>
                question.SEQUENCE_ID === sequenceId
                  ? { ...question, status: 2 }
                  : question,
              ),
            })),
          }
        : current,
    );
  }

  if (selected)
    return (
      <QuestionWorkspace
        key={selected.SEQUENCE_ID}
        course={course}
        question={selected}
        nextQuestion={nextQuestion}
        onBack={() => {
          openQuestion(null);
        }}
        onNext={() => {
          if (nextQuestion) openQuestion(nextQuestion.SEQUENCE_ID);
        }}
        onCompleted={markCompleted}
      />
    );

  return (
    <div className="page-enter course-overview">
      <Link className="back-link" href="/dashboard/courses">
        <ArrowLeft size={16} />
        Your courses
      </Link>
      <div className="page-heading">
        <div>
          <h1>
            {courseTitle(course)}
            <span className="blue-text">.</span>
          </h1>
        </div>
      </div>
      {error && <div className="inline-notice">{error}</div>}
      <div className="course-progress-summary">
        <div>
          <span className="eyebrow">YOUR COURSE PROGRESS</span>
          <p>
            <strong>{completed}</strong> of {allQuestions.length} problems
            completed
          </p>
        </div>
        <div className="course-progress-track">
          <span>{progress}% complete</span>
          <div
            role="progressbar"
            aria-label="Course completion"
            aria-valuenow={progress}
            aria-valuemin={0}
            aria-valuemax={100}
          >
            <i style={{ width: `${progress}%` }} />
          </div>
        </div>
      </div>
      <div className="question-toolbar">
        <div className="level-tabs" role="tablist" aria-label="Question levels">
          {levels.map((item) => {
            const questions = allQuestions.filter(
              (question) => question.level === item,
            );
            return (
              <button
                key={item}
                role="tab"
                aria-selected={level === item}
                aria-controls="level-questions"
                className={level === item ? "is-active" : ""}
                onClick={() => setLevel(item)}
              >
                Level 0{item}
                <span>
                  {questions.filter((question) => question.status === 2).length}
                  /{questions.length}
                </span>
              </button>
            );
          })}
        </div>
        <div className="question-legend">
          <span>
            <i className="legend-completed" />
            Completed
          </span>
          <span>
            <i className="legend-available" />
            Available
          </span>
          <span>
            <i className="legend-unopened" />
            Not opened
          </span>
        </div>
      </div>
      <div
        id="level-questions"
        role="tabpanel"
        aria-label={`Level ${level} questions`}
        className="sessions-list"
      >
        {info.sessions.map((session) => {
          const questions = session.questions.filter(
            (question) => question.level === level,
          );
          if (!questions.length) return null;
          const done = questions.filter(
            (question) => question.status === 2,
          ).length;
          return (
            <section className="session-card" key={session.id}>
              <div className="session-heading">
                <div>
                  <span>{String(session.id).padStart(2, "0")}</span>
                  <h2>{displayName(session.name)}</h2>
                </div>
                <span className="session-count">
                  {done} / {questions.length} completed{" "}
                  <ChevronDown size={14} />
                </span>
              </div>
              <div className="question-circles">
                {questions.map((question) => {
                  const state = questionState(question);
                  return (
                    <button
                      key={question.SEQUENCE_ID}
                      className={`question-circle ${state}`}
                      onClick={() => openQuestion(question.SEQUENCE_ID)}
                      aria-label={`Question ${question.SEQUENCE_ID}, ${state}`}
                      title={`Question ${question.SEQUENCE_ID} · ${state}`}
                    >
                      <span>{question.SEQUENCE_ID}</span>
                      {state === "completed" && (
                        <Check className="circle-check" size={10} />
                      )}
                    </button>
                  );
                })}
              </div>
            </section>
          );
        })}
        {!allQuestions.length && (
          <div className="empty-state">
            <h2>No questions available yet.</h2>
            <p>Questions will appear when E-Lab makes this course available.</p>
          </div>
        )}
      </div>
    </div>
  );
}
