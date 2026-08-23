# SQLAlchemy 2.x Learning Guide

A beginner-friendly, hands-on tutorial to **SQLAlchemy** — the de facto Python SQL toolkit and Object Relational Mapper (ORM). It assumes you know basic Python but have little or no experience with SQLAlchemy. Everything uses the modern **SQLAlchemy 2.x** API and best practices.

## Table of Contents

1. [Introduction](#1-introduction)
2. [Prerequisites and Setup](#2-prerequisites-and-setup)
3. [SQLAlchemy Core](#3-sqlalchemy-core)
4. [SQLAlchemy ORM](#4-sqlalchemy-orm)
5. [Relationships](#5-relationships)
6. [Queries](#6-queries)
7. [Practical Application: A Blog Database](#7-practical-application-a-blog-database)
8. [Database Migrations with Alembic](#8-database-migrations-with-alembic)
9. [Best Practices](#9-best-practices)
10. [Common Mistakes](#10-common-mistakes)
11. [SQLAlchemy 2.x Cheat Sheet](#11-sqlalchemy-2x-cheat-sheet)
12. [Exercises](#12-exercises)
13. [Exercise Solutions](#13-exercise-solutions)

---

## 1. Introduction

### What is SQLAlchemy?

SQLAlchemy is a Python library for working with relational databases. It has two distinct halves that can be used together or on their own:

- **SQLAlchemy Core** — a Pythonic way to write SQL. You describe tables as Python objects and compose statements (`select`, `insert`, `update`, `delete`) as Python expressions that get compiled into real SQL.
- **SQLAlchemy ORM** — an Object Relational Mapper. It maps Python classes (models) to database tables, so a Python object such as `user.name` becomes a row in a `users` table, and you can query with `select(User).where(User.name == "alice")` instead of writing SQL strings by hand.

### Why use SQLAlchemy?

| Problem it solves | How SQLAlchemy helps |
| --- | --- |
| Writing repetitive, error-prone SQL by hand | Compose queries in Python; SQL is generated for you |
| Locking your app to one database | The same code runs on SQLite, PostgreSQL, MySQL, and more — you just swap the connection URL |
| SQL injection | Statements use bound parameters automatically (never string concatenation) |
| Object-relational impedance mismatch | Query results come back as Python objects, not raw tuples |
| Evolving your schema | Works with **Alembic**, the standard migration tool, for versioned schema changes |
| Type safety | The 2.x API plays nicely with type hints and static type checkers |

### SQLAlchemy Core vs. SQLAlchemy ORM

Think of Core as "SQL with nicer syntax" and the ORM as "your Python objects are the database."

| | SQLAlchemy Core | SQLAlchemy ORM |
| --- | --- | --- |
| Building block | `Table` objects and `Connection` | Mapped Python classes and `Session` |
| Style | SQL expression language | Declarative models + unit-of-work session |
| Query result | Rows / mappings | Python objects (with identity map) |
| Best for | Raw SQL needs, bulk operations, reporting, libraries | Application business logic that manipulates objects |
| Learning curve | Moderate | Moderate (different concepts, similar effort) |
| Can they mix? | Yes — the ORM is built on top of Core | Yes — you can drop to Core within an ORM session |

Both styles are covered in this guide. The ORM section builds on Core concepts, so read the Core section first even if you plan to use the ORM day to day.

### About SQLAlchemy 2.x

SQLAlchemy 2.0 (released January 2023) is a major modernization of the API. If you search the web you will still find plenty of **1.x** tutorials using patterns like `session.query(User).filter(...)`. Those patterns still work in 2.x but are considered legacy and are being removed. **This guide only teaches 2.x idioms:**

- `select(User)` instead of `session.query(User)`
- `session.scalars(select(User))` instead of `session.query(User).all()`
- `Mapped` / `mapped_column()` declarative models (introduced in 1.4, the standard in 2.0)
- `session.get(User, id)` instead of the old `session.query(User).get(id)`

The [Common Mistakes](#10-common-mistakes) section explains what changed and why.

---

## 2. Prerequisites and Setup

### Required Python version

- SQLAlchemy 2.x requires **Python 3.7+**, but use **Python 3.10 or newer** — the examples in this guide use modern type-hint syntax like `str | None` that requires 3.10+.
- You will need `pip` (bundled with Python).

Check your version:

```bash
python --version
```

### Create a virtual environment

Always isolate project dependencies in a virtual environment:

```bash
python -m venv .venv
```

Activate it:

```bash
# macOS / Linux
source .venv/bin/activate
```

```bash
# Windows (Git Bash, PowerShell, or cmd all work with this form)
source .venv/Scripts/activate
```

> **Note:** If you use plain Windows PowerShell you can also activate with `.venv\Scripts\Activate.ps1`; in cmd it is `.venv\Scripts\activate.bat`. If `source .venv/Scripts/activate` fails in your shell, use the appropriate one above.

Your prompt should now show `(.venv)`.

### Install SQLAlchemy

```bash
pip install "sqlalchemy>=2.0"
```

Verify the installation and version:

```bash
python -c "import sqlalchemy; print(sqlalchemy.__version__)"
```

You should see something like:

```text
2.0.36
```

> **Important:** Some older tutorials install `sqlalchemy` and get a 1.x version. If your version prints something like `1.4.x`, upgrade with `pip install -U "sqlalchemy>=2.0"` — this guide targets 2.x.

### Database drivers

SQLAlchemy is database-agnostic; it talks to each database through a *dialect* plus a DBAPI driver.

| Database | Driver to install | Example connection URL |
| --- | --- | --- |
| SQLite | none (bundled with Python) | `sqlite+pysqlite:///blog.db` |
| PostgreSQL | `psycopg[binary]` (psycopg 3, recommended) or `psycopg2-binary` | `postgresql+psycopg://user:pass@localhost:5432/blog` |
| MySQL / MariaDB | `pymysql` | `mysql+pymysql://user:pass@localhost:3306/blog` |

```bash
# For PostgreSQL (pick one driver):
pip install "psycopg[binary]"

# For MySQL / MariaDB:
pip install pymysql
```

This guide's examples run on **SQLite**, which needs no driver and stores everything in a single file — perfect for learning. Everything shown also runs on PostgreSQL/MySQL with only the connection URL changed.

Create a `requirements.txt` for the project:

```text
sqlalchemy>=2.0
alembic>=1.13
psycopg[binary]          # only needed if you use PostgreSQL
```

Install from it with `pip install -r requirements.txt`.

---

## 3. SQLAlchemy Core

In this section we work with the database directly: engines, connections, tables, and SQL statements built with Python expressions. This is "SQL with better syntax and total safety."

All examples in this section use a single database file, `core_demo.db`. To reset the database so outputs match this guide, delete the file first:

```bash
rm core_demo.db
```

### 3.1 Engine and database connections

An **Engine** is the starting point: it knows how to reach your database and manages connections (a connection pool under the hood).

```python
from sqlalchemy import create_engine

# sqlite+pysqlite:///  ->  SQLite database in the file core_demo.db
# echo=True            ->  print every SQL statement to the console
engine = create_engine("sqlite+pysqlite:///core_demo.db", echo=True)

print(engine)
```

```text
Engine(sqlite+pysqlite:///core_demo.db)
```

**Nothing has touched the database yet** — `create_engine()` is lazy. The engine opens a connection the first time you actually run a statement.

There are two idiomatic ways to work with a `Connection`:

```python
# 1) engine.connect() — you must commit/rollback explicitly
with engine.connect() as conn:
    conn.execute(...)
    conn.commit()   # required if you made changes

# 2) engine.begin() — commits on success, rolls back on error, automatically
with engine.begin() as conn:
    conn.execute(...)   # no explicit commit needed
```

We will see both in action below.

### 3.2 Metadata and tables

**Metadata** is a catalog of the tables SQLAlchemy knows about. **Table** objects describe columns and constraints:

```python
from sqlalchemy import Boolean, Column, Integer, MetaData, String, Table

metadata = MetaData()

users = Table(
    "users",              # table name (singular is a common convention)
    metadata,             # register this table in the metadata catalog
    Column("id", Integer, primary_key=True),
    Column("name", String(50), nullable=False),
    Column("email", String(100), nullable=False, unique=True),
    Column("age", Integer, nullable=False),
    Column("is_active", Boolean, nullable=False, default=True),
)
```

Note the syntax: `Table(name, metadata, columns...)`.

### 3.3 Columns and data types

| SQLAlchemy type | Python type | Notes |
| --- | --- | --- |
| `Integer` | `int` | Auto-incrementing primary keys by default |
| `String(n)` | `str` | Variable-length text; `n` is optional |
| `Text` | `str` | Unlimited-length text (good for bodies/content) |
| `Boolean` | `bool` | |
| `DateTime` | `datetime.datetime` | Date + time |
| `Date` | `datetime.date` | Date only |
| `Float` | `float` | |
| `Numeric(p, s)` | `decimal.Decimal` | Exact decimals — use for money |
| `ForeignKey("table.column")` | — | References another table (used with `Integer`, etc.) |

Common `Column` options:

| Option | Meaning |
| --- | --- |
| `primary_key=True` | Part of the primary key |
| `nullable=False` | NOT NULL constraint (default is `True`) |
| `unique=True` | UNIQUE constraint |
| `index=True` | Create an index on this column |
| `default=<value or callable>` | Python-side default applied when inserting |
| `server_default=<SQL text>` | Default applied *by the database* (e.g. `server_default=text("CURRENT_TIMESTAMP")`) |

### 3.4 Creating tables

```python
# Creates all tables in metadata that don't exist yet.
# Safe to call repeatedly — it checks first (checkfirst=True by default).
metadata.create_all(engine)
```

With `echo=True` you will see the generated SQL:

```text
INFO sqlalchemy.engine.Engine
CREATE TABLE users (
        id INTEGER NOT NULL,
        name VARCHAR(50) NOT NULL,
        email VARCHAR(100) NOT NULL,
        age INTEGER NOT NULL,
        is_active BOOLEAN NOT NULL,
        PRIMARY KEY (id),
        UNIQUE (email)
)
INFO sqlalchemy.engine.Engine COMMIT
```

Notice that SQLAlchemy translated our Python definitions into real `CREATE TABLE` SQL — including the `UNIQUE` constraint on `email`.

> **Note on generated SQL:** SQLAlchemy does not quote you out of writing SQL; it *generates* it for you. Every statement below can be inspected, which is great for debugging and for understanding what the ORM does later.

### 3.5 Inserting data

Use `insert()` with `.values()`:

```python
from sqlalchemy import insert

with engine.begin() as conn:
    result = conn.execute(
        insert(users).values(
            [
                {"name": "Alice", "email": "alice@example.com", "age": 30},
                {"name": "Bob", "email": "bob@example.com", "age": 25},
                {"name": "Carol", "email": "carol@example.com", "age": 35},
                {"name": "Dave", "email": "dave@example.com", "age": 28},
            ]
        )
    )
    print("Inserted rows:", result.rowcount)
```

```text
Inserted rows: 4
```

A single row insert lets you read back the generated primary key:

```python
with engine.begin() as conn:
    result = conn.execute(
        insert(users).values(name="Eve", email="eve@example.com", age=29)
    )
    print("New user id:", result.inserted_primary_key[0])
```

```text
New user id: 5
```

> **Note:** `is_active` was not provided, so SQLAlchemy applied the Python-side `default=True`. SQLite is the only common database where auto-incrementing primary keys are this predictable (1, 2, 3...); other databases are fine with it too but don't rely on exact numbers in production code.

### 3.6 Selecting and filtering data

```python
from sqlalchemy import select

with engine.connect() as conn:
    result = conn.execute(select(users))     # SELECT * FROM users
    for row in result:
        print(row)
```

```text
(1, 'Alice', 'alice@example.com', 30, True)
(2, 'Bob', 'bob@example.com', 25, True)
(3, 'Carol', 'carol@example.com', 35, True)
(4, 'Dave', 'dave@example.com', 28, True)
(5, 'Eve', 'eve@example.com', 29, True)
```

Filter with `.where()` (which you can chain). Access row values either positionally (`row[1]`), by name (`row.name`), or as a mapping:

```python
with engine.connect() as conn:
    # Column attributes live on the table object: users.c.age
    rows = conn.execute(
        select(users).where(users.c.age >= 28)
    ).all()
    for row in rows:
        print(row.name, row.age)
```

```text
Alice 30
Carol 35
Dave 28
```

```python
with engine.connect() as conn:
    # .mappings() yields dict-like rows: row["name"]
    for mapping in conn.execute(
        select(users).where(users.c.name == "Alice")
    ).mappings():
        print(mapping["name"], mapping["email"])
```

```text
Alice alice@example.com
```

A few more useful filters:

```python
from sqlalchemy import or_

with engine.connect() as conn:
    # SELECT name FROM users WHERE age > 26 ORDER BY age DESC
    names = conn.execute(
        select(users.c.name).where(users.c.age > 26).order_by(users.c.age.desc())
    ).scalars().all()
    print("Over 26, oldest first:", names)

    # IN (...) and LIKE
    names = conn.execute(
        select(users.c.name).where(users.c.name.in_(["Alice", "Bob"]))
    ).scalars().all()
    print("In list:", names)

    emails = conn.execute(
        select(users.c.email).where(users.c.email.like("%@example.com"))
    ).scalars().all()
    print("example.com emails:", emails)

    # or_() combines conditions; note Python `or` does NOT work here
    names = conn.execute(
        select(users.c.name).where(or_(users.c.age < 26, users.c.age > 34))
    ).scalars().all()
    print("Younger than 26 or older than 34:", names)
```

```text
Over 26, oldest first: ['Carol', 'Alice', 'Eve', 'Dave']
In list: ['Alice', 'Bob']
example.com emails: ['alice@example.com', 'bob@example.com', 'carol@example.com', 'dave@example.com', 'eve@example.com']
Younger than 26 or older than 34: ['Bob', 'Carol']
```

When you expect exactly one row, use `scalar_one()` (raises if zero or more than one) or `scalar_one_or_none()`:

```python
with engine.connect() as conn:
    name = conn.execute(
        select(users.c.name).where(users.c.id == 1)
    ).scalar_one()
    print(name)
```

```text
Alice
```

### 3.7 Updating and deleting data

```python
from sqlalchemy import update

with engine.begin() as conn:
    result = conn.execute(
        update(users).where(users.c.name == "Dave").values(is_active=False)
    )
    print("Rows updated:", result.rowcount)
```

```text
Rows updated: 1
```

```python
with engine.begin() as conn:
    result = conn.execute(
        update(users).values(is_active=True)          # no WHERE -> updates ALL rows
    )
    print("Rows updated (all rows):", result.rowcount)
```

```text
Rows updated (all rows): 5
```

> **Warning:** An `update()` or `delete()` without a `where()` applies to **every row**. That's occasionally what you want, but it's a common and destructive mistake — double-check before running.

```python
from sqlalchemy import delete

with engine.begin() as conn:
    result = conn.execute(
        delete(users).where(users.c.email == "eve@example.com")
    )
    print("Rows deleted:", result.rowcount)
```

```text
Rows deleted: 1
```

After this our table holds Alice, Bob, Carol, and Dave (all with `is_active=True` again because of the blanket update above).

### 3.8 Transactions

A **transaction** groups statements so they succeed or fail together. SQLAlchemy gives you this for free: every `Connection` is inside a transaction until you `commit()` or `rollback()`.

With `engine.begin()` this is automatic — commit on success, rollback on error:

```python
with engine.begin() as conn:
    conn.execute(insert(users).values(name="Frank", email="frank@example.com", age=40))
    # If an exception is raised here, the insert is rolled back.
```

With `engine.connect()` the transaction is *implicit*: nothing is permanent until you call `conn.commit()`. If you exit the `with` block without committing, the work is **discarded**:

```python
with engine.connect() as conn:
    conn.execute(insert(users).values(name="Grace", email="grace@example.com", age=27))
    # No conn.commit()! Grace is inserted and then rolled back on exit.

with engine.connect() as conn:
    count = conn.execute(select(users.c.id)).all()
    print("Rows in table:", len(count))   # Grace is NOT there
```

```text
Rows in table: 5
```

You can also scope a transaction explicitly inside a connection:

```python
with engine.connect() as conn:
    with conn.begin():        # begin/commit (or rollback on error) a sub-transaction
        conn.execute(insert(users).values(name="Grace", email="grace@example.com", age=27))
    # Grace is committed here
```

And errors roll back automatically — here we violate the unique constraint on `email`:

```python
from sqlalchemy.exc import IntegrityError

try:
    with engine.begin() as conn:
        conn.execute(
            insert(users).values(name="Impostor", email="alice@example.com", age=99)
        )
except IntegrityError as exc:
    print("Insert failed (email already exists), transaction rolled back.")
```

```text
Insert failed (email already exists), transaction rolled back.
```

**Rule of thumb:** prefer `engine.begin()` — it makes the transaction boundary impossible to get wrong.

### 3.9 Parameterized queries

Never build SQL by concatenating strings — that is how SQL injection happens. If your input is `'; DROP TABLE users; --`, a naive f-string query turns into a disaster. SQLAlchemy always uses **bound parameters** instead:

```python
from sqlalchemy import text

user_input = "Alice"          # pretend this came from a web form

# BAD — never do this:
# conn.execute(text(f"SELECT * FROM users WHERE name = '{user_input}'"))

# GOOD — bind parameter with :name
with engine.connect() as conn:
    result = conn.execute(
        text("SELECT * FROM users WHERE name = :name"),
        {"name": user_input},               # values passed as a dict
    )
    for row in result:
        print(row.name, row.email)
```

```text
Alice alice@example.com
```

You can also attach parameters to the statement itself with `.params()`:

```python
stmt = text("SELECT * FROM users WHERE age >= :min_age").params(min_age=28)

with engine.connect() as conn:
    rows = conn.execute(stmt).all()
    print("Age >= 28:", [row.name for row in rows])
```

```text
Age >= 28: ['Alice', 'Carol', 'Dave', 'Frank']
```

> **The rule:** values go in *parameters*, never in the SQL string. Core expressions like `users.c.name == user_input` parameterize automatically, and `text()` uses `:name` placeholders. You never need to escape quotes yourself.

### 3.10 Reading the generated SQL

With `echo=True` on the engine, SQLAlchemy logs every statement. Running the parameterized query above produces output like:

```text
INFO sqlalchemy.engine.Engine SELECT users.id, users.name, users.email, users.age, users.is_active
FROM users
WHERE users.name = ?
INFO sqlalchemy.engine.Engine [generated in 0.00012s] ('Alice',)
```

Two things worth noticing:

- The `?` is a placeholder — SQLite uses `?`, PostgreSQL would show `$1`. The value `'Alice'` is sent separately by the driver, never spliced into the string. This is why SQL injection is impossible when you follow the parameter pattern.
- You can see exactly what your ORM/Core code is doing to the database, which becomes invaluable when debugging N+1 queries later.

To inspect a statement without executing it, compile it:

```python
print(select(users).where(users.c.age >= 28))
```

```text
SELECT users.id, users.name, users.email, users.age, users.is_active
FROM users
WHERE users.age >= :age_1
```

`print(stmt)` shows the statement with **unbound** parameters (`:age_1` here). When the statement is actually executed, the driver replaces it with `?` (SQLite) or `$1` (PostgreSQL) and sends the values separately.

---

## 4. SQLAlchemy ORM

The ORM maps Python classes to database tables. Instead of `Table` objects and `Connection`, you work with **models** and a **Session**. SQLAlchemy translates your object operations into SQL under the hood — you get to write Python, and it handles the database.

### 4.1 ORM concepts in one minute

- **Model / Mapped class** — a Python class whose attributes map to table columns. An instance is one row.
- **Declarative base** — the shared base class your models inherit from. Its `metadata` knows all your tables.
- **Session** — the work area. You add/attach objects to a session, and it tracks changes and flushes them to the database when you commit. A session also keeps an **identity map**: loading the same row twice gives you the *same* Python object.
- **Transaction** — just like Core, every session works inside a transaction until you `commit()` or `rollback()`.

From here on the examples build one evolving demo file, `orm_demo.py`, using the database file `orm_demo.db`. Reset it whenever you want outputs to match:

```bash
rm orm_demo.db
```

### 4.2 Defining models: `DeclarativeBase`, `Mapped`, `mapped_column`

In SQLAlchemy 2.x you subclass `DeclarativeBase` and annotate attributes with `Mapped[...]`. The annotation tells SQLAlchemy the *type* of the column; `mapped_column()` provides the details (primary key, constraints, defaults).

```python
from datetime import datetime

from sqlalchemy import String, create_engine, func
from sqlalchemy.orm import DeclarativeBase, Mapped, mapped_column, sessionmaker


class Base(DeclarativeBase):
    """Every model inherits from this."""
    pass


class User(Base):
    __tablename__ = "users"

    id: Mapped[int] = mapped_column(primary_key=True)        # auto-increment PK
    name: Mapped[str] = mapped_column(String(50), nullable=False)
    email: Mapped[str] = mapped_column(String(100), unique=True, nullable=False)
    age: Mapped[int] = mapped_column(nullable=False)
    is_active: Mapped[bool] = mapped_column(default=True)
    created_at: Mapped[datetime] = mapped_column(server_default=func.now())

    def __repr__(self) -> str:
        # Makes print(user) readable; no DB impact.
        return f"User(id={self.id!r}, name={self.name!r}, email={self.email!r})"


engine = create_engine("sqlite+pysqlite:///orm_demo.db", echo=False)
Session = sessionmaker(bind=engine)

# Create the tables that Base.metadata knows about.
Base.metadata.create_all(engine)
```

**How `Mapped[...]` maps to column types:**

| Annotation | Column type | Notes |
| --- | --- | --- |
| `Mapped[int]` | `Integer` | |
| `Mapped[str]` | `String` | no length — fine for SQLite; give it one via `mapped_column(String(50))` |
| `Mapped[bool]` | `Boolean` | |
| `Mapped[datetime]` | `DateTime` | |
| `Mapped[float]` | `Float` | |
| `Mapped[Decimal]` | `Numeric` | for money, `mapped_column(Numeric(10, 2))` |
| `Mapped[str \| None]` | `String`, nullable | the `\| None` union makes the column nullable |

**What `mapped_column()` adds:**

```python
id: Mapped[int] = mapped_column(primary_key=True)                       # PK
email: Mapped[str] = mapped_column(unique=True, nullable=False)         # constraints
age: Mapped[int] = mapped_column(index=True)                            # index
is_active: Mapped[bool] = mapped_column(default=True)                   # Python-side default
created_at: Mapped[datetime] = mapped_column(server_default=func.now()) # DB-side default
```

> **Why `Mapped`?** In 1.x you wrote `Column(String, ...)` directly. In 2.x, `Mapped[int]` (a) gives your IDE and type checker the real Python type of the attribute, and (b) lets SQLAlchemy infer the SQL column type from the annotation, so you only write `mapped_column(...)` for the *extra* details.

### 4.3 Creating tables from models

```python
Base.metadata.create_all(engine)   # creates any missing tables
```

That's it — SQLAlchemy inspected the class annotations and issued `CREATE TABLE users (...)`. (We already called it above; it's safe to call again.)

### 4.4 The `Session`

A `Session` is where you stage and commit changes. `sessionmaker` is a factory that produces session objects bound to our engine:

```python
session = Session()          # a new session
```

The three golden rules:

1. `add()` objects you create; `add_all()` for several.
2. `commit()` makes changes permanent (this also flushes pending SQL).
3. Always `close()` the session when done (context managers do this for you).

The idiomatic patterns:

```python
# Pattern A — closes the session, but does NOT auto-commit.
with Session() as session:
    session.add(User(name="Alice", email="alice@example.com", age=30))
    session.commit()

# Pattern B — commits on success, rolls back on error, closes. Preferred for writes.
with Session.begin() as session:
    session.add(User(name="Bob", email="bob@example.com", age=25))
```

> **Note:** A `Session` is *not* thread-safe and should not be shared between threads. Create one per operation or per request (web apps typically one session per HTTP request).

### 4.5 CRUD: create, read, update, delete

Let's seed a little data and walk through each operation. Reset the database first so ids match the outputs:

```bash
rm orm_demo.db
```

**Create** — add objects, then commit. The primary key is filled in automatically when the insert is flushed:

```python
with Session.begin() as session:
    session.add_all(
        [
            User(name="Alice", email="alice@example.com", age=30),
            User(name="Bob", email="bob@example.com", age=25),
            User(name="Carol", email="carol@example.com", age=35),
        ]
    )
    # session.begin() commits here automatically
```

**Read** — `select()` builds the query, `session.scalars()` executes it and returns row objects:

```python
from sqlalchemy import select

with Session() as session:
    all_users = session.scalars(select(User)).all()
    print("All:", all_users)

    adults = session.scalars(select(User).where(User.age >= 30)).all()
    print("Age >= 30:", adults)

    # Exactly one result (raises if zero or more than one)
    alice = session.scalars(select(User).where(User.name == "Alice")).one()
    print("Alice:", alice)

    # By primary key — the fast, idiomatic way
    alice_again = session.get(User, 1)
    print("Same object?", alice is alice_again)   # identity map: True

    # First result or None
    nobody = session.scalars(select(User).where(User.name == "Nobody")).first()
    print("Nobody:", nobody)
```

```text
All: [User(id=1, name='Alice', email='alice@example.com'), User(id=2, name='Bob', email='bob@example.com'), User(id=3, name='Carol', email='carol@example.com')]
Age >= 30: [User(id=1, name='Alice', email='alice@example.com'), User(id=3, name='Carol', email='carol@example.com')]
Alice: User(id=1, name='Alice', email='alice@example.com')
Same object? True
Nobody: None
```

**Update** — load the object, change an attribute, commit. The session tracks what changed (`dirty` objects) and only issues UPDATEs for those:

```python
with Session.begin() as session:
    bob = session.get(User, 2)
    bob.age = 26
    # committed automatically — SQLAlchemy detects bob.age changed

with Session() as session:
    print(session.get(User, 2))
```

```text
User(id=2, name='Bob', email='bob@example.com')
```

You can also run bulk UPDATEs directly (the ORM form of the Core `update()`), for example "deactivate everyone":

```python
from sqlalchemy import update

with Session.begin() as session:
    result = session.execute(
        update(User).where(User.age > 30).values(is_active=False)
    )
    print("Deactivated:", result.rowcount)
```

```text
Deactivated: 1
```

**Delete** — load and `session.delete()`:

```python
with Session.begin() as session:
    carol = session.get(User, 3)
    session.delete(carol)

with Session() as session:
    print("Remaining:", session.scalars(select(User)).all())
```

```text
Remaining: [User(id=1, name='Alice', email='alice@example.com'), User(id=2, name='Bob', email='bob@example.com')]
```

Bulk delete without loading objects:

```python
from sqlalchemy import delete

with Session.begin() as session:
    result = session.execute(delete(User).where(User.is_active.is_(False)))
    print("Deleted inactive users:", result.rowcount)
```

```text
Deleted inactive users: 0
```

### 4.6 Commits, rollbacks, and transaction boundaries

Understanding the session's transaction lifecycle prevents the most confusing errors:

1. **A session starts a transaction lazily** — the first time it talks to the database (insert, query, etc.).
2. **`session.flush()`** sends pending SQL to the database *inside* the transaction. `commit()` flushes first, then commits.
3. **`session.rollback()`** undoes everything since the transaction began and returns objects to their database state.
4. **After `commit()`**, by default all loaded object attributes are *expired* — SQLAlchemy reloads them from the database the next time you access them (that's why it's important to access objects while the session is open).
5. **An exception leaves the transaction in a failed state** — you must `rollback()` before the session is usable again.

```python
with Session() as session:
    session.add(User(name="Dave", email="dave@example.com", age=28))
    print("Pending (not yet in DB):", session.new)

    session.rollback()          # discard the pending insert
    print("After rollback, new:", session.new)

    print("Users in DB:", session.scalars(select(User)).all())
```

```text
Pending (not yet in DB): IdentitySet([User(id=None, name='Dave', email='dave@example.com')])
After rollback, new: IdentitySet([])
Users in DB: [User(id=1, name='Alice', email='alice@example.com'), User(id=2, name='Bob', email='bob@example.com')]
```

> **Warning:** If a statement raises (e.g. `IntegrityError`), the session's transaction is broken until you call `session.rollback()`. Using the session without rolling back first raises `InvalidRequestError: This Session's transaction has been rolled back due to a previous exception during flush.` Always roll back in an exception handler.

### 4.7 ORM vs. Core, side by side

| Task | Core | ORM |
| --- | --- | --- |
| Select all | `conn.execute(select(users))` | `session.scalars(select(User)).all()` |
| Filter | `select(users).where(users.c.age >= 30)` | `select(User).where(User.age >= 30)` |
| Insert | `insert(users).values(name="A")` | `session.add(User(name="A")); session.commit()` |
| Update | `update(users).where(...).values(...)` | modify attribute; `session.commit()` |
| Delete | `delete(users).where(...)` | `session.delete(obj); session.commit()` |

Note how similar the query syntax is — the ORM is literally built on top of Core, which is why learning Core first pays off.

---

## 5. Relationships

Relational databases link tables with **foreign keys**. In the ORM, `relationship()` turns those foreign keys into Python attributes you can navigate: `user.posts`, `post.author`, `post.tags`.

We continue the `orm_demo.py` demo. The examples below add new classes; add the new lines to your existing `User` where noted.

### 5.1 Foreign keys: the database side

A foreign key is a column that stores the primary key of another table:

```python
from sqlalchemy import ForeignKey, Text

class Post(Base):
    __tablename__ = "posts"

    id: Mapped[int] = mapped_column(primary_key=True)
    title: Mapped[str] = mapped_column(String(120), nullable=False)
    content: Mapped[str] = mapped_column(Text)
    # "users.id" -> references the id column of the users table
    user_id: Mapped[int] = mapped_column(ForeignKey("users.id"), index=True)

    def __repr__(self) -> str:
        return f"Post(id={self.id!r}, title={self.title!r})"
```

> **Convention:** `ForeignKey("users.id")` is the table name and column name *in the database* — lowercase, plural, as defined by `__tablename__`. The `index=True` on foreign key columns is cheap insurance: joins on this column become much faster as the table grows.

### 5.2 One-to-many: `relationship()` and `back_populates`

The FK column (`user_id`) is the database-level link. `relationship()` adds the Python-level navigation on *both* sides:

```python
# Add to User:
posts: Mapped[list["Post"]] = relationship(
    back_populates="author",
    cascade="all, delete-orphan",   # deleting a user deletes their posts
)

# Add to Post:
author: Mapped["User"] = relationship(back_populates="posts")
```

- `User.posts` is a **collection** (`list["Post"]`), `Post.author` is a **scalar** (`"User"`).
- `back_populates="posts"` / `back_populates="author"` tells SQLAlchemy these two relationships are the two ends of the *same* link. Update one and the other stays in sync automatically.
- **Cascade** `all, delete-orphan` means: when a user is deleted, their posts are deleted too, and a post removed from `user.posts` is deleted. Without a cascade, the database would leave orphaned posts (or raise a foreign-key error).

> **Warning:** Always pair `back_populates` on both sides. Two unlinked `relationship()`s to the same table create two independent relationships that silently get out of sync.

### 5.3 One-to-many in action

```python
# Reset the database so ids match the outputs below:
# rm orm_demo.db   (then run Base.metadata.create_all(engine) again)

with Session.begin() as session:
    alice = User(name="Alice", email="alice@example.com", age=30)
    alice.posts.append(Post(title="Hello SQLAlchemy", content="My first post."))
    alice.posts.append(Post(title="Relationships 101", content="FKs and friends."))
    session.add(alice)   # cascades: inserting alice inserts her posts too
```

Because the relationship is bidirectional, you can navigate from either side:

```python
with Session() as session:
    alice = session.scalars(select(User).where(User.name == "Alice")).one()

    for post in alice.posts:                      # user -> posts
        print(post.title, "| author:", post.author.name)   # post -> user

    print("Alice's posts:", alice.posts)
```

```text
Hello SQLAlchemy | author: Alice
Relationships 101 | author: Alice
Alice's posts: [Post(id=1, title='Hello SQLAlchemy'), Post(id=2, title='Relationships 101')]
```

> **Behind the scenes:** the moment you access `alice.posts`, SQLAlchemy runs a lazy `SELECT` to fetch the posts (you'd see it with `echo=True`). This is *lazy loading* — convenient, but it becomes a performance problem in loops (see [Section 6.8](#68-loading-related-objects-eager-vs-lazy)).

The cascade in action:

```python
with Session.begin() as session:
    alice = session.scalars(select(User).where(User.name == "Alice")).one()
    session.delete(alice)

with Session() as session:
    print("Users left:", session.scalars(select(User)).all())
    print("Posts left:", session.scalars(select(Post)).all())
```

```text
Users left: []
Posts left: []
```

Alice's posts were deleted along with her. Without `cascade="all, delete-orphan"`, the DELETE would have failed or left dangling rows.

### 5.4 One-to-one

A one-to-one is a one-to-many constrained to a single row: the foreign key column gets `unique=True`, and the relationship gets `uselist=False`.

```python
class Profile(Base):
    __tablename__ = "profiles"

    id: Mapped[int] = mapped_column(primary_key=True)
    bio: Mapped[str | None] = mapped_column(Text)
    user_id: Mapped[int] = mapped_column(ForeignKey("users.id"), unique=True)

    user: Mapped["User"] = relationship(back_populates="profile")


# Add to User:
profile: Mapped["Profile | None"] = relationship(back_populates="user", uselist=False)
```

```python
with Session.begin() as session:
    session.add(User(name="Bob", email="bob@example.com", age=25))

with Session.begin() as session:
    bob = session.scalars(select(User).where(User.name == "Bob")).one()
    bob.profile = Profile(bio="Loves databases.")

with Session() as session:
    bob = session.scalars(select(User).where(User.name == "Bob")).one()
    print(bob.profile.bio)            # user -> profile
    print(bob.profile.user.name)      # profile -> user (back_populates)
```

```text
Loves databases.
Bob
```

### 5.5 Many-to-many with an association table

Many-to-many needs a third **association table** holding pairs of foreign keys. Here, a post can have many tags and a tag can belong to many posts:

```python
from sqlalchemy import Column, Table

post_tags = Table(
    "post_tags",
    Base.metadata,
    Column("post_id", ForeignKey("posts.id"), primary_key=True),
    Column("tag_id", ForeignKey("tags.id"), primary_key=True),
)


class Tag(Base):
    __tablename__ = "tags"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(30), unique=True)

    posts: Mapped[list["Post"]] = relationship(
        secondary=post_tags,          # the association table
        back_populates="tags",
    )

    def __repr__(self) -> str:
        return f"Tag(id={self.id!r}, name={self.name!r})"


# Add to Post:
tags: Mapped[list["Tag"]] = relationship(secondary=post_tags, back_populates="posts")
```

The `secondary=` argument points at the association table; SQLAlchemy handles the joins for you. Usage is just list append/remove:

```python
with Session.begin() as session:
    bob = session.scalars(select(User).where(User.name == "Bob")).one()
    post = Post(title="SQLAlchemy Core vs ORM", content="Which to choose?")
    post.author = bob
    post.tags.append(Tag(name="sqlalchemy"))
    post.tags.append(Tag(name="tutorial"))
    session.add(post)     # inserts the post, the tags, and the association rows

with Session() as session:
    post = session.scalars(select(Post).where(Post.title == "SQLAlchemy Core vs ORM")).one()
    print("Tags:", post.tags)

    # Find all posts tagged "sqlalchemy" by joining through the relationship
    posts = session.scalars(
        select(Post).join(Post.tags).where(Tag.name == "sqlalchemy")
    ).all()
    print("Tagged posts:", posts)
```

```text
Tags: [Tag(id=1, name='sqlalchemy'), Tag(id=2, name='tutorial')]
Tagged posts: [Post(id=1, title='SQLAlchemy Core vs ORM')]
```

### 5.6 Relationship types at a glance

| Relationship | FK on | `unique` on FK | `uselist` | Example |
| --- | --- | --- | --- | --- |
| One-to-many | the "many" table | no | default (list) | `User.posts` / `Post.author` |
| One-to-one | either side | yes | `uselist=False` | `User.profile` / `Profile.user` |
| Many-to-many | association table | — (composite PK) | default | `Post.tags` via `post_tags` |

---

## 6. Queries

This section dives into `select()`. We'll use the same models, now with a `Comment` class added so we can demo joins and aggregations:

```python
class Comment(Base):
    __tablename__ = "comments"

    id: Mapped[int] = mapped_column(primary_key=True)
    body: Mapped[str] = mapped_column(Text, nullable=False)
    post_id: Mapped[int] = mapped_column(ForeignKey("posts.id"), index=True)
    user_id: Mapped[int] = mapped_column(ForeignKey("users.id"), index=True)

    post: Mapped["Post"] = relationship(back_populates="comments")
    author: Mapped["User"] = relationship(back_populates="comments")

    def __repr__(self) -> str:
        return f"Comment(id={self.id!r}, body={self.body!r})"


# Add to Post:
comments: Mapped[list["Comment"]] = relationship(
    back_populates="post", cascade="all, delete-orphan"
)

# Add to User:
comments: Mapped[list["Comment"]] = relationship(back_populates="author")
```

> **Note:** a comment has *two* foreign keys — the post it belongs to and the user who wrote it — so it participates in two many-to-one relationships.

Reset and seed a deterministic dataset (run `rm orm_demo.db` first). Note the pattern: build the object graph and let the relationships fill in the foreign keys automatically:

```python
Base.metadata.create_all(engine)

with Session.begin() as session:
    alice = User(name="Alice", email="alice@example.com", age=30)
    bob = User(name="Bob", email="bob@example.com", age=25)
    carol = User(name="Carol", email="carol@example.com", age=35)

    p1 = Post(title="Hello SQLAlchemy", content="Welcome!")
    p2 = Post(title="Relationships 101", content="FKs and friends.")
    p3 = Post(title="SQLAlchemy Core vs ORM", content="Which to choose?")
    p4 = Post(title="Alembic Migrations", content="Version your schema.")
    p5 = Post(title="Query Basics", content="select() and friends.")

    alice.posts = [p1, p2]
    bob.posts = [p3, p4]
    carol.posts = [p5]

    session.add_all([alice, bob, carol])

    # comments: (post, author, body)
    session.add_all(
        [
            Comment(post=p1, author=bob, body="Great intro!"),
            Comment(post=p1, author=carol, body="Very helpful, thanks"),
            Comment(post=p3, author=alice, body="Nice comparison"),
            Comment(post=p3, author=carol, body="Core all the way"),
            Comment(post=p3, author=bob, body="Agreed!"),
            Comment(post=p5, author=alice, body="Looking forward to more"),
        ]
    )
```

Resulting dataset (deterministic ids, fresh database):

| id | title | author | comment count |
| --- | --- | --- | --- |
| 1 | Hello SQLAlchemy | Alice | 2 |
| 2 | Relationships 101 | Alice | 0 |
| 3 | SQLAlchemy Core vs ORM | Bob | 3 |
| 4 | Alembic Migrations | Bob | 0 |
| 5 | Query Basics | Carol | 1 |

### 6.1 Filtering

```python
with Session() as session:
    print("Contains 'SQL':", session.scalars(
        select(Post.title).where(Post.title.contains("SQL"))
    ).all())

    print("AND:", session.scalars(
        select(User.name).where(User.age >= 26, User.age <= 34)
    ).all())

    print("IN:", session.scalars(
        select(User.name).where(User.name.in_(["Alice", "Carol"]))
    ).all())

    print("LIKE:", session.scalars(
        select(Post.title).where(Post.title.like("%Basics%"))
    ).all())

    print("OR (use or_, not Python or):", session.scalars(
        select(User.name).where(or_(User.age < 26, User.age > 34))
    ).all())

    print("Is NULL (never == None):", session.scalars(
        select(Post.title).where(Post.content.is_(None))
    ).all())
```

```text
Contains 'SQL': ['Hello SQLAlchemy', 'SQLAlchemy Core vs ORM']
AND: ['Alice']
IN: ['Alice', 'Carol']
LIKE: ['Query Basics']
OR (use or_, not Python or): ['Bob', 'Carol']
Is NULL (never == None): []
```

Notes:

- Multiple `.where()` calls (or comma-separated arguments) are combined with **AND**. For OR, import `or_` from `sqlalchemy` — the Python keyword `or` does not work inside expressions (`User.age < 26 or User.age > 34` silently produces garbage).
- Compare to NULL with `.is_(None)` / `.is_not(None)` — `== None` never matches anything in SQL.

### 6.2 Ordering

```python
with Session() as session:
    print(session.scalars(
        select(Post.title).order_by(Post.id.desc())
    ).all())

    print(session.scalars(
        select(User.name).order_by(User.age.desc(), User.name)  # multiple keys
    ).all())
```

```text
['Query Basics', 'Alembic Migrations', 'SQLAlchemy Core vs ORM', 'Relationships 101', 'Hello SQLAlchemy']
['Carol', 'Alice', 'Bob']
```

### 6.3 Pagination

Use `.limit()` and `.offset()` — the SQL equivalent of `LIMIT`/`OFFSET`:

```python
per_page = 2
page = 2

with Session() as session:
    posts = session.scalars(
        select(Post).order_by(Post.id).limit(per_page).offset((page - 1) * per_page)
    ).all()
    print(f"Page {page}:", posts)

    total = session.scalar(select(func.count()).select_from(Post))
    print("Total posts:", total, "| total pages:", (total + per_page - 1) // per_page)
```

```text
Page 2: [Post(id=3, title='SQLAlchemy Core vs ORM'), Post(id=4, title='Alembic Migrations')]
Total posts: 5 | total pages: 3
```

> For very large tables, `OFFSET` gets slower the deeper you page. The scalable alternative is **keyset pagination**: `WHERE (id) > :last_seen_id ORDER BY id LIMIT :per_page`. Keep it in mind for production.

### 6.4 Joins

`.join()` accepts either an explicit ON clause or a relationship name:

```python
with Session() as session:
    # Join through the relationship (Post.author) — ON clause inferred
    alices_posts = session.scalars(
        select(Post).join(Post.author).where(User.name == "Alice")
    ).all()
    print("Alice's posts:", alices_posts)

    # Explicit ON clause (Core style) — same result
    alices_posts = session.scalars(
        select(Post).join(User, User.id == Post.user_id).where(User.name == "Alice")
    ).all()
    print("Again:", alices_posts)

    # Project both tables in one row
    rows = session.execute(
        select(User.name, Post.title).join(Post, Post.user_id == User.id)
    ).all()
    for name, title in rows:
        print(f"{name} wrote {title!r}")
```

```text
Alice's posts: [Post(id=1, title='Hello SQLAlchemy'), Post(id=2, title='Relationships 101')]
Again: [Post(id=1, title='Hello SQLAlchemy'), Post(id=2, title='Relationships 101')]
Alice wrote 'Hello SQLAlchemy'
Alice wrote 'Relationships 101'
Bob wrote 'SQLAlchemy Core vs ORM'
Bob wrote 'Alembic Migrations'
Carol wrote 'Query Basics'
```

**Left outer joins** — keep all rows from the left side even without a match. This is how you find posts *with no comments*:

```python
with Session() as session:
    rows = session.execute(
        select(Post.title, func.count(Comment.id))          # count() skips NULLs,
        .outerjoin(Comment, Comment.post_id == Post.id)     # so unmatched posts -> 0
        .group_by(Post.id, Post.title)
    ).all()
    for title, count in rows:
        print(f"{title!r}: {count} comments")
```

```text
'Hello SQLAlchemy': 2 comments
'Relationships 101': 0 comments
'SQLAlchemy Core vs ORM': 3 comments
'Alembic Migrations': 0 comments
'Query Basics': 1 comments
```

### 6.5 Aggregations and grouping

```python
from sqlalchemy import func

with Session() as session:
    print("Total users:", session.scalar(select(func.count()).select_from(User)))
    print("Average age:", round(session.scalar(select(func.avg(User.age))), 2))
    print("Youngest:", session.scalar(select(func.min(User.age))))

    # Posts per user, grouped
    rows = session.execute(
        select(User.name, func.count(Post.id))
        .join(User.posts)                       # inner join: only users with posts
        .group_by(User.id, User.name)
        .order_by(func.count(Post.id).desc(), User.name)   # deterministic tie-breaking
    ).all()
    print("Posts per user:", rows)

    # ...and only users with 2+ posts (HAVING filters groups)
    rows = session.execute(
        select(User.name, func.count(Post.id))
        .join(User.posts)
        .group_by(User.id, User.name)
        .having(func.count(Post.id) >= 2)
        .order_by(User.name)
    ).all()
    print("Users with 2+ posts:", rows)
```

```text
Total users: 3
Average age: 30.0
Youngest: 25
Posts per user: [('Alice', 2), ('Bob', 2), ('Carol', 1)]
Users with 2+ posts: [('Alice', 2), ('Bob', 2)]
```

- `func.count()`, `func.avg()`, `func.min()`, `func.max()`, `func.sum()` are the SQL aggregate functions.
- **`WHERE` filters rows before grouping; `HAVING` filters groups after.**
- When grouping, list every non-aggregated selected column in `group_by()` — this keeps the SQL portable across databases (PostgreSQL would reject the shorthand).

### 6.6 Counting without loading rows

```python
with Session() as session:
    total = session.scalar(select(func.count()).select_from(Post))
    print("Posts:", total)

    # Count distinct values
    distinct_authors = session.scalar(
        select(func.count(func.distinct(Post.user_id)))
    )
    print("Distinct authors:", distinct_authors)

    # Avoid len(session.scalars(...).all()) for big tables — it loads every row
```

```text
Posts: 5
Distinct authors: 3
```

### 6.7 Useful query patterns

```python
with Session() as session:
    # Subquery: users with their most recent post title
    latest_posts = (
        select(Post.user_id, func.max(Post.id).label("max_id"))
        .group_by(Post.user_id)
        .subquery()
    )
    rows = session.execute(
        select(User.name, Post.title)
        .join(latest_posts, latest_posts.c.max_id == Post.id)
        .join(User, User.id == Post.user_id)
        .order_by(User.name)
    ).all()
    print("Latest post per user:", rows)
```

```text
Latest post per user: [('Alice', 'Relationships 101'), ('Bob', 'Alembic Migrations'), ('Carol', 'Query Basics')]
```

### 6.8 Loading related objects: lazy vs. eager

This is the single most important performance concept in SQLAlchemy. By default, relationships are **lazy**: the related rows are loaded with a separate query *the moment you access the attribute*.

**The N+1 problem.** This innocent-looking loop fires **1 + N queries** (one for the users, then one per user for their posts):

```python
with Session() as session:
    users = session.scalars(select(User)).all()
    for user in users:                     # 3 users
        print(user.name, "->", [p.title for p in user.posts])   # 3 extra queries!
```

```text
Alice -> ['Hello SQLAlchemy', 'Relationships 101']
Bob -> ['SQLAlchemy Core vs ORM', 'Alembic Migrations']
Carol -> ['Query Basics']
```

With `echo=True` you'd see one `SELECT` for users followed by three more `SELECT`s for posts — hence the name *N+1*: N extra queries for N rows.

**Eager loading** loads the related rows up front. Two strategies:

- `selectinload()` — runs a **second query** that loads all related rows with `WHERE id IN (...)`. Best for **collections** (`user.posts`, `post.comments`) because it never duplicates parent rows.
- `joinedload()` — adds a **JOIN** to the original query. Best for **many-to-one** scalars (`post.author`) where each parent has exactly one child.

```python
from sqlalchemy.orm import joinedload, selectinload

# Two queries total: users + posts (WHERE user_id IN (1,2,3))
with Session() as session:
    users = session.scalars(
        select(User).options(selectinload(User.posts))
    ).all()
    for user in users:
        print(user.name, "->", [p.title for p in user.posts])
```

```text
Alice -> ['Hello SQLAlchemy', 'Relationships 101']
Bob -> ['SQLAlchemy Core vs ORM', 'Alembic Migrations']
Carol -> ['Query Basics']
```

```python
# One query total: SELECT ... JOIN users
with Session() as session:
    posts = session.scalars(
        select(Post).options(joinedload(Post.author))
    ).all()
    for post in posts:
        print(post.title, "by", post.author.name)
```

```text
Hello SQLAlchemy by Alice
Relationships 101 by Alice
SQLAlchemy Core vs ORM by Bob
Alembic Migrations by Bob
Query Basics by Carol
```

**Nested eager loading** — load posts *and* their comments in one go:

```python
with Session() as session:
    users = session.scalars(
        select(User).options(
            selectinload(User.posts).selectinload(Post.comments)
        )
    ).all()
    for user in users:
        for post in user.posts:
            print(user.name, "-", post.title, "-", len(post.comments), "comments")
```

```text
Alice - Hello SQLAlchemy - 2 comments
Alice - Relationships 101 - 0 comments
Bob - SQLAlchemy Core vs ORM - 3 comments
Bob - Alembic Migrations - 0 comments
Carol - Query Basics - 1 comments
```

**Choosing a strategy:**

| Situation | Strategy | Why |
| --- | --- | --- |
| Load a collection (`user.posts`) | `selectinload` | No row duplication; separate `IN` query |
| Load a many-to-one (`post.author`) | `joinedload` | Single JOIN, no extra query |
| Both, nested | chain them | e.g. `selectinload(User.posts).selectinload(Post.comments)` |
| Large result sets / paginated lists | avoid loading collections at all | `joinedload` on a collection duplicates rows and breaks `LIMIT` pagination |

> **Warning:** Never use `joinedload()` on a *collection* (e.g. `User.posts`) combined with `.limit()`/`.offset()` — the JOIN multiplies rows, so the pagination counts wrong rows. Use `selectinload` for collections.

---

## 7. Practical Application: A Blog Database

Let's put everything together in a small but realistic project: the database layer for a blog with **users**, **posts**, and **comments**. Everything so far (models, sessions, relationships, queries, transactions, error handling) shows up here.

### 7.1 Project structure

```text
blog_app/
├── db.py          # engine, Session, Base
├── models.py      # User, Post, Comment
├── crud.py        # database operations
├── main.py        # demo script
└── requirements.txt
```

### 7.2 `db.py` — database configuration

```python
# blog_app/db.py
from sqlalchemy import create_engine, event
from sqlalchemy.orm import DeclarativeBase, sessionmaker

# Change this URL to switch databases (e.g. PostgreSQL in production).
DATABASE_URL = "sqlite+pysqlite:///blog.db"

engine = create_engine(DATABASE_URL, echo=False)

# One session factory for the whole app; create a Session per operation/request.
Session = sessionmaker(bind=engine, expire_on_commit=False)


class Base(DeclarativeBase):
    """All models inherit from this."""
    pass


# SQLite does not enforce foreign keys unless told to. One small pragma fixes it.
if DATABASE_URL.startswith("sqlite"):

    @event.listens_for(engine, "connect")
    def _set_sqlite_pragma(dbapi_connection, connection_record):
        cursor = dbapi_connection.cursor()
        cursor.execute("PRAGMA foreign_keys=ON")
        cursor.close()
```

> **Note:** `expire_on_commit=False` keeps attribute values usable after `commit()` — convenient, and common in web apps that render objects after the transaction ends.

### 7.3 `models.py` — model definitions

```python
# blog_app/models.py
from datetime import datetime

from sqlalchemy import DateTime, ForeignKey, String, Text, func
from sqlalchemy.orm import Mapped, mapped_column, relationship

from db import Base


class User(Base):
    __tablename__ = "users"

    id: Mapped[int] = mapped_column(primary_key=True)
    username: Mapped[str] = mapped_column(String(50), unique=True, nullable=False)
    email: Mapped[str] = mapped_column(String(120), unique=True, nullable=False)
    password_hash: Mapped[str] = mapped_column(String(255), nullable=False)
    created_at: Mapped[datetime] = mapped_column(DateTime, server_default=func.now())

    posts: Mapped[list["Post"]] = relationship(
        back_populates="author", cascade="all, delete-orphan"
    )
    comments: Mapped[list["Comment"]] = relationship(back_populates="author")

    def __repr__(self) -> str:
        return f"User(id={self.id!r}, username={self.username!r})"


class Post(Base):
    __tablename__ = "posts"

    id: Mapped[int] = mapped_column(primary_key=True)
    title: Mapped[str] = mapped_column(String(200), nullable=False)
    content: Mapped[str] = mapped_column(Text, nullable=False)
    published_at: Mapped[datetime | None] = mapped_column(DateTime)  # NULL = draft
    created_at: Mapped[datetime] = mapped_column(DateTime, server_default=func.now())

    user_id: Mapped[int] = mapped_column(ForeignKey("users.id"), index=True)

    author: Mapped["User"] = relationship(back_populates="posts")
    comments: Mapped[list["Comment"]] = relationship(
        back_populates="post", cascade="all, delete-orphan"
    )

    def __repr__(self) -> str:
        return f"Post(id={self.id!r}, title={self.title!r})"


class Comment(Base):
    __tablename__ = "comments"

    id: Mapped[int] = mapped_column(primary_key=True)
    body: Mapped[str] = mapped_column(Text, nullable=False)
    created_at: Mapped[datetime] = mapped_column(DateTime, server_default=func.now())

    post_id: Mapped[int] = mapped_column(ForeignKey("posts.id"), index=True)
    user_id: Mapped[int] = mapped_column(ForeignKey("users.id"), index=True)

    post: Mapped["Post"] = relationship(back_populates="comments")
    author: Mapped["User"] = relationship(back_populates="comments")

    def __repr__(self) -> str:
        return f"Comment(id={self.id!r}, body={self.body!r})"
```

Design notes:

- `published_at` is nullable — `NULL` means "draft", a value means "published".
- `user_id`/`post_id` get `index=True` because we join/filter on them constantly.
- Deleting a `User` cascades to their `posts` (and, via `Post.comments`, to the comments on those posts). Comments are *not* deleted when the commenting `User` is removed — `User.comments` has no cascade. In a real app you'd decide what happens to a deleted user's comments: block the deletion while comments exist, anonymize them, or set the FK to `ON DELETE SET NULL`. For this demo, deleting a user who has comments raises a foreign-key error — the *safe* default (thanks to `PRAGMA foreign_keys=ON` in `db.py`).

### 7.4 `crud.py` — CRUD operations, queries, error handling

```python
# blog_app/crud.py
from sqlalchemy import func, select
from sqlalchemy.exc import IntegrityError
from sqlalchemy.orm import Session, joinedload, selectinload

from models import Comment, Post, User


# --- Create ---------------------------------------------------------------

def create_user(session: Session, username: str, email: str, password_hash: str) -> User:
    """Create a user. Rolls back and raises ValueError if the name/email is taken."""
    user = User(username=username, email=email, password_hash=password_hash)
    session.add(user)
    try:
        session.flush()   # send the INSERT now so unique errors surface here
    except IntegrityError:
        session.rollback()
        raise ValueError(f"Username {username!r} or email {email!r} is already taken.")
    return user


def create_post(
    session: Session, title: str, content: str, user_id: int, published_at=None
) -> Post:
    post = Post(title=title, content=content, user_id=user_id, published_at=published_at)
    session.add(post)
    session.flush()   # populate post.id so callers can reference it right away
    return post


def add_comment(session: Session, post_id: int, user_id: int, body: str) -> Comment:
    comment = Comment(post_id=post_id, user_id=user_id, body=body)
    session.add(comment)
    return comment


# --- Read ----------------------------------------------------------------

def get_user(session: Session, user_id: int) -> User | None:
    return session.get(User, user_id)


def get_user_by_username(session: Session, username: str) -> User | None:
    return session.scalars(select(User).where(User.username == username)).first()


def list_posts(session: Session, page: int = 1, per_page: int = 10) -> tuple[list[Post], int]:
    """Paginated posts (newest first) with authors preloaded — no N+1."""
    total = session.scalar(select(func.count()).select_from(Post))
    posts = session.scalars(
        select(Post)
        .options(joinedload(Post.author))
        .order_by(Post.created_at.desc(), Post.id.desc())
        .limit(per_page)
        .offset((page - 1) * per_page)
    ).all()
    return posts, total


def get_post_with_comments(session: Session, post_id: int) -> Post | None:
    """A post with its author, comments, and comment authors — all preloaded."""
    return session.scalars(
        select(Post)
        .options(
            joinedload(Post.author),
            selectinload(Post.comments).joinedload(Comment.author),
        )
        .where(Post.id == post_id)
    ).first()


def search_posts(session: Session, term: str) -> list[Post]:
    """Case-insensitive title search."""
    return session.scalars(
        select(Post)
        .where(func.lower(Post.title).contains(term.lower()))
        .order_by(Post.created_at.desc())
    ).all()


# --- Delete --------------------------------------------------------------

def delete_post(session: Session, post_id: int) -> bool:
    """Delete a post (its comments go with it via cascade)."""
    post = session.get(Post, post_id)
    if post is None:
        return False
    session.delete(post)
    return True


# --- Reports -------------------------------------------------------------

def post_comment_counts(session: Session) -> list[tuple[str, int]]:
    """(title, comment count) for every post, including those with zero comments."""
    rows = session.execute(
        select(Post.title, func.count(Comment.id))
        .outerjoin(Comment, Comment.post_id == Post.id)
        .group_by(Post.id, Post.title)
        .order_by(Post.id)
    ).all()
    return [(title, count) for title, count in rows]


def user_post_counts(session: Session) -> list[tuple[str, int]]:
    """(username, post count), most prolific first."""
    rows = session.execute(
        select(User.username, func.count(Post.id))
        .join(User.posts)
        .group_by(User.id, User.username)
        .order_by(func.count(Post.id).desc(), User.username)
    ).all()
    return [(username, count) for username, count in rows]
```

Notice the pattern: functions receive a `Session` and **do not commit**. The caller owns the transaction boundary — that keeps `crud.py` composable (a caller can bundle several operations into one transaction) and makes error handling predictable.

### 7.5 `main.py` — session management, transactions, error handling

```python
# blog_app/main.py
from datetime import datetime, timezone

from sqlalchemy import select
from sqlalchemy.exc import IntegrityError

import crud
from db import Base, Session, engine
from models import User

# Create tables. In production, use Alembic migrations instead (Section 8).
Base.metadata.create_all(engine)


def seed_demo_data() -> None:
    """Insert a small deterministic dataset. Idempotent — skips if users exist."""
    with Session.begin() as session:      # auto commit / rollback
        if session.scalars(select(User)).first():
            return

        alice = crud.create_user(session, "alice", "alice@example.com", "hash-1")
        bob = crud.create_user(session, "bob", "bob@example.com", "hash-2")
        carol = crud.create_user(session, "carol", "carol@example.com", "hash-3")

        now = datetime.now(timezone.utc)
        hello = crud.create_post(session, "Hello, blog!", "First post.", alice.id, now)
        tips = crud.create_post(session, "SQLAlchemy tips", "Lots of tips.", alice.id, now)
        crud.create_post(session, "Why migrations matter", "Alembic rocks.", bob.id, None)  # draft

        crud.add_comment(session, hello.id, bob.id, "Welcome, Alice!")
        crud.add_comment(session, hello.id, carol.id, "Nice work.")
        crud.add_comment(session, tips.id, carol.id, "Bookmarking this.")


def main() -> None:
    seed_demo_data()

    with Session() as session:      # read-only session: no commit needed
        # 1. Latest posts with authors, eagerly loaded
        posts, total = crud.list_posts(session, page=1, per_page=5)
        print(f"--- {total} posts (page 1) ---")
        for post in posts:
            status = "draft" if post.published_at is None else "published"
            print(f"  #{post.id} {post.title!r} by {post.author.username} [{status}]")

        # 2. One post with its comments (all eager-loaded)
        print("\n--- Post #1 with comments ---")
        post = crud.get_post_with_comments(session, 1)
        print(f"{post.title} by {post.author.username}")
        for comment in post.comments:
            print(f"  {comment.author.username}: {comment.body}")

        # 3. Comment counts per post
        print("\n--- Comment counts ---")
        for title, count in crud.post_comment_counts(session):
            print(f"  {title!r}: {count}")

        # 4. Case-insensitive search
        print("\n--- Search 'sqlalchemy' ---")
        for post in crud.search_posts(session, "sqlalchemy"):
            print(f"  {post.title!r}")

    # 5. Error handling: duplicate username -> clean ValueError, transaction rolled back
    print("\n--- Duplicate username ---")
    try:
        with Session.begin() as session:
            crud.create_user(session, "alice", "another@example.com", "hash-x")
    except ValueError as exc:
        print(f"  Caught: {exc}")

    # 6. Transaction management: two writes, one fails -> both rolled back
    print("\n--- Rollback demo ---")
    try:
        with Session.begin() as session:
            session.add(User(username="dave", email="dave@example.com", password_hash="hash-4"))
            session.add(User(username="eve", email="alice@example.com", password_hash="hash-5"))  # duplicate email
    except IntegrityError:
        print("  Duplicate email -> IntegrityError; both inserts rolled back.")

    with Session() as session:
        print("  Dave exists?", crud.get_user_by_username(session, "dave") is not None)


if __name__ == "__main__":
    main()
```

### 7.6 Run it

```bash
cd blog_app
rm blog.db        # start fresh so ids match (optional)
python main.py
```

```text
--- 3 posts (page 1) ---
  #3 'Why migrations matter' by bob [draft]
  #2 'SQLAlchemy tips' by alice [published]
  #1 'Hello, blog!' by alice [published]

--- Post #1 with comments ---
Hello, blog! by alice
  bob: Welcome, Alice!
  carol: Nice work.

--- Comment counts ---
  'Hello, blog!': 2
  'SQLAlchemy tips': 1
  'Why migrations matter': 0

--- Search 'sqlalchemy' ---
  'SQLAlchemy tips'

--- Duplicate username ---
  Caught: Username 'alice' or email 'another@example.com' is already taken.

--- Rollback demo ---
  Duplicate email -> IntegrityError; both inserts rolled back.
  Dave exists? False
```

What this demo exercises:

- **Session management** — one session per operation, context managers throughout.
- **CRUD** — create user/post/comment; read with joins; delete with cascade.
- **Relationships** — `post.author`, `post.comments`, `comment.author`.
- **Useful queries** — pagination, search, per-post and per-user counts.
- **Error handling** — `IntegrityError` → rollback → friendly `ValueError`.
- **Transaction management** — a failed second insert rolls back the first insert too.

---

## 8. Database Migrations with Alembic

### Why migrations?

Your models evolve: new columns, new tables, renames. `create_all()` only creates *missing* tables — it never alters existing ones. If you add a `bio` column to `User`, `create_all()` will not add it to an existing database. In production you cannot just drop and recreate the database (you'd lose data), and every teammate/instance needs the same schema changes applied in the same order.

**Migrations** are version-controlled schema changes: each migration is a Python file that knows how to apply (`upgrade()`) and undo (`downgrade()`) one schema change. **Alembic** is the standard migration tool for SQLAlchemy and integrates directly with your `Base.metadata`.

### 8.1 Install and initialize

```bash
pip install alembic
```

Inside the `blog_app/` directory:

```bash
alembic init alembic
```

This creates:

```text
blog_app/
├── alembic.ini        # configuration (connection URL, logging)
└── alembic/           # migration environment + version files
    ├── env.py         # tells Alembic about our metadata
    ├── script.py.mako # template for new migration files
    └── versions/      # generated migration files live here
```

### 8.2 Configure it

**1. `alembic.ini`** — point at the database:

```ini
# alembic.ini
sqlalchemy.url = sqlite:///blog.db
```

> The URL lives in `alembic.ini` by default, but for production you'll want it from the environment instead (see Best Practices). You can override it in `env.py` with `config.set_main_option("sqlalchemy.url", os.environ["DATABASE_URL"])`.

**2. `alembic/env.py`** — teach Alembic about our models so it can *autogenerate* migrations. The key step: import the app's modules so the models register on `Base.metadata`:

```python
# alembic/env.py (the lines you must add/change)
import db
import models                    # importing models registers them on Base.metadata

target_metadata = db.Base.metadata
```

> **Common gotcha:** `db.py` only defines `Base` — it does not import your models. If `env.py` imports only `db`, `Base.metadata` is empty and autogenerate silently produces empty migrations. Importing `models` (directly or indirectly) is what populates the metadata.

If you use SQLite, also enable **batch mode** so column alterations work (SQLite can't `ALTER TABLE` the normal way; Alembic rebuilds the table instead):

```python
# inside run_migrations_online(), in the context.configure(...) call:
context.configure(
    connection=connection,
    target_metadata=target_metadata,
    render_as_batch=True,   # SQLite-safe ALTER TABLE
)
```

### 8.3 Generate and apply your first migration

With models defined and `target_metadata` wired up, Alembic can compare the models against the database and write the migration for you:

```bash
alembic revision --autogenerate -m "create users posts comments tables"
```

This writes a file like `alembic/versions/abc123_create_users_posts_comments_tables.py` containing:

```python
def upgrade() -> None:
    op.create_table(
        "users",
        sa.Column("id", sa.Integer(), nullable=False),
        sa.Column("username", sa.String(length=50), nullable=False),
        ...
    )
    op.create_table("posts", ...)
    op.create_table("comments", ...)
    op.create_index(op.f("ix_posts_user_id"), "posts", ["user_id"], unique=False)
    ...


def downgrade() -> None:
    op.drop_table("comments")
    op.drop_table("posts")
    op.drop_table("users")
```

Apply it:

```bash
alembic upgrade head
```

Inspect the state:

```bash
alembic current      # which revision the database is on
```

```text
3044ed473a7f (head)
```

(`alembic current` prints the revision id the database is on; `(head)` means it is the newest one. Use `alembic history` to see the full chain with messages.)

Other essential commands:

```bash
alembic history          # all revisions, newest last
alembic downgrade -1     # undo the last migration
alembic downgrade base   # undo everything (empty database)
alembic check            # verify models and database are in sync (no pending autogen)
```

### 8.4 Autogeneration, and adding a column

Say we add a `published` flag to `Post`:

```python
class Post(Base):
    ...
    published: Mapped[bool] = mapped_column(server_default="1")  # existing rows -> True
```

Then:

```bash
alembic revision --autogenerate -m "add published column to posts"
```

```python
def upgrade() -> None:
    with op.batch_alter_table("posts", schema=None) as batch_op:  # batch mode (SQLite)
        batch_op.add_column(
            sa.Column("published", sa.Boolean(), server_default="1", nullable=False)
        )


def downgrade() -> None:
    with op.batch_alter_table("posts", schema=None) as batch_op:
        batch_op.drop_column("published")
```

```bash
alembic upgrade head
```

**What autogenerate does and doesn't do:** it detects *schema* differences (new/removed tables, columns, indexes, constraints) by diffing `target_metadata` against the live database. It does **not** detect renamed columns (it sees a drop + add), data backfills, or changes to Python-side defaults. **Always review and edit the generated file** — autogenerate is a draft, not a contract.

### 8.5 Production considerations

- **Review every migration** before applying — never trust autogenerate blindly.
- **Never edit a migration that has already been applied** in any environment. Write a new migration instead.
- **Back up the database** before running migrations in production.
- **Test `upgrade` *and* `downgrade`** on staging; `downgrade` is how you recover from a bad release.
- **One logical change per migration** — it makes `downgrade -1` predictable.
- **New columns on existing tables need `server_default`** (or `nullable=True`) so old rows get a value.
- **Run migrations as part of deployment/CI**, not by hand on the server.
- **Add a `naming_convention`** to your `MetaData` so constraints have stable, predictable names (huge help when migrations need to alter constraints).
- For SQLite, keep `render_as_batch=True` and prefer non-destructive changes.

---

## 9. Best Practices

### Session lifecycle

- Create a `Session` per operation (or per HTTP request in a web app), use it, close it. Do not keep sessions alive across requests or share them between threads (they are not thread-safe).
- Prefer context managers: `with Session() as session:` for reads, `with Session.begin() as session:` for writes (auto commit/rollback).
- Set `expire_on_commit=False` if you render objects after the transaction (common in web apps).

### Transaction boundaries

- Keep transactions **short**. Never hold a transaction open while waiting on network I/O or user input.
- Commit explicitly at the end of a unit of work; don't scatter `commit()` calls inside helper functions (see `crud.py` above — helpers take a session, the caller commits).
- Always `rollback()` in an exception handler, or use `Session.begin()` which does it for you.

### Avoid N+1 queries

- If you know you'll access `user.posts` for many users, load them with `selectinload(User.posts)` up front.
- Use `joinedload` for many-to-one relationships like `post.author`.
- Detect N+1 in development: `echo=True` or query logging; in tests, assert the number of SQL statements executed.

### Avoid SQL injection

- Values always go in **bound parameters** — never f-string them into SQL: `select(User).where(User.username == user_input)` parameterizes automatically; `text()` uses `:name` placeholders.
- Treat `text()` like a raw SQL escape hatch: no interpolation of untrusted values.

### Connection pooling

- Create the `engine` **once** at module level and reuse it; never per request.
- Production databases (PostgreSQL/MySQL) tune the pool: `create_engine(url, pool_size=10, max_overflow=20, pool_pre_ping=True, pool_recycle=1800)`.
  - `pool_pre_ping=True` — check stale connections before use (robust against dropped connections/restarts).
  - `pool_recycle` — avoid holding connections longer than the database's idle timeout.
- Call `engine.dispose()` at application shutdown to close pooled connections cleanly (frameworks like FastAPI do this for you).
- SQLite uses its own pool strategies (a single file/connection) — don't add `pool_size` for SQLite.

### Configuration management

- Read `DATABASE_URL` from the environment, never hardcode credentials:

```python
import os
DATABASE_URL = os.environ.get("DATABASE_URL", "sqlite+pysqlite:///blog.db")
engine = create_engine(DATABASE_URL)
```

- Keep `echo=False` in production (it logs every statement).

### Proper model design

- One model = one table; name tables explicitly with `__tablename__` (e.g. singular class `User`, plural table `users`).
- Choose the right column types (`Numeric` for money, `DateTime(timezone=True)`-friendly types for timestamps, `Text` for long content).
- Add `index=True` on foreign keys and columns you filter/sort by.
- Add `unique=True` where the domain requires it (usernames, emails) — the database should enforce it, not just your app.
- Store timestamps in **UTC** and be consistent.
- Prefer `server_default` for defaults that must survive raw SQL inserts; use Python `default=` for app-level defaults.

### Testing database code

- Test against SQLite in memory or a temp file for speed: `create_engine("sqlite+pysqlite:///:memory:")` (single-threaded tests only).
- Reset state per test: recreate tables or wrap each test in a transaction and roll it back.
- Use a dedicated test database (or testcontainers for Postgres parity) in CI.
- Run Alembic migrations in test setup so tests exercise the real schema path.
- Assert query counts to catch N+1 regressions.

### Handling errors

- Catch `SQLAlchemyError` (and specific subclasses like `IntegrityError`) at boundaries; roll back; log; convert to a domain error (e.g. `ValueError`) — as `crud.create_user` does above.
- Never swallow exceptions: a silent rollback hides bugs.

### Performance considerations

- **Select only what you need**: `select(User.id, User.name)` instead of whole objects for reports.
- **Index** what you filter/order/join on.
- **Batch inserts** — `session.add_all([...])` or Core `insert(t).values([...])` in chunks (e.g. 1000 at a time).
- For very large result sets, iterate in batches: `session.scalars(select(...).execution_options(yield_per=500))` (Postgres: add `stream_results=True`).
- Don't eager-load collections you don't touch, and don't eager-load collections on paginated list queries (`joinedload` + `LIMIT` = wrong counts; `selectinload` on big lists can also blow up — prefer counting + loading only the page).

---

## 10. Common Mistakes

| # | Mistake | Why it happens | The fix |
| --- | --- | --- | --- |
| 1 | `session.query(User).filter(...)` everywhere | Old 1.x tutorials; it still runs, so nothing complains | Use `select(User).where(...)` + `session.scalars()` — the 2.x way |
| 2 | Forgetting `commit()` | `add()` stages objects; nothing is written until commit | Call `session.commit()`, or use `with Session.begin() as session:` |
| 3 | Using the session after an exception without `rollback()` | An error poisons the transaction | `session.rollback()` in `except` before anything else |
| 4 | N+1 queries in loops | Relationships load lazily by default | `selectinload` / `joinedload` (Section 6.8) |
| 5 | `where(User.age < 26 or User.age > 34)` | Python `or` doesn't build SQL | `or_(User.age < 26, User.age > 34)` or chain `.where()` |
| 6 | `where(User.name == None)` | Looks right, matches nothing in SQL | `User.name.is_(None)` / `.is_not(None)` |
| 7 | `default=[]` on a column/relationship | Mutable default shared across all instances | `default=list`, or `mapped_column(default=list)` |
| 8 | `relationship()` without `back_populates` | Two unlinked relationships silently desync | Always pair `back_populates` on both ends |
| 9 | Wrong (or missing) `cascade` | Deleting a parent leaves orphans or wipes too much | Use `cascade="all, delete-orphan"` for compositions; nothing for simple associations |
| 10 | `:memory:` SQLite + multiple connections/threads | Each connection gets its own empty database → "no such table" | Use a file database, or `StaticPool` for a single shared in-memory DB |
| 11 | Building SQL with f-strings | Habit from other languages; it's SQL injection | Always parameters: `text("... :p")`, dict of values, or expressions |
| 12 | Creating an `engine` per request | Copy-paste of `create_engine` into handlers | Create once at module/import time |
| 13 | No index on FK columns | It works on small data, so it goes unnoticed | `mapped_column(ForeignKey("users.id"), index=True)` |
| 14 | Naive datetimes (`datetime.now()`) | `datetime.now()` returns local naive time | `datetime.now(timezone.utc)` everywhere |

Three of these deserve a closer look:

**The poisoned session (mistake 3):**

```python
with Session() as session:
    try:
        session.add(User(username="x", email="taken@example.com"))
        session.commit()
    except IntegrityError:
        # Without rollback(), the NEXT use of session raises
        # "This Session's transaction has been rolled back due to a previous exception"
        session.rollback()
```

**Mutable default (mistake 7):**

```python
# BAD — every new User would share the SAME list object
# tags: Mapped[list[str]] = mapped_column(default=[])

# GOOD
tags: Mapped[list[str]] = mapped_column(default=list)
```

**Python `or` in filters (mistake 5):**

```python
# BAD — Python evaluates User.age > 34 first, and the result is nonsense
# select(User).where(User.age < 26 or User.age > 34)

# GOOD
from sqlalchemy import or_
select(User).where(or_(User.age < 26, User.age > 34))
```

---

## 11. SQLAlchemy 2.x Cheat Sheet

### Setup

| Task | Code |
| --- | --- |
| Engine | `engine = create_engine("sqlite+pysqlite:///app.db")` |
| Session factory | `Session = sessionmaker(bind=engine)` |
| Declarative base | `class Base(DeclarativeBase): pass` |
| Create tables | `Base.metadata.create_all(engine)` |

### Model definition

```python
class User(Base):
    __tablename__ = "users"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(50), nullable=False)
    email: Mapped[str] = mapped_column(String(120), unique=True)
    age: Mapped[int | None] = mapped_column()          # nullable via | None
    posts: Mapped[list["Post"]] = relationship(back_populates="author")

    def __repr__(self) -> str:
        return f"User(id={self.id!r}, name={self.name!r})"
```

### CRUD

| Operation | Code |
| --- | --- |
| Create | `session.add(obj)` / `session.add_all([...])` then `session.commit()` |
| Read by PK | `session.get(User, 1)` |
| Read all | `session.scalars(select(User)).all()` |
| Read one | `session.scalars(select(User).where(...)).one()` / `.one_or_none()` / `.first()` |
| Update | `obj.name = "New"; session.commit()` |
| Bulk update | `session.execute(update(User).where(...).values(...))` |
| Delete | `session.delete(obj); session.commit()` |
| Bulk delete | `session.execute(delete(User).where(...))` |
| Count | `session.scalar(select(func.count()).select_from(User))` |

### Queries

| Goal | Code |
| --- | --- |
| Filter | `select(User).where(User.age >= 18, User.is_active == True)` |
| OR | `select(User).where(or_(User.age < 18, User.age > 65))` |
| IN / LIKE / contains | `.where(User.name.in_([...]))`, `.like("%x%")`, `.contains("x")` |
| NULL | `.where(User.email.is_(None))` |
| Order | `.order_by(User.name, User.id.desc())` |
| Paginate | `.limit(per_page).offset((page - 1) * per_page)` |
| Join (via relationship) | `select(Post).join(Post.author).where(User.name == "Alice")` |
| Join (explicit ON) | `select(Post).join(User, User.id == Post.user_id)` |
| Left join | `.outerjoin(Comment, Comment.post_id == Post.id)` |
| Group + count | `select(User.name, func.count(Post.id)).join(User.posts).group_by(User.id, User.name).having(func.count(Post.id) > 1)` |
| Subquery | `sub = select(...).subquery()`; use via `sub.c.column` |

### Relationships

| Kind | Recipe |
| --- | --- |
| One-to-many | FK on the many side; `relationship(back_populates=...)` both ends |
| One-to-one | FK column `unique=True`; `relationship(..., uselist=False)` |
| Many-to-many | association `Table`; `relationship(secondary=assoc, back_populates=...)` |
| Cascade | `relationship(..., cascade="all, delete-orphan")` on the parent's collection |

### Session operations

| Operation | Code |
| --- | --- |
| Commit | `session.commit()` |
| Rollback | `session.rollback()` |
| Flush (SQL now, commit later) | `session.flush()` |
| Reload from DB | `session.refresh(obj)` |
| Discard cached state | `session.expire(obj)` |
| Close | `session.close()` |
| One-shot write | `with Session.begin() as session:` (commits/rolls back on exit) |

### Loading strategies

| Strategy | Use for | Behavior |
| --- | --- | --- |
| (none — default) | rarely | lazy `SELECT` on attribute access → N+1 risk |
| `selectinload(User.posts)` | collections | one extra `WHERE id IN (...)` query; no row duplication |
| `joinedload(Post.author)` | many-to-one | adds a JOIN; single query |
| Nested | both | `selectinload(User.posts).selectinload(Post.comments)` |

### Core quick reference

| Task | Code |
| --- | --- |
| Table | `users = Table("users", metadata, Column("id", Integer, primary_key=True), ...)` |
| Create | `metadata.create_all(engine)` |
| Insert | `conn.execute(insert(users).values(name="A"))` |
| Select | `conn.execute(select(users).where(users.c.age >= 18))` |
| Update | `conn.execute(update(users).where(users.c.id == 1).values(name="B"))` |
| Delete | `conn.execute(delete(users).where(users.c.id == 1))` |
| Raw SQL | `conn.execute(text("SELECT * FROM users WHERE id = :id"), {"id": 1})` |
| Transactions | `with engine.begin() as conn:` |

---

## 12. Exercises

Work through these in order. Each is self-contained; solutions are in [Section 13](#13-exercise-solutions). For the exercises that use a database file, delete it (`rm exX.db`) before re-running so ids stay predictable.

**Exercise 1 — Your first model (easy).**
Define a `User` model with `username` (unique) and `email` (unique) columns. Create the table, insert three users, and print all users ordered by `username`.

**Exercise 2 — CRUD (easy).**
Using a `User` model, demonstrate the full create → read → update → delete cycle: insert a user, read it back by primary key, change its email, verify the change, then delete it and verify the table is empty.

**Exercise 3 — One-to-many with cascade (easy).**
Create `Author` and `Book` models with a one-to-many relationship (`cascade="all, delete-orphan"` on `Author.books`). Create an author with two books, print the author's books, delete the author, and show that the books are gone too.

**Exercise 4 — Filtering, ordering, pagination (medium).**
Seed a `User` table with five users of varying ages. Write queries that: (a) return users aged 30+, ordered by name descending; (b) return page 2 of the full list with 2 items per page; (c) print the total number of users.

**Exercise 5 — Aggregations and grouping (medium).**
Using `Author`/`Book`, print for each author the number of books they've written (ordered most → fewest), then list only authors with 2 or more books. Use `join`, `group_by`, `func.count`, and `having`.

**Exercise 6 — Many-to-many (medium).**
Create `Student` and `Course` models connected through an association table. Enroll two students in overlapping courses. Write queries to (a) list a student's courses, and (b) find all students enrolled in a given course using `join(Student.courses)`.

**Exercise 7 — Fix the N+1 problem (medium).**
Seed several users, each with several posts. Print `user -> [post titles]` for all users using a plain lazy load, and count the SQL queries (add an event listener that counts `before_cursor_execute`). Then rewrite with `selectinload(User.posts)` and show the query count drops from `1 + N` to `2`.

**Exercise 8 — Transactions (medium-hard).**
Create an `Account` model (`name`, `balance`). Implement `transfer(session, from_name, to_name, amount)` that debits one account and credits another, raising `ValueError` on insufficient funds. Show that when the transfer fails, *both* balances are unchanged (the whole transaction rolled back).

**Exercise 9 — Migration with Alembic (medium).**
On the blog models from Section 7, add a `published: Mapped[bool]` column to `Post` with `server_default="1"`. Generate an autogenerated migration, review it, apply it with `alembic upgrade head`, and confirm with `alembic current`. Then write a second migration that adds an index on `Post.title`.

**Exercise 10 — Subqueries and combined reports (hard).**
Using `User`, `Post`, and `Comment`, produce one report showing each user's username, total posts, and total comments (including users with zero posts — use `coalesce` and outer joins on subqueries), ordered by username.

---

## 13. Exercise Solutions

### Exercise 1 — Your first model

```python
from sqlalchemy import String, create_engine, select
from sqlalchemy.orm import DeclarativeBase, Mapped, mapped_column, sessionmaker

engine = create_engine("sqlite+pysqlite:///:memory:")   # in-memory DB, fine single-threaded
Session = sessionmaker(bind=engine)


class Base(DeclarativeBase):
    pass


class User(Base):
    __tablename__ = "users"

    id: Mapped[int] = mapped_column(primary_key=True)
    username: Mapped[str] = mapped_column(String(50), unique=True, nullable=False)
    email: Mapped[str] = mapped_column(String(120), unique=True, nullable=False)

    def __repr__(self) -> str:
        return f"User(id={self.id!r}, username={self.username!r})"


Base.metadata.create_all(engine)

with Session.begin() as session:
    session.add_all(
        [
            User(username="ada", email="ada@example.com"),
            User(username="linus", email="linus@example.com"),
            User(username="grace", email="grace@example.com"),
        ]
    )

with Session() as session:
    print(session.scalars(select(User).order_by(User.username)).all())
```

```text
[User(id=1, username='ada'), User(id=3, username='grace'), User(id=2, username='linus')]
```

### Exercise 2 — CRUD

```python
from sqlalchemy import String, create_engine, select
from sqlalchemy.orm import DeclarativeBase, Mapped, mapped_column, sessionmaker

engine = create_engine("sqlite+pysqlite:///:memory:")
Session = sessionmaker(bind=engine)


class Base(DeclarativeBase):
    pass


class User(Base):
    __tablename__ = "users"

    id: Mapped[int] = mapped_column(primary_key=True)
    username: Mapped[str] = mapped_column(String(50), unique=True)
    email: Mapped[str] = mapped_column(String(120), unique=True)

    def __repr__(self) -> str:
        return f"User(id={self.id!r}, username={self.username!r}, email={self.email!r})"


Base.metadata.create_all(engine)

# CREATE
with Session.begin() as session:
    session.add(User(username="ada", email="ada@example.com"))

# READ
with Session() as session:
    ada = session.get(User, 1)
    print("Read:", ada)

    # UPDATE
    ada.email = "ada.lovelace@example.com"
    session.commit()
    print("Updated:", session.get(User, 1))

# DELETE
with Session.begin() as session:
    session.delete(session.get(User, 1))

with Session() as session:
    print("Remaining:", session.scalars(select(User)).all())
```

```text
Read: User(id=1, username='ada', email='ada@example.com')
Updated: User(id=1, username='ada', email='ada.lovelace@example.com')
Remaining: []
```

### Exercise 3 — One-to-many with cascade

```python
from sqlalchemy import ForeignKey, String, create_engine, select
from sqlalchemy.orm import DeclarativeBase, Mapped, mapped_column, relationship, sessionmaker

engine = create_engine("sqlite+pysqlite:///:memory:")
Session = sessionmaker(bind=engine)


class Base(DeclarativeBase):
    pass


class Author(Base):
    __tablename__ = "authors"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(80))
    books: Mapped[list["Book"]] = relationship(
        back_populates="author", cascade="all, delete-orphan"
    )

    def __repr__(self) -> str:
        return f"Author(id={self.id!r}, name={self.name!r})"


class Book(Base):
    __tablename__ = "books"

    id: Mapped[int] = mapped_column(primary_key=True)
    title: Mapped[str] = mapped_column(String(120))
    author_id: Mapped[int] = mapped_column(ForeignKey("authors.id"), index=True)
    author: Mapped["Author"] = relationship(back_populates="books")

    def __repr__(self) -> str:
        return f"Book(id={self.id!r}, title={self.title!r})"


Base.metadata.create_all(engine)

with Session.begin() as session:
    author = Author(name="Grace Hopper")
    author.books.append(Book(title="Compilers"))
    author.books.append(Book(title="COBOL"))
    session.add(author)

with Session() as session:
    author = session.scalars(select(Author).where(Author.name == "Grace Hopper")).one()
    print("Books:", author.books)

with Session.begin() as session:
    session.delete(session.scalars(select(Author).where(Author.name == "Grace Hopper")).one())

with Session() as session:
    print("Authors left:", session.scalars(select(Author)).all())
    print("Books left:", session.scalars(select(Book)).all())
```

```text
Books: [Book(id=1, title='Compilers'), Book(id=2, title='COBOL')]
Authors left: []
Books left: []
```

### Exercise 4 — Filtering, ordering, pagination

```python
from sqlalchemy import String, create_engine, func, select
from sqlalchemy.orm import DeclarativeBase, Mapped, mapped_column, sessionmaker

engine = create_engine("sqlite+pysqlite:///:memory:")
Session = sessionmaker(bind=engine)


class Base(DeclarativeBase):
    pass


class User(Base):
    __tablename__ = "users"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(50))
    age: Mapped[int] = mapped_column()

    def __repr__(self) -> str:
        return f"User(id={self.id!r}, name={self.name!r}, age={self.age!r})"


Base.metadata.create_all(engine)

with Session.begin() as session:
    session.add_all(
        [
            User(name="Alice", age=30),
            User(name="Bob", age=25),
            User(name="Carol", age=35),
            User(name="Dave", age=28),
            User(name="Eve", age=22),
        ]
    )

with Session() as session:
    # (a) 30+, ordered by name descending
    print("30+ desc:", session.scalars(
        select(User).where(User.age >= 30).order_by(User.name.desc())
    ).all())

    # (b) page 2, 2 per page
    print("Page 2:", session.scalars(
        select(User).order_by(User.id).limit(2).offset(2)
    ).all())

    # (c) total
    print("Total:", session.scalar(select(func.count()).select_from(User)))
```

```text
30+ desc: [User(id=3, name='Carol', age=35), User(id=1, name='Alice', age=30)]
Page 2: [User(id=3, name='Carol', age=35), User(id=4, name='Dave', age=28)]
Total: 5
```

### Exercise 5 — Aggregations and grouping

```python
from sqlalchemy import ForeignKey, String, create_engine, func, select
from sqlalchemy.orm import DeclarativeBase, Mapped, mapped_column, relationship, sessionmaker

engine = create_engine("sqlite+pysqlite:///:memory:")
Session = sessionmaker(bind=engine)


class Base(DeclarativeBase):
    pass


class Author(Base):
    __tablename__ = "authors"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(80))
    books: Mapped[list["Book"]] = relationship(back_populates="author")


class Book(Base):
    __tablename__ = "books"

    id: Mapped[int] = mapped_column(primary_key=True)
    title: Mapped[str] = mapped_column(String(120))
    author_id: Mapped[int] = mapped_column(ForeignKey("authors.id"))
    author: Mapped["Author"] = relationship(back_populates="books")


Base.metadata.create_all(engine)

with Session.begin() as session:
    ada = Author(name="Ada")
    knuth = Author(name="Knuth")
    ada.books.append(Book(title="Notes"))
    knuth.books.append(Book(title="TAOCP Vol 1"))
    knuth.books.append(Book(title="TAOCP Vol 2"))
    knuth.books.append(Book(title="TAOCP Vol 3"))
    session.add_all([ada, knuth])

with Session() as session:
    counts = session.execute(
        select(Author.name, func.count(Book.id))
        .join(Author.books)
        .group_by(Author.id, Author.name)
        .order_by(func.count(Book.id).desc(), Author.name)
    ).all()
    print("Books per author:", counts)

    prolific = session.execute(
        select(Author.name, func.count(Book.id))
        .join(Author.books)
        .group_by(Author.id, Author.name)
        .having(func.count(Book.id) >= 2)
        .order_by(Author.name)
    ).all()
    print("2+ books:", prolific)
```

```text
Books per author: [('Knuth', 3), ('Ada', 1)]
2+ books: [('Knuth', 3)]
```

### Exercise 6 — Many-to-many

```python
from sqlalchemy import Column, ForeignKey, String, Table, create_engine, select
from sqlalchemy.orm import DeclarativeBase, Mapped, mapped_column, relationship, sessionmaker

engine = create_engine("sqlite+pysqlite:///:memory:")
Session = sessionmaker(bind=engine)


class Base(DeclarativeBase):
    pass


enrollment = Table(
    "enrollment",
    Base.metadata,
    Column("student_id", ForeignKey("students.id"), primary_key=True),
    Column("course_id", ForeignKey("courses.id"), primary_key=True),
)


class Student(Base):
    __tablename__ = "students"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(80))
    courses: Mapped[list["Course"]] = relationship(
        secondary=enrollment, back_populates="students"
    )

    def __repr__(self) -> str:
        return f"Student(id={self.id!r}, name={self.name!r})"


class Course(Base):
    __tablename__ = "courses"

    id: Mapped[int] = mapped_column(primary_key=True)
    title: Mapped[str] = mapped_column(String(120))
    students: Mapped[list["Student"]] = relationship(
        secondary=enrollment, back_populates="courses"
    )

    def __repr__(self) -> str:
        return f"Course(id={self.id!r}, title={self.title!r})"


Base.metadata.create_all(engine)

with Session.begin() as session:
    alice = Student(name="Alice")
    bob = Student(name="Bob")
    databases = Course(title="Databases")
    networks = Course(title="Networks")
    alice.courses = [databases, networks]
    bob.courses = [databases]
    session.add_all([alice, bob])

with Session() as session:
    alice = session.scalars(select(Student).where(Student.name == "Alice")).one()
    print("Alice's courses:", alice.courses)

    enrollees = session.scalars(
        select(Student).join(Student.courses).where(Course.title == "Databases")
    ).all()
    print("In Databases:", enrollees)
```

```text
Alice's courses: [Course(id=1, title='Databases'), Course(id=2, title='Networks')]
In Databases: [Student(id=1, name='Alice'), Student(id=2, name='Bob')]
```

### Exercise 7 — Fix the N+1 problem

```python
from sqlalchemy import ForeignKey, String, create_engine, event, select
from sqlalchemy.orm import DeclarativeBase, Mapped, mapped_column, relationship, selectinload, sessionmaker

engine = create_engine("sqlite+pysqlite:///:memory:")
Session = sessionmaker(bind=engine)

# Count every SQL statement that reaches the database
query_count = 0

@event.listens_for(engine, "before_cursor_execute")
def count_queries(*args, **kwargs):
    global query_count
    query_count += 1


class Base(DeclarativeBase):
    pass


class User(Base):
    __tablename__ = "users"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(50))
    posts: Mapped[list["Post"]] = relationship(back_populates="author")


class Post(Base):
    __tablename__ = "posts"

    id: Mapped[int] = mapped_column(primary_key=True)
    title: Mapped[str] = mapped_column(String(120))
    user_id: Mapped[int] = mapped_column(ForeignKey("users.id"))
    author: Mapped["User"] = relationship(back_populates="posts")


Base.metadata.create_all(engine)

with Session.begin() as session:
    for name in ("Alice", "Bob", "Carol"):
        user = User(name=name)
        user.posts = [Post(title=f"{name} post {i}") for i in (1, 2)]
        session.add(user)


def report(label: str):
    global query_count
    query_count = 0
    with Session() as session:
        users = session.scalars(select(User)).all()
        for user in users:
            print(f"  {user.name} ->", [p.title for p in user.posts])   # lazy loads here
    print(f"{label}: {query_count} queries")


report("LAZY  ")

query_count = 0
with Session() as session:
    users = session.scalars(select(User).options(selectinload(User.posts))).all()
    for user in users:
        print(f"  {user.name} ->", [p.title for p in user.posts])
print(f"EAGER : {query_count} queries")
```

```text
  Alice -> ['Alice post 1', 'Alice post 2']
  Bob -> ['Bob post 1', 'Bob post 2']
  Carol -> ['Carol post 1', 'Carol post 2']
LAZY  : 4 queries        # 1 for users + 3 for posts = N+1
  Alice -> ['Alice post 1', 'Alice post 2']
  Bob -> ['Bob post 1', 'Bob post 2']
  Carol -> ['Carol post 1', 'Carol post 2']
EAGER : 2 queries        # 1 for users + 1 for posts (WHERE user_id IN (...))
```

### Exercise 8 — Transactions

```python
from sqlalchemy import String, create_engine, select
from sqlalchemy.orm import DeclarativeBase, Mapped, mapped_column, sessionmaker

engine = create_engine("sqlite+pysqlite:///:memory:")
Session = sessionmaker(bind=engine)


class Base(DeclarativeBase):
    pass


class Account(Base):
    __tablename__ = "accounts"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(50), unique=True)
    balance: Mapped[int] = mapped_column(default=0)

    def __repr__(self) -> str:
        return f"Account(name={self.name!r}, balance={self.balance})"


Base.metadata.create_all(engine)

with Session.begin() as session:
    session.add_all([Account(name="alice", balance=500), Account(name="bob", balance=100)])


def transfer(session, from_name: str, to_name: str, amount: int) -> None:
    sender = session.scalars(select(Account).where(Account.name == from_name)).one()
    recipient = session.scalars(select(Account).where(Account.name == to_name)).one()
    if sender.balance < amount:
        raise ValueError(f"Insufficient funds in {from_name}")
    sender.balance -= amount
    recipient.balance += amount


# Success: 100 moves from alice to bob
with Session.begin() as session:
    transfer(session, "alice", "bob", 100)

with Session() as session:
    print("After transfer:", session.scalars(select(Account).order_by(Account.name)).all())

# Failure: bob (100) cannot pay 10_000 -> ValueError -> automatic rollback
failed = None
try:
    with Session.begin() as session:
        transfer(session, "bob", "alice", 10_000)
except ValueError as exc:
    failed = exc

with Session() as session:
    print("Failed with:", failed)
    print("Balances unchanged:", session.scalars(select(Account).order_by(Account.name)).all())
```

```text
After transfer: [Account(name='alice', balance=400), Account(name='bob', balance=200)]
Failed with: Insufficient funds in bob
Balances unchanged: [Account(name='alice', balance=400), Account(name='bob', balance=200)]
```

The `ValueError` fired *after* the debit had already been applied in memory — but because `Session.begin()` rolled the whole transaction back, the database never saw the change.

### Exercise 9 — Migration with Alembic

**1. Update the model** (in `blog_app/models.py`):

```python
class Post(Base):
    ...
    published: Mapped[bool] = mapped_column(server_default="1")   # existing rows -> True
```

**2. Generate the migration** (autogenerate diffs models vs. database):

```bash
alembic revision --autogenerate -m "add published column to posts"
```

**3. Review the generated file** — it should contain something like:

```python
def upgrade() -> None:
    op.add_column("posts", sa.Column("published", sa.Boolean(), server_default="1", nullable=False))


def downgrade() -> None:
    op.drop_column("posts", "published")
```

**4. Apply and verify:**

```bash
alembic upgrade head
alembic current      # shows the new revision as (head)
```

**5. Second migration — index on `Post.title`:**

```bash
alembic revision --autogenerate -m "index posts.title"
```

```python
def upgrade() -> None:
    op.create_index(op.f("ix_posts_title"), "posts", ["title"], unique=False)
```

```bash
alembic upgrade head
```

### Exercise 10 — Subqueries and combined reports

```python
from sqlalchemy import ForeignKey, String, Text, create_engine, func, select
from sqlalchemy.orm import DeclarativeBase, Mapped, mapped_column, relationship, sessionmaker

engine = create_engine("sqlite+pysqlite:///:memory:")
Session = sessionmaker(bind=engine)


class Base(DeclarativeBase):
    pass


class User(Base):
    __tablename__ = "users"

    id: Mapped[int] = mapped_column(primary_key=True)
    username: Mapped[str] = mapped_column(String(50))
    posts: Mapped[list["Post"]] = relationship(back_populates="author")
    comments: Mapped[list["Comment"]] = relationship(back_populates="author")


class Post(Base):
    __tablename__ = "posts"

    id: Mapped[int] = mapped_column(primary_key=True)
    title: Mapped[str] = mapped_column(String(200))
    user_id: Mapped[int] = mapped_column(ForeignKey("users.id"))
    author: Mapped["User"] = relationship(back_populates="posts")
    comments: Mapped[list["Comment"]] = relationship(back_populates="post")


class Comment(Base):
    __tablename__ = "comments"

    id: Mapped[int] = mapped_column(primary_key=True)
    body: Mapped[str] = mapped_column(Text)
    post_id: Mapped[int] = mapped_column(ForeignKey("posts.id"))
    user_id: Mapped[int] = mapped_column(ForeignKey("users.id"))
    post: Mapped["Post"] = relationship(back_populates="comments")
    author: Mapped["User"] = relationship(back_populates="comments")


Base.metadata.create_all(engine)

with Session.begin() as session:
    alice = User(username="alice")
    bob = User(username="bob")
    carol = User(username="carol")          # no posts, no comments
    p1 = Post(title="One")
    p1.author = alice
    p2 = Post(title="Two")
    p2.author = alice
    p3 = Post(title="Three")
    p3.author = bob
    c1 = Comment(body="Nice!", post=p1, author=bob)
    c2 = Comment(body="Thanks", post=p3, author=alice)
    session.add_all([alice, bob, carol, p1, p2, p3, c1, c2])

# Per-user aggregates as subqueries, then outer-joined to users.
post_counts = (
    select(Post.user_id, func.count(Post.id).label("num_posts"))
    .group_by(Post.user_id)
    .subquery()
)
comment_counts = (
    select(Comment.user_id, func.count(Comment.id).label("num_comments"))
    .group_by(Comment.user_id)
    .subquery()
)

with Session() as session:
    rows = session.execute(
        select(
            User.username,
            func.coalesce(post_counts.c.num_posts, 0),
            func.coalesce(comment_counts.c.num_comments, 0),
        )
        .outerjoin(post_counts, post_counts.c.user_id == User.id)
        .outerjoin(comment_counts, comment_counts.c.user_id == User.id)
        .order_by(User.username)
    ).all()
    print("username | posts | comments")
    for username, posts, comments in rows:
        print(f"{username:8} | {posts:5} | {comments}")
```

```text
username | posts | comments
alice    |     2 | 1
bob      |     1 | 1
carol    |     0 | 0
```

Notes:

- Counting from two different tables in one query would multiply rows (posts × comments per user); separate subqueries avoid that.
- `coalesce(..., 0)` turns the missing subquery row (no posts/comments) into `0`.

---

## Further Reading

- Official docs: [SQLAlchemy 2.0 Tutorial](https://docs.sqlalchemy.org/en/20/tutorial/), [ORM API reference](https://docs.sqlalchemy.org/en/20/orm/), [Alembic docs](https://alembic.sqlalchemy.org/)
- alembic naming conventions: https://docs.sqlalchemy.org/en/20/core/metadata.html#naming-conventions
- For web apps, see how sessions integrate with frameworks: FastAPI + SQLAlchemy sessions — https://fastapi.tiangolo.com/tutorial/sql-databases/

