# PictoPy Backend — Issue Report

> Severity-sorted audit of the PictoPy backend, sync microservice, and album-share subsystem.
> Repository: `C:\Users\homro\Dev\GSoC\PictoPy` · version **1.3.0-alpha** · audited 2026-10-10.
> Method: four parallel read-only audits (database/routes, AI/utils, security/sync, dead-code/tests); every finding below was verified by reading the actual source and carries a `file:line` reference. Speculative and style-only items were dropped.
> Paths are relative to the repository root.

---

## Table of contents

- [Summary](#summary)
- [Severity legend](#severity-legend)
- [Critical](#critical)
- [High](#high)
- [Medium](#medium)
- [Low — cleanup](#low--cleanup)
- [Test gaps](#test-gaps)
- [Recommended fix order](#recommended-fix-order)
- [Verified non-issues](#verified-non-issues)

---

## Summary

| Severity | Count | Themes |
| --- | --- | --- |
| **Critical** | 4 | data destruction on unreadable folders; open localhost API with no auth; unauthenticated kill switch; one bad file halts all AI tagging |
| **High** | 12 | stale AI results after edits; SQLite locking; download reaper; cross-process state blindness; destructive sync-folder; watcher orphans; CI trust broken |
| **Medium** | 15 | list-response 500s, memory blowups, non-atomic claims, symlink reads, swallowed errors, error-code lies |
| **Low** | 10+ | dead files, unused/unpinned deps, stale scripts, minor robustness |
| **Test gaps** | 6 areas | share/shutdown/sync-folder/images routes untested; no test imports `main`; sync-microservice has no tests at all |

A note on process: this project's rules require maintainer review and a labelled issue before any PR. Items marked **[design — confirm]** below are real defects but involve a deliberate trade-off; raise them on an issue first rather than PR-ing a unilateral change.

---

## Severity legend

- **Critical** — data loss, security takeover, or a feature permanently bricked for realistic inputs.
- **High** — significant correctness/robustness failure under common conditions, or CI giving false confidence.
- **Medium** — real defect with narrower trigger or degraded impact.
- **Low** — cleanup, dead code, minor robustness; low risk if left.

---

## Critical

### C1. An unreadable folder deletes every image row and thumbnail under it

**Severity:** Critical · **Where:** `backend/app/utils/images.py:73-96`, `:401-432`, `:464-480`

**Problem:** During folder indexing, `folder_id` is appended to `all_folder_ids` *before* the filesystem walk. The walk helpers never raise on an unreadable directory — the recursive branch uses `os.walk` (missing dir yields nothing) and the non-recursive branch catches `OSError` and returns `[]`. An unmounted drive, revoked permission, or transient I/O error therefore looks identical to "this folder contains zero photos", and `image_util_remove_obsolete_images` then deletes every DB row whose `path` no longer exists — after first deleting each thumbnail from disk. Because `images.folder_id REFERENCES folders(...) ON DELETE CASCADE`, faces, class tags, embeddings, album links and memory membership all go with it. Re-mounting the drive re-indexes the photos, but every AI result for that folder is permanently gone.

**Evidence:**

```python
all_folder_ids.append(folder_id)          # appended BEFORE the walk
image_files = image_util_get_images_from_folder(folder_path, recursive)
if not image_files:
    continue                              # unreadable dir lands here
...
if all_folder_ids:
    image_util_remove_obsolete_images(all_folder_ids)
```

**Solution:** Treat a folder as authoritative for deletion only when the walk actually succeeded. Have the walk helpers distinguish "empty" from "failed" (return `None` or raise on `OSError`), and exclude failed folders from `all_folder_ids`. Additionally, never run obsolete-deletion against a root that itself fails `os.path.isdir` — surface it as `INDEXING_INTERRUPTED` instead, matching the vocabulary already used elsewhere in `routes/folders.py`.

---

### C2. Wildcard CORS and no authentication let any website control the app

**Severity:** Critical **[design — confirm]** · **Where:** `backend/main.py:172-177`; no auth dependency exists anywhere (`app/routes/dependencies.py:7-9` is the only shared dependency)

**Problem:** The backend adds `CORSMiddleware` with `allow_origins=["*"]`, `allow_credentials=True`, `allow_methods=["*"]`, `allow_headers=["*"]`, and uses no cookies or tokens at all — the frontend is a plain `fetch` to `http://localhost:52123`. With starlette's semantics, `allow_origins=["*"]` permits every origin's preflight, and simple responses carry `Access-Control-Allow-Origin: *`, which browsers hand to any origin's JavaScript. Chrome's Private Network Access may block public-site→localhost in some builds, but Firefox/Safari do not enforce it, and a LAN-hosted page is unaffected everywhere.

**Impact:** A user visiting `evil.com` exposes: `GET /images/` (every photo's absolute path and EXIF including GPS), `GET /face-clusters` (people names and faces), `GET /share/` (**live share tokens plus LAN URLs**, which the attacker can then use from any LAN device to pull photos from the `0.0.0.0`-bound share server), `POST /share/albums/{id}` (instantly expose any album under an attacker-chosen password), `POST /folders/delete-folders`, `DELETE /models/{key}`, and `POST /folders/add-folder` pointing at sensitive directories for enumeration.

**Solution:** Restrict `allow_origins` to the Tauri WebView origins (`tauri://localhost`, `http://tauri.localhost`, `http://localhost:1420` for dev) and drop `allow_credentials` (nothing uses cookies). Better still: mint a per-process random token when the Rust shell launches the sidecar, pass it via environment/args, require it on every request, and have the frontend send it — a single change that also closes C3, and High issues H4/H5 and Medium items below. Raise on an issue first since it touches the frontend↔backend contract.

---

### C3. Unauthenticated `POST /shutdown` permanently kills both services

**Severity:** Critical **[design — confirm]** · **Where:** `backend/app/routes/shutdown.py:31-36,39-66`; `sync-microservice/app/routes/shutdown.py:32-37,40-75`

**Problem:** Neither service authenticates its shutdown route, and with C2 (and the sync service's identical CORS) any webpage can call them. On Windows the backend does `os._exit(0)`, which bypasses the entire lifespan shutdown in `main.py:114-123` — the share server stop and both `ProcessPoolExecutor.shutdown()` calls never run. Neither service restarts itself; the Tauri shell only spawns them at app start.

**Impact:** Any sandboxed local app, browser tab, or other user on a shared machine can loop `curl -X POST http://localhost:52123/shutdown` and keep the desktop app permanently dead until manual restart, with in-flight SQLite work cut off mid-transaction.

**Solution:** Require the same shared secret as C2 on `/shutdown` in both services. Replace `os._exit(0)` with the graceful uvicorn `should_exit` path on all platforms (the SIGTERM unreliability comment applies to subprocess trees, not to in-process shutdown). The Rust shell already knows how to stop the services; keep `kill_process_tree` as the last-resort fallback.

---

### C4. One GIF or non-ASCII filename permanently stalls the entire AI tagging pass

**Severity:** Critical · **Where:** `backend/app/utils/images.py:229` (crash site), `backend/app/models/ObjectClassifier.py:17-21` (source of `None`)

**Problem:** `ObjectClassifier.get_classes` returns `None` when `cv2.imread` fails — which happens for **every GIF** (GIF is in `SUPPORTED_IMAGE_EXTENSIONS` but OpenCV has no GIF decoder) and for non-ASCII filenames on Windows (`imread` uses ANSI `fopen`). The tagging loop then evaluates `len(classes)` on `None` and raises `TypeError`. The per-image loop at `images.py:221-263` has no isolation, so the exception aborts the whole sweep, is caught at `images.py:120-122`, logged, and the sweep returns `False`. `db_get_untagged_images()` returns the same stable ordering every run, so every subsequent sweep dies at the same file: images before it get tagged, images after it are **never tagged, silently, forever**. The identical pattern is already handled correctly elsewhere — `videos.py:1018` uses `get_classes(frame["frame_path"]) or []`, and `images.py:240` guards with `if result and result["embeddings"]`.

**Evidence:**

```python
classes = object_classifier.get_classes(image_path)
if len(classes) > 0:          # TypeError when get_classes returns None
```

**Solution:** Make `get_classes` return `[]` (not `None`) on read failure and defensively write `classes = object_classifier.get_classes(image_path) or []`. Add a per-image `try/except` mirroring `videos.py:1060-1063` so one bad file can never abort a pass. Longer term, consider decoding via Pillow for formats OpenCV lacks.

---

## High

### H1. Edited photos keep stale AI results forever and orphan their old thumbnail

**Severity:** High · **Where:** `backend/app/database/images.py:161-168` (also `database/videos.py:112-115`); `backend/app/utils/images.py:334-344`, `:382-383`

**Problem:** When a file's mtime/size changes, the upsert emits `isTagged=False, isEmbedded=False` — but the conflict clause is `isTagged=CASE WHEN excluded.isTagged THEN 1 ELSE images.isTagged END`, which treats incoming `False` as "keep the old value". Nothing in production ever resets those flags (only `scripts/reset_embeddings.py` and a test do). Result: an edited or re-exported image gets a fresh thumbnail and metadata but **never re-runs YOLO, FaceNet or SigLIP** — its class tags, face embeddings and semantic embeddings stay from the old content, poisoning search, face grouping and memory scoring. Additionally the new record generates a new `thumbnail_<uuid>.jpg` and overwrites `thumbnailPath` with **no collection of the superseded thumbnail** — videos have exactly that logic (`utils/videos.py:106-149`), images don't.

**Solution:** When `image_util_is_unchanged` reports a change, insert with `isTagged=0/isEmbedded=0` and make the conflict clause honor a real reset — compare stored `file_mtime`/size against the incoming row, and force both flags to 0 on change. Reuse `video_util_collect_superseded_thumbnails`-style cleanup for images.

---

### H2. No WAL, no busy_timeout — four writers on one rollback-journal SQLite file

**Severity:** High · **Where:** `backend/app/database/connection.py:19-26`; every `_connect()`; same in `sync-microservice/app/database/folders.py`

**Problem:** A repo-wide grep finds zero `journal_mode`/`busy_timeout` pragmas. `sqlite3.connect(DATABASE_PATH)` uses the default rollback journal and 5 s busy timeout, while `main.py:101-103` runs a 2-worker indexing pool, a 1-worker AI pool, and every request thread, plus the sync-microservice reading the same file from another process. Any writer holding the reserved lock beyond 5 s turns unrelated writes into `sqlite3.OperationalError: database is locked` — which several call sites swallow into `False`/`[]` (see M8), presenting a lock error to the user as an empty library. In the sync service, the swallowed error makes the watcher start log "No folders found in database" and watch nothing (all subsequent filesystem events missed).

**Solution:** Set `PRAGMA journal_mode=WAL` once (WAL lets readers proceed during a write — critical for the cross-process reader) and `PRAGMA busy_timeout=30000` on every connection: `connection.py`, each database module's `_connect()`, and the sync service's connects. Also stop converting lock errors into empty results (M8).

---

### H3. The stale-download reaper cancels healthy downloads and hangs SSE clients forever

**Severity:** High · **Where:** `backend/app/routes/models.py:84-97` (reaper), `:59-66` (`created_at` never refreshed), `:276-281` (task), `:359-387` (SSE stream)

**Problem:** Task age is measured from `DownloadTaskEntry` creation and never updated by progress callbacks, and the reaper checks neither `active_listeners` nor last-progress time. The ~1.1 GB SigLIP2 text model on any slow connection exceeds 10–15 minutes easily and is cancelled mid-flight while actively downloading. `asyncio.CancelledError` is a `BaseException`, so `background_setup`'s `except Exception` never pushes a terminal event onto the queue, and the entry has already been popped — so `event_generator` loops on `wait_for(queue.get(), timeout=15)` yielding heartbeats **forever**: the UI shows a permanently stuck progress bar with no error. The pop also makes `GET /models/download/status` 404 for that task.

**Solution:** Track `last_progress_at`, updated in the progress callback; reap only when there has been no progress for N minutes *and* no active SSE listener. On cancellation, push a terminal `{"status": "error", "detail": "cancelled"}` (or set a flag the generator checks) before popping the entry.

---

### H4. The model-in-use guard is per-process and blind to where inference actually runs

**Severity:** High · **Where:** `backend/app/models/session_registry.py` (module globals + `RLock`); mark calls in `ONNXSessionBase.py:64`, `YOLO.py:61-64`, `FaceNet.py:61`; consumers `main.py:101-103`, `routes/folders.py:355`, `routes/memories.py:222`

**Problem:** `session_registry` state is visible only inside the process that imports it. Sessions are created inside `ProcessPoolExecutor` workers (tagging, scoring and curation all run in `app.state.executor`), so the API process sees **0 active sessions for a model a worker is actively running**, passes `try_mark_model_for_deletion`, and deletes the file. On Windows an in-use `.onnx` yields `PermissionError` → 500; on Linux the file is unlinked out from under the worker and every later session creation fails until re-download. The registry's documented purpose is defeated for the entire background workload.

**Solution:** Persist active-session state in SQLite — a counter row per model key, incremented/decremented by workers and checked by `DELETE /models/{key}` — or defer actual file removal until all processes confirm release (e.g. rename to a `.deleting` marker and unlink at next startup when no worker holds it).

---

### H5. `POST /folders/sync-folder` never checks that folder_id and folder_path describe the same folder

**Severity:** High · **Where:** `backend/app/routes/folders.py:491-526`

**Problem:** The handler queries child folders by `parent_folder_id = request.folder_id` and separately lists filesystem children by `request.folder_path`, then deletes DB children whose path isn't in the filesystem set. Nothing reconciles the two inputs. A mismatched pair deletes folder A's children based on folder B's contents — cascading into images, faces and embeddings — then re-indexes the wrong path under folder A's id. Any local process (and, given C2, any webpage) can send arbitrary pairs.

**Evidence:**

```python
db_child_folders = db_get_direct_child_folders(request.folder_id)
filesystem_folders = folder_util_get_filesystem_direct_child_folders(request.folder_path)
folders_to_delete = db_folder_paths - filesystem_folder_set
```

**Solution:** Look the folder up by id and derive the path from the DB row instead of trusting the request body — the sync-microservice watcher doesn't need to send a path at all. Return 400 if a path is supplied and doesn't match.

---

### H6. Restarting the watcher from inside the watcher thread leaks unstoppable duplicate watchers

**Severity:** High · **Where:** `sync-microservice/app/utils/watcher.py:88` (restart call), `:208` (same-thread call site), `:312-328` (stop/join/clear), `:284-290` (new thread + `stop_event.clear()`)

**Problem:** When a watched root folder is deleted (unplug a USB drive, delete a synced folder), the watcher thread calls restart → stop → `watcher_thread.join(timeout=5.0)` where `watcher_thread` **is the current thread** → `RuntimeError: cannot join current thread`, swallowed by `except Exception`. The `finally` then nulls the thread handle and `start` clears `stop_event` and spawns a new thread. The old thread resumes its loop, sees the *cleared* stop event, and never exits. Every deleted-root event adds one more permanently live watcher, each firing `/folders/sync-folder`, `/folders/delete-folders` and `/watcher/restart` at the backend — duplicate indexing storms, growing thread/FD usage, and a global handle that can no longer stop the orphans.

**Solution:** Guard all start/stop/restart state with a single `threading.Lock`. Never `join()` when `threading.current_thread() is watcher_thread` — set the stop event and let the loop break after `handle_file_changes` returns. Clear/re-set the event only under the lock.

---

### H7. No recovery from `BrokenProcessPool`; clustering can OOM the worker that triggers it

**Severity:** High · **Where:** `backend/main.py:101-103`; `backend/app/utils/face_clusters.py:325-337`; zero `BrokenProcessPool` handling anywhere in `backend/`

**Problem:** If a pool worker dies (OOM, native cv2/ONNX crash), `ProcessPoolExecutor` never self-heals — every future `submit()` raises `BrokenProcessPool`. Pending work never runs its cleanup: folders stay `INDEXING_IN_PROGRESS`, memories runs stay claimed, and every subsequent add-folder/tagging/curation request 500s until app restart. The most likely OOM source is in the same pipeline: `cosine_distances(embeddings_array)` materializes a float64 N×N matrix (10k faces ≈ 800 MB; 50k ≈ 20 GB) inside the single AI worker.

**Solution:** Wrap submits in a helper that catches `BrokenProcessPool`, recreates the executor on `app.state`, releases claimed runs (reuse `_release_run` in `routes/memories.py`), marks claimed folders interrupted, and either resubmits or fails cleanly. For clustering, compute distances in bounded chunks, cap to float32 (sklearn accepts float32 precomputed), and rely on the existing incremental-assignment path for large N.

---

### H8. CI's "Backend Tests" run against the sync-microservice's dependency set, not the backend's

**Severity:** High · **Where:** `.github/workflows/pr-check.yml:141-157`

**Problem:** One job, one interpreter: it installs `backend/requirements.txt` (fastapi 0.111.0, starlette 0.37.2, pydantic 2.7.1), then installs `sync-microservice/requirements.txt` **into the same environment** (fastapi 0.116.1, starlette 0.47.2, pydantic 2.11.7, uvicorn 0.35.0), and only then runs `pytest`. The green badge therefore proves nothing about compatibility with the pinned backend set; an incompatibility with the backend's own pins can never surface.

**Solution:** Split into separate jobs (or separate venvs) so backend tests install only backend requirements and sync tests (once they exist) install only sync requirements. Keep the PyInstaller build smoke checks in their own steps.

---

### H9. Local `pytest` writes to the user's production database; `TEST_MODE` does nothing

**Severity:** High · **Where:** `backend/app/config/settings.py:41-44`; `backend/tests/conftest.py:19-54`

**Problem:** `DATABASE_PATH` switches only on `GITHUB_ACTIONS` — locally, every test that doesn't monkeypatch it reads and writes the real `user_data_dir("PictoPy")/database/PictoPy.db`. `conftest.py` creates 13 tables through the production connection. `TEST_MODE` is set at `conftest.py:24` and documented in `backend/AGENTS.md` as part of the harness, but is **read nowhere in `backend/app`**. A contributor running the suite locally can corrupt their own library. Additionally `conftest.py`'s table-creation order differs from `main.py`'s — today both respect the one critical pair (clusters before faces), but the documented "must match exactly" invariant is unenforced.

**Solution:** Honor an env override: `DATABASE_PATH = os.getenv("PICTOPY_DATABASE_PATH") or (test path when GITHUB_ACTIONS else production path)`, and have `conftest.py` set it to a temp file before any import touches settings. Either implement `TEST_MODE` where documented or delete the fiction from `AGENTS.md`. Extract the table-creation order into one shared helper used by both `main.py` and `conftest.py`.

---

### H10. Tagging writes classes → faces → isTagged in three transactions, and face inserts are not idempotent

**Severity:** High · **Where:** `backend/app/utils/images.py:235-259`; `backend/app/database/faces.py:187-194`

**Problem:** The three writes each open their own connection and commit independently. `image_classes` uses `INSERT OR IGNORE`; `faces` uses a plain `INSERT` with no dedup key. A crash, kill or `database is locked` between the face insert and the `isTagged=1` update leaves the image untagged, so the next pass re-runs inference and inserts a **second copy of every face** — duplicated rows then feed clustering and face search. The `False` return from `db_update_image_tagged_status` (its own error path) is ignored.

**Solution:** Perform all three steps on one connection inside one transaction, or make face inserts idempotent (`INSERT OR IGNORE` keyed on a stable per-image hash of the embedding). Never mark tagged unless every preceding write committed.

---

### H11. Full recluster holds a write transaction open across per-cluster disk I/O

**Severity:** High · **Where:** `backend/app/utils/face_clusters.py:160-187`, `:976-1011`

**Problem:** `cluster_util_face_clusters_sync` opens a transaction at the `DELETE FROM face_clusters` and then, for every cluster, reads a source photo with `cv2.imread`, crops, and `cv2.imencode`s it — seconds to tens of seconds of disk work while holding SQLite's reserved lock. Combined with H2's 5 s default, favourite toggles, tagging-status updates and folder writes fail with "database is locked" for the whole window.

**Solution:** Generate face images (and read the face rows) *before* opening the transaction, then write the collected results in one short transaction.

---

### H12. Cross-process concurrent model download corrupts `.onnx` files

**Severity:** High · **Where:** `backend/app/routes/models.py:70-81` (`asyncio.Lock` per model key); `backend/app/routes/folders.py:165` (`ensure_ai_tagging_models()` in a worker)

**Problem:** The download locks are `asyncio.Lock`s — visible only within one event loop. `post_AI_tagging_enabled_sequence` runs in a `ProcessPoolExecutor` worker and downloads required models, while `POST /models/setup` downloads in the API process. Both write the same destination path with no cross-process exclusion: interleaved writes produce a file that fails SHA-256 and retries, or (rarely) a partially-corrupted file that passes a read window.

**Solution:** Download to a unique temp name and atomically `os.replace` into place (already the shape of a correct fix), plus an OS-level lock file (`os.open(..., O_CREAT|O_EXCL)` / `msvcrt.locking`) around the whole download when the destination doesn't exist.

---

## Medium

### M1. One imperfect row 500s the entire image library listing

**Severity:** Medium · **Where:** `backend/app/routes/images.py:80-93`, `:122-135`, `:280-298`

**Problem:** `GET /images/`, `/images/search` and semantic search build the whole response in one list comprehension inside one `try`. `MetadataModel` requires name/width/height/file_location/file_size/item_type with no defaults, and `ImageData.thumbnailPath` is non-optional — but `image_util_parse_metadata` deliberately returns `{}` for NULL/corrupt JSON and `thumbnailPath` is a nullable column. A single legacy or hand-edited row therefore 500s the entire listing. This is precisely the anti-pattern `backend/AGENTS.md` bans ("Build list responses row by row… see `get_all_videos`"), which `video_util_to_video_data` (`utils/videos.py:58-80`) already implements correctly.

**Solution:** Validate per row inside the loop, log-and-skip bad records, and make `thumbnailPath`/`metadata` optional or defaulted to match what the columns can hold.

---

### M2. Semantic search loads every embedding in the database into RAM per request

**Severity:** Medium · **Where:** `backend/app/database/image_embeddings.py` (`db_get_all_embeddings`), consumed by `routes/images.py:155+` and `routes/videos.py:114+`

**Problem:** Each query pulls all rows and decodes them to float32: 100k images × 768 dims ≈ 300 MB per request, ~1.5 GB at 500k photos, multiplied by concurrent requests inside uvicorn's threadpool. At "offline photo manager" scale this is the most likely runtime OOM/swap trigger outside clustering.

**Solution:** Filter candidates in SQL first (folder/tag/date predicates, recency limit), batch the matmul in bounded chunks, or maintain a process-owned scored cache refreshed by the existing worker instead of per-request full loads.

---

### M3. Video frame directory wiped before the capture is known to open; transient failure permanently tags the video empty

**Severity:** Medium · **Where:** `backend/app/utils/videos.py:598-604`, `:1002-1011`

**Problem:** `video_util_remove_frame_directory` runs before `cv2.VideoCapture` is opened. If the open fails, the frames are already gone and the function returns `[]`. The caller treats empty frames as "undecodable file" and permanently marks the video tagged + faces-scanned, so `db_get_untagged_videos` never retries it — but the same path is hit by a transient failure (file locked mid-copy, network hiccup), which `images.py:193-198` explicitly designs around. The empty branch also skips `db_delete_frames_for_videos`, leaving DB rows pointing at already-deleted JPEGs.

**Solution:** Open the capture first; wipe only after a successful open (or after frames are produced). In the empty branch, clear stale DB frame rows too, and don't set `facesScanned` on an open failure so a retry is possible.

---

### M4. Folder walk failures are reported as success

**Severity:** Medium · **Where:** `backend/app/routes/folders.py:131-138`; return values ignored; `utils/images.py:103-105` and `utils/videos.py:159-161` swallow their own exceptions and `return False`

**Problem:** Because the walk functions return `False` instead of raising, the `except` at `folders.py:145-153` (which correctly marks `INDEXING_INTERRUPTED`) never fires for walk/insert failures. The sequence writes `INDEXING_COMPLETED` and the tagging sweep proceeds as if indexing succeeded.

**Solution:** Check both return values; on `False`, mark folders `INDEXING_INTERRUPTED` and return `False`, reusing the existing except-path logic.

---

### M5. Folder path-prefix lookup over-matches siblings and interpolates wildcards

**Severity:** Medium · **Where:** `backend/app/database/folders.py:363-376`; consumed by `routes/folders.py:121-138`

**Problem:** `WHERE folder_path LIKE ? || '%'` with an unescaped root means `C:\photos` also matches `C:\photos2`, and a `_` or `%` in a user's folder name acts as a wildcard. `post_folder_add_sequence` then marks those unrelated folders `INDEXING_IN_PROGRESS` → `COMPLETED` and runs an image walk over them.

**Solution:** Match `root || os.sep` with `LIKE ? ESCAPE '\'` (escaping `%`/`_` in the parameter), or compare with `substr(folder_path, 1, length(?)) = ?`.

---

### M6. The memories run "claim" is not atomic — a run can be queued twice

**Severity:** Medium · **Where:** `backend/app/routes/memories.py:183-223`; `backend/app/database/memories.py:840-857`

**Problem:** The route reads the run row, checks `status == "running"`, then calls `db_start_memory_run`, whose upsert always succeeds and whose `rowcount` cannot distinguish insert from update. Two requests interleaving between the check and the upsert both pass and both submit `memory_curator_run` — duplicate full curation passes (ONNX + embedding work) racing on the same `dedupe_key` rows.

**Solution:** Make the claim conditional — `INSERT … ON CONFLICT(run_date) DO UPDATE SET … WHERE memory_runs.status != 'running'` — and queue the work only when `rowcount` reflects a real transition.

---

### M7. Expired shares never stop the `0.0.0.0` listener; the registry only GCs lazily

**Severity:** Medium · **Where:** `backend/app/share/registry.py:96-122`; `backend/app/utils/share.py:66-77`

**Problem:** `share_util_revoke` stops the server only when an explicit revoke drops the count to zero. When every share merely *expires*, nothing ever calls the count check, so the public port stays open and the uvicorn task runs until process exit. `share_registry_list` filters expired entries but doesn't remove them, so a long-lived session accumulates dead `ShareEntry` objects.

**Solution:** On expiry touch (and on a lightweight periodic sweep), check `share_registry_count() == 0` and schedule `share_server_stop()`. Have `share_registry_list` delete what it filters.

---

### M8. DB errors are swallowed into empty results; wrong HTTP status codes

**Severity:** Medium · **Where:** `backend/app/database/images.py:289-291`; `backend/app/routes/albums.py:241-247`, `:351-362`; several `str(e)` 500s in `routes/folders.py`, `routes/models.py`

**Problem:** `db_get_all_images` catches every `sqlite3.Error` and returns `[]`, so a lock or corruption error is presented as "you have no photos" with `success=True`. `update_album` maps every exception (including DB failures) to HTTP 400; `add_images_to_album` maps a `ValueError` (client error) to 500 and reports a success count based on requested rather than inserted ids. Several 500 responses embed raw `str(e)`, which includes absolute paths and sqlite internals — harmless while localhost-only, readable by any webpage under C2.

**Solution:** Narrow the blanket handlers — let lock/IO errors propagate to a retryable 500; catch `ValueError` as 400/404 as the sibling handlers already do; log exceptions server-side and return a generic message with a correlation id, matching the share app's uniform `_not_found()` discipline.

---

### M9. One corrupt face or cluster row kills clustering or the whole cluster listing

**Severity:** Medium · **Where:** `backend/app/database/faces.py:414`; `backend/app/database/face_clusters.py:405-409`

**Problem:** `db_get_all_cluster_face_embeddings` does an unguarded `json.loads` + `np.array` per row, while its sibling at `faces.py:327-338` deliberately skips bad rows ("One face must not fail the search"). `cluster_util_cluster_all_face_embeddings` calls the unguarded one with no try, so one corrupt row aborts clustering inside `post_AI_tagging_enabled_sequence`, whose `except` only logs and whose `finally` sets `taggingCompleted = True` — clustering never runs again and the UI reports success. Separately, the cluster listing unguards `json.loads(metadata)`/`json.loads(bbox_json)`, so one corrupt blob 500s every cluster.

**Solution:** Apply the existing per-row `try/except (json.JSONDecodeError, TypeError): continue` pattern to both functions; log-and-skip with a warning.

---

### M10. Share media follows symlinks — arbitrary file bytes served to the LAN

**Severity:** Medium · **Where:** `backend/app/share/media.py:44-57`; routes at `app/share/routes.py:150-166`

**Problem:** The membership check correctly prevents ID-oracle attacks, but `os.path.isfile` and `FileResponse` follow symlinks. Once an indexed row's `path` is a symlink, the `0.0.0.0`-bound share server serves the *target's* bytes to any token holder, with the mimetype guessed from the symlink's name (a symlink named `x.png` → secret file is delivered as `image/png`). A process that can write into an indexed folder (cloud-sync dir, another local user) can plant such a link in a folder the victim is likely to share.

**Solution:** `os.path.realpath()` the resolved path and require it to stay inside the album's registered folder root before serving.

---

### M11. Preferences PUT is an unguarded read-modify-write of the shared metadata blob

**Severity:** Medium · **Where:** `backend/app/routes/user_preferences.py:83-92`; concurrent writers at `utils/face_clusters.py:139`, `:187`

**Problem:** The handler reads the whole `metadata` JSON, deep-merges, and writes the whole blob back. Clustering writes `reclustering_time` into the same blob. An interleaved preferences update and cluster sync lose whichever write lands second.

**Solution:** Store preferences in a dedicated row/column with a targeted `json_set`-style update, or use compare-and-swap on a version value in the blob.

---

### M12. Async handlers block the event loop on sync SQLite and filesystem work

**Severity:** Medium · **Where:** `backend/app/routes/models.py:162-164` (DB read under `threading.RLock` inside `async def delete_model`); `backend/app/routes/share.py:97`; sync-microservice `app/routes/watcher.py:23-57`, `app/utils/watcher.py:315`, `app/core/lifespan.py:57`

**Problem:** Sync SQLite connects, `thread.join(timeout=5.0)` and per-folder `os.path.exists` probes run directly inside `async def` handlers, stalling `/health`, `/folders/status` and every other request for seconds while they run. `delete_model` already uses `await asyncio.to_thread(os.remove, path)`, so the convention exists but isn't applied to the DB read or the lock hold.

**Solution:** Wrap blocking calls in `asyncio.to_thread` (or make the sync-microservice lifecycle routes plain `def` so FastAPI's threadpool runs them), and keep lock scopes tight.

---

### M13. Async handlers build one unbounded `IN` clause from client input

**Severity:** Medium · **Where:** `backend/app/database/albums.py:372-378`; `backend/app/utils/images.py:478-480` + `database/images.py:575-579`

**Problem:** `db_add_images_to_album` and `db_delete_images_by_ids` build a single `IN (?,?,…)` from the full id list without chunking. `SQLITE_ID_CHUNK = 500` exists and is applied elsewhere (`db_get_images_by_ids`, memories, embeddings). Over ~999 ids, SQLite raises `too many SQL variables` — and in the obsolete-image path this happens **after the thumbnails have already been deleted from disk**, with the failure returned as `False` and the caller still logging success.

**Solution:** Reuse the existing chunking loop. In the obsolete-image path, delete DB rows first (chunked), honour the return value, and only then remove thumbnails for rows that actually deleted.

---

### M14. `create_album` check-then-insert race surfaces as 500; unused N+1 in `get_albums`

**Severity:** Medium · **Where:** `backend/app/routes/albums.py:98-109`, `:70-91`; `backend/app/database/albums.py:317`, `:378`

**Problem:** A concurrent `create_album` passes the `db_get_album_by_name` check and hits the UNIQUE constraint → generic 500 instead of the 409 helper defined next door. `get_albums` is N+1 — it fetches every album's full image-id list just to compute `len()`, plus a cover query each — while `db_count_album_images` sits unused.

**Solution:** Catch `sqlite3.IntegrityError` and raise the existing `_album_exists` 409. Replace the per-album queries with one grouped `COUNT(*)` and one grouped cover query (or call `db_count_album_images`).

---

### M15. Security headers missing on the public share pages; weak share password floor

**Severity:** Medium · **Where:** `backend/app/share/routes.py:33-109` (no header middleware); `backend/app/share/app.py:20-25`; `backend/app/schemas/share.py:16` (`min_length=4`); `backend/app/share/registry.py:31-32` (10 guesses / 30 s, forever)

**Problem:** LAN-facing share responses carry no CSP, `X-Content-Type-Options`, or `frame-ancestors`, so the password gate can be iframed by any LAN page (clickjacking/redressing) and future template regressions lose a protection layer. Templates are autoescaped today (starlette forces it; verified no XSS), so this is defense-in-depth, not an open hole. Separately, a 4-character minimum against a flat 10-per-30s budget means a 4-digit PIN falls in ~3.5 hours of LAN-resident grinding.

**Solution:** Add `frame-ancestors 'none'`, `nosniff` and a matching CSP on share responses. Raise `min_length` to 8, and make the unlock cooldown grow per lockout.

---

## Low — cleanup

| ID | Issue | Where | Fix |
| --- | --- | --- | --- |
| L1 | Three dead legacy files: `test.py` (broken scratch — queries a non-existent `image_id_mapping` table), `routes/test.py` (100% commented, imports non-existent modules), `schemas/test.py` | `backend/test.py`, `app/routes/test.py`, `app/schemas/test.py` | Delete all three |
| L2 | Two modules never imported anywhere: `schemas/facetagging.py`, `utils/image_metadata.py` (duplicates `image_util_extract_metadata`) | `app/schemas/facetagging.py`, `app/utils/image_metadata.py` | Delete |
| L3 | Functions with parameters they never read — callers believe they're narrowing behaviour | `routes/folders.py:111` (`folder_id`), `database/folders.py:245` (`root_folder_path`), `models/YOLO.py:174` (`draw_scores`) | Remove the params or honor them |
| L4 | Six never-called functions incl. `db_get_all_clusters`, `db_get_images_by_ids_for_memories`, `install_signal_handlers` | see audit; each has exactly one grep hit — its own `def` | Delete |
| L5 | Whole YOLO drawing chain unreachable (~80 lines) | `utils/YOLO.py:161-228` → `models/YOLO.py:174` (no callers) | Delete or wire to a debug flag |
| L6 | Dead settings + 8.9 MB of unreferenced test fixtures, duplicated into sync-microservice settings (a service with no tests) | `settings.py:39-40,47`; `tests/inputs/`, `tests/outputs/`; `sync-microservice/app/config/settings.py:22,23,30` | Delete constants and unreferenced fixtures |
| L7 | Stale launchers bind `0.0.0.0:8000` while the app uses `localhost:52123`; sole consumer of `Hypercorn` | `backend/run.sh`, `backend/run-server.ps1`, `requirements.txt:18` | Delete scripts + Hypercorn pin, or rewrite to 52123 |
| L8 | `requests` imported at boot but unpinned — resolves only transitively via `mkdocs-material` | `app/utils/API.py:1`; chain `main.py:43` → `routes/folders.py:43` | Pin `requests` in `requirements.txt`; move docs packages out of runtime requirements |
| L9 | Unused runtime deps: `loguru`, `pytest-asyncio` (no async tests exist), `sentry-sdk` in sync-microservice (red flag in a privacy-first product) | `requirements.txt:23,69`; `sync-microservice/requirements.txt:28,39` | Remove |
| L10 | Dev-tool pins disagree with CI lint pins — running `black`/`ruff` directly rewrites files CI then rejects | `requirements.txt:66-68` vs `requirements-lint.txt` + `.pre-commit-config.yaml` | Align pins |
| L11 | Startup rewrites a git-tracked file, dirtying the working tree; nothing verifies committed contract matches code | `main.py:77,145-168` → `docs/backend/backend_python/openapi.json` | Write only when explicitly requested, or diff-check in CI |
| L12 | Logger immediately overwritten, losing project logging setup for the module | `app/utils/images.py:37` then `:43` | Delete line 43 |
| L13 | Zero-vector face embedding → NaN → silent empty search results | `app/models/FaceNet.py:16-23`; `utils/faceSearch.py:91-93` | Guard with the existing `_validate_embedding`; return a clear "no usable face" error |
| L14 | Placeholder model entries are downloadable (guaranteed failure) and entangled with the active-tier delete guard | `app/models/model_registry.py:108-123`; `routes/models.py:163-174,291-300` | Reject `PLACEHOLDER_URL` specs in `ensure_model`/routes; give them their own tier |
| L15 | Port 52123 hardcoded in six places; `DATABASE_PATH` duplicated in sync-microservice | `main.py:135,213`, `settings.py:19,23`, `frontend/src/config/Backend.ts`, `src-tauri` ×2, `tauri.conf.json:69` | Single source of truth per constant |
| L16 | Starting the share server silently disables main-backend access logging process-wide | `app/share/server.py:133-138` (uvicorn configures the shared `uvicorn.access` logger globally) | `access_log=False` on the share Config, restore level afterwards |
| L17 | No free-disk-space check before multi-GB downloads; non-retryable 404s burn all retries; case-sensitive digest compare; callback exceptions abort downloads | `app/utils/model_downloader.py` | Preflight `shutil.disk_usage`; branch on status before retrying; lowercase both digests; isolate callback errors |
| L18 | Watcher path matching is case-sensitive on Windows — changes can be missed | `sync-microservice/app/utils/watcher.py:115-117` | Compare `os.path.normcase(os.path.abspath(...))` on both sides |
| L19 | Watcher thread death is final — sync silently stops forever with only a log line | `sync-microservice/app/utils/watcher.py:209-212` | Supervise with capped exponential backoff restart, or have the backend poll `/health` and restart |
| L20 | `db_update_cluster` closes a caller-owned connection (`own_connection` computed, never read); `db_create_images_table` leaks its connection on error | `database/face_clusters.py:246,274-275`; `database/images.py:75-141` | `if own_connection: conn.close()`; wrap in `try/finally` like sibling creators |
| L21 | `sync-microservice/README.md` documents routes that don't exist (`GET /`, `GET /folders`), an outdated tree, and a 0-byte `file_watcher.py` it tells contributors to extend | `sync-microservice/README.md:52-56,93,103,133-144`; `app/utils/file_watcher.py` | Rewrite README from `main.py` + routes; delete the empty module |
| L22 | Frontend dead wiring: `shareEndpoints.getInterfaces` never referenced; `syncFolder` never read; `/share/*` HTTP routes have zero tests | `frontend/src/api/apiEndpoints.ts:66,36`; `backend/tests/` | Delete dead entry or wire it; add share route tests (see test gaps) |
| L23 | Windows shutdown skips lifespan cleanup — pool workers can outlive the API | `routes/shutdown.py:31-33` vs `main.py:114-123` | Shut down both executors explicitly before `os._exit(0)` (folded into C3's fix) |

---

## Test gaps

These are behaviors the product depends on that have **no HTTP-level or end-to-end coverage**:

| Gap | Detail |
| --- | --- |
| **`/share/*` and `/shutdown` have zero route tests** | All four share endpoints (`routes/share.py:48,68,82,122`) and shutdown (`routes/shutdown.py:39`) — grep for `share_router`/`shutdown_router` in tests → 0 hits. Share registry/throttle logic *is* unit-tested; the HTTP surface and its wiring are not. |
| **`POST /folders/sync-folder` has no route test** | The exact endpoint the filesystem watcher calls (`sync-microservice/app/utils/watcher.py:135`), including its 400/404/500 branches. The orchestrator `post_sync_folder_sequence` *is* unit-tested 3×; the route is not. Also note a pool inconsistency: sync-folder submits to `executor` while add-folder uses `indexing_executor`. |
| **Primary image routes untested** | `/images/`, `/images/search`, `/images/toggle-favourite` — only `/images/semantic-search` is covered. The video twins are well covered; asymmetric risk. |
| **Face-search and recluster HTTP shaping untested** | `POST /face-clusters/face-search` and `POST /face-clusters/global-recluster` handlers; underlying utils are covered, HTTP layer is not. |
| **Video semantic search max-pooling untested** | The only `/videos/semantic-search` test asserts the 404-when-models-missing branch; the cross-frame aggregation — the core correctness claim — is untested. |
| **Model downloader untested; sync-microservice has no tests at all** | `model_downloader.py`'s Range/416/SHA-256/retry logic is only ever *patched* in `test_models.py`. `sync-microservice/` has no `tests/` directory and no pytest config. |
| **No test imports `main`; two tests mount routers with wrong prefixes** | `import main` in tests → 0 hits, so router prefixes, CORS, `/health` and the lifespan table/cleanup sequence are unverified. `test_face_clusters.py:29` mounts `/face_clusters` (app uses `/face-clusters`); `test_user_preferences.py:8` mounts `/user_preferences` (app uses `/user-preferences`). A typo'd hyphen in `main.py` would pass CI. |

**Recommendation:** add one integration test that mounts `main.app` via `TestClient` and smoke-hits `/health` plus one endpoint per router — it would catch prefix drift, unregistered routers and lifespan regressions at once — then fill the per-endpoint gaps in the order listed above.

---

## Recommended fix order

1. **Restore trust in the test signal first** — H8 (CI tests the wrong dependency set) and H9/H2 (tests write the production DB; no WAL) undermine every other verification. One `PICTOPY_DATABASE_PATH` env override fixes the root cause of H9.
2. **H10 / pin `requests` (L8)** — the one-line dependency fix removes an import-time boot failure risk.
3. **C4** — `or []` plus per-image isolation; smallest change, largest user-visible fix (one GIF currently bricks tagging forever).
4. **C1** — read-gate before obsolete-deletion; prevents irreversible data loss.
5. **C2 + C3 (+ H5)** — one shared-secret design covers the CORS/auth surface, shutdown, and sync-folder path trust. **Raise as an issue first** — it changes the frontend↔backend contract and is a [design — confirm] item.
6. **H3 + H12** — download reaper progress-tracking and atomic replace; fixes the stuck-progress UX and file corruption.
7. **H1** — reset `isTagged`/`isEmbedded` on change; restores the core "search reflects your library" promise.
8. **H6 + H19** — lock the watcher state machine; stop orphan watchers.
9. **H7 + H11 + M2** — clustering/memory-safety and BrokenProcessPool recovery.
10. **Test gaps** — mount `main.app`, then share/sync-folder/images routes.
11. **Medium batch** — M1 (row-by-row listings), M3, M4, M8 (status codes + no swallowed errors), M9 (corrupt-row tolerance), M13 (chunking).
12. **Low/cleanup batch** — L1–L7 dead files, L9–L11 dep and process hygiene, L21 README rewrite — one cleanup PR.

Per project rules: **do not open PRs until maintainers review and label an issue.** Suggest filing the Criticals as individual issues (they're independently reproducible) and grouping the Medium/Low batches.

---

## Verified non-issues

Checked and deliberately **not** reported, so they aren't re-investigated:

- **SQL injection** — every `f"... IN ({placeholders})"` interpolates only `?` lists or module constants; parameterized throughout.
- **Share token security** — 256-bit `secrets.token_urlsafe`, bcrypt cost 12, 72-byte cap enforced at both schema and unlock, HMAC-SHA256 unlock cookie with `hmac.compare_digest`, `httponly` + `samesite=lax` + path-scoped; throttle races correctly counted via `pending_unlocks`.
- **Template injection / XSS on share pages** — starlette forces Jinja2 `autoescape=True`; album names only interpolated via `{{ }}`; JS context uses `| tojson`.
- **Model download integrity** — all live URLs HTTPS with pinned SHA-256; `ensure_model` verifies before returning and deletes on mismatch.
- **Embedding normalization** — SigLIP2 text/vision and semantic labels all L2-normalize; stored float32; dot == cosine across the pipeline.
- **Memory date arithmetic** — all `captured_at` writers produce naive datetimes consistently; anniversary candidates filter future years.
- **Memory run reaping/claim-release on failed submit** — correct apart from the non-atomic claim in M6.
- **`/folders/status`** — lives on the sync-microservice and is reached correctly via `syncApiClient`; not broken.
- **`VIDEO_FRAMES_PATH` creation** — lazily created with `exist_ok=True` by every writer; guarded readers; safe as written.
- **DB connection leaks in sync-microservice** — both `folders.py` functions close in `finally`.
- **Dependency conflicts** — `fastapi==0.111.0` + `starlette==0.37.2` + `pydantic==2.7.1` resolve cleanly; the fastapi hard-deps pinned in requirements are legitimate.
- **No silently skipped tests** — zero `skip`/`xfail`/`importorskip` hits; ONNX mocked with an explicit reason; no network I/O in tests.
- **No orphaned routes** — all 58 route decorators map to routers registered in `main.py:187-201`.
