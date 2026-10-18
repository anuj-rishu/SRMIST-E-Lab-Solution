import type { NextConfig } from "next";

const nextConfig: NextConfig = {
  devIndicators: false,
  async rewrites() {
    const serverUrl = process.env.API_SERVER_URL?.trim();
    if (!serverUrl)
      throw new Error(
        "Set API_SERVER_URL to the server's full URL in your deployment environment (for example, https://your-service.koyeb.app).",
      );
    let upstream: URL;
    try {
      upstream = new URL(serverUrl);
    } catch {
      throw new Error("API_SERVER_URL must be a full URL starting with http:// or https://.");
    }
    if (
      !["http:", "https:"].includes(upstream.protocol) ||
      upstream.username ||
      upstream.password ||
      upstream.pathname !== "/" ||
      upstream.search ||
      upstream.hash
    ) {
      throw new Error(
        "API_SERVER_URL must be an HTTP(S) server origin without credentials, a path, a query, or a fragment.",
      );
    }
    return [
      {
        source: "/api/v1/:path*",
        destination: `${upstream.origin}/api/v1/:path*`,
      },
    ];
  },
  cacheComponents: true,
  partialPrefetching: true,
  turbopack: {
    rules: {
      "*.css": {
        loaders: ["@tailwindcss/turbopack"],
        as: "*.css",
      },
    },
  },
};

export default nextConfig;
