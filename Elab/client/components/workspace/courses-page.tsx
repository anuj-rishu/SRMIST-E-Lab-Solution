"use client";

import { useWorkspace } from "../providers/workspace-provider";
import { PageSkeleton } from "../ui/skeleton";
import { ErrorState } from "../ui/feedback";
import { CourseList } from "./course-card";

export function CoursesPage() {
  const { courses, loading, error, refresh } = useWorkspace();

  if (loading) return <PageSkeleton variant="courses" />;
  if (error && !courses.length)
    return <ErrorState message={error} onRetry={() => void refresh()} />;

  return (
    <div className="page-enter courses-page">
      <CourseList courses={courses} />
    </div>
  );
}
