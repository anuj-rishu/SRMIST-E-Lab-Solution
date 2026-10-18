"use client";

import { useEffect, useState } from "react";
import Link from "next/link";
import { usePathname, useRouter } from "next/navigation";
import {
  BookOpen,
  BookPlus,
  ChevronRight,
  LayoutDashboard,
  LogOut,
  Menu,
  PanelLeftClose,
  RefreshCw,
  UserRound,
} from "lucide-react";
import { useSession } from "../providers/session-provider";
import { useWorkspace } from "../providers/workspace-provider";
import { Brand } from "../shared/brand";
import { Button } from "../ui/button";
import { PageSkeleton, type PageSkeletonVariant } from "../ui/skeleton";
import { displayName, initials, solvedInCourse } from "@/lib/format";

const links = [
  { href: "/dashboard", label: "Overview", icon: LayoutDashboard },
  { href: "/dashboard/courses", label: "My courses", icon: BookOpen },
  {
    href: "/dashboard/course-requests",
    label: "Course requests",
    icon: BookPlus,
  },
  { href: "/dashboard/profile", label: "My profile", icon: UserRound },
];

function WorkspaceShell({ children }: { children: React.ReactNode }) {
  const pathname = usePathname();
  const { signOut } = useSession();
  const { profile, courses, loading, refreshing, refresh } = useWorkspace();
  const [mobileOpen, setMobileOpen] = useState(false);
  const solved = courses.reduce(
    (total, course) => total + solvedInCourse(course),
    0,
  );
  const fullName =
    `${displayName(profile?.FIRST_NAME)} ${profile?.LAST_NAME ? displayName(profile.LAST_NAME) : ""}`.trim();
  const section = pathname.includes("/profile")
    ? "My profile"
    : pathname === "/dashboard/course-requests"
      ? "Course requests"
      : pathname.startsWith("/dashboard/courses")
        ? "My courses"
        : "Overview";

  useEffect(() => {
    if (!mobileOpen) return;
    const old = document.body.style.overflow;
    document.body.style.overflow = "hidden";
    const close = (event: KeyboardEvent) => {
      if (event.key === "Escape") setMobileOpen(false);
    };
    window.addEventListener("keydown", close);
    return () => {
      document.body.style.overflow = old;
      window.removeEventListener("keydown", close);
    };
  }, [mobileOpen]);

  return (
    <div className="workspace">
      <a href="#workspace-content" className="skip-link">
        Skip to content
      </a>
      {mobileOpen && (
        <button
          className="sidebar-overlay"
          onClick={() => setMobileOpen(false)}
          aria-label="Close navigation"
        />
      )}
      <aside
        className={`sidebar ${mobileOpen ? "sidebar-open" : ""}`}
        id="workspace-navigation"
        aria-label="Workspace navigation"
      >
        <div className="sidebar-brand">
          <Brand compact />
          <button
            className="mobile-nav-close icon-button"
            onClick={() => setMobileOpen(false)}
            aria-label="Close navigation"
          >
            <PanelLeftClose size={20} />
          </button>
        </div>
        <div className="sidebar-group">
          <span className="sidebar-label">YOUR WORKSPACE</span>
          <nav>
            {links.map(({ href, label, icon: Icon }) => {
              const active =
                href === "/dashboard"
                  ? pathname === href
                  : href === "/dashboard/courses"
                    ? pathname.startsWith("/dashboard/courses")
                    : pathname === href;
              return (
                <Link
                  key={href}
                  href={href}
                  onClick={() => setMobileOpen(false)}
                  className={`sidebar-link ${active ? "is-active" : ""}`}
                  aria-current={active ? "page" : undefined}
                >
                  <Icon size={18} />
                  <span>{label}</span>
                  {active && <span className="sidebar-active-dot" />}
                </Link>
              );
            })}
          </nav>
        </div>
        <div className="sidebar-momentum">
          <h3>Keep your momentum.</h3>
          <p>
            {loading
              ? "Your next step is waiting."
              : `${solved} ${solved === 1 ? "problem" : "problems"} behind you. A new possibility ahead.`}
          </p>
          <Link href="/dashboard/courses" onClick={() => setMobileOpen(false)}>
            Back to your courses <ChevronRight size={14} />
          </Link>
        </div>
        <div className="sidebar-bottom">
          <div className="sidebar-user">
            <span className="avatar">
              {initials(profile?.FIRST_NAME, profile?.LAST_NAME)}
            </span>
            <div>
              <strong>{fullName}</strong>
              <span>{profile?.REGISTER_NUMBER || "Your E-Lab account"}</span>
            </div>
            <button
              className="icon-button"
              onClick={signOut}
              aria-label="Sign out"
              title="Sign out"
            >
              <LogOut size={17} />
            </button>
          </div>
        </div>
      </aside>
      <div className="workspace-main">
        <header className="workspace-header">
          <div className="breadcrumbs">
            <button
              className="mobile-menu icon-button"
              onClick={() => setMobileOpen(true)}
              aria-expanded={mobileOpen}
              aria-controls="workspace-navigation"
              aria-label="Open navigation"
            >
              <Menu size={22} />
            </button>
            <span>Workspace</span>
            <ChevronRight size={14} />
            <strong>
              {section === "Course requests" ? (
                <>
                  <span className="course-request-header-full">Course requests</span>
                  <span className="course-request-header-short">Course req</span>
                </>
              ) : section}
            </strong>
          </div>
          <div className="workspace-header-right">
            <Button
              variant="secondary"
              className="header-refresh"
              loading={refreshing}
              onClick={() => void refresh()}
              aria-label="Refresh workspace"
              title="Refresh workspace"
            >
              {!refreshing && <RefreshCw size={15} />}
              <span>Refresh</span>
            </Button>
            <Link
              href="/dashboard/profile"
              className="avatar avatar-small"
              aria-label="Open your profile"
            >
              {initials(profile?.FIRST_NAME, profile?.LAST_NAME)}
            </Link>
          </div>
        </header>
        <main className="workspace-content" id="workspace-content">
          {children}
        </main>
      </div>
    </div>
  );
}

export function ProtectedWorkspace({
  children,
}: {
  children: React.ReactNode;
}) {
  const { token, ready } = useSession();
  const router = useRouter();
  const pathname = usePathname();
  const variant: PageSkeletonVariant = pathname.includes("/profile")
    ? "profile"
    : pathname.startsWith("/dashboard/courses/")
      ? "course"
      : pathname === "/dashboard/courses" ||
          pathname === "/dashboard/course-requests"
        ? "courses"
        : "overview";
  useEffect(() => {
    if (ready && !token) router.replace("/");
  }, [ready, token, router]);
  if (!ready || !token)
    return (
      <WorkspaceShell>
        <PageSkeleton variant={variant} />
      </WorkspaceShell>
    );
  return <WorkspaceShell>{children}</WorkspaceShell>;
}
