# 🏥 HealthAI — Backend Development Guide

**A complete, mentor-led roadmap for building the HealthAI Healthcare Assistance Platform backend from scratch.**

> **Stack:** Python · FastAPI · Pydantic · SQLAlchemy 2.0 · Alembic · Uvicorn · PostgreSQL (Supabase)
> **Audience:** A CSE student who knows Python well and wants to *understand* backend engineering.
> **Teaching model:** You write the code. This guide tells you *what* to build, *why*, *how the pieces interact*, *what decisions to make*, and *what to do next*.

---

## How to Use This Guide

This is not a code dump. It is a **roadmap + reference manual** in three parts:

| Part | Location | Purpose |
| ---- | -------- | ------- |
| **Main Tutorial (Phases 0–26)** | Top of the file | Teaches concepts, architecture, and design. You implement. |
| **🆘 Code Reference** | End of the file | Working implementations you can consult *only when stuck*. |
| **🐛 Troubleshooting Guide** | Very end | Symptom → cause → fix for the most common problems. |

**Suggested workflow:**

1. Read Phase 0 to understand exactly what you're building. **Don't skip this.**
2. Work through phases **in order**. The guide is deliberately ordered so you never build on a broken foundation.
3. After every phase, run the **✅ Verify Your Work** checklist before moving on.
4. When you hit a wall, **first** follow the debugging method (symptom → logs → layer → root cause). **Only then** open the Code Reference for that section.
5. When the MVP is done, run the **Phase 26 checklist** end-to-end.

**Conventions used in this guide:**

- 🧭 **Decision point** — a choice you must make, with my recommendation.
- ✅ **Verify Your Work** — how to prove the phase worked before moving on.
- 🐛 **Common mistakes** — what students typically get wrong here.
- 💡 **Concept** — a foundational idea explained in plain language.

> ⚠️ **Healthcare safety notice:** This project assists, screens, summarizes, and supports decisions. It **does not diagnose or treat**. The AI features are information-support tools, never autonomous doctors. Every phase keeps this boundary visible. You will see this reminder where it matters.

---

# Phase 0 — Understanding the MVP

**Goal of this phase:** define precisely what you are building before writing a single line of code. A clear MVP boundary is what keeps this project finishable.

## 0.1 Project Goals

HealthAI is a platform where:

- **Patients** manage their health data (profile, medical history, allergies, metrics), upload and analyze medical documents, chat with an AI health assistant, and book appointments with doctors.
- **Doctors** see their patients, view medical information and reports, and manage appointments.
- **Management** (hospital staff) manages patients, doctors, departments, and appointments, and views operational analytics.
- **Admins** manage roles, users, and system configuration, and review audit logs.

The backend exists to do one job: **safely store, protect, and serve healthcare data, and to expose it to the right people through a consistent API.**

## 0.2 Target Users and Their Mental Model

Think about each role as a *capability set*, not a person table:

| Role | What they do | What they must NOT be able to do |
| ---- | ------------ | -------------------------------- |
| **PATIENT** | Own profile, health data, documents, appointments, AI assistant | See any other patient's data, change roles, see analytics |
| **DOCTOR** | Their patients' medical data, reports, appointments, clinical notes | Change system roles, access unrelated patients |
| **MANAGEMENT** | Patient/doctor/department/appointment management, operational analytics | Access raw clinical details they don't need, change roles |
| **ADMIN** | Users, roles, system config, audit logs | (Nothing within the system — the highest privilege, but still audited) |

This table becomes your **authorization matrix** in Phase 9. Everything about roles in this project flows from it.

## 0.3 Workflows

### Patient workflow

```
Register/Login
   ↓
Complete Profile + Health Profile (optional medical history, allergies)
   ↓
Record Health Metrics over time (weight, BP, glucose, ...)
   ↓
Upload a medical document → system analyzes it → view structured summary
   ↓
Ask the AI Health Assistant questions → get cited, cautious answers
   ↓
Request an appointment with a doctor → track its status
```

### Doctor workflow

```
Login
   ↓
See list of assigned patients
   ↓
Open a patient profile → medical history, allergies, metrics, documents, analyses
   ↓
Manage appointments (confirm, reschedule, complete)
   ↓
Add clinical notes / prescriptions (if in scope)
```

### Management workflow

```
Login
   ↓
Manage patients / doctors / departments / appointments
   ↓
View operational analytics (appointments per department, load, trends)
```

### Admin workflow

```
Login
   ↓
Manage users and roles
   ↓
Manage system configuration
   ↓
Review audit logs (who did what, when)
```

## 0.4 Backend Responsibilities (what the server actually does)

For **every** feature above, the backend is responsible for:

