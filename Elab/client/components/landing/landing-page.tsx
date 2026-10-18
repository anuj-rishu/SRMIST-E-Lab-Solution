"use client";

import { useEffect } from "react";
import { useRouter } from "next/navigation";
import { Braces, Layers3 } from "lucide-react";
import { useSession } from "../providers/session-provider";
import { SiteHeader } from "../shared/site-header";
import { SiteFooter } from "../shared/site-footer";
import { LoginForm } from "./login-form";

export function LandingPage() {
  const { token, ready } = useSession();
  const router = useRouter();
  useEffect(() => {
    if (ready && token) router.replace("/dashboard");
  }, [ready, token, router]);

  return (
    <div className="landing" id="top">
      <SiteHeader />
      <main>
        <section className="container hero">
          <div className="hero-copy">
            <h1>
              Your next
              <br />
              breakthrough
              <br />
              starts <span>here.</span>
            </h1>
            <p className="hero-description">
              One focused workspace for your E-Lab journey
              <span className="hero-description-extra">
                {" — "}<br className="desktop-break" />your courses, your progress,
                your next step, <br className="desktop-break" />all coming together.
              </span>
            </p>
            <div className="hero-courses">
              <span>
                <Braces size={17} />C Programming
              </span>
              <span className="course-separator" />
              <span>
                <Layers3 size={17} />
                Data Structures
              </span>
            </div>
          </div>
          <div className="hero-form">
            <div className="form-orbit" aria-hidden="true" />
            <LoginForm />
          </div>
        </section>
      </main>
      <SiteFooter />
    </div>
  );
}
