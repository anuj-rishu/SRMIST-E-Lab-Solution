Run from `server` after `npm run build`:

```sh
ELAB_TOKEN_FILE=/path/to/private-token-file node scripts/solve-range.mjs 86 300
```

The token file must contain the full Bearer authorization value. Keep it outside the repository. `ELAB_TOKEN` is also supported.

The script submits questions sequentially, skipping completed questions and previous successful entries in its report. It uses the normal matcher, mandatory checks, and C/C++ compiler detection. It does not edit database solutions.

Reports are written after every question to `info/course-26-86-300/summary.json`. Questions with errors or scores below 100% have separate `question-N.json` files containing question details and evaluation results. These reports omit login tokens and student profiles.

Rerun the command to resume. It retries previous failures while skipping successes. Ctrl+C stops after the current request and saves progress. An expired or rejected token stops the run.

For a separate account, choose a separate report folder:

```sh
ELAB_TOKEN_FILE=/path/to/private-token-file ELAB_REPORT_DIR=info2 ELAB_RECHECK_COMPLETE=1 node scripts/solve-range.mjs 1 300
```

`ELAB_RECHECK_COMPLETE=1` evaluates questions even if E-Lab marks them complete, so partial scores are recorded. A saved report includes an account hash to prevent resuming it with a different account. Neither the token nor the student profile is saved in reports.

To retry only transient request timeouts from an existing report, add `ELAB_RETRY_TIMEOUTS_ONLY=1`. A successful retry removes that question's previous failure file; its successful evaluation remains in `summary.json`.
