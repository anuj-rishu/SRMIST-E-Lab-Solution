import type { Metadata } from "next";
import { ProtectedWorkspace } from "@/components/workspace/workspace-shell";
import { ProfilePage } from "@/components/workspace/profile-page";

export const metadata: Metadata = { title: "My profile" };

export default function Profile() {
  return (
    <ProtectedWorkspace>
      <ProfilePage />
    </ProtectedWorkspace>
  );
}
