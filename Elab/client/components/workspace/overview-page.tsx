"use client";

import { BookOpen, CircleCheck, Trophy } from "lucide-react";
import { useWorkspace } from "../providers/workspace-provider";
import { displayName, solvedInCourse } from "@/lib/format";
import { PageSkeleton } from "../ui/skeleton";
import { ErrorState } from "../ui/feedback";
import { CourseList } from "./course-card";
import { StatCard } from "./stat-card";

export function OverviewPage() {
  const { profile, courses, rank, loading, error, refresh } = useWorkspace();
  if (loading) return <PageSkeleton variant="overview" />;
  if (error && !profile && !courses.length)
    return <ErrorState message={error} onRetry={() => void refresh()} />;
  const solved = courses.reduce(
    (total, course) => total + solvedInCourse(course),
    0,
  );
  return (
    <div className="page-enter">
      <div className="page-heading">
        <div>
          <h1>
            Welcome back, {displayName(profile?.FIRST_NAME)}
            <span className="blue-text">.</span>
          </h1>
        </div>
      </div>
      {error && (
        <div className="inline-notice">
          Some workspace data couldn’t be refreshed.{" "}
          <button onClick={() => void refresh()}>Try again</button>
        </div>
      )}
      <div className="stat-grid">
        <StatCard
          icon={CircleCheck}
          label="Problems solved"
          value={solved}
          detail="Across all your registered courses"
        />
        <StatCard
          icon={Trophy}
          label="Your current rank"
          value={
            rank?.RANK ? (
              <>
                <span className="stat-prefix">#</span>
                {rank.RANK}
              </>
            ) : (
              "—"
            )
          }
          detail={
            rank?.RANK
              ? "Your position in the E-Lab ranking"
              : "Ranking will appear when available"
          }
        />
        <StatCard
          icon={BookOpen}
          label="Active courses"
          value={courses.length.toString().padStart(2, "0")}
          detail="A new opportunity in every session"
        />
      </div>
      <CourseList courses={courses} />
    </div>
  );
}
