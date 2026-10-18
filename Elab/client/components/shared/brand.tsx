import Link from "next/link";
import { Code2 } from "lucide-react";

export function Brand({ compact = false }: { compact?: boolean }) {
  return (
    <Link href="/" className="brand" aria-label="E-Lab home">
      <span className="brand-mark">
        <Code2 size={22} strokeWidth={2.5} />
      </span>
      <span>
        e<span className="brand-slash">/</span>lab
        {!compact && (
          <span className="brand-caption">YOUR CODING WORKSPACE</span>
        )}
      </span>
    </Link>
  );
}
