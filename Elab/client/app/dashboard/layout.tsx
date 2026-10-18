import { Suspense } from "react";
import { WorkspaceProvider } from "@/components/providers/workspace-provider";
import { WorkspaceSkeleton } from "@/components/ui/skeleton";

export default function DashboardLayout({
  children,
}: {
  children: React.ReactNode;
}) {
  return (
    <Suspense fallback={<WorkspaceSkeleton />}>
      <WorkspaceProvider>{children}</WorkspaceProvider>
    </Suspense>
  );
}
