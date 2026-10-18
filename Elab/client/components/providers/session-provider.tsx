"use client";

import {
  createContext,
  useCallback,
  useContext,
  useEffect,
  useState,
} from "react";
import { apiRequest } from "@/lib/api";

interface SessionContextValue {
  token: string | null;
  ready: boolean;
  signIn: (userId: string, password: string) => Promise<void>;
  signOut: () => void;
}

const SessionContext = createContext<SessionContextValue | null>(null);
const STORAGE_KEY = "elab.session";

export function SessionProvider({ children }: { children: React.ReactNode }) {
  const [token, setToken] = useState<string | null>(null);
  const [ready, setReady] = useState(false);

  const signOut = useCallback(() => {
    sessionStorage.removeItem(STORAGE_KEY);
    setToken(null);
  }, []);

  useEffect(() => {
    setToken(sessionStorage.getItem(STORAGE_KEY));
    setReady(true);
    window.addEventListener("elab:session-expired", signOut);
    return () => window.removeEventListener("elab:session-expired", signOut);
  }, [signOut]);

  async function signIn(userId: string, password: string) {
    const data = await apiRequest<{ Status: number; token?: string }>("login", {
      body: { USER_ID: userId.trim(), PASSWORD: password },
    });
    if (!data.token || typeof data.token !== "string")
      throw new Error("Login did not return a session. Please try again.");
    sessionStorage.setItem(STORAGE_KEY, data.token);
    setToken(data.token);
  }

  return (
    <SessionContext.Provider value={{ token, ready, signIn, signOut }}>
      {children}
    </SessionContext.Provider>
  );
}

export function useSession() {
  const context = useContext(SessionContext);
  if (!context) throw new Error("SessionProvider is required.");
  return context;
}
