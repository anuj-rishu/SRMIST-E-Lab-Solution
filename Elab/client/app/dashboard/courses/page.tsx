import type { Metadata } from "next";
import { CoursesPage } from "@/components/workspace/courses-page";
import { ProtectedWorkspace } from "@/components/workspace/workspace-shell";

export const metadata: Metadata = { title: "My courses" };

export default function Courses() {
  return (
    <ProtectedWorkspace>
      <CoursesPage />
    </ProtectedWorkspace>
  );
}
