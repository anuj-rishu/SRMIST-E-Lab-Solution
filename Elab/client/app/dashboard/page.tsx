import type { Metadata } from "next";
import { ProtectedWorkspace } from "@/components/workspace/workspace-shell";
import { OverviewPage } from "@/components/workspace/overview-page";

export const metadata: Metadata = { title: "Overview" };

export default function Dashboard() {
  return (
    <ProtectedWorkspace>
      <OverviewPage />
    </ProtectedWorkspace>
  );
}
