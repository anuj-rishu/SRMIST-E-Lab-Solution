import type { Metadata } from "next";
import { CourseRequestsPage } from "@/components/workspace/course-requests-page";
import { ProtectedWorkspace } from "@/components/workspace/workspace-shell";

export const metadata: Metadata = { title: "Course requests" };

export default function CourseRequests() {
  return (
    <ProtectedWorkspace>
      <CourseRequestsPage />
    </ProtectedWorkspace>
  );
}
