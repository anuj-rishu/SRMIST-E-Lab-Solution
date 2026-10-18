"use client";

import { useState } from "react";
import { useRouter } from "next/navigation";
import {
  ArrowRight,
  Eye,
  EyeOff,
  KeyRound,
  LockKeyhole,
  UserRound,
} from "lucide-react";
import { useSession } from "../providers/session-provider";
import { Button } from "../ui/button";
import { Feedback } from "../ui/feedback";
import { errorMessage } from "@/lib/api";

export function LoginForm() {
  const router = useRouter();
  const { signIn } = useSession();
  const [visible, setVisible] = useState(false);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);

  async function submit(event: React.FormEvent<HTMLFormElement>) {
    event.preventDefault();
    setError(null);
    setLoading(true);
    const values = new FormData(event.currentTarget);
    try {
      await signIn(
        String(values.get("userId") || ""),
        String(values.get("password") || ""),
      );
      router.push("/dashboard");
    } catch (issue) {
      setError(errorMessage(issue));
    } finally {
      setLoading(false);
    }
  }

  return (
    <section className="login-card" id="login" aria-labelledby="login-title">
      <div className="login-card-top">
        <span className="eyebrow">YOUR NEXT CHAPTER</span>
        <KeyRound size={19} />
      </div>
      <div className="login-heading">
        <h2 id="login-title">Welcome back.</h2>
        <p>Good to see you. Let’s get you signed in.</p>
      </div>
      <form onSubmit={submit}>
        <div className="field">
          <label htmlFor="user-id">Username</label>
          <div className="input-wrap">
            <UserRound size={18} />
            <input
              id="user-id"
              name="userId"
              autoComplete="username"
              inputMode="numeric"
              placeholder="Enter your user ID"
              required
              disabled={loading}
            />
          </div>
        </div>
        <div className="field">
          <label htmlFor="password">Password</label>
          <div className="input-wrap">
            <LockKeyhole size={18} />
            <input
              id="password"
              name="password"
              type={visible ? "text" : "password"}
              autoComplete="current-password"
              placeholder="Enter your password"
              required
              disabled={loading}
            />
            <button
              className="password-toggle"
              type="button"
              onClick={() => setVisible(!visible)}
              aria-label={visible ? "Hide password" : "Show password"}
            >
              {visible ? <EyeOff size={18} /> : <Eye size={18} />}
            </button>
          </div>
        </div>
        {error && <Feedback>{error}</Feedback>}
        <Button type="submit" className="login-submit" loading={loading}>
          {loading ? "Signing you in…" : "Enter workspace"}
          {!loading && <ArrowRight size={18} />}
        </Button>
      </form>
      <div className="login-account-note">
        <span className="blue-dot" />
        Use your existing SRMIST E-Lab account
      </div>
      <div className="login-privacy">
        <LockKeyhole size={13} />
        <span>Your credentials are never saved.</span>
      </div>
    </section>
  );
}
