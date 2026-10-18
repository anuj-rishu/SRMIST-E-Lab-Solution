import { ArrowUpRight } from "lucide-react";
import { Brand } from "./brand";

export function SiteHeader() {
  return (
    <header className="site-header">
      <div className="container header-inner">
        <Brand />
        <nav aria-label="Main navigation">
          <a className="header-signin" href="#login">
            Sign in <ArrowUpRight size={15} />
          </a>
        </nav>
      </div>
    </header>
  );
}
