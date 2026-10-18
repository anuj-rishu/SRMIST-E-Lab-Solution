"use client";

import {
  createContext,
  useCallback,
  useContext,
  useEffect,
  useRef,
  useState,
} from "react";
import { apiRequest, errorMessage } from "@/lib/api";
import type { Course, Profile, Rank } from "@/lib/types";
import { useSession } from "./session-provider";

interface WorkspaceContextValue {
  profile: Profile | null;
  courses: Course[];
  rank: Rank | null;
  loading: boolean;
  refreshing: boolean;
  error: string | null;
  refresh: () => Promise<void>;
}

const WorkspaceContext = createContext<WorkspaceContextValue | null>(null);

export function WorkspaceProvider({ children }: { children: React.ReactNode }) {
  const { token } = useSession();
  const [profile, setProfile] = useState<Profile | null>(null);
  const [courses, setCourses] = useState<Course[]>([]);
  const [rank, setRank] = useState<Rank | null>(null);
  const [loading, setLoading] = useState(true);
  const [refreshing, setRefreshing] = useState(false);
  const [error, setError] = useState<string | null>(null);
  const requestId = useRef(0);

  const refresh = useCallback(async () => {
    if (!token) return;
    const id = ++requestId.current;
    setRefreshing(true);
    const results = await Promise.allSettled([
      apiRequest<{ profile: Profile }>("profile", { token }),
      apiRequest<{ courses: Course[] }>("registeredcourses", { token }),
      apiRequest<{ data: Rank }>("rank", { token }),
    ]);
    if (id !== requestId.current) return;
    const [profileResult, courseResult, rankResult] = results;
    const issues: string[] = [];
    if (profileResult.status === "fulfilled")
      setProfile(profileResult.value.profile);
    else issues.push(errorMessage(profileResult.reason));
    if (
      courseResult.status === "fulfilled" &&
      Array.isArray(courseResult.value.courses)
    ) {
      setCourses(courseResult.value.courses);
    } else
      issues.push(
        courseResult.status === "rejected"
          ? errorMessage(courseResult.reason)
          : "Course data is unavailable.",
      );
    setRank(rankResult.status === "fulfilled" ? rankResult.value.data : null);
    setError(issues[0] || null);
    setLoading(false);
    setRefreshing(false);
  }, [token]);

  useEffect(() => {
    void refresh();
    return () => {
      requestId.current++;
    };
  }, [refresh]);

  return (
    <WorkspaceContext.Provider
      value={{ profile, courses, rank, loading, refreshing, error, refresh }}
    >
      {children}
    </WorkspaceContext.Provider>
  );
}

export function useWorkspace() {
  const context = useContext(WorkspaceContext);
  if (!context) throw new Error("WorkspaceProvider is required.");
  return context;
}
