Build the server, then collect account 1 before account 2 using private token files:

```sh
npm run build
ELAB_ACCOUNT1_TOKEN_FILE=/private/path/account1-token \
ELAB_ACCOUNT2_TOKEN_FILE=/private/path/account2-token \
node scripts/collect-question-catalog.mjs
```

Collection only reads registered-course and question-info APIs. It never saves logs or submits code. Three requests run concurrently within each account; account 2 starts after account 1 finishes. Snapshots contain stored code and must remain outside the repository. They default to the system temporary directory under `elab-question-catalog`; `ELAB_CATALOG_CACHE_DIR` overrides that directory. Collection resumes only when the cached account hash matches the supplied token's account.

Use the snapshot paths to plan the index, then write it:

```sh
ELAB_CATALOG_ACCOUNT1_FILE=/private/path/elab-qid-account1.json \
ELAB_CATALOG_ACCOUNT2_FILE=/private/path/elab-qid-account2.json \
node scripts/index-question-catalog.mjs

ELAB_CATALOG_ACCOUNT1_FILE=/private/path/elab-qid-account1.json \
ELAB_CATALOG_ACCOUNT2_FILE=/private/path/elab-qid-account2.json \
node scripts/index-question-catalog.mjs --write
```

`question_catalog` has a unique `(courseId, Q_ID)` index. Account 1 entries take priority; repeated IDs from account 2 are skipped. A conflicting description/mandatory/complexity/example fingerprint is reported without overwriting the original entry. Existing entries are skipped when rerunning the indexer.

Each question stores its full description, required constructs, limits, examples and a 384-dimensional question-content embedding. ID strings are not embedded. These embeddings are separate from the existing solution introduction embeddings. Exact ID lookup uses the ordinary MongoDB index and does not need a vector search index.

A solution link is recorded only from existing verified metadata, a reviewed link, or token-identical code already stored for that question in one of the accounts. Whitespace and comments are ignored for code identity; literal contents and compound operators are preserved. Stored-source identity establishes which solution belongs to the question; it does not certify a fresh 100% evaluation. Existing solution records and their embeddings are never rewritten.

Known IDs resolve through one indexed catalog query joined to their source. The full requirement fingerprint, course and source checksum are checked. A known ID without a confirmed link returns an explicit error; it cannot silently select similar-looking code. Unknown IDs retain the legacy fallback.

Verify both account snapshots without submitting anything:

```sh
ELAB_CATALOG_ACCOUNT1_FILE=/private/path/elab-qid-account1.json \
ELAB_CATALOG_ACCOUNT2_FILE=/private/path/elab-qid-account2.json \
node scripts/verify-question-catalog.mjs
```

Reports in `reports/question-catalog` contain counts, skipped duplicates, unresolved links, a Q_ID-to-sequence map, and lookup verification results. Tokens and student profiles are omitted. Deploy the updated server before the hosted API uses the catalog.
