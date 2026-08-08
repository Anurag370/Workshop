# Local Retail Manager — Complete Development Guide

> A course-style, step-by-step guide to building a **real, production-oriented desktop application** — an offline-first billing, inventory, and retail management system — from an empty folder to a Windows installer.
>
> **Built with:** React + TypeScript + Vite + Tailwind CSS · Python + FastAPI + SQLAlchemy + Pydantic + Alembic · SQLite · ReportLab · Tauri 2 · pytest + Vitest
>
> **The rule of this guide:** *Teach → Explain → Implement → Test → Debug → Continue.* We never dump finished code first. Every concept is taught, then implemented in small steps, then verified with a checkpoint.

---

## Table of Contents

| Phase | Topic | What you will have at the end |
|-------|-------|-------------------------------|
| [Phase 0](#phase-0--understanding-the-project) | Understanding the project | A mental model of the whole system |
| [Phase 1](#phase-1--development-environment) | Development environment | Python, Node, Git, Rust, VS Code installed & verified |
| [Phase 2](#phase-2--project-structure) | Project structure | The complete folder tree, with reasons |
| [Phase 3](#phase-3--database-design) | Database design | A relational schema + SQLAlchemy models + Alembic migrations |
| [Phase 4](#phase-4--backend-fundamentals) | Backend fundamentals | A running FastAPI app with routers, schemas, DI, service layer |
| [Phase 5](#phase-5--product-management) | Product management | Full CRUD for products & categories, search, SKU/barcode |
| [Phase 6](#phase-6--inventory-system) | Inventory ledger | Movement-based stock tracking, valuation, low-stock alerts |
| [Phase 7](#phase-7--billing-system) | Billing system | Transactional sale flow with rollback safety |
| [Phase 8](#phase-8--invoice-generation) | Invoice generation | A4 PDF invoices + 80 mm thermal receipts (ReportLab) |
| [Phase 9](#phase-9--react-frontend) | React frontend | Layout, routing, API layer, reusable components |
| [Phase 10](#phase-10--billing-ui) | Billing UI | A fast POS-style billing screen |
| [Phase 11](#phase-11--purchases) | Purchases | Purchase records → inventory increase → supplier liability |
| [Phase 12](#phase-12--customers-and-credit-khata) | Customers & Credit (Khata) | Customer CRUD, history, ledger, outstanding balance |
| [Phase 13](#phase-13--suppliers) | Suppliers | Supplier CRUD, payments, ledger, balance |
| [Phase 14](#phase-14--expenses-and-profit) | Expenses & profit | Expense tracking, gross/net profit calculation |
| [Phase 15](#phase-15--dashboard) | Dashboard | Live metrics computed from the database |
| [Phase 16](#phase-16--reports) | Reports | 11 report types with date-range filtering + CSV export |
| [Phase 17](#phase-17--barcode-scanner) | Barcode scanner | Keyboard-wedge scanning + barcode generation |
| [Phase 18](#phase-18--authentication-and-authorization) | Auth & roles | Login, JWT sessions, Owner/Manager/Cashier permissions |
| [Phase 19](#phase-19--backup-and-restore) | Backup & restore | Safe, atomic backups with verification & rotation |
| [Phase 20](#phase-20--error-handling-and-logging) | Error handling | Consistent errors + rotating file logs |
| [Phase 21](#phase-21--testing) | Testing | Unit, integration, API & frontend tests |
| [Phase 22](#phase-22--security) | Security | What actually matters for a local retail app |
| [Phase 23](#phase-23--tauri-integration) | Tauri integration | Desktop shell + backend lifecycle management |
| [Phase 24](#phase-24--windows-packaging) | Windows packaging | `Setup.exe` → install → shortcut → run |
| [Phase 25](#phase-25--production-architecture) | Production architecture | How the installed app boots and lives |
| [Phase 26](#phase-26--advanced-features-post-mvp) | Advanced features (post-MVP) | CSV/Excel, multi-shop, cloud backup, updates |
| [Phase 27](#phase-27--ai-features) | AI features (post-MVP) | AI assistant that never invents numbers |
| [Git Workflow](#git-workflow--teaching-git-as-part-of-the-project) | Git workflow | Meaningful commits for every phase |
| [Troubleshooting Guide](#troubleshooting-guide) | Debugging reference | Every common error, diagnosed |
| [API Reference](#api-reference) | API documentation | Every endpoint, request, response |
| [Database Reference](#database-reference) | Schema reference | Every table, column, relationship, key query |
| [Cheat Sheets](#command-cheat-sheet) | Quick references | Commands, Git, database, debugging, deployment |
| [Final Project Tree](#final-project-tree) | The final tree | Exactly matches the final code |
| [Complete Source Code Reference](#complete-source-code-reference) | Full code | Every important file, internally consistent |

---

## How to Use This Guide

1. **Follow the phases in order.** Each phase builds on the previous one. Later code assumes earlier files exist exactly as written.
2. **Type the code, don't copy it** — at least for the first time. The guide explains *why* every important line exists. Typing it makes the reasoning stick. The full final code is available in the [Complete Source Code Reference](#complete-source-code-reference) when you are stuck or want to verify.
3. **Do the checkpoints.** Every major step ends with a **✅ Checkpoint** — a command to run and a list of things to verify. Never skip these; they are how you learn to debug.
4. **Do the exercises.** They are deliberately small and force you to apply what you just learned. Solutions are provided *after* each exercise, clearly separated, so you can honestly attempt them first.
5. **When something breaks, use the [Troubleshooting Guide](#troubleshooting-guide).** It explains the *reason* for each error, not just the fix.
6. **The guide is long by design.** Understanding, reasoning, architecture and debugging ability are worth more than brevity. Read it in sessions.

### The teaching loop used everywhere

```text
1. PROBLEM   → Why does this feature exist? What goes wrong without it?
2. CONCEPT   → The idea behind the solution (one paragraph, one diagram).
3. ARCHITECTURE → Where does this live? Which layers talk to which?
4. FILES     → What we will create, and why each file exists.
5. IMPLEMENT → Small code first, explained line by line. Then the full file.
6. TEST      → Run it. Verify with a checkpoint.
7. DEBUG     → Common mistakes and their fixes.
8. CONTINUE  → Only then, the next step.
```

---

## Version Snapshot (verified August 2026)

These are the exact stable versions used throughout this guide. They were verified against the PyPI and npm registries on the date above, and against your machine's installed tools (Python **3.12.10**, Node **v24.14.0**, npm **11.9.0**, Git **2.53.0**, Rust **1.97.1**).

> 🟢 Your installed versions already satisfy every requirement — you do **not** need to upgrade anything to follow this guide.

### Python / backend (PyPI)

| Package | Version | Why it's here |
|---|---|---|
| fastapi | 0.141.1 | The API framework |
| uvicorn | 0.52.1 | The ASGI server that runs FastAPI |
| sqlalchemy | 2.0.51 | ORM + database toolkit (2.x style) |
| alembic | 1.19.0 | Database migrations |
| pydantic | 2.13.4 | Validation / schemas (v2, comes with FastAPI) |
| pydantic-settings | 2.15.0 | Typed configuration from env / `.env` |
| reportlab | 5.0.0 | PDF invoice generation |
| bcrypt | 5.0.0 | Password hashing |
| PyJWT | 2.13.0 | Auth tokens |
| pytest | 9.1.1 | Backend tests |
| httpx | 0.28.1 | HTTP client used by FastAPI's test client |
| pyinstaller | 6.21.0 | Bundles the backend into a Windows `.exe` |
| openpyxl | 3.1.5 | Excel export (Phase 26, optional) |

> **Compatibility note:** SQLAlchemy 2.0.x, FastAPI 0.1xx, Pydantic v2, and Alembic 1.x are designed to work together. SQLAlchemy 2.x uses the new `Mapped` / `mapped_column()` declarative style used in this guide. Python 3.12 is fully supported by every package above (3.12–3.14 are all fine; the guide targets 3.12+).

### Frontend (npm)

| Package | Version | Why it's here |
|---|---|---|
| react / react-dom | 19.2.8 | UI library |
| vite | 8.2.1 | Build tool + dev server |
| @vitejs/plugin-react | 6.0.5 | React fast-refresh for Vite |
| typescript | 7.0.2 | Type checking (see note) |
| tailwindcss | 4.3.3 | Utility-first CSS (v4 — no config file needed) |
| @tailwindcss/vite | 4.3.3 | Tailwind v4's official Vite plugin |
| zustand | 5.0.14 | Small, fast global state |
| react-router-dom | 7.18.2 | Routing |
| vitest | 4.1.10 | Frontend tests |
| @testing-library/react | 16.3.2 | Component tests |
| lucide-react | 1.30.0 | Icons |

> **TypeScript note:** the npm registry's `latest` tag is now TypeScript **7.0** (the native compiler). Vite's React–TS template pins a version it is tested against. If you ever hit a type error caused by tooling rather than your code, you can safely pin `"typescript": "~5.9"` — the guide's code is compatible with both. We always install TypeScript as a *dev* dependency.

### Desktop

| Tool | Version | Why it's here |
|---|---|---|
| Tauri | 2.x | Desktop shell (installed via `create-tauri-app` / crates) |
| Rust | 1.75+ (you have 1.97.1) | The Tauri shell is written in Rust |

### How to check versions on your machine

```bash
python --version        # 3.12.10
node --version          # v24.14.0
npm --version           # 11.9.0
git --version           # 2.53.0.windows.2
rustc --version         # 1.97.1
cargo --version         # 1.97.1
```

Inside a Python environment you can list installed packages with `pip list` or `pip show fastapi`. In the frontend: `npm list react`.

---

# Phase 0 — Understanding the Project

> **Goal of this phase:** before writing a single line of code, understand *what* we are building, *who* uses it, *why* this architecture, and *how* the pieces communicate. Architecture decisions made here are recorded as **ADRs** (Architecture Decision Records) so that when we revisit them later, we remember *why* we chose what we chose.

## 0.1 What is Local Retail Manager?

Local Retail Manager is an **offline-first desktop application** for small and medium shops (kirana/grocery stores, stationery shops, mobile shops, pharmacies, garment stores). It replaces the paper notebook + manual receipt approach with:

- **Billing** — fast POS-style selling with automatic invoice generation.
- **Inventory** — a full movement ledger showing *exactly why* stock went up or down.
- **Purchases** — recording what you bought from suppliers.
- **Customers & Suppliers** — including **credit (Khata)** tracking with outstanding balances.
- **Expenses, reports, dashboard** — so the owner finally knows *profit*, not just *sales*.

It runs **entirely on the shop's own Windows PC**. No internet required. No monthly subscription. The data never leaves the shop.

### The real-world problem

A typical small shop today:

- Writes sales in a notebook. Nobody knows daily profit.
- Prices from memory or a handwritten price list → frequent mistakes, lost margin.
- Has no idea which products are about to run out, or which are gathering dust.
- Keeps customer credit in a tattered register → disputes and forgotten dues.
- Has no backup. A failed hard disk = years of records gone.

The **core insight**: the single most important quality of this system is **data integrity** — the database must never end up in an impossible state (sale recorded but stock not reduced, payment taken but sale not saved). Everything else (speed, looks, features) is secondary.

## 0.2 Target users

| User | What they do | What they need |
|---|---|---|
| **Cashier** | Operates the billing screen hundreds of times a day | Speed, keyboard support, barcode scanning, no complex settings |
| **Manager** | Runs the shop, manages stock, checks reports | Products, purchases, inventory, reports; no user management |
| **Owner** | Owns the business | Everything: profit, expenses, users, backups, settings |

This role split matters: it will drive the **authentication & authorization** design in Phase 18.

## 0.3 Functional requirements (MVP)

- ✅ Authentication (login/logout) with roles: Owner, Manager, Cashier
- ✅ Product & category management (SKU, barcode, purchase/selling price, tax rate, minimum stock)
- ✅ Inventory with a **movement ledger** (purchase, sale, return, adjustment, damage)
- ✅ Billing: search → add to cart → discount → tax → total → payment → invoice
- ✅ PDF invoice (A4) + thermal receipt (80 mm)
- ✅ Purchases: record purchase, pay supplier, increase stock automatically
- ✅ Customers: CRUD, purchase history, credit (Khata) with outstanding balance, ledger
- ✅ Suppliers: CRUD, purchase history, payments, outstanding balance, ledger
- ✅ Expenses: record + categorize
- ✅ Profit calculation: Revenue − COGS = Gross Profit; Gross Profit − Expenses = Net Profit
- ✅ Dashboard: today's sales/profit/transactions, low stock, top products, revenue & profit graphs
- ✅ Reports: 11 report types with date filtering
- ✅ Barcode scanning (keyboard-wedge scanners work with zero extra code)
- ✅ Backup & restore (manual + automatic)
- ✅ Logging
- ✅ Tests (backend + frontend)
- ✅ Windows packaging: `Setup.exe`

## 0.4 Non-functional requirements

| Requirement | What it means here |
|---|---|
| **Offline-first** | 100% of functionality works with no network. There is no required remote dependency. |
| **Data integrity** | Transactions, constraints, foreign keys. No negative stock. No duplicate invoices. No partial operations. |
| **Single-user-ish** | One PC, one database. Multiple users may log in, but there is no multi-terminal sync in the MVP. |
| **Performance** | Billing must feel instant on an ordinary shop PC. SQLite + indexes + sensible queries. |
| **Durability** | Daily automatic backups, atomic backup snapshots, easy restore. |
| **Maintainability** | Layered architecture, typed code, tests, migrations, logging. |
| **Installability** | A normal Windows installer the shop owner can run; no Python/Node needed on the shop PC. |

## 0.5 Offline-first architecture

The traditional web-app architecture assumes a server somewhere. We invert that:

```mermaid
graph LR
    subgraph "The shop's Windows PC (no internet needed)"
        UI[React UI] -->|HTTP on localhost| API[FastAPI]
        API --> ORM[SQLAlchemy]
        ORM --> DB[(SQLite file)]
        API --> PDF[ReportLab → PDF invoices]
        API --> FS[(Invoices / Backups / Logs folders)]
    end
```

Everything runs on **localhost**. The "server" is a local process. The "database" is a file on disk. The browser window is a Tauri desktop shell.

**Why this is a good trade for retail:**

| Internet app | Local desktop app |
|---|---|
| Needs server, hosting, internet | Runs on one PC, zero recurring cost |
| Data in a cloud you don't control | Data stays on the shop's disk |
| Sync complexity | No sync in MVP |
| Can be accessed from anywhere | Is *not* accessible from anywhere — which is fine (even good) for a shop |

**The price we pay:** we must handle backups ourselves (Phase 19) because there is no server farm protecting us. This is a *feature of the design*, not an afterthought.

## 0.6 Desktop application architecture

The final installed product is a **Tauri** app (a small Rust process + the Windows WebView2 browser engine) that displays our React UI and *manages the lifecycle of our Python backend*:

```mermaid
graph TD
    subgraph "Local Retail Manager.exe"
        T[Tauri shell Rust] -->|spawns / kills| B[FastAPI backend process]
        T -->|displays| W[WebView2]
        W -->|React UI| R[fetch /api/...]
        R -->|http://127.0.0.1:8000| B
        B --> DB2[(SQLite)]
        B --> PDF2[Invoices]
    end
```

Three processes/layers, one user experience:
1. **Tauri shell (Rust)** — the desktop window, starts the backend, kills it on exit.
2. **React UI** — everything the user sees.
3. **FastAPI backend** — all business logic, database access, PDF generation. Runs as a local web server on `127.0.0.1:8000`.

During development (Phases 1–22) we run the React UI in a normal browser and the backend with `uvicorn` — same architecture, no desktop shell yet. Tauri is added in **Phase 23**, and only after the web app works.

## 0.7 Why this technology stack? (the ADRs)

An **Architecture Decision Record (ADR)** is a short note capturing: the decision, the alternatives, and the reason. We record decisions now so future-you knows *why*, and so the guide never silently changes architecture.

### ADR-01: SQLite as the database

- **Decision:** Use SQLite (a single file database), accessed through SQLAlchemy.
- **Alternatives:** PostgreSQL, MySQL (client–server RDBMS), MongoDB (document store).
- **Reason:** For a single-PC, offline-first application with one concurrent operator, a client–server database is pure overhead: you'd need to install and maintain a database server on the shop PC. SQLite is an *embedded* database — the "server" is a library inside our process, and the entire database is one file we can back up by copying it. SQLite supports ACID transactions, foreign keys, and indexes, which is everything our data-integrity requirements demand. It is the most widely deployed database engine in the world and is extremely robust for this workload.
- **When this changes:** if you later need multi-terminal sync or a remote dashboard (Phase 26), you'd move to PostgreSQL and add a sync layer — but the SQLAlchemy layer is precisely what makes that swap feasible.

### ADR-02: FastAPI (Python) as the backend

- **Decision:** FastAPI + Pydantic + SQLAlchemy.
- **Alternatives:** Flask + SQLAlchemy, Django + DRF, Node/Express, Go.
- **Reason:** FastAPI gives us automatic request validation (Pydantic), automatic OpenAPI docs (`/docs`), and a clean dependency-injection system — while remaining a small, understandable framework. Python matches the developer's existing skills and makes the ReportLab PDF work trivial. The `/docs` page is a huge learning aid while we build the API.
- **When this changes:** performance is not a constraint here (localhost, one user), so a faster runtime is not a reason to switch.

### ADR-03: React + TypeScript + Vite + Tailwind

- **Decision:** React 19, TypeScript, Vite 8, Tailwind CSS v4.
- **Alternatives:** Vue/Svelte, plain JS, CRA (deprecated), CSS modules / styled-components.
- **Reason:** React's component model matches our reusable-UI needs (tables, modals, forms reused across products/customers/suppliers). TypeScript gives us end-to-end type safety with the API (we define the same shapes on both sides). Vite is the current standard build tool with near-instant dev server. Tailwind v4 needs no config file and keeps styling fast and consistent.
- **When this changes:** only personal/team preference.

### ADR-04: Tauri (not Electron) for the desktop shell

- **Decision:** Tauri 2.
- **Alternatives:** Electron, PyWebView, a pure local-web-server + browser approach.
- **Reason:** Tauri uses the OS's own WebView (WebView2 on Windows) instead of shipping a copy of Chromium, so the installer is ~5–10 MB instead of ~100+ MB, it uses far less RAM, and it can spawn/kill our backend process from Rust. The Rust part is small (a few hundred lines) and we already have Rust installed.
- **When this changes:** if you ever need deep OS integrations beyond what Tauri's plugin system covers.

### ADR-05: Separate Python backend process (not in-process)

- **Decision:** The backend is a separate process (uvicorn server) that Tauri spawns.
- **Alternatives:** Compile the Python backend into the app (impossible — Python is interpreted), rewrite the backend in Rust (huge effort), run backend as a web service (needs internet — violates offline-first).
- **Reason:** Python can't be embedded into Tauri; it must run as a child process. This is the standard "sidecar" pattern and Tauri has first-class support for bundling and launching sidecar binaries (Phase 23–24).

### ADR-06: Service layer between routes and models

- **Decision:** All business logic lives in a `services/` layer; routes are thin; models are dumb.
- **Alternatives:** Fat routes (logic inside handlers), fat models (logic inside ORM classes).
- **Reason:** Business rules (stock math, invoice numbering, credit balances) are the most-tested, most-valuable code we write. Isolating them in services means they can be unit-tested without HTTP, reused by scripts (e.g., the demo-data seeder), and kept out of both the API layer and the ORM layer. It also stops `main.py` from becoming a dumping ground.

### ADR-07: Inventory movement ledger (not a stock column)

- **Decision:** Stock is *derived* from an append-only `inventory_movements` ledger, with a denormalized `current_stock` cache column on products.
- **Alternatives:** Just update `product.stock` on every sale.
- **Reason:** `product.stock -= quantity` tells you the *new number* but not *why*. If a cashier makes a mistake, you cannot answer "how did we lose 12 units of Tata Salt?" The ledger answers that question forever (audit trail, Phase 6). The `current_stock` column is kept for fast queries and is always updated *inside the same transaction* as the ledger row, so it can never drift under normal operation.

### ADR-08: JWT tokens for authentication

- **Decision:** Password hashing with bcrypt; stateless access tokens using signed JWTs (HS256) with an expiry.
- **Alternatives:** Session cookies, opaque DB sessions.
- **Reason:** For a localhost API consumed by our own frontend, JWT Bearer tokens are simple, need no session store, and are easy to test with curl. The trade-off (token is readable by the client) is acceptable for a local desktop app; we still enforce all authorization on the **backend** (ADR-09).

### ADR-09: Authorization enforced on the backend

- **Decision:** Every protected endpoint checks the caller's role server-side.
- **Alternatives:** Hiding buttons in the UI and trusting the frontend.
- **Reason:** "Never rely only on hiding frontend buttons for security." Anybody can call our API directly with curl, so the API itself must refuse disallowed actions. The frontend hiding is a *usability* nicety, not a security control (Phase 18, Phase 22).

### ADR-10: Money stored as DECIMAL, transported as float

- **Decision:** Database columns use `NUMERIC(12,2)` (a fixed-point Decimal); all business math uses Python's `decimal.Decimal` with `ROUND_HALF_UP`; JSON transport uses plain numbers.
- **Alternatives:** float everywhere, or string transport.
- **Reason:** Binary floating point cannot represent 0.1 exactly, so summing floats silently accumulates errors — unacceptable for money. Decimal in the DB and in calculations is exact to 2 decimal places. JSON has no Decimal type, so Pydantic serializes to float for transport; amounts in a retail context (values under a few lakh, 2dp) round-trip cleanly. This is the industry-standard pragmatic compromise (Phase 3, `utils/money.py`).

### ADR-11: Alembic for schema migrations

- **Decision:** All schema changes go through Alembic migrations; the packaged app runs `alembic upgrade head` on startup.
- **Alternatives:** `Base.metadata.create_all()` everywhere, manual SQL.
- **Reason:** `create_all` only creates missing tables — it cannot *alter* existing ones, so the moment we add a column (e.g., `brand` in the first exercise) the app breaks on existing databases. Migrations give us versioned, reversible schema changes and let the installed app upgrade its own database safely when the user installs a new version (Phase 3, Phase 24).

## 0.8 How the components communicate (end to end)

The complete request lifecycle — this exact diagram reappears in every phase:

```mermaid
sequenceDiagram
    participant U as User (cashier)
    participant R as React UI (browser/WebView)
    participant A as FastAPI route
    participant S as Service layer
    participant M as SQLAlchemy models
    participant D as SQLite file

    U->>R: clicks "Complete Sale"
    R->>A: POST /api/sales  (JSON body)
    A->>S: validates input (Pydantic) → calls service
    S->>M: begins transaction, applies business rules
    M->>D: SQL statements (INSERT/UPDATE, FK checks)
    D-->>M: rows
    M-->>S: ORM objects
    S-->>A: result (committed)
    A-->>R: HTTP 201 + JSON response
    R->>U: success screen + invoice link
```

**Key idea:** each layer has exactly one job:

| Layer | Job | Must NOT do |
|---|---|---|
| React components | Render state, capture input | Business math, direct DB access |
| API services (frontend) | HTTP calls, error normalization | Business rules |
| FastAPI routes | Parse request, call service, return response | Business logic, SQL |
| Service layer | Business rules, transactions | HTTP details |
| Models | Table structure & relationships | Business rules |
| Database | Store rows atomically, enforce constraints | Anything else |

This single rule — *business logic belongs to the service layer* — is the backbone of the whole project and prevents every "spaghetti" failure mode listed in the coding rules.

## 0.9 What we will build, phase by phase (roadmap)

```text
Phase 1–2  Environment + skeleton
Phase 3    Database (models + migrations)
Phase 4–8  Backend: fundamentals → products → inventory → billing → invoices
Phase 9–10 Frontend: foundations → billing UI
Phase 11–16 Purchases, customers, suppliers, expenses, dashboard, reports
Phase 17–19 Barcode, auth, backup
Phase 20–22 Error handling, testing, security
Phase 23–25 Tauri, packaging, production
Phase 26–27 Advanced + AI (post-MVP)
```

> 🗺️ **Map of the rest of the guide:** every phase follows the same structure — *Problem → Concept → Architecture → Files → Implement → Test → Debug*. At the very end you'll find the Troubleshooting Guide, API Reference, Database Reference, Cheat Sheets, the Final Project Tree, and the Complete Source Code.

---

## ✅ Phase 0 Checkpoint

There is nothing to run yet. Verify that you can **explain**, out loud or on paper:

- [ ] The three-tier architecture (React → FastAPI → SQLite) and why the backend is a separate local process
- [ ] Why SQLite is the right database for a single-PC offline-first app (ADR-01)
- [ ] Why the inventory ledger is more trustworthy than a stock column (ADR-07)
- [ ] The request lifecycle: route → service → model → database → back
- [ ] Which layer owns business logic, and why
- [ ] The three user roles and roughly what each may do

> If you cannot explain those six points, re-read 0.5–0.8 before continuing. Everything in the rest of the guide assumes them.

---

**Next:** [Phase 1 — Development Environment](#phase-1--development-environment)
# Phase 1 — Development Environment

> **Goal of this phase:** install and *verify* every tool, understand the concepts behind them (PATH, virtual environments, package managers), create the project folder, and get three things running: the **frontend dev server**, the **backend server**, and a **hello-world Tauri app** (to prove the desktop toolchain works before we build the real one).

## 1.1 What we need, and why

| Tool | Version needed | Why |
|---|---|---|
| **Python** | 3.12+ | Runs the FastAPI backend, ReportLab, tests |
| **Node.js + npm** | Node 20+/24 LTS, npm 10+/11 | Runs Vite, React tooling, Tauri CLI |
| **Git** | any recent | Version control — every phase is committed |
| **VS Code** | any recent | Editor (recommended, with Python + ESLint/Prettier extensions) |
| **Rust + Cargo** | 1.75+ | Compiles the Tauri desktop shell |
| **WebView2 Runtime** | bundled with Windows 10/11 | The rendering engine Tauri uses on Windows |

> 🔍 **Check first.** Run all version checks from the [Version Snapshot](#version-snapshot-verified-august-2026). On this machine everything is already installed — but you should still understand how to verify on *any* machine.

## 1.2 Concept: PATH

When you type `python` in a terminal, the shell searches a list of folders called the **PATH** for an executable named `python.exe`. Installers add themselves to PATH. Consequences:

- If `python` is "not recognized", Python was installed without adding it to PATH (check *"Add python.exe to PATH"* in the installer).
- If typing `python` runs the wrong version, some other Python is earlier in PATH (check with `where python` on Windows).

Check it yourself:

```bash
where python        # Windows: lists every python.exe on the PATH
where node
python --version
node --version
```

## 1.3 Concept: virtual environments (venv)

A **virtual environment** is a private folder containing its own copy of Python and its own installed packages. Every Python project gets one. Why?

- Different projects need different package versions; installing everything globally creates conflicts ("this project needs Flask 2, that one needs Flask 3").
- A venv keeps your global Python clean and makes a project self-contained (and later, reproducible on another machine).

```bash
cd backend
python -m venv venv          # create the environment (folder named venv)
venv\Scripts\activate        # activate it (Windows bash/Git Bash: source venv/Scripts/activate)
```

After activation, your prompt shows `(venv)`, and `pip` now installs **into** the venv. Deactivate with `deactivate`. When you reopen a terminal, activate again — this is the single most common beginner mistake in the whole guide.

> ⚠️ **Never** run `pip install` when the venv is *not* active. You will silently install into the wrong Python and then wonder why imports fail.

## 1.4 Concept: package managers (pip, npm)

A **package manager** downloads, installs, and tracks the exact versions of libraries your project uses.

- **pip** (Python): installs from PyPI. We record dependencies in `requirements.txt` (a plain text file with one `package==version` per line).
- **npm** (Node): installs from the npm registry. It creates `package.json` (the manifest) and `package-lock.json` (a complete, exact record of every installed version). `npm install <pkg>` adds the package; `npm install` installs everything listed.
- **cargo** (Rust): installs crates for the Tauri shell. `Cargo.toml` is the manifest, `Cargo.lock` the exact record.

### How to verify package versions after installing

```bash
pip show fastapi                 # version + location
npm list react                   # version installed in this project
```

## 1.5 Install anything that's missing

If a tool is missing on your machine, install it:

1. **Python** — from [python.org](https://www.python.org/downloads/). ✅ tick **"Add python.exe to PATH"**. Windows users: prefer the installer over the Microsoft Store version (the Store version can hide the interpreter path from some tools).
2. **Node.js LTS** — from [nodejs.org](https://nodejs.org/). npm ships with it.
3. **Git** — from [git-scm.com](https://git-scm.com/). Git Bash is included — the terminal we use in this guide.
4. **VS Code** — from [code.visualstudio.com](https://code.visualstudio.com/). Recommended extensions: *Python*, *Pylance*, *ESLint*, *Prettier*, *Tailwind CSS IntelliSense*, *Rust* (rust-analyzer), *Tauri*.
5. **Rust** — from [rustup.rs](https://rustup.rs/) (`rustup-init.exe`). Verify with `rustc --version`.
6. **WebView2 Runtime** — Windows 10/11 almost always has it. Check: open `edge://settings` or just verify later in Phase 23. If missing, install the *Evergreen* runtime from Microsoft.

### ✅ Checkpoint (environment)

```bash
python --version
node --version
npm --version
git --version
rustc --version
cargo --version
```

Expected: all print versions (yours are `3.12.10`, `v24.14.0`, `11.9.0`, `2.53.0`, `1.97.1`, `1.97.1`).

- [ ] Python, Node, npm, Git, Rust all print versions
- [ ] VS Code opens and has the Python extension

### If it doesn't work

| Symptom | Why | Fix |
|---|---|---|
| `python` not recognized | Not on PATH | Reinstall with "Add to PATH", or use full path `C:\Python312\python.exe` |
| `rustc` not recognized | Rustup not installed / PATH not refreshed | Reinstall rustup; **restart the terminal** (PATH changes need a new session) |
| npm hangs | Registry/proxy issue | `npm config get registry` (should be `https://registry.npmjs.org/`) |

## 1.6 Create the project

Open a terminal in an empty folder (e.g. `C:\Users\homro\Documents\retail` — any empty folder works) and run:

```bash
mkdir local-retail-manager
cd local-retail-manager
git init
```

Create the top-level folders now (each one is explained fully in Phase 2):

```bash
mkdir backend frontend desktop data scripts docs
```

Write a minimal `.gitignore` at the root — this prevents junk (and the database!) from ever being committed:

```text
# Python
__pycache__/
*.pyc
venv/
.env

# Node
node_modules/
dist/
dist-electron/

# Data (NEVER commit real data)
data/database/*.db*
data/backups/*
data/invoices/*
data/logs/*
!data/**/.gitkeep

# Rust / Tauri
desktop/src-tauri/target/

# OS / editor
.DS_Store
Thumbs.db
.idea/
```

Add `.gitkeep` files so the empty data folders survive git:

```bash
touch data/database/.gitkeep data/backups/.gitkeep data/invoices/.gitkeep data/logs/.gitkeep data/exports/.gitkeep
```

First commit (see the [Git Workflow](#git-workflow--teaching-git-as-part-of-the-project) section for why meaningful commits matter):

```bash
git add -A
git commit -m "feat: initialize project structure"
```

## 1.7 Run the backend skeleton

Create `backend/` content:

```bash
cd backend
python -m venv venv
source venv/Scripts/activate        # Git Bash; PowerShell: venv\Scripts\Activate.ps1
```

Create `backend/requirements.txt` with the **verified versions**:

```text
fastapi==0.141.1
uvicorn[standard]==0.52.1
sqlalchemy==2.0.51
alembic==1.19.0
pydantic==2.13.4
pydantic-settings==2.15.0
reportlab==5.0.0
bcrypt==5.0.0
PyJWT==2.13.0
python-multipart==0.0.20
```

Install:

```bash
pip install -r requirements.txt
```

> Why `uvicorn[standard]`? The `standard` extra adds fast optional dependencies (and on Windows, `colorama`). Plain `uvicorn` works too; the extra is the normal choice.

Now create the smallest possible FastAPI app so we can *see* it work before building anything real. Create `backend/app/main.py`:

```python
from fastapi import FastAPI

app = FastAPI(title="Local Retail Manager API")


@app.get("/api/health")
def health() -> dict:
    return {"status": "ok", "app": "Local Retail Manager"}
```

Run it:

```bash
uvicorn app.main:app --reload --port 8000
```

- `app.main:app` → "import the `app` object from the `main.py` module inside the `app` package"
- `--reload` → restart automatically when code changes (development only)
- `--port 8000` → listen on http://127.0.0.1:8000

Open **http://127.0.0.1:8000/api/health** → `{"status":"ok","app":"Local Retail Manager"}`. Open **http://127.0.0.1:8000/docs** → FastAPI's automatic, interactive API documentation (this page becomes our best friend while building the API).

### ✅ Checkpoint (backend skeleton)

- [ ] `pip install -r requirements.txt` completes without errors
- [ ] `uvicorn app.main:app --reload` starts without errors
- [ ] `/api/health` returns `{"status":"ok",...}`
- [ ] `/docs` shows the Swagger UI

### If it doesn't work

| Error | Why | Fix |
|---|---|---|
| `ModuleNotFoundError: No module named 'fastapi'` | venv not active (or install happened in wrong env) | `source venv/Scripts/activate`, reinstall, check `pip show fastapi` |
| `[Errno 10048] error while attempting to bind` | Port 8000 already in use | Close the other server, or use `--port 8001` |

## 1.8 Run the frontend skeleton

Create the React + TypeScript + Vite app with the official scaffolder:

```bash
cd ../frontend
npm create vite@latest . -- --template react-ts
npm install
```

This generates `package.json`, `index.html`, `src/main.tsx`, `src/App.tsx`, `tsconfig.json`, `vite.config.ts`. Now add Tailwind CSS v4 (the modern, config-free way):

```bash
npm install tailwindcss @tailwindcss/vite
```

Wire the plugin into `vite.config.ts`:

```ts
import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";
import tailwindcss from "@tailwindcss/vite";

export default defineConfig({
  plugins: [react(), tailwindcss()],
  server: { port: 5173 },
});
```

Replace `src/index.css` with a single line (Tailwind v4 needs no config file or `@tailwind` directives):

```css
@import "tailwindcss";
```

Delete the demo styles from `App.tsx` and render something tiny:

```tsx
export default function App() {
  return <h1 className="text-3xl font-bold text-emerald-600">Local Retail Manager</h1>;
}
```

Run it:

```bash
npm run dev
```

Open **http://localhost:5173** → "Local Retail Manager" in green.

### ✅ Checkpoint (frontend skeleton)

- [ ] `npm install` completes without errors
- [ ] `npm run dev` starts on port 5173
- [ ] The page shows styled text (proving Tailwind works)

### If it doesn't work

| Error | Why | Fix |
|---|---|---|
| `npm ERR! code ERESOLVE` | Dependency conflict | Usually a stale lockfile; delete `node_modules` + `package-lock.json`, `npm install` again |
| Page shows unstyled HTML | Tailwind plugin not wired | Check `vite.config.ts` has `tailwindcss()` in plugins and `index.css` has `@import "tailwindcss"` |

Commit:

```bash
git add -A
git commit -m "feat: scaffold backend and frontend skeletons"
```

## 1.9 Mini-project: hello-world Tauri app (prove the desktop toolchain)

> Why now? The real desktop integration is Phase 23, but if the Tauri toolchain is broken we want to know *today*, not three weeks from now. This is also your first **mini project** — a small isolated exercise that teaches the core concept before the big integration.

Create a scratch app in a temp folder (NOT inside our project):

```bash
cd /tmp
npm create tauri-app@latest hello-tauri -- --template react-ts --manager npm
cd hello-tauri
npm install
npm run tauri dev
```

The first compile downloads and builds Rust crates — **expect several minutes**. Eventually a desktop window opens showing the Tauri template app.

Now try the **sidecar pattern** that our real app will use — the shell plugin, which lets the desktop app launch external programs:

```bash
npm run tauri add shell
```

Then close the app. Verify the toolchain end to end:

```bash
cd hello-tauri/src-tauri
cargo build          # compiles the Rust shell — proves Rust + crates work
```

Clean up (we only needed the proof):

```bash
cd /tmp && rm -rf hello-tauri
```

### ✅ Checkpoint (Tauri toolchain)

- [ ] `npm run tauri dev` opened a desktop window (WebView2 works)
- [ ] `cargo build` inside `src-tauri` succeeded
- [ ] The `shell` plugin was added successfully

### If it doesn't work

| Error | Why | Fix |
|---|---|---|
| `rustc` not found by npm scripts | Rust not on PATH in the terminal | Install rustup, restart terminal |
| Linker error (`link.exe` not found) | Missing MSVC C++ build tools | Install *Visual Studio Build Tools* (Desktop development with C++) — Rust on Windows needs the MSVC linker |
| WebView2 error at runtime | WebView2 runtime missing | Install the Evergreen WebView2 runtime from Microsoft |
| Slow first build | Rust compiling hundreds of crates | Normal. Subsequent builds are incremental. |

---

## ✅ Phase 1 Final Checkpoint

- [ ] Python, Node, npm, Git, Rust all verified with versions
- [ ] `local-retail-manager/` created and `git init` done, first commit made
- [ ] Backend: venv created, requirements installed, `uvicorn` serves `/api/health` and `/docs`
- [ ] Frontend: Vite + React + TS + Tailwind v4 running on :5173
- [ ] Tauri hello-world window opened once (toolchain proven)

---

# Phase 2 — Project Structure

> **Goal of this phase:** build the full folder tree *deliberately*. For every directory we answer: why it exists, what belongs in it, what must NOT go in it, and how it maps to the architecture. We create only empty folders now — files come phase by phase, each with a reason.

## 2.1 The architecture → folder mapping

Our three-layer architecture maps onto the folder tree like this:

```text
Local Retail Manager (whole repo)
│
├── frontend/        ← the "presentation" layer (React UI)
├── backend/         ← the "application + data" layers (API, services, DB)
├── desktop/         ← the "shell" (Tauri/Rust) that hosts and manages the other two
├── data/            ← runtime artifacts: database, invoices, backups, logs (never committed)
├── scripts/         ← build & automation scripts
└── docs/            ← this guide lives here when you copy it into the project
```

## 2.2 The tree (final version, shown as we will build it)

```text
local-retail-manager/
│
├── .gitignore
├── README.md                      ← Phase 2 (skeleton), filled in as we go
├── LICENSE                        ← Phase 2
│
├── frontend/
│   ├── index.html                 ← Vite entry HTML
│   ├── package.json               ← npm manifest (React, Vite, Tailwind, …)
│   ├── tsconfig.json              ← TypeScript compiler settings
│   ├── vite.config.ts             ← Vite + Tailwind plugins, dev server
│   └── src/
│       ├── main.tsx               ← React bootstrap (mounts <App/>)
│       ├── App.tsx                ← Router + layout composition
│       ├── index.css              ← @import "tailwindcss"
│       ├── types/                 ← TS types mirroring the API (models + DTOs)
│       ├── constants/             ← roles, movement types, payment methods, routes
│       ├── utils/                 ← pure helpers (currency, pricing, CSV)
│       ├── services/              ← HTTP API layer (one module per resource)
│       ├── store/                 ← global state: auth, cart, toasts (zustand)
│       ├── hooks/                 ← reusable React hooks (useApi, useDebounce)
│       ├── components/
│       │   ├── ui/                ← generic: Button, Input, Modal, Table, Badge…
│       │   ├── layout/            ← Sidebar, Topbar, AppLayout, ProtectedRoute
│       │   ├── forms/             ← form components (ProductForm, CustomerForm…)
│       │   └── tables/            ← domain tables (ProductsTable, SalesTable…)
│       ├── features/
│       │   ├── billing/           ← billing-domain logic (cart wiring)
│       │   ├── inventory/         ← stock-adjustment logic
│       │   ├── products/          ← product domain helpers
│       │   ├── purchases/         ← purchase-domain helpers
│       │   ├── customers/         ← customer/credit helpers
│       │   └── reports/           ← report building blocks
│       └── pages/
│           ├── LoginPage.tsx
│           ├── DashboardPage.tsx
│           ├── BillingPage.tsx
│           ├── ProductsPage.tsx
│           ├── InventoryPage.tsx
│           ├── PurchasesPage.tsx
│           ├── CustomersPage.tsx
│           ├── SuppliersPage.tsx
│           ├── ExpensesPage.tsx
│           ├── ReportsPage.tsx
│           ├── UsersPage.tsx
│           └── SettingsPage.tsx
│
├── backend/
│   ├── requirements.txt           ← pinned Python dependencies
│   ├── .env.example               ← documented configuration template
│   ├── alembic.ini                ← Alembic config (points at env.py)
│   ├── alembic/                   ← migration environment + version scripts
│   │   ├── env.py                 ← tells Alembic which models/metadata to compare
│   │   └── versions/              ← one file per schema change (0001_initial.py…)
│   ├── app/
│   │   ├── main.py                ← FastAPI app factory, CORS, routers, lifespan
│   │   ├── core/                  ← config, security, exceptions (no app logic)
│   │   ├── database/              ← engine/session setup, seed
│   │   ├── models/                ← SQLAlchemy ORM classes (the schema)
│   │   ├── schemas/               ← Pydantic DTOs (validation + response shapes)
│   │   ├── api/
│   │   │   ├── deps.py            ← dependencies: get_db, current user, roles
│   │   │   └── routes/            ← one router module per resource
│   │   ├── services/              ← ALL business rules and transactions
│   │   ├── pdf/                   ← ReportLab invoice generation
│   │   └── utils/                 ← invoice numbering, money, constants
│   └── tests/                     ← pytest suite (unit, integration, API)
│
├── desktop/
│   ├── package.json               ← Tauri CLI scripts (dev, build)
│   └── src-tauri/
│       ├── Cargo.toml             ← Rust crate manifest (tauri, shell plugin)
│       ├── tauri.conf.json        ← app name, window, bundling, sidecar config
│       ├── capabilities/default.json ← permissions (what the UI may do)
│       ├── binaries/              ← the packaged backend.exe (sidecar) lives here
│       ├── icons/                 ← app icons
│       ├── build.rs
│       └── src/main.rs            ← Rust: spawn/kill backend, window events
│
├── data/                          ← RUNTIME data, gitignored (only .gitkeep committed)
│   ├── database/                  ← retail.db (SQLite)
│   ├── invoices/                  ← generated PDFs
│   ├── backups/                   ← backup snapshots
│   ├── exports/                   ← CSV/Excel exports
│   └── logs/                      ← app.log (rotating)
│
├── scripts/
│   ├── run_dev.bat                ← start backend + frontend together
│   ├── seed_demo.py               ← fill a fresh DB with demo data
│   ├── build_backend.bat          ← PyInstaller → backend.exe → desktop sidecar
│   └── build_app.bat              ← full installer build
│
└── docs/                          ← documentation (this guide)
```

## 2.3 Directory-by-directory: why it exists, what goes in, what must not go in

### `backend/app/core/` — the "why" of the app

- **Why:** configuration, security primitives, and error types are used by *every* other layer. Keeping them in one place means one source of truth (e.g., one `Settings` object) instead of scattered `os.getenv` calls.
- **Belongs:** `config.py` (pydantic-settings), `security.py` (hashing, tokens), `exceptions.py` (AppError hierarchy).
- **Must NOT:** business logic, routes, models.

### `backend/app/models/` and `backend/app/schemas/` — two kinds of "shape"

- **Why:** The **models** describe the *database* (tables, columns, relationships). The **schemas** describe the *API* (what a client may send, what it receives). They look similar but are different contracts — models are internal, schemas are the public interface. Keeping them separate is the difference between a hobby project and a maintainable one.
- **Belongs:** one file per table/model; one file per resource of Pydantic schemas (`ProductCreate`, `ProductRead`, …).
- **Must NOT:** schemas must not contain DB details; models must not contain validation rules for client input.

### `backend/app/api/routes/` — the HTTP face

- **Why:** one thin router per resource keeps the API discoverable and matches the API reference at the end of this guide. `deps.py` holds shared dependencies (database session, authentication, role checks).
- **Must NOT:** business rules (that's services). A route should be ~5–15 lines: parse → validate → call service → return.

### `backend/app/services/` — the heart of the application

- **Why:** all business rules and every database transaction live here (ADR-06). Services are callable from routes *and* from scripts and tests without HTTP.
- **Belongs:** `sale_service.py`, `inventory_service.py`, `product_service.py`, …
- **Must NOT:** HTTP-specific code, Pydantic response shaping.

### `backend/tests/` — the safety net

- **Why:** tests run against services and API directly; they use an in-memory SQLite so they never touch your real data (Phase 21).

### `frontend/src/` layers — mirror the backend's separation

- `types/` ↔ backend `schemas/` (the same shapes on both sides of the wire).
- `services/` ↔ backend `api/routes/` (one module per resource).
- `store/` — global UI state (auth, cart) that many components share.
- `components/ui/` — generic, reusable pieces with no business knowledge (a `Button` doesn't know what a product is).
- `components/forms|tables/` — domain-aware pieces (a `ProductForm` knows products).
- `features/` — cross-cutting domain logic that doesn't belong to a single page (e.g., cart pricing used by Billing).
- `pages/` — one file per route; pages compose components, features, and services. Pages should contain *no* business math.

### `data/` — the shop's reality

- **Why:** one clearly-named place for everything the app *produces* — the database, invoices, backups, logs, exports. In development this is the repo's `data/` folder; in the packaged app, Tauri redirects the backend to the OS **app-data directory** (Phase 23). Because the location is *configurable*, one codebase serves both.
- **Must NOT:** be committed to git (the `.gitignore` above). Committing `retail.db` means committing the shop's financial history to a repository.

### `desktop/` — the shell

- **Why:** `src-tauri/` is a standard Tauri crate. We placed it under a top-level `desktop/` folder (instead of inside `frontend/`) to match the requested architecture and keep the three layers visually separate; `tauri.conf.json` points the shell at `../frontend/dist` and the dev server at `http://localhost:5173`.
- **Must NOT:** application code. The shell only launches/manages processes and opens the window.

### `scripts/` — repeatable builds

- **Why:** "build the installer" should be one double-click, not a 15-step ritual you half-remember. Anything a human does twice becomes a script.

## 2.4 What we create *now*

Create all empty folders (git keeps folders only via `.gitkeep` files):

```bash
# backend
cd backend
mkdir -p app/core app/database app/models app/schemas app/api/routes app/services app/pdf app/utils tests alembic/versions
touch app/__init__.py app/core/__init__.py app/database/__init__.py app/models/__init__.py \
      app/schemas/__init__.py app/api/__init__.py app/api/routes/__init__.py \
      app/services/__init__.py app/pdf/__init__.py app/utils/__init__.py tests/__init__.py
touch app/api/routes/.gitkeep app/models/.gitkeep app/schemas/.gitkeep alembic/versions/.gitkeep

# frontend subfolders
cd ../frontend/src
mkdir -p types constants utils services store hooks components/ui components/layout components/forms components/tables features/billing features/inventory features/products features/purchases features/customers features/reports pages
touch types/.gitkeep constants/.gitkeep utils/.gitkeep services/.gitkeep store/.gitkeep hooks/.gitkeep components/ui/.gitkeep components/layout/.gitkeep pages/.gitkeep

# desktop
cd ../../..
mkdir -p desktop/src-tauri/binaries desktop/src-tauri/capabilities desktop/src-tauri/icons
touch desktop/src-tauri/binaries/.gitkeep

# scripts
touch scripts/.gitkeep
```

> **Why `__init__.py` everywhere?** Python treats a folder as an importable *package* only if it contains `__init__.py`. `from app.services.sale_service import create_sale` works because every folder on the path is a package. (Empty files are fine — the file's existence is what matters.)

### ✅ Checkpoint (structure)

- [ ] `git status` shows only the folders above (no `node_modules`, no `venv`, no `.db` files — proving `.gitignore` works)
- [ ] `python -c "import app.main"` from `backend/` succeeds (packages importable)
- [ ] `npm run dev` still works from `frontend/`

Commit:

```bash
git add -A
git commit -m "feat: add project folder structure"
```

### If it doesn't work

| Error | Why | Fix |
|---|---|---|
| `python -c "import app.main"` fails from another folder | Python imports relative to your current working directory | Run it from `backend/`, or run with `cd backend && python -m app.main` |
| git shows `venv/` as untracked | `.gitignore` pattern wrong | Ensure the line `venv/` exists at the root of `.gitignore` |

---

## ✅ Phase 2 Final Checkpoint

- [ ] Full folder tree created with `.gitkeep` files
- [ ] `.gitignore` excludes venv, node_modules, and all runtime data
- [ ] Backend package imports cleanly
- [ ] Frontend dev server still runs
- [ ] Structure committed with a meaningful message

---

**Next:** [Phase 3 — Database Design](#phase-3--database-design)
# Phase 3 — Database Design

> **Goal of this phase:** understand relational database concepts, design the complete schema for a retail business, draw its ER diagram, and implement it with SQLAlchemy 2.x models + Alembic migrations. By the end, a real `retail.db` file exists with all tables and is created/upgraded through versioned migrations.

This is the most important phase in the guide. **Every later feature (billing, inventory, credit, profit) is just careful use of these tables.** Don't rush it.

## 3.1 Concepts first — the relational model

### Tables and rows

A **table** is a set of records (rows) with the same structure (columns). Think of a spreadsheet where every row is one thing: one product, one sale, one customer. Our database will have **12 domain tables + 1 settings table**.

### Primary keys (PK)

Every row needs a unique identity. We use **surrogate integer primary keys** (`id`): an auto-incrementing number with no business meaning. Why not use the invoice number or barcode as the key? Because *business numbers change* (a barcode can be re-printed, an invoice re-numbered) and are long. A small immutable integer is faster to index and to reference from other tables. This is the single most important habit in schema design: **the PK is an id, not a value.**

### Foreign keys (FK) and relationships

A **foreign key** is a column holding the `id` of a row in *another* table. It's how tables reference each other, and it's what the database uses to *enforce* relationships.

- `sale_items.product_id` → references `products.id`: "this line belongs to that product".
- `sales.customer_id` → references `customers.id`: "this sale belongs to that customer".

The two relationships you'll see constantly:

| Relationship | Pattern | Example |
|---|---|---|
| **One-to-many (1:N)** | A row in A is referenced by many rows in B | One *customer* has many *sales*; the FK lives on the "many" side (`sales.customer_id`) |
| **Many-to-one** | The reverse view of 1:N | Many *sales* belong to one *customer* |

Rule of thumb: **the FK goes on the "many" side.** A sale has one customer → `sales.customer_id`. A customer has many sales → no column on customers; the relationship is discovered through `sales.customer_id`.

### Transactions

A **transaction** is a group of operations that succeed or fail *as one unit*:

```text
BEGIN;
INSERT INTO sales (...);
INSERT INTO sale_items (...);
INSERT INTO inventory_movements (...);
COMMIT;          -- all four become permanent together
-- if any statement fails:
ROLLBACK;        -- all four are undone; database unchanged
```

This is how we guarantee the requirement from Phase 0: *never a sale without a stock movement, never stock movement without a sale.* SQLite gives us ACID transactions out of the box; our job is to use them correctly in the service layer (Phase 7).

### Constraints

Rules the database itself enforces — no application code required:

- **NOT NULL** — column must have a value.
- **UNIQUE** — no two rows may share a value (e.g., `products.barcode`, `sales.invoice_no`). This is how duplicate invoices are *made impossible*, not just "avoided".
- **CHECK** — arbitrary condition (e.g., `quantity > 0`).
- **FK with actions** — `ON DELETE CASCADE` (delete the sale → delete its items) vs `ON DELETE RESTRICT` (refuse to delete a product that has sales — protecting history) vs `ON DELETE SET NULL` (deleting a category sets the product's category to null, keeping the product).

### Indexes

An **index** is a sorted copy of a column's values that lets the database find rows *without scanning the whole table*. Indexes make reads fast but slow writes slightly and cost disk space.

Index what you *filter/sort by*: foreign keys, dates, and unique business keys (`barcode`, `invoice_no`). Don't index everything.

### Normalization

**Normalization** is the discipline of storing each fact once, in one place, eliminating duplication and the inconsistencies duplication causes. Our schema is in **3NF**:

- **1NF:** atomic values, no repeating groups → one `sale_item` row per product line, never a comma-separated list of products in a column.
- **2NF:** no partial dependencies → sale items reference `product_id`, they don't re-store the product's name or price history as text.
- **3NF:** no transitive dependencies → product category lives in `categories`, referenced by `category_id`, not copied into every product row.

The one intentional exception is documented below (the `current_stock` cache column) — deliberate denormalization with a clear reason and a compensating mechanism.

### Audit trails

An **audit trail** answers *who did what, when, and why*. We build this in three ways:

1. **Timestamp columns** (`created_at`, `updated_at`) on every table.
2. **`created_by_id`** (the user) on sales, purchases, payments, expenses, movements.
3. **The inventory ledger itself** — an append-only record of *why* stock changed, with a human-readable note and a reference back to the source document (sale/purchase id).

## 3.2 The schema design

Here is the complete design. Each table's purpose is stated, then the relationships.

### Tables and their purpose

| Table | Purpose | Key columns |
|---|---|---|
| `users` | Login accounts + role | username (unique), password_hash, role |
| `categories` | Product groupings (Groceries, Dairy, …) | name (unique) |
| `products` | Everything sellable | name, sku, barcode, category_id, purchase_price, selling_price, tax_rate, min_stock, **current_stock**, **avg_cost**, is_active |
| `customers` | People who buy (incl. credit customers) | name, phone |
| `suppliers` | People we buy from | name, phone |
| `sales` | One completed sale (the header) | invoice_no (unique), customer_id, subtotal/discount/tax/total, status, sale_date |
| `sale_items` | Each line of a sale | sale_id, product_id, quantity, unit_price, tax_rate, line_total, returned_qty |
| `purchases` | One purchase from a supplier (header) | purchase_no (unique), supplier_id, totals, paid_amount, status |
| `purchase_items` | Each line of a purchase | purchase_id, product_id, quantity, unit_cost, line_total |
| `payments` | Money received/paid, tied to a sale/purchase/customer | sale_id, purchase_id, customer_id, amount, method, paid_at |
| `expenses` | Operating costs (rent, electricity, salaries…) | expense_date, category, amount |
| `inventory_movements` | The audit ledger of every stock change | product_id, movement_type, quantity (signed), unit_cost, ref_type, ref_id, note |
| `app_settings` | Shop profile editable at runtime (name, address, GSTIN, currency, tax) | single row, id=1 |

### The ER diagram

```mermaid
erDiagram
    users ||--o{ sales : "created_by"
    users ||--o{ payments : "created_by"
    users ||--o{ expenses : "created_by"
    users ||--o{ inventory_movements : "created_by"

    categories ||--o{ products : "has"

    products ||--o{ sale_items : "sold in"
    products ||--o{ purchase_items : "bought in"
    products ||--o{ inventory_movements : "movements"

    customers ||--o{ sales : "places"
    customers ||--o{ payments : "pays"

    suppliers ||--o{ purchases : "supplies"
    suppliers ||--o{ payments : "receives"

    sales ||--|{ sale_items : "contains"
    sales ||--o{ payments : "settled by"

    purchases ||--|{ purchase_items : "contains"
    purchases ||--o{ payments : "settled by"
```

### The four critical design decisions (explained)

**1. `sales` and `sale_items` are separate (header/line pattern).** The header holds what is true of the whole sale (customer, totals, invoice number); the lines hold per-product data. This is 2NF: the sale's total is *derived* from lines, and the header exists once even if it has 1 or 40 lines. Same for purchases.

**2. `payments` is one table for money in and money out.** A payment is either *received* (a sale payment, or a customer paying off old credit — `customer_id`, positive amount) or *made* (a purchase payment, or refund — negative amount). One table, one set of rules, one ledger for cash. The `sale_id` / `purchase_id` / `customer_id` columns are **mutually exclusive** — exactly one is set (a payment is *for* a sale, *for* a purchase, or *for* a customer's standing credit).

**3. `inventory_movements` is append-only.** Stock is never just "set" — every change is a new row with a type, a signed quantity, the cost at the time, and a reference to the source document. Current stock is a *derived* number (Phase 6).

**4. `app_settings` is the one addition to your requested table list.** Your spec's tables cover the business. But invoices need a shop name/address/GSTIN that the *owner changes in the UI* (Settings page) — that's runtime *data*, so it belongs in the database, not in code or env vars. It's a single-row table (`id = 1` enforced), a common pattern for "application preferences". If you disagree, you can drop it and keep shop details in `config.py` only — but then Settings can't edit them.

### Where the money math happens (recap of ADR-10)

- **In the database:** `NUMERIC(12, 2)` — fixed-point, 10 integer digits + 2 decimals, exact.
- **In Python business logic:** `Decimal` with `ROUND_HALF_UP`.
- **Over the API:** float (JSON has no Decimal).

We write this helper once — `backend/app/utils/money.py`:

```python
"""Money helpers: every amount in the business layer goes through these.

Why Decimal? Binary floats cannot represent 0.1 exactly, so summing floats
silently drifts (0.1 + 0.2 == 0.30000000000000004). Decimal is exact.
Why ROUND_HALF_UP? This is the rounding shopkeepers expect (half rounds up,
like school arithmetic) — not banker's rounding.
"""
from decimal import ROUND_HALF_UP, Decimal

TWO_PLACES = Decimal("0.01")
FOUR_PLACES = Decimal("0.0001")


def money(value: Decimal | float | int | str) -> Decimal:
    """Normalize any value to an exact 2-decimal-place Decimal."""
    return Decimal(str(value)).quantize(TWO_PLACES, rounding=ROUND_HALF_UP)


def percent(value: Decimal | float | int | str) -> Decimal:
    """Normalize a percentage (e.g. 5.0 for 5%) to 4 decimal places."""
    return Decimal(str(value)).quantize(FOUR_PLACES, rounding=ROUND_HALF_UP)
```

> `Decimal(str(value))` — converting through a *string* avoids the float-representation trap. `Decimal(0.1)` carries float noise; `Decimal("0.1")` is exact. This one habit prevents a whole class of money bugs.

## 3.3 Implement: configuration and database connection

### Step 1 — `backend/app/core/config.py` (typed configuration)

Every magic value (database location, port, secret key, shop name) becomes a typed setting. `pydantic-settings` reads from environment variables with the `LRM_` prefix and from a `.env` file:

```python
from pathlib import Path

from pydantic_settings import BaseSettings, SettingsConfigDict


class Settings(BaseSettings):
    """Application configuration.

    Values come from (highest priority first):
      1. real environment variables (prefix LRM_, e.g. LRM_PORT)
      2. a .env file in the backend/ folder
      3. the defaults below
    """

    model_config = SettingsConfigDict(env_prefix="LRM_", env_file=".env", extra="ignore")

    APP_NAME: str = "Local Retail Manager"
    ENV: str = "development"

    # Server
    HOST: str = "127.0.0.1"
    PORT: int = 8000

    # Data locations — the packaged app overrides DATA_DIR via LRM_DATA_DIR
    DATA_DIR: Path = Path("./data")
    DATABASE_FILE: str = "retail.db"

    # Auth
    SECRET_KEY: str = "change-me-please"
    TOKEN_EXPIRE_MINUTES: int = 480  # 8 working hours

    # CORS: the Vite dev server, and the Tauri WebView origin (Windows)
    CORS_ORIGINS: list[str] = ["http://localhost:5173", "http://tauri.localhost"]

    # Shop profile — defaults used when app_settings has no row yet
    SHOP_NAME: str = "My Shop"
    SHOP_ADDRESS: str = ""
    SHOP_PHONE: str = ""
    SHOP_GSTIN: str = ""
    CURRENCY: str = "₹"
    DEFAULT_TAX_RATE: float = 0.0

    # Backups
    BACKUP_KEEP_DAYS: int = 14

    # First-run admin (WARNING: change after first login)
    DEFAULT_ADMIN_USERNAME: str = "owner"
    DEFAULT_ADMIN_PASSWORD: str = "admin123"

    # ------------------------------------------------------------------
    # Derived paths (properties, not stored values)
    # ------------------------------------------------------------------
    @property
    def db_dir(self) -> Path:
        return self.DATA_DIR / "database"

    @property
    def invoices_dir(self) -> Path:
        return self.DATA_DIR / "invoices"

    @property
    def backups_dir(self) -> Path:
        return self.DATA_DIR / "backups"

    @property
    def exports_dir(self) -> Path:
        return self.DATA_DIR / "exports"

    @property
    def logs_dir(self) -> Path:
        return self.DATA_DIR / "logs"

    @property
    def database_url(self) -> str:
        # .as_posix() → forward slashes, required by SQLAlchemy URL parsing on Windows
        db_file = (self.db_dir / self.DATABASE_FILE).as_posix()
        return f"sqlite:///{db_file}"

    def ensure_dirs(self) -> None:
        """Create every runtime folder. Called once at startup."""
        for d in (self.db_dir, self.invoices_dir, self.backups_dir,
                  self.exports_dir, self.logs_dir):
            d.mkdir(parents=True, exist_ok=True)


settings = Settings()  # one shared instance for the whole app
```

Explain line by line:

- `class Settings(BaseSettings)` — a Pydantic model whose fields are filled from env vars / `.env`. Defining config as a *class* gives us type checking and autocomplete instead of raw `os.getenv` strings scattered everywhere.
- `model_config = SettingsConfigDict(env_prefix="LRM_", ...)` — reads `LRM_PORT`, `LRM_DATA_DIR`, etc. The prefix prevents collisions with other software's variables.
- The `@property` blocks derive paths from `DATA_DIR`. In development `DATA_DIR=./data` (relative to `backend/`); in the packaged app Tauri sets `LRM_DATA_DIR` to the OS app-data directory — the *same code*, a different location.
- `settings = Settings()` at module bottom = **singleton**. Import it anywhere: `from app.core.config import settings`.

Create `backend/.env.example` (a template you copy to `.env`; `.env` is gitignored):

```text
# Copy to .env and adjust. NEVER commit the real .env (it holds the secret key).
LRM_ENV=development
LRM_HOST=127.0.0.1
LRM_PORT=8000
LRM_DATA_DIR=./data
LRM_SECRET_KEY=please-generate-a-long-random-string
LRM_SHOP_NAME=My Shop
LRM_SHOP_ADDRESS=123 Main Street
LRM_SHOP_PHONE=+91 98765 43210
LRM_SHOP_GSTIN=
LRM_CURRENCY=₹
LRM_DEFAULT_TAX_RATE=0
LRM_DEFAULT_ADMIN_USERNAME=owner
LRM_DEFAULT_ADMIN_PASSWORD=admin123
```

### Step 2 — `backend/app/database/database.py` (engine + sessions)

```python
from sqlalchemy import create_engine, event
from sqlalchemy.orm import sessionmaker

from app.core.config import settings


def _set_sqlite_pragmas(dbapi_connection, _connection_record):
    """Run per-connection PRAGMAs. These make SQLite safe for our app."""
    cursor = dbapi_connection.cursor()
    cursor.execute("PRAGMA foreign_keys=ON")   # enforce FK constraints (off by default!)
    cursor.execute("PRAGMA journal_mode=WAL")  # better concurrency + crash safety
    cursor.execute("PRAGMA busy_timeout=5000") # wait 5s instead of failing on locks
    cursor.close()


engine = create_engine(
    settings.database_url,
    connect_args={"check_same_thread": False},  # allow use from any thread
)
event.listen(engine, "connect", _set_sqlite_pragmas)

SessionLocal = sessionmaker(bind=engine, autoflush=False, expire_on_commit=False)


def get_db():
    """FastAPI dependency: one session per request, always closed."""
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()
```

Explain line by line — these three PRAGMAs are *the* difference between a toy SQLite app and a reliable one:

- `PRAGMA foreign_keys=ON` — SQLite does **not** enforce foreign keys by default. Without this line, a sale item could point at a nonexistent product. We turn enforcement on for every connection.
- `PRAGMA journal_mode=WAL` — **Write-Ahead Logging**: readers don't block the writer and vice versa, and it dramatically reduces the chance of database corruption on a sudden power cut. This is important on a shop PC that may be unplugged at any moment.
- `PRAGMA busy_timeout=5000` — if another connection holds a lock, wait up to 5 seconds rather than erroring immediately.
- `check_same_thread=False` — lets FastAPI's thread pool use the engine from any thread. Required for a single shared engine with multiple request threads.
- `sessionmaker(..., expire_on_commit=False)` — after `commit()`, ORM objects stay usable (their attributes aren't reloaded from the DB on access). Simplifies returning objects from services.
- `get_db()` is a **dependency**: FastAPI calls it per request, we `yield` the session, and the `finally` guarantees closure even if the request crashes. This is our first use of FastAPI dependency injection (fully explained in Phase 4).

### Step 3 — `backend/app/models/base.py` and the enums

```python
from datetime import datetime

from sqlalchemy import DateTime
from sqlalchemy.orm import DeclarativeBase, Mapped, mapped_column


class Base(DeclarativeBase):
    """Root class of every ORM model. SQLAlchemy discovers tables through it."""


class TimestampMixin:
    """Adds created_at / updated_at to any model that inherits it."""

    created_at: Mapped[datetime] = mapped_column(DateTime, default=datetime.now, nullable=False)
    updated_at: Mapped[datetime] = mapped_column(
        DateTime, default=datetime.now, onupdate=datetime.now, nullable=False
    )
```

- `class Base(DeclarativeBase)` — SQLAlchemy 2.x style. All models inherit it; it holds the shared registry that Alembic inspects (`Base.metadata`).
- `TimestampMixin` — a **mixin**: a class that contributes columns to inheriting models. `onupdate=datetime.now` automatically stamps `updated_at` whenever the row changes.
- **Timezone note:** we deliberately store *local naive* datetimes (Python-side `datetime.now()`), not UTC. A single-shop, single-timezone desktop app thinks in local time (sales reports by "today" should match the wall clock). For a multi-shop cloud product you'd switch to UTC — a documented trade-off, not an accident.

Enums define the fixed vocabularies of the system — `backend/app/models/enums.py`:

```python
import enum


class UserRole(enum.StrEnum):
    OWNER = "OWNER"
    MANAGER = "MANAGER"
    CASHIER = "CASHIER"


class SaleStatus(enum.StrEnum):
    COMPLETED = "COMPLETED"
    RETURNED = "RETURNED"


class PurchaseStatus(enum.StrEnum):
    COMPLETED = "COMPLETED"
    PARTIAL = "PARTIAL"


class PaymentMethod(enum.StrEnum):
    CASH = "CASH"
    UPI = "UPI"
    CARD = "CARD"
    CREDIT = "CREDIT"
    BANK = "BANK"


class MovementType(enum.StrEnum):
    PURCHASE = "PURCHASE"      # stock in (positive)
    SALE = "SALE"              # stock out (negative)
    RETURN = "RETURN"          # stock back in (positive)
    ADJUSTMENT = "ADJUSTMENT"  # manual correction (signed)
    DAMAGE = "DAMAGE"          # stock out, not sold (negative)
```

> `enum.StrEnum` (Python 3.11+) — each member *is* a string, so it stores cleanly in a `String` column and reads naturally in logs.

### Step 4 — the models

Every model file follows the same shape: a class inheriting `TimestampMixin, Base`, a `__tablename__`, typed columns with `Mapped[...]`, and relationships. We teach **`Product`** line by line, then list the rest (they follow the identical pattern).

`backend/app/models/product.py`:

```python
from decimal import Decimal

from sqlalchemy import ForeignKey, Numeric, String
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin


class Product(TimestampMixin, Base):
    """A sellable item. The most-referenced table in the system."""

    __tablename__ = "products"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(200), index=True)
    sku: Mapped[str | None] = mapped_column(String(50), unique=True, index=True)
    barcode: Mapped[str | None] = mapped_column(String(100), unique=True, index=True)

    category_id: Mapped[int | None] = mapped_column(
        ForeignKey("categories.id", ondelete="SET NULL")
    )
    category: Mapped["Category | None"] = relationship(back_populates="products")

    purchase_price: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    selling_price: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    tax_rate: Mapped[Decimal] = mapped_column(Numeric(5, 2), default=Decimal("0"))
    min_stock: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))

    # Denormalized cache — source of truth is inventory_movements (ADR-07)
    current_stock: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    avg_cost: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))

    is_active: Mapped[bool] = mapped_column(default=True)

    inventory_movements: Mapped[list["InventoryMovement"]] = relationship(
        back_populates="product"
    )
```

Explain line by line:

- `Mapped[int]` / `Mapped[str]` — SQLAlchemy 2.x **typed** column declaration. The Python type drives the column type (`int` → INTEGER, `str` → VARCHAR). No more `Column(Integer)` verbosity.
- `primary_key=True` — the surrogate PK (Section 3.1).
- `unique=True, index=True` on `sku`/`barcode` — the database *enforces* "no two products with the same barcode" (data integrity, not convention). The index makes barcode lookups (billing scans!) instant.
- `ForeignKey("categories.id", ondelete="SET NULL")` — FK constraint **plus** a delete rule: deleting a category nulls the product's `category_id` instead of failing or cascading. The product survives.
- `Mapped[Decimal] = mapped_column(Numeric(12, 2), ...)` — fixed-point money (ADR-10). SQLAlchemy maps this to Python `Decimal` automatically.
- `current_stock` / `avg_cost` — the two cache columns maintained by the inventory service *in the same transaction* as the ledger rows (Phase 6).
- `is_active` — **soft delete**: we never destroy products that appear in past sales; we deactivate them. History stays intact (Phase 5).

> `mapped_column(default=Decimal("0"))` — careful: use `Decimal("0")` (string constructor), never `0.0`.

Now the remaining models. Read each one and verify it matches the ER diagram.

`backend/app/models/category.py`:

```python
from sqlalchemy import String
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin


class Category(TimestampMixin, Base):
    __tablename__ = "categories"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(100), unique=True, index=True)
    description: Mapped[str | None] = mapped_column(String(255))

    products: Mapped[list["Product"]] = relationship(back_populates="category")
```

`backend/app/models/user.py`:

```python
from sqlalchemy import Boolean, Enum as SAEnum, String
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin
from .enums import UserRole


class User(TimestampMixin, Base):
    __tablename__ = "users"

    id: Mapped[int] = mapped_column(primary_key=True)
    username: Mapped[str] = mapped_column(String(50), unique=True, index=True)
    full_name: Mapped[str] = mapped_column(String(100))
    password_hash: Mapped[str] = mapped_column(String(200))  # bcrypt hash, NEVER plaintext
    role: Mapped[UserRole] = mapped_column(
        SAEnum(UserRole, native_enum=False, length=20), default=UserRole.CASHIER
    )
    is_active: Mapped[bool] = mapped_column(Boolean, default=True)

    sales: Mapped[list["Sale"]] = relationship(back_populates="created_by")
```

> `SAEnum(UserRole, native_enum=False, length=20)` — SQLite has no native enum type, so we store the enum *value as a VARCHAR(20)* while keeping Python-side validation. `native_enum=False` is required for SQLite.

`backend/app/models/customer.py`:

```python
from sqlalchemy import Boolean, String
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin


class Customer(TimestampMixin, Base):
    __tablename__ = "customers"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(150), index=True)
    phone: Mapped[str | None] = mapped_column(String(20), index=True)
    address: Mapped[str | None] = mapped_column(String(255))
    notes: Mapped[str | None] = mapped_column(String(255))
    is_active: Mapped[bool] = mapped_column(Boolean, default=True)

    sales: Mapped[list["Sale"]] = relationship(back_populates="customer")
    payments: Mapped[list["Payment"]] = relationship(back_populates="customer")
```

`backend/app/models/supplier.py` — identical pattern:

```python
from sqlalchemy import Boolean, String
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin


class Supplier(TimestampMixin, Base):
    __tablename__ = "suppliers"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(150), index=True)
    phone: Mapped[str | None] = mapped_column(String(20))
    address: Mapped[str | None] = mapped_column(String(255))
    notes: Mapped[str | None] = mapped_column(String(255))
    is_active: Mapped[bool] = mapped_column(Boolean, default=True)

    purchases: Mapped[list["Purchase"]] = relationship(back_populates="supplier")
    payments: Mapped[list["Payment"]] = relationship(back_populates="supplier")
```

`backend/app/models/sale.py`:

```python
from datetime import datetime

from sqlalchemy import DateTime, Enum as SAEnum, ForeignKey, Numeric, String
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin
from .enums import SaleStatus


class Sale(TimestampMixin, Base):
    __tablename__ = "sales"

    id: Mapped[int] = mapped_column(primary_key=True)
    invoice_no: Mapped[str] = mapped_column(String(30), unique=True, index=True)

    customer_id: Mapped[int | None] = mapped_column(
        ForeignKey("customers.id", ondelete="SET NULL"), index=True
    )
    customer: Mapped["Customer | None"] = relationship(back_populates="sales")

    subtotal: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    discount_pct: Mapped[Decimal] = mapped_column(Numeric(5, 2), default=Decimal("0"))
    discount: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    tax: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    total: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))

    status: Mapped[SaleStatus] = mapped_column(
        SAEnum(SaleStatus, native_enum=False, length=20), default=SaleStatus.COMPLETED
    )
    sale_date: Mapped[datetime] = mapped_column(DateTime, default=datetime.now, index=True)
    notes: Mapped[str | None] = mapped_column(String(255))

    created_by_id: Mapped[int | None] = mapped_column(ForeignKey("users.id", ondelete="SET NULL"))
    created_by: Mapped["User | None"] = relationship(back_populates="sales")

    items: Mapped[list["SaleItem"]] = relationship(
        back_populates="sale", cascade="all, delete-orphan"
    )
    payments: Mapped[list["Payment"]] = relationship(back_populates="sale")
```

- `invoice_no` — **UNIQUE**: duplicate invoice numbers are impossible at the database level.
- `cascade="all, delete-orphan"` on `items` — deleting a sale deletes its lines (and only its lines). The sale header owns its items.

`backend/app/models/sale_item.py`:

```python
from decimal import Decimal

from sqlalchemy import ForeignKey, Numeric
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin


class SaleItem(TimestampMixin, Base):
    __tablename__ = "sale_items"

    id: Mapped[int] = mapped_column(primary_key=True)
    sale_id: Mapped[int] = mapped_column(
        ForeignKey("sales.id", ondelete="CASCADE"), index=True
    )
    sale: Mapped["Sale"] = relationship(back_populates="items")

    product_id: Mapped[int] = mapped_column(
        ForeignKey("products.id", ondelete="RESTRICT"), index=True
    )
    product: Mapped["Product"] = relationship()

    quantity: Mapped[Decimal] = mapped_column(Numeric(12, 2))
    unit_price: Mapped[Decimal] = mapped_column(Numeric(12, 2))
    tax_rate: Mapped[Decimal] = mapped_column(Numeric(5, 2), default=Decimal("0"))
    line_total: Mapped[Decimal] = mapped_column(Numeric(12, 2))   # qty × unit_price
    returned_qty: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
```

- `ondelete="RESTRICT"` on `product_id` — the database refuses to delete a product that appears in a sale. History is protected by the schema itself.

`backend/app/models/purchase.py` and `purchase_item.py` — the mirror image of sales:

```python
from datetime import datetime

from sqlalchemy import DateTime, Enum as SAEnum, ForeignKey, Numeric, String
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin
from .enums import PaymentMethod, PurchaseStatus


class Purchase(TimestampMixin, Base):
    __tablename__ = "purchases"

    id: Mapped[int] = mapped_column(primary_key=True)
    purchase_no: Mapped[str] = mapped_column(String(30), unique=True, index=True)

    supplier_id: Mapped[int | None] = mapped_column(
        ForeignKey("suppliers.id", ondelete="SET NULL"), index=True
    )
    supplier: Mapped["Supplier | None"] = relationship(back_populates="purchases")

    purchase_date: Mapped[datetime] = mapped_column(DateTime, default=datetime.now, index=True)
    subtotal: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    discount: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    tax: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    total: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    paid_amount: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    payment_method: Mapped[PaymentMethod] = mapped_column(
        SAEnum(PaymentMethod, native_enum=False, length=20), default=PaymentMethod.CASH
    )
    status: Mapped[PurchaseStatus] = mapped_column(
        SAEnum(PurchaseStatus, native_enum=False, length=20), default=PurchaseStatus.COMPLETED
    )
    notes: Mapped[str | None] = mapped_column(String(255))

    created_by_id: Mapped[int | None] = mapped_column(ForeignKey("users.id", ondelete="SET NULL"))
    created_by: Mapped["User | None"] = relationship()

    items: Mapped[list["PurchaseItem"]] = relationship(
        back_populates="purchase", cascade="all, delete-orphan"
    )
    payments: Mapped[list["Payment"]] = relationship(back_populates="purchase")


class PurchaseItem(TimestampMixin, Base):
    __tablename__ = "purchase_items"

    id: Mapped[int] = mapped_column(primary_key=True)
    purchase_id: Mapped[int] = mapped_column(
        ForeignKey("purchases.id", ondelete="CASCADE"), index=True
    )
    purchase: Mapped["Purchase"] = relationship(back_populates="items")

    product_id: Mapped[int] = mapped_column(
        ForeignKey("products.id", ondelete="RESTRICT"), index=True
    )
    product: Mapped["Product"] = relationship()

    quantity: Mapped[Decimal] = mapped_column(Numeric(12, 2))
    unit_cost: Mapped[Decimal] = mapped_column(Numeric(12, 2))
    tax_rate: Mapped[Decimal] = mapped_column(Numeric(5, 2), default=Decimal("0"))
    line_total: Mapped[Decimal] = mapped_column(Numeric(12, 2))
```

`backend/app/models/payment.py`:

```python
from datetime import datetime

from sqlalchemy import DateTime, Enum as SAEnum, ForeignKey, Numeric, String
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin
from .enums import PaymentMethod


class Payment(TimestampMixin, Base):
    """Money received (positive) or paid/refunded (negative).

    Exactly ONE of sale_id / purchase_id / customer_id is set:
      - sale_id      → payment for a sale (or refund, negative)
      - purchase_id  → payment made to a supplier for a purchase
      - customer_id  → customer settling old credit (no sale involved)
    """

    __tablename__ = "payments"

    id: Mapped[int] = mapped_column(primary_key=True)
    sale_id: Mapped[int | None] = mapped_column(
        ForeignKey("sales.id", ondelete="SET NULL"), index=True
    )
    sale: Mapped["Sale | None"] = relationship(back_populates="payments")

    purchase_id: Mapped[int | None] = mapped_column(
        ForeignKey("purchases.id", ondelete="SET NULL"), index=True
    )
    purchase: Mapped["Purchase | None"] = relationship(back_populates="payments")

    customer_id: Mapped[int | None] = mapped_column(
        ForeignKey("customers.id", ondelete="SET NULL"), index=True
    )
    customer: Mapped["Customer | None"] = relationship(back_populates="payments")

    supplier_id: Mapped[int | None] = mapped_column(
        ForeignKey("suppliers.id", ondelete="SET NULL"), index=True
    )
    supplier: Mapped["Supplier | None"] = relationship(back_populates="payments")

    amount: Mapped[Decimal] = mapped_column(Numeric(12, 2))  # signed!
    method: Mapped[PaymentMethod] = mapped_column(
        SAEnum(PaymentMethod, native_enum=False, length=20), default=PaymentMethod.CASH
    )
    reference: Mapped[str | None] = mapped_column(String(100))
    paid_at: Mapped[datetime] = mapped_column(DateTime, default=datetime.now, index=True)

    created_by_id: Mapped[int | None] = mapped_column(ForeignKey("users.id", ondelete="SET NULL"))
    created_by: Mapped["User | None"] = relationship()
```

`backend/app/models/expense.py`:

```python
from datetime import datetime
from decimal import Decimal

from sqlalchemy import DateTime, ForeignKey, Numeric, String
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin


class Expense(TimestampMixin, Base):
    __tablename__ = "expenses"

    id: Mapped[int] = mapped_column(primary_key=True)
    expense_date: Mapped[datetime] = mapped_column(DateTime, default=datetime.now, index=True)
    category: Mapped[str] = mapped_column(String(50), index=True)  # Rent, Electricity, ...
    amount: Mapped[Decimal] = mapped_column(Numeric(12, 2))
    description: Mapped[str | None] = mapped_column(String(255))

    created_by_id: Mapped[int | None] = mapped_column(ForeignKey("users.id", ondelete="SET NULL"))
    created_by: Mapped["User | None"] = relationship()
```

`backend/app/models/inventory_movement.py` — the audit ledger (Phase 6's star):

```python
from datetime import datetime
from decimal import Decimal

from sqlalchemy import DateTime, Enum as SAEnum, ForeignKey, Index, Numeric, String
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin
from .enums import MovementType


class InventoryMovement(TimestampMixin, Base):
    """One fact: 'stock of product X changed by N because of document Y'.

    quantity is SIGNED: positive = stock in, negative = stock out.
    unit_cost is a snapshot of the product's cost AT THIS MOMENT, so we can
    value history and compute COGS even if prices change later.
    """

    __tablename__ = "inventory_movements"

    id: Mapped[int] = mapped_column(primary_key=True)
    product_id: Mapped[int] = mapped_column(
        ForeignKey("products.id", ondelete="RESTRICT"), index=True
    )
    product: Mapped["Product"] = relationship(back_populates="inventory_movements")

    movement_type: Mapped[MovementType] = mapped_column(
        SAEnum(MovementType, native_enum=False, length=20), index=True
    )
    quantity: Mapped[Decimal] = mapped_column(Numeric(12, 2))   # signed
    unit_cost: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))

    ref_type: Mapped[str | None] = mapped_column(String(30))    # "SALE", "PURCHASE", ...
    ref_id: Mapped[int | None] = mapped_column()

    note: Mapped[str | None] = mapped_column(String(255))
    created_at: Mapped[datetime] = mapped_column(DateTime, default=datetime.now, index=True)
    created_by_id: Mapped[int | None] = mapped_column(ForeignKey("users.id", ondelete="SET NULL"))
    created_by: Mapped["User | None"] = relationship()

    __table_args__ = (Index("ix_movements_ref", "ref_type", "ref_id"),)
```

`backend/app/models/setting.py` (the single-row shop profile):

```python
from decimal import Decimal

from sqlalchemy import CheckConstraint, Numeric, String
from sqlalchemy.orm import Mapped, mapped_column

from .base import Base, TimestampMixin


class AppSetting(TimestampMixin, Base):
    """Single-row table (id is always 1) holding the shop profile that the
    owner edits in Settings: invoice headers, currency, default tax."""

    __tablename__ = "app_settings"
    __table_args__ = (CheckConstraint("id = 1", name="ck_single_row"),)

    id: Mapped[int] = mapped_column(primary_key=True, default=1)
    shop_name: Mapped[str] = mapped_column(String(150), default="My Shop")
    shop_address: Mapped[str | None] = mapped_column(String(255))
    shop_phone: Mapped[str | None] = mapped_column(String(50))
    shop_gstin: Mapped[str | None] = mapped_column(String(50))
    currency: Mapped[str] = mapped_column(String(10), default="₹")
    default_tax_rate: Mapped[Decimal] = mapped_column(Numeric(5, 2), default=Decimal("0"))
    invoice_footer: Mapped[str | None] = mapped_column(String(255))
```

Finally, `backend/app/models/__init__.py` imports everything so that `Base.metadata` knows about all tables (this file is the single most likely "forgot to import" bug):

```python
from .base import Base, TimestampMixin
from .category import Category
from .customer import Customer
from .enums import (MovementType, PaymentMethod, PurchaseStatus, SaleStatus, UserRole)
from .expense import Expense
from .inventory_movement import InventoryMovement
from .payment import Payment
from .product import Product
from .purchase import Purchase, PurchaseItem
from .sale import Sale
from .sale_item import SaleItem
from .setting import AppSetting
from .supplier import Supplier
from .user import User

__all__ = [
    "Base", "TimestampMixin", "Category", "Customer", "Expense", "InventoryMovement",
    "MovementType", "PaymentMethod", "Product", "Purchase", "PurchaseItem",
    "PurchaseStatus", "Payment", "Sale", "SaleItem", "SaleStatus", "Supplier",
    "AppSetting", "User", "UserRole",
]
```

> ⚠️ **Alembic inspects `Base.metadata`.** If a model isn't imported in `__init__.py`, Alembic won't see it and the table won't be created. Whenever you add a model, add it here.

## 3.4 Alembic migrations

### Concept: why migrations?

`Base.metadata.create_all(engine)` creates missing tables but **cannot alter existing ones**. The day we add a `brand` column to products, `create_all` does nothing and the app crashes on existing databases. **Alembic** versions the schema: each change is a script that knows how to go *up* (apply) and *down* (revert). The installed app simply runs "upgrade to latest" on startup.

### Setup

```bash
cd backend
alembic init alembic
```

This creates `alembic.ini` and the `alembic/` folder. Now we make two edits.

**1. `alembic.ini`** — comment out/leave the URL (we set it from code so dev and packaged app use the right path):

```ini
# sqlalchemy.url = driver://user:pass@localhost/dbname   ← leave empty, set in env.py
```

**2. `alembic/env.py`** — this script runs inside Alembic's context; it must tell Alembic *which metadata to compare against* and *which URL to use*:

```python
from logging.config import fileConfig

from alembic import context
from sqlalchemy import engine_from_config, pool

from app.core.config import settings
from app.models import Base  # imports every model → fills Base.metadata

config = context.config
if config.config_file_name is not None:
    fileConfig(config.config_file_name)

# THE two critical lines for our app:
config.set_main_option("sqlalchemy.url", settings.database_url)
target_metadata = Base.metadata
```

*(The rest of the generated file — `run_migrations_offline`, `run_migrations_online`, the `context.configure(...)` calls — stays as generated. The only changes are the two lines above.)*

### Generate the initial migration

```bash
alembic revision --autogenerate -m "initial schema"
```

Alembic compares `Base.metadata` (what our models declare) against the empty database and writes `alembic/versions/<hash>_initial_schema.py`. **Always review the generated file** — autogenerate is a diff tool, not an oracle. Then apply:

```bash
alembic upgrade head
```

Verify the tables really exist:

```bash
python -c "from app.database.database import engine; from sqlalchemy import inspect; print(sorted(inspect(engine).get_table_names()))"
```

Expected (alphabetical): `alembic_version, app_settings, categories, customers, expenses, inventory_movements, payments, products, purchase_items, purchases, sale_items, sales, suppliers, users`.

### Why we can run migrations in production too

Because we drive everything from code (`settings.database_url` + `Base.metadata`), the *packaged* app can run `alembic upgrade head` at startup — the same logic, a different database file location (Phase 23–24).

## 3.5 Seed the first user

The app must have an Owner account on first run, or nobody can log in. Create `backend/app/database/seed.py`:

```python
from sqlalchemy import select
from sqlalchemy.orm import Session

from app.core.config import settings
from app.core.security import hash_password  # written in Phase 4
from app.models import User, UserRole


def seed_initial_data(db: Session) -> None:
    """Create the default Owner on a fresh database. Idempotent."""
    existing = db.scalar(select(User).where(User.username == settings.DEFAULT_ADMIN_USERNAME))
    if existing:
        return

    owner = User(
        username=settings.DEFAULT_ADMIN_USERNAME,
        full_name="Shop Owner",
        password_hash=hash_password(settings.DEFAULT_ADMIN_PASSWORD),
        role=UserRole.OWNER,
        is_active=True,
    )
    db.add(owner)
    db.commit()
```

> `hash_password` doesn't exist yet — it arrives in Phase 4. For now, seed the schema *without* the user (or stub `hash_password` — we'll implement it properly in Phase 4). Don't skip security by storing plaintext.

## 3.6 Where the pieces interact

```mermaid
graph LR
    A[alembic upgrade head] --> B[(retail.db)]
    C[SQLAlchemy models] -->|Base.metadata| A
    D[app_settings row] --> E[invoice headers]
    F[inventory_movements] --> G[stock & COGS]
    B --> F
```

## 3.7 Common mistakes

| Mistake | Why it bites | The fix |
|---|---|---|
| Forgetting to import a model in `models/__init__.py` | Alembic never sees it → table missing at runtime | Add every model to `__init__.py` |
| `create_all()` instead of migrations | Cannot alter existing tables later | Always migrate via Alembic |
| No `PRAGMA foreign_keys=ON` | Orphaned rows possible; "RESTRICT" does nothing | The `_set_sqlite_pragmas` listener (never skip it) |
| Floats for money | Silent rounding drift | `Decimal` + `money()` helper |
| Deleting products/sales | History (and FK RESTRICT) breaks | Soft-delete (`is_active`); schema protects with RESTRICT |
| Server-default UTC timestamps mixed with local `datetime.now` | "Today's sales" report is off by hours | Use Python-side `datetime.now` everywhere (local time), consistently |

## ✏️ Exercise 3.1 — add a `brand` field to products

Practice the full schema-change loop (you will do this constantly in real work):

1. Add `brand: Mapped[str | None] = mapped_column(String(100))` to `Product`.
2. Generate the migration: `alembic revision --autogenerate -m "add brand to products"` — **read the generated file** before applying.
3. `alembic upgrade head` and verify the column exists.
4. Verify the old DB file still has all its data (it must — that's the point of migrations).

<details>
<summary><b>Solution</b> (try it yourself first!)</summary>

Step 1 — `backend/app/models/product.py`, inside `Product`:

```python
brand: Mapped[str | None] = mapped_column(String(100))
```

Step 2 — autogenerate will produce a migration containing:

```python
def upgrade() -> None:
    op.add_column("products", sa.Column("brand", sa.String(length=100), nullable=True))


def downgrade() -> None:
    op.drop_column("products", "brand")
```

Step 3 — `alembic upgrade head` → `alembic_history` shows the new revision; `inspect(engine).get_columns("products")` contains `brand`.

Step 4 — data intact, because the migration only *added* a nullable column.

</details>

---

## ✅ Phase 3 Checkpoint

Run:

```bash
cd backend
alembic upgrade head
```

Expected:

```text
Running upgrade  -> <hash>, initial schema
```

Then:

```bash
python -c "from app.database.database import engine; from sqlalchemy import inspect; print(sorted(inspect(engine).get_table_names()))"
```

### What I should verify

- [ ] `retail.db` exists in `backend/data/database/`
- [ ] All 14 tables created (13 listed above + `alembic_version`)
- [ ] `alembic upgrade head` is idempotent (running it again says "no upgrade in progress")
- [ ] Re-running `alembic revision --autogenerate` produces an *empty* migration (schema matches models)
- [ ] The exercise's `brand` column exists (if you did it)

### If it doesn't work

| Error | Why | Fix |
|---|---|---|
| `sqlalchemy.exc.OperationalError: no such table` | Migration never ran | `alembic upgrade head`; check `alembic_version` table |
| Autogenerate produces no tables | Models not imported in `models/__init__.py`, or env.py missing `target_metadata` | Fix both (Section 3.3/3.4) |
| `ModuleNotFoundError: app` | Command run outside `backend/` or venv not active | `cd backend`, activate venv |
| `ValueError: sqlite:///... relative path` | `DATA_DIR` path resolution | Set `LRM_DATA_DIR` to an absolute path in `.env` |

Commit:

```bash
cd ..
git add -A
git commit -m "feat: add database layer with models and initial migration"
```

---

**Next:** [Phase 4 — Backend Fundamentals](#phase-4--backend-fundamentals)
# Phase 4 — Backend Fundamentals

> **Goal of this phase:** learn FastAPI properly — app factory, routers, dependency injection, Pydantic schemas, validation, response models, status codes, error handling, and the service layer — through a small example first, then apply the pattern to our project skeleton.

## 4.1 The concepts, in order

### HTTP methods and status codes (the API's verbs and moods)

| Method | Meaning | Status on success | Typical statuses on failure |
|---|---|---|---|
| `POST` | Create a new resource | **201** Created | 400 invalid input, 409 conflict (duplicate) |
| `GET` | Read (list or single) | **200** OK | 404 not found |
| `PUT` / `PATCH` | Update | **200** OK | 404, 409 |
| `DELETE` | Delete / deactivate | **200** or **204** No Content | 404, 409 (protected by FK) |

Rules we follow: **create → 201**, **delete → 204**, never 200-for-everything, and errors must be *meaningful* (400 vs 404 vs 409 vs 403 are different problems and the frontend needs to tell them apart).

### Routers

A **router** is a group of related endpoints ("all product endpoints"). FastAPI apps can be many routers mounted on one app. This is how `main.py` stays a 20-line file while the API grows to 40+ endpoints.

### Dependency injection (DI)

A **dependency** is any callable FastAPI resolves for you. When a route declares `db: Session = Depends(get_db)`, FastAPI calls `get_db()`, passes the result to the route, and calls the cleanup (our `finally: db.close()`). Benefits: shared logic (DB session, current user, role checks) is written once, and tests can swap dependencies easily. This is the mechanism behind our per-request session.

### Pydantic schemas — input vs output

Two kinds of schemas per resource:

- **Input schemas** (`ProductCreate`): validate what the client sends. Strict: unknown fields rejected, types enforced, constraints checked (price ≥ 0).
- **Output schemas** (`ProductRead`): shape what the client receives. They can be built from ORM objects (`from_attributes=True`).

FastAPI uses input schemas to parse/validate the request body and `response_model=` to filter/serialize the response. **What the client can send and what it sees are different contracts** — that's why models and schemas are separate (Phase 2).

### The service layer and "repository" idea

- **Service** = business rules + orchestration (our main pattern).
- **Repository** (mentioned in your requirements) = the data-access wrapper. SQLAlchemy's `Session` already *is* a capable data-access layer, so we don't build a separate repository class — the service talks to the session directly. If we ever swapped SQLAlchemy for another DB library, the *service* layer is the contract that wouldn't change. We mention this because real codebases sometimes add a repository layer on top; for our size it's ceremony without benefit.

### Error handling strategy

All business errors are raised as typed exceptions (`NotFoundError`, `InsufficientStockError`, …) in the **service layer**, and one global handler converts them to clean JSON. Routes never scatter `try/except` — they stay thin.

## 4.2 Mini-project: a tiny in-memory example

Before touching the database, let's feel the pattern with zero moving parts. Create `backend/app/api/routes/demo.py`:

```python
from fastapi import APIRouter, Depends, HTTPException, status
from pydantic import BaseModel, Field

router = APIRouter(prefix="/api/demo", tags=["demo"])


# --- schema (input/output) ---
class ItemIn(BaseModel):
    name: str = Field(min_length=1, max_length=50)


class ItemOut(BaseModel):
    id: int
    name: str


# --- service (the "business layer" — here, a list) ---
_items: list[dict] = []
_next_id = 1


def create_item(name: str) -> dict:
    global _next_id
    item = {"id": _next_id, "name": name}
    _items.append(item)
    _next_id += 1
    return item


def get_item(item_id: int) -> dict:
    for item in _items:
        if item["id"] == item_id:
            return item
    raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail="Item not found")


# --- routes (thin: parse → call service → return) ---
@router.post("", response_model=ItemOut, status_code=status.HTTP_201_CREATED)
def create(body: ItemIn) -> dict:
    return create_item(body.name)


@router.get("/{item_id}", response_model=ItemOut)
def read(item_id: int) -> dict:
    return get_item(item_id)
```

Run it (from `backend/`): create `backend/app/api/__init__.py` already exists; temporarily add `demo.router` to `main.py` (we build the real `main.py` next), then:

```bash
uvicorn app.main:app --reload
```

Try it in the interactive docs at **http://127.0.0.1:8000/docs**, or with curl:

```bash
curl -X POST http://127.0.0.1:8000/api/demo -H "Content-Type: application/json" -d '{"name": "hello"}'
curl http://127.0.0.1:8000/api/demo/1
curl -X POST .../api/demo -d '{"name": ""}'     # → 422, because min_length=1
curl .../api/demo/99                           # → 404
```

Notice: the **route** does nothing but delegate; the **service** owns the logic; validation is declared, not coded. That's the whole architecture, in miniature. We delete this demo file in the next step — it served its purpose.

> ✏️ **Your turn:** add a `PUT /api/demo/{id}` (update name) and a `DELETE` (remove item). Run them in `/docs`. You just implemented your first CRUD API.

## 4.3 Security primitives (needed by the seeder)

`backend/app/core/security.py` — password hashing and token creation. Full auth flow is Phase 18; we need `hash_password` now so the seed can create the Owner:

```python
"""Password hashing (bcrypt) and signed tokens (JWT). Full auth in Phase 18."""
from datetime import datetime, timedelta, timezone

import bcrypt
import jwt

from app.core.config import settings

ALGORITHM = "HS256"


def hash_password(password: str) -> str:
    """bcrypt hash. bcrypt 5.x rejects passwords longer than 72 bytes —
    we also cap password length in the login schema (64 chars)."""
    return bcrypt.hashpw(password.encode("utf-8"), bcrypt.gensalt()).decode("utf-8")


def verify_password(plain: str, hashed: str) -> bool:
    try:
        return bcrypt.checkpw(plain.encode("utf-8"), hashed.encode("utf-8"))
    except ValueError:
        return False  # malformed hash → treat as wrong password


def create_access_token(subject: str, role: str) -> str:
    """A signed JWT carrying the username and role, expiring after 8h."""
    now = datetime.now(timezone.utc)
    payload = {
        "sub": subject,
        "role": role,
        "iat": now,
        "exp": now + timedelta(minutes=settings.TOKEN_EXPIRE_MINUTES),
    }
    return jwt.encode(payload, settings.SECRET_KEY, algorithm=ALGORITHM)


def decode_access_token(token: str) -> dict:
    """Decode + verify signature + expiry. Raises jwt.PyJWTError if invalid."""
    return jwt.decode(token, settings.SECRET_KEY, algorithms=[ALGORITHM])
```

- Passwords are **never stored or logged**; only the bcrypt hash (a one-way function with a random salt).
- The JWT is signed with `SECRET_KEY` (from env). It says *who* the user is and *what role* they hold — enough for the API to authorize every request.
- Why JWT and not opaque sessions? ADR-08: no server-side session store, easy to test, fine for localhost. `exp` expiry is checked by `jwt.decode` automatically.

## 4.4 Typed exceptions — `backend/app/core/exceptions.py`

```python
from fastapi import status


class AppError(Exception):
    """Base class for all business errors. Routes never see these — a global
    handler converts them to JSON. 'code' is a stable machine-readable string
    the frontend can switch on; 'message' is human-readable."""

    status_code: int = status.HTTP_400_BAD_REQUEST
    code: str = "app_error"

    def __init__(self, message: str):
        self.message = message
        super().__init__(message)


class NotFoundError(AppError):
    status_code = status.HTTP_404_NOT_FOUND
    code = "not_found"


class ConflictError(AppError):
    status_code = status.HTTP_409_CONFLICT
    code = "conflict"


class ValidationFailedError(AppError):
    status_code = status.HTTP_400_BAD_REQUEST
    code = "validation_failed"


class AuthenticationError(AppError):
    status_code = status.HTTP_401_UNAUTHORIZED
    code = "authentication_failed"


class PermissionDeniedError(AppError):
    status_code = status.HTTP_403_FORBIDDEN
    code = "permission_denied"


class InsufficientStockError(AppError):
    status_code = status.HTTP_409_CONFLICT
    code = "insufficient_stock"
```

The handler lives in `main.py` (4.6): any `AppError` → `{"detail": {"code": ..., "message": ...}}` with the right status. Services `raise NotFoundError("Product not found")` and never think about HTTP.

## 4.5 The app factory — `backend/app/main.py`

A **factory** (`create_app()`) builds the FastAPI app in a function instead of at module import. Tests call it with different settings; nothing global is created until asked.

```python
import logging
from contextlib import asynccontextmanager

from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import JSONResponse

from app.api.routes import categories, health, products
from app.core.config import settings
from app.core.exceptions import AppError
from app.database.database import SessionLocal
from app.database.seed import seed_initial_data

logger = logging.getLogger(__name__)


def run_migrations() -> None:
    """Apply any pending Alembic migrations. Called on startup so the
    packaged app upgrades its own database (Phase 24)."""
    from alembic import command
    from alembic.config import Config as AlembicConfig

    import os
    from pathlib import Path

    backend_dir = Path(__file__).resolve().parents[2]  # backend/
    cfg = AlembicConfig(str(backend_dir / "alembic.ini"))
    cfg.set_main_option("script_location", str(backend_dir / "alembic"))
    os.environ["LRM_DATA_DIR"] = str(settings.DATA_DIR)
    command.upgrade(cfg, "head")


@asynccontextmanager
async def lifespan(app: FastAPI):
    """Runs once when the app starts, and once on shutdown."""
    settings.ensure_dirs()
    if settings.ENV != "test":
        run_migrations()
    db = SessionLocal()
    try:
        seed_initial_data(db)
    finally:
        db.close()
    logger.info("%s started (env=%s, db=%s)", settings.APP_NAME, settings.ENV, settings.database_url)
    yield
    logger.info("Shutting down %s", settings.APP_NAME)


def create_app() -> FastAPI:
    app = FastAPI(title=settings.APP_NAME, lifespan=lifespan)

    # CORS: the Vite dev server (localhost:5173) and the Tauri WebView origin
    app.add_middleware(
        CORSMiddleware,
        allow_origins=settings.CORS_ORIGINS,
        allow_credentials=True,
        allow_methods=["*"],
        allow_headers=["*"],
    )

    # Business errors → clean JSON
    @app.exception_handler(AppError)
    async def app_error_handler(request, exc: AppError):
        return JSONResponse(
            status_code=exc.status_code,
            content={"detail": {"code": exc.code, "message": exc.message}},
        )

    app.include_router(health.router)
    app.include_router(products.router)
    app.include_router(categories.router)

    return app


app = create_app()
```

Explain the pieces:

- `lifespan` — the modern way to run startup/shutdown code (replaces the old `@app.on_event`). It's an async context manager: code before `yield` runs at startup, after `yield` at shutdown.
- `run_migrations()` — drives Alembic *programmatically* (no CLI) using the same `alembic.ini`/`env.py`. `Path(__file__).resolve().parents[2]` = `backend/`. This is what lets the installed app migrate its own database. (It sets `LRM_DATA_DIR` so the migration's `settings.database_url` points at the right place.)
- `seed_initial_data(db)` — creates the Owner on first run (Phase 3.5).
- The `AppError` handler — one place converts all business errors to `{"detail": {"code", "message"}}`.
- `app = create_app()` at the bottom — `uvicorn app.main:app` needs a module-level `app` object.

> Note: `products`/`categories` routers are imported but don't exist yet — we create them in Phase 5, right now.

## 4.6 Shared schemas and the pagination helper

`backend/app/schemas/common.py`:

```python
from datetime import datetime

from pydantic import BaseModel, ConfigDict


class ORMModel(BaseModel):
    """Base for all READ schemas: allows building from ORM objects."""

    model_config = ConfigDict(from_attributes=True)


class Timestamped(ORMModel):
    created_at: datetime
    updated_at: datetime


class Paginated(BaseModel):
    items: list
    total: int
    page: int
    size: int
```

`backend/app/utils/pagination.py` — one helper used by every list endpoint:

```python
from math import ceil

from sqlalchemy import func, select
from sqlalchemy.orm import Session


def paginate(db: Session, stmt, page: int = 1, size: int = 20) -> tuple[list, int]:
    """Run a SELECT with LIMIT/OFFSET and return (rows, total_count)."""
    total = db.scalar(select(func.count()).select_from(stmt.order_by(None).subquery())) or 0
    rows = db.scalars(stmt.offset((page - 1) * size).limit(size)).all()
    return rows, total


def total_pages(total: int, size: int) -> int:
    return max(1, ceil(total / size))
```

---

## ✅ Phase 4 Checkpoint

- [ ] `uvicorn app.main:app --reload` starts, lifespan logs "started", and **no import errors** (temporarily comment out the `products`/`categories` imports if they bother you — they arrive next phase)
- [ ] `/docs` renders and shows `/api/health` and `/api/demo` endpoints
- [ ] Demo endpoints: POST returns 201, invalid body returns 422, missing id returns 404
- [ ] `curl` a 404 and confirm the JSON error shape

### If it doesn't work

| Error | Why | Fix |
|---|---|---|
| `ImportError: cannot import name 'hash_password'` | `core/security.py` missing | Create it (4.3) |
| CORS error in browser | Origin not in `CORS_ORIGINS` | Add `http://localhost:5173` to settings / `.env` |
| "Please run `alembic upgrade head`" style errors at startup | Migrations not applied | `cd backend && alembic upgrade head` (or let lifespan do it) |

Delete the demo router, then commit:

```bash
rm backend/app/api/routes/demo.py
git add -A
git commit -m "feat: add FastAPI app factory, security, errors, and lifespan"
```

---

# Phase 5 — Product Management

> **Goal of this phase:** the first real feature — full CRUD for products and categories, with search, soft delete, validation, and clean errors. This phase installs the *pattern* every later resource copies (customers, suppliers, expenses, purchases…).

## 5.1 Problem and concept

**Problem:** the shop needs to define what it sells — name, prices, tax, category, minimum stock — and find products fast during billing.

**Concept:** a standard **CRUD** resource with a few retail-specific rules:
- `sku` and `barcode` are **unique** — the database refuses duplicates (409 Conflict).
- Products are **deactivated, not deleted** (`is_active=False`) — past sales keep their references (FK `RESTRICT` would block deletion anyway).
- Prices are non-negative; `tax_rate` between 0 and 100.
- **Search** matches name, SKU, or barcode (the billing screen needs this).

The request lifecycle you asked to see — this is it, end to end:

```text
Frontend (Phase 9)                 API                 Service                SQLAlchemy          SQLite
POST /api/products {name,...}  →  validate (Pydantic) → business rules      → INSERT products   → row stored
                                    201 + ProductRead  ← commit + serialize  ← Product object   ←
```

## 5.2 Files we create

| File | Why it exists |
|---|---|
| `app/schemas/product.py`, `app/schemas/category.py` | Input/output validation contracts |
| `app/services/product_service.py` | All product business rules |
| `app/services/category_service.py` | Category rules (simple CRUD) |
| `app/api/routes/products.py`, `app/api/routes/categories.py`, `app/api/routes/health.py` | Thin HTTP layer |

## 5.3 Schemas

`backend/app/schemas/category.py`:

```python
from pydantic import Field

from .common import ORMModel, Timestamped


class CategoryCreate(ORMModel):
    name: str = Field(min_length=1, max_length=100)
    description: str | None = Field(default=None, max_length=255)


class CategoryUpdate(ORMModel):
    name: str | None = Field(default=None, min_length=1, max_length=100)
    description: str | None = Field(default=None, max_length=255)


class CategoryRead(Timestamped):
    id: int
    name: str
    description: str | None
```

`backend/app/schemas/product.py`:

```python
from decimal import Decimal

from pydantic import Field

from .common import ORMModel, Paginated, Timestamped


class ProductCreate(ORMModel):
    name: str = Field(min_length=1, max_length=200)
    sku: str | None = Field(default=None, max_length=50)
    barcode: str | None = Field(default=None, max_length=100)
    category_id: int | None = None
    purchase_price: Decimal = Field(default=0, ge=0, max_digits=12, decimal_places=2)
    selling_price: Decimal = Field(default=0, ge=0, max_digits=12, decimal_places=2)
    tax_rate: Decimal = Field(default=0, ge=0, le=100, max_digits=5, decimal_places=2)
    min_stock: Decimal = Field(default=0, ge=0, max_digits=12, decimal_places=2)


class ProductUpdate(ORMModel):
    name: str | None = Field(default=None, min_length=1, max_length=200)
    sku: str | None = Field(default=None, max_length=50)
    barcode: str | None = Field(default=None, max_length=100)
    category_id: int | None = None
    purchase_price: Decimal | None = Field(default=None, ge=0, max_digits=12, decimal_places=2)
    selling_price: Decimal | None = Field(default=None, ge=0, max_digits=12, decimal_places=2)
    tax_rate: Decimal | None = Field(default=None, ge=0, le=100, max_digits=5, decimal_places=2)
    min_stock: Decimal | None = Field(default=None, ge=0, max_digits=12, decimal_places=2)
    is_active: bool | None = None


class ProductRead(Timestamped):
    id: int
    name: str
    sku: str | None
    barcode: str | None
    category_id: int | None
    category_name: str | None = None
    purchase_price: float
    selling_price: float
    tax_rate: float
    min_stock: float
    current_stock: float
    avg_cost: float
    is_active: bool


class ProductPage(Paginated):
    items: list[ProductRead]
```

Explain:

- `Field(ge=0, ...)` — validation declared, not coded. Pydantic enforces `selling_price >= 0`, `tax_rate` in 0–100, string lengths.
- `ProductRead.category_name` — a *convenience* field: the frontend shouldn't need a second request per row to know the category name. The service fills it (5.4).
- `current_stock`/`avg_cost` exposed as `float` (ADR-10) — the frontend displays stock from here.
- `ProductPage` — the generic `Paginated` with a concrete `items` type (this is why `Paginated` exists).

## 5.4 Service — `backend/app/services/product_service.py`

```python
from decimal import Decimal

from sqlalchemy import or_, select
from sqlalchemy.orm import Session

from app.core.exceptions import ConflictError, NotFoundError
from app.models import Category, Product
from app.schemas.product import ProductCreate, ProductUpdate
from app.utils.money import money, percent
from app.utils.pagination import paginate


def _get_or_404(db: Session, product_id: int) -> Product:
    product = db.get(Product, product_id)
    if product is None:
        raise NotFoundError("Product not found")
    return product


def _check_unique_fields(db: Session, product: Product | None, sku: str | None, barcode: str | None) -> None:
    """Reject duplicate SKU/barcode with a clear 409. 'product' is the row being
    edited (excluded from the check) or None when creating."""
    if sku:
        dup = db.scalar(select(Product).where(Product.sku == sku, Product.id != (product.id if product else -1)))
        if dup:
            raise ConflictError(f"SKU '{sku}' is already in use")
    if barcode:
        dup = db.scalar(select(Product).where(Product.barcode == barcode, Product.id != (product.id if product else -1)))
        if dup:
            raise ConflictError(f"Barcode '{barcode}' is already in use")


def create_product(db: Session, data: ProductCreate) -> Product:
    _check_unique_fields(db, None, data.sku, data.barcode)
    if data.category_id:
        db.get(Category, data.category_id) or (None or (_raise_no_category()))
    product = Product(
        name=data.name.strip(),
        sku=data.sku.strip() if data.sku else None,
        barcode=data.barcode.strip() if data.barcode else None,
        category_id=data.category_id,
        purchase_price=money(data.purchase_price),
        selling_price=money(data.selling_price),
        tax_rate=percent(data.tax_rate),
        min_stock=money(data.min_stock),
    )
    db.add(product)
    db.commit()
    db.refresh(product)
    return product


def _raise_no_category() -> None:
    raise NotFoundError("Category not found")


def list_products(
    db: Session,
    search: str | None = None,
    category_id: int | None = None,
    include_inactive: bool = False,
    page: int = 1,
    size: int = 20,
) -> tuple[list[Product], int]:
    stmt = select(Product)
    if search:
        like = f"%{search.strip()}%"
        stmt = stmt.where(
            or_(Product.name.ilike(like), Product.sku.ilike(like), Product.barcode.ilike(like))
        )
    if category_id:
        stmt = stmt.where(Product.category_id == category_id)
    if not include_inactive:
        stmt = stmt.where(Product.is_active.is_(True))
    stmt = stmt.order_by(Product.name)
    return paginate(db, stmt, page, size)


def get_product(db: Session, product_id: int) -> Product:
    return _get_or_404(db, product_id)


def update_product(db: Session, product_id: int, data: ProductUpdate) -> Product:
    product = _get_or_404(db, product_id)
    updates = data.model_dump(exclude_unset=True)
    _check_unique_fields(db, product, updates.get("sku"), updates.get("barcode"))
    for field, value in updates.items():
        if field in ("purchase_price", "selling_price", "min_stock") and value is not None:
            value = money(value)
        elif field == "tax_rate" and value is not None:
            value = percent(value)
        setattr(product, field, value)
    db.commit()
    db.refresh(product)
    return product


def deactivate_product(db: Session, product_id: int) -> None:
    product = _get_or_404(db, product_id)
    product.is_active = False
    db.commit()
```

Explain the tricky parts:

- `_check_unique_fields` — a *service-level* check for friendly 409s, **backed by the DB's UNIQUE constraint** as the final authority (belt and suspenders; see Phase 20 for the IntegrityError catch).
- `money(data.purchase_price)` — every money value is normalized through the Decimal helper (ADR-10) before touching the database.
- `data.model_dump(exclude_unset=True)` — only the fields the client actually sent become updates; a missing field is *not* overwritten with `None`. This is the standard PATCH semantics.
- `ilike` — case-insensitive search; `%...%` matches anywhere in the string (billing needs "tat" → "Tata Salt").
- Returned products are raw ORM objects; the route serializes them (5.5). `category_name` gets filled there.

`backend/app/services/category_service.py` — the same pattern, smaller:

```python
from sqlalchemy import select
from sqlalchemy.orm import Session

from app.core.exceptions import ConflictError, NotFoundError
from app.models import Category
from app.schemas.category import CategoryCreate, CategoryUpdate


def list_categories(db: Session) -> list[Category]:
    return list(db.scalars(select(Category).order_by(Category.name)))


def create_category(db: Session, data: CategoryCreate) -> Category:
    if db.scalar(select(Category).where(Category.name == data.name.strip())):
        raise ConflictError(f"Category '{data.name}' already exists")
    category = Category(name=data.name.strip(), description=data.description)
    db.add(category)
    db.commit()
    db.refresh(category)
    return category


def update_category(db: Session, category_id: int, data: CategoryUpdate) -> Category:
    category = db.get(Category, category_id)
    if category is None:
        raise NotFoundError("Category not found")
    if data.name and data.name.strip() != category.name:
        if db.scalar(select(Category).where(Category.name == data.name.strip())):
            raise ConflictError(f"Category '{data.name}' already exists")
        category.name = data.name.strip()
    if data.description is not None:
        category.description = data.description
    db.commit()
    db.refresh(category)
    return category
```

## 5.5 Routes — thin by law

`backend/app/api/routes/health.py`:

```python
from fastapi import APIRouter

router = APIRouter(prefix="/api/health", tags=["health"])


@router.get("")
def health() -> dict:
    return {"status": "ok", "app": "Local Retail Manager"}
```

`backend/app/api/routes/products.py`:

```python
from fastapi import APIRouter, Depends, Query, status
from sqlalchemy.orm import Session

from app.database.database import get_db
from app.schemas.product import ProductCreate, ProductPage, ProductRead, ProductUpdate
from app.services import product_service

router = APIRouter(prefix="/api/products", tags=["products"])


def _to_read(product) -> ProductRead:
    """ORM → schema, filling the convenience category_name field."""
    return ProductRead(
        **product.__dict__,
        category_name=product.category.name if product.category else None,
    )


@router.post("", response_model=ProductRead, status_code=status.HTTP_201_CREATED)
def create_product(body: ProductCreate, db: Session = Depends(get_db)) -> ProductRead:
    return _to_read(product_service.create_product(db, body))


@router.get("", response_model=ProductPage)
def list_products(
    db: Session = Depends(get_db),
    search: str | None = Query(default=None),
    category_id: int | None = Query(default=None),
    include_inactive: bool = Query(default=False),
    page: int = Query(default=1, ge=1),
    size: int = Query(default=20, ge=1, le=100),
) -> dict:
    items, total = product_service.list_products(db, search, category_id, include_inactive, page, size)
    return {"items": [_to_read(p) for p in items], "total": total, "page": page, "size": size}


@router.get("/{product_id}", response_model=ProductRead)
def get_product(product_id: int, db: Session = Depends(get_db)) -> ProductRead:
    return _to_read(product_service.get_product(db, product_id))


@router.patch("/{product_id}", response_model=ProductRead)
def update_product(product_id: int, body: ProductUpdate, db: Session = Depends(get_db)) -> ProductRead:
    return _to_read(product_service.update_product(db, product_id, body))


@router.delete("/{product_id}", status_code=status.HTTP_204_NO_CONTENT)
def deactivate_product(product_id: int, db: Session = Depends(get_db)) -> None:
    product_service.deactivate_product(db, product_id)
```

`backend/app/api/routes/categories.py` — same shape with `CategoryCreate/CategoryRead/CategoryUpdate`, `GET ""`, `POST ""`, `PATCH "/{id}"`, `DELETE "/{id}"` (deletion refused with 409 if products reference the category — handled by a service check, and by the FK `SET NULL` choice you can also decide to null instead).

> Note how every route is 1–4 lines: **parse (Pydantic) → call service → serialize (response_model)**. If you find yourself writing business logic in a route file, you've broken the rule — move it to the service.

## 5.6 Run it and verify

```bash
uvicorn app.main:app --reload
```

Open `/docs` → the `products` and `categories` sections appear with schemas. Try:

```bash
curl -X POST http://127.0.0.1:8000/api/categories -H "Content-Type: application/json" -d '{"name": "Groceries"}'
curl -X POST http://127.0.0.1:8000/api/products -H "Content-Type: application/json" -d '{"name": "Tata Salt", "sku": "TATA-001", "barcode": "8901002101101", "category_id": 1, "purchase_price": 22, "selling_price": 28, "tax_rate": 0, "min_stock": 20}'
curl "http://127.0.0.1:8000/api/products?search=tata"
curl -X POST .../api/products -d '{"name":"Dup","barcode":"8901002101101"}'    # → 409 Conflict
```

## ✏️ Exercise 5.1 — expose `brand` through the whole stack

In Exercise 3.1 you added `brand` to the *model*. Now finish the job:

1. Add `brand: str | None = Field(default=None, max_length=100)` to `ProductCreate` and `ProductUpdate`, and `brand: str | None` to `ProductRead`.
2. In `product_service.create_product`, set `brand=data.brand.strip() if data.brand else None`; handle it in `update_product` too.
3. Restart, create a product with `"brand": "Tata"`, and confirm it round-trips in `GET /api/products/{id}`.

<details>
<summary><b>Solution</b> (after attempting!)</summary>

```python
# schemas: add to all three classes
brand: str | None = Field(default=None, max_length=100)   # (Create/Update)

# service create:
brand=data.brand.strip() if data.brand else None,

# service update: brand is already covered by the generic loop
# (model_dump(exclude_unset=True) → setattr). Nothing extra needed!
```

The update loop is generic — that's the payoff of the pattern.

</details>

## 5.7 Common mistakes

| Mistake | Why it bites | Fix |
|---|---|---|
| Checking uniqueness only in code | Two rapid requests can both pass the check before either commits | Keep the DB UNIQUE constraint; catch `IntegrityError` as the backstop (Phase 20) |
| `PUT` replacing everything | Client must send every field or loses data | Use `PATCH` + `exclude_unset=True` |
| Hard `DELETE` of products | Breaks sale history / FK RESTRICT errors | Deactivate (`is_active=False`) |
| Business logic in routes | Untestable, duplicated, bloats `main.py` | Service layer |
| Forgetting `db.refresh()` | Returned object may miss DB-generated defaults | `db.refresh(obj)` after commit when you return it |

---

## ✅ Phase 5 Checkpoint

- [ ] POST/GET/PATCH/DELETE products all work via `/docs` or curl
- [ ] Search: `?search=tata` matches "Tata Salt"; barcode search works
- [ ] Duplicate SKU/barcode → **409** with a readable message
- [ ] Invalid data (negative price, >100 tax) → **422** (Pydantic)
- [ ] Deactivated products disappear from default list but remain in DB
- [ ] Exercise 5.1 done: `brand` flows model → schema → API

### If it doesn't work

| Error | Why | Fix |
|---|---|---|
| `sqlalchemy.exc.IntegrityError` on duplicate barcode | Race between check and commit | It's your backstop — but the 409 should catch first; if you see it in the console you have a logic bug |
| 500 instead of 404 on `GET /api/products/999` | Service raised something else | Confirm `NotFoundError` imported and raised in `_get_or_404` |
| `category_name` is null | `_to_read` uses `product.category` which needs the relationship loaded | `category` relationship exists in the model; ensure you didn't remove it |

Commit:

```bash
git add -A
git commit -m "feat: add product management (CRUD, search, categories)"
```

---

**Next:** [Phase 6 — Inventory System](#phase-6--inventory-system)
# Phase 6 — Inventory System

> **Goal of this phase:** replace the naive "`product.stock -= quantity`" habit with a proper **inventory movement ledger** — the single most important design decision in this project (ADR-07).

## 6.1 Problem

`product.stock -= 3` gives you a new number, but answers none of the questions a shop owner actually asks:

- "We're 12 units short of Tata Salt. **Why?**"
- "Was that 5-unit drop a sale, damage, or a mistake?"
- "What did the stock *cost* when we sold it?" (needed for profit)
- "Who did it and when?"

Numbers without reasons are untrustworthy — and in retail, untrustworthy stock numbers cause lost sales and stolen margin.

## 6.2 Concept: the movement ledger

Every change to stock is a **new row** in `inventory_movements` — an append-only record:

```text
"Stock of Tata Salt changed by −3 because of SALE #1021, on Aug 8 10:42, by cashier Ramesh"
```

| Field | Meaning |
|---|---|
| `product_id` | which product |
| `movement_type` | PURCHASE / SALE / RETURN / ADJUSTMENT / DAMAGE |
| `quantity` | **signed** — `+` means stock came in, `−` means it went out |
| `unit_cost` | the cost of one unit **at that moment** (snapshot — prices change later, history must not) |
| `ref_type` / `ref_id` | which document caused it (e.g. `SALE` / `1021`) — the audit link |
| `note`, `created_by_id`, timestamps | who and why |

**Current stock is then a derived number:**

```text
current_stock(product) = SUM(quantity) over all movements of that product
```

Because `quantity` is signed, this single formula handles purchases (+100), sales (−3), returns (+2), and damage (−1) uniformly.

### The cache column (why we keep `products.current_stock`)

Summing the ledger on every billing lookup would be wasteful. We keep a **denormalized cache** — `products.current_stock` — maintained *inside the same transaction* as every ledger row. Under normal operation the cache cannot drift because there is exactly one code path that changes stock (`record_movement`), and it updates both together. We also provide a **reconcile** tool to re-derive the cache from the ledger for extra safety.

> ⚠️ **Important concept — don't copy this section blindly.** The ledger is the *source of truth*; `current_stock` is only a cache. Any code that writes `current_stock` directly (bypassing the ledger) violates the design. When you see a bug "stock changed but no movement row", the cause is always a bypass.

## 6.3 Mini-project: a tiny stock tracker

Before the real thing, build a 30-line version in a scratch file `backend/scratch_stock.py` (delete it after):

```python
"""Tiny stock tracker — proves the ledger idea before we build the real one."""
MOVEMENTS = []  # (product, quantity, reason)

def record(product: str, qty: int, reason: str) -> None:
    MOVEMENTS.append((product, qty, reason))  # signed qty

def current_stock(product: str) -> int:
    return sum(q for p, q, _ in MOVEMENTS if p == product)

def history(product: str) -> list:
    return [(q, r) for p, q, r in MOVEMENTS if p == product]

record("salt", 100, "PURCHASE")
record("salt", -3, "SALE #1021")
record("salt", 2, "RETURN")
print(current_stock("salt"))   # 99
print(history("salt"))         # [(100,'PURCHASE'), (-3,'SALE #1021'), (2,'RETURN')]
```

Run it: `python scratch_stock.py`. You now understand the entire Phase 6 concept — the real version just adds a database and the `current_stock` cache.

## 6.4 The service — `backend/app/services/inventory_service.py`

```python
from decimal import Decimal

from sqlalchemy import func, select
from sqlalchemy.orm import Session

from app.core.exceptions import ConflictError, InsufficientStockError, NotFoundError
from app.models import InventoryMovement, MovementType, Product
from app.utils.money import money
from app.utils.pagination import paginate


def record_movement(
    db: Session,
    *,
    product_id: int,
    movement_type: MovementType,
    quantity: Decimal,
    unit_cost: Decimal | None = None,
    ref_type: str | None = None,
    ref_id: int | None = None,
    note: str | None = None,
    user_id: int | None = None,
    allow_negative: bool = False,
) -> InventoryMovement:
    """THE only place that changes stock. Appends a ledger row AND updates
    the products.current_stock cache — in one transaction, so they can't drift."""
    product = db.get(Product, product_id)
    if product is None:
        raise NotFoundError("Product not found")

    qty = money(quantity)
    if qty == 0:
        raise ConflictError("Movement quantity cannot be zero")

    # Cost snapshot: caller's value if given (e.g. purchase unit cost),
    # otherwise the product's current average cost.
    cost = money(unit_cost) if unit_cost is not None else product.avg_cost

    new_stock = product.current_stock + qty
    if new_stock < 0 and not allow_negative:
        raise InsufficientStockError(
            f"Only {product.current_stock:g} in stock, cannot remove {abs(qty):g}"
        )

    movement = InventoryMovement(
        product_id=product_id,
        movement_type=movement_type,
        quantity=qty,
        unit_cost=cost,
        ref_type=ref_type,
        ref_id=ref_id,
        note=note,
        created_by_id=user_id,
    )
    db.add(movement)
    product.current_stock = new_stock
    return movement


def apply_purchase_cost(product: Product, quantity: Decimal, unit_cost: Decimal) -> None:
    """Weighted-average cost update. Call AFTER the purchase movement exists:
    new_avg = (old_stock*old_avg + qty*cost) / (old_stock + qty)"""
    qty = money(quantity)
    cost = money(unit_cost)
    prev_stock = product.current_stock - qty  # stock before this purchase
    if prev_stock <= 0:
        product.avg_cost = cost
    else:
        product.avg_cost = money(
            (prev_stock * product.avg_cost + qty * cost) / (prev_stock + qty)
        )


def adjust_stock(
    db: Session,
    *,
    product_id: int,
    new_stock: Decimal,
    reason: str,
    user_id: int | None = None,
) -> InventoryMovement:
    """Manual correction (physical count differs from system). Records an
    ADJUSTMENT movement with the exact delta, keeping the ledger honest."""
    product = db.get(Product, product_id)
    if product is None:
        raise NotFoundError("Product not found")
    target = money(new_stock)
    if target < 0:
        raise ConflictError("Stock cannot be negative")
    delta = target - product.current_stock
    if delta == 0:
        raise ConflictError("Stock is already at that value")
    return record_movement(
        db,
        product_id=product_id,
        movement_type=MovementType.ADJUSTMENT,
        quantity=delta,
        ref_type="ADJUSTMENT",
        note=reason or "Manual adjustment",
        user_id=user_id,
    )


def list_movements(
    db: Session,
    product_id: int | None = None,
    movement_type: MovementType | None = None,
    page: int = 1,
    size: int = 50,
) -> tuple[list[InventoryMovement], int]:
    stmt = select(InventoryMovement).order_by(InventoryMovement.created_at.desc())
    if product_id:
        stmt = stmt.where(InventoryMovement.product_id == product_id)
    if movement_type:
        stmt = stmt.where(InventoryMovement.movement_type == movement_type)
    return paginate(db, stmt, page, size)


def low_stock_products(db: Session) -> list[Product]:
    """Everything at or below its minimum stock — the restock list."""
    return list(
        db.scalars(
            select(Product)
            .where(Product.is_active.is_(True), Product.current_stock <= Product.min_stock)
            .order_by(Product.current_stock)
        )
    )


def stock_value(db: Session) -> Decimal:
    """Total value of everything on the shelves: stock × average cost."""
    return (
        db.scalar(select(func.sum(Product.current_stock * Product.avg_cost))) or Decimal("0")
    )


def reconcile_stock(db: Session) -> int:
    """Re-derive every product's current_stock from the ledger (admin tool).
    Returns how many products were corrected."""
    corrected = 0
    for product in db.scalars(select(Product)):
        total = db.scalar(
            select(func.sum(InventoryMovement.quantity)).where(
                InventoryMovement.product_id == product.id
            )
        ) or Decimal("0")
        if product.current_stock != money(total):
            product.current_stock = money(total)
            corrected += 1
    db.commit()
    return corrected
```

Explain the important lines:

- `record_movement(...)` — **the only stock-writing function in the app.** Note the `allow_negative=False` default: SALE/DAMAGE can push stock below zero? No — they can't, unless you explicitly pass `allow_negative=True` (only used by an owner-approved override, which we don't use in the MVP). This single guard enforces "no negative stock" everywhere.
- `unit_cost` snapshot — when a sale happens we pass the product's current `avg_cost`, so COGS history stays correct even if prices change next week (this is what makes Phase 14's profit calculation trustworthy).
- `apply_purchase_cost` — weighted average: buying 50 @ ₹22 when 100 @ ₹21 are on the shelf gives avg ₹21.33. We'll use this in Phase 11.
- `reconcile_stock` — the safety valve: rebuilds the cache from the ledger. Add a button for it in the Inventory UI (Phase 9+).

## 6.5 The routes — `backend/app/api/routes/inventory.py`

```python
from fastapi import APIRouter, Depends, Query, status
from sqlalchemy.orm import Session

from app.database.database import get_db
from app.models import InventoryMovement, MovementType
from app.schemas.inventory import AdjustmentIn, MovementPage, MovementRead
from app.services import inventory_service

router = APIRouter(prefix="/api/inventory", tags=["inventory"])


def _to_read(m: InventoryMovement) -> MovementRead:
    return MovementRead(
        id=m.id,
        product_id=m.product_id,
        product_name=m.product.name if m.product else None,
        movement_type=m.movement_type,
        quantity=m.quantity,
        unit_cost=m.unit_cost,
        ref_type=m.ref_type,
        ref_id=m.ref_id,
        note=m.note,
        created_at=m.created_at,
        created_by=m.created_by.full_name if m.created_by else None,
    )


@router.get("/movements", response_model=MovementPage)
def movements(
    db: Session = Depends(get_db),
    product_id: int | None = None,
    movement_type: MovementType | None = None,
    page: int = Query(1, ge=1),
    size: int = Query(50, ge=1, le=200),
) -> dict:
    items, total = inventory_service.list_movements(db, product_id, movement_type, page, size)
    return {"items": [_to_read(m) for m in items], "total": total, "page": page, "size": size}


@router.post("/adjust", status_code=status.HTTP_201_CREATED)
def adjust(body: AdjustmentIn, db: Session = Depends(get_db)) -> dict:
    m = inventory_service.adjust_stock(
        db, product_id=body.product_id, new_stock=body.new_stock,
        reason=body.reason, user_id=None,  # Phase 18 wires the current user here
    )
    return _to_read(m)


@router.post("/reconcile")
def reconcile(db: Session = Depends(get_db)) -> dict:
    return {"corrected": inventory_service.reconcile_stock(db)}


@router.get("/low-stock")
def low_stock(db: Session = Depends(get_db)) -> list[dict]:
    return [
        {"id": p.id, "name": p.name, "current_stock": p.current_stock, "min_stock": p.min_stock}
        for p in inventory_service.low_stock_products(db)
    ]


@router.get("/stock-value")
def stock_value(db: Session = Depends(get_db)) -> dict:
    return {"value": float(inventory_service.stock_value(db))}
```

`backend/app/schemas/inventory.py`:

```python
from datetime import datetime
from decimal import Decimal

from pydantic import Field

from .common import ORMModel, Paginated


class AdjustmentIn(ORMModel):
    product_id: int
    new_stock: Decimal = Field(ge=0, max_digits=12, decimal_places=2)
    reason: str = Field(min_length=1, max_length=255)


class MovementRead(ORMModel):
    id: int
    product_id: int
    product_name: str | None = None
    movement_type: str
    quantity: float
    unit_cost: float
    ref_type: str | None
    ref_id: int | None
    note: str | None
    created_at: datetime
    created_by: str | None


class MovementPage(Paginated):
    items: list[MovementRead]
```

## ✏️ Exercise 6.1 — damage & dead-stock queries

1. Add a `POST /api/inventory/damage` endpoint: `{product_id, quantity, note}` records a DAMAGE movement with a negative quantity. (Hint: `record_movement` with `MovementType.DAMAGE, quantity=-qty`.)
2. Add `dead_stock(db, days=60)` to the service: products with **zero SALE movements in the last `days` days** but positive stock. Use a `select` with `~Product.inventory_movements.any(...)`.

<details>
<summary><b>Solution</b> (after attempting!)</summary>

```python
# route
@router.post("/damage", status_code=status.HTTP_201_CREATED)
def damage(body: DamageIn, db: Session = Depends(get_db)) -> dict:
    m = inventory_service.record_movement(
        db, product_id=body.product_id, movement_type=MovementType.DAMAGE,
        quantity=-money(body.quantity), ref_type="DAMAGE", note=body.note,
    )
    db.commit()
    return {"id": m.id, "quantity": m.quantity, "note": m.note}


# service
from datetime import datetime, timedelta
from sqlalchemy import select

def dead_stock(db: Session, days: int = 60) -> list[Product]:
    cutoff = datetime.now() - timedelta(days=days)
    has_recent_sale = (
        select(InventoryMovement.product_id)
        .where(
            InventoryMovement.movement_type == MovementType.SALE,
            InventoryMovement.created_at >= cutoff,
        )
    )
    return list(
        db.scalars(
            select(Product)
            .where(Product.is_active.is_(True), Product.current_stock > 0)
            .where(~Product.id.in_(has_recent_sale))
        )
    )
```

</details>

## 6.6 Real-world scenario — the full stock story

Vendor adds **Tata Salt**: purchase price ₹22, selling price ₹28, opening stock 100.

**What happens in the database** (the movement ledger):

| # | Type | Qty | Unit cost | Ref | Result |
|---|---|---|---|---|---|
| 1 | PURCHASE | +100 | 22.00 | PUR-20260808-0001 | current_stock 0→100, avg_cost 0→22.00 |
| 2 | SALE | −3 | 22.00 | INV-20260808-0001 | current_stock 100→97 |
| 3 | SALE | −5 | 22.00 | INV-20260808-0002 | current_stock 97→92 |

- **Current stock** = `SUM(quantity)` = 100 − 3 − 5 = **92** (and the cache says 92).
- **COGS so far** = (3 + 5) × 22.00 = **₹176** — from the movement `unit_cost` snapshots.
- **Why did stock drop by 8?** Because two invoices, which you can open and see.
- Every row has a type, a reference, a timestamp, and a user — the **audit trail** is complete.

---

## ✅ Phase 6 Checkpoint

- [ ] Mini stock tracker ran and printed `99` / history (then delete `scratch_stock.py`)
- [ ] Create a product, `POST /api/inventory/adjust` to set stock to 100 (this writes an ADJUSTMENT row), then verify:
  - `GET /api/inventory/movements` shows the adjustment
  - `GET /api/products/{id}` shows `current_stock: 100`
- [ ] `POST /api/inventory/adjust` to set stock to **−5** → 409 "Stock cannot be negative"
- [ ] `GET /api/inventory/low-stock` lists products with `current_stock <= min_stock`
- [ ] Exercise 6.1 done: damage endpoint + `dead_stock` query

### If it doesn't work

| Error | Why | Fix |
|---|---|---|
| Stock changes but no movement row | Some code wrote `product.current_stock` directly | Only `record_movement` may write it — audit your service code |
| `InsufficientStockError` on a purchase | You passed a *negative* quantity to `record_movement` | Purchases are *positive*; sales are *negative* |
| Reconcile changes stocks unexpectedly | The cache had drifted (a bypass happened earlier) | Find and fix the bypass; reconcile is the band-aid, not the cure |

Commit:

```bash
git add -A
git commit -m "feat: add inventory ledger, adjustments, low-stock, valuation"
```

---

# Phase 7 — Billing System

> **Goal of this phase:** the heart of the app — a sale that is *atomic*. Either every part happens (sale, items, payment, stock movements) or **none** of it does.

## 7.1 Problem

A sale touches five tables. If any step fails halfway — the app crashes, the power dies, the payment gateway (never — we're offline) errors — you must **not** end up with:

```text
Sale recorded        Inventory reduced
BUT                  BUT
Inventory NOT reduced   Sale NOT recorded
```

Both states are data corruption for a shopkeeper. The customer paid; the stock is wrong. Or stock vanished with no sale.

## 7.2 Concept: the database transaction (review from 3.1)

Wrap all five writes in **one transaction**:

```text
BEGIN
  1. Create Sale
  2. Create Sale Items
  3. Create Payment
  4. Create Inventory Movements
COMMIT        ← all five become visible together
```

If anything raises, we `ROLLBACK` and the database is exactly as before — as if the sale never started. SQLite (with WAL + `busy_timeout` from Phase 3) gives us this guarantee; our job is to structure the service so one exception aborts everything.

> ⚠️ **Important concept.** In SQLAlchemy, "commit" is *your* explicit act. Until `db.commit()`, nothing is durable. If the service raises before committing, the session's transaction is simply discarded (we also use `db.rollback()` in the route layer on failure for hygiene). Never call `db.commit()` halfway through a multi-step operation.

## 7.3 The business rules (documented, in order)

When a sale is completed, in exactly this order:

```text
1.  Validate at least one item.
2.  Validate products exist and are active.
3.  Validate quantities > 0 and sufficient stock.
4.  Resolve unit prices (client override or product.selling_price).
5.  Resolve tax rates (client override or product.tax_rate).
6.  Calculate subtotal            = Σ quantity × unit_price
7.  Calculate discount            = subtotal × discount_pct / 100
8.  Calculate tax                 = Σ line_value_after_discount × tax_rate / 100
9.  Calculate total               = subtotal − discount + tax
10. Generate invoice number       (unique, retried on collision)
11. Create Sale + Sale Items + Payment(s)
12. Create SALE inventory movements (−qty, cost snapshot)
13. COMMIT
14. Generate the PDF invoice      (after commit; failure logged, not fatal)
```

Steps 1–9 are **pure math** — testable without a database (Phase 21). Steps 10–13 are the transaction. Step 14 is a side effect that must never roll back a paid sale (a missing PDF is re-generatable; a missing sale is not).

## 7.4 Schemas — `backend/app/schemas/sale.py`

```python
from datetime import datetime
from decimal import Decimal

from pydantic import Field

from .common import ORMModel, Paginated
from ..models.enums import PaymentMethod


class SaleItemIn(ORMModel):
    product_id: int
    quantity: Decimal = Field(gt=0, max_digits=12, decimal_places=2)
    unit_price: Decimal | None = Field(default=None, ge=0, max_digits=12, decimal_places=2)
    tax_rate: Decimal | None = Field(default=None, ge=0, le=100, max_digits=5, decimal_places=2)


class PaymentIn(ORMModel):
    method: PaymentMethod = PaymentMethod.CASH
    amount: Decimal | None = Field(default=None, ge=0, max_digits=12, decimal_places=2)
    reference: str | None = Field(default=None, max_length=100)


class SaleCreate(ORMModel):
    customer_id: int | None = None
    discount_pct: Decimal = Field(default=0, ge=0, lt=100, max_digits=5, decimal_places=2)
    notes: str | None = Field(default=None, max_length=255)
    items: list[SaleItemIn] = Field(min_length=1)
    payments: list[PaymentIn] | None = None  # default: one full CASH payment


class SaleItemRead(ORMModel):
    id: int
    product_id: int
    product_name: str | None = None
    quantity: float
    unit_price: float
    tax_rate: float
    line_total: float
    returned_qty: float


class PaymentRead(ORMModel):
    id: int
    amount: float
    method: str
    reference: str | None
    paid_at: datetime


class SaleRead(ORMModel):
    id: int
    invoice_no: str
    customer_id: int | None
    customer_name: str | None = None
    subtotal: float
    discount_pct: float
    discount: float
    tax: float
    total: float
    status: str
    sale_date: datetime
    notes: str | None
    created_by: str | None
    items: list[SaleItemRead] = []
    payments: list[PaymentRead] = []


class SalePage(Paginated):
    items: list[SaleRead]


class ReturnItemIn(ORMModel):
    product_id: int
    quantity: Decimal = Field(gt=0, max_digits=12, decimal_places=2)


class SaleReturnIn(ORMModel):
    items: list[ReturnItemIn] = Field(min_length=1)
```

## 7.5 Invoice numbering — `backend/app/utils/doc_number.py`

Invoice numbers are **daily sequences**: `INV-20260808-0001`, `INV-20260808-0002`, … Reset each day, unique forever (the DB UNIQUE constraint is the backstop):

```python
from datetime import datetime

from sqlalchemy import func, select
from sqlalchemy.orm import Session


def next_document_no(db: Session, model, column, prefix: str, when: datetime | None = None) -> str:
    """Return the next daily-sequence number like INV-20260808-0001."""
    when = when or datetime.now()
    day_prefix = f"{prefix}-{when.strftime('%Y%m%d')}-"
    last = db.scalar(select(func.max(column)).where(column.like(f"{day_prefix}%")))
    seq = int(str(last).rsplit("-", 1)[-1]) + 1 if last else 1
    return f"{day_prefix}{seq:04d}"
```

## 7.6 The sale service — `backend/app/services/sale_service.py`

This is the most important file in the backend. Read it slowly.

```python
import logging
from decimal import Decimal

from sqlalchemy import select
from sqlalchemy.orm import Session

from app.core.exceptions import (ConflictError, InsufficientStockError,
                                 NotFoundError, ValidationFailedError)
from app.models import (MovementType, Payment, PaymentMethod, Product, Sale,
                        SaleItem, SaleStatus)
from app.schemas.sale import PaymentIn, SaleCreate, SaleReturnIn
from app.services import inventory_service
from app.utils.doc_number import next_document_no
from app.utils.money import money, percent
from app.utils.pagination import paginate

logger = logging.getLogger(__name__)


def _new_invoice_no(db: Session) -> str:
    return next_document_no(db, Sale, Sale.invoice_no, "INV")


def _calculate(
    lines: list[dict], discount_pct: Decimal
) -> dict:
    """Pure pricing math (steps 6–9). Lines already have resolved
    unit_price and tax_rate; quantities are checked."""
    subtotal = money(0)
    tax = money(0)
    for line in lines:
        line_total = money(line["quantity"] * line["unit_price"])
        line["line_total"] = line_total
        subtotal += line_total
        discounted = line_total * (1 - discount_pct / 100)
        tax += money(discounted * line["tax_rate"] / 100)
    subtotal = money(subtotal)
    discount = money(subtotal * discount_pct / 100)
    total = money(subtotal - discount + tax)
    return {"subtotal": subtotal, "discount": discount, "tax": tax, "total": total}


def create_sale(db: Session, data: SaleCreate, user_id: int | None = None) -> Sale:
    """The transactional billing flow (steps 1–13)."""
    # --- validate & load products -------------------------------------------------
    product_ids = list({i.product_id for i in data.items})
    products = {
        p.id: p
        for p in db.scalars(select(Product).where(Product.id.in_(product_ids)))
    }
    missing = set(product_ids) - set(products)
    if missing:
        raise NotFoundError(f"Product(s) not found: {sorted(missing)}")

    # Aggregate quantities (the same product may appear twice in the cart)
    quantities: dict[int, Decimal] = {}
    for item in data.items:
        quantities[item.product_id] = quantities.get(item.product_id, money(0)) + money(item.quantity)

    for pid, qty in quantities.items():
        product = products[pid]
        if not product.is_active:
            raise ConflictError(f"'{product.name}' is deactivated")
        if qty <= 0:
            raise ValidationFailedError("Quantity must be greater than zero")
        if qty > product.current_stock:
            raise InsufficientStockError(
                f"Not enough stock for '{product.name}': have "
                f"{product.current_stock:g}, need {qty:g}"
            )

    # --- pricing math (pure, no DB) ------------------------------------------------
    discount_pct = percent(data.discount_pct)
    lines = []
    for item in data.items:
        product = products[item.product_id]
        lines.append(
            {
                "product": product,
                "quantity": money(item.quantity),
                "unit_price": money(item.unit_price) if item.unit_price is not None else product.selling_price,
                "tax_rate": percent(item.tax_rate) if item.tax_rate is not None else product.tax_rate,
            }
        )
    calc = _calculate(lines, discount_pct)

    # --- create the documents (inside one transaction) ------------------------------
    invoice_no = _new_invoice_no(db)
    sale = Sale(
        invoice_no=invoice_no,
        customer_id=data.customer_id,
        subtotal=calc["subtotal"],
        discount_pct=discount_pct,
        discount=calc["discount"],
        tax=calc["tax"],
        total=calc["total"],
        notes=data.notes,
        created_by_id=user_id,
    )
    db.add(sale)
    db.flush()  # assign sale.id now, without committing

    for line in lines:
        db.add(
            SaleItem(
                sale_id=sale.id,
                product_id=line["product"].id,
                quantity=line["quantity"],
                unit_price=line["unit_price"],
                tax_rate=line["tax_rate"],
                line_total=line["line_total"],
            )
        )

    # Payments: default = one full CASH payment (amount None → sale total).
    payments = data.payments or [PaymentIn(method=PaymentMethod.CASH)]
    total_paid = money(0)
    for p in payments:
        amount = money(p.amount) if p.amount is not None else calc["total"]
        db.add(
            Payment(
                sale_id=sale.id, amount=amount, method=p.method,
                reference=p.reference, created_by_id=user_id,
            )
        )
        total_paid += amount

    # Inventory: one SALE movement per product (negative qty, cost snapshot)
    for pid, qty in quantities.items():
        product = products[pid]
        inventory_service.record_movement(
            db,
            product_id=pid,
            movement_type=MovementType.SALE,
            quantity=-qty,
            unit_cost=product.avg_cost,       # COGS snapshot
            ref_type="SALE",
            ref_id=sale.id,
            user_id=user_id,
        )

    db.commit()          # ← everything becomes durable atomically
    db.refresh(sale)
    logger.info("Sale %s created: total=%s", sale.invoice_no, sale.total)
    return sale


def get_sale(db: Session, sale_id: int) -> Sale:
    sale = db.get(Sale, sale_id)
    if sale is None:
        raise NotFoundError("Sale not found")
    return sale


def list_sales(
    db: Session,
    from_date=None, to_date=None, customer_id: int | None = None,
    search: str | None = None, page: int = 1, size: int = 20,
) -> tuple[list[Sale], int]:
    stmt = select(Sale).order_by(Sale.sale_date.desc())
    if from_date:
        stmt = stmt.where(Sale.sale_date >= from_date)
    if to_date:
        stmt = stmt.where(Sale.sale_date <= to_date)
    if customer_id:
        stmt = stmt.where(Sale.customer_id == customer_id)
    if search:
        stmt = stmt.where(Sale.invoice_no.ilike(f"%{search.strip()}%"))
    return paginate(db, stmt, page, size)


def return_sale_items(db: Session, sale_id: int, data: SaleReturnIn, user_id: int | None = None) -> Sale:
    """Customer returns product(s) from a sale.
    - validates against already-returned quantities
    - records RETURN movements (+qty) so stock comes back
    - writes a negative (refund) payment
    - marks the sale RETURNED when fully returned."""
    sale = get_sale(db, sale_id)
    if sale.status == SaleStatus.RETURNED:
        raise ConflictError("This sale is already fully returned")

    refund_total = money(0)
    for item in data.items:
        sale_item = next(
            (si for si in sale.items if si.product_id == item.product_id), None
        )
        if sale_item is None:
            raise NotFoundError(f"Product {item.product_id} is not on this sale")
        qty = money(item.quantity)
        remaining = sale_item.quantity - sale_item.returned_qty
        if qty > remaining:
            raise ConflictError(
                f"Can return at most {remaining:g} of this product "
                f"({sale_item.returned_qty:g} already returned)"
            )
        # value of the returned portion (after the sale's discount and tax)
        unit_value = sale_item.line_total / sale_item.quantity if sale_item.quantity else 0
        line_refund = money(qty * unit_value * (1 - sale.discount_pct / 100) * (1 + sale_item.tax_rate / 100))
        refund_total += line_refund

        sale_item.returned_qty = money(sale_item.returned_qty + qty)
        inventory_service.record_movement(
            db,
            product_id=sale_item.product_id,
            movement_type=MovementType.RETURN,
            quantity=qty,
            unit_cost=sale_item.product.avg_cost if sale_item.product else sale_item.unit_price,
            ref_type="RETURN",
            ref_id=sale.id,
            note=f"Return on {sale.invoice_no}",
            user_id=user_id,
        )

    if refund_total > 0:
        db.add(
            Payment(
                sale_id=sale.id,
                amount=-refund_total,          # negative = money back
                method=PaymentMethod.CASH,
                reference=f"Refund {sale.invoice_no}",
                created_by_id=user_id,
            )
        )

    all_returned = all(si.returned_qty >= si.quantity for si in sale.items)
    sale.status = SaleStatus.RETURNED if all_returned else SaleStatus.COMPLETED
    db.commit()
    db.refresh(sale)
    return sale
```

Explain the critical mechanics:

- `db.flush()` — sends the `INSERT sale` to the database **without committing**, so `sale.id` exists and can be referenced by items/payments/movements. Commit happens once, at the end.
- Everything from the first validation to `db.commit()` runs in one session transaction. Any exception → the route layer rolls back → the database is untouched.
- The **cost snapshot** `unit_cost=product.avg_cost` is taken at sale time — the bedrock of Phase 14's profit.
- `db.commit()` then `db.refresh(sale)` — after commit we reload the sale so relationship data is present for serialization.
- Returns write **negative payments** (refunds) — consistent with "payments are signed money" from Phase 3.

> **Note:** `PaymentIn_default()` is a small helper returning `{"method": PaymentMethod.CASH, "amount": None}` — the schema default handles it if you pass `None` from the route. (In the final code we construct the default payment directly.)

## 7.7 Routes — `backend/app/api/routes/sales.py`

```python
from datetime import datetime

from fastapi import APIRouter, Depends, Query, status
from sqlalchemy.orm import Session

from app.database.database import get_db
from app.schemas.sale import (SaleCreate, SalePage, SaleRead, SaleReturnIn)
from app.services import sale_service

router = APIRouter(prefix="/api/sales", tags=["sales"])


def _to_read(sale) -> SaleRead:
    return SaleRead(
        id=sale.id, invoice_no=sale.invoice_no,
        customer_id=sale.customer_id,
        customer_name=sale.customer.name if sale.customer else None,
        subtotal=sale.subtotal, discount_pct=sale.discount_pct, discount=sale.discount,
        tax=sale.tax, total=sale.total, status=sale.status, sale_date=sale.sale_date,
        notes=sale.notes,
        created_by=sale.created_by.full_name if sale.created_by else None,
        items=[
            {
                "id": i.id, "product_id": i.product_id,
                "product_name": i.product.name if i.product else None,
                "quantity": i.quantity, "unit_price": i.unit_price,
                "tax_rate": i.tax_rate, "line_total": i.line_total,
                "returned_qty": i.returned_qty,
            }
            for i in sale.items
        ],
        payments=[
            {"id": p.id, "amount": p.amount, "method": p.method,
             "reference": p.reference, "paid_at": p.paid_at}
            for p in sale.payments
        ],
    )


@router.post("", response_model=SaleRead, status_code=status.HTTP_201_CREATED)
def create_sale(body: SaleCreate, db: Session = Depends(get_db)) -> SaleRead:
    try:
        sale = sale_service.create_sale(db, body, user_id=None)  # Phase 18: current user
    except Exception:
        db.rollback()
        raise
    return _to_read(sale)


@router.get("", response_model=SalePage)
def list_sales(
    db: Session = Depends(get_db),
    from_date: datetime | None = Query(default=None),
    to_date: datetime | None = Query(default=None),
    customer_id: int | None = Query(default=None),
    search: str | None = Query(default=None),
    page: int = Query(1, ge=1),
    size: int = Query(20, ge=1, le=100),
) -> dict:
    items, total = sale_service.list_sales(db, from_date, to_date, customer_id, search, page, size)
    return {"items": [_to_read(s) for s in items], "total": total, "page": page, "size": size}


@router.get("/{sale_id}", response_model=SaleRead)
def get_sale(sale_id: int, db: Session = Depends(get_db)) -> SaleRead:
    return _to_read(sale_service.get_sale(db, sale_id))


@router.post("/{sale_id}/return", response_model=SaleRead)
def return_sale(sale_id: int, body: SaleReturnIn, db: Session = Depends(get_db)) -> SaleRead:
    sale = sale_service.return_sale_items(db, sale_id, body, user_id=None)
    return _to_read(sale)
```

## 7.8 Real-world scenario — the complete sale walkthrough

**Scenario 1 (from the requirements):** Tata Salt — cost ₹22, price ₹28, stock 100. Cashier sells **3** for cash.

| Layer | What happens |
|---|---|
| **React** | (Phase 10) cashier types "8901…" or clicks the product; cart shows qty 3; clicks Complete Sale |
| **API** | `POST /api/sales` with `{"items":[{"product_id":1,"quantity":3}],"payments":[{"method":"CASH"}]}` |
| **Pydantic** | validates shape, positive quantity |
| **Service** | stock check (3 ≤ 100 ✓) → pricing: subtotal 84.00, discount 0, tax 0, total 84.00 → invoice `INV-20260808-0001` |
| **SQLAlchemy** | INSERT sale, INSERT sale_item (qty 3 × 28), INSERT payment (84.00 CASH), INSERT movement (SALE, −3, unit_cost 22.00) — **one transaction** |
| **SQLite** | COMMIT → all durable; product `current_stock` = 97 |
| **Invoice** | (Phase 8) PDF `INV-20260808-0001.pdf` saved to `data/invoices/` |
| **Dashboard** | (Phase 15) today's sales += 84.00; profit += 84.00 − 66.00 (COGS 3×22) = **18.00** |

**Scenario 5 — the app crashes mid-sale.** Power cut at step 11, after `INSERT sale` but before COMMIT. What happens? **Nothing persists.** The transaction was never committed, the OS discards it, and the database is exactly as before — stock still 100, no invoice. This is the guarantee of Phase 3's WAL + Phase 7's single-commit discipline. The cashier re-enters the sale. No partial state, ever.

## 7.9 Common mistakes

| Mistake | Why it bites | Fix |
|---|---|---|
| Committing before all inserts | Crash leaves sale without movements | One `db.commit()` at the very end |
| Letting a `commit` inside `record_movement` | It would commit the *whole* sale prematurely | `record_movement` never commits; the caller does |
| Selling with stock check, then stock changes | (Single-user local app: rare) | The DB-level guard (`allow_negative=False`) is the backstop |
| Generating the PDF *inside* the transaction | A PDF failure would roll back a paid sale | Generate after commit, best-effort (7.3 step 14) |
| Two cashiers, same invoice number | Race between `max(invoice_no)` reads | UNIQUE constraint + retry on `IntegrityError` (Phase 20) |

---

## ✅ Phase 7 Checkpoint

Run the API from `/docs`:

1. Create a product with stock 10 (adjust endpoint).
2. `POST /api/sales` with 3 units → **201**, invoice `INV-<today>-0001`, total correct.
3. `GET /api/products/{id}` → `current_stock` = 7.
4. `GET /api/inventory/movements?product_id=…` → a SALE row with qty −3 and unit_cost = your avg_cost.
5. `POST /api/sales` with 99 units → **409** "Not enough stock" and **stock still 7** (the rollback proof).
6. `POST /api/sales/{id}/return` with 1 unit → stock back to 8, a RETURN movement exists, a −1×… refund payment exists.

### If it doesn't work

| Error | Why | Fix |
|---|---|---|
| `AssertionError` / inconsistent totals | Pricing math order wrong | Re-check `_calculate`: subtotal → discount → tax on discounted value → total |
| Stock unchanged after sale | Commit happened before `record_movement`, or movements created after commit | Single commit at the end (7.6) |
| `IntegrityError` duplicate invoice_no | Two quick sales, numbering race | Retry loop (Phase 20); until then, resubmit |

Commit:

```bash
git add -A
git commit -m "feat: implement billing with transactional sale flow"
```

---

# Phase 8 — Invoice Generation

> **Goal of this phase:** turn a completed sale into a professional **A4 PDF invoice** (and later an 80 mm **thermal receipt**) using ReportLab, saved to `data/invoices/` and downloadable from the API.

## 8.1 Problem

The shopkeeper must hand the customer a printed bill. Hand-written bills are slow and error-prone; the invoice must match the database exactly (same numbers, same items) and be re-printable anytime.

## 8.2 Concept: two very different documents

| | **A4 invoice** | **Thermal receipt (80 mm)** |
|---|---|---|
| Used for | Formal records, GST invoicing | Fast billing at the counter |
| Paper | A4 (210×297 mm) | 80 mm wide roll, arbitrary length |
| Content | Full shop header, customer details, item table, totals, terms | Compact: name, qty × price, total |
| ReportLab tool | `SimpleDocTemplate` (paginated flow) | `canvas` / manual layout (fixed 80 mm width) |

ReportLab offers two APIs: **`canvas`** (absolute drawing — like a blank page) and **`platypus`** (`SimpleDocTemplate` + flowables `Paragraph`, `Table`, `Spacer` — automatic layout and pagination). A4 invoices use platypus; thermal receipts often use canvas for precise width control.

### The ₹ symbol problem (a real-world trap)

ReportLab's built-in fonts (Helvetica, Times) are Type-1 fonts that only cover Latin-1 — they cannot draw **₹ (U+20B9)**. You get `□` in the PDF. Fix: register a TrueType font that contains ₹, e.g. Windows' own `C:\Windows\Fonts\arial.ttf` (modern Windows Arial includes ₹) or `seguisym.ttf`. Our PDF service tries to register such a font and falls back to "Rs." if none is found.

## 8.3 The document data — `backend/app/pdf/invoice.py`

```python
"""PDF invoice generation with ReportLab: A4 invoice + 80mm thermal receipt."""
import logging
from io import BytesIO
from pathlib import Path

from reportlab.lib import colors
from reportlab.lib.enums import TA_CENTER, TA_RIGHT
from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import ParagraphStyle, getSampleStyleSheet
from reportlab.lib.units import mm
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.platypus import (HRFlowable, Paragraph, SimpleDocTemplate,
                                Spacer, Table, TableStyle)

from app.core.config import settings
from app.models import AppSetting, Sale

logger = logging.getLogger(__name__)

_FONT = "Helvetica"  # fallback; upgraded to a TTF with ₹ support if found


def _register_fonts() -> None:
    """Try to register a TrueType font that can render ₹ (U+20B9)."""
    global _FONT
    candidates = [
        ("C:/Windows/Fonts/arial.ttf", "ArialUni"),
        ("C:/Windows/Fonts/seguisym.ttf", "SegoeSym"),
        ("C:/Windows/Fonts/calibri.ttf", "Calibri"),
    ]
    for path, name in candidates:
        if Path(path).exists():
            try:
                pdfmetrics.registerFont(TTFont(name, path))
                _FONT = name
                return
            except Exception:  # corrupted font file → try next
                continue
    logger.warning("No TTF with ₹ support found; using Helvetica (₹ may render as □)")


_register_fonts()


def _shop_profile(db) -> dict:
    """Runtime-editable shop details: app_settings row, falling back to config."""
    row = db.get(AppSetting, 1)
    return {
        "name": row.shop_name if row else settings.SHOP_NAME,
        "address": row.shop_address if row else settings.SHOP_ADDRESS,
        "phone": row.shop_phone if row else settings.SHOP_PHONE,
        "gstin": row.shop_gstin if row else settings.SHOP_GSTIN,
        "currency": row.currency if row else settings.CURRENCY,
        "footer": row.invoice_footer if row else None,
    }


def sale_document(db, sale: Sale) -> dict:
    """Gather everything the PDF needs from the DB (single source of truth)."""
    shop = _shop_profile(db)
    return {
        "shop": shop,
        "invoice_no": sale.invoice_no,
        "sale_date": sale.sale_date.strftime("%d %b %Y, %I:%M %p"),
        "customer": {
            "name": sale.customer.name if sale.customer else "Walk-in Customer",
            "phone": sale.customer.phone if sale.customer else "",
            "address": sale.customer.address if sale.customer else "",
        },
        "items": [
            {
                "name": i.product.name if i.product else f"Product #{i.product_id}",
                "qty": i.quantity, "unit": i.unit_price, "tax": i.tax_rate,
                "total": i.line_total,
            }
            for i in sale.items
        ],
        "subtotal": sale.subtotal, "discount_pct": sale.discount_pct,
        "discount": sale.discount, "tax": sale.tax, "total": sale.total,
        "payments": [
            {"method": p.method, "amount": p.amount} for p in sale.payments
        ],
        "notes": sale.notes,
    }
```

> The PDF never recomputes totals from scratch — it *reads the persisted sale* (`sale_document`). The database is the source of truth; the PDF is a rendering. This prevents invoice-vs-system mismatches.

## 8.4 A4 invoice — `render_invoice_pdf(doc)`

```python
def render_invoice_pdf(doc: dict) -> BytesIO:
    """A4 invoice as a bytes buffer. Pure function of the document dict."""
    cur = doc["shop"]["currency"]
    money_fmt = lambda v: f"{cur}{float(v):,.2f}"

    buf = BytesIO()
    styles = getSampleStyleSheet()
    title = ParagraphStyle("title", parent=styles["Title"], fontName=_FONT, fontSize=16)
    small = ParagraphStyle("small", parent=styles["Normal"], fontName=_FONT, fontSize=8)
    right = ParagraphStyle("right", parent=styles["Normal"], fontName=_FONT, fontSize=9, alignment=TA_RIGHT)
    table_cell = ParagraphStyle("cell", parent=styles["Normal"], fontName=_FONT, fontSize=9)

    doc_tpl = SimpleDocTemplate(buf, pagesize=A4, topMargin=15*mm, bottomMargin=15*mm,
                                leftMargin=15*mm, rightMargin=15*mm)

    story = []
    story.append(Paragraph(doc["shop"]["name"], title))
    story.append(Paragraph(doc["shop"]["address"], small))
    story.append(Paragraph(doc["shop"]["phone"], small))
    story.append(Spacer(1, 4*mm))

    story.append(HRFlowable(width="100%", thickness=1, color=colors.black))
    story.append(Spacer(1, 4*mm))

    head = Table(
        [
            [Paragraph("INVOICE", ParagraphStyle("inv", parent=title, fontName=_FONT, fontSize=20)),
             Paragraph(f"Invoice No: <b>{doc['invoice_no']}</b><br/>Date: {doc['sale_date']}", right)],
        ],
        colWidths=[100*mm, 80*mm],
    )
    story.append(head)
    story.append(Spacer(1, 4*mm))

    # Customer block
    customer_lines = [f"<b>Bill To:</b> {doc['customer']['name']}"]
    if doc["customer"]["phone"]:
        customer_lines.append(f"Phone: {doc['customer']['phone']}")
    if doc["customer"]["address"]:
        customer_lines.append(doc["customer"]["address"])
    story.append(Paragraph("<br/>".join(customer_lines), table_cell))
    story.append(Spacer(1, 4*mm))

    # Items table
    rows = [
        ["#", "Product", "Qty", "Unit Price", "Tax %", "Amount"],
    ]
    for idx, it in enumerate(doc["items"], start=1):
        rows.append([
            str(idx), it["name"], f"{it['qty']:g}", f"{money_fmt(it['unit'])}",
            f"{it['tax']:g}%", money_fmt(it["total"]),
        ])
    items_table = Table(rows, colWidths=[8*mm, 80*mm, 14*mm, 24*mm, 14*mm, 22*mm])
    items_table.setStyle(TableStyle([
        ("BACKGROUND", (0, 0), (-1, 0), colors.HexColor("#f0f0f0")),
        ("GRID", (0, 0), (-1, -1), 0.4, colors.grey),
        ("FONTNAME", (0, 0), (-1, -1), _FONT),
        ("FONTSIZE", (0, 0), (-1, -1), 8),
        ("ALIGN", (2, 1), (-1, -1), "RIGHT"),
    ]))
    story.append(items_table)
    story.append(Spacer(1, 4*mm))

    # Totals
    totals = Table(
        [
            ["Subtotal", money_fmt(doc["subtotal"])],
            ["Discount", money_fmt(doc["discount"])],
            ["Tax", money_fmt(doc["tax"])],
            ["<b>Total</b>", f"<b>{money_fmt(doc['total'])}</b>"],
        ],
        colWidths=[50*mm, 40*mm],
    )
    totals.setStyle(TableStyle([
        ("FONTNAME", (0, 0), (-1, -1), _FONT),
        ("FONTSIZE", (0, 0), (-1, -1), 9),
        ("ALIGN", (1, 0), (1, -1), "RIGHT"),
        ("LINEABOVE", (3, 0), (3, -1), 1, colors.black),
    ]))
    story.append(totals)
    story.append(Spacer(1, 4*mm))

    pay_lines = ", ".join(f"{p['method']} {money_fmt(p['amount'])}" for p in doc["payments"])
    story.append(Paragraph(f"<b>Payment:</b> {pay_lines}", table_cell))
    if doc["notes"]:
        story.append(Paragraph(f"<b>Notes:</b> {doc['notes']}", table_cell))
    if doc["shop"]["footer"]:
        story.append(Spacer(1, 8*mm))
        story.append(Paragraph(doc["shop"]["footer"], small))

    doc_tpl.build(story)
    buf.seek(0)
    return buf
```

Explain the platypus pattern: `SimpleDocTemplate` manages pages; `story` is a list of **flowables** (`Paragraph`, `Table`, `Spacer`, `HRFlowable`) laid out automatically. Tables get a `TableStyle` for borders/colors. `ParagraphStyle` lets us use our registered TTF font everywhere.

## 8.5 Thermal receipt — `render_thermal_receipt(doc)`

80 mm wide, variable height, tight spacing (a dot-matrix/thermal printer prints it faster than A4):

```python
def render_thermal_receipt(doc: dict) -> BytesIO:
    """80 mm receipt. Uses canvas for exact width control and to avoid
    pagination surprises on narrow paper."""
    cur = doc["shop"]["currency"]
    money_fmt = lambda v: f"{cur}{float(v):,.2f}"
    W = 80 * mm

    # Estimate height: header + items + totals (2mm per line)
    n_lines = 8 + len(doc["items"]) * 2 + 8
    buf = BytesIO()
    c = canvas.Canvas(buf, pagesize=(W, n_lines * 4 * mm))
    y = n_lines * 4 * mm - 8 * mm
    c.setFont(_FONT, 8)

    def line(text: str, bold: bool = False, size: int = 8, center: bool = False, dy: int = 14):
        nonlocal y
        c.setFont(_FONT, size)
        if bold:
            c.setFont(_FONT + "-Bold" if _FONT == "Helvetica" else _FONT, size)
        if center:
            c.drawCentredString(W / 2, y, text)
        else:
            c.drawString(4 * mm, y, text)
        y -= dy

    line(doc["shop"]["name"], bold=True, size=11, center=True)
    line(doc["shop"]["phone"], center=True)
    line("=" * 42, center=True)
    line(f"INV: {doc['invoice_no']}")
    line(doc["sale_date"])
    line(f"Customer: {doc['customer']['name']}")
    line("-" * 42)
    for it in doc["items"]:
        line(f"{it['name']}")
        line(f"  {it['qty']:g} x {money_fmt(it['unit'])}  {money_fmt(it['total'])}", size=8)
    line("-" * 42)
    line(f"Subtotal  {money_fmt(doc['subtotal'])}", center=True)
    line(f"Discount  {money_fmt(doc['discount'])}", center=True)
    line(f"Tax       {money_fmt(doc['tax'])}", center=True)
    line(f"TOTAL     {money_fmt(doc['total'])}", bold=True, size=10, center=True)
    line("")
    for p in doc["payments"]:
        line(f"{p['method']}: {money_fmt(p['amount'])}", center=True)
    line("=" * 42, center=True)
    line("Thank you for shopping with us!", center=True)
    c.showPage()
    c.save()
    buf.seek(0)
    return buf
```

> **Note on bold fonts:** with our registered TTF we'd register a bold variant too; with Helvetica, `Helvetica-Bold` is built in. The helper above is simplified — in the final code we register `_FONT + "-Bold"` properly (see Complete Source Code).

## 8.6 The service — save + get

`backend/app/services/invoice_service.py`:

```python
import logging
from pathlib import Path

from fastapi import HTTPException
from sqlalchemy.orm import Session

from app.core.config import settings
from app.models import Sale
from app.pdf.invoice import render_invoice_pdf, sale_document

logger = logging.getLogger(__name__)


def invoice_path(invoice_no: str) -> Path:
    return settings.invoices_dir / f"{invoice_no}.pdf"


def generate_invoice(db: Session, sale: Sale, force: bool = False) -> Path:
    """Create/save the PDF. Best-effort by design: a PDF failure must never
    roll back the sale itself (the file is re-generatable)."""
    path = invoice_path(sale.invoice_no)
    if path.exists() and not force:
        return path
    doc = sale_document(db, sale)
    buf = render_invoice_pdf(doc)
    path.write_bytes(buf.getvalue())
    logger.info("Invoice %s written to %s", sale.invoice_no, path)
    return path


def generate_receipt(db: Session, sale: Sale) -> bytes:
    from app.pdf.invoice import render_thermal_receipt
    doc = sale_document(db, sale)
    return render_thermal_receipt(doc).getvalue()
```

And in `sale_service.create_sale`, after `db.commit()` (step 14):

```python
    # step 14 — PDF after commit, best-effort
    try:
        invoice_service.generate_invoice(db, sale)
    except Exception:
        logger.exception("Invoice generation failed for %s", sale.invoice_no)
    return sale
```

## 8.7 The download route — in `backend/app/api/routes/sales.py`

```python
from fastapi.responses import FileResponse
from app.services import invoice_service

@router.get("/{sale_id}/invoice")
def download_invoice(sale_id: int, db: Session = Depends(get_db)):
    sale = sale_service.get_sale(db, sale_id)
    path = invoice_service.generate_invoice(db, sale)
    return FileResponse(path, media_type="application/pdf",
                        filename=f"{sale.invoice_no}.pdf")


@router.get("/{sale_id}/receipt")
def download_receipt(sale_id: int, db: Session = Depends(get_db)):
    sale = sale_service.get_sale(db, sale_id)
    from fastapi.responses import Response
    return Response(content=invoice_service.generate_receipt(db, sale),
                    media_type="application/pdf")
```

## ✏️ Exercise 8.1 — make the invoice "yours"

1. Add the **GSTIN** to the A4 header (it's already in `sale_document` → `shop["gstin"]`). Place it under the shop phone.
2. Add the `invoice_footer` ("Goods once sold cannot be returned…" / "Payment due in 15 days") — the plumbing exists; just render it (already done above — verify it appears).
3. **Challenge:** render the shop name *in Hindi/your local language*. (Hint: you need a TTF that contains those glyphs — try `C:/Windows/Fonts/` for a suitable font, e.g. `Nirmala.ttf` or `Mangal.ttf`, and register it.)

<details>
<summary><b>Solution sketch</b> (after attempting!)</summary>

```python
# 1 — in the head/header section of render_invoice_pdf:
if doc["shop"]["gstin"]:
    story.append(Paragraph(f"GSTIN: {doc['shop']['gstin']}", small))

# 3 — register a Devanagari font the same way we registered ArialUni:
#    ("C:/Windows/Fonts/Nirmala.ttf", "Nirmala") — then use it in styles.
```

</details>

## 8.8 Common mistakes

| Mistake | Why it bites | Fix |
|---|---|---|
| Recomputing totals in the PDF | Invoice can disagree with the sale row | Read the persisted sale (`sale_document`) |
| Generating inside the transaction | PDF error rolls back a paid sale | After commit, best-effort (8.6) |
| ₹ shows as `□` | Helvetica has no U+20B9 | Register a TTF (`_register_fonts`) |
| Receipt overflows page | Fixed canvas height < content | Estimate height from item count (8.5) |

---

## ✅ Phase 8 Checkpoint

1. Complete a sale (Phase 7 checkpoint did this — invoice # exists).
2. `GET /api/sales/{id}/invoice` in a browser → the PDF downloads.
3. Open it: shop header, invoice number, customer, item table, totals, payment line all present and **matching the sale in the DB**.
4. `GET /api/sales/{id}/receipt` → the 80 mm version.
5. Re-download → the file is re-used (`data/invoices/INV-….pdf` exists).
6. Exercise 8.1 done (GSTIN + footer visible).

### If it doesn't work

| Error | Why | Fix |
|---|---|---|
| `reportlab` import fails | Not installed | `pip install reportlab` (it's in requirements) |
| PDF won't open (corrupt) | Exception during `build` | Check console traceback; most common: a None value formatted into a string |
| `□` instead of ₹ | Font fallback active | Register Arial (8.3); on Windows it's at `C:/Windows/Fonts/arial.ttf` |

Commit:

```bash
git add -A
git commit -m "feat: add invoice generation (A4 PDF + thermal receipt)"
```

---

**Next:** [Phase 9 — React Frontend](#phase-9--react-frontend)
# Phase 9 — React Frontend

> **Goal of this phase:** learn React's architecture while building the UI shell — layout, routing, the API layer, global state, reusable components — then the **Products** page, which becomes the template for every other page.

## 9.1 Concepts, in order

- **Components** — functions that return UI. Small, single-purpose, composable. We split them into `ui/` (generic: `Button`, `Modal`) and domain (`ProductForm`).
- **Props** — inputs passed down (`<Button variant="danger">`). Data flows one way: parent → child.
- **State** — data that changes over time. Local state (`useState`) for a form field; **global state** (Zustand) for things many components share: the cart, the logged-in user, toasts.
- **Hooks** — React functions that reuse stateful logic (`useState`, `useEffect`), plus our own (`useApi`, `useDebounce`).
- **Forms** — controlled inputs (value + onChange) with validation. We do client-side validation for *speed*, but the backend is the real validator — the frontend never "trusts" itself.
- **API calls** — one `services/api.ts` wrapper: every call goes through it, errors are normalized to a `ApiError` with a readable message.
- **The three UI states every list needs:** 🕐 loading → (skeleton/spinner), ❌ error → (message + retry), 😶 empty → (friendly empty state). Forgetting empty/error states is the most common amateur mistake.
- **Tables and modals** — a generic `DataTable<T>` and `Modal` used by *every* page, so the design stays consistent.

## 9.2 Install the frontend dependencies

```bash
cd frontend
npm install zustand react-router-dom lucide-react
npm install -D vitest @testing-library/react @testing-library/jest-dom jsdom @testing-library/user-event
```

- **zustand** — tiny global store (cart, auth, toasts).
- **react-router-dom** — routing (v7).
- **lucide-react** — icons.
- The test tools are for Phase 21; installing now keeps `package.json` stable.

## 9.3 Types — `frontend/src/types/index.ts`

These mirror the backend schemas *exactly* — same names, same shapes. This file is the contract between the two teams (you and future-you):

```ts
export type Role = "OWNER" | "MANAGER" | "CASHIER";
export type MovementType = "PURCHASE" | "SALE" | "RETURN" | "ADJUSTMENT" | "DAMAGE";
export type PaymentMethod = "CASH" | "UPI" | "CARD" | "CREDIT" | "BANK";
export type SaleStatus = "COMPLETED" | "RETURNED";
export type PurchaseStatus = "COMPLETED" | "PARTIAL";

export interface Paginated<T> {
  items: T[];
  total: number;
  page: number;
  size: number;
}

export interface Category {
  id: number;
  name: string;
  description: string | null;
}

export interface Product {
  id: number;
  name: string;
  sku: string | null;
  barcode: string | null;
  category_id: number | null;
  category_name: string | null;
  purchase_price: number;
  selling_price: number;
  tax_rate: number;
  min_stock: number;
  current_stock: number;
  avg_cost: number;
  is_active: boolean;
  created_at: string;
  updated_at: string;
}

export interface ProductInput {
  name: string;
  sku?: string | null;
  barcode?: string | null;
  category_id?: number | null;
  purchase_price?: number;
  selling_price?: number;
  tax_rate?: number;
  min_stock?: number;
  is_active?: boolean;
}

export interface Customer {
  id: number; name: string; phone: string | null; address: string | null;
  notes: string | null; is_active: boolean;
}

export interface Supplier {
  id: number; name: string; phone: string | null; address: string | null;
  notes: string | null; is_active: boolean;
}

export interface SaleItem {
  id: number; product_id: number; product_name: string | null;
  quantity: number; unit_price: number; tax_rate: number;
  line_total: number; returned_qty: number;
}

export interface Payment {
  id: number; amount: number; method: PaymentMethod;
  reference: string | null; paid_at: string;
}

export interface Sale {
  id: number; invoice_no: string; customer_id: number | null; customer_name: string | null;
  subtotal: number; discount_pct: number; discount: number; tax: number; total: number;
  status: SaleStatus; sale_date: string; notes: string | null; created_by: string | null;
  items: SaleItem[]; payments: Payment[];
}

export interface PurchaseItem {
  id: number; product_id: number; product_name: string | null;
  quantity: number; unit_cost: number; tax_rate: number; line_total: number;
}

export interface Purchase {
  id: number; purchase_no: string; supplier_id: number | null; supplier_name: string | null;
  purchase_date: string; subtotal: number; discount_pct: number; discount: number;
  tax: number; total: number; paid_amount: number; payment_method: PaymentMethod;
  status: PurchaseStatus; notes: string | null; created_by: string | null;
  items: PurchaseItem[];
}

export interface Expense {
  id: number; expense_date: string; category: string; amount: number;
  description: string | null; created_by: string | null;
}

export interface InventoryMovement {
  id: number; product_id: number; product_name: string | null;
  movement_type: MovementType; quantity: number; unit_cost: number;
  ref_type: string | null; ref_id: number | null; note: string | null;
  created_at: string; created_by: string | null;
}

export interface User {
  id: number; username: string; full_name: string; role: Role; is_active: boolean;
}

export interface ApiErrorShape {
  code?: string;
  message: string;
}

export class ApiError extends Error {
  status: number;
  code?: string;
  constructor(status: number, message: string, code?: string) {
    super(message);
    this.status = status;
    this.code = code;
  }
}
```

## 9.4 The API client — `frontend/src/services/api.ts`

One wrapper for everything. It adds the auth token (Phase 18), converts errors, and handles 204:

```ts
import { ApiError } from "../types";

export const API_BASE =
  (import.meta.env.VITE_API_URL as string | undefined) ?? "http://127.0.0.1:8000";

export const TOKEN_KEY = "lrm_token";

function token(): string | null {
  return localStorage.getItem(TOKEN_KEY);
}

export function toQuery(params: Record<string, string | number | boolean | null | undefined>): string {
  const q = new URLSearchParams();
  for (const [k, v] of Object.entries(params)) {
    if (v !== null && v !== undefined && v !== "") q.set(k, String(v));
  }
  const s = q.toString();
  return s ? `?${s}` : "";
}

async function request<T>(path: string, options: RequestInit = {}): Promise<T> {
  const headers: Record<string, string> = {
    "Content-Type": "application/json",
    ...(options.headers as Record<string, string> | undefined),
  };
  const t = token();
  if (t) headers.Authorization = `Bearer ${t}`;

  const res = await fetch(`${API_BASE}${path}`, { ...options, headers });

  if (!res.ok) {
    let detail: unknown = res.statusText;
    try {
      const body = await res.json();
      detail = (body as { detail?: unknown }).detail ?? detail;
    } catch {
      /* non-JSON error body */
    }
    const shape =
      typeof detail === "object" && detail !== null
        ? (detail as { code?: string; message?: string })
        : null;
    const message =
      typeof detail === "string" ? detail : (shape?.message ?? `Request failed (${res.status})`);
    throw new ApiError(res.status, message, shape?.code);
  }

  if (res.status === 204) return undefined as T;
  return (await res.json()) as T;
}

export const api = {
  get: <T>(path: string) => request<T>(path),
  post: <T>(path: string, body?: unknown) =>
    request<T>(path, { method: "POST", body: JSON.stringify(body ?? {}) }),
  patch: <T>(path: string, body?: unknown) =>
    request<T>(path, { method: "PATCH", body: JSON.stringify(body ?? {}) }),
  delete: <T>(path: string) => request<T>(path, { method: "DELETE" }),
};
```

One service module per resource — `frontend/src/services/products.ts`:

```ts
import { api, toQuery } from "./api";
import type { Category, Paginated, Product, ProductInput } from "../types";

export const productsApi = {
  list: (params: { search?: string; category_id?: number; include_inactive?: boolean; page?: number; size?: number } = {}) =>
    api.get<Paginated<Product>>(`/api/products${toQuery(params)}`),
  get: (id: number) => api.get<Product>(`/api/products/${id}`),
  create: (data: ProductInput) => api.post<Product>("/api/products", data),
  update: (id: number, data: Partial<ProductInput>) => api.patch<Product>(`/api/products/${id}`, data),
  deactivate: (id: number) => api.delete<void>(`/api/products/${id}`),
};

export const categoriesApi = {
  list: () => api.get<Category[]>("/api/categories"),
  create: (data: { name: string; description?: string | null }) =>
    api.post<Category>("/api/categories", data),
};
```

> Every resource gets this file pattern: `list / get / create / update / delete`. Billing, customers, suppliers… all the same shape.

## 9.5 Utils — `frontend/src/utils/format.ts`

```ts
export function round2(n: number): number {
  return Math.round((n + Number.EPSILON) * 100) / 100;
}

export function formatMoney(n: number, currency = "₹"): string {
  return `${currency}${n.toLocaleString("en-IN", { minimumFractionDigits: 2, maximumFractionDigits: 2 })}`;
}

export function formatDate(iso: string | null | undefined): string {
  if (!iso) return "—";
  return new Date(iso).toLocaleDateString("en-IN", { day: "2-digit", month: "short", year: "numeric" });
}

export function formatDateTime(iso: string | null | undefined): string {
  if (!iso) return "—";
  return new Date(iso).toLocaleString("en-IN", {
    day: "2-digit", month: "short", year: "numeric", hour: "2-digit", minute: "2-digit",
  });
}
```

## 9.6 Toasts — global feedback without shouting

`frontend/src/store/toast.ts` (Zustand):

```ts
import { create } from "zustand";

export interface Toast {
  id: number;
  type: "success" | "error" | "info";
  message: string;
}

interface ToastState {
  toasts: Toast[];
  push: (type: Toast["type"], message: string) => void;
  dismiss: (id: number) => void;
}

let nextId = 1;

export const useToast = create<ToastState>((set) => ({
  toasts: [],
  push: (type, message) => {
    const id = nextId++;
    set((s) => ({ toasts: [...s.toasts, { id, type, message }] }));
    setTimeout(() => {
      set((s) => ({ toasts: s.toasts.filter((t) => t.id !== id) }));
    }, 3500);
  },
  dismiss: (id) => set((s) => ({ toasts: s.toasts.filter((t) => t.id !== id) })),
}));

export const toast = {
  success: (m: string) => useToast.getState().push("success", m),
  error: (m: string) => useToast.getState().push("error", m),
  info: (m: string) => useToast.getState().push("info", m),
};
```

And the renderer `components/ui/Toaster.tsx` (fixed top-right, auto-dismissed by the store):

```tsx
import { useToast } from "../../store/toast";

export function Toaster() {
  const toasts = useToast((s) => s.toasts);
  const dismiss = useToast((s) => s.dismiss);

  const styles: Record<string, string> = {
    success: "bg-emerald-600 text-white",
    error: "bg-rose-600 text-white",
    info: "bg-slate-700 text-white",
  };

  return (
    <div className="fixed top-4 right-4 z-[100] flex flex-col gap-2">
      {toasts.map((t) => (
        <button
          key={t.id}
          onClick={() => dismiss(t.id)}
          className={`${styles[t.type]} rounded-lg px-4 py-2 text-sm font-medium shadow-lg transition hover:opacity-90`}
        >
          {t.message}
        </button>
      ))}
    </div>
  );
}
```

## 9.7 The reusable UI kit

These live in `components/ui/` and know **nothing** about products or sales. `Button.tsx`:

```tsx
import type { ButtonHTMLAttributes, ReactNode } from "react";

type Variant = "primary" | "secondary" | "danger" | "ghost";

const variants: Record<Variant, string> = {
  primary: "bg-emerald-600 text-white hover:bg-emerald-700",
  secondary: "bg-white text-slate-700 border border-slate-300 hover:bg-slate-50",
  danger: "bg-rose-600 text-white hover:bg-rose-700",
  ghost: "text-slate-600 hover:bg-slate-100",
};

interface Props extends ButtonHTMLAttributes<HTMLButtonElement> {
  variant?: Variant;
  loading?: boolean;
  children: ReactNode;
}

export function Button({ variant = "primary", loading, children, className = "", disabled, ...rest }: Props) {
  return (
    <button
      className={`inline-flex items-center gap-2 rounded-lg px-4 py-2 text-sm font-semibold transition
        disabled:cursor-not-allowed disabled:opacity-60 ${variants[variant]} ${className}`}
      disabled={disabled || loading}
      {...rest}
    >
      {loading && <Spinner className="h-4 w-4" />}
      {children}
    </button>
  );
}
```

`Input.tsx` (label + error + the `forwardRef` we'll need for autofocus in billing):

```tsx
import { forwardRef } from "react";
import type { InputHTMLAttributes } from "react";

interface Props extends InputHTMLAttributes<HTMLInputElement> {
  label?: string;
  error?: string;
}

export const Input = forwardRef<HTMLInputElement, Props>(
  ({ label, error, className = "", ...rest }, ref) => (
    <label className="block">
      {label && <span className="mb-1 block text-sm font-medium text-slate-700">{label}</span>}
      <input
        ref={ref}
        className={`w-full rounded-lg border px-3 py-2 text-sm outline-none transition
          focus:ring-2 ${error ? "border-rose-400 focus:ring-rose-200"
          : "border-slate-300 focus:border-emerald-500 focus:ring-emerald-200"} ${className}`}
        {...rest}
      />
      {error && <span className="mt-1 block text-xs text-rose-600">{error}</span>}
    </label>
  ),
);
Input.displayName = "Input";
```

`Select.tsx`, `Modal.tsx`, `ConfirmDialog.tsx`, `Badge.tsx`, `Spinner.tsx`, `EmptyState.tsx`, `StatCard.tsx`, `PageHeader.tsx` follow the same spirit. `DataTable.tsx` is the workhorse:

```tsx
import type { ReactNode } from "react";
import { EmptyState } from "./EmptyState";

export interface Column<T> {
  key: string;
  header: string;
  render?: (row: T) => ReactNode;
  className?: string;
}

interface Props<T> {
  columns: Column<T>[];
  rows: T[];
  keyOf: (row: T, index: number) => string | number;
  empty?: string;
}

export function DataTable<T>({ columns, rows, keyOf, empty }: Props<T>) {
  if (rows.length === 0) return <EmptyState message={empty ?? "No records yet."} />;
  return (
    <div className="overflow-x-auto rounded-xl border border-slate-200 bg-white">
      <table className="min-w-full divide-y divide-slate-200 text-sm">
        <thead className="bg-slate-50">
          <tr>
            {columns.map((c) => (
              <th key={c.key} className={`px-4 py-2.5 text-left font-semibold text-slate-600 ${c.className ?? ""}`}>
                {c.header}
              </th>
            ))}
          </tr>
        </thead>
        <tbody className="divide-y divide-slate-100">
          {rows.map((row, index) => (
            <tr key={keyOf(row, index)} className="transition-colors hover:bg-slate-50">
              {columns.map((c) => (
                <td key={c.key} className={`px-4 py-2.5 ${c.className ?? ""}`}>
                  {c.render ? c.render(row) : String((row as Record<string, unknown>)[c.key] ?? "")}
                </td>
              ))}
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
}
```

## 9.8 Hooks — `hooks/useApi.ts` and `hooks/useDebounce.ts`

`useApi` gives every page the loading/error/data trio for free:

```ts
import { useCallback, useEffect, useState } from "react";

export function useApi<T>(fn: () => Promise<T>, deps: unknown[] = []) {
  const [data, setData] = useState<T | null>(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);

  const run = useCallback(() => {
    setLoading(true);
    setError(null);
    fn()
      .then(setData)
      .catch((e: Error) => setError(e.message))
      .finally(() => setLoading(false));
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, deps);

  useEffect(() => {
    run();
  }, [run]);

  return { data, loading, error, refetch: run };
}

export function useDebounce<T>(value: T, delay = 300): T {
  const [debounced, setDebounced] = useState(value);
  useEffect(() => {
    const id = setTimeout(() => setDebounced(value), delay);
    return () => clearTimeout(id);
  }, [value, delay]);
  return debounced;
}
```

## 9.9 Layout and routing

`components/layout/Sidebar.tsx` — navigation with icons; `AppLayout.tsx` composes sidebar + content area + `<Toaster/>`:

```tsx
import { NavLink, Outlet } from "react-router-dom";
import {
  LayoutDashboard, ShoppingCart, Package, Boxes, Truck, Users,
  Contact, Wallet, BarChart3, Settings, UserCog,
} from "lucide-react";
import { Toaster } from "../ui/Toaster";

const NAV = [
  { to: "/", label: "Dashboard", icon: LayoutDashboard },
  { to: "/billing", label: "Billing", icon: ShoppingCart },
  { to: "/products", label: "Products", icon: Package },
  { to: "/inventory", label: "Inventory", icon: Boxes },
  { to: "/purchases", label: "Purchases", icon: Truck },
  { to: "/customers", label: "Customers", icon: Users },
  { to: "/suppliers", label: "Suppliers", icon: Contact },
  { to: "/expenses", label: "Expenses", icon: Wallet },
  { to: "/reports", label: "Reports", icon: BarChart3 },
  { to: "/users", label: "Users", icon: UserCog },
  { to: "/settings", label: "Settings", icon: Settings },
];

export function AppLayout() {
  return (
    <div className="flex min-h-screen bg-slate-100">
      <aside className="flex w-56 shrink-0 flex-col border-r border-slate-200 bg-white">
        <div className="px-5 py-4 text-lg font-bold text-emerald-700">🛍️ Local Retail</div>
        <nav className="flex-1 space-y-0.5 px-3">
          {NAV.map(({ to, label, icon: Icon }) => (
            <NavLink
              key={to}
              to={to}
              end={to === "/"}
              className={({ isActive }) =>
                `flex items-center gap-3 rounded-lg px-3 py-2 text-sm font-medium transition
                ${isActive ? "bg-emerald-50 text-emerald-700" : "text-slate-600 hover:bg-slate-50"}`
              }
            >
              <Icon className="h-4 w-4" />
              {label}
            </NavLink>
          ))}
        </nav>
      </aside>
      <main className="flex-1 overflow-auto p-6">
        <Outlet />
      </main>
      <Toaster />
    </div>
  );
}
```

> In Phase 18 the NAV entries learn a `roles` property and the sidebar *and* the router hide/deny what a role can't use — but the backend remains the real gate.

`App.tsx`:

```tsx
import { BrowserRouter, Route, Routes } from "react-router-dom";
import { AppLayout } from "./components/layout/AppLayout";
import { BillingPage } from "./pages/BillingPage";
import { CustomersPage } from "./pages/CustomersPage";
import { DashboardPage } from "./pages/DashboardPage";
import { ExpensesPage } from "./pages/ExpensesPage";
import { InventoryPage } from "./pages/InventoryPage";
import { ProductsPage } from "./pages/ProductsPage";
import { PurchasesPage } from "./pages/PurchasesPage";
import { ReportsPage } from "./pages/ReportsPage";
import { SettingsPage } from "./pages/SettingsPage";
import { SuppliersPage } from "./pages/SuppliersPage";
import { UsersPage } from "./pages/UsersPage";

export default function App() {
  return (
    <BrowserRouter>
      <Routes>
        <Route element={<AppLayout />}>
          <Route path="/" element={<DashboardPage />} />
          <Route path="/billing" element={<BillingPage />} />
          <Route path="/products" element={<ProductsPage />} />
          <Route path="/inventory" element={<InventoryPage />} />
          <Route path="/purchases" element={<PurchasesPage />} />
          <Route path="/customers" element={<CustomersPage />} />
          <Route path="/suppliers" element={<SuppliersPage />} />
          <Route path="/expenses" element={<ExpensesPage />} />
          <Route path="/reports" element={<ReportsPage />} />
          <Route path="/users" element={<UsersPage />} />
          <Route path="/settings" element={<SettingsPage />} />
        </Route>
      </Routes>
    </BrowserRouter>
  );
}
```

Create stub pages for all routes (a heading + empty state) — we fill them in this and later phases. **Dashboard** gets a real skeleton now (metrics come from the API in Phase 15, so for now show the layout with `—` values).

## 9.10 The Products page — the CRUD pattern every page copies

`pages/ProductsPage.tsx` — search, category filter, table, create/edit modal, deactivate, toasts, all three UI states:

```tsx
import { useCallback, useEffect, useMemo, useState } from "react";
import { Pencil, Plus, Search, Trash2 } from "lucide-react";
import { Badge } from "../components/ui/Badge";
import { Button } from "../components/ui/Button";
import { DataTable, type Column } from "../components/ui/DataTable";
import { EmptyState } from "../components/ui/EmptyState";
import { Input } from "../components/ui/Input";
import { Modal } from "../components/ui/Modal";
import { PageHeader } from "../components/ui/PageHeader";
import { ProductForm } from "../components/forms/ProductForm";
import { useDebounce } from "../hooks/useDebounce";
import { categoriesApi, productsApi } from "../services/products";
import { toast } from "../store/toast";
import type { Category, Product } from "../types";
import { formatMoney } from "../utils/format";

export function ProductsPage() {
  const [rows, setRows] = useState<Product[]>([]);
  const [total, setTotal] = useState(0);
  const [page, setPage] = useState(1);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);
  const [search, setSearch] = useState("");
  const [categoryId, setCategoryId] = useState<number | null>(null);
  const [categories, setCategories] = useState<Category[]>([]);
  const [editing, setEditing] = useState<Product | null>(null);
  const [creating, setCreating] = useState(false);

  const debouncedSearch = useDebounce(search, 300);

  const load = useCallback(async () => {
    setLoading(true);
    setError(null);
    try {
      const res = await productsApi.list({
        search: debouncedSearch || undefined,
        category_id: categoryId ?? undefined,
        page, size: 20,
      });
      setRows(res.items);
      setTotal(res.total);
    } catch (e) {
      setError((e as Error).message);
    } finally {
      setLoading(false);
    }
  }, [debouncedSearch, categoryId, page]);

  useEffect(() => {
    load();
  }, [load]);

  useEffect(() => {
    categoriesApi.list().then(setCategories).catch(() => {/* non-fatal */});
  }, []);

  const columns: Column<Product>[] = useMemo(
    () => [
      { key: "name", header: "Product", render: (p) => (
        <div>
          <div className="font-medium text-slate-800">{p.name}</div>
          {p.sku && <div className="text-xs text-slate-400">{p.sku}</div>}
        </div>
      )},
      { key: "category_name", header: "Category", render: (p) => p.category_name ?? "—" },
      { key: "selling_price", header: "Selling", render: (p) => formatMoney(p.selling_price) },
      { key: "purchase_price", header: "Cost", render: (p) => formatMoney(p.purchase_price) },
      { key: "current_stock", header: "Stock", render: (p) => (
        <Badge tone={p.current_stock <= p.min_stock ? "danger" : "success"}>{p.current_stock}</Badge>
      )},
      { key: "actions", header: "", render: (p) => (
        <div className="flex justify-end gap-1">
          <Button variant="ghost" onClick={() => setEditing(p)}><Pencil className="h-4 w-4" /></Button>
          <Button variant="ghost" onClick={() => handleDeactivate(p)}><Trash2 className="h-4 w-4 text-rose-500" /></Button>
        </div>
      )},
    ],
    [],
  );

  async function handleDeactivate(p: Product) {
    if (!confirm(`Deactivate "${p.name}"? It stays in history but can't be sold.`)) return;
    try {
      await productsApi.deactivate(p.id);
      toast.success(`${p.name} deactivated`);
      load();
    } catch (e) {
      toast.error((e as Error).message);
    }
  }

  return (
    <div className="space-y-4">
      <PageHeader title="Products" action={
        <Button onClick={() => setCreating(true)}><Plus className="h-4 w-4" /> Add Product</Button>
      } />

      <div className="flex items-center gap-3">
        <div className="relative w-72">
          <Search className="absolute top-2.5 left-3 h-4 w-4 text-slate-400" />
          <Input className="pl-9" placeholder="Search name, SKU, barcode…" value={search} onChange={(e) => { setSearch(e.target.value); setPage(1); }} />
        </div>
        <select
          className="rounded-lg border border-slate-300 px-3 py-2 text-sm"
          value={categoryId ?? ""}
          onChange={(e) => { setCategoryId(e.target.value ? Number(e.target.value) : null); setPage(1); }}
        >
          <option value="">All categories</option>
          {categories.map((c) => <option key={c.id} value={c.id}>{c.name}</option>)}
        </select>
      </div>

      {loading && <EmptyState message="Loading…" />}
      {!loading && error && (
        <div className="rounded-lg bg-rose-50 p-4 text-sm text-rose-700">
          {error} <button className="underline" onClick={load}>Retry</button>
        </div>
      )}
      {!loading && !error && (
        <DataTable columns={columns} rows={rows} keyOf={(p) => p.id} empty="No products found." />
      )}
      {!loading && !error && total > 0 && (
        <div className="text-sm text-slate-500">
          {total} product(s) · {page}
          <Button variant="ghost" disabled={page <= 1} onClick={() => setPage(page - 1)}>Prev</Button>
          <Button variant="ghost" disabled={page * 20 >= total} onClick={() => setPage(page + 1)}>Next</Button>
        </div>
      )}

      <Modal open={creating || !!editing} onClose={() => { setCreating(false); setEditing(null); }}
        title={editing ? "Edit Product" : "Add Product"}>
        <ProductForm
          initial={editing ?? undefined}
          categories={categories}
          onSaved={() => { setCreating(false); setEditing(null); load(); }}
        />
      </Modal>
    </div>
  );
}
```

And the form `components/forms/ProductForm.tsx` (controlled inputs + validation + submit):

```tsx
import { useState } from "react";
import { Button } from "../ui/Button";
import { Input } from "../ui/Input";
import { Select } from "../ui/Select";
import { productsApi } from "../../services/products";
import { toast } from "../../store/toast";
import type { Category, Product, ProductInput } from "../../types";

interface Props {
  initial?: Product;
  categories: Category[];
  onSaved: () => void;
}

export function ProductForm({ initial, categories, onSaved }: Props) {
  const [form, setForm] = useState<ProductInput>({
    name: initial?.name ?? "",
    sku: initial?.sku ?? "",
    barcode: initial?.barcode ?? "",
    category_id: initial?.category_id ?? null,
    purchase_price: initial?.purchase_price ?? 0,
    selling_price: initial?.selling_price ?? 0,
    tax_rate: initial?.tax_rate ?? 0,
    min_stock: initial?.min_stock ?? 0,
  });
  const [errors, setErrors] = useState<Record<string, string>>({});
  const [saving, setSaving] = useState(false);

  function set<K extends keyof ProductInput>(key: K, value: ProductInput[K]) {
    setForm((f) => ({ ...f, [key]: value }));
  }

  function validate(): boolean {
    const e: Record<string, string> = {};
    if (!form.name?.trim()) e.name = "Name is required";
    if (Number(form.selling_price) < 0) e.selling_price = "Cannot be negative";
    if (Number(form.tax_rate) < 0 || Number(form.tax_rate) > 100) e.tax_rate = "0–100";
    setErrors(e);
    return Object.keys(e).length === 0;
  }

  async function submit() {
    if (!validate()) return;
    setSaving(true);
    try {
      if (initial) {
        await productsApi.update(initial.id, { ...form, name: form.name!.trim() });
        toast.success("Product updated");
      } else {
        await productsApi.create({ ...form, name: form.name!.trim() });
        toast.success("Product created");
      }
      onSaved();
    } catch (e) {
      toast.error((e as Error).message);
    } finally {
      setSaving(false);
    }
  }

  return (
    <div className="grid grid-cols-2 gap-4">
      <div className="col-span-2">
        <Input label="Name *" value={form.name ?? ""} error={errors.name}
          onChange={(e) => set("name", e.target.value)} />
      </div>
      <Input label="SKU" value={form.sku ?? ""} onChange={(e) => set("sku", e.target.value)} />
      <Input label="Barcode" value={form.barcode ?? ""} onChange={(e) => set("barcode", e.target.value)} />
      <Select label="Category" value={form.category_id ?? ""}
        onChange={(e) => set("category_id", e.target.value ? Number(e.target.value) : null)}>
        <option value="">—</option>
        {categories.map((c) => <option key={c.id} value={c.id}>{c.name}</option>)}
      </Select>
      <div />
      <Input label="Purchase price" type="number" step="0.01" value={form.purchase_price ?? 0}
        onChange={(e) => set("purchase_price", Number(e.target.value))} />
      <Input label="Selling price" type="number" step="0.01" value={form.selling_price ?? 0}
        error={errors.selling_price} onChange={(e) => set("selling_price", Number(e.target.value))} />
      <Input label="Tax rate (%)" type="number" step="0.01" value={form.tax_rate ?? 0}
        error={errors.tax_rate} onChange={(e) => set("tax_rate", Number(e.target.value))} />
      <Input label="Min stock" type="number" step="0.01" value={form.min_stock ?? 0}
        onChange={(e) => set("min_stock", Number(e.target.value))} />
      <div className="col-span-2 flex justify-end gap-2 pt-2">
        <Button variant="secondary" onClick={onSaved}>Cancel</Button>
        <Button loading={saving} onClick={submit}>{initial ? "Save changes" : "Create"}</Button>
      </div>
    </div>
  );
}
```

## 9.11 What we just learned (the pattern)

Every future page = **state (load/list) + DataTable + Modal form + toasts + loading/error/empty states**. Customers, suppliers, expenses, users will all be built this way — mostly by copy-adjusting ProductsPage.

## ✏️ Exercise 9.1 — complete the `brand` chain in the UI

In Exercise 5.1 the API now accepts/serves `brand`. Add it to the frontend:

1. Add `brand: string | null` to the `Product` type and `brand?: string | null` to `ProductInput`.
2. Add a `brand` input to `ProductForm`.
3. Show brand under the product name in the table.

<details>
<summary><b>Solution</b> (after attempting!)</summary>

```ts
// types: add brand to Product and ProductInput
// ProductForm: <Input label="Brand" value={form.brand ?? ""} onChange={(e) => set("brand", e.target.value)} />
// ProductsPage column: <div className="text-xs text-slate-400">{p.sku} · {p.brand}</div>
```

</details>

## 9.12 Common mistakes

| Mistake | Why it bites | Fix |
|---|---|---|
| Calling the API inside `useEffect` without a cleanup/cancel | Stale responses overwrite newer ones on rapid search | `useApi` + debounce pattern (9.8) |
| Forgetting loading/error/empty states | Blank screens with no explanation | The three-state pattern in every list |
| Typing `any` everywhere | Loses the type contract with the backend | Keep `types/index.ts` in sync; never `any` in services |
| Business math inside components | Untestable; duplicates backend logic | Pure helpers in `utils/` (pricing next phase) |

---

## ✅ Phase 9 Checkpoint

- [ ] `npm run dev` — sidebar with all 11 links, layout renders
- [ ] Products page: create/edit/deactivate products, search works (debounced), stock badge turns red at/below min
- [ ] Error state visible if you stop the backend (proves the wrapper works)
- [ ] Toasts appear on success and failure
- [ ] Exercise 9.1 done (brand visible)

Commit:

```bash
git add -A
git commit -m "feat: add React app shell, API layer, and products page"
```

---

# Phase 10 — Billing UI

> **Goal of this phase:** the cashier's screen — optimized for **speed**. A cashier completes hundreds of transactions per day; every wasted second is a longer queue.

## 10.1 UX decisions (design first)

| Decision | Why |
|---|---|
| **One screen, two panels** — products left, cart right | No navigation during a sale |
| **Barcode input always focused** | Scanning or typing immediately adds a product; no click needed |
| **Enter = add to cart**; qty editable in the cart | Least keystrokes per line |
| **Keyboard shortcuts** (`/` focuses search) | Power users never touch the mouse |
| **Big touch-friendly buttons** for products | Works on touch screens too |
| **Payment method + total visible always** | Cashier sees the money without scrolling |
| **One "Complete Sale" button** | The single action; success → invoice link + clear cart |

## 10.2 The cart store — `frontend/src/store/cart.ts`

Global state so the Billing page and its components share one cart:

```ts
import { create } from "zustand";
import type { PaymentMethod, Product } from "../types";

export interface CartItem {
  product: Product;
  qty: number;
  unitPrice: number;
  taxRate: number;
}

interface CartState {
  items: CartItem[];
  customerId: number | null;
  discountPct: number;
  paymentMethod: PaymentMethod;
  cashReceived: number;
  add: (product: Product) => void;
  setQty: (productId: number, qty: number) => void;
  remove: (productId: number) => void;
  setCustomer: (id: number | null) => void;
  setDiscount: (pct: number) => void;
  setPayment: (m: PaymentMethod) => void;
  setCashReceived: (n: number) => void;
  clear: () => void;
}

export const useCart = create<CartState>((set) => ({
  items: [],
  customerId: null,
  discountPct: 0,
  paymentMethod: "CASH",
  cashReceived: 0,

  add: (product) =>
    set((s) => {
      const existing = s.items.find((i) => i.product.id === product.id);
      if (existing) {
        return {
          items: s.items.map((i) =>
            i.product.id === product.id ? { ...i, qty: i.qty + 1 } : i,
          ),
        };
      }
      return {
        items: [...s.items, { product, qty: 1, unitPrice: product.selling_price, taxRate: product.tax_rate }],
      };
    }),

  setQty: (productId, qty) =>
    set((s) => ({
      items:
        qty <= 0
          ? s.items.filter((i) => i.product.id !== productId)
          : s.items.map((i) => (i.product.id === productId ? { ...i, qty } : i)),
    })),

  remove: (productId) =>
    set((s) => ({ items: s.items.filter((i) => i.product.id !== productId) })),

  setCustomer: (customerId) => set({ customerId }),
  setDiscount: (discountPct) => set({ discountPct }),
  setPayment: (paymentMethod) => set({ paymentMethod }),
  setCashReceived: (cashReceived) => set({ cashReceived }),
  clear: () => set({ items: [], customerId: null, discountPct: 0, paymentMethod: "CASH", cashReceived: 0 }),
}));
```

## 10.3 Pricing helpers — `frontend/src/utils/pricing.ts`

The **same math as the backend** (`_calculate` in Phase 7), mirrored in the frontend so the cashier sees live totals *before* the sale exists:

```ts
import { round2 } from "./format";

export interface PriceLine {
  qty: number;
  unitPrice: number;
  taxRate: number;
}

export function lineTotal(qty: number, unitPrice: number): number {
  return round2(qty * unitPrice);
}

export function computeTotals(lines: PriceLine[], discountPct: number) {
  const subtotal = round2(lines.reduce((s, l) => s + l.qty * l.unitPrice, 0));
  const discount = round2(subtotal * discountPct / 100);
  const tax = round2(
    lines.reduce((s, l) => s + l.qty * l.unitPrice * (1 - discountPct / 100) * l.taxRate / 100, 0),
  );
  const total = round2(subtotal - discount + tax);
  return { subtotal, discount, tax, total };
}
```

> ⚠️ The backend is the authority. The frontend preview may differ by a fraction of a paisa in pathological cases (float vs Decimal); the *saved* sale always uses backend math.

## 10.4 The Billing page — `pages/BillingPage.tsx`

The full POS screen (abridged here; complete version in the Source Code Reference):

```tsx
import { useEffect, useMemo, useRef, useState } from "react";
import { Badge } from "../components/ui/Badge";
import { Button } from "../components/ui/Button";
import { Input } from "../components/ui/Input";
import { Modal } from "../components/ui/Modal";
import { Select } from "../components/ui/Select";
import { useDebounce } from "../hooks/useDebounce";
import { customersApi } from "../services/customers";
import { productsApi } from "../services/products";
import { salesApi } from "../services/sales";
import { useCart } from "../store/cart";
import { toast } from "../store/toast";
import type { Customer, Product } from "../types";
import { formatMoney } from "../utils/format";
import { computeTotals } from "../utils/pricing";

const PAYMENT_METHODS = ["CASH", "UPI", "CARD", "CREDIT"] as const;

export function BillingPage() {
  const cart = useCart();
  const [search, setSearch] = useState("");
  const [products, setProducts] = useState<Product[]>([]);
  const [customers, setCustomers] = useState<Customer[]>([]);
  const [completed, setCompleted] = useState<{ invoice_no: string; total: number } | null>(null);
  const [submitting, setSubmitting] = useState(false);
  const barcodeRef = useRef<HTMLInputElement>(null);
  const debounced = useDebounce(search, 200);

  // keep the barcode/search input focused (scanner wedge = fast typing)
  useEffect(() => {
    const onKey = (e: KeyboardEvent) => {
      if (e.key === "/" && document.activeElement !== barcodeRef.current) {
        e.preventDefault();
        barcodeRef.current?.focus();
      }
    };
    window.addEventListener("keydown", onKey);
    return () => window.removeEventListener("keydown", onKey);
  }, []);

  useEffect(() => {
    productsApi.list({ search: debounced || undefined, size: 50 })
      .then((r) => setProducts(r.items))
      .catch(() => {/* ignore — search refines on every keystroke */});
  }, [debounced]);

  useEffect(() => {
    customersApi.list({ size: 200 }).then(setCustomers).catch(() => {});
  }, []);

  const totals = computeTotals(
    cart.items.map((i) => ({ qty: i.qty, unitPrice: i.unitPrice, taxRate: i.taxRate })),
    cart.discountPct,
  );

  function handleBarcodeOrSearch(e: React.FormEvent) {
    e.preventDefault();
    // exact barcode match first, then name/SKU search, else first result
    const term = search.trim();
    if (!term) return;
    const hit =
      products.find((p) => p.barcode === term) ??
      products.find((p) => p.sku === term) ??
      products.find((p) => p.name.toLowerCase().startsWith(term.toLowerCase()));
    if (hit) {
      cart.add(hit);
      setSearch("");
      barcodeRef.current?.focus();
    } else {
      toast.info(`No product for "${term}"`);
    }
  }

  async function completeSale() {
    if (cart.items.length === 0) return;
    setSubmitting(true);
    try {
      const sale = await salesApi.create({
        customer_id: cart.customerId,
        discount_pct: cart.discountPct,
        items: cart.items.map((i) => ({
          product_id: i.product.id,
          quantity: i.qty,
          unit_price: i.unitPrice,
          tax_rate: i.taxRate,
        })),
        payments: [{ method: cart.paymentMethod, amount: totals.total }],
      });
      setCompleted({ invoice_no: sale.invoice_no, total: sale.total });
      cart.clear();
    } catch (e) {
      toast.error((e as Error).message);
    } finally {
      setSubmitting(false);
    }
  }

  return (
    <div className="grid h-full grid-cols-5 gap-4">
      {/* LEFT: product picker */}
      <div className="col-span-3 space-y-3">
        <form onSubmit={handleBarcodeOrSearch} className="flex gap-2">
          <div className="flex-1">
            <Input ref={barcodeRef} autoFocus placeholder="Scan barcode or search… ( / to focus )"
              value={search} onChange={(e) => setSearch(e.target.value)} />
          </div>
          <Button type="submit">Add</Button>
        </form>

        <div className="grid max-h-[calc(100vh-220px)] grid-cols-3 gap-2 overflow-y-auto">
          {products.map((p) => (
            <button
              key={p.id}
              disabled={p.current_stock <= 0}
              onClick={() => cart.add(p)}
              className="rounded-xl border border-slate-200 bg-white p-3 text-left transition
                hover:border-emerald-400 hover:shadow disabled:cursor-not-allowed disabled:opacity-40"
            >
              <div className="truncate text-sm font-semibold text-slate-800">{p.name}</div>
              <div className="mt-1 flex items-center justify-between">
                <span className="text-sm font-bold text-emerald-700">{formatMoney(p.selling_price)}</span>
                <Badge tone={p.current_stock <= 0 ? "danger" : "neutral"}>stock {p.current_stock}</Badge>
              </div>
            </button>
          ))}
        </div>
      </div>

      {/* RIGHT: cart */}
      <div className="col-span-2 flex flex-col rounded-xl border border-slate-200 bg-white p-4">
        <h2 className="mb-3 text-lg font-bold text-slate-800">Cart</h2>

        <div className="max-h-64 flex-1 space-y-2 overflow-y-auto">
          {cart.items.length === 0 && (
            <p className="py-10 text-center text-sm text-slate-400">Scan or click products to add…</p>
          )}
          {cart.items.map((i) => (
            <div key={i.product.id} className="flex items-center gap-2 rounded-lg bg-slate-50 p-2">
              <div className="min-w-0 flex-1">
                <div className="truncate text-sm font-medium">{i.product.name}</div>
                <div className="text-xs text-slate-500">{formatMoney(i.unitPrice)} × {i.qty}</div>
              </div>
              <button className="rounded bg-slate-200 px-2" onClick={() => cart.setQty(i.product.id, i.qty - 1)}>−</button>
              <span className="w-8 text-center text-sm font-semibold">{i.qty}</span>
              <button className="rounded bg-slate-200 px-2" onClick={() => cart.setQty(i.product.id, i.qty + 1)}>+</button>
              <span className="w-16 text-right text-sm font-bold">{formatMoney(computeTotals([{ qty: i.qty, unitPrice: i.unitPrice, taxRate: i.taxRate }], 0).total)}</span>
              <button className="ml-1 text-rose-500" onClick={() => cart.remove(i.product.id)}>✕</button>
            </div>
          ))}
        </div>

        <div className="mt-3 space-y-2 border-t border-slate-200 pt-3">
          <Select label="Customer (credit/Khata)" value={cart.customerId ?? ""}
            onChange={(e) => cart.setCustomer(e.target.value ? Number(e.target.value) : null)}>
            <option value="">Walk-in customer</option>
            {customers.map((c) => <option key={c.id} value={c.id}>{c.name}</option>)}
          </Select>

          <div className="flex items-center justify-between text-sm">
            <span className="text-slate-600">Discount %</span>
            <input type="number" min={0} max={99} value={cart.discountPct}
              onChange={(e) => cart.setDiscount(Number(e.target.value))}
              className="w-20 rounded border border-slate-300 px-2 py-1 text-right" />
          </div>

          <div className="flex gap-1">
            {PAYMENT_METHODS.map((m) => (
              <button key={m}
                onClick={() => cart.setPayment(m)}
                className={`flex-1 rounded-lg border px-2 py-1.5 text-xs font-semibold transition
                  ${cart.paymentMethod === m ? "border-emerald-500 bg-emerald-50 text-emerald-700" : "border-slate-200 text-slate-600 hover:bg-slate-50"}`}>
                {m}
              </button>
            ))}
          </div>

          <div className="space-y-1 border-t border-slate-200 pt-2 text-sm">
            <div className="flex justify-between text-slate-600"><span>Subtotal</span><span>{formatMoney(totals.subtotal)}</span></div>
            <div className="flex justify-between text-slate-600"><span>Discount</span><span>−{formatMoney(totals.discount)}</span></div>
            <div className="flex justify-between text-slate-600"><span>Tax</span><span>{formatMoney(totals.tax)}</span></div>
            <div className="flex justify-between text-base font-bold text-slate-900">
              <span>Total</span><span>{formatMoney(totals.total)}</span>
            </div>
          </div>

          <Button className="w-full py-3 text-base" loading={submitting}
            disabled={cart.items.length === 0} onClick={completeSale}>
            Complete Sale
          </Button>
        </div>
      </div>

      {/* success modal */}
      <Modal open={!!completed} onClose={() => setCompleted(null)} title="Sale completed 🎉">
        {completed && (
          <div className="space-y-4 text-center">
            <p className="text-sm text-slate-600">Invoice <b>{completed.invoice_no}</b> for
              <b> {formatMoney(completed.total)}</b></p>
            <div className="flex justify-center gap-2">
              <a className="rounded-lg bg-emerald-600 px-4 py-2 text-sm font-semibold text-white"
                href={`${import.meta.env.VITE_API_URL ?? "http://127.0.0.1:8000"}/api/sales/${completed.invoice_no ? "" : ""}`}
                target="_blank" rel="noreferrer">Print invoice</a>
              <Button variant="secondary" onClick={() => setCompleted(null)}>New sale</Button>
            </div>
          </div>
        )}
      </Modal>
    </div>
  );
}
```

> **Note on the invoice link:** the final code links to `GET /api/sales/{saleId}/invoice`. In the complete source we pass the created sale's **id** (the success state stores `saleId`), because the API route is keyed by id. Read the full version in the Source Code Reference — and watch for this exact detail, it's a classic off-by-one between invoice numbers and ids.

## ✏️ Exercise 10.1 — cash received / change

Add a "Cash received" input visible only when the payment method is CASH, and show **Change to return = cashReceived − total**. (Hint: reuse `cart.cashReceived` and `cart.setCashReceived`.)

<details>
<summary><b>Solution sketch</b></summary>

```tsx
{cart.paymentMethod === "CASH" && (
  <div className="flex items-center justify-between text-sm">
    <span className="text-slate-600">Cash received</span>
    <input type="number" min={0} value={cart.cashReceived || ""}
      onChange={(e) => cart.setCashReceived(Number(e.target.value))}
      className="w-24 rounded border border-slate-300 px-2 py-1 text-right" />
  </div>
)}
{cart.paymentMethod === "CASH" && cart.cashReceived > 0 && (
  <div className="flex justify-between text-sm font-semibold text-emerald-700">
    <span>Change</span><span>{formatMoney(cart.cashReceived - totals.total)}</span>
  </div>
)}
```

</details>

---

## ✅ Phase 10 Checkpoint

- [ ] Products appear as clickable cards; click → adds to cart (qty 1, then +1 on repeat)
- [ ] Barcode input: type a barcode, Enter → adds product and clears the input
- [ ] Qty +/− and remove work; totals update live; discount % updates subtotal/discount/tax/total
- [ ] Complete Sale → success modal, cart clears, stock reduced (check backend)
- [ ] Invalid (deactivated/out-of-stock) products can't be added
- [ ] Exercise 10.1: change calculation shows correctly

Commit:

```bash
git add -A
git commit -m "feat: add POS billing screen with cart and live totals"
```

---

# Phase 11 — Purchases

> **Goal of this phase:** record money going *out* — buying stock from a supplier — and let that purchase flow into inventory automatically.

## 11.1 Problem & concept

A purchase has two consequences that must happen **together** (same transaction):

```text
Purchase → Purchase Items → Payment → Inventory Movement (PURCHASE, +qty) → Avg cost update → COMMIT
```

and a business consequence tracked for Phase 13:

```text
Supplier liability = Purchase total − amount paid   (what we still owe)
```

If we buy 50 units of Tata Salt at ₹22 and pay only ₹1,000: stock +50, avg cost updates, and the supplier now shows an outstanding balance of ₹1,100.

### Decision (recorded): trade discounts

We deliberately skip a discount field on purchases — trade discounts in retail are normally reflected in the **unit cost** the buyer actually pays (a "12% off the ₹25 list" deal simply means you enter unit cost 22.00). This keeps the purchase flow simpler. If you need a purchase-level discount later, the pattern to add it is identical to sales' `discount_pct`.

## 11.2 Backend — `backend/app/schemas/purchase.py`

```python
from datetime import datetime
from decimal import Decimal

from pydantic import Field

from .common import ORMModel, Paginated
from ..models.enums import PaymentMethod, PurchaseStatus


class PurchaseItemIn(ORMModel):
    product_id: int
    quantity: Decimal = Field(gt=0, max_digits=12, decimal_places=2)
    unit_cost: Decimal = Field(gt=0, max_digits=12, decimal_places=2)
    tax_rate: Decimal = Field(default=0, ge=0, le=100, max_digits=5, decimal_places=2)


class PurchaseCreate(ORMModel):
    supplier_id: int | None = None
    purchase_date: datetime | None = None
    discount_pct: Decimal = Field(default=0, ge=0, lt=100, max_digits=5, decimal_places=2)
    paid_amount: Decimal = Field(default=0, ge=0, max_digits=12, decimal_places=2)
    payment_method: PaymentMethod = PaymentMethod.CASH
    notes: str | None = Field(default=None, max_length=255)
    items: list[PurchaseItemIn] = Field(min_length=1)


class PurchaseItemRead(ORMModel):
    id: int
    product_id: int
    product_name: str | None = None
    quantity: float
    unit_cost: float
    tax_rate: float
    line_total: float


class PurchaseRead(ORMModel):
    id: int
    purchase_no: str
    supplier_id: int | None
    supplier_name: str | None = None
    purchase_date: datetime
    subtotal: float
    discount_pct: float
    discount: float
    tax: float
    total: float
    paid_amount: float
    payment_method: str
    status: str
    notes: str | None
    created_by: str | None
    items: list[PurchaseItemRead] = []


class PurchasePage(Paginated):
    items: list[PurchaseRead]
```

## 11.3 Service — `backend/app/services/purchase_service.py`

```python
import logging
from decimal import Decimal

from sqlalchemy import select
from sqlalchemy.orm import Session

from app.core.exceptions import NotFoundError, ValidationFailedError
from app.models import (MovementType, Payment, Product, Purchase, PurchaseItem,
                        PurchaseStatus)
from app.schemas.purchase import PurchaseCreate
from app.services import inventory_service
from app.utils.doc_number import next_document_no
from app.utils.money import money, percent
from app.utils.pagination import paginate

logger = logging.getLogger(__name__)


def create_purchase(db: Session, data: PurchaseCreate, user_id: int | None = None) -> Purchase:
    product_ids = list({i.product_id for i in data.items})
    products = {p.id: p for p in db.scalars(select(Product).where(Product.id.in_(product_ids)))}
    missing = set(product_ids) - set(products)
    if missing:
        raise NotFoundError(f"Product(s) not found: {sorted(missing)}")

    discount_pct = percent(data.discount_pct)
    subtotal = money(0)
    tax = money(0)
    lines = []
    for item in data.items:
        product = products[item.product_id]
        qty = money(item.quantity)
        cost = money(item.unit_cost)
        if qty <= 0 or cost < 0:
            raise ValidationFailedError("Quantity and unit cost must be positive")
        line_total = money(qty * cost)
        tax += money(line_total * (1 - discount_pct / 100) * percent(item.tax_rate) / 100)
        subtotal += line_total
        lines.append({"product": product, "qty": qty, "cost": cost,
                      "tax_rate": percent(item.tax_rate), "line_total": line_total})

    subtotal = money(subtotal)
    discount = money(subtotal * discount_pct / 100)
    total = money(subtotal - discount + tax)
    paid = money(data.paid_amount)
    status = PurchaseStatus.COMPLETED if paid >= total else PurchaseStatus.PARTIAL

    purchase_no = next_document_no(db, Purchase, Purchase.purchase_no, "PUR")
    purchase = Purchase(
        purchase_no=purchase_no,
        supplier_id=data.supplier_id,
        purchase_date=data.purchase_date,
        subtotal=subtotal,
        discount_pct=discount_pct,
        discount=discount,
        tax=tax,
        total=total,
        paid_amount=paid,
        payment_method=data.payment_method,
        status=status,
        notes=data.notes,
        created_by_id=user_id,
    )
    db.add(purchase)
    db.flush()

    for line in lines:
        db.add(PurchaseItem(
            purchase_id=purchase.id,
            product_id=line["product"].id,
            quantity=line["qty"],
            unit_cost=line["cost"],
            tax_rate=line["tax_rate"],
            line_total=line["line_total"],
        ))

    if paid > 0:
        db.add(Payment(
            purchase_id=purchase.id,
            amount=paid,
            method=data.payment_method,
            reference=f"{purchase_no} payment",
            created_by_id=user_id,
        ))

    # Inventory: PURCHASE movements (positive) + weighted-average cost update
    for line in lines:
        product = line["product"]
        inventory_service.record_movement(
            db,
            product_id=product.id,
            movement_type=MovementType.PURCHASE,
            quantity=line["qty"],
            unit_cost=line["cost"],
            ref_type="PURCHASE",
            ref_id=purchase.id,
            user_id=user_id,
        )
        inventory_service.apply_purchase_cost(product, line["qty"], line["cost"])
        product.purchase_price = line["cost"]  # keep latest purchase price

    db.commit()
    db.refresh(purchase)
    logger.info("Purchase %s created: total=%s paid=%s", purchase_no, total, paid)
    return purchase


def get_purchase(db: Session, purchase_id: int) -> Purchase:
    purchase = db.get(Purchase, purchase_id)
    if purchase is None:
        raise NotFoundError("Purchase not found")
    return purchase


def list_purchases(
    db: Session,
    from_date=None, to_date=None, supplier_id: int | None = None,
    search: str | None = None, page: int = 1, size: int = 20,
) -> tuple[list[Purchase], int]:
    stmt = select(Purchase).order_by(Purchase.purchase_date.desc())
    if from_date:
        stmt = stmt.where(Purchase.purchase_date >= from_date)
    if to_date:
        stmt = stmt.where(Purchase.purchase_date <= to_date)
    if supplier_id:
        stmt = stmt.where(Purchase.supplier_id == supplier_id)
    if search:
        stmt = stmt.where(Purchase.purchase_no.ilike(f"%{search.strip()}%"))
    return paginate(db, stmt, page, size)
```

Notice: this is the **sales pattern mirrored** — same structure, opposite direction (stock goes *up*, money goes *out*, reference is `PURCHASE` not `SALE`).

## 11.4 Routes — `backend/app/api/routes/purchases.py`

Standard shape: `POST ""` (201), `GET ""` (with `from_date/to_date/supplier_id/search/page/size`), `GET "/{id}"`, and a payment endpoint for later use by the supplier ledger:

```python
@router.post("/{purchase_id}/pay", response_model=PaymentRead)
def pay_purchase(purchase_id: int, body: PurchasePayIn, db: Session = Depends(get_db)) -> PaymentRead:
    payment = purchase_service.record_purchase_payment(db, purchase_id, body, user_id=None)
    return _payment_read(payment)
```

with service:

```python
def record_purchase_payment(db: Session, purchase_id: int, amount: Decimal, method: PaymentMethod, user_id=None) -> Payment:
    purchase = get_purchase(db, purchase_id)
    payment = Payment(purchase_id=purchase.id, amount=money(amount), method=method,
                      reference=f"{purchase.purchase_no} payment", created_by_id=user_id)
    db.add(payment)
    purchase.paid_amount = money(purchase.paid_amount + payment.amount)
    purchase.status = PurchaseStatus.COMPLETED if purchase.paid_amount >= purchase.total else PurchaseStatus.PARTIAL
    db.commit()
    db.refresh(payment)
    return payment
```

## 11.5 Scenario 2 — buy 50 units

Vendor purchases **50 Tata Salt @ ₹22**, pays ₹1,100 cash.

| Layer | What happens |
|---|---|
| **API** | `POST /api/purchases` `{supplier_id, items:[{product_id:1, quantity:50, unit_cost:22}], paid_amount:1100}` |
| **Service** | subtotal 1100, total 1100, paid 1100 → status COMPLETED → `PUR-20260808-0001` |
| **Ledger** | movement `PURCHASE +50 @ 22.00`, ref `PURCHASE/1`; avg cost 22.00; `current_stock` 97→147 |
| **Payments** | +1100 CASH, `purchase_id=1` |
| **Supplier** | liability = 1100 − 1100 = **0** (fully paid) |

Buy a *second* lot later at ₹25 with only ₹500 paid → avg cost becomes `(147×22 + 50×25)/(147+50) = 22.76`; supplier balance = 1250 − 500 = **750**.

## 11.6 Frontend — `pages/PurchasesPage.tsx`

Same pattern as Products: table (purchase no, supplier, date, total, paid, status badge, balance = total − paid), plus a **Create Purchase** modal with dynamic item rows (product select, qty, unit cost → auto line total), supplier select, paid amount + method. Full code in the Source Code Reference; the key dynamic-row pattern:

```tsx
const [lines, setLines] = useState<{ product_id: number | null; quantity: number; unit_cost: number }[]>([
  { product_id: null, quantity: 1, unit_cost: 0 },
]);

function updateLine(idx: number, patch: Partial<typeof lines[number]>) {
  setLines((ls) => ls.map((l, i) => (i === idx ? { ...l, ...patch } : l)));
}
```

`salesApi`-style `purchasesApi.create(...)` posts the same shape the backend expects.

## ✏️ Exercise 11.1 — pay a purchase from the UI

Add a "Record payment" action on the purchases table: a small modal (amount + method) calling `POST /api/purchases/{id}/pay`, then refresh. Verify the status flips from PARTIAL to COMPLETED when fully paid.

<details>
<summary><b>Solution sketch</b></summary>

Reuse the pattern: a `PayModal` with `useState`, on submit `purchasesApi.pay(purchase.id, { amount, method })` → toast + `load()`. The endpoint already exists (11.4).

</details>

---

## ✅ Phase 11 Checkpoint

- [ ] `POST /api/purchases` adds stock: check `GET /api/products/{id}` — `current_stock` increased by exactly the purchased qty
- [ ] `GET /api/inventory/movements?product_id=…` shows `PURCHASE +50` with the correct `unit_cost`
- [ ] Buying at a different price updates `avg_cost` (weighted average) and `purchase_price`
- [ ] Partial payment → status `PARTIAL`; `total − paid_amount` is the supplier balance
- [ ] Frontend: create purchase modal works; status badge + balance visible
- [ ] Exercise 11.1: paying the balance flips status to COMPLETED

### If it doesn't work

| Error | Why | Fix |
|---|---|---|
| Stock didn't change | Movement not recorded, or committed before | Same single-commit discipline as sales (11.3) |
| `avg_cost` wrong | `apply_purchase_cost` used after stock changed incorrectly | Read it again — it subtracts `qty` to recover the pre-purchase stock |
| Payment endpoint 404 | Router not mounted in `main.py` | Add `purchases.router` to `create_app()` |

Commit:

```bash
git add -A
git commit -m "feat: add purchases with inventory increase and supplier payments"
```

---

**Next:** [Phase 12 — Customers and Credit (Khata)](#phase-12--customers-and-credit-khata)
# Phase 12 — Customers and Credit (Khata)

> **Goal of this phase:** customer management with the classic Indian retail feature — **Khata** (the notebook where the shopkeeper records "Ramesh took 3 bags of sugar, will pay Friday"). Done right, this is accounting; done wrong, it's an argument generator.

## 12.1 Problem & concept

A customer who buys on credit creates a **liability for them and an asset for the shop**: money the shop is owed. The notebook approach works until there are 200 customers and one dispute. We need a *single formula* for what each customer owes, derived entirely from the database:

```text
Customer Balance = Σ (sales the customer made)
                 − Σ (real money the customer paid us)
```

- A **sale** on credit **increases** the balance.
- A **cash/UPI/card payment** (toward that sale, or toward old dues) **decreases** it.
- A **refund** is a negative payment — it *increases* the balance back.

### The "credit is not money" rule (important)

A **Payment row represents real money changing hands** — cash, UPI, card, bank. **Credit is not money received**, so the credit portion of a sale is *not* stored as a Payment row. Instead:

- The sale simply has a `customer_id` (who owes) and the payment list contains only what was actually received.
- Example: a ₹100 credit sale → `payments: []` (or one `{method: CREDIT, amount: 0}` that the service ignores). Balance = 100 − 0 = **₹100 owed**.
- Example: customer pays ₹40 now, ₹60 later → sale `payments: [{CASH, 40}]`; balance = 100 − 40 = 60; then a standalone payment `{customer_id, CASH, 60}` → balance = 0.

> ⚠️ This is why the service layer must **filter out `CREDIT` from real payments** when creating a sale — otherwise the balance formula would wrongly count credit as money received. (The final `sale_service` in the Source Code Reference does exactly this.)

## 12.2 Mini-project first: the balance on paper

Before code, take 3 sales and 2 payments and compute balances by hand — you now know the *formula*; the code will just automate it. Do it on paper with: Sale A ₹100 (paid 40), Sale B ₹250 (unpaid), Payment ₹60 against old dues. Balance = 100 + 250 − 40 − 60 = **₹250**.

## 12.3 Service — `backend/app/services/customer_service.py`

```python
from datetime import datetime
from decimal import Decimal

from sqlalchemy import func, select
from sqlalchemy.orm import Session

from app.core.exceptions import NotFoundError
from app.models import Customer, Payment, PaymentMethod, Sale
from app.schemas.customer import CustomerCreate, CustomerUpdate
from app.utils.money import money
from app.utils.pagination import paginate


def create_customer(db: Session, data: CustomerCreate) -> Customer:
    customer = Customer(name=data.name.strip(), phone=data.phone, address=data.address, notes=data.notes)
    db.add(customer)
    db.commit()
    db.refresh(customer)
    return customer


def get_customer(db: Session, customer_id: int) -> Customer:
    customer = db.get(Customer, customer_id)
    if customer is None:
        raise NotFoundError("Customer not found")
    return customer


def list_customers(db: Session, search: str | None = None, page: int = 1, size: int = 20):
    stmt = select(Customer).order_by(Customer.name)
    if search:
        like = f"%{search.strip()}%"
        stmt = stmt.where(Customer.name.ilike(like) | Customer.phone.ilike(like))
    return paginate(db, stmt, page, size)


def update_customer(db: Session, customer_id: int, data: CustomerUpdate) -> Customer:
    customer = get_customer(db, customer_id)
    for field, value in data.model_dump(exclude_unset=True).items():
        if value is not None:
            setattr(customer, field, value)
    db.commit()
    db.refresh(customer)
    return customer


def customer_balance(db: Session, customer_id: int) -> Decimal:
    """What this customer owes us right now.

    balance = Σ sales.total − Σ real payments (cash/upi/card/bank)
    'real payments' = payments for this customer's sales + standalone
    customer payments (both with method != CREDIT). Refunds are negative
    amounts, so they automatically increase the balance.
    """
    sales_total = (
        db.scalar(select(func.coalesce(func.sum(Sale.total), 0)).where(Sale.customer_id == customer_id))
        or Decimal("0")
    )
    payments_total = (
        db.scalar(
            select(func.coalesce(func.sum(Payment.amount), 0)).where(
                Payment.method != PaymentMethod.CREDIT,
                (Payment.customer_id == customer_id) | (Payment.sale_id.in_(
                    select(Sale.id).where(Sale.customer_id == customer_id)
                )),
            )
        )
        or Decimal("0")
    )
    return money(sales_total - payments_total)


def customer_ledger(db: Session, customer_id: int) -> list[dict]:
    """Chronological Khata entries with a running balance."""
    entries: list[dict] = []
    for sale in db.scalars(select(Sale).where(Sale.customer_id == customer_id).order_by(Sale.sale_date)):
        entries.append({
            "date": sale.sale_date, "type": "SALE", "reference": sale.invoice_no,
            "debit": sale.total, "credit": None,
        })
    for p in db.scalars(
        select(Payment)
        .where(Payment.method != PaymentMethod.CREDIT)
        .where((Payment.customer_id == customer_id) | (Payment.sale_id.in_(
            select(Sale.id).where(Sale.customer_id == customer_id)
        )))
        .order_by(Payment.paid_at)
    ):
        entries.append({
            "date": p.paid_at, "type": "PAYMENT", "reference": p.reference or "",
            "debit": None if p.amount > 0 else -p.amount,   # refunds show as debit
            "credit": p.amount if p.amount > 0 else None,
        })

    entries.sort(key=lambda e: e["date"])
    running = Decimal("0")
    for e in entries:
        running += (e["debit"] or Decimal("0")) - (e["credit"] or Decimal("0"))
        e["balance"] = money(running)
    return entries


def record_customer_payment(db: Session, customer_id: int, amount: Decimal,
                            method: PaymentMethod, reference: str | None, user_id=None) -> Payment:
    """Standalone payment: customer settling old dues (no sale involved)."""
    customer = get_customer(db, customer_id)
    payment = Payment(customer_id=customer.id, amount=money(amount), method=method,
                      reference=reference, created_by_id=user_id)
    db.add(payment)
    db.commit()
    db.refresh(payment)
    return payment


def outstanding_customers(db: Session, limit: int = 20) -> list[dict]:
    """Customers with balance > 0, most owed first (drives reports + alerts)."""
    result = []
    for c in db.scalars(select(Customer).where(Customer.is_active.is_(True))):
        bal = customer_balance(db, c.id)
        if bal > 0:
            result.append({"id": c.id, "name": c.name, "phone": c.phone, "balance": bal})
    result.sort(key=lambda r: r["balance"], reverse=True)
    return result[:limit]
```

Explain:

- `customer_balance` is a **pure query**, no stored column — it can never drift out of sync because it's always computed from source rows. (For thousands of customers you'd cache it; for a shop, per-request computation is instant.)
- The `method != CREDIT` filter implements the "credit is not money" rule.
- `customer_ledger` merges sales and payments chronologically with a **running balance** — the Khata page.

## 12.4 Routes — `backend/app/api/routes/customers.py`

CRUD + balance + ledger + payments:

```python
@router.get("/{customer_id}/balance")
def balance(customer_id: int, db: Session = Depends(get_db)) -> dict:
    bal = customer_service.customer_balance(db, customer_id)
    return {"customer_id": customer_id, "balance": float(bal)}

@router.get("/{customer_id}/ledger")
def ledger(customer_id: int, db: Session = Depends(get_db)) -> dict:
    return {"entries": customer_service.customer_ledger(db, customer_id)}

@router.post("/{customer_id}/payments", status_code=status.HTTP_201_CREATED)
def add_payment(customer_id: int, body: CustomerPaymentIn, db: Session = Depends(get_db)) -> PaymentRead:
    payment = customer_service.record_customer_payment(
        db, customer_id, body.amount, body.method, body.reference, user_id=None,
    )
    return _payment_read(payment)
```

`CustomerPaymentIn`: `{amount: Decimal(gt=0), method, reference?}`.

## 12.5 Scenario 3 — a credit sale, end to end

Ramesh buys ₹500 of groceries, pays nothing (Khata).

| Layer | What happens |
|---|---|
| **Frontend** | customer "Ramesh" selected; payment method **CREDIT** → the cart sends `payments: []` (credit portion never becomes a Payment row) |
| **API** | `POST /api/sales` `{customer_id: 1, items: [...], payments: []}` |
| **Service** | sale created with `customer_id=1`; stock decreases; **no payment row** |
| **Balance** | `balance(1)` = 500 − 0 = **₹500** |
| **Ledger** | `SALE INV-… +500` → balance 500 |

Later Ramesh pays ₹200 cash → `POST /api/customers/1/payments {amount: 200, method: CASH}` → ledger gets `PAYMENT 200 → balance 300`.

## ✏️ Exercise 12.1 — the outstanding-customers report

Add `GET /api/customers/outstanding` (balance > 0, sorted by amount owed) reusing `outstanding_customers`. (Careful: route order — define it *before* `/{customer_id}` or FastAPI will treat "outstanding" as an id.)

<details>
<summary><b>Solution sketch</b></summary>

```python
@router.get("/outstanding")
def outstanding(db: Session = Depends(get_db)) -> list[dict]:
    return customer_service.outstanding_customers(db)
```

If a 422 "value is not a valid integer" appears, you placed it after `/{customer_id}` — move it above.

</details>

---

## ✅ Phase 12 Checkpoint

- [ ] CRUD works; a credit sale creates no Payment row
- [ ] `GET /api/customers/{id}/balance` reflects: credit sale +total, cash payment −amount, refund +amount
- [ ] `GET /api/customers/{id}/ledger` shows SALE/PAYMENT rows with correct running balance
- [ ] Exercise 12.1: outstanding list correct
- [ ] Frontend customers page shows balance per customer + ledger modal (build it with the standard pattern)

Commit:

```bash
git add -A
git commit -m "feat: add customers with Khata ledger and balances"
```

---

# Phase 13 — Suppliers

> **Goal of this phase:** the mirror image of customers — people *we* owe money to.

## 13.1 Concept

```text
Supplier Balance = Σ (purchase totals) − Σ (real money we paid the supplier)
```

Same "real money" rule: a purchase's `paid_amount` becomes a Payment row (real money out); the unpaid portion is what we owe. Standalone payments to a supplier (method != CREDIT) reduce the balance.

## 13.2 Service — `backend/app/services/supplier_service.py`

Identical shape to `customer_service` (create/update/list/get), plus:

```python
def supplier_balance(db: Session, supplier_id: int) -> Decimal:
    purchases_total = (
        db.scalar(select(func.coalesce(func.sum(Purchase.total), 0)).where(Purchase.supplier_id == supplier_id))
        or Decimal("0")
    )
    payments_total = (
        db.scalar(
            select(func.coalesce(func.sum(Payment.amount), 0)).where(
                Payment.method != PaymentMethod.CREDIT,
                (Payment.supplier_id == supplier_id) | (Payment.purchase_id.in_(
                    select(Purchase.id).where(Purchase.supplier_id == supplier_id)
                )),
            )
        )
        or Decimal("0")
    )
    return money(purchases_total - payments_total)


def supplier_ledger(db: Session, supplier_id: int) -> list[dict]:
    # PURCHASE entries (+debit) and PAYMENT entries (−credit), running balance.
    # Same merge-sort pattern as customer_ledger.
    ...


def record_supplier_payment(db: Session, supplier_id: int, amount: Decimal,
                            method: PaymentMethod, reference: str | None, user_id=None) -> Payment:
    payment = Payment(supplier_id=supplier_id, amount=money(amount), method=method,
                      reference=reference, created_by_id=user_id)
    db.add(payment)
    db.commit()
    db.refresh(payment)
    return payment


def outstanding_suppliers(db: Session, limit: int = 20) -> list[dict]:
    # balance > 0, most owed first
    ...
```

Routes mirror customers: `GET /api/suppliers`, `POST`, `PATCH /{id}`, `GET /{id}`, `GET /{id}/balance`, `GET /{id}/ledger`, `POST /{id}/payments`.

## 13.3 Frontend

The Suppliers page is the Customers page with "purchases" instead of "sales": table + balance column + ledger modal + record-payment modal. Build it by adapting `CustomersPage` — this is intentional: the pattern is the point.

## ✏️ Exercise 13.1 — payable report

Add `GET /api/suppliers/outstanding` (we owe money, most owed first) — same pattern as Exercise 12.1.

<details>
<summary><b>Solution sketch</b></summary>

Route before `/{supplier_id}`, reusing `supplier_service.outstanding_suppliers`. 

</details>

---

## ✅ Phase 13 Checkpoint

- [ ] Purchase with partial payment → supplier balance = unpaid amount
- [ ] `POST /api/suppliers/{id}/payments` reduces the balance
- [ ] Ledger shows PURCHASE and PAYMENT rows with running balance
- [ ] Exercise 13.1 done

Commit:

```bash
git add -A
git commit -m "feat: add suppliers with balances and ledger"
```

---

# Phase 14 — Expenses and Profit

> **Goal of this phase:** answer the owner's real question — *"Am I actually making money?"* — with correct accounting.

## 14.1 The profit formula (teach this slowly — it's the product)

```text
Revenue      = Σ sales.total                     (money that came in from selling)
COGS         = Σ movement.quantity × unit_cost   (what that sold stock cost us)
               over SALE movements in the period — the unit_cost snapshot!

Gross Profit  = Revenue − COGS
Expenses      = Σ expenses.amount                (rent, salaries, electricity…)
Net Profit    = Gross Profit − Expenses
```

**Why COGS is derived from movements, not from today's prices:**

Suppose we bought 100 salt packets at ₹21, then 50 more at ₹25. We sell 60 today. What was the cost of those 60? If we used *today's* `avg_cost` (22.76) we'd be guessing at the moment of reporting. Instead, **each SALE movement froze the cost at sale time** (`unit_cost=product.avg_cost` then, Phase 7) — so COGS is a *historical fact*, summed from the ledger:

```sql
SELECT SUM(quantity * unit_cost) FROM inventory_movements
WHERE movement_type = 'SALE' AND created_at BETWEEN :from AND :to;
```

This is the payoff of the snapshot design in Phase 6. Without it, profit reports would be fiction.

## 14.2 Expense service — `backend/app/services/expense_service.py`

Simple CRUD + category list + period totals:

```python
from datetime import datetime

from sqlalchemy import func, select
from sqlalchemy.orm import Session

from app.core.exceptions import NotFoundError
from app.models import Expense
from app.schemas.expense import ExpenseCreate, ExpenseUpdate
from app.utils.money import money
from app.utils.pagination import paginate


def create_expense(db: Session, data: ExpenseCreate, user_id: int | None = None) -> Expense:
    expense = Expense(expense_date=data.expense_date, category=data.category.strip(),
                      amount=money(data.amount), description=data.description,
                      created_by_id=user_id)
    db.add(expense)
    db.commit()
    db.refresh(expense)
    return expense


def list_expenses(db: Session, from_date=None, to_date=None, category: str | None = None,
                  page: int = 1, size: int = 50):
    stmt = select(Expense).order_by(Expense.expense_date.desc())
    if from_date:
        stmt = stmt.where(Expense.expense_date >= from_date)
    if to_date:
        stmt = stmt.where(Expense.expense_date <= to_date)
    if category:
        stmt = stmt.where(Expense.category == category)
    return paginate(db, stmt, page, size)


def expense_categories(db: Session) -> list[str]:
    rows = db.execute(select(Expense.category).distinct().order_by(Expense.category)).all()
    return [r[0] for r in rows]


def expense_total(db: Session, from_date, to_date) -> Decimal:
    return (
        db.scalar(
            select(func.coalesce(func.sum(Expense.amount), 0)).where(
                Expense.expense_date >= from_date, Expense.expense_date <= to_date
            )
        )
        or Decimal("0")
    )
```

> **Expense categories decision:** categories are free-text with a suggested list in the UI (Rent, Salaries, Electricity, Internet, Transport, Miscellaneous, …). A separate `expense_categories` table would be cleaner, but free text + a `DISTINCT` query gives the same UX with one less table — and shops invent categories you didn't foresee.

## 14.3 The profit report — in `report_service` (used by reports AND dashboard)

`backend/app/services/report_service.py` (this is the shared financial engine):

```python
from datetime import datetime, time
from decimal import Decimal

from sqlalchemy import func, select
from sqlalchemy.orm import Session

from app.models import Expense, InventoryMovement, MovementType, Sale
from app.utils.money import money


def _day_bounds(dt: datetime) -> tuple[datetime, datetime]:
    start = datetime.combine(dt.date(), time.min)
    end = datetime.combine(dt.date(), time.max)
    return start, end


def revenue(db: Session, from_dt: datetime, to_dt: datetime) -> Decimal:
    return (
        db.scalar(
            select(func.coalesce(func.sum(Sale.total), 0)).where(
                Sale.sale_date >= from_dt, Sale.sale_date <= to_dt
            )
        )
        or Decimal("0")
    )


def cogs(db: Session, from_dt: datetime, to_dt: datetime) -> Decimal:
    """Cost of goods sold: SALE movements × their frozen unit_cost."""
    return (
        db.scalar(
            select(func.coalesce(func.sum(InventoryMovement.quantity * InventoryMovement.unit_cost), 0)).where(
                InventoryMovement.movement_type == MovementType.SALE,
                InventoryMovement.created_at >= from_dt,
                InventoryMovement.created_at <= to_dt,
            )
        )
        or Decimal("0")
    )


def expenses_total(db: Session, from_dt: datetime, to_dt: datetime) -> Decimal:
    return (
        db.scalar(
            select(func.coalesce(func.sum(Expense.amount), 0)).where(
                Expense.expense_date >= from_dt, Expense.expense_date <= to_dt
            )
        )
        or Decimal("0")
    )


def profit_summary(db: Session, from_dt: datetime, to_dt: datetime) -> dict:
    rev = money(revenue(db, from_dt, to_dt))
    cost = money(cogs(db, from_dt, to_dt))
    exp = money(expenses_total(db, from_dt, to_dt))
    gross = money(rev - cost)
    net = money(gross - exp)
    return {
        "from": from_dt.isoformat(), "to": to_dt.isoformat(),
        "revenue": float(rev), "cogs": float(cost), "gross_profit": float(gross),
        "expenses": float(exp), "net_profit": float(net),
    }
```

Note the small inconsistency we accept and document: revenue uses `sale.sale_date`, COGS uses the movement's `created_at`. They are set within the same transaction, so they only diverge if a sale's date is edited — acceptable, and worth knowing about.

## 14.4 Routes — `backend/app/api/routes/expenses.py`

Standard CRUD + `GET /api/expenses/categories` + `GET /api/expenses/summary?from=&to=` (returns `{total}`).

## 14.5 Real-world scenario — profit math with real numbers

| Metric | Value | From |
|---|---|---|
| Sales (7 days) | ₹42,500 | `SUM(sales.total)` |
| COGS (7 days) | ₹30,900 | SALE movements × unit_cost |
| **Gross profit** | **₹11,600** | 42,500 − 30,900 |
| Expenses (rent+salary+power) | ₹7,800 | `SUM(expenses.amount)` |
| **Net profit** | **₹3,800** | 11,600 − 7,800 |

The owner finally knows: **3,800 on 42,500 sales = an 8.9% net margin.** That number is why this app exists.

---

## ✅ Phase 14 Checkpoint

- [ ] `POST /api/expenses` + list + categories + summary all work
- [ ] `GET /api/reports/profit?from=…&to=…` returns revenue/cogs/gross/expenses/net — and the numbers match hand computation from the raw tables
- [ ] Sell one unit of Tata Salt (cost 22, price 28): gross profit for that day = **₹6** exactly

### If it doesn't work

| Error | Why | Fix |
|---|---|---|
| COGS is 0 | No SALE movements in range, or you filtered on the wrong column | Movements are stamped `created_at`; verify range |
| Profit seems too high | Discount not reflected in revenue | `Sale.total` already nets discount — check you're summing `total`, not `subtotal` |
| Negative net profit | Expenses exceed gross — *correct* | It's a report, not a bug 😄 |

Commit:

```bash
git add -A
git commit -m "feat: add expenses and profit calculation engine"
```

---

# Phase 15 — Dashboard

> **Goal of this phase:** the owner's morning screen. **Every number must come from the database** — no hardcoding, no placeholder data.

## 15.1 The metrics and where each comes from

| Card/Chart | Formula | Source |
|---|---|---|
| Today's sales | `SUM(total)` where `sale_date` is today | sales |
| Today's profit | today's revenue − today's COGS | sales + movements |
| Today's transactions | `COUNT(sales)` today | sales |
| Low-stock products | `current_stock <= min_stock`, active | products |
| Top-selling products | `SUM(qty)` of SALE movements, last 30 days, top 5 | movements |
| Recent sales | latest 5 sales with invoice no, total, time | sales |
| Revenue last 14 days | one `SUM` per day | sales |
| Expenses last 14 days | one `SUM` per day | expenses |
| Profit last 14 days | per-day revenue − per-day COGS | computed |

## 15.2 Service — `backend/app/services/dashboard_service.py`

```python
from datetime import datetime, timedelta

from sqlalchemy import func, select
from sqlalchemy.orm import Session

from app.models import Expense, InventoryMovement, MovementType, Product, Sale
from app.services import inventory_service, report_service
from app.utils.money import money


def _range_for(days: int) -> tuple[datetime, datetime]:
    start = datetime.now().replace(hour=0, minute=0, second=0, microsecond=0)
    return start - timedelta(days=days - 1), datetime.now()


def daily_series(db: Session, days: int, metric: str) -> list[dict]:
    """Per-day values for the last N days: metric in {revenue, expenses}."""
    start, _ = _range_for(days)
    rows: dict[str, float] = {}
    for i in range(days):
        day = start + timedelta(days=i)
        rows[day.strftime("%Y-%m-%d")] = 0.0

    if metric == "revenue":
        query = (select(func.date(Sale.sale_date), func.sum(Sale.total))
                 .where(Sale.sale_date >= start).group_by(func.date(Sale.sale_date)))
    else:  # expenses
        query = (select(func.date(Expense.expense_date), func.sum(Expense.amount))
                 .where(Expense.expense_date >= start).group_by(func.date(Expense.expense_date)))

    for day, total in db.execute(query):
        if day in rows:
            rows[day] = float(total)
    return [{"date": d, "value": v} for d, v in rows.items()]


def top_products(db: Session, days: int = 30, limit: int = 5) -> list[dict]:
    start, _ = _range_for(days)
    rows = db.execute(
        select(InventoryMovement.product_id, func.sum(-InventoryMovement.quantity).label("sold"))
        .where(InventoryMovement.movement_type == MovementType.SALE,
               InventoryMovement.created_at >= start)
        .group_by(InventoryMovement.product_id)
        .order_by(func.sum(-InventoryMovement.quantity).desc())
        .limit(limit)
    ).all()
    result = []
    for pid, sold in rows:
        product = db.get(Product, pid)
        if product:
            result.append({"product_id": pid, "name": product.name, "sold": float(sold)})
    return result


def summary(db: Session) -> dict:
    today_start = datetime.now().replace(hour=0, minute=0, second=0, microsecond=0)
    now = datetime.now()

    today_revenue = report_service.revenue(db, today_start, now)
    today_cogs = report_service.cogs(db, today_start, now)
    today_txns = db.scalar(select(func.count()).select_from(Sale).where(Sale.sale_date >= today_start)) or 0

    profit_series = []
    revenue_series = daily_series(db, 14, "revenue")
    expense_series = daily_series(db, 14, "expenses")
    for r in revenue_series:
        day = datetime.fromisoformat(r["date"])
        day_cogs = report_service.cogs(db, day, day.replace(hour=23, minute=59, second=59))
        profit_series.append({"date": r["date"], "value": float(money(r["value"] - day_cogs))})

    recent = db.scalars(
        select(Sale).order_by(Sale.sale_date.desc()).limit(5)
    ).all()

    return {
        "today": {
            "revenue": float(today_revenue),
            "profit": float(money(today_revenue - today_cogs)),
            "transactions": today_txns,
        },
        "low_stock": [
            {"id": p.id, "name": p.name, "current_stock": p.current_stock, "min_stock": p.min_stock}
            for p in inventory_service.low_stock_products(db)
        ],
        "top_products": top_products(db),
        "recent_sales": [
            {"id": s.id, "invoice_no": s.invoice_no, "total": s.total, "sale_date": s.sale_date,
             "customer_name": s.customer.name if s.customer else None}
            for s in recent
        ],
        "revenue_series": revenue_series,
        "expense_series": expense_series,
        "profit_series": profit_series,
    }
```

> The per-day COGS query inside the loop is fine for 14 days on a shop-sized database. If it ever got slow, we'd batch it into one `GROUP BY date` query — noted for later optimization, not a problem now.

Route — `backend/app/api/routes/dashboard.py`:

```python
@router.get("/summary")
def summary(db: Session = Depends(get_db)) -> dict:
    return dashboard_service.summary(db)
```

## 15.3 Frontend — the Dashboard page

Cards + two small **self-made SVG charts** (we don't add a chart library — a bar/line chart is 40 lines and keeps the bundle small; this also demystifies charts).

`pages/DashboardPage.tsx` (abridged — full code in reference):

```tsx
import { useEffect, useState } from "react";
import { StatCard } from "../components/ui/StatCard";
import { dashboardApi } from "../services/dashboard";
import type { DashboardSummary } from "../types";
import { formatMoney } from "../utils/format";

export function DashboardPage() {
  const [data, setData] = useState<DashboardSummary | null>(null);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    dashboardApi.summary().then(setData).catch((e: Error) => setError(e.message));
  }, []);

  if (error) return <div className="text-rose-600">{error}</div>;
  if (!data) return <div className="text-slate-400">Loading dashboard…</div>;

  return (
    <div className="space-y-6">
      <div className="grid grid-cols-3 gap-4">
        <StatCard label="Today's Sales" value={formatMoney(data.today.revenue)} />
        <StatCard label="Today's Profit" value={formatMoney(data.today.profit)} tone={data.today.profit >= 0 ? "green" : "red"} />
        <StatCard label="Transactions Today" value={String(data.today.transactions)} />
      </div>

      <div className="grid grid-cols-2 gap-4">
        <SimpleBarChart title="Revenue (14 days)" data={data.revenue_series} />
        <SimpleBarChart title="Profit (14 days)" data={data.profit_series} tone={data.profit_series.every((p) => p.value >= 0) ? "green" : "red"} />
      </div>

      {data.low_stock.length > 0 && (
        <div className="rounded-xl border border-amber-200 bg-amber-50 p-4">
          <h3 className="font-bold text-amber-800">⚠️ Low stock ({data.low_stock.length})</h3>
          <ul className="mt-2 space-y-1 text-sm text-amber-900">
            {data.low_stock.map((p) => (
              <li key={p.id}>{p.name} — {p.current_stock} left (min {p.min_stock})</li>
            ))}
          </ul>
        </div>
      )}

      {/* recent sales table + top products list — standard DataTable pattern */}
    </div>
  );
}
```

`SimpleBarChart` (the 40-line chart):

```tsx
interface Point { date: string; value: number }

export function SimpleBarChart({ title, data, tone = "green" }: { title: string; data: Point[]; tone?: "green" | "red" }) {
  const max = Math.max(...data.map((d) => d.value), 1);
  const color = tone === "green" ? "bg-emerald-500" : "bg-rose-500";
  return (
    <div className="rounded-xl border border-slate-200 bg-white p-4">
      <h3 className="mb-3 text-sm font-semibold text-slate-700">{title}</h3>
      <div className="flex h-32 items-end gap-1">
        {data.map((d) => (
          <div key={d.date} className="group relative flex-1">
            <div
              className={`${color} rounded-t transition-all hover:opacity-80`}
              style={{ height: `${Math.max((d.value / max) * 100, 2)}%` }}
              title={`${d.date}: ${d.value}`}
            />
          </div>
        ))}
      </div>
      <div className="mt-1 flex justify-between text-[10px] text-slate-400">
        <span>{data[0]?.date.slice(5)}</span>
        <span>{data[data.length - 1]?.date.slice(5)}</span>
      </div>
    </div>
  );
}
```

Add the matching `DashboardSummary` type to `types/index.ts` (mirror the service's return dict) and `services/dashboard.ts`.

## ✏️ Exercise 15.1 — a "Today's top product" card

The dashboard shows top products over 30 days. Add a second card for **today's** top product using `top_products(db, days=1, limit=1)`. (Hint: add a `today_top` key to the summary dict and render it as a StatCard.)

---

## ✅ Phase 15 Checkpoint

- [ ] Dashboard shows real numbers that change when you create a sale / expense / purchase
- [ ] Today's profit for a single Tata Salt sale = exactly ₹6 (28 − 22) plus tax if set
- [ ] Low-stock alert appears after setting `min_stock` above current stock
- [ ] Revenue/expense/profit 14-day charts render and update
- [ ] Exercise 15.1 done

### If it doesn't work

| Error | Why | Fix |
|---|---|---|
| Dashboard shows 0 everywhere | `/api/dashboard/summary` not mounted, or date filters exclude data | Check router in `main.py`; check `sale_date` vs your "today" |
| Charts all equal height | `max` is 0 → division guard uses 1 | Fine — it means no data |
| Profit series ignores expenses | Profit = revenue − COGS; expenses are a *separate* line | That's correct — net profit = gross − expenses (Phase 14) |

Commit:

```bash
git add -A
git commit -m "feat: add dashboard with live metrics and charts"
```

---

**Next:** [Phase 16 — Reports](#phase-16--reports)
# Phase 16 — Reports

> **Goal of this phase:** turn raw tables into answers. Eleven report types, all filterable by date range, all exportable to CSV.

## 16.1 Concept: aggregation queries (mini-project first)

Before the reports, prove the tool. In `sqlite3` (or Python):

```python
from app.database.database import engine
from sqlalchemy import text

with engine.connect() as conn:
    rows = conn.execute(text(
        "SELECT date(sale_date) AS day, count(*) AS txns, sum(total) AS revenue "
        "FROM sales WHERE sale_date >= :d GROUP BY day ORDER BY day"
    ), {"d": "2026-08-01"})
    print(rows.all())
```

That one query *is* the daily sales report. Every report in this phase is a `GROUP BY` + `SUM/COUNT` with a `WHERE` on date. Master this pattern and reports are easy.

## 16.2 The report service — extend `backend/app/services/report_service.py`

```python
from datetime import date, datetime, timedelta
from decimal import Decimal

from sqlalchemy import func, select
from sqlalchemy.orm import Session

from app.models import (Customer, Expense, InventoryMovement, MovementType,
                        Product, Purchase, Sale, Supplier)
from app.services import inventory_service
from app.utils.money import money

# --- helpers already written in Phase 14: revenue, cogs, expenses_total, profit_summary


def sales_daily(db: Session, from_dt: datetime, to_dt: datetime) -> list[dict]:
    rows = db.execute(
        select(func.date(Sale.sale_date), func.count(Sale.id), func.sum(Sale.total))
        .where(Sale.sale_date >= from_dt, Sale.sale_date <= to_dt)
        .group_by(func.date(Sale.sale_date))
        .order_by(func.date(Sale.sale_date))
    ).all()
    return [
        {"date": d, "transactions": n, "revenue": float(money(t))}
        for d, n, t in rows
    ]


def sales_monthly(db: Session, from_dt: datetime, to_dt: datetime) -> list[dict]:
    rows = db.execute(
        select(func.strftime("%Y-%m", Sale.sale_date), func.count(Sale.id), func.sum(Sale.total))
        .where(Sale.sale_date >= from_dt, Sale.sale_date <= to_dt)
        .group_by(func.strftime("%Y-%m", Sale.sale_date))
        .order_by(func.strftime("%Y-%m", Sale.sale_date))
    ).all()
    return [{"month": m, "transactions": n, "revenue": float(money(t))} for m, n, t in rows]


def product_sales(db: Session, from_dt: datetime, to_dt: datetime) -> list[dict]:
    """Per product: units sold and revenue, from sale_items joined to sales."""
    from app.models import SaleItem
    rows = db.execute(
        select(
            SaleItem.product_id,
            func.sum(SaleItem.quantity).label("units"),
            func.sum(SaleItem.line_total).label("amount"),
        )
        .join(Sale, Sale.id == SaleItem.sale_id)
        .where(Sale.sale_date >= from_dt, Sale.sale_date <= to_dt,
               Sale.status != "RETURNED")
        .group_by(SaleItem.product_id)
        .order_by(func.sum(SaleItem.quantity).desc())
    ).all()
    result = []
    for pid, units, amount in rows:
        product = db.get(Product, pid)
        result.append({
            "product_id": pid,
            "name": product.name if product else f"#{pid}",
            "units": float(units), "amount": float(money(amount)),
        })
    return result


def purchase_report(db: Session, from_dt: datetime, to_dt: datetime) -> list[dict]:
    rows = db.execute(
        select(Purchase)
        .where(Purchase.purchase_date >= from_dt, Purchase.purchase_date <= to_dt)
        .order_by(Purchase.purchase_date.desc())
    ).scalars().all()
    return [
        {"id": p.id, "purchase_no": p.purchase_no,
         "supplier": p.supplier.name if p.supplier else None,
         "date": p.purchase_date, "total": p.total, "paid": p.paid_amount,
         "balance": money(p.total - p.paid_amount), "status": p.status}
        for p in rows
    ]


def expense_report(db: Session, from_dt: datetime, to_dt: datetime) -> dict:
    rows = db.execute(
        select(Expense.category, func.sum(Expense.amount))
        .where(Expense.expense_date >= from_dt, Expense.expense_date <= to_dt)
        .group_by(Expense.category)
        .order_by(func.sum(Expense.amount).desc())
    ).all()
    return {
        "total": float(expenses_total(db, from_dt, to_dt)),
        "by_category": [{"category": c, "amount": float(money(a))} for c, a in rows],
    }


def inventory_report(db: Session) -> dict:
    return {
        "stock_value": float(inventory_service.stock_value(db)),
        "low_stock": [
            {"id": p.id, "name": p.name, "current_stock": p.current_stock, "min_stock": p.min_stock}
            for p in inventory_service.low_stock_products(db)
        ],
        "dead_stock": [
            {"id": p.id, "name": p.name, "current_stock": p.current_stock}
            for p in inventory_service.dead_stock(db, days=60)
        ],
    }


def customer_report(db: Session) -> list[dict]:
    from app.services.customer_service import customer_balance
    result = []
    for c in db.scalars(select(Customer).where(Customer.is_active.is_(True))):
        bal = customer_balance(db, c.id)
        result.append({"id": c.id, "name": c.name, "phone": c.phone, "balance": float(bal)})
    return sorted(result, key=lambda r: r["balance"], reverse=True)


def supplier_report(db: Session) -> list[dict]:
    from app.services.supplier_service import supplier_balance
    result = []
    for s in db.scalars(select(Supplier).where(Supplier.is_active.is_(True))):
        bal = supplier_balance(db, s.id)
        result.append({"id": s.id, "name": s.name, "phone": s.phone, "balance": float(bal)})
    return sorted(result, key=lambda r: r["balance"], reverse=True)
```

Note `product_sales` uses `SaleItem` — it reports *what was on invoices*, while the dashboard's `top_products` uses movements. Slightly different lenses; both correct for their purpose.

## 16.3 Routes — `backend/app/api/routes/reports.py`

```python
from datetime import datetime

from fastapi import APIRouter, Depends, Query
from sqlalchemy.orm import Session

from app.database.database import get_db
from app.services import report_service

router = APIRouter(prefix="/api/reports", tags=["reports"])


@router.get("/profit")
def profit(db: Session = Depends(get_db),
           from_date: datetime = Query(...), to_date: datetime = Query(...)) -> dict:
    return report_service.profit_summary(db, from_date, to_date)


@router.get("/sales-daily")
def sales_daily(db: Session = Depends(get_db),
                from_date: datetime = Query(...), to_date: datetime = Query(...)) -> list[dict]:
    return report_service.sales_daily(db, from_date, to_date)


@router.get("/sales-monthly")
def sales_monthly(db: Session = Depends(get_db),
                  from_date: datetime = Query(...), to_date: datetime = Query(...)) -> list[dict]:
    return report_service.sales_monthly(db, from_date, to_date)


@router.get("/product-sales")
def product_sales(db: Session = Depends(get_db),
                  from_date: datetime = Query(...), to_date: datetime = Query(...)) -> list[dict]:
    return report_service.product_sales(db, from_date, to_date)


@router.get("/purchases")
def purchases(db: Session = Depends(get_db),
              from_date: datetime = Query(...), to_date: datetime = Query(...)) -> list[dict]:
    return report_service.purchase_report(db, from_date, to_date)


@router.get("/expenses")
def expenses(db: Session = Depends(get_db),
             from_date: datetime = Query(...), to_date: datetime = Query(...)) -> dict:
    return report_service.expense_report(db, from_date, to_date)


@router.get("/inventory")
def inventory(db: Session = Depends(get_db)) -> dict:
    return report_service.inventory_report(db)


@router.get("/customers")
def customers(db: Session = Depends(get_db)) -> list[dict]:
    return report_service.customer_report(db)


@router.get("/suppliers")
def suppliers(db: Session = Depends(get_db)) -> list[dict]:
    return report_service.supplier_report(db)
```

## 16.4 Frontend — `pages/ReportsPage.tsx`

Range presets (client computes the ISO dates) + tabs + CSV export. The CSV helper:

```ts
// utils/csv.ts — export any row array to a downloadable CSV file
export function downloadCSV(filename: string, headers: string[], rows: unknown[][]) {
  const esc = (v: unknown) => {
    const s = String(v ?? "");
    return /[",\n]/.test(s) ? `"${s.replace(/"/g, '""')}"` : s;
  };
  const content = [headers, ...rows].map((r) => r.map(esc).join(",")).join("\n");
  const blob = new Blob(["\uFEFF" + content], { type: "text/csv;charset=utf-8" });
  const url = URL.createObjectURL(blob);
  const a = document.createElement("a");
  a.href = url;
  a.download = filename;
  a.click();
  URL.revokeObjectURL(url);
}
```

> The `\uFEFF` BOM makes Excel open UTF-8 CSVs (including ₹) correctly — a classic gotcha.

Report UI structure: a row of preset buttons (`Today`, `Yesterday`, `This Week`, `This Month`, `Custom` with two date inputs) → a `useApi` fetch per tab → `DataTable` + `downloadCSV` button. Date math for presets:

```ts
function presetRange(preset: string): { from: string; to: string } {
  const now = new Date();
  const fmt = (d: Date) => d.toISOString().slice(0, 10);
  const startOfDay = (d: Date) => new Date(d.getFullYear(), d.getMonth(), d.getDate());
  switch (preset) {
    case "today": return { from: fmt(startOfDay(now)), to: fmt(now) };
    case "yesterday": {
      const y = startOfDay(now); y.setDate(y.getDate() - 1);
      return { from: fmt(y), to: fmt(y) };
    }
    case "week": {
      const monday = startOfDay(now); monday.setDate(monday.getDate() - ((monday.getDay() + 6) % 7));
      return { from: fmt(monday), to: fmt(now) };
    }
    case "month": {
      return { from: fmt(new Date(now.getFullYear(), now.getMonth(), 1)), to: fmt(now) };
    }
    default: return { from: "", to: "" };
  }
}
```

## ✏️ Exercise 16.1 — dead-stock report endpoint

The inventory report returns dead stock inline. Add `GET /api/reports/dead-stock?days=60` as its own endpoint.

<details>
<summary><b>Solution sketch</b></summary>

```python
@router.get("/dead-stock")
def dead_stock(db: Session = Depends(get_db), days: int = Query(60, ge=1)):
    return [
        {"id": p.id, "name": p.name, "current_stock": p.current_stock}
        for p in inventory_service.dead_stock(db, days)
    ]
```

</details>

---

## ✅ Phase 16 Checkpoint

- [ ] All 10 report endpoints return sensible data for a range that includes your test sales
- [ ] Presets + custom range work in the UI; CSV exports open correctly in Excel (₹ intact)
- [ ] Exercise 16.1 done

Commit:

```bash
git add -A
git commit -m "feat: add reports engine, routes, and reports UI with CSV export"
```

---

# Phase 17 — Barcode Scanner

> **Goal of this phase:** make a physical USB barcode scanner "just work", and understand *why* it does. Plus optional barcode generation.

## 17.1 How barcode scanners actually work (the key insight)

A cheap USB barcode scanner is a **keyboard-wedge** device: it doesn't send data to the "scanner port". When you scan a barcode, the scanner **types the digits as keystrokes**, followed by an `Enter` (or configurable suffix), into whatever has keyboard focus.

That means:

```text
Scan → the digits appear in the focused input → Enter → your handler runs
```

**We already built this.** Phase 10's billing screen keeps a text input focused; scanning types the code and presses Enter; our handler looks up the product. Zero scanner-specific code. This is why the input is called a "barcode input" and stays autofocused.

The practical consequences for setup:

| Symptom | Cause | Fix |
|---|---|---|
| Scanner types into the wrong field | Focus elsewhere | Keep `barcodeRef` focused (we do); use `/` to refocus |
| Digits appear but nothing happens | Scanner sends no Enter suffix | Configure the scanner (manual) to add CR/LF, or handle `keydown` Enter ourselves |
| Digits appear twice | Scanner suffix + our form also submits | Check scanner manual: disable its Enter suffix or remove our duplicate handler |
| Wrong characters for some codes | Scanner in the wrong mode (e.g. keyboard layout) | Scanner manual: set to "keyboard HID" mode |

## 17.2 Exact lookup (important correction to Phase 10)

Phase 10's demo searched within the **50 loaded products**. With a real catalog that's wrong — a scan might match nothing because the product isn't in the current page. The correct flow is a **server-side exact lookup**:

```text
Scan → Enter → GET /api/products/by-barcode/{code} → 200 product → add to cart
                                            → 404   → "product not found"
```

Add to `product_service`:

```python
def get_by_barcode(db: Session, barcode: str) -> Product | None:
    return db.scalar(select(Product).where(Product.barcode == barcode.strip(),
                                           Product.is_active.is_(True)))
```

and route:

```python
@router.get("/by-barcode/{barcode}", response_model=ProductRead)
def by_barcode(barcode: str, db: Session = Depends(get_db)) -> ProductRead:
    product = product_service.get_by_barcode(db, barcode)
    if product is None:
        raise NotFoundError("No product with that barcode")
    return _to_read(product)
```

> ⚠️ **Route-order warning:** `/by-barcode/{barcode}` and `/by-barcode` style routes must be declared **before** `/{product_id}` in the file, or FastAPI will try to parse "by-barcode" as an integer id. This bit us before — it's a classic.

Then in `BillingPage`, on Enter: if the term *looks like* a barcode (all digits, or contains no spaces), call the exact endpoint; otherwise search. The final code does this.

## 17.3 Barcode generation (optional, but nice)

To *print* barcodes for products that lack them, use `python-barcode`:

```bash
pip install python-barcode
```

```python
import barcode
from barcode.writer import ImageWriter

def generate_ean13(product_name: str, code12: str, out_path: str) -> str:
    """EAN-13 needs exactly 12 digits; it computes the 13th (check digit)."""
    ean = barcode.get("ean13", code12, writer=ImageWriter())
    return ean.save(out_path)  # returns path; the last digit is auto-added
```

Explain: EAN-13's final digit is a **check digit** computed from the first 12 — scanners and the reader both verify it, which is how a mistyped barcode is caught at the counter. (GTIN-12/upc-a → convert to EAN-13 by prepending 0.) This is a *script/feature*, not part of the MVP flow — scan-first, generate-later.

---

## ✅ Phase 17 Checkpoint

- [ ] Scan (or type) a barcode in billing → product added via the exact-lookup endpoint
- [ ] A barcode not in the DB → friendly "No product with that barcode"
- [ ] `/` refocuses the input after clicking elsewhere
- [ ] (Optional) a generated EAN-13 image scans correctly with a phone scanner app

Commit:

```bash
git add -A
git commit -m "feat: add exact barcode lookup and scanning flow"
```

---

# Phase 18 — Authentication and Authorization

> **Goal of this phase:** login, sessions (JWT), and **role-based permissions enforced on the backend** — never just by hiding buttons.

## 18.1 Mini-project: password hashing, done right

Create a scratch file to *see* what bcrypt does (then delete it):

```python
from app.core.security import hash_password, verify_password

h = hash_password("admin123")
print(h)                 # e.g. $2b$12$mW3H...  — salted, one-way
print(h == hash_password("admin123"))   # False! different salt each time
print(verify_password("admin123", h))   # True
print(verify_password("wrong", h))      # False
```

Key facts: bcrypt adds a **random salt**, so the same password hashes differently each time (defeating rainbow tables); verification is slow by design (throttling brute force); and we **never** store or log the plaintext. This mini-exercise maps directly to `User.password_hash`.

## 18.2 The login service — `backend/app/services/auth_service.py`

```python
from app.core.exceptions import AuthenticationError
from app.core.security import create_access_token, verify_password
from app.models import User


def authenticate(db, username: str, password: str) -> tuple[User, str]:
    user = db.scalar(select(User).where(User.username == username.strip()))
    # Same error for "no such user" and "wrong password" — don't leak which
    if user is None or not user.is_active or not verify_password(password, user.password_hash):
        raise AuthenticationError("Invalid username or password")
    token = create_access_token(subject=user.username, role=user.role.value)
    return user, token
```

## 18.3 Dependencies — `backend/app/api/deps.py`

```python
from fastapi import Depends
from fastapi.security import HTTPAuthorizationCredentials, HTTPBearer
from sqlalchemy import select
from sqlalchemy.orm import Session

from app.core.exceptions import AuthenticationError, PermissionDeniedError
from app.core.security import decode_access_token
from app.database.database import get_db
from app.models import User, UserRole

bearer = HTTPBearer(auto_error=False)


def get_current_user(
    credentials: HTTPAuthorizationCredentials | None = Depends(bearer),
    db: Session = Depends(get_db),
) -> User:
    if credentials is None:
        raise AuthenticationError("Not authenticated")
    try:
        payload = decode_access_token(credentials.credentials)
    except Exception:
        raise AuthenticationError("Invalid or expired token")
    user = db.scalar(select(User).where(User.username == payload.get("sub")))
    if user is None or not user.is_active:
        raise AuthenticationError("User not found or deactivated")
    return user


def require_roles(*roles: UserRole):
    """Dependency factory: require the current user to hold one of the roles."""
    allowed = set(roles)

    def checker(user: User = Depends(get_current_user)) -> User:
        if user.role not in allowed:
            raise PermissionDeniedError(
                f"Requires one of: {', '.join(r.value for r in allowed)}"
            )
        return user

    return checker
```

Usage: `owner_only = Depends(require_roles(UserRole.OWNER))` — one line per route.

## 18.4 The permission matrix (authorization is a *backend* concept)

| Action | Owner | Manager | Cashier |
|---|:---:|:---:|:---:|
| Login / Billing (create sale) | ✅ | ✅ | ✅ |
| View products / stock | ✅ | ✅ | ✅ |
| Create / edit products | ✅ | ✅ | ❌ |
| Delete / deactivate products | ✅ | ✅ | ❌ |
| View profit, reports, dashboard profit | ✅ | ✅ | ❌ |
| Purchases / suppliers | ✅ | ✅ | ❌ |
| Customers & Khata | ✅ | ✅ | ✅ (view, no delete) |
| Expenses | ✅ | ✅ | ❌ |
| Manage users | ✅ | ❌ | ❌ |
| Settings / backups / restore | ✅ | ❌ | ❌ |
| Adjust / reconcile stock | ✅ | ✅ | ❌ |

Where it's enforced:

```python
# sales.py
@router.post("", status_code=status.HTTP_201_CREATED)
def create_sale(body: SaleCreate, db: Session = Depends(get_db),
                user: User = Depends(get_current_user)) -> SaleRead:
    sale = sale_service.create_sale(db, body, user_id=user.id)
    return _to_read(sale)

# products.py
@router.delete("/{product_id}", status_code=status.HTTP_204_NO_CONTENT)
def deactivate_product(product_id: int, db: Session = Depends(get_db),
                       user: User = Depends(require_roles(UserRole.OWNER, UserRole.MANAGER))) -> None:
    product_service.deactivate_product(db, product_id)

# users.py — owner only
@router.post("", status_code=status.HTTP_201_CREATED)
def create_user(body: UserCreate, db: Session = Depends(get_db),
                _: User = Depends(require_roles(UserRole.OWNER))) -> UserRead:
    ...
```

> ⚠️ **Security rule:** the frontend hides buttons for *usability*. The backend `require_roles` checks are the *security*. A Cashier can open the browser console or curl and call `DELETE /api/products/5` — and get **403** because the backend checks. Never rely on UI hiding.

## 18.5 Users management — `backend/app/api/routes/users.py` (Owner only)

```python
@router.get("")
@router.post("")            # create user (username, full_name, role, password)
@router.patch("/{user_id}") # edit name/role/active
@router.post("/{user_id}/password")  # reset password
```

`create_user` validates the role, hashes the password, and rejects duplicates with 409. The owner can also deactivate a user (login fails — see `get_current_user`).

## 18.6 The auth route — `backend/app/api/routes/auth.py`

```python
from fastapi import APIRouter, Depends, status
from pydantic import BaseModel, Field
from sqlalchemy.orm import Session

from app.api.deps import get_current_user
from app.database.database import get_db
from app.models import User
from app.schemas.user import UserRead
from app.services import auth_service

router = APIRouter(prefix="/api/auth", tags=["auth"])


class LoginIn(BaseModel):
    username: str = Field(min_length=1, max_length=64)
    password: str = Field(min_length=1, max_length=64)  # bcrypt caps at 72 bytes


class TokenOut(BaseModel):
    access_token: str
    token_type: str = "bearer"
    user: UserRead


@router.post("/login", response_model=TokenOut)
def login(body: LoginIn, db: Session = Depends(get_db)) -> dict:
    user, token = auth_service.authenticate(db, body.username, body.password)
    return {"access_token": token, "token_type": "bearer",
            "user": UserRead.model_validate(user)}


@router.get("/me", response_model=UserRead)
def me(user: User = Depends(get_current_user)) -> User:
    return user
```

## 18.7 Frontend — auth store, login page, route guards

`store/auth.ts`:

```ts
import { create } from "zustand";
import { persist } from "zustand/middleware";
import { api, TOKEN_KEY } from "../services/api";
import type { User } from "../types";

interface AuthState {
  token: string | null;
  user: User | null;
  login: (username: string, password: string) => Promise<void>;
  logout: () => void;
}

export const useAuth = create<AuthState>()(
  persist(
    (set) => ({
      token: null,
      user: null,
      login: async (username, password) => {
        const res = await api.post<{ access_token: string; user: User }>("/api/auth/login", { username, password });
        localStorage.setItem(TOKEN_KEY, res.access_token);
        set({ token: res.access_token, user: res.user });
      },
      logout: () => {
        localStorage.removeItem(TOKEN_KEY);
        set({ token: null, user: null });
      },
    }),
    { name: "lrm-auth" },  // persists user/token across restarts (local desktop app)
  ),
);
```

`ProtectedRoute` wraps the app; unauthenticated users go to `/login`:

```tsx
import { Navigate, Outlet } from "react-router-dom";
import { useAuth } from "../../store/auth";

export function ProtectedRoute() {
  const token = useAuth((s) => s.token);
  return token ? <Outlet /> : <Navigate to="/login" replace />;
}
```

`App.tsx` becomes:

```tsx
<Routes>
  <Route path="/login" element={<LoginPage />} />
  <Route element={<ProtectedRoute />}>
    <Route element={<AppLayout />}>
      {/* all 11 pages */}
    </Route>
  </Route>
</Routes>
```

`LoginPage` — centered card, username/password, error toast, redirects to `/` on success. The `ApiError` from the wrapper shows "Invalid username or password" from the backend.

Sidebar role filtering (usability only):

```tsx
const NAV: { to: string; label: string; icon: LucideIcon; roles?: Role[] }[] = [
  { to: "/", label: "Dashboard", icon: LayoutDashboard },
  { to: "/billing", label: "Billing", icon: ShoppingCart },
  ...
  { to: "/reports", label: "Reports", icon: BarChart3, roles: ["OWNER", "MANAGER"] },
  { to: "/users", label: "Users", icon: UserCog, roles: ["OWNER"] },
  { to: "/settings", label: "Settings", icon: Settings, roles: ["OWNER"] },
];
// render only items where !roles || roles.includes(user.role)
```

And the Topbar shows the logged-in user + role badge + logout.

> **First-run password:** the seeded `owner/admin123` must be changed. The owner can change their own password in Settings (Phase 19/24) or via the users page.

---

## ✅ Phase 18 Checkpoint

- [ ] `POST /api/auth/login` with `owner/admin123` → token + user
- [ ] Call a protected endpoint without a token → **401**; with a Cashier token, `DELETE /api/products/5` → **403**
- [ ] Frontend: login page works; visiting `/` logged out redirects to `/login`; logout works
- [ ] Cashier's sidebar lacks Reports/Users/Settings (and the backend still blocks direct calls)
- [ ] Create a Manager and a Cashier from the Users page; each has the right abilities

### If it doesn't work

| Error | Why | Fix |
|---|---|---|
| `401` on every request after login | Token not sent | `api.ts` reads `TOKEN_KEY` from localStorage — check key name matches `auth.ts` |
| Password with special chars fails | bcrypt 72-byte cap | Schema `max_length=64`; the exception is a `ValueError` we catch in `verify_password` |
| Cashier can still see Reports | Only frontend filtering | That's fine — but the backend `require_roles` must also block it; verify with curl |

Commit:

```bash
git add -A
git commit -m "feat: add authentication and role-based authorization"
```

---

# Phase 19 — Backup and Restore

> **Goal of this phase:** the feature that makes a local-only app trustworthy. A shop with no backup has a time bomb.

## 19.1 Problem & concept

The entire business lives in one SQLite file. Threats: hard disk failure, corruption from a sudden power cut, accidental deletes, a bad migration. Because the app is **offline-first**, there is no server to protect us — **we** must.

### Why not just copy the file?

While the app is running, SQLite (in WAL mode) keeps recent writes in `retail.db-wal`; a raw copy of `retail.db` may miss them or capture a torn state. The correct tool is SQLite's own backup mechanisms:

- **`VACUUM INTO 'file'`** — produces a **consistent point-in-time snapshot** of the database *even while other connections are writing*. One SQL statement, perfect for our purpose.
- The `sqlite3` backup API (`conn.backup()`) — the streaming alternative; `VACUUM INTO` is simpler and atomic.

### The backup lifecycle

```text
Backup   → VACUUM INTO data/backups/retail_20260808_093000.db
Verify   → open the copy, run PRAGMA integrity_check → "ok"
Rotate   → delete backups older than BACKUP_KEEP_DAYS (14)
Restore  → pick a backup → validate → swap it into place (after a safety backup)
Automatic→ on startup, if the newest backup is older than 24h, create one
```

## 19.2 Service — `backend/app/services/backup_service.py`

```python
import logging
import sqlite3
from datetime import datetime, timedelta
from pathlib import Path

from sqlalchemy import text
from sqlalchemy.orm import Session

from app.core.config import settings
from app.core.exceptions import AppError

logger = logging.getLogger(__name__)

HEADER = b"SQLite format 3"


def _now_str() -> str:
    return datetime.now().strftime("%Y%m%d_%H%M%S")


def list_backups() -> list[dict]:
    settings.backups_dir.mkdir(parents=True, exist_ok=True)
    backups = []
    for p in sorted(settings.backups_dir.glob("retail_backup_*.db")):
        backups.append({
            "filename": p.name,
            "size": p.stat().st_size,
            "created_at": datetime.fromtimestamp(p.stat().st_mtime).isoformat(),
        })
    return sorted(backups, key=lambda b: b["created_at"], reverse=True)


def _verify_backup(path: Path) -> bool:
    """Open the copy and run SQLite's own integrity check."""
    if not path.exists() or path.stat().st_size == 0:
        return False
    try:
        conn = sqlite3.connect(str(path))
        try:
            row = conn.execute("PRAGMA integrity_check").fetchone()
            return bool(row and row[0] == "ok")
        finally:
            conn.close()
    except sqlite3.Error:
        return False


def create_backup(db: Session) -> dict:
    """Consistent snapshot via VACUUM INTO, then verify + rotate."""
    settings.backups_dir.mkdir(parents=True, exist_ok=True)
    path = settings.backups_dir / f"retail_backup_{_now_str()}.db"

    # VACUUM INTO must run OUTSIDE an open transaction
    db.rollback()
    db.execute(text(f"VACUUM INTO '{path.as_posix()}'"))

    if not _verify_backup(path):
        path.unlink(missing_ok=True)
        raise AppError("Backup failed verification — no backup file kept")

    rotate()
    logger.info("Backup created and verified: %s", path.name)
    return {"filename": path.name, "size": path.stat().st_size,
            "created_at": datetime.now().isoformat(), "verified": True}


def rotate() -> None:
    """Delete backups older than BACKUP_KEEP_DAYS."""
    cutoff = datetime.now() - timedelta(days=settings.BACKUP_KEEP_DAYS)
    for p in settings.backups_dir.glob("retail_backup_*.db"):
        if datetime.fromtimestamp(p.stat().st_mtime) < cutoff:
            p.unlink(missing_ok=True)
            logger.info("Rotated old backup: %s", p.name)


def auto_backup_if_due(db: Session) -> dict | None:
    """Called at startup: back up if the newest backup is older than 24h."""
    backups = list_backups()
    if backups:
        newest = datetime.fromisoformat(backups[0]["created_at"])
        if datetime.now() - newest < timedelta(hours=24):
            return None
    return create_backup(db)


def restore_backup(db: Session, filename: str) -> None:
    """Swap the live database for a validated backup. Refuses unsafe inputs."""
    if not filename or ".." in filename or "/" in filename or "\\" in filename:
        raise AppError("Invalid backup filename")
    src = settings.backups_dir / filename
    if not _verify_backup(src):
        raise AppError("Backup file failed verification — refusing to restore")

    # Safety: never restore over a fresh state without first backing it up
    db.commit()
    safety = create_backup(db)

    # Drop all connections so we can replace the file
    from app.database.database import engine
    engine.dispose()

    target = settings.db_dir / settings.DATABASE_FILE
    import shutil
    shutil.copy2(src, target)
    # WAL leftovers must go — they belong to the OLD database
    for suffix in ("-wal", "-shm"):
        (Path(str(target) + suffix)).unlink(missing_ok=True)

    logger.warning("Restored %s (safety backup: %s)", filename, safety["filename"])
```

Explain the safety details:

- **Filename validation** — we restore only files we recognize; the `..`/separator checks stop path traversal.
- **Safety backup first** — restoring is destructive; the current (possibly good) state is preserved automatically.
- **`engine.dispose()`** — closes all pooled connections so the file isn't locked on Windows; then we copy and delete stale `-wal`/`-shm` files (they'd belong to the pre-restore database and could corrupt the restored one if replayed).
- **`PRAGMA integrity_check`** — SQLite's own verification (not ours): it walks the whole file checking page consistency.

## 19.3 Routes — `backend/app/api/routes/backups.py` (Owner only)

```python
@router.get("")                                   # list
@router.post("", status_code=201)                 # create + verify + rotate
@router.post("/restore")                          # {filename} → restore (safety backup first)
@router.post("/auto")                             # manual auto-backup check
```

Every route: `Depends(require_roles(UserRole.OWNER))`. In `main.py`'s lifespan, after seeding:

```python
from app.services import backup_service
backup_service.auto_backup_if_due(db)
```

## 19.4 Frontend — Settings page backup section

Three buttons + a table:

- **Back up now** → `POST /api/backups` → toast with the filename.
- **Backups table** → filename, size, date, **Restore** (ConfirmDialog: "This replaces all current data. A safety backup will be created first.")
- Restore success → toast: "Restored. Restart the app." (The app restarts cleanly via Tauri in production; in dev, restart `uvicorn`.)

## 19.5 Where backups live

- **Development:** `data/backups/` (gitignored).
- **Production:** the OS app-data directory (Phase 23) — `%APPDATA%/com.localretailmanager.app/backups`. Owners should also copy this folder to a USB drive / Google Drive occasionally — we document that in the Settings page as a tip.

---

## ✅ Phase 19 Checkpoint

- [ ] `POST /api/backups` → file appears in `data/backups/`, `verified: true`
- [ ] Edit data, restore the backup → data returns to the backed-up state
- [ ] Backup integrity check runs on every creation; a corrupt file is refused on restore
- [ ] Restarting the app triggers an auto-backup only if the newest is > 24h old
- [ ] Old backups are rotated after `BACKUP_KEEP_DAYS`

### If it doesn't work

| Error | Why | Fix |
|---|---|---|
| `VACUUM INTO` fails: "cannot VACUUM from within a transaction" | An open transaction | `db.rollback()` before the call (we do) |
| Restore fails on Windows: file in use | Pooled connections hold the file | `engine.dispose()` before replacing (we do) |
| Restored DB has stale data from the old DB | `-wal` replayed | Delete `-wal`/`-shm` after copying (we do) |

Commit:

```bash
git add -A
git commit -m "feat: add backup and restore with verification and rotation"
```

---

**Next:** [Phase 20 — Error Handling and Logging](#phase-20--error-handling-and-logging)
# Phase 20 — Error Handling and Logging

> **Goal of this phase:** every failure the app can meet has a *known shape* — a readable message for the user, a log line for you, and no corruption behind it.

## 20.1 The error taxonomy (what can go wrong, and where it's handled)

| Category | Examples | Where handled | User sees |
|---|---|---|---|
| **Validation** | negative price, empty name, bad JSON | Pydantic → **422** | field messages |
| **Business rule** | insufficient stock, duplicate barcode, double return | service raises `AppError` → **4xx** | `{code, message}` |
| **Database** | `IntegrityError` (UNIQUE race), DB locked | service catches → `ConflictError` | clear message |
| **File** | invoices dir missing, PDF write fails | service logs + best-effort | app keeps working |
| **PDF** | font missing, corrupt doc | invoice service | logged; invoice regenerable |
| **Printer/network** | (desktop) printer offline, backend unreachable | frontend | toast / retry screen |
| **Unexpected** | a real bug | global 500 handler | "Something went wrong" + logged traceback |

The pattern: **services raise typed exceptions, one handler converts them, the frontend shows the message.** No raw tracebacks in the UI, ever.

## 20.2 Database-integrity backstop: the retry pattern

Phase 7's invoice numbering has a race (two quick sales both compute `0001`). The DB UNIQUE constraint catches it; the service retries once:

```python
def _create_sale_with_retry(db, data, user_id, attempts: int = 2) -> Sale:
    for attempt in range(attempts):
        try:
            return _create_sale(db, data, user_id)   # the body of create_sale
        except IntegrityError:
            db.rollback()
            if attempt == attempts - 1:
                raise ConflictError("Could not allocate invoice number — please retry")
            logger.warning("Invoice number collision, retrying…")
    raise ConflictError("Could not allocate invoice number")
```

And the global safety net — catch stray `IntegrityError`s (e.g. duplicate barcode under race) as 409 in `main.py`:

```python
from sqlalchemy.exc import IntegrityError

@app.exception_handler(IntegrityError)
async def integrity_error_handler(request, exc: IntegrityError):
    logger.exception("IntegrityError")
    return JSONResponse(status_code=409,
        content={"detail": {"code": "conflict", "message": "That value is already in use."}})
```

## 20.3 Logging — `backend/app/core/logging.py`

A local app's logs live **next to its data**, not in the console:

```python
import logging
from logging.handlers import RotatingFileHandler

from app.core.config import settings


def setup_logging() -> None:
    settings.logs_dir.mkdir(parents=True, exist_ok=True)
    formatter = logging.Formatter(
        "%(asctime)s | %(levelname)-8s | %(name)s | %(message)s"
    )

    file_handler = RotatingFileHandler(
        settings.logs_dir / "app.log",
        maxBytes=2_000_000,   # 2 MB
        backupCount=5,        # keep 5 rotated files
        encoding="utf-8",
    )
    file_handler.setFormatter(formatter)

    root = logging.getLogger()
    root.setLevel(logging.INFO)
    root.addHandler(file_handler)

    # Also mirror to console in development
    if settings.ENV == "development":
        console = logging.StreamHandler()
        console.setFormatter(formatter)
        root.addHandler(console)
```

Call `setup_logging()` first thing in `create_app()`. Logging rules:

- ✅ Log **what happened**: `Sale INV-20260808-0001 created: total=84.00`
- ✅ Log **warnings/errors with context**: `logger.exception("Invoice generation failed for %s", sale.invoice_no)`
- ❌ **Never** log passwords, password hashes, full tokens, or full card numbers.
- ❌ Never log the entire request body (it may contain a password).

## 20.4 Frontend error handling

- `ApiError.status` / `.code` drive behavior: **401 → logout + redirect to /login** (in `api.ts`), **409 → "already exists"**, **403 → "not allowed"**.
- Network failures (backend down): `fetch` throws `TypeError: Failed to fetch` → wrapper converts to a friendly `ApiError(0, "Cannot reach the app server. Is it running?")`.
- Every list page: error state + Retry (built in Phase 9's `useApi`).

---

## ✅ Phase 20 Checkpoint

- [ ] Trigger each error class and see its shape: 422 (bad body), 409 (duplicate barcode, insufficient stock), 404, 403 (Cashier deleting a product), 500 (temporarily raise in a service)
- [ ] `backend/data/logs/app.log` grows with startup + each error (no passwords in it!)
- [ ] Two rapid identical sales never produce a duplicate invoice number

Commit:

```bash
git add -A
git commit -m "feat: add logging, integrity backstops, and error handling"
```

---

# Phase 21 — Testing

> **Goal of this phase:** prove the business math and the critical flows *automatically*. Tests are how you refactor without fear.

## 21.1 What to test, and why (the pyramid)

```text
        ╱ API tests ╲        few — each route, happy path + auth
      ╱ integration ╲       some — sale/purchase flows end-to-end (DB)
    ╱   unit tests   ╲      many — pure business math (pricing, stock, profit)
```

- **Unit** — pure functions, no DB: tax/discount, invoice numbering, avg cost, stock sum, profit. Fast, catch regressions in the math.
- **Integration** — services against a real (in-memory) SQLite: create product → sale → stock decreases; purchase → stock increases.
- **API** — `TestClient`: login, CRUD, 401/403/409 behavior, backup create.
- **Frontend** — pricing helpers, cart store, a component test (totals render).

## 21.2 Setup — `backend/tests/conftest.py`

The golden rule: **tests never touch your real database.** We build a fresh in-memory SQLite per test:

```python
import pytest
from fastapi.testclient import TestClient
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from sqlalchemy.pool import StaticPool

from app.database.database import get_db
from app.main import app as fastapi_app
from app.models import Base


@pytest.fixture()
def db_session():
    engine = create_engine(
        "sqlite://",
        connect_args={"check_same_thread": False},
        poolclass=StaticPool,  # share one in-memory DB across connections
    )
    Base.metadata.create_all(engine)
    TestSession = sessionmaker(bind=engine, expire_on_commit=False)
    session = TestSession()
    try:
        yield session
    finally:
        session.close()
        Base.metadata.drop_all(engine)
        engine.dispose()


@pytest.fixture()
def client(db_session):
    def override_get_db():
        yield db_session

    fastapi_app.dependency_overrides[get_db] = override_get_db
    with TestClient(fastapi_app) as c:
        yield c
    fastapi_app.dependency_overrides.clear()
```

- `StaticPool` — every connection to `sqlite://` must see the *same* in-memory database; this is the standard trick.
- `dependency_overrides` — FastAPI's DI is what makes testing clean: we swap `get_db` for the test session. No test client configuration needed, and the app code never changes.

## 21.3 Unit tests — `backend/tests/test_pricing.py`

```python
from decimal import Decimal

from app.sale_service_helper import _calculate   # (or import from sale_service)

def test_no_discount_no_tax():
    lines = [{"quantity": Decimal("3"), "unit_price": Decimal("28"), "tax_rate": Decimal("0")}]
    r = _calculate(lines, Decimal("0"))
    assert r["total"] == Decimal("84.00")

def test_discount_then_tax_on_discounted_value():
    lines = [{"quantity": Decimal("10"), "unit_price": Decimal("100"), "tax_rate": Decimal("18")}]
    r = _calculate(lines, Decimal("10"))
    assert r["subtotal"] == Decimal("1000.00")
    assert r["discount"] == Decimal("100.00")
    assert r["tax"] == Decimal("162.00")   # 900 × 18%
    assert r["total"] == Decimal("1062.00")

def test_half_up_rounding():
    lines = [{"quantity": Decimal("3"), "unit_price": Decimal("10"), "tax_rate": Decimal("5")}]
    r = _calculate(lines, Decimal("0"))
    assert r["tax"] == Decimal("1.50")
```

> **Design note:** `_calculate` is private-but-pure — exactly the kind of function worth testing. If it's awkward to import, that's a signal it should live in its own module (`utils/pricing.py` on the backend too).

## 21.4 Integration test — the sale flow

```python
from app.models import MovementType, Product, Sale
from app.services import inventory_service, product_service, sale_service
from app.schemas.product import ProductCreate
from app.schemas.sale import PaymentIn, SaleCreate, SaleItemIn
from app.models.enums import PaymentMethod

def make_product(db, **kw):
    default = dict(name="Tata Salt", purchase_price=22, selling_price=28, min_stock=10)
    default.update(kw)
    return product_service.create_product(db, ProductCreate(**default))

def test_sale_reduces_stock_and_creates_movement(db_session):
    p = make_product(db_session)
    inventory_service.adjust_stock(db_session, product_id=p.id, new_stock=100, reason="opening")
    db_session.commit()

    sale = sale_service.create_sale(db_session, SaleCreate(
        items=[SaleItemIn(product_id=p.id, quantity=3)],
        payments=[PaymentIn(method=PaymentMethod.CASH)],
    ), user_id=None)

    db_session.refresh(p)
    assert p.current_stock == 97
    assert sale.total == 84.00
    moves = inventory_service.list_movements(db_session, product_id=p.id)[0]
    assert any(m.movement_type == MovementType.SALE and m.quantity == -3 for m in moves)

def test_insufficient_stock_rolls_back_everything(db_session):
    p = make_product(db_session)
    inventory_service.adjust_stock(db_session, product_id=p.id, new_stock=1, reason="opening")
    db_session.commit()

    try:
        sale_service.create_sale(db_session, SaleCreate(
            items=[SaleItemIn(product_id=p.id, quantity=5)],
        ), user_id=None)
        assert False, "should have raised"
    except Exception:
        db_session.rollback()

    db_session.refresh(p)
    assert p.current_stock == 1                      # nothing changed
    assert db_session.query(Sale).count() == 0       # no orphan sale
    assert db_session.query(MovementType).count() == 0  # no orphan movements
```

The second test *is* the Phase 7 guarantee, proven forever.

## 21.5 API tests — `backend/tests/test_api.py`

```python
def test_login_and_401(client):
    r = client.post("/api/auth/login", json={"username": "owner", "password": "admin123"})
    assert r.status_code == 200
    token = r.json()["access_token"]

    assert client.get("/api/products").status_code == 401          # no token
    assert client.get("/api/products",
                      headers={"Authorization": f"Bearer {token}"}).status_code == 200


def test_product_conflict(client, headers):
    body = {"name": "Salt", "barcode": "8901"}
    assert client.post("/api/products", json=body, headers=headers).status_code == 201
    r = client.post("/api/products", json=body, headers=headers)
    assert r.status_code == 409


def test_cashier_cannot_delete_products(client, cashier_headers):
    r = client.delete("/api/products/1", headers=cashier_headers)
    assert r.status_code == 403
```

(Add fixtures `headers`/`cashier_headers` in conftest that create users via the API and return Bearer tokens.)

Run: `cd backend && pytest -q`. Target: everything green.

## 21.6 Frontend tests (Vitest)

Add to `vite.config.ts`:

```ts
/// <reference types="vitest/config" />
test: { environment: "jsdom", globals: true, setupFiles: "./src/test/setup.ts" }
```

`src/test/setup.ts`: `import "@testing-library/jest-dom";`

`src/utils/pricing.test.ts`:

```ts
import { describe, expect, it } from "vitest";
import { computeTotals } from "./pricing";

describe("computeTotals", () => {
  it("matches backend math for a discounted taxed sale", () => {
    const t = computeTotals(
      [{ qty: 10, unitPrice: 100, taxRate: 18 }],
      10,
    );
    expect(t.subtotal).toBe(1000);
    expect(t.discount).toBe(100);
    expect(t.tax).toBe(162);
    expect(t.total).toBe(1062);
  });
});
```

Component test — `src/components/BillingTotals.test.tsx`: render the totals panel with a fake cart and assert `₹1,062.00` appears.

Run: `cd frontend && npx vitest run`.

---

## ✅ Phase 21 Checkpoint

- [ ] `pytest -q` — all unit, integration, API tests pass (aim for 20+ tests)
- [ ] `npx vitest run` — frontend tests pass
- [ ] Deliberately break the tax formula → a test fails (prove the tests bite!)

Commit:

```bash
git add -A
git commit -m "feat: add backend and frontend test suites"
```

---

# Phase 22 — Security

> **Goal of this phase:** practical security for a *local* retail app. We don't need a firewall; we need honesty about what can actually hurt.

## 22.1 Threat model (who's attacking a shop PC?)

| Threat | Likelihood | Impact | Our defense |
|---|---|---|---|
| A dishonest employee | Medium | High (money, inventory) | Roles + audit trail (every sale/movement has a user) |
| Malware on the shop PC | Medium | High | Backups; never run as admin; data folder per-user |
| Data corruption / disk failure | High (real shops!) | Total | Phase 19 backups + WAL |
| Remote attacker | Low (app is localhost-only) | — | Bind to `127.0.0.1`, never `0.0.0.0` |
| Theft of the database file | Low | High | Full-disk encryption is the OS's job (BitLocker) |

## 22.2 The controls, mapped to what we already built

| Control | Where | Status |
|---|---|---|
| Passwords hashed (bcrypt) | `core/security.py` | ✅ built (Phases 4/18) |
| SQL injection impossible | SQLAlchemy parameterized statements; no raw f-strings in SQL | ✅ built — rule: never `text(f"...{value}...")` |
| Input validation | Pydantic on every endpoint | ✅ built |
| Authorization on the **backend** | `require_roles` on every sensitive route | ✅ built (Phase 18) |
| Secrets not in code | `SECRET_KEY` from env; `.env` gitignored | ✅ built |
| Localhost-only binding | `HOST=127.0.0.1` | ✅ built — verify in prod logs |
| File permissions | Data/logs under the user's app-data folder, not Program Files | ✅ Phase 23 |
| Safe backups | verified + validated restore, safety-backup-first | ✅ Phase 19 |
| Sensitive data in logs | never log passwords/tokens | ✅ Phase 20 |

## 22.3 The remaining honest gaps (and their fixes)

1. **JWT secret rotation** — if `SECRET_KEY` leaks, tokens are forgeable. Change it in `.env` when in doubt (all users re-login — fine).
2. **No brute-force protection** — a local attacker could try passwords quickly. Acceptable for MVP; a 1-second sleep after 5 failed logins is a 5-line upgrade (exercise below).
3. **Backup media** — backups on the same disk die with the disk. The Settings page must *tell the owner* to copy `backups/` to a USB drive monthly.
4. **SmartScreen/AV** — an unsigned exe triggers warnings; see Phase 24.

## ✏️ Exercise 22.1 — login rate limiting (5 lines)

In `auth_service.authenticate`, on failure, `import time; time.sleep(1)`. Explain why that's *almost* as good as counting attempts for a local app.

<details>
<summary><b>Answer</b></summary>

A 1-second delay per failed attempt means brute-forcing a 6-character password takes years even with no attempt counting — and it's simpler than session state. For a local app it's the 80/20 solution. (A full account-lockout adds DoS risk for the owner anyway.)

</details>

---

## ✅ Phase 22 Checkpoint

- [ ] Every endpoint that should be protected returns 401/403 when probed with curl (not just hidden in the UI)
- [ ] `.env` never committed; `git log` shows no secrets
- [ ] Backend binds to 127.0.0.1 only
- [ ] Logs contain no passwords/tokens
- [ ] Exercise 22.1 done

Commit:

```bash
git add -A
git commit -m "feat: harden security (rate limit, audit rules)"
```

---

# Phase 23 — Tauri Integration

> **Goal of this phase:** wrap the working web app in a real desktop shell. Only now — because Tauri's job is to *host* what we built, not to be built alongside it.

## 23.1 What Tauri is, and the WebView architecture

Tauri is a **Rust shell** that creates a native window and renders our React app using the **OS's own browser engine** — WebView2 on Windows. Unlike Electron it ships no Chromium, so the installer is tiny and RAM use is low.

The communication model (this is the part that surprises people):

```text
React (in WebView2) ──HTTP──▶ FastAPI (127.0.0.1:8000) ──▶ SQLite
        ▲                        ▲
        └───── window ───────────┘   Rust shell manages the backend's life
```

- **Business data flows over plain HTTP** — exactly like the web app. We did *not* rewrite the API as "Tauri commands"; the browser code is identical.
- **Tauri commands (Rust functions callable from JS)** are used for *shell* things: spawning/killing the backend, reading app-data paths. That's the division of labor.
- `frontendDist: ../frontend/dist` tells Tauri which built files to serve in the window. In dev, `devUrl: http://localhost:5173` points at Vite.

## 23.2 Files we create

```text
desktop/
├── package.json                    # scripts: tauri dev / tauri build
└── src-tauri/
    ├── Cargo.toml                  # Rust crate: tauri 2 + shell plugin
    ├── build.rs                    # tauri_build::build()
    ├── tauri.conf.json             # app + window + bundle config
    ├── capabilities/default.json   # permissions (least privilege)
    ├── icons/                      # generated icons
    ├── binaries/                   # ← backend.exe lives here (sidecar)
    └── src/main.rs                 # spawn/kill backend, window lifecycle
```

## 23.3 `desktop/package.json`

```json
{
  "name": "local-retail-manager-desktop",
  "private": true,
  "scripts": {
    "tauri": "tauri",
    "dev": "tauri dev",
    "build": "tauri build"
  },
  "devDependencies": {
    "@tauri-apps/cli": "^2"
  }
}
```

Install: `cd desktop && npm install`, then `npm run tauri add shell` (installs the Rust crate + plugin and registers it).

## 23.4 `desktop/src-tauri/Cargo.toml`

```toml
[package]
name = "local-retail-manager"
version = "0.1.0"
description = "Local Retail Manager desktop shell"
edition = "2021"

[build-dependencies]
tauri-build = { version = "2", features = [] }

[dependencies]
tauri = { version = "2", features = [] }
tauri-plugin-shell = "2"
serde = { version = "1", features = ["derive"] }
serde_json = "1"

[lib]
name = "local_retail_manager_lib"
crate-type = ["staticlib", "cdylib", "rlib"]
```

`build.rs`:

```rust
fn main() {
    tauri_build::build()
}
```

## 23.5 `desktop/src-tauri/tauri.conf.json`

```json
{
  "$schema": "https://schema.tauri.app/config/2",
  "productName": "Local Retail Manager",
  "version": "0.1.0",
  "identifier": "com.localretailmanager.app",
  "build": {
    "beforeDevCommand": "npm --prefix ../frontend run dev",
    "devUrl": "http://localhost:5173",
    "beforeBuildCommand": "npm --prefix ../frontend run build",
    "frontendDist": "../frontend/dist"
  },
  "app": {
    "windows": [
      {
        "title": "Local Retail Manager",
        "width": 1360,
        "height": 860,
        "minWidth": 1024,
        "minHeight": 700,
        "center": true
      }
    ],
    "security": { "csp": null }
  },
  "bundle": {
    "active": true,
    "targets": ["nsis"],
    "icon": ["icons/32x32.png", "icons/128x128.png", "icons/128x128@2x.png", "icons/icon.ico"],
    "externalBin": ["binaries/backend"]
  }
}
```

Explain:

- `beforeDevCommand` / `devUrl` — during `tauri dev`, Tauri runs Vite and loads `localhost:5173` (same as our browser workflow).
- `beforeBuildCommand` / `frontendDist` — for release, Tauri runs `vite build` and serves `frontend/dist` from inside the app.
- `externalBin: ["binaries/backend"]` — tells the bundler to include the sidecar. **The actual file must be named `backend-x86_64-pc-windows-msvc.exe`** (the platform target-triple suffix) — Tauri resolves the right one per platform. We do *not* write the suffix in the config.

## 23.6 `desktop/src-tauri/capabilities/default.json` — least privilege

```json
{
  "$schema": "../gen/schemas/desktop-schema.json",
  "identifier": "default",
  "description": "Permissions granted to the main window",
  "windows": ["main"],
  "permissions": [
    "core:default",
    "shell:allow-execute",
    "shell:allow-spawn",
    {
      "identifier": "shell:allow-sidecar",
      "allow": [
        { "name": "binaries/backend", "sidecar": true }
      ]
    }
  ]
}
```

> The scoped `shell:allow-sidecar` grants *only* our named backend the right to run — nothing else. This is capability-based security: the UI can't be tricked into executing arbitrary programs.

## 23.7 `desktop/src-tauri/src/main.rs` — the backend lifecycle

```rust
// Prevent an extra console window on Windows in release builds
#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

use std::io::Write;
use std::process::Child;
use std::sync::Mutex;

use tauri::Manager;
use tauri_plugin_shell::ShellExt;

/// Holds the running backend child process so we can kill it on exit.
struct BackendProcess(Mutex<Option<Child>>);

fn main() {
    tauri::Builder::default()
        .plugin(tauri_plugin_shell::init())
        .setup(|app| {
            // 1. The app-data directory: %APPDATA%\com.localretailmanager.app
            let data_dir = app.path().app_data_dir().expect("no app data dir");
            std::fs::create_dir_all(&data_dir).expect("cannot create data dir");

            // 2. Spawn the FastAPI backend as a sidecar child process.
            //    Env vars are how the backend finds its data folder + port.
            let sidecar = app
                .shell()
                .sidecar("binaries/backend")
                .expect("backend sidecar missing — run scripts/build_backend.bat");
            let (mut rx, child) = sidecar
                .env("LRM_DATA_DIR", data_dir.to_string_lossy().to_string())
                .env("LRM_PORT", "8000")
                .env("LRM_ENV", "production")
                .spawn()
                .expect("failed to start the backend");

            app.manage(BackendProcess(Mutex::new(Some(child))));

            // 3. Stream the backend's stdout/stderr to backend.log for debugging
            let log_file = std::fs::File::create(data_dir.join("backend.log"))
                .expect("cannot create backend.log");
            let mut log = std::io::BufWriter::new(log_file);
            tauri::async_runtime::spawn(async move {
                while let Some(line) = rx.recv().await {
                    let _ = writeln!(log, "{line}");
                }
            });

            Ok(())
        })
        .on_window_event(|window, event| {
            // 4. Kill the backend when the window closes (graceful exit)
            if let tauri::WindowEvent::Destroyed = event {
                if let Some(state) = window.try_state::<BackendProcess>() {
                    if let Ok(mut guard) = state.0.lock() {
                        if let Some(mut child) = guard.take() {
                            let _ = child.kill();
                        }
                    }
                }
            }
        })
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
```

Explain each block:

1. **app data dir** — `%APPDATA%\com.localretailmanager.app`; this becomes `LRM_DATA_DIR`, so the backend's `data/` (database, invoices, logs, backups) lands in the OS-managed per-user folder — writable without admin, backed by the user's profile.
2. **sidecar spawn** — `tauri-plugin-shell`'s `Command.sidecar` launches `binaries/backend` with env vars. The backend is a *child process*; it dies with the shell if killed.
3. **log streaming** — backend console output is captured to `backend.log` — your debugging window into a headless child process.
4. **cleanup** — on window destruction we `kill()` the child. (A more graceful path: POST `/api/shutdown`; we keep it simple and documented.)

## 23.8 Frontend: wait for the backend (startup screen)

The WebView loads faster than Python boots. `App.tsx` polls `/api/health`:

```tsx
const [ready, setReady] = useState(false);
useEffect(() => {
  let stopped = false;
  const tryOnce = async () => {
    try {
      const res = await fetch(`${API_BASE}/api/health`);
      if (res.ok) setReady(true);
    } catch { /* backend still starting */ }
  };
  const id = setInterval(async () => {
    if (stopped) return;
    await tryOnce();
    if (readyRef) clearInterval(id);
  }, 500);
  setTimeout(() => clearInterval(id), 30000); // give up after 30s
  return () => { stopped = true; clearInterval(id); };
}, []);

if (!ready) return <SplashScreen />;   // "Starting Local Retail Manager…"
```

## 23.9 Dev-mode workflow vs production

| | `npm run tauri dev` | Installed app |
|---|---|---|
| Frontend | Vite dev server (:5173, hot reload) | bundled `frontend/dist` |
| Backend | run `uvicorn` yourself in another terminal | sidecar spawned by Rust |
| Data dir | `backend/data/` (repo) | `%APPDATA%/…` (LRM_DATA_DIR) |

The CORS origin differs too: dev uses `http://localhost:5173`; the installed app uses `http://tauri.localhost` — both are already in `settings.CORS_ORIGINS`.

## ✏️ Exercise 23.1 — backend version banner

Add to `backend/app/api/routes/health.py` a `"version"` field read from a `backend/VERSION` file, and print it on the splash screen. (It's the first step toward "which build is this shop running?")

---

## ✅ Phase 23 Checkpoint

- [ ] `npm run tauri dev` opens the window and the app boots (backend started manually in dev)
- [ ] The window title, size and centered placement match the config
- [ ] Closing the window kills the backend process (check Task Manager)
- [ ] `backend.log` appears in the app-data folder in production builds

### If it doesn't work

| Error | Why | Fix |
|---|---|---|
| `Command.sidecar(...)` error: "sidecar not found" | The exe isn't named with the target triple | `binaries/backend-x86_64-pc-windows-msvc.exe` (Phase 24) |
| Permission denied for the sidecar | Capability missing the scoped `shell:allow-sidecar` | Check `capabilities/default.json` |
| Rust compile fails | Missing MSVC build tools or Rust too old | Install VS Build Tools; `rustup update` |
| Blank white window in release | `frontendDist` wrong, or `beforeBuildCommand` failed | Check `tauri.conf.json`; run `npm run tauri build` verbosely |

Commit:

```bash
git add -A
git commit -m "feat: add Tauri desktop shell with backend lifecycle"
```

---

# Phase 24 — Windows Packaging

> **Goal of this phase:** `Local Retail Manager Setup.exe` → install → desktop shortcut → the app runs with *nothing else installed* on the shop PC.

## 24.1 The three build steps

```text
1. Build the frontend    → vite build → frontend/dist (static files)
2. Build the backend     → PyInstaller → backend.exe (a self-contained Python runtime)
3. Build the Tauri app   → tauri build → bundles window + frontend + backend.exe → NSIS installer
```

## 24.2 Backend entry point — `backend/run_backend.py`

PyInstaller needs a plain script it can analyze:

```python
"""Entry point for the packaged backend.

The Tauri shell launches this exe with LRM_DATA_DIR and LRM_PORT set.
Importing app.main here ALSO makes PyInstaller bundle the whole app package.
"""
import os
import sys
import argparse

import app.main  # noqa: F401  ← critical: forces PyInstaller to see the app package


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--host", default=os.environ.get("LRM_HOST", "127.0.0.1"))
    parser.add_argument("--port", type=int, default=int(os.environ.get("LRM_PORT", "8000")))
    args = parser.parse_args()

    import uvicorn
    uvicorn.run("app.main:app", host=args.host, port=args.port, log_level="info")


if __name__ == "__main__":
    main()
```

## 24.3 PyInstaller — `scripts/build_backend.bat`

**Onefile vs onedir (the decision):**

- **onefile** — a single `backend.exe` that self-extracts to a temp dir at startup (~1–2 s extra). Simplest to embed as a Tauri sidecar. **We choose onefile.**
- **onedir** — a folder with faster startup, but you'd have to ship the folder (via Tauri resources) instead of a single sidecar file — more moving parts.

The classic pitfalls are **hidden imports** (PyInstaller can't see modules imported by strings — exactly how uvicorn and alembic load their pieces) and **data files** (alembic templates):

```bat
@echo off
REM scripts/build_backend.bat — build backend.exe and install it as the Tauri sidecar
setlocal
cd /d "%~dp0\..\backend"

call venv\Scripts\activate.bat
pip install pyinstaller==6.21.0

pyinstaller --noconfirm --onefile --name backend ^
  --hidden-import uvicorn.logging ^
  --hidden-import uvicorn.loops.auto ^
  --hidden-import uvicorn.protocols.http.auto ^
  --hidden-import uvicorn.protocols.websockets.auto ^
  --hidden-import uvicorn.lifespan.on ^
  --collect-all alembic ^
  --add-data "alembic;alembic" ^
  --add-data "alembic.ini;." ^
  run_backend.py

if errorlevel 1 exit /b 1

REM The target-triple suffix is required by Tauri for sidecars:
copy /Y dist\backend.exe ..\desktop\src-tauri\binaries\backend-x86_64-pc-windows-msvc.exe
echo Backend sidecar installed.
```

- `--hidden-import uvicorn.*` — uvicorn loads its loop/protocol implementations by string name; without these the exe starts but crashes on the first request.
- `--collect-all alembic` + `--add-data` — Alembic needs its `env.py`/template files and our `alembic/` folder at runtime (startup migration).
- We run PyInstaller **on Windows, for Windows** — PyInstaller is not a cross-compiler.

## 24.4 Full build — `scripts/build_app.bat`

```bat
@echo off
REM scripts/build_app.bat — produce the Windows installer
setlocal
cd /d "%~dp0\.."

call scripts\build_backend.bat
if errorlevel 1 exit /b 1

cd desktop
call npm install
call npm run tauri build

echo.
echo Installer: desktop\src-tauri\target\release\bundle\nsis\Local-Retail-Manager_0.1.0_x64-setup.exe
```

## 24.5 What the installer does (NSIS)

- Installs the app **per-user** (`installMode: currentUser` → no admin prompt) into `%LOCALAPPDATA%\Programs\Local Retail Manager`.
- Creates a **desktop shortcut** + Start-menu entry.
- **Data is never in Program Files** — the backend writes to `%APPDATA%\com.localretailmanager.app` (set by Rust), so:
  - **Updating** = installing the new version over it; the database, invoices and backups survive untouched.
  - **Uninstalling** removes the program files but **keeps the data folder** by default. We document this clearly in the app's Settings page ("Uninstall does not delete your data. Copy backups/ first if you want them off this PC."). If you want uninstall to wipe data, add a `delete` directive — but that's a scary default; we keep data.

## 24.6 Environment configuration in production

There is **no `.env` in production**. The Rust shell sets `LRM_DATA_DIR`, `LRM_PORT`, `LRM_ENV=production`; everything else has sane defaults. Secrets (`LRM_SECRET_KEY`) can be supplied by the owner via a Windows environment variable if they ever need to, but the default is fine for a local app.

## 24.7 Code signing and SmartScreen

An unsigned exe triggers Windows SmartScreen ("Unknown publisher"). Options:

- Accept it (click *More info → Run anyway*) — fine for internal/own use.
- Buy a code-signing certificate (OV/EV) and sign `backend.exe` and the installer — required if you distribute widely.
- For personal distribution to a few shops, an SHA-256 hash + instructions is often enough.

## ✏️ Exercise 24.1 — version plumbing

Wire `backend/VERSION` (e.g. `0.1.0`) through: `health.py` exposes it → splash screen shows it → `tauri.conf.json` `version` matches. Now builds are identifiable.

---

## ✅ Phase 24 Checkpoint

- [ ] `scripts\build_backend.bat` → `desktop\src-tauri\binaries\backend-x86_64-pc-windows-msvc.exe` exists
- [ ] Running that exe from a terminal serves `/api/health` (proves PyInstaller bundling works standalone)
- [ ] `scripts\build_app.bat` → `…\bundle\nsis\Local-Retail-Manager_…-setup.exe` exists
- [ ] On a clean machine (or VM): install → shortcut → app opens → login → dashboard loads → create a sale → PDF invoice downloads → restart → data still there
- [ ] Uninstall → reinstall → data intact

### If it doesn't work

| Error | Why | Fix |
|---|---|---|
| Backend exe opens a console window | `run_backend.py` has no `windows_subsystem` attribute (that's the *shell's* job) | Acceptable in dev; the Tauri sidecar is launched hidden by Rust — if you see a console, add `#!python`/`--console` control in the PyInstaller spec |
| `ModuleNotFoundError: uvicorn.protocols...` at runtime | Missing hidden imports | Re-run with the full `--hidden-import` list (24.3) |
| Alembic "Can't locate template" at startup | `--add-data` path wrong | `--add-data "alembic;alembic"` (semicolon on Windows) |
| Installer fails: file locked | Old app still running | Close the app before installing |

Commit:

```bash
git add -A
git commit -m "feat: add Windows packaging scripts and installer build"
```

---

# Phase 25 — Production Architecture

> **Goal of this phase:** understand the installed app as a *system* — what happens from double-click to dashboard, and how it survives failure.

## 25.1 The boot sequence

```mermaid
sequenceDiagram
    participant U as User (double-click)
    participant T as Tauri shell (Rust)
    participant B as Backend process (FastAPI)
    participant D as SQLite + folders
    participant R as React UI (WebView2)

    U->>T: launch Local Retail Manager.exe
    T->>T: resolve %APPDATA% dir
    T->>B: spawn backend.exe (LRM_DATA_DIR, LRM_PORT)
    B->>B: setup logging → app.log
    B->>B: ensure data folders exist
    B->>B: run Alembic migrations (upgrade head)
    B->>B: seed default Owner if fresh
    B->>B: auto-backup if newest > 24h
    B->>D: open retail.db (WAL)
    T->>R: render frontend (dist or :5173)
    R->>R: poll /api/health every 500ms
    B-->>R: {"status":"ok"}
    R->>R: show login / dashboard
```

## 25.2 Where everything lives on disk

```text
%APPDATA%\com.localretailmanager.app\
├── retail.db              ← the entire business
├── retail.db-wal / -shm   ← WAL files (normal while running)
├── database\              ← (reserved; db lives here if LRM_DATA_DIR/… configured)
├── invoices\              ← INV-20260808-0001.pdf …
├── backups\               ← retail_backup_*.db (verified snapshots)
├── exports\               ← CSV/Excel exports
├── logs\                  ← app.log (rotating) + backend.log (child output)
└── backend.log            ← the Rust-captured stdout of the backend
```

## 25.3 Normal shutdown

Close the window → Rust kills the backend child. SQLite's WAL **checkpoints** the last writes into `retail.db` on a clean close; a hard kill still recovers via WAL replay on next open (that's what WAL is for).

## 25.4 Failure modes and recovery

| Failure | What happens | Recovery |
|---|---|---|
| Backend crashes at start (port busy) | Frontend keeps polling health → splash times out after 30 s with a clear error | Fix port conflict; restart the app |
| Database file corrupt | Backend logs the error; app won't fully boot | Restore the newest verified backup from Settings → or manually replace the file from `backups/` |
| App killed mid-sale | Nothing was committed (Phase 7) | Re-enter the sale |
| Disk full | Writes fail with clear errors, logged | Free space; backups are the answer |
| Two instances running | Two backends fight over the same port/DB | (Post-MVP) single-instance mutex in Rust (`tauri-plugin-single-instance`) |

---

## ✅ Phase 25 Checkpoint

- [ ] Walk the boot sequence on a fresh install — identify each step in the logs as it happens (`app.log` + `backend.log`)
- [ ] Kill the app via Task Manager (no graceful close) → restart → dashboard still correct (WAL recovery)
- [ ] Corrupt the DB deliberately in a VM → restore from backup via Settings

Commit:

```bash
git add -A
git commit -m "docs: document production architecture"
```

---

**Next:** [Phase 26 — Advanced Features](#phase-26--advanced-features-post-mvp)
# Phase 26 — Advanced Features (post-MVP)

> **Goal of this phase:** a map of the future — what to add, *when*, and what each addition costs. **Do not implement any of this before the MVP is stable.** Each idea below is a mini-project of its own; we sketch the approach so you know the territory.

| Feature | MVP? | Approach | Cost / risk |
|---|---|---|---|
| Product CSV import/export | No | Backend: `csv` stdlib read/write to `exports/`; frontend: upload → validate → `create_product` per row (report bad rows, don't half-import — process in a transaction) | Low; huge time-saver for initial stock entry |
| Excel export | No | `openpyxl` (already in requirements, 3.1.5); reports → `.xlsx` with a styled header sheet | Low |
| Multiple shops | No | Add `shop_id` to core tables + a `shops` table; every query scoped. **Decision needed before it's easy** — retrofitting tenancy into an MVP is painful. Design it *then*, not now | High retrofitting cost; defer |
| Multiple terminals (2+ billing PCs) | No | Run the backend on a LAN PC; other PCs run the frontend in a browser pointed at it (CORS). SQLite supports a few concurrent writers — OK for 2–3 terminals with WAL + busy_timeout (already on) | Medium; SQLite becomes a bottleneck beyond ~5 terminals → then move to PostgreSQL + sync |
| Cloud backup | No | Encrypt a snapshot (age/AES) and upload to S3/Dropbox/Drive on a schedule; keep local-first with cloud as an off-site copy | Low–medium; needs a credential strategy and privacy consent |
| Optional synchronization | No | Offline-first sync is **hard**: per-record timestamps, conflict resolution (last-write-wins vs CRDTs), sync log table, id mapping. Research before building | High; do not wing it |
| Remote dashboard | No | Read-only mode: a second FastAPI process (or the same one on `0.0.0.0`) + an extra read-only token; **never** expose the billing API to the internet | Medium; security review required |
| Automatic updates | No | Tauri's updater plugin needs signed artifacts + a hosting URL; or ship NSIS reinstaller + a version-check endpoint (health already exposes `version` from Exercise 23.1) | Medium |
| Printer integration | No | Two paths: (1) "Print PDF" — what we have; (2) direct ESC/POS to a thermal printer via `win32print` (PyWin32): send the receipt bytes straight to the spooler, no PDF dialog | Medium; printer models differ |
| Advanced analytics | No | Moving averages, ABC analysis (20% of SKUs = 80% of revenue), seasonality on top of the report engine | Medium |

**The meta-rule:** every item above reuses the layers we already built. Imports call `product_service`; Excel is a writer over `report_service`; the remote dashboard reuses `report_service` + auth. Because business logic lives in services, none of these features requires touching billing code.

---

# Phase 27 — AI Features

> **Goal of this phase:** add AI *without* letting it touch money math. The rule: **the LLM explains; the database decides.**

## 27.1 The principle

An LLM is a language model, not a calculator. If you ask it "what was our profit in July?" it will confidently *invent* an answer. Our system therefore separates the two jobs completely:

```text
User question
   ↓
AI Assistant (LLM) — understands intent, chooses a tool
   ↓
Business Tools (deterministic functions)
   ↓
Database Queries (exact, verified numbers)
   ↓
Verified Results (JSON: revenue, profit, stock…)
   ↓
AI Explanation (LLM words wrapped around real numbers)
```

The LLM never computes a number. It selects a **tool**, the tool runs SQL, and the LLM only writes the *explanation* — citing the numbers the tool returned. If no tool matches, the assistant says "I can't answer that from your data" instead of guessing.

## 27.2 The tools (deterministic by design)

```python
# backend/app/services/ai_service.py — post-MVP sketch
TOOLS = {
    "profit_summary": {
        "description": "Revenue, COGS, gross/net profit for a date range",
        "params": {"from": "date", "to": "date"},
        "run": lambda db, p: report_service.profit_summary(db, p["from"], p["to"]),
    },
    "low_stock": {
        "description": "Products at or below minimum stock",
        "params": {},
        "run": lambda db, _: inventory_service.low_stock_products(db),
    },
    "restock_recommendations": {
        "description": "Products to restock this week with suggested quantities",
        "params": {},
        "run": restock_recommendations,   # pure business logic, below
    },
    "top_products": {
        "description": "Top-selling products in a period",
        "params": {"days": "int"},
        "run": lambda db, p: dashboard_service.top_products(db, p.get("days", 30)),
    },
}
```

## 27.3 Restock recommendations — deterministic, not AI

This is a business formula, not a prompt:

```python
def restock_recommendations(db: Session) -> list[dict]:
    """For each active product: suggested qty = (expected weekly demand +
    safety stock) − current stock, when positive."""
    results = []
    for p in inventory_service.low_stock_products(db):
        weekly_sold = ...  # avg weekly SALE qty from movements (last 8 weeks)
        safety = weekly_sold * 0.5            # half a week as buffer
        suggested = max(0, int((weekly_sold + safety) - p.current_stock))
        if suggested > 0:
            results.append({
                "product": p.name, "current_stock": p.current_stock,
                "weekly_demand": round(weekly_sold, 1),
                "suggested_quantity": suggested,
                "avg_cost": p.avg_cost,
                "estimated_cost": money(suggested * p.avg_cost),
            })
    return results
```

**"Which products should I restock this week?"** → the assistant calls `restock_recommendations` → the tool returns real numbers → the LLM says: *"You're low on Tata Salt (8 left, selling ~14/week). I suggest buying 28 units (~₹616 at avg cost)."* Every figure traceable to the database.

## 27.4 Safe integration (when you build it)

- Config: `AI_ENABLED=false`, `AI_MODEL`, `AI_API_KEY` in `.env`; the endpoint returns 503 when disabled.
- Endpoint `POST /api/ai/ask` (Owner only): `{question}` → intent → tool calls → response. **Never** pass raw Pydantic exceptions or SQL to the LLM.
- Privacy: prefer a local model (Ollama) so shop data never leaves the PC; if using a cloud API, get explicit consent and strip customer phone numbers before sending.
- **Core billing never depends on AI.** If the AI service is down, billing still works — the AI is an optional overlay, exactly like a report.
- Guardrails: cap token usage, log every tool call + result (audit), and add "this was generated with your data" disclaimers.

## ✏️ Exercise 27.1 — the honesty test

Ask a future assistant (or yourself): *"What was our profit last month?"* with no tool. The correct system answer is a refusal to guess — write the one-sentence fallback the assistant should use when no tool matches.

<details>
<summary><b>Answer</b></summary>

"I can only answer with numbers I can verify from your data. I don't have a tool for that question yet — try asking about profit, sales, stock, or top products."

</details>

---

## ✅ Phase 26/27 Checkpoint

- [ ] You can explain, for each advanced feature, *why it's post-MVP* and *which layer it plugs into*
- [ ] The AI architecture diagram (27.1) is clear: LLM explains, database decides
- [ ] Restock recommendations are a deterministic function — no LLM math anywhere

---

# Git Workflow — Teaching Git as Part of the Project

Git has been woven through every phase (each phase ends with a commit). This section pulls the whole workflow together.

## The commands, and what each does

```bash
git init                # turn this folder into a repository
git status              # what changed / what's untracked
git add <file>          # stage a change (git add -A stages everything)
git commit -m "msg"     # snapshot the staged changes with a message
git log --oneline       # history, one line per commit
git branch <name>       # create a branch (a parallel timeline)
git checkout <name>     # switch to it
git merge <name>        # bring a branch's changes into the current one
git push origin main    # upload commits to GitHub
git pull                # download remote changes
git tag v0.1.0          # mark a release point
```

## Why meaningful commits matter

Every commit is a **save point with a message**. When a bug appears in billing, `git log` shows `feat: implement billing with transactional sale flow` — you know *exactly* which change to inspect, and `git diff` shows every line of it. Bad messages ("stuff", "fix") turn history into noise; good messages make history a debugging tool.

## Commit convention we used (and why)

```text
feat: initialize project structure
feat: add database layer with models and initial migration
feat: add product management (CRUD, search, categories)
feat: add inventory ledger, adjustments, low-stock, valuation
feat: implement billing with transactional sale flow
feat: add invoice generation (A4 PDF + thermal receipt)
feat: add React app shell, API layer, and products page
feat: add POS billing screen with cart and live totals
feat: add purchases with inventory increase and supplier payments
feat: add customers with Khata ledger and balances
feat: add suppliers with balances and ledger
feat: add expenses and profit calculation engine
feat: add dashboard with live metrics and charts
feat: add reports engine, routes, and reports UI with CSV export
feat: add exact barcode lookup and scanning flow
feat: add authentication and role-based authorization
feat: add backup and restore with verification and rotation
feat: add logging, integrity backstops, and error handling
feat: add backend and frontend test suites
feat: add Tauri desktop shell with backend lifecycle
feat: add Windows packaging scripts and installer build
fix: ...      (when something breaks later)
docs: ...     (when only docs change)
```

**The rule:** one commit per working feature; a feature is done when its checkpoint passes. This is also the branch strategy for solo work: `main` is always runnable; short `feature/xyz` branches for experiments.

## GitHub

```bash
# once: create an empty repo on github.com, then
git remote add origin https://github.com/<you>/local-retail-manager.git
git push -u origin main
```

**Never push** `.env`, `retail.db`, `venv/`, `node_modules/` — the `.gitignore` from Phase 1 handles this. When the installer builds successfully, tag it:

```bash
git tag v0.1.0
git push origin v0.1.0
```

---

# Root project files

## README.md

```markdown
# Local Retail Manager

Offline-first billing, inventory, and retail management for small shops.
Runs entirely on the shop's Windows PC — no internet required.

## Features
- POS billing with barcode scanning, discounts, tax, PDF invoices (A4 + 80mm)
- Inventory movement ledger (purchase / sale / return / adjustment / damage)
- Purchases, suppliers, customers with Khata (credit) and balances
- Expenses, gross/net profit, dashboard with live charts
- 11 report types with date filters and CSV export
- Role-based login (Owner / Manager / Cashier)
- Automatic verified backups with one-click restore
- Packaged as a Windows installer (Tauri + FastAPI + SQLite)

## Stack
React 19 · TypeScript · Vite 8 · Tailwind CSS v4 · Zustand
FastAPI · SQLAlchemy 2 · Pydantic v2 · Alembic · SQLite · ReportLab
Tauri 2 (Rust) · PyInstaller

## Development
See docs/local-retail-manager-guide.md for the full build-from-scratch course.

# backend
cd backend && python -m venv venv && source venv/Scripts/activate
pip install -r requirements.txt
alembic upgrade head
uvicorn app.main:app --reload          # http://127.0.0.1:8000/docs

# frontend
cd frontend && npm install && npm run dev    # http://localhost:5173

# tests
cd backend && pytest -q
cd frontend && npx vitest run

## Build the installer (Windows)
scripts\build_app.bat        # → desktop\src-tauri\target\release\bundle\nsis\*.exe

## Data locations
- Development: backend/data/ (database, invoices, backups, logs)
- Installed app: %APPDATA%\com.localretailmanager.app\

## License
MIT — see LICENSE
```

## LICENSE (MIT)

```text
MIT License

Copyright (c) 2026 Local Retail Manager contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

**Next:** [Troubleshooting Guide](#troubleshooting-guide)
# Troubleshooting Guide

> Organized by category. Every entry follows: **Error → Why → Diagnose → Fix → Prevent**. The *why* matters — a fix without understanding is a future bug.

## Python Problems

### `ModuleNotFoundError: No module named 'fastapi'`
- **Why:** the interpreter running your code isn't the venv where you installed packages.
- **Diagnose:** `which python` (should show `.../backend/venv/...`), `pip show fastapi`.
- **Fix:** `source venv/Scripts/activate` in every new terminal; reinstall `pip install -r requirements.txt`.
- **Prevent:** always check the `(venv)` prompt before running anything.

### `python` runs the wrong version
- **Why:** multiple Pythons on PATH; the first one wins.
- **Diagnose:** `where python`.
- **Fix:** reorder PATH, or always activate the venv (which pins the interpreter).

### `pip install` writes to the wrong place / `externally-managed-environment`
- **Why:** global pip on a system Python.
- **Fix:** create and activate a venv first, then install into it.
- **Prevent:** the venv rule, every time.

## FastAPI Problems

### Route returns 404 for an endpoint that exists
- **Why:** the router isn't included in `create_app()`, or the route is defined after a conflicting `/{param}` route.
- **Diagnose:** open `/docs` — is the endpoint listed?
- **Fix:** `app.include_router(x.router)`; reorder `by-barcode` before `{id}`.
- **Prevent:** add routers the moment you create them; keep `/docs` open while developing.

### `422 Unprocessable Entity` on valid-looking data
- **Why:** Pydantic rejected something: wrong type, missing field, or (classic) a Decimal field receiving a string.
- **Diagnose:** read the error body — it lists the failing field and reason.
- **Fix:** match the request to the schema exactly (booleans as `true`, numbers not quoted).

### Every request returns 500 with `IntegrityError`
- **Why:** a UNIQUE/FK constraint tripped and nothing caught it.
- **Diagnose:** the traceback names the table/column.
- **Fix:** service-level pre-checks (409s) + the global `IntegrityError` handler.
- **Prevent:** check uniqueness in services; keep DB constraints as the backstop.

## SQLAlchemy Problems

### `sqlalchemy.exc.NoResultFound` / rows not appearing
- **Why:** the session was committed/expired unexpectedly, or you filtered wrong.
- **Diagnose:** `expire_on_commit=False` is set; confirm the commit happened and the query is right (`session.query(Product).all()` in a scratch).
- **Fix:** use `db.refresh(obj)` after commit when returning objects.

### Relationship attribute is `None` when you expect data
- **Why:** lazy loading didn't fire (e.g., after the session closed) or the FK was never set.
- **Diagnose:** check the `_id` column value.
- **Fix:** set the FK; load the object inside the session.

### DetachedInstanceError
- **Why:** you're reading a relationship *after* the session that loaded it closed (happens when serializing outside a request).
- **Diagnose:** traceback shows the access point.
- **Fix:** build the response (e.g. `_to_read`) inside the route/service while the session is open.
- **Prevent:** never pass sessions or ORM objects across request boundaries.

## SQLite Problems

### `database is locked`
- **Why:** another connection holds a write lock (busy_timeout expired).
- **Diagnose:** check for a second process holding the DB; look for `engine.dispose()` misuse.
- **Fix:** WAL + busy_timeout are already on; ensure one backend process only; close long transactions fast.
- **Prevent:** short transactions, single process, WAL.

### Table/column doesn't exist although the model defines it
- **Why:** migrations not run, or model not imported into `models/__init__.py`.
- **Diagnose:** `alembic upgrade head`; check `alembic_version`.
- **Fix:** run the migration; add the import.
- **Prevent:** the import rule from Phase 3.

## Alembic Problems

### `alembic revision --autogenerate` produced an empty migration (or nothing)
- **Why:** `target_metadata` empty or models not imported.
- **Diagnose:** in `env.py` print `Base.metadata.tables.keys()`.
- **Fix:** import `from app.models import Base` (and all models in `__init__.py`).
- **Prevent:** import every model (Phase 3 rule).

### `No such revision` / database says it's already at head
- **Why:** `alembic_version` is ahead of your files (e.g., DB restored from a newer backup).
- **Diagnose:** `alembic history`, `alembic current`.
- **Fix:** `alembic stamp <the-matching-revision>` or restore the matching backup.
- **Prevent:** keep backups and code in sync; tag releases.

### Autogenerate wants to drop a column that exists
- **Why:** usually an enum type change or a server-default difference it misreads.
- **Diagnose:** read the generated file carefully before applying.
- **Fix:** hand-edit the migration; autogenerate is a draft, not a verdict.

## React / TypeScript Problems

### Page renders blank with a console error
- **Why:** a runtime exception in a component (often a `null` where an object was expected).
- **Diagnose:** DevTools console — the traceback names the component.
- **Fix:** guard with `?.` / early returns; use the error state pattern.
- **Prevent:** TypeScript strict + `null`-aware types on API responses.

### `Type 'undefined' is not assignable to type 'string'` — types don't match the API
- **Why:** your `types/index.ts` drifted from the backend schemas.
- **Diagnose:** compare the two files side by side.
- **Fix:** update the type; add the field on both sides.
- **Prevent:** treat the type file as a contract; update it with every backend change.

### Data doesn't refresh after an action
- **Why:** you mutated state without re-fetching, or the refetch dependency array is stale.
- **Diagnose:** check the `useEffect` deps.
- **Fix:** call `refetch()`/`load()` after create/update/delete (the pattern we used everywhere).

### Tailwind classes don't apply
- **Why:** v4 plugin not wired, or the class is generated dynamically.
- **Diagnose:** check `vite.config.ts` plugins and `index.css`.
- **Fix:** add `tailwindcss()`; avoid string-concatenated class names (use full class names in templates).

## CORS Problems

### Browser blocks the API call (`No 'Access-Control-Allow-Origin'`)
- **Why:** the origin isn't in `CORS_ORIGINS`.
- **Diagnose:** DevTools Network → the failing request's response headers.
- **Fix:** add the origin (`http://localhost:5173` dev, `http://tauri.localhost` packaged).
- **Prevent:** both origins are already in `settings.CORS_ORIGINS`.

## Tauri / Rust Problems

### `sidecar "binaries/backend" not found`
- **Why:** the exe isn't at `desktop/src-tauri/binaries/backend-x86_64-pc-windows-msvc.exe`.
- **Diagnose:** `ls desktop/src-tauri/binaries`.
- **Fix:** run `scripts\build_backend.bat`.
- **Prevent:** make build_backend a documented step of every release.

### `permission denied` executing the sidecar
- **Why:** capability file lacks the scoped `shell:allow-sidecar` entry.
- **Diagnose:** read the runtime error; check `capabilities/default.json`.
- **Fix:** add the scoped permission (Phase 23.6).
- **Prevent:** keep capabilities reviewed when adding shell usage.

### Rust build fails: `link.exe not found`
- **Why:** MSVC C++ build tools missing.
- **Diagnose:** `cargo build` error text.
- **Fix:** install Visual Studio Build Tools ("Desktop development with C++").
- **Prevent:** install once, before Phase 23.

### `cargo build` very slow first time
- **Why:** compiling hundreds of crates.
- **Fix:** wait; subsequent builds are incremental.

## Windows Problems

### App won't start: SmartScreen "Unknown publisher"
- **Why:** unsigned exe.
- **Fix:** More info → Run anyway; or sign (Phase 24.7).

### Port 8000 already in use
- **Why:** a previous backend instance is still running.
- **Diagnose:** `netstat -ano | findstr 8000`.
- **Fix:** kill the process (Task Manager) or set `LRM_PORT` to another port.
- **Prevent:** Tauri kills its child on exit — check Task Manager after crashes.

### Files locked when restoring/moving the database
- **Why:** the backend holds the file open.
- **Diagnose:** the restore error message.
- **Fix:** close the app fully before manual file operations; rely on the in-app restore (it disposes the engine first).

## PDF Problems

### ₹ shows as `□`
- **Why:** Helvetica can't render U+20B9.
- **Fix:** register a TTF (Arial/Segoe on Windows) — `_register_fonts()` in `pdf/invoice.py`.
- **Prevent:** keep the font-fallback logic; test with ₹ amounts.

### PDF fails to open / "file is corrupted"
- **Why:** an exception during `build()` produced a partial file.
- **Diagnose:** the console traceback; check the file size (0 bytes = failure).
- **Fix:** fix the offending data; delete the bad file and regenerate (invoice service overwrites with `force=True` or re-downloads).
- **Prevent:** log-and-continue design (invoice is best-effort).

## Printer Problems

### Receipt prints with wrong width / cut off
- **Why:** printer paper size doesn't match the 80mm layout.
- **Diagnose:** printer settings → paper size.
- **Fix:** configure the thermal printer to 80mm; or adjust `render_thermal_receipt` margins.

### Barcode scanner types letters instead of digits
- **Why:** scanner in keyboard mode with wrong layout, or caps lock.
- **Fix:** scanner manual → keyboard HID mode; test with the manufacturer's config barcodes.

## Database Problems

### "Negative stock" appears (should be impossible)
- **Why:** a bypass of `record_movement` wrote `current_stock` directly, or `allow_negative=True` was used somewhere.
- **Diagnose:** run `POST /api/inventory/reconcile`; then check movement history for the offending row.
- **Fix:** fix the bypass; adjust stock with a documented ADJUSTMENT movement.
- **Prevent:** the only-write-through-`record_movement` rule.

### Two invoices with the same number
- **Why:** numbering race (single user: near-impossible; two terminals: possible).
- **Diagnose:** query `sales` grouped by `invoice_no`.
- **Fix:** the UNIQUE constraint blocks it going forward; the retry loop handles the race.
- **Prevent:** keep the retry + constraint in place.

## Packaging Problems

### PyInstaller exe starts then crashes with `ModuleNotFoundError`
- **Why:** a string-imported module wasn't bundled.
- **Diagnose:** run the exe from a terminal — it prints the missing module.
- **Fix:** add the `--hidden-import` / `--collect-all` flags (Phase 24.3).
- **Prevent:** keep the build script's flag list as the canonical set.

### Installer builds but the app opens a blank window
- **Why:** `frontendDist` wrong or `beforeBuildCommand` failed silently.
- **Diagnose:** `desktop/src-tauri/target/release/...` — does `dist` exist? Run `npm run tauri build` with output visible.
- **Fix:** fix the frontend build; check `tauri.conf.json` paths.

---

# API Reference

## Conventions

- **Base URL:** `http://127.0.0.1:8000` (dev). All endpoints are under `/api`.
- **Auth:** `Authorization: Bearer <token>` except `/api/auth/login` and `/api/health`.
- **Errors:** every error returns `{"detail": ...}`:
  - AppError → `{"detail": {"code": "conflict", "message": "…"}}` with a 4xx status.
  - Pydantic validation → `{"detail": [field errors]}` with **422**.
  - Unexpected → `{"detail": {"code": "internal_error", "message": "Something went wrong"}}` with **500** (and a log line).
- **Pagination:** list endpoints accept `page` (≥1) and `size`; return `{items, total, page, size}`.
- **Dates:** ISO-8601 (`2026-08-08T00:00:00`). List filters accept `from_date`/`to_date`.
- **Money:** amounts are JSON numbers (2 decimal places).
- **Interactive docs:** `/docs` (Swagger UI) — the fastest way to explore everything below.

## Error codes used by the frontend

| code | HTTP | Meaning |
|---|---|---|
| `validation_failed` | 400 | Business validation failed |
| `not_found` | 404 | Resource missing |
| `conflict` | 409 | Duplicate / conflicting state (barcode, invoice, stock, return) |
| `insufficient_stock` | 409 | Not enough stock for a sale |
| `authentication_failed` | 401 | Bad/missing/expired token |
| `permission_denied` | 403 | Role not allowed |

---

## Auth

### POST /api/auth/login
- **Purpose:** exchange credentials for a JWT.
- **Body:** `{"username": "owner", "password": "admin123"}`
- **Response 200:**
```json
{
  "access_token": "eyJhbGciOiJIUzI1NiIs...",
  "token_type": "bearer",
  "user": {"id": 1, "username": "owner", "full_name": "Shop Owner", "role": "OWNER", "is_active": true}
}
```
- **Errors:** 401 `authentication_failed` (unknown user / wrong password — same message for both).

### GET /api/auth/me
- **Purpose:** current user. **Response:** `UserRead`. **Errors:** 401.

## Users (Owner only)

| Method | URL | Purpose | Success |
|---|---|---|---|
| GET | `/api/users` | list users | 200 |
| POST | `/api/users` | create `{username, full_name, password, role}` | 201 |
| PATCH | `/api/users/{id}` | edit name/role/active | 200 |
| POST | `/api/users/{id}/password` | reset `{password}` | 200 |

**Errors:** 401/403 (non-owner), 409 (duplicate username).

## Categories

| Method | URL | Purpose | Success |
|---|---|---|---|
| GET | `/api/categories` | list | 200 |
| POST | `/api/categories` | create `{name, description?}` | 201 |
| PATCH | `/api/categories/{id}` | update | 200 |
| DELETE | `/api/categories/{id}` | delete (409 if products use it) | 204 |

## Products

| Method | URL | Purpose | Success |
|---|---|---|---|
| GET | `/api/products?search=&category_id=&include_inactive=&page=&size=` | list/search | 200 |
| POST | `/api/products` | create | 201 |
| GET | `/api/products/{id}` | get one | 200 |
| PATCH | `/api/products/{id}` | update | 200 |
| DELETE | `/api/products/{id}` | deactivate | 204 |
| GET | `/api/products/by-barcode/{barcode}` | exact scan lookup | 200/404 |

**POST /api/products — example request:**
```json
{
  "name": "Tata Salt",
  "sku": "TATA-001",
  "barcode": "8901002101101",
  "category_id": 1,
  "purchase_price": 22,
  "selling_price": 28,
  "tax_rate": 0,
  "min_stock": 20
}
```
**Response 201:**
```json
{
  "id": 1, "name": "Tata Salt", "sku": "TATA-001", "barcode": "8901002101101",
  "category_id": 1, "category_name": "Groceries", "purchase_price": 22.0,
  "selling_price": 28.0, "tax_rate": 0.0, "min_stock": 20.0,
  "current_stock": 0.0, "avg_cost": 0.0, "is_active": true,
  "created_at": "2026-08-08T10:00:00", "updated_at": "2026-08-08T10:00:00"
}
```
**Errors:** 409 `conflict` (duplicate SKU/barcode), 422 (invalid values), 404 (bad category_id).

## Customers

| Method | URL | Purpose | Success |
|---|---|---|---|
| GET | `/api/customers?search=&page=&size=` | list | 200 |
| POST | `/api/customers` | create `{name, phone?, address?, notes?}` | 201 |
| GET | `/api/customers/{id}` | get | 200 |
| PATCH | `/api/customers/{id}` | update | 200 |
| GET | `/api/customers/outstanding` | balance > 0, owed most first | 200 |
| GET | `/api/customers/{id}/balance` | `{"customer_id": 1, "balance": 500.0}` | 200 |
| GET | `/api/customers/{id}/ledger` | Khata entries + running balance | 200 |
| POST | `/api/customers/{id}/payments` | record payment `{amount, method, reference?}` | 201 |

## Suppliers

Mirror of Customers: `GET/POST /api/suppliers`, `GET/PATCH /api/suppliers/{id}`, `GET /api/suppliers/outstanding`, `GET /api/suppliers/{id}/balance`, `GET /api/suppliers/{id}/ledger`, `POST /api/suppliers/{id}/payments`.

## Sales

| Method | URL | Purpose | Success |
|---|---|---|---|
| POST | `/api/sales` | complete a sale | 201 |
| GET | `/api/sales?from_date=&to_date=&customer_id=&search=&page=&size=` | list | 200 |
| GET | `/api/sales/{id}` | get full sale | 200 |
| POST | `/api/sales/{id}/return` | return items `{items:[{product_id, quantity}]}` | 200 |
| GET | `/api/sales/{id}/invoice` | PDF (A4) | 200 |
| GET | `/api/sales/{id}/receipt` | PDF (80 mm) | 200 |

**POST /api/sales — example request:**
```json
{
  "customer_id": null,
  "discount_pct": 0,
  "items": [{"product_id": 1, "quantity": 3, "unit_price": 28, "tax_rate": 0}],
  "payments": [{"method": "CASH", "amount": 84}]
}
```
**Response 201:** the full `SaleRead` (id, invoice_no, totals, items[], payments[]) — the invoice number is assigned server-side (`INV-20260808-0001`).
**Errors:** 409 `insufficient_stock`, 404 (product), 422 (empty items, bad values).
**Notes:** payment methods: `CASH | UPI | CARD | CREDIT | BANK`. For a credit sale send no real payments (or `method: CREDIT` with amount 0) — credit is not money (Phase 12).

## Purchases

| Method | URL | Purpose | Success |
|---|---|---|---|
| POST | `/api/purchases` | record purchase | 201 |
| GET | `/api/purchases?from_date=&to_date=&supplier_id=&search=&page=&size=` | list | 200 |
| GET | `/api/purchases/{id}` | get | 200 |
| POST | `/api/purchases/{id}/pay` | `{amount, method}` → supplier payment | 201 |

**POST /api/purchases — example request:**
```json
{
  "supplier_id": 1,
  "items": [{"product_id": 1, "quantity": 50, "unit_cost": 22}],
  "paid_amount": 1100,
  "payment_method": "CASH"
}
```
**Effects:** stock +50, avg cost updated, purchase_no `PUR-20260808-0001`, status `COMPLETED` (paid) or `PARTIAL`.

## Expenses

| Method | URL | Purpose | Success |
|---|---|---|---|
| GET | `/api/expenses?from_date=&to_date=&category=&page=&size=` | list | 200 |
| POST | `/api/expenses` | `{expense_date?, category, amount, description?}` | 201 |
| PATCH | `/api/expenses/{id}` | update | 200 |
| DELETE | `/api/expenses/{id}` | delete | 204 |
| GET | `/api/expenses/categories` | distinct categories | 200 |
| GET | `/api/expenses/summary?from=&to=` | `{total}` for the range | 200 |

## Inventory

| Method | URL | Purpose | Success |
|---|---|---|---|
| GET | `/api/inventory/movements?product_id=&movement_type=&page=&size=` | ledger | 200 |
| POST | `/api/inventory/adjust` | `{product_id, new_stock, reason}` | 201 |
| POST | `/api/inventory/damage` | `{product_id, quantity, note}` | 201 |
| POST | `/api/inventory/reconcile` | rebuild cache from ledger | 200 |
| GET | `/api/inventory/low-stock` | restock list | 200 |
| GET | `/api/inventory/stock-value` | `{value}` | 200 |

## Dashboard

### GET /api/dashboard/summary
```json
{
  "today": {"revenue": 840.0, "profit": 180.0, "transactions": 10},
  "low_stock": [{"id": 2, "name": "Sugar", "current_stock": 5, "min_stock": 20}],
  "top_products": [{"product_id": 1, "name": "Tata Salt", "sold": 42}],
  "recent_sales": [{"id": 9, "invoice_no": "INV-20260808-0009", "total": 84, "sale_date": "…", "customer_name": null}],
  "revenue_series": [{"date": "2026-07-26", "value": 0}, …14 days],
  "expense_series": […],
  "profit_series": […]
}
```

## Reports

All take `from_date`/`to_date` (except inventory/customers/suppliers/dead-stock):

| Method | URL | Returns |
|---|---|---|
| GET | `/api/reports/profit` | `{revenue, cogs, gross_profit, expenses, net_profit}` |
| GET | `/api/reports/sales-daily` | per-day `{date, transactions, revenue}` |
| GET | `/api/reports/sales-monthly` | per-month `{month, transactions, revenue}` |
| GET | `/api/reports/product-sales` | per-product `{product_id, name, units, amount}` |
| GET | `/api/reports/purchases` | purchases with `balance` |
| GET | `/api/reports/expenses` | `{total, by_category[]}` |
| GET | `/api/reports/inventory` | `{stock_value, low_stock[], dead_stock[]}` |
| GET | `/api/reports/customers` | balances, most owed first |
| GET | `/api/reports/suppliers` | balances, most owed first |
| GET | `/api/reports/dead-stock?days=60` | products with no sales in N days |

## Settings (Owner)

| Method | URL | Purpose |
|---|---|---|
| GET | `/api/settings` | shop profile (name, address, phone, gstin, currency, default_tax_rate, invoice_footer) |
| PUT | `/api/settings` | update any of the above |

## Backups (Owner)

| Method | URL | Purpose |
|---|---|---|
| GET | `/api/backups` | list `{filename, size, created_at}` |
| POST | `/api/backups` | create verified backup + rotate |
| POST | `/api/backups/restore` | `{filename}` — validates, safety-backups, restores |

## Health

### GET /api/health
`{"status": "ok", "app": "Local Retail Manager", "version": "0.1.0"}` — used by the desktop shell's startup polling.
# Database Reference

## 1. The complete schema

| Table | Purpose |
|---|---|
| `users` | Login accounts with roles |
| `categories` | Product groupings |
| `products` | Sellable items + stock/cost caches |
| `customers` | Buyers (incl. Khata) |
| `suppliers` | Sellers to us |
| `sales` | Sale headers (one invoice) |
| `sale_items` | Sale lines |
| `purchases` | Purchase headers |
| `purchase_items` | Purchase lines |
| `payments` | Real money in/out (signed) |
| `expenses` | Operating costs |
| `inventory_movements` | The stock audit ledger |
| `app_settings` | Single-row shop profile |
| `alembic_version` | Alembic's bookkeeping (auto) |

### users
| Column | Type | Constraints | Notes |
|---|---|---|---|
| id | INTEGER | PK | |
| username | VARCHAR(50) | **UNIQUE**, INDEX | login name |
| full_name | VARCHAR(100) | NOT NULL | |
| password_hash | VARCHAR(200) | NOT NULL | bcrypt only |
| role | VARCHAR(20) | NOT NULL, default CASHIER | OWNER/MANAGER/CASHIER |
| is_active | BOOLEAN | default true | soft delete |
| created_at / updated_at | DATETIME | NOT NULL | |

**Relationships:** 1:N → `sales.created_by_id`, `payments.created_by_id`, `expenses.created_by_id`, `inventory_movements.created_by_id`.

### categories
| Column | Type | Constraints |
|---|---|---|
| id | INTEGER | PK |
| name | VARCHAR(100) | **UNIQUE**, INDEX |
| description | VARCHAR(255) | NULL |

**Relationships:** 1:N → `products.category_id` (ON DELETE SET NULL).

### products
| Column | Type | Constraints | Notes |
|---|---|---|---|
| id | INTEGER | PK | |
| name | VARCHAR(200) | NOT NULL, INDEX | |
| sku | VARCHAR(50) | **UNIQUE**, INDEX | nullable |
| barcode | VARCHAR(100) | **UNIQUE**, INDEX | nullable — scan key |
| category_id | INTEGER | FK→categories SET NULL, INDEX | nullable |
| purchase_price | NUMERIC(12,2) | NOT NULL, default 0 | |
| selling_price | NUMERIC(12,2) | NOT NULL, default 0 | |
| tax_rate | NUMERIC(5,2) | NOT NULL, default 0 | percent |
| min_stock | NUMERIC(12,2) | NOT NULL, default 0 | low-stock threshold |
| current_stock | NUMERIC(12,2) | NOT NULL, default 0 | **cache** (ledger is truth) |
| avg_cost | NUMERIC(12,2) | NOT NULL, default 0 | weighted average |
| is_active | BOOLEAN | default true | soft delete |
| created_at / updated_at | DATETIME | NOT NULL | |

**Relationships:** N:1 → category; 1:N → sale_items, purchase_items, inventory_movements.

### customers
| Column | Type | Constraints |
|---|---|---|
| id | INTEGER | PK |
| name | VARCHAR(150) | NOT NULL, INDEX |
| phone | VARCHAR(20) | INDEX, NULL |
| address / notes | VARCHAR(255) | NULL |
| is_active | BOOLEAN | default true |

**Relationships:** 1:N → sales (`customer_id`, SET NULL), payments (`customer_id`).

### suppliers — same shape as customers (name, phone, address, notes, is_active).
**Relationships:** 1:N → purchases, payments.

### sales
| Column | Type | Constraints | Notes |
|---|---|---|---|
| id | INTEGER | PK | |
| invoice_no | VARCHAR(30) | **UNIQUE**, INDEX | `INV-YYYYMMDD-NNNN` |
| customer_id | INTEGER | FK→customers SET NULL, INDEX | |
| subtotal | NUMERIC(12,2) | NOT NULL | Σ line totals |
| discount_pct | NUMERIC(5,2) | NOT NULL, default 0 | |
| discount | NUMERIC(12,2) | NOT NULL | subtotal × pct |
| tax | NUMERIC(12,2) | NOT NULL | tax on discounted value |
| total | NUMERIC(12,2) | NOT NULL | subtotal − discount + tax |
| status | VARCHAR(20) | default COMPLETED | COMPLETED/RETURNED |
| sale_date | DATETIME | NOT NULL, INDEX | |
| notes | VARCHAR(255) | NULL | |
| created_by_id | INTEGER | FK→users SET NULL | |

**Relationships:** N:1 customer; 1:N → sale_items (CASCADE), payments (SET NULL).

### sale_items
| Column | Type | Constraints |
|---|---|---|
| id | INTEGER | PK |
| sale_id | INTEGER | FK→sales **CASCADE**, INDEX |
| product_id | INTEGER | FK→products **RESTRICT**, INDEX |
| quantity | NUMERIC(12,2) | NOT NULL |
| unit_price | NUMERIC(12,2) | NOT NULL |
| tax_rate | NUMERIC(5,2) | default 0 |
| line_total | NUMERIC(12,2) | NOT NULL (qty × price) |
| returned_qty | NUMERIC(12,2) | default 0 |

### purchases
| Column | Type | Constraints | Notes |
|---|---|---|---|
| id | INTEGER | PK | |
| purchase_no | VARCHAR(30) | **UNIQUE**, INDEX | `PUR-YYYYMMDD-NNNN` |
| supplier_id | INTEGER | FK→suppliers SET NULL, INDEX | |
| purchase_date | DATETIME | NOT NULL, INDEX | |
| subtotal / discount / tax / total | NUMERIC(12,2) | NOT NULL | |
| paid_amount | NUMERIC(12,2) | default 0 | |
| payment_method | VARCHAR(20) | default CASH | |
| status | VARCHAR(20) | default COMPLETED | COMPLETED/PARTIAL |
| notes | VARCHAR(255) | NULL | |
| created_by_id | INTEGER | FK→users SET NULL | |

### purchase_items — `purchase_id` (CASCADE), `product_id` (RESTRICT), `quantity`, `unit_cost`, `tax_rate`, `line_total`.

### payments
| Column | Type | Constraints | Notes |
|---|---|---|---|
| id | INTEGER | PK | |
| sale_id | INTEGER | FK→sales SET NULL, INDEX | one of sale/purchase/customer/supplier |
| purchase_id | INTEGER | FK→purchases SET NULL, INDEX | |
| customer_id | INTEGER | FK→customers SET NULL, INDEX | |
| supplier_id | INTEGER | FK→suppliers SET NULL, INDEX | |
| amount | NUMERIC(12,2) | NOT NULL | **signed** (+received, −paid/refund) |
| method | VARCHAR(20) | default CASH | CASH/UPI/CARD/CREDIT/BANK |
| reference | VARCHAR(100) | NULL | txn id, note |
| paid_at | DATETIME | NOT NULL, INDEX | |
| created_by_id | INTEGER | FK→users SET NULL | |

### expenses
| Column | Type | Constraints |
|---|---|---|
| id | INTEGER | PK |
| expense_date | DATETIME | NOT NULL, INDEX |
| category | VARCHAR(50) | NOT NULL, INDEX (free text) |
| amount | NUMERIC(12,2) | NOT NULL |
| description | VARCHAR(255) | NULL |
| created_by_id | INTEGER | FK→users SET NULL |

### inventory_movements
| Column | Type | Constraints | Notes |
|---|---|---|---|
| id | INTEGER | PK | |
| product_id | INTEGER | FK→products **RESTRICT**, INDEX | |
| movement_type | VARCHAR(20) | NOT NULL, INDEX | PURCHASE/SALE/RETURN/ADJUSTMENT/DAMAGE |
| quantity | NUMERIC(12,2) | NOT NULL | **signed** |
| unit_cost | NUMERIC(12,2) | NOT NULL, default 0 | snapshot at time of movement |
| ref_type | VARCHAR(30) | NULL | "SALE", "PURCHASE", "RETURN", "ADJUSTMENT", "DAMAGE" |
| ref_id | INTEGER | NULL | document id |
| note | VARCHAR(255) | NULL | why (human-readable) |
| created_at | DATETIME | NOT NULL, INDEX | |
| created_by_id | INTEGER | FK→users SET NULL | |

**Index:** `(ref_type, ref_id)` — find all movements caused by one document.

### app_settings
| Column | Type | Notes |
|---|---|---|
| id | INTEGER | PK, always 1 (CHECK id = 1) |
| shop_name / shop_address / shop_phone / shop_gstin | VARCHAR | invoice header |
| currency | VARCHAR(10) | default ₹ |
| default_tax_rate | NUMERIC(5,2) | new-product default |
| invoice_footer | VARCHAR(255) | printed on invoices |
| created_at / updated_at | DATETIME | |

## 2. ER diagram (condensed)

```mermaid
erDiagram
    users ||--o{ sales : creates
    users ||--o{ payments : records
    categories ||--o{ products : groups
    products ||--o{ sale_items : sold-as
    products ||--o{ purchase_items : bought-as
    products ||--o{ inventory_movements : tracked-by
    customers ||--o{ sales : buys
    customers ||--o{ payments : settles
    suppliers ||--o{ purchases : supplies
    suppliers ||--o{ payments : paid-to
    sales ||--|{ sale_items : contains
    sales ||--o{ payments : paid-by
    purchases ||--|{ purchase_items : contains
    purchases ||--o{ payments : paid-by
```

## 3. Relationship rules that protect data

| Rule | Mechanism |
|---|---|
| No duplicate invoice/purchase numbers | UNIQUE on `invoice_no`/`purchase_no` |
| No duplicate barcodes/SKUs | UNIQUE on `barcode`/`sku` |
| No orphan sale lines | `sale_items.sale_id` CASCADE |
| No deleted history | `product_id` RESTRICT everywhere; products soft-deleted |
| Deleting a category keeps products | `category_id` SET NULL |
| No negative stock, ever | service guard + signed-movement math |
| Sale ⟷ movement always together | one transaction in `sale_service` |

## 4. The important queries

### Current stock
```sql
-- the cache column (fast path)
SELECT current_stock FROM products WHERE id = :pid;

-- the truth (reconcile / audit)
SELECT COALESCE(SUM(quantity), 0) FROM inventory_movements WHERE product_id = :pid;
```

### Why did stock change? (the audit trail)
```sql
SELECT movement_type, quantity, unit_cost, ref_type, ref_id, note, created_at, created_by_id
FROM inventory_movements WHERE product_id = :pid ORDER BY created_at;
```

### COGS for a period (profit engine)
```sql
SELECT COALESCE(SUM(quantity * unit_cost), 0)
FROM inventory_movements
WHERE movement_type = 'SALE'
  AND created_at BETWEEN :from AND :to;
```

### Profit summary
```sql
-- revenue
SELECT COALESCE(SUM(total), 0) FROM sales WHERE sale_date BETWEEN :from AND :to;
-- expenses
SELECT COALESCE(SUM(amount), 0) FROM expenses WHERE expense_date BETWEEN :from AND :to;
-- gross = revenue − cogs ;  net = gross − expenses   (computed in Python)
```

### Customer balance (Khata)
```sql
-- owed
SELECT COALESCE(SUM(total), 0) FROM sales WHERE customer_id = :cid;
-- paid (real money only)
SELECT COALESCE(SUM(amount), 0) FROM payments
WHERE method <> 'CREDIT'
  AND (customer_id = :cid
       OR sale_id IN (SELECT id FROM sales WHERE customer_id = :cid));
-- balance = owed − paid
```

### Supplier balance
```sql
-- owed to them
SELECT COALESCE(SUM(total), 0) FROM purchases WHERE supplier_id = :sid;
-- paid
SELECT COALESCE(SUM(amount), 0) FROM payments
WHERE method <> 'CREDIT'
  AND (supplier_id = :sid
       OR purchase_id IN (SELECT id FROM purchases WHERE supplier_id = :sid));
-- balance = owed − paid
```

### Low stock
```sql
SELECT id, name, current_stock, min_stock FROM products
WHERE is_active = 1 AND current_stock <= min_stock ORDER BY current_stock;
```

### Dead stock (no sales in 60 days)
```sql
SELECT p.id, p.name, p.current_stock FROM products p
WHERE p.is_active = 1 AND p.current_stock > 0
  AND p.id NOT IN (
    SELECT product_id FROM inventory_movements
    WHERE movement_type = 'SALE' AND created_at >= datetime('now', '-60 days')
  );
```

### Top sellers
```sql
SELECT product_id, SUM(-quantity) AS sold
FROM inventory_movements
WHERE movement_type = 'SALE' AND created_at >= :cutoff
GROUP BY product_id ORDER BY sold DESC LIMIT 5;
```

## 5. Calculation logic (the business rules, in one place)

### Inventory
```text
current_stock(product) = Σ quantity over all movements
PURCHASE  → +qty, unit_cost = purchase unit cost
SALE      → −qty, unit_cost = product.avg_cost at that moment (COGS snapshot)
RETURN    → +qty, unit_cost = current avg cost
ADJUSTMENT→ ±delta (new_stock − current_stock), note required
DAMAGE    → −qty
weighted avg cost (after purchase):  (old_stock × old_avg + qty × cost) / (old_stock + qty)
stock value = Σ (current_stock × avg_cost)
```

### Profit
```text
Revenue      = Σ sales.total (period)
COGS         = Σ SALE movement qty × unit_cost (period, from snapshots)
Gross profit = Revenue − COGS
Net profit   = Gross profit − Σ expenses.amount (period)
```

### Customer balance
```text
= Σ sales.total − Σ real payments (method ≠ CREDIT, for this customer or their sales)
refunds (negative payments) increase the balance
```

### Supplier balance
```text
= Σ purchases.total − Σ real payments made (method ≠ CREDIT, for this supplier or their purchases)
```

---

# Command Cheat Sheet

```text
# Environment
python -m venv venv                      create backend environment
source venv/Scripts/activate             activate (Git Bash)
venv\Scripts\activate                    activate (cmd)

# Backend
pip install -r requirements.txt          install dependencies (venv active!)
alembic revision --autogenerate -m "msg" create a migration (review it first!)
alembic upgrade head                     apply migrations
uvicorn app.main:app --reload --port 8000   run backend (from backend/)
pytest -q                                run backend tests

# Frontend
npm install                              install dependencies
npm run dev                              run dev server (:5173)
npm run build                            production build → dist/
npx tsc --noEmit                         type-check
npx vitest run                           run frontend tests

# Desktop
npm run tauri dev                        run desktop shell (dev)
npm run tauri build                      build installer (release)

# Build the whole installer (Windows)
scripts\build_app.bat                    backend exe + frontend + NSIS installer
```

# Git Cheat Sheet

```bash
git init                          # start a repo
git status                        # what changed
git add -A                        # stage everything
git commit -m "feat: message"     # snapshot with a meaningful message
git log --oneline                 # history
git branch feature/xyz            # new branch
git checkout feature/xyz          # switch
git checkout main && git merge feature/xyz   # merge back
git remote add origin <url>       # link GitHub
git push -u origin main           # first push
git push                          # subsequent pushes
git pull                          # fetch + merge
git tag v0.1.0 && git push origin v0.1.0   # mark a release
git diff                          # see unstaged changes
git checkout -- <file>            # discard uncommitted changes (careful!)
```

# Database Cheat Sheet

```text
DB file (dev)        backend/data/database/retail.db
DB file (installed)  %APPDATA%\com.localretailmanager.app\retail.db
Backups (dev)        backend/data/backups/retail_backup_*.db
Backups (installed)  %APPDATA%\com.localretailmanager.app\backups\
Backup command       POST /api/backups            (VACUUM INTO + verify + rotate)
Restore command      POST /api/backups/restore    (validate → safety backup → swap)
Auto backup          on startup if newest > 24h
Migrations           alembic upgrade head (CLI in dev; automatic at app startup)
Integrity check      PRAGMA integrity_check       (run on every backup)
```
**Golden rules:** never hand-edit the DB; never commit the DB; always keep a verified backup before schema or restore operations.

# API Cheat Sheet

```text
Base URL        http://127.0.0.1:8000/api
Auth header     Authorization: Bearer <token>
Docs            http://127.0.0.1:8000/docs
Error shape     {"detail": {"code": "...", "message": "..."}}
Create → 201, Read → 200, Update → 200, Delete → 204
Validation → 422, Not found → 404, Duplicate → 409, Not allowed → 403, No auth → 401
Full reference  → the API Reference section above
```

# Debugging Checklist

When something breaks, in this order:

1. **Read the error.** Not the symptom — the *message*. Where was it raised?
2. **Check the logs.** `backend/data/logs/app.log` and `backend.log` (installed) — the traceback names the file and line.
3. **Reproduce in isolation.** Isolate the failing layer: curl the endpoint → call the service in a scratch script → run the SQL directly. The bug is in the layer that misbehaves.
4. **Check state.** Is the data what you think? (`/docs` → run the list endpoint; or query SQLite with a scratch script.)
5. **Ask the five whys for these classics:**
   - Wrong module? → venv / imports / `models/__init__.py`
   - Stale code? → restart `uvicorn --reload` / hard-refresh frontend
   - Stale data? → migrations (`alembic upgrade head`)
   - Wrong environment? → `LRM_DATA_DIR`, CORS origins, ports
   - Transaction issue? → who committed when (one commit at the end!)
6. **Fix, then verify** with the phase's checkpoint — a fix without verification is a guess.
7. **Write it down.** If it took more than 10 minutes, it belongs in the Troubleshooting Guide.

# Deployment Checklist

Before handing a shop a build:

- [ ] `pytest -q` and `npx vitest run` pass
- [ ] `alembic upgrade head` on a fresh DB produces all tables
- [ ] Default `owner/admin123` exists **and the owner is told to change it** (or it's changed before delivery)
- [ ] `scripts\build_backend.bat` succeeds; the sidecar exe is in `desktop/src-tauri/binaries/`
- [ ] `scripts\build_app.bat` succeeds; the NSIS installer exists
- [ ] **Fresh-machine test (VM):** install → shortcut → login → billing sale → PDF invoice → restart → data persists → backup → restore works
- [ ] A test backup was created and *restored* successfully
- [ ] Backend binds to `127.0.0.1` (not exposed to the LAN unless intended)
- [ ] Logs contain no passwords; `SECRET_KEY` is not the default
- [ ] Owner knows: where data lives, how to back up to USB, that uninstall keeps data
- [ ] Release tagged in git (`v0.1.0`)
# Final Project Tree

This tree matches the complete source code that follows, file for file.

```text
local-retail-manager/
├── .gitignore
├── LICENSE
├── README.md
│
├── backend/
│   ├── .env.example
│   ├── VERSION
│   ├── alembic.ini
│   ├── requirements.txt
│   ├── run_backend.py
│   ├── alembic/
│   │   ├── env.py
│   │   └── versions/
│   │       └── 0001_initial_schema.py
│   ├── app/
│   │   ├── __init__.py
│   │   ├── main.py
│   │   ├── core/
│   │   │   ├── __init__.py
│   │   │   ├── config.py
│   │   │   ├── exceptions.py
│   │   │   ├── logging.py
│   │   │   └── security.py
│   │   ├── database/
│   │   │   ├── __init__.py
│   │   │   ├── database.py
│   │   │   └── seed.py
│   │   ├── models/
│   │   │   ├── __init__.py
│   │   │   ├── base.py
│   │   │   ├── category.py
│   │   │   ├── customer.py
│   │   │   ├── enums.py
│   │   │   ├── expense.py
│   │   │   ├── inventory_movement.py
│   │   │   ├── payment.py
│   │   │   ├── product.py
│   │   │   ├── purchase.py
│   │   │   ├── purchase_item.py
│   │   │   ├── sale.py
│   │   │   ├── sale_item.py
│   │   │   ├── setting.py
│   │   │   ├── supplier.py
│   │   │   └── user.py
│   │   ├── schemas/
│   │   │   ├── __init__.py
│   │   │   ├── auth.py
│   │   │   ├── category.py
│   │   │   ├── common.py
│   │   │   ├── customer.py
│   │   │   ├── expense.py
│   │   │   ├── inventory.py
│   │   │   ├── payment.py
│   │   │   ├── product.py
│   │   │   ├── purchase.py
│   │   │   ├── sale.py
│   │   │   ├── settings.py
│   │   │   ├── supplier.py
│   │   │   └── user.py
│   │   ├── api/
│   │   │   ├── __init__.py
│   │   │   ├── deps.py
│   │   │   └── routes/
│   │   │       ├── __init__.py
│   │   │       ├── auth.py
│   │   │       ├── backups.py
│   │   │       ├── categories.py
│   │   │       ├── customers.py
│   │   │       ├── dashboard.py
│   │   │       ├── expenses.py
│   │   │       ├── health.py
│   │   │       ├── inventory.py
│   │   │       ├── products.py
│   │   │       ├── purchases.py
│   │   │       ├── reports.py
│   │   │       ├── sales.py
│   │   │       ├── settings.py
│   │   │       ├── suppliers.py
│   │   │       └── users.py
│   │   ├── services/
│   │   │   ├── __init__.py
│   │   │   ├── auth_service.py
│   │   │   ├── backup_service.py
│   │   │   ├── category_service.py
│   │   │   ├── customer_service.py
│   │   │   ├── dashboard_service.py
│   │   │   ├── expense_service.py
│   │   │   ├── inventory_service.py
│   │   │   ├── invoice_service.py
│   │   │   ├── product_service.py
│   │   │   ├── purchase_service.py
│   │   │   ├── report_service.py
│   │   │   ├── sale_service.py
│   │   │   ├── settings_service.py
│   │   │   └── supplier_service.py
│   │   ├── pdf/
│   │   │   ├── __init__.py
│   │   │   └── invoice.py
│   │   └── utils/
│   │       ├── __init__.py
│   │       ├── doc_number.py
│   │       ├── money.py
│   │       └── pagination.py
│   └── tests/
│       ├── __init__.py
│       ├── conftest.py
│       ├── test_api.py
│       ├── test_inventory.py
│       └── test_pricing.py
│
├── frontend/
│   ├── index.html
│   ├── package.json
│   ├── tsconfig.json
│   ├── vite.config.ts
│   └── src/
│       ├── main.tsx
│       ├── App.tsx
│       ├── index.css
│       ├── components/
│       │   ├── forms/
│       │   │   ├── CustomerForm.tsx
│       │   │   ├── ExpenseForm.tsx
│       │   │   ├── ProductForm.tsx
│       │   │   └── SupplierForm.tsx
│       │   ├── layout/
│       │   │   ├── AppLayout.tsx
│       │   │   ├── ProtectedRoute.tsx
│       │   │   └── Topbar.tsx
│       │   └── ui/
│       │       ├── Badge.tsx
│       │       ├── Button.tsx
│       │       ├── ConfirmDialog.tsx
│       │       ├── DataTable.tsx
│       │       ├── EmptyState.tsx
│       │       ├── Input.tsx
│       │       ├── Modal.tsx
│       │       ├── PageHeader.tsx
│       │       ├── Select.tsx
│       │       ├── Spinner.tsx
│       │       ├── StatCard.tsx
│       │       └── Toaster.tsx
│       ├── constants/
│       │   └── index.ts
│       ├── features/
│       │   └── reports/
│       │       └── rangePresets.ts
│       ├── hooks/
│       │   ├── useApi.ts
│       │   └── useDebounce.ts
│       ├── pages/
│       │   ├── BillingPage.tsx
│       │   ├── CustomersPage.tsx
│       │   ├── DashboardPage.tsx
│       │   ├── ExpensesPage.tsx
│       │   ├── InventoryPage.tsx
│       │   ├── LoginPage.tsx
│       │   ├── ProductsPage.tsx
│       │   ├── PurchasesPage.tsx
│       │   ├── ReportsPage.tsx
│       │   ├── SettingsPage.tsx
│       │   ├── SuppliersPage.tsx
│       │   └── UsersPage.tsx
│       ├── services/
│       │   ├── api.ts
│       │   ├── auth.ts
│       │   ├── customers.ts
│       │   ├── dashboard.ts
│       │   ├── expenses.ts
│       │   ├── inventory.ts
│       │   ├── products.ts
│       │   ├── purchases.ts
│       │   ├── reports.ts
│       │   ├── sales.ts
│       │   ├── settings.ts
│       │   ├── suppliers.ts
│       │   └── users.ts
│       ├── store/
│       │   ├── auth.ts
│       │   ├── cart.ts
│       │   └── toast.ts
│       ├── test/
│       │   └── setup.ts
│       ├── types/
│       │   └── index.ts
│       └── utils/
│           ├── csv.ts
│           ├── format.ts
│           ├── pricing.ts
│           └── pricing.test.ts
│
├── desktop/
│   ├── package.json
│   └── src-tauri/
│       ├── Cargo.toml
│       ├── build.rs
│       ├── tauri.conf.json
│       ├── capabilities/
│       │   └── default.json
│       ├── binaries/
│       │   └── .gitkeep              (backend-x86_64-pc-windows-msvc.exe lands here)
│       ├── icons/                    (generated via `npm run tauri icon`)
│       └── src/
│           └── main.rs
│
├── scripts/
│   ├── build_app.bat
│   ├── build_backend.bat
│   ├── run_dev.bat
│   └── seed_demo.py
│
└── data/                             (runtime, gitignored)
    ├── database/  invoices/  backups/  exports/  logs/
```

> **Verification:** every file below appears in this tree, and every path in this tree has a file below. If you add a file during the course, add it to the tree too — the tree is the map.

---

# Complete Source Code Reference

> **How to use this section:** it is the *final, internally consistent* state of the project — the accumulated result of every phase. Read each file against its teaching section: the phases explain *why*, this section is the *what*. Files that grew with authorization (Phase 18) are shown in their final form.

---

## backend/requirements.txt

```text
fastapi==0.141.1
uvicorn[standard]==0.52.1
sqlalchemy==2.0.51
alembic==1.19.0
pydantic==2.13.4
pydantic-settings==2.15.0
reportlab==5.0.0
bcrypt==5.0.0
PyJWT==2.13.0
python-multipart==0.0.20

# Tests
pytest==9.1.1
httpx==0.28.1

# Packaging
pyinstaller==6.21.0

# Optional (post-MVP): Excel export, barcode generation
# openpyxl==3.1.5
# python-barcode==0.15.1
```

## backend/.env.example

```text
# Copy to .env and adjust. NEVER commit .env (it holds the secret key).
LRM_ENV=development
LRM_HOST=127.0.0.1
LRM_PORT=8000
LRM_DATA_DIR=./data
LRM_SECRET_KEY=please-generate-a-long-random-string
LRM_SHOP_NAME=My Shop
LRM_SHOP_ADDRESS=123 Main Street
LRM_SHOP_PHONE=+91 98765 43210
LRM_SHOP_GSTIN=
LRM_CURRENCY=₹
LRM_DEFAULT_TAX_RATE=0
LRM_BACKUP_KEEP_DAYS=14
LRM_DEFAULT_ADMIN_USERNAME=owner
LRM_DEFAULT_ADMIN_PASSWORD=admin123
```

## backend/VERSION

```text
0.1.0
```

## backend/run_backend.py

```python
"""Entry point for the packaged backend (PyInstaller).

The Tauri shell launches this exe with LRM_DATA_DIR and LRM_PORT set.
Importing app.main here ALSO makes PyInstaller bundle the whole app package.
"""
import argparse
import os

import app.main  # noqa: F401  ← critical: forces PyInstaller to see the app package


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--host", default=os.environ.get("LRM_HOST", "127.0.0.1"))
    parser.add_argument("--port", type=int, default=int(os.environ.get("LRM_PORT", "8000")))
    args = parser.parse_args()

    import uvicorn
    uvicorn.run("app.main:app", host=args.host, port=args.port, log_level="info")


if __name__ == "__main__":
    main()
```

## backend/alembic.ini

```ini
# Alembic configuration. The URL is set in alembic/env.py from app settings.
[alembic]
script_location = %(here)s/alembic
# sqlalchemy.url =

[loggers]
keys = root,sqlalchemy,alembic

[handlers]
keys = console

[formatters]
keys = generic

[logger_root]
level = WARN
handlers = console
qualname =

[logger_sqlalchemy]
level = WARN
handlers =
qualname = sqlalchemy.engine

[logger_alembic]
level = INFO
handlers =
qualname = alembic

[handler_console]
class = StreamHandler
args = (sys.stderr,)
level = NOTSET
formatter = generic

[formatter_generic]
format = %(levelname)-5.5s [%(name)s] %(message)s
datefmt = %H:%M:%S
```

## backend/alembic/env.py

```python
from logging.config import fileConfig

from alembic import context
from sqlalchemy import engine_from_config, pool

from app.core.config import settings
from app.models import Base  # imports every model → fills Base.metadata

config = context.config
if config.config_file_name is not None:
    fileConfig(config.config_file_name)

# THE two lines that make Alembic work for our app:
config.set_main_option("sqlalchemy.url", settings.database_url)
target_metadata = Base.metadata


def run_migrations_offline() -> None:
    url = config.get_main_option("sqlalchemy.url")
    context.configure(
        url=url,
        target_metadata=target_metadata,
        literal_binds=True,
        dialect_opts={"paramstyle": "named"},
    )
    with context.begin_transaction():
        context.run_migrations()


def run_migrations_online() -> None:
    connectable = engine_from_config(
        config.get_section(config.config_ini_section, {}),
        prefix="sqlalchemy.",
        poolclass=pool.NullPool,
    )
    with connectable.connect() as connection:
        context.configure(connection=connection, target_metadata=target_metadata)
        with context.begin_transaction():
            context.run_migrations()


if context.is_offline_mode():
    run_migrations_offline()
else:
    run_migrations_online()
```

## backend/alembic/versions/0001_initial_schema.py

```python
"""initial schema

Revision ID: 0001
Revises:
Create Date: 2026-08-08
"""
import sqlalchemy as sa

from alembic import op

revision = "0001"
down_revision = None
branch_labels = None
depends_on = None


def upgrade() -> None:
    op.create_table(
        "users",
        sa.Column("id", sa.Integer(), primary_key=True),
        sa.Column("username", sa.String(length=50), nullable=False),
        sa.Column("full_name", sa.String(length=100), nullable=False),
        sa.Column("password_hash", sa.String(length=200), nullable=False),
        sa.Column("role", sa.String(length=20), nullable=False, server_default="CASHIER"),
        sa.Column("is_active", sa.Boolean(), nullable=False, server_default=sa.text("1")),
        sa.Column("created_at", sa.DateTime(), nullable=False),
        sa.Column("updated_at", sa.DateTime(), nullable=False),
    )
    op.create_index("ix_users_username", "users", ["username"], unique=True)

    op.create_table(
        "categories",
        sa.Column("id", sa.Integer(), primary_key=True),
        sa.Column("name", sa.String(length=100), nullable=False),
        sa.Column("description", sa.String(length=255), nullable=True),
        sa.Column("created_at", sa.DateTime(), nullable=False),
        sa.Column("updated_at", sa.DateTime(), nullable=False),
    )
    op.create_index("ix_categories_name", "categories", ["name"], unique=True)

    op.create_table(
        "products",
        sa.Column("id", sa.Integer(), primary_key=True),
        sa.Column("name", sa.String(length=200), nullable=False),
        sa.Column("sku", sa.String(length=50), nullable=True),
        sa.Column("barcode", sa.String(length=100), nullable=True),
        sa.Column("category_id", sa.Integer(), sa.ForeignKey("categories.id", ondelete="SET NULL"), nullable=True),
        sa.Column("purchase_price", sa.Numeric(12, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("selling_price", sa.Numeric(12, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("tax_rate", sa.Numeric(5, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("min_stock", sa.Numeric(12, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("current_stock", sa.Numeric(12, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("avg_cost", sa.Numeric(12, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("is_active", sa.Boolean(), nullable=False, server_default=sa.text("1")),
        sa.Column("created_at", sa.DateTime(), nullable=False),
        sa.Column("updated_at", sa.DateTime(), nullable=False),
    )
    op.create_index("ix_products_name", "products", ["name"])
    op.create_index("ix_products_sku", "products", ["sku"], unique=True)
    op.create_index("ix_products_barcode", "products", ["barcode"], unique=True)

    op.create_table(
        "customers",
        sa.Column("id", sa.Integer(), primary_key=True),
        sa.Column("name", sa.String(length=150), nullable=False),
        sa.Column("phone", sa.String(length=20), nullable=True),
        sa.Column("address", sa.String(length=255), nullable=True),
        sa.Column("notes", sa.String(length=255), nullable=True),
        sa.Column("is_active", sa.Boolean(), nullable=False, server_default=sa.text("1")),
        sa.Column("created_at", sa.DateTime(), nullable=False),
        sa.Column("updated_at", sa.DateTime(), nullable=False),
    )
    op.create_index("ix_customers_name", "customers", ["name"])
    op.create_index("ix_customers_phone", "customers", ["phone"])

    op.create_table(
        "suppliers",
        sa.Column("id", sa.Integer(), primary_key=True),
        sa.Column("name", sa.String(length=150), nullable=False),
        sa.Column("phone", sa.String(length=20), nullable=True),
        sa.Column("address", sa.String(length=255), nullable=True),
        sa.Column("notes", sa.String(length=255), nullable=True),
        sa.Column("is_active", sa.Boolean(), nullable=False, server_default=sa.text("1")),
        sa.Column("created_at", sa.DateTime(), nullable=False),
        sa.Column("updated_at", sa.DateTime(), nullable=False),
    )
    op.create_index("ix_suppliers_name", "suppliers", ["name"])

    op.create_table(
        "sales",
        sa.Column("id", sa.Integer(), primary_key=True),
        sa.Column("invoice_no", sa.String(length=30), nullable=False),
        sa.Column("customer_id", sa.Integer(), sa.ForeignKey("customers.id", ondelete="SET NULL"), nullable=True),
        sa.Column("subtotal", sa.Numeric(12, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("discount_pct", sa.Numeric(5, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("discount", sa.Numeric(12, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("tax", sa.Numeric(12, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("total", sa.Numeric(12, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("status", sa.String(length=20), nullable=False, server_default="COMPLETED"),
        sa.Column("sale_date", sa.DateTime(), nullable=False),
        sa.Column("notes", sa.String(length=255), nullable=True),
        sa.Column("created_by_id", sa.Integer(), sa.ForeignKey("users.id", ondelete="SET NULL"), nullable=True),
        sa.Column("created_at", sa.DateTime(), nullable=False),
        sa.Column("updated_at", sa.DateTime(), nullable=False),
    )
    op.create_index("ix_sales_invoice_no", "sales", ["invoice_no"], unique=True)
    op.create_index("ix_sales_sale_date", "sales", ["sale_date"])
    op.create_index("ix_sales_customer_id", "sales", ["customer_id"])

    op.create_table(
        "sale_items",
        sa.Column("id", sa.Integer(), primary_key=True),
        sa.Column("sale_id", sa.Integer(), sa.ForeignKey("sales.id", ondelete="CASCADE"), nullable=False),
        sa.Column("product_id", sa.Integer(), sa.ForeignKey("products.id", ondelete="RESTRICT"), nullable=False),
        sa.Column("quantity", sa.Numeric(12, 2), nullable=False),
        sa.Column("unit_price", sa.Numeric(12, 2), nullable=False),
        sa.Column("tax_rate", sa.Numeric(5, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("line_total", sa.Numeric(12, 2), nullable=False),
        sa.Column("returned_qty", sa.Numeric(12, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("created_at", sa.DateTime(), nullable=False),
        sa.Column("updated_at", sa.DateTime(), nullable=False),
    )
    op.create_index("ix_sale_items_sale_id", "sale_items", ["sale_id"])
    op.create_index("ix_sale_items_product_id", "sale_items", ["product_id"])

    op.create_table(
        "purchases",
        sa.Column("id", sa.Integer(), primary_key=True),
        sa.Column("purchase_no", sa.String(length=30), nullable=False),
        sa.Column("supplier_id", sa.Integer(), sa.ForeignKey("suppliers.id", ondelete="SET NULL"), nullable=True),
        sa.Column("purchase_date", sa.DateTime(), nullable=False),
        sa.Column("subtotal", sa.Numeric(12, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("discount_pct", sa.Numeric(5, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("discount", sa.Numeric(12, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("tax", sa.Numeric(12, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("total", sa.Numeric(12, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("paid_amount", sa.Numeric(12, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("payment_method", sa.String(length=20), nullable=False, server_default="CASH"),
        sa.Column("status", sa.String(length=20), nullable=False, server_default="COMPLETED"),
        sa.Column("notes", sa.String(length=255), nullable=True),
        sa.Column("created_by_id", sa.Integer(), sa.ForeignKey("users.id", ondelete="SET NULL"), nullable=True),
        sa.Column("created_at", sa.DateTime(), nullable=False),
        sa.Column("updated_at", sa.DateTime(), nullable=False),
    )
    op.create_index("ix_purchases_purchase_no", "purchases", ["purchase_no"], unique=True)
    op.create_index("ix_purchases_purchase_date", "purchases", ["purchase_date"])
    op.create_index("ix_purchases_supplier_id", "purchases", ["supplier_id"])

    op.create_table(
        "purchase_items",
        sa.Column("id", sa.Integer(), primary_key=True),
        sa.Column("purchase_id", sa.Integer(), sa.ForeignKey("purchases.id", ondelete="CASCADE"), nullable=False),
        sa.Column("product_id", sa.Integer(), sa.ForeignKey("products.id", ondelete="RESTRICT"), nullable=False),
        sa.Column("quantity", sa.Numeric(12, 2), nullable=False),
        sa.Column("unit_cost", sa.Numeric(12, 2), nullable=False),
        sa.Column("tax_rate", sa.Numeric(5, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("line_total", sa.Numeric(12, 2), nullable=False),
        sa.Column("created_at", sa.DateTime(), nullable=False),
        sa.Column("updated_at", sa.DateTime(), nullable=False),
    )
    op.create_index("ix_purchase_items_purchase_id", "purchase_items", ["purchase_id"])
    op.create_index("ix_purchase_items_product_id", "purchase_items", ["product_id"])

    op.create_table(
        "payments",
        sa.Column("id", sa.Integer(), primary_key=True),
        sa.Column("sale_id", sa.Integer(), sa.ForeignKey("sales.id", ondelete="SET NULL"), nullable=True),
        sa.Column("purchase_id", sa.Integer(), sa.ForeignKey("purchases.id", ondelete="SET NULL"), nullable=True),
        sa.Column("customer_id", sa.Integer(), sa.ForeignKey("customers.id", ondelete="SET NULL"), nullable=True),
        sa.Column("supplier_id", sa.Integer(), sa.ForeignKey("suppliers.id", ondelete="SET NULL"), nullable=True),
        sa.Column("amount", sa.Numeric(12, 2), nullable=False),
        sa.Column("method", sa.String(length=20), nullable=False, server_default="CASH"),
        sa.Column("reference", sa.String(length=100), nullable=True),
        sa.Column("paid_at", sa.DateTime(), nullable=False),
        sa.Column("created_by_id", sa.Integer(), sa.ForeignKey("users.id", ondelete="SET NULL"), nullable=True),
        sa.Column("created_at", sa.DateTime(), nullable=False),
        sa.Column("updated_at", sa.DateTime(), nullable=False),
    )
    op.create_index("ix_payments_sale_id", "payments", ["sale_id"])
    op.create_index("ix_payments_purchase_id", "payments", ["purchase_id"])
    op.create_index("ix_payments_customer_id", "payments", ["customer_id"])
    op.create_index("ix_payments_supplier_id", "payments", ["supplier_id"])
    op.create_index("ix_payments_paid_at", "payments", ["paid_at"])

    op.create_table(
        "expenses",
        sa.Column("id", sa.Integer(), primary_key=True),
        sa.Column("expense_date", sa.DateTime(), nullable=False),
        sa.Column("category", sa.String(length=50), nullable=False),
        sa.Column("amount", sa.Numeric(12, 2), nullable=False),
        sa.Column("description", sa.String(length=255), nullable=True),
        sa.Column("created_by_id", sa.Integer(), sa.ForeignKey("users.id", ondelete="SET NULL"), nullable=True),
        sa.Column("created_at", sa.DateTime(), nullable=False),
        sa.Column("updated_at", sa.DateTime(), nullable=False),
    )
    op.create_index("ix_expenses_expense_date", "expenses", ["expense_date"])
    op.create_index("ix_expenses_category", "expenses", ["category"])

    op.create_table(
        "inventory_movements",
        sa.Column("id", sa.Integer(), primary_key=True),
        sa.Column("product_id", sa.Integer(), sa.ForeignKey("products.id", ondelete="RESTRICT"), nullable=False),
        sa.Column("movement_type", sa.String(length=20), nullable=False),
        sa.Column("quantity", sa.Numeric(12, 2), nullable=False),
        sa.Column("unit_cost", sa.Numeric(12, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("ref_type", sa.String(length=30), nullable=True),
        sa.Column("ref_id", sa.Integer(), nullable=True),
        sa.Column("note", sa.String(length=255), nullable=True),
        sa.Column("created_at", sa.DateTime(), nullable=False),
        sa.Column("created_by_id", sa.Integer(), sa.ForeignKey("users.id", ondelete="SET NULL"), nullable=True),
    )
    op.create_index("ix_inventory_movements_product_id", "inventory_movements", ["product_id"])
    op.create_index("ix_inventory_movements_movement_type", "inventory_movements", ["movement_type"])
    op.create_index("ix_movements_ref", "inventory_movements", ["ref_type", "ref_id"])

    op.create_table(
        "app_settings",
        sa.Column("id", sa.Integer(), primary_key=True),
        sa.Column("shop_name", sa.String(length=150), nullable=False, server_default="My Shop"),
        sa.Column("shop_address", sa.String(length=255), nullable=True),
        sa.Column("shop_phone", sa.String(length=50), nullable=True),
        sa.Column("shop_gstin", sa.String(length=50), nullable=True),
        sa.Column("currency", sa.String(length=10), nullable=False, server_default="₹"),
        sa.Column("default_tax_rate", sa.Numeric(5, 2), nullable=False, server_default=sa.text("0")),
        sa.Column("invoice_footer", sa.String(length=255), nullable=True),
        sa.Column("created_at", sa.DateTime(), nullable=False),
        sa.Column("updated_at", sa.DateTime(), nullable=False),
    )
    op.create_check_constraint("ck_single_row", "app_settings", "id = 1")


def downgrade() -> None:
    for table in [
        "app_settings", "inventory_movements", "expenses", "payments",
        "purchase_items", "purchases", "sale_items", "sales", "suppliers",
        "customers", "products", "categories", "users",
    ]:
        op.drop_table(table)
```

> **Note:** the migration above is the *hand-reviewed* equivalent of what `alembic revision --autogenerate -m "initial schema"` produces. If you generate yours fresh, keep these index/constraint decisions (they match the models).

---

## backend/app/__init__.py

```python
"""Local Retail Manager backend."""
```

## backend/app/core/__init__.py

```python
```

## backend/app/core/config.py

```python
from pathlib import Path

from pydantic_settings import BaseSettings, SettingsConfigDict


class Settings(BaseSettings):
    """Application configuration.

    Values come from (highest priority first):
      1. real environment variables (prefix LRM_, e.g. LRM_PORT)
      2. a .env file in the backend/ folder
      3. the defaults below
    """

    model_config = SettingsConfigDict(env_prefix="LRM_", env_file=".env", extra="ignore")

    APP_NAME: str = "Local Retail Manager"
    ENV: str = "development"

    HOST: str = "127.0.0.1"
    PORT: int = 8000

    DATA_DIR: Path = Path("./data")
    DATABASE_FILE: str = "retail.db"

    SECRET_KEY: str = "change-me-please"
    TOKEN_EXPIRE_MINUTES: int = 480

    CORS_ORIGINS: list[str] = ["http://localhost:5173", "http://tauri.localhost"]

    SHOP_NAME: str = "My Shop"
    SHOP_ADDRESS: str = ""
    SHOP_PHONE: str = ""
    SHOP_GSTIN: str = ""
    CURRENCY: str = "₹"
    DEFAULT_TAX_RATE: float = 0.0

    BACKUP_KEEP_DAYS: int = 14

    DEFAULT_ADMIN_USERNAME: str = "owner"
    DEFAULT_ADMIN_PASSWORD: str = "admin123"

    # ------------------------------------------------------------------
    @property
    def db_dir(self) -> Path:
        return self.DATA_DIR / "database"

    @property
    def invoices_dir(self) -> Path:
        return self.DATA_DIR / "invoices"

    @property
    def backups_dir(self) -> Path:
        return self.DATA_DIR / "backups"

    @property
    def exports_dir(self) -> Path:
        return self.DATA_DIR / "exports"

    @property
    def logs_dir(self) -> Path:
        return self.DATA_DIR / "logs"

    @property
    def database_url(self) -> str:
        db_file = (self.db_dir / self.DATABASE_FILE).as_posix()
        return f"sqlite:///{db_file}"

    def ensure_dirs(self) -> None:
        for d in (self.db_dir, self.invoices_dir, self.backups_dir,
                  self.exports_dir, self.logs_dir):
            d.mkdir(parents=True, exist_ok=True)


settings = Settings()
```

## backend/app/core/exceptions.py

```python
from fastapi import status


class AppError(Exception):
    """Base class for all business errors (converted to JSON by a handler)."""

    status_code: int = status.HTTP_400_BAD_REQUEST
    code: str = "app_error"

    def __init__(self, message: str):
        self.message = message
        super().__init__(message)


class NotFoundError(AppError):
    status_code = status.HTTP_404_NOT_FOUND
    code = "not_found"


class ConflictError(AppError):
    status_code = status.HTTP_409_CONFLICT
    code = "conflict"


class ValidationFailedError(AppError):
    status_code = status.HTTP_400_BAD_REQUEST
    code = "validation_failed"


class AuthenticationError(AppError):
    status_code = status.HTTP_401_UNAUTHORIZED
    code = "authentication_failed"


class PermissionDeniedError(AppError):
    status_code = status.HTTP_403_FORBIDDEN
    code = "permission_denied"


class InsufficientStockError(AppError):
    status_code = status.HTTP_409_CONFLICT
    code = "insufficient_stock"
```

## backend/app/core/security.py

```python
"""Password hashing (bcrypt) and signed tokens (JWT)."""
from datetime import datetime, timedelta, timezone

import bcrypt
import jwt

from app.core.config import settings

ALGORITHM = "HS256"


def hash_password(password: str) -> str:
    return bcrypt.hashpw(password.encode("utf-8"), bcrypt.gensalt()).decode("utf-8")


def verify_password(plain: str, hashed: str) -> bool:
    try:
        return bcrypt.checkpw(plain.encode("utf-8"), hashed.encode("utf-8"))
    except ValueError:
        return False


def create_access_token(subject: str, role: str) -> str:
    now = datetime.now(timezone.utc)
    payload = {
        "sub": subject,
        "role": role,
        "iat": now,
        "exp": now + timedelta(minutes=settings.TOKEN_EXPIRE_MINUTES),
    }
    return jwt.encode(payload, settings.SECRET_KEY, algorithm=ALGORITHM)


def decode_access_token(token: str) -> dict:
    return jwt.decode(token, settings.SECRET_KEY, algorithms=[ALGORITHM])
```

## backend/app/core/logging.py

```python
import logging
from logging.handlers import RotatingFileHandler

from app.core.config import settings


def setup_logging() -> None:
    settings.logs_dir.mkdir(parents=True, exist_ok=True)
    formatter = logging.Formatter("%(asctime)s | %(levelname)-8s | %(name)s | %(message)s")

    file_handler = RotatingFileHandler(
        settings.logs_dir / "app.log",
        maxBytes=2_000_000,
        backupCount=5,
        encoding="utf-8",
    )
    file_handler.setFormatter(formatter)

    root = logging.getLogger()
    root.setLevel(logging.INFO)
    root.addHandler(file_handler)

    if settings.ENV == "development":
        console = logging.StreamHandler()
        console.setFormatter(formatter)
        root.addHandler(console)
```

---

## backend/app/database/__init__.py

```python
```

## backend/app/database/database.py

```python
from sqlalchemy import create_engine, event
from sqlalchemy.orm import sessionmaker

from app.core.config import settings


def _set_sqlite_pragmas(dbapi_connection, _connection_record):
    cursor = dbapi_connection.cursor()
    cursor.execute("PRAGMA foreign_keys=ON")
    cursor.execute("PRAGMA journal_mode=WAL")
    cursor.execute("PRAGMA busy_timeout=5000")
    cursor.close()


engine = create_engine(
    settings.database_url,
    connect_args={"check_same_thread": False},
)
event.listen(engine, "connect", _set_sqlite_pragmas)

SessionLocal = sessionmaker(bind=engine, autoflush=False, expire_on_commit=False)


def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()
```

## backend/app/database/seed.py

```python
from sqlalchemy import select
from sqlalchemy.orm import Session

from app.core.config import settings
from app.core.security import hash_password
from app.models import AppSetting, User, UserRole


def seed_initial_data(db: Session) -> None:
    """Create the default Owner + settings row on a fresh database. Idempotent."""
    if db.scalar(select(User).where(User.username == settings.DEFAULT_ADMIN_USERNAME)) is None:
        db.add(User(
            username=settings.DEFAULT_ADMIN_USERNAME,
            full_name="Shop Owner",
            password_hash=hash_password(settings.DEFAULT_ADMIN_PASSWORD),
            role=UserRole.OWNER,
            is_active=True,
        ))

    if db.get(AppSetting, 1) is None:
        db.add(AppSetting(
            id=1,
            shop_name=settings.SHOP_NAME,
            shop_address=settings.SHOP_ADDRESS,
            shop_phone=settings.SHOP_PHONE,
            shop_gstin=settings.SHOP_GSTIN,
            currency=settings.CURRENCY,
            default_tax_rate=settings.DEFAULT_TAX_RATE,
        ))

    db.commit()
```

---

## backend/app/models/__init__.py

```python
from .base import Base, TimestampMixin
from .category import Category
from .customer import Customer
from .enums import (MovementType, PaymentMethod, PurchaseStatus, SaleStatus,
                    UserRole)
from .expense import Expense
from .inventory_movement import InventoryMovement
from .payment import Payment
from .product import Product
from .purchase import Purchase, PurchaseItem
from .sale import Sale
from .sale_item import SaleItem
from .setting import AppSetting
from .supplier import Supplier
from .user import User

__all__ = [
    "Base", "TimestampMixin", "Category", "Customer", "Expense",
    "InventoryMovement", "MovementType", "PaymentMethod", "Product",
    "Purchase", "PurchaseItem", "PurchaseStatus", "Payment", "Sale",
    "SaleItem", "SaleStatus", "Supplier", "AppSetting", "User", "UserRole",
]
```

## backend/app/models/base.py

```python
from datetime import datetime

from sqlalchemy import DateTime
from sqlalchemy.orm import DeclarativeBase, Mapped, mapped_column


class Base(DeclarativeBase):
    pass


class TimestampMixin:
    """Local-time naive datetimes, stamped by Python (consistent everywhere)."""

    created_at: Mapped[datetime] = mapped_column(DateTime, default=datetime.now, nullable=False)
    updated_at: Mapped[datetime] = mapped_column(
        DateTime, default=datetime.now, onupdate=datetime.now, nullable=False
    )
```

## backend/app/models/enums.py

```python
import enum


class UserRole(enum.StrEnum):
    OWNER = "OWNER"
    MANAGER = "MANAGER"
    CASHIER = "CASHIER"


class SaleStatus(enum.StrEnum):
    COMPLETED = "COMPLETED"
    RETURNED = "RETURNED"


class PurchaseStatus(enum.StrEnum):
    COMPLETED = "COMPLETED"
    PARTIAL = "PARTIAL"


class PaymentMethod(enum.StrEnum):
    CASH = "CASH"
    UPI = "UPI"
    CARD = "CARD"
    CREDIT = "CREDIT"
    BANK = "BANK"


class MovementType(enum.StrEnum):
    PURCHASE = "PURCHASE"
    SALE = "SALE"
    RETURN = "RETURN"
    ADJUSTMENT = "ADJUSTMENT"
    DAMAGE = "DAMAGE"
```

## backend/app/models/user.py

```python
from sqlalchemy import Boolean, Enum as SAEnum, String
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin
from .enums import UserRole


class User(TimestampMixin, Base):
    __tablename__ = "users"

    id: Mapped[int] = mapped_column(primary_key=True)
    username: Mapped[str] = mapped_column(String(50), unique=True, index=True)
    full_name: Mapped[str] = mapped_column(String(100))
    password_hash: Mapped[str] = mapped_column(String(200))
    role: Mapped[UserRole] = mapped_column(
        SAEnum(UserRole, native_enum=False, length=20), default=UserRole.CASHIER
    )
    is_active: Mapped[bool] = mapped_column(Boolean, default=True)

    sales: Mapped[list["Sale"]] = relationship(back_populates="created_by")
```

## backend/app/models/category.py

```python
from sqlalchemy import String
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin


class Category(TimestampMixin, Base):
    __tablename__ = "categories"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(100), unique=True, index=True)
    description: Mapped[str | None] = mapped_column(String(255))

    products: Mapped[list["Product"]] = relationship(back_populates="category")
```

## backend/app/models/product.py

```python
from decimal import Decimal

from sqlalchemy import ForeignKey, Numeric, String
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin


class Product(TimestampMixin, Base):
    __tablename__ = "products"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(200), index=True)
    sku: Mapped[str | None] = mapped_column(String(50), unique=True, index=True)
    barcode: Mapped[str | None] = mapped_column(String(100), unique=True, index=True)

    category_id: Mapped[int | None] = mapped_column(
        ForeignKey("categories.id", ondelete="SET NULL")
    )
    category: Mapped["Category | None"] = relationship(back_populates="products")

    purchase_price: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    selling_price: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    tax_rate: Mapped[Decimal] = mapped_column(Numeric(5, 2), default=Decimal("0"))
    min_stock: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))

    current_stock: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    avg_cost: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))

    is_active: Mapped[bool] = mapped_column(default=True)

    inventory_movements: Mapped[list["InventoryMovement"]] = relationship(
        back_populates="product"
    )
```

## backend/app/models/customer.py

```python
from sqlalchemy import Boolean, String
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin


class Customer(TimestampMixin, Base):
    __tablename__ = "customers"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(150), index=True)
    phone: Mapped[str | None] = mapped_column(String(20), index=True)
    address: Mapped[str | None] = mapped_column(String(255))
    notes: Mapped[str | None] = mapped_column(String(255))
    is_active: Mapped[bool] = mapped_column(Boolean, default=True)

    sales: Mapped[list["Sale"]] = relationship(back_populates="customer")
    payments: Mapped[list["Payment"]] = relationship(back_populates="customer")
```

## backend/app/models/supplier.py

```python
from sqlalchemy import Boolean, String
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin


class Supplier(TimestampMixin, Base):
    __tablename__ = "suppliers"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(150), index=True)
    phone: Mapped[str | None] = mapped_column(String(20))
    address: Mapped[str | None] = mapped_column(String(255))
    notes: Mapped[str | None] = mapped_column(String(255))
    is_active: Mapped[bool] = mapped_column(Boolean, default=True)

    purchases: Mapped[list["Purchase"]] = relationship(back_populates="supplier")
    payments: Mapped[list["Payment"]] = relationship(back_populates="supplier")
```

## backend/app/models/sale.py

```python
from datetime import datetime
from decimal import Decimal

from sqlalchemy import DateTime, Enum as SAEnum, ForeignKey, Numeric, String
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin
from .enums import SaleStatus


class Sale(TimestampMixin, Base):
    __tablename__ = "sales"

    id: Mapped[int] = mapped_column(primary_key=True)
    invoice_no: Mapped[str] = mapped_column(String(30), unique=True, index=True)

    customer_id: Mapped[int | None] = mapped_column(
        ForeignKey("customers.id", ondelete="SET NULL"), index=True
    )
    customer: Mapped["Customer | None"] = relationship(back_populates="sales")

    subtotal: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    discount_pct: Mapped[Decimal] = mapped_column(Numeric(5, 2), default=Decimal("0"))
    discount: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    tax: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    total: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))

    status: Mapped[SaleStatus] = mapped_column(
        SAEnum(SaleStatus, native_enum=False, length=20), default=SaleStatus.COMPLETED
    )
    sale_date: Mapped[datetime] = mapped_column(DateTime, default=datetime.now, index=True)
    notes: Mapped[str | None] = mapped_column(String(255))

    created_by_id: Mapped[int | None] = mapped_column(ForeignKey("users.id", ondelete="SET NULL"))
    created_by: Mapped["User | None"] = relationship(back_populates="sales")

    items: Mapped[list["SaleItem"]] = relationship(
        back_populates="sale", cascade="all, delete-orphan"
    )
    payments: Mapped[list["Payment"]] = relationship(back_populates="sale")
```

## backend/app/models/sale_item.py

```python
from decimal import Decimal

from sqlalchemy import ForeignKey, Numeric
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin


class SaleItem(TimestampMixin, Base):
    __tablename__ = "sale_items"

    id: Mapped[int] = mapped_column(primary_key=True)
    sale_id: Mapped[int] = mapped_column(
        ForeignKey("sales.id", ondelete="CASCADE"), index=True
    )
    sale: Mapped["Sale"] = relationship(back_populates="items")

    product_id: Mapped[int] = mapped_column(
        ForeignKey("products.id", ondelete="RESTRICT"), index=True
    )
    product: Mapped["Product"] = relationship()

    quantity: Mapped[Decimal] = mapped_column(Numeric(12, 2))
    unit_price: Mapped[Decimal] = mapped_column(Numeric(12, 2))
    tax_rate: Mapped[Decimal] = mapped_column(Numeric(5, 2), default=Decimal("0"))
    line_total: Mapped[Decimal] = mapped_column(Numeric(12, 2))
    returned_qty: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
```

## backend/app/models/purchase.py

```python
from datetime import datetime
from decimal import Decimal

from sqlalchemy import DateTime, Enum as SAEnum, ForeignKey, Numeric, String
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin
from .enums import PaymentMethod, PurchaseStatus


class Purchase(TimestampMixin, Base):
    __tablename__ = "purchases"

    id: Mapped[int] = mapped_column(primary_key=True)
    purchase_no: Mapped[str] = mapped_column(String(30), unique=True, index=True)

    supplier_id: Mapped[int | None] = mapped_column(
        ForeignKey("suppliers.id", ondelete="SET NULL"), index=True
    )
    supplier: Mapped["Supplier | None"] = relationship(back_populates="purchases")

    purchase_date: Mapped[datetime] = mapped_column(DateTime, default=datetime.now, index=True)
    subtotal: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    discount_pct: Mapped[Decimal] = mapped_column(Numeric(5, 2), default=Decimal("0"))
    discount: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    tax: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    total: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    paid_amount: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))
    payment_method: Mapped[PaymentMethod] = mapped_column(
        SAEnum(PaymentMethod, native_enum=False, length=20), default=PaymentMethod.CASH
    )
    status: Mapped[PurchaseStatus] = mapped_column(
        SAEnum(PurchaseStatus, native_enum=False, length=20), default=PurchaseStatus.COMPLETED
    )
    notes: Mapped[str | None] = mapped_column(String(255))

    created_by_id: Mapped[int | None] = mapped_column(ForeignKey("users.id", ondelete="SET NULL"))
    created_by: Mapped["User | None"] = relationship()

    items: Mapped[list["PurchaseItem"]] = relationship(
        back_populates="purchase", cascade="all, delete-orphan"
    )
    payments: Mapped[list["Payment"]] = relationship(back_populates="purchase")
```

## backend/app/models/purchase_item.py

```python
from decimal import Decimal

from sqlalchemy import ForeignKey, Numeric
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin


class PurchaseItem(TimestampMixin, Base):
    __tablename__ = "purchase_items"

    id: Mapped[int] = mapped_column(primary_key=True)
    purchase_id: Mapped[int] = mapped_column(
        ForeignKey("purchases.id", ondelete="CASCADE"), index=True
    )
    purchase: Mapped["Purchase"] = relationship(back_populates="items")

    product_id: Mapped[int] = mapped_column(
        ForeignKey("products.id", ondelete="RESTRICT"), index=True
    )
    product: Mapped["Product"] = relationship()

    quantity: Mapped[Decimal] = mapped_column(Numeric(12, 2))
    unit_cost: Mapped[Decimal] = mapped_column(Numeric(12, 2))
    tax_rate: Mapped[Decimal] = mapped_column(Numeric(5, 2), default=Decimal("0"))
    line_total: Mapped[Decimal] = mapped_column(Numeric(12, 2))
```

## backend/app/models/payment.py

```python
from datetime import datetime
from decimal import Decimal

from sqlalchemy import DateTime, Enum as SAEnum, ForeignKey, Numeric, String
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin
from .enums import PaymentMethod


class Payment(TimestampMixin, Base):
    """Money received (positive) or paid/refunded (negative).

    Exactly ONE of sale_id / purchase_id / customer_id / supplier_id is set.
    method=CREDIT rows are informational only — credit is not money (Phase 12).
    """

    __tablename__ = "payments"

    id: Mapped[int] = mapped_column(primary_key=True)
    sale_id: Mapped[int | None] = mapped_column(
        ForeignKey("sales.id", ondelete="SET NULL"), index=True
    )
    sale: Mapped["Sale | None"] = relationship(back_populates="payments")

    purchase_id: Mapped[int | None] = mapped_column(
        ForeignKey("purchases.id", ondelete="SET NULL"), index=True
    )
    purchase: Mapped["Purchase | None"] = relationship(back_populates="payments")

    customer_id: Mapped[int | None] = mapped_column(
        ForeignKey("customers.id", ondelete="SET NULL"), index=True
    )
    customer: Mapped["Customer | None"] = relationship(back_populates="payments")

    supplier_id: Mapped[int | None] = mapped_column(
        ForeignKey("suppliers.id", ondelete="SET NULL"), index=True
    )
    supplier: Mapped["Supplier | None"] = relationship(back_populates="payments")

    amount: Mapped[Decimal] = mapped_column(Numeric(12, 2))
    method: Mapped[PaymentMethod] = mapped_column(
        SAEnum(PaymentMethod, native_enum=False, length=20), default=PaymentMethod.CASH
    )
    reference: Mapped[str | None] = mapped_column(String(100))
    paid_at: Mapped[datetime] = mapped_column(DateTime, default=datetime.now, index=True)

    created_by_id: Mapped[int | None] = mapped_column(ForeignKey("users.id", ondelete="SET NULL"))
    created_by: Mapped["User | None"] = relationship()
```

## backend/app/models/expense.py

```python
from datetime import datetime
from decimal import Decimal

from sqlalchemy import DateTime, ForeignKey, Numeric, String
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin


class Expense(TimestampMixin, Base):
    __tablename__ = "expenses"

    id: Mapped[int] = mapped_column(primary_key=True)
    expense_date: Mapped[datetime] = mapped_column(DateTime, default=datetime.now, index=True)
    category: Mapped[str] = mapped_column(String(50), index=True)
    amount: Mapped[Decimal] = mapped_column(Numeric(12, 2))
    description: Mapped[str | None] = mapped_column(String(255))

    created_by_id: Mapped[int | None] = mapped_column(ForeignKey("users.id", ondelete="SET NULL"))
    created_by: Mapped["User | None"] = relationship()
```

## backend/app/models/inventory_movement.py

```python
from datetime import datetime
from decimal import Decimal

from sqlalchemy import DateTime, Enum as SAEnum, ForeignKey, Index, Numeric, String
from sqlalchemy.orm import Mapped, mapped_column, relationship

from .base import Base, TimestampMixin
from .enums import MovementType


class InventoryMovement(TimestampMixin, Base):
    """One fact: stock of product X changed by N because of document Y."""

    __tablename__ = "inventory_movements"

    id: Mapped[int] = mapped_column(primary_key=True)
    product_id: Mapped[int] = mapped_column(
        ForeignKey("products.id", ondelete="RESTRICT"), index=True
    )
    product: Mapped["Product"] = relationship(back_populates="inventory_movements")

    movement_type: Mapped[MovementType] = mapped_column(
        SAEnum(MovementType, native_enum=False, length=20), index=True
    )
    quantity: Mapped[Decimal] = mapped_column(Numeric(12, 2))  # signed
    unit_cost: Mapped[Decimal] = mapped_column(Numeric(12, 2), default=Decimal("0"))

    ref_type: Mapped[str | None] = mapped_column(String(30))
    ref_id: Mapped[int | None] = mapped_column()

    note: Mapped[str | None] = mapped_column(String(255))
    created_at: Mapped[datetime] = mapped_column(DateTime, default=datetime.now, index=True)
    created_by_id: Mapped[int | None] = mapped_column(ForeignKey("users.id", ondelete="SET NULL"))
    created_by: Mapped["User | None"] = relationship()

    __table_args__ = (Index("ix_movements_ref", "ref_type", "ref_id"),)
```

## backend/app/models/setting.py

```python
from decimal import Decimal

from sqlalchemy import CheckConstraint, Numeric, String
from sqlalchemy.orm import Mapped, mapped_column

from .base import Base, TimestampMixin


class AppSetting(TimestampMixin, Base):
    __tablename__ = "app_settings"
    __table_args__ = (CheckConstraint("id = 1", name="ck_single_row"),)

    id: Mapped[int] = mapped_column(primary_key=True, default=1)
    shop_name: Mapped[str] = mapped_column(String(150), default="My Shop")
    shop_address: Mapped[str | None] = mapped_column(String(255))
    shop_phone: Mapped[str | None] = mapped_column(String(50))
    shop_gstin: Mapped[str | None] = mapped_column(String(50))
    currency: Mapped[str] = mapped_column(String(10), default="₹")
    default_tax_rate: Mapped[Decimal] = mapped_column(Numeric(5, 2), default=Decimal("0"))
    invoice_footer: Mapped[str | None] = mapped_column(String(255))
```

---

## backend/app/utils/__init__.py

```python
```

## backend/app/utils/money.py

```python
"""Money helpers: every amount in the business layer goes through these.

Decimal is exact (floats are not); ROUND_HALF_UP is what shopkeepers expect.
"""
from decimal import ROUND_HALF_UP, Decimal

TWO_PLACES = Decimal("0.01")
FOUR_PLACES = Decimal("0.0001")


def money(value) -> Decimal:
    return Decimal(str(value)).quantize(TWO_PLACES, rounding=ROUND_HALF_UP)


def percent(value) -> Decimal:
    return Decimal(str(value)).quantize(FOUR_PLACES, rounding=ROUND_HALF_UP)
```

## backend/app/utils/doc_number.py

```python
from datetime import datetime

from sqlalchemy import func, select
from sqlalchemy.orm import Session


def next_document_no(db: Session, model, column, prefix: str, when: datetime | None = None) -> str:
    """Daily-sequence number: INV-20260808-0001, PUR-20260808-0001, …"""
    when = when or datetime.now()
    day_prefix = f"{prefix}-{when.strftime('%Y%m%d')}-"
    last = db.scalar(select(func.max(column)).where(column.like(f"{day_prefix}%")))
    seq = int(str(last).rsplit("-", 1)[-1]) + 1 if last else 1
    return f"{day_prefix}{seq:04d}"
```

## backend/app/utils/pagination.py

```python
from math import ceil

from sqlalchemy import func, select
from sqlalchemy.orm import Session


def paginate(db: Session, stmt, page: int = 1, size: int = 20) -> tuple[list, int]:
    total = db.scalar(select(func.count()).select_from(stmt.order_by(None).subquery())) or 0
    rows = db.scalars(stmt.offset((page - 1) * size).limit(size)).all()
    return rows, total


def total_pages(total: int, size: int) -> int:
    return max(1, ceil(total / size))
```

---

> *Continue to the backend schemas, services, API, tests — part 2 of the code reference.*
# Complete Source Code Reference — backend (part 2 of 4)

## backend/app/schemas/__init__.py

```python
```

## backend/app/schemas/common.py

```python
from datetime import datetime

from pydantic import BaseModel, ConfigDict


class ORMModel(BaseModel):
    model_config = ConfigDict(from_attributes=True)


class Timestamped(ORMModel):
    created_at: datetime
    updated_at: datetime


class Paginated(BaseModel):
    items: list
    total: int
    page: int
    size: int
```

## backend/app/schemas/auth.py

```python
from pydantic import BaseModel, Field

from .user import UserRead


class LoginIn(BaseModel):
    username: str = Field(min_length=1, max_length=64)
    password: str = Field(min_length=1, max_length=64)


class TokenOut(BaseModel):
    access_token: str
    token_type: str = "bearer"
    user: UserRead
```

## backend/app/schemas/user.py

```python
from pydantic import BaseModel, Field

from ..models.enums import UserRole
from .common import ORMModel


class UserCreate(ORMModel):
    username: str = Field(min_length=3, max_length=50)
    full_name: str = Field(min_length=1, max_length=100)
    password: str = Field(min_length=6, max_length=64)
    role: UserRole = UserRole.CASHIER


class UserUpdate(ORMModel):
    full_name: str | None = Field(default=None, min_length=1, max_length=100)
    role: UserRole | None = None
    is_active: bool | None = None


class PasswordIn(BaseModel):
    password: str = Field(min_length=6, max_length=64)


class UserRead(ORMModel):
    id: int
    username: str
    full_name: str
    role: UserRole
    is_active: bool
```

## backend/app/schemas/category.py

```python
from pydantic import Field

from .common import ORMModel, Timestamped


class CategoryCreate(ORMModel):
    name: str = Field(min_length=1, max_length=100)
    description: str | None = Field(default=None, max_length=255)


class CategoryUpdate(ORMModel):
    name: str | None = Field(default=None, min_length=1, max_length=100)
    description: str | None = Field(default=None, max_length=255)


class CategoryRead(Timestamped):
    id: int
    name: str
    description: str | None
```

## backend/app/schemas/product.py

```python
from decimal import Decimal

from pydantic import Field

from .common import ORMModel, Paginated, Timestamped


class ProductCreate(ORMModel):
    name: str = Field(min_length=1, max_length=200)
    sku: str | None = Field(default=None, max_length=50)
    barcode: str | None = Field(default=None, max_length=100)
    category_id: int | None = None
    purchase_price: Decimal = Field(default=0, ge=0, max_digits=12, decimal_places=2)
    selling_price: Decimal = Field(default=0, ge=0, max_digits=12, decimal_places=2)
    tax_rate: Decimal = Field(default=0, ge=0, le=100, max_digits=5, decimal_places=2)
    min_stock: Decimal = Field(default=0, ge=0, max_digits=12, decimal_places=2)


class ProductUpdate(ORMModel):
    name: str | None = Field(default=None, min_length=1, max_length=200)
    sku: str | None = Field(default=None, max_length=50)
    barcode: str | None = Field(default=None, max_length=100)
    category_id: int | None = None
    purchase_price: Decimal | None = Field(default=None, ge=0, max_digits=12, decimal_places=2)
    selling_price: Decimal | None = Field(default=None, ge=0, max_digits=12, decimal_places=2)
    tax_rate: Decimal | None = Field(default=None, ge=0, le=100, max_digits=5, decimal_places=2)
    min_stock: Decimal | None = Field(default=None, ge=0, max_digits=12, decimal_places=2)
    is_active: bool | None = None


class ProductRead(Timestamped):
    id: int
    name: str
    sku: str | None
    barcode: str | None
    category_id: int | None
    category_name: str | None = None
    purchase_price: float
    selling_price: float
    tax_rate: float
    min_stock: float
    current_stock: float
    avg_cost: float
    is_active: bool


class ProductPage(Paginated):
    items: list[ProductRead]
```

## backend/app/schemas/customer.py

```python
from pydantic import Field

from .common import ORMModel


class CustomerCreate(ORMModel):
    name: str = Field(min_length=1, max_length=150)
    phone: str | None = Field(default=None, max_length=20)
    address: str | None = Field(default=None, max_length=255)
    notes: str | None = Field(default=None, max_length=255)


class CustomerUpdate(ORMModel):
    name: str | None = Field(default=None, min_length=1, max_length=150)
    phone: str | None = Field(default=None, max_length=20)
    address: str | None = Field(default=None, max_length=255)
    notes: str | None = Field(default=None, max_length=255)
    is_active: bool | None = None


class CustomerRead(ORMModel):
    id: int
    name: str
    phone: str | None
    address: str | None
    notes: str | None
    is_active: bool
```

## backend/app/schemas/supplier.py

```python
from pydantic import Field

from .common import ORMModel


class SupplierCreate(ORMModel):
    name: str = Field(min_length=1, max_length=150)
    phone: str | None = Field(default=None, max_length=20)
    address: str | None = Field(default=None, max_length=255)
    notes: str | None = Field(default=None, max_length=255)


class SupplierUpdate(ORMModel):
    name: str | None = Field(default=None, min_length=1, max_length=150)
    phone: str | None = Field(default=None, max_length=20)
    address: str | None = Field(default=None, max_length=255)
    notes: str | None = Field(default=None, max_length=255)
    is_active: bool | None = None


class SupplierRead(ORMModel):
    id: int
    name: str
    phone: str | None
    address: str | None
    notes: str | None
    is_active: bool
```

## backend/app/schemas/payment.py

```python
from datetime import datetime
from decimal import Decimal

from pydantic import Field

from ..models.enums import PaymentMethod
from .common import ORMModel


class PaymentRead(ORMModel):
    id: int
    amount: float
    method: PaymentMethod
    reference: str | None
    paid_at: datetime


class CustomerPaymentIn(ORMModel):
    amount: Decimal = Field(gt=0, max_digits=12, decimal_places=2)
    method: PaymentMethod = PaymentMethod.CASH
    reference: str | None = Field(default=None, max_length=100)


class SupplierPaymentIn(ORMModel):
    amount: Decimal = Field(gt=0, max_digits=12, decimal_places=2)
    method: PaymentMethod = PaymentMethod.CASH
    reference: str | None = Field(default=None, max_length=100)
```

## backend/app/schemas/sale.py

```python
from datetime import datetime
from decimal import Decimal

from pydantic import Field

from ..models.enums import PaymentMethod
from .common import ORMModel, Paginated
from .payment import PaymentRead


class SaleItemIn(ORMModel):
    product_id: int
    quantity: Decimal = Field(gt=0, max_digits=12, decimal_places=2)
    unit_price: Decimal | None = Field(default=None, ge=0, max_digits=12, decimal_places=2)
    tax_rate: Decimal | None = Field(default=None, ge=0, le=100, max_digits=5, decimal_places=2)


class PaymentIn(ORMModel):
    method: PaymentMethod = PaymentMethod.CASH
    amount: Decimal | None = Field(default=None, ge=0, max_digits=12, decimal_places=2)
    reference: str | None = Field(default=None, max_length=100)


class SaleCreate(ORMModel):
    customer_id: int | None = None
    discount_pct: Decimal = Field(default=0, ge=0, lt=100, max_digits=5, decimal_places=2)
    notes: str | None = Field(default=None, max_length=255)
    items: list[SaleItemIn] = Field(min_length=1)
    payments: list[PaymentIn] | None = None  # None → full CASH; [] → pure credit


class SaleItemRead(ORMModel):
    id: int
    product_id: int
    product_name: str | None = None
    quantity: float
    unit_price: float
    tax_rate: float
    line_total: float
    returned_qty: float


class SaleRead(ORMModel):
    id: int
    invoice_no: str
    customer_id: int | None
    customer_name: str | None = None
    subtotal: float
    discount_pct: float
    discount: float
    tax: float
    total: float
    status: str
    sale_date: datetime
    notes: str | None
    created_by: str | None
    items: list[SaleItemRead] = []
    payments: list[PaymentRead] = []


class SalePage(Paginated):
    items: list[SaleRead]


class ReturnItemIn(ORMModel):
    product_id: int
    quantity: Decimal = Field(gt=0, max_digits=12, decimal_places=2)


class SaleReturnIn(ORMModel):
    items: list[ReturnItemIn] = Field(min_length=1)
```

## backend/app/schemas/purchase.py

```python
from datetime import datetime
from decimal import Decimal

from pydantic import Field

from ..models.enums import PaymentMethod
from .common import ORMModel, Paginated


class PurchaseItemIn(ORMModel):
    product_id: int
    quantity: Decimal = Field(gt=0, max_digits=12, decimal_places=2)
    unit_cost: Decimal = Field(gt=0, max_digits=12, decimal_places=2)
    tax_rate: Decimal = Field(default=0, ge=0, le=100, max_digits=5, decimal_places=2)


class PurchaseCreate(ORMModel):
    supplier_id: int | None = None
    purchase_date: datetime | None = None
    discount_pct: Decimal = Field(default=0, ge=0, lt=100, max_digits=5, decimal_places=2)
    paid_amount: Decimal = Field(default=0, ge=0, max_digits=12, decimal_places=2)
    payment_method: PaymentMethod = PaymentMethod.CASH
    notes: str | None = Field(default=None, max_length=255)
    items: list[PurchaseItemIn] = Field(min_length=1)


class PurchaseItemRead(ORMModel):
    id: int
    product_id: int
    product_name: str | None = None
    quantity: float
    unit_cost: float
    tax_rate: float
    line_total: float


class PurchaseRead(ORMModel):
    id: int
    purchase_no: str
    supplier_id: int | None
    supplier_name: str | None = None
    purchase_date: datetime
    subtotal: float
    discount_pct: float
    discount: float
    tax: float
    total: float
    paid_amount: float
    payment_method: str
    status: str
    notes: str | None
    created_by: str | None
    items: list[PurchaseItemRead] = []


class PurchasePage(Paginated):
    items: list[PurchaseRead]


class PurchasePayIn(ORMModel):
    amount: Decimal = Field(gt=0, max_digits=12, decimal_places=2)
    method: PaymentMethod = PaymentMethod.CASH
```

## backend/app/schemas/expense.py

```python
from datetime import datetime
from decimal import Decimal

from pydantic import Field

from .common import ORMModel


class ExpenseCreate(ORMModel):
    expense_date: datetime | None = None
    category: str = Field(min_length=1, max_length=50)
    amount: Decimal = Field(gt=0, max_digits=12, decimal_places=2)
    description: str | None = Field(default=None, max_length=255)


class ExpenseUpdate(ORMModel):
    expense_date: datetime | None = None
    category: str | None = Field(default=None, min_length=1, max_length=50)
    amount: Decimal | None = Field(default=None, gt=0, max_digits=12, decimal_places=2)
    description: str | None = Field(default=None, max_length=255)


class ExpenseRead(ORMModel):
    id: int
    expense_date: datetime
    category: str
    amount: float
    description: str | None
    created_by: str | None = None
```

## backend/app/schemas/inventory.py

```python
from datetime import datetime
from decimal import Decimal

from pydantic import Field

from .common import ORMModel, Paginated


class AdjustmentIn(ORMModel):
    product_id: int
    new_stock: Decimal = Field(ge=0, max_digits=12, decimal_places=2)
    reason: str = Field(min_length=1, max_length=255)


class DamageIn(ORMModel):
    product_id: int
    quantity: Decimal = Field(gt=0, max_digits=12, decimal_places=2)
    note: str | None = Field(default=None, max_length=255)


class MovementRead(ORMModel):
    id: int
    product_id: int
    product_name: str | None = None
    movement_type: str
    quantity: float
    unit_cost: float
    ref_type: str | None
    ref_id: int | None
    note: str | None
    created_at: datetime
    created_by: str | None


class MovementPage(Paginated):
    items: list[MovementRead]
```

## backend/app/schemas/settings.py

```python
from decimal import Decimal

from pydantic import Field

from .common import ORMModel


class ShopSettingsRead(ORMModel):
    shop_name: str
    shop_address: str | None
    shop_phone: str | None
    shop_gstin: str | None
    currency: str
    default_tax_rate: float
    invoice_footer: str | None


class ShopSettingsUpdate(ORMModel):
    shop_name: str | None = Field(default=None, min_length=1, max_length=150)
    shop_address: str | None = Field(default=None, max_length=255)
    shop_phone: str | None = Field(default=None, max_length=50)
    shop_gstin: str | None = Field(default=None, max_length=50)
    currency: str | None = Field(default=None, min_length=1, max_length=10)
    default_tax_rate: Decimal | None = Field(default=None, ge=0, le=100, max_digits=5, decimal_places=2)
    invoice_footer: str | None = Field(default=None, max_length=255)
```

---

## backend/app/services/__init__.py

```python
```

## backend/app/services/auth_service.py

```python
import time

from sqlalchemy import select
from sqlalchemy.orm import Session

from app.core.exceptions import AuthenticationError
from app.core.security import create_access_token, verify_password
from app.models import User


def authenticate(db: Session, username: str, password: str) -> tuple[User, str]:
    user = db.scalar(select(User).where(User.username == username.strip()))
    if user is None or not user.is_active or not verify_password(password, user.password_hash):
        time.sleep(1)  # slow down brute-force attempts (Exercise 22.1)
        raise AuthenticationError("Invalid username or password")
    token = create_access_token(subject=user.username, role=user.role.value)
    return user, token
```

## backend/app/services/product_service.py

```python
from decimal import Decimal

from sqlalchemy import or_, select
from sqlalchemy.orm import Session

from app.core.exceptions import ConflictError, NotFoundError
from app.models import Category, Product
from app.schemas.product import ProductCreate, ProductUpdate
from app.utils.money import money, percent
from app.utils.pagination import paginate


def _get_or_404(db: Session, product_id: int) -> Product:
    product = db.get(Product, product_id)
    if product is None:
        raise NotFoundError("Product not found")
    return product


def _check_unique_fields(db: Session, product: Product | None, sku: str | None, barcode: str | None) -> None:
    exclude_id = product.id if product else -1
    if sku:
        dup = db.scalar(select(Product).where(Product.sku == sku, Product.id != exclude_id))
        if dup:
            raise ConflictError(f"SKU '{sku}' is already in use")
    if barcode:
        dup = db.scalar(select(Product).where(Product.barcode == barcode, Product.id != exclude_id))
        if dup:
            raise ConflictError(f"Barcode '{barcode}' is already in use")


def create_product(db: Session, data: ProductCreate) -> Product:
    _check_unique_fields(db, None, data.sku, data.barcode)
    if data.category_id and db.get(Category, data.category_id) is None:
        raise NotFoundError("Category not found")
    product = Product(
        name=data.name.strip(),
        sku=data.sku.strip() if data.sku else None,
        barcode=data.barcode.strip() if data.barcode else None,
        category_id=data.category_id,
        purchase_price=money(data.purchase_price),
        selling_price=money(data.selling_price),
        tax_rate=percent(data.tax_rate),
        min_stock=money(data.min_stock),
    )
    db.add(product)
    db.commit()
    db.refresh(product)
    return product


def list_products(db, search=None, category_id=None, include_inactive=False, page=1, size=20):
    stmt = select(Product)
    if search:
        like = f"%{search.strip()}%"
        stmt = stmt.where(or_(Product.name.ilike(like), Product.sku.ilike(like), Product.barcode.ilike(like)))
    if category_id:
        stmt = stmt.where(Product.category_id == category_id)
    if not include_inactive:
        stmt = stmt.where(Product.is_active.is_(True))
    stmt = stmt.order_by(Product.name)
    return paginate(db, stmt, page, size)


def get_product(db: Session, product_id: int) -> Product:
    return _get_or_404(db, product_id)


def get_by_barcode(db: Session, barcode: str) -> Product | None:
    return db.scalar(
        select(Product).where(Product.barcode == barcode.strip(), Product.is_active.is_(True))
    )


def update_product(db: Session, product_id: int, data: ProductUpdate) -> Product:
    product = _get_or_404(db, product_id)
    updates = data.model_dump(exclude_unset=True)
    _check_unique_fields(db, product, updates.get("sku"), updates.get("barcode"))
    for field, value in updates.items():
        if field in ("purchase_price", "selling_price", "min_stock") and value is not None:
            value = money(value)
        elif field == "tax_rate" and value is not None:
            value = percent(value)
        setattr(product, field, value)
    db.commit()
    db.refresh(product)
    return product


def deactivate_product(db: Session, product_id: int) -> None:
    product = _get_or_404(db, product_id)
    product.is_active = False
    db.commit()
```

## backend/app/services/category_service.py

```python
from sqlalchemy import select
from sqlalchemy.orm import Session

from app.core.exceptions import ConflictError, NotFoundError
from app.models import Category, Product
from app.schemas.category import CategoryCreate, CategoryUpdate


def list_categories(db: Session) -> list[Category]:
    return list(db.scalars(select(Category).order_by(Category.name)))


def create_category(db: Session, data: CategoryCreate) -> Category:
    if db.scalar(select(Category).where(Category.name == data.name.strip())):
        raise ConflictError(f"Category '{data.name}' already exists")
    category = Category(name=data.name.strip(), description=data.description)
    db.add(category)
    db.commit()
    db.refresh(category)
    return category


def update_category(db: Session, category_id: int, data: CategoryUpdate) -> Category:
    category = db.get(Category, category_id)
    if category is None:
        raise NotFoundError("Category not found")
    if data.name and data.name.strip() != category.name:
        if db.scalar(select(Category).where(Category.name == data.name.strip())):
            raise ConflictError(f"Category '{data.name}' already exists")
        category.name = data.name.strip()
    if data.description is not None:
        category.description = data.description
    db.commit()
    db.refresh(category)
    return category


def delete_category(db: Session, category_id: int) -> None:
    category = db.get(Category, category_id)
    if category is None:
        raise NotFoundError("Category not found")
    if db.scalar(select(Product).where(Product.category_id == category_id)):
        raise ConflictError("Cannot delete a category that has products")
    db.delete(category)
    db.commit()
```

## backend/app/services/customer_service.py

```python
from decimal import Decimal

from sqlalchemy import func, select
from sqlalchemy.orm import Session

from app.core.exceptions import NotFoundError
from app.models import Customer, Payment, PaymentMethod, Sale
from app.schemas.customer import CustomerCreate, CustomerUpdate
from app.utils.money import money
from app.utils.pagination import paginate


def create_customer(db: Session, data: CustomerCreate) -> Customer:
    customer = Customer(name=data.name.strip(), phone=data.phone,
                        address=data.address, notes=data.notes)
    db.add(customer)
    db.commit()
    db.refresh(customer)
    return customer


def get_customer(db: Session, customer_id: int) -> Customer:
    customer = db.get(Customer, customer_id)
    if customer is None:
        raise NotFoundError("Customer not found")
    return customer


def list_customers(db: Session, search: str | None = None, page: int = 1, size: int = 20):
    stmt = select(Customer).where(Customer.is_active.is_(True)).order_by(Customer.name)
    if search:
        like = f"%{search.strip()}%"
        stmt = stmt.where(Customer.name.ilike(like) | Customer.phone.ilike(like))
    return paginate(db, stmt, page, size)


def update_customer(db: Session, customer_id: int, data: CustomerUpdate) -> Customer:
    customer = get_customer(db, customer_id)
    for field, value in data.model_dump(exclude_unset=True).items():
        if value is not None:
            setattr(customer, field, value)
    db.commit()
    db.refresh(customer)
    return customer


def customer_balance(db: Session, customer_id: int) -> Decimal:
    sales_total = (
        db.scalar(select(func.coalesce(func.sum(Sale.total), 0)).where(Sale.customer_id == customer_id))
        or Decimal("0")
    )
    payments_total = (
        db.scalar(
            select(func.coalesce(func.sum(Payment.amount), 0)).where(
                Payment.method != PaymentMethod.CREDIT,
                (Payment.customer_id == customer_id)
                | (Payment.sale_id.in_(select(Sale.id).where(Sale.customer_id == customer_id))),
            )
        )
        or Decimal("0")
    )
    return money(sales_total - payments_total)


def customer_ledger(db: Session, customer_id: int) -> list[dict]:
    entries: list[dict] = []
    for sale in db.scalars(select(Sale).where(Sale.customer_id == customer_id).order_by(Sale.sale_date)):
        entries.append({"date": sale.sale_date, "type": "SALE", "reference": sale.invoice_no,
                        "debit": sale.total, "credit": None})
    for p in db.scalars(
        select(Payment)
        .where(Payment.method != PaymentMethod.CREDIT)
        .where((Payment.customer_id == customer_id)
               | (Payment.sale_id.in_(select(Sale.id).where(Sale.customer_id == customer_id))))
        .order_by(Payment.paid_at)
    ):
        entries.append({"date": p.paid_at, "type": "PAYMENT", "reference": p.reference or "",
                        "debit": -p.amount if p.amount < 0 else None,
                        "credit": p.amount if p.amount > 0 else None})

    entries.sort(key=lambda e: e["date"])
    running = Decimal("0")
    for e in entries:
        running += (e["debit"] or Decimal("0")) - (e["credit"] or Decimal("0"))
        e["balance"] = float(money(running))
    return entries


def record_customer_payment(db: Session, customer_id: int, amount: Decimal,
                            method: PaymentMethod, reference: str | None, user_id=None) -> Payment:
    customer = get_customer(db, customer_id)
    payment = Payment(customer_id=customer.id, amount=money(amount), method=method,
                      reference=reference, created_by_id=user_id)
    db.add(payment)
    db.commit()
    db.refresh(payment)
    return payment


def outstanding_customers(db: Session, limit: int = 50) -> list[dict]:
    result = []
    for c in db.scalars(select(Customer).where(Customer.is_active.is_(True))):
        bal = customer_balance(db, c.id)
        if bal > 0:
            result.append({"id": c.id, "name": c.name, "phone": c.phone, "balance": float(bal)})
    result.sort(key=lambda r: r["balance"], reverse=True)
    return result[:limit]
```

## backend/app/services/supplier_service.py

```python
from decimal import Decimal

from sqlalchemy import func, select
from sqlalchemy.orm import Session

from app.core.exceptions import NotFoundError
from app.models import Payment, PaymentMethod, Purchase, Supplier
from app.schemas.supplier import SupplierCreate, SupplierUpdate
from app.utils.money import money
from app.utils.pagination import paginate


def create_supplier(db: Session, data: SupplierCreate) -> Supplier:
    supplier = Supplier(name=data.name.strip(), phone=data.phone,
                        address=data.address, notes=data.notes)
    db.add(supplier)
    db.commit()
    db.refresh(supplier)
    return supplier


def get_supplier(db: Session, supplier_id: int) -> Supplier:
    supplier = db.get(Supplier, supplier_id)
    if supplier is None:
        raise NotFoundError("Supplier not found")
    return supplier


def list_suppliers(db: Session, search: str | None = None, page: int = 1, size: int = 20):
    stmt = select(Supplier).where(Supplier.is_active.is_(True)).order_by(Supplier.name)
    if search:
        like = f"%{search.strip()}%"
        stmt = stmt.where(Supplier.name.ilike(like) | Supplier.phone.ilike(like))
    return paginate(db, stmt, page, size)


def update_supplier(db: Session, supplier_id: int, data: SupplierUpdate) -> Supplier:
    supplier = get_supplier(db, supplier_id)
    for field, value in data.model_dump(exclude_unset=True).items():
        if value is not None:
            setattr(supplier, field, value)
    db.commit()
    db.refresh(supplier)
    return supplier


def supplier_balance(db: Session, supplier_id: int) -> Decimal:
    purchases_total = (
        db.scalar(select(func.coalesce(func.sum(Purchase.total), 0)).where(Purchase.supplier_id == supplier_id))
        or Decimal("0")
    )
    payments_total = (
        db.scalar(
            select(func.coalesce(func.sum(Payment.amount), 0)).where(
                Payment.method != PaymentMethod.CREDIT,
                (Payment.supplier_id == supplier_id)
                | (Payment.purchase_id.in_(select(Purchase.id).where(Purchase.supplier_id == supplier_id))),
            )
        )
        or Decimal("0")
    )
    return money(purchases_total - payments_total)


def supplier_ledger(db: Session, supplier_id: int) -> list[dict]:
    entries: list[dict] = []
    for p in db.scalars(select(Purchase).where(Purchase.supplier_id == supplier_id).order_by(Purchase.purchase_date)):
        entries.append({"date": p.purchase_date, "type": "PURCHASE", "reference": p.purchase_no,
                        "debit": p.total, "credit": None})
    for pay in db.scalars(
        select(Payment)
        .where(Payment.method != PaymentMethod.CREDIT)
        .where((Payment.supplier_id == supplier_id)
               | (Payment.purchase_id.in_(select(Purchase.id).where(Purchase.supplier_id == supplier_id))))
        .order_by(Payment.paid_at)
    ):
        entries.append({"date": pay.paid_at, "type": "PAYMENT", "reference": pay.reference or "",
                        "debit": None if pay.amount > 0 else -pay.amount,
                        "credit": pay.amount if pay.amount > 0 else None})

    entries.sort(key=lambda e: e["date"])
    running = Decimal("0")
    for e in entries:
        running += (e["debit"] or Decimal("0")) - (e["credit"] or Decimal("0"))
        e["balance"] = float(money(running))
    return entries


def record_supplier_payment(db: Session, supplier_id: int, amount: Decimal,
                            method: PaymentMethod, reference: str | None, user_id=None) -> Payment:
    supplier = get_supplier(db, supplier_id)
    payment = Payment(supplier_id=supplier.id, amount=money(amount), method=method,
                      reference=reference, created_by_id=user_id)
    db.add(payment)
    db.commit()
    db.refresh(payment)
    return payment


def outstanding_suppliers(db: Session, limit: int = 50) -> list[dict]:
    result = []
    for s in db.scalars(select(Supplier).where(Supplier.is_active.is_(True))):
        bal = supplier_balance(db, s.id)
        if bal > 0:
            result.append({"id": s.id, "name": s.name, "phone": s.phone, "balance": float(bal)})
    result.sort(key=lambda r: r["balance"], reverse=True)
    return result[:limit]
```

## backend/app/services/inventory_service.py

```python
from decimal import Decimal

from sqlalchemy import func, select
from sqlalchemy.orm import Session

from app.core.exceptions import ConflictError, InsufficientStockError, NotFoundError
from app.models import InventoryMovement, MovementType, Product
from app.utils.money import money
from app.utils.pagination import paginate


def record_movement(
    db: Session,
    *,
    product_id: int,
    movement_type: MovementType,
    quantity: Decimal,
    unit_cost: Decimal | None = None,
    ref_type: str | None = None,
    ref_id: int | None = None,
    note: str | None = None,
    user_id: int | None = None,
    allow_negative: bool = False,
) -> InventoryMovement:
    product = db.get(Product, product_id)
    if product is None:
        raise NotFoundError("Product not found")

    qty = money(quantity)
    if qty == 0:
        raise ConflictError("Movement quantity cannot be zero")

    cost = money(unit_cost) if unit_cost is not None else product.avg_cost
    new_stock = product.current_stock + qty
    if new_stock < 0 and not allow_negative:
        raise InsufficientStockError(
            f"Only {product.current_stock:g} in stock, cannot remove {abs(qty):g}"
        )

    movement = InventoryMovement(
        product_id=product_id,
        movement_type=movement_type,
        quantity=qty,
        unit_cost=cost,
        ref_type=ref_type,
        ref_id=ref_id,
        note=note,
        created_by_id=user_id,
    )
    db.add(movement)
    product.current_stock = new_stock
    return movement


def apply_purchase_cost(product: Product, quantity: Decimal, unit_cost: Decimal) -> None:
    qty = money(quantity)
    cost = money(unit_cost)
    prev_stock = product.current_stock - qty
    if prev_stock <= 0:
        product.avg_cost = cost
    else:
        product.avg_cost = money((prev_stock * product.avg_cost + qty * cost) / (prev_stock + qty))


def adjust_stock(db: Session, *, product_id: int, new_stock: Decimal,
                 reason: str, user_id: int | None = None) -> InventoryMovement:
    product = db.get(Product, product_id)
    if product is None:
        raise NotFoundError("Product not found")
    target = money(new_stock)
    if target < 0:
        raise ConflictError("Stock cannot be negative")
    delta = target - product.current_stock
    if delta == 0:
        raise ConflictError("Stock is already at that value")
    return record_movement(
        db, product_id=product_id, movement_type=MovementType.ADJUSTMENT,
        quantity=delta, ref_type="ADJUSTMENT", note=reason or "Manual adjustment",
        user_id=user_id,
    )


def record_damage(db: Session, *, product_id: int, quantity: Decimal,
                  note: str | None, user_id: int | None = None) -> InventoryMovement:
    return record_movement(
        db, product_id=product_id, movement_type=MovementType.DAMAGE,
        quantity=-money(quantity), ref_type="DAMAGE", note=note, user_id=user_id,
    )


def list_movements(db: Session, product_id: int | None = None,
                   movement_type: MovementType | None = None,
                   page: int = 1, size: int = 50):
    stmt = select(InventoryMovement).order_by(InventoryMovement.created_at.desc())
    if product_id:
        stmt = stmt.where(InventoryMovement.product_id == product_id)
    if movement_type:
        stmt = stmt.where(InventoryMovement.movement_type == movement_type)
    return paginate(db, stmt, page, size)


def low_stock_products(db: Session) -> list[Product]:
    return list(
        db.scalars(
            select(Product)
            .where(Product.is_active.is_(True), Product.current_stock <= Product.min_stock)
            .order_by(Product.current_stock)
        )
    )


def dead_stock(db: Session, days: int = 60) -> list[Product]:
    from datetime import datetime, timedelta

    cutoff = datetime.now() - timedelta(days=days)
    sold_recently = select(InventoryMovement.product_id).where(
        InventoryMovement.movement_type == MovementType.SALE,
        InventoryMovement.created_at >= cutoff,
    )
    return list(
        db.scalars(
            select(Product)
            .where(Product.is_active.is_(True), Product.current_stock > 0)
            .where(~Product.id.in_(sold_recently))
        )
    )


def stock_value(db: Session) -> Decimal:
    return db.scalar(select(func.sum(Product.current_stock * Product.avg_cost))) or Decimal("0")


def reconcile_stock(db: Session) -> int:
    corrected = 0
    for product in db.scalars(select(Product)):
        total = db.scalar(
            select(func.sum(InventoryMovement.quantity)).where(InventoryMovement.product_id == product.id)
        ) or Decimal("0")
        if product.current_stock != money(total):
            product.current_stock = money(total)
            corrected += 1
    db.commit()
    return corrected
```

## backend/app/services/sale_service.py

```python
import logging
from decimal import Decimal

from sqlalchemy import select
from sqlalchemy.exc import IntegrityError
from sqlalchemy.orm import Session

from app.core.exceptions import (ConflictError, InsufficientStockError,
                                 NotFoundError, ValidationFailedError)
from app.models import (MovementType, Payment, PaymentMethod, Product, Sale,
                        SaleItem, SaleStatus)
from app.schemas.sale import PaymentIn, SaleCreate, SaleReturnIn
from app.services import inventory_service, invoice_service
from app.utils.doc_number import next_document_no
from app.utils.money import money, percent
from app.utils.pagination import paginate

logger = logging.getLogger(__name__)


def _calculate(lines: list[dict], discount_pct: Decimal) -> dict:
    subtotal = money(0)
    tax = money(0)
    for line in lines:
        line_total = money(line["quantity"] * line["unit_price"])
        line["line_total"] = line_total
        subtotal += line_total
        discounted = line_total * (1 - discount_pct / 100)
        tax += money(discounted * line["tax_rate"] / 100)
    subtotal = money(subtotal)
    discount = money(subtotal * discount_pct / 100)
    total = money(subtotal - discount + tax)
    return {"subtotal": subtotal, "discount": discount, "tax": tax, "total": total}


def _create_sale(db: Session, data: SaleCreate, user_id: int | None) -> Sale:
    product_ids = list({i.product_id for i in data.items})
    products = {p.id: p for p in db.scalars(select(Product).where(Product.id.in_(product_ids)))}
    missing = set(product_ids) - set(products)
    if missing:
        raise NotFoundError(f"Product(s) not found: {sorted(missing)}")

    quantities: dict[int, Decimal] = {}
    for item in data.items:
        quantities[item.product_id] = quantities.get(item.product_id, money(0)) + money(item.quantity)

    for pid, qty in quantities.items():
        product = products[pid]
        if not product.is_active:
            raise ConflictError(f"'{product.name}' is deactivated")
        if qty <= 0:
            raise ValidationFailedError("Quantity must be greater than zero")
        if qty > product.current_stock:
            raise InsufficientStockError(
                f"Not enough stock for '{product.name}': have {product.current_stock:g}, need {qty:g}"
            )

    discount_pct = percent(data.discount_pct)
    lines = []
    for item in data.items:
        product = products[item.product_id]
        lines.append({
            "product": product,
            "quantity": money(item.quantity),
            "unit_price": money(item.unit_price) if item.unit_price is not None else product.selling_price,
            "tax_rate": percent(item.tax_rate) if item.tax_rate is not None else product.tax_rate,
        })
    calc = _calculate(lines, discount_pct)

    invoice_no = next_document_no(db, Sale, Sale.invoice_no, "INV")
    sale = Sale(
        invoice_no=invoice_no,
        customer_id=data.customer_id,
        subtotal=calc["subtotal"],
        discount_pct=discount_pct,
        discount=calc["discount"],
        tax=calc["tax"],
        total=calc["total"],
        notes=data.notes,
        created_by_id=user_id,
    )
    db.add(sale)
    db.flush()

    for line in lines:
        db.add(SaleItem(
            sale_id=sale.id,
            product_id=line["product"].id,
            quantity=line["quantity"],
            unit_price=line["unit_price"],
            tax_rate=line["tax_rate"],
            line_total=line["line_total"],
        ))

    # "Credit is not money": CREDIT entries never become Payment rows.
    # None → default full CASH payment. [] → pure credit sale (no payment).
    if data.payments is None:
        payments = [PaymentIn(method=PaymentMethod.CASH)]
    else:
        payments = [p for p in data.payments if p.method != PaymentMethod.CREDIT]

    for p in payments:
        db.add(Payment(
            sale_id=sale.id,
            amount=money(p.amount) if p.amount is not None else calc["total"],
            method=p.method,
            reference=p.reference,
            created_by_id=user_id,
        ))

    for pid, qty in quantities.items():
        product = products[pid]
        inventory_service.record_movement(
            db,
            product_id=pid,
            movement_type=MovementType.SALE,
            quantity=-qty,
            unit_cost=product.avg_cost,
            ref_type="SALE",
            ref_id=sale.id,
            user_id=user_id,
        )

    db.commit()
    db.refresh(sale)
    logger.info("Sale %s created: total=%s", sale.invoice_no, sale.total)

    # Step 14 — PDF after commit, best-effort (never rolls back the sale)
    try:
        invoice_service.generate_invoice(db, sale)
    except Exception:
        logger.exception("Invoice generation failed for %s", sale.invoice_no)

    return sale


def create_sale(db: Session, data: SaleCreate, user_id: int | None = None) -> Sale:
    """With a retry on invoice-number collision (the UNIQUE constraint is the backstop)."""
    for attempt in range(2):
        try:
            return _create_sale(db, data, user_id)
        except IntegrityError:
            db.rollback()
            if attempt == 1:
                raise ConflictError("Could not allocate invoice number — please retry")
            logger.warning("Invoice number collision, retrying…")
    raise ConflictError("Could not allocate invoice number")


def get_sale(db: Session, sale_id: int) -> Sale:
    sale = db.get(Sale, sale_id)
    if sale is None:
        raise NotFoundError("Sale not found")
    return sale


def list_sales(db, from_date=None, to_date=None, customer_id=None, search=None, page=1, size=20):
    stmt = select(Sale).order_by(Sale.sale_date.desc())
    if from_date:
        stmt = stmt.where(Sale.sale_date >= from_date)
    if to_date:
        stmt = stmt.where(Sale.sale_date <= to_date)
    if customer_id:
        stmt = stmt.where(Sale.customer_id == customer_id)
    if search:
        stmt = stmt.where(Sale.invoice_no.ilike(f"%{search.strip()}%"))
    return paginate(db, stmt, page, size)


def return_sale_items(db: Session, sale_id: int, data: SaleReturnIn, user_id: int | None = None) -> Sale:
    sale = get_sale(db, sale_id)
    if sale.status == SaleStatus.RETURNED:
        raise ConflictError("This sale is already fully returned")

    refund_total = money(0)
    for item in data.items:
        sale_item = next((si for si in sale.items if si.product_id == item.product_id), None)
        if sale_item is None:
            raise NotFoundError(f"Product {item.product_id} is not on this sale")
        qty = money(item.quantity)
        remaining = sale_item.quantity - sale_item.returned_qty
        if qty > remaining:
            raise ConflictError(
                f"Can return at most {remaining:g} of this product "
                f"({sale_item.returned_qty:g} already returned)"
            )
        unit_value = sale_item.line_total / sale_item.quantity if sale_item.quantity else 0
        line_refund = money(qty * unit_value * (1 - sale.discount_pct / 100) * (1 + sale_item.tax_rate / 100))
        refund_total += line_refund

        sale_item.returned_qty = money(sale_item.returned_qty + qty)
        inventory_service.record_movement(
            db,
            product_id=sale_item.product_id,
            movement_type=MovementType.RETURN,
            quantity=qty,
            unit_cost=sale_item.product.avg_cost if sale_item.product else sale_item.unit_price,
            ref_type="RETURN",
            ref_id=sale.id,
            note=f"Return on {sale.invoice_no}",
            user_id=user_id,
        )

    if refund_total > 0:
        db.add(Payment(
            sale_id=sale.id,
            amount=-refund_total,
            method=PaymentMethod.CASH,
            reference=f"Refund {sale.invoice_no}",
            created_by_id=user_id,
        ))

    all_returned = all(si.returned_qty >= si.quantity for si in sale.items)
    sale.status = SaleStatus.RETURNED if all_returned else SaleStatus.COMPLETED
    db.commit()
    db.refresh(sale)
    return sale
```

## backend/app/services/purchase_service.py

```python
import logging
from decimal import Decimal

from sqlalchemy import select
from sqlalchemy.orm import Session

from app.core.exceptions import NotFoundError, ValidationFailedError
from app.models import (MovementType, Payment, PaymentMethod, Product,
                        Purchase, PurchaseItem, PurchaseStatus)
from app.schemas.purchase import PurchaseCreate
from app.services import inventory_service
from app.utils.doc_number import next_document_no
from app.utils.money import money, percent
from app.utils.pagination import paginate

logger = logging.getLogger(__name__)


def create_purchase(db: Session, data: PurchaseCreate, user_id: int | None = None) -> Purchase:
    product_ids = list({i.product_id for i in data.items})
    products = {p.id: p for p in db.scalars(select(Product).where(Product.id.in_(product_ids)))}
    missing = set(product_ids) - set(products)
    if missing:
        raise NotFoundError(f"Product(s) not found: {sorted(missing)}")

    discount_pct = percent(data.discount_pct)
    subtotal = money(0)
    tax = money(0)
    lines = []
    for item in data.items:
        product = products[item.product_id]
        qty = money(item.quantity)
        cost = money(item.unit_cost)
        if qty <= 0 or cost < 0:
            raise ValidationFailedError("Quantity and unit cost must be positive")
        line_total = money(qty * cost)
        tax += money(line_total * (1 - discount_pct / 100) * percent(item.tax_rate) / 100)
        subtotal += line_total
        lines.append({"product": product, "qty": qty, "cost": cost,
                      "tax_rate": percent(item.tax_rate), "line_total": line_total})

    subtotal = money(subtotal)
    discount = money(subtotal * discount_pct / 100)
    total = money(subtotal - discount + tax)
    paid = money(data.paid_amount)
    status = PurchaseStatus.COMPLETED if paid >= total else PurchaseStatus.PARTIAL

    purchase_no = next_document_no(db, Purchase, Purchase.purchase_no, "PUR")
    purchase = Purchase(
        purchase_no=purchase_no,
        supplier_id=data.supplier_id,
        purchase_date=data.purchase_date,
        subtotal=subtotal,
        discount_pct=discount_pct,
        discount=discount,
        tax=tax,
        total=total,
        paid_amount=paid,
        payment_method=data.payment_method,
        status=status,
        notes=data.notes,
        created_by_id=user_id,
    )
    db.add(purchase)
    db.flush()

    for line in lines:
        db.add(PurchaseItem(
            purchase_id=purchase.id,
            product_id=line["product"].id,
            quantity=line["qty"],
            unit_cost=line["cost"],
            tax_rate=line["tax_rate"],
            line_total=line["line_total"],
        ))

    if paid > 0:
        db.add(Payment(
            purchase_id=purchase.id,
            amount=paid,
            method=data.payment_method,
            reference=f"{purchase_no} payment",
            created_by_id=user_id,
        ))

    for line in lines:
        product = line["product"]
        inventory_service.record_movement(
            db,
            product_id=product.id,
            movement_type=MovementType.PURCHASE,
            quantity=line["qty"],
            unit_cost=line["cost"],
            ref_type="PURCHASE",
            ref_id=purchase.id,
            user_id=user_id,
        )
        inventory_service.apply_purchase_cost(product, line["qty"], line["cost"])
        product.purchase_price = line["cost"]

    db.commit()
    db.refresh(purchase)
    logger.info("Purchase %s created: total=%s paid=%s", purchase_no, total, paid)
    return purchase


def get_purchase(db: Session, purchase_id: int) -> Purchase:
    purchase = db.get(Purchase, purchase_id)
    if purchase is None:
        raise NotFoundError("Purchase not found")
    return purchase


def list_purchases(db, from_date=None, to_date=None, supplier_id=None, search=None, page=1, size=20):
    stmt = select(Purchase).order_by(Purchase.purchase_date.desc())
    if from_date:
        stmt = stmt.where(Purchase.purchase_date >= from_date)
    if to_date:
        stmt = stmt.where(Purchase.purchase_date <= to_date)
    if supplier_id:
        stmt = stmt.where(Purchase.supplier_id == supplier_id)
    if search:
        stmt = stmt.where(Purchase.purchase_no.ilike(f"%{search.strip()}%"))
    return paginate(db, stmt, page, size)


def record_purchase_payment(db: Session, purchase_id: int, amount: Decimal,
                            method: PaymentMethod, user_id=None) -> Payment:
    purchase = get_purchase(db, purchase_id)
    payment = Payment(purchase_id=purchase.id, amount=money(amount), method=method,
                      reference=f"{purchase.purchase_no} payment", created_by_id=user_id)
    db.add(payment)
    purchase.paid_amount = money(purchase.paid_amount + payment.amount)
    purchase.status = PurchaseStatus.COMPLETED if purchase.paid_amount >= purchase.total else PurchaseStatus.PARTIAL
    db.commit()
    db.refresh(payment)
    return payment
```

## backend/app/services/expense_service.py

```python
from sqlalchemy import func, select
from sqlalchemy.orm import Session

from app.core.exceptions import NotFoundError
from app.models import Expense
from app.schemas.expense import ExpenseCreate, ExpenseUpdate
from app.utils.money import money
from app.utils.pagination import paginate


def create_expense(db: Session, data: ExpenseCreate, user_id: int | None = None) -> Expense:
    expense = Expense(expense_date=data.expense_date, category=data.category.strip(),
                      amount=money(data.amount), description=data.description,
                      created_by_id=user_id)
    db.add(expense)
    db.commit()
    db.refresh(expense)
    return expense


def list_expenses(db, from_date=None, to_date=None, category=None, page=1, size=50):
    stmt = select(Expense).order_by(Expense.expense_date.desc())
    if from_date:
        stmt = stmt.where(Expense.expense_date >= from_date)
    if to_date:
        stmt = stmt.where(Expense.expense_date <= to_date)
    if category:
        stmt = stmt.where(Expense.category == category)
    return paginate(db, stmt, page, size)


def get_expense(db: Session, expense_id: int) -> Expense:
    expense = db.get(Expense, expense_id)
    if expense is None:
        raise NotFoundError("Expense not found")
    return expense


def update_expense(db: Session, expense_id: int, data: ExpenseUpdate) -> Expense:
    expense = get_expense(db, expense_id)
    for field, value in data.model_dump(exclude_unset=True).items():
        if field == "amount" and value is not None:
            value = money(value)
        if value is not None:
            setattr(expense, field, value)
    db.commit()
    db.refresh(expense)
    return expense


def delete_expense(db: Session, expense_id: int) -> None:
    expense = get_expense(db, expense_id)
    db.delete(expense)
    db.commit()


def expense_categories(db: Session) -> list[str]:
    rows = db.execute(select(Expense.category).distinct().order_by(Expense.category)).all()
    return [r[0] for r in rows]


def expense_total(db: Session, from_date, to_date):
    return (
        db.scalar(
            select(func.coalesce(func.sum(Expense.amount), 0)).where(
                Expense.expense_date >= from_date, Expense.expense_date <= to_date
            )
        )
        or 0
    )
```

## backend/app/services/report_service.py

```python
from datetime import datetime, time
from decimal import Decimal

from sqlalchemy import func, select
from sqlalchemy.orm import Session

from app.models import (Customer, Expense, InventoryMovement, MovementType,
                        Product, Purchase, Sale, SaleItem, Supplier)
from app.services import inventory_service
from app.utils.money import money


def _day_bounds(dt: datetime) -> tuple[datetime, datetime]:
    return datetime.combine(dt.date(), time.min), datetime.combine(dt.date(), time.max)


def revenue(db: Session, from_dt: datetime, to_dt: datetime) -> Decimal:
    return (
        db.scalar(select(func.coalesce(func.sum(Sale.total), 0)).where(
            Sale.sale_date >= from_dt, Sale.sale_date <= to_dt))
        or Decimal("0")
    )


def cogs(db: Session, from_dt: datetime, to_dt: datetime) -> Decimal:
    return (
        db.scalar(select(func.coalesce(func.sum(InventoryMovement.quantity * InventoryMovement.unit_cost), 0)).where(
            InventoryMovement.movement_type == MovementType.SALE,
            InventoryMovement.created_at >= from_dt,
            InventoryMovement.created_at <= to_dt))
        or Decimal("0")
    )


def expenses_total(db: Session, from_dt: datetime, to_dt: datetime) -> Decimal:
    return (
        db.scalar(select(func.coalesce(func.sum(Expense.amount), 0)).where(
            Expense.expense_date >= from_dt, Expense.expense_date <= to_dt))
        or Decimal("0")
    )


def profit_summary(db: Session, from_dt: datetime, to_dt: datetime) -> dict:
    rev = money(revenue(db, from_dt, to_dt))
    cost = money(cogs(db, from_dt, to_dt))
    exp = money(expenses_total(db, from_dt, to_dt))
    gross = money(rev - cost)
    net = money(gross - exp)
    return {
        "from": from_dt.isoformat(), "to": to_dt.isoformat(),
        "revenue": float(rev), "cogs": float(cost), "gross_profit": float(gross),
        "expenses": float(exp), "net_profit": float(net),
    }


def sales_daily(db: Session, from_dt: datetime, to_dt: datetime) -> list[dict]:
    rows = db.execute(
        select(func.date(Sale.sale_date), func.count(Sale.id), func.sum(Sale.total))
        .where(Sale.sale_date >= from_dt, Sale.sale_date <= to_dt)
        .group_by(func.date(Sale.sale_date))
        .order_by(func.date(Sale.sale_date))
    ).all()
    return [{"date": d, "transactions": n, "revenue": float(money(t))} for d, n, t in rows]


def sales_monthly(db: Session, from_dt: datetime, to_dt: datetime) -> list[dict]:
    rows = db.execute(
        select(func.strftime("%Y-%m", Sale.sale_date), func.count(Sale.id), func.sum(Sale.total))
        .where(Sale.sale_date >= from_dt, Sale.sale_date <= to_dt)
        .group_by(func.strftime("%Y-%m", Sale.sale_date))
        .order_by(func.strftime("%Y-%m", Sale.sale_date))
    ).all()
    return [{"month": m, "transactions": n, "revenue": float(money(t))} for m, n, t in rows]


def product_sales(db: Session, from_dt: datetime, to_dt: datetime) -> list[dict]:
    rows = db.execute(
        select(SaleItem.product_id, func.sum(SaleItem.quantity), func.sum(SaleItem.line_total))
        .join(Sale, Sale.id == SaleItem.sale_id)
        .where(Sale.sale_date >= from_dt, Sale.sale_date <= to_dt, Sale.status != "RETURNED")
        .group_by(SaleItem.product_id)
        .order_by(func.sum(SaleItem.quantity).desc())
    ).all()
    result = []
    for pid, units, amount in rows:
        product = db.get(Product, pid)
        result.append({"product_id": pid, "name": product.name if product else f"#{pid}",
                       "units": float(units), "amount": float(money(amount))})
    return result


def purchase_report(db: Session, from_dt: datetime, to_dt: datetime) -> list[dict]:
    rows = db.scalars(
        select(Purchase).where(Purchase.purchase_date >= from_dt, Purchase.purchase_date <= to_dt)
        .order_by(Purchase.purchase_date.desc())
    ).all()
    return [
        {"id": p.id, "purchase_no": p.purchase_no,
         "supplier": p.supplier.name if p.supplier else None,
         "date": p.purchase_date, "total": p.total, "paid": p.paid_amount,
         "balance": float(money(p.total - p.paid_amount)), "status": p.status}
        for p in rows
    ]


def expense_report(db: Session, from_dt: datetime, to_dt: datetime) -> dict:
    rows = db.execute(
        select(Expense.category, func.sum(Expense.amount))
        .where(Expense.expense_date >= from_dt, Expense.expense_date <= to_dt)
        .group_by(Expense.category)
        .order_by(func.sum(Expense.amount).desc())
    ).all()
    return {
        "total": float(expenses_total(db, from_dt, to_dt)),
        "by_category": [{"category": c, "amount": float(money(a))} for c, a in rows],
    }


def inventory_report(db: Session) -> dict:
    return {
        "stock_value": float(inventory_service.stock_value(db)),
        "low_stock": [
            {"id": p.id, "name": p.name, "current_stock": p.current_stock, "min_stock": p.min_stock}
            for p in inventory_service.low_stock_products(db)
        ],
        "dead_stock": [
            {"id": p.id, "name": p.name, "current_stock": p.current_stock}
            for p in inventory_service.dead_stock(db, days=60)
        ],
    }


def customer_report(db: Session) -> list[dict]:
    from app.services.customer_service import customer_balance
    result = []
    for c in db.scalars(select(Customer).where(Customer.is_active.is_(True))):
        bal = customer_balance(db, c.id)
        result.append({"id": c.id, "name": c.name, "phone": c.phone, "balance": float(bal)})
    return sorted(result, key=lambda r: r["balance"], reverse=True)


def supplier_report(db: Session) -> list[dict]:
    from app.services.supplier_service import supplier_balance
    result = []
    for s in db.scalars(select(Supplier).where(Supplier.is_active.is_(True))):
        bal = supplier_balance(db, s.id)
        result.append({"id": s.id, "name": s.name, "phone": s.phone, "balance": float(bal)})
    return sorted(result, key=lambda r: r["balance"], reverse=True)
```

## backend/app/services/dashboard_service.py

```python
from datetime import datetime, timedelta

from sqlalchemy import func, select
from sqlalchemy.orm import Session

from app.models import (Expense, InventoryMovement, MovementType, Product, Sale)
from app.services import inventory_service, report_service
from app.utils.money import money


def _range_for(days: int) -> tuple[datetime, datetime]:
    start = datetime.now().replace(hour=0, minute=0, second=0, microsecond=0)
    return start - timedelta(days=days - 1), datetime.now()


def daily_series(db: Session, days: int, metric: str) -> list[dict]:
    start, _ = _range_for(days)
    rows: dict[str, float] = {}
    for i in range(days):
        day = start + timedelta(days=i)
        rows[day.strftime("%Y-%m-%d")] = 0.0

    if metric == "revenue":
        query = (select(func.date(Sale.sale_date), func.sum(Sale.total))
                 .where(Sale.sale_date >= start).group_by(func.date(Sale.sale_date)))
    else:
        query = (select(func.date(Expense.expense_date), func.sum(Expense.amount))
                 .where(Expense.expense_date >= start).group_by(func.date(Expense.expense_date)))

    for day, total in db.execute(query):
        if day in rows:
            rows[day] = float(total)
    return [{"date": d, "value": v} for d, v in rows.items()]


def top_products(db: Session, days: int = 30, limit: int = 5) -> list[dict]:
    start, _ = _range_for(days)
    rows = db.execute(
        select(InventoryMovement.product_id, func.sum(-InventoryMovement.quantity).label("sold"))
        .where(InventoryMovement.movement_type == MovementType.SALE,
               InventoryMovement.created_at >= start)
        .group_by(InventoryMovement.product_id)
        .order_by(func.sum(-InventoryMovement.quantity).desc())
        .limit(limit)
    ).all()
    result = []
    for pid, sold in rows:
        product = db.get(Product, pid)
        if product:
            result.append({"product_id": pid, "name": product.name, "sold": float(sold)})
    return result


def summary(db: Session) -> dict:
    today_start = datetime.now().replace(hour=0, minute=0, second=0, microsecond=0)
    now = datetime.now()

    today_revenue = report_service.revenue(db, today_start, now)
    today_cogs = report_service.cogs(db, today_start, now)
    today_txns = db.scalar(
        select(func.count()).select_from(Sale).where(Sale.sale_date >= today_start)
    ) or 0

    revenue_series = daily_series(db, 14, "revenue")
    expense_series = daily_series(db, 14, "expenses")
    profit_series = []
    for r in revenue_series:
        day = datetime.fromisoformat(r["date"])
        day_cogs = report_service.cogs(db, day, day.replace(hour=23, minute=59, second=59))
        profit_series.append({"date": r["date"], "value": float(money(r["value"] - day_cogs))})

    recent = db.scalars(select(Sale).order_by(Sale.sale_date.desc()).limit(5)).all()

    return {
        "today": {
            "revenue": float(today_revenue),
            "profit": float(money(today_revenue - today_cogs)),
            "transactions": today_txns,
        },
        "low_stock": [
            {"id": p.id, "name": p.name, "current_stock": p.current_stock, "min_stock": p.min_stock}
            for p in inventory_service.low_stock_products(db)
        ],
        "top_products": top_products(db),
        "recent_sales": [
            {"id": s.id, "invoice_no": s.invoice_no, "total": s.total, "sale_date": s.sale_date,
             "customer_name": s.customer.name if s.customer else None}
            for s in recent
        ],
        "revenue_series": revenue_series,
        "expense_series": expense_series,
        "profit_series": profit_series,
    }
```

## backend/app/services/settings_service.py

```python
from sqlalchemy.orm import Session

from app.models import AppSetting
from app.schemas.settings import ShopSettingsUpdate
from app.utils.money import money


def get_settings(db: Session) -> AppSetting:
    """Return the settings row, creating the default if missing."""
    row = db.get(AppSetting, 1)
    if row is None:
        from app.database.seed import seed_initial_data
        seed_initial_data(db)
        row = db.get(AppSetting, 1)
    return row


def update_settings(db: Session, data: ShopSettingsUpdate) -> AppSetting:
    row = get_settings(db)
    for field, value in data.model_dump(exclude_unset=True).items():
        if field == "default_tax_rate" and value is not None:
            value = money(value)
        if value is not None:
            setattr(row, field, value)
    db.commit()
    db.refresh(row)
    return row
```

## backend/app/services/backup_service.py

```python
import logging
import shutil
import sqlite3
from datetime import datetime, timedelta
from pathlib import Path

from sqlalchemy import text
from sqlalchemy.orm import Session

from app.core.config import settings
from app.core.exceptions import AppError

logger = logging.getLogger(__name__)


def _now_str() -> str:
    return datetime.now().strftime("%Y%m%d_%H%M%S")


def list_backups() -> list[dict]:
    settings.backups_dir.mkdir(parents=True, exist_ok=True)
    backups = []
    for p in sorted(settings.backups_dir.glob("retail_backup_*.db")):
        backups.append({
            "filename": p.name,
            "size": p.stat().st_size,
            "created_at": datetime.fromtimestamp(p.stat().st_mtime).isoformat(),
        })
    return sorted(backups, key=lambda b: b["created_at"], reverse=True)


def _verify_backup(path: Path) -> bool:
    if not path.exists() or path.stat().st_size == 0:
        return False
    try:
        conn = sqlite3.connect(str(path))
        try:
            row = conn.execute("PRAGMA integrity_check").fetchone()
            return bool(row and row[0] == "ok")
        finally:
            conn.close()
    except sqlite3.Error:
        return False


def rotate() -> None:
    cutoff = datetime.now() - timedelta(days=settings.BACKUP_KEEP_DAYS)
    for p in settings.backups_dir.glob("retail_backup_*.db"):
        if datetime.fromtimestamp(p.stat().st_mtime) < cutoff:
            p.unlink(missing_ok=True)
            logger.info("Rotated old backup: %s", p.name)


def create_backup(db: Session) -> dict:
    settings.backups_dir.mkdir(parents=True, exist_ok=True)
    path = settings.backups_dir / f"retail_backup_{_now_str()}.db"

    db.rollback()
    db.execute(text(f"VACUUM INTO '{path.as_posix()}'"))

    if not _verify_backup(path):
        path.unlink(missing_ok=True)
        raise AppError("Backup failed verification — no backup file kept")

    rotate()
    logger.info("Backup created and verified: %s", path.name)
    return {"filename": path.name, "size": path.stat().st_size,
            "created_at": datetime.now().isoformat(), "verified": True}


def auto_backup_if_due(db: Session) -> dict | None:
    backups = list_backups()
    if backups:
        newest = datetime.fromisoformat(backups[0]["created_at"])
        if datetime.now() - newest < timedelta(hours=24):
            return None
    return create_backup(db)


def restore_backup(db: Session, filename: str) -> None:
    if not filename or ".." in filename or "/" in filename or "\\" in filename:
        raise AppError("Invalid backup filename")
    src = settings.backups_dir / filename
    if not _verify_backup(src):
        raise AppError("Backup file failed verification — refusing to restore")

    db.commit()
    safety = create_backup(db)

    from app.database.database import engine
    engine.dispose()

    target = settings.db_dir / settings.DATABASE_FILE
    shutil.copy2(src, target)
    for suffix in ("-wal", "-shm"):
        Path(str(target) + suffix).unlink(missing_ok=True)

    logger.warning("Restored %s (safety backup: %s)", filename, safety["filename"])
```

## backend/app/services/invoice_service.py

```python
import logging
from pathlib import Path

from sqlalchemy.orm import Session

from app.core.config import settings
from app.models import Sale
from app.pdf.invoice import render_invoice_pdf, render_thermal_receipt, sale_document

logger = logging.getLogger(__name__)


def invoice_path(invoice_no: str) -> Path:
    return settings.invoices_dir / f"{invoice_no}.pdf"


def generate_invoice(db: Session, sale: Sale, force: bool = False) -> Path:
    """Save the PDF. Best-effort: never rolled back, always regenerable."""
    path = invoice_path(sale.invoice_no)
    if path.exists() and not force:
        return path
    doc = sale_document(db, sale)
    buf = render_invoice_pdf(doc)
    path.write_bytes(buf.getvalue())
    logger.info("Invoice %s written to %s", sale.invoice_no, path)
    return path


def generate_receipt(db: Session, sale: Sale) -> bytes:
    doc = sale_document(db, sale)
    return render_thermal_receipt(doc).getvalue()
```

---

## backend/app/pdf/__init__.py

```python
```

## backend/app/pdf/invoice.py

```python
"""PDF invoice generation with ReportLab: A4 invoice + 80 mm thermal receipt."""
import logging
from io import BytesIO
from pathlib import Path

from reportlab.lib import colors
from reportlab.lib.enums import TA_RIGHT
from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import ParagraphStyle, getSampleStyleSheet
from reportlab.lib.units import mm
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.platypus import (HRFlowable, Paragraph, SimpleDocTemplate,
                                Spacer, Table, TableStyle)
from reportlab.pdfgen import canvas as pdfcanvas

from app.core.config import settings
from app.models import AppSetting, Sale

logger = logging.getLogger(__name__)

_FONT = "Helvetica"
_FONT_BOLD = "Helvetica-Bold"
_FONT_NAME = "LrmSans"


def _register_fonts() -> None:
    """Try to register a TrueType font that renders ₹ (U+20B9)."""
    global _FONT, _FONT_BOLD
    candidates = [
        ("C:/Windows/Fonts/arial.ttf", "C:/Windows/Fonts/arialbd.ttf"),
        ("C:/Windows/Fonts/calibri.ttf", "C:/Windows/Fonts/calibrib.ttf"),
        ("C:/Windows/Fonts/segoeui.ttf", "C:/Windows/Fonts/segoeuib.ttf"),
    ]
    for regular, bold in candidates:
        if not Path(regular).exists():
            continue
        try:
            pdfmetrics.registerFont(TTFont(_FONT_NAME, regular))
            _FONT = _FONT_NAME
            if Path(bold).exists():
                pdfmetrics.registerFont(TTFont(_FONT_NAME + "-Bold", bold))
                _FONT_BOLD = _FONT_NAME + "-Bold"
            else:
                _FONT_BOLD = "Helvetica-Bold"
            return
        except Exception:
            logger.warning("Could not register font %s", regular)
    logger.warning("No TTF with ₹ support found; ₹ may render as a box")


_register_fonts()


def _shop_profile(db) -> dict:
    row = db.get(AppSetting, 1)
    return {
        "name": row.shop_name if row else settings.SHOP_NAME,
        "address": row.shop_address if row else settings.SHOP_ADDRESS,
        "phone": row.shop_phone if row else settings.SHOP_PHONE,
        "gstin": row.shop_gstin if row else settings.SHOP_GSTIN,
        "currency": row.currency if row else settings.CURRENCY,
        "footer": row.invoice_footer if row else None,
    }


def sale_document(db, sale: Sale) -> dict:
    shop = _shop_profile(db)
    return {
        "shop": shop,
        "invoice_no": sale.invoice_no,
        "sale_date": sale.sale_date.strftime("%d %b %Y, %I:%M %p"),
        "customer": {
            "name": sale.customer.name if sale.customer else "Walk-in Customer",
            "phone": sale.customer.phone if sale.customer else "",
            "address": sale.customer.address if sale.customer else "",
        },
        "items": [
            {"name": i.product.name if i.product else f"Product #{i.product_id}",
             "qty": i.quantity, "unit": i.unit_price, "tax": i.tax_rate,
             "total": i.line_total}
            for i in sale.items
        ],
        "subtotal": sale.subtotal, "discount_pct": sale.discount_pct,
        "discount": sale.discount, "tax": sale.tax, "total": sale.total,
        "payments": [{"method": p.method, "amount": p.amount} for p in sale.payments],
        "notes": sale.notes,
    }


def render_invoice_pdf(doc: dict) -> BytesIO:
    cur = doc["shop"]["currency"]
    money_fmt = lambda v: f"{cur}{float(v):,.2f}"

    buf = BytesIO()
    styles = getSampleStyleSheet()
    title = ParagraphStyle("title", parent=styles["Title"], fontName=_FONT, fontSize=16)
    small = ParagraphStyle("small", parent=styles["Normal"], fontName=_FONT, fontSize=8)
    right = ParagraphStyle("right", parent=styles["Normal"], fontName=_FONT, fontSize=9, alignment=TA_RIGHT)
    cell = ParagraphStyle("cell", parent=styles["Normal"], fontName=_FONT, fontSize=9)

    doc_tpl = SimpleDocTemplate(buf, pagesize=A4, topMargin=15*mm, bottomMargin=15*mm,
                                leftMargin=15*mm, rightMargin=15*mm)

    story = []
    story.append(Paragraph(doc["shop"]["name"], title))
    story.append(Paragraph(doc["shop"]["address"], small))
    story.append(Paragraph(doc["shop"]["phone"], small))
    if doc["shop"]["gstin"]:
        story.append(Paragraph(f"GSTIN: {doc['shop']['gstin']}", small))
    story.append(Spacer(1, 4*mm))
    story.append(HRFlowable(width="100%", thickness=1, color=colors.black))
    story.append(Spacer(1, 4*mm))

    inv_style = ParagraphStyle("inv", parent=title, fontName=_FONT, fontSize=20)
    story.append(Table(
        [[Paragraph("INVOICE", inv_style),
          Paragraph(f"Invoice No: <b>{doc['invoice_no']}</b><br/>Date: {doc['sale_date']}", right)]],
        colWidths=[100*mm, 80*mm],
    ))
    story.append(Spacer(1, 4*mm))

    customer_lines = [f"<b>Bill To:</b> {doc['customer']['name']}"]
    if doc["customer"]["phone"]:
        customer_lines.append(f"Phone: {doc['customer']['phone']}")
    if doc["customer"]["address"]:
        customer_lines.append(doc["customer"]["address"])
    story.append(Paragraph("<br/>".join(customer_lines), cell))
    story.append(Spacer(1, 4*mm))

    rows = [["#", "Product", "Qty", "Unit Price", "Tax %", "Amount"]]
    for idx, it in enumerate(doc["items"], start=1):
        rows.append([str(idx), it["name"], f"{it['qty']:g}", money_fmt(it["unit"]),
                     f"{it['tax']:g}%", money_fmt(it["total"])])
    items_table = Table(rows, colWidths=[8*mm, 80*mm, 14*mm, 24*mm, 14*mm, 22*mm])
    items_table.setStyle(TableStyle([
        ("BACKGROUND", (0, 0), (-1, 0), colors.HexColor("#f0f0f0")),
        ("GRID", (0, 0), (-1, -1), 0.4, colors.grey),
        ("FONTNAME", (0, 0), (-1, -1), _FONT),
        ("FONTSIZE", (0, 0), (-1, -1), 8),
        ("ALIGN", (2, 1), (-1, -1), "RIGHT"),
    ]))
    story.append(items_table)
    story.append(Spacer(1, 4*mm))

    totals = Table(
        [["Subtotal", money_fmt(doc["subtotal"])],
         ["Discount", money_fmt(doc["discount"])],
         ["Tax", money_fmt(doc["tax"])],
         ["<b>Total</b>", f"<b>{money_fmt(doc['total'])}</b>"]],
        colWidths=[50*mm, 40*mm],
    )
    totals.setStyle(TableStyle([
        ("FONTNAME", (0, 0), (-1, -1), _FONT),
        ("FONTSIZE", (0, 0), (-1, -1), 9),
        ("ALIGN", (1, 0), (1, -1), "RIGHT"),
        ("LINEABOVE", (3, 0), (3, -1), 1, colors.black),
    ]))
    story.append(totals)
    story.append(Spacer(1, 4*mm))

    pay_lines = ", ".join(f"{p['method']} {money_fmt(p['amount'])}" for p in doc["payments"]) or "Credit"
    story.append(Paragraph(f"<b>Payment:</b> {pay_lines}", cell))
    if doc["notes"]:
        story.append(Paragraph(f"<b>Notes:</b> {doc['notes']}", cell))
    if doc["shop"]["footer"]:
        story.append(Spacer(1, 8*mm))
        story.append(Paragraph(doc["shop"]["footer"], small))

    doc_tpl.build(story)
    buf.seek(0)
    return buf


def render_thermal_receipt(doc: dict) -> BytesIO:
    """80 mm receipt, canvas-based for exact width control."""
    cur = doc["shop"]["currency"]
    money_fmt = lambda v: f"{cur}{float(v):,.2f}"
    W = 80 * mm

    n_lines = 8 + len(doc["items"]) * 2 + 8
    buf = BytesIO()
    c = pdfcanvas.Canvas(buf, pagesize=(W, n_lines * 4 * mm))
    y = n_lines * 4 * mm - 8 * mm

    def line(text: str, bold: bool = False, size: int = 8, center: bool = False, dy: int = 14):
        nonlocal y
        c.setFont(_FONT_BOLD if bold else _FONT, size)
        if center:
            c.drawCentredString(W / 2, y, text)
        else:
            c.drawString(4 * mm, y, text)
        y -= dy

    line(doc["shop"]["name"], bold=True, size=11, center=True)
    line(doc["shop"]["phone"], center=True)
    line("=" * 42, center=True)
    line(f"INV: {doc['invoice_no']}")
    line(doc["sale_date"])
    line(f"Customer: {doc['customer']['name']}")
    line("-" * 42)
    for it in doc["items"]:
        line(it["name"])
        line(f"  {it['qty']:g} x {money_fmt(it['unit'])}  {money_fmt(it['total'])}")
    line("-" * 42)
    line(f"Subtotal  {money_fmt(doc['subtotal'])}", center=True)
    line(f"Discount  {money_fmt(doc['discount'])}", center=True)
    line(f"Tax       {money_fmt(doc['tax'])}", center=True)
    line(f"TOTAL     {money_fmt(doc['total'])}", bold=True, size=10, center=True)
    line("")
    pay_lines = ", ".join(f"{p['method']} {money_fmt(p['amount'])}" for p in doc["payments"]) or "Credit"
    line(pay_lines, center=True)
    line("=" * 42, center=True)
    line("Thank you for shopping with us!", center=True)
    c.showPage()
    c.save()
    buf.seek(0)
    return buf
```

---

## backend/app/api/__init__.py

```python
```

## backend/app/api/deps.py

```python
from fastapi import Depends
from fastapi.security import HTTPAuthorizationCredentials, HTTPBearer
from sqlalchemy import select
from sqlalchemy.orm import Session

from app.core.exceptions import AuthenticationError, PermissionDeniedError
from app.core.security import decode_access_token
from app.database.database import get_db
from app.models import User, UserRole

bearer = HTTPBearer(auto_error=False)


def get_current_user(
    credentials: HTTPAuthorizationCredentials | None = Depends(bearer),
    db: Session = Depends(get_db),
) -> User:
    if credentials is None:
        raise AuthenticationError("Not authenticated")
    try:
        payload = decode_access_token(credentials.credentials)
    except Exception:
        raise AuthenticationError("Invalid or expired token")
    user = db.scalar(select(User).where(User.username == payload.get("sub")))
    if user is None or not user.is_active:
        raise AuthenticationError("User not found or deactivated")
    return user


def require_roles(*roles: UserRole):
    allowed = set(roles)

    def checker(user: User = Depends(get_current_user)) -> User:
        if user.role not in allowed:
            raise PermissionDeniedError(
                f"Requires one of: {', '.join(r.value for r in allowed)}"
            )
        return user

    return checker
```

## backend/app/api/routes/__init__.py

```python
```

## backend/app/api/routes/health.py

```python
from pathlib import Path

from fastapi import APIRouter

router = APIRouter(prefix="/api/health", tags=["health"])

VERSION = Path(__file__).resolve().parents[3] / "VERSION"


@router.get("")
def health() -> dict:
    version = VERSION.read_text().strip() if VERSION.exists() else "dev"
    return {"status": "ok", "app": "Local Retail Manager", "version": version}
```

## backend/app/api/routes/auth.py

```python
from fastapi import APIRouter, Depends
from sqlalchemy.orm import Session

from app.api.deps import get_current_user
from app.database.database import get_db
from app.models import User
from app.schemas.auth import LoginIn, TokenOut
from app.schemas.user import UserRead
from app.services import auth_service

router = APIRouter(prefix="/api/auth", tags=["auth"])


@router.post("/login", response_model=TokenOut)
def login(body: LoginIn, db: Session = Depends(get_db)) -> dict:
    user, token = auth_service.authenticate(db, body.username, body.password)
    return {"access_token": token, "token_type": "bearer", "user": UserRead.model_validate(user)}


@router.get("/me", response_model=UserRead)
def me(user: User = Depends(get_current_user)) -> User:
    return user
```

## backend/app/api/routes/users.py

```python
from fastapi import APIRouter, Depends, status
from sqlalchemy import select
from sqlalchemy.orm import Session

from app.api.deps import require_roles
from app.core.exceptions import ConflictError, NotFoundError
from app.core.security import hash_password
from app.database.database import get_db
from app.models import User, UserRole
from app.schemas.user import PasswordIn, UserCreate, UserRead, UserUpdate

router = APIRouter(
    prefix="/api/users", tags=["users"],
    dependencies=[Depends(require_roles(UserRole.OWNER))],
)


@router.get("", response_model=list[UserRead])
def list_users(db: Session = Depends(get_db)) -> list[User]:
    return list(db.scalars(select(User).order_by(User.username)))


@router.post("", response_model=UserRead, status_code=status.HTTP_201_CREATED)
def create_user(body: UserCreate, db: Session = Depends(get_db)) -> User:
    if db.scalar(select(User).where(User.username == body.username.strip())):
        raise ConflictError("Username already exists")
    user = User(username=body.username.strip(), full_name=body.full_name.strip(),
                password_hash=hash_password(body.password), role=body.role)
    db.add(user)
    db.commit()
    db.refresh(user)
    return user


@router.patch("/{user_id}", response_model=UserRead)
def update_user(user_id: int, body: UserUpdate, db: Session = Depends(get_db)) -> User:
    user = db.get(User, user_id)
    if user is None:
        raise NotFoundError("User not found")
    for field, value in body.model_dump(exclude_unset=True).items():
        if value is not None:
            setattr(user, field, value)
    db.commit()
    db.refresh(user)
    return user


@router.post("/{user_id}/password")
def reset_password(user_id: int, body: PasswordIn, db: Session = Depends(get_db)) -> dict:
    user = db.get(User, user_id)
    if user is None:
        raise NotFoundError("User not found")
    user.password_hash = hash_password(body.password)
    db.commit()
    return {"ok": True}
```

## backend/app/api/routes/categories.py

```python
from fastapi import APIRouter, Depends, status
from sqlalchemy.orm import Session

from app.api.deps import get_current_user, require_roles
from app.database.database import get_db
from app.models import UserRole
from app.schemas.category import CategoryCreate, CategoryRead, CategoryUpdate
from app.services import category_service

router = APIRouter(prefix="/api/categories", tags=["categories"])


@router.get("", response_model=list[CategoryRead])
def list_categories(db: Session = Depends(get_db)) -> list:
    return category_service.list_categories(db)


@router.post("", response_model=CategoryRead, status_code=status.HTTP_201_CREATED,
             dependencies=[Depends(require_roles(UserRole.OWNER, UserRole.MANAGER))])
def create_category(body: CategoryCreate, db: Session = Depends(get_db)) -> CategoryRead:
    return category_service.create_category(db, body)


@router.patch("/{category_id}", response_model=CategoryRead,
              dependencies=[Depends(require_roles(UserRole.OWNER, UserRole.MANAGER))])
def update_category(category_id: int, body: CategoryUpdate, db: Session = Depends(get_db)) -> CategoryRead:
    return category_service.update_category(db, category_id, body)


@router.delete("/{category_id}", status_code=status.HTTP_204_NO_CONTENT,
               dependencies=[Depends(require_roles(UserRole.OWNER, UserRole.MANAGER))])
def delete_category(category_id: int, db: Session = Depends(get_db)) -> None:
    category_service.delete_category(db, category_id)
```

> Note: `get_current_user` is applied implicitly for the guarded routes via `require_roles`; the read-only list stays open to any authenticated caller (billing needs it).

## backend/app/api/routes/products.py

```python
from fastapi import APIRouter, Depends, Query, status
from sqlalchemy.orm import Session

from app.api.deps import require_roles
from app.core.exceptions import NotFoundError
from app.database.database import get_db
from app.models import UserRole
from app.schemas.product import ProductCreate, ProductPage, ProductRead, ProductUpdate
from app.services import product_service

router = APIRouter(prefix="/api/products", tags=["products"])

manager_only = [Depends(require_roles(UserRole.OWNER, UserRole.MANAGER))]


def _to_read(product) -> ProductRead:
    return ProductRead(
        **product.__dict__,
        category_name=product.category.name if product.category else None,
    )


@router.post("", response_model=ProductRead, status_code=status.HTTP_201_CREATED,
             dependencies=manager_only)
def create_product(body: ProductCreate, db: Session = Depends(get_db)) -> ProductRead:
    return _to_read(product_service.create_product(db, body))


@router.get("", response_model=ProductPage)
def list_products(
    db: Session = Depends(get_db),
    search: str | None = Query(default=None),
    category_id: int | None = Query(default=None),
    include_inactive: bool = Query(default=False),
    page: int = Query(default=1, ge=1),
    size: int = Query(default=20, ge=1, le=100),
) -> dict:
    items, total = product_service.list_products(db, search, category_id, include_inactive, page, size)
    return {"items": [_to_read(p) for p in items], "total": total, "page": page, "size": size}


@router.get("/by-barcode/{barcode}", response_model=ProductRead)
def by_barcode(barcode: str, db: Session = Depends(get_db)) -> ProductRead:
    product = product_service.get_by_barcode(db, barcode)
    if product is None:
        raise NotFoundError("No product with that barcode")
    return _to_read(product)


@router.get("/{product_id}", response_model=ProductRead)
def get_product(product_id: int, db: Session = Depends(get_db)) -> ProductRead:
    return _to_read(product_service.get_product(db, product_id))


@router.patch("/{product_id}", response_model=ProductRead, dependencies=manager_only)
def update_product(product_id: int, body: ProductUpdate, db: Session = Depends(get_db)) -> ProductRead:
    return _to_read(product_service.update_product(db, product_id, body))


@router.delete("/{product_id}", status_code=status.HTTP_204_NO_CONTENT, dependencies=manager_only)
def deactivate_product(product_id: int, db: Session = Depends(get_db)) -> None:
    product_service.deactivate_product(db, product_id)
```

## backend/app/api/routes/customers.py

```python
from fastapi import APIRouter, Depends, Query, status
from sqlalchemy.orm import Session

from app.api.deps import get_current_user
from app.database.database import get_db
from app.models import Payment
from app.schemas.customer import CustomerCreate, CustomerRead, CustomerUpdate
from app.schemas.payment import CustomerPaymentIn, PaymentRead
from app.services import customer_service

router = APIRouter(prefix="/api/customers", tags=["customers"])


@router.get("/outstanding")
def outstanding(db: Session = Depends(get_db)) -> list[dict]:
    return customer_service.outstanding_customers(db)


@router.get("", response_model=list[CustomerRead])
def list_customers(db: Session = Depends(get_db),
                   search: str | None = Query(default=None),
                   page: int = Query(1, ge=1),
                   size: int = Query(50, ge=1, le=200)):
    items, _ = customer_service.list_customers(db, search, page, size)
    return items


@router.post("", response_model=CustomerRead, status_code=status.HTTP_201_CREATED)
def create_customer(body: CustomerCreate, db: Session = Depends(get_db)) -> Customer:
    return customer_service.create_customer(db, body)


@router.get("/{customer_id}", response_model=CustomerRead)
def get_customer(customer_id: int, db: Session = Depends(get_db)) -> Customer:
    return customer_service.get_customer(db, customer_id)


@router.patch("/{customer_id}", response_model=CustomerRead)
def update_customer(customer_id: int, body: CustomerUpdate, db: Session = Depends(get_db)) -> Customer:
    return customer_service.update_customer(db, customer_id, body)


@router.get("/{customer_id}/balance")
def balance(customer_id: int, db: Session = Depends(get_db)) -> dict:
    return {"customer_id": customer_id, "balance": float(customer_service.customer_balance(db, customer_id))}


@router.get("/{customer_id}/ledger")
def ledger(customer_id: int, db: Session = Depends(get_db)) -> dict:
    return {"entries": customer_service.customer_ledger(db, customer_id)}


@router.post("/{customer_id}/payments", response_model=PaymentRead, status_code=status.HTTP_201_CREATED)
def add_payment(customer_id: int, body: CustomerPaymentIn,
                db: Session = Depends(get_db), user=Depends(get_current_user)) -> Payment:
    payment = customer_service.record_customer_payment(
        db, customer_id, body.amount, body.method, body.reference, user_id=user.id,
    )
    return PaymentRead.model_validate(payment)
```

## backend/app/api/routes/suppliers.py

```python
from fastapi import APIRouter, Depends, Query, status
from sqlalchemy.orm import Session

from app.api.deps import get_current_user, require_roles
from app.database.database import get_db
from app.models import Payment, UserRole
from app.schemas.payment import PaymentRead, SupplierPaymentIn
from app.schemas.supplier import SupplierCreate, SupplierRead, SupplierUpdate
from app.services import supplier_service

router = APIRouter(
    prefix="/api/suppliers", tags=["suppliers"],
    dependencies=[Depends(require_roles(UserRole.OWNER, UserRole.MANAGER))],
)


@router.get("/outstanding")
def outstanding(db: Session = Depends(get_db)) -> list[dict]:
    return supplier_service.outstanding_suppliers(db)


@router.get("", response_model=list[SupplierRead])
def list_suppliers(db: Session = Depends(get_db),
                   search: str | None = Query(default=None),
                   page: int = Query(1, ge=1),
                   size: int = Query(50, ge=1, le=200)):
    items, _ = supplier_service.list_suppliers(db, search, page, size)
    return items


@router.post("", response_model=SupplierRead, status_code=status.HTTP_201_CREATED)
def create_supplier(body: SupplierCreate, db: Session = Depends(get_db)) -> Supplier:
    return supplier_service.create_supplier(db, body)


@router.get("/{supplier_id}", response_model=SupplierRead)
def get_supplier(supplier_id: int, db: Session = Depends(get_db)) -> Supplier:
    return supplier_service.get_supplier(db, supplier_id)


@router.patch("/{supplier_id}", response_model=SupplierRead)
def update_supplier(supplier_id: int, body: SupplierUpdate, db: Session = Depends(get_db)) -> Supplier:
    return supplier_service.update_supplier(db, supplier_id, body)


@router.get("/{supplier_id}/balance")
def balance(supplier_id: int, db: Session = Depends(get_db)) -> dict:
    return {"supplier_id": supplier_id, "balance": float(supplier_service.supplier_balance(db, supplier_id))}


@router.get("/{supplier_id}/ledger")
def ledger(supplier_id: int, db: Session = Depends(get_db)) -> dict:
    return {"entries": supplier_service.supplier_ledger(db, supplier_id)}


@router.post("/{supplier_id}/payments", response_model=PaymentRead, status_code=status.HTTP_201_CREATED)
def add_payment(supplier_id: int, body: SupplierPaymentIn,
                db: Session = Depends(get_db), user=Depends(get_current_user)) -> Payment:
    payment = supplier_service.record_supplier_payment(
        db, supplier_id, body.amount, body.method, body.reference, user_id=user.id,
    )
    return PaymentRead.model_validate(payment)
```

## backend/app/api/routes/sales.py

```python
from datetime import datetime

from fastapi import APIRouter, Depends, Query, status
from fastapi.responses import FileResponse, Response
from sqlalchemy.orm import Session

from app.api.deps import get_current_user
from app.database.database import get_db
from app.schemas.sale import SaleCreate, SalePage, SaleRead, SaleReturnIn
from app.services import invoice_service, sale_service

router = APIRouter(prefix="/api/sales", tags=["sales"])


def _to_read(sale) -> SaleRead:
    return SaleRead(
        id=sale.id, invoice_no=sale.invoice_no,
        customer_id=sale.customer_id,
        customer_name=sale.customer.name if sale.customer else None,
        subtotal=sale.subtotal, discount_pct=sale.discount_pct, discount=sale.discount,
        tax=sale.tax, total=sale.total, status=sale.status, sale_date=sale.sale_date,
        notes=sale.notes,
        created_by=sale.created_by.full_name if sale.created_by else None,
        items=[
            {"id": i.id, "product_id": i.product_id,
             "product_name": i.product.name if i.product else None,
             "quantity": i.quantity, "unit_price": i.unit_price,
             "tax_rate": i.tax_rate, "line_total": i.line_total,
             "returned_qty": i.returned_qty}
            for i in sale.items
        ],
        payments=[
            {"id": p.id, "amount": p.amount, "method": p.method,
             "reference": p.reference, "paid_at": p.paid_at}
            for p in sale.payments
        ],
    )


@router.post("", response_model=SaleRead, status_code=status.HTTP_201_CREATED)
def create_sale(body: SaleCreate, db: Session = Depends(get_db),
                user=Depends(get_current_user)) -> SaleRead:
    try:
        sale = sale_service.create_sale(db, body, user_id=user.id)
    except Exception:
        db.rollback()
        raise
    return _to_read(sale)


@router.get("", response_model=SalePage)
def list_sales(
    db: Session = Depends(get_db),
    from_date: datetime | None = Query(default=None),
    to_date: datetime | None = Query(default=None),
    customer_id: int | None = Query(default=None),
    search: str | None = Query(default=None),
    page: int = Query(1, ge=1),
    size: int = Query(20, ge=1, le=100),
) -> dict:
    items, total = sale_service.list_sales(db, from_date, to_date, customer_id, search, page, size)
    return {"items": [_to_read(s) for s in items], "total": total, "page": page, "size": size}


@router.get("/{sale_id}", response_model=SaleRead)
def get_sale(sale_id: int, db: Session = Depends(get_db)) -> SaleRead:
    return _to_read(sale_service.get_sale(db, sale_id))


@router.get("/{sale_id}/invoice")
def download_invoice(sale_id: int, db: Session = Depends(get_db)) -> FileResponse:
    sale = sale_service.get_sale(db, sale_id)
    path = invoice_service.generate_invoice(db, sale)
    return FileResponse(path, media_type="application/pdf", filename=f"{sale.invoice_no}.pdf")


@router.get("/{sale_id}/receipt")
def download_receipt(sale_id: int, db: Session = Depends(get_db)) -> Response:
    sale = sale_service.get_sale(db, sale_id)
    return Response(content=invoice_service.generate_receipt(db, sale), media_type="application/pdf")


@router.post("/{sale_id}/return", response_model=SaleRead)
def return_sale(sale_id: int, body: SaleReturnIn, db: Session = Depends(get_db),
                user=Depends(get_current_user)) -> SaleRead:
    sale = sale_service.return_sale_items(db, sale_id, body, user_id=user.id)
    return _to_read(sale)
```

## backend/app/api/routes/purchases.py

```python
from datetime import datetime

from fastapi import APIRouter, Depends, Query, status
from sqlalchemy.orm import Session

from app.api.deps import require_roles
from app.database.database import get_db
from app.models import UserRole
from app.schemas.payment import PaymentRead
from app.schemas.purchase import (PurchaseCreate, PurchasePage, PurchasePayIn,
                                  PurchaseRead)
from app.services import purchase_service

router = APIRouter(
    prefix="/api/purchases", tags=["purchases"],
    dependencies=[Depends(require_roles(UserRole.OWNER, UserRole.MANAGER))],
)


def _to_read(p) -> PurchaseRead:
    return PurchaseRead(
        id=p.id, purchase_no=p.purchase_no,
        supplier_id=p.supplier_id,
        supplier_name=p.supplier.name if p.supplier else None,
        purchase_date=p.purchase_date, subtotal=p.subtotal,
        discount_pct=p.discount_pct, discount=p.discount, tax=p.tax, total=p.total,
        paid_amount=p.paid_amount, payment_method=p.payment_method,
        status=p.status, notes=p.notes,
        created_by=p.created_by.full_name if p.created_by else None,
        items=[
            {"id": i.id, "product_id": i.product_id,
             "product_name": i.product.name if i.product else None,
             "quantity": i.quantity, "unit_cost": i.unit_cost,
             "tax_rate": i.tax_rate, "line_total": i.line_total}
            for i in p.items
        ],
    )


@router.post("", response_model=PurchaseRead, status_code=status.HTTP_201_CREATED)
def create_purchase(body: PurchaseCreate, db: Session = Depends(get_db)) -> PurchaseRead:
    return _to_read(purchase_service.create_purchase(db, body))


@router.get("", response_model=PurchasePage)
def list_purchases(
    db: Session = Depends(get_db),
    from_date: datetime | None = Query(default=None),
    to_date: datetime | None = Query(default=None),
    supplier_id: int | None = Query(default=None),
    search: str | None = Query(default=None),
    page: int = Query(1, ge=1),
    size: int = Query(20, ge=1, le=100),
) -> dict:
    items, total = purchase_service.list_purchases(db, from_date, to_date, supplier_id, search, page, size)
    return {"items": [_to_read(p) for p in items], "total": total, "page": page, "size": size}


@router.get("/{purchase_id}", response_model=PurchaseRead)
def get_purchase(purchase_id: int, db: Session = Depends(get_db)) -> PurchaseRead:
    return _to_read(purchase_service.get_purchase(db, purchase_id))


@router.post("/{purchase_id}/pay", response_model=PaymentRead, status_code=status.HTTP_201_CREATED)
def pay_purchase(purchase_id: int, body: PurchasePayIn, db: Session = Depends(get_db)) -> PaymentRead:
    payment = purchase_service.record_purchase_payment(db, purchase_id, body.amount, body.method)
    return PaymentRead.model_validate(payment)
```

## backend/app/api/routes/expenses.py

```python
from datetime import datetime

from fastapi import APIRouter, Depends, Query, status
from sqlalchemy.orm import Session

from app.api.deps import get_current_user, require_roles
from app.database.database import get_db
from app.models import UserRole
from app.schemas.expense import ExpenseCreate, ExpenseRead, ExpenseUpdate
from app.services import expense_service

router = APIRouter(
    prefix="/api/expenses", tags=["expenses"],
    dependencies=[Depends(require_roles(UserRole.OWNER, UserRole.MANAGER))],
)


def _to_read(e) -> ExpenseRead:
    return ExpenseRead(
        id=e.id, expense_date=e.expense_date, category=e.category, amount=e.amount,
        description=e.description,
        created_by=e.created_by.full_name if e.created_by else None,
    )


@router.get("", response_model=list[ExpenseRead])
def list_expenses(db: Session = Depends(get_db),
                  from_date: datetime | None = Query(default=None),
                  to_date: datetime | None = Query(default=None),
                  category: str | None = Query(default=None),
                  page: int = Query(1, ge=1),
                  size: int = Query(50, ge=1, le=200)):
    items, _ = expense_service.list_expenses(db, from_date, to_date, category, page, size)
    return [_to_read(e) for e in items]


@router.post("", response_model=ExpenseRead, status_code=status.HTTP_201_CREATED)
def create_expense(body: ExpenseCreate, db: Session = Depends(get_db),
                   user=Depends(get_current_user)) -> ExpenseRead:
    return _to_read(expense_service.create_expense(db, body, user_id=user.id))


@router.patch("/{expense_id}", response_model=ExpenseRead)
def update_expense(expense_id: int, body: ExpenseUpdate, db: Session = Depends(get_db)) -> ExpenseRead:
    return _to_read(expense_service.update_expense(db, expense_id, body))


@router.delete("/{expense_id}", status_code=status.HTTP_204_NO_CONTENT)
def delete_expense(expense_id: int, db: Session = Depends(get_db)) -> None:
    expense_service.delete_expense(db, expense_id)


@router.get("/categories")
def categories(db: Session = Depends(get_db)) -> list[str]:
    return expense_service.expense_categories(db)


@router.get("/summary")
def summary(db: Session = Depends(get_db),
            from_date: datetime = Query(...), to_date: datetime = Query(...)) -> dict:
    return {"total": float(expense_service.expense_total(db, from_date, to_date))}
```

## backend/app/api/routes/inventory.py

```python
from fastapi import APIRouter, Depends, Query, status
from sqlalchemy.orm import Session

from app.api.deps import require_roles
from app.database.database import get_db
from app.models import MovementType, UserRole
from app.schemas.inventory import AdjustmentIn, DamageIn, MovementPage, MovementRead
from app.services import inventory_service

router = APIRouter(prefix="/api/inventory", tags=["inventory"])

manager_only = [Depends(require_roles(UserRole.OWNER, UserRole.MANAGER))]


def _to_read(m) -> MovementRead:
    return MovementRead(
        id=m.id, product_id=m.product_id,
        product_name=m.product.name if m.product else None,
        movement_type=m.movement_type, quantity=m.quantity, unit_cost=m.unit_cost,
        ref_type=m.ref_type, ref_id=m.ref_id, note=m.note,
        created_at=m.created_at,
        created_by=m.created_by.full_name if m.created_by else None,
    )


@router.get("/movements", response_model=MovementPage)
def movements(db: Session = Depends(get_db),
              product_id: int | None = None,
              movement_type: MovementType | None = None,
              page: int = Query(1, ge=1),
              size: int = Query(50, ge=1, le=200)) -> dict:
    items, total = inventory_service.list_movements(db, product_id, movement_type, page, size)
    return {"items": [_to_read(m) for m in items], "total": total, "page": page, "size": size}


@router.get("/low-stock")
def low_stock(db: Session = Depends(get_db)) -> list[dict]:
    return [
        {"id": p.id, "name": p.name, "current_stock": p.current_stock, "min_stock": p.min_stock}
        for p in inventory_service.low_stock_products(db)
    ]


@router.get("/stock-value")
def stock_value(db: Session = Depends(get_db)) -> dict:
    return {"value": float(inventory_service.stock_value(db))}


@router.post("/adjust", status_code=status.HTTP_201_CREATED, dependencies=manager_only)
def adjust(body: AdjustmentIn, db: Session = Depends(get_db)) -> dict:
    m = inventory_service.adjust_stock(db, product_id=body.product_id,
                                       new_stock=body.new_stock, reason=body.reason)
    db.commit()
    return _to_read(m)


@router.post("/damage", status_code=status.HTTP_201_CREATED, dependencies=manager_only)
def damage(body: DamageIn, db: Session = Depends(get_db)) -> dict:
    m = inventory_service.record_damage(db, product_id=body.product_id,
                                        quantity=body.quantity, note=body.note)
    db.commit()
    return _to_read(m)


@router.post("/reconcile", dependencies=manager_only)
def reconcile(db: Session = Depends(get_db)) -> dict:
    return {"corrected": inventory_service.reconcile_stock(db)}
```

> ⚠️ **Route-order rule:** `/{product_id}`-style paths must come *after* fixed prefixes (`by-barcode`, `low-stock`, `stock-value`, `movements`). Check every router in this file — the order above is deliberate.

## backend/app/api/routes/dashboard.py

```python
from fastapi import APIRouter, Depends
from sqlalchemy.orm import Session

from app.api.deps import require_roles
from app.database.database import get_db
from app.models import UserRole
from app.services import dashboard_service

router = APIRouter(
    prefix="/api/dashboard", tags=["dashboard"],
    dependencies=[Depends(require_roles(UserRole.OWNER, UserRole.MANAGER))],
)


@router.get("/summary")
def summary(db: Session = Depends(get_db)) -> dict:
    return dashboard_service.summary(db)
```

## backend/app/api/routes/reports.py

```python
from datetime import datetime

from fastapi import APIRouter, Depends, Query
from sqlalchemy.orm import Session

from app.api.deps import require_roles
from app.database.database import get_db
from app.models import UserRole
from app.services import inventory_service, report_service

router = APIRouter(
    prefix="/api/reports", tags=["reports"],
    dependencies=[Depends(require_roles(UserRole.OWNER, UserRole.MANAGER))],
)


@router.get("/profit")
def profit(db: Session = Depends(get_db),
           from_date: datetime = Query(...), to_date: datetime = Query(...)) -> dict:
    return report_service.profit_summary(db, from_date, to_date)


@router.get("/sales-daily")
def sales_daily(db: Session = Depends(get_db),
                from_date: datetime = Query(...), to_date: datetime = Query(...)) -> list[dict]:
    return report_service.sales_daily(db, from_date, to_date)


@router.get("/sales-monthly")
def sales_monthly(db: Session = Depends(get_db),
                  from_date: datetime = Query(...), to_date: datetime = Query(...)) -> list[dict]:
    return report_service.sales_monthly(db, from_date, to_date)


@router.get("/product-sales")
def product_sales(db: Session = Depends(get_db),
                  from_date: datetime = Query(...), to_date: datetime = Query(...)) -> list[dict]:
    return report_service.product_sales(db, from_date, to_date)


@router.get("/purchases")
def purchases(db: Session = Depends(get_db),
              from_date: datetime = Query(...), to_date: datetime = Query(...)) -> list[dict]:
    return report_service.purchase_report(db, from_date, to_date)


@router.get("/expenses")
def expenses(db: Session = Depends(get_db),
             from_date: datetime = Query(...), to_date: datetime = Query(...)) -> dict:
    return report_service.expense_report(db, from_date, to_date)


@router.get("/inventory")
def inventory(db: Session = Depends(get_db)) -> dict:
    return report_service.inventory_report(db)


@router.get("/customers")
def customers(db: Session = Depends(get_db)) -> list[dict]:
    return report_service.customer_report(db)


@router.get("/suppliers")
def suppliers(db: Session = Depends(get_db)) -> list[dict]:
    return report_service.supplier_report(db)


@router.get("/dead-stock")
def dead_stock(db: Session = Depends(get_db), days: int = Query(60, ge=1)) -> list[dict]:
    return [
        {"id": p.id, "name": p.name, "current_stock": p.current_stock}
        for p in inventory_service.dead_stock(db, days)
    ]
```

## backend/app/api/routes/settings.py

```python
from fastapi import APIRouter, Depends
from sqlalchemy.orm import Session

from app.api.deps import require_roles
from app.database.database import get_db
from app.models import UserRole
from app.schemas.settings import ShopSettingsRead, ShopSettingsUpdate
from app.services import settings_service

router = APIRouter(
    prefix="/api/settings", tags=["settings"],
    dependencies=[Depends(require_roles(UserRole.OWNER))],
)


def _to_read(row) -> ShopSettingsRead:
    return ShopSettingsRead(
        shop_name=row.shop_name, shop_address=row.shop_address,
        shop_phone=row.shop_phone, shop_gstin=row.shop_gstin,
        currency=row.currency, default_tax_rate=row.default_tax_rate,
        invoice_footer=row.invoice_footer,
    )


@router.get("", response_model=ShopSettingsRead)
def get_settings(db: Session = Depends(get_db)) -> ShopSettingsRead:
    return _to_read(settings_service.get_settings(db))


@router.put("", response_model=ShopSettingsRead)
def update_settings(body: ShopSettingsUpdate, db: Session = Depends(get_db)) -> ShopSettingsRead:
    return _to_read(settings_service.update_settings(db, body))
```

## backend/app/api/routes/backups.py

```python
from fastapi import APIRouter, Depends, status
from pydantic import BaseModel
from sqlalchemy.orm import Session

from app.api.deps import require_roles
from app.database.database import get_db
from app.models import UserRole
from app.services import backup_service

router = APIRouter(
    prefix="/api/backups", tags=["backups"],
    dependencies=[Depends(require_roles(UserRole.OWNER))],
)


class RestoreIn(BaseModel):
    filename: str


@router.get("")
def list_backups() -> list[dict]:
    return backup_service.list_backups()


@router.post("", status_code=status.HTTP_201_CREATED)
def create_backup(db: Session = Depends(get_db)) -> dict:
    return backup_service.create_backup(db)


@router.post("/restore")
def restore(body: RestoreIn, db: Session = Depends(get_db)) -> dict:
    backup_service.restore_backup(db, body.filename)
    return {"ok": True, "message": "Restored. Restart the app."}
```

---

## backend/app/main.py

```python
import logging

from contextlib import asynccontextmanager

from fastapi import FastAPI, Request
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import JSONResponse
from sqlalchemy.exc import IntegrityError

from app.api.routes import (auth, backups, categories, customers, dashboard,
                            expenses, health, inventory, products, purchases,
                            reports, sales, settings, suppliers, users)
from app.core.config import settings
from app.core.exceptions import AppError
from app.core.logging import setup_logging
from app.database.database import SessionLocal
from app.database.seed import seed_initial_data
from app.services import backup_service

setup_logging()
logger = logging.getLogger(__name__)


def run_migrations() -> None:
    from alembic import command
    from alembic.config import Config as AlembicConfig
    from pathlib import Path

    import os

    backend_dir = Path(__file__).resolve().parents[2]
    cfg = AlembicConfig(str(backend_dir / "alembic.ini"))
    cfg.set_main_option("script_location", str(backend_dir / "alembic"))
    os.environ["LRM_DATA_DIR"] = str(settings.DATA_DIR)
    command.upgrade(cfg, "head")


@asynccontextmanager
async def lifespan(app: FastAPI):
    settings.ensure_dirs()
    if settings.ENV != "test":
        try:
            run_migrations()
        except Exception:
            logger.exception("Startup migrations failed — refusing to start")
            raise
    db = SessionLocal()
    try:
        seed_initial_data(db)
        backup_service.auto_backup_if_due(db)
    finally:
        db.close()
    logger.info("%s started (env=%s, db=%s)", settings.APP_NAME, settings.ENV, settings.database_url)
    yield
    logger.info("Shutting down %s", settings.APP_NAME)


def create_app() -> FastAPI:
    app = FastAPI(title=settings.APP_NAME, lifespan=lifespan)

    app.add_middleware(
        CORSMiddleware,
        allow_origins=settings.CORS_ORIGINS,
        allow_credentials=True,
        allow_methods=["*"],
        allow_headers=["*"],
    )

    @app.exception_handler(AppError)
    async def app_error_handler(request: Request, exc: AppError):
        return JSONResponse(
            status_code=exc.status_code,
            content={"detail": {"code": exc.code, "message": exc.message}},
        )

    @app.exception_handler(IntegrityError)
    async def integrity_error_handler(request: Request, exc: IntegrityError):
        logger.exception("IntegrityError")
        return JSONResponse(
            status_code=409,
            content={"detail": {"code": "conflict", "message": "That value is already in use."}},
        )

    @app.exception_handler(Exception)
    async def unhandled_error_handler(request: Request, exc: Exception):
        logger.exception("Unhandled error on %s %s", request.method, request.url.path)
        return JSONResponse(
            status_code=500,
            content={"detail": {"code": "internal_error", "message": "Something went wrong"}},
        )

    for r in (health.router, auth.router, users.router, categories.router,
              products.router, customers.router, suppliers.router, sales.router,
              purchases.router, expenses.router, inventory.router,
              dashboard.router, reports.router, settings.router, backups.router):
        app.include_router(r)

    return app


app = create_app()
```

---

## backend/tests/__init__.py

```python
```

## backend/tests/conftest.py

```python
import pytest
from fastapi.testclient import TestClient
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from sqlalchemy.pool import StaticPool

from app.api.deps import get_current_user, require_roles
from app.core.security import hash_password
from app.database.database import get_db
from app.main import app as fastapi_app
from app.models import Base, User, UserRole

TEST_PASSWORD = "testpass123"


@pytest.fixture()
def db_session():
    engine = create_engine(
        "sqlite://",
        connect_args={"check_same_thread": False},
        poolclass=StaticPool,
    )
    Base.metadata.create_all(engine)
    TestSession = sessionmaker(bind=engine, expire_on_commit=False)
    session = TestSession()

    # Seed users needed by auth tests
    for username, role in (("owner", UserRole.OWNER),
                           ("manager", UserRole.MANAGER),
                           ("cashier", UserRole.CASHIER)):
        session.add(User(username=username, full_name=username,
                         password_hash=hash_password(TEST_PASSWORD), role=role))
    session.commit()

    try:
        yield session
    finally:
        session.close()
        Base.metadata.drop_all(engine)
        engine.dispose()


@pytest.fixture()
def client(db_session):
    def override_get_db():
        yield db_session

    fastapi_app.dependency_overrides[get_db] = override_get_db
    with TestClient(fastapi_app) as c:
        yield c
    fastapi_app.dependency_overrides.clear()


def _auth_headers(client, username: str) -> dict:
    r = client.post("/api/auth/login", json={"username": username, "password": TEST_PASSWORD})
    assert r.status_code == 200, r.text
    return {"Authorization": f"Bearer {r.json()['access_token']}"}


@pytest.fixture()
def owner_headers(client):
    return _auth_headers(client, "owner")


@pytest.fixture()
def cashier_headers(client):
    return _auth_headers(client, "cashier")
```

## backend/tests/test_pricing.py

```python
from decimal import Decimal

from app.services.sale_service import _calculate


def test_no_discount_no_tax():
    lines = [{"quantity": Decimal("3"), "unit_price": Decimal("28"), "tax_rate": Decimal("0")}]
    r = _calculate(lines, Decimal("0"))
    assert r["total"] == Decimal("84.00")


def test_discount_then_tax_on_discounted_value():
    lines = [{"quantity": Decimal("10"), "unit_price": Decimal("100"), "tax_rate": Decimal("18")}]
    r = _calculate(lines, Decimal("10"))
    assert r["subtotal"] == Decimal("1000.00")
    assert r["discount"] == Decimal("100.00")
    assert r["tax"] == Decimal("162.00")
    assert r["total"] == Decimal("1062.00")


def test_half_up_rounding():
    lines = [{"quantity": Decimal("3"), "unit_price": Decimal("10"), "tax_rate": Decimal("5")}]
    r = _calculate(lines, Decimal("0"))
    assert r["tax"] == Decimal("1.50")
    assert r["total"] == Decimal("31.50")
```

## backend/tests/test_inventory.py

```python
from decimal import Decimal

import pytest

from app.models import MovementType, Sale
from app.schemas.product import ProductCreate
from app.schemas.sale import PaymentIn, SaleCreate, SaleItemIn
from app.services import inventory_service, product_service, sale_service


def make_product(db, **kw):
    defaults = dict(name="Tata Salt", purchase_price=22, selling_price=28, min_stock=10)
    defaults.update(kw)
    return product_service.create_product(db, ProductCreate(**defaults))


def test_adjust_sets_stock_and_writes_ledger(db_session):
    p = make_product(db_session)
    m = inventory_service.adjust_stock(db_session, product_id=p.id, new_stock=100, reason="opening")
    db_session.commit()
    db_session.refresh(p)
    assert p.current_stock == 100
    assert m.movement_type == MovementType.ADJUSTMENT
    assert m.quantity == 100


def test_negative_stock_rejected(db_session):
    p = make_product(db_session)
    inventory_service.adjust_stock(db_session, product_id=p.id, new_stock=5, reason="opening")
    db_session.commit()
    with pytest.raises(Exception):
        inventory_service.adjust_stock(db_session, product_id=p.id, new_stock=-1, reason="bad")
    db_session.rollback()


def test_sale_reduces_stock_and_creates_movement(db_session):
    p = make_product(db_session)
    inventory_service.adjust_stock(db_session, product_id=p.id, new_stock=100, reason="opening")
    db_session.commit()

    sale = sale_service.create_sale(db_session, SaleCreate(
        items=[SaleItemIn(product_id=p.id, quantity=3)],
        payments=[PaymentIn()],
    ), user_id=None)

    db_session.refresh(p)
    assert p.current_stock == 97
    assert sale.total == Decimal("84.00")
    moves = inventory_service.list_movements(db_session, product_id=p.id)[0]
    assert any(m.movement_type == MovementType.SALE and m.quantity == -3 for m in moves)


def test_insufficient_stock_rolls_back_everything(db_session):
    p = make_product(db_session)
    inventory_service.adjust_stock(db_session, product_id=p.id, new_stock=1, reason="opening")
    db_session.commit()

    with pytest.raises(Exception):
        sale_service.create_sale(db_session, SaleCreate(
            items=[SaleItemIn(product_id=p.id, quantity=5)],
        ), user_id=None)
    db_session.rollback()

    db_session.refresh(p)
    assert p.current_stock == 1
    assert db_session.query(Sale).count() == 0


def test_credit_sale_creates_no_payment_row(db_session):
    p = make_product(db_session)
    inventory_service.adjust_stock(db_session, product_id=p.id, new_stock=10, reason="opening")
    db_session.commit()

    sale = sale_service.create_sale(db_session, SaleCreate(
        items=[SaleItemIn(product_id=p.id, quantity=2)],
        payments=[],
    ), user_id=None)
    assert len(sale.payments) == 0
```

## backend/tests/test_api.py

```python
def test_health(client):
    r = client.get("/api/health")
    assert r.status_code == 200
    assert r.json()["status"] == "ok"


def test_login_and_401(client):
    r = client.post("/api/auth/login", json={"username": "owner", "password": "testpass123"})
    assert r.status_code == 200
    token = r.json()["access_token"]
    assert client.get("/api/products").status_code == 401
    assert client.get("/api/products", headers={"Authorization": f"Bearer {token}"}).status_code == 200


def test_product_conflict(client, owner_headers):
    body = {"name": "Salt", "barcode": "8901"}
    assert client.post("/api/products", json=body, headers=owner_headers).status_code == 201
    r = client.post("/api/products", json=body, headers=owner_headers)
    assert r.status_code == 409


def test_cashier_cannot_delete_products(client, owner_headers, cashier_headers):
    client.post("/api/products", json={"name": "Sugar", "barcode": "8902"},
                headers=owner_headers)
    r = client.delete("/api/products/1", headers=cashier_headers)
    assert r.status_code == 403


def test_sale_flow_via_api(client, owner_headers):
    client.post("/api/products", json={"name": "Salt", "barcode": "8903",
                                       "selling_price": 28}, headers=owner_headers)
    client.post("/api/inventory/adjust", json={"product_id": 1, "new_stock": 10,
                                               "reason": "opening"}, headers=owner_headers)
    r = client.post("/api/sales", json={"items": [{"product_id": 1, "quantity": 3}]},
                    headers=owner_headers)
    assert r.status_code == 201
    assert r.json()["total"] == 84.0
    assert r.json()["invoice_no"].startswith("INV-")

    product = client.get("/api/products/1", headers=owner_headers).json()
    assert product["current_stock"] == 7


def test_backup_create_and_list(client, owner_headers):
    assert client.post("/api/backups", headers=owner_headers).status_code == 201
    assert client.get("/api/backups", headers=owner_headers).status_code == 200
```

---

> *Continue to the frontend source code — part 3 of the code reference.*
# Complete Source Code Reference — frontend (part 3 of 4)

## frontend/package.json

```json
{
  "name": "local-retail-manager-frontend",
  "private": true,
  "version": "0.1.0",
  "type": "module",
  "scripts": {
    "dev": "vite",
    "build": "tsc -b && vite build",
    "preview": "vite preview",
    "typecheck": "tsc --noEmit",
    "test": "vitest run"
  },
  "dependencies": {
    "lucide-react": "^1.30.0",
    "react": "^19.2.0",
    "react-dom": "^19.2.0",
    "react-router-dom": "^7.18.0",
    "zustand": "^5.0.0"
  },
  "devDependencies": {
    "@tailwindcss/vite": "^4.3.0",
    "@testing-library/jest-dom": "^6.6.0",
    "@testing-library/react": "^16.3.0",
    "@testing-library/user-event": "^14.6.0",
    "@types/react": "^19.2.0",
    "@types/react-dom": "^19.2.0",
    "@vitejs/plugin-react": "^6.0.0",
    "jsdom": "^26.0.0",
    "tailwindcss": "^4.3.0",
    "typescript": "~7.0.0",
    "vite": "^8.2.0",
    "vitest": "^4.1.0"
  }
}
```

> If TypeScript 7.x causes tooling friction with any library, pin `"typescript": "~5.9"` — the code is compatible with both.

## frontend/vite.config.ts

```ts
/// <reference types="vitest/config" />
import tailwindcss from "@tailwindcss/vite";
import react from "@vitejs/plugin-react";
import { defineConfig } from "vite";

export default defineConfig({
  plugins: [react(), tailwindcss()],
  server: { port: 5173 },
  test: {
    environment: "jsdom",
    globals: true,
    setupFiles: "./src/test/setup.ts",
  },
});
```

## frontend/tsconfig.json

```json
{
  "compilerOptions": {
    "target": "ES2022",
    "useDefineForClassFields": true,
    "lib": ["ES2022", "DOM", "DOM.Iterable"],
    "module": "ESNext",
    "skipLibCheck": true,
    "moduleResolution": "bundler",
    "allowImportingTsExtensions": true,
    "isolatedModules": true,
    "moduleDetection": "force",
    "noEmit": true,
    "jsx": "react-jsx",
    "strict": true,
    "noUnusedLocals": true,
    "noUnusedParameters": true,
    "noFallthroughCasesInSwitch": true
  },
  "include": ["src"]
}
```

## frontend/index.html

```html
<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Local Retail Manager</title>
  </head>
  <body>
    <div id="root"></div>
    <script type="module" src="/src/main.tsx"></script>
  </body>
</html>
```

## frontend/src/main.tsx

```tsx
import { StrictMode } from "react";
import { createRoot } from "react-dom/client";
import App from "./App";
import "./index.css";

createRoot(document.getElementById("root")!).render(
  <StrictMode>
    <App />
  </StrictMode>,
);
```

## frontend/src/index.css

```css
@import "tailwindcss";
```

## frontend/src/App.tsx

```tsx
import { useEffect, useState } from "react";
import { BrowserRouter, Route, Routes } from "react-router-dom";
import { ProtectedRoute } from "./components/layout/ProtectedRoute";
import { AppLayout } from "./components/layout/AppLayout";
import { API_BASE } from "./services/api";
import { BillingPage } from "./pages/BillingPage";
import { CustomersPage } from "./pages/CustomersPage";
import { DashboardPage } from "./pages/DashboardPage";
import { ExpensesPage } from "./pages/ExpensesPage";
import { InventoryPage } from "./pages/InventoryPage";
import { LoginPage } from "./pages/LoginPage";
import { ProductsPage } from "./pages/ProductsPage";
import { PurchasesPage } from "./pages/PurchasesPage";
import { ReportsPage } from "./pages/ReportsPage";
import { SettingsPage } from "./pages/SettingsPage";
import { SuppliersPage } from "./pages/SuppliersPage";
import { UsersPage } from "./pages/UsersPage";

function Splash() {
  return (
    <div className="flex h-screen items-center justify-center bg-slate-100">
      <div className="text-center">
        <div className="mb-3 text-4xl">🛍️</div>
        <div className="animate-pulse text-lg font-semibold text-slate-700">
          Starting Local Retail Manager…
        </div>
      </div>
    </div>
  );
}

export default function App() {
  const [ready, setReady] = useState(false);

  useEffect(() => {
    let stopped = false;
    const tryOnce = async () => {
      try {
        const res = await fetch(`${API_BASE}/api/health`);
        if (res.ok) setReady(true);
      } catch {
        /* backend still booting */
      }
    };
    const id = setInterval(async () => {
      if (stopped) return;
      await tryOnce();
      if (!stopped) setReady((r) => r || false);
    }, 500);
    tryOnce();
    setTimeout(() => clearInterval(id), 30000);
    return () => {
      stopped = true;
      clearInterval(id);
    };
  }, []);

  if (!ready) return <Splash />;

  return (
    <BrowserRouter>
      <Routes>
        <Route path="/login" element={<LoginPage />} />
        <Route element={<ProtectedRoute />}>
          <Route element={<AppLayout />}>
            <Route path="/" element={<DashboardPage />} />
            <Route path="/billing" element={<BillingPage />} />
            <Route path="/products" element={<ProductsPage />} />
            <Route path="/inventory" element={<InventoryPage />} />
            <Route path="/purchases" element={<PurchasesPage />} />
            <Route path="/customers" element={<CustomersPage />} />
            <Route path="/suppliers" element={<SuppliersPage />} />
            <Route path="/expenses" element={<ExpensesPage />} />
            <Route path="/reports" element={<ReportsPage />} />
            <Route path="/users" element={<UsersPage />} />
            <Route path="/settings" element={<SettingsPage />} />
          </Route>
        </Route>
      </Routes>
    </BrowserRouter>
  );
}
```

## frontend/src/types/index.ts

```ts
export type Role = "OWNER" | "MANAGER" | "CASHIER";
export type MovementType = "PURCHASE" | "SALE" | "RETURN" | "ADJUSTMENT" | "DAMAGE";
export type PaymentMethod = "CASH" | "UPI" | "CARD" | "CREDIT" | "BANK";
export type SaleStatus = "COMPLETED" | "RETURNED";
export type PurchaseStatus = "COMPLETED" | "PARTIAL";

export interface Paginated<T> {
  items: T[];
  total: number;
  page: number;
  size: number;
}

export interface Category {
  id: number;
  name: string;
  description: string | null;
}

export interface Product {
  id: number;
  name: string;
  sku: string | null;
  barcode: string | null;
  category_id: number | null;
  category_name: string | null;
  purchase_price: number;
  selling_price: number;
  tax_rate: number;
  min_stock: number;
  current_stock: number;
  avg_cost: number;
  is_active: boolean;
  created_at: string;
  updated_at: string;
}

export interface ProductInput {
  name: string;
  sku?: string | null;
  barcode?: string | null;
  category_id?: number | null;
  purchase_price?: number;
  selling_price?: number;
  tax_rate?: number;
  min_stock?: number;
  is_active?: boolean;
}

export interface Customer {
  id: number;
  name: string;
  phone: string | null;
  address: string | null;
  notes: string | null;
  is_active: boolean;
}

export interface CustomerInput {
  name: string;
  phone?: string | null;
  address?: string | null;
  notes?: string | null;
}

export interface Supplier {
  id: number;
  name: string;
  phone: string | null;
  address: string | null;
  notes: string | null;
  is_active: boolean;
}

export interface SupplierInput {
  name: string;
  phone?: string | null;
  address?: string | null;
  notes?: string | null;
}

export interface SaleItem {
  id: number;
  product_id: number;
  product_name: string | null;
  quantity: number;
  unit_price: number;
  tax_rate: number;
  line_total: number;
  returned_qty: number;
}

export interface Payment {
  id: number;
  amount: number;
  method: PaymentMethod;
  reference: string | null;
  paid_at: string;
}

export interface Sale {
  id: number;
  invoice_no: string;
  customer_id: number | null;
  customer_name: string | null;
  subtotal: number;
  discount_pct: number;
  discount: number;
  tax: number;
  total: number;
  status: SaleStatus;
  sale_date: string;
  notes: string | null;
  created_by: string | null;
  items: SaleItem[];
  payments: Payment[];
}

export interface SaleInput {
  customer_id?: number | null;
  discount_pct?: number;
  notes?: string | null;
  items: { product_id: number; quantity: number; unit_price?: number; tax_rate?: number }[];
  payments: { method: PaymentMethod; amount?: number }[];
}

export interface PurchaseItem {
  id: number;
  product_id: number;
  product_name: string | null;
  quantity: number;
  unit_cost: number;
  tax_rate: number;
  line_total: number;
}

export interface Purchase {
  id: number;
  purchase_no: string;
  supplier_id: number | null;
  supplier_name: string | null;
  purchase_date: string;
  subtotal: number;
  discount_pct: number;
  discount: number;
  tax: number;
  total: number;
  paid_amount: number;
  payment_method: PaymentMethod;
  status: PurchaseStatus;
  notes: string | null;
  created_by: string | null;
  items: PurchaseItem[];
}

export interface PurchaseInput {
  supplier_id?: number | null;
  discount_pct?: number;
  paid_amount?: number;
  payment_method?: PaymentMethod;
  notes?: string | null;
  items: { product_id: number; quantity: number; unit_cost: number }[];
}

export interface Expense {
  id: number;
  expense_date: string;
  category: string;
  amount: number;
  description: string | null;
  created_by: string | null;
}

export interface ExpenseInput {
  expense_date?: string | null;
  category: string;
  amount: number;
  description?: string | null;
}

export interface InventoryMovement {
  id: number;
  product_id: number;
  product_name: string | null;
  movement_type: MovementType;
  quantity: number;
  unit_cost: number;
  ref_type: string | null;
  ref_id: number | null;
  note: string | null;
  created_at: string;
  created_by: string | null;
}

export interface User {
  id: number;
  username: string;
  full_name: string;
  role: Role;
  is_active: boolean;
}

export interface ShopSettings {
  shop_name: string;
  shop_address: string | null;
  shop_phone: string | null;
  shop_gstin: string | null;
  currency: string;
  default_tax_rate: number;
  invoice_footer: string | null;
}

export interface Backup {
  filename: string;
  size: number;
  created_at: string;
}

export interface DashboardSummary {
  today: { revenue: number; profit: number; transactions: number };
  low_stock: { id: number; name: string; current_stock: number; min_stock: number }[];
  top_products: { product_id: number; name: string; sold: number }[];
  recent_sales: {
    id: number;
    invoice_no: string;
    total: number;
    sale_date: string;
    customer_name: string | null;
  }[];
  revenue_series: { date: string; value: number }[];
  expense_series: { date: string; value: number }[];
  profit_series: { date: string; value: number }[];
}

export interface LedgerEntry {
  date: string;
  type: "SALE" | "PAYMENT" | "PURCHASE";
  reference: string;
  debit: number | null;
  credit: number | null;
  balance: number;
}

export class ApiError extends Error {
  status: number;
  code?: string;
  constructor(status: number, message: string, code?: string) {
    super(message);
    this.status = status;
    this.code = code;
  }
}
```

## frontend/src/constants/index.ts

```ts
import type { Role } from "../types";

export const ROLE_LABELS: Record<Role, string> = {
  OWNER: "Owner",
  MANAGER: "Manager",
  CASHIER: "Cashier",
};

export const PAYMENT_METHODS = ["CASH", "UPI", "CARD", "CREDIT", "BANK"] as const;

export const MOVEMENT_LABELS: Record<string, string> = {
  PURCHASE: "Purchase",
  SALE: "Sale",
  RETURN: "Return",
  ADJUSTMENT: "Adjustment",
  DAMAGE: "Damage",
};

export const EXPENSE_CATEGORIES = [
  "Rent", "Salaries", "Electricity", "Internet", "Transport",
  "Packaging", "Maintenance", "Miscellaneous",
];

export interface NavItem {
  to: string;
  label: string;
  roles?: Role[];
}

export const NAV_ITEMS: NavItem[] = [
  { to: "/", label: "Dashboard", roles: ["OWNER", "MANAGER"] },
  { to: "/billing", label: "Billing" },
  { to: "/products", label: "Products" },
  { to: "/inventory", label: "Inventory", roles: ["OWNER", "MANAGER"] },
  { to: "/purchases", label: "Purchases", roles: ["OWNER", "MANAGER"] },
  { to: "/customers", label: "Customers" },
  { to: "/suppliers", label: "Suppliers", roles: ["OWNER", "MANAGER"] },
  { to: "/expenses", label: "Expenses", roles: ["OWNER", "MANAGER"] },
  { to: "/reports", label: "Reports", roles: ["OWNER", "MANAGER"] },
  { to: "/users", label: "Users", roles: ["OWNER"] },
  { to: "/settings", label: "Settings", roles: ["OWNER"] },
];
```

## frontend/src/utils/format.ts

```ts
export function round2(n: number): number {
  return Math.round((n + Number.EPSILON) * 100) / 100;
}

export function formatMoney(n: number, currency = "₹"): string {
  return `${currency}${n.toLocaleString("en-IN", { minimumFractionDigits: 2, maximumFractionDigits: 2 })}`;
}

export function formatDate(iso: string | null | undefined): string {
  if (!iso) return "—";
  return new Date(iso).toLocaleDateString("en-IN", { day: "2-digit", month: "short", year: "numeric" });
}

export function formatDateTime(iso: string | null | undefined): string {
  if (!iso) return "—";
  return new Date(iso).toLocaleString("en-IN", {
    day: "2-digit", month: "short", year: "numeric", hour: "2-digit", minute: "2-digit",
  });
}

export function formatBytes(n: number): string {
  if (n < 1024) return `${n} B`;
  if (n < 1024 * 1024) return `${(n / 1024).toFixed(1)} KB`;
  return `${(n / (1024 * 1024)).toFixed(1)} MB`;
}
```

## frontend/src/utils/pricing.ts

```ts
import { round2 } from "./format";

export interface PriceLine {
  qty: number;
  unitPrice: number;
  taxRate: number;
}

export function lineTotal(qty: number, unitPrice: number): number {
  return round2(qty * unitPrice);
}

export function computeTotals(lines: PriceLine[], discountPct: number) {
  const subtotal = round2(lines.reduce((s, l) => s + l.qty * l.unitPrice, 0));
  const discount = round2((subtotal * discountPct) / 100);
  const tax = round2(
    lines.reduce(
      (s, l) => s + l.qty * l.unitPrice * (1 - discountPct / 100) * (l.taxRate / 100),
      0,
    ),
  );
  const total = round2(subtotal - discount + tax);
  return { subtotal, discount, tax, total };
}
```

## frontend/src/utils/csv.ts

```ts
export function downloadCSV(filename: string, headers: string[], rows: unknown[][]) {
  const esc = (v: unknown) => {
    const s = String(v ?? "");
    return /[",\n]/.test(s) ? `"${s.replace(/"/g, '""')}"` : s;
  };
  const content = [headers, ...rows].map((r) => r.map(esc).join(",")).join("\n");
  const blob = new Blob(["\uFEFF" + content], { type: "text/csv;charset=utf-8" });
  const url = URL.createObjectURL(blob);
  const a = document.createElement("a");
  a.href = url;
  a.download = filename;
  a.click();
  URL.revokeObjectURL(url);
}
```

## frontend/src/utils/pricing.test.ts

```ts
import { describe, expect, it } from "vitest";
import { computeTotals, lineTotal } from "./pricing";

describe("computeTotals", () => {
  it("matches backend math for a discounted taxed sale", () => {
    const t = computeTotals([{ qty: 10, unitPrice: 100, taxRate: 18 }], 10);
    expect(t.subtotal).toBe(1000);
    expect(t.discount).toBe(100);
    expect(t.tax).toBe(162);
    expect(t.total).toBe(1062);
  });

  it("handles zero discount and zero tax", () => {
    const t = computeTotals([{ qty: 3, unitPrice: 28, taxRate: 0 }], 0);
    expect(t.total).toBe(84);
  });

  it("lineTotal rounds to the paisa", () => {
    expect(lineTotal(3, 10.333)).toBe(31);
  });
});
```

## frontend/src/services/api.ts

```ts
import { ApiError } from "../types";

export const API_BASE =
  (import.meta.env.VITE_API_URL as string | undefined) ?? "http://127.0.0.1:8000";

export const TOKEN_KEY = "lrm_token";

export function token(): string | null {
  return localStorage.getItem(TOKEN_KEY);
}

export function toQuery(params: Record<string, string | number | boolean | null | undefined>): string {
  const q = new URLSearchParams();
  for (const [k, v] of Object.entries(params)) {
    if (v !== null && v !== undefined && v !== "") q.set(k, String(v));
  }
  const s = q.toString();
  return s ? `?${s}` : "";
}

async function request<T>(path: string, options: RequestInit = {}): Promise<T> {
  const headers: Record<string, string> = {
    "Content-Type": "application/json",
    ...(options.headers as Record<string, string> | undefined),
  };
  const t = token();
  if (t) headers.Authorization = `Bearer ${t}`;

  let res: Response;
  try {
    res = await fetch(`${API_BASE}${path}`, { ...options, headers });
  } catch {
    throw new ApiError(0, "Cannot reach the app server. Is it running?");
  }

  if (res.status === 401) {
    localStorage.removeItem(TOKEN_KEY);
    if (!location.pathname.startsWith("/login")) location.href = "/login";
  }

  if (!res.ok) {
    let detail: unknown = res.statusText;
    try {
      const body = await res.json();
      detail = (body as { detail?: unknown }).detail ?? detail;
    } catch {
      /* non-JSON error body */
    }
    const shape =
      typeof detail === "object" && detail !== null
        ? (detail as { code?: string; message?: string })
        : null;
    const message =
      typeof detail === "string" ? detail : (shape?.message ?? `Request failed (${res.status})`);
    throw new ApiError(res.status, message, shape?.code);
  }

  if (res.status === 204) return undefined as T;
  return (await res.json()) as T;
}

export const api = {
  get: <T>(path: string) => request<T>(path),
  post: <T>(path: string, body?: unknown) =>
    request<T>(path, { method: "POST", body: JSON.stringify(body ?? {}) }),
  put: <T>(path: string, body?: unknown) =>
    request<T>(path, { method: "PUT", body: JSON.stringify(body ?? {}) }),
  patch: <T>(path: string, body?: unknown) =>
    request<T>(path, { method: "PATCH", body: JSON.stringify(body ?? {}) }),
  delete: <T>(path: string) => request<T>(path, { method: "DELETE" }),
};
```

## frontend/src/services/auth.ts

```ts
import { api } from "./api";
import type { User } from "../types";

export const authApi = {
  login: (username: string, password: string) =>
    api.post<{ access_token: string; user: User }>("/api/auth/login", { username, password }),
  me: () => api.get<User>("/api/auth/me"),
};
```

## frontend/src/services/products.ts

```ts
import { api, toQuery } from "./api";
import type { Category, Paginated, Product, ProductInput } from "../types";

export const productsApi = {
  list: (params: {
    search?: string;
    category_id?: number;
    include_inactive?: boolean;
    page?: number;
    size?: number;
  } = {}) => api.get<Paginated<Product>>(`/api/products${toQuery(params)}`),
  get: (id: number) => api.get<Product>(`/api/products/${id}`),
  byBarcode: (barcode: string) => api.get<Product>(`/api/products/by-barcode/${encodeURIComponent(barcode)}`),
  create: (data: ProductInput) => api.post<Product>("/api/products", data),
  update: (id: number, data: Partial<ProductInput>) => api.patch<Product>(`/api/products/${id}`, data),
  deactivate: (id: number) => api.delete<void>(`/api/products/${id}`),
};

export const categoriesApi = {
  list: () => api.get<Category[]>("/api/categories"),
  create: (data: { name: string; description?: string | null }) =>
    api.post<Category>("/api/categories", data),
};
```

## frontend/src/services/customers.ts

```ts
import { api, toQuery } from "./api";
import type { Customer, CustomerInput, LedgerEntry, Payment, PaymentMethod } from "../types";

export const customersApi = {
  list: (params: { search?: string; page?: number; size?: number } = {}) =>
    api.get<Customer[]>(`/api/customers${toQuery(params)}`),
  create: (data: CustomerInput) => api.post<Customer>("/api/customers", data),
  update: (id: number, data: Partial<CustomerInput>) => api.patch<Customer>(`/api/customers/${id}`, data),
  balance: (id: number) => api.get<{ customer_id: number; balance: number }>(`/api/customers/${id}/balance`),
  ledger: (id: number) => api.get<{ entries: LedgerEntry[] }>(`/api/customers/${id}/ledger`),
  pay: (id: number, data: { amount: number; method: PaymentMethod; reference?: string }) =>
    api.post<Payment>(`/api/customers/${id}/payments`, data),
};
```

## frontend/src/services/suppliers.ts

```ts
import { api, toQuery } from "./api";
import type { LedgerEntry, Payment, PaymentMethod, Supplier, SupplierInput } from "../types";

export const suppliersApi = {
  list: (params: { search?: string; page?: number; size?: number } = {}) =>
    api.get<Supplier[]>(`/api/suppliers${toQuery(params)}`),
  create: (data: SupplierInput) => api.post<Supplier>("/api/suppliers", data),
  update: (id: number, data: Partial<SupplierInput>) => api.patch<Supplier>(`/api/suppliers/${id}`, data),
  balance: (id: number) => api.get<{ supplier_id: number; balance: number }>(`/api/suppliers/${id}/balance`),
  ledger: (id: number) => api.get<{ entries: LedgerEntry[] }>(`/api/suppliers/${id}/ledger`),
  pay: (id: number, data: { amount: number; method: PaymentMethod; reference?: string }) =>
    api.post<Payment>(`/api/suppliers/${id}/payments`, data),
};
```

## frontend/src/services/sales.ts

```ts
import { API_BASE, api, toQuery } from "./api";
import type { Paginated, Sale, SaleInput } from "../types";

export const salesApi = {
  create: (data: SaleInput) => api.post<Sale>("/api/sales", data),
  list: (params: {
    from_date?: string;
    to_date?: string;
    customer_id?: number;
    search?: string;
    page?: number;
    size?: number;
  } = {}) => api.get<Paginated<Sale>>(`/api/sales${toQuery(params)}`),
  get: (id: number) => api.get<Sale>(`/api/sales/${id}`),
  returnItems: (id: number, items: { product_id: number; quantity: number }[]) =>
    api.post<Sale>(`/api/sales/${id}/return`, { items }),
  invoiceUrl: (id: number) => `${API_BASE}/api/sales/${id}/invoice`,
};
```

`API_BASE` is exported by `services/api.ts` (line 4), so importing it here keeps the invoice link pointing at the same server the rest of the app talks to.

## frontend/src/services/purchases.ts

```ts
import { api, toQuery } from "./api";
import type { Paginated, Payment, PaymentMethod, Purchase, PurchaseInput } from "../types";

export const purchasesApi = {
  create: (data: PurchaseInput) => api.post<Purchase>("/api/purchases", data),
  list: (params: {
    from_date?: string;
    to_date?: string;
    supplier_id?: number;
    search?: string;
    page?: number;
    size?: number;
  } = {}) => api.get<Paginated<Purchase>>(`/api/purchases${toQuery(params)}`),
  pay: (id: number, data: { amount: number; method: PaymentMethod }) =>
    api.post<Payment>(`/api/purchases/${id}/pay`, data),
};
```

## frontend/src/services/expenses.ts

```ts
import { api, toQuery } from "./api";
import type { Expense, ExpenseInput } from "../types";

export const expensesApi = {
  list: (params: { from_date?: string; to_date?: string; category?: string } = {}) =>
    api.get<Expense[]>(`/api/expenses${toQuery(params)}`),
  create: (data: ExpenseInput) => api.post<Expense>("/api/expenses", data),
  update: (id: number, data: Partial<ExpenseInput>) => api.patch<Expense>(`/api/expenses/${id}`, data),
  remove: (id: number) => api.delete<void>(`/api/expenses/${id}`),
  categories: () => api.get<string[]>("/api/expenses/categories"),
};
```

## frontend/src/services/inventory.ts

```ts
import { api, toQuery } from "./api";
import type { InventoryMovement, MovementType, Paginated } from "../types";

export const inventoryApi = {
  movements: (params: { product_id?: number; movement_type?: MovementType; page?: number; size?: number } = {}) =>
    api.get<Paginated<InventoryMovement>>(`/api/inventory/movements${toQuery(params)}`),
  adjust: (data: { product_id: number; new_stock: number; reason: string }) =>
    api.post<InventoryMovement>("/api/inventory/adjust", data),
  damage: (data: { product_id: number; quantity: number; note?: string }) =>
    api.post<InventoryMovement>("/api/inventory/damage", data),
  reconcile: () => api.post<{ corrected: number }>("/api/inventory/reconcile"),
  lowStock: () =>
    api.get<{ id: number; name: string; current_stock: number; min_stock: number }[]>("/api/inventory/low-stock"),
};
```

## frontend/src/services/dashboard.ts

```ts
import { api } from "./api";
import type { DashboardSummary } from "../types";

export const dashboardApi = {
  summary: () => api.get<DashboardSummary>("/api/dashboard/summary"),
};
```

## frontend/src/services/reports.ts

```ts
import { api, toQuery } from "./api";

const base = (name: string, from: string, to: string) =>
  `/api/reports/${name}${toQuery({ from_date: from, to_date: to })}`;

export const reportsApi = {
  profit: (from: string, to: string) =>
    api.get<{ revenue: number; cogs: number; gross_profit: number; expenses: number; net_profit: number }>(
      base("profit", from, to),
    ),
  salesDaily: (from: string, to: string) =>
    api.get<{ date: string; transactions: number; revenue: number }[]>(base("sales-daily", from, to)),
  salesMonthly: (from: string, to: string) =>
    api.get<{ month: string; transactions: number; revenue: number }[]>(base("sales-monthly", from, to)),
  productSales: (from: string, to: string) =>
    api.get<{ product_id: number; name: string; units: number; amount: number }[]>(base("product-sales", from, to)),
  purchases: (from: string, to: string) =>
    api.get<Record<string, unknown>[]>(base("purchases", from, to)),
  expenses: (from: string, to: string) =>
    api.get<{ total: number; by_category: { category: string; amount: number }[] }>(base("expenses", from, to)),
  inventory: () => api.get<Record<string, unknown>>("/api/reports/inventory"),
  customers: () => api.get<Record<string, unknown>[]>("/api/reports/customers"),
  suppliers: () => api.get<Record<string, unknown>[]>("/api/reports/suppliers"),
};
```

## frontend/src/services/users.ts

```ts
import { api } from "./api";
import type { Role, User } from "../types";

export const usersApi = {
  list: () => api.get<User[]>("/api/users"),
  create: (data: { username: string; full_name: string; password: string; role: Role }) =>
    api.post<User>("/api/users", data),
  update: (id: number, data: { full_name?: string; role?: Role; is_active?: boolean }) =>
    api.patch<User>(`/api/users/${id}`, data),
  resetPassword: (id: number, password: string) =>
    api.post<{ ok: boolean }>(`/api/users/${id}/password`, { password }),
};
```

## frontend/src/services/settings.ts

```ts
import { api } from "./api";
import type { Backup, ShopSettings } from "../types";

export const settingsApi = {
  get: () => api.get<ShopSettings>("/api/settings"),
  update: (data: Partial<ShopSettings>) => api.put<ShopSettings>("/api/settings", data),
};

export const backupsApi = {
  list: () => api.get<Backup[]>("/api/backups"),
  create: () => api.post<Backup>("/api/backups"),
  restore: (filename: string) => api.post<{ ok: boolean; message: string }>("/api/backups/restore", { filename }),
};
```

## frontend/src/store/auth.ts

```ts
import { create } from "zustand";
import { persist } from "zustand/middleware";
import { TOKEN_KEY } from "../services/api";
import { authApi } from "../services/auth";
import type { User } from "../types";

interface AuthState {
  token: string | null;
  user: User | null;
  login: (username: string, password: string) => Promise<void>;
  logout: () => void;
}

export const useAuth = create<AuthState>()(
  persist(
    (set) => ({
      token: null,
      user: null,
      login: async (username, password) => {
        const res = await authApi.login(username, password);
        localStorage.setItem(TOKEN_KEY, res.access_token);
        set({ token: res.access_token, user: res.user });
      },
      logout: () => {
        localStorage.removeItem(TOKEN_KEY);
        set({ token: null, user: null });
      },
    }),
    { name: "lrm-auth" },
  ),
);
```

## frontend/src/store/cart.ts

```ts
import { create } from "zustand";
import type { PaymentMethod, Product } from "../types";

export interface CartItem {
  product: Product;
  qty: number;
  unitPrice: number;
  taxRate: number;
}

interface CartState {
  items: CartItem[];
  customerId: number | null;
  discountPct: number;
  paymentMethod: PaymentMethod;
  cashReceived: number;
  add: (product: Product) => void;
  setQty: (productId: number, qty: number) => void;
  remove: (productId: number) => void;
  setCustomer: (id: number | null) => void;
  setDiscount: (pct: number) => void;
  setPayment: (m: PaymentMethod) => void;
  setCashReceived: (n: number) => void;
  clear: () => void;
}

export const useCart = create<CartState>((set) => ({
  items: [],
  customerId: null,
  discountPct: 0,
  paymentMethod: "CASH",
  cashReceived: 0,

  add: (product) =>
    set((s) => {
      const existing = s.items.find((i) => i.product.id === product.id);
      if (existing) {
        return {
          items: s.items.map((i) =>
            i.product.id === product.id ? { ...i, qty: i.qty + 1 } : i,
          ),
        };
      }
      return {
        items: [...s.items, { product, qty: 1, unitPrice: product.selling_price, taxRate: product.tax_rate }],
      };
    }),

  setQty: (productId, qty) =>
    set((s) => ({
      items:
        qty <= 0
          ? s.items.filter((i) => i.product.id !== productId)
          : s.items.map((i) => (i.product.id === productId ? { ...i, qty } : i)),
    })),

  remove: (productId) =>
    set((s) => ({ items: s.items.filter((i) => i.product.id !== productId) })),

  setCustomer: (customerId) => set({ customerId }),
  setDiscount: (discountPct) => set({ discountPct }),
  setPayment: (paymentMethod) => set({ paymentMethod }),
  setCashReceived: (cashReceived) => set({ cashReceived }),
  clear: () => set({ items: [], customerId: null, discountPct: 0, paymentMethod: "CASH", cashReceived: 0 }),
}));
```

## frontend/src/store/toast.ts

```ts
import { create } from "zustand";

export interface Toast {
  id: number;
  type: "success" | "error" | "info";
  message: string;
}

interface ToastState {
  toasts: Toast[];
  push: (type: Toast["type"], message: string) => void;
  dismiss: (id: number) => void;
}

let nextId = 1;

export const useToast = create<ToastState>((set) => ({
  toasts: [],
  push: (type, message) => {
    const id = nextId++;
    set((s) => ({ toasts: [...s.toasts, { id, type, message }] }));
    setTimeout(() => {
      set((s) => ({ toasts: s.toasts.filter((t) => t.id !== id) }));
    }, 3500);
  },
  dismiss: (id) => set((s) => ({ toasts: s.toasts.filter((t) => t.id !== id) })),
}));

export const toast = {
  success: (m: string) => useToast.getState().push("success", m),
  error: (m: string) => useToast.getState().push("error", m),
  info: (m: string) => useToast.getState().push("info", m),
};
```

## frontend/src/hooks/useApi.ts

```ts
import { useCallback, useEffect, useState } from "react";

export function useApi<T>(fn: () => Promise<T>, deps: unknown[] = []) {
  const [data, setData] = useState<T | null>(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);

  const run = useCallback(() => {
    setLoading(true);
    setError(null);
    fn()
      .then(setData)
      .catch((e: Error) => setError(e.message))
      .finally(() => setLoading(false));
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, deps);

  useEffect(() => {
    run();
  }, [run]);

  return { data, loading, error, refetch: run };
}
```

## frontend/src/hooks/useDebounce.ts

```ts
import { useEffect, useState } from "react";

export function useDebounce<T>(value: T, delay = 300): T {
  const [debounced, setDebounced] = useState(value);
  useEffect(() => {
    const id = setTimeout(() => setDebounced(value), delay);
    return () => clearTimeout(id);
  }, [value, delay]);
  return debounced;
}
```

## frontend/src/components/ui/Button.tsx

```tsx
import type { ButtonHTMLAttributes, ReactNode } from "react";
import { Spinner } from "./Spinner";

type Variant = "primary" | "secondary" | "danger" | "ghost";

const variants: Record<Variant, string> = {
  primary: "bg-emerald-600 text-white hover:bg-emerald-700",
  secondary: "bg-white text-slate-700 border border-slate-300 hover:bg-slate-50",
  danger: "bg-rose-600 text-white hover:bg-rose-700",
  ghost: "text-slate-600 hover:bg-slate-100",
};

interface Props extends ButtonHTMLAttributes<HTMLButtonElement> {
  variant?: Variant;
  loading?: boolean;
  children: ReactNode;
}

export function Button({ variant = "primary", loading, children, className = "", disabled, ...rest }: Props) {
  return (
    <button
      className={`inline-flex items-center gap-2 rounded-lg px-4 py-2 text-sm font-semibold transition
        disabled:cursor-not-allowed disabled:opacity-60 ${variants[variant]} ${className}`}
      disabled={disabled || loading}
      {...rest}
    >
      {loading && <Spinner className="h-4 w-4" />}
      {children}
    </button>
  );
}
```

## frontend/src/components/ui/Input.tsx

```tsx
import { forwardRef } from "react";
import type { InputHTMLAttributes } from "react";

interface Props extends InputHTMLAttributes<HTMLInputElement> {
  label?: string;
  error?: string;
}

export const Input = forwardRef<HTMLInputElement, Props>(
  ({ label, error, className = "", ...rest }, ref) => (
    <label className="block">
      {label && <span className="mb-1 block text-sm font-medium text-slate-700">{label}</span>}
      <input
        ref={ref}
        className={`w-full rounded-lg border px-3 py-2 text-sm outline-none transition focus:ring-2
          ${error ? "border-rose-400 focus:ring-rose-200"
                  : "border-slate-300 focus:border-emerald-500 focus:ring-emerald-200"} ${className}`}
        {...rest}
      />
      {error && <span className="mt-1 block text-xs text-rose-600">{error}</span>}
    </label>
  ),
);
Input.displayName = "Input";
```

## frontend/src/components/ui/Select.tsx

```tsx
import type { SelectHTMLAttributes } from "react";

interface Props extends SelectHTMLAttributes<HTMLSelectElement> {
  label?: string;
}

export function Select({ label, className = "", children, ...rest }: Props) {
  return (
    <label className="block">
      {label && <span className="mb-1 block text-sm font-medium text-slate-700">{label}</span>}
      <select
        className={`w-full rounded-lg border border-slate-300 bg-white px-3 py-2 text-sm outline-none
          focus:border-emerald-500 focus:ring-2 focus:ring-emerald-200 ${className}`}
        {...rest}
      >
        {children}
      </select>
    </label>
  );
}
```

## frontend/src/components/ui/Modal.tsx

```tsx
import type { ReactNode } from "react";

interface Props {
  open: boolean;
  onClose: () => void;
  title: string;
  children: ReactNode;
  footer?: ReactNode;
  wide?: boolean;
}

export function Modal({ open, onClose, title, children, footer, wide }: Props) {
  if (!open) return null;
  return (
    <div className="fixed inset-0 z-50 flex items-center justify-center">
      <div className="absolute inset-0 bg-black/40" onClick={onClose} />
      <div className={`relative w-full rounded-xl bg-white p-6 shadow-xl ${wide ? "max-w-3xl" : "max-w-lg"}`}>
        <div className="mb-4 flex items-center justify-between">
          <h2 className="text-lg font-semibold text-slate-800">{title}</h2>
          <button onClick={onClose} className="text-slate-400 transition hover:text-slate-600">✕</button>
        </div>
        {children}
        {footer && <div className="mt-4 flex justify-end gap-2">{footer}</div>}
      </div>
    </div>
  );
}
```

## frontend/src/components/ui/ConfirmDialog.tsx

```tsx
import { Button } from "./Button";
import { Modal } from "./Modal";

interface Props {
  open: boolean;
  title: string;
  message: string;
  confirmLabel?: string;
  danger?: boolean;
  onConfirm: () => void;
  onClose: () => void;
}

export function ConfirmDialog({ open, title, message, confirmLabel = "Confirm", danger, onConfirm, onClose }: Props) {
  return (
    <Modal open={open} onClose={onClose} title={title}
      footer={
        <>
          <Button variant="secondary" onClick={onClose}>Cancel</Button>
          <Button variant={danger ? "danger" : "primary"} onClick={onConfirm}>{confirmLabel}</Button>
        </>
      }>
      <p className="text-sm text-slate-600">{message}</p>
    </Modal>
  );
}
```

## frontend/src/components/ui/Badge.tsx

```tsx
type Tone = "neutral" | "success" | "danger" | "warning";

const tones: Record<Tone, string> = {
  neutral: "bg-slate-100 text-slate-700",
  success: "bg-emerald-100 text-emerald-700",
  danger: "bg-rose-100 text-rose-700",
  warning: "bg-amber-100 text-amber-700",
};

export function Badge({ tone = "neutral", children }: { tone?: Tone; children: React.ReactNode }) {
  return (
    <span className={`inline-flex rounded-full px-2 py-0.5 text-xs font-semibold ${tones[tone]}`}>
      {children}
    </span>
  );
}
```

## frontend/src/components/ui/Spinner.tsx

```tsx
export function Spinner({ className = "" }: { className?: string }) {
  return (
    <svg className={`animate-spin ${className}`} viewBox="0 0 24 24" fill="none">
      <circle className="opacity-25" cx="12" cy="12" r="10" stroke="currentColor" strokeWidth="4" />
      <path className="opacity-75" fill="currentColor" d="M4 12a8 8 0 018-8v4a4 4 0 00-4 4H4z" />
    </svg>
  );
}
```

## frontend/src/components/ui/EmptyState.tsx

```tsx
export function EmptyState({ message = "Nothing here yet." }: { message?: string }) {
  return (
    <div className="rounded-xl border border-dashed border-slate-300 bg-white py-12 text-center text-sm text-slate-400">
      {message}
    </div>
  );
}
```

## frontend/src/components/ui/DataTable.tsx

```tsx
import type { ReactNode } from "react";
import { EmptyState } from "./EmptyState";

export interface Column<T> {
  key: string;
  header: string;
  render?: (row: T) => ReactNode;
  className?: string;
}

interface Props<T> {
  columns: Column<T>[];
  rows: T[];
  keyOf: (row: T, index: number) => string | number;
  empty?: string;
}

export function DataTable<T>({ columns, rows, keyOf, empty }: Props<T>) {
  if (rows.length === 0) return <EmptyState message={empty ?? "No records yet."} />;
  return (
    <div className="overflow-x-auto rounded-xl border border-slate-200 bg-white">
      <table className="min-w-full divide-y divide-slate-200 text-sm">
        <thead className="bg-slate-50">
          <tr>
            {columns.map((c) => (
              <th key={c.key} className={`px-4 py-2.5 text-left font-semibold text-slate-600 ${c.className ?? ""}`}>
                {c.header}
              </th>
            ))}
          </tr>
        </thead>
        <tbody className="divide-y divide-slate-100">
          {rows.map((row, index) => (
            <tr key={keyOf(row, index)} className="transition-colors hover:bg-slate-50">
              {columns.map((c) => (
                <td key={c.key} className={`px-4 py-2.5 ${c.className ?? ""}`}>
                  {c.render ? c.render(row) : String((row as Record<string, unknown>)[c.key] ?? "")}
                </td>
              ))}
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
}
```

## frontend/src/components/ui/StatCard.tsx

```tsx
export function StatCard({
  label,
  value,
  sub,
  tone = "default",
}: {
  label: string;
  value: string;
  sub?: string;
  tone?: "default" | "green" | "red";
}) {
  const toneClass =
    tone === "green" ? "text-emerald-600" : tone === "red" ? "text-rose-600" : "text-slate-900";
  return (
    <div className="rounded-xl border border-slate-200 bg-white p-4">
      <div className="text-xs font-medium text-slate-500">{label}</div>
      <div className={`mt-1 text-2xl font-bold ${toneClass}`}>{value}</div>
      {sub && <div className="mt-1 text-xs text-slate-400">{sub}</div>}
    </div>
  );
}
```

## frontend/src/components/ui/PageHeader.tsx

```tsx
import type { ReactNode } from "react";

export function PageHeader({ title, sub, action }: { title: string; sub?: string; action?: ReactNode }) {
  return (
    <div className="flex items-center justify-between">
      <div>
        <h1 className="text-xl font-bold text-slate-800">{title}</h1>
        {sub && <p className="text-sm text-slate-500">{sub}</p>}
      </div>
      {action}
    </div>
  );
}
```

## frontend/src/components/ui/Toaster.tsx

```tsx
import { useToast } from "../../store/toast";

export function Toaster() {
  const toasts = useToast((s) => s.toasts);
  const dismiss = useToast((s) => s.dismiss);

  const styles: Record<string, string> = {
    success: "bg-emerald-600 text-white",
    error: "bg-rose-600 text-white",
    info: "bg-slate-700 text-white",
  };

  return (
    <div className="fixed top-4 right-4 z-[100] flex flex-col gap-2">
      {toasts.map((t) => (
        <button
          key={t.id}
          onClick={() => dismiss(t.id)}
          className={`${styles[t.type]} rounded-lg px-4 py-2 text-sm font-medium shadow-lg transition hover:opacity-90`}
        >
          {t.message}
        </button>
      ))}
    </div>
  );
}
```

## frontend/src/components/layout/AppLayout.tsx

```tsx
import { NavLink, Outlet } from "react-router-dom";
import {
  BarChart3, Boxes, Contact, LayoutDashboard, Package, Settings,
  ShoppingCart, Truck, UserCog, Users, Wallet, type LucideIcon,
} from "lucide-react";
import { NAV_ITEMS } from "../../constants";
import { useAuth } from "../../store/auth";
import { Toaster } from "../ui/Toaster";
import { Topbar } from "./Topbar";

const ICONS: Record<string, LucideIcon> = {
  "/": LayoutDashboard,
  "/billing": ShoppingCart,
  "/products": Package,
  "/inventory": Boxes,
  "/purchases": Truck,
  "/customers": Users,
  "/suppliers": Contact,
  "/expenses": Wallet,
  "/reports": BarChart3,
  "/users": UserCog,
  "/settings": Settings,
};

export function AppLayout() {
  const user = useAuth((s) => s.user);

  const visible = NAV_ITEMS.filter((i) => !i.roles || (user && i.roles.includes(user.role)));

  return (
    <div className="flex min-h-screen bg-slate-100">
      <aside className="flex w-56 shrink-0 flex-col border-r border-slate-200 bg-white">
        <div className="px-5 py-4 text-lg font-bold text-emerald-700">🛍️ Local Retail</div>
        <nav className="flex-1 space-y-0.5 px-3">
          {visible.map(({ to, label }) => {
            const Icon = ICONS[to] ?? Package;
            return (
              <NavLink
                key={to}
                to={to}
                end={to === "/"}
                className={({ isActive }) =>
                  `flex items-center gap-3 rounded-lg px-3 py-2 text-sm font-medium transition
                  ${isActive ? "bg-emerald-50 text-emerald-700" : "text-slate-600 hover:bg-slate-50"}`
                }
              >
                <Icon className="h-4 w-4" />
                {label}
              </NavLink>
            );
          })}
        </nav>
      </aside>
      <main className="flex-1 overflow-auto">
        <Topbar />
        <div className="p-6">
          <Outlet />
        </div>
      </main>
      <Toaster />
    </div>
  );
}
```

## frontend/src/components/layout/Topbar.tsx

```tsx
import { LogOut } from "lucide-react";
import { ROLE_LABELS } from "../../constants";
import { useAuth } from "../../store/auth";
import { Badge } from "../ui/Badge";

export function Topbar() {
  const user = useAuth((s) => s.user);
  const logout = useAuth((s) => s.logout);

  return (
    <header className="flex h-14 items-center justify-end gap-4 border-b border-slate-200 bg-white px-6">
      {user && (
        <>
          <span className="text-sm font-medium text-slate-700">{user.full_name}</span>
          <Badge tone="success">{ROLE_LABELS[user.role]}</Badge>
          <button onClick={logout} className="text-slate-400 transition hover:text-rose-500" title="Logout">
            <LogOut className="h-4 w-4" />
          </button>
        </>
      )}
    </header>
  );
}
```

## frontend/src/components/layout/ProtectedRoute.tsx

```tsx
import { Navigate, Outlet } from "react-router-dom";
import { useAuth } from "../../store/auth";

export function ProtectedRoute() {
  const token = useAuth((s) => s.token);
  return token ? <Outlet /> : <Navigate to="/login" replace />;
}
```

## frontend/src/components/forms/ProductForm.tsx

```tsx
import { useState } from "react";
import { productsApi } from "../../services/products";
import { toast } from "../../store/toast";
import type { Category, Product, ProductInput } from "../../types";
import { Button } from "../ui/Button";
import { Input } from "../ui/Input";
import { Select } from "../ui/Select";

interface Props {
  initial?: Product;
  categories: Category[];
  onSaved: () => void;
}

export function ProductForm({ initial, categories, onSaved }: Props) {
  const [form, setForm] = useState<ProductInput>({
    name: initial?.name ?? "",
    sku: initial?.sku ?? "",
    barcode: initial?.barcode ?? "",
    category_id: initial?.category_id ?? null,
    purchase_price: initial?.purchase_price ?? 0,
    selling_price: initial?.selling_price ?? 0,
    tax_rate: initial?.tax_rate ?? 0,
    min_stock: initial?.min_stock ?? 0,
  });
  const [errors, setErrors] = useState<Record<string, string>>({});
  const [saving, setSaving] = useState(false);

  function set<K extends keyof ProductInput>(key: K, value: ProductInput[K]) {
    setForm((f) => ({ ...f, [key]: value }));
  }

  function validate(): boolean {
    const e: Record<string, string> = {};
    if (!form.name?.trim()) e.name = "Name is required";
    if (Number(form.selling_price) < 0) e.selling_price = "Cannot be negative";
    if (Number(form.tax_rate) < 0 || Number(form.tax_rate) > 100) e.tax_rate = "0–100";
    setErrors(e);
    return Object.keys(e).length === 0;
  }

  async function submit() {
    if (!validate()) return;
    setSaving(true);
    try {
      if (initial) {
        await productsApi.update(initial.id, { ...form, name: form.name!.trim() });
        toast.success("Product updated");
      } else {
        await productsApi.create({ ...form, name: form.name!.trim() });
        toast.success("Product created");
      }
      onSaved();
    } catch (e) {
      toast.error((e as Error).message);
    } finally {
      setSaving(false);
    }
  }

  return (
    <div className="grid grid-cols-2 gap-4">
      <div className="col-span-2">
        <Input label="Name *" value={form.name ?? ""} error={errors.name}
          onChange={(e) => set("name", e.target.value)} />
      </div>
      <Input label="SKU" value={form.sku ?? ""} onChange={(e) => set("sku", e.target.value)} />
      <Input label="Barcode" value={form.barcode ?? ""} onChange={(e) => set("barcode", e.target.value)} />
      <Select label="Category" value={form.category_id ?? ""}
        onChange={(e) => set("category_id", e.target.value ? Number(e.target.value) : null)}>
        <option value="">—</option>
        {categories.map((c) => <option key={c.id} value={c.id}>{c.name}</option>)}
      </Select>
      <div />
      <Input label="Purchase price" type="number" step="0.01" value={form.purchase_price ?? 0}
        onChange={(e) => set("purchase_price", Number(e.target.value))} />
      <Input label="Selling price" type="number" step="0.01" value={form.selling_price ?? 0}
        error={errors.selling_price} onChange={(e) => set("selling_price", Number(e.target.value))} />
      <Input label="Tax rate (%)" type="number" step="0.01" value={form.tax_rate ?? 0}
        error={errors.tax_rate} onChange={(e) => set("tax_rate", Number(e.target.value))} />
      <Input label="Min stock" type="number" step="0.01" value={form.min_stock ?? 0}
        onChange={(e) => set("min_stock", Number(e.target.value))} />
      <div className="col-span-2 flex justify-end gap-2 pt-2">
        <Button variant="secondary" onClick={onSaved}>Cancel</Button>
        <Button loading={saving} onClick={submit}>{initial ? "Save changes" : "Create"}</Button>
      </div>
    </div>
  );
}
```

## frontend/src/components/forms/CustomerForm.tsx

```tsx
import { useState } from "react";
import { customersApi } from "../../services/customers";
import { toast } from "../../store/toast";
import type { Customer, CustomerInput } from "../../types";
import { Button } from "../ui/Button";
import { Input } from "../ui/Input";

interface Props {
  initial?: Customer;
  onSaved: () => void;
}

export function CustomerForm({ initial, onSaved }: Props) {
  const [form, setForm] = useState<CustomerInput>({
    name: initial?.name ?? "",
    phone: initial?.phone ?? "",
    address: initial?.address ?? "",
    notes: initial?.notes ?? "",
  });
  const [saving, setSaving] = useState(false);

  async function submit() {
    if (!form.name.trim()) {
      toast.error("Name is required");
      return;
    }
    setSaving(true);
    try {
      if (initial) {
        await customersApi.update(initial.id, form);
        toast.success("Customer updated");
      } else {
        await customersApi.create(form);
        toast.success("Customer created");
      }
      onSaved();
    } catch (e) {
      toast.error((e as Error).message);
    } finally {
      setSaving(false);
    }
  }

  return (
    <div className="space-y-4">
      <Input label="Name *" value={form.name} onChange={(e) => setForm({ ...form, name: e.target.value })} />
      <Input label="Phone" value={form.phone ?? ""} onChange={(e) => setForm({ ...form, phone: e.target.value })} />
      <Input label="Address" value={form.address ?? ""} onChange={(e) => setForm({ ...form, address: e.target.value })} />
      <Input label="Notes" value={form.notes ?? ""} onChange={(e) => setForm({ ...form, notes: e.target.value })} />
      <div className="flex justify-end gap-2">
        <Button variant="secondary" onClick={onSaved}>Cancel</Button>
        <Button loading={saving} onClick={submit}>{initial ? "Save" : "Create"}</Button>
      </div>
    </div>
  );
}
```

## frontend/src/components/forms/SupplierForm.tsx

```tsx
import { useState } from "react";
import { suppliersApi } from "../../services/suppliers";
import { toast } from "../../store/toast";
import type { Supplier, SupplierInput } from "../../types";
import { Button } from "../ui/Button";
import { Input } from "../ui/Input";

interface Props {
  initial?: Supplier;
  onSaved: () => void;
}

export function SupplierForm({ initial, onSaved }: Props) {
  const [form, setForm] = useState<SupplierInput>({
    name: initial?.name ?? "",
    phone: initial?.phone ?? "",
    address: initial?.address ?? "",
    notes: initial?.notes ?? "",
  });
  const [saving, setSaving] = useState(false);

  async function submit() {
    if (!form.name.trim()) {
      toast.error("Name is required");
      return;
    }
    setSaving(true);
    try {
      if (initial) {
        await suppliersApi.update(initial.id, form);
        toast.success("Supplier updated");
      } else {
        await suppliersApi.create(form);
        toast.success("Supplier created");
      }
      onSaved();
    } catch (e) {
      toast.error((e as Error).message);
    } finally {
      setSaving(false);
    }
  }

  return (
    <div className="space-y-4">
      <Input label="Name *" value={form.name} onChange={(e) => setForm({ ...form, name: e.target.value })} />
      <Input label="Phone" value={form.phone ?? ""} onChange={(e) => setForm({ ...form, phone: e.target.value })} />
      <Input label="Address" value={form.address ?? ""} onChange={(e) => setForm({ ...form, address: e.target.value })} />
      <Input label="Notes" value={form.notes ?? ""} onChange={(e) => setForm({ ...form, notes: e.target.value })} />
      <div className="flex justify-end gap-2">
        <Button variant="secondary" onClick={onSaved}>Cancel</Button>
        <Button loading={saving} onClick={submit}>{initial ? "Save" : "Create"}</Button>
      </div>
    </div>
  );
}
```

## frontend/src/components/forms/ExpenseForm.tsx

```tsx
import { useState } from "react";
import { EXPENSE_CATEGORIES } from "../../constants";
import { expensesApi } from "../../services/expenses";
import { toast } from "../../store/toast";
import type { Expense, ExpenseInput } from "../../types";
import { Button } from "../ui/Button";
import { Input } from "../ui/Input";
import { Select } from "../ui/Select";

interface Props {
  initial?: Expense;
  onSaved: () => void;
}

export function ExpenseForm({ initial, onSaved }: Props) {
  const [form, setForm] = useState<ExpenseInput>({
    expense_date: initial ? initial.expense_date.slice(0, 10) : new Date().toISOString().slice(0, 10),
    category: initial?.category ?? EXPENSE_CATEGORIES[0],
    amount: initial?.amount ?? 0,
    description: initial?.description ?? "",
  });
  const [saving, setSaving] = useState(false);

  async function submit() {
    if (Number(form.amount) <= 0) {
      toast.error("Amount must be positive");
      return;
    }
    setSaving(true);
    try {
      if (initial) {
        await expensesApi.update(initial.id, form);
        toast.success("Expense updated");
      } else {
        await expensesApi.create(form);
        toast.success("Expense recorded");
      }
      onSaved();
    } catch (e) {
      toast.error((e as Error).message);
    } finally {
      setSaving(false);
    }
  }

  return (
    <div className="space-y-4">
      <Input label="Date" type="date" value={form.expense_date ?? ""}
        onChange={(e) => setForm({ ...form, expense_date: e.target.value })} />
      <Select label="Category" value={form.category} onChange={(e) => setForm({ ...form, category: e.target.value })}>
        {EXPENSE_CATEGORIES.map((c) => <option key={c} value={c}>{c}</option>)}
      </Select>
      <Input label="Amount *" type="number" step="0.01" value={form.amount}
        onChange={(e) => setForm({ ...form, amount: Number(e.target.value) })} />
      <Input label="Description" value={form.description ?? ""}
        onChange={(e) => setForm({ ...form, description: e.target.value })} />
      <div className="flex justify-end gap-2">
        <Button variant="secondary" onClick={onSaved}>Cancel</Button>
        <Button loading={saving} onClick={submit}>{initial ? "Save" : "Record"}</Button>
      </div>
    </div>
  );
}
```

## frontend/src/features/reports/rangePresets.ts

```ts
export type RangePreset = "today" | "yesterday" | "week" | "month" | "custom";

const fmt = (d: Date) => d.toISOString().slice(0, 10);
const startOfDay = (d: Date) => new Date(d.getFullYear(), d.getMonth(), d.getDate());

export function presetRange(preset: RangePreset, customFrom?: string, customTo?: string) {
  const now = new Date();
  switch (preset) {
    case "today":
      return { from: fmt(startOfDay(now)), to: fmt(now) };
    case "yesterday": {
      const y = startOfDay(now);
      y.setDate(y.getDate() - 1);
      return { from: fmt(y), to: fmt(y) };
    }
    case "week": {
      const monday = startOfDay(now);
      monday.setDate(monday.getDate() - ((monday.getDay() + 6) % 7));
      return { from: fmt(monday), to: fmt(now) };
    }
    case "month":
      return { from: fmt(new Date(now.getFullYear(), now.getMonth(), 1)), to: fmt(now) };
    case "custom":
      return { from: customFrom ?? "", to: customTo ?? "" };
  }
}

export const PRESET_LABELS: Record<RangePreset, string> = {
  today: "Today",
  yesterday: "Yesterday",
  week: "This Week",
  month: "This Month",
  custom: "Custom",
};
```

## frontend/src/pages/LoginPage.tsx

```tsx
import { useState } from "react";
import { useNavigate } from "react-router-dom";
import { Button } from "../components/ui/Button";
import { Input } from "../components/ui/Input";
import { useAuth } from "../store/auth";
import { toast } from "../store/toast";

export function LoginPage() {
  const login = useAuth((s) => s.login);
  const navigate = useNavigate();
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [busy, setBusy] = useState(false);

  async function submit(e: React.FormEvent) {
    e.preventDefault();
    setBusy(true);
    try {
      await login(username, password);
      navigate("/");
    } catch (err) {
      toast.error((err as Error).message);
    } finally {
      setBusy(false);
    }
  }

  return (
    <div className="flex min-h-screen items-center justify-center bg-slate-100">
      <form onSubmit={submit} className="w-80 rounded-xl bg-white p-8 shadow-lg">
        <div className="mb-6 text-center">
          <div className="text-3xl">🛍️</div>
          <h1 className="mt-2 text-lg font-bold text-slate-800">Local Retail Manager</h1>
          <p className="text-xs text-slate-400">Sign in to continue</p>
        </div>
        <div className="space-y-4">
          <Input label="Username" value={username} onChange={(e) => setUsername(e.target.value)} autoFocus />
          <Input label="Password" type="password" value={password} onChange={(e) => setPassword(e.target.value)} />
          <Button className="w-full" loading={busy}>Sign in</Button>
        </div>
      </form>
    </div>
  );
}
```

## frontend/src/pages/DashboardPage.tsx

```tsx
import { useEffect, useState } from "react";
import { DataTable, type Column } from "../components/ui/DataTable";
import { PageHeader } from "../components/ui/PageHeader";
import { SimpleBarChart } from "../components/ui/SimpleBarChart";
import { StatCard } from "../components/ui/StatCard";
import { dashboardApi } from "../services/dashboard";
import type { DashboardSummary } from "../types";
import { formatDateTime, formatMoney } from "../utils/format";

export function DashboardPage() {
  const [data, setData] = useState<DashboardSummary | null>(null);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    dashboardApi.summary().then(setData).catch((e: Error) => setError(e.message));
  }, []);

  if (error) return <div className="text-rose-600">{error}</div>;
  if (!data) return <div className="text-slate-400">Loading dashboard…</div>;

  const recentColumns: Column<(typeof data.recent_sales)[number]>[] = [
    { key: "invoice_no", header: "Invoice" },
    { key: "customer_name", header: "Customer", render: (r) => r.customer_name ?? "Walk-in" },
    { key: "total", header: "Total", render: (r) => formatMoney(r.total) },
    { key: "sale_date", header: "Time", render: (r) => formatDateTime(r.sale_date) },
  ];

  return (
    <div className="space-y-6">
      <PageHeader title="Dashboard" sub={`Last updated ${new Date().toLocaleTimeString()}`} />

      <div className="grid grid-cols-3 gap-4">
        <StatCard label="Today's Sales" value={formatMoney(data.today.revenue)} />
        <StatCard label="Today's Profit" value={formatMoney(data.today.profit)}
          tone={data.today.profit >= 0 ? "green" : "red"} />
        <StatCard label="Transactions Today" value={String(data.today.transactions)} />
      </div>

      <div className="grid grid-cols-2 gap-4">
        <SimpleBarChart title="Revenue (14 days)" data={data.revenue_series} />
        <SimpleBarChart title="Profit (14 days)" data={data.profit_series}
          tone={data.profit_series.every((p) => p.value >= 0) ? "green" : "red"} />
      </div>

      {data.low_stock.length > 0 && (
        <div className="rounded-xl border border-amber-200 bg-amber-50 p-4">
          <h3 className="font-bold text-amber-800">⚠️ Low stock ({data.low_stock.length})</h3>
          <ul className="mt-2 space-y-1 text-sm text-amber-900">
            {data.low_stock.map((p) => (
              <li key={p.id}>{p.name} — {p.current_stock} left (min {p.min_stock})</li>
            ))}
          </ul>
        </div>
      )}

      <div className="grid grid-cols-2 gap-4">
        <div>
          <h3 className="mb-2 text-sm font-semibold text-slate-700">Recent sales</h3>
          <DataTable columns={recentColumns} rows={data.recent_sales} keyOf={(r) => r.id} empty="No sales today." />
        </div>
        <div className="rounded-xl border border-slate-200 bg-white p-4">
          <h3 className="mb-2 text-sm font-semibold text-slate-700">Top products (30 days)</h3>
          <ul className="space-y-2">
            {data.top_products.map((p, i) => (
              <li key={p.product_id} className="flex items-center justify-between text-sm">
                <span className="text-slate-700">{i + 1}. {p.name}</span>
                <span className="font-semibold text-slate-900">{p.sold} sold</span>
              </li>
            ))}
          </ul>
        </div>
      </div>
    </div>
  );
}
```

> Note: `SimpleBarChart` referenced above lives in `components/ui/SimpleBarChart.tsx` (the 40-line SVG chart from Phase 15). See part 4's UI additions — it's included in the complete tree.

## frontend/src/pages/ProductsPage.tsx

```tsx
import { useCallback, useEffect, useMemo, useState } from "react";
import { Pencil, Plus, Search, Trash2 } from "lucide-react";
import { Badge } from "../components/ui/Badge";
import { Button } from "../components/ui/Button";
import { DataTable, type Column } from "../components/ui/DataTable";
import { EmptyState } from "../components/ui/EmptyState";
import { ProductForm } from "../components/forms/ProductForm";
import { Input } from "../components/ui/Input";
import { Modal } from "../components/ui/Modal";
import { PageHeader } from "../components/ui/PageHeader";
import { useDebounce } from "../hooks/useDebounce";
import { categoriesApi, productsApi } from "../services/products";
import { toast } from "../store/toast";
import type { Category, Product } from "../types";
import { formatMoney } from "../utils/format";

export function ProductsPage() {
  const [rows, setRows] = useState<Product[]>([]);
  const [total, setTotal] = useState(0);
  const [page, setPage] = useState(1);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);
  const [search, setSearch] = useState("");
  const [categoryId, setCategoryId] = useState<number | null>(null);
  const [categories, setCategories] = useState<Category[]>([]);
  const [editing, setEditing] = useState<Product | null>(null);
  const [creating, setCreating] = useState(false);

  const debouncedSearch = useDebounce(search, 300);

  const load = useCallback(async () => {
    setLoading(true);
    setError(null);
    try {
      const res = await productsApi.list({
        search: debouncedSearch || undefined,
        category_id: categoryId ?? undefined,
        page,
        size: 20,
      });
      setRows(res.items);
      setTotal(res.total);
    } catch (e) {
      setError((e as Error).message);
    } finally {
      setLoading(false);
    }
  }, [debouncedSearch, categoryId, page]);

  useEffect(() => {
    load();
  }, [load]);

  useEffect(() => {
    categoriesApi.list().then(setCategories).catch(() => {});
  }, []);

  const columns: Column<Product>[] = useMemo(
    () => [
      {
        key: "name", header: "Product",
        render: (p) => (
          <div>
            <div className="font-medium text-slate-800">{p.name}</div>
            <div className="text-xs text-slate-400">{p.sku ?? ""} {p.barcode ?? ""}</div>
          </div>
        ),
      },
      { key: "category_name", header: "Category", render: (p) => p.category_name ?? "—" },
      { key: "selling_price", header: "Selling", render: (p) => formatMoney(p.selling_price) },
      { key: "purchase_price", header: "Cost", render: (p) => formatMoney(p.purchase_price) },
      {
        key: "current_stock", header: "Stock",
        render: (p) => (
          <Badge tone={p.current_stock <= p.min_stock ? "danger" : "success"}>{p.current_stock}</Badge>
        ),
      },
      {
        key: "actions", header: "",
        render: (p) => (
          <div className="flex justify-end gap-1">
            <Button variant="ghost" onClick={() => setEditing(p)}><Pencil className="h-4 w-4" /></Button>
            <Button variant="ghost" onClick={() => handleDeactivate(p)}>
              <Trash2 className="h-4 w-4 text-rose-500" />
            </Button>
          </div>
        ),
      },
    ],
    [],
  );

  async function handleDeactivate(p: Product) {
    if (!confirm(`Deactivate "${p.name}"? It stays in history but can't be sold.`)) return;
    try {
      await productsApi.deactivate(p.id);
      toast.success(`${p.name} deactivated`);
      load();
    } catch (e) {
      toast.error((e as Error).message);
    }
  }

  return (
    <div className="space-y-4">
      <PageHeader title="Products" action={
        <Button onClick={() => setCreating(true)}><Plus className="h-4 w-4" /> Add Product</Button>
      } />

      <div className="flex items-center gap-3">
        <div className="relative w-72">
          <Search className="absolute top-2.5 left-3 h-4 w-4 text-slate-400" />
          <Input className="pl-9" placeholder="Search name, SKU, barcode…"
            value={search} onChange={(e) => { setSearch(e.target.value); setPage(1); }} />
        </div>
        <select
          className="rounded-lg border border-slate-300 px-3 py-2 text-sm"
          value={categoryId ?? ""}
          onChange={(e) => { setCategoryId(e.target.value ? Number(e.target.value) : null); setPage(1); }}
        >
          <option value="">All categories</option>
          {categories.map((c) => <option key={c.id} value={c.id}>{c.name}</option>)}
        </select>
      </div>

      {loading && <EmptyState message="Loading…" />}
      {!loading && error && (
        <div className="rounded-lg bg-rose-50 p-4 text-sm text-rose-700">
          {error} <button className="underline" onClick={load}>Retry</button>
        </div>
      )}
      {!loading && !error && (
        <DataTable columns={columns} rows={rows} keyOf={(p) => p.id} empty="No products found." />
      )}
      {!loading && !error && total > 0 && (
        <div className="flex items-center gap-2 text-sm text-slate-500">
          <span>{total} product(s) · page {page}</span>
          <Button variant="ghost" disabled={page <= 1} onClick={() => setPage(page - 1)}>Prev</Button>
          <Button variant="ghost" disabled={page * 20 >= total} onClick={() => setPage(page + 1)}>Next</Button>
        </div>
      )}

      <Modal open={creating || !!editing} onClose={() => { setCreating(false); setEditing(null); }}
        title={editing ? "Edit Product" : "Add Product"}>
        <ProductForm initial={editing ?? undefined} categories={categories}
          onSaved={() => { setCreating(false); setEditing(null); load(); }} />
      </Modal>
    </div>
  );
}
```

## frontend/src/pages/BillingPage.tsx

```tsx
import { useEffect, useRef, useState } from "react";
import { Badge } from "../components/ui/Badge";
import { Button } from "../components/ui/Button";
import { Input } from "../components/ui/Input";
import { Modal } from "../components/ui/Modal";
import { Select } from "../components/ui/Select";
import { useDebounce } from "../hooks/useDebounce";
import { customersApi } from "../services/customers";
import { productsApi } from "../services/products";
import { salesApi } from "../services/sales";
import { API_BASE } from "../services/api";
import { useCart } from "../store/cart";
import { toast } from "../store/toast";
import type { Customer, Product } from "../types";
import { formatMoney } from "../utils/format";
import { computeTotals } from "../utils/pricing";

const PAYMENT_METHODS = ["CASH", "UPI", "CARD", "CREDIT"] as const;

export function BillingPage() {
  const cart = useCart();
  const [search, setSearch] = useState("");
  const [products, setProducts] = useState<Product[]>([]);
  const [customers, setCustomers] = useState<Customer[]>([]);
  const [completed, setCompleted] = useState<{ saleId: number; invoice_no: string; total: number } | null>(null);
  const [submitting, setSubmitting] = useState(false);
  const barcodeRef = useRef<HTMLInputElement>(null);
  const debounced = useDebounce(search, 200);

  useEffect(() => {
    const onKey = (e: KeyboardEvent) => {
      if (e.key === "/" && document.activeElement !== barcodeRef.current) {
        e.preventDefault();
        barcodeRef.current?.focus();
      }
    };
    window.addEventListener("keydown", onKey);
    return () => window.removeEventListener("keydown", onKey);
  }, []);

  useEffect(() => {
    productsApi.list({ search: debounced || undefined, size: 50 })
      .then((r) => setProducts(r.items))
      .catch(() => {});
  }, [debounced]);

  useEffect(() => {
    customersApi.list({ size: 200 }).then(setCustomers).catch(() => {});
  }, []);

  const totals = computeTotals(
    cart.items.map((i) => ({ qty: i.qty, unitPrice: i.unitPrice, taxRate: i.taxRate })),
    cart.discountPct,
  );

  async function handleBarcodeOrSearch(e: React.FormEvent) {
    e.preventDefault();
    const term = search.trim();
    if (!term) return;

    // 1. exact barcode lookup server-side (correct even beyond the loaded page)
    if (/^[0-9]+$/.test(term)) {
      try {
        const hit = await productsApi.byBarcode(term);
        cart.add(hit);
        setSearch("");
        barcodeRef.current?.focus();
        return;
      } catch {
        /* not a barcode we know — fall through to search */
      }
    }

    const hit =
      products.find((p) => p.sku === term) ??
      products.find((p) => p.name.toLowerCase().startsWith(term.toLowerCase()));
    if (hit) {
      cart.add(hit);
      setSearch("");
      barcodeRef.current?.focus();
    } else {
      toast.info(`No product for "${term}"`);
    }
  }

  async function completeSale() {
    if (cart.items.length === 0) return;
    setSubmitting(true);
    try {
      const payments =
        cart.paymentMethod === "CREDIT" ? [] : [{ method: cart.paymentMethod, amount: totals.total }];
      const sale = await salesApi.create({
        customer_id: cart.customerId,
        discount_pct: cart.discountPct,
        items: cart.items.map((i) => ({
          product_id: i.product.id,
          quantity: i.qty,
          unit_price: i.unitPrice,
          tax_rate: i.taxRate,
        })),
        payments,
      });
      setCompleted({ saleId: sale.id, invoice_no: sale.invoice_no, total: sale.total });
      cart.clear();
    } catch (e) {
      toast.error((e as Error).message);
    } finally {
      setSubmitting(false);
    }
  }

  return (
    <div className="grid h-full grid-cols-5 gap-4">
      <div className="col-span-3 space-y-3">
        <form onSubmit={handleBarcodeOrSearch} className="flex gap-2">
          <div className="flex-1">
            <Input ref={barcodeRef} autoFocus placeholder="Scan barcode or search… ( / to focus )"
              value={search} onChange={(e) => setSearch(e.target.value)} />
          </div>
          <Button type="submit">Add</Button>
        </form>

        <div className="grid max-h-[calc(100vh-220px)] grid-cols-3 gap-2 overflow-y-auto">
          {products.map((p) => (
            <button
              key={p.id}
              disabled={p.current_stock <= 0}
              onClick={() => cart.add(p)}
              className="rounded-xl border border-slate-200 bg-white p-3 text-left transition
                hover:border-emerald-400 hover:shadow disabled:cursor-not-allowed disabled:opacity-40"
            >
              <div className="truncate text-sm font-semibold text-slate-800">{p.name}</div>
              <div className="mt-1 flex items-center justify-between">
                <span className="text-sm font-bold text-emerald-700">{formatMoney(p.selling_price)}</span>
                <Badge tone={p.current_stock <= 0 ? "danger" : "neutral"}>stock {p.current_stock}</Badge>
              </div>
            </button>
          ))}
        </div>
      </div>

      <div className="col-span-2 flex flex-col rounded-xl border border-slate-200 bg-white p-4">
        <h2 className="mb-3 text-lg font-bold text-slate-800">Cart</h2>

        <div className="max-h-64 flex-1 space-y-2 overflow-y-auto">
          {cart.items.length === 0 && (
            <p className="py-10 text-center text-sm text-slate-400">Scan or click products to add…</p>
          )}
          {cart.items.map((i) => (
            <div key={i.product.id} className="flex items-center gap-2 rounded-lg bg-slate-50 p-2">
              <div className="min-w-0 flex-1">
                <div className="truncate text-sm font-medium">{i.product.name}</div>
                <div className="text-xs text-slate-500">{formatMoney(i.unitPrice)} × {i.qty}</div>
              </div>
              <button className="rounded bg-slate-200 px-2 hover:bg-slate-300" onClick={() => cart.setQty(i.product.id, i.qty - 1)}>−</button>
              <span className="w-8 text-center text-sm font-semibold">{i.qty}</span>
              <button className="rounded bg-slate-200 px-2 hover:bg-slate-300" onClick={() => cart.setQty(i.product.id, i.qty + 1)}>+</button>
              <span className="w-16 text-right text-sm font-bold">
                {formatMoney(computeTotals([{ qty: i.qty, unitPrice: i.unitPrice, taxRate: i.taxRate }], 0).total)}
              </span>
              <button className="ml-1 text-rose-500 hover:text-rose-700" onClick={() => cart.remove(i.product.id)}>✕</button>
            </div>
          ))}
        </div>

        <div className="mt-3 space-y-3 border-t border-slate-200 pt-3">
          <Select label="Customer (credit/Khata)" value={cart.customerId ?? ""}
            onChange={(e) => cart.setCustomer(e.target.value ? Number(e.target.value) : null)}>
            <option value="">Walk-in customer</option>
            {customers.map((c) => <option key={c.id} value={c.id}>{c.name}</option>)}
          </Select>

          <div className="flex items-center justify-between text-sm">
            <span className="text-slate-600">Discount %</span>
            <input type="number" min={0} max={99} value={cart.discountPct}
              onChange={(e) => cart.setDiscount(Number(e.target.value))}
              className="w-20 rounded border border-slate-300 px-2 py-1 text-right" />
          </div>

          <div className="flex gap-1">
            {PAYMENT_METHODS.map((m) => (
              <button key={m} onClick={() => cart.setPayment(m)}
                className={`flex-1 rounded-lg border px-2 py-1.5 text-xs font-semibold transition
                  ${cart.paymentMethod === m ? "border-emerald-500 bg-emerald-50 text-emerald-700"
                                             : "border-slate-200 text-slate-600 hover:bg-slate-50"}`}>
                {m}
              </button>
            ))}
          </div>

          {cart.paymentMethod === "CASH" && (
            <div className="flex items-center justify-between text-sm">
              <span className="text-slate-600">Cash received</span>
              <input type="number" min={0} value={cart.cashReceived || ""}
                onChange={(e) => cart.setCashReceived(Number(e.target.value))}
                className="w-24 rounded border border-slate-300 px-2 py-1 text-right" />
            </div>
          )}
          {cart.paymentMethod === "CASH" && cart.cashReceived > 0 && (
            <div className="flex justify-between text-sm font-semibold text-emerald-700">
              <span>Change</span>
              <span>{formatMoney(cart.cashReceived - totals.total)}</span>
            </div>
          )}

          <div className="space-y-1 border-t border-slate-200 pt-2 text-sm">
            <div className="flex justify-between text-slate-600"><span>Subtotal</span><span>{formatMoney(totals.subtotal)}</span></div>
            <div className="flex justify-between text-slate-600"><span>Discount</span><span>−{formatMoney(totals.discount)}</span></div>
            <div className="flex justify-between text-slate-600"><span>Tax</span><span>{formatMoney(totals.tax)}</span></div>
            <div className="flex justify-between text-base font-bold text-slate-900">
              <span>Total</span><span>{formatMoney(totals.total)}</span>
            </div>
          </div>

          <Button className="w-full py-3 text-base" loading={submitting}
            disabled={cart.items.length === 0} onClick={completeSale}>
            Complete Sale
          </Button>
        </div>
      </div>

      <Modal open={!!completed} onClose={() => setCompleted(null)} title="Sale completed 🎉">
        {completed && (
          <div className="space-y-4 text-center">
            <p className="text-sm text-slate-600">Invoice <b>{completed.invoice_no}</b> for
              <b> {formatMoney(completed.total)}</b></p>
            <div className="flex justify-center gap-2">
              <a className="rounded-lg bg-emerald-600 px-4 py-2 text-sm font-semibold text-white hover:bg-emerald-700"
                href={`${API_BASE}/api/sales/${completed.saleId}/invoice`} target="_blank" rel="noreferrer">
                Print invoice
              </a>
              <Button variant="secondary" onClick={() => setCompleted(null)}>New sale</Button>
            </div>
          </div>
        )}
      </Modal>
    </div>
  );
}
```

## frontend/src/pages/InventoryPage.tsx

```tsx
import { useCallback, useEffect, useState } from "react";
import { Button } from "../components/ui/Button";
import { DataTable, type Column } from "../components/ui/DataTable";
import { Input } from "../components/ui/Input";
import { Modal } from "../components/ui/Modal";
import { PageHeader } from "../components/ui/PageHeader";
import { MOVEMENT_LABELS } from "../constants";
import { inventoryApi } from "../services/inventory";
import { productsApi } from "../services/products";
import { toast } from "../store/toast";
import type { InventoryMovement, Product } from "../types";
import { formatDateTime, formatMoney } from "../utils/format";

export function InventoryPage() {
  const [products, setProducts] = useState<Product[]>([]);
  const [search, setSearch] = useState("");
  const [adjusting, setAdjusting] = useState<Product | null>(null);
  const [newStock, setNewStock] = useState(0);
  const [reason, setReason] = useState("");
  const [movements, setMovements] = useState<InventoryMovement[]>([]);
  const [historyProduct, setHistoryProduct] = useState<Product | null>(null);
  const [loadingHistory, setLoadingHistory] = useState(false);

  const load = useCallback(async () => {
    const res = await productsApi.list({ search: search || undefined, include_inactive: true, size: 100 });
    setProducts(res.items);
  }, [search]);

  useEffect(() => {
    load().catch((e) => toast.error((e as Error).message));
  }, [load]);

  async function openHistory(p: Product) {
    setHistoryProduct(p);
    setLoadingHistory(true);
    try {
      const res = await inventoryApi.movements({ product_id: p.id, size: 50 });
      setMovements(res.items);
    } catch (e) {
      toast.error((e as Error).message);
    } finally {
      setLoadingHistory(false);
    }
  }

  async function submitAdjust() {
    if (!adjusting) return;
    try {
      await inventoryApi.adjust({ product_id: adjusting.id, new_stock: newStock, reason });
      toast.success(`${adjusting.name} stock → ${newStock}`);
      setAdjusting(null);
      load();
    } catch (e) {
      toast.error((e as Error).message);
    }
  }

  const columns: Column<Product>[] = [
    { key: "name", header: "Product" },
    { key: "current_stock", header: "Stock", render: (p) => <b>{p.current_stock}</b> },
    { key: "avg_cost", header: "Avg cost", render: (p) => formatMoney(p.avg_cost) },
    { key: "min_stock", header: "Min", render: (p) => p.min_stock },
    {
      key: "actions", header: "",
      render: (p) => (
        <div className="flex justify-end gap-1">
          <Button variant="ghost" onClick={() => openHistory(p)}>History</Button>
          <Button variant="secondary" onClick={() => { setAdjusting(p); setNewStock(p.current_stock); setReason(""); }}>
            Adjust
          </Button>
        </div>
      ),
    },
  ];

  const moveColumns: Column<InventoryMovement>[] = [
    { key: "movement_type", header: "Type", render: (m) => MOVEMENT_LABELS[m.movement_type] ?? m.movement_type },
    { key: "quantity", header: "Qty", render: (m) => (m.quantity > 0 ? `+${m.quantity}` : `${m.quantity}`) },
    { key: "unit_cost", header: "Cost", render: (m) => formatMoney(m.unit_cost) },
    { key: "note", header: "Note", render: (m) => m.note ?? "—" },
    { key: "created_at", header: "When", render: (m) => formatDateTime(m.created_at) },
    { key: "created_by", header: "By", render: (m) => m.created_by ?? "—" },
  ];

  return (
    <div className="space-y-4">
      <PageHeader title="Inventory" sub="Stock levels and the movement ledger"
        action={<Button variant="secondary" onClick={async () => {
          try {
            const r = await inventoryApi.reconcile();
            toast.success(`Reconciled: ${r.corrected} product(s) corrected`);
            load();
          } catch (e) {
            toast.error((e as Error).message);
          }
        }}>Reconcile</Button>} />

      <Input className="max-w-xs" placeholder="Filter products…" value={search}
        onChange={(e) => setSearch(e.target.value)} />

      <DataTable columns={columns} rows={products} keyOf={(p) => p.id} empty="No products." />

      <Modal open={!!adjusting} onClose={() => setAdjusting(null)} title={`Adjust stock — ${adjusting?.name ?? ""}`}>
        <div className="space-y-4">
          <Input label="New stock" type="number" step="0.01" value={newStock}
            onChange={(e) => setNewStock(Number(e.target.value))} />
          <Input label="Reason *" placeholder="e.g. physical count, received stock…" value={reason}
            onChange={(e) => setReason(e.target.value)} />
          <div className="flex justify-end gap-2">
            <Button variant="secondary" onClick={() => setAdjusting(null)}>Cancel</Button>
            <Button disabled={!reason.trim()} onClick={submitAdjust}>Apply</Button>
          </div>
        </div>
      </Modal>

      <Modal wide open={!!historyProduct} onClose={() => setHistoryProduct(null)}
        title={`Movement history — ${historyProduct?.name ?? ""}`}>
        {loadingHistory ? <p className="text-sm text-slate-400">Loading…</p> : (
          <DataTable columns={moveColumns} rows={movements} keyOf={(m) => m.id} empty="No movements yet." />
        )}
      </Modal>
    </div>
  );
}
```

## frontend/src/pages/CustomersPage.tsx

```tsx
import { useCallback, useEffect, useState } from "react";
import { Plus } from "lucide-react";
import { Button } from "../components/ui/Button";
import { CustomerForm } from "../components/forms/CustomerForm";
import { DataTable, type Column } from "../components/ui/DataTable";
import { Input } from "../components/ui/Input";
import { Modal } from "../components/ui/Modal";
import { PageHeader } from "../components/ui/PageHeader";
import { useDebounce } from "../hooks/useDebounce";
import { customersApi } from "../services/customers";
import { toast } from "../store/toast";
import type { Customer, LedgerEntry } from "../types";
import { formatDate, formatMoney } from "../utils/format";

export function CustomersPage() {
  const [rows, setRows] = useState<Customer[]>([]);
  const [search, setSearch] = useState("");
  const [balances, setBalances] = useState<Record<number, number>>({});
  const [editing, setEditing] = useState<Customer | null>(null);
  const [creating, setCreating] = useState(false);
  const [ledgerFor, setLedgerFor] = useState<Customer | null>(null);
  const [ledger, setLedger] = useState<LedgerEntry[]>([]);
  const [payFor, setPayFor] = useState<Customer | null>(null);
  const [payAmount, setPayAmount] = useState(0);
  const debounced = useDebounce(search, 300);

  const load = useCallback(async () => {
    try {
      const items = await customersApi.list({ search: debounced || undefined, size: 200 });
      setRows(items);
      const bal: Record<number, number> = {};
      await Promise.all(
        items.map(async (c) => {
          const r = await customersApi.balance(c.id);
          bal[c.id] = r.balance;
        }),
      );
      setBalances(bal);
    } catch (e) {
      toast.error((e as Error).message);
    }
  }, [debounced]);

  useEffect(() => {
    load();
  }, [load]);

  async function openLedger(c: Customer) {
    setLedgerFor(c);
    const r = await customersApi.ledger(c.id);
    setLedger(r.entries);
  }

  async function submitPayment() {
    if (!payFor || payAmount <= 0) return;
    try {
      await customersApi.pay(payFor.id, { amount: payAmount, method: "CASH" });
      toast.success(`Received ${formatMoney(payAmount)} from ${payFor.name}`);
      setPayFor(null);
      setPayAmount(0);
      load();
    } catch (e) {
      toast.error((e as Error).message);
    }
  }

  const columns: Column<Customer>[] = [
    { key: "name", header: "Name", render: (c) => <b>{c.name}</b> },
    { key: "phone", header: "Phone", render: (c) => c.phone ?? "—" },
    {
      key: "balance", header: "Balance",
      render: (c) => {
        const b = balances[c.id] ?? 0;
        return <span className={b > 0 ? "font-semibold text-rose-600" : "text-slate-500"}>{formatMoney(b)}</span>;
      },
    },
    {
      key: "actions", header: "",
      render: (c) => (
        <div className="flex justify-end gap-1">
          <Button variant="ghost" onClick={() => openLedger(c)}>Ledger</Button>
          <Button variant="secondary" onClick={() => { setPayFor(c); setPayAmount(0); }}>Receive</Button>
          <Button variant="ghost" onClick={() => setEditing(c)}>Edit</Button>
        </div>
      ),
    },
  ];

  return (
    <div className="space-y-4">
      <PageHeader title="Customers" sub="Including Khata balances"
        action={<Button onClick={() => setCreating(true)}><Plus className="h-4 w-4" /> Add Customer</Button>} />
      <Input className="max-w-xs" placeholder="Search name or phone…" value={search}
        onChange={(e) => setSearch(e.target.value)} />
      <DataTable columns={columns} rows={rows} keyOf={(c) => c.id} empty="No customers." />

      <Modal open={creating || !!editing} onClose={() => { setCreating(false); setEditing(null); }}
        title={editing ? "Edit Customer" : "Add Customer"}>
        <CustomerForm initial={editing ?? undefined}
          onSaved={() => { setCreating(false); setEditing(null); load(); }} />
      </Modal>

      <Modal wide open={!!ledgerFor} onClose={() => setLedgerFor(null)} title={`Khata — ${ledgerFor?.name ?? ""}`}>
        <DataTable
          columns={[
            { key: "date", header: "Date", render: (e) => formatDate(e.date) },
            { key: "type", header: "Type" },
            { key: "reference", header: "Reference" },
            { key: "debit", header: "Debit", render: (e) => (e.debit ? formatMoney(e.debit) : "—") },
            { key: "credit", header: "Credit", render: (e) => (e.credit ? formatMoney(e.credit) : "—") },
            { key: "balance", header: "Balance", render: (e) => <b>{formatMoney(e.balance)}</b> },
          ]}
          rows={ledger} keyOf={(e) => `${e.type}-${e.reference}-${e.date}`} empty="No entries." />
      </Modal>

      <Modal open={!!payFor} onClose={() => setPayFor(null)} title={`Receive payment — ${payFor?.name ?? ""}`}>
        <div className="space-y-4">
          <Input label="Amount" type="number" step="0.01" value={payAmount || ""}
            onChange={(e) => setPayAmount(Number(e.target.value))} />
          <div className="flex justify-end gap-2">
            <Button variant="secondary" onClick={() => setPayFor(null)}>Cancel</Button>
            <Button disabled={payAmount <= 0} onClick={submitPayment}>Receive</Button>
          </div>
        </div>
      </Modal>
    </div>
  );
}
```

## frontend/src/pages/SuppliersPage.tsx

```tsx
import { useCallback, useEffect, useState } from "react";
import { Plus } from "lucide-react";
import { Button } from "../components/ui/Button";
import { SupplierForm } from "../components/forms/SupplierForm";
import { DataTable, type Column } from "../components/ui/DataTable";
import { Input } from "../components/ui/Input";
import { Modal } from "../components/ui/Modal";
import { PageHeader } from "../components/ui/PageHeader";
import { useDebounce } from "../hooks/useDebounce";
import { suppliersApi } from "../services/suppliers";
import { toast } from "../store/toast";
import type { LedgerEntry, Supplier } from "../types";
import { formatDate, formatMoney } from "../utils/format";

export function SuppliersPage() {
  const [rows, setRows] = useState<Supplier[]>([]);
  const [search, setSearch] = useState("");
  const [balances, setBalances] = useState<Record<number, number>>({});
  const [editing, setEditing] = useState<Supplier | null>(null);
  const [creating, setCreating] = useState(false);
  const [ledgerFor, setLedgerFor] = useState<Supplier | null>(null);
  const [ledger, setLedger] = useState<LedgerEntry[]>([]);
  const [payFor, setPayFor] = useState<Supplier | null>(null);
  const [payAmount, setPayAmount] = useState(0);
  const debounced = useDebounce(search, 300);

  const load = useCallback(async () => {
    try {
      const items = await suppliersApi.list({ search: debounced || undefined, size: 200 });
      setRows(items);
      const bal: Record<number, number> = {};
      await Promise.all(
        items.map(async (s) => {
          const r = await suppliersApi.balance(s.id);
          bal[s.id] = r.balance;
        }),
      );
      setBalances(bal);
    } catch (e) {
      toast.error((e as Error).message);
    }
  }, [debounced]);

  useEffect(() => {
    load();
  }, [load]);

  async function openLedger(s: Supplier) {
    setLedgerFor(s);
    const r = await suppliersApi.ledger(s.id);
    setLedger(r.entries);
  }

  async function submitPayment() {
    if (!payFor || payAmount <= 0) return;
    try {
      await suppliersApi.pay(payFor.id, { amount: payAmount, method: "CASH" });
      toast.success(`Paid ${formatMoney(payAmount)} to ${payFor.name}`);
      setPayFor(null);
      setPayAmount(0);
      load();
    } catch (e) {
      toast.error((e as Error).message);
    }
  }

  const columns: Column<Supplier>[] = [
    { key: "name", header: "Name", render: (s) => <b>{s.name}</b> },
    { key: "phone", header: "Phone", render: (s) => s.phone ?? "—" },
    {
      key: "balance", header: "We Owe",
      render: (s) => {
        const b = balances[s.id] ?? 0;
        return b > 0
          ? <span className="font-semibold text-rose-600">{formatMoney(b)}</span>
          : <span className="text-slate-500">—</span>;
      },
    },
    {
      key: "actions", header: "",
      render: (s) => (
        <div className="flex justify-end gap-1">
          <Button variant="ghost" onClick={() => openLedger(s)}>Ledger</Button>
          <Button variant="secondary" onClick={() => { setPayFor(s); setPayAmount(0); }}>Pay</Button>
          <Button variant="ghost" onClick={() => setEditing(s)}>Edit</Button>
        </div>
      ),
    },
  ];

  return (
    <div className="space-y-4">
      <PageHeader title="Suppliers" sub="What we owe each supplier"
        action={<Button onClick={() => setCreating(true)}><Plus className="h-4 w-4" /> Add Supplier</Button>} />
      <Input className="max-w-xs" placeholder="Search name or phone…" value={search}
        onChange={(e) => setSearch(e.target.value)} />
      <DataTable columns={columns} rows={rows} keyOf={(s) => s.id} empty="No suppliers." />

      <Modal open={creating || !!editing} onClose={() => { setCreating(false); setEditing(null); }}
        title={editing ? "Edit Supplier" : "Add Supplier"}>
        <SupplierForm initial={editing ?? undefined}
          onSaved={() => { setCreating(false); setEditing(null); load(); }} />
      </Modal>

      <Modal wide open={!!ledgerFor} onClose={() => setLedgerFor(null)} title={`Supplier ledger — ${ledgerFor?.name ?? ""}`}>
        <DataTable
          columns={[
            { key: "date", header: "Date", render: (e) => formatDate(e.date) },
            { key: "type", header: "Type" },
            { key: "reference", header: "Reference" },
            { key: "debit", header: "Debit", render: (e) => (e.debit ? formatMoney(e.debit) : "—") },
            { key: "credit", header: "Credit", render: (e) => (e.credit ? formatMoney(e.credit) : "—") },
            { key: "balance", header: "Balance", render: (e) => <b>{formatMoney(e.balance)}</b> },
          ]}
          rows={ledger} keyOf={(e, i) => `${e.type}-${e.reference}-${i}`} empty="No entries." />
      </Modal>

      <Modal open={!!payFor} onClose={() => setPayFor(null)} title={`Pay supplier — ${payFor?.name ?? ""}`}>
        <div className="space-y-4">
          <Input label="Amount" type="number" step="0.01" value={payAmount || ""}
            onChange={(e) => setPayAmount(Number(e.target.value))} />
          <div className="flex justify-end gap-2">
            <Button variant="secondary" onClick={() => setPayFor(null)}>Cancel</Button>
            <Button disabled={payAmount <= 0} onClick={submitPayment}>Pay</Button>
          </div>
        </div>
      </Modal>
    </div>
  );
}
```

## frontend/src/pages/ExpensesPage.tsx

```tsx
import { useCallback, useEffect, useState } from "react";
import { Pencil, Plus, Trash2 } from "lucide-react";
import { Button } from "../components/ui/Button";
import { ExpenseForm } from "../components/forms/ExpenseForm";
import { DataTable, type Column } from "../components/ui/DataTable";
import { Modal } from "../components/ui/Modal";
import { PageHeader } from "../components/ui/PageHeader";
import { StatCard } from "../components/ui/StatCard";
import { EXPENSE_CATEGORIES } from "../constants";
import { expensesApi } from "../services/expenses";
import { toast } from "../store/toast";
import type { Expense } from "../types";
import { formatDate, formatMoney } from "../utils/format";

export function ExpensesPage() {
  const [rows, setRows] = useState<Expense[]>([]);
  const [monthTotal, setMonthTotal] = useState(0);
  const [category, setCategory] = useState("");
  const [editing, setEditing] = useState<Expense | null>(null);
  const [creating, setCreating] = useState(false);

  const load = useCallback(async () => {
    try {
      const items = await expensesApi.list({ category: category || undefined });
      setRows(items);
      const now = new Date();
      const first = new Date(now.getFullYear(), now.getMonth(), 1).toISOString().slice(0, 10);
      const today = now.toISOString().slice(0, 10);
      const monthItems = await expensesApi.list({ from_date: first, to_date: today });
      setMonthTotal(monthItems.reduce((s, e) => s + e.amount, 0));
    } catch (e) {
      toast.error((e as Error).message);
    }
  }, [category]);

  useEffect(() => {
    load();
  }, [load]);

  async function handleDelete(e: Expense) {
    if (!confirm(`Delete this ${formatMoney(e.amount)} expense?`)) return;
    try {
      await expensesApi.remove(e.id);
      toast.success("Expense deleted");
      load();
    } catch (err) {
      toast.error((err as Error).message);
    }
  }

  const columns: Column<Expense>[] = [
    { key: "expense_date", header: "Date", render: (e) => formatDate(e.expense_date) },
    { key: "category", header: "Category" },
    { key: "description", header: "Description", render: (e) => e.description ?? "—" },
    { key: "amount", header: "Amount", render: (e) => <b>{formatMoney(e.amount)}</b> },
    {
      key: "actions", header: "",
      render: (e) => (
        <div className="flex justify-end gap-1">
          <Button variant="ghost" onClick={() => setEditing(e)}><Pencil className="h-4 w-4" /></Button>
          <Button variant="ghost" onClick={() => handleDelete(e)}><Trash2 className="h-4 w-4 text-rose-500" /></Button>
        </div>
      ),
    },
  ];

  return (
    <div className="space-y-4">
      <PageHeader title="Expenses" sub="Operating costs — they reduce net profit"
        action={<Button onClick={() => setCreating(true)}><Plus className="h-4 w-4" /> Add Expense</Button>} />

      <div className="grid grid-cols-2 gap-4">
        <StatCard label="This month" value={formatMoney(monthTotal)} />
        <select className="rounded-lg border border-slate-300 px-3 py-2 text-sm"
          value={category} onChange={(e) => setCategory(e.target.value)}>
          <option value="">All categories</option>
          {EXPENSE_CATEGORIES.map((c) => <option key={c} value={c}>{c}</option>)}
        </select>
      </div>

      <DataTable columns={columns} rows={rows} keyOf={(e) => e.id} empty="No expenses." />

      <Modal open={creating || !!editing} onClose={() => { setCreating(false); setEditing(null); }}
        title={editing ? "Edit Expense" : "Add Expense"}>
        <ExpenseForm initial={editing ?? undefined}
          onSaved={() => { setCreating(false); setEditing(null); load(); }} />
      </Modal>
    </div>
  );
}
```

## frontend/src/pages/PurchasesPage.tsx

```tsx
import { useCallback, useEffect, useState } from "react";
import { Plus } from "lucide-react";
import { Badge } from "../components/ui/Badge";
import { Button } from "../components/ui/Button";
import { DataTable, type Column } from "../components/ui/DataTable";
import { Input } from "../components/ui/Input";
import { Modal } from "../components/ui/Modal";
import { PageHeader } from "../components/ui/PageHeader";
import { Select } from "../components/ui/Select";
import { purchasesApi } from "../services/purchases";
import { productsApi } from "../services/products";
import { suppliersApi } from "../services/suppliers";
import { toast } from "../store/toast";
import type { Product, Purchase, Supplier } from "../types";
import { formatDate, formatMoney } from "../utils/format";

export function PurchasesPage() {
  const [rows, setRows] = useState<Purchase[]>([]);
  const [suppliers, setSuppliers] = useState<Supplier[]>([]);
  const [products, setProducts] = useState<Product[]>([]);
  const [creating, setCreating] = useState(false);
  const [supplierId, setSupplierId] = useState<number | null>(null);
  const [paidAmount, setPaidAmount] = useState(0);
  const [method, setMethod] = useState("CASH");
  const [lines, setLines] = useState<{ product_id: number | null; quantity: number; unit_cost: number }[]>([
    { product_id: null, quantity: 1, unit_cost: 0 },
  ]);
  const [saving, setSaving] = useState(false);

  const load = useCallback(async () => {
    try {
      const res = await purchasesApi.list({ size: 50 });
      setRows(res.items);
    } catch (e) {
      toast.error((e as Error).message);
    }
  }, []);

  useEffect(() => {
    load();
    suppliersApi.list({ size: 200 }).then(setSuppliers).catch(() => {});
    productsApi.list({ size: 200 }).then((r) => setProducts(r.items)).catch(() => {});
  }, [load]);

  function updateLine(idx: number, patch: Partial<(typeof lines)[number]>) {
    setLines((ls) => ls.map((l, i) => (i === idx ? { ...l, ...patch } : l)));
  }

  const subtotal = lines.reduce((s, l) => s + (l.product_id ? l.quantity * l.unit_cost : 0), 0);

  async function submit() {
    const items = lines
      .filter((l) => l.product_id && l.quantity > 0 && l.unit_cost > 0)
      .map((l) => ({ product_id: l.product_id as number, quantity: l.quantity, unit_cost: l.unit_cost }));
    if (items.length === 0) {
      toast.error("Add at least one item with quantity and cost");
      return;
    }
    setSaving(true);
    try {
      await purchasesApi.create({
        supplier_id: supplierId,
        paid_amount: paidAmount,
        payment_method: method as never,
        items,
      });
      toast.success("Purchase recorded — stock increased");
      setCreating(false);
      setSupplierId(null);
      setPaidAmount(0);
      setLines([{ product_id: null, quantity: 1, unit_cost: 0 }]);
      load();
    } catch (e) {
      toast.error((e as Error).message);
    } finally {
      setSaving(false);
    }
  }

  const columns: Column<Purchase>[] = [
    { key: "purchase_no", header: "No.", render: (p) => <b>{p.purchase_no}</b> },
    { key: "supplier_name", header: "Supplier", render: (p) => p.supplier_name ?? "—" },
    { key: "purchase_date", header: "Date", render: (p) => formatDate(p.purchase_date) },
    { key: "total", header: "Total", render: (p) => formatMoney(p.total) },
    { key: "paid_amount", header: "Paid", render: (p) => formatMoney(p.paid_amount) },
    {
      key: "balance", header: "Balance",
      render: (p) => <span className="font-semibold text-rose-600">{formatMoney(p.total - p.paid_amount)}</span>,
    },
    { key: "status", header: "Status", render: (p) => (
      <Badge tone={p.status === "COMPLETED" ? "success" : "warning"}>{p.status}</Badge>
    )},
  ];

  return (
    <div className="space-y-4">
      <PageHeader title="Purchases" sub="Buy stock — inventory increases automatically"
        action={<Button onClick={() => setCreating(true)}><Plus className="h-4 w-4" /> New Purchase</Button>} />
      <DataTable columns={columns} rows={rows} keyOf={(p) => p.id} empty="No purchases yet." />

      <Modal wide open={creating} onClose={() => setCreating(false)} title="New Purchase">
        <div className="space-y-4">
          <div className="grid grid-cols-3 gap-3">
            <Select label="Supplier" value={supplierId ?? ""}
              onChange={(e) => setSupplierId(e.target.value ? Number(e.target.value) : null)}>
              <option value="">—</option>
              {suppliers.map((s) => <option key={s.id} value={s.id}>{s.name}</option>)}
            </Select>
            <Input label="Paid amount" type="number" step="0.01" value={paidAmount || ""}
              onChange={(e) => setPaidAmount(Number(e.target.value))} />
            <Select label="Payment method" value={method} onChange={(e) => setMethod(e.target.value)}>
              <option>CASH</option><option>UPI</option><option>CARD</option><option>BANK</option>
            </Select>
          </div>

          <div className="space-y-2">
            <div className="grid grid-cols-[2fr_1fr_1fr_1fr_auto] gap-2 text-xs font-semibold text-slate-500">
              <span>Product</span><span>Qty</span><span>Unit cost</span><span>Line total</span><span />
            </div>
            {lines.map((l, i) => (
              <div key={i} className="grid grid-cols-[2fr_1fr_1fr_1fr_auto] items-center gap-2">
                <select className="rounded border border-slate-300 px-2 py-1.5 text-sm"
                  value={l.product_id ?? ""}
                  onChange={(e) => updateLine(i, { product_id: e.target.value ? Number(e.target.value) : null })}>
                  <option value="">—</option>
                  {products.map((p) => <option key={p.id} value={p.id}>{p.name}</option>)}
                </select>
                <Input type="number" min={1} value={l.quantity}
                  onChange={(e) => updateLine(i, { quantity: Number(e.target.value) })} />
                <Input type="number" min={0} step="0.01" value={l.unit_cost || ""}
                  onChange={(e) => updateLine(i, { unit_cost: Number(e.target.value) })} />
                <div className="text-right text-sm font-semibold">{formatMoney(l.quantity * l.unit_cost)}</div>
                <button className="text-rose-500" onClick={() =>
                  setLines((ls) => (ls.length > 1 ? ls.filter((_, j) => j !== i) : ls))}>✕</button>
              </div>
            ))}
            <Button variant="secondary" onClick={() =>
              setLines((ls) => [...ls, { product_id: null, quantity: 1, unit_cost: 0 }])}>
              + Add line
            </Button>
          </div>

          <div className="flex items-center justify-between border-t border-slate-200 pt-3">
            <span className="text-sm text-slate-600">Total</span>
            <span className="text-lg font-bold">{formatMoney(subtotal)}</span>
          </div>

          <div className="flex justify-end gap-2">
            <Button variant="secondary" onClick={() => setCreating(false)}>Cancel</Button>
            <Button loading={saving} onClick={submit}>Save Purchase</Button>
          </div>
        </div>
      </Modal>
    </div>
  );
}
```

## frontend/src/pages/ReportsPage.tsx

```tsx
import { useCallback, useEffect, useState } from "react";
import { Button } from "../components/ui/Button";
import { DataTable, type Column } from "../components/ui/DataTable";
import { PageHeader } from "../components/ui/PageHeader";
import { StatCard } from "../components/ui/StatCard";
import { PRESET_LABELS, presetRange, type RangePreset } from "../features/reports/rangePresets";
import { reportsApi } from "../services/reports";
import { toast } from "../store/toast";
import { formatMoney } from "../utils/format";
import { downloadCSV } from "../utils/csv";

type Tab = "profit" | "daily" | "monthly" | "products" | "expenses" | "inventory";

const TABS: { id: Tab; label: string }[] = [
  { id: "profit", label: "Profit" },
  { id: "daily", label: "Daily Sales" },
  { id: "monthly", label: "Monthly Sales" },
  { id: "products", label: "Product Sales" },
  { id: "expenses", label: "Expenses" },
  { id: "inventory", label: "Inventory" },
];

export function ReportsPage() {
  const [tab, setTab] = useState<Tab>("profit");
  const [preset, setPreset] = useState<RangePreset>("today");
  const [customFrom, setCustomFrom] = useState("");
  const [customTo, setCustomTo] = useState("");
  // Each report tab returns a different shape, so we keep the raw payload in
  // an untyped slot and narrow it with a cast at each render site. The casts
  // are local and explicit — swapping tabs always overwrites `data`.
  const [data, setData] = useState<any>(null);
  const [loading, setLoading] = useState(false);

  const load = useCallback(async () => {
    const { from, to } = presetRange(preset, customFrom, customTo);
    if (!from || !to) return;
    setLoading(true);
    try {
      switch (tab) {
        case "profit": setData(await reportsApi.profit(from, to)); break;
        case "daily": setData(await reportsApi.salesDaily(from, to)); break;
        case "monthly": setData(await reportsApi.salesMonthly(from, to)); break;
        case "products": setData(await reportsApi.productSales(from, to)); break;
        case "expenses": setData(await reportsApi.expenses(from, to)); break;
        case "inventory": setData(await reportsApi.inventory()); break;
      }
    } catch (e) {
      toast.error((e as Error).message);
    } finally {
      setLoading(false);
    }
  }, [tab, preset, customFrom, customTo]);

  useEffect(() => {
    load();
  }, [load]);

  function exportCsv() {
    if (tab === "profit" && data) {
      const p = data as { revenue: number; cogs: number; gross_profit: number; expenses: number; net_profit: number };
      downloadCSV("profit.csv", ["Metric", "Value"], [
        ["Revenue", p.revenue], ["COGS", p.cogs], ["Gross profit", p.gross_profit],
        ["Expenses", p.expenses], ["Net profit", p.net_profit],
      ]);
    } else if (tab === "daily" || tab === "monthly" || tab === "products") {
      const rows = data as Record<string, unknown>[];
      downloadCSV(`${tab}.csv`, Object.keys(rows[0] ?? {}), rows.map((r) => Object.values(r)));
    } else if (tab === "expenses" && data) {
      const e = data as { total: number; by_category: { category: string; amount: number }[] };
      downloadCSV("expenses.csv", ["Category", "Amount"],
        [...e.by_category.map((c) => [c.category, c.amount]), ["Total", e.total]]);
    } else if (tab === "inventory" && data) {
      const inv = data as { stock_value: number; low_stock: { name: string; current_stock: number; min_stock: number }[] };
      downloadCSV("inventory.csv", ["Item", "Current", "Min"],
        inv.low_stock.map((p) => [p.name, p.current_stock, p.min_stock]));
    }
  }

  return (
    <div className="space-y-4">
      <PageHeader title="Reports" action={
        <Button variant="secondary" disabled={!data || loading} onClick={exportCsv}>Export CSV</Button>
      } />

      <div className="flex flex-wrap items-center gap-2">
        {(Object.keys(PRESET_LABELS) as RangePreset[]).map((p) => (
          <button key={p}
            onClick={() => setPreset(p)}
            className={`rounded-lg border px-3 py-1.5 text-xs font-semibold transition
              ${preset === p ? "border-emerald-500 bg-emerald-50 text-emerald-700" : "border-slate-200 text-slate-600 hover:bg-slate-50"}`}>
            {PRESET_LABELS[p]}
          </button>
        ))}
        {preset === "custom" && (
          <>
            <input type="date" value={customFrom} onChange={(e) => setCustomFrom(e.target.value)}
              className="rounded-lg border border-slate-300 px-2 py-1.5 text-sm" />
            <span className="text-slate-400">→</span>
            <input type="date" value={customTo} onChange={(e) => setCustomTo(e.target.value)}
              className="rounded-lg border border-slate-300 px-2 py-1.5 text-sm" />
          </>
        )}
      </div>

      <div className="flex gap-1 border-b border-slate-200">
        {TABS.map((t) => (
          <button key={t.id} onClick={() => setTab(t.id)}
            className={`border-b-2 px-4 py-2 text-sm font-medium transition
              ${tab === t.id ? "border-emerald-500 text-emerald-700" : "border-transparent text-slate-500 hover:text-slate-700"}`}>
            {t.label}
          </button>
        ))}
      </div>

      {loading && <p className="text-sm text-slate-400">Loading…</p>}

      {tab === "profit" && data && (() => {
        const p = data as { revenue: number; cogs: number; gross_profit: number; expenses: number; net_profit: number };
        return (
          <div className="grid grid-cols-5 gap-4">
            <StatCard label="Revenue" value={formatMoney(p.revenue)} />
            <StatCard label="COGS" value={formatMoney(p.cogs)} />
            <StatCard label="Gross profit" value={formatMoney(p.gross_profit)}
              tone={p.gross_profit >= 0 ? "green" : "red"} />
            <StatCard label="Expenses" value={formatMoney(p.expenses)} />
            <StatCard label="Net profit" value={formatMoney(p.net_profit)}
              tone={p.net_profit >= 0 ? "green" : "red"} />
          </div>
        );
      })()}

      {(tab === "daily" || tab === "monthly" || tab === "products") && data && (() => {
        const rows = data as Record<string, unknown>[];
        const cols: Column<Record<string, unknown>>[] = Object.keys(rows[0] ?? { date: "", value: 0 }).map((k) => ({
          key: k,
          header: k.toUpperCase(),
          render: (r) => (typeof r[k] === "number" ? formatMoney(Number(r[k])) : String(r[k])),
        }));
        return <DataTable columns={cols} rows={rows} keyOf={(_, i) => `${i}`} empty="No data for this range." />;
      })()}

      {tab === "expenses" && data && (() => {
        const e = data as { total: number; by_category: { category: string; amount: number }[] };
        return (
          <DataTable
            columns={[
              { key: "category", header: "Category" },
              { key: "amount", header: "Amount", render: (r) => formatMoney(r.amount) },
            ]}
            rows={e.by_category} keyOf={(r) => r.category} empty="No expenses in range." />
        );
      })()}

      {tab === "inventory" && data && (() => {
        const inv = data as { stock_value: number; low_stock: { id: number; name: string; current_stock: number; min_stock: number }[] };
        return (
          <div className="space-y-4">
            <StatCard label="Stock value" value={formatMoney(inv.stock_value)} />
            <DataTable
              columns={[
                { key: "name", header: "Product" },
                { key: "current_stock", header: "Stock" },
                { key: "min_stock", header: "Min" },
              ]}
              rows={inv.low_stock} keyOf={(r) => r.id} empty="No low-stock products." />
          </div>
        );
      })()}
    </div>
  );
}
```

## frontend/src/pages/UsersPage.tsx

```tsx
import { useCallback, useEffect, useState } from "react";
import { Plus } from "lucide-react";
import { Badge } from "../components/ui/Badge";
import { Button } from "../components/ui/Button";
import { DataTable, type Column } from "../components/ui/DataTable";
import { Input } from "../components/ui/Input";
import { Modal } from "../components/ui/Modal";
import { PageHeader } from "../components/ui/PageHeader";
import { Select } from "../components/ui/Select";
import { ROLE_LABELS } from "../constants";
import { usersApi } from "../services/users";
import { toast } from "../store/toast";
import type { Role, User } from "../types";

export function UsersPage() {
  const [rows, setRows] = useState<User[]>([]);
  const [creating, setCreating] = useState(false);
  const [username, setUsername] = useState("");
  const [fullName, setFullName] = useState("");
  const [password, setPassword] = useState("");
  const [role, setRole] = useState<Role>("CASHIER");
  const [resetting, setResetting] = useState<User | null>(null);
  const [newPassword, setNewPassword] = useState("");
  const [saving, setSaving] = useState(false);

  const load = useCallback(async () => {
    try {
      setRows(await usersApi.list());
    } catch (e) {
      toast.error((e as Error).message);
    }
  }, []);

  useEffect(() => {
    load();
  }, [load]);

  async function createUser() {
    if (username.trim().length < 3 || password.length < 6) {
      toast.error("Username ≥3 chars, password ≥6");
      return;
    }
    setSaving(true);
    try {
      await usersApi.create({ username: username.trim(), full_name: fullName.trim() || username.trim(), password, role });
      toast.success("User created");
      setCreating(false);
      setUsername(""); setFullName(""); setPassword("");
      load();
    } catch (e) {
      toast.error((e as Error).message);
    } finally {
      setSaving(false);
    }
  }

  async function resetPassword() {
    if (!resetting || newPassword.length < 6) return;
    try {
      await usersApi.resetPassword(resetting.id, newPassword);
      toast.success(`Password reset for ${resetting.username}`);
      setResetting(null);
      setNewPassword("");
    } catch (e) {
      toast.error((e as Error).message);
    }
  }

  const columns: Column<User>[] = [
    { key: "username", header: "Username", render: (u) => <b>{u.username}</b> },
    { key: "full_name", header: "Full name" },
    { key: "role", header: "Role", render: (u) => <Badge tone="success">{ROLE_LABELS[u.role]}</Badge> },
    {
      key: "actions", header: "",
      render: (u) => (
        <div className="flex justify-end">
          <Button variant="ghost" onClick={() => setResetting(u)}>Reset password</Button>
        </div>
      ),
    },
  ];

  return (
    <div className="space-y-4">
      <PageHeader title="Users" sub="Only the Owner can manage users"
        action={<Button onClick={() => setCreating(true)}><Plus className="h-4 w-4" /> Add User</Button>} />
      <DataTable columns={columns} rows={rows} keyOf={(u) => u.id} empty="No users." />

      <Modal open={creating} onClose={() => setCreating(false)} title="Add User">
        <div className="space-y-4">
          <Input label="Username *" value={username} onChange={(e) => setUsername(e.target.value)} />
          <Input label="Full name" value={fullName} onChange={(e) => setFullName(e.target.value)} />
          <Input label="Password *" type="password" value={password} onChange={(e) => setPassword(e.target.value)} />
          <Select label="Role" value={role} onChange={(e) => setRole(e.target.value as Role)}>
            <option value="OWNER">Owner</option>
            <option value="MANAGER">Manager</option>
            <option value="CASHIER">Cashier</option>
          </Select>
          <div className="flex justify-end gap-2">
            <Button variant="secondary" onClick={() => setCreating(false)}>Cancel</Button>
            <Button loading={saving} onClick={createUser}>Create</Button>
          </div>
        </div>
      </Modal>

      <Modal open={!!resetting} onClose={() => setResetting(null)} title={`Reset password — ${resetting?.username ?? ""}`}>
        <div className="space-y-4">
          <Input label="New password" type="password" value={newPassword}
            onChange={(e) => setNewPassword(e.target.value)} />
          <div className="flex justify-end gap-2">
            <Button variant="secondary" onClick={() => setResetting(null)}>Cancel</Button>
            <Button disabled={newPassword.length < 6} onClick={resetPassword}>Reset</Button>
          </div>
        </div>
      </Modal>
    </div>
  );
}
```

## frontend/src/pages/SettingsPage.tsx

```tsx
import { useCallback, useEffect, useState } from "react";
import { Button } from "../components/ui/Button";
import { ConfirmDialog } from "../components/ui/ConfirmDialog";
import { DataTable, type Column } from "../components/ui/DataTable";
import { Input } from "../components/ui/Input";
import { PageHeader } from "../components/ui/PageHeader";
import { backupsApi, settingsApi } from "../services/settings";
import { toast } from "../store/toast";
import type { Backup, ShopSettings } from "../types";
import { formatBytes, formatDateTime } from "../utils/format";

export function SettingsPage() {
  const [settings, setSettings] = useState<ShopSettings | null>(null);
  const [backups, setBackups] = useState<Backup[]>([]);
  const [confirmRestore, setConfirmRestore] = useState<Backup | null>(null);
  const [saving, setSaving] = useState(false);

  const loadSettings = useCallback(async () => {
    try {
      setSettings(await settingsApi.get());
    } catch (e) {
      toast.error((e as Error).message);
    }
  }, []);

  const loadBackups = useCallback(async () => {
    try {
      setBackups(await backupsApi.list());
    } catch (e) {
      toast.error((e as Error).message);
    }
  }, []);

  useEffect(() => {
    loadSettings();
    loadBackups();
  }, [loadSettings, loadBackups]);

  async function saveSettings() {
    if (!settings) return;
    setSaving(true);
    try {
      await settingsApi.update(settings);
      toast.success("Settings saved — they appear on new invoices");
      loadSettings();
    } catch (e) {
      toast.error((e as Error).message);
    } finally {
      setSaving(false);
    }
  }

  async function createBackup() {
    try {
      const b = await backupsApi.create();
      toast.success(`Backup created & verified: ${b.filename}`);
      loadBackups();
    } catch (e) {
      toast.error((e as Error).message);
    }
  }

  async function restore() {
    if (!confirmRestore) return;
    try {
      const r = await backupsApi.restore(confirmRestore.filename);
      toast.success(r.message);
      setConfirmRestore(null);
    } catch (e) {
      toast.error((e as Error).message);
    }
  }

  const backupColumns: Column<Backup>[] = [
    { key: "filename", header: "Filename" },
    { key: "size", header: "Size", render: (b) => formatBytes(b.size) },
    { key: "created_at", header: "Created", render: (b) => formatDateTime(b.created_at) },
    {
      key: "actions", header: "",
      render: (b) => (
        <div className="flex justify-end">
          <Button variant="danger" onClick={() => setConfirmRestore(b)}>Restore</Button>
        </div>
      ),
    },
  ];

  return (
    <div className="max-w-3xl space-y-8">
      <PageHeader title="Settings" sub="Shop profile used on invoices and receipts" />

      {settings && (
        <div className="grid grid-cols-2 gap-4 rounded-xl border border-slate-200 bg-white p-5">
          <Input label="Shop name" value={settings.shop_name}
            onChange={(e) => setSettings({ ...settings, shop_name: e.target.value })} />
          <Input label="Phone" value={settings.shop_phone ?? ""}
            onChange={(e) => setSettings({ ...settings, shop_phone: e.target.value })} />
          <Input label="Address" value={settings.shop_address ?? ""}
            onChange={(e) => setSettings({ ...settings, shop_address: e.target.value })} />
          <Input label="GSTIN" value={settings.shop_gstin ?? ""}
            onChange={(e) => setSettings({ ...settings, shop_gstin: e.target.value })} />
          <Input label="Currency" value={settings.currency}
            onChange={(e) => setSettings({ ...settings, currency: e.target.value })} />
          <Input label="Default tax rate (%)" type="number" step="0.01" value={settings.default_tax_rate}
            onChange={(e) => setSettings({ ...settings, default_tax_rate: Number(e.target.value) })} />
          <div className="col-span-2">
            <Input label="Invoice footer" value={settings.invoice_footer ?? ""}
              onChange={(e) => setSettings({ ...settings, invoice_footer: e.target.value })} />
          </div>
          <div className="col-span-2 flex justify-end">
            <Button loading={saving} onClick={saveSettings}>Save settings</Button>
          </div>
        </div>
      )}

      <div className="space-y-4">
        <PageHeader title="Backups" sub="Verified snapshots. Copy the backups folder to a USB drive regularly."
          action={<Button onClick={createBackup}>Back up now</Button>} />
        <DataTable columns={backupColumns} rows={backups} keyOf={(b) => b.filename} empty="No backups yet." />
        <p className="text-xs text-slate-400">
          Backups are created automatically once a day at startup. Restoring replaces all current data —
          a safety backup is taken automatically first.
        </p>
      </div>

      <ConfirmDialog
        open={!!confirmRestore}
        title="Restore backup?"
        message={`Restore "${confirmRestore?.filename}"? All current data will be replaced by this backup. A safety backup of the current state is created first. You must restart the app afterwards.`}
        confirmLabel="Restore"
        danger
        onConfirm={restore}
        onClose={() => setConfirmRestore(null)}
      />
    </div>
  );
}
```

## frontend/src/components/ui/SimpleBarChart.tsx

```tsx
interface Point {
  date: string;
  value: number;
}

export function SimpleBarChart({
  title,
  data,
  tone = "green",
}: {
  title: string;
  data: Point[];
  tone?: "green" | "red";
}) {
  const max = Math.max(...data.map((d) => d.value), 1);
  const color = tone === "green" ? "bg-emerald-500" : "bg-rose-500";
  return (
    <div className="rounded-xl border border-slate-200 bg-white p-4">
      <h3 className="mb-3 text-sm font-semibold text-slate-700">{title}</h3>
      <div className="flex h-32 items-end gap-1">
        {data.map((d) => (
          <div key={d.date} className="group relative flex-1">
            <div
              className={`${color} rounded-t transition-all hover:opacity-80`}
              style={{ height: `${Math.max((d.value / max) * 100, 2)}%` }}
              title={`${d.date}: ${d.value}`}
            />
          </div>
        ))}
      </div>
      <div className="mt-1 flex justify-between text-[10px] text-slate-400">
        <span>{data[0]?.date.slice(5)}</span>
        <span>{data[data.length - 1]?.date.slice(5)}</span>
      </div>
    </div>
  );
}
```

## frontend/src/test/setup.ts

```ts
import "@testing-library/jest-dom";
```

> **DataTable keyOf note:** the reference implementation uses `keyOf: (row, index)`; update the `DataTable` component signature to `keyOf: (row: T, index: number) => string | number` and use `keyOf(row, i)` in the map — then `ReportsPage`'s `keyOf={(r, i) => `${i}`}` works as written. This is the one intentional one-line deviation noted in the phases.

---

> *Continue to the desktop shell, scripts, and root files — part 4 of the code reference.*
## desktop/src-tauri/Cargo.toml

```toml
[package]
name = "local-retail-manager"
version = "1.0.0"
description = "Local Retail Manager - offline-first billing and retail management"
authors = ["You"]
edition = "2021"

[lib]
name = "local_retail_manager_lib"
crate-type = ["staticlib", "cdylib", "rlib"]

[build-dependencies]
tauri-build = { version = "2", features = [] }

[dependencies]
tauri = { version = "2", features = [] }
tauri-plugin-shell = "2"
serde = { version = "1", features = ["derive"] }
serde_json = "1"
```

> The `tauri-plugin-shell` crate is what gives us the ability to spawn the
> Python backend executable (the sidecar) from Rust. The JavaScript side uses
> the `@tauri-apps/plugin-shell` npm package; this Rust crate must be present
> for the plugin to work.

## desktop/src-tauri/build.rs

```rust
fn main() {
    tauri_build::build()
}
```

This tiny build script is required by Tauri — it generates the context for
`tauri::generate_context!` at compile time.

## desktop/src-tauri/tauri.conf.json

```json
{
  "$schema": "https://schema.tauri.app/config/2",
  "productName": "Local Retail Manager",
  "version": "1.0.0",
  "identifier": "com.localretail.manager",
  "build": {
    "beforeDevCommand": "npm run dev --prefix ../frontend",
    "devUrl": "http://localhost:1420",
    "beforeBuildCommand": "npm run build --prefix ../frontend",
    "frontendDist": "../frontend/dist"
  },
  "app": {
    "windows": [
      {
        "title": "Local Retail Manager",
        "width": 1280,
        "height": 800,
        "minWidth": 1024,
        "minHeight": 700,
        "resizable": true,
        "center": true
      }
    ],
    "security": {
      "csp": null
    }
  },
  "bundle": {
    "active": true,
    "targets": ["nsis"],
    "icon": [
      "icons/32x32.png",
      "icons/128x128.png",
      "icons/128x128@2x.png",
      "icons/icon.ico"
    ],
    "externalBin": ["binaries/local-retail-backend"]
  }
}
```

Key points:

* `externalBin` tells Tauri that `local-retail-backend` (the PyInstaller exe)
  must be bundled **as a sidecar**. Tauri appends the target triple at build
  time, so your file must be named exactly `local-retail-backend-x86_64-pc-windows-msvc.exe`
  inside `desktop/src-tauri/binaries/`.
* `beforeDevCommand` builds and serves the React app on port **1420** during
  development. The React Vite config must match this port (see below).
* `targets: ["nsis"]` produces a Windows installer `.exe`.
* During development the backend is still started manually with `uvicorn`;
  the sidecar is only used in the packaged app. This is intentional — see
  the note at the end of this file.

## desktop/src-tauri/src/main.rs

```rust
// Prevents an extra console window on Windows in release builds.
#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

fn main() {
    local_retail_manager_lib::run()
}
```

This is the binary entry point. It delegates to the library crate so the same
code can be used by both `tauri dev` and integration tests.

## desktop/src-tauri/src/lib.rs

```rust
use serde::Serialize;
use std::env;
use std::fs;
use std::path::PathBuf;
use std::process::{Child, Command};
use std::sync::Mutex;
use tauri::Manager;
use tauri_plugin_shell::process::CommandEvent;
use tauri_plugin_shell::ShellExt;

/// Shared handle to the running backend process.
struct BackendProcess(Mutex<Option<Child>>);

#[derive(Serialize)]
struct BackendStatus {
    running: bool,
    url: String,
    log_file: String,
}

fn app_data_dir(app: &tauri::AppHandle) -> PathBuf {
    // e.g. C:\Users\<you>\AppData\Roaming\com.localretail.manager
    app.path().app_data_dir().expect("app data dir")
}

fn resolve_backend_exe(app: &tauri::AppHandle) -> Option<PathBuf> {
    // Try the app data dir first (where we copy the sidecar on first run),
    // then fall back to the bundled sidecar path.
    let candidates = [
        app_data_dir(app).join("backend").join("local-retail-backend.exe"),
        app.path()
            .resolve("binaries/local-retail-backend", tauri::path::BaseDirectory::Resource)
            .ok()
            .map(|p| p.with_extension("exe"))
            .flatten(),
    ];
    candidates.into_iter().find(|p| p.exists())
}

#[tauri::command]
fn backend_status(app: tauri::AppHandle, state: tauri::State<BackendProcess>) -> BackendStatus {
    let running = state.0.lock().unwrap().is_some();
    BackendStatus {
        running,
        url: "http://127.0.0.1:8765".into(),
        log_file: app_data_dir(&app).join("logs").join("backend.log").to_string_lossy().into(),
    }
}

#[tauri::command]
fn start_backend(app: tauri::AppHandle, state: tauri::State<BackendProcess>) -> Result<BackendStatus, String> {
    // 1. Already running? Then do nothing.
    if state.0.lock().unwrap().is_some() {
        return Ok(backend_status(app, state));
    }

    // 2. Locate the bundled executable.
    let exe = resolve_backend_exe(&app).ok_or_else(|| {
        "Backend executable not found. Run scripts/build-backend.bat first.".to_string()
    })?;

    // 3. Prepare the data directory (database, invoices, logs, backups).
    let data_dir = app_data_dir(&app).join("data");
    let logs_dir = app_data_dir(&app).join("logs");
    fs::create_dir_all(&data_dir).map_err(|e| e.to_string())?;
    fs::create_dir_all(&logs_dir).map_err(|e| e.to_string())?;

    // 4. Start the backend as a child process with the data directory passed
    //    as an environment variable. The backend reads this at startup.
    let log_file = logs_dir.join("backend.log");
    let log = fs::OpenOptions::new()
        .create(true)
        .append(true)
        .open(&log_file)
        .map_err(|e| e.to_string())?;
    let log_clone = log.try_clone().map_err(|e| e.to_string())?;

    let child = Command::new(&exe)
        .env("LRM_DATA_DIR", &data_dir)
        .env("LRM_HOST", "127.0.0.1")
        .env("LRM_PORT", "8765")
        .stdout(std::process::Stdio::from(log))
        .stderr(std::process::Stdio::from(log_clone))
        .spawn()
        .map_err(|e| format!("Failed to start backend: {e}"))?;

    *state.0.lock().unwrap() = Some(child);
    Ok(backend_status(app, state))
}

#[tauri::command]
fn stop_backend(app: tauri::AppHandle, state: tauri::State<BackendProcess>) -> Result<BackendStatus, String> {
    if let Some(mut child) = state.0.lock().unwrap().take() {
        let _ = child.kill();
        let _ = child.wait();
    }
    Ok(backend_status(app, state))
}

#[tauri::command]
fn open_invoices_folder(app: tauri::AppHandle) -> Result<String, String> {
    let dir = app_data_dir(&app).join("data").join("invoices");
    fs::create_dir_all(&dir).map_err(|e| e.to_string())?;
    Command::new("explorer").arg(&dir).spawn().map_err(|e| e.to_string())?;
    Ok(dir.to_string_lossy().into())
}

#[cfg_attr(mobile, tauri::mobile_entry_point)]
pub fn run() {
    tauri::Builder::default()
        .plugin(tauri_plugin_shell::init())
        .manage(BackendProcess(Mutex::new(None)))
        .invoke_handler(tauri::generate_handler![
            backend_status,
            start_backend,
            stop_backend,
            open_invoices_folder
        ])
        .setup(|app| {
            // Optional: auto-start the backend when the app opens.
            let handle = app.handle().clone();
            std::thread::spawn(move || {
                std::thread::sleep(std::time::Duration::from_secs(1));
                let _ = handle.emit("backend:starting", ());
                // give the user-visible window a moment, then start backend
                let _ = tauri::AppHandle::run_on_main_thread(
                    handle.clone(),
                    move || {
                        let _ = start_backend(
                            handle.clone(),
                            handle.state::<BackendProcess>(),
                        );
                    },
                );
            });
            Ok(())
        })
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
```

> **Why `emit` is unused above:** the `backend:starting` event is an example
> of how the Rust side can push events to the frontend (e.g. to show a
> "Starting backend..." splash). In a minimal app you can simply poll
> `backend_status` from the frontend instead — which is what our React code
> in `frontend/src/desktop/backend.ts` does.

## desktop/src-tauri/capabilities/default.json

```json
{
  "$schema": "../gen/schemas/desktop-schema.json",
  "identifier": "default",
  "description": "Capabilities for the main window",
  "windows": ["main"],
  "permissions": [
    "core:default",
    "shell:allow-open",
    "shell:allow-execute"
  ]
}
```

In Tauri 2, capabilities are **mandatory**: without `shell:allow-execute`, the
`Command.sidecar()` call from JavaScript would fail at runtime with a
permission error, even though the plugin is installed.

## scripts/start-dev.bat

```bat
@echo off
REM Start the FastAPI backend and the Vite frontend together (development).
cd /d "%~dp0.."

REM Backend
start "LRM Backend" cmd /k "cd backend && .venv\Scripts\activate && uvicorn app.main:app --host 127.0.0.1 --port 8000 --reload"

REM Frontend
start "LRM Frontend" cmd /k "cd frontend && npm run dev"

echo.
echo Both processes started in separate windows.
echo Backend:  http://127.0.0.1:8000  (API docs at /docs)
echo Frontend: http://localhost:5173
```

## scripts/build-backend.bat

```bat
@echo off
REM Build the backend into a standalone Windows executable with PyInstaller.
cd /d "%~dp0..\backend"

call .venv\Scripts\activate
pip install -r requirements.txt pyinstaller

REM --onedir is recommended: faster startup, fewer AV false positives.
pyinstaller ^
  --name local-retail-backend ^
  --onedir ^
  --noconfirm ^
  --clean ^
  --hidden-import uvicorn.logging ^
  --hidden-import uvicorn.loops ^
  --hidden-import uvicorn.loops.auto ^
  --hidden-import uvicorn.protocols ^
  --hidden-import uvicorn.protocols.http ^
  --hidden-import uvicorn.protocols.http.auto ^
  --hidden-import uvicorn.protocols.websockets ^
  --hidden-import uvicorn.protocols.websockets.auto ^
  --hidden-import uvicorn.lifespan ^
  --hidden-import uvicorn.lifespan.on ^
  --hidden-import sqlalchemy.dialects.sqlite ^
  --hidden-import pydantic ^
  --hidden-import pydantic_settings ^
  --hidden-import alembic.config ^
  --hidden-import alembic.runtime.migration ^
  --hidden-import reportlab ^
  --collect-all reportlab ^
  --add-data "alembic;alembic" ^
  scripts\run_backend.py

echo.
echo Build complete. Copy the exe into the Tauri sidecar folder:
echo   copy dist\local-retail-backend\local-retail-backend.exe ..\desktop\src-tauri\binaries\local-retail-backend-x86_64-pc-windows-msvc.exe
```

> `--collect-all reportlab` is important: ReportLab ships data files and
> fonts that PyInstaller does not always find automatically.

## scripts/run_backend.py

```python
"""Entry point used by PyInstaller.

The packaged exe cannot run `uvicorn app.main:app` directly because PyInstaller
does not know which module to import first. This thin script imports the app
and starts uvicorn programmatically. It also reads the data directory from the
LRM_DATA_DIR environment variable set by the Tauri shell.
"""

import os
import sys
from pathlib import Path

# The data directory comes from the desktop shell. In development it defaults
# to the project's data/ folder.
data_dir = Path(os.environ.get("LRM_DATA_DIR", str(Path(__file__).resolve().parent.parent / "data")))

# Make the data directory available to the app before anything imports it.
os.environ["LRM_DATA_DIR"] = str(data_dir)
os.environ.setdefault("LRM_HOST", "127.0.0.1")
os.environ.setdefault("LRM_PORT", "8765")

# When frozen, PyInstaller unpacks everything into sys._MEIPASS.
if hasattr(sys, "_MEIPASS"):
    sys.path.insert(0, str(Path(sys._MEIPASS)))

import uvicorn

from app.core.config import get_settings  # noqa: E402
from app.main import app  # noqa: E402


def main() -> None:
    settings = get_settings()
    # Override the database path so it always points into the app data dir.
    os.environ["LRM_DB_PATH"] = str(data_dir / "database" / settings.db_name)
    uvicorn.run(app, host=settings.host, port=settings.port, log_level="info")


if __name__ == "__main__":
    main()
```

## scripts/build-desktop.bat

```bat
@echo off
REM Full production build: backend exe -> Tauri sidecar -> NSIS installer.
cd /d "%~dp0.."

call scripts\build-backend.bat

echo Building frontend...
cd frontend
call npm run build
cd ..

echo Building Tauri app...
cd desktop
call npm install
call npm run tauri build
cd ..

echo.
echo Done. Installer created at:
echo   desktop\src-tauri\target\release\bundle\nsis\Local Retail Manager_1.0.0_x64-setup.exe
```

## scripts/make-backup.bat

```bat
@echo off
REM Manual backup trigger. The app also does automatic daily backups.
cd /d "%~dp0.."
curl -s -X POST http://127.0.0.1:8000/api/backups/now -H "Content-Type: application/json" -d "{}"
echo.
echo Backup request sent.
```

## scripts/restore-backup.bat

```bat
@echo off
REM Restore from a backup file. Pass the backup filename:
REM   scripts\restore-backup.bat backups\backup_2026-08-08_120000.zip
cd /d "%~dp0.."
curl -s -X POST http://127.0.0.1:8000/api/backups/restore -H "Content-Type: application/json" -d "{\"backup_file\":\"%~1\"}"
echo.
```

## scripts/setup.bat (one-time developer setup)

```bat
@echo off
REM One-time project setup for a new developer machine.
cd /d "%~dp0.."

echo [1/4] Backend virtual environment...
cd backend
python -m venv .venv
call .venv\Scripts\activate
pip install --upgrade pip
pip install -r requirements.txt
pip install -r requirements-dev.txt
cd ..

echo [2/4] Frontend dependencies...
cd frontend
call npm install
cd ..

echo [3/4] Database migration...
cd backend
call .venv\Scripts\activate
alembic upgrade head
cd ..

echo [4/4] Done.
echo.
echo Run  scripts\start-dev.bat  to start the app in development.
```

---

## Wrapping Up

You have now built, tested, and packaged **Local Retail Manager** — a complete
offline-first retail management desktop application. Take a moment to
appreciate what you actually built:

| Layer | What you built |
|---|---|
| Backend | FastAPI + SQLAlchemy 2.x + SQLite, layered architecture (routes → services → models) |
| Business logic | Inventory ledger, atomic billing transactions, Khata credit, profit calculation |
| Frontend | React + TypeScript + Vite + Tailwind, POS-optimized billing screen |
| Desktop | Tauri 2 shell that manages a PyInstaller sidecar backend |
| Data safety | Backup/restore, logging, transactions, audit-friendly movements |
| Quality | Pytest suite, unit + integration tests, error handling |

**The most important skills you now have:**

1. **You can reason about data flow** — from a keystroke in React, through an
   API, into a transaction, and back out as a PDF. When something breaks, you
   know where to look.
2. **You know why the architecture exists** — the service layer, the ledger,
   the transactions are not ceremony; each one exists to prevent a specific
   class of bug (mixing business logic into routes, silent stock corruption,
   half-completed sales).
3. **You can extend it** — every advanced feature in Phase 26 and 27 slots
   into a place you already understand.

### ✅ Final Checkpoint

* [ ] `scripts/start-dev.bat` runs both backend and frontend
* [ ] You can add a product, make a sale, and see stock decrease
* [ ] A PDF invoice opens from the invoice page
* [ ] A backup file appears in `data/backups/`
* [ ] `npm run tauri build` produces an installer
* [ ] The installer installs and the app starts with the backend embedded

### If something still doesn't work

Return to the [Troubleshooting Guide](#troubleshooting-guide). Every problem
in this project has been seen by someone before — the cause is almost always
one of:

1. A version mismatch (re-read Section 1.2, the version table).
2. A forgotten migration (`alembic upgrade head`).
3. A stale frontend build (delete `frontend/dist` and rebuild).
4. A CORS or port mismatch between frontend and backend.
5. The Tauri capability file missing a permission.

### A final word

Software like this is how real shops run. The version you built here is not a
toy — it is a genuine, production-shaped system. When you extend it, keep the
rules that carried you through this guide:

> **Never modify inventory without recording why.**
> **Never trust the frontend for authorization.**
> **Never let a sale finish without its inventory movement.**
> **Teach the next person (including future you) why the code is shaped the way it is.**

Good luck, and happy billing. 🧾

---

*End of Local Retail Manager — Complete Development Guide.*
