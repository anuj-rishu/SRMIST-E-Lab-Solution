"use client";

import { useEffect, useRef, useState } from "react";
import { BookPlus } from "lucide-react";
import { apiRequest, errorMessage } from "@/lib/api";
import type { CourseRequestCatalog, RequestableCourse } from "@/lib/types";
import { useSession } from "../providers/session-provider";
import { useWorkspace } from "../providers/workspace-provider";
import { Button } from "../ui/button";
import { ErrorState, Feedback } from "../ui/feedback";
import { PageSkeleton } from "../ui/skeleton";

function courseKey(course: RequestableCourse) {
  return `${course.COURSE_ID}_${course.MODE}_${course.SET}`;
}

export function CourseRequestsPage() {
  const { token } = useSession();
  const {
    courses: registered,
    loading: accountLoading,
    refresh,
  } = useWorkspace();
  const [catalog, setCatalog] = useState<CourseRequestCatalog | null>(null);
  const [loading, setLoading] = useState(true);
  const [loadError, setLoadError] = useState<string | null>(null);
  const [revision, setRevision] = useState(0);
  const [sending, setSending] = useState<string | null>(null);
  const [requested, setRequested] = useState<Set<string>>(new Set());
  const [feedback, setFeedback] = useState<{
    text: string;
    success: boolean;
  } | null>(null);
  const sendingRequest = useRef(false);

  useEffect(() => {
    if (!token) return;
    const controller = new AbortController();
    apiRequest<CourseRequestCatalog>("courserequest/allcourses", {
      token,
      signal: controller.signal,
    })
      .then((data) => {
        if (controller.signal.aborted) return;
        if (
          !Array.isArray(data.academicCourses) ||
          !Array.isArray(data.certificationCourses)
        ) {
          throw new Error("E-Lab returned an invalid course catalog.");
        }
        setCatalog(data);
      })
      .catch((error: unknown) => {
        if (!controller.signal.aborted) setLoadError(errorMessage(error));
      })
      .finally(() => {
        if (!controller.signal.aborted) setLoading(false);
      });
    return () => controller.abort();
  }, [token, revision]);

  function reload() {
    setLoading(true);
    setLoadError(null);
    setRevision((value) => value + 1);
  }

  async function enroll(course: RequestableCourse) {
    const key = courseKey(course);
    if (
      !token ||
      sendingRequest.current ||
      requested.has(key) ||
      course.ENABLED !== 1 ||
      accountLoading ||
      registered.some((item) => item.COURSE_ID === course.COURSE_ID)
    )
      return;
    sendingRequest.current = true;
    setSending(key);
    setFeedback(null);
    try {
      const result = await apiRequest<{ Status: number; msg?: string }>(
        "courserequest/send",
        {
          token,
          body: { course },
        },
      );
      if (result.Status !== 1)
        throw new Error(
          result.msg || "E-Lab did not confirm the course request.",
        );
      setRequested((previous) => new Set([...previous, key]));
      setFeedback({
        text: result.msg || `Enrollment request sent for ${course.TITLE}.`,
        success: true,
      });
      void refresh();
    } catch (error) {
      setFeedback({ text: errorMessage(error), success: false });
    } finally {
      sendingRequest.current = false;
      setSending(null);
    }
  }

  if (loading) return <PageSkeleton variant="courses" />;
  if (loadError) return <ErrorState message={loadError} onRetry={reload} />;
  if (!catalog) return null;

  const groups = [
    { title: "Academic courses", courses: catalog.academicCourses },
    { title: "Certification courses", courses: catalog.certificationCourses },
  ];

  return (
    <div className="page-enter course-requests-page">
      <div className="page-heading">
        <div>
          <h1>Course requests</h1>
          <p>Find your next course and send an enrollment request.</p>
        </div>
      </div>
      {feedback && (
        <Feedback success={feedback.success}>{feedback.text}</Feedback>
      )}
      {groups.map((group) => {
        const courses = group.courses;
        return (
          <section
            className="courses-section"
            key={group.title}
            aria-label={group.title}
          >
            <div className="content-section-heading">
              <h2>{group.title}</h2>
              <span className="count-label">
                {courses.length} {courses.length === 1 ? "course" : "courses"}
              </span>
            </div>
            {courses.length ? (
              <div className="course-grid">
                {courses.map((course) => {
                  const key = courseKey(course);
                  const enrolled = registered.some(
                    (item) => item.COURSE_ID === course.COURSE_ID,
                  );
                  const sent = requested.has(key);
                  const enabled = course.ENABLED === 1;
                  return (
                    <article
                      className="course-card course-request-card"
                      key={key}
                    >
                      <div className="course-card-heading">
                        <span className="course-icon">
                          <BookPlus size={25} />
                        </span>
                        <span className="course-id">
                          {course.COURSE_NAME} · {course.SET}
                        </span>
                      </div>
                      <h3>{course.TITLE}</h3>
                      <p>{course.DESCRIPTION}</p>
                      <div className="course-request-footer">
                        <span>{course.MODE.toLowerCase()}</span>
                        <Button
                          onClick={() => void enroll(course)}
                          loading={sending === key}
                          disabled={
                            !enabled ||
                            enrolled ||
                            sent ||
                            sending !== null ||
                            accountLoading
                          }
                        >
                          {sending === key
                            ? "Sending…"
                            : enrolled
                              ? "Enrolled"
                              : sent
                                ? "Request sent"
                                : !enabled
                                  ? "Unavailable"
                                  : "Enroll"}
                        </Button>
                      </div>
                    </article>
                  );
                })}
              </div>
            ) : (
              <div className="empty-state">
                <BookPlus size={28} />
                <h3>No courses available.</h3>
                <p>Check back later for new courses.</p>
              </div>
            )}
          </section>
        );
      })}
    </div>
  );
}
