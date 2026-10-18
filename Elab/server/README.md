# E-Lab API deployment

## Course requests

The client page at `/dashboard/course-requests` lists the academic and certification
catalog and lets the signed-in student send an enrollment request.

- `POST /api/v1/courserequest/allcourses`: returns `academicCourses` and
  `certificationCourses` from E-Lab. Send an empty JSON object.
- `POST /api/v1/courserequest/send`: send `{ "course": <catalog course object> }`.
  The API derives the upstream request type, such as `DS_REGULAR_SET1`, and rejects
  disabled or malformed courses.

Both endpoints require the current login token in the `Authorization` header.
The student profile comes from that token; a profile supplied in the request body
does not override the signed-in student. Successful submission means the request
was sent, and does not imply that enrollment has already been approved.

## Deploy from GitHub to Koyeb

1. Push this server directory, including `Dockerfile`, `package.json`, and
   `package-lock.json`, to your GitHub repository.
2. In Koyeb, create a **Web Service**, select **GitHub**, and choose your repository
   and deployment branch. Keep automatic deployment enabled for updates on push.
3. Select the **Dockerfile** builder. Set **Work directory** to the server path
   relative to the GitHub repository root (`server` if this project is the repository
   root; `Elab/server` if the repository contains the `Elab` folder). Set the
   **Dockerfile** location to `Dockerfile`. Leave the run command unset so the
   image starts Node directly.
4. Add the four variables from `.env.example` in the service environment, replacing
   the MongoDB placeholder with your actual connection string. Store `MONGODB_URI`
   as a Koyeb Secret. Set `CLIENT_ORIGIN` to
   your frontend's full origin, including `https://`, without a path. To allow local
   development too, use `http://localhost:3000,https://e-lab-solver.vercel.app`.
   Production ignores local `.env`
   files and fails immediately if required configuration is missing or invalid.
5. Expose port **8000**, protocol **HTTP**, with public route **/**. Keep `PORT=8000`.
   Configure an HTTP health check at **/api/v1/health** on port **8000**.
6. Deploy. Verify `https://YOUR-SERVICE.koyeb.app/api/v1/health` returns
   `{"status":"ok"}`.

The image uses Node 22, compiles TypeScript during the build, includes only production
dependencies at runtime, and runs as a non-root user. SIGTERM stops accepting new
connections, drains requests, and disconnects MongoDB, with a 10-second shutdown limit.
The health check confirms the HTTP service is running; it does not call E-Lab,
connect to MongoDB, or load the embedding model.

## Connect the frontend

Set `API_SERVER_URL=https://YOUR-SERVICE.koyeb.app` in the **frontend** deployment
environment, then rebuild/redeploy the Next.js client. Its existing rewrites forward
`/api/v1/*` to the API. This URL must be available when the frontend builds. Keep
the frontend's public origin in the API's comma-separated `CLIENT_ORIGIN` allowlist.
For a localhost client that uses the deployed Koyeb API, update `CLIENT_ORIGIN` in
the **Koyeb service environment** as well; changing local `.env` files does not
change a running deployment.

## MongoDB and model cache

### Submission performance on small instances

Uncached solution lookup uses embedding inference and one vector query with the
existing confidence thresholds. There is no preliminary fingerprint query.

Successful matches are cached for 60 seconds, with limits of 128 entries and 2 MiB
of serialized solution data. Requests for the same full description and course
share an in-progress lookup. No tokens, student profiles, or evaluations are cached;
each submission still fetches the current question, checks mandatory code, saves
logs, and evaluates normally. Database edits may take up to a minute to appear in
cached matches.

The embedding runtime is imported during startup, while model weights load on the
first lookup. Inference uses the original two-thread setting without the added serial
queue. Koyeb logs include `Question submission timing`, with milliseconds for question
fetching, solution lookup, source preparation, saving logs, evaluation, and the total
request. Use those measured stages to investigate latency on the deployed instance.

Koyeb free-instance sleep and upstream evaluation/network latency still apply.
These changes do not send keep-alive traffic or bypass the platform's idle policy.

Use a MongoDB deployment reachable from Koyeb and configure its network access and
database credentials. Solution search needs the existing solutions, embeddings, and
vector index identified by `EMBEDDING_CONFIG.indexName` in `src/config/settings.ts`;
the API does not create these on
startup. Preserve the embedding model, revision, dimensions, and text settings used
when generating your existing embeddings.

The model downloads on the first solution search, so outbound access to Hugging Face
is required. The image provides a writable `/app/.cache/embeddings` directory. Its
contents can be lost when the instance is replaced, causing another download. If you
mount persistent storage instead, make its cache directory writable by UID 1000 and
update `EMBEDDING_CONFIG.cacheDir` in `src/config/settings.ts`. Size the instance for the model's measured memory usage;
an HTTP health check alone does not exercise model inference.

## Local validation

```sh
cd server
npm ci
npm run typecheck
npm run build
```

For development use `npm run dev` with `.env.local`. For a production launch,
provide the environment, run `npm run build`, then `npm start`; startup does not
compile TypeScript.

Only `NODE_ENV`, `PORT`, `CLIENT_ORIGIN`, and `MONGODB_URI` are read from the
environment. E-Lab endpoints, upstream API keys, and embedding settings are defined
in `src/config/settings.ts`. That file contains the upstream credentials.

To validate the Linux image with Docker running, build from the server directory:

```sh
docker build -t elab-api .
docker run --rm --env-file /path/to/private-production.env -p 8000:8000 elab-api
```

Official references: [GitHub deployment](https://www.koyeb.com/docs/build-and-deploy/deploy-with-git),
[monorepo work directories](https://www.koyeb.com/docs/build-and-deploy/monorepo),
and [health checks](https://www.koyeb.com/docs/run-and-scale/health-checks).
