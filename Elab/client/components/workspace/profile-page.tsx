"use client";

import {
  BookOpen,
  CircleCheck,
  GraduationCap,
  Mail,
  Phone,
  Trophy,
  UserRound,
} from "lucide-react";
import { useWorkspace } from "../providers/workspace-provider";
import { displayName, initials, solvedInCourse } from "@/lib/format";
import { PageSkeleton } from "../ui/skeleton";
import { ErrorState } from "../ui/feedback";

export function ProfilePage() {
  const { profile, courses, rank, loading, error, refresh } = useWorkspace();
  if (loading) return <PageSkeleton variant="profile" />;
  if (!profile)
    return (
      <ErrorState
        message={error || "Your profile is unavailable."}
        onRetry={() => void refresh()}
      />
    );
  const solved = courses.reduce(
    (total, course) => total + solvedInCourse(course),
    0,
  );
  const details = [
    {
      icon: UserRound,
      label: "Register number",
      value: profile.REGISTER_NUMBER,
    },
    { icon: Mail, label: "Email address", value: profile.MAIL_ID },
    {
      icon: GraduationCap,
      label: "Department",
      value: profile.DEPARTMENT ? displayName(profile.DEPARTMENT) : undefined,
    },
    { icon: Phone, label: "Phone number", value: profile.MOBILE },
  ];
  return (
    <div className="page-enter">
      <div className="page-heading">
        <div>
          <h1>
            Your profile<span className="blue-text">.</span>
          </h1>
        </div>
      </div>
      <section className="profile-card">
        <div className="profile-card-main">
          <span className="avatar avatar-large">
            {initials(profile.FIRST_NAME, profile.LAST_NAME)}
          </span>
          <div>
            <span className="eyebrow">E-LAB STUDENT</span>
            <h2>
              {displayName(profile.FIRST_NAME)}{" "}
              {profile.LAST_NAME ? displayName(profile.LAST_NAME) : ""}
            </h2>
            <p>{profile.USER_ID}</p>
          </div>
        </div>
        <div className="profile-milestones">
          <div>
            <Trophy size={19} />
            <strong>{rank?.RANK ? `#${rank.RANK}` : "—"}</strong>
            <span>Current rank</span>
          </div>
          <div>
            <CircleCheck size={19} />
            <strong>{solved}</strong>
            <span>Problems solved</span>
          </div>
          <div>
            <BookOpen size={19} />
            <strong>{courses.length}</strong>
            <span>Registered courses</span>
          </div>
        </div>
        <dl className="profile-details">
          {details.map(({ icon: Icon, label, value }) => (
            <div key={label}>
              <Icon size={17} />
              <div>
                <dt>{label}</dt>
                <dd>{value || "Not provided"}</dd>
              </div>
            </div>
          ))}
        </dl>
      </section>
    </div>
  );
}