1. **Authentication** — verify *who* you are (login, JWT).
2. **Authorization** — verify *what you may do* (roles, ownership, object-level checks).
3. **Validation** — reject malformed or dangerous input (Pydantic).
4. **Business logic** — apply real-world rules (e.g., a doctor can only see *their* patients; an appointment's status transitions must be legal).
5. **Data access** — read/write PostgreSQL through SQLAlchemy.
6. **Serialization** — return exactly the data the client is allowed to see.
7. **Processing** — files (validation, storage, extraction, AI analysis) and AI (analysis, chat) as *services*, not inline route code.
8. **Auditability & logging** — record what happened so you can answer "who did what when".

## 0.5 Inside the MVP — Outside the MVP

Draw the boundary now and defend it. Scope creep is the #1 reason student projects die.

**✅ Inside the MVP:**

- Auth (register, login, JWT, refresh) and the four-role RBAC model
- Patient: profile, health profile, medical history, allergies, health metrics (time-series), documents, appointments, AI assistant
- Doctor: patient list/search, patient profile view, reports, appointment management, clinical notes
- Management: patient/doctor/department/appointment management, basic analytics
- Admin: user management, role management, system config, audit log viewer
- Document pipeline: upload → validate → store → extract → AI analyze → structured result
- Basic testing, logging, security hardening, Docker, deployment

**🚫 Outside the MVP (explicitly deferred):**

- Real-time chat / video calls, notifications (email/SMS), payments
- Mobile push, WebSockets, multi-hospital tenancy
- FHIR/HL7 interoperability, insurance/claims
- Complex analytics dashboards (charts live in the frontend; the API just serves aggregates)
- Prescriptions / e-prescriptions — **optional stretch**, designed but can be cut (see Phase 4)
- Full audit/compliance tooling beyond a basic audit log

> **Why draw a boundary?** Because every feature you add multiplies the surface area of models, routes, permissions, and tests. The MVP boundary is your contract with yourself: *finish these first, correctly.*

## 0.6 The Non-Negotiable Safety Principles

These are repeated throughout the guide because they shape *every* design decision:

1. **The system is not an autonomous doctor.** AI assists, screens, informs, summarizes, and supports decisions — it never independently diagnoses.
2. **Protect medical data.** Treat patient information as more sensitive than ordinary business data.
3. **Least privilege.** Users access only what they are authorized to access — nothing more.
4. **Never trust the frontend.** Every permission check happens on the backend, every time.
5. **AI output is untrusted.** Validate and constrain AI-generated data before storing or displaying it.
6. **Keep auditability.** Important data access and admin actions must be traceable.

### ✅ Verify Your Work (Phase 0)

- [ ] You can explain the MVP boundary in two sentences ("we build X, we do not build Y").
- [ ] You can name every database entity you *expect* to need (you'll formalize this in Phase 4).
- [ ] You can describe, in one paragraph each, the patient and doctor workflows.
- [ ] You have internalized why "never trust the frontend" forces checks on the backend.

---

# Phase 1 — Backend Architecture

**Goal of this phase:** understand the mental model of how a web backend works before touching code.

## 1.1 The Client–Server Model

```
┌────────────┐   HTTP request (JSON)    ┌────────────────────────────┐
│   Client   │ ───────────────────────▶ │   Backend (FastAPI)        │
│ (frontend/ │ ◀─────────────────────── │   - receives & validates   │
│  mobile/   │   HTTP response (JSON)   │   - authorizes             │
│  curl)     │                          │   - runs business logic    │
└────────────┘                          │   - talks to PostgreSQL    │
                                        └────────────┬───────────────┘
                                                     │ SQL
                                             ┌───────▼────────┐
                                             │   PostgreSQL    │
                                             └────────────────┘
```

Key insight: the client and server **never share memory, functions, or variables**. They communicate only through HTTP messages containing JSON. This is why validation must happen on the server: the client is a stranger that may send anything.

## 1.2 REST APIs in One Paragraph

REST is a *style* of API where:

- Resources (patients, doctors, appointments) are identified by **URLs**: `GET /patients/42`.
- Actions on resources are expressed with **HTTP methods**: `GET` (read), `POST` (create), `PUT`/`PATCH` (update), `DELETE` (remove).
- Responses carry an **HTTP status code** that tells the client the *kind* of outcome.

FastAPI implements this style for you almost for free. Your job is to design resources sensibly and map them to code.

## 1.3 HTTP Methods and Status Codes (memorize the important ones)

| Method | Meaning | Typical use |
| ------ | ------- | ----------- |
| `GET` | Read (no side effects) | Fetch resources |
| `POST` | Create | Create a resource, trigger an action |
| `PUT` | Replace | Full update |
| `PATCH` | Partial update | Small updates |
| `DELETE` | Remove | Delete |

| Status | Class | Examples you will use |
| ------ | ----- | --------------------- |
| 2xx | Success | `200 OK`, `201 Created`, `204 No Content` |
| 3xx | Redirection | rarely used by you |
| 4xx | Client error | `400 Bad Request`, `401 Unauthorized`, `403 Forbidden`, `404 Not Found`, `409 Conflict`, `422 Validation Error` |
| 5xx | Server error | `500 Internal Server Error`, `502/503/504` (gateway/timeouts) |

**Critical distinction to internalize now:**
- **401 Unauthorized** = "I don't know *who* you are" (missing/invalid token) → the client should log in.
- **403 Forbidden** = "I know *who* you are, but you may not do this" → logging in again won't help.

Students mix these up constantly. Phase 19 covers error design; Phase 22 covers why this matters for security.

## 1.4 The Request/Response Lifecycle in FastAPI

Trace what happens when a client sends `POST /patients`:

```
Client sends POST /patients  (JSON body)
        │
        ▼
Routing  ── FastAPI matches the URL+method to a router/path operation
        │
        ▼
Dependencies  ── run first (get current user from JWT, open DB session)
        │
        ▼
Validation  ── Pydantic parses the JSON body; rejects bad input with 422
        │
        ▼
Authorization  ── check the user's role and ownership of the resource
        │
        ▼
Service layer  ── business rules run here (not in the route function)
        │
        ▼
Data access  ── SQLAlchemy executes SQL against PostgreSQL
        │
        ▼
Response  ── a Pydantic response schema serializes the result to JSON
        │
        ▼
Client receives JSON + status code
```

**The most important design rule you'll learn in this project:** *routes are thin.* A route function should validate input, call a service, and return a serialized response — nothing clever. All real logic lives in services. This keeps your code testable and your routes readable.

## 1.5 Dependency Injection (FastAPI's superpower)

FastAPI lets you declare "things this endpoint needs" as **dependencies** — functions that run before the endpoint and can provide values to it.

```text
GET /patients/me
   └── depends(get_db)             → yields a DB session
   └── depends(get_current_user)   → verifies JWT, returns the User
```

Why this matters:

- **Reusability** — every protected route reuses the same auth dependency.
- **Testability** — in tests you can *override* dependencies (e.g., swap the real DB for a test DB) without touching route code.
- **Separation** — the "how do I get the user?" logic lives in one place, not in 40 routes.

You will write three foundational dependencies: `get_db` (session), `get_current_user` (JWT → User), and role checkers built on top (Phase 9).

## 1.6 The Layered Architecture for This Project

```
Client
   ↓  HTTP/JSON
FastAPI (routers)              ← API layer: routing, auth wiring, serialization
   ↓
Dependencies / Authentication  ← get_db, get_current_user, role guards
   ↓
Service Layer                  ← business rules, orchestration, transactions
   ↓
Repository / Data Access       ← optional; for the MVP, services talk to SQLAlchemy directly
   ↓
SQLAlchemy ORM                 ← models ↔ tables
   ↓
PostgreSQL (Supabase)
```

**AI functionality is separated from the core:**

```
FastAPI
   │
   ├── Core Application          (auth, users, patients, doctors, appointments)
   ├── Document Services         (upload, validation, storage, extraction queue)
   └── AI Services
            ├── Medical Report Analyzer   (document → structured analysis)
            └── AI Health Assistant       (chat sessions, RAG, safety)
```

**Why separate AI?** AI calls are slow, flaky, and expensive. If AI code is tangled into route handlers, a slow model call blocks or corrupts a simple request, and you can't test the AI independently. Isolation lets you: mock AI in tests, retry on failure, swap providers, and add human review — without touching the API layer.

## 1.7 Is a Repository Layer Actually Useful for This MVP?

**Honest answer: mostly no — start without it.**

A repository layer (a class per entity wrapping all queries) earns its keep when you need to:

- Swap storage backends (Postgres → another DB) without touching services
- Unit-test services with mocked repositories
- Reuse identical complex queries in many places
- Enforce a data-access policy in one spot

For this MVP you have **one** database, a small entity set, and most queries are simple and used once. A repository layer would be ~150 extra files of indirection with zero payoff. **Start with services calling SQLAlchemy directly.**

When should you introduce repositories? When a service accumulates messy queries, when you begin mocking DB access in unit tests, or when the entity set grows past ~10 models. The guide's structure still includes a `repositories/` note in the folder layout — you may keep it empty or delete it. **Architecture should follow need, not fashion.** Revisit in Phase 26.

## 1.8 Authentication Layer (preview)

Authentication is a *cross-cutting* concern, not a feature: almost every route needs it.

```
Login (email + password)
   ↓ verify password hash
   ↓ issue JWT (access token, short-lived)
   ↓
Every subsequent request:  Authorization: Bearer <token>
   ↓
get_current_user dependency decodes the token → loads the user → done
```

Full treatment in Phase 8. For now, just internalize that **auth is a dependency**, applied to routes, not logic scattered inside them.

### ✅ Verify Your Work (Phase 1)

- [ ] You can trace a request through all layers by hand (draw it).
- [ ] You can explain the difference between 401 and 403.
- [ ] You can explain why routes should be thin and logic should live in services.
- [ ] You can explain why a repository layer is optional for this MVP.

---

# Phase 2 — Development Environment

**Goal of this phase:** a reproducible Python environment with every tool installed and understood. No application code yet.

## 2.1 Decide Your Python Version First

Use **Python 3.11 or 3.12** (3.12 is the safe recommendation in 2026). Do **not** adopt the newest Python release on day one of a serious project — library wheels and your OS tooling need a beat to catch up. If you have multiple Python versions installed, learn to pin one per project: that is exactly what a virtual environment is for.

## 2.2 Virtual Environments (why they exist)

A virtual environment (`.venv`) is a private copy of Python plus an isolated package directory for **one project**. Without it, `pip install fastapi` would install into your *global* Python, where projects collide: project A needs `sqlalchemy==2.0`, project B needs `1.4`, and the global install can only hold one.

**Create and activate it inside your project folder:**

```bash
python -m venv .venv
# Windows (bash):
source .venv/Scripts/activate
# macOS/Linux:
source .venv/bin/activate
```

**What to verify:** `which python` should now point inside `.venv`, and `pip list` should be nearly empty. This is your project's private world. Also: **never commit `.venv` to git** — it is machine-specific and regenerable (see `.gitignore` in 2.6).

## 2.3 Dependency Management: requirements.txt vs pyproject.toml

Two options, pick one and be consistent:

| Approach | What it is | When to use it |
| -------- | ---------- | -------------- |
| `requirements.txt` | A flat list of packages for `pip install -r requirements.txt` | Simplest; fine for this MVP and most students |
| `pyproject.toml` + `uv`/`poetry` | Declarative project metadata + a lock file | When you want locked, reproducible installs and publishing tooling |

**Recommendation:** start with `requirements.txt`. It keeps the mental overhead low while you learn. If you later deploy with Docker, a `requirements.txt` is all Docker needs. (A lock file is the *real* win of the fancy tools — if you try `uv`, its `uv.lock` does this for you.)

**Pin philosophy:** install latest, then pin what works:

```bash
pip install fastapi uvicorn sqlalchemy alembic psycopg pydantic pydantic-settings
pip freeze > requirements.txt   # pins exact working versions
```

`pip freeze` writes exact versions (`fastapi==0.115.x`). For an MVP, exact pins are fine and make failures reproducible. Later you may loosen to `>=` ranges once you trust the stack.

## 2.4 What Each Dependency Is For (know your stack)

| Package | Role | Why you need it |
| ------- | ---- | --------------- |
| `fastapi` | The web framework | Handles routing, validation wiring, OpenAPI generation |
| `uvicorn` | ASGI server | Actually serves your app over HTTP (`uvicorn app.main:app --reload`) |
| `pydantic` | Validation & serialization | Schemas for request bodies, responses, settings |
| `pydantic-settings` | Config loading | Reads `.env` into typed settings objects |
| `sqlalchemy` | ORM | Python classes ↔ PostgreSQL tables |
| `alembic` | Migrations | Version-controlled schema changes |
| `psycopg` (v3) | Postgres driver | The bridge SQLAlchemy uses to talk to PostgreSQL |
| `python-multipart` | File uploads | Needed for `UploadFile` / form parsing |
| `email-validator` | Email validation | Powers Pydantic's `EmailStr` type |
| `bcrypt` | Password hashing | Secure password storage (see Phase 8) |
| `PyJWT` | JWT creation/verification | Access + refresh tokens |
| `httpx` + `pytest` | Testing | `TestClient` needs httpx; pytest runs tests |

> **Why not `passlib`?** The classic tutorial library is largely unmaintained and conflicts with modern `bcrypt` releases. In 2026 the clean choices are: call `bcrypt` directly (simple, reliable), or use `pwdlib` (modern, recommended by FastAPI's own templates). This guide uses `bcrypt` directly — fewer moving parts.

> **Why `psycopg` v3 and not `psycopg2`?** v3 is the actively maintained successor with better typing, better async support, and it installs cleanly on modern Python. psycopg2 is in maintenance mode.

## 2.5 FastAPI + Uvicorn: the Development Server

Uvicorn is what makes your FastAPI app reachable over HTTP. The workflow you'll repeat all project:

```bash
uvicorn app.main:app --reload
```

That command says: *"load `app` from `app/main.py`, run the `app` object, and restart on file changes."* `--reload` is for development only — never in production (Phase 25).

**Verify the server before writing a single route:** a bare `FastAPI()` instance should start, and `GET /` should 404 (no routes yet) while `/docs` shows the empty Swagger UI. If you cannot start an empty app, adding routes will only compound the problem — this is your first "fail early" checkpoint.

## 2.6 .gitignore (non-negotiable)

Before the first commit, create `.gitignore` with at minimum:

```gitignore
.venv/
__pycache__/
*.pyc
.env
.env.*
!.env.example
.DS_Store
.pytest_cache/
.mypy_cache/
*.db
```

**The `*.env` rules are the important ones.** Phase 3 explains why secrets in git are a real incident, not a theoretical one.

## 2.7 Project Folder Structure (design it before coding)

Design your structure as a plan, then adapt as you learn. A sound starting point:

```text
backend/
├── app/
│   ├── main.py              # app factory, middleware, router registration
│   ├── core/                # settings, security (hashing/JWT), logging
│   ├── db/                  # engine, session, Base
│   ├── models/              # SQLAlchemy models (1 file per entity or domain)
│   ├── schemas/             # Pydantic request/response models
│   ├── api/                 # routers (auth, patients, doctors, ...)
│   ├── services/            # business logic
│   ├── ai/                  # AI analyzer + assistant (isolated)
│   ├── storage/             # object-storage wrapper (file uploads)
│   ├── middleware/          # request logging, CORS config lives here or in main
│   └── utils/               # small shared helpers
├── tests/                   # pytest suite
├── alembic/                 # migrations (generated)
├── .env                     # local secrets (gitignored)
├── .env.example             # documented template (committed)
├── requirements.txt
└── README.md
```

**Why each directory exists, and what must NOT go inside it:**

| Directory | Belongs | Never put here |
| --------- | ------- | -------------- |
| `core/` | Settings, security helpers, logging setup | Database sessions, route logic |
| `db/` | Engine, `SessionLocal`, `Base` | Model classes, business rules |
| `models/` | SQLAlchemy classes only | Pydantic schemas, queries |
| `schemas/` | Pydantic classes only | SQLAlchemy classes, logic |
| `api/` | Routers + dependencies wiring | SQL, business rules, AI calls |
| `services/` | Business logic, transactions | HTTP concerns, schemas |
| `ai/` | LLM calls, prompts, structured outputs | Direct DB writes, auth |

**How modules communicate (the dependency rule):**

```text
api (routers) ───▶ services ───▶ db/models
     │                 │
     └── schemas ──────┘
     └── core (settings, security)
```

Rules of thumb: **routers may import services, schemas, core, and dependencies — never models directly in route bodies.** **Services may import models, db, core — never routers.** Schemas import nothing app-internal. This one-way flow is what keeps the codebase navigable as it grows.

**How it evolves later:** when you add a queue worker (Phase 15) or a second service (notifications), they sit *beside* the API layer and import services — the arrow direction never reverses. That is the whole game.

### ✅ Verify Your Work (Phase 2)

- [ ] `python --version` prints 3.11+ **from inside** the activated `.venv`.
- [ ] `pip freeze` shows a sane set of pinned versions.
- [ ] An empty FastAPI app starts with `uvicorn app.main:app --reload` and `/docs` renders.
- [ ] `.gitignore` exists and `.env` is ignored (test: `git status` shows no `.env`).
- [ ] You can explain what each top-level directory in `app/` is *for*, and what it must not contain.

---

# Phase 3 — Cloud PostgreSQL Setup

**Goal of this phase:** a real, cloud-hosted PostgreSQL database your backend connects to, configured entirely through environment variables. By the end, a raw SQL query from your machine (or a tiny Python script) reaches your cloud database.

## 3.1 Why PostgreSQL

- **Relational integrity:** foreign keys, unique constraints, transactions — exactly what healthcare data (appointments, patient↔doctor links) needs.
- **Powerful and standard:** the de-facto open-source relational database; skills transfer everywhere.
- **Rich types & extensions:** JSONB, arrays, and (later, for RAG) `pgvector` for embeddings.
- **Maturity:** 30+ years of battle testing; Supabase, Neon, RDS, and most cloud platforms offer it.

**Why a cloud database and not local PostgreSQL?** Because the final product is a *deployed* system: a cloud database is reachable from your local dev machine *and* from your deployed server with the same URL. You develop against exactly what you'll run in production, and you never learn the painful lesson of "works on my machine" at deployment time.

**Why not SQLite for this project?** SQLite is a fantastic embedded library, but: it is a single file with no network access (each server can't share it), it has weak support for concurrent writes, it lacks real role-based access, and — critically — **it isn't what you'll deploy**. This project exists to teach the real shape of backend engineering. Use the real thing.

## 3.2 Provider Choice

**Recommendation: Supabase.** It gives you a free-tier PostgreSQL, a friendly dashboard, object storage (Phase 18), and (if you ever want it) auth helpers — one account covers most of this MVP's infrastructure.

**Alternatives worth knowing:** Neon (serverless Postgres with branching — great for preview databases), Tiger Cloud, Railway, or a plain AWS RDS. Supabase wins for a beginner because the dashboard and docs are the smoothest onboarding. The good news: because you connect through a standard PostgreSQL URL, **switching providers later is mostly a string change.**

## 3.3 Creating the Project and Obtaining the Connection String

Walk through the Supabase dashboard once, carefully:

1. **Create an account and a project.** Choose a region close to you, set a strong database password, and *save it somewhere safe* (a password manager).
2. **Open Project Settings → Database** (or click the **Connect** button on the project overview).
3. **Copy the connection string.** Supabase shows several tabs. For a long-running server (your FastAPI backend on a VM/container), the guidance in 2026 is:

| Connection | Host / Port | Use when |
| ---------- | ----------- | -------- |
| **Direct** | `db.<ref>.supabase.co:5432` | Your server supports IPv6 (most modern VMs/containers do) |
| **Pooler – Session mode** | `<region>.pooler.supabase.com:5432` | Your host is IPv4-only |
| **Pooler – Transaction mode** | `<region>.pooler.supabase.com:6543` | Serverless/short-lived processes only |

   The connection string looks like:

```text
postgresql://postgres.<ref>:<password>@aws-0-<region>.pooler.supabase.com:5432/postgres?sslmode=require
```

   Or the direct form:

```text
postgresql://postgres.<ref>:<password>@db.<ref>.supabase.co:5432/postgres
```

   **Percent-encode special characters in your password** (`@` → `%40`, `#` → `%23`, `/` → `%2F`). The `?sslmode=require` fragment is optional with psycopg v3 (SSL is negotiated by default) but harmless and explicit.

> 🧭 **Decision point — which endpoint?** For a *normal, always-on FastAPI server*, prefer the **direct** connection (or session-mode pooler if your host is IPv4-only). Transaction mode (6543) disables prepared statements and is designed for serverless functions — it will bite you later if you pick it now.

## 3.4 Connection Pooling (what it is, why it matters)

Every database connection is a resource: network socket + server-side process + memory. Opening one per request is wasteful; holding one open per user doesn't scale. **Connection pooling** reuses a small set of live connections across many requests.

```text
Application
     ↓
Database URL
     ↓
SQLAlchemy Engine   ← creates a pool of N reusable connections
     ↓
Connection Pool     ← checked out per request, returned after
     ↓
PostgreSQL
```

SQLAlchemy gives you pooling for free through the **Engine**. You configure it with a few numbers — `pool_size` and `max_overflow` — sized to your load (e.g., 5 + 10 for an MVP). The two layers here:

- **Your app's pool (SQLAlchemy):** controls how many connections *your process* holds.
- **The provider's pool (Supavisor):** sits in front of the database when you use pooler endpoints.

You don't need deep pool tuning for an MVP — just know the knob exists and what it controls. A common mistake is setting an enormous pool size and exhausting the provider's connection limit; for a student project, keep it small.

## 3.5 Environment Variables: .env and .env.example

Secrets do not belong in code. The standard pattern:

- **`.env`** — your real values, **gitignored**, only on your machine (and later, injected by the deployment platform).
- **`.env.example`** — a committed template with placeholder values, so teammates (and future-you) know *which* variables exist.

```dotenv
# .env.example (committed)
DATABASE_URL=postgresql://postgres.<ref>:<password>@aws-0-<region>.pooler.supabase.com:5432/postgres?sslmode=require
JWT_SECRET=change-me-in-production
JWT_ALGORITHM=HS256
ACCESS_TOKEN_EXPIRE_MINUTES=30
REFRESH_TOKEN_EXPIRE_DAYS=7
CORS_ORIGINS=http://localhost:5173
```

In Phase 23 you'll formalize this with Pydantic Settings. For now: **create `.env`, copy it to `.env.example` with fake values, and verify `git status` ignores `.env`.**

## 3.6 Why Credentials Must Never Be Committed to GitHub

Three real reasons, from least to most important:

1. **It's permanent.** GitHub history keeps deleted secrets forever. Rotating a leaked key doesn't remove the leak.
2. **Bots scan for it.** Automated crawlers hunt for `postgres://`, AWS keys, and API keys in public repos within *minutes* of a push — your free database will be mined, spammed, or held for ransom.
3. **It's a compliance and trust issue.** For healthcare data, leaking credentials isn't just embarrassing — it's a reportable event with real consequences.

**Habit to build now:** before any commit, ask *"does this file reference a real password or key?"* If yes, it does not belong in git.

## 3.7 Prove the Connection Works

Before wiring SQLAlchemy, prove the endpoint, credentials, and SSL work with the raw driver. Write a tiny throwaway script:

```python
# scratch_test_db.py (delete after)
import psycopg
import os
url = os.environ["DATABASE_URL"]
with psycopg.connect(url) as conn:
    print(conn.execute("SELECT version();").fetchone())
```

Run it with the env var set (or after loading `.env`). What you should see: a PostgreSQL version string, e.g. `('PostgreSQL 15.x on x86_64-pc-linux-gnu ...',)`.

### ✅ Verify Your Work (Phase 3)

- [ ] You can connect to Supabase from your machine with a raw `psycopg` query.
- [ ] `git status` confirms `.env` is untracked and `.env.example` is tracked.
- [ ] You can explain what a connection pool is and why the engine owns it.
- [ ] You understand *which* Supabase endpoint you chose (direct vs pooler) and why.

---

# Phase 4 — Database Architecture

**Goal of this phase:** design the schema *before* any model code. A schema is a contract — it's far cheaper to change a diagram than a migrated production table. You will make the design decisions here; Phase 6 turns them into SQLAlchemy models.

## 4.1 Two Principles Before the Entities

1. **Design for time, not for the snapshot.** Health metrics, appointment status, and document state all *change over time*. Store what changes as rows with timestamps (time-series), not as single overwritten columns.
2. **Metadata in PostgreSQL, files elsewhere.** Never store a 10 MB PDF inside a database row. Store a *reference* to it (Phase 18).

## 4.2 The Entity Set

Here is the entity set for the MVP, with the decisions each one forces you to make. **Read each row and make the decision before moving on** — this is your schema design exercise.

### Users

| Field | Type | Notes / decision |
| ----- | ---- | ---------------- |
| `id` | UUID or bigint | **Decision:** UUIDs are safer for healthcare (no enumerable IDs — see BOLA in Phase 22) and merge-friendly; bigint is simpler. Recommendation: **UUID**.
| `full_name` | text | |
| `email` | text | **Unique + indexed.** This is your login identifier.
| `password_hash` | text | Never the raw password. Phase 8.
| `role` | enum (PATIENT, DOCTOR, MANAGEMENT, ADMIN) | **Decision:** store as a native Postgres enum or as text + app-level validation? Recommendation for MVP: text + Pydantic enum validation — avoids migration headaches, still safe. |
| `status` | active / inactive | Lets you disable accounts without deleting data.
| `created_at`, `updated_at` | timestamptz | Every table gets these. |

### Patient (extends User)

One-to-one with User. Contains clinical-adjacent identity data:

- `date_of_birth`, `gender` (offer a safe, non-binary set or free text — your call)
- `phone`, `address` (contact)
- `emergency_contact_name`, `emergency_contact_phone`
- `blood_group` (helpful for the health profile)

**Decision point:** do you store patient fields on the `users` table or a separate `patients` table? **Separate table.** Doctors and admins aren't patients; mixing clinical fields into a shared users table pollutes it with nulls and muddies permissions.

### Doctor (extends User)

- `specialization` (cardiology, general, ...)
- `license_number` (professional identifier — unique)
- `department_id` (FK → departments)
- `bio` / `years_of_experience` optional

### Department

- `name` (unique), `description`, `head_doctor_id` (optional FK to doctors)

### MedicalHistory

- `patient_id` (FK), `condition_name`, `diagnosed_date`, `status` (active/resolved), `notes`
- One patient → many history records. **Decision:** free-text condition names (simple) vs a curated condition catalog (accurate, more work). MVP: free text + status.

### Allergy

- `patient_id`, `allergen`, `severity` (mild/moderate/severe), `reaction`, `notes`

### HealthMetric (time-series — the important design)

| Field | Type | Notes |
| ----- | ---- | ----- |
| `patient_id` | FK | |
| `metric_type` | enum/text | blood_pressure, heart_rate, blood_glucose, weight, height, temperature, oxygen_saturation, bmi |
| `value` | numeric | Raw reading |
| `unit` | text | mg/dL, bpm, kg, °C, % |
| `recorded_at` | timestamptz | When the reading was taken |
| `notes` | text | optional |

**Why this shape?** One row per *reading* means a patient can have hundreds of blood-pressure rows over months — which is exactly what a trend chart needs. Never store `current_bp` as a single column. **Decision:** store systolic/diastolic as two rows sharing a timestamp (simple) or as a JSONB payload (compact). MVP: keep it flat and explicit.

### MedicalDocument

Metadata only — the file lives in object storage (Phase 15/18):

- `patient_id`, `document_type` (lab report, prescription, scan, ...)
- `original_filename`, `stored_object_key` (the storage reference)
- `file_size_bytes`, `content_type`
- `uploaded_at`, `uploaded_by`
- `processing_status` (pending / processing / completed / failed)
- `analysis` → link to the AI analysis result (Phase 16)

### Appointment

- `patient_id`, `doctor_id`, `department_id` (denormalized convenience — decision: keep or derive?)
- `scheduled_at` (timestamptz), `duration_minutes`
- `status`: requested / confirmed / completed / cancelled / no_show
- `reason`, `notes`
- **Decision:** who can cancel? Can a doctor reschedule? These become service rules in Phase 11–13.

### Prescription (optional stretch)

- `patient_id`, `doctor_id`, `medication_name`, `dosage`, `instructions`, `prescribed_at`, `valid_until`
- **Decision:** include or cut. It's cheap to design, and it rounds out the doctor module. **Recommendation:** design it now, implement it *after* the core modules are done (it's listed as a stretch in the Phase 0 boundary).

### AuditLog

- `user_id`, `action` (created/updated/accessed/deleted), `resource_type`, `resource_id`, `details` (JSONB), `ip_address`, `created_at`
- **Why healthcare needs auditability:** medical records are sensitive; you must be able to answer *"who looked at what, when, and why"* — for patient trust, for dispute resolution, and because it is legally required in most jurisdictions. The audit log is append-only: never update or delete rows.

## 4.3 Object Storage (why files don't live in Postgres)

A database is built for *querying structured data*, not for serving large binary blobs. Storing a 10 MB PDF in a row bloats backups, slows queries, and wastes money. **Object storage** (Supabase Storage, S3, R2) is purpose-built for files: cheap, scalable, and it serves downloads with signed URLs. The pattern:

```text
PostgreSQL                         Object Storage
   MedicalDocument table               /bucket/patient-42/uuid.pdf
   (metadata + object key)  ─────▶     (the actual bytes)
```

Your database holds a *pointer* (the object key). Phase 18 covers access control for those pointers.

### ✅ Verify Your Work (Phase 4)

- [ ] You have a written/drawn list of every table with its key fields.
- [ ] You made and can justify each 🧭 decision: UUID vs bigint, role storage, separate patients/doctors tables, time-series metrics, prescriptions in/out.
- [ ] You can explain why files are stored outside the database.
- [ ] You can explain what an audit log is for.

---

# Phase 5 — Database Relationships

**Goal of this phase:** learn to *read and design* relational structure. This is where your schema goes from a list of tables to a connected graph.

## 5.1 The Relationship Map

```text
User
 │
 ├──(1:1)── Patient
 │            │
 │            ├──(1:N)── MedicalHistory
 │            ├──(1:N)── Allergy
 │            ├──(1:N)── HealthMetric
 │            ├──(1:N)── MedicalDocument
 │            ├──(1:N)── Appointment (as patient)
 │            └──(1:N)── Prescription (as patient)   [stretch]
 │
 └──(1:1)── Doctor
              │
              ├──(N:1)── Department
              ├──(1:N)── Appointment (as doctor)
              └──(1:N)── Prescription (as doctor)    [stretch]

Department ──(1:N)── Doctor
AuditLog ──(N:1)── User (who did the action)
```

## 5.2 Relationship Types (with the vocabulary you'll need)

| Type | Meaning | Example | How it's stored |
| ---- | ------- | ------- | --------------- |
| **One-to-one (1:1)** | Each row relates to at most one other row | User ↔ Patient | Foreign key on one side (usually with `unique=True`) |
| **One-to-many (1:N)** | One parent, many children | Patient → HealthMetric | Foreign key on the *child* (many side) |
| **Many-to-many (N:M)** | Many on both sides | (Future: Doctor ↔ Patient *shared care*) | **Association table** with two foreign keys |

**Where is the foreign key?** This is the question that trips everyone up. The rule: **the many side carries the foreign key.** An appointment belongs to one patient → `appointments.patient_id`. A department has many doctors → `doctors.department_id`. If you get this backwards, your queries become awkward and your cascade rules break.

## 5.3 Foreign Keys, Cascades, and What They Cost You

- **Foreign key (FK):** a column that references a parent row's primary key. The database *enforces* that the referenced row exists — you cannot create an appointment for patient 999 if no such patient exists.
- **Cascades:** what happens to children when a parent is deleted.
  - `CASCADE` — delete children too (dangerous for medical data!).
  - `RESTRICT`/`NO ACTION` — refuse to delete the parent while children exist.
  - `SET NULL` — children keep existing but lose the link.
  - **Recommendation for healthcare:** avoid hard `CASCADE` on clinical data. A deleted user should typically *soft-delete* (mark inactive) or have children `SET NULL`. You rarely want to silently destroy medical history.

> **Thinking question:** a patient has 50 health metrics. If you delete the patient, what should happen to the metrics? If your answer is "keep them or mark them, never silently destroy them," you've got the healthcare instinct already.

## 5.4 Indexes, Unique Constraints, Nullable, Timestamps

| Concept | What it does | Where you need it here |
| ------- | ------------ | ---------------------- |
| **Index** | Speeds up lookups/filters on a column | `users.email`, `appointments.patient_id`, `health_metrics(patient_id, recorded_at)`, `appointments.doctor_id` |
| **Unique constraint** | Only one row may have that value | `users.email`, `doctors.license_number`, `departments.name` |
| **Nullable** | Column may be empty | Patient's `date_of_birth` optional? `appointments.notes` optional — but `patient_id` never null |
| **Timestamps** | `created_at`, `updated_at` | Convention: every table. Use `timestamptz` (timezone-aware) — healthcare data across time zones demands it |

**The `(patient_id, recorded_at)` composite index** is a great example of indexing for a real query pattern: "show me this patient's glucose readings over time" hits both columns.

**Nullable discipline:** a column is nullable only when *missing* is a valid state, not a lazy default. Every FK column in a required relationship should be `NOT NULL` — the database should *enforce* your integrity, not hope.

## 5.5 Design the Schema Yourself (checklist before Phase 6)

Draw each table with columns, types, nullability, keys, and indexes. For each, decide:

- [ ] Primary key type (UUID vs bigint) and who generates it (app vs DB)
- [ ] Which columns are **unique** and which need **indexes** (and composite ones?)
- [ ] Every foreign key and its **cascade behavior**
- [ ] Every **nullable** column and why
- [ ] Timestamps on every table, and who sets them (`server_default` vs app)
- [ ] For status fields: which states exist and which transitions are legal
- [ ] How **soft delete** works if you use it (a `deleted_at` or `status` column) — do you need it for the MVP? (Recommendation: a `status` on users is enough; full soft-delete is Phase 26 polish)
- [ ] Whether audit log rows can ever be updated (they cannot)

**Do not start Phase 6 until this drawing exists and you can defend every FK and every null.**

### ✅ Verify Your Work (Phase 5)

- [ ] You can identify which side of each relationship holds the foreign key and why.
- [ ] You chose a cascade policy per relationship and can justify it.
- [ ] Your schema drawing includes indexes for the queries you know you'll run.
- [ ] You can explain the difference between a unique constraint and an index.

---

# Phase 6 — SQLAlchemy Models

**Goal of this phase:** turn your Phase 5 schema drawing into SQLAlchemy 2.0 models. By the end, every table you designed exists as a Python class, and `Base.metadata` can create/migrate it.

## 6.1 The Two Things a Model Does

A SQLAlchemy model class is a **bridge**: it describes the table (columns, types, constraints) *and* gives you Python objects that map to rows. You write it once, and then:

```python
patient = Patient(full_name="Ayesha Khan")   # a Python object
session.add(patient); session.commit()        # becomes a row
```

## 6.2 What You Must Implement (per model)

For **every** model you designed, implement and be able to explain these six things:

1. **Purpose** — one sentence on what rows in this table represent.
2. **Fields** — each column, with the correct SQLAlchemy type (`String`, `Integer`/`BigInteger`, `Numeric`, `DateTime`, `Boolean`, `Text`, `JSONB`, `Uuid`).
3. **Data types** — why each type; `timestamptz` for times (`DateTime(timezone=True)`), `Numeric` for measurements (never `Float` for clinical values — floating point is approximate).
4. **Constraints** — `primary_key`, `unique`, `nullable=False`, `CheckConstraint` where it adds safety.
5. **Relationships** — `ForeignKey` on the many side + `relationship()` for convenient traversal; keep `lazy` behavior explicit.
6. **Indexes** — `index=True` for lookup columns, `Index(...)` for composites.

Plus two things your table design didn't capture:

7. **Security considerations** — which fields on this model are *sensitive* and therefore must be filtered in responses (Phase 10/19). `password_hash` is the canonical example.
8. **`__repr__`** — a safe, readable string representation for debugging that **never prints sensitive fields**. (A `__repr__` that prints `password_hash` into logs is a data leak you will regret.)

## 6.3 Base and Shared Columns

Create one `Base(DeclarativeBase)` with a **naming convention** so Alembic autogenerate produces stable constraint names (see Code Reference §4 for the exact pattern). Then build a small `TimestampMixin` or a `TimeStampedBase` that provides `created_at`/`updated_at` with `server_default=func.now()` — every model inherits it. This is a classic DRY win.

## 6.4 The Models You'll Write (in dependency order)

Write them in this order because each depends on the previous:

1. **User** — the foundation. Includes `password_hash`; **never expose it in schemas**. Role as an enum.
2. **Department** — `name` unique; referenced by Doctor.
3. **Doctor** — FK to `departments`, unique `license_number`.
4. **Patient** — FK to `users` (one-to-one).
5. **MedicalHistory**, **Allergy** — FK to patients.
6. **HealthMetric** — FK to patients + `recorded_at`; the time-series design from Phase 4.
7. **Appointment** — FKs to patient, doctor, department; status column.
8. **MedicalDocument** — FK to patient + `stored_object_key` + `processing_status`.
9. **AuditLog** — FK to user (nullable — system actions have no user); JSONB `details`.
10. **Prescription** *(stretch)* — FKs to patient and doctor.

## 6.5 Relationships: `back_populates` and the Golden Rules

When two models are linked by FKs, wire both sides with `relationship()` and `back_populates` so navigation works in both directions (`patient.health_metrics` and `metric.patient`). Golden rules:

- **Declare the FK on the many side**, mirror the relationship on both sides.
- **Never store lists in columns** — a `List[float]` column is a relational smell; use child rows.
- **Watch out for lazy loading surprises**: with a sync session, accessing `patient.health_metrics` after the session closes raises `DetachedInstanceError`. Learn this now — it will visit you in Phase 10.
- **Be deliberate with `cascade`** — per your Phase 5 decisions. Defaults are rarely what healthcare needs.

## 6.6 The Classic Beginner Bugs in This Phase

- Putting the FK on the wrong side (Phase 5 will save you).
- Forgetting `nullable=False` and letting the DB accept junk.
- Using `Float` for clinical measurements.
- Forgetting `unique=True` on email/license and discovering duplicate accounts later.
- No indexes on FK columns → slow joins as data grows.
- Exposing `password_hash` through a schema (Phase 10 guardrail).

### ✅ Verify Your Work (Phase 6)

- [ ] Every table from your Phase 5 drawing exists as a model.
- [ ] You can print each model's `__table__` columns and explain each one.
- [ ] `Base.metadata.create_all(engine)` runs against your local/cloud Postgres without error.
- [ ] Creating a User and a related Patient row works, and the relationship navigates both ways **inside** an open session.
- [ ] You can explain why `Float` is wrong for clinical values.

---

# Phase 7 — Alembic Migrations

**Goal of this phase:** version-controlled schema changes. From here on, your schema changes are *code*, reviewable and reversible — never random `ALTER TABLE` commands you type into a console.

## 7.1 Why Migrations Exist

Your database schema will evolve (add a column, change a type, add a table). Without migrations, every developer and every environment (local, staging, prod) evolves differently and drifts apart. **Migrations are git for your schema**: each change is a numbered, reviewable script, applied in order.

```text
model changes → alembic revision --autogenerate → migration file → alembic upgrade head
```

## 7.2 The Migration Workflow (your daily rhythm)

1. Change a model (e.g., add `notes` to `Appointment`).
2. `alembic revision --autogenerate -m "add notes to appointments"` — Alembic diffs your models against the live database and drafts a migration.
3. **Review the generated file.** Autogenerate is a draft, not gospel. It frequently misses or over-captures things (indexes, enum changes, server defaults).
4. `alembic upgrade head` — apply it.
5. Test that the app still works against the new schema.
6. Commit both the model change and the migration together.

## 7.3 The Critical Rules

- **Never hand-edit the live database.** Direct `ALTER TABLE` in production bypasses version control: the migration history and the real schema drift apart, and no one can reproduce the state. If it's not in a migration, it doesn't exist.
- **Migrations are one-way tickets most of the time.** `alembic downgrade` exists, but downgrades of data-heavy changes (dropping a column with data) are often lossy. Get into the habit of *reviewing* before *applying*.
- **Autogenerate needs a live database** to diff against — it compares models to the *current schema*, so `upgrade head` must be run against a database whose state matches your migration history.
- **Never edit an already-applied migration.** Create a new one. Editing history = broken history.
- **Keep migrations small and focused** so they're reviewable and failures are easy to localize.

## 7.4 Decisions You Must Make Here

- **Who owns timestamps?** If `created_at` has `server_default=func.now()` in the model, Alembic carries that into the migration. Keep the source of truth in the migration, and let the DB set timestamps (`server_default`), not the app.
- **Enums:** if you used native PG enums, autogenerate's handling is imperfect — plan to hand-review enum migrations. (Another reason the guide recommends text + app-level validation for MVP roles/statuses.)
- **Dev vs prod:** run `upgrade head` automatically in CI/deploy for prod; locally, just run it. Never run `downgrade` in prod without a plan.

## 7.5 The "Database Out of Sync" Failure (know it now)

You'll hit it: `alembic upgrade head` claims nothing to do, or autogenerate produces a no-op when it shouldn't, or the app errors with "column does not exist." Cause: migration history and real schema disagree — usually because someone edited the DB by hand or a migration was edited after apply. The debugging path is Phase 7 of the Troubleshooting section at the end of this guide.

### ✅ Verify Your Work (Phase 7)

- [ ] `alembic upgrade head` applies cleanly and `alembic current` shows your latest revision.
- [ ] A schema change (add a column) flows through: model → autogenerate → reviewed migration → `upgrade head` → confirmed with a `\d` psql query or `alembic history`.
- [ ] You can run `alembic downgrade -1` and then `upgrade head` again to see reversibility on your *dev* database.
- [ ] You can explain why hand-editing the production database is dangerous.

---

# Phase 8 — Authentication

**Goal of this phase:** users can register and log in, and protected routes can identify them. Authentication answers **"who are you?"**

## 8.1 The Full Authentication Flow

```text
Registration
    ↓ password validation (length, strength)
    ↓ password hashing (never stored raw)
    ↓ user creation (role assigned)
Login
    ↓ password verification (hash comparison)
    ↓ issue JWT (access token + refresh token)
Authenticated requests
    ↓ Authorization: Bearer <token>
    ↓ dependency decodes token → loads user → route proceeds
```

## 8.2 Password Hashing (and why salting matters)

**Never store passwords.** Store a *one-way hash*: a deterministic-but-irreversible digest computed with a deliberately slow algorithm. On login you hash the candidate password and compare hashes — you never need the original.

**Salt** is random data mixed into the password *before* hashing, making each hash unique even for identical passwords. Why it matters: without salts, two users with password `123456` produce identical hashes (and precomputed "rainbow tables" crack them trivially); with salts, each hash is unique and rainbow tables are useless.

Use `bcrypt` directly (per Phase 2): it handles salting internally and is deliberately slow — that slowness is the security. Rules: **never write your own hashing, never use MD5/SHA1, never store plaintext even "temporarily".**

## 8.3 JWT: What a Token Actually Is

A JWT is a compact, signed data package: `header.payload.signature`. The payload contains **claims** (facts about the token), and the signature proves the token was issued by *you* (your server holds the secret).

Your access-token payload should carry at minimum:

- `sub` — the user ID (standard subject claim)
- `role` — the user's role (speeds up authorization; still verify against the DB)
- `type` — `access` vs `refresh`
- `iat` — issued at
- `exp` — expiration (required; a token without expiry is a permanent key)
- `jti` — unique token ID (lets you revoke a specific token later, if you build a denylist)

**Do not put sensitive medical data in tokens.** Tokens are signed, not encrypted — anyone can read the payload. Base64-decoding a token reveals everything inside.

## 8.4 Access Tokens vs Refresh Tokens

| | Access token | Refresh token |
| --- | ------------ | ------------- |
| Lifetime | Short (15–30 min) | Longer (7–30 days) |
| Sent with | Every request (`Authorization: Bearer`) | Only the `/auth/refresh` call |
| Purpose | Proves identity now | Obtains a *new* access token when one expires |

**Why two tokens?** If a 30-day token is stolen, the thief has 30 days of access. If a 30-minute token is stolen, the damage window is small. The refresh token — the long-lived one — should be stored more carefully (client-side, e.g., httpOnly cookie or secure storage) and can be rotated or revoked server-side.

## 8.5 The Authentication Dependency

Every protected route declares:

```text
current_user: User = Depends(get_current_user)
```

The dependency: extracts the `Authorization: Bearer <token>` header → decodes the JWT → validates `exp` and `type` → loads the user from the DB → returns them (or raises 401). Because it's a dependency, Swagger gets a working **Authorize** button and every route reuses the same hardened logic. Build this dependency **first** and test it with raw curl before building any business route.

## 8.6 Logout Considerations

Stateless JWTs can't be "logged out" server-side without extra machinery. Options, in increasing order of effort:

1. **Client discards the token** — simplest; token remains valid until expiry. Fine for an MVP.
2. **Server-side denylist of revoked `jti`s** — a `token_blacklist` table checked by the auth dependency. Revocation on logout, real.
3. **Short access + rotated refresh with a stored hash** — proper session management. Overkill for the MVP; note it for later.

**Decision:** start with (1) + short access tokens; add (2) only if the product asks for it.

### ✅ Verify Your Work (Phase 8)

- [ ] Register creates a user whose stored password is a bcrypt hash (inspect the row — you should *not* see the plaintext).
- [ ] Login returns an access token that contains your claims when decoded (use jwt.io locally, never paste production tokens into web tools).
- [ ] `/auth/me` (or equivalent) returns the current user with a valid token.
- [ ] Requests without a token get **401**; requests with a garbage token get **401**.
- [ ] An expired token gets **401** (test by minting a token with `exp` in the past).
- [ ] No endpoint returns `password_hash` anywhere in its response.

---

# Phase 9 — Role-Based Access Control (RBAC)

**Goal of this phase:** decide *what each role may do*, then enforce it in code. Authorization answers **"what are you allowed to do?"**

## 9.1 Authentication vs Authorization (say it until it's automatic)

- **Authentication** = identity. *"The token is valid; I know you are user 42."*
- **Authorization** = permission. *"User 42 is a DOCTOR, and only doctors may list patients."*

Auth says *who you are*; authz says *what you can do*. **Both are mandatory and independent.** A perfectly authenticated patient must still be denied a doctor's endpoint (403).

## 9.2 The Permission Matrix

Implement these permissions exactly. This table is your contract with the frontend.

### PATIENT

| Can | Cannot |
| --- | ------ |
| View/update own profile & permitted personal info | View any other patient's data |
| View own medical history, allergies, metrics, reports | View hospital analytics |
| Upload own documents | Modify doctors, departments, roles |
| View own appointments, request appointments | Change role or status of any user |
| Use the AI assistant (own data only) | |

### DOCTOR

| Can | Cannot |
| --- | ------ |
| View *assigned* patients (list, search, profile) | Change system roles |
| View authorized medical info (history, metrics, docs, analyses) | Access unrelated patients (no authorization link) |
| Manage appointments (confirm/reschedule/complete) | View audit logs or analytics |
| Add clinical notes / prescriptions (stretch) | Modify patients' personal identity data |

### MANAGEMENT

| Can | Cannot |
| --- | ------ |
| Manage patients, doctors, departments, appointments | Change roles / system config |
| View operational analytics | Access raw clinical detail beyond what management screens need |

### ADMIN

| Can | Cannot |
| --- | ------ |
| Manage users & roles | (nothing inside the system — highest privilege, but audited) |
| Manage system configuration | |
| View audit logs | |

## 9.3 Two Authorization Layers (you need both)

1. **Role-level checks** — "is this user a DOCTOR?" via a `require_roles(...)` dependency. Protects endpoints. Fast, coarse.
2. **Object-level checks** — "is this *specific patient* one this doctor is allowed to see?" Inside the service, per request. Slow-ish, fine-grained, **mandatory**. Role-level checks alone are the #1 security hole in student projects (Phase 22's BOLA).

```text
GET /patients/42
   → require_roles(DOCTOR, MANAGEMENT, ADMIN)   [role layer]
   → is doctor assigned to patient 42?           [object layer]
   → if not: 403
```

## 9.4 Roles as Code: Keep the Matrix Testable

Define roles as a Python `enum` + permission helpers, so the matrix is *data* you can unit-test ("patient cannot call doctor endpoints") rather than scattered `if role == ...` in every route. The Code Reference (§8) shows the dependency pattern.

### ✅ Verify Your Work (Phase 9)

- [ ] A PATIENT calling a DOCTOR endpoint gets **403** (not 401, not 200).
- [ ] A DOCTOR can list patients; a PATIENT cannot.
- [ ] An ADMIN can reach admin endpoints; everyone else gets 403.
- [ ] A doctor attempting to open an *unassigned* patient's profile gets **403** (object-level check working).
- [ ] You can state the difference between authentication and authorization without looking.

---

# Phase 10 — API Design

**Goal of this phase:** design every endpoint *before* implementing, so the surface is consistent, complete, and securable. Each endpoint is specified by eight things (see 10.3) — fill them in as you plan.

## 10.1 The API Planning Table

This is your master contract. Extend it with every endpoint you add, keeping the column format. (This is *not* exhaustive — build it out as you design each module.)

| Module | Method | Endpoint | Role | Purpose |
| ------ | ------ | -------- | ---- | ------- |
| Auth | POST | `/auth/register` | Public | Register a patient account |
| Auth | POST | `/auth/login` | Public | Exchange credentials for tokens |
| Auth | POST | `/auth/refresh` | Authenticated | New access token from refresh token |
| Auth | GET | `/auth/me` | Authenticated | Current user + role |
| Patient | GET | `/patients/me` | Patient | Own profile |
| Patient | PATCH | `/patients/me` | Patient | Update permitted fields |
| Patient | GET | `/patients/{id}` | Authorized | Patient profile (doctor/management/admin) |
| Patient | GET | `/patients` | Doctor+ | List/search patients |
| History | GET/POST | `/patients/{id}/history` | Authorized | Read/add medical history |
| Allergy | GET/POST | `/patients/{id}/allergies` | Authorized | Read/add allergies |
| Metrics | GET/POST | `/patients/{id}/metrics` | Authorized | Read/add health metric readings |
| Documents | POST | `/patients/{id}/documents` | Authorized | Upload a document |
| Documents | GET | `/patients/{id}/documents` | Authorized | List document metadata |
| Documents | GET | `/documents/{id}/download` | Authorized | Get a signed download URL |
| Documents | GET | `/documents/{id}/analysis` | Authorized | View AI analysis |
| Appointments | POST | `/appointments` | Patient | Request an appointment |
| Appointments | GET | `/appointments` | Authorized | List own (patient) / assigned (doctor) / all (management) |
| Appointments | PATCH | `/appointments/{id}` | Doctor+ | Update status (confirm/cancel/complete) |
| AI | POST | `/chat/sessions` | Patient | Start a chat session |
| AI | POST | `/chat/sessions/{id}/messages` | Patient | Send a message |
| Admin | GET/PATCH | `/admin/users` | Admin | List/update users & roles |
| Admin | GET | `/admin/audit-logs` | Admin | Read audit trail |
| Management | GET | `/management/analytics` | Management+ | Operational aggregates |

## 10.2 Resource URL Design Principles

- **Nouns, not verbs:** `/patients/42` not `/getPatient`. (Exceptions for actions: `/auth/login`.)
- **Hierarchies for owned sub-resources:** `/patients/42/metrics` says "metrics belonging to patient 42" — and it *forces* you to check ownership of patient 42.
- **`/me` for the current user's own resources:** `/patients/me` avoids clients guessing their own ID — a small but real BOLA defense.
- **Plural nouns, consistent casing, no trailing slashes.**

## 10.3 Specify Every Endpoint with Eight Items

For each row in your planning table, write down (mentally or in a design doc):

1. **Input** — path params, query params, request body schema.
2. **Validation** — which Pydantic schema, what rules (e.g., `scheduled_at` must be in the future).
3. **Authentication** — which token requirement.
4. **Authorization** — role check *and* object-level check (whose resource is this?).
5. **Business logic** — rules in the service (e.g., only own documents may be downloaded).
6. **Database operation** — what's read/written, what's audited.
7. **Response** — the exact response schema (never the raw model — see 10.4).
8. **Error conditions** — every 4xx/5xx this endpoint can produce and why.

## 10.4 The Golden Rule: Never Return Raw ORM Models

A route must **never** return a SQLAlchemy object directly. Always return a **Pydantic response schema**. Three reasons:

1. **Security:** schemas whitelist fields — you can't accidentally leak `password_hash` or internal fields.
2. **Stability:** the API contract doesn't change when your model internals change.
3. **Control:** you decide exactly what the client sees (e.g., a doctor's view of a patient may include clinical data; a patient's own view may include less or more).

This is why `schemas/` and `models/` are separate directories: they are *different layers of the same resource*.

### ✅ Verify Your Work (Phase 10)

- [ ] Your planning table covers every feature in Phase 0's scope.
- [ ] For 5 sample endpoints, you can answer all eight specification items.
- [ ] No planned endpoint returns a raw ORM object.
- [ ] URL design follows the noun/hierarchy/`me` principles.

---

# Phase 11 — Patient Module

**Goal of this phase:** every patient-facing feature, implemented one layer at a time. This is where the architecture from Phase 1 becomes real code.

## 11.1 The Layer Template (repeat for every sub-module)

```text
Database  →  Model  →  Schema  →  Service  →  Router  →  API
```

| Layer | Responsibility | What NOT to put here |
| ----- | -------------- | -------------------- |
| Model | Table definition | Business rules, validation |
| Schema | Request/response contracts | SQL, logic |
| Service | Business rules, ownership checks, transactions, audit calls | HTTP details, raw SQL |
| Router | HTTP wiring, dependencies, serialization | Business logic |

Implement in this order: model (Phase 6) → schema → service → router → test. **Never write a router first and invent the rest around it.**

## 11.2 Patient Profile

- `GET /patients/me` returns the current patient's profile. Service: load user + patient row; **never let a client pass an ID to fetch their own profile** (the `me` pattern again).
- `PATCH /patients/me` — **field-level permission decision:** which fields may a patient change themselves (phone, address, emergency contact) vs which require staff (date of birth after verification)? Decide and enforce in the service. A common cheat is accepting the whole user model and saving everything — that's how patients end up editing their own roles.

## 11.3 Health Profile (blood group, height baseline, etc.)

Decide what "health profile" means in your schema (baseline info stored on `patients`, vs metrics which are time-series). Keep static baseline info on the patient row; keep readings in `health_metrics`. This split is a design decision from Phase 4 — revisit it here and be consistent.

## 11.4 Medical History & Allergies

- Both are simple child resources: `GET/POST /patients/{id}/history`, `GET/POST /patients/{id}/allergies`.
- **Ownership check on every read/write**: is `{id}` the current patient (`/me` equivalent) or a patient this doctor is authorized for? Both routes share a *service-level* guard — write it once, use everywhere (this is the object-level authorization layer from Phase 9).
- For POSTs, the service assigns `patient_id` from the authorized patient — **never trust a `patient_id` in the request body** (classic BOLA vector).

## 11.5 Health Metrics

- `POST` a single reading (type, value, unit, recorded_at) or a batch.
- `GET` returns readings filtered by type and date range, ordered by `recorded_at` — the time-series design pays off here.
- **Validation decisions:** range checks per metric type (blood pressure can't be 0 or 5000), unit consistency. Pydantic can enforce much of this; a service-level guard for cross-field rules.

## 11.6 Medical Documents

- Upload endpoint validates the file (Phase 15), stores it (Phase 18), records metadata, and kicks off analysis.
- Patients upload; the response is the **metadata record**, never the binary.
- **List** returns metadata only — document *contents* require a download flow (signed URL, Phase 18).

## 11.7 Appointments

- Patient requests an appointment: `POST /appointments` with doctor, department, time, reason. **Validation:** future time, doctor exists, doctor is in that department.
- Status is a state machine: `requested → confirmed → completed` or `requested → cancelled`. **Enforce legal transitions in the service** — a patient shouldn't be able to set `confirmed` themselves (that's the doctor's action), and nobody can resurrect a cancelled appointment. Encode transitions as a table in code.
- Patient views their own appointments; **the list endpoint must filter by the authenticated user**, not accept a `patient_id` param.

## 11.8 AI Health Assistant

- Patient creates a session, sends a message, receives a response. The AI service (Phase 17) is *injected* into the chat service — the router never touches the LLM directly.
- **Boundary:** assistant responses must cite sources and include medical disclaimers; the service validates and sanitizes AI output before storing.

### ✅ Verify Your Work (Phase 11)

- [ ] A patient can complete the full self-serve workflow end-to-end via curl/TestClient: profile → history → allergies → metrics → document upload → appointment request → chat message.
- [ ] Every patient endpoint 403s for another patient and 401s for anonymous calls.
- [ ] A patient cannot create a metric/history/document *for another patient* by tampering with the URL or body.
- [ ] Appointment status transitions follow your state machine (illegal transitions rejected).
- [ ] No patient endpoint leaks another patient's data.

---

# Phase 12 — Doctor Module

**Goal of this phase:** the doctor's workspace — with *strict* authorization boundaries. This is the phase where most student projects fail security, so pay close attention to 12.3.

## 12.1 What to Build

- **Patient list & search** — `GET /patients?search=...&department=...` — returns only *assigned* patients.
- **Patient profile** — full authorized view: history, allergies, metrics, documents, analyses.
- **Medical reports** — view analysis results and download documents.
- **Appointment management** — confirm, reschedule, complete, cancel.
- **Clinical notes** — add notes to a patient record (and prescriptions, if you took the stretch).

## 12.2 The Assignment Concept

A doctor sees a patient because there is a **link** between them: the patient booked an appointment with them, or the patient is assigned to them. Decide how "assignment" works in your data model:

- **Simple:** doctor sees patients they have (past or upcoming) appointments with.
- **Explicit:** a `doctor_patients` association table (many-to-many) for ongoing care.

**Recommendation:** start with appointments-based access (no new table), and note that an explicit assignment table is the natural upgrade — the queries in the service are written behind one function (`can_doctor_access_patient`) so the rule can change in one place.

## 12.3 Authorization Boundaries (the heart of this phase)

**The trap:** "I'm an authenticated DOCTOR, so I can query any patient." No. The backend must prove a specific link between this doctor and this patient **on every request**:

```text
GET /patients/{id}/metrics
   ↓ authenticate (who are you?)
   ↓ role check (are you a doctor?)
   ↓ OBJECT CHECK: does patient {id} link to you?  ← the part students skip
       → appointment exists? assignment exists?
       → no → 403 Forbidden
   ↓ proceed
```

Implement this as a **reusable service function** (e.g., `authorize_patient_access(db, doctor, patient_id)`), because it's needed by *every* doctor endpoint. If the rule ever changes, it changes in one place. Never copy-paste the check into each router.

## 12.4 Clinical Notes (and audit)

Notes are sensitive free text. Requirements:

- Write path: doctor adds/edits notes — restricted to authorized doctors.
- Read path: authorized doctors only; patients see notes *if you decide they should* (product decision — note it).
- **Audit note access and edits** (Phase 20): "Dr. X read patient Y's notes at 14:03" is exactly what an audit log is for.

## 12.5 Doctor List & Search Performance

Search over patient name/department should hit an **indexed** query (`ILIKE` with care, or full-text search as a stretch). For the MVP, a simple indexed prefix search is fine; keep the service boundary so you can upgrade to Postgres full-text later without touching the API.

### ✅ Verify Your Work (Phase 12)

- [ ] A doctor sees **only** linked patients in the list.
- [ ] A doctor gets **403** on an unlinked patient's profile, history, metrics, docs, notes.
- [ ] A doctor can manage appointments (confirm/complete) — and a patient cannot.
- [ ] Note edits and profile views appear in the audit log.
- [ ] You can explain, in one sentence, why role-level auth alone is insufficient here.

---

# Phase 13 — Management Module

**Goal of this phase:** operational administration — the "hospital back office" view.

## 13.1 What to Build

- **Patient management:** list all patients (with search), view profiles, deactivate accounts.
- **Doctor management:** create/edit doctors, assign departments, activate/deactivate.
- **Department management:** CRUD departments, list doctors per department.
- **Appointment management:** view all appointments, resolve conflicts (the state machine still applies).
- **Analytics:** operational aggregates (see 13.3).

## 13.2 Clinical Data vs Operational Data (the key distinction)

| | Clinical data | Operational data |
| --- | ------------- | ---------------- |
| Examples | History, allergies, metrics, document *contents*, notes | Appointment counts, department loads, user counts, statuses |
| Who sees it | Patients (own), authorized doctors, admin as needed | Management, admin |
| Sensitivity | Highest | Lower (but still private) |

**Design principle:** management screens need *operational* views — how many appointments per department, how many doctors per department, how many active patients. They do **not** need raw clinical notes. Your analytics endpoints should **aggregate, never dump**. Return counts/trends, not patient rows. This keeps management's data access minimal (least privilege from Phase 0).

## 13.3 Analytics: Aggregate in the Database, Not in Python

Write analytics queries as SQL aggregation (`COUNT`, `GROUP BY`, date-bucketed `COUNT` with `date_trunc`), executed through SQLAlchemy, returning compact summaries. Fetching 10,000 appointment rows into Python to count them by hand is the anti-pattern. Examples:

- Appointments per department this month
- Appointments per status (requested/confirmed/completed/cancelled)
- Active patients & doctors per department
- Average wait days from request to confirmation

### ✅ Verify Your Work (Phase 13)

- [ ] Management can list/search patients and doctors and manage departments.
- [ ] Analytics endpoints return aggregates (counts/trends), not raw clinical rows.
- [ ] A patient or doctor gets 403 on management endpoints.
- [ ] You can state the difference between clinical and operational data with examples.

---

# Phase 14 — Admin Module

**Goal of this phase:** the highest-privilege surface — users, roles, configuration, audit — and its protection.

## 14.1 What to Build

- **User management:** list users, change status (activate/deactivate), **change roles**.
- **Role management:** roles are code (an enum); admin assigns roles to users. (Full "create custom roles" is out of MVP scope — roles are fixed, assignment is admin-controlled.)
- **System configuration:** a small `settings` store (e.g., a `SystemSetting` table with key/value, or env-driven for static config). Keep it minimal.
- **Audit logs:** read-only viewer with filters (user, action, date range).

## 14.2 Protecting Privileged Endpoints

Three layers, all required:

1. **Role dependency** — `require_roles(ADMIN)` on every admin router.
2. **Defense in depth** — even with the role guard, admin services still load the acting user and verify, and every admin action is **audited** (who changed whose role, when). Privilege without audit is invisible power.
3. **No privilege escalation paths** — the role-change service must refuse to modify `ADMIN` users by non-admins (obviously) and should *guard against an admin locking themselves out* (e.g., cannot deactivate your own account or demote the last admin — a classic self-inflicted outage).

## 14.3 Why Role Management Is Code, Not Data

If roles were rows in a table, any admin UI bug could create a role with arbitrary permissions. Fixed roles + enum + permission matrix (Phase 9) means permissions are *compiled into* the code and testable. Custom roles are a Phase 26+ feature — note it, don't build it.

### ✅ Verify Your Work (Phase 14)

- [ ] Admin endpoints are 403 for every non-admin role (test all three).
- [ ] Role changes and deactivations appear in the audit log with actor + target.
- [ ] An admin cannot deactivate their own account or demote the last admin (test it).
- [ ] Audit log viewer returns filtered, read-only data.

---

# Phase 15 — Medical Document System

**Goal of this phase:** a safe, asynchronous pipeline that takes a patient's uploaded file and turns it into stored metadata + analysis-ready text. AI comes in Phase 16; here you build the plumbing.

## 15.1 The Pipeline

```text
Patient Upload
     ↓
File Validation        (type, size, magic bytes)
     ↓
Storage               (object storage, private bucket)
     ↓
Document Metadata     (PostgreSQL row: pending)
     ↓
Processing Queue      (background job)
     ↓
Text Extraction       (PDF/OCR → text)
     ↓
AI Analysis           (Phase 16)
     ↓
Stored Result         (analysis row + status: completed/failed)
```

## 15.2 File Validation (before anything else)

- **Size limit:** reject over a cap (e.g., 10 MB) with 413 or 400 *before* reading the whole file into memory — stream in chunks.
- **Type validation:** check the declared content type *and* the file's actual magic bytes. Never trust a filename or a client-declared MIME type — a `.pdf` label can hide anything.
- **Secure filenames:** never store the client's filename as the storage key. Generate your own key (UUID + safe extension) — this defeats path traversal (`../../etc/passwd`) and duplicate collisions in one move. Keep the original name *only* as metadata.
- **Whitelist:** accept a small set (PDF, PNG, JPEG, maybe DOCX) and reject the rest.

## 15.3 Storage and Metadata (the split from Phase 4)

- File bytes → object storage in a **private** bucket, keyed by generated name: `patient-{id}/{uuid}.pdf` (per-patient prefix = easy access control later).
- Metadata → `medical_documents` row: patient, type, original filename, object key, size, content type, `processing_status`, timestamps, uploader.
- **Never store the binary in PostgreSQL. Never upload to a public bucket.**

## 15.4 Processing States (design the state machine)

```text
pending → processing → completed
                │
                └──────→ failed   (with error message, retryable)
```

- `failed` must carry *why* (validation failure, extraction failure, AI failure) so it's diagnosable.
- **Decision:** is retry manual or automatic? MVP: manual "retry" button that resets to `pending` and requeues.

## 15.5 Asynchronous Processing (the queue decision)

AI analysis takes seconds to minutes — you cannot block the HTTP response. Options, simplest first:

| Option | How it works | Verdict for MVP |
| ------ | ------------ | --------------- |
| **FastAPI `BackgroundTasks`** | Runs after the response is sent, in-process | Fine for learning; dies with the process, no retries |
| **A simple worker + queue table** | `pending` rows claimed by a polling worker | Still simple, survives restarts, retryable — good middle ground |
| **Celery/ARQ/RQ** | Full job queue with brokers | The "real" production answer; adds Redis and operational weight |

**Recommendation:** implement with a worker that polls for `pending` documents (or `BackgroundTasks` first, then migrate). The important part is the *status column* — your API already communicates progress to the frontend through it, regardless of the queue technology underneath.

## 15.6 Text Extraction (bridge to AI)

Convert the file to plain text: PDF text extraction (`pypdf`), OCR for scans (e.g., `pytesseract`/Tesseract — note: heavy dependency, install decision), DOCX via `python-docx`. Extraction is **unreliable** — assume partial/failed extraction is normal and record it in the failed state with a useful message.

### ✅ Verify Your Work (Phase 15)

- [ ] Uploading a valid PDF creates a metadata row (pending) and the file lands in the private bucket.
- [ ] Oversized / wrong-type files are rejected before storage.
- [ ] A document with a malicious filename stores under a generated key (test with `../../evil.pdf`).
- [ ] The pipeline ends at `completed` with extracted text, or at `failed` with a stored reason.
- [ ] The upload endpoint returns in < 1s (processing is async, not inline).

---

# Phase 16 — AI Medical Report Analyzer

**Goal of this phase:** a *separated, controlled* AI service that turns extracted document text into structured analysis. Safety-first by design.

## 16.1 Where AI Belongs in the Architecture

```text
Medical Document
     ↓
Text Extraction        (Phase 15)
     ↓
Cleaning              (trim, length caps, PII caution)
     ↓
Chunking              (long texts → manageable pieces)
     ↓
[Embedding / Retrieval — only if you add RAG here]
     ↓
LLM                   (via AIService — the only file that calls the model)
     ↓
Structured Analysis   (Pydantic-validated output)
     ↓
Database              (analysis row linked to the document)
```

## 16.2 Why AI Must Not Be Mixed Into API Routes

AI calls are slow (seconds), unreliable (timeouts, malformed JSON, hallucinations), and **expensive**. If the route handler calls the LLM directly:

- A slow model stalls the request; a failure 500s the whole upload.
- You can't test business logic without paying for real API calls.
- You can't swap providers or add human review without rewriting routes.

So: **one `AIService` abstraction** owns all model calls. Routes/services depend on an interface; tests inject a fake. (Code Reference §16 shows the pattern — provider config via env, `base_url` configurable.)

## 16.3 Structured Outputs (the anti-hallucination lever you control)

Ask the model for **structured JSON**, not free prose, and validate it with Pydantic before storing:

```text
LLM response → parse into Pydantic model → reject if invalid → store validated result
```

- Define an `AnalysisResult` schema: summary, key findings (list), flagged abnormalities, suggested questions for a doctor, confidence (optional), extracted values.
- **Never store raw LLM output.** If it doesn't parse into the schema, mark the analysis `failed` and keep the raw text for debugging (with care).

## 16.4 Prompt Management & Model Failure Handling

- **Prompts are code:** keep them in a `prompts.py` (or templates), versioned, reviewed — not string-soup inside the service. Include system instructions that define the assistant's role, scope limits, and output format.
- **Handle failure modes explicitly:** timeout → retry once then mark failed; invalid JSON → one repair attempt then fail; model/API unavailable → clear error message, not a silent empty result. Each maps to a document `failed` state (Phase 15.4).

## 16.5 Hallucination, Attribution, and Human Review

- **Hallucination risk is real and unavoidable.** Mitigations: constrain output format, forbid the model from *inventing* values not in the text, and require it to flag uncertainty. **Source attribution:** every finding should reference where it came from ("appears in Section 2 of the report") so a human can verify.
- **Human review:** the system is decision *support*. Add a `review_status` on analysis (e.g., `unreviewed / reviewed / disputed`) and let a doctor mark findings as reviewed or flag errors. This turns an AI feature into a *workflow* feature — and it's what makes the feature defensible.
- **Positioning:** every analysis response carries a visible disclaimer that this is assistance/information, not a diagnosis.

## 16.6 The Safety Contract (paste this into your prompt design)

1. Summarize and structure *what the text says*; do not extrapolate diagnoses.
2. Never invent findings absent from the source; mark uncertainty explicitly.
3. Recommend professional consultation for anything abnormal or unclear.
4. Output must conform to the JSON schema; no markdown, no extra prose.

### ✅ Verify Your Work (Phase 16)

- [ ] A real upload completes the pipeline and stores a *validated* structured analysis.
- [ ] Feeding garbage text produces a valid (if empty) structured result or a clean `failed` state — never a crash.
- [ ] The route layer never imports the LLM client; only `AIService` calls it.
- [ ] With the AI mocked/faked, the whole pipeline still works and is testable.
- [ ] The response/UI copy explicitly says this is not a diagnosis.

---

# Phase 17 — AI Health Assistant

**Goal of this phase:** a *controlled* chat assistant — not a raw LLM bolted to a chat box. The difference is the entire point of this phase.

## 17.1 Why "user input → LLM" Is Wrong for Healthcare

A raw chat-to-LLM endpoint is dangerous in three ways:

1. **No context discipline** — the model doesn't know the patient's real data, so it either invents it or gives generic (and sometimes confidently wrong) advice.
2. **No safety rails** — nothing stops the model from diagnosing, giving dosing advice, or ignoring crises.
3. **No accountability** — no record of what was asked or answered, no citations, no human-escalation path.

The assistant must be a **pipeline with gates**, not a passthrough.

## 17.2 The Architecture

```text
Patient message
     ↓
Validate & sanitize input (length, content policy)
     ↓
Load context: chat history + patient profile + relevant document analyses
     ↓
[RAG retrieval — see 17.4]
     ↓
Prompt assembly: system instructions + safety rules + context + history + question
     ↓
LLM call (AIService — structured response)
     ↓
Validate & sanitize output (format, disclaimers, escalation flags)
     ↓
Store message pair + response metadata (citations, sources)
     ↓
Return response
```

## 17.3 Sessions, History, Context

- **ChatSession** (patient, created_at, status) and **ChatMessage** (session, role, content, citations JSONB, created_at) — tables from your Phase 4 design.
- **History window:** send recent messages (last N) to the model, with token budgeting for long sessions.
- **Context injection:** include *relevant* patient data — e.g., the latest analysis summaries — clearly labeled so the model knows what it's allowed to reference. **Never dump the entire medical record into every prompt** (cost, leakage, and the model will treat it all as equally authoritative).

## 17.4 RAG: Retrieval-Augmented Generation (understand it, keep it MVP-sized)

**The problem:** an LLM knows nothing about *this patient*. **The idea:** retrieve the most relevant pieces of *this patient's* data and feed them to the model as context, so answers are grounded in real records.

| Piece | MVP approach | Upgrade path |
| ----- | ------------ | ------------ |
| Document store | Stored extracted text of the patient's documents | — |
| Retrieval | Simple: latest analyses + keyword match on document text | Embeddings + `pgvector` similarity search |
| Citations | Response includes the source document/analysis IDs | Full source-quote mapping |

**RAG for the MVP = "fetch relevant context by patient, then prompt."** That's it. You don't need vector databases to learn the pattern; `pgvector` is a natural Phase 26 upgrade because you're already on Postgres.

## 17.5 Prompt Safety & Response Validation

- **System prompt rules (non-negotiable):** assist, inform, and support decisions; **never diagnose or prescribe**; escalate emergencies ("seek immediate care") rather than answer; stay within the provided context; flag uncertainty; cite sources.
- **Input gate:** block/limit obvious abuse (huge inputs, prompt-injection attempts disguised as system commands — treat *any* user text as untrusted data, never as instructions).
- **Output gate:** validate the structured response (Pydantic), require a `disclaimer_present` or append the standard disclaimer yourself, and detect escalation triggers (mention of emergency symptoms → the response must include a seek-care warning).

## 17.6 Citations, Disclaimers, Escalation

- **Citations:** response carries `source_ids` referencing the documents/analyses used. Store them; the frontend renders them as links. Uncited claims should not happen — if the model can't ground it, it must say so.
- **Disclaimers:** every response explains this is information support, not medical advice, and to consult a professional. The backend *enforces* this — never rely on the frontend to add it.
- **Escalation:** define trigger terms/patterns (chest pain, suicidal ideation, severe bleeding). On trigger: response includes urgent-care guidance and the system records an audit entry. Optionally notify a doctor (out of scope, but design the flag now).

### ✅ Verify Your Work (Phase 17)

- [ ] A chat response is stored with its citations; messages persist across a session.
- [ ] A question about *another* patient's data is refused (context = only this patient's data).
- [ ] The response always includes a disclaimer (enforced server-side, not just prompt-requested).
- [ ] Trigger inputs produce an escalation response and an audit log entry.
- [ ] An empty/failed LLM response degrades to a safe fallback message, not a crash.

---

# Phase 18 — Cloud Storage (Medical Documents)

**Goal of this phase:** files stored safely, served only to authorized users, and never publicly accessible.

## 18.1 The Storage Split (recap)

```text
PostgreSQL (metadata + object key)      Object Storage (the bytes)
   medical_documents row                   private bucket / patient-{id}/{uuid}.pdf
```

**Supabase Storage** (the natural fit with Supabase Postgres) or any S3-compatible service (R2, S3, MinIO). **Decision:** use Supabase Storage for the MVP — one provider, one dashboard, storage API is enough for uploads and signed URLs.

## 18.2 Private Buckets and Signed URLs

- **Private bucket, always.** Public buckets for medical documents are a data breach by default. The server writes via the storage API (service key — server-side only, never exposed to the client).
- **Signed URLs:** the client should *never* talk to storage directly. Your backend creates a short-lived signed URL (`GET /documents/{id}/download` returns one, valid for e.g. 15 minutes) that the frontend uses to fetch the file.
- **Expiration:** signed URLs expire. Short expiry = narrow theft window. Long-lived links are how "private" files become public.

## 18.3 Access Control (who may download what)

The signed URL is a *transport* mechanism, not an *authorization* mechanism. The authorization check happens in **your backend**, before the URL is issued:

```text
GET /documents/{id}/download
   → authenticate
   → load document metadata
   → is the requester the patient OR an authorized doctor/admin?
   → yes → issue 15-min signed URL → 200
   → no → 403
```

Same rule as everywhere else in this project: **check in the service, not in the URL.** Also enforce the *storage-level* rule with bucket policies per patient path if your provider supports it (defense in depth), but never rely on it alone.

## 18.4 Encryption and Safety

- **In transit:** HTTPS everywhere (Phase 22).
- **At rest:** object storage providers encrypt at rest by default — verify and note it; do not roll your own encryption.
- **Avoid public documents:** nothing medical ever lives in a public bucket, ever.
- **Deletion policy:** deleting a document = delete metadata *and* the object (or soft-delete metadata + keep the object per compliance — product decision). Decide and be consistent; a metadata row pointing at a deleted object is a broken download.

### ✅ Verify Your Work (Phase 18)

- [ ] Uploads land in a private bucket; the object URL is not directly reachable without a signed URL.
- [ ] `GET /documents/{id}/download` returns 403 for unauthorized users and a working signed URL for authorized ones.
- [ ] Expired signed URLs are rejected by storage (test after expiry window).
- [ ] The storage service key is server-side only (never in the frontend, never in git).

---

# Phase 19 — Error Handling

**Goal of this phase:** every failure mode has a predictable, documented HTTP response — and the frontend never has to guess.

## 19.1 The Error Taxonomy

| Failure | Status code | Meaning for the client |
| ------- | ----------- | ---------------------- |
| Validation | **422** | Input failed schema rules (Pydantic gives you this for free) |
| Authentication | **401** | Missing/invalid/expired token |
| Authorization | **403** | Valid user, insufficient permission |
| Not found | **404** | Resource doesn't exist — *or* exists but you're not allowed to know (see 19.3) |
| Conflict | **409** | State conflict: duplicate email, illegal appointment transition, already exists |
| Rate limited | **429** | Too many requests (Phase 22) |
| File problems | **400/413/415** | Bad file, too large, unsupported type |
| DB failure | **500** | Server-side; log details, return generic message |
| AI / processing failure | **503/500** or domain state | Model down → 503-ish; per-document failure → `failed` state on the record |
| Unexpected | **500** | Catch-all; must be logged with a trace ID |

## 19.2 One Consistent Error Shape

Define one error body so the frontend can handle errors uniformly:

```text
{ "detail": "human-readable message", "code": "APPOINTMENT_NOT_CONFIRMABLE", "field": "scheduled_at" }
```

- FastAPI's built-in `detail` is the baseline; extend it with a stable machine-readable `code`.
- **Never leak internals** (stack traces, SQL, library error text) to the client — 500 responses return a generic message; the detail goes to server logs with a trace ID.
- Register **exception handlers** for: `RequestValidationError` (format 422s consistently), your app error base class, and the generic `Exception` (500 + log + trace ID).

## 19.3 The 404-vs-403 Privacy Decision (healthcare-specific)

If patient 42's record doesn't exist, and you're *not* authorized to see it — should the API say 404 or 403?

- **404 for everyone** leaks nothing but reveals "this record exists or not" — a patient probing IDs learns nothing if unauthorized users always get 404.
- **403 for unauthorized** admits the record *exists*.

**Healthcare best practice:** for sensitive resources, unauthorized access returns **403 or a uniform 404** consistently. Decide once, document it, and apply it everywhere — inconsistency itself is an information leak (probing for behavior differences). Simplest safe rule for the MVP: **authorization failures → 403; nonexistent resources → 404; and never distinguish the two in a way that depends on whether the resource exists.**

## 19.4 A Domain Error Base Class

Create an `AppError` hierarchy (e.g., `NotFoundError`, `PermissionDeniedError`, `ConflictError`, `ValidationError`) raised by services and translated to status codes by an exception handler. This lets services say *what* went wrong in business language while HTTP translation happens in exactly one place.

### ✅ Verify Your Work (Phase 19)

- [ ] Every endpoint's error conditions are documented (Phase 10.3 item 8) and match actual behavior.
- [ ] 422s, 401s, 403s, 404s, 409s all return the consistent error shape.
- [ ] A forced 500 (throw in a service) returns a generic message + logged trace, not a stack trace.
- [ ] The 404/403 policy is documented and consistent across modules.

---

# Phase 20 — Logging & Auditing

**Goal of this phase:** two separate systems that students routinely confuse: *application logs* (diagnostics) and *audit logs* (accountability).

## 20.1 Application Logs vs Audit Logs

| | Application logs | Audit logs |
| --- | ---------------- | ---------- |
| Purpose | Debugging & operations | Accountability & compliance |
| Content | Requests, errors, slow queries, DB issues | *Who did what to which record, when* |
| Retention | Short (roll over) | Long, append-only, immutable-ish |
| Consumers | Developers, ops | Admins, auditors, regulators |
| Storage | stdout/file via logging (JSON) | Database table (Phase 4) |

Both matter. A crash without application logs is undebuggable; a security question without audit logs is unanswerable.

## 20.2 Structured Logging (application logs)

Configure `logging` **once** (in `core/logging.py`) to emit **JSON lines** — one JSON object per line — instead of ad-hoc `print()`s:

```text
{"ts": "...", "level": "ERROR", "logger": "app.services.appointments", "event": "status_transition_rejected", "appointment_id": 42, "from": "confirmed", "to": "requested"}
```

Why JSON: machines can filter/aggregate it; your future log platform will thank you. Include a **request ID** (middleware assigns one per request; it threads through logs) so you can trace one request across services. Add `logging` calls at meaningful points: request start/end, auth failures, service decisions, DB errors, AI calls.

## 20.3 What to Audit (and what NOT to log)

**Audit these healthcare-relevant actions:**

- Patient record access (who viewed which patient's record)
- Document access and downloads
- Record modifications (history, metrics, notes, profile)
- Role changes and user deactivation
- Login attempts (success *and* failure — brute-force detection)
- Administrative actions (config changes, user management)

**Never log:**

- Passwords or password hashes
- JWT secrets or tokens
- API keys / LLM keys / storage credentials
- Sensitive medical information *unnecessarily* (log that a record was read, not its contents; if you must log a summary, strip identifiers)

**Pattern:** a `log_audit(db, actor, action, resource_type, resource_id, details)` helper called from services at the decision point. The audit write is a normal DB insert in the same transaction where practical (or its own — decide: same-transaction = stronger guarantee, separate = survives partial failures).

### ✅ Verify Your Work (Phase 20)

- [ ] Application logs are JSON, carry a request ID, and appear for requests and errors.
- [ ] A patient-profile view by a doctor creates an audit row (actor, action, resource, time).
- [ ] A failed login is audited; a role change is audited.
- [ ] Searching logs for passwords/tokens/keys returns nothing.
- [ ] You can explain the difference between application logs and audit logs.

---

# Phase 21 — Testing

**Goal of this phase:** a test suite that grows *with* the project — not one written after everything "works." Tests are how you prove the security and safety claims of every earlier phase.

## 21.1 The Test Pyramid for This Project

| Layer | What it tests | Examples |
| ----- | ------------- | -------- |
| **Unit** | Business logic in isolation | Appointment state machine, permission matrix, password hashing, date validation |
| **Integration** | API + DB together | Every endpoint against a real test database |
| **Auth** | Token flows | Valid/invalid login, expired token, missing token |
| **Authorization** | Role + object-level rules | Patient A cannot reach Patient B; doctor blocked from unlinked patient |
| **API** | Contract + errors | Status codes, response shapes, error bodies, file uploads |

**Testing philosophy for this project:** integration tests dominate, because most of the value here is *permission boundaries*, which only exist when the full stack runs. Pure unit tests are for logic-heavy pieces (state machines, hash utilities, prompt builders).

## 21.2 The Test Database Strategy (protect production data, always)

- **Never run tests against your real (or production) database.**
- Use a **separate test database** (e.g., `healthai_test` on the same Supabase project, or a local Postgres).
- Set `DATABASE_URL` from `TEST_DATABASE_URL` in test fixtures; run migrations (`alembic upgrade head`) once per test session; truncate tables between tests (or roll back transactions).
- FastAPI's **dependency override** is the key tool: override `get_db` to yield sessions bound to the test engine. (Code Reference §18 shows the pattern.)
- **Cleanup:** drop the test schema after the run so state never leaks between runs.

## 21.3 The Tests You Must Have

**Auth:** valid login → tokens; invalid login → 401; expired token → 401; garbage token → 401; wrong password → 401.

**Authorization (the security tests that matter):**

```text
Patient A  ──▶ GET /patients/B/metrics  → 403
Doctor X   ──▶ GET /patients/{unlinked}/metrics  → 403
Patient    ──▶ POST /appointments  with patient_id of B  → 403 or ignored
Management ──▶ PATCH /admin/users  → 403
Anonymous  ──▶ GET /patients/me  → 401
```

**API:** every endpoint returns the documented status for: happy path, missing fields, wrong types, nonexistent IDs, and duplicate resources.

**State machines:** every illegal appointment/document-status transition is rejected.

## 21.4 Test Data Fixtures

Build small factories (or simple helper functions) that create a patient, a doctor, an admin, an appointment, a document — with distinct, memorable emails/IDs. Fixtures are *code*: one helper used by dozens of tests beats copying creation logic.

## 21.5 When You Can't Test: AI and Storage

- **Mock the AIService** (inject a fake returning canned structured output) — your pipeline tests never call a real LLM.
- **For storage**, test against the provider's test bucket, or abstract storage behind an interface and fake it. Decide once, document it.

### ✅ Verify Your Work (Phase 21)

- [ ] `pytest` runs green against the test database, with production data untouched.
- [ ] The authorization matrix from Phase 9 is encoded as tests — every "can/cannot" cell.
- [ ] Tests cover the 401/403 distinctions and the BOLA cases (Patient A → Patient B).
- [ ] AI/storage-dependent tests run with mocks/fakes, not real external calls.
- [ ] A failing permission check is caught by a test before it ships (add one on purpose to prove it fails).

---

# Phase 22 — Security

**Goal of this phase:** harden the app as you build it. For healthcare data, security isn't a phase at the end — it's a property of every layer. Treat every earlier "Verify Your Work" as a security check.

## 22.1 OWASP API Security Risks (your map)

The OWASP API Security Top 10 is the industry checklist for API flaws. The ones that matter most here, and where they're handled in this guide:

| Risk | What it is | Where this guide covers it |
| ---- | ---------- | -------------------------- |
| **BOLA / IDOR** (Broken Object Level Authorization) | Accessing another user's object by guessing IDs | 22.2 below — the most important item |
| Broken Authentication | Weak token/session handling | Phase 8 |
| Broken Object Property Level Authorization | Reading/writing fields you shouldn't (e.g., `role` in a PATCH body) | Phases 10–11 (whitelist schemas) |
| Unrestricted Resource Consumption | No limits on input size, rate, pagination | 22.5 (rate limits), Phase 15 (file caps) |
| Broken Function Level Authorization | Calling admin endpoints as a patient | Phase 9 (role dependencies) |
| Unrestricted Access to Sensitive Business Flows | e.g., unlimited appointment booking | Phase 11 + rate limits |
| Server-Side Request Forgery (SSRF) | Backend fetching attacker-controlled URLs | Avoid fetching user-supplied URLs; note in AI/storage integrations |
| Security Misconfiguration | Verbose errors, missing headers, open CORS | 22.4–22.6 |
| Improper Inventory Management | Stale endpoints, env differences | Phase 23 (env separation), Phase 25 (deployment) |
| Unsafe Consumption of APIs | Trusting third-party API responses (the LLM!) | Phases 16–17 (validate AI output) |

## 22.2 BOLA / IDOR — The #1 Hole in This Kind of App

**The flaw:** endpoints that trust the ID in the URL without checking who's asking.

```text
GET /patients/123   ← the mistake: "anyone with a valid JWT can read patient 123"
```

**The fix:** before touching data, verify that the requester is authorized for *that specific object*.

```text
GET /patients/123
  → authenticate → who are you?
  → role check → may this role view patients at all?
  → object check → may THIS user view patient 123?
        patient → 123 == me?
        doctor  → am I linked to patient 123?
        management/admin → yes (within scope)
  → fail any check → 403
```

**Why it happens:** developers implement authentication (everyone must log in), then assume that's enough. It isn't — BOLA is *authorization*, and it must be checked per resource. **The fixes are structural, not a single feature:**

1. Use `/patients/me` for self-service instead of accepting an ID (Phase 10).
2. Never trust IDs from the request body (`patient_id` in a POST body is attacker-controlled).
3. Centralize object-level checks in service functions (Phases 11–12) so no route "forgets" them.
4. Write the BOLA tests first (Phase 21) — Patient A vs Patient B is a test, not a feature.

**BOLA also applies to nested resources:** `GET /patients/42/documents/7` must check *both* that you may see patient 42 *and* that document 7 belongs to patient 42. Checking only the document ID is a classic nested-BOLA bug.

## 22.3 Authentication & Authorization Hardening (recap as security rules)

- **Password hashing:** bcrypt (or argon2); never plaintext, never your own scheme.
- **JWT security:** strong random secret from env (Phase 23); HS256 or better; always set `exp`, `iat`, `type`; keep payload free of sensitive data.
- **RBAC:** role checks at the router AND object checks at the service — role alone is never enough.
- **Input validation:** Pydantic everywhere; whitelist fields per role; never bind request bodies directly to models (a patient sending `role: ADMIN` in a PATCH must have it rejected or ignored — property-level authorization).
- **Never trust the frontend:** every check on the backend, every time. A hidden button isn't security.

## 22.4 Injection, Files, and Other Input Attacks

- **SQL injection:** SQLAlchemy parameterizes queries automatically — *if you never hand-build SQL strings with user input.* Rule: use the ORM and `text()` with bound parameters only; never `f"SELECT ... {user_input}"`. Same for `LIKE` filters (escape `%`/`_`).
- **NoSQL/other injection:** not applicable here (PostgreSQL), but the habit — treat input as data, never as code — carries everywhere.
- **File upload security (recap + hardening):** magic-byte validation, size caps, generated storage keys, private buckets, no executable extensions, and never serving files with `Content-Type` guessed from the client. Consider scanning as an enterprise feature (out of MVP scope — note it).
- **Path traversal:** never join user input into filesystem or object keys; keys are always generated server-side (Phase 15).
- **LLM prompt injection:** AI is now an input surface. Treat chat text as untrusted data, never instructions; isolate system prompts from user content; validate structured output (Phases 16–17).

## 22.5 Rate Limiting

Rate limiting protects the login endpoint (brute force) and the AI endpoints (cost blowups). Implement with a small library (e.g., `slowapi`) or a simple in-memory counter for an MVP:

- `/auth/login`: e.g., 5 attempts/minute/IP.
- Chat/AI endpoints: tighter per-user caps (LLM calls cost money — an unauthenticated loop is a bill, not a bug).
- Document upload: reasonable per-user cap.

Return **429** with a clear message when exceeded. For a real deployment, note that in-memory limits don't work across multiple server instances — use a shared store (Redis). MVP: in-memory is fine.

## 22.6 CORS, HTTPS, Headers, and Secrets

- **CORS:** allow only the origins your frontend actually uses (from env, Phase 23). `*` with credentials is never correct. CORS is a *browser* protection — it does not stop non-browser clients, so it is defense in depth, not authorization.
- **HTTPS:** always in production (your host provides it); never serve medical data over plain HTTP. In dev, localhost is fine.
- **Secure headers:** set `X-Content-Type-Options: nosniff`, `X-Frame-Options: DENY`, and a sensible `Content-Security-Policy` where applicable (middleware or proxy).
- **Secrets management:** everything in env vars (Phase 23); never in code, never in git; rotate on suspicion. Deployment platforms provide secret stores — use them.
- **Database security:** the DB password lives only in env; the database is reachable only over SSL; never expose the DB port publicly (Supabase handles network isolation — your *app* should be the only client; if self-hosting, firewall it).
- **Dependency vulnerabilities:** `pip-audit` (or Dependabot on GitHub) scans for known CVEs; run it regularly, not just at the end.
- **Data minimization:** store only what the MVP needs; don't collect or retain fields you never use. Less data = less to leak and less to audit.
- **Encryption:** HTTPS in transit; provider-managed encryption at rest (verify your provider's settings); never roll your own crypto.
- **Audit logs as security control:** they're both evidence and deterrent — and they're the first thing an investigation asks for.

## 22.7 The Security Review Ritual (do this before "done")

Walk every endpoint and answer: *who can reach it, what can they read/write, what if they change the ID, what if they add fields, what if they flood it?* The tests from Phase 21 encode the answers. If an endpoint can't be justified against the Phase 9 matrix, fix it now.

### ✅ Verify Your Work (Phase 22)

- [ ] BOLA test suite green: cross-patient access blocked at every object endpoint, including nested documents.
- [ ] A PATCH containing `role`/`status` tampering is ignored or rejected (property-level check).
- [ ] Login and AI endpoints are rate-limited (429 observed under burst).
- [ ] CORS reflects env-configured origins; no wildcard with credentials.
- [ ] `pip-audit` reports no known vulnerabilities in your pinned deps.
- [ ] Secrets grep test: no real keys/URLs in the repo (git history too).
- [ ] You can name three OWASP API risks this app specifically faces and where each is defended.

---

# Phase 23 — Environment Configuration

**Goal of this phase:** every environment variable is typed, documented, and never hardcoded.

## 23.1 What Belongs in Environment Variables

| Put in env (always) | Keep in code (never in env) |
| ------------------- | --------------------------- |
| `DATABASE_URL` | Table/column names |
| `JWT_SECRET` | Role names |
| `OPENAI_API_KEY` / LLM keys | Fixed business rules (e.g., "appointments must be in the future") |
| `SUPABASE_URL`, `SUPABASE_SERVICE_KEY` | Constants like token lifetimes *that never change per environment* (even these often go in env) |
| `CORS_ORIGINS` | — |
| `APP_ENV` / `DEBUG` | — |
| `LOG_LEVEL` | — |

**Rule:** if it differs between dev/test/prod, or if it's a credential, it's an env var. If it would be embarrassing in a screenshot of the repo, it's an env var.

## 23.2 Pydantic Settings: One Typed Object

Consolidate env access into a single `Settings` class (pydantic-settings) loaded from `.env`:

- Typed fields (`str`, `int`, `list[str]` for CORS origins) — typos in env names become startup errors, not runtime mysteries.
- `model_config = SettingsConfigDict(env_file=".env", extra="ignore")`.
- Access via a cached `get_settings()` dependency — import the instance, don't call it per-request.
- **Fail fast:** required secrets without defaults cause a clear startup error, so a missing `JWT_SECRET` fails *before* the server accepts traffic.

## 23.3 The Three Environments (and how they differ)

| Environment | Database | Secrets | Behavior |
| ----------- | -------- | ------- | -------- |
| **Development** | Dev DB (cloud or local) | Real dev values in `.env` | `--reload`, verbose logs |
| **Testing** | Separate `TEST_DATABASE_URL` | Test-only values | Fixtures manage schema; no prod data ever |
| **Production** | Prod DB | Injected by the platform's secret store | No reload, structured logs, real origins |

**Never share one database between testing and anything else; never let dev code touch production credentials.** If `DEBUG=True` accidentally ships, you'll find out why this separation exists.

### ✅ Verify Your Work (Phase 23)

- [ ] `get_settings()` returns typed values; missing required vars fail startup with a clear message.
- [ ] `.env` (real) vs `.env.example` (template) are kept in sync and `.env` is gitignored.
- [ ] Dev/test/prod each have their own database URL, and tests can never hit the dev DB by accident.
- [ ] No hardcoded credentials anywhere in `app/` (grep for `postgres://`, key names, etc.).

---

# Phase 24 — API Documentation

**Goal of this phase:** an API that a frontend developer can consume *without asking you*. FastAPI gives you OpenAPI + Swagger UI (`/docs`) and ReDoc (`/redoc`) for free — your job is to make that documentation *good*.

## 24.1 What FastAPI Gives You (and what you must add)

| Automatic | You must add |
| --------- | ------------ |
| Endpoint list, methods, paths | **Descriptions** per endpoint (`summary`, `description`) |
| Request/response schemas from Pydantic | **Field descriptions** and examples in schemas (`Field(description=..., examples=[...])`) |
| Auth scheme (declare `OAuth2PasswordBearer` → Authorize button) | **Error documentation** (which statuses, what bodies) |
| Status codes from `response_model` | **Tag organization** (`tags=["patients"]`) |
| Server URLs | **Example payloads** for every major request/response |

## 24.2 Documentation As a Contract

For every major endpoint, the OpenAPI spec should answer:

1. **Description** — one or two sentences: what it does, for whom.
2. **Authentication** — which roles may call it (visible via the Authorize button + tags).
3. **Request body** — schema with field descriptions and an example.
4. **Response** — response model, plus example.
5. **Errors** — documented statuses (401/403/404/409/422...) with the error shape from Phase 19.

**Write descriptions while coding, not at the end.** A route with a one-line docstring and a good example is documentation gold; a bare route is a support ticket.

## 24.3 Docs for the Frontend Team

- Keep response schemas *stable* — renaming fields breaks every frontend screen. Treat `/docs` as the contract the frontend codes against.
- Prefer explicit `response_model=` on every route (it also filters fields — the Phase 10 rule).
- Example payloads should use realistic (fake) data — it doubles as test fixtures.
- If the docs would embarrass you in front of a frontend dev, they're not done.

### ✅ Verify Your Work (Phase 24)

- [ ] `/docs` shows every endpoint with a summary, description, tags, and schemas.
- [ ] The Authorize button works against your login endpoint.
- [ ] Every major request/response has an example payload.
- [ ] A frontend developer (or future-you) could build a client from `/docs` alone.

---

# Phase 25 — Deployment

**Goal of this phase:** your backend running in the cloud, reachable over HTTPS, configured entirely through environment variables.

## 25.1 The Deployment Shape

```text
GitHub ──▶ Docker image ──▶ Cloud hosting (Render / Railway / Fly.io / VPS) ──▶ FastAPI ──▶ Cloud PostgreSQL (Supabase)
```

Your code lives in git; the platform builds a container, injects secrets, and runs it. **The same Docker image that runs locally must run in production** — that's the reproducibility guarantee.

## 25.2 Why the Dev Server Is Not Production

`uvicorn --reload` is a development convenience: it restarts on file changes and runs a single worker with debug-friendly behavior. Production needs:

- **Multiple workers** (`--workers N` or a process manager) — concurrency under real load.
- **No reload.**
- **A real reverse proxy / HTTPS** in front (platform-managed, or Caddy/Nginx on a VPS).
- **Proper logging** to stdout (JSON, Phase 20) so the platform collects it.
- **Health checks** the platform can ping.

## 25.3 The Dockerfile and Compose (what to get right)

- Base on a slim Python image; install from `requirements.txt`; copy only what's needed; run as a **non-root user** (containers default to root — a real security smell for a healthcare app).
- `CMD` runs uvicorn **without** `--reload`, with multiple workers, binding `0.0.0.0`.
- **Do not bake secrets into the image.** Inject at runtime via env vars / secrets.
- `docker-compose.yml` (for local/demo): app + optional Postgres service; **your real deployment still points `DATABASE_URL` at Supabase**, not the compose database.
- Health check endpoint: `GET /health` returns 200 when the app can reach the database (a lightweight `SELECT 1`). Platforms use it to restart unhealthy instances.

## 25.4 Choosing a Host (decision point)

| Option | Effort | Best for |
| ------ | ------ | -------- |
| **Render / Railway** | Low | Students: git-push deploy, managed HTTPS, easy env/secrets UI |
| **Fly.io** | Medium | More control, generous free tier, Docker-native |
| **VPS (DigitalOcean/etc.)** | High | Full control; you manage Nginx, systemd, HTTPS, updates — a great *learning* deployment, more work |

**Recommendation:** Render or Railway for the MVP. You'll learn containerized deploys without fighting infrastructure.

## 25.5 The Production Checklist (configuration)

- [ ] **Environment variables** injected by the platform (DB URL → prod Supabase, JWT secret — a *different* strong secret than dev, LLM key, storage keys, `CORS_ORIGINS` = the real frontend origin).
- [ ] **Production server:** multiple workers, no reload, health check wired.
- [ ] **Database:** prod database separate from dev/test; migrations run on deploy (carefully — Phase 7 rules apply).
- [ ] **CORS:** only the real frontend origin(s).
- [ ] **HTTPS:** enforced (platform default; redirect HTTP if a VPS).
- [ ] **Logging:** JSON to stdout, captured by the platform; log levels set via env.
- [ ] **Health checks:** `/health` wired into the platform.
- [ ] **Secrets rotation & backup:** know how to rotate a leaked key; understand your DB backups (Supabase does automated backups on paid tiers — know what your tier offers).

## 25.6 First-Deploy Debugging Mindset

"It works locally, fails in prod" is almost always one of: env vars missing/mismatched, CORS origins wrong, migrations not applied, or the dev-vs-prod database mismatch. The Troubleshooting Guide's Deployment section walks each. **Deploy early, deploy often** — a first deploy of a hello-world endpoint in week one removes an entire class of end-of-project misery.

### ✅ Verify Your Work (Phase 25)

- [ ] The same Docker image runs locally and on the host.
- [ ] The deployed app answers `/health` 200 and `/docs` over HTTPS.
- [ ] Prod env vars are in the platform's secret store, not in the repo or image.
- [ ] A request from the deployed frontend origin succeeds; a foreign origin is rejected by CORS.
- [ ] Migrations apply as part of the deploy, safely.

---

# Phase 26 — Backend Completion Checklist

Run this from a clean checkout, in order. Every box must be checked — and where it says "test", the test must exist and pass.

```text
[ ] Project setup (venv, requirements, .gitignore, folder structure)
[ ] FastAPI application starts; /docs renders
[ ] PostgreSQL connection works (raw psycopg probe)
[ ] SQLAlchemy engine + session + Base with naming conventions
[ ] Alembic initialized; initial migration; upgrade head clean
[ ] Database schema complete per Phase 4/5 design
[ ] Authentication (register, login, JWT, refresh, /me)
[ ] RBAC (four roles, permission matrix, role dependencies)
[ ] Patient APIs (profile, history, allergies, metrics)
[ ] Doctor APIs (list/search, profile, notes, appointment management)
[ ] Management APIs (patients, doctors, departments, appointments)
[ ] Admin APIs (users, roles, config, audit log viewer)
[ ] Appointment system (request, state machine, authorization)
[ ] Medical documents (upload, validation, metadata, states)
[ ] Object storage (private bucket, signed URLs, access control)
[ ] AI report analyzer (pipeline, structured output, review status)
[ ] AI assistant (sessions, history, RAG-lite, safety gates)
[ ] Error handling (consistent shape, handlers, 404/403 policy)
[ ] Logging (JSON, request IDs)
[ ] Audit logging (the Phase 20 action list)
[ ] Testing (unit, integration, auth, authorization incl. BOLA, API)
[ ] Security (Phase 22 checklist: rate limits, headers, pip-audit, secrets)
[ ] API documentation (descriptions, examples, Authorize)
[ ] Docker (image runs same locally and in prod, non-root)
[ ] Deployment (HTTPS, env injection, health check, CORS)
```

**When every box is checked:** you have a production-shaped healthcare backend MVP. The natural next steps — repositories layer, `pgvector` RAG, real queues, custom roles, prescriptions — are all designed-for but deliberately deferred. That was the plan from Phase 0.

---

# 🧩 The Debugging Method (apply it everywhere)

Every subsystem in this guide has common failure modes. Before opening the Code Reference or asking for help, run this loop:

```text
Symptom
   ↓
Check logs           (JSON logs + audit logs — do they name the layer?)
   ↓
Identify layer       (routing? auth? service? DB? AI? storage?)
   ↓
Reproduce            (curl/TestClient the exact failing call)
   ↓
Inspect input        (what exactly was sent? headers, body, token)
   ↓
Inspect database     (state of the rows involved — is the data what you think?)
   ↓
Fix root cause       (fix the cause, not the symptom)
   ↓
Write regression test (prove it stays fixed)
```

**The single most common debugging mistake:** guessing. "The token must be broken" → you change token code → still broken. The loop above replaces guessing with evidence. When you're stuck, the Troubleshooting Guide at the end of this document maps the most common symptoms to their real causes — but always start from logs and reproduction.

---

# 🆘 CODE REFERENCE — USE ONLY IF STUCK

**This is the last resort.** You should have attempted each phase yourself and followed the debugging loop first. This reference exists so that "stuck for two hours" becomes "understand the pattern, adapt it, move on."

- Each section: **what it does → where it belongs → the code → key lines → common mistakes → how to test.**
- The code is written for the stack pinned in Phase 2 (FastAPI, SQLAlchemy 2.0 sync, PyJWT, bcrypt, psycopg v3, Pydantic v2).
- Sections build on each other — imports reference files from earlier sections.
- Treat this as a *reference implementation*, not the only correct one. If your design differs and works, that's fine — that's the point of the guide.

```text
CODE REFERENCE
├── 1. Project Setup          ├── 11. Management APIs
├── 2. Configuration          ├── 12. Admin APIs
├── 3. Database Connection    ├── 13. Appointments
├── 4. SQLAlchemy Base        ├── 14. Medical Documents
├── 5. Models                 ├── 15. File Storage
├── 6. Authentication         ├── 16. AI Service
├── 7. JWT                    ├── 17. Error Handling
├── 8. RBAC                   ├── 18. Testing
├── 9. Patient APIs           ├── 19. Docker
└── 10. Doctor APIs           └── 20. Deployment
```

---

## 1. Project Setup

**What it does:** pins the Python environment and lays out the package skeleton.

**Where it belongs:** `backend/requirements.txt`, `.gitignore`, `app/__init__.py` files.

```text
# requirements.txt (pin what you actually install via pip freeze)
fastapi
uvicorn[standard]
sqlalchemy>=2.0
psycopg[binary]
alembic
pydantic>=2
pydantic-settings
email-validator
python-multipart
bcrypt
PyJWT
httpx            # required by fastapi.testclient
pytest
openai           # AI service (only if you implement Phase 16/17)
```

```gitignore
# .gitignore
.venv/
__pycache__/
*.pyc
.env
.env.*
!.env.example
.pytest_cache/
.mypy_cache/
*.db
.DS_Store
```

**Key lines:** the `.env` rules — without them, your database credentials will be committed on the first `git add .`.

**Common mistakes:** forgetting `httpx` (TestClient crashes on import), forgetting `python-multipart` (file uploads and form login fail with a confusing error), pinning nothing ("works today, broken tomorrow").

**How to test:** `pip install -r requirements.txt` succeeds; `python -c "import fastapi, sqlalchemy, jwt, bcrypt, psycopg; print('ok')"` prints `ok`.

---

## 2. Configuration

**What it does:** loads every environment variable into one typed object — one source of truth for the whole app.

**Where it belongs:** `app/core/config.py`.

```python
from functools import lru_cache
from pydantic_settings import BaseSettings, SettingsConfigDict

class Settings(BaseSettings):
    model_config = SettingsConfigDict(env_file=".env", extra="ignore")

    app_name: str = "HealthAI API"
    environment: str = "development"
    debug: bool = False

    database_url: str                 # required — fails startup if missing
    jwt_secret: str                   # required
    jwt_algorithm: str = "HS256"
    access_token_expire_minutes: int = 30
    refresh_token_expire_days: int = 7

    cors_origins: list[str] = ["http://localhost:5173"]
    log_level: str = "INFO"

    # AI
    openai_api_key: str | None = None
    openai_base_url: str | None = None
    ai_model: str = "gpt-4o-mini"

    # Storage
    supabase_url: str | None = None
    supabase_service_key: str | None = None
    storage_bucket: str = "medical-documents"

@lru_cache
def get_settings() -> Settings:
    return Settings()

settings = get_settings()
```

**Key lines:** `model_config` points at `.env`; `database_url`/`jwt_secret` have no defaults so a missing secret is a loud startup error, not a silent runtime one; `cors_origins: list[str]` lets you write `CORS_ORIGINS=["https://app.example.com"]` in `.env`.

**Common mistakes:** instantiating `Settings()` per-request (wasteful; use the cached instance), defaulting secrets (`` = ""` hides misconfiguration), forgetting `.env` on the deployment platform.

**How to test:** set a bad value (`JWT_SECRET=`) and start the app — it should fail immediately with a validation error naming the field.

---

## 3. Database Connection

**What it does:** builds the SQLAlchemy engine (connection pooling included) and the request-scoped session dependency.

**Where it belongs:** `app/db/session.py`.

```python
from collections.abc import Generator
from sqlalchemy import create_engine
from sqlalchemy.orm import Session, sessionmaker
from app.core.config import settings

engine = create_engine(
    settings.database_url,
    pool_size=5,
    max_overflow=10,
    pool_pre_ping=True,
)

SessionLocal = sessionmaker(bind=engine, autoflush=False, autocommit=False)

def get_db() -> Generator[Session, None, None]:
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()
```

**Key lines:** `pool_pre_ping=True` (transparently reconnects stale pooled connections — cheap insurance), `autoflush=False` (predictable query behavior), and the `get_db` generator: yield the session to the route, **always close it** in `finally`. FastAPI runs this dependency for the whole request and tears it down after.

**Common mistakes:** a leaked session (never closed) that eventually exhausts the pool; `SessionLocal()` created inside routes instead of via the dependency; using `settings.database_url` with a trailing newline or unencoded password.

**How to test:** from a shell, `python -c "from app.db.session import engine; from sqlalchemy import text; print(engine.connect().execute(text('SELECT 1')).scalar())"` prints `1`.

---

## 4. SQLAlchemy Base

**What it does:** the shared declarative base every model inherits, with Alembic-friendly naming conventions and common timestamp columns.

**Where it belongs:** `app/db/base.py`.

```python
from datetime import datetime
from sqlalchemy import DateTime, MetaData, func
from sqlalchemy.orm import DeclarativeBase, Mapped, mapped_column

NAMING_CONVENTION = {
    "ix": "ix_%(column_0_label)s",
    "uq": "uq_%(table_name)s_%(column_0_name)s",
    "ck": "ck_%(table_name)s_%(constraint_name)s",
    "fk": "fk_%(table_name)s_%(column_0_name)s_%(referred_table_name)s",
    "pk": "pk_%(table_name)s",
}

class Base(DeclarativeBase):
    metadata = MetaData(naming_convention=NAMING_CONVENTION)

class TimestampMixin:
    created_at: Mapped[datetime] = mapped_column(
        DateTime(timezone=True), server_default=func.now()
    )
    updated_at: Mapped[datetime] = mapped_column(
        DateTime(timezone=True), server_default=func.now(), onupdate=func.now()
    )
```

**Key lines:** the naming convention makes Alembic autogenerate produce stable constraint names (without it, autogenerate churns when constraints are dropped/renamed); `server_default=func.now()` makes the *database* own timestamps.

**Also needed:** an `app/models/__init__.py` that imports every model, so `Base.metadata` knows them. Alembic's `env.py` must import it too (`from app.models import *` or `from app.db.base import Base; from app import models`) before using `target_metadata = Base.metadata` — a missing import is the classic "autogenerate sees nothing" bug.

**Common mistakes:** forgetting `timezone=True` (naive timestamps across time zones), letting the *app* set `created_at` instead of the DB, forgetting the models import in Alembic.

**How to test:** `Base.metadata.create_all(engine)` creates tables; `alembic revision --autogenerate` detects your models (see Phase 7).

---

## 5. Models

**What it does:** every table from Phase 4/5 as SQLAlchemy 2.0 classes. Split into `app/models/user.py`, `app/models/clinical.py`, `app/models/operations.py` (or one file per model — your call; keep related models together).

**Key lines to internalize (applies to all models):** `Mapped[...]` + `mapped_column(...)` is the 2.0 style; `Uuid` primary keys default to `uuid.uuid4`; `DateTime(timezone=True)` for all times; `String(enum value)` for statuses (validated at the Pydantic layer); `ForeignKey` on the *many* side; `relationship(back_populates=...)` on both sides.

```python
# app/models/user.py
from __future__ import annotations
import uuid
from datetime import date, datetime
from enum import StrEnum
from sqlalchemy import DateTime, ForeignKey, String, Uuid, func
from sqlalchemy.orm import Mapped, mapped_column, relationship
from app.db.base import Base, TimestampMixin

class Role(StrEnum):
    PATIENT = "patient"
    DOCTOR = "doctor"
    MANAGEMENT = "management"
    ADMIN = "admin"

class UserStatus(StrEnum):
    ACTIVE = "active"
    INACTIVE = "inactive"

class User(Base, TimestampMixin):
    __tablename__ = "users"

    id: Mapped[uuid.UUID] = mapped_column(Uuid, primary_key=True, default=uuid.uuid4)
    full_name: Mapped[str] = mapped_column(String(120))
    email: Mapped[str] = mapped_column(String(255), unique=True, index=True)
    password_hash: Mapped[str] = mapped_column(String(255))
    role: Mapped[str] = mapped_column(String(20), default=Role.PATIENT.value)
    status: Mapped[str] = mapped_column(String(20), default=UserStatus.ACTIVE.value)

    patient: Mapped[Patient | None] = relationship(back_populates="user", uselist=False)
    doctor: Mapped[Doctor | None] = relationship(back_populates="user", uselist=False)

    def __repr__(self) -> str:
        return f"<User {self.email} role={self.role}>"   # never include password_hash

class Patient(Base, TimestampMixin):
    __tablename__ = "patients"

    id: Mapped[uuid.UUID] = mapped_column(Uuid, primary_key=True, default=uuid.uuid4)
    user_id: Mapped[uuid.UUID] = mapped_column(
        ForeignKey("users.id", ondelete="CASCADE"), unique=True
    )
    date_of_birth: Mapped[date | None]
    gender: Mapped[str | None] = mapped_column(String(30))
    phone: Mapped[str | None] = mapped_column(String(30))
    address: Mapped[str | None] = mapped_column(String(255))
    blood_group: Mapped[str | None] = mapped_column(String(5))
    emergency_contact_name: Mapped[str | None] = mapped_column(String(120))
    emergency_contact_phone: Mapped[str | None] = mapped_column(String(30))

    user: Mapped[User] = relationship(back_populates="patient")
    medical_history: Mapped[list[MedicalHistory]] = relationship(back_populates="patient")
    allergies: Mapped[list[Allergy]] = relationship(back_populates="patient")
    health_metrics: Mapped[list[HealthMetric]] = relationship(back_populates="patient")
    documents: Mapped[list[MedicalDocument]] = relationship(back_populates="patient")
    appointments: Mapped[list[Appointment]] = relationship(back_populates="patient")

class Doctor(Base, TimestampMixin):
    __tablename__ = "doctors"

    id: Mapped[uuid.UUID] = mapped_column(Uuid, primary_key=True, default=uuid.uuid4)
    user_id: Mapped[uuid.UUID] = mapped_column(
        ForeignKey("users.id", ondelete="CASCADE"), unique=True
    )
    specialization: Mapped[str] = mapped_column(String(80))
    license_number: Mapped[str] = mapped_column(String(40), unique=True)
    department_id: Mapped[uuid.UUID | None] = mapped_column(
        ForeignKey("departments.id", ondelete="SET NULL"), index=True
    )
    bio: Mapped[str | None] = mapped_column(String(500))

    user: Mapped[User] = relationship(back_populates="doctor")
    department: Mapped[Department | None] = relationship(back_populates="doctors")
    appointments: Mapped[list[Appointment]] = relationship(back_populates="doctor")

class Department(Base, TimestampMixin):
    __tablename__ = "departments"

    id: Mapped[uuid.UUID] = mapped_column(Uuid, primary_key=True, default=uuid.uuid4)
    name: Mapped[str] = mapped_column(String(100), unique=True)
    description: Mapped[str | None] = mapped_column(String(300))

    doctors: Mapped[list[Doctor]] = relationship(back_populates="department")
```

```python
# app/models/clinical.py
from __future__ import annotations
import uuid
from datetime import date, datetime
from decimal import Decimal
from enum import StrEnum
from sqlalchemy import DateTime, ForeignKey, Index, Numeric, String, Text, Uuid, func
from sqlalchemy.dialects.postgresql import JSONB
from sqlalchemy.orm import Mapped, mapped_column, relationship
from app.db.base import Base, TimestampMixin

class MedicalHistory(Base, TimestampMixin):
    __tablename__ = "medical_history"

    id: Mapped[uuid.UUID] = mapped_column(Uuid, primary_key=True, default=uuid.uuid4)
    patient_id: Mapped[uuid.UUID] = mapped_column(
        ForeignKey("patients.id", ondelete="RESTRICT"), index=True
    )
    condition_name: Mapped[str] = mapped_column(String(150))
    diagnosed_date: Mapped[date | None]
    status: Mapped[str] = mapped_column(String(20), default="active")
    notes: Mapped[str | None] = mapped_column(Text)

    patient: Mapped[Patient] = relationship(back_populates="medical_history")

class Allergy(Base, TimestampMixin):
    __tablename__ = "allergies"

    id: Mapped[uuid.UUID] = mapped_column(Uuid, primary_key=True, default=uuid.uuid4)
    patient_id: Mapped[uuid.UUID] = mapped_column(
        ForeignKey("patients.id", ondelete="RESTRICT"), index=True
    )
    allergen: Mapped[str] = mapped_column(String(150))
    severity: Mapped[str] = mapped_column(String(20), default="mild")
    reaction: Mapped[str | None] = mapped_column(String(300))
    notes: Mapped[str | None] = mapped_column(Text)

    patient: Mapped[Patient] = relationship(back_populates="allergies")

class HealthMetric(Base, TimestampMixin):
    __tablename__ = "health_metrics"
    __table_args__ = (
        Index("ix_health_metrics_patient_recorded", "patient_id", "recorded_at"),
    )

    id: Mapped[uuid.UUID] = mapped_column(Uuid, primary_key=True, default=uuid.uuid4)
    patient_id: Mapped[uuid.UUID] = mapped_column(ForeignKey("patients.id", ondelete="RESTRICT"))
    metric_type: Mapped[str] = mapped_column(String(40), index=True)
    value: Mapped[Decimal] = mapped_column(Numeric(10, 2))
    unit: Mapped[str] = mapped_column(String(20))
    recorded_at: Mapped[datetime] = mapped_column(DateTime(timezone=True))
    notes: Mapped[str | None] = mapped_column(Text)

    patient: Mapped[Patient] = relationship(back_populates="health_metrics")
```

**Common mistakes:** putting `unique=True` on the wrong column; forgetting the composite index that your "metrics over time" query needs; `Float` instead of `Numeric`; `relationship` without `back_populates` (silent asymmetry); the `__repr__` printing sensitive fields.

**How to test:** create a User + Patient + a couple of metrics in a scratch script and confirm `patient.health_metrics` traverses inside an open session.

```python
# app/models/operations.py
from __future__ import annotations
import uuid
from datetime import datetime
from enum import StrEnum
from sqlalchemy import DateTime, ForeignKey, Index, Integer, String, Text, Uuid, func
from sqlalchemy.dialects.postgresql import JSONB
from sqlalchemy.orm import Mapped, mapped_column, relationship
from app.db.base import Base, TimestampMixin

class AppointmentStatus(StrEnum):
    REQUESTED = "requested"
    CONFIRMED = "confirmed"
    COMPLETED = "completed"
    CANCELLED = "cancelled"
    NO_SHOW = "no_show"

class Appointment(Base, TimestampMixin):
    __tablename__ = "appointments"

    id: Mapped[uuid.UUID] = mapped_column(Uuid, primary_key=True, default=uuid.uuid4)
    patient_id: Mapped[uuid.UUID] = mapped_column(
        ForeignKey("patients.id", ondelete="RESTRICT"), index=True
    )
    doctor_id: Mapped[uuid.UUID] = mapped_column(
        ForeignKey("doctors.id", ondelete="RESTRICT"), index=True
    )
    department_id: Mapped[uuid.UUID | None] = mapped_column(
        ForeignKey("departments.id", ondelete="SET NULL")
    )
    scheduled_at: Mapped[datetime] = mapped_column(DateTime(timezone=True))
    duration_minutes: Mapped[int] = mapped_column(Integer, default=30)
    status: Mapped[str] = mapped_column(String(20), default=AppointmentStatus.REQUESTED.value)
    reason: Mapped[str | None] = mapped_column(String(500))
    notes: Mapped[str | None] = mapped_column(Text)

    patient: Mapped[Patient] = relationship(back_populates="appointments")
    doctor: Mapped[Doctor] = relationship(back_populates="appointments")

class DocumentStatus(StrEnum):
    PENDING = "pending"
    PROCESSING = "processing"
    COMPLETED = "completed"
    FAILED = "failed"

class MedicalDocument(Base, TimestampMixin):
    __tablename__ = "medical_documents"

    id: Mapped[uuid.UUID] = mapped_column(Uuid, primary_key=True, default=uuid.uuid4)
    patient_id: Mapped[uuid.UUID] = mapped_column(
        ForeignKey("patients.id", ondelete="RESTRICT"), index=True
    )
    document_type: Mapped[str] = mapped_column(String(40))
    original_filename: Mapped[str] = mapped_column(String(255))
    stored_object_key: Mapped[str] = mapped_column(String(500), unique=True)
    file_size_bytes: Mapped[int] = mapped_column(Integer)
    content_type: Mapped[str] = mapped_column(String(100))
    processing_status: Mapped[str] = mapped_column(
        String(20), default=DocumentStatus.PENDING.value, index=True
    )
    error_message: Mapped[str | None] = mapped_column(Text)

    patient: Mapped[Patient] = relationship(back_populates="documents")
    analysis: Mapped[DocumentAnalysis | None] = relationship(
        back_populates="document", uselist=False, cascade="all, delete-orphan"
    )

class ReviewStatus(StrEnum):
    UNREVIEWED = "unreviewed"
    REVIEWED = "reviewed"
    DISPUTED = "disputed"

class DocumentAnalysis(Base, TimestampMixin):
    __tablename__ = "document_analyses"

    id: Mapped[uuid.UUID] = mapped_column(Uuid, primary_key=True, default=uuid.uuid4)
    document_id: Mapped[uuid.UUID] = mapped_column(
        ForeignKey("medical_documents.id", ondelete="CASCADE"), unique=True
    )
    summary: Mapped[str] = mapped_column(Text)
    findings: Mapped[list] = mapped_column(JSONB, default=list)     # list of {text, section, severity}
    flagged_abnormalities: Mapped[list] = mapped_column(JSONB, default=list)
    questions_for_doctor: Mapped[list] = mapped_column(JSONB, default=list)
    review_status: Mapped[str] = mapped_column(String(20), default=ReviewStatus.UNREVIEWED.value)
    reviewed_by_id: Mapped[uuid.UUID | None] = mapped_column(ForeignKey("users.id", ondelete="SET NULL"))
    reviewed_at: Mapped[datetime | None] = mapped_column(DateTime(timezone=True))

    document: Mapped[MedicalDocument] = relationship(back_populates="analysis")

class ClinicalNote(Base, TimestampMixin):
    __tablename__ = "clinical_notes"

    id: Mapped[uuid.UUID] = mapped_column(Uuid, primary_key=True, default=uuid.uuid4)
    patient_id: Mapped[uuid.UUID] = mapped_column(
        ForeignKey("patients.id", ondelete="RESTRICT"), index=True
    )
    doctor_id: Mapped[uuid.UUID] = mapped_column(ForeignKey("doctors.id", ondelete="RESTRICT"))
    content: Mapped[str] = mapped_column(Text)

    patient: Mapped[Patient] = relationship()
    doctor: Mapped[Doctor] = relationship()

class ChatSession(Base, TimestampMixin):
    __tablename__ = "chat_sessions"

    id: Mapped[uuid.UUID] = mapped_column(Uuid, primary_key=True, default=uuid.uuid4)
    patient_id: Mapped[uuid.UUID] = mapped_column(
        ForeignKey("patients.id", ondelete="RESTRICT"), index=True
    )
    status: Mapped[str] = mapped_column(String(20), default="active")

    patient: Mapped[Patient] = relationship()
    messages: Mapped[list[ChatMessage]] = relationship(back_populates="session")

class ChatMessage(Base, TimestampMixin):
    __tablename__ = "chat_messages"

    id: Mapped[uuid.UUID] = mapped_column(Uuid, primary_key=True, default=uuid.uuid4)
    session_id: Mapped[uuid.UUID] = mapped_column(
        ForeignKey("chat_sessions.id", ondelete="CASCADE"), index=True
    )
    role: Mapped[str] = mapped_column(String(20))        # "user" | "assistant"
    content: Mapped[str] = mapped_column(Text)
    citations: Mapped[list] = mapped_column(JSONB, default=list)  # source document/analysis ids

    session: Mapped[ChatSession] = relationship(back_populates="messages")

class AuditLog(Base):
    __tablename__ = "audit_logs"

    id: Mapped[uuid.UUID] = mapped_column(Uuid, primary_key=True, default=uuid.uuid4)
    user_id: Mapped[uuid.UUID | None] = mapped_column(
        ForeignKey("users.id", ondelete="SET NULL"), index=True
    )
    action: Mapped[str] = mapped_column(String(60), index=True)   # created/read/updated/deleted/role_changed/login_failed...
    resource_type: Mapped[str] = mapped_column(String(60))
    resource_id: Mapped[str | None] = mapped_column(String(60))
    details: Mapped[dict] = mapped_column(JSONB, default=dict)
    ip_address: Mapped[str | None] = mapped_column(String(45))
    created_at: Mapped[datetime] = mapped_column(
        DateTime(timezone=True), server_default=func.now(), index=True
    )

class Prescription(Base, TimestampMixin):     # stretch
    __tablename__ = "prescriptions"

    id: Mapped[uuid.UUID] = mapped_column(Uuid, primary_key=True, default=uuid.uuid4)
    patient_id: Mapped[uuid.UUID] = mapped_column(ForeignKey("patients.id", ondelete="RESTRICT"), index=True)
    doctor_id: Mapped[uuid.UUID] = mapped_column(ForeignKey("doctors.id", ondelete="RESTRICT"))
    medication_name: Mapped[str] = mapped_column(String(150))
    dosage: Mapped[str] = mapped_column(String(100))
    instructions: Mapped[str | None] = mapped_column(Text)
    prescribed_at: Mapped[datetime] = mapped_column(DateTime(timezone=True), server_default=func.now())
```

**Common mistakes:** `cascade="all, delete-orphan"` on a one-to-one child you don't want silently deleted; audit log rows with no index on `created_at`/`user_id` (queries scan everything); JSONB columns without defaults; forgetting that `MedicalDocument.analysis` is lazy-loaded (access it inside the session).

**How to test:** after `alembic upgrade head`, inspect `\d` output for every table; insert a document + analysis and confirm the one-to-one relationship holds (a second analysis for the same document must violate the unique constraint).

---

## 6. Authentication

**What it does:** password hashing, registration, login, and the current-user dependency. The JWT details live in §7; this section wires them into endpoints.

**Where it belongs:** `app/core/security.py`, `app/schemas/auth.py`, `app/services/auth_service.py`, `app/api/routers/auth.py`.

```python
# app/core/security.py  (hashing half; JWT helpers are in §7)
import bcrypt

def hash_password(password: str) -> str:
    return bcrypt.hashpw(password.encode("utf-8"), bcrypt.gensalt()).decode("utf-8")

def verify_password(plain: str, hashed: str) -> bool:
    return bcrypt.checkpw(plain.encode("utf-8"), hashed.encode("utf-8"))
```

```python
# app/schemas/auth.py
import uuid
from pydantic import BaseModel, ConfigDict, EmailStr, Field
from app.models.user import Role

class RegisterRequest(BaseModel):
    full_name: str = Field(min_length=2, max_length=120)
    email: EmailStr
    password: str = Field(min_length=8, max_length=128)

class UserOut(BaseModel):
    model_config = ConfigDict(from_attributes=True)
    id: uuid.UUID
    full_name: str
    email: EmailStr
    role: Role

class TokenResponse(BaseModel):
    access_token: str
    refresh_token: str
    token_type: str = "bearer"

class RefreshRequest(BaseModel):
    refresh_token: str
```

```python
# app/services/auth_service.py
import uuid
from sqlalchemy import select
from sqlalchemy.orm import Session
from app.core.security import hash_password, verify_password, create_access_token, create_refresh_token
from app.models.user import Patient, Role, User, UserStatus
from app.schemas.auth import RegisterRequest, TokenResponse
from app.core.errors import ConflictError, UnauthorizedError   # §17

def register_patient(db: Session, data: RegisterRequest) -> User:
    if db.scalar(select(User.id).where(User.email == data.email)) is not None:
        raise ConflictError("An account with this email already exists", code="EMAIL_TAKEN")
    user = User(
        full_name=data.full_name,
        email=str(data.email).lower(),
        password_hash=hash_password(data.password),
        role=Role.PATIENT.value,
    )
    db.add(user)
    db.flush()  # assigns user.id without committing
    db.add(Patient(user_id=user.id))
    db.commit()
    db.refresh(user)
    return user

def authenticate(db: Session, email: str, password: str) -> User:
    user = db.scalar(select(User).where(User.email == email.lower()))
    if user is None or not verify_password(password, user.password_hash):
        raise UnauthorizedError("Incorrect email or password", code="INVALID_CREDENTIALS")
    if user.status != UserStatus.ACTIVE.value:
        raise UnauthorizedError("Account is disabled", code="ACCOUNT_DISABLED")
    return user

def issue_tokens(user: User) -> TokenResponse:
    return TokenResponse(
        access_token=create_access_token(user),
        refresh_token=create_refresh_token(user),
    )
```

```python
# app/api/routers/auth.py
from typing import Annotated
from fastapi import APIRouter, Depends, status
from fastapi.security import OAuth2PasswordRequestForm
from sqlalchemy.orm import Session
from app.db.session import get_db
from app.api.deps import get_current_user
from app.models.user import User
from app.schemas.auth import RefreshRequest, RegisterRequest, TokenResponse, UserOut
from app.services import auth_service

router = APIRouter()

@router.post("/register", response_model=TokenResponse, status_code=status.HTTP_201_CREATED)
def register(data: RegisterRequest, db: Annotated[Session, Depends(get_db)]):
    user = auth_service.register_patient(db, data)
    return auth_service.issue_tokens(user)

@router.post("/login", response_model=TokenResponse)
def login(form: Annotated[OAuth2PasswordRequestForm, Depends()], db: Annotated[Session, Depends(get_db)]):
    user = auth_service.authenticate(db, form.username, form.password)
    return auth_service.issue_tokens(user)

@router.get("/me", response_model=UserOut)
def me(current_user: Annotated[User, Depends(get_current_user)]):
    return current_user

@router.post("/refresh", response_model=TokenResponse)
def refresh(data: RefreshRequest, db: Annotated[Session, Depends(get_db)]):
    return auth_service.refresh_tokens(db, data.refresh_token)
```

**Key lines:** `db.flush()` then `db.add(Patient(...))` creates the patient row in the same transaction; `form.username` is the email because the login form uses the `username` field (the standard OAuth2 form); `/me` returns the authenticated user via the dependency — no token parsing in the route.

**Common mistakes:** hashing with the wrong scheme or comparing plaintext; storing email case-sensitively (normalize to lowercase); letting `role` come from the request body (register always creates a PATIENT); leaking the password hash via `UserOut` (it's never in the schema — that's the point of `from_attributes` with explicit fields).

**How to test:** register → 201 + tokens; login wrong password → 401; `/me` with no token → 401; duplicate email → 409.

---

## 7. JWT

**What it does:** creates and verifies signed access/refresh tokens, and the refresh flow that issues a new pair.

**Where it belongs:** `app/core/jwt.py` (helpers) + `auth_service.refresh_tokens`.

```python
# app/core/jwt.py
import uuid
from datetime import datetime, timedelta, timezone
import jwt
from app.core.config import settings

def _create_token(sub: uuid.UUID, role: str, type_: str, expires: timedelta) -> str:
    now = datetime.now(timezone.utc)
    payload = {
        "sub": str(sub),
        "role": role,
        "type": type_,
        "iat": now,
        "exp": now + expires,
        "jti": str(uuid.uuid4()),
    }
    return jwt.encode(payload, settings.jwt_secret, algorithm=settings.jwt_algorithm)

def create_access_token(user) -> str:
    return _create_token(
        user.id, user.role, "access",
        timedelta(minutes=settings.access_token_expire_minutes),
    )

def create_refresh_token(user) -> str:
    return _create_token(
        user.id, user.role, "refresh",
        timedelta(days=settings.refresh_token_expire_days),
    )

def decode_token(token: str) -> dict:
    return jwt.decode(token, settings.jwt_secret, algorithms=[settings.jwt_algorithm])
```

```python
# app/services/auth_service.py  (add)
import uuid
import jwt
from app.core.jwt import decode_token
from app.core.errors import UnauthorizedError

def refresh_tokens(db: Session, refresh_token: str) -> TokenResponse:
    try:
        payload = decode_token(refresh_token)
    except jwt.PyJWTError:
        raise UnauthorizedError("Invalid refresh token", code="INVALID_TOKEN")
    if payload.get("type") != "refresh":
        raise UnauthorizedError("Not a refresh token", code="INVALID_TOKEN")
    user = db.get(User, uuid.UUID(payload["sub"]))
    if user is None or user.status != UserStatus.ACTIVE.value:
        raise UnauthorizedError("Account unavailable", code="ACCOUNT_DISABLED")
    return issue_tokens(user)
```

**Key lines:** `exp` is always set (a token without expiry is a permanent credential); `type` distinguishes access vs refresh so a stolen refresh token can't be used as an access token (and vice versa); `jti` is a unique ID you could denylist later (Phase 8.6); the refresh endpoint **re-issues a whole new pair** and validates `type == "refresh"`.

**Common mistakes:** signing with a hardcoded secret; using the same secret in dev and prod; putting sensitive data (email, medical info) in the payload (tokens are signed, not encrypted — base64-decode one and you'll see); catching only `ExpiredSignatureError` and letting other decode errors crash the endpoint.

**How to test:** decode a returned token locally and confirm the claims; call `/auth/refresh` with an access token (should 401 — type check works); tamper with one character in a token (signature fails → 401); mint a token with `exp` in the past (expired → 401).

---

## 8. RBAC

**What it does:** the `get_current_user` dependency (who you are) and role guards (what you may do).

**Where it belongs:** `app/api/deps.py`.

```python
# app/api/deps.py
import uuid
from typing import Annotated
import jwt
from fastapi import Depends, HTTPException, status
from fastapi.security import OAuth2PasswordBearer
from sqlalchemy.orm import Session
from app.core.jwt import decode_token
from app.core.errors import PermissionDeniedError, UnauthorizedError
from app.db.session import get_db
from app.models.user import Role, User, UserStatus

oauth2_scheme = OAuth2PasswordBearer(tokenUrl="/auth/login")

def get_current_user(
    token: Annotated[str, Depends(oauth2_scheme)],
    db: Annotated[Session, Depends(get_db)],
) -> User:
    try:
        payload = decode_token(token)
    except jwt.PyJWTError:
        raise UnauthorizedError("Invalid or expired token", code="INVALID_TOKEN")
    if payload.get("type") != "access":
        raise UnauthorizedError("Expected an access token", code="INVALID_TOKEN")
    user = db.get(User, uuid.UUID(payload["sub"]))
    if user is None or user.status != UserStatus.ACTIVE.value:
        raise UnauthorizedError("Account unavailable", code="ACCOUNT_DISABLED")
    return user

CurrentUser = Annotated[User, Depends(get_current_user)]

def require_roles(*roles: Role):
    def checker(user: CurrentUser) -> User:
        if user.role not in [r.value for r in roles]:
            raise PermissionDeniedError("You do not have permission for this action", code="FORBIDDEN")
        return user
    return checker

AdminOnly = Annotated[User, Depends(require_roles(Role.ADMIN))]
DoctorOrAbove = Annotated[User, Depends(require_roles(Role.DOCTOR, Role.MANAGEMENT, Role.ADMIN))]
ManagementOrAbove = Annotated[User, Depends(require_roles(Role.MANAGEMENT, Role.ADMIN))]
```

**Key lines:** `OAuth2PasswordBearer(tokenUrl="/auth/login")` gives Swagger a working **Authorize** button; `get_current_user` verifies the token, checks it's an *access* token, loads the user, and rejects inactive accounts — every protected route reuses it; `require_roles` returns a *dependency factory* so you can declare `DoctorOrAbove` once and reuse it.

**Common mistakes:** role checks in the route body instead of a dependency (scattered, easy to forget); treating role-level auth as sufficient (it is *not* — object-level checks in §9/§10 are mandatory); 401 vs 403 confusion (invalid token → 401; valid token, wrong role → 403).

**How to test:** patient token on a `DoctorOrAbove` route → 403; no token → 401; expired token → 401; admin token on an admin route → 200.

---

## 9. Patient APIs

**What it does:** profile, medical history, allergies, and health metrics — plus the **central object-level authorization helper** every patient/doctor route uses. This helper is where BOLA is defeated.

**Where it belongs:** `app/core/access.py`, `app/schemas/patient.py`, `app/services/patient_service.py`, `app/api/routers/patients.py`.

```python
# app/core/access.py  (the object-level authorization gate — use everywhere)
import uuid
from sqlalchemy import select
from sqlalchemy.orm import Session
from app.models import operations  # noqa: ensure models loaded
from app.models.user import Patient, Role, User
from app.core.errors import NotFoundError, PermissionDeniedError

def can_access_patient(db: Session, user: User, patient_id: uuid.UUID) -> Patient:
    if user.role == Role.PATIENT.value:
        if user.patient is None or user.patient.id != patient_id:
            raise PermissionDeniedError("You cannot access this patient's record")
        return user.patient

    if user.role == Role.DOCTOR.value:
        patient = db.get(Patient, patient_id)
        if patient is None:
            raise NotFoundError("Patient not found")
        linked = db.scalar(
            select(operations.Appointment.id)
            .where(
                operations.Appointment.patient_id == patient_id,
                operations.Appointment.doctor_id == user.doctor.id,
            )
            .limit(1)
        )
        if linked is None:
            raise PermissionDeniedError("You are not authorized to view this patient")
        return patient

    if user.role in (Role.MANAGEMENT.value, Role.ADMIN.value):
        patient = db.get(Patient, patient_id)
        if patient is None:
            raise NotFoundError("Patient not found")
        return patient

    raise PermissionDeniedError("You cannot access this patient's record")
```

```python
# app/schemas/patient.py
import uuid
from datetime import date, datetime
from decimal import Decimal
from pydantic import BaseModel, ConfigDict, Field

class PatientProfileOut(BaseModel):
    model_config = ConfigDict(from_attributes=True)
    id: uuid.UUID
    date_of_birth: date | None = None
    gender: str | None = None
    phone: str | None = None
    address: str | None = None
    blood_group: str | None = None
    emergency_contact_name: str | None = None
    emergency_contact_phone: str | None = None

class PatientProfileUpdate(BaseModel):
    phone: str | None = None
    address: str | None = None
    emergency_contact_name: str | None = None
    emergency_contact_phone: str | None = None

class MedicalHistoryIn(BaseModel):
    condition_name: str = Field(min_length=2, max_length=150)
    diagnosed_date: date | None = None
    status: str = "active"
    notes: str | None = None

class MedicalHistoryOut(MedicalHistoryIn):
    model_config = ConfigDict(from_attributes=True)
    id: uuid.UUID
    created_at: datetime

class AllergyIn(BaseModel):
    allergen: str = Field(min_length=1, max_length=150)
    severity: str = "mild"
    reaction: str | None = None
    notes: str | None = None

class AllergyOut(AllergyIn):
    model_config = ConfigDict(from_attributes=True)
    id: uuid.UUID

class HealthMetricIn(BaseModel):
    metric_type: str
    value: Decimal = Field(gt=0)
    unit: str
    recorded_at: datetime
    notes: str | None = None

class HealthMetricOut(HealthMetricIn):
    model_config = ConfigDict(from_attributes=True)
    id: uuid.UUID
```

```python
# app/services/patient_service.py
import uuid
from sqlalchemy import select
from sqlalchemy.orm import Session
from app.core.access import can_access_patient
from app.core.errors import PermissionDeniedError
from app.models.user import Patient, User
from app.models.clinical import Allergy, HealthMetric, MedicalHistory
from app.schemas.patient import (
    AllergyIn, HealthMetricIn, MedicalHistoryIn, PatientProfileUpdate,
)

def get_my_patient(db: Session, user: User) -> Patient:
    if user.role == "patient" and user.patient is not None:
        return user.patient
    raise PermissionDeniedError("No patient profile")

def update_my_profile(db: Session, user: User, data: PatientProfileUpdate) -> Patient:
    patient = get_my_patient(db, user)
    for field, value in data.model_dump(exclude_unset=True).items():
        setattr(patient, field, value)
    db.commit()
    db.refresh(patient)
    return patient

def add_history(db: Session, user: User, patient_id: uuid.UUID, data: MedicalHistoryIn) -> MedicalHistory:
    patient = can_access_patient(db, user, patient_id)   # object-level check
    row = MedicalHistory(patient_id=patient.id, **data.model_dump())
    db.add(row); db.commit(); db.refresh(row)
    return row

def list_history(db: Session, user: User, patient_id: uuid.UUID) -> list[MedicalHistory]:
    can_access_patient(db, user, patient_id)
    return list(db.scalars(select(MedicalHistory).where(MedicalHistory.patient_id == patient_id).order_by(MedicalHistory.created_at.desc())))

def add_allergy(db, user, patient_id, data: AllergyIn) -> Allergy:
    patient = can_access_patient(db, user, patient_id)
    row = Allergy(patient_id=patient.id, **data.model_dump())
    db.add(row); db.commit(); db.refresh(row)
    return row

def list_allergies(db, user, patient_id) -> list[Allergy]:
    can_access_patient(db, user, patient_id)
    return list(db.scalars(select(Allergy).where(Allergy.patient_id == patient_id)))

def add_metric(db, user, patient_id, data: HealthMetricIn) -> HealthMetric:
    patient = can_access_patient(db, user, patient_id)
    row = HealthMetric(patient_id=patient.id, **data.model_dump())
    db.add(row); db.commit(); db.refresh(row)
    return row

def list_metrics(db, user, patient_id, metric_type: str | None = None) -> list[HealthMetric]:
    can_access_patient(db, user, patient_id)
    q = select(HealthMetric).where(HealthMetric.patient_id == patient_id)
    if metric_type:
        q = q.where(HealthMetric.metric_type == metric_type)
    return list(db.scalars(q.order_by(HealthMetric.recorded_at.desc())))
```

```python
# app/api/routers/patients.py
import uuid
from typing import Annotated
from fastapi import APIRouter, Depends, status
from sqlalchemy.orm import Session
from app.db.session import get_db
from app.api.deps import CurrentUser
from app.models.user import User
from app.schemas.patient import (
    AllergyIn, AllergyOut, HealthMetricIn, HealthMetricOut,
    MedicalHistoryIn, MedicalHistoryOut, PatientProfileOut, PatientProfileUpdate,
)
from app.services import patient_service

router = APIRouter()

@router.get("/me", response_model=PatientProfileOut)
def my_profile(user: CurrentUser, db: Annotated[Session, Depends(get_db)]):
    return patient_service.get_my_patient(db, user)

@router.patch("/me", response_model=PatientProfileOut)
def update_me(data: PatientProfileUpdate, user: CurrentUser, db: Annotated[Session, Depends(get_db)]):
    return patient_service.update_my_profile(db, user, data)

@router.get("/{patient_id}/history", response_model=list[MedicalHistoryOut])
def history(patient_id: uuid.UUID, user: CurrentUser, db: Annotated[Session, Depends(get_db)]):
    return patient_service.list_history(db, user, patient_id)

@router.post("/{patient_id}/history", response_model=MedicalHistoryOut, status_code=status.HTTP_201_CREATED)
def add_history(patient_id: uuid.UUID, data: MedicalHistoryIn, user: CurrentUser, db: Annotated[Session, Depends(get_db)]):
    return patient_service.add_history(db, user, patient_id, data)

@router.get("/{patient_id}/allergies", response_model=list[AllergyOut])
def allergies(patient_id: uuid.UUID, user: CurrentUser, db: Annotated[Session, Depends(get_db)]):
    return patient_service.list_allergies(db, user, patient_id)

@router.post("/{patient_id}/allergies", response_model=AllergyOut, status_code=status.HTTP_201_CREATED)
def add_allergy(patient_id: uuid.UUID, data: AllergyIn, user: CurrentUser, db: Annotated[Session, Depends(get_db)]):
    return patient_service.add_allergy(db, user, patient_id, data)

@router.get("/{patient_id}/metrics", response_model=list[HealthMetricOut])
def metrics(patient_id: uuid.UUID, user: CurrentUser, db: Annotated[Session, Depends(get_db)], metric_type: str | None = None):
    return patient_service.list_metrics(db, user, patient_id, metric_type)

@router.post("/{patient_id}/metrics", response_model=HealthMetricOut, status_code=status.HTTP_201_CREATED)
def add_metric(patient_id: uuid.UUID, data: HealthMetricIn, user: CurrentUser, db: Annotated[Session, Depends(get_db)]):
    return patient_service.add_metric(db, user, patient_id, data)
```

**Key lines:** `can_access_patient` is the *single* object-level gate reused by every route — a patient may only touch their own `patient_id`, a doctor only linked patients, management/admin within scope; the `doctor_id`/`patient_id` in the request body are **never** trusted (the service assigns them from the authorized patient).

**Common mistakes:** skipping the object check (the BOLA bug); trusting `patient_id` from the body; forgetting `exclude_unset=True` on updates (overwrites fields the client didn't send with `None`); returning raw ORM objects instead of schemas.

**How to test:** Patient A `GET /patients/{B}/metrics` → 403; doctor on an unlinked patient → 403; doctor on a linked patient → 200; anonymous → 401.

---

## 10. Doctor APIs

**What it does:** the doctor's workspace: their patient list/search, a full authorized patient view, clinical notes, and document download. The authorization boundary from Phase 12 is enforced through `can_access_patient`.

**Where it belongs:** `app/services/doctor_service.py`, `app/api/routers/doctors.py`.

```python
# app/services/doctor_service.py
import uuid
from sqlalchemy import func, select
from sqlalchemy.orm import Session
from app.core.access import can_access_patient
from app.core.errors import PermissionDeniedError
from app.models.user import Patient, User
from app.models.clinical import ClinicalNote
from app.models.operations import Appointment

def list_assigned_patients(db: Session, user: User, search: str | None = None) -> list[Patient]:
    if user.role != "doctor" or user.doctor is None:
        raise PermissionDeniedError("Only doctors can list assigned patients")
    subq = (
        select(Appointment.patient_id)
        .where(Appointment.doctor_id == user.doctor.id)
        .distinct()
        .subquery()
    )
    q = select(Patient).join(Patient.user).join(subq, Patient.id == subq.c.patient_id)
    if search:
        q = q.where(func.lower(User.full_name).like(f"%{search.lower()}%"))
    return list(db.scalars(q.order_by(User.full_name)))

def get_patient_detail(db: Session, user: User, patient_id: uuid.UUID) -> Patient:
    return can_access_patient(db, user, patient_id)   # object-level gate

def add_note(db: Session, user: User, patient_id: uuid.UUID, content: str) -> ClinicalNote:
    patient = can_access_patient(db, user, patient_id)
    note = ClinicalNote(patient_id=patient.id, doctor_id=user.doctor.id, content=content)
    db.add(note); db.commit(); db.refresh(note)
    return note

def list_notes(db: Session, user: User, patient_id: uuid.UUID) -> list[ClinicalNote]:
    can_access_patient(db, user, patient_id)
    return list(db.scalars(select(ClinicalNote).where(ClinicalNote.patient_id == patient_id).order_by(ClinicalNote.created_at.desc())))
```

```python
# app/api/routers/doctors.py
import uuid
from typing import Annotated
from fastapi import APIRouter, Depends, status
from pydantic import BaseModel, ConfigDict, Field
from sqlalchemy.orm import Session
from app.db.session import get_db
from app.api.deps import DoctorOrAbove
from app.models.user import User
from app.schemas.patient import PatientProfileOut
from app.services import doctor_service

class NoteIn(BaseModel):
    content: str = Field(min_length=1, max_length=5000)

class NoteOut(NoteIn):
    model_config = ConfigDict(from_attributes=True)
    id: uuid.UUID

class PatientListItem(BaseModel):
    id: uuid.UUID
    full_name: str

router = APIRouter()

@router.get("/patients", response_model=list[PatientListItem])
def my_patients(user: DoctorOrAbove, db: Annotated[Session, Depends(get_db)], search: str | None = None):
    patients = doctor_service.list_assigned_patients(db, user, search)
    return [PatientListItem(id=p.id, full_name=p.user.full_name) for p in patients]

@router.get("/patients/{patient_id}", response_model=PatientProfileOut)
def patient_detail(patient_id: uuid.UUID, user: DoctorOrAbove, db: Annotated[Session, Depends(get_db)]):
    return doctor_service.get_patient_detail(db, user, patient_id)

@router.post("/patients/{patient_id}/notes", response_model=NoteOut, status_code=status.HTTP_201_CREATED)
def add_note(patient_id: uuid.UUID, data: NoteIn, user: DoctorOrAbove, db: Annotated[Session, Depends(get_db)]):
    return doctor_service.add_note(db, user, patient_id, data.content)

@router.get("/patients/{patient_id}/notes", response_model=list[NoteOut])
def notes(patient_id: uuid.UUID, user: DoctorOrAbove, db: Annotated[Session, Depends(get_db)]):
    return doctor_service.list_notes(db, user, patient_id)
```

**Key lines:** the assigned-patient list is derived from **appointments** (the Phase 12 decision) via a `DISTINCT` subquery — no new table needed; `joinedload(Patient.user)` avoids an N+1 on the list; `can_access_patient` guards both detail and notes.

**Common mistakes:** letting a doctor query *any* patient by forgetting the object gate; N+1 queries on the patient list (fix with `joinedload`); returning the raw `Patient` (use the schema); search built with an unescaped `%`/`_` (escape them or accept the small risk for an MVP with a note).

**How to test:** doctor sees only linked patients in the list; unlinked patient detail → 403; add a note → 201 and it's listed; patient token on `/doctors/patients` → 403.

---

## 11. Management APIs

**What it does:** doctor management, department management, and operational analytics. The recurring theme: **aggregate, never dump.**

**Where it belongs:** `app/services/management_service.py`, `app/api/routers/management.py`.

```python
# app/services/management_service.py
import uuid
from sqlalchemy import func, select
from sqlalchemy.orm import Session
from app.core.errors import ConflictError, NotFoundError
from app.core.security import hash_password
from app.models.user import Department, Doctor, Role, User, UserStatus
from app.models.operations import Appointment

def create_doctor(db: Session, full_name: str, email: str, password: str, specialization: str, license_number: str, department_id: uuid.UUID | None) -> Doctor:
    if db.scalar(select(User.id).where(User.email == email.lower())) is not None:
        raise ConflictError("Email already in use", code="EMAIL_TAKEN")
    user = User(full_name=full_name, email=email.lower(), password_hash=hash_password(password), role=Role.DOCTOR.value)
    db.add(user); db.flush()
    doctor = Doctor(user_id=user.id, specialization=specialization, license_number=license_number, department_id=department_id)
    db.add(doctor); db.commit(); db.refresh(doctor)
    return doctor

def update_doctor(db: Session, doctor_id: uuid.UUID, specialization=None, department_id=None) -> Doctor:
    doctor = db.get(Doctor, doctor_id)
    if doctor is None:
        raise NotFoundError("Doctor not found")
    if specialization is not None:
        doctor.specialization = specialization
    if department_id is not None:
        doctor.department_id = department_id
    db.commit(); db.refresh(doctor)
    return doctor

def create_department(db: Session, name: str, description: str | None) -> Department:
    if db.scalar(select(Department.id).where(Department.name == name)) is not None:
        raise ConflictError("Department already exists", code="DEPARTMENT_EXISTS")
    dept = Department(name=name, description=description)
    db.add(dept); db.commit(); db.refresh(dept)
    return dept

def list_departments(db: Session) -> list[Department]:
    return list(db.scalars(select(Department).order_by(Department.name)))

def appointment_analytics(db: Session) -> dict:
    per_status = dict(
        db.execute(
            select(Appointment.status, func.count(Appointment.id))
            .group_by(Appointment.status)
        ).all()
    )
    total = sum(per_status.values())
    return {
        "total": total,
        "by_status": per_status,
        "by_department": [
            {"department_id": str(row[0]), "count": row[1]}
            for row in db.execute(
                select(Appointment.department_id, func.count(Appointment.id))
                .group_by(Appointment.department_id)
            ).all()
        ],
    }
```

```python
# app/api/routers/management.py
import uuid
from typing import Annotated
from fastapi import APIRouter, Depends, status
from pydantic import BaseModel, ConfigDict, EmailStr, Field
from sqlalchemy.orm import Session
from app.db.session import get_db
from app.api.deps import ManagementOrAbove
from app.services import management_service

class DoctorCreate(BaseModel):
    full_name: str = Field(min_length=2)
    email: EmailStr
    password: str = Field(min_length=8)
    specialization: str = Field(min_length=2)
    license_number: str = Field(min_length=3)
    department_id: uuid.UUID | None = None

class DoctorUpdate(BaseModel):
    specialization: str | None = None
    department_id: uuid.UUID | None = None

class DepartmentCreate(BaseModel):
    name: str = Field(min_length=2)
    description: str | None = None

class DoctorOut(BaseModel):
    model_config = ConfigDict(from_attributes=True)
    id: uuid.UUID
    specialization: str
    license_number: str
    department_id: uuid.UUID | None = None
    bio: str | None = None

class DepartmentOut(BaseModel):
    model_config = ConfigDict(from_attributes=True)
    id: uuid.UUID
    name: str
    description: str | None = None

router = APIRouter()

@router.post("/doctors", response_model=DoctorOut, status_code=status.HTTP_201_CREATED)
def create_doctor(data: DoctorCreate, user: ManagementOrAbove, db: Annotated[Session, Depends(get_db)]):
    return management_service.create_doctor(db, **data.model_dump())

@router.patch("/doctors/{doctor_id}", response_model=DoctorOut)
def update_doctor(doctor_id: uuid.UUID, data: DoctorUpdate, user: ManagementOrAbove, db: Annotated[Session, Depends(get_db)]):
    return management_service.update_doctor(db, doctor_id, **data.model_dump(exclude_unset=True))

@router.post("/departments", response_model=DepartmentOut, status_code=status.HTTP_201_CREATED)
def create_department(data: DepartmentCreate, user: ManagementOrAbove, db: Annotated[Session, Depends(get_db)]):
    return management_service.create_department(db, **data.model_dump())

@router.get("/departments", response_model=list[DepartmentOut])
def departments(user: ManagementOrAbove, db: Annotated[Session, Depends(get_db)]):
    return management_service.list_departments(db)

@router.get("/analytics/appointments")
def analytics(user: ManagementOrAbove, db: Annotated[Session, Depends(get_db)]):
    return management_service.appointment_analytics(db)
```

**Key lines:** the analytics queries do the counting **in the database** (`COUNT` + `GROUP BY`) and return compact summaries — no patient rows ever leave this endpoint; creating a doctor creates the `User` + `Doctor` in one transaction; the `ManagementOrAbove` dependency (defined in §8) guards the router.

**Common mistakes:** returning raw `User` objects from analytics (operational data only!); `COUNT` in Python instead of SQL; letting `password` default or be visible in responses.

**How to test:** management token creates a doctor and department; patient token → 403 on all of these; analytics returns status/department counts.

---

## 12. Admin APIs

**What it does:** user listing, role/status changes (with self-lockout guards), and the audit log viewer. Every mutation is audited.

**Where it belongs:** `app/services/admin_service.py`, `app/services/audit_service.py`, `app/api/routers/admin.py`.

```python
# app/services/audit_service.py
from sqlalchemy.orm import Session
from app.models.operations import AuditLog

def log_audit(db: Session, *, user_id=None, action: str, resource_type: str, resource_id=None, details: dict | None = None, ip_address: str | None = None) -> None:
    db.add(AuditLog(user_id=user_id, action=action, resource_type=resource_type, resource_id=resource_id, details=details or {}, ip_address=ip_address))
    db.commit()
```

```python
# app/services/admin_service.py
import uuid
from sqlalchemy import func, select
from sqlalchemy.orm import Session
from app.core.errors import ConflictError, NotFoundError, PermissionDeniedError
from app.models.operations import AuditLog
from app.models.user import Role, User, UserStatus
from app.services.audit_service import log_audit

def list_users(db: Session, role: str | None = None, status: str | None = None) -> list[User]:
    q = select(User)
    if role:
        q = q.where(User.role == role)
    if status:
        q = q.where(User.status == status)
    return list(db.scalars(q.order_by(User.created_at.desc())))

def change_role(db: Session, actor: User, user_id: uuid.UUID, new_role: str) -> User:
    target = db.get(User, user_id)
    if target is None:
        raise NotFoundError("User not found")
    if new_role not in [r.value for r in Role]:
        raise ConflictError("Unknown role", code="INVALID_ROLE")
    if target.id == actor.id:
        raise PermissionDeniedError("You cannot change your own role", code="SELF_ROLE_CHANGE")
    if target.role == Role.ADMIN.value and new_role != Role.ADMIN.value:
        admin_count = db.scalar(select(func.count(User.id)).where(User.role == Role.ADMIN.value))
        if admin_count <= 1:
            raise ConflictError("Cannot demote the last admin", code="LAST_ADMIN")
    old_role = target.role
    target.role = new_role
    db.commit(); db.refresh(target)
    log_audit(db, user_id=actor.id, action="role_changed", resource_type="user", resource_id=str(target.id), details={"from": old_role, "to": new_role})
    return target

def set_user_status(db: Session, actor: User, user_id: uuid.UUID, status: str) -> User:
    target = db.get(User, user_id)
    if target is None:
        raise NotFoundError("User not found")
    if target.id == actor.id:
        raise PermissionDeniedError("You cannot deactivate your own account", code="SELF_DEACTIVATE")
    target.status = status
    db.commit(); db.refresh(target)
    log_audit(db, user_id=actor.id, action="status_changed", resource_type="user", resource_id=str(target.id), details={"status": status})
    return target

def list_audit_logs(db: Session, user_id: uuid.UUID | None = None, action: str | None = None, limit: int = 100) -> list[AuditLog]:
    q = select(AuditLog).order_by(AuditLog.created_at.desc()).limit(min(limit, 500))
    if user_id:
        q = q.where(AuditLog.user_id == user_id)
    if action:
        q = q.where(AuditLog.action == action)
    return list(db.scalars(q))
```

```python
# app/api/routers/admin.py
import uuid
from datetime import datetime
from typing import Annotated
from fastapi import APIRouter, Depends
from pydantic import BaseModel, ConfigDict, EmailStr
from sqlalchemy.orm import Session
from app.db.session import get_db
from app.api.deps import AdminOnly
from app.models.user import User
from app.services import admin_service

class RoleChange(BaseModel):
    role: str

class StatusChange(BaseModel):
    status: str

class UserAdminOut(BaseModel):
    model_config = ConfigDict(from_attributes=True)
    id: uuid.UUID
    full_name: str
    email: EmailStr
    role: str
    status: str
    created_at: datetime

router = APIRouter()

@router.get("/users", response_model=list[UserAdminOut])
def users(user: AdminOnly, db: Annotated[Session, Depends(get_db)], role: str | None = None):
    return admin_service.list_users(db, role=role)

@router.patch("/users/{user_id}/role", response_model=UserAdminOut)
def change_role(user_id: uuid.UUID, data: RoleChange, user: AdminOnly, db: Annotated[Session, Depends(get_db)]):
    return admin_service.change_role(db, user, user_id, data.role)

@router.patch("/users/{user_id}/status", response_model=UserAdminOut)
def change_status(user_id: uuid.UUID, data: StatusChange, user: AdminOnly, db: Annotated[Session, Depends(get_db)]):
    return admin_service.set_user_status(db, user, user_id, data.status)

@router.get("/audit-logs")
def audit_logs(user: AdminOnly, db: Annotated[Session, Depends(get_db)], action: str | None = None, user_id: uuid.UUID | None = None):
    return admin_service.list_audit_logs(db, user_id=user_id, action=action)
```

**Key lines:** `AdminOnly` guards the router (Phase 14, layer 1); the **self-lockout guards** (`SELF_ROLE_CHANGE`, `LAST_ADMIN`, `SELF_DEACTIVATE`) are Phase 14.2 layer 3 — easy to forget, embarrassing when you hit them; every mutation calls `log_audit` with the actor, so role changes are traceable (Phase 14.2 layer 2).

**Common mistakes:** forgetting the audit call; letting an admin demote the last admin or lock themselves out; returning password hashes in the user list (whitelist a `UserOut` schema here too); trusting a role string without validating it against the enum.

**How to test:** admin lists users, changes a patient's role → row appears in audit logs; non-admin → 403; self-role-change → 403; demoting the only admin → 409.

---

## 13. Appointments

**What it does:** request, list, and transition appointments — with a legal-transitions state machine and role-aware behavior.

**Where it belongs:** `app/services/appointment_service.py`, `app/api/routers/appointments.py`.

```python
# app/services/appointment_service.py
import uuid
from datetime import datetime, timezone
from sqlalchemy import select
from sqlalchemy.orm import Session
from app.core.errors import ConflictError, NotFoundError, PermissionDeniedError
from app.models.operations import Appointment, AppointmentStatus
from app.models.user import Role, User
from app.schemas.appointment import AppointmentCreate

# The state machine from Phase 11.7 — single source of truth
TRANSITIONS: dict[str, set[str]] = {
    AppointmentStatus.REQUESTED.value: {AppointmentStatus.CONFIRMED.value, AppointmentStatus.CANCELLED.value},
    AppointmentStatus.CONFIRMED.value: {AppointmentStatus.COMPLETED.value, AppointmentStatus.CANCELLED.value, AppointmentStatus.NO_SHOW.value},
    AppointmentStatus.COMPLETED.value: set(),
    AppointmentStatus.CANCELLED.value: set(),
    AppointmentStatus.NO_SHOW.value: set(),
}

DOCTOR_ACTIONS = {AppointmentStatus.CONFIRMED.value, AppointmentStatus.COMPLETED.value, AppointmentStatus.NO_SHOW.value}

def request_appointment(db: Session, user: User, data: AppointmentCreate) -> Appointment:
    if user.role != Role.PATIENT.value or user.patient is None:
        raise PermissionDeniedError("Only patients can request appointments")
    if data.scheduled_at <= datetime.now(timezone.utc):
        raise ConflictError("Appointment must be in the future", code="PAST_APPOINTMENT")
    row = Appointment(
        patient_id=user.patient.id,
        doctor_id=data.doctor_id,
        department_id=data.department_id,
        scheduled_at=data.scheduled_at,
        reason=data.reason,
    )
    db.add(row); db.commit(); db.refresh(row)
    return row

def list_appointments(db: Session, user: User) -> list[Appointment]:
    if user.role == Role.PATIENT.value:
        return list(db.scalars(select(Appointment).where(Appointment.patient_id == user.patient.id).order_by(Appointment.scheduled_at)))
    if user.role == Role.DOCTOR.value:
        return list(db.scalars(select(Appointment).where(Appointment.doctor_id == user.doctor.id).order_by(Appointment.scheduled_at)))
    return list(db.scalars(select(Appointment).order_by(Appointment.scheduled_at)))  # management/admin

def _load_and_authorize(db: Session, user: User, appointment_id: uuid.UUID) -> Appointment:
    appt = db.get(Appointment, appointment_id)
    if appt is None:
        raise NotFoundError("Appointment not found")
    if user.role == Role.PATIENT.value and appt.patient_id != user.patient.id:
        raise PermissionDeniedError("Not your appointment")
    if user.role == Role.DOCTOR.value and appt.doctor_id != user.doctor.id:
        raise PermissionDeniedError("Not your appointment")
    return appt

def transition(db: Session, user: User, appointment_id: uuid.UUID, new_status: str) -> Appointment:
    appt = _load_and_authorize(db, user, appointment_id)
    if new_status not in TRANSITIONS.get(appt.status, set()):
        raise ConflictError(f"Cannot move appointment from {appt.status} to {new_status}", code="ILLEGAL_TRANSITION")
    if new_status in DOCTOR_ACTIONS and user.role not in (Role.DOCTOR.value, Role.MANAGEMENT.value, Role.ADMIN.value):
        raise PermissionDeniedError("Only staff may confirm or complete appointments")
    if new_status == AppointmentStatus.CANCELLED.value and user.role == Role.PATIENT.value:
        if appt.status not in (AppointmentStatus.REQUESTED.value, AppointmentStatus.CONFIRMED.value):
            raise ConflictError("This appointment can no longer be cancelled", code="ILLEGAL_TRANSITION")
    appt.status = new_status
    db.commit(); db.refresh(appt)
    return appt
```

```python
# app/schemas/appointment.py
import uuid
from datetime import datetime
from pydantic import BaseModel, ConfigDict

class AppointmentCreate(BaseModel):
    doctor_id: uuid.UUID
    department_id: uuid.UUID | None = None
    scheduled_at: datetime
    reason: str | None = None

class AppointmentStatusUpdate(BaseModel):
    status: str

class AppointmentOut(AppointmentCreate):
    model_config = ConfigDict(from_attributes=True)
    id: uuid.UUID
    patient_id: uuid.UUID
    status: str
```

```python
# app/api/routers/appointments.py
import uuid
from typing import Annotated
from fastapi import APIRouter, Depends, status
from sqlalchemy.orm import Session
from app.db.session import get_db
from app.api.deps import CurrentUser
from app.models.user import User
from app.schemas.appointment import AppointmentCreate, AppointmentOut, AppointmentStatusUpdate
from app.services import appointment_service

router = APIRouter()

@router.post("", response_model=AppointmentOut, status_code=status.HTTP_201_CREATED)
def create(data: AppointmentCreate, user: CurrentUser, db: Annotated[Session, Depends(get_db)]):
    return appointment_service.request_appointment(db, user, data)

@router.get("", response_model=list[AppointmentOut])
def list(user: CurrentUser, db: Annotated[Session, Depends(get_db)]):
    return appointment_service.list_appointments(db, user)

@router.patch("/{appointment_id}", response_model=AppointmentOut)
def update_status(appointment_id: uuid.UUID, data: AppointmentStatusUpdate, user: CurrentUser, db: Annotated[Session, Depends(get_db)]):
    return appointment_service.transition(db, user, appointment_id, data.status)
```

**Key lines:** the `TRANSITIONS` table is the **single source of truth** for legal status changes — a fresh status string is rejected by `ConflictError`; `_load_and_authorize` enforces object-level rules per role (patients touch only their own, doctors only theirs); doctor-only actions are role-checked again inside the service (defense in depth).

**Common mistakes:** letting clients set any status (the state machine fixes this); a patient confirming their own appointment; trusting `patient_id` in the create body; forgetting that management/admin listing shows *all* appointments (fine) but must still use `AppointmentOut`, never raw models.

**How to test:** patient requests → `requested`; doctor confirms → `confirmed`; patient cancels → `cancelled`; `completed` → `requested` → 409; patient confirms → 403; another patient's appointment → 403.

---

## 14. Medical Documents + 15. File Storage

**What it does:** validates and stores an uploaded file, records metadata, kicks off async processing (extract → AI → result), and issues signed download URLs. Storage never touches route code directly.

**Where it belongs:** `app/services/storage_service.py` (storage wrapper), `app/services/document_service.py` (pipeline), `app/api/routers/documents.py`.

```python
# app/services/storage_service.py  (Supabase Storage via its REST API)
import httpx
from app.core.config import settings

class StorageService:
    def __init__(self, url: str | None = None, service_key: str | None = None, bucket: str | None = None):
        self.url = (url or settings.supabase_url).rstrip("/")
        self.service_key = service_key or settings.supabase_service_key
        self.bucket = bucket or settings.storage_bucket

    def _headers(self) -> dict:
        return {"Authorization": f"Bearer {self.service_key}", "apikey": self.service_key}

    def upload(self, key: str, data: bytes, content_type: str) -> None:
        r = httpx.post(
            f"{self.url}/storage/v1/object/{self.bucket}/{key}",
            headers={**self._headers(), "Content-Type": content_type},
            content=data,
        )
        r.raise_for_status()

    def create_signed_url(self, key: str, expires_in: int = 900) -> str:
        r = httpx.post(
            f"{self.url}/storage/v1/object/sign/{self.bucket}/{key}",
            headers=self._headers(),
            json={"expiresIn": expires_in},
        )
        r.raise_for_status()
        return f"{self.url}{r.json()['signedURL']}"

storage = StorageService()
```

```python
# app/services/document_service.py
import uuid
from fastapi import UploadFile
from sqlalchemy import select
from sqlalchemy.orm import Session
from app.core.access import can_access_patient
from app.core.errors import NotFoundError, ValidationError
from app.models.operations import DocumentStatus, MedicalDocument
from app.models.user import User
from app.services.storage_service import storage

MAX_SIZE = 10 * 1024 * 1024  # 10 MB
ALLOWED_EXTENSIONS = {"pdf": "application/pdf", "png": "image/png", "jpg": "image/jpeg", "jpeg": "image/jpeg"}

def upload_document(db: Session, user: User, patient_id: uuid.UUID, document_type: str, file: UploadFile) -> MedicalDocument:
    patient = can_access_patient(db, user, patient_id)  # object-level gate

    ext = (file.filename or "").rsplit(".", 1)[-1].lower()
    if ext not in ALLOWED_EXTENSIONS:
        raise ValidationError("Unsupported file type", code="UNSUPPORTED_TYPE")
    expected = ALLOWED_EXTENSIONS[ext]
    if file.content_type != expected:
        raise ValidationError("File type does not match its content", code="TYPE_MISMATCH")

    data = file.file.read(MAX_SIZE + 1)
    if len(data) > MAX_SIZE:
        raise ValidationError("File exceeds 10 MB", code="FILE_TOO_LARGE")
    # MVP magic-byte check: verify PDF starts with %PDF
    if expected == "application/pdf" and not data.startswith(b"%PDF"):
        raise ValidationError("Not a valid PDF", code="INVALID_FILE")

    key = f"patient-{patient.id}/{uuid.uuid4()}.{ext}"   # server-generated key
    storage.upload(key, data, expected)

    doc = MedicalDocument(
        patient_id=patient.id,
        document_type=document_type,
        original_filename=file.filename or "untitled",
        stored_object_key=key,
        file_size_bytes=len(data),
        content_type=expected,
        processing_status=DocumentStatus.PENDING.value,
    )
    db.add(doc); db.commit(); db.refresh(doc)
    return doc

def list_documents(db: Session, user: User, patient_id: uuid.UUID) -> list[MedicalDocument]:
    can_access_patient(db, user, patient_id)
    return list(db.scalars(select(MedicalDocument).where(MedicalDocument.patient_id == patient_id).order_by(MedicalDocument.created_at.desc())))

def download_url(db: Session, user: User, document_id: uuid.UUID) -> str:
    doc = db.get(MedicalDocument, document_id)
    if doc is None:
        raise NotFoundError("Document not found")
    can_access_patient(db, user, doc.patient_id)   # check the OWNING patient
    return storage.create_signed_url(doc.stored_object_key)
```

```python
# app/api/routers/documents.py
import uuid
from typing import Annotated
from fastapi import APIRouter, BackgroundTasks, Depends, File, Form, UploadFile, status
from sqlalchemy.orm import Session
from app.db.session import get_db
from app.api.deps import CurrentUser, DoctorOrAbove
from app.models.user import User
from app.schemas.document import DocumentOut, DownloadOut
from app.services import document_service
from app.ai.analyzer import process_document_async

router = APIRouter()

@router.post("/patients/{patient_id}/documents", response_model=DocumentOut, status_code=status.HTTP_201_CREATED)
def upload(
    patient_id: uuid.UUID,
    document_type: Annotated[str, Form()],
    file: Annotated[UploadFile, File()],
    background: BackgroundTasks,
    user: CurrentUser,
    db: Annotated[Session, Depends(get_db)],
):
    doc = document_service.upload_document(db, user, patient_id, document_type, file)
    background.add_task(process_document_async, doc.id)  # Phase 15.5: async processing
    return doc

@router.get("/patients/{patient_id}/documents", response_model=list[DocumentOut])
def documents(patient_id: uuid.UUID, user: DoctorOrAbove, db: Annotated[Session, Depends(get_db)]):
    return document_service.list_documents(db, user, patient_id)

@router.get("/documents/{document_id}/download", response_model=DownloadOut)
def download(document_id: uuid.UUID, user: CurrentUser, db: Annotated[Session, Depends(get_db)]):
    return DownloadOut(url=document_service.download_url(db, user, document_id))
```

```python
# app/schemas/document.py
import uuid
from datetime import datetime
from pydantic import BaseModel, ConfigDict

class DocumentOut(BaseModel):
    model_config = ConfigDict(from_attributes=True)
    id: uuid.UUID
    document_type: str
    original_filename: str
    file_size_bytes: int
    content_type: str
    processing_status: str
    error_message: str | None = None
    created_at: datetime

class DownloadOut(BaseModel):
    url: str
```

**Key lines:** `can_access_patient` on the *owning* patient gates even the signed-URL endpoint (authorization before transport, Phase 18.3); the storage key is **server-generated** (`patient-{id}/{uuid}.{ext}`) — path traversal is impossible and the original filename is only metadata; validation checks extension *and* declared type *and* magic bytes, with a hard size cap read in one chunk; `BackgroundTasks` keeps the response fast (upgrade to a queue per Phase 15.5).

**Common mistakes:** storing the user's filename as the key; trusting `file.content_type` alone; no size cap (memory blowups); issuing signed URLs without the object-level check; leaking the storage service key to the frontend.

**How to test:** upload a real PDF → 201, metadata row `pending`, object in the private bucket; a `.exe` renamed `.pdf` → rejected by the magic-byte check; an unauthorized user gets 403 on download; the signed URL opens the file; after the pipeline runs, status is `completed` or `failed` with a reason.

---

## 16. AI Service

**What it does:** the *only* place that talks to an LLM. It owns the prompts, requests **structured JSON**, validates the result with Pydantic, and fails gracefully. Routes and document processing depend on this abstraction — so tests can swap in a fake.

**Where it belongs:** `app/ai/client.py` (the LLM wrapper), `app/ai/schemas.py` (output models), `app/ai/prompts.py` (prompt text), `app/ai/analyzer.py` + `app/ai/assistant.py` (use cases).

```python
# app/ai/schemas.py
from pydantic import BaseModel, Field

class Finding(BaseModel):
    text: str
    section: str | None = None
    severity: str = Field(default="low", pattern="^(low|moderate|high)$")

class AnalysisResult(BaseModel):
    summary: str
    findings: list[Finding]
    flagged_abnormalities: list[str] = []
    questions_for_doctor: list[str] = []

class ChatResult(BaseModel):
    reply: str
    citations: list[str] = []      # document/analysis IDs
    needs_escalation: bool = False
```

```python
# app/ai/prompts.py
ANALYZER_SYSTEM = """
You are a medical document summarizer for the HealthAI platform.
You are NOT a doctor and you do NOT diagnose or prescribe.
Rules:
- Summarize only what the document text actually says.
- Never invent findings, values, or diagnoses absent from the text.
- Mark anything unclear or uncertain explicitly as uncertain.
- List questions the patient may want to ask their doctor.
- Respond ONLY as valid JSON matching the required schema.
"""

ASSISTANT_SYSTEM = """
You are the HealthAI assistant. You provide information and decision support, never diagnosis or treatment advice.
Rules:
- Answer only from the provided context; if the context cannot answer, say so.
- For anything urgent (chest pain, severe bleeding, suicidal thoughts), tell the user to seek emergency care immediately.
- Include a short disclaimer that this is information, not medical advice.
- Never invent citations; only reference the source IDs provided in context.
"""
```

```python
# app/ai/client.py
from typing import Protocol
from openai import OpenAI
from app.core.config import settings
from app.ai.schemas import AnalysisResult, ChatResult

class AIProvider(Protocol):
    def analyze_document(self, text: str) -> AnalysisResult: ...
    def chat(self, *, context: list[dict], question: str) -> ChatResult: ...

class OpenAIProvider:
    def __init__(self):
        self.client = OpenAI(api_key=settings.openai_api_key, base_url=settings.openai_base_url)
        self.model = settings.ai_model

    def analyze_document(self, text: str) -> AnalysisResult:
        response = self.client.beta.chat.completions.parse(
            model=self.model,
            messages=[
                {"role": "system", "content": ANALYZER_SYSTEM},
                {"role": "user", "content": text[:20000]},   # hard cap on input
            ],
            response_format=AnalysisResult,
        )
        parsed = response.choices[0].message.parsed
        if parsed is None:
            raise RuntimeError("Model returned unparseable output")
        return parsed

    def chat(self, *, context: list[dict], question: str) -> ChatResult:
        response = self.client.beta.chat.completions.parse(
            model=self.model,
            messages=[
                {"role": "system", "content": ASSISTANT_SYSTEM},
                *context,   # recent messages + retrieved context, role/content only
                {"role": "user", "content": question},
            ],
            response_format=ChatResult,
        )
        parsed = response.choices[0].message.parsed
        if parsed is None:
            raise RuntimeError("Model returned unparseable output")
        return parsed

class FakeAIProvider:   # for tests and offline dev
    def analyze_document(self, text: str) -> AnalysisResult:
        return AnalysisResult(summary="Fake summary", findings=[], flagged_abnormalities=[])
    def chat(self, *, context, question):
        return ChatResult(reply="This is a fake response.", citations=[])

def get_ai_provider() -> AIProvider:
    if settings.environment == "testing" or settings.openai_api_key is None:
        return FakeAIProvider()
    return OpenAIProvider()
```

```python
# app/ai/analyzer.py  (called by the async document pipeline)
import uuid
from sqlalchemy.orm import Session
from app.ai.client import get_ai_provider
from app.models.operations import DocumentStatus, DocumentAnalysis, MedicalDocument
from app.db.session import SessionLocal

def process_document_async(document_id: uuid.UUID):
    """Background task: extract text → AI analysis → stored result."""
    db = SessionLocal()
    try:
        doc = db.get(MedicalDocument, document_id)
        if doc is None:
            return
        doc.processing_status = DocumentStatus.PROCESSING.value
        db.commit()
        try:
            text = extract_text(doc)          # pypdf / OCR — Phase 15.6
            result = get_ai_provider().analyze_document(text)
            db.add(DocumentAnalysis(
                document_id=doc.id,
                summary=result.summary,
                findings=[f.model_dump() for f in result.findings],
                flagged_abnormalities=result.flagged_abnormalities,
                questions_for_doctor=result.questions_for_doctor,
            ))
            doc.processing_status = DocumentStatus.COMPLETED.value
        except Exception as exc:               # log, then record a clean failure
            doc.processing_status = DocumentStatus.FAILED.value
            doc.error_message = f"{type(exc).__name__}: {exc}"
        db.commit()
    finally:
        db.close()
```

**Key lines:** the `AIProvider` protocol is the seam — routes and the pipeline never import `openai`; `response_format` + Pydantic gives **validated structured output** (Phase 16.3); prompts are versioned strings in `prompts.py`, not inline soup; input is hard-capped (`text[:20000]`) and the whole pipeline degrades to `failed` + a stored error message, never a crash.

**Common mistakes:** calling the LLM from a route; storing raw model output instead of the parsed `AnalysisResult`; no retry/timeout handling (add one retry with a short backoff before failing); forgetting that `message.parsed` can be `None`; shipping without the disclaimer in `ASSISTANT_SYSTEM`.

**How to test:** with `environment=testing` (or no API key), the whole pipeline runs on the fake; with a real key, upload → `completed` with a valid analysis; force an AI exception → document `failed` with a stored reason.

---

## 17. Error Handling

**What it does:** one error hierarchy, one response shape, and the exception handlers that translate them — plus the `main.py` that assembles the app (CORS, routers, handlers, health).

**Where it belongs:** `app/core/errors.py`, `app/api/errors.py` (handlers), `app/main.py`.

```python
# app/core/errors.py
class AppError(Exception):
    status_code = 500
    code = "internal_error"
    def __init__(self, message: str, *, code: str | None = None):
        super().__init__(message)
        self.message = message
        if code:
            self.code = code

class UnauthorizedError(AppError):     status_code = 401; code = "unauthorized"
class PermissionDeniedError(AppError): status_code = 403; code = "forbidden"
class NotFoundError(AppError):         status_code = 404; code = "not_found"
class ConflictError(AppError):         status_code = 409; code = "conflict"
class ValidationError(AppError):       status_code = 422; code = "validation_error"
```

```python
# app/api/errors.py
import logging
from fastapi import FastAPI, Request
from fastapi.exceptions import RequestValidationError
from fastapi.responses import JSONResponse
from app.core.errors import AppError

logger = logging.getLogger("app")

def error_body(message: str, code: str, field: str | None = None) -> dict:
    return {"detail": message, "code": code, "field": field}

def register_exception_handlers(app: FastAPI) -> None:
    @app.exception_handler(AppError)
    async def handle_app_error(request: Request, exc: AppError):
        return JSONResponse(status_code=exc.status_code, content=error_body(exc.message, exc.code))

    @app.exception_handler(RequestValidationError)
    async def handle_validation(request: Request, exc: RequestValidationError):
        first = exc.errors()[0] if exc.errors() else {}
        return JSONResponse(
            status_code=422,
            content=error_body(
                f"Invalid input: {first.get('msg', 'validation error')}",
                "validation_error",
                str(first.get("loc", [None])[-1]),
            ),
        )

    @app.exception_handler(Exception)
    async def handle_unexpected(request: Request, exc: Exception):
        logger.exception("Unhandled error on %s %s", request.method, request.url.path)
        return JSONResponse(
            status_code=500,
            content=error_body("An unexpected error occurred. Please try again later.", "internal_error"),
        )
```

```python
# app/main.py
from typing import Annotated
from fastapi import Depends, FastAPI
from fastapi.middleware.cors import CORSMiddleware
from sqlalchemy import text
from sqlalchemy.orm import Session
from app.api.errors import register_exception_handlers
from app.api.routers import admin, appointments, auth, doctors, documents, management, patients
from app.core.config import settings
from app.db.session import get_db
from app import models  # noqa: F401  — registers all models with Base.metadata

app = FastAPI(title=settings.app_name, version="0.1.0", description="HealthAI backend API — healthcare assistance platform")

app.add_middleware(
    CORSMiddleware,
    allow_origins=settings.cors_origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

register_exception_handlers(app)

app.include_router(auth.router, prefix="/auth", tags=["auth"])
app.include_router(patients.router, prefix="/patients", tags=["patients"])
app.include_router(doctors.router, prefix="/doctors", tags=["doctors"])
app.include_router(appointments.router, prefix="/appointments", tags=["appointments"])
app.include_router(documents.router, prefix="", tags=["documents"])
app.include_router(management.router, prefix="/management", tags=["management"])
app.include_router(admin.router, prefix="/admin", tags=["admin"])

@app.get("/health")
def health(db: Annotated[Session, Depends(get_db)]):
    db.execute(text("SELECT 1"))   # proves the DB connection for the platform's health check
    return {"status": "ok"}
```

**Key lines:** services raise business errors (`NotFoundError("Patient not found")`) and the handler translates them — HTTP lives in exactly one place; validation errors are flattened to a consistent shape; the catch-all `Exception` handler logs the traceback server-side and returns a **generic** 500 (never leak internals); `allow_origins=settings.cors_origins` comes from env (never `*` with credentials); `from app import models` before router imports guarantees Alembic and `Base.metadata` see every model.

**Common mistakes:** raising `HTTPException` inside services (couples services to HTTP); leaking stack traces in 500 bodies; forgetting the validation handler (Pydantic's default 422 is fine but inconsistent with your shape); wildcard CORS.

**How to test:** every error path in §19 of the main guide returns the `{detail, code, field}` shape; trigger a 500 and confirm the body is generic while the log has the trace.

---

## 18. Testing

**What it does:** a pytest harness with a **separate test database**, dependency overrides, and the security tests that matter (auth + BOLA).

**Where it belongs:** `tests/conftest.py`, `tests/test_auth.py`, `tests/test_bola.py`.

```python
# tests/conftest.py
import os
import pytest
from fastapi.testclient import TestClient
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from app.db.base import Base
from app.db.session import get_db
from app.main import app

TEST_DATABASE_URL = os.environ["TEST_DATABASE_URL"]   # NEVER the real one (Phase 21.2)

engine = create_engine(TEST_DATABASE_URL)
TestingSessionLocal = sessionmaker(bind=engine, autoflush=False, autocommit=False)

def override_get_db():
    db = TestingSessionLocal()
    try:
        yield db
    finally:
        db.close()

app.dependency_overrides[get_db] = override_get_db

@pytest.fixture(scope="session", autouse=True)
def schema():
    Base.metadata.drop_all(engine)
    Base.metadata.create_all(engine)
    yield
    Base.metadata.drop_all(engine)

@pytest.fixture()
def client():
    return TestClient(app)

def register_and_login(client: TestClient, email: str, password: str = "password123") -> str:
    client.post("/auth/register", json={"full_name": "Test User", "email": email, "password": password})
    r = client.post("/auth/login", data={"username": email, "password": password})
    return r.json()["access_token"]

@pytest.fixture()
def patient_a_token(client):
    return register_and_login(client, "patient_a@example.com")

@pytest.fixture()
def patient_b_token(client):
    return register_and_login(client, "patient_b@example.com")

def auth(token: str) -> dict:
    return {"Authorization": f"Bearer {token}"}
```

```python
# tests/test_auth.py
from tests.conftest import auth, register_and_login

def test_register_and_login(client):
    token = register_and_login(client, "user@example.com")
    me = client.get("/auth/me", headers=auth(token))
    assert me.status_code == 200
    assert me.json()["email"] == "user@example.com"

def test_wrong_password_rejected(client):
    register_and_login(client, "u2@example.com")
    r = client.post("/auth/login", data={"username": "u2@example.com", "password": "wrongpass"})
    assert r.status_code == 401

def test_missing_token_rejected(client):
    assert client.get("/auth/me").status_code == 401

def test_expired_token_rejected(client):
    # mint a token with exp in the past via the app's own helper
    import uuid
    from datetime import timedelta
    from app.core.jwt import _create_token
    expired = _create_token(uuid.uuid4(), "patient", "access", timedelta(minutes=-5))
    assert client.get("/auth/me", headers=auth(expired)).status_code == 401
```

```python
# tests/test_bola.py
from tests.conftest import auth

def _patient_id_of(client, token):
    return client.get("/patients/me", headers=auth(token)).json()["id"]

def test_patient_a_cannot_read_patient_b_metrics(client, patient_a_token, patient_b_token):
    b_id = _patient_id_of(client, patient_b_token)
    r = client.get(f"/patients/{b_id}/metrics", headers=auth(patient_a_token))
    assert r.status_code == 403

def test_patient_cannot_add_metric_to_other_patient(client, patient_a_token, patient_b_token):
    b_id = _patient_id_of(client, patient_b_token)
    r = client.post(
        f"/patients/{b_id}/metrics",
        headers=auth(patient_a_token),
        json={"metric_type": "heart_rate", "value": 72, "unit": "bpm", "recorded_at": "2026-01-01T10:00:00Z"},
    )
    assert r.status_code == 403

def test_patient_cannot_reach_doctor_endpoints(client, patient_a_token):
    r = client.get("/doctors/patients", headers=auth(patient_a_token))
    assert r.status_code == 403

def test_anonymous_cannot_access_appointments(client):
    assert client.get("/appointments").status_code == 401
```

**Key lines:** `TEST_DATABASE_URL` comes from env and the fixtures **drop and recreate the schema per session** — production data is untouchable by construction (Phase 21.2); `app.dependency_overrides[get_db]` points every route at the test DB; the expired-token test mints its own token with a negative lifetime — no waiting; the BOLA tests encode the Phase 9 matrix directly.

**Common mistakes:** running tests against the real DB (the `TEST_DATABASE_URL` env guard); registering the same email across tests (unique constraint — use distinct emails per test); forgetting `data=` (form) for `/auth/login` vs `json=` for `/auth/register`; asserting on `status_code` instead of the documented error body.

**How to test:** `TEST_DATABASE_URL=... pytest` — green, with the dev/prod DB untouched. `pip-audit` isn't part of the suite but run it before release (Phase 22.6).

---

## 19. Docker

**What it does:** packages the app so the same image runs anywhere — your laptop and the cloud host (Phase 25.3).

**Where it belongs:** `Dockerfile`, `.dockerignore`, `docker-compose.yml` (project root).

```dockerfile
# Dockerfile
FROM python:3.12-slim
ENV PYTHONDONTWRITEBYTECODE=1 PYTHONUNBUFFERED=1
WORKDIR /app

RUN adduser --disabled-password --gecos "" appuser   # non-root (Phase 25.2)

COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY . .
USER appuser
EXPOSE 8000

CMD ["uvicorn", "app.main:app", "--host", "0.0.0.0", "--port", "8000", "--workers", "2"]
```

```dockerignore
.venv
__pycache__
*.pyc
.env
.git
.pytest_cache
```

```yaml
# docker-compose.yml (local development / demo only — prod DB stays on Supabase)
services:
  app:
    build: .
    ports:
      - "8000:8000"
    env_file: .env
    depends_on:
      db:
        condition: service_healthy
    healthcheck:
      test: ["CMD", "python", "-c", "import urllib.request; urllib.request.urlopen('http://localhost:8000/health')"]
      interval: 30s
      timeout: 5s
      retries: 3

  db:
    image: postgres:16
    environment:
      POSTGRES_USER: healthai
      POSTGRES_PASSWORD: healthai_dev_pw
      POSTGRES_DB: healthai
    ports:
      - "5432:5432"
    healthcheck:
      test: ["CMD-SHELL", "pg_isready -U healthai"]
      interval: 5s
      timeout: 3s
      retries: 5
```

**Key lines:** the non-root `appuser`; `--workers 2` (multiple workers, no reload — never run `--reload` in a container); `.dockerignore` keeps secrets and junk out of the build context; the compose `db` is a *local stand-in* — your `.env` `DATABASE_URL` decides whether the app talks to it or to Supabase.

**Common mistakes:** baking `.env` into the image (copying `.env` — the `COPY . .` picks it up unless `.dockerignore` excludes it — so the ignore file matters!); running as root; `--reload` in the image; port bind mismatches.

**How to test:** `docker compose up --build` → `/health` 200, `/docs` renders; `docker run` the image without `.env` and confirm it fails loudly on the missing `DATABASE_URL` (proving secrets are injected, not baked).

---

## 20. Deployment

**What it does:** puts the container in the cloud with the right env, health checks, and HTTPS.

**Where it belongs:** your hosting platform (Render/Railway/Fly.io — Phase 25.4) + the env vars from Phase 2/3.

```yaml
# render.yaml (Render — example; Railway/Fly.io have equivalent UIs)
services:
  - type: web
    name: healthai-api
    runtime: docker
    plan: free
    healthCheckPath: /health
    envVars:
      - key: DATABASE_URL
        sync: false          # set in the dashboard, never in the repo
      - key: JWT_SECRET
        sync: false
      - key: CORS_ORIGINS
        value: https://healthai.example.com
      - key: OPENAI_API_KEY
        sync: false
      - key: SUPABASE_URL
        sync: false
      - key: SUPABASE_SERVICE_KEY
        sync: false
      - key: ENVIRONMENT
        value: production
```

**The production deployment checklist (from Phase 25.5, made concrete):**

1. **Env vars:** set every one in the platform's secret store — `DATABASE_URL` (prod Supabase), `JWT_SECRET` (**a fresh strong secret, never the dev one**), `OPENAI_API_KEY`, `SUPABASE_URL`, `SUPABASE_SERVICE_KEY`, `CORS_ORIGINS` (the real frontend origin), `ENVIRONMENT=production`, `LOG_LEVEL=INFO`.
2. **Migrations:** run `alembic upgrade head` as a deploy step (a start command like `alembic upgrade head && uvicorn ...`), or in CI — never by hand in prod.
3. **Health check:** the platform pings `/health` (which verifies DB connectivity) — wire it as shown.
4. **HTTPS:** platform-managed; no plain HTTP anywhere.
5. **Logging:** your JSON logs go to stdout, which the platform captures.
6. **Verify from outside:** `curl https://your-app/health`, `curl https://your-app/docs`, and a real register → login → authed request from your machine.
7. **Secrets hygiene:** confirm the deployed env vars are NOT in the image (`docker run` without env fails) and not in git.

**Common mistakes:** deploying with dev CORS origins (frontend blocked); a stale `JWT_SECRET` shared with dev (rotate on first suspicion); forgetting migrations on deploy (schema mismatch → 500s); health check missing (platform kills/restarts a healthy app); env var typos (pydantic-settings fails fast — that's the point).

**How to test:** the full external verification in step 6, plus a browser session logged in against the deployed API.

---

# 🐛 Troubleshooting Guide

Every entry follows the same shape: **Problem / Symptoms / Likely Causes / How to Diagnose / How to Fix / How to Prevent**. Always start at the Debugging Method (symptom → logs → layer → reproduce), then find your case here.

## Environment Problems

**Problem: Python version issues**
- *Symptoms:* `pip install` errors about missing wheels or "Python 3.x is not supported"; code using new syntax fails with `SyntaxError`.
- *Likely causes:* wrong Python on PATH; mixing global and venv Python.
- *How to diagnose:* `python --version` *inside the activated venv* (`which python`).
- *How to fix:* create the venv with an explicit interpreter: `python3.12 -m venv .venv`.
- *How to prevent:* pin the version in your README and `.python-version`; never install project deps globally.

**Problem: Virtual environment problems**
- *Symptoms:* `pip` installs but the app can't import the packages; `uvicorn` not found.
- *Likely causes:* you're running outside the venv; multiple venvs; shell not activated.
- *How to diagnose:* `which pip` vs `which python` — do they point into the same `.venv`?
- *How to fix:* `source .venv/Scripts/activate` (Windows bash) or `source .venv/bin/activate` (macOS/Linux), then `pip install -r requirements.txt` again.
- *How to prevent:* make activation the first step of every work session; add it to your editor's terminal settings.

**Problem: Package installation problems**
- *Symptoms:* install fails on `psycopg`/`bcrypt`/`pydantic-core`; wheels not found.
- *Likely causes:* too-new or too-old Python (pydantic-core needs a wheel for your exact version); proxy/network issues; pip cache corruption.
- *How to diagnose:* the error names the package — check its Python requirement; `pip install --no-cache-dir <pkg>`.
- *How to fix:* use a supported Python (3.11/3.12), upgrade pip (`pip install -U pip`), retry with `--no-cache-dir`.
- *How to prevent:* stick to the pinned versions in `requirements.txt`; don't chase the newest Python mid-project.

## FastAPI Problems

**Problem: Server won't start**
- *Symptoms:* `uvicorn` exits immediately; traceback at import time.
- *Likely causes:* syntax error in a module; missing dependency; an env var that fails settings loading; port already in use.
- *How to diagnose:* read the first traceback lines — they name the file and line; `python -c "from app.main import app"`.
- *How to fix:* fix the named issue; `kill` the process on the port (`lsof -i :8000` / `netstat`) if that's it.
- *How to prevent:* run the import check before starting uvicorn; keep `main.py` small.

**Problem: Import errors (circular imports)**
- *Symptoms:* `ImportError: cannot import name ... from partially initialized module`.
- *Likely causes:* a module imports another module that imports it back (e.g., a router importing a service that imports the router).
- *How to diagnose:* the traceback shows the import cycle — A imports B imports A.
- *How to fix:* move the shared piece (schemas, models) to its own module; import inside functions when truly needed; keep the one-way rule from Phase 2.7.
- *How to prevent:* respect the dependency arrow (routers → services → models; schemas standalone).

**Problem: Route not appearing in Swagger**
- *Symptoms:* you wrote a route, `/docs` doesn't show it, calling it 404s.
- *Likely causes:* router not included in `main.py`; wrong prefix; decorator path mismatch; file not imported.
- *How to diagnose:* grep for `include_router` in `main.py`; compare the decorator path to what you curl.
- *How to fix:* include the router; fix the prefix/path; restart the dev server (the `--reload` watcher can miss new files).
- *How to prevent:* add every router to `main.py` the moment you create it; check `/docs` after each new router.

**Problem: Dependency errors at runtime**
- *Symptoms:* `FastAPI dependency ... failed to run`; endpoints 500 when the dependency runs.
- *Likely causes:* the dependency raises (token decode, DB session, settings) and you didn't handle it.
- *How to diagnose:* the logs name the dependency and exception; call the dependency path directly in a script.
- *How to fix:* make the dependency raise a proper `AppError`/HTTPException (401/403) instead of leaking; fix the root cause named in the trace.
- *How to prevent:* test every dependency with its failure mode (bad token, closed DB) as a test case.

## PostgreSQL Problems

**Problem: Connection refused**
- *Symptoms:* `OperationalError: connection refused`; app hangs then fails.
- *Likely causes:* wrong host/port; IPv4-only host using an IPv6-only direct endpoint; provider paused the project; wrong region endpoint.
- *How to diagnose:* `psql` or a raw `psycopg` probe with the exact URL; check the provider dashboard for the status.
- *How to fix:* use the session-mode pooler endpoint (`*.pooler.supabase.com:5432`) on IPv4-only hosts; unpause/restart the project; double-check the region in the URL.
- *How to prevent:* test the raw connection (Phase 3.7) *before* wiring SQLAlchemy; document which endpoint you chose.

**Problem: Authentication failed**
- *Symptoms:* `FATAL: password authentication failed`; 28P01 errors.
- *Likely causes:* wrong password; special characters in the password not percent-encoded in the URL (`@`, `#`, `/`); wrong role name in the connection string.
- *How to diagnose:* decode your URL by hand — is the password intact? Try the dashboard's own "connect" snippet.
- *How to fix:* percent-encode specials; reset the password in the dashboard; copy the URL fresh from the dashboard.
- *How to prevent:* store the URL in `.env` once it works and never hand-retype it.

**Problem: SSL errors**
- *Symptoms:* `SSL error: sslmode value "require" invalid`; `connection requires SSL`.
- *Likely causes:* missing/invalid `sslmode` fragment; old driver behavior.
- *How to diagnose:* try `?sslmode=require` on the URL; check driver version.
- *How to fix:* add `?sslmode=require`; upgrade `psycopg` (v3 negotiates SSL by default).
- *How to prevent:* keep the fragment in `.env.example` so it's never lost.

**Problem: Connection pool issues**
- *Symptoms:* `too many connections`; requests stall; `TimeoutError: QueuePool limit`.
- *Likely causes:* pool size too large for the provider's limit; leaked sessions; multiple processes each with their own pool.
- *How to diagnose:* count open connections in the dashboard; grep your code for `SessionLocal()` outside the dependency.
- *How to fix:* keep `pool_size` small (5–10); ensure `get_db` closes in `finally`; reduce workers if each opens a pool.
- *How to prevent:* treat `get_db` as the *only* way to get a session; set `pool_pre_ping=True`.

## SQLAlchemy Problems

**Problem: Model errors**
- *Symptoms:* `ArgumentError: Mapper ... could not assemble`; `AmbiguousForeignKeysError`; missing `__tablename__`.
- *Likely causes:* two FKs between the same tables without `foreign_keys=`; typo in a relationship target; model not imported.
- *How to diagnose:* the error names the mapper and the ambiguous column(s).
- *How to fix:* pass `foreign_keys=[...]` on the relationship; fix the target class name; import the model.
- *How to prevent:* declare FKs explicitly; import all models in `app/models/__init__.py`.

**Problem: Relationship errors**
- *Symptoms:* `DetachedInstanceError` when accessing `patient.health_metrics` outside the session; `MissingGreenlet` with async (if you switched).
- *Likely causes:* lazy loading after the session closed (Phase 6.5); accessing relationships after the request ended.
- *How to diagnose:* where is the attribute accessed? Inside or outside the `get_db` scope?
- *How to fix:* eager-load with `selectinload`/`joinedload`, or access relationships inside the session (before returning from the service).
- *How to prevent:* treat sessions as request-scoped; load what you need before the session closes.

**Problem: Session problems**
- *Symptoms:* `sqlalchemy.orm.exc.StaleDataError`; concurrent-write conflicts; "object is already attached".
- *Likely causes:* sharing a session across requests; committing twice; mixing objects from different sessions.
- *How to diagnose:* trace where the session object came from; check for `SessionLocal()` inside route bodies.
- *How to fix:* one session per request via `get_db`; `db.refresh()` after commit; use `db.get()` fresh where needed.
- *How to prevent:* the dependency is the only session factory (same rule as the pool).

**Problem: Query errors**
- *Symptoms:* `TypeError` on results; `InvalidRequestError` on chained filters; wrong data back.
- *Likely causes:* forgetting `.scalars()`/`.all()`; comparing columns to Python objects; mutating a query after execution.
- *How to diagnose:* print the compiled query in a scratch script (`str(q)`) and run it raw.
- *How to fix:* use `db.scalars(select(...))` for rows; execute once, then read.
- *How to prevent:* test queries in a script before embedding them in services.

## Alembic Problems

**Problem: Migration errors**
- *Symptoms:* `alembic upgrade head` fails midway; partial migration applied.
- *Likely causes:* a migration references a column/table that doesn't exist; autogenerate produced broken SQL.
- *How to diagnose:* the error names the failing statement — compare it to your models.
- *How to fix:* review the migration; fix the statement; `alembic downgrade -1` to a clean state then re-upgrade.
- *How to prevent:* review every autogenerated migration before applying (Phase 7.2); keep them small.

**Problem: Migration not detecting models**
- *Symptoms:* `alembic revision --autogenerate` produces an empty migration; new tables never appear.
- *Likely causes:* models not imported by Alembic's `env.py` (`target_metadata` sees nothing).
- *How to diagnose:* check `env.py` — does it import `app.models`?
- *How to fix:* add `from app import models  # noqa` in `env.py` before `target_metadata`.
- *How to prevent:* add that import when you create the alembic setup; never delete it.

**Problem: Database out of sync**
- *Symptoms:* app errors "column does not exist"; `upgrade head` says nothing to do; autogenerate no-ops.
- *Likely causes:* someone edited the DB by hand; a migration was edited after being applied; history ≠ schema.
- *How to diagnose:* compare `alembic current` to the migration files; inspect the actual table with a `\d` psql query.
- *How to fix:* reconcile: either `alembic stamp` to the true revision (if the DB is actually ahead) or re-run the missing migrations on a dev DB and fix from there — **never hand-fix production**.
- *How to prevent:* the Phase 7 rules — migrations only, never hand-edits; review before apply.

## Authentication Problems

**Problem: JWT invalid**
- *Symptoms:* 401 with `INVALID_TOKEN` on every protected call, even right after login.
- *Likely causes:* wrong secret in `decode` (dev vs prod secret mismatch); `jwt_algorithm` mismatch; token truncated by the client.
- *How to diagnose:* decode the token with the app's own helper in a script; compare `settings.jwt_secret` between the process that minted it and the one verifying.
- *How to fix:* align secrets/algorithm; ensure the client sends the full `Bearer <token>` header.
- *How to prevent:* never change secrets casually; put the secret in `.env` once and reference `settings` everywhere.

**Problem: Token expired**
- *Symptoms:* requests work for a while, then suddenly 401; `exp` claims in the past.
- *Likely causes:* `access_token_expire_minutes` too short; client not refreshing; clock skew.
- *How to diagnose:* decode the token and inspect `exp` vs `datetime.now(timezone.utc)`.
- *How to fix:* lengthen the access window; implement `/auth/refresh` in the client; tolerate small skew (a few seconds is fine).
- *How to prevent:* keep refresh working end-to-end from day one (Phase 8.4).

**Problem: Password verification failure**
- *Symptoms:* register works, login always 401 `INVALID_CREDENTIALS`.
- *Likely causes:* hashing at register and verifying at login use different inputs (case, trailing space); storing the hash wrong (encoding).
- *How to diagnose:* hash a known password and verify it in a scratch script; compare the stored hash format.
- *How to fix:* normalize email/password the same way at both ends (lowercase email; never trim passwords); re-hash with the same `hash_password`.
- *How to prevent:* use the same `security` functions everywhere; add a login unit test on day one.

## RBAC Problems

**Problem: User getting 403 (when they should have access)**
- *Symptoms:* a legit doctor/admin gets `FORBIDDEN`.
- *Likely causes:* role string mismatch (`"doctor"` vs `"DOCTOR"`); `require_roles` comparing against the wrong enum; user object without the linked profile (`user.doctor is None`).
- *How to diagnose:* check the user's `role` value in the DB and what the dependency compares against.
- *How to fix:* use `Role` enum values consistently; guard the missing-profile case with a clear error.
- *How to prevent:* make the permission matrix a test (Phase 21.3) — roles become data you verify.

**Problem: User accessing an unauthorized resource (403 missing when it should fire)**
- *Symptoms:* Patient A reads Patient B's data; a doctor opens any patient.
- *Likely causes:* the object-level check was forgotten (role check only — the BOLA bug); the check tests the wrong ID (document vs owning patient).
- *How to diagnose:* walk the endpoint: does it call `can_access_patient`? With whose ID?
- *How to fix:* add the object check to the service; test nested resources too (document's owning patient).
- *How to prevent:* BOLA tests (Phase 21) — write them before you think the feature is done.

**Problem: Role dependency problems**
- *Symptoms:* `Depends()` errors; factory misuse; route signatures explode.
- *Likely causes:* calling `require_roles(...)` (the factory) instead of passing the result to `Depends`; missing annotations.
- *How to diagnose:* the traceback names the dependency; re-read §8.
- *How to fix:* `user: AdminOnly = Depends(...)` or the `Annotated` form — never `Depends(require_roles)` with parentheses missing.
- *How to prevent:* define the reusable aliases (`AdminOnly`, `DoctorOrAbove`) once and reuse.

## File Upload Problems

**Problem: File validation errors**
- *Symptoms:* valid-looking files rejected; `TYPE_MISMATCH`; uploads failing with 422.
- *Likely causes:* extension vs declared `content_type` mismatch (browsers are sloppy); your whitelist too strict.
- *How to diagnose:* print `file.content_type` and the extension for a failing file; check your `ALLOWED_EXTENSIONS` mapping.
- *How to fix:* relax to a sane mapping (Phase 15.2) and validate by magic bytes, not declared type alone.
- *How to prevent:* keep the extension→type map explicit and tested with real files.

**Problem: Storage errors**
- *Symptoms:* upload 500s; `raise_for_status()` fires; signed URL 404s.
- *Likely causes:* wrong `supabase_url`/service key; bucket doesn't exist or is public; wrong REST path; key collision.
- *How to diagnose:* the storage error body; test the endpoint with `curl` and the service key.
- *How to fix:* create the bucket; fix the URL/key in `.env`; make keys unique (UUID).
- *How to prevent:* a storage smoke test in your pipeline (Phase 18 verify); keep the key server-side only.

**Problem: Permission errors on download**
- *Symptoms:* signed URL returns 403/404 from storage; only some users can download.
- *Likely causes:* bucket policy denies; the object key doesn't match the metadata; URL expired.
- *How to diagnose:* request the URL directly with the storage API; compare `stored_object_key` to the actual object.
- *How to fix:* align key and policy; regenerate the URL (expiry is working as intended).
- *How to prevent:* store the exact key returned by the upload call; keep expiry short and regenerate per request.

## AI Problems

**Problem: Model/API unavailable**
- *Symptoms:* AI calls raise `APIConnectionError`/timeouts; pipeline marks documents `failed`.
- *Likely causes:* missing/invalid API key; network egress blocked; provider outage; wrong `base_url`.
- *How to diagnose:* test the key with the provider's own client in a script; check the exact error class.
- *How to fix:* fix the key/base_url; add one retry with backoff; keep the graceful `failed` path (it's the product behavior).
- *How to prevent:* config via env (Phase 23); a fake provider for tests (Phase 16); monitor failures via logs.

**Problem: Invalid AI response**
- *Symptoms:* `parsed is None`; validation errors on structured output; JSON that doesn't fit the schema.
- *Likely causes:* the model ignored the format instructions; prompt too weak; model mismatch.
- *How to diagnose:* log the raw completion; check what the model actually returned.
- *How to fix:* strengthen the system prompt; re-ask once with the schema error; then fail cleanly (never store raw output).
- *How to prevent:* treat structured output as a contract the prompt enforces (Phase 16.3) and validate with Pydantic.

**Problem: Timeout**
- *Symptoms:* chat/document requests take tens of seconds; the client gives up.
- *Likely causes:* long input (hard cap missing); model latency; no timeout configured.
- *How to diagnose:* measure the call; check input length at the point of call.
- *How to fix:* cap input (`text[:20000]`), set a client timeout, move work off the request path (queue).
- *How to prevent:* the pipeline design (Phase 15.5) — never let AI latency block the upload response.

**Problem: Hallucinated output**
- *Symptoms:* findings that aren't in the document; invented values; confident wrong answers.
- *Likely causes:* open-ended prompts; no grounding; model trained to comply.
- *How to diagnose:* compare the finding against the source text (citations make this possible).
- *How to fix:* constrain to the source ("only what the text says"), require citations, add human review status.
- *How to prevent:* the Phase 16/17 safety contract — structure, attribution, disclaimers, review — as defaults, not features.

**Problem: RAG retrieval failure**
- *Symptoms:* answers don't use the patient's data; citations empty; irrelevant context.
- *Likely causes:* context never injected; retrieval returns nothing (no docs/analyses); history window too small.
- *How to diagnose:* log the assembled context for a failing message — is the patient's data there?
- *How to fix:* fix the context builder; ensure documents are `completed` before referencing them; widen the window.
- *How to prevent:* test the context assembly as a unit (Phase 21.1); keep retrieval explicit and debuggable.

## Deployment Problems

**Problem: Environment variables missing**
- *Symptoms:* app starts locally, fails on the host; `validation error` on startup naming a field; 500s on first DB call.
- *Likely causes:* env vars set in local `.env` never set in the platform's secret store; typo in a var name.
- *How to diagnose:* the startup error names the missing variable; check the platform's logs/env tab.
- *How to fix:* set every var in the platform's dashboard (Phase 25.5 checklist); restart the service.
- *How to prevent:* make `.env.example` the deploy checklist; diff it against the platform's env before going live.

**Problem: CORS**
- *Symptoms:* the frontend can call the API from Postman/curl but the browser blocks it (`CORS policy` error).
- *Likely causes:* `cors_origins` doesn't include the exact frontend origin; missing scheme/port; wildcard with credentials.
- *How to diagnose:* look at the browser console error — it prints the offending origin; compare with `settings.cors_origins`.
- *How to fix:* add the exact origin (scheme + host + port) to `CORS_ORIGINS`; redeploy.
- *How to prevent:* set `CORS_ORIGINS` per environment from day one (Phase 23).

**Problem: Database connection on the host**
- *Symptoms:* `connection refused` from the deployed app; works locally.
- *Likely causes:* the platform's network is IPv4-only and you used the IPv6 direct endpoint; `sslmode` missing; prod `DATABASE_URL` pointing at a paused project.
- *How to diagnose:* the exact driver error; test the URL from the host's environment.
- *How to fix:* switch to the session-mode pooler endpoint (Phase 3.3); add `?sslmode=require`; unpause the DB.
- *How to prevent:* choose the endpoint based on the *host's* network, not your laptop's (Phase 3.3 decision).

**Problem: Docker**
- *Symptoms:* image builds locally, fails on the host; missing modules at runtime; secrets visible in the image.
- *Likely causes:* build context includes junk (no `.dockerignore`); `.env` baked in; platform rebuilds from the wrong branch.
- *How to diagnose:* `docker build` locally with `--no-cache`; inspect the image (`docker history`) for leaked files.
- *How to fix:* add `.dockerignore`; move secrets to runtime env; rebuild from the deploy branch.
- *How to prevent:* the rule from Phase 25.3 — no secrets in the image, ever; CI builds the same image you test.

**Problem: Production server behavior**
- *Symptoms:* requests drop under load; single-worker slowness; `--reload` behaving oddly in prod.
- *Likely causes:* one worker; dev flags in the prod command; missing health check so the platform restarts a healthy app.
- *How to diagnose:* check the process list on the host; review the platform's logs for restarts.
- *How to fix:* `--workers 2+`, no `--reload`; wire `/health` (Phase 25.5).
- *How to prevent:* the Docker CMD is your production contract — keep it fixed and tested.

---

# 🎯 Final Learning Objectives & Safety Recap

Before you call the MVP done, read the Phase 26 checklist one more time — then close on the principles this entire guide was built around.

## The Healthcare Safety Requirements (they are features, not warnings)

1. **The system is not an autonomous doctor.** AI assists, screens, informs, summarizes, and supports decisions — it never independently diagnoses. Every AI surface carries the disclaimer server-side.
2. **Protect medical data.** Treat patient information as the most sensitive thing you will ever store. Private buckets, signed URLs, HTTPS, least privilege.
3. **Apply least privilege.** Users access only what they're authorized to access — the permission matrix is code, and it is tested.
4. **Never trust the frontend.** Every permission check happens on the backend, every time — hidden buttons are not security.
5. **AI output must be treated as untrusted.** Structured, validated, attributed, reviewable — never stored raw.
6. **Keep auditability.** Important data access and administrative operations are traceable end to end.

## What You Should Now Be Able to Build and Explain

- How FastAPI routes, dependencies, and lifecycle work — and why routes are thin
- How REST APIs are designed: resources, methods, status codes, error contracts
- How PostgreSQL works with SQLAlchemy 2.0: models, sessions, relationships
- How relational schemas are designed: FKs, cascades, indexes, time-series shapes
- How migrations work with Alembic — and why you never hand-edit production
- How authentication works: hashing, salt, JWT, access + refresh tokens
- How RBAC works: roles, permission matrices, object-level authorization
- How to design secure APIs: the OWASP map, BOLA/IDOR, input and file safety
- How medical documents are handled: validation, object storage, signed URLs, states
- How backend services communicate: the layered architecture and its one-way rule
- How AI integrates: isolated services, structured outputs, prompts as code, review workflows
- How RAG fits: context retrieval, citations, and the MVP-sized path to pgvector
- How to test APIs: test databases, dependency overrides, the BOLA test suite
- How to debug backend problems: symptom → logs → layer → reproduce → root cause → regression test
- How to deploy: Docker, cloud hosting, env injection, health checks, HTTPS

## A Last Word From Your Mentor

The point of this project was never the finished API. It was the *reasoning*: why the FK goes on the many side, why the object check happens in the service, why the AI lives behind an interface, why the audit row is written before you tell anyone it worked. When you hit the wall in the next project — and you will — you'll already know the shape of the answer: **find the layer, read the logs, reproduce, fix the root cause, and write the regression test.** That loop is the entire discipline of backend engineering. It's yours now.

**Build it, break it, fix it, ship it. You're ready.**

---

*End of HEALTHAI_BACKEND_GUIDE.md — the HealthAI MVP backend roadmap. Revisit Phase 0 if you ever wonder what you're building and why.*

