"use client";

import { ProtectedWorkspace } from "@/components/workspace/workspace-shell";
import { useParams } from "next/navigation";
import { CourseWorkspace } from "@/components/workspace/course-workspace";

export default function CoursePage() {
  const params = useParams<{ courseId: string }>();
  return (
    <ProtectedWorkspace>
      <CourseWorkspace
        key={params.courseId}
        courseId={Number(params.courseId)}
      />
    </ProtectedWorkspace>
  );
}
