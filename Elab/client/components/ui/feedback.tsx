import { AlertCircle, CheckCircle2 } from "lucide-react";
import { Button } from "./button";

export function Feedback({
  children,
  success = false,
}: {
  children: React.ReactNode;
  success?: boolean;
}) {
  const Icon = success ? CheckCircle2 : AlertCircle;
  return (
    <div
      className={`feedback ${success ? "feedback-success" : "feedback-error"}`}
      role={success ? "status" : "alert"}
    >
      <Icon size={18} aria-hidden="true" />
      <div>{children}</div>
    </div>
  );
}

export function ErrorState({
  message,
  onRetry,
}: {
  message: string;
  onRetry: () => void;
}) {
  return (
    <div className="empty-state">
      <AlertCircle size={28} />
      <h2>Let’s try that again.</h2>
      <p>{message}</p>
      <Button variant="secondary" onClick={onRetry}>
        Try again
      </Button>
    </div>
  );
}
