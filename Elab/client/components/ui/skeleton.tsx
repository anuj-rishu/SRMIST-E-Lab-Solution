import type { CSSProperties } from "react";

export type PageSkeletonVariant =
  "overview" | "courses" | "course" | "profile" | "question";

export function Skeleton({
  width = "100%",
  height = 16,
  circle = false,
}: {
  width?: CSSProperties["width"];
  height?: CSSProperties["height"];
  circle?: boolean;
}) {
  return (
    <span
      className={`skeleton ${circle ? "skeleton-circle" : ""}`}
      style={{ width, height }}
    />
  );
}

function HeadingSkeleton() {
  return (
    <div className="page-heading">
      <Skeleton width="min(70%, 320px)" height={36} />
    </div>
  );
}

function CourseCardsSkeleton() {
  return (
    <section className="courses-section">
      <div className="content-section-heading">
        <div className="skeleton-stack">
          <Skeleton width={180} height={16} />
          <Skeleton width={240} height={28} />
        </div>
        <Skeleton width={80} height={32} />
      </div>
      <div className="course-grid">
        {[0, 1].map((item) => (
          <article className="course-card" key={item}>
            <div className="course-card-heading">
              <Skeleton width={40} height={40} />
              <Skeleton width={90} height={16} />
            </div>
            <div className="skeleton-course-title">
              <Skeleton width="65%" height={28} />
            </div>
            <Skeleton width="90%" height={20} />
            <div className="course-levels">
              {[0, 1, 2].map((level) => (
                <div className="skeleton-stack" key={level}>
                  <Skeleton width="80%" />
                  <Skeleton width="70%" height={28} />
                </div>
              ))}
            </div>
            <div className="course-card-footer">
              <Skeleton width="50%" height={20} />
              <Skeleton width="25%" height={24} />
            </div>
          </article>
        ))}
      </div>
    </section>
  );
}

function ProfileSkeleton() {
  return (
    <>
      <HeadingSkeleton />
      <section className="profile-card">
        <div className="profile-card-main">
          <Skeleton width={76} height={76} circle />
          <div className="skeleton-stack skeleton-profile-name">
            <Skeleton width="45%" />
            <Skeleton width="90%" height={28} />
            <Skeleton width="60%" />
          </div>
        </div>
        <div className="profile-milestones">
          {[0, 1, 2].map((item) => (
            <div key={item}>
              <Skeleton width={19} height={19} />
              <Skeleton width={48} height={30} />
              <span>
                <Skeleton width="85%" height={20} />
              </span>
            </div>
          ))}
        </div>
        <dl className="profile-details">
          {[0, 1, 2, 3].map((item) => (
            <div key={item}>
              <Skeleton width={17} height={17} />
              <div className="skeleton-stack skeleton-profile-name">
                <Skeleton width="45%" />
                <Skeleton width="90%" height={20} />
              </div>
            </div>
          ))}
        </dl>
      </section>
    </>
  );
}

function CourseSkeleton() {
  return (
    <div className="course-overview">
      <div className="back-link">
        <Skeleton width={110} height={20} />
      </div>
      <HeadingSkeleton />
      <div className="course-progress-summary">
        <div className="skeleton-stack">
          <Skeleton width={180} />
          <Skeleton width={230} height={28} />
        </div>
        <Skeleton width="35%" height={8} />
      </div>
      <div className="question-toolbar">
        <Skeleton width="min(100%, 360px)" height={46} />
      </div>
      <div className="sessions-list">
        {[0, 1, 2].map((item) => (
          <section className="session-card" key={item}>
            <div className="session-heading">
              <Skeleton width="45%" height={24} />
              <Skeleton width="20%" />
            </div>
            <div className="question-circles">
              {Array.from({ length: 10 }, (_, index) => (
                <Skeleton width={46} height={46} circle key={index} />
              ))}
            </div>
          </section>
        ))}
      </div>
    </div>
  );
}

export function QuestionSkeleton() {
  return (
    <div
      className="question-layout"
      role="status"
      aria-label="Loading question"
      aria-busy="true"
    >
      <article className="statement-card">
        <div className="statement-card-title">
          <Skeleton width={180} height={24} />
        </div>
        <div className="statement-card-body skeleton-stack">
          <Skeleton width="35%" height={22} />
          {[100, 96, 90, 100, 72].map((width, index) => (
            <Skeleton width={`${width}%`} height={18} key={index} />
          ))}
          <div className="skeleton-section-gap" />
          <Skeleton width="30%" height={22} />
          <Skeleton width="85%" height={18} />
          <Skeleton width="65%" height={18} />
        </div>
        <div className="testcases skeleton-stack">
          <Skeleton width={160} height={22} />
          <Skeleton height={100} />
        </div>
      </article>
      <aside className="submission-column">
        <section className="submission-card skeleton-stack">
          <Skeleton width="60%" />
          <Skeleton width="85%" height={28} />
          <Skeleton height={18} />
          <Skeleton width="80%" height={18} />
          <Skeleton height={100} />
          <Skeleton height={44} />
        </section>
      </aside>
    </div>
  );
}

export function PageSkeleton({
  variant = "overview",
}: {
  variant?: PageSkeletonVariant;
}) {
  return (
    <div
      role="status"
      aria-label={`Loading ${variant}`}
      aria-busy="true"
      className={`page-skeleton ${variant === "courses" ? "courses-page" : ""}`}
    >
      {variant === "profile" ? (
        <ProfileSkeleton />
      ) : variant === "course" ? (
        <CourseSkeleton />
      ) : variant === "question" ? (
        <QuestionSkeleton />
      ) : (
        <>
          {variant === "overview" && (
            <>
              <HeadingSkeleton />
              <div className="stat-grid">
                {[0, 1, 2].map((item) => (
                  <article className="stat-card" key={item}>
                    <div className="stat-card-top">
                      <Skeleton width="65%" height={20} />
                      <Skeleton width={17} height={17} />
                    </div>
                    <div className="stat-value">
                      <Skeleton width={65} height={50} />
                    </div>
                    <div className="stat-detail">
                      <Skeleton width="90%" height={21} />
                    </div>
                  </article>
                ))}
              </div>
            </>
          )}
          <CourseCardsSkeleton />
        </>
      )}
    </div>
  );
}

export function WorkspaceSkeleton() {
  return (
    <div
      className="workspace"
      role="status"
      aria-label="Loading workspace"
      aria-busy="true"
    >
      <aside className="sidebar">
        <div className="sidebar-brand">
          <Skeleton width={120} height={36} />
        </div>
        <div className="skeleton-sidebar-links">
          {[0, 1, 2].map((item) => (
            <Skeleton key={item} height={44} />
          ))}
        </div>
      </aside>
      <div className="workspace-main">
        <div className="workspace-header">
          <Skeleton width={160} height={20} />
          <Skeleton width={34} height={34} circle />
        </div>
        <div className="workspace-content">
          <PageSkeleton />
        </div>
      </div>
    </div>
  );
}
