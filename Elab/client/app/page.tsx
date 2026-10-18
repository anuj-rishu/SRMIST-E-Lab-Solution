import type { Metadata } from "next";
import { LandingPage } from "@/components/landing/landing-page";

export const metadata: Metadata = { title: "Sign in · E-Lab" };

export default function Home() {
  return <LandingPage />;
}
