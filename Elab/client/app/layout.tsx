import type { Metadata } from "next";
import { Geist, Geist_Mono } from "next/font/google";
import { SessionProvider } from "@/components/providers/session-provider";
import "./globals.css";
import "../styles/landing.css";
import "../styles/ui.css";
import "../styles/workspace.css";
import "../styles/questions.css";
import "../styles/responsive.css";

const geistSans = Geist({ variable: "--font-geist-sans", subsets: ["latin"] });
const geistMono = Geist_Mono({
  variable: "--font-geist-mono",
  subsets: ["latin"],
});

export const metadata: Metadata = {
  title: { default: "E-Lab — Your coding workspace", template: "%s · E-Lab" },
  description:
    "A focused workspace for your E-Lab courses. Track your progress, explore questions, and move forward one problem at a time.",
};

export default function RootLayout({
  children,
}: {
  children: React.ReactNode;
}) {
  return (
    <html lang="en" className={`${geistSans.variable} ${geistMono.variable}`}>
      <body>
        <SessionProvider>{children}</SessionProvider>
      </body>
    </html>
  );
}
