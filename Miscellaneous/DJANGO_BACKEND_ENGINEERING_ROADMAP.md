# Django & Python Backend Engineering — Job-Ready Roadmap

> A comprehensive, deeply structured learning guide that takes you from Python developer to **job-ready professional Django/Python Backend Engineer**.
>
> 📚 Textbook + Course + Practical Lab + Project Roadmap + Interview Preparation + Software Engineering Handbook

---

## How to Use This Guide

🎯 **Goal:** By the end of this guide you will be able to design, build, test, secure, optimize, deploy, monitor, and maintain production-grade backend systems using Django, PostgreSQL, and the broader Python ecosystem.

This is not a superficial Django tutorial. It teaches you to **think like a software engineer**, not merely like someone who knows Django.

### Learning Philosophy

1. **WHY before HOW.** Every concept is introduced by the problem it solves.
2. **First principles.** Nothing is "just magic" — we explain internals.
3. **Progressive difficulty.** Concepts build on prerequisites.
4. **30% theory + 70% implementation.** Reading without coding is tutorial-dependency.
5. **Production-first thinking.** Every concept includes what changes in production.
6. **Interview-ready.** Every phase includes categorized interview questions.

### Three Questions This Guide Answers Continuously

1. **What am I learning?**
2. **Why does it matter?**
3. **Can I actually build something with it?**

---

## The Learning Progression

```text
Development Environment Setup
      ↓
Python for Professional Backend Development
      ↓
Software Engineering Fundamentals
      ↓
Git and Professional Workflow
      ↓
Web Development Fundamentals
      ↓
Django Fundamentals
      ↓
Django Models and ORM
      ↓
SQL and PostgreSQL
      ↓
Authentication and Authorization
      ↓
Django REST Framework
      ↓
API Security
      ↓
Redis and Caching
      ↓
Celery and Background Jobs
      ↓
Testing
      ↓
Docker
      ↓
Linux and Server Fundamentals
      ↓
Production Django
      ↓
CI/CD
      ↓
Observability
      ↓
Performance Engineering
      ↓
System Design
      ↓
Design Patterns
      ↓
Architecture
      ↓
Real-World Projects
      ↓
Final Capstone
      ↓
Job-Ready Software Engineer
```

---

## Phase Map

| Phase | Topic | Goal |
|---|---|---|
| 0 | Development Environment | Set up a professional Python/Django development environment |
| 1 | Python for Backend Development | Master Python from fundamentals to async |
| 2 | Software Engineering Fundamentals | Learn SOLID, DRY, clean code, and professional practices |
| 3 | Git and Professional Workflow | Git from beginner to team-level workflows |
| 4 | Web Development Fundamentals | HTTP, networking, APIs — before Django |
| 5 | Django Fundamentals | Django's architecture, request lifecycle, MVT |
| 6 | Django Models and ORM | Deep ORM mastery, N+1, QuerySets, transactions |
| 7 | SQL and PostgreSQL | SQL fundamentals through advanced PostgreSQL |
| 8 | Authentication and Authorization | Sessions, passwords, RBAC, permissions |
| 9 | Django REST Framework | APIs from fundamentals to production |
| 10 | API Security | CSRF, CORS, XSS, JWT, threat mitigation |
| 11 | Redis and Caching | Caching strategies, invalidation, Redis primitives |
| 12 | Celery and Background Jobs | Async processing, workers, scheduled tasks |
| 13 | Testing | pytest, TDD, mocking, integration testing |
| 14 | Docker | Containers, images, Docker Compose |
| 15 | Linux and Server Fundamentals | Enough Linux for a backend engineer |
| 16 | Production Django | Security, logging, reverse proxy, deployment |
| 17 | CI/CD | Automated pipelines with GitHub Actions |
| 18 | Observability | Logs, metrics, traces, health checks |
| 19 | Performance Engineering | Database optimization, profiling, load testing |
| 20 | System Design | Scalability, distributed systems, design problems |
| 21 | Design Patterns | Practical patterns for Python/Django |
| 22 | Architecture | Clean architecture, modular monoliths, DDD basics |
| 23 | Real-World Projects | Progressive project portfolio |
| 24 | Interview Preparation | Comprehensive technical interview prep |
| 25 | Portfolio and Job Search | Professional presentation and job hunting |

---

# Phase 0 — Development Environment

> **Prerequisite:** Basic computer literacy.
> **Goal:** Set up a professional, reproducible Python/Django development environment.

## 0.1 Why Your Environment Matters

### Concept

Your development environment is the foundation everything else builds on. A bad environment means wasted hours debugging setup issues instead of learning or building.

### Mental Model

Think of your environment as a **workshop**. A professional carpenter doesn't use rusty, dull tools — they invest in sharp, well-organized tools that make the work faster and more enjoyable.

### What You Need

| Tool | Purpose |
|---|---|
| **Python 3.12+** | The language runtime |
| **pyenv** | Python version management |
| **virtual environments** | Isolate project dependencies |
| **pip** | Package installation |
| **pyproject.toml** | Project metadata and dependencies |
| **VS Code** | IDE with Python support |
| **Git** | Version control |
| **Ruff** | Linting and formatting |
| **mypy/pyright** | Type checking |

## 0.2 Python Installation

### pyenv (Recommended)

```bash
# Install pyenv (Linux/macOS)
curl https://pyenv.run | bash

# Install Python
pyenv install 3.12.0
pyenv local 3.12.0

# Verify
python --version
```

### Virtual Environments

**Why:** Each project may need different package versions. Virtual environments prevent conflicts.

```bash
# Create a virtual environment
python -m venv .venv

# Activate (Linux/macOS)
source .venv/bin/activate

# Activate (Windows)
.venv\Scripts\activate

# Deactivate
deactivate
```

### Mental Model

```text
System Python          →  global tools
Virtual Environment    →  project-specific dependencies
pyenv                  →  Python version management
```

## 0.3 Package Management

### pip

```bash
# Install a package
pip install django

# Install from requirements
pip install -r requirements.txt

# Freeze dependencies
pip freeze > requirements.txt
```

### pyproject.toml (Modern Standard)

```toml
[project]
name = "my-project"
version = "0.1.0"
requires-python = ">=3.12"
dependencies = [
    "django>=5.1",
    "djangorestframework>=3.15",
    "psycopg2-binary>=2.9",
    "redis>=5.0",
]

[project.optional-dependencies]
dev = [
    "pytest>=8.0",
    "pytest-django>=4.8",
    "ruff>=0.5",
    "mypy>=1.10",
]
```

### uv (Modern Alternative)

```bash
# Install uv
pip install uv

# Create project
uv init my-project
cd my-project

# Add dependencies
uv add django djangorestframework

# Run scripts
uv run python manage.py runserver
```

## 0.4 Environment Variables

### .env Files

```bash
# .env (never commit this file!)
DEBUG=True
SECRET_KEY=your-secret-key
DATABASE_URL=postgres://user:pass@localhost:5432/mydb
REDIS_URL=redis://localhost:6379/0
```

### .env.example (commit this)

```bash
# .env.example (commit this — tells others what variables they need)
DEBUG=True
SECRET_KEY=change-me
DATABASE_URL=postgres://user:pass@localhost:5432/mydb
REDIS_URL=redis://localhost:6379/0
```

### .gitignore

```gitignore
# Python
__pycache__/
*.py[cod]
.venv/
*.egg-info/

# Environment
.env
.env.local

# IDE
.vscode/
.idea/

# Django
db.sqlite3
media/
staticfiles/
```

## 0.5 IDE Configuration

### VS Code Settings

```json
{
  "python.defaultInterpreterPath": ".venv/bin/python",
  "editor.formatOnSave": true,
  "editor.codeActionsOnSave": {
    "source.fixAll.ruff": "explicit",
    "source.organizeImports.ruff": "explicit"
  },
  "[python]": {
    "editor.defaultFormatter": "charliermarsh.ruff"
  },
  "python.analysis.typeCheckingMode": "basic"
}
```

### Recommended Extensions

- **Python** (ms-python)
- **Ruff** (charliermarsh.ruff)
- **Pylance** (ms-python.vscode-pylance)
- **GitLens** (eamodio.gitlens)

## 0.6 Linting and Formatting

### Ruff

```bash
# Lint
ruff check .

# Format
ruff format .

# Fix auto-fixable issues
ruff check --fix .
```

### Why These Tools Exist

| Tool | Purpose | Why |
|---|---|---|
| **Ruff** | Linting + formatting | Catches bugs, enforces style, much faster than flake8/black |
| **mypy/pyright** | Type checking | Catches type errors before runtime |
| **isort** (in Ruff) | Import sorting | Consistent import order |
| **Black** (in Ruff) | Code formatting | Consistent style across team |

## 0.7 Debugging in VS Code

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Django",
      "type": "debugpy",
      "request": "launch",
      "program": "${workspaceFolder}/manage.py",
      "args": ["runserver"],
      "autoReload": true
    }
  ]
}
```

## Common Beginner Mistakes

- 🚨 Installing packages globally instead of using virtual environments
- 🚨 Committing `.env` files with secrets
- 🚨 Not using type hints (you'll thank yourself later)
- 🚨 Skipping linting — bugs caught by linters are free to fix

## ✅ Phase 0 Checkpoint

- [ ] Python 3.12+ installed via pyenv
- [ ] Virtual environment created and activated
- [ ] pyproject.toml with dependencies configured
- [ ] .env and .gitignore set up
- [ ] VS Code configured with Python, Ruff, Pylance
- [ ] Can run `ruff check .` and `ruff format .`
- [ ] Can debug a Python script in VS Code

---

# Phase 1 — Python for Professional Backend Development

> **Prerequisite:** Phase 0. Basic programming concepts in any language.
> **Goal:** Master Python from fundamentals through async, OOP, and advanced features needed for Django development.

## 1.1 Python Fundamentals

### Variables and Data Types

```python
# Integers
age: int = 25

# Floats
price: float = 29.99

# Strings (immutable, UTF-8)
name: str = "Alice"
greeting = f"Hello, {name}!"  # f-strings (preferred)

# Booleans
is_active: bool = True

# None (absence of value)
result: str | None = None
```

### Collections

```python
# Lists (ordered, mutable)
scores: list[int] = [90, 85, 92]
scores.append(88)
scores[0]  # 90

# Tuples (ordered, immutable)
point: tuple[int, int] = (10, 20)

# Sets (unordered, unique)
unique_ids: set[int] = {1, 2, 3}

# Dictionaries (key-value, ordered since 3.7)
user: dict[str, str] = {"name": "Alice", "email": "alice@example.com"}
```

### Control Flow

```python
# If/elif/else
if score >= 90:
    grade = "A"
elif score >= 80:
    grade = "B"
else:
    grade = "C"

# For loops
for item in collection:
    process(item)

# While loops
while condition:
    do_something()
```

### Functions

```python
def calculate_total(items: list[dict], tax_rate: float = 0.08) -> float:
    """Calculate total price with tax."""
    subtotal = sum(item["price"] * item["quantity"] for item in items)
    return subtotal * (1 + tax_rate)
```

## 1.2 Intermediate Python

### List Comprehensions

```python
# Transform
squares = [x**2 for x in range(10)]

# Filter
evens = [x for x in range(10) if x % 2 == 0]

# Nested
matrix = [[i * j for j in range(3)] for i in range(3)]

# Dict comprehension
name_lengths = {name: len(name) for name in ["Alice", "Bob", "Charlie"]}
```

### Generators

```python
def fibonacci():
    """Infinite fibonacci sequence."""
    a, b = 0, 1
    while True:
        yield a
        a, b = b, a + b

# Generators are lazy — they produce values on demand
fib = fibonacci()
next(fib)  # 0
next(fib)  # 1

# Generator expression (like list comprehension, but lazy)
large_sum = sum(x**2 for x in range(1_000_000))  # no intermediate list
```

### Why Generators Matter

```python
# BAD: loads entire file into memory
def get_lines_bad(filepath: str) -> list[str]:
    with open(filepath) as f:
        return f.readlines()  # 1GB file = 1GB in memory

# GOOD: yields one line at a time
def get_lines_good(filepath: str):
    with open(filepath) as f:
        for line in f:
            yield line.strip()  # 1GB file = ~0 memory

# In Django: QuerySets are lazy like generators
queryset = User.objects.all()  # no database hit yet
for user in queryset:          # database hit NOW
    process(user)
```

### Decorators

```python
import functools
import time

def timing_decorator(func):
    """Measure function execution time."""
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        start = time.perf_counter()
        result = func(*args, **kwargs)
        elapsed = time.perf_counter() - start
        print(f"{func.__name__} took {elapsed:.4f}s")
        return result
    return wrapper

@timing_decorator
def slow_function():
    time.sleep(1)

# Django decorators you'll use
from django.contrib.auth.decorators import login_required
from django.views.decorators.cache import cache_page

@login_required
def my_view(request):
    ...

@cache_page(60 * 15)  # Cache for 15 minutes
def my_api_view(request):
    ...
```

### Context Managers

```python
# Custom context manager
class DatabaseConnection:
    def __enter__(self):
        self.connection = create_connection()
        return self.connection

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.connection.close()
        return False  # Don't suppress exceptions

# Usage
with DatabaseConnection() as conn:
    conn.execute("SELECT * FROM users")

# File handling
with open("data.txt") as f:
    content = f.read()

# Django's ORM uses context managers for transactions
from django.db import transaction

with transaction.atomic():
    user = User.objects.create(username="alice")
    Profile.objects.create(user=user)
    # Both succeed or both roll back
```

### Lambda Functions

```python
# Simple transformations
add_one = lambda x: x + 1

# Sorting
users_sorted = sorted(users, key=lambda u: u["name"])

# With map/filter
names = list(map(lambda u: u["name"], users))
admins = list(filter(lambda u: u["is_admin"], users))

# Better with comprehensions (usually)
names = [u["name"] for u in users]
admins = [u for u in users if u["is_admin"]]
```

### *args and **kwargs

```python
def log_message(level: str, *args: str, **kwargs: str) -> None:
    """Flexible function signature."""
    print(f"[{level}] {' '.join(args)}")
    for key, value in kwargs.items():
        print(f"  {key}: {value}")

log_message("ERROR", "Database", "connection", "failed",
            host="localhost", port=5432)
# [ERROR] Database connection failed
#   host: localhost
#   port: 5432
```

## 1.3 Object-Oriented Programming

### Classes and Objects

```python
from dataclasses import dataclass
from datetime import datetime

@dataclass
class User:
    """Represents a user in the system."""
    username: str
    email: str
    created_at: datetime
    is_active: bool = True

    def deactivate(self) -> None:
        self.is_active = False

    @property
    def display_name(self) -> str:
        return self.username.title()
```

### Inheritance and Composition

```python
# Inheritance (use sparingly)
class Admin(User):
    def __init__(self, username: str, email: str, permissions: list[str]):
        super().__init__(username, email, datetime.now())
        self.permissions = permissions

    def has_permission(self, permission: str) -> bool:
        return permission in self.permissions

# Composition (preferred for most cases)
class UserService:
    """Handles user-related business logic."""
    def __init__(self, repository: UserRepository, mailer: EmailService):
        self.repository = repository
        self.mailer = mailer

    def create_user(self, data: dict) -> User:
        user = self.repository.create(data)
        self.mailer.send_welcome(user.email)
        return user
```

### Polymorphism

```python
from abc import ABC, abstractmethod

class NotificationSender(ABC):
    @abstractmethod
    def send(self, recipient: str, message: str) -> bool:
        ...

class EmailSender(NotificationSender):
    def send(self, recipient: str, message: str) -> bool:
        # Send email
        return True

class SMSSender(NotificationSender):
    def send(self, recipient: str, message: str) -> bool:
        # Send SMS
        return True

# Both work the same way
def notify(sender: NotificationSender, recipient: str, message: str) -> bool:
    return sender.send(recipient, message)

notify(EmailSender(), "alice@example.com", "Welcome!")
notify(SMSSender(), "+1234567890", "Your code is 1234")
```

### Interfaces/Protocols (Python's Approach)

```python
from typing import Protocol, runtime_checkable

@runtime_checkable
class CacheBackend(Protocol):
    """Any object that implements get/set is a CacheBackend."""
    def get(self, key: str) -> str | None: ...
    def set(self, key: str, value: str, ttl: int = 300) -> None: ...

class RedisCache:
    def get(self, key: str) -> str | None:
        return self.redis.get(key)

    def set(self, key: str, value: str, ttl: int = 300) -> None:
        self.redis.setex(key, ttl, value)

class FileCache:
    def get(self, key: str) -> str | None:
        path = Path(f"cache/{key}")
        return path.read_text() if path.exists() else None

    def set(self, key: str, value: str, ttl: int = 300) -> None:
        Path(f"cache/{key}").write_text(value)

# Both work — no inheritance needed
def get_from_cache(cache: CacheBackend, key: str) -> str | None:
    return cache.get(key)
```

## 1.4 Advanced Python

### Type Hints (Professional Standard)

```python
from typing import TypeAlias
from collections.abc import Sequence, Callable

# Basic
def process_items(items: list[str]) -> dict[str, int]:
    return {item: len(item) for item in items}

# Complex types
UserDict: TypeAlias = dict[str, str | int | bool]

def create_user(name: str, **kwargs: str | int) -> dict[str, str | int]:
    return {"name": name, **kwargs}

# Generic types
def first_or_default(items: Sequence[T], default: T) -> T:
    return items[0] if items else default
```

### Custom Exceptions

```python
class AppError(Exception):
    """Base application error."""
    pass

class ValidationError(AppError):
    """Raised when input validation fails."""
    def __init__(self, field: str, message: str):
        self.field = field
        self.message = message
        super().__init__(f"{field}: {message}")

class NotFoundError(AppError):
    """Raised when a resource is not found."""
    def __init__(self, resource: str, identifier: str):
        self.resource = resource
        self.identifier = identifier
        super().__init__(f"{resource} with id '{identifier}' not found")

class PermissionDenied(AppError):
    """Raised when user lacks permission."""
    pass

# Usage
def get_user(user_id: int) -> User:
    try:
        return User.objects.get(id=user_id)
    except User.DoesNotExist:
        raise NotFoundError("User", str(user_id))
```

### Logging

```python
import logging

logger = logging.getLogger(__name__)

def process_order(order_id: int) -> None:
    logger.info("Processing order %s", order_id)
    try:
        order = Order.objects.get(id=order_id)
        order.process()
        logger.info("Order %s processed successfully", order_id)
    except Order.DoesNotExist:
        logger.error("Order %s not found", order_id)
        raise
    except Exception:
        logger.exception("Failed to process order %s", order_id)
        raise
```

## 1.5 Async Python

### Synchronous vs Asynchronous

```text
Synchronous:  Task A → wait → Task A → wait → Task A (sequential)
Asynchronous: Task A → Task B → Task C → Task A → Task B (concurrent)
```

### When to Use Each

| Use Case | Approach |
|---|---|
| Django views (traditional) | Synchronous |
| Django views with ORM | Synchronous (Django ORM is sync) |
| HTTP requests to external APIs | Async (with httpx/aiohttp) |
| Background tasks | Celery (separate process) |
| Real-time (WebSockets) | Django Channels (async) |
| Simple CRUD API | Synchronous is fine |

### asyncio Basics

```python
import asyncio
import httpx

async def fetch_url(url: str) -> str:
    """Fetch a URL asynchronously."""
    async with httpx.AsyncClient() as client:
        response = await client.get(url)
        return response.text

async def main():
    # Sequential (slow)
    result1 = await fetch_url("https://api.example.com/users")
    result2 = await fetch_url("https://api.example.com/posts")

    # Concurrent (fast)
    result1, result2 = await asyncio.gather(
        fetch_url("https://api.example.com/users"),
        fetch_url("https://api.example.com/posts"),
    )

asyncio.run(main())
```

### Threading and Multiprocessing

```python
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor

# Threading: good for I/O-bound tasks
def fetch_all(urls: list[str]) -> list[str]:
    with ThreadPoolExecutor(max_workers=10) as executor:
        return list(executor.map(fetch_url, urls))

# Multiprocessing: good for CPU-bound tasks
def compute_all(data: list[list[float]]) -> list[float]:
    with ProcessPoolExecutor() as executor:
        return list(executor.map(expensive_calculation, data))

# In Django: use Celery for background tasks, not raw threading
```

### Common Mistakes

- 🚨 Using async Django views when the ORM is synchronous (causes thread pool issues)
- 🚨 Creating new event loops (use `asyncio.run()` only at the top level)
- 🚨 Blocking in async code (`time.sleep()` instead of `await asyncio.sleep()`)
- 🚨 Using threads for database operations (use connection pooling instead)

## ✅ Phase 1 Checkpoint

### What I Should Know

- [ ] Python data types, control flow, functions
- [ ] List/dict/set comprehensions
- [ ] Generators and lazy evaluation
- [ ] Decorators (writing and using)
- [ ] Context managers
- [ ] OOP: classes, inheritance, composition, polymorphism
- [ ] Protocols and structural subtyping
- [ ] Type hints (intermediate level)
- [ ] Custom exceptions
- [ ] Logging basics
- [ ] Async/await basics, threading, multiprocessing
- [ ] When to use sync vs async

### Interview Questions

**Beginner:**
1. What's the difference between a list and a tuple?
2. What are decorators and why would you use one?
3. What is `None` in Python?

**Intermediate:**
4. Explain generators vs list comprehensions. When do you prefer one?
5. What's the difference between `*args` and `**kwargs`?
6. Explain the GIL. How does it affect threading?
7. What is a context manager? Implement one using `__enter__` and `__exit__`.

**Advanced:**
8. When would you use async Python in Django?
9. Explain Protocol vs ABC. When do you prefer each?
10. What are the trade-offs between inheritance and composition?

### Coding Challenge

Build a `Cache` class that:
- Stores key-value pairs with TTL
- Implements the context manager protocol
- Supports both dict-style and method-style access
- Has type hints throughout
- Includes logging

---

# Phase 2 — Software Engineering Fundamentals

> **Prerequisite:** Phase 1. Comfortable with Python.
> **Goal:** Learn professional engineering practices that distinguish junior from senior engineers.

## 2.1 SDLC (Software Development Life Cycle)

### The Phases

```text
Requirements → Design → Implementation → Testing → Deployment → Maintenance
     ↑                                                              |
     └──────────────────────── Feedback Loop ───────────────────────┘
```

### Why It Matters

Professional software isn't "write code, ship it." It's a structured process:

1. **Requirements:** What should it do? (User stories, acceptance criteria)
2. **Design:** How will it work? (Architecture, data models, APIs)
3. **Implementation:** Build it (Code, commit, review)
4. **Testing:** Does it work correctly? (Unit, integration, E2E)
5. **Deployment:** Ship it (CI/CD, staging, production)
6. **Maintenance:** Keep it working (Bug fixes, monitoring, scaling)

## 2.2 SOLID Principles

### Single Responsibility Principle (SRP)

```python
# BAD: One class does everything
class UserManager:
    def create_user(self, data): ...
    def send_email(self, user, message): ...
    def generate_report(self, users): ...
    def validate_input(self, data): ...

# GOOD: Each class has one reason to change
class UserService:
    def create_user(self, data): ...

class EmailService:
    def send_email(self, user, message): ...

class ReportGenerator:
    def generate_report(self, users): ...

class InputValidator:
    def validate(self, data): ...
```

### Open/Closed Principle (OCP)

```python
# BAD: Must modify class to add new notification types
class NotificationService:
    def send(self, type: str, recipient: str, message: str):
        if type == "email":
            self._send_email(recipient, message)
        elif type == "sms":
            self._send_sms(recipient, message)
        # Must add elif for every new type!

# GOOD: Open for extension, closed for modification
class NotificationSender(Protocol):
    def send(self, recipient: str, message: str) -> bool: ...

class NotificationService:
    def __init__(self, senders: list[NotificationSender]):
        self.senders = senders

    def send(self, recipient: str, message: str) -> None:
        for sender in self.senders:
            sender.send(recipient, message)
```

### Liskov Substitution Principle (LSP)

```python
# BAD: Subclass changes expected behavior
class Rectangle:
    def set_width(self, w): self.width = w
    def set_height(self, h): self.height = h
    def area(self): return self.width * self.height

class Square(Rectangle):
    def set_width(self, w):
        self.width = w
        self.height = w  # ← surprises callers expecting independent width/height

# GOOD: Don't force inheritance where composition fits
# A Square IS-NOT-A Rectangle in terms of behavior
```

### Interface Segregation Principle (ISP)

```python
# BAD: Fat interface forces implementers to do unnecessary work
class FileSystem:
    def read(self, path: str) -> str: ...
    def write(self, path: str, data: str) -> None: ...
    def delete(self, path: str) -> None: ...
    def rename(self, old: str, new: str) -> None: ...

# GOOD: Small, focused interfaces
class Readable(Protocol):
    def read(self, path: str) -> str: ...

class Writable(Protocol):
    def write(self, path: str, data: str) -> None: ...
```

### Dependency Inversion Principle (DIP)

```python
# BAD: High-level module depends on low-level module
class OrderService:
    def __init__(self):
        self.db = MySQLDatabase()  # ← hard-coded dependency

# GOOD: Depend on abstractions
class OrderService:
    def __init__(self, repository: OrderRepository):  # ← abstract dependency
        self.repository = repository

# Different implementations
class SQLOrderRepository:
    def get(self, id: int) -> Order: ...

class InMemoryOrderRepository:  # For testing
    def get(self, id: int) -> Order: ...
```

## 2.3 DRY, KISS, YAGNI

### DRY (Don't Repeat Yourself)

```python
# BAD
def calculate_tax_price(price: float) -> float:
    return price * 1.2

def calculate_shipping_price(price: float) -> float:
    return price * 1.15

# GOOD
def apply_percentage(price: float, percentage: float) -> float:
    return price * (1 + percentage / 100)

calculate_tax_price = lambda p: apply_percentage(p, 20)
calculate_shipping_price = lambda p: apply_percentage(p, 15)
```

### KISS (Keep It Simple, Stupid)

```python
# BAD: Over-engineered
class DataProcessor:
    def __init__(self, strategy: ProcessingStrategy):
        self.strategy = strategy

    def process(self, data):
        return self.strategy.execute(data)

# GOOD: Simple function
def process_data(data: list[int]) -> int:
    return sum(data)
```

### YAGNI (You Aren't Gonna Need It)

```python
# BAD: Building for future requirements that don't exist
class PaymentProcessor:
    def process_stripe(self, amount): ...
    def process_paypal(self, amount): ...
    def process_bitcoin(self, amount): ...
    def process_wire_transfer(self, amount): ...
    def process_apple_pay(self, amount): ...
    # If you only support Stripe today, don't build the others

# GOOD: Build what you need now
class PaymentProcessor:
    def process(self, amount: float) -> PaymentResult:
        # Stripe integration
        ...
```

## 2.4 Clean Code Practices

### Readable Naming

```python
# BAD
def proc(d):
    r = []
    for x in d:
        if x[1] > 18:
            r.append(x)
    return r

# GOOD
def filter_adults(people: list[dict]) -> list[dict]:
    return [person for person in people if person["age"] > 18]
```

### Function Design

```python
# BAD: Function does too much
def handle_request(request):
    # 50 lines of validation, business logic, database operations,
    # email sending, and response formatting all in one function

# GOOD: Each function does one thing
def validate_request(data: dict) -> tuple[bool, list[str]]:
    ...

def create_order(user: User, data: dict) -> Order:
    ...

def send_confirmation_email(order: Order) -> None:
    ...

def format_order_response(order: Order) -> dict:
    ...

# Request handler
def handle_request(request):
    errors = validate_request(request.data)
    if errors:
        return Response({"errors": errors}, status=400)

    order = create_order(request.user, request.data)
    send_confirmation_email(order)
    return Response(format_order_response(order), status=201)
```

### Error Handling

```python
# BAD: Silently swallowing errors
def get_user(user_id):
    try:
        return User.objects.get(id=user_id)
    except:
        pass  # ← DANGEROUS: swallows everything including SystemExit

# GOOD: Specific handling with logging
def get_user(user_id: int) -> User:
    try:
        return User.objects.get(id=user_id)
    except User.DoesNotExist:
        logger.warning("User %s not found", user_id)
        raise NotFoundError("User", str(user_id))
```

## 2.5 Common Anti-Patterns

| Anti-Pattern | Problem | Solution |
|---|---|---|
| God function | One function doing everything | Split into focused functions |
| Spaghetti code | Untangled control flow | Extract functions, use early returns |
| Magic numbers | Unexplained constants | Named constants |
| Deep nesting | Hard to read | Guard clauses, early returns |
| Stringly typed | `"admin"` instead of `User.Role.ADMIN` | Enums, constants |

## ✅ Phase 2 Checkpoint

### What I Should Know

- [ ] SDLC phases
- [ ] SOLID principles with Django/Python examples
- [ ] DRY, KISS, YAGNI
- [ ] Clean code: naming, function design, error handling
- [ ] Common anti-patterns and their solutions

### Interview Questions

1. Explain SOLID with a Django example for each principle.
2. What is the difference between DRY and YAGNI? Can they conflict?
3. Show me bad code and explain how to refactor it.
4. When does "simple" code become "too simple"?

### Coding Challenge

Refactor a 100-line Django view function that handles user registration, validation, database operations, email sending, and response formatting into clean, testable functions following SOLID principles.

---

# Phase 3 — Git and Professional Workflow

> **Prerequisite:** Basic command line.
> **Goal:** Use Git professionally in a team environment.

## 3.1 Git Fundamentals

### Core Concepts

```text
Working Directory → Staging Area → Repository
     (edit)         (git add)      (git commit)
```

### Essential Commands

```bash
# Initialize
git init

# Stage and commit
git add <file>           # Stage specific file
git add .                # Stage all changes
git commit -m "message"  # Commit staged changes

# Status and history
git status               # See what's changed
git log --oneline        # Compact history
git diff                 # See unstaged changes
git diff --staged        # See staged changes
```

### Branching

```bash
# Create and switch
git checkout -b feature/user-auth
# or
git switch -c feature/user-auth

# List branches
git branch -a

# Switch branches
git switch main

# Delete branch
git branch -d feature/user-auth
```

### Merging vs Rebasing

```bash
# Merge (creates merge commit)
git checkout main
git merge feature/user-auth

# Rebase (linear history)
git checkout feature/user-auth
git rebase main
```

### When to Use Each

| Use Case | Approach |
|---|---|
| Merging feature branches | Rebase (cleaner history) |
| Public/shared branches | Merge (safe) |
| Cleaning up commits | Interactive rebase |
| Undoing changes | Reset/revert |

## 3.2 Advanced Git

### Interactive Rebase

```bash
# Clean up last 3 commits
git rebase -i HEAD~3

# In the editor:
pick abc1234 Add user model
squash def5678 Fix typo in model
squash ghi9012 Add tests
# Result: One clean commit "Add user model with tests"
```

### Stash

```bash
# Save working changes
git stash

# Save with message
git stash push -m "WIP: user auth"

# List stashes
git stash list

# Apply most recent
git stash pop

# Apply specific stash
git stash apply stash@{1}
```

### Cherry-Pick

```bash
# Apply specific commit to current branch
git cherry-pick abc1234
```

### Reset vs Revert

```bash
# Reset: undo commits (rewrites history)
git reset --soft HEAD~1    # Undo commit, keep changes staged
git reset --mixed HEAD~1   # Undo commit, keep changes unstaged
git reset --hard HEAD~1    # Undo commit, discard changes

# Revert: create new commit that undoes changes (safe for shared branches)
git revert abc1234
```

## 3.3 Professional Git Workflow

### Feature Branch Workflow

```text
main ────────────────────────────────── main
  │                                      ↑
  └── feature/user-auth ── PR ── merge ──┘
         │
         ├── commit: "Add User model"
         ├── commit: "Add authentication views"
         └── commit: "Add tests for auth"
```

### Commit Messages (Conventional Commits)

```text
<type>(<scope>): <description>

[optional body]

[optional footer]
```

**Types:**
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation
- `style`: Formatting (no code change)
- `refactor`: Code restructuring
- `test`: Adding tests
- `chore`: Build, CI, dependencies

**Examples:**
```text
feat(auth): add JWT authentication
fix(orders): prevent duplicate order submission
docs(api): update endpoint documentation
refactor(users): extract validation logic
test(auth): add login endpoint tests
```

### Pull Requests

```text
1. Create feature branch
2. Make changes, commit frequently
3. Push branch
4. Create PR with description
5. Request review
6. Address feedback
7. Merge (squash or rebase)
8. Delete feature branch
```

### Code Reviews

**As a reviewer, check for:**
1. Correctness — does it solve the problem?
2. Security — any vulnerabilities?
3. Tests — are there adequate tests?
4. Readability — can a new team member understand it?
5. Performance — any obvious bottlenecks?
6. Documentation — are complex parts explained?

**As an author, ensure:**
1. PR is small and focused
2. Description explains WHY, not just what
3. Tests pass
4. Code is formatted and linted
5. You've self-reviewed before requesting review

## 3.4 Merge Conflicts

### How to Resolve

```bash
# When merge conflict occurs:
# 1. Open the conflicted file
# 2. Look for conflict markers:
<<<<<<< HEAD
your changes
=======
their changes
>>>>>>> feature-branch

# 3. Choose/combine the changes
# 4. Remove conflict markers
# 5. Stage and commit
git add <file>
git commit
```

### Prevention

- Pull/rebase frequently
- Keep feature branches short-lived
- Communicate with team about shared files

## ✅ Phase 3 Checkpoint

### What I Should Know

- [ ] Basic Git operations (add, commit, push, pull)
- [ ] Branching and merging
- [ ] Interactive rebase for cleaning history
- [ ] Stash for temporary saves
- [ ] Reset vs revert (when to use each)
- [ ] Conventional commits
- [ ] Pull request workflow
- [ ] Code review best practices
- [ ] Merge conflict resolution

### Interview Questions

1. What's the difference between `git merge` and `git rebase`?
2. When would you use `git reset --hard` vs `git revert`?
3. Explain the Git object model (blobs, trees, commits).
4. How do you undo a pushed commit?
5. What's `git reflog` and when would you use it?

### Git Exercises

1. Create a repository, make 5 commits, then rebase them into 2 clean commits.
2. Create two branches, make conflicting changes, resolve the conflict.
3. Use `git bisect` to find which commit introduced a bug.

---

# Phase 4 — Web Development Fundamentals

> **Prerequisite:** Phases 0-3.
> **Goal:** Deeply understand HTTP, networking, and APIs before Django touches them.

## 4.1 HTTP Protocol

### Request/Response Cycle

```text
Client (Browser/API)                    Server
       │                                 │
       │──── HTTP Request ──────────────→│
       │     GET /api/users              │
       │     Host: example.com           │
       │     Accept: application/json    │
       │                                 │
       │←──── HTTP Response ─────────────│
       │      HTTP/1.1 200 OK            │
       │      Content-Type: app/json     │
       │      {"users": [...]}           │
```

### HTTP Methods

| Method | Purpose | Idempotent | Safe |
|---|---|---|---|
| `GET` | Read resource | Yes | Yes |
| `POST` | Create resource | No | No |
| `PUT` | Replace resource | Yes | No |
| `PATCH` | Partial update | No | No |
| `DELETE` | Delete resource | Yes | No |
| `OPTIONS` | Describe allowed methods | Yes | Yes |
| `HEAD` | Same as GET but no body | Yes | Yes |

### Status Codes

```text
2xx Success
  200 OK                    → Request succeeded
  201 Created               → Resource created
  204 No Content            → Success, no response body

3xx Redirection
  301 Moved Permanently     → Resource moved
  304 Not Modified          → Use cached version

4xx Client Error
  400 Bad Request           → Invalid input
  401 Unauthorized          → Not authenticated
  403 Forbidden             → Not authorized
  404 Not Found             → Resource doesn't exist
  409 Conflict              → State conflict
  422 Unprocessable Entity  → Validation error
  429 Too Many Requests     → Rate limited

5xx Server Error
  500 Internal Server Error → Server crashed
  502 Bad Gateway           → Upstream server error
  503 Service Unavailable   → Server overloaded
```

### Headers

```text
Request Headers:
  Host: example.com
  Accept: application/json
  Authorization: Bearer <token>
  Content-Type: application/json
  User-Agent: MyApp/1.0

Response Headers:
  Content-Type: application/json
  Cache-Control: max-age=3600
  X-Request-Id: abc-123
  Set-Cookie: session=xyz; HttpOnly; Secure
```

### Cookies and Sessions

```text
Cookie-based session:
1. Client sends GET /login with credentials
2. Server validates, creates session, sends Set-Cookie header
3. Client stores cookie
4. All subsequent requests include cookie
5. Server reads cookie, looks up session

Cookie attributes:
  HttpOnly  → JS cannot access (XSS protection)
  Secure    → Only sent over HTTPS
  SameSite  → CSRF protection (Strict/Lax/None)
  Path      → Only sent for specific paths
  Max-Age   → When cookie expires
```

## 4.2 Networking Fundamentals

### IP, Ports, TCP, UDP

```text
IP Address:  Unique address for a device on the network
              IPv4: 192.168.1.1
              IPv6: 2001:db8::1

Port:        Identifies a specific process/service
              HTTP: 80, HTTPS: 443, PostgreSQL: 5432, Redis: 6379

TCP:         Reliable, ordered delivery (HTTP, databases)
UDP:         Fast, no guarantees (DNS, video streaming)
```

### DNS Resolution

```text
User types "example.com"
    ↓
1. Browser checks local cache
    ↓
2. OS checks /etc/hosts
    ↓
3. Query to recursive resolver (ISP's DNS)
    ↓
4. Resolver checks root servers → TLD servers → authoritative server
    ↓
5. Returns IP: 93.184.216.34
    ↓
6. Browser connects to IP on port 443 (HTTPS)
```

### TLS/HTTPS

```text
1. Client sends ClientHello (supported ciphers, TLS version)
2. Server sends ServerHello (chosen cipher, certificate)
3. Client verifies certificate against CA chain
4. Key exchange (generate shared secret)
5. Encrypted communication begins
```

## 4.3 What Happens When You Type a URL

```text
1. DNS Resolution
   Browser → DNS → IP address

2. TCP Connection
   Browser → Three-way handshake → Server

3. TLS Handshake (if HTTPS)
   Certificate verification, key exchange

4. HTTP Request
   GET /api/users HTTP/2
   Host: api.example.com
   Accept: application/json

5. Server Processing
   Load balancer → Reverse proxy → Application → Database
   Route matching → Authentication → Business logic → Query

6. HTTP Response
   HTTP/2 200 OK
   Content-Type: application/json
   {"users": [...]}

7. Browser Rendering (for HTML)
   Parse HTML → Build DOM → Load CSS/JS → Execute → Paint
```

## 4.4 REST API Design

### Principles

```text
Resources:  Nouns, not verbs
            GET /users         (not GET /getUsers)
            POST /users        (not POST /createUser)

Endpoints:  Hierarchical
            /users/{id}/posts  (posts belonging to a user)

Stateless:  Every request contains all needed information
            Authorization header with JWT (not server-side session for APIs)
```

### Example API Design

```text
Users:
  GET    /api/v1/users/           → List users
  POST   /api/v1/users/           → Create user
  GET    /api/v1/users/{id}/      → Get user
  PUT    /api/v1/users/{id}/      → Update user (full)
  PATCH  /api/v1/users/{id}/      → Update user (partial)
  DELETE /api/v1/users/{id}/      → Delete user

Posts:
  GET    /api/v1/users/{id}/posts/       → User's posts
  POST   /api/v1/users/{id}/posts/       → Create post for user
  GET    /api/v1/posts/                   → List all posts
  GET    /api/v1/posts/{id}/              → Get post
  PATCH  /api/v1/posts/{id}/              → Update post
  DELETE /api/v1/posts/{id}/              → Delete post
```

### Response Format

```json
{
    "id": 1,
    "username": "alice",
    "email": "alice@example.com",
    "created_at": "2024-01-15T10:30:00Z",
    "profile": {
        "bio": "Software engineer",
        "avatar_url": "https://example.com/avatar.jpg"
    }
}
```

### Error Response Format

```json
{
    "error": {
        "code": "VALIDATION_ERROR",
        "message": "Invalid input data",
        "details": [
            {
                "field": "email",
                "message": "Enter a valid email address"
            },
            {
                "field": "password",
                "message": "Password must be at least 8 characters"
            }
        ]
    }
}
```

## ✅ Phase 4 Checkpoint

- [ ] Can explain the full request/response cycle
- [ ] Know all HTTP methods and when to use each
- [ ] Understand status codes (2xx, 3xx, 4xx, 5xx)
- [ ] Can describe DNS resolution and TLS handshake
- [ ] Can design a REST API for a given resource
- [ ] Understand cookies, sessions, and their differences

---

# Phase 5 — Django Fundamentals

> **Prerequisite:** Phases 0-4. Strong Python and web fundamentals.
> **Goal:** Understand Django's architecture, request lifecycle, and core concepts.

## 5.1 What Django Is

### Django Philosophy

```text
"Django is a high-level Python web framework that encourages
rapid development and clean, pragmatic design."

Core principles:
  1. Don't repeat yourself (DRY)
  2. Explicit is better than implicit
  3. Loose coupling
  4. Quick development
  5. Clean design
  6. Security by default
```

### Why Django

| Feature | Benefit |
|---|---|
| ORM | Database without raw SQL |
| Admin | Instant data management UI |
| Authentication | Built-in user system |
| Security | CSRF, XSS, SQL injection protection |
| URL routing | Clean URL design |
| Template engine | HTML generation |
| Middleware | Request/response pipeline |
| Migrations | Schema version control |

## 5.2 Project vs App

### Concept

```text
Project = entire website
  ├── app1 (a feature, e.g., users)
  ├── app2 (a feature, e.g., blog)
  └── app3 (a feature, e.g., payments)
```

### Mental Model

Think of a project as a **company** and apps as **departments**. Each department handles one area of responsibility.

### Creating

```bash
# Create project
django-admin startproject myproject .
# The "." puts files in current directory

# Create app
python manage.py startapp users
python manage.py startapp blog
```

### Project Structure

```text
myproject/
├── manage.py
├── myproject/
│   ├── __init__.py
│   ├── settings.py
│   ├── urls.py
│   ├── asgi.py
│   └── wsgi.py
├── users/
│   ├── __init__.py
│   ├── admin.py
│   ├── apps.py
│   ├── models.py
│   ├── views.py
│   ├── urls.py
│   └── tests.py
├── blog/
│   ├── ...
├── templates/
├── static/
└── .env
```

## 5.3 Settings Configuration

### settings.py Key Settings

```python
# Security
DEBUG = os.environ.get("DEBUG", "False") == "True"
SECRET_KEY = os.environ.get("SECRET_KEY")
ALLOWED_HOSTS = os.environ.get("ALLOWED_HOSTS", "").split(",")

# Database
DATABASES = {
    "default": {
        "ENGINE": "django.db.backends.postgresql",
        "NAME": os.environ.get("DB_NAME", "myproject"),
        "USER": os.environ.get("DB_USER", "postgres"),
        "PASSWORD": os.environ.get("DB_PASSWORD", ""),
        "HOST": os.environ.get("DB_HOST", "localhost"),
        "PORT": os.environ.get("DB_PORT", "5432"),
    }
}

# Apps
INSTALLED_APPS = [
    "django.contrib.admin",
    "django.contrib.auth",
    "django.contrib.contenttypes",
    "django.contrib.sessions",
    "django.contrib.messages",
    "django.contrib.staticfiles",
    # Third-party
    "rest_framework",
    # Local
    "users",
    "blog",
]

# Middleware
MIDDLEWARE = [
    "django.middleware.security.SecurityMiddleware",
    "django.contrib.sessions.middleware.SessionMiddleware",
    "django.middleware.common.CommonMiddleware",
    "django.middleware.csrf.CsrfViewMiddleware",
    "django.contrib.auth.middleware.AuthenticationMiddleware",
    "django.contrib.messages.middleware.MessageMiddleware",
    "django.middleware.clickjacking.XFrameOptionsMiddleware",
]
```

## 5.4 URL Routing

### URL Configuration

```python
# myproject/urls.py
from django.contrib import admin
from django.urls import path, include

urlpatterns = [
    path("admin/", admin.site.urls),
    path("api/users/", include("users.urls")),
    path("api/blog/", include("blog.urls")),
]

# users/urls.py
from django.urls import path
from . import views

urlpatterns = [
    path("", views.user_list, name="user-list"),
    path("<int:pk>/", views.user_detail, name="user-detail"),
]
```

### URL Patterns

```python
from django.urls import path, re_path

urlpatterns = [
    # Simple
    path("users/", views.user_list),
    # With parameter
    path("users/<int:pk>/", views.user_detail),
    # With slug
    path("posts/<slug:slug>/", views.post_detail),
    # Regex (legacy, prefer path())
    re_path(r"^users/(?P<pk>\d+)/$", views.user_detail),
]
```

## 5.5 Views

### Function-Based Views (FBV)

```python
from django.http import JsonResponse
from django.shortcuts import get_object_or_404
from .models import User

def user_list(request):
    """List all users."""
    users = User.objects.all().values("id", "username", "email")
    return JsonResponse(list(users), safe=False)

def user_detail(request, pk):
    """Get a single user."""
    user = get_object_or_404(User, pk=pk)
    return JsonResponse({
        "id": user.id,
        "username": user.username,
        "email": user.email,
    })
```

### Class-Based Views (CBV)

```python
from django.views import View
from django.http import JsonResponse
from django.shortcuts import get_object_or_404
from .models import User

class UserListView(View):
    def get(self, request):
        users = User.objects.all().values("id", "username", "email")
        return JsonResponse(list(users), safe=False)

    def post(self, request):
        # Handle user creation
        ...
```

## 5.6 Templates

### Template Language

```html
<!-- templates/users/profile.html -->
{% extends "base.html" %}

{% block title %}{{ user.username }}{% endblock %}

{% block content %}
<h1>{{ user.username }}</h1>
<p>{{ user.email }}</p>

{% if user.is_active %}
    <span class="badge">Active</span>
{% else %}
    <span class="badge inactive">Inactive</span>
{% endif %}

<ul>
{% for post in posts %}
    <li>
        <a href="{% url 'blog:post-detail' post.slug %}">
            {{ post.title }}
        </a>
    </li>
{% empty %}
    <li>No posts yet.</li>
{% endfor %}
</ul>
{% endblock %}
```

### Template Tags

```text
{{ variable }}           → Variable output
{% tag %}                → Template tags
{{ variable|filter }}    → Filters (upper, lower, date, etc.)
{% url 'name' arg %}    → URL reverse
{% static 'path' %}     → Static file URL
{% include 'partial.html' %}  → Include another template
{% extends 'base.html' %}     → Template inheritance
{% block name %}...{% endblock %}  → Define block content
{% csrf_token %}        → CSRF token (forms)
```

## 5.7 Admin

### Registering Models

```python
# users/admin.py
from django.contrib import admin
from .models import User, Profile

@admin.register(User)
class UserAdmin(admin.ModelAdmin):
    list_display = ("username", "email", "is_active", "created_at")
    list_filter = ("is_active", "is_staff")
    search_fields = ("username", "email")
    ordering = ("-created_at",)
    readonly_fields = ("created_at", "updated_at")
```

## 5.8 Forms

### Django Forms

```python
from django import forms
from .models import User

class UserForm(forms.ModelForm):
    class Meta:
        model = User
        fields = ["username", "email", "password"]
        widgets = {
            "password": forms.PasswordInput(),
        }

    def clean_email(self):
        email = self.cleaned_data.get("email")
        if User.objects.filter(email=email).exists():
            raise forms.ValidationError("Email already in use.")
        return email
```

### Using in Views

```python
def register(request):
    if request.method == "POST":
        form = UserForm(request.POST)
        if form.is_valid():
            user = form.save()
            return redirect("user-detail", pk=user.pk)
    else:
        form = UserForm()
    return render(request, "users/register.html", {"form": form})
```

## 5.9 Request Lifecycle

```text
Client Request
    ↓
WSGI/ASGI Server (Gunicorn/Uvicorn)
    ↓
Django's URL Resolver
    ↓
Middleware (pre-processing)
    ↓
View Function/Class
    ↓
    ├── Process Request
    ├── Interact with Models/Database
    ├── Generate Response
    ↓
Middleware (post-processing)
    ↓
HTTP Response → Client
```

### Middleware Execution Order

```text
Request:
  SecurityMiddleware → SessionMiddleware → CommonMiddleware
  → CsrfViewMiddleware → AuthenticationMiddleware → MessageMiddleware

Response:
  MessageMiddleware → AuthenticationMiddleware → CsrfViewMiddleware
  → CommonMiddleware → SessionMiddleware → SecurityMiddleware
  (reverse order)
```

## 5.10 Static and Media Files

```python
# settings.py
STATIC_URL = "/static/"
STATICFILES_DIRS = [BASE_DIR / "static"]
STATIC_ROOT = BASE_DIR / "staticfiles"

MEDIA_URL = "/media/"
MEDIA_ROOT = BASE_DIR / "media"

# URLs (development)
from django.conf import settings
from django.conf.urls.static import static

urlpatterns = [
    ...
] + static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)
```

## Common Beginner Mistakes

- 🚨 Putting business logic in views (put it in services/models)
- 🚨 Not using `get_object_or_404` (leads to unhandled DoesNotExist exceptions)
- 🚨 Hardcoding URLs instead of using `{% url %}` and `reverse()`
- 🚨 Forgetting `{% csrf_token %}` in forms
- 🚨 Modifying settings directly instead of using environment variables

## ✅ Phase 5 Checkpoint

### What I Should Know

- [ ] Django project and app structure
- [ ] settings.py configuration
- [ ] URL routing and reversing
- [ ] Function-based and class-based views
- [ ] Template language basics
- [ ] Admin configuration
- [ ] Django forms
- [ ] Request lifecycle
- [ ] Static and media files

### Interview Questions

1. What is Django's MVT architecture?
2. Explain the Django request lifecycle from URL to response.
3. What is middleware? Name 3 built-in middleware.
4. What's the difference between a project and an app?
5. How does URL reversing work?

---

# Phase 6 — Django Models and ORM

> **Prerequisite:** Phase 5. Comfortable with Django basics.
> **Goal:** Master Django ORM — from basic models to advanced query optimization.

## 6.1 Models

### Basic Model

```python
from django.db import models
from django.contrib.auth.models import AbstractUser

class User(AbstractUser):
    """Extended user model."""
    bio = models.TextField(max_length=500, blank=True)
    avatar = models.ImageField(upload_to="avatars/", blank=True)
    date_of_birth = models.DateField(null=True, blank=True)
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)

    class Meta:
        ordering = ["-created_at"]
        verbose_name = "user"
        verbose_name_plural = "users"

    def __str__(self):
        return self.username
```

### Field Types

```python
# Text
models.CharField(max_length=255)      # Short text
models.TextField()                     # Long text
models.SlugField()                     # URL-safe string

# Numbers
models.IntegerField()                  # Integer
models.FloatField()                    # Float
models.DecimalField(max_digits=10, decimal_places=2)  # Precise decimal

# Boolean
models.BooleanField(default=False)

# Date/Time
models.DateField()                     # Date only
models.DateTimeField()                 # Date + time
models.TimeField()                     # Time only

# Files
models.FileField(upload_to="files/")
models.ImageField(upload_to="images/")

# Relationships
models.ForeignKey(User, on_delete=models.CASCADE)
models.OneToOneField(User, on_delete=models.CASCADE)
models.ManyToManyField("Category")
```

### Relationships

```python
class Category(models.Model):
    name = models.CharField(max_length=100, unique=True)
    slug = models.SlugField(unique=True)

class Post(models.Model):
    # ForeignKey (many-to-one)
    author = models.ForeignKey(
        User,
        on_delete=models.CASCADE,
        related_name="posts"
    )

    # Many-to-Many
    categories = models.ManyToManyField(
        Category,
        related_name="posts"
    )

    title = models.CharField(max_length=200)
    slug = models.SlugField(unique=True)
    content = models.TextField()
    published = models.BooleanField(default=False)
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)

    class Meta:
        ordering = ["-created_at"]

    def __str__(self):
        return self.title

class Comment(models.Model):
    # ForeignKey with SET_NULL (keep comments if post deleted)
    post = models.ForeignKey(
        Post,
        on_delete=models.CASCADE,
        related_name="comments"
    )
    author = models.ForeignKey(
        User,
        on_delete=models.SET_NULL,
        null=True,
        related_name="comments"
    )
    content = models.TextField()
    created_at = models.DateTimeField(auto_now_add=True)

    class Meta:
        ordering = ["created_at"]
```

### on_delete Options

```text
CASCADE       → Delete related objects
PROTECT       → Prevent deletion (raise error)
SET_NULL      → Set FK to NULL (requires null=True)
SET_DEFAULT   → Set FK to default value
DO_NOTHING    → Do nothing (dangerous, breaks integrity)
```

## 6.2 QuerySets

### Basic Queries

```python
# Get all
users = User.objects.all()

# Filter
active_users = User.objects.filter(is_active=True)
admins = User.objects.filter(is_staff=True, is_superuser=True)

# Exclude
non_admins = User.objects.exclude(is_staff=True)

# Get single object
user = User.objects.get(pk=1)           # Raises DoesNotExist
user = User.objects.filter(pk=1).first() # Returns None
user = User.objects.filter(pk=1).first() # Returns None

# Ordering
users = User.objects.order_by("-created_at")
users = User.objects.order_by("username", "-created_at")
```

### Complex Filters

```python
from django.db.models import Q, F, Value
from django.db.models.functions import Lower

# Q objects (OR, NOT)
users = User.objects.filter(
    Q(username__icontains="admin") | Q(email__icontains="admin")
)

users = User.objects.filter(
    Q(is_active=True) & Q(is_staff=False)
)

# F objects (compare fields to other fields)
# Posts where comments exceed a threshold
posts = Post.objects.annotate(
    comment_count=Count("comments")
).filter(comment_count__gte=10)

# Lookup expressions
users = User.objects.filter(
    email__icontains="gmail",      # LIKE '%gmail%'
    created_at__year=2024,          # WHERE EXTRACT(YEAR FROM created_at) = 2024
    profile__age__gte=18,           # JOIN + WHERE age >= 18
    username__startswith="a",       # LIKE 'a%'
)
```

### Aggregation and Annotation

```python
from django.db.models import Count, Sum, Avg, Max, Min

# Aggregation (summary across all objects)
total_posts = Post.objects.count()
avg_comments = Post.objects.aggregate(avg_comments=Count("comments"))
stats = Post.objects.aggregate(
    total=Count("id"),
    avg_likes=Avg("likes_count"),
    max_likes=Max("likes_count"),
)

# Annotation (per-object summary)
posts_with_counts = Post.objects.annotate(
    comment_count=Count("comments"),
    like_count=Count("likes"),
).order_by("-comment_count")

# Grouping
from django.db.models import Count
from django.db.models.functions import TruncMonth

monthly_posts = Post.objects.annotate(
    month=TruncMonth("created_at")
).values("month").annotate(
    count=Count("id")
).order_by("month")
```

## 6.3 select_related and prefetch_related

### The N+1 Query Problem

```python
# BAD: N+1 queries
posts = Post.objects.all()
for post in posts:
    print(post.author.username)  # Each access = new query!
    for comment in post.comments.all():
        print(comment.content)   # Another N queries!

# How many queries?
# 1 (get all posts) + N (get author for each post) + N*M (get comments)
# For 100 posts with 10 comments each = 1 + 100 + 1000 = 1101 queries!
```

### select_related (ForeignKey, OneToOne)

```python
# GOOD: Uses SQL JOIN, single query
posts = Post.objects.select_related("author").all()
for post in posts:
    print(post.author.username)  # No extra query!

# SQL equivalent:
# SELECT posts.*, users.* FROM posts
# INNER JOIN users ON posts.author_id = users.id
```

### prefetch_related (ManyToMany, reverse ForeignKey)

```python
# GOOD: Uses separate optimized queries
posts = Post.objects.prefetch_related("comments", "categories").all()
for post in posts:
    for comment in post.comments.all():  # No extra query!
        print(comment.content)

# SQL equivalent:
# SELECT * FROM posts;
# SELECT * FROM comments WHERE post_id IN (1, 2, 3, ...);
# SELECT * FROM categories INNER JOIN post_categories ON ...
```

### Combined

```python
# Production-ready query
posts = (
    Post.objects
    .select_related("author")
    .prefetch_related("comments__author", "categories")
    .filter(published=True)
    .annotate(comment_count=Count("comments"))
    .order_by("-created_at")[:20]
)
```

## 6.4 Transactions

```python
from django.db import transaction

# Atomic block (all or nothing)
with transaction.atomic():
    user = User.objects.create(username="alice")
    Profile.objects.create(user=user, bio="Hello!")
    # If Profile creation fails, User creation is rolled back

# Savepoint (nested)
with transaction.atomic():
    order = Order.objects.create(user=user, total=100)
    with transaction.atomic():
        # This can fail without rolling back the order
        Inventory.reserve(order.items)
```

## 6.5 Migrations

### Creating Migrations

```bash
# After changing models
python manage.py makemigrations

# Named migration
python manage.py makemigrations users --name add_user_bio

# Apply
python manage.py migrate

# Rollback
python manage.py migrate users 0003
```

### Data Migrations

```python
from django.db import migrations

def set_default_role(apps, schema_editor):
    User = apps.get_model("users", "User")
    User.objects.update(default_role="member")

class Migration(migrations.Migration):
    dependencies = [
        ("users", "0003_user_default_role"),
    ]

    operations = [
        migrations.RunPython(set_default_role),
    ]
```

## 6.6 Custom Managers

```python
class PostManager(models.Manager):
    def published(self):
        return self.filter(published=True)

    def draft(self):
        return self.filter(published=False)

    def by_author(self, author):
        return self.filter(author=author)

class Post(models.Model):
    objects = PostManager()

# Usage
Post.objects.published()           # Only published posts
Post.objects.draft()               # Only drafts
Post.objects.by_author(user)       # Posts by specific user
```

## Common ORM Mistakes

- 🚨 Not using `select_related`/`prefetch_related` (N+1 queries)
- 🚨 Using `.all()` when you only need `.first()` or `.exists()`
- 🚨 Fetching entire objects when you only need specific fields (use `.values()`)
- 🚨 Not using `only()` or `defer()` for large models
- 🚨 Running queries inside loops instead of using `in` operator
- 🚨 Not using `transaction.atomic()` for multi-step operations

## ✅ Phase 6 Checkpoint

### What I Should Know

- [ ] Model fields and relationships
- [ ] QuerySet methods (filter, exclude, annotate, aggregate)
- [ ] Q objects for complex queries
- [ ] select_related and prefetch_related
- [ ] N+1 query problem and solutions
- [ ] Transactions and atomic operations
- [ ] Migrations (schema and data)
- [ ] Custom managers

### Interview Questions

1. Explain the N+1 query problem with an example.
2. When do you use `select_related` vs `prefetch_related`?
3. What is a QuerySet and why is it lazy?
4. How do transactions work in Django ORM?
5. Write a query that gets the top 5 users by post count.

---

# Phase 7 — SQL and PostgreSQL

> **Prerequisite:** Phase 6 (Django ORM).
> **Goal:** Deep SQL and PostgreSQL knowledge — not just "what Django generates."

## 7.1 SQL Fundamentals

### Basic Queries

```sql
-- SELECT
SELECT id, username, email FROM users;

-- WHERE
SELECT * FROM users WHERE is_active = true AND created_at > '2024-01-01';

-- ORDER BY
SELECT * FROM users ORDER BY created_at DESC;

-- LIMIT/OFFSET
SELECT * FROM posts ORDER BY created_at DESC LIMIT 10 OFFSET 20;

-- INSERT
INSERT INTO users (username, email, password_hash)
VALUES ('alice', 'alice@example.com', 'hash...')
RETURNING id;

-- UPDATE
UPDATE users SET is_active = false WHERE last_login < '2023-01-01';

-- DELETE
DELETE FROM posts WHERE published = false AND created_at < '2023-01-01';
```

### JOINs

```sql
-- INNER JOIN (only matching rows)
SELECT p.title, u.username
FROM posts p
INNER JOIN users u ON p.author_id = u.id;

-- LEFT JOIN (all from left, matches from right)
SELECT p.title, COALESCE(c.comment_count, 0) as comment_count
FROM posts p
LEFT JOIN (
    SELECT post_id, COUNT(*) as comment_count
    FROM comments
    GROUP BY post_id
) c ON p.id = c.post_id;

-- Multiple JOINs
SELECT p.title, u.username, c.content
FROM posts p
INNER JOIN users u ON p.author_id = u.id
LEFT JOIN comments c ON p.id = c.post_id;
```

### GROUP BY and HAVING

```sql
-- Count posts per author
SELECT
    u.username,
    COUNT(p.id) as post_count
FROM users u
LEFT JOIN posts p ON u.id = p.author_id
GROUP BY u.id, u.username
HAVING COUNT(p.id) > 5
ORDER BY post_count DESC;
```

### Subqueries

```sql
-- Subquery in WHERE
SELECT * FROM posts
WHERE author_id IN (
    SELECT id FROM users WHERE is_staff = true
);

-- Correlated subquery
SELECT
    p.title,
    (SELECT COUNT(*) FROM comments c WHERE c.post_id = p.id) as comment_count
FROM posts p;

-- EXISTS
SELECT * FROM users u
WHERE EXISTS (
    SELECT 1 FROM posts p WHERE p.author_id = u.id
);
```

### CTEs (Common Table Expressions)

```sql
-- CTE for readable complex queries
WITH active_authors AS (
    SELECT id, username
    FROM users
    WHERE is_active = true
),
author_post_counts AS (
    SELECT
        author_id,
        COUNT(*) as post_count
    FROM posts
    GROUP BY author_id
)
SELECT
    u.username,
    COALESCE(apc.post_count, 0) as post_count
FROM active_authors u
LEFT JOIN author_post_counts apc ON u.id = apc.author_id
ORDER BY post_count DESC;
```

### Window Functions

```sql
-- Ranking
SELECT
    u.username,
    COUNT(p.id) as post_count,
    RANK() OVER (ORDER BY COUNT(p.id) DESC) as rank,
    DENSE_RANK() OVER (ORDER BY COUNT(p.id) DESC) as dense_rank,
    ROW_NUMBER() OVER (ORDER BY COUNT(p.id) DESC) as row_num
FROM users u
LEFT JOIN posts p ON u.id = p.author_id
GROUP BY u.id, u.username;

-- Running total
SELECT
    created_at,
    amount,
    SUM(amount) OVER (ORDER BY created_at) as running_total
FROM transactions;

-- Partition by
SELECT
    u.username,
    p.title,
    ROW_NUMBER() OVER (PARTITION BY p.author_id ORDER BY p.created_at DESC) as post_number
FROM posts p
INNER JOIN users u ON p.author_id = u.id;
```

## 7.2 PostgreSQL Specifics

### Data Types

```sql
-- Text
VARCHAR(255)      -- Variable length, max 255
TEXT               -- Variable length, unlimited
CHAR(10)          -- Fixed length

-- Numeric
INTEGER            -- 4 bytes
BIGINT             -- 8 bytes
SMALLINT           -- 2 bytes
DECIMAL(10, 2)     -- Precise decimal
NUMERIC             -- Same as DECIMAL

-- Date/Time
DATE               -- Date only
TIME               -- Time only
TIMESTAMP          -- Date + time (no timezone)
TIMESTAMPTZ        -- Date + time with timezone (preferred)

-- Boolean
BOOLEAN            -- true/false

-- JSON
JSONB              -- Binary JSON (indexable, preferred)
JSON               -- Text JSON (not indexable)

-- Array
INTEGER[]          -- Array of integers
TEXT[]             -- Array of text
```

### Indexes

```sql
-- B-tree (default, most common)
CREATE INDEX idx_users_email ON users(email);
CREATE INDEX idx_posts_author ON posts(author_id, created_at DESC);

-- Partial index (only index rows matching condition)
CREATE INDEX idx_active_users ON users(id)
WHERE is_active = true;

-- GIN (for JSONB, arrays, full-text search)
CREATE INDEX idx_posts_tags ON posts USING GIN(tags);
CREATE INDEX idx_posts_content ON posts USING GIN(to_tsvector('english', content));

-- GiST (for geometric, range, full-text)
CREATE INDEX idx_locations ON places USING GIST(coordinates);

-- Unique index
CREATE UNIQUE INDEX idx_users_email_unique ON users(email);
```

### ACID and Transactions

```sql
-- ACID Properties:
-- Atomicity:    All operations succeed or all fail
-- Consistency:  Database moves from one valid state to another
-- Isolation:    Concurrent transactions don't interfere
-- Durability:   Committed data survives crashes

-- Isolation Levels (PostgreSQL default: READ COMMITTED):
-- READ UNCOMMITTED  → dirty reads possible (PostgreSQL doesn't actually allow this)
-- READ COMMITTED    → only committed data visible
-- REPEATABLE READ   → consistent snapshot within transaction
-- SERIALIZABLE      → full isolation (slowest)

-- Setting isolation level
BEGIN ISOLATION LEVEL SERIALIZABLE;
SELECT * FROM accounts WHERE id = 1 FOR UPDATE;
UPDATE accounts SET balance = balance - 100 WHERE id = 1;
COMMIT;
```

### EXPLAIN ANALYZE

```sql
-- See query plan
EXPLAIN ANALYZE
SELECT p.title, u.username
FROM posts p
INNER JOIN users u ON p.author_id = u.id
WHERE p.published = true
ORDER BY p.created_at DESC
LIMIT 10;

-- Look for:
-- Seq Scan → missing index
-- Nested Loop with high cost → consider join optimization
-- Sort → consider index for ORDER BY
-- Hash → usually good for joins
```

## 7.3 Django to SQL Translation

```python
# Django
User.objects.filter(is_active=True, email__icontains="gmail")
# SQL
SELECT * FROM users WHERE is_active = true AND email LIKE '%gmail%';

# Django
Post.objects.select_related("author").filter(author__username="alice")
# SQL
SELECT posts.*, users.*
FROM posts
INNER JOIN users ON posts.author_id = users.id
WHERE users.username = 'alice';

# Django
Post.objects.annotate(comment_count=Count("comments")).filter(comment_count__gte=5)
# SQL
SELECT posts.*, COUNT(comments.id) as comment_count
FROM posts
LEFT JOIN comments ON posts.id = comments.post_id
GROUP BY posts.id
HAVING COUNT(comments.id) >= 5;
```

## ✅ Phase 7 Checkpoint

- [ ] Can write complex SQL queries from scratch
- [ ] Understand all JOIN types
- [ ] Can use CTEs and window functions
- [ ] Know PostgreSQL data types and when to use each
- [ ] Can create and analyze indexes
- [ ] Can read EXPLAIN ANALYZE output
- [ ] Understand ACID and isolation levels
- [ ] Can translate Django ORM to SQL

---

# Phase 8 — Authentication and Authorization

> **Prerequisite:** Phases 5-6.
> **Goal:** Implement secure authentication and authorization systems.

## 8.1 Authentication vs Authorization

```text
Authentication: WHO are you? (login, identity)
Authorization:  WHAT can you do? (permissions, access control)
```

## 8.2 Django Authentication System

### Custom User Model (Best Practice)

```python
from django.contrib.auth.models import AbstractUser
from django.db import models

class User(AbstractUser):
    email = models.EmailField(unique=True)
    is_verified = models.BooleanField(default=False)

    USERNAME_FIELD = "email"
    REQUIRED_FIELDS = ["username"]

    class Meta:
        ordering = ["-date_joined"]

    def __str__(self):
        return self.email
```

### Registration

```python
from django.contrib.auth import get_user_model
from django import forms

User = get_user_model()

class RegistrationForm(forms.ModelForm):
    password = forms.CharField(widget=forms.PasswordInput)
    password_confirm = forms.CharField(widget=forms.PasswordInput)

    class Meta:
        model = User
        fields = ["email", "username", "password"]

    def clean(self):
        cleaned_data = super().clean()
        if cleaned_data.get("password") != cleaned_data.get("password_confirm"):
            raise forms.ValidationError("Passwords do not match.")
        return cleaned_data

    def save(self, commit=True):
        user = super().save(commit=False)
        user.set_password(self.cleaned_data["password"])
        if commit:
            user.save()
        return user
```

### Login/Logout

```python
from django.contrib.auth import authenticate, login, logout
from django.shortcuts import redirect, render

def login_view(request):
    if request.method == "POST":
        email = request.POST["email"]
        password = request.POST["password"]
        user = authenticate(request, username=email, password=password)
        if user is not None:
            login(request, user)
            return redirect("dashboard")
        else:
            return render(request, "auth/login.html", {"error": "Invalid credentials"})
    return render(request, "auth/login.html")

def logout_view(request):
    logout(request)
    return redirect("login")
```

### Password Hashing

```text
Django uses PBKDF2 by default:
1. Generate random salt
2. Hash password + salt (thousands of iterations)
3. Store hash, not password

# Django functions:
user.set_password("raw_password")  # Hashes and stores
user.check_password("raw_password") # Verifies

# Never store plain text passwords!
# Never write custom hashing — use Django's built-in
```

## 8.3 Permissions and Groups

### Model Permissions

```python
class Post(models.Model):
    class Meta:
        permissions = [
            ("publish_post", "Can publish post"),
            ("feature_post", "Can feature post"),
        ]
```

### Assigning Permissions

```python
from django.contrib.auth.models import Permission

# Assign permission to user
permission = Permission.objects.get(codename="publish_post")
user.user_permissions.add(permission)

# Check permission
user.has_perm("blog.publish_post")

# Group-based permissions
from django.contrib.auth.models import Group

editors_group = Group.objects.create(name="Editors")
editors_group.permissions.add(permission)
user.groups.add(editors_group)
user.has_perm("blog.publish_post")  # True
```

### RBAC (Role-Based Access Control)

```python
# roles.py
from enum import Enum

class Role(Enum):
    VIEWER = "viewer"
    EDITOR = "editor"
    ADMIN = "admin"

class UserRole(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE, related_name="roles")
    role = models.CharField(max_length=20, choices=[(r.value, r.name) for r in Role])

    class Meta:
        unique_together = ["user", "role"]

# Permission checking
def has_role(user, role: Role) -> bool:
    return UserRole.objects.filter(user=user, role=role.value).exists()

def is_editor(user) -> bool:
    return has_role(user, Role.EDITOR)
```

### Object-Level Permissions

```python
# Using django-guardian or custom logic
class PostPermission:
    @staticmethod
    def can_edit(user, post) -> bool:
        return (
            user == post.author or
            user.has_perm("blog.publish_post") or
            user.is_staff
        )

    @staticmethod
    def can_delete(user, post) -> bool:
        return (
            user == post.author or
            user.is_superuser
        )

# In views
def edit_post(request, pk):
    post = get_object_or_404(Post, pk=pk)
    if not PostPermission.can_edit(request.user, post):
        return HttpResponseForbidden("You cannot edit this post.")
    # ...
```

## 8.4 Email Verification

```python
from django.core.mail import send_mail
from django.utils.http import urlsafe_base64_encode, urlsafe_base64_decode
from django.contrib.auth.tokens import default_token_generator

def send_verification_email(user):
    token = default_token_generator.make_token(user)
    uid = urlsafe_base64_encode(str(user.pk).encode())
    verification_url = f"https://example.com/verify/{uid}/{token}/"

    send_mail(
        "Verify your email",
        f"Click here to verify: {verification_url}",
        "noreply@example.com",
        [user.email],
    )

def verify_email(request, uidb64, token):
    try:
        uid = urlsafe_base64_decode(uidb64).decode()
        user = User.objects.get(pk=uid)
    except (TypeError, ValueError, OverflowError, User.DoesNotExist):
        user = None

    if user is not None and default_token_generator.check_token(user, token):
        user.is_verified = True
        user.save()
        return redirect("login")
    return render(request, "auth/verification_failed.html")
```

## ✅ Phase 8 Checkpoint

- [ ] Custom user model
- [ ] Registration, login, logout
- [ ] Password hashing (understand the concept)
- [ ] Model permissions and groups
- [ ] RBAC implementation
- [ ] Object-level permissions
- [ ] Email verification flow

---

# Phase 9 — Django REST Framework

> **Prerequisite:** Phases 5-8.
> **Goal:** Build professional REST APIs with DRF.

## 9.1 DRF Overview

### Why DRF

```text
Without DRF:
  - Manual JSON parsing
  - Manual validation
  - Manual serialization
  - Manual authentication
  - Manual pagination
  - Manual error handling

With DRF:
  - Serializers handle all of the above
  - Built-in authentication, permissions, throttling
  - Browsable API for development
  - OpenAPI schema generation
```

## 9.2 Serializers

### ModelSerializer

```python
from rest_framework import serializers
from .models import User, Post

class UserSerializer(serializers.ModelSerializer):
    post_count = serializers.SerializerMethodField()

    class Meta:
        model = User
        fields = ["id", "username", "email", "post_count", "created_at"]
        read_only_fields = ["id", "created_at"]

    def get_post_count(self, obj) -> int:
        return obj.posts.count()

class PostSerializer(serializers.ModelSerializer):
    author = UserSerializer(read_only=True)
    comment_count = serializers.SerializerMethodField()

    class Meta:
        model = Post
        fields = [
            "id", "title", "slug", "content", "author",
            "published", "comment_count", "created_at", "updated_at"
        ]
        read_only_fields = ["id", "slug", "created_at", "updated_at"]

    def get_comment_count(self, obj) -> int:
        return obj.comments.count()

class PostCreateSerializer(serializers.ModelSerializer):
    class Meta:
        model = Post
        fields = ["title", "content", "categories"]

    def create(self, validated_data):
        validated_data["author"] = self.context["request"].user
        return super().create(validated_data)
```

### Custom Validation

```python
class PostSerializer(serializers.ModelSerializer):
    class Meta:
        model = Post
        fields = ["title", "content"]

    def validate_title(self, value):
        if len(value) < 5:
            raise serializers.ValidationError("Title must be at least 5 characters.")
        return value

    def validate(self, data):
        if "python" in data["title"].lower() and "python" not in data["content"].lower():
            raise serializers.ValidationError(
                "Posts about Python must mention Python in the content."
            )
        return data
```

## 9.3 Views

### APIView

```python
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status
from django.shortcuts import get_object_or_404
from .models import Post
from .serializers import PostSerializer

class PostListView(APIView):
    def get(self, request):
        posts = Post.objects.all()
        serializer = PostSerializer(posts, many=True)
        return Response(serializer.data)

    def post(self, request):
        serializer = PostCreateSerializer(data=request.data)
        if serializer.is_valid():
            post = serializer.save()
            return Response(
                PostSerializer(post).data,
                status=status.HTTP_201_CREATED
            )
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

class PostDetailView(APIView):
    def get(self, request, pk):
        post = get_object_or_404(Post, pk=pk)
        serializer = PostSerializer(post)
        return Response(serializer.data)

    def put(self, request, pk):
        post = get_object_or_404(Post, pk=pk)
        serializer = PostSerializer(post, data=request.data, partial=True)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

    def delete(self, request, pk):
        post = get_object_or_404(Post, pk=pk)
        post.delete()
        return Response(status=status.HTTP_204_NO_CONTENT)
```

### Generic Views and Mixins

```python
from rest_framework import generics, mixins
from .models import Post
from .serializers import PostSerializer
from .permissions import IsAuthorOrReadOnly

class PostListCreateView(generics.ListCreateAPIView):
    """List all posts or create a new post."""
    queryset = Post.objects.all()
    serializer_class = PostSerializer
    permission_classes = [IsAuthorOrReadOnly]

    def perform_create(self, serializer):
        serializer.save(author=self.request.user)

class PostDetailView(generics.RetrieveUpdateDestroyAPIView):
    """Retrieve, update, or delete a post."""
    queryset = Post.objects.all()
    serializer_class = PostSerializer
    permission_classes = [IsAuthorOrReadOnly]
    lookup_field = "slug"
```

### ViewSets and Routers

```python
from rest_framework import viewsets, status
from rest_framework.decorators import action
from rest_framework.response import Response
from .models import Post
from .serializers import PostSerializer

class PostViewSet(viewsets.ModelViewSet):
    queryset = Post.objects.all()
    serializer_class = PostSerializer
    permission_classes = [IsAuthorOrReadOnly]

    def perform_create(self, serializer):
        serializer.save(author=self.request.user)

    @action(detail=True, methods=["post"])
    def publish(self, request, pk=None):
        post = self.get_object()
        post.published = True
        post.save()
        return Response({"status": "published"})

    @action(detail=False, methods=["get"])
    def my_posts(self, request):
        posts = Post.objects.filter(author=request.user)
        serializer = self.get_serializer(posts, many=True)
        return Response(serializer.data)

# urls.py
from rest_framework.routers import DefaultRouter

router = DefaultRouter()
router.register(r"posts", PostViewSet)

urlpatterns = [
    path("api/", include(router.urls)),
]

# Generated URLs:
# GET    /api/posts/           → list
# POST   /api/posts/           → create
# GET    /api/posts/{id}/      → retrieve
# PUT    /api/posts/{id}/      → update
# PATCH  /api/posts/{id}/      → partial_update
# DELETE /api/posts/{id}/      → destroy
# POST   /api/posts/{id}/publish/ → custom action
# GET    /api/posts/my_posts/  → custom action
```

## 9.4 Pagination

```python
# settings.py
REST_FRAMEWORK = {
    "DEFAULT_PAGINATION_CLASS": "rest_framework.pagination.PageNumberPagination",
    "PAGE_SIZE": 20,
}

# Custom pagination
class PostPagination(PageNumberPagination):
    page_size = 20
    page_size_query_param = "page_size"
    max_page_size = 100

# Usage in viewset
class PostViewSet(viewsets.ModelViewSet):
    pagination_class = PostPagination
```

## 9.5 Filtering

```python
# Using django-filter
# pip install django-filter

# settings.py
INSTALLED_APPS = [..., "django_filters"]
REST_FRAMEWORK = {
    "DEFAULT_FILTER_BACKENDS": [
        "django_filters.rest_framework.DjangoFilterBackend",
        "rest_framework.filters.SearchFilter",
        "rest_framework.filters.OrderingFilter",
    ]
}

# views.py
class PostViewSet(viewsets.ModelViewSet):
    filterset_fields = ["author", "published"]
    search_fields = ["title", "content"]
    ordering_fields = ["created_at", "title"]
    ordering = ["-created_at"]
```

## 9.6 Authentication in DRF

```python
# settings.py
REST_FRAMEWORK = {
    "DEFAULT_AUTHENTICATION_CLASSES": [
        "rest_framework.authentication.SessionAuthentication",
        "rest_framework_simplejwt.authentication.JWTAuthentication",
    ],
    "DEFAULT_PERMISSION_CLASSES": [
        "rest_framework.permissions.IsAuthenticatedOrReadOnly",
    ],
}

# Token authentication (simple)
from rest_framework.authtoken.views import ObtainAuthToken
from rest_framework.authtoken.models import Token

# JWT authentication
# pip install djangorestframework-simplejwt
from rest_framework_simplejwt.views import TokenObtainPairView, TokenRefreshView

urlpatterns = [
    path("api/token/", TokenObtainPairView.as_view()),
    path("api/token/refresh/", TokenRefreshView.as_view()),
]
```

## 9.7 Error Handling

```python
from rest_framework.views import exception_handler
from rest_framework.response import Response
from rest_framework import status

def custom_exception_handler(exc, context):
    response = exception_handler(exc, context)

    if response is not None:
        response.data = {
            "error": {
                "code": response.status_code,
                "message": response.data,
            }
        }

    return response

# settings.py
REST_FRAMEWORK = {
    "EXCEPTION_HANDLER": "myproject.exceptions.custom_exception_handler"
}
```

## 9.8 OpenAPI/Swagger Documentation

### Why API Documentation Matters

```text
Without documentation:
  - Frontend developers guess endpoint behavior
  - Mobile developers build wrong assumptions
  - New team members struggle to understand the API
  - No contract between backend and consumers

With OpenAPI/Swagger:
  - Auto-generated interactive documentation
  - Client SDK generation
  - API testing from browser
  - Clear contract for all stakeholders
```

### Setup with drf-spectacular

```bash
pip install drf-spectacular
```

```python
# settings.py
INSTALLED_APPS = [..., "drf_spectacular"]

REST_FRAMEWORK = {
    "DEFAULT_SCHEMA_CLASS": "drf_spectacular.openapi.AutoSchema",
}

# URLs
from drf_spectacular.views import (
    SpectacularAPIView,
    SpectacularRedocView,
    SpectacularSwaggerView,
)

urlpatterns = [
    path("api/schema/", SpectacularAPIView.as_view(), name="schema"),
    path("api/docs/", SpectacularSwaggerView.as_view(url_name="schema")),
    path("api/redoc/", SpectacularRedocView.as_view(url_name="schema")),
]
```

### Schema Customization

```python
# schemas.py
from drf_spectacular.utils import extend_schema, OpenApiExample

class PostViewSet(viewsets.ModelViewSet):
    queryset = Post.objects.all()
    serializer_class = PostSerializer

    @extend_schema(
        summary="List all published posts",
        description="Returns paginated list of published posts.",
        examples=[
            OpenApiExample(
                "Example response",
                value={"id": 1, "title": "Hello World", "content": "..."},
                request_only=False,
            ),
        ],
    )
    def list(self, request):
        return super().list(request)
```

### Custom Authentication Schema

```python
# schemas.py
class CustomAutoSchema(AutoSchema):
    def get_security(self, path, method):
        return [{"jwtAuth": []}]

    def get_security_definitions(self):
        return {
            "jwtAuth": {
                "type": "http",
                "scheme": "bearer",
                "bearerFormat": "JWT",
            }
        }
```

## 9.9 WebSockets with Django Channels

### When to Use WebSockets

```text
Use WebSockets for:
  ✅ Real-time chat
  ✅ Live notifications
  ✅ Collaborative editing
  ✅ Live dashboards
  ✅ Gaming
  ✅ Real-time feeds

Use REST for:
  ✅ CRUD operations
  ✅ Non-real-time data
  ✅ File uploads
  ✅ Simple request-response
```

### Mental Model

```text
REST:     Client asks → Server responds → Done
WebSocket: Client connects → Server pushes → Stays open

REST is like phone calls.
WebSocket is like a walkie-talkie.
```

### Setup with Django Channels

```bash
pip install channels
```

```python
# settings.py
INSTALLED_APPS = [..., "channels"]

ASGI_APPLICATION = "myproject.asgi.application"
CHANNEL_LAYERS = {
    "default": {
        "BACKEND": "channels_redis.core.RedisChannelLayer",
        "CONFIG": {
            "hosts": [os.environ.get("REDIS_URL", "redis://localhost:6379/0")],
        },
    },
}
```

### ASGI Configuration

```python
# myproject/asgi.py
import os
from django.core.asgi import get_asgi_application
from channels.routing import ProtocolTypeRouter, URLRouter
from channels.auth import AuthMiddlewareStack

os.environ.setdefault("DJANGO_SETTINGS_MODULE", "myproject.settings")

django_asgi_app = get_asgi_application()

from chat import routing

application = ProtocolTypeRouter({
    "http": django_asgi_app,
    "websocket": AuthMiddlewareStack(
        URLRouter(
            routing.websocket_urlpatterns
        )
    ),
})
```

### WebSocket Consumer

```python
# chat/consumers.py
import json
from channels.generic.websocket import AsyncWebsocketConsumer
from channels.db import database_sync_to_async

class ChatConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        self.room_name = self.scope["url_route"]["kwargs"]["room_name"]
        self.room_group_name = f"chat_{self.room_name}"
        self.user = self.scope["user"]

        if self.user.is_anonymous:
            await self.close()
            return

        # Join room group
        await self.channel_layer.group_add(
            self.room_group_name,
            self.channel_name
        )
        await self.accept()

    async def disconnect(self, close_code):
        await self.channel_layer.group_discard(
            self.room_group_name,
            self.channel_name
        )

    async def receive(self, text_data):
        data = json.loads(text_data)
        message = data["message"]

        # Save message to database
        await self.save_message(message)

        # Broadcast to room group
        await self.channel_layer.group_send(
            self.room_group_name,
            {
                "type": "chat_message",
                "message": message,
                "username": self.user.username,
            }
        )

    async def chat_message(self, event):
        await self.send(text_data=json.dumps({
            "message": event["message"],
            "username": event["username"],
        }))

    @database_sync_to_async
    def save_message(self, content):
        from .models import Message
        Message.objects.create(
            room_name=self.room_name,
            user=self.user,
            content=content
        )
```

### Routing

```python
# chat/routing.py
from django.urls import re_path
from . import consumers

websocket_urlpatterns = [
    re_path(r"ws/chat/(?P<room_name>\w+)/$", consumers.ChatConsumer.as_asgi()),
]
```

### Client-Side JavaScript

```javascript
// chat.js
const roomName = 'lobby';
const chatSocket = new WebSocket(
    `ws://${window.location.host}/ws/chat/${roomName}/`
);

chatSocket.onmessage = function(e) {
    const data = JSON.parse(e.data);
    document.querySelector('#chat-log').innerHTML += (
        `<div><strong>${data.username}</strong>: ${data.message}</div>`
    );
};

chatSocket.onclose = function(e) {
    console.error('Chat socket closed unexpectedly');
};

document.querySelector('#chat-message-input').onkeyup = function(e) {
    if (e.key === 'Enter') {
        chatSocket.send(JSON.stringify({
            'message': e.target.value
        }));
        e.target.value = '';
    }
};
```

### WebSocket vs Server-Sent Events vs Polling

| Feature | WebSocket | SSE | Polling |
|---|---|---|---|
| Direction | Bidirectional | Server → Client | Client → Server |
| Protocol | ws:// or wss:// | HTTP | HTTP |
| Real-time | Yes | Yes | No (delay) |
| Complexity | Higher | Lower | Lowest |
| Use case | Chat, gaming | Live feeds, notifications | Simple updates |

## Common DRF Mistakes

- 🚨 Not using `select_related`/`prefetch_related` in viewsets
- 🚨 Returning all fields (use specific fields in serializer)
- 🚨 Not implementing proper permissions
- 🚨 Using the same serializer for create and list (different needs)
- 🚨 Not handling pagination
- 🚨 Not documenting API with OpenAPI/Swagger
- 🚨 Using WebSockets when REST would suffice

## ✅ Phase 9 Checkpoint

- [ ] ModelSerializer and custom validation
- [ ] APIView, GenericAPIView, ViewSets
- [ ] Routers and URL generation
- [ ] Pagination, filtering, searching
- [ ] Authentication (Session, Token, JWT)
- [ ] Permissions (IsAuthenticated, custom)
- [ ] Custom error handling

---

# Phase 10 — API Security

> **Prerequisite:** Phase 9.
> **Goal:** Understand and mitigate common web security threats.

## 10.1 Common Vulnerabilities

### CSRF (Cross-Site Request Forgery)

```text
Attack: Malicious site tricks user into making requests to your site.
Defense: CSRF tokens in forms.

# Django enables CSRF middleware by default
# For API (JWT), CSRF is less relevant (tokens in headers, not cookies)
```

### CORS (Cross-Origin Resource Sharing)

```text
Attack: Browser makes requests to different origin.
Defense: Configure allowed origins.

# pip install django-cors-headers
# settings.py
INSTALLED_APPS = [..., "corsheaders"]
MIDDLEWARE = ["corsheaders.middleware.CorsMiddleware", ...]

CORS_ALLOWED_ORIGINS = [
    "http://localhost:3000",
    "https://yourdomain.com",
]
CORS_ALLOW_CREDENTIALS = True
```

### XSS (Cross-Site Scripting)

```text
Attack: Inject malicious scripts into pages.
Defense: Escape output, use CSP headers.

# Django templates auto-escape by default
# For DRF (JSON), XSS is less relevant
# Use Content-Security-Policy header
```

### SQL Injection

```text
Attack: Inject SQL through user input.
Defense: Use parameterized queries (ORM does this automatically).

# NEVER do this:
cursor.execute(f"SELECT * FROM users WHERE id = {user_id}")

# Django ORM protects against SQL injection automatically
# But raw SQL needs parameterization:
cursor.execute("SELECT * FROM users WHERE id = %s", [user_id])
```

## 10.2 JWT Security

### Access + Refresh Tokens

```text
Access Token:
  - Short-lived (15-60 minutes)
  - Contains user identity and permissions
  - Sent in Authorization header
  - Used for API requests

Refresh Token:
  - Long-lived (days/weeks)
  - Used only to get new access tokens
  - Stored securely (httpOnly cookie or secure storage)
  - Can be revoked
```

### Token Rotation

```text
1. User logs in → gets access + refresh tokens
2. Access token expires → use refresh token
3. Refresh token used → old refresh token invalidated
4. New access + refresh tokens issued
5. If refresh token is stolen, rotation detects it
```

### When JWT vs Sessions

| Use Case | Recommended |
|---|---|
| Traditional web app | Sessions (cookies) |
| SPA + API | JWT or sessions with httpOnly cookies |
| Mobile app | JWT |
| Microservices | JWT |
| Server-rendered pages | Sessions |

## 10.3 Rate Limiting

```python
# settings.py
REST_FRAMEWORK = {
    "DEFAULT_THROTTLE_CLASSES": [
        "rest_framework.throttling.AnonRateThrottle",
        "rest_framework.throttling.UserRateThrottle",
    ],
    "DEFAULT_THROTTLE_RATES": {
        "anon": "100/hour",
        "user": "1000/hour",
    },
}

# Custom throttle
from rest_framework.throttling import SimpleRateThrottle

class LoginThrottle(SimpleRateThrottle):
    scope = "login"

    def get_cache_key(self, request, view):
        return self.get_ident(request)

# settings.py
REST_FRAMEWORK = {
    "DEFAULT_THROTTLE_RATES": {
        "login": "5/minute",
    },
}
```

## 10.4 Security Checklist

```text
✅ Use HTTPS everywhere
✅ Set SECURE_HSTS_SECONDS
✅ Set SECURE_SSL_REDIRECT
✅ Set SESSION_COOKIE_SECURE = True
✅ Set CSRF_COOKIE_SECURE = True
✅ Use httpOnly cookies for tokens
✅ Rate limit login endpoints
✅ Hash passwords with PBKDF2
✅ Validate and sanitize all input
✅ Use parameterized queries (ORM)
✅ Set appropriate CORS headers
✅ Use Content-Security-Policy header
✅ Never expose stack traces in production
✅ Rotate secrets regularly
✅ Use environment variables for secrets
```

## ✅ Phase 10 Checkpoint

- [ ] Can explain CSRF, CORS, XSS, SQL injection
- [ ] Understand JWT access and refresh tokens
- [ ] Know when to use JWT vs sessions
- [ ] Can implement rate limiting
- [ ] Can run a security audit on a Django project

---

# Phase 11 — Redis and Caching

> **Prerequisite:** Phases 5-6.
> **Goal:** Use Redis and caching effectively in Django.

## 11.1 Redis Fundamentals

### Key Concepts

```text
Redis: Remote Dictionary Server
  - In-memory data store
  - Key-value model
  - Supports multiple data structures
  - Very fast (sub-millisecond)
  - Used for caching, sessions, queues, real-time features
```

### Data Structures

```bash
# Strings
SET user:1:name "Alice"
GET user:1:name
SETEX user:1:token "abc123" 3600  # Set with TTL (seconds)

# Hashes
HSET user:1 name "Alice" email "alice@example.com" age 30
HGET user:1 name
HGETALL user:1

# Lists
LPUSH notifications:user:1 "New message"
RPOP notifications:user:1
LRANGE notifications:user:1 0 -1  # Get all

# Sets
SADD tags:post:1 "python" "django" "rest-api"
SMEMBERS tags:post:1
SISMEMBER tags:post:1 "python"  # Check membership

# Sorted Sets
ZADD leaderboard 100 "player1" 200 "player2"
ZRANGE leaderboard 0 -1 WITHSCORES  # Get ranked
```

### Expiration

```bash
# Set with TTL
SETEX cache:products "..." 300  # Expires in 5 minutes

# Check TTL
TTL cache:products

# Remove
DEL cache:products
```

## 11.2 Django Caching

### Settings

```python
# settings.py
CACHES = {
    "default": {
        "BACKEND": "django.core.cache.backends.redis.RedisCache",
        "LOCATION": os.environ.get("REDIS_URL", "redis://127.0.0.1:6379/1"),
    }
}

# Alternative: local memory (development)
CACHES = {
    "default": {
        "BACKEND": "django.core.cache.backends.locmem.LocMemCache",
    }
}
```

### Per-View Caching

```python
from django.views.decorators.cache import cache_page

@cache_page(60 * 15)  # Cache for 15 minutes
def product_list(request):
    products = Product.objects.all()
    return render(request, "products/list.html", {"products": products})
```

### Template Fragment Caching

```html
{% load cache %}

{% cache 300 product_list %}
    <!-- Expensive query result cached for 5 minutes -->
    {% for product in products %}
        {{ product.name }}
    {% endfor %}
{% endcache %}
```

### Low-Level Cache API

```python
from django.core.cache import cache

# Set
cache.set("products:list", products, timeout=300)

# Get
products = cache.get("products:list")

# Get or set
products = cache.get_or_set(
    "products:list",
    lambda: Product.objects.all(),
    timeout=300
)

# Delete
cache.delete("products:list")

# Get many
cache.get_many(["key1", "key2", "key3"])
```

## 11.3 Caching Strategies

### Cache-Aside (Lazy Loading)

```python
def get_product_list():
    # 1. Check cache
    cache_key = "products:list"
    products = cache.get(cache_key)

    if products is None:
        # 2. Cache miss — query database
        products = list(Product.objects.all())
        # 3. Store in cache
        cache.set(cache_key, products, timeout=300)

    return products
```

### Cache Invalidation

```python
# When product is updated, invalidate cache
def update_product(product_id, data):
    product = Product.objects.get(id=product_id)
    for key, value in data.items():
        setattr(product, key, value)
    product.save()
    # Invalidate related caches
    cache.delete("products:list")
    cache.delete(f"products:{product_id}")
```

### Cache Stampede Prevention

```python
import threading

def get_or_set_with_lock(key, compute_fn, timeout=300):
    """Prevent multiple processes from recomputing the same cache key."""
    value = cache.get(key)
    if value is not None:
        return value

    lock_key = f"lock:{key}"
    lock = cache.lock(lock_key, timeout=5)

    if lock.acquire(blocking=True):
        try:
            # Double-check after acquiring lock
            value = cache.get(key)
            if value is None:
                value = compute_fn()
                cache.set(key, value, timeout=timeout)
        finally:
            lock.release()
    else:
        # Another process is computing, wait and retry
        time.sleep(0.1)
        return cache.get(key)

    return value
```

## 11.4 Session Storage in Redis

```python
# settings.py
SESSION_ENGINE = "django.contrib.sessions.backends.cache"
SESSION_CACHE_ALIAS = "default"
```

## Common Caching Mistakes

- 🚨 Caching everything without invalidation strategy
- 🚨 Using cache as primary data store
- 🚨 Not considering cache stampede
- 🚨 Caching user-specific data with shared keys
- 🚨 Not warming cache on deployment

## ✅ Phase 11 Checkpoint

- [ ] Redis data structures (strings, hashes, lists, sets, sorted sets)
- [ ] Django cache configuration
- [ ] Per-view, template fragment, and low-level caching
- [ ] Cache-aside pattern
- [ ] Cache invalidation strategies
- [ ] Cache stampede prevention

---

# Phase 12 — Celery and Background Jobs

> **Prerequisite:** Phases 5, 11.
> **Goal:** Process background tasks asynchronously with Celery.

## 12.1 Why Background Tasks

```text
Synchronous (bad for long tasks):
  User clicks "Export" → Server generates report → User waits 30 seconds → Done

Asynchronous (good):
  User clicks "Export" → Server queues task → User gets "Processing" message
  → Background worker generates report → User notified when ready
```

### When to Use Background Tasks

| Task | Use Background? |
|---|---|
| Send email | Yes |
| Generate report | Yes |
| Process image | Yes |
| Sync data from API | Yes |
| Simple CRUD | No |
| Real-time response | No |

## 12.2 Celery Setup

### Configuration

```python
# myproject/celery.py
import os
from celery import Celery

os.environ.setdefault("DJANGO_SETTINGS_MODULE", "myproject.settings")

app = Celery("myproject")
app.config_from_object("django.conf:settings", namespace="CELERY")
app.autodiscover_tasks()

# settings.py
CELERY_BROKER_URL = os.environ.get("REDIS_URL", "redis://localhost:6379/0")
CELERY_RESULT_BACKEND = os.environ.get("REDIS_URL", "redis://localhost:6379/0")
CELERY_ACCEPT_CONTENT = ["json"]
CELERY_TASK_SERIALIZER = "json"
CELERY_RESULT_SERIALIZER = "json"
```

### Defining Tasks

```python
# users/tasks.py
from celery import shared_task
from django.core.mail import send_mail
import logging

logger = logging.getLogger(__name__)

@shared_task(bind=True, max_retries=3)
def send_welcome_email(self, user_id: int) -> bool:
    """Send welcome email to new user."""
    from users.models import User  # Import inside task to avoid circular imports

    try:
        user = User.objects.get(id=user_id)
        send_mail(
            subject="Welcome!",
            message=f"Hello {user.username}!",
            from_email="noreply@example.com",
            recipient_list=[user.email],
        )
        logger.info("Welcome email sent to %s", user.email)
        return True
    except User.DoesNotExist:
        logger.error("User %s not found", user_id)
        return False
    except Exception as exc:
        logger.exception("Failed to send email to user %s", user_id)
        raise self.retry(exc=exc, countdown=60)  # Retry in 60 seconds
```

### Calling Tasks

```python
# Synchronous (bad for long tasks)
send_welcome_email(user.id)

# Asynchronous (good)
send_welcome_email.delay(user.id)

# With arguments
send_welcome_email.apply_async(
    args=[user.id],
    countdown=10,  # Delay 10 seconds
    expires=3600,   # Task expires after 1 hour
)
```

## 12.3 Periodic Tasks

```python
# settings.py
CELERY_BEAT_SCHEDULE = {
    "cleanup-expired-sessions": {
        "task": "users.tasks.cleanup_expired_sessions",
        "schedule": crontab(hour=2, minute=0),  # Daily at 2 AM
    },
    "generate-daily-report": {
        "task": "reports.tasks.generate_daily_report",
        "schedule": crontab(hour=6, minute=0),
    },
    "sync-external-data": {
        "task": "integrations.tasks.sync_data",
        "schedule": timedelta(minutes=30),
    },
}
```

## 12.4 Monitoring

```bash
# Flower (Celery monitoring tool)
pip install flower
celery -A myproject flower

# Monitor tasks in real-time
# View worker status
# See task history and failures
```

## Common Celery Mistakes

- 🚨 Importing models at the module level (causes circular imports)
- 🚨 Not handling task failures (missing retry logic)
- 🚨 Serializing complex objects (use IDs, fetch in task)
- 🚨 Not using `bind=True` for retry functionality
- 🚨 Running too many workers (consume too much memory)

## ✅ Phase 12 Checkpoint

- [ ] Celery architecture (broker, worker, result backend)
- [ ] Defining and calling tasks
- [ ] Retry logic with exponential backoff
- [ ] Periodic tasks with Celery Beat
- [ ] Monitoring with Flower

---

# Phase 13 — Testing

> **Prerequisite:** Phases 5-9.
> **Goal:** Write professional tests that catch real bugs.

## 13.1 Testing Philosophy

### Testing Pyramid

```text
        /\
       /  \        E2E Tests (few, slow, expensive)
      /    \
     /------\      Integration Tests (moderate, test components together)
    /        \
   /----------\    Unit Tests (many, fast, cheap)
```

### What to Test

| Test Type | What | Example |
|---|---|---|
| Unit | Single function/class | `calculate_total()` |
| Integration | Components working together | View + Serializer + Model |
| E2E | Full user flow | Register → Login → Create Post |

## 13.2 pytest with Django

### Setup

```python
# pyproject.toml
[tool.pytest.ini_options]
django_settings_module = "myproject.settings"
python_files = ["test_*.py"]
python_classes = ["Test*"]
python_functions = ["test_*"]

# conftest.py
import pytest
from django.contrib.auth import get_user_model

User = get_user_model()

@pytest.fixture
def user(db):
    return User.objects.create_user(
        username="testuser",
        email="test@example.com",
        password="testpass123",
    )

@pytest.fixture
def authenticated_client(client, user):
    client.login(email="test@example.com", password="testpass123")
    return client
```

### Unit Tests

```python
# tests/test_models.py
import pytest
from users.models import User

@pytest.mark.django_db
class TestUserModel:
    def test_create_user(self):
        user = User.objects.create_user(
            username="alice",
            email="alice@example.com",
            password="pass123",
        )
        assert user.username == "alice"
        assert user.is_active is True
        assert user.check_password("pass123")

    def test_create_superuser(self):
        user = User.objects.create_superuser(
            username="admin",
            email="admin@example.com",
            password="admin123",
        )
        assert user.is_staff is True
        assert user.is_superuser is True
```

### API Tests

```python
# tests/test_api.py
import pytest
from rest_framework import status
from rest_framework.test import APIClient
from posts.models import Post

@pytest.fixture
def api_client():
    return APIClient()

@pytest.fixture
def user(db):
    from django.contrib.auth import get_user_model
    User = get_user_model()
    return User.objects.create_user(
        username="testuser",
        email="test@example.com",
        password="testpass123",
    )

@pytest.fixture
def authenticated_client(api_client, user):
    api_client.force_authenticate(user=user)
    return api_client

@pytest.mark.django_db
class TestPostAPI:
    def test_list_posts(self, api_client):
        Post.objects.create(title="Test", content="Content", author=user)
        response = api_client.get("/api/posts/")
        assert response.status_code == status.HTTP_200_OK
        assert len(response.data["results"]) == 1

    def test_create_post(self, authenticated_client):
        response = authenticated_client.post(
            "/api/posts/",
            {"title": "New Post", "content": "Content"},
            format="json",
        )
        assert response.status_code == status.HTTP_201_CREATED
        assert Post.objects.count() == 1

    def test_unauthenticated_create(self, api_client):
        response = api_client.post(
            "/api/posts/",
            {"title": "New Post", "content": "Content"},
            format="json",
        )
        assert response.status_code == status.HTTP_401_UNAUTHORIZED

    def test_only_author_can_edit(self, api_client, user):
        post = Post.objects.create(title="Test", content="Content", author=user)
        other_user = User.objects.create_user(
            username="other", email="other@example.com", password="pass"
        )
        api_client.force_authenticate(user=other_user)
        response = api_client.patch(
            f"/api/posts/{post.id}/",
            {"title": "Hacked"},
            format="json",
        )
        assert response.status_code == status.HTTP_403_FORBIDDEN
```

### Mocking

```python
from unittest.mock import patch, MagicMock

@pytest.mark.django_db
class TestEmailSending:
    @patch("users.tasks.send_mail")
    def test_send_welcome_email(self, mock_send_mail, user):
        from users.tasks import send_welcome_email

        send_welcome_email(user.id)

        mock_send_mail.assert_called_once()
        call_args = mock_send_mail.call_args
        assert "Welcome!" in call_args[1]["subject"]

    @patch("integrations.client.ExternalAPI")
    def test_sync_external_data(self, mock_api_class):
        mock_api = mock_api_class.return_value
        mock_api.get_users.return_value = [{"id": 1, "name": "Alice"}]

        result = sync_external_data()

        assert result == 1
        mock_api.get_users.assert_called_once()
```

## 13.3 Test Coverage

```bash
# Install
pip install pytest-cov

# Run with coverage
pytest --cov=. --cov-report=html

# View report
open htmlcov/index.html
```

## 13.4 Test-Driven Development (TDD)

```text
1. Write a failing test
2. Write minimum code to pass
3. Refactor
4. Repeat

Example:
1. Test: "POST /api/posts/ should create a post" → FAILS (no view yet)
2. Write the view → TEST PASSES
3. Refactor → TEST STILL PASSES
4. Add test for validation → FAILS
5. Add validation → PASSES
```

## Common Testing Mistakes

- 🚨 Not testing edge cases (empty inputs, permissions, errors)
- 🚨 Testing implementation details instead of behavior
- 🚨 Slow tests (use `pytest-xdist` for parallel execution)
- 🚨 Not isolating tests (tests depend on execution order)
- 🚨 Mocking everything (integration tests catch real bugs)

## ✅ Phase 13 Checkpoint

- [ ] pytest and pytest-django setup
- [ ] Fixtures and factories
- [ ] Unit tests for models and functions
- [ ] API tests with DRF's APIClient
- [ ] Mocking external dependencies
- [ ] Test coverage reporting
- [ ] TDD basics

---

# Phase 14 — Docker

> **Prerequisite:** Basic command line.
> **Goal:** Containerize Django applications for consistent development and deployment.

## 14.1 Docker Fundamentals

### Concepts

```text
Image:     Blueprint for a container (read-only)
Container: Running instance of an image
Dockerfile: Instructions for building an image
Volume:     Persistent data storage
Network:    Container-to-container communication
```

### Dockerfile

```dockerfile
# Dockerfile
FROM python:3.12-slim

# Set environment variables
ENV PYTHONDONTWRITEBYTECODE=1
ENV PYTHONUNBUFFERED=1

# Set work directory
WORKDIR /app

# Install system dependencies
RUN apt-get update && apt-get install -y \
    gcc \
    libpq-dev \
    && rm -rf /var/lib/apt/lists/*

# Install Python dependencies
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

# Copy project
COPY . .

# Collect static files
RUN python manage.py collectstatic --noinput

# Expose port
EXPOSE 8000

# Run with gunicorn
CMD ["gunicorn", "myproject.wsgi:application", "--bind", "0.0.0.0:8000"]
```

## 14.2 Docker Compose

```yaml
# docker-compose.yml
services:
  db:
    image: postgres:16-alpine
    volumes:
      - postgres_data:/var/lib/postgresql/data
    environment:
      POSTGRES_DB: myproject
      POSTGRES_USER: postgres
      POSTGRES_PASSWORD: postgres
    ports:
      - "5432:5432"

  redis:
    image: redis:7-alpine
    ports:
      - "6379:6379"

  web:
    build: .
    command: python manage.py runserver 0.0.0.0:8000
    volumes:
      - .:/app
    ports:
      - "8000:8000"
    environment:
      - DEBUG=True
      - DATABASE_URL=postgres://postgres:postgres@db:5432/myproject
      - REDIS_URL=redis://redis:6379/0
    depends_on:
      - db
      - redis

  celery:
    build: .
    command: celery -A myproject worker -l info
    volumes:
      - .:/app
    environment:
      - DATABASE_URL=postgres://postgres:postgres@db:5432/myproject
      - REDIS_URL=redis://redis:6379/0
    depends_on:
      - db
      - redis

  celery-beat:
    build: .
    command: celery -A myproject beat -l info
    volumes:
      - .:/app
    environment:
      - DATABASE_URL=postgres://postgres:postgres@db:5432/myproject
      - REDIS_URL=redis://redis:6379/0
    depends_on:
      - redis

volumes:
  postgres_data:
```

## 14.3 Essential Commands

```bash
# Build
docker compose build

# Run
docker compose up -d

# Stop
docker compose down

# Logs
docker compose logs -f web

# Execute command in container
docker compose exec web python manage.py shell

# Database operations
docker compose exec web python manage.py migrate
docker compose exec web python manage.py createsuperuser
```

## Common Docker Mistakes

- 🚨 Not using `.dockerignore` (sends entire `.git` to build context)
- 🚨 Running as root in container
- 🚨 Not using multi-stage builds for production
- 🚨 Hardcoding secrets in Dockerfile
- 🚨 Not using volumes for development (causes permission issues)

## ✅ Phase 14 Checkpoint

- [ ] Write a Dockerfile for Django
- [ ] Configure Docker Compose with multiple services
- [ ] Use volumes for persistent data
- [ ] Use environment variables for configuration
- [ ] Debug container issues with logs and exec

---

# Phase 15 — Linux and Server Fundamentals

> **Prerequisite:** Basic command line.
> **Goal:** Enough Linux knowledge for backend development and server management.

## 15.1 Essential Commands

### File System

```bash
ls -la          # List files with details
cd /path        # Change directory
pwd             # Print working directory
mkdir -p dir    # Create directory
rm -rf dir      # Remove directory
cp -r src dst   # Copy directory
mv src dst      # Move/rename
find . -name "*.py"  # Find files
grep -r "pattern" .  # Search in files
cat file.txt    # Print file contents
less file.txt   # View file (scrollable)
head -n 20 file # First 20 lines
tail -f log.txt # Follow log file
```

### Permissions

```bash
chmod 755 file   # rwxr-xr-x
chmod +x script  # Make executable
chown user:group file
ls -la           # View permissions
```

### Process Management

```bash
ps aux          # List processes
top             # Process monitor
htop            # Better process monitor
kill PID        # Kill process
kill -9 PID     # Force kill
nohup cmd &     # Run in background
systemctl status nginx  # Service status
systemctl start nginx   # Start service
systemctl stop nginx    # Stop service
systemctl restart nginx # Restart service
journalctl -u nginx -f  # Follow service logs
```

### Networking

```bash
curl -I https://example.com    # HTTP headers
curl -X POST url -d "data"     # POST request
netstat -tlnp                  # List listening ports
ss -tlnp                       # Same (modern)
ping host                      # Test connectivity
dig domain                     # DNS lookup
host domain                    # DNS lookup (simpler)
```

### Disk and Memory

```bash
df -h               # Disk usage
du -sh /var/log     # Directory size
free -h             # Memory usage
uptime              # System uptime
```

## 15.2 SSH

```bash
# Connect to server
ssh user@server-ip

# Key-based authentication
ssh-keygen -t ed25519
ssh-copy-id user@server-ip

# SSH config (~/.ssh/config)
Host production
    HostName 192.168.1.100
    User deploy
    IdentityFile ~/.ssh/id_ed25519

# Now use: ssh production
```

## 15.3 Systemd Services

```ini
# /etc/systemd/system/myproject.service
[Unit]
Description=Gunicorn Django Application
After=network.target

[Service]
User=deploy
Group=www-data
WorkingDirectory=/opt/myproject
ExecStart=/opt/myproject/venv/bin/gunicorn \
    --workers 3 \
    --bind unix:/run/gunicorn.sock \
    myproject.wsgi:application
Restart=on-failure

[Install]
WantedBy=multi-user.target
```

## ✅ Phase 15 Checkpoint

- [ ] Essential Linux commands
- [ ] File permissions
- [ ] Process management
- [ ] SSH key-based authentication
- [ ] Systemd service management

---

# Phase 16 — Production Django

> **Prerequisite:** Phases 5-15.
> **Goal:** Configure Django for production with security, performance, and reliability.

## 16.1 Production Architecture

```text
Client
  ↓
Nginx (reverse proxy, static files, SSL)
  ↓
Gunicorn/Uvicorn (WSGI/ASGI server)
  ↓
Django Application
  ├── PostgreSQL (database)
  ├── Redis (cache, sessions, Celery broker)
  └── Celery Workers (background tasks)
```

## 16.2 Security Configuration

```python
# settings.py (production)
DEBUG = False
ALLOWED_HOSTS = ["yourdomain.com"]

# Security headers
SECURE_HSTS_SECONDS = 31536000
SECURE_HSTS_INCLUDE_SUBDOMAINS = True
SECURE_HSTS_PRELOAD = True
SECURE_SSL_REDIRECT = True
SESSION_COOKIE_SECURE = True
CSRF_COOKIE_SECURE = True
SECURE_BROWSER_XSS_FILTER = True
SECURE_CONTENT_TYPE_NOSNIFF = True
X_FRAME_OPTIONS = "DENY"

# Static files
STATIC_URL = "/static/"
STATIC_ROOT = BASE_DIR / "staticfiles"
```

## 16.3 Nginx Configuration

```nginx
# /etc/nginx/sites-available/myproject
server {
    listen 80;
    server_name yourdomain.com;
    return 301 https://$server_name$request_uri;
}

server {
    listen 443 ssl http2;
    server_name yourdomain.com;

    ssl_certificate /etc/letsencrypt/live/yourdomain.com/fullchain.pem;
    ssl_certificate_key /etc/letsencrypt/live/yourdomain.com/privkey.pem;

    # Static files
    location /static/ {
        alias /opt/myproject/staticfiles/;
        expires 30d;
        add_header Cache-Control "public, immutable";
    }

    # Media files
    location /media/ {
        alias /opt/myproject/media/;
        expires 7d;
    }

    # Django application
    location / {
        proxy_pass http://unix:/run/gunicorn.sock;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
    }
}
```

## 16.4 Logging Configuration

```python
# settings.py
LOGGING = {
    "version": 1,
    "disable_existing_loggers": False,
    "formatters": {
        "verbose": {
            "format": "{levelname} {asctime} {module} {message}",
            "style": "{",
        },
    },
    "handlers": {
        "console": {
            "class": "logging.StreamHandler",
            "formatter": "verbose",
        },
        "file": {
            "class": "logging.handlers.RotatingFileHandler",
            "filename": BASE_DIR / "logs" / "django.log",
            "maxBytes": 1024 * 1024 * 10,  # 10MB
            "backupCount": 5,
            "formatter": "verbose",
        },
    },
    "root": {
        "handlers": ["console", "file"],
        "level": "INFO",
    },
    "loggers": {
        "django": {
            "handlers": ["console", "file"],
            "level": "INFO",
            "propagate": False,
        },
        "users": {
            "handlers": ["console", "file"],
            "level": "DEBUG",
            "propagate": False,
        },
    },
}
```

## 16.5 Error Handling

```python
# myproject/middleware.py
import logging

logger = logging.getLogger(__name__)

class ExceptionLoggingMiddleware:
    def __init__(self, get_response):
        self.get_response = get_response

    def __call__(self, request):
        response = self.get_response(request)
        return response

    def process_exception(self, request, exception):
        logger.exception(
            "Unhandled exception: %s %s",
            request.method,
            request.path,
            exc_info=True,
        )
        # Return JSON error in production
        from django.http import JsonResponse
        return JsonResponse(
            {"error": "Internal server error"},
            status=500,
        )
```

## ✅ Phase 16 Checkpoint

- [ ] Production settings configuration
- [ ] Security headers
- [ ] Nginx reverse proxy setup
- [ ] Logging configuration
- [ ] Error handling middleware
- [ ] Static file serving

---

# Phase 17 — CI/CD

> **Prerequisite:** Phases 13-14.
> **Goal:** Automate testing and deployment with GitHub Actions.

## 17.1 GitHub Actions Pipeline

```yaml
# .github/workflows/ci.yml
name: CI

on:
  push:
    branches: [main]
  pull_request:
    branches: [main]

jobs:
  lint:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - uses: actions/setup-python@v5
        with:
          python-version: "3.12"
      - run: pip install ruff
      - run: ruff check .
      - run: ruff format --check .

  test:
    runs-on: ubuntu-latest
    services:
      postgres:
        image: postgres:16
        env:
          POSTGRES_DB: test_db
          POSTGRES_USER: postgres
          POSTGRES_PASSWORD: postgres
        ports:
          - 5432:5432
        options: >-
          --health-cmd pg_isready
          --health-interval 10s
          --health-timeout 5s
          --health-retries 5
      redis:
        image: redis:7
        ports:
          - 6379:6379

    steps:
      - uses: actions/checkout@v4
      - uses: actions/setup-python@v5
        with:
          python-version: "3.12"
          cache: pip
      - run: pip install -r requirements.txt
      - run: pytest --cov=. --cov-report=xml
        env:
          DATABASE_URL: postgres://postgres:postgres@localhost:5432/test_db
          REDIS_URL: redis://localhost:6379/0
          SECRET_KEY: test-secret-key
          DEBUG: "false"

  build:
    needs: [lint, test]
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - run: docker build -t myproject:${{ github.sha }} .
```

## 17.2 Pipeline Flow

```text
Push to main
    ↓
┌───────┐    ┌───────┐    ┌───────┐
│ Lint  │    │ Test  │    │Type   │
│ (Ruff)│    │(pytest│    │Check  │
└───┬───┘    └───┬───┘    └───┬───┘
    │            │            │
    └────────────┴────────────┘
                 ↓
          ┌──────────────┐
          │ Build Docker │
          │    Image     │
          └──────────────┘
                 ↓
          ┌──────────────┐
          │   Deploy     │
          │ (if on main) │
          └──────────────┘
```

## 17.3 Deployment

```yaml
# .github/workflows/deploy.yml
name: Deploy

on:
  push:
    branches: [main]

jobs:
  deploy:
    runs-on: ubuntu-latest
    needs: [lint, test]
    steps:
      - uses: actions/checkout@v4
      - name: Deploy to server
        uses: appleboy/ssh-action@master
        with:
          host: ${{ secrets.SERVER_HOST }}
          username: ${{ secrets.SERVER_USER }}
          key: ${{ secrets.SSH_KEY }}
          script: |
            cd /opt/myproject
            git pull origin main
            docker compose -f docker-compose.prod.yml build
            docker compose -f docker-compose.prod.yml up -d
            docker compose exec web python manage.py migrate
            docker compose exec web python manage.py collectstatic --noinput
```

## ✅ Phase 17 Checkpoint

- [ ] GitHub Actions workflow for CI
- [ ] Automated linting and testing
- [ ] Docker image build
- [ ] Automated deployment
- [ ] Secrets management

---

# Phase 18 — Observability

> **Prerequisite:** Phases 16-17.
> **Goal:** Monitor production systems and diagnose issues.

## 18.1 Three Pillars of Observability

```text
Logs:      What happened? (discrete events)
Metrics:   How much? How fast? (numeric measurements)
Traces:    Where did time go? (request flow through services)
```

## 18.2 Health Checks

```python
# views.py
from django.http import JsonResponse
from django.db import connection
import redis

def health_check(request):
    """Basic health check."""
    return JsonResponse({"status": "ok"})

def deep_health_check(request):
    """Comprehensive health check."""
    checks = {}

    # Database check
    try:
        with connection.cursor() as cursor:
            cursor.execute("SELECT 1")
        checks["database"] = "ok"
    except Exception as e:
        checks["database"] = f"error: {str(e)}"

    # Redis check
    try:
        r = redis.from_url(os.environ.get("REDIS_URL"))
        r.ping()
        checks["redis"] = "ok"
    except Exception as e:
        checks["redis"] = f"error: {str(e)}"

    status_code = 200 if all(v == "ok" for v in checks.values()) else 503
    return JsonResponse(checks, status=status_code)
```

## 18.3 Structured Logging

```python
import structlog

logger = structlog.get_logger()

def process_order(order_id: int) -> None:
    log = logger.bind(order_id=order_id)
    log.info("order.processing_started")

    try:
        order = Order.objects.get(id=order_id)
        order.process()
        log.info("order.processed", total=order.total)
    except Order.DoesNotExist:
        log.error("order.not_found")
        raise
    except Exception:
        log.exception("order.processing_failed")
        raise
```

## 18.4 Diagnosing Common Issues

### Slow API

```text
1. Check application logs for slow queries
2. Check database slow query log
3. Run EXPLAIN ANALYZE on suspicious queries
4. Check if N+1 queries are happening
5. Check Redis/cache hit rates
6. Profile with django-silk or py-spy
```

### High CPU

```text
1. Identify which process is consuming CPU (top/htop)
2. Check if it's the application, database, or Celery
3. Profile the application (cProfile, py-spy)
4. Check for infinite loops or expensive computations
5. Consider adding caching
```

### Memory Issues

```text
1. Monitor memory usage over time
2. Check for memory leaks (objects not being garbage collected)
3. Check for large QuerySets not being evaluated
4. Use tracemalloc to find memory allocation sources
5. Consider connection pooling
```

## ✅ Phase 18 Checkpoint

- [ ] Health check endpoints
- [ ] Structured logging
- [ ] Metrics collection basics
- [ ] Can diagnose slow APIs
- [ ] Can diagnose high CPU/memory

---

# Phase 19 — Performance Engineering

> **Prerequisite:** Phases 6-7, 11.
> **Goal:** Identify and fix performance bottlenecks systematically.

## 19.1 Database Optimization

### Indexes

```sql
-- Identify slow queries
SELECT query, mean_time, calls
FROM pg_stat_statements
ORDER BY mean_time DESC
LIMIT 10;

-- Add index for frequent queries
CREATE INDEX idx_posts_author_created ON posts(author_id, created_at DESC);

-- Partial index for common filter
CREATE INDEX idx_active_users ON users(id) WHERE is_active = true;
```

### Query Optimization

```python
# BAD
for post in Post.objects.all():
    print(post.author.username)  # N+1

# GOOD
for post in Post.objects.select_related("author").all():
    print(post.author.username)

# BAD
users = User.objects.all()  # Fetches all fields
for user in users:
    print(user.username)  # Only needs username

# GOOD
users = User.objects.only("id", "username")  # Only fetch needed fields
```

## 19.2 Caching Strategy

```text
Level 1: Template fragment caching (HTML snippets)
Level 2: View caching (entire responses)
Level 3: Low-level caching (computed values)
Level 4: Database query caching
Level 5: CDN for static files
```

## 19.3 Connection Pooling

```python
# settings.py
DATABASES = {
    "default": {
        ...
        "CONN_MAX_AGE": 600,  # Persistent connections
        "CONN_HEALTH_CHECKS": True,
    }
}

# With pgbouncer (recommended for production)
# Add pgbouncer between Django and PostgreSQL
```

## 19.4 Profiling

```python
# django-silk (in development)
# pip install django-silk
# Add to INSTALLED_APPS and middleware

# py-spy (production)
# pip install py-spy
# py-spy top --pid <django-pid>

# cProfile
import cProfile
cProfile.run("my_function()")
```

## 19.5 Load Testing

```bash
# Using locust
pip install locust

# locustfile.py
from locust import HttpUser, task

class WebsiteUser(HttpUser):
    @task
    def view_posts(self):
        self.client.get("/api/posts/")

# Run
locust -f locustfile.py --host=http://localhost:8000
```

## ✅ Phase 19 Checkpoint

- [ ] Can identify slow queries with EXPLAIN ANALYZE
- [ ] Know how to add appropriate indexes
- [ ] Can implement multi-level caching
- [ ] Can profile Django applications
- [ ] Can run basic load tests

---

# Phase 20 — System Design

> **Prerequisite:** All previous phases.
> **Goal:** Design scalable backend systems and ace system design interviews.

## 20.1 Core Concepts

### Scalability

```text
Vertical Scaling (Scale Up):  More CPU/RAM to one server
Horizontal Scaling (Scale Out): More servers

Vertical: Simple, limited by hardware
Horizontal: Complex, virtually unlimited
```

### Availability

```text
Availability = Uptime / (Uptime + Downtime)

99.9%   = 8.76 hours downtime/year
99.99%  = 52.6 minutes downtime/year
99.999% = 5.26 minutes downtime/year
```

### CAP Theorem

```text
In a distributed system, you can only guarantee 2 of 3:

C - Consistency:  All nodes see the same data at the same time
A - Availability: Every request gets a response
P - Partition Tolerance: System works despite network failures

Real-world: P is always required (networks fail)
So you choose: CP (consistency) or AP (availability)
```

## 20.2 Architecture Patterns

### Monolith vs Microservices

```text
Monolith:
  ✅ Simple to develop and deploy
  ✅ Easy to debug
  ✅ Low latency (no network calls between components)
  ❌ Hard to scale individual components
  ❌ Large codebase becomes hard to manage

Microservices:
  ✅ Scale individual services
  ✅ Independent deployments
  ✅ Team autonomy
  ❌ Complex infrastructure
  ❌ Network latency between services
  ❌ Distributed debugging

Rule: Start with a monolith. Split when you have a clear reason.
```

## 20.3 Design Problems

### URL Shortener

```text
Requirements:
  - Shorten URLs
  - Redirect short URLs to original
  - Custom aliases
  - Expiration

API:
  POST /api/shorten  → {"url": "...", "alias": "..."}
  GET  /{alias}      → 301 redirect

Database:
  urls: id, short_code, original_url, created_at, expires_at, click_count

Design:
  - Hash function (base62) to generate short codes
  - Redis cache for hot URLs
  - Analytics with click tracking
```

### Notification System

```text
Requirements:
  - Send notifications via email, push, SMS
  - User preferences for channels
  - Rate limiting
  - Delivery tracking

Architecture:
  NotificationService → MessageQueue → Channel Workers
                                        ├── EmailWorker
                                        ├── PushWorker
                                        └── SMSWorker

Database:
  notifications: id, user_id, channel, title, body, status, sent_at
  user_preferences: user_id, channel, enabled, quiet_hours
```

### Chat System

```text
Requirements:
  - Real-time messaging
  - Message history
  - Online status
  - Read receipts

Architecture:
  Client ←→ WebSocket Server ←→ Message Queue ←→ Chat Service
                                                  ├── Message Storage
                                                  ├── User Service
                                                  └── Notification Service

Technology:
  - Django Channels (WebSockets)
  - Redis (message broker, presence)
  - PostgreSQL (message history)
```

## ✅ Phase 20 Checkpoint

- [ ] Can explain scalability, availability, consistency
- [ ] Understand CAP theorem
- [ ] Can design a URL shortener
- [ ] Can design a notification system
- [ ] Can design a chat system
- [ ] Can explain trade-offs in architecture decisions

---

# Phase 21 — Design Patterns

> **Prerequisite:** Phase 2 (SOLID), Phase 5 (Django).
> **Goal:** Apply practical design patterns in Python/Django projects.

## 21.1 Repository Pattern

```python
# Problem: Business logic coupled to ORM
# Solution: Abstract data access behind an interface

from abc import ABC, abstractmethod

class UserRepository(ABC):
    @abstractmethod
    def get_by_id(self, user_id: int) -> User | None: ...

    @abstractmethod
    def get_by_email(self, email: str) -> User | None: ...

    @abstractmethod
    def create(self, data: dict) -> User: ...

# Django ORM implementation
class DjangoUserRepository(UserRepository):
    def get_by_id(self, user_id: int) -> User | None:
        return User.objects.filter(id=user_id).first()

    def get_by_email(self, email: str) -> User | None:
        return User.objects.filter(email=email).first()

    def create(self, data: dict) -> User:
        return User.objects.create(**data)

# In-memory implementation (for testing)
class InMemoryUserRepository(UserRepository):
    def __init__(self):
        self._users = {}
        self._next_id = 1

    def get_by_id(self, user_id: int) -> User | None:
        return self._users.get(user_id)

    def create(self, data: dict) -> User:
        user = User(id=self._next_id, **data)
        self._users[self._next_id] = user
        self._next_id += 1
        return user
```

## 21.2 Service Layer

```python
# Problem: Business logic scattered in views
# Solution: Centralize in service classes

class OrderService:
    def __init__(
        self,
        order_repository: OrderRepository,
        inventory_service: InventoryService,
        email_service: EmailService,
    ):
        self.order_repository = order_repository
        self.inventory_service = inventory_service
        self.email_service = email_service

    @transaction.atomic
    def create_order(self, user: User, items: list[dict]) -> Order:
        # Validate inventory
        for item in items:
            if not self.inventory_service.check_availability(item["product_id"], item["quantity"]):
                raise ValidationError(f"Product {item['product_id']} out of stock")

        # Create order
        order = self.order_repository.create(user=user, items=items)

        # Reserve inventory
        for item in items:
            self.inventory_service.reserve(item["product_id"], item["quantity"])

        # Send confirmation
        self.email_service.send_order_confirmation(order)

        return order
```

## 21.3 Strategy Pattern

```python
# Problem: Multiple ways to do the same thing
# Solution: Interchangeable algorithms

class PricingStrategy(ABC):
    @abstractmethod
    def calculate(self, base_price: float, quantity: int) -> float: ...

class StandardPricing(PricingStrategy):
    def calculate(self, base_price: float, quantity: int) -> float:
        return base_price * quantity

class BulkPricing(PricingStrategy):
    def calculate(self, base_price: float, quantity: int) -> float:
        discount = 0.1 if quantity >= 10 else 0
        return base_price * quantity * (1 - discount)

class Order:
    def __init__(self, pricing_strategy: PricingStrategy):
        self.pricing_strategy = pricing_strategy

    def total(self, items: list[dict]) -> float:
        return sum(
            self.pricing_strategy.calculate(item["price"], item["quantity"])
            for item in items
        )
```

## 21.4 Factory Pattern

```python
class NotificationFactory:
    _senders = {
        "email": EmailSender,
        "sms": SMSSender,
        "push": PushSender,
    }

    @classmethod
    def create(cls, channel: str) -> NotificationSender:
        sender_class = cls._senders.get(channel)
        if not sender_class:
            raise ValueError(f"Unknown channel: {channel}")
        return sender_class()

# Usage
sender = NotificationFactory.create("email")
sender.send("user@example.com", "Hello!")
```

## ✅ Phase 21 Checkpoint

- [ ] Repository pattern
- [ ] Service layer
- [ ] Strategy pattern
- [ ] Factory pattern
- [ ] Know when to use each pattern
- [ ] Know when NOT to use each pattern

---

# Phase 22 — Architecture

> **Prerequisite:** Phases 2, 21.
> **Goal:** Design maintainable Django project structures.

## 22.1 Project Structure Comparison

### Simple Django

```text
myproject/
├── manage.py
├── myproject/settings.py
├── users/
│   ├── models.py
│   ├── views.py
│   └── urls.py
└── blog/
    ├── models.py
    ├── views.py
    └── urls.py
```

### Production Django (Layered)

```text
myproject/
├── manage.py
├── config/
│   ├── settings/
│   │   ├── base.py
│   │   ├── development.py
│   │   └── production.py
│   ├── urls.py
│   └── wsgi.py
├── apps/
│   ├── users/
│   │   ├── models.py
│   │   ├── serializers.py
│   │   ├── views.py
│   │   ├── urls.py
│   │   ├── services.py
│   │   ├── repositories.py
│   │   ├── tasks.py
│   │   └── tests/
│   │       ├── test_models.py
│   │       ├── test_views.py
│   │       └── test_services.py
│   └── blog/
│       └── ...
├── core/
│   ├── permissions.py
│   ├── pagination.py
│   ├── exceptions.py
│   └── middleware.py
├── templates/
├── static/
└── requirements/
    ├── base.txt
    ├── development.txt
    └── production.txt
```

## 22.2 Clean Architecture Principles

```text
Dependency Rule:
  Inner layers do NOT depend on outer layers.
  Domain → Application → Infrastructure → Presentation

Domain:      Business logic, entities, value objects
Application: Use cases, services
Infrastructure: Database, external APIs, cache
Presentation: Views, serializers, templates
```

## 22.3 When to Use What

| Project Size | Recommended Structure |
|---|---|
| Prototype / Hackathon | Simple Django structure |
| Small team / MVP | Apps + services |
| Medium production | Layered architecture |
| Large production | Modular monolith |

## ✅ Phase 22 Checkpoint

- [ ] Can choose appropriate project structure
- [ ] Understand layered architecture
- [ ] Can separate concerns in Django projects
- [ ] Know when to refactor from simple to complex

---

# Phase 23 — Real-World Projects

> **Prerequisite:** Phases 0-22.
> **Goal:** Build progressively complex projects for your portfolio.

## Project 1 — Blog Platform

### Features
- User registration and authentication
- CRUD operations for posts
- PostgreSQL database
- Django admin
- Comments on posts
- Tags and categories
- Image upload
- Basic pagination

### Tech Stack
- Django
- PostgreSQL
- Django ORM
- Django Forms
- Django Admin

### README Template

```markdown
# Blog Platform

A full-featured blog platform built with Django.

## Features
- User registration and authentication
- Create, read, update, delete posts
- Comments and replies
- Tags and categories
- Image uploads
- Pagination

## Architecture
![Architecture](docs/architecture.png)

## ER Diagram
![ER Diagram](docs/er-diagram.png)

## Setup
1. Clone the repository
2. Create virtual environment: `python -m venv .venv`
3. Activate: `source .venv/bin/activate`
4. Install dependencies: `pip install -r requirements.txt`
5. Set up database: `python manage.py migrate`
6. Create superuser: `python manage.py createsuperuser`
7. Run server: `python manage.py runserver`

## API Endpoints
| Method | Endpoint | Description |
|---|---|---|
| GET | /api/posts/ | List posts |
| POST | /api/posts/ | Create post |
| GET | /api/posts/{id}/ | Get post |
| PUT | /api/posts/{id}/ | Update post |
| DELETE | /api/posts/{id}/ | Delete post |

## Tests
Run tests: `pytest`

## License
MIT
```

---

## Project 2 — Task Management API

### Features
- JWT authentication
- Role-based permissions
- Task CRUD with filtering and pagination
- Team management
- Due dates and priority levels
- Task assignment
- Activity log
- Comprehensive test suite

### Tech Stack
- Django + DRF
- PostgreSQL
- JWT (SimpleJWT)
- pytest + pytest-django
- Docker

---

## Project 3 — E-Commerce Backend

### Features
- User management with roles (buyer/seller/admin)
- Product catalog with categories
- Shopping cart
- Order management
- Payment integration concepts
- Inventory tracking
- Redis caching
- Celery background tasks
- Comprehensive API documentation (Swagger)
- Docker Compose setup

### Tech Stack
- Django + DRF
- PostgreSQL
- Redis
- Celery
- Docker Compose
- drf-spectacular (OpenAPI)

---

## Project 4 — Production SaaS Backend

### Features
- Multi-tenant architecture
- Organization and team management
- Role-based access control
- Subscription concepts
- REST API with versioning
- Background job processing
- Email notifications
- Caching layer
- Rate limiting
- Comprehensive logging
- CI/CD pipeline
- Docker deployment
- Health checks
- Monitoring

### Tech Stack
- Django + DRF
- PostgreSQL
- Redis
- Celery
- Docker
- GitHub Actions
- Nginx + Gunicorn

---

## Final Capstone — Build Something Serious

### Product Requirements
Choose one:
1. **Social Media API** — Posts, comments, likes, followers, feed
2. **Learning Management System** — Courses, lessons, quizzes, progress tracking
3. **Marketplace Backend** — Listings, search, messaging, payments
4. **Project Management Tool** — Projects, tasks, boards, team collaboration

### Requirements Document Template

```markdown
# [Project Name] — Requirements

## Functional Requirements
- [ ] User registration and authentication
- [ ] [Feature 1]
- [ ] [Feature 2]

## Non-Functional Requirements
- Response time < 200ms for all endpoints
- 99.9% uptime
- Support 1000 concurrent users
- GDPR compliant

## User Stories
- As a user, I can register with email
- As a user, I can create a post
- As an admin, I can manage users

## Database Requirements
- PostgreSQL with proper indexing
- Data retention policies
- Backup strategy

## API Requirements
- RESTful design
- JWT authentication
- Rate limiting
- Pagination
- Filtering and search
- Versioning

## Security Requirements
- HTTPS everywhere
- Input validation
- SQL injection prevention
- XSS prevention
- CSRF protection
- Rate limiting

## Performance Requirements
- Database queries < 100ms
- API response < 200ms
- Support 100 req/s per endpoint

## Deployment Requirements
- Docker containerization
- CI/CD pipeline
- Health checks
- Logging
- Monitoring
```

---

# Phase 24 — Interview Preparation

> **Prerequisite:** All previous phases.
> **Goal:** Ace Django and backend engineering interviews.

## 24.1 Django Interview Questions

### Beginner

| Question | Key Points |
|---|---|
| What is Django? | High-level Python web framework, MVT, batteries-included |
| What is MVT? | Model-View-Template (similar to MVC) |
| What is the Django ORM? | Object-Relational Mapper, Python objects ↔ database tables |
| What are migrations? | Schema version control, auto-generated from model changes |
| What is the admin? | Auto-generated UI for managing data |
| What is middleware? | Request/response processing pipeline |

### Intermediate

| Question | Key Points |
|---|---|
| How does Django ORM work? | QuerySets are lazy, translated to SQL, executed on evaluation |
| What is `select_related`? | SQL JOIN for ForeignKey/OneToOne, prevents N+1 |
| What is `prefetch_related`? | Separate query for ManyToMany/reverse FK |
| What is CSRF? | Cross-Site Request Forgery, prevented by tokens |
| What is the difference between authentication and authorization? | WHO you are vs WHAT you can do |
| How does Django authentication work? | Sessions, password hashing (PBKDF2), middleware |
| How does DRF serialization work? | Converts model ↔ JSON, validates data |
| APIView vs ViewSet? | Manual method handling vs automatic CRUD + custom actions |

### Advanced

| Question | Key Points |
|---|---|
| How would you optimize a slow Django API? | Profiling, N+1, indexes, caching, pagination |
| How would you scale Django? | Load balancing, caching, database optimization, async |
| JWT vs sessions? | JWT: stateless, mobile-friendly. Sessions: simpler, server-controlled |
| Explain Django middleware lifecycle | Request flows down, response flows up |
| When would you use async Django? | I/O-bound views, WebSockets, external API calls |
| How do you handle database migrations in production? | Zero-downtime, backward-compatible migrations |

## 24.2 PostgreSQL Interview Questions

| Question | Key Points |
|---|---|
| What are indexes? | Data structures for fast lookups |
| When would you NOT use an index? | Small tables, high write-heavy tables |
| What is a CTE? | Common Table Expression, named temporary result set |
| What is the difference between WHERE and HAVING? | WHERE filters rows, HAVING filters groups |
| Explain ACID | Atomicity, Consistency, Isolation, Durability |
| What are isolation levels? | READ COMMITTED, REPEATABLE READ, SERIALIZABLE |
| How do you find slow queries? | pg_stat_statements, EXPLAIN ANALYZE |

## 24.3 System Design Interview Framework

```text
1. Clarify requirements (5 min)
   - Functional requirements
   - Non-functional requirements
   - Scale expectations

2. High-level design (10 min)
   - Main components
   - Data flow
   - API design

3. Database design (10 min)
   - Schema
   - Indexes
   - Scaling strategy

4. Detailed design (10 min)
   - Deep dive on key components
   - Caching strategy
   - Message queues

5. Wrap up (5 min)
   - Trade-offs
   - Bottlenecks
   - Monitoring
```

## 24.4 Behavioral Interview Questions

```text
STAR Method:
  Situation → Task → Action → Result

Common questions:
- Tell me about a time you debugging a production issue
- Describe a time you had to make a technical decision
- How do you handle disagreements in code reviews?
- Tell me about a project you're most proud of
- How do you prioritize when everything is urgent?
```

## 24.5 Coding Interview Preparation

### Data Structures

```python
# Arrays/Lists
# Time: Access O(1), Search O(n), Insert O(n)

# Hash Maps/Dictionaries
# Time: Access O(1), Search O(1), Insert O(1)

# Stacks
# LIFO - push, pop, peek

# Queues
# FIFO - enqueue, dequeue

# Linked Lists
# Node → Node → Node

# Trees
# Binary Search Tree: left < root < right

# Graphs
# Adjacency list or matrix
```

### Common Patterns

```text
1. Two Pointers
2. Sliding Window
3. Fast & Slow Pointers
4. Merge Intervals
5. Cyclic Sort
6. In-place Reversal
7. Tree BFS/DFS
8. Two Heaps
9. Top K Elements
10. K-way Merge
11. Topological Sort
12. Binary Search
13. Dynamic Programming
14. Greedy
15. Backtracking
```

### Practice Platforms

- LeetCode (algorithms)
- HackerRank (Python)
- Exercism (Python track)
- CodeWars (Python katas)

## 24.6 Backend Coding Challenges

### 1. Rate Limiter

```python
class RateLimiter:
    """Token bucket rate limiter."""

    def __init__(self, max_tokens: int, refill_rate: float):
        self.max_tokens = max_tokens
        self.refill_rate = refill_rate
        self.tokens = max_tokens
        self.last_refill = time.time()

    def allow(self) -> bool:
        self._refill()
        if self.tokens >= 1:
            self.tokens -= 1
            return True
        return False

    def _refill(self):
        now = time.time()
        elapsed = now - self.last_refill
        self.tokens = min(
            self.max_tokens,
            self.tokens + elapsed * self.refill_rate
        )
        self.last_refill = now
```

### 2. Pagination

```python
class CursorPaginator:
    """Cursor-based pagination."""

    def __init__(self, queryset, page_size: int = 20):
        self.queryset = queryset
        self.page_size = page_size

    def get_page(self, cursor: int | None = None):
        if cursor is not None:
            items = self.queryset.filter(id__lt=cursor)[:self.page_size]
        else:
            items = self.queryset[:self.page_size]

        items = list(items)
        has_next = len(items) == self.page_size
        next_cursor = items[-1].id if has_next and items else None

        return {
            "items": items,
            "next_cursor": next_cursor,
            "has_next": has_next,
        }
```

### 3. Caching Layer

```python
class CacheAside:
    """Cache-aside implementation."""

    def __init__(self, cache, db_fetch_fn):
        self.cache = cache
        self.db_fetch = db_fetch_fn

    def get(self, key: str, ttl: int = 300):
        # Check cache
        value = self.cache.get(key)
        if value is not None:
            return value

        # Cache miss — fetch from DB
        value = self.db_fetch(key)
        if value is not None:
            self.cache.set(key, value, timeout=ttl)

        return value

    def invalidate(self, key: str):
        self.cache.delete(key)
```

## ✅ Phase 24 Checkpoint

- [ ] Can answer Django interview questions confidently
- [ ] Can answer PostgreSQL interview questions
- [ ] Can design a system given requirements
- [ ] Can solve coding problems using common patterns
- [ ] Can present projects using STAR method

---

# Phase 25 — Portfolio and Job Search

> **Prerequisite:** Completed Projects 1-4 and Capstone.
> **Goal:** Present your work professionally and land a job.

## 25.1 GitHub Portfolio

### Repository Structure

```text
project-name/
├── README.md              # Clear description, setup, screenshots
├── docs/
│   ├── architecture.md    # Architecture decisions
│   ├── api.md            # API documentation
│   └── deployment.md     # Deployment guide
├── docker-compose.yml
├── Dockerfile
├── .github/workflows/    # CI/CD
├── requirements/
├── apps/
├── tests/
└── scripts/
```

### README Template

```markdown
# Project Name

> One-line description of what it does.

## 🎯 Problem It Solves

Brief description of the problem.

## 🏗️ Architecture

![Architecture](docs/architecture.png)

**Tech Stack:** Django, DRF, PostgreSQL, Redis, Celery, Docker

## 🚀 Features

- Feature 1
- Feature 2
- Feature 3

## 📊 API Documentation

Interactive docs at `/api/docs/`

| Endpoint | Method | Description |
|---|---|---|
| `/api/v1/users/` | GET | List users |
| ... | ... | ... |

## 🛠️ Setup

### Prerequisites
- Python 3.12+
- Docker & Docker Compose
- PostgreSQL 16+

### Installation
1. Clone: `git clone ...`
2. Install: `docker compose up -d`
3. Migrate: `docker compose exec web python manage.py migrate`
4. Seed: `docker compose exec web python manage.py seed_data`

### Running Tests
`docker compose exec web pytest`

## 📈 Performance

- API response time: < 200ms (p95)
- 1000 concurrent users supported
- Database queries: < 50ms average

## 🔒 Security

- JWT authentication
- Rate limiting
- Input validation
- CORS configuration
- Security headers

## 🐳 Deployment

See [deployment.md](docs/deployment.md)

## 📝 Decisions

See [architecture.md](docs/architecture.md) for technical decisions.

## 📄 License

MIT
```

## 25.2 LinkedIn Profile

### Headline

```text
Python Backend Engineer | Django | PostgreSQL | Building Scalable APIs
```

### About Section

```text
Backend engineer with [X] years of experience building production APIs
with Django, PostgreSQL, and Redis.

Built and deployed [X] applications serving [X] users.

Core skills: Python, Django, DRF, PostgreSQL, Redis, Celery, Docker, CI/CD

Currently learning: System design, distributed systems, performance engineering
```

### Projects Section

```text
Project Name
Brief description. Tech stack. Key features. Results/impact.
GitHub: [link]
Live: [link]
```

## 25.3 Resume Tips

```text
Technical Skills Section:
  Languages: Python, SQL, Bash
  Frameworks: Django, DRF
  Databases: PostgreSQL, Redis
  Tools: Git, Docker, CI/CD, Linux
  Concepts: REST APIs, Authentication, Testing, Caching

Project Section (for each project):
  - What it does (1 line)
  - Your role and contributions
  - Tech stack
  - Key metrics (performance, users, etc.)
  - Link to GitHub/deployment
```

## 25.4 Job Search Strategy

```text
1. Apply to 10-15 jobs per day
2. Customize resume for each role
3. Write a brief cover letter explaining fit
4. Follow up after 1 week
5. Network on LinkedIn and Twitter
6. Attend local meetups
7. Contribute to open source
8. Share your projects on social media
```

## 25.5 Interview Strategy

```text
Before the interview:
  - Research the company
  - Study their tech stack
  - Review your projects

During the interview:
  - Think out loud
  - Ask clarifying questions
  - Start with the simplest solution
  - Discuss trade-offs

After the interview:
  - Send thank you email
  - Reflect on what went well/poorly
  - Practice weak areas
```

---

# Job-Readiness Checklist

## Technical Skills

- [ ] Can build a Django application from scratch
- [ ] Can design a PostgreSQL schema
- [ ] Can write complex SQL queries
- [ ] Can optimize Django ORM queries
- [ ] Can build REST APIs with DRF
- [ ] Can implement JWT authentication
- [ ] Can implement RBAC
- [ ] Can write unit, integration, and API tests
- [ ] Can Dockerize an application
- [ ] Can configure PostgreSQL for production
- [ ] Can use Redis for caching and sessions
- [ ] Can use Celery for background tasks
- [ ] Can deploy Django to production
- [ ] Can configure Nginx and Gunicorn
- [ ] Can set up CI/CD with GitHub Actions
- [ ] Can debug production problems
- [ ] Can profile and optimize performance
- [ ] Can design scalable APIs
- [ ] Can explain architecture decisions

## Soft Skills

- [ ] Can explain technical concepts clearly
- [ ] Can participate in code reviews
- [ ] Can read an unfamiliar codebase
- [ ] Can write clear documentation
- [ ] Can estimate task complexity
- [ ] Can collaborate effectively in a team

## Professional Skills

- [ ] Can use Git professionally (branching, rebasing, PRs)
- [ ] Can write clean, maintainable code
- [ ] Can follow SOLID principles
- [ ] Can design and document APIs
- [ ] Can write technical documentation
- [ ] Can explain system design trade-offs

---

# Learning Schedules

## Fast Track (3 Months)

```text
Hours per day: 6-8

Week 1-2:   Phase 0-1 (Environment + Python)
Week 3-4:   Phase 2-3 (Engineering + Git)
Week 5-6:   Phase 4-5 (Web + Django)
Week 7-8:   Phase 6-7 (ORM + PostgreSQL)
Week 9-10:  Phase 8-9 (Auth + DRF)
Week 11:    Phase 10-11 (Security + Redis)
Week 12:    Project 1 + Portfolio

Note: This is extremely aggressive. Only recommended for
those with strong prior programming experience.
```

## Balanced (6 Months)

```text
Hours per day: 4-6

Month 1:  Phase 0-2 (Environment, Python, Engineering)
Month 2:  Phase 3-5 (Git, Web, Django)
Month 3:  Phase 6-7 (ORM, PostgreSQL)
Month 4:  Phase 8-9 (Auth, DRF)
Month 5:  Phase 10-14 (Security, Redis, Celery, Testing, Docker)
Month 6:  Phase 15-17 (Linux, Production, CI/CD) + Project 1-2

Includes revision and project time.
```

## Deep Mastery (9-12 Months)

```text
Hours per day: 3-5

Month 1-2:   Phase 0-3 (Foundation)
Month 3:     Phase 4-5 (Web + Django)
Month 4-5:   Phase 6-7 (ORM + PostgreSQL)
Month 6:     Phase 8-9 (Auth + DRF)
Month 7:     Phase 10-12 (Security + Redis + Celery)
Month 8:     Phase 13-14 (Testing + Docker)
Month 9:     Phase 15-17 (Linux + Production + CI/CD)
Month 10:    Phase 18-19 (Observability + Performance)
Month 11:    Phase 20-22 (System Design + Patterns + Architecture)
Month 12:    Phase 23-25 (Projects + Interview Prep + Portfolio)

Includes comprehensive revision and mock interviews.
```

---

# Recommended Resources

## Python
- **Primary:** [Python Official Tutorial](https://docs.python.org/3/tutorial/)
- **Secondary:** [Automate the Boring Stuff](https://automatetheboringstuff.com/)
- **Practice:** [Exercism Python Track](https://exercism.org/tracks/python)

## Django
- **Primary:** [Django Official Tutorial](https://docs.djangoproject.com/en/stable/intro/tutorial01/)
- **Secondary:** [Django for Professionals](https://djangoforprofessionals.com/)
- **Practice:** Build the 4 projects in this guide

## PostgreSQL
- **Primary:** [PostgreSQL Official Docs](https://www.postgresql.org/docs/)
- **Secondary:** [PostgreSQL Tutorial](https://www.postgresqltutorial.com/)
- **Practice:** [SQLBolt](https://sqlbolt.com/)

## REST API Design
- **Primary:** [RESTful Web APIs](https://www.oreilly.com/library/view/restful-web-apis/9781449359713/)
- **Secondary:** [Microsoft REST API Guidelines](https://github.com/microsoft/api-guidelines)
- **Practice:** Design APIs for the projects

## Testing
- **Primary:** [pytest Documentation](https://docs.pytest.org/)
- **Secondary:** [Testing with pytest](https://www.oreilly.com/library/view/testing-python/9781491958346/)
- **Practice:** Write tests for every project

## Docker
- **Primary:** [Docker Official Getting Started](https://docs.docker.com/get-started/)
- **Secondary:** [Docker Deep Dive](https://www.amazon.com/Docker-Deep-Dive-Nigel-Poulton/dp/1521822808)
- **Practice:** Dockerize all projects

## System Design
- **Primary:** [System Design Interview](https://www.amazon.com/System-Design-Interview-Insiders-Guide/dp/1736049127)
- **Secondary:** [Designing Data-Intensive Applications](https://dataintensive.net/)
- **Practice:** Practice design problems weekly

## Git
- **Primary:** [Pro Git Book](https://git-scm.com/book/en/v2)
- **Secondary:** [Oh Shit, Git](https://ohshitgit.com/)
- **Practice:** Use Git daily in every project

---

# Milestone Exams

> Complete these practical exams before advancing. Each milestone requires hands-on implementation, not just reading.

## Milestone 1 — Python Fundamentals

### Practical Exam
```text
Build a CLI tool that:
1. Reads a CSV file of student grades
2. Calculates averages, min/max, and letter grades
3. Outputs a formatted report
4. Includes type hints throughout
5. Has error handling for invalid files
6. Uses context managers for file operations
7. Includes logging for debugging

Time limit: 2 hours
```

### Evaluation Criteria
```text
✅ Uses generators for large file processing
✅ Proper type hints on all functions
✅ Custom exception handling
✅ Context manager for file I/O
✅ Unit tests for grade calculation logic
✅ Clear, descriptive variable names
✅ Logging at appropriate levels
```

### Verification
```bash
# Must pass these checks
ruff check .
ruff format --check .
mypy cli_tool.py
pytest test_grade_calculator.py -v
```

---

## Milestone 2 — Django Fundamentals

### Practical Exam
```text
Build a Blog application:
1. User model with email authentication
2. Post model with author, title, content, published status
3. Comment model with post and author
4. Admin interface with filters and search
5. CRUD views for posts (FBV or CBV)
6. User registration and login
7. Template inheritance with base template
8. Static files and media uploads

Time limit: 4 hours
```

### Evaluation Criteria
```text
✅ Custom User model (not default)
✅ Proper model relationships (ForeignKey, related_name)
✅ get_object_or_404 for detail views
✅ Form validation
✅ {% csrf_token %} in all forms
✅ {% url %} tag instead of hardcoded URLs
✅ Django admin with list_display, list_filter, search_fields
✅ Pagination on post list
```

### Verification
```bash
python manage.py test
python manage.py makemigrations --check
python manage.py check --deploy
```

---

## Milestone 3 — PostgreSQL + ORM

### Practical Exam
```text
Given a database with users, posts, comments, and likes:
1. Write 10 SQL queries including:
   - Complex JOINs
   - Subqueries
   - CTEs
   - Window functions
   - GROUP BY with HAVING
2. Convert 5 of these to Django ORM
3. Optimize 3 slow queries using:
   - select_related / prefetch_related
   - Indexes
   - Only / defer
4. Write EXPLAIN ANALYZE for 2 queries

Time limit: 3 hours
```

### Evaluation Criteria
```text
✅ All 10 SQL queries execute correctly
✅ Django ORM translations produce same results
✅ N+1 problems identified and fixed
✅ Appropriate indexes identified
✅ EXPLAIN ANALYZE interpreted correctly
✅ Understanding of when to use ORM vs raw SQL
```

---

## Milestone 4 — REST APIs

### Practical Exam
```text
Build a Task Management API:
1. JWT authentication (login, register, refresh)
2. CRUD endpoints for tasks
3. Filtering by status, priority, assignee
4. Pagination (cursor-based)
5. Custom permissions (only task owner can edit)
6. OpenAPI documentation
7. Rate limiting
8. Proper error responses

Time limit: 5 hours
```

### Evaluation Criteria
```text
✅ JWT token flow works end-to-end
✅ Serializers handle nested relationships
✅ ViewSet with custom actions
✅ Permission classes correctly restrict access
✅ API documentation accessible at /api/docs/
✅ Rate limiting configured and tested
✅ Consistent error response format
✅ Pagination returns proper metadata
```

### API Contract
```text
POST   /api/v1/auth/register/     → {"email", "username", "password"}
POST   /api/v1/auth/login/        → {"access", "refresh"}
POST   /api/v1/auth/refresh/      → {"access"}
GET    /api/v1/tasks/             → paginated list
POST   /api/v1/tasks/             → create task
GET    /api/v1/tasks/{id}/        → get task
PUT    /api/v1/tasks/{id}/        → update task
DELETE /api/v1/tasks/{id}/        → delete task
GET    /api/v1/tasks/{id}/assign/ → assign user
```

---

## Milestone 5 — Authentication + Security

### Practical Exam
```text
Implement a complete auth system:
1. User registration with email verification
2. Login with JWT
3. Password reset flow
4. Role-based permissions (admin, editor, viewer)
5. Object-level permissions
6. CORS configuration
7. Security headers
8. Rate limiting on auth endpoints

Time limit: 4 hours
```

### Evaluation Criteria
```text
✅ Password hashing (PBKDF2 via Django)
✅ Email verification token flow
✅ JWT access + refresh token rotation
✅ Roles assigned correctly
✅ Object-level permissions prevent unauthorized access
✅ CORS headers present in responses
✅ Rate limiting returns 429 when exceeded
✅ No secrets in codebase (environment variables only)
```

---

## Milestone 6 — Testing

### Practical Exam
```text
Write comprehensive tests for existing API:
1. Unit tests for all model methods
2. Unit tests for all serializer validation
3. API tests for all endpoints (happy path)
4. API tests for error cases (400, 401, 403, 404)
5. Permission tests (unauthorized, wrong role)
6. Mock external service calls
7. Achieve >80% code coverage

Time limit: 3 hours
```

### Evaluation Criteria
```text
✅ pytest and pytest-django configured
✅ Fixtures for common test data
✅ Tests are isolated (no shared state)
✅ Edge cases covered (empty inputs, permissions)
✅ External services mocked
✅ Coverage report shows >80%
✅ Tests run in <30 seconds
```

### Verification
```bash
pytest --cov=. --cov-report=term-missing -v
# Must show >80% coverage
```

---

## Milestone 7 — Docker + DevOps

### Practical Exam
```text
Dockerize a Django application:
1. Multi-stage Dockerfile
2. docker-compose.yml with:
   - Django app
   - PostgreSQL
   - Redis
   - Celery worker
   - Celery beat
3. .dockerignore
4. Health check endpoint
5. Production-ready Gunicorn config
6. GitHub Actions CI pipeline

Time limit: 3 hours
```

### Evaluation Criteria
```text
✅ Docker build succeeds
✅ All services start with docker compose up
✅ Database migrations run automatically
✅ Static files collected
✅ Celery worker connects to broker
✅ CI pipeline runs lint and tests
✅ No secrets in Dockerfile
✅ Non-root user in container
```

### Verification
```bash
docker compose build
docker compose up -d
docker compose ps  # All services healthy
docker compose exec web python manage.py test
docker compose down
```

---

## Milestone 8 — Production Deployment

### Practical Exam
```text
Deploy Django to production:
1. Server setup with Ubuntu
2. Nginx reverse proxy with SSL
3. Gunicorn with systemd service
4. PostgreSQL with proper configuration
5. Redis for caching and sessions
6. Static file serving via Nginx
7. Logging configuration
8. Security hardening

Time limit: 4 hours
```

### Evaluation Criteria
```text
✅ HTTPS enabled with valid certificate
✅ Nginx serves static files efficiently
✅ Gunicorn configured with appropriate workers
✅ Systemd service auto-restarts on failure
✅ Security headers present
✅ DEBUG=False in production
✅ Logs written to files
✅ Database backups configured
```

---

## Milestone 9 — System Design

### Practical Exam
```text
Design a URL shortener service:
1. Requirements gathering (ask clarifying questions)
2. High-level architecture diagram
3. Database schema design
4. API design
5. Scaling strategy
6. Caching strategy
7. Failure scenarios and handling
8. Trade-offs discussion

Time limit: 1 hour (oral presentation)
```

### Evaluation Criteria
```text
✅ Asked clarifying questions about scale
✅ Clear architecture diagram
✅ Database schema with proper indexing
✅ RESTful API design
✅ Scaling from 1K to 1M users considered
✅ Caching strategy explained
✅ Trade-offs articulated
✅ Failure modes identified
```

---

## Final Capstone Exam

### Practical Exam
```text
Build a production-ready application:
1. Choose one:
   - Social media API
   - E-commerce backend
   - Job portal
   - Learning management system
2. Must include:
   - Authentication + authorization
   - CRUD operations
   - Pagination + filtering
   - Background tasks (Celery)
   - Caching (Redis)
   - Docker setup
   - CI/CD pipeline
   - Test suite (>80% coverage)
   - OpenAPI documentation
   - Deployment to production

Time limit: 2 weeks
```

### Evaluation Criteria
```text
✅ Code quality (SOLID, DRY, KISS)
✅ Test coverage >80%
✅ Docker builds and runs
✅ CI pipeline passes
✅ API documented with OpenAPI
✅ No N+1 queries
✅ Proper error handling
✅ Logging configured
✅ Security considerations addressed
✅ README with setup instructions
✅ Deployed and accessible
```

---

# Final Notes

## How to Think Like a Software Engineer

```text
1. Start with the problem, not the solution
2. Consider trade-offs before making decisions
3. Write code for humans first, computers second
4. Test your assumptions with data
5. Monitor production systems
6. Learn from failures
7. Share knowledge with your team
8. Keep learning — technology evolves constantly
```

## The Journey

```text
You started:  Python Developer
            ↓
You learned:  Django Basics
            ↓
You built:    REST APIs with DRF
            ↓
You mastered: Database design and optimization
            ↓
You deployed: Production systems
            ↓
You designed: Scalable architectures
            ↓
You are now:  Job-Ready Software Engineer
```

## Final Advice

1. **Build projects.** Reading is not enough. Build the 4 projects and the capstone.
2. **Write tests.** Tests catch bugs and give you confidence.
3. **Read code.** Read open-source Django projects to learn patterns.
4. **Debug patiently.** Every bug is a learning opportunity.
5. **Ask questions.** No one knows everything. Seek help when stuck.
6. **Stay curious.** The best engineers are lifelong learners.
7. **Ship it.** Perfect is the enemy of good. Deploy and iterate.

---

# Appendix A — Computer Science Fundamentals

> **Prerequisite:** Basic programming.
> **Goal:** Understand the CS knowledge every backend engineer needs.

## A.1 Big-O Notation

### Concept

Big-O describes how an algorithm's time or space grows as input grows.

### Common Complexities

| Big-O | Name | Example | 10 items | 100 items |
|---|---|---|---|---|
| O(1) | Constant | Array index access | 1 | 1 |
| O(log n) | Logarithmic | Binary search | 3 | 7 |
| O(n) | Linear | Loop through array | 10 | 100 |
| O(n log n) | Linearithmic | Merge sort | 33 | 664 |
| O(n²) | Quadratic | Nested loops | 100 | 10,000 |
| O(2ⁿ) | Exponential | Recursive Fibonacci | 1,024 | Huge |

### Mental Model

```text
O(1)        █
O(log n)    ███
O(n)        ██████████
O(n log n)  ████████████████
O(n²)       ██████████████████████████████████████████████
```

### When It Matters

```text
- Database queries: O(n) vs O(log n) with index
- Nested loops: O(n²) often becomes bottleneck
- Caching: O(1) lookup vs O(n) query
- Pagination: O(page_size) vs O(total)
```

## A.2 Data Structures

### Arrays/Lists

```python
# Access: O(1)  Search: O(n)  Insert: O(n)
arr = [1, 2, 3, 4, 5]
arr[0]      # O(1) - direct access
arr.append(6)  # O(1) amortized
arr.insert(0, 0)  # O(n) - shift elements
```

### Hash Maps/Dicts

```python
# Access: O(1)  Search: O(1)  Insert: O(1)
d = {"alice": 1, "bob": 2}
d["alice"]   # O(1)
"alice" in d  # O(1)
d["charlie"] = 3  # O(1)

# Use cases: counting, lookup tables, grouping
```

### Stacks (LIFO)

```python
stack = []
stack.append(1)    # push - O(1)
stack.append(2)
stack.pop()        # pop - O(1) returns 2
stack[-1]          # peek - O(1)

# Use cases: undo, function calls, parentheses validation
```

### Queues (FIFO)

```python
from collections import deque

queue = deque()
queue.append(1)      # enqueue - O(1)
queue.append(2)
queue.popleft()      # dequeue - O(1) returns 1

# Use cases: BFS, task scheduling, print queues
```

### Linked Lists

```python
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

# Access: O(n)  Search: O(n)  Insert at head: O(1)
# Use cases: when you need frequent insertions/deletions
```

### Trees (Binary Search Tree)

```python
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# BST Property: left < root < right
# Access/Search: O(log n) average, O(n) worst
# Use cases: sorted data, hierarchical data
```

### Heaps (Priority Queue)

```python
import heapq

heap = []
heapq.heappush(heap, 3)  # O(log n)
heapq.heappush(heap, 1)
heapq.heappush(heap, 2)
smallest = heapq.heappop(heap)  # O(log n) returns 1

# Use cases: top-K problems, task scheduling by priority
```

## A.3 Algorithms

### Binary Search

```python
def binary_search(arr: list[int], target: int) -> int:
    """O(log n) search in sorted array."""
    left, right = 0, len(arr) - 1

    while left <= right:
        mid = (left + right) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1

    return -1
```

### Sorting

```python
# Quick Sort: O(n log n) average, O(n²) worst
def quicksort(arr: list[int]) -> list[int]:
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quicksort(left) + middle + quicksort(right)
```

### Graph Algorithms

```python
# BFS - Shortest path in unweighted graph
def bfs(graph: dict, start: str) -> list[str]:
    from collections import deque
    visited = set([start])
    queue = deque([start])
    order = []

    while queue:
        node = queue.popleft()
        order.append(node)
        for neighbor in graph[node]:
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)

    return order
```

## A.4 Operating Systems Fundamentals

### Processes vs Threads

```text
Process:
  - Independent execution unit
  - Own memory space
  - Heavyweight (expensive to create)
  - Inter-process communication (IPC) needed

Thread:
  - Unit of execution within a process
  - Shares memory with other threads
  - Lightweight (cheap to create)
  - Shared memory communication
```

### Concurrency vs Parallelism

```text
Concurrency:  Dealing with multiple things at once
              (one CPU, switching between tasks)

Parallelism:  Doing multiple things at once
              (multiple CPUs, true simultaneous execution)

Django context:
  - WSGI: One request at a time per worker process
  - ASGI: Can handle concurrent connections
  - Celery: Multiple worker processes for parallelism
```

### Memory Management

```text
Stack:
  - Local variables, function calls
  - Fast access, limited size
  - Automatic cleanup

Heap:
  - Dynamic allocation (objects, lists)
  - Slower access, large size
  - Must be managed (garbage collected in Python)

Python's GIL:
  - Global Interpreter Lock
  - Only one thread executes Python at a time
  - Doesn't affect I/O-bound code (thread releases GIL during I/O)
  - Use multiprocessing for CPU-bound code
```

## A.5 Networking Fundamentals

### TCP/IP Model

```text
Application Layer   → HTTP, HTTPS, DNS, SMTP
Transport Layer     → TCP (reliable), UDP (fast)
Internet Layer      → IP (routing, addressing)
Link Layer          → Ethernet, WiFi
```

### TCP vs UDP

```text
TCP:
  - Connection-oriented (3-way handshake)
  - Reliable delivery (retransmission)
  - Ordered delivery
  - Flow control
  - Use: HTTP, databases, email

UDP:
  - Connectionless
  - No delivery guarantee
  - No ordering
  - Fast, low overhead
  - Use: DNS, video streaming, gaming
```

### HTTP/2 and HTTP/3

```text
HTTP/1.1:
  - One request per connection (pipelining limited)
  - Text-based headers

HTTP/2:
  - Multiplexing (multiple requests per connection)
  - Binary protocol
  - Header compression
  - Server push

HTTP/3:
  - Uses QUIC (UDP-based)
  - Better performance on unreliable networks
```

## A.6 Database Fundamentals

### ACID Properties

```text
Atomicity:    All operations succeed or all fail
Consistency:  Database moves from valid state to valid state
Isolation:    Concurrent transactions don't interfere
Durability:   Committed data survives crashes
```

### Indexing

```text
Without index:  Full table scan O(n)
With B-tree index: Tree traversal O(log n)

When to index:
  - Columns used in WHERE clauses
  - Columns used in JOIN conditions
  - Columns used in ORDER BY

When NOT to index:
  - Small tables
  - Columns with low cardinality (few unique values)
  - Tables with heavy write operations
```

### N+1 Problem

```text
Without optimization:
  Query 1: SELECT * FROM posts;           -- returns N posts
  Query 2: SELECT * FROM users WHERE id=1; -- for post 1
  Query 3: SELECT * FROM users WHERE id=2; -- for post 2
  ... N more queries

With select_related:
  Query 1: SELECT posts.*, users.* FROM posts
           INNER JOIN users ON posts.author_id = users.id;
  -- Single query!
```

## A.7 Distributed Systems Fundamentals

### CAP Theorem

```text
In a distributed system, you can only guarantee 2 of 3:

C - Consistency:  All nodes see same data at same time
A - Availability: Every request gets a response
P - Partition Tolerance: System works despite network failures

Real-world: P is always required (networks fail)
So you choose: CP (consistency) or AP (availability)
```

### Common Patterns

```text
Load Balancing:
  - Round Robin: Distribute requests sequentially
  - Least Connections: Send to server with fewest active connections
  - IP Hash: Route based on client IP

Caching:
  - CDN: Cache static assets at edge locations
  - Application cache: Redis/Memcached
  - Database query cache

Message Queues:
  - Producer → Queue → Consumer
  - Decouples components
  - Handles traffic spikes
  - Enables async processing

Database Replication:
  - Primary-Replica: Write to primary, read from replicas
  - Multi-Primary: Write to any node (conflict resolution needed)
```

---

# Appendix B — Additional Backend Coding Challenges

> Build these to demonstrate practical backend engineering skills.

## B.1 Rate Limiter Implementation

### Requirements
```text
- Implement token bucket algorithm
- Support multiple rate limit tiers
- Thread-safe
- Configurable limits per endpoint
- Return proper HTTP headers (X-RateLimit-Remaining, etc.)
```

### Expected Architecture
```python
class RateLimiter:
    def __init__(self, max_tokens: int, refill_rate: float):
        self.max_tokens = max_tokens
        self.refill_rate = refill_rate
        self.tokens = max_tokens
        self.last_refill = time.time()
        self.lock = threading.Lock()

    def allow(self) -> bool:
        with self.lock:
            self._refill()
            if self.tokens >= 1:
                self.tokens -= 1
                return True
            return False

    def _refill(self):
        now = time.time()
        elapsed = now - self.last_refill
        self.tokens = min(
            self.max_tokens,
            self.tokens + elapsed * self.refill_rate
        )
        self.last_refill = now
```

## B.2 URL Shortener

### Requirements
```text
- Generate short URLs from long URLs
- Custom aliases support
- Expiration support
- Click tracking
- Redirect with 301/302
```

### Expected Architecture
```python
class URLShortener:
    BASE62 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

    def shorten(self, url: str, alias: str = None) -> str:
        if alias:
            if self._alias_exists(alias):
                raise ValueError("Alias already in use")
            short_code = alias
        else:
            short_code = self._generate_code(url)
        self._store_mapping(short_code, url)
        return short_code

    def resolve(self, short_code: str) -> str:
        url = self._get_url(short_code)
        if not url:
            raise NotFoundError("URL", short_code)
        self._record_click(short_code)
        return url

    def _generate_code(self, url: str) -> str:
        hash_bytes = hashlib.md5(url.encode()).digest()
        return self._encode_base62(hash_bytes)[:7]
```

## B.3 Caching Layer

### Requirements
```text
- Cache-aside pattern implementation
- TTL support
- Cache invalidation
- Stampede prevention with locks
- Cache warming
```

### Expected Architecture
```python
class CacheLayer:
    def __init__(self, redis_client, default_ttl: int = 300):
        self.redis = redis_client
        self.default_ttl = default_ttl

    def get_or_set(self, key: str, compute_fn, ttl: int = None):
        # Check cache
        value = self.redis.get(key)
        if value is not None:
            return json.loads(value)

        # Try to acquire lock
        lock = self.redis.lock(f"lock:{key}", timeout=5)
        if lock.acquire(blocking=True):
            try:
                # Double-check
                value = self.redis.get(key)
                if value is not None:
                    return json.loads(value)

                # Compute and cache
                value = compute_fn()
                self.redis.setex(
                    key,
                    ttl or self.default_ttl,
                    json.dumps(value)
                )
                return value
            finally:
                lock.release()
        else:
            # Another process is computing, wait and retry
            time.sleep(0.1)
            return self.get_or_set(key, compute_fn, ttl)

    def invalidate(self, pattern: str):
        keys = self.redis.keys(pattern)
        if keys:
            self.redis.delete(*keys)
```

## B.4 Background Job Processor

### Requirements
```text
- Task queue with Redis backend
- Worker processes
- Retry with exponential backoff
- Task priorities
- Dead letter queue for failed tasks
```

## B.5 Notification Service

### Requirements
```text
- Multi-channel: email, SMS, push
- User preference management
- Rate limiting per user
- Delivery tracking
- Template support
```

## B.6 File Upload Service

### Requirements
```text
- Chunked upload support
- Progress tracking
- File type validation
- Size limits
- Virus scanning hook
- S3/local storage abstraction
```

---

# Appendix C — Debugging Training

> Diagnose these deliberately broken scenarios before seeing solutions.

## C.1 N+1 Query Problem

### Symptom
API endpoint returns 100 posts in 4.5 seconds.

### Exercise
```python
# Find the bug
posts = Post.objects.all()
for post in posts:
    print(f"{post.title} by {post.author.username}")
    for comment in post.comments.all():
        print(f"  - {comment.content}")
```

### Diagnosis Steps
1. Enable Django debug toolbar
2. Check number of queries in SQL panel
3. Identify pattern: 1 + N + N*M queries

### Solution
```python
posts = Post.objects.select_related("author").prefetch_related("comments").all()
```

## C.2 Broken Authentication

### Symptom
Users can't log in. Password check passes but login fails.

### Exercise
```python
def login_view(request):
    if request.method == "POST":
        email = request.POST.get("email")
        password = request.POST.get("password")
        user = authenticate(username=email, password=password)  # Bug here!
        if user:
            login(request, user)
            return redirect("dashboard")
    return render(request, "login.html")
```

### Diagnosis Steps
1. Check if `authenticate` is using correct parameter
2. Check if custom user model uses `email` as `USERNAME_FIELD`
3. Check if `authenticate` expects `username` or `email`

### Solution
```python
# authenticate expects the field name defined in USERNAME_FIELD
user = authenticate(request, email=email, password=password)
# Or if USERNAME_FIELD is 'email':
user = authenticate(request, username=email, password=password)
```

## C.3 Race Condition

### Symptom
Inventory shows negative stock. Two orders both succeeded for last item.

### Exercise
```python
def place_order(request, product_id):
    product = Product.objects.get(id=product_id)
    if product.stock > 0:  # Check
        product.stock -= 1  # Decrease
        product.save()  # Save
        return JsonResponse({"status": "success"})
    return JsonResponse({"status": "out of stock"})
```

### Diagnosis Steps
1. Two requests hit simultaneously
2. Both read stock = 1
3. Both pass the check
4. Both decrement and save
5. Stock becomes -1

### Solution
```python
from django.db import transaction, F

@transaction.atomic
def place_order(request, product_id):
    product = Product.objects.select_for_update().get(id=product_id)
    if product.stock > 0:
        Product.objects.filter(id=product_id).update(stock=F("stock") - 1)
        return JsonResponse({"status": "success"})
    return JsonResponse({"status": "out of stock"})
```

## C.4 Database Deadlock

### Symptom
Application hangs. Timeout errors in logs.

### Diagnosis Steps
1. Check PostgreSQL locks: `SELECT * FROM pg_locks;`
2. Check for circular dependencies in transactions
3. Look for inconsistent lock ordering

### Common Cause
```python
# Thread 1                    # Thread 2
with transaction.atomic():    with transaction.atomic():
    Order.objects.get(id=1)       User.objects.get(id=1)
    User.objects.get(id=1)        Order.objects.get(id=1)
```

### Solution
- Always acquire locks in the same order
- Use `select_for_update()` consistently
- Keep transactions short

## C.5 Memory Leak

### Symptom
Django process memory grows over hours. Eventually OOM killed.

### Diagnosis Steps
1. Monitor memory: `ps aux | grep gunicorn`
2. Use `tracemalloc` to find allocations
3. Check for growing caches or global variables
4. Look for model instances not being garbage collected

### Common Causes
```python
# Global list that grows
all_users = []  # Module-level variable
def process_user(user):
    all_users.append(user)  # Never cleared!

# Solution: Use proper caching with TTL
# or clear after processing
```

## C.6 Slow Database Query

### Symptom
One endpoint takes 30 seconds. Others are fast.

### Diagnosis Steps
1. Enable SQL logging: `LOGGING = {"handlers": {"console": {...}}, "loggers": {"django.db.backends": {"level": "DEBUG"}}}`
2. Find the slow query in logs
3. Run `EXPLAIN ANALYZE` on the query
4. Look for sequential scans, missing indexes

### Solution
```sql
-- Before: Sequential scan on 1M rows
EXPLAIN ANALYZE SELECT * FROM orders WHERE user_id = 123;
-- Seq Scan on orders  (cost=0.00..18384.00 rows=500 width=200)

-- Add index
CREATE INDEX idx_orders_user_id ON orders(user_id);

-- After: Index scan
EXPLAIN ANALYZE SELECT * FROM orders WHERE user_id = 123;
-- Index Scan using idx_orders_user_id  (cost=0.42..8.44 rows=500 width=200)
```

## C.7 CORS Problem

### Symptom
Browser shows CORS error. API works with curl.

### Diagnosis Steps
1. Check browser console for exact error
2. Verify `CORS_ALLOWED_ORIGINS` includes frontend URL
3. Check if `Content-Type` header is allowed
4. Verify preflight OPTIONS request succeeds

### Solution
```python
# settings.py
CORS_ALLOWED_ORIGINS = [
    "http://localhost:3000",
    "https://yourdomain.com",
]
CORS_ALLOW_HEADERS = [
    "accept",
    "authorization",
    "content-type",
    "x-csrftoken",
]
```

---

# Appendix D — Production Incident Training

> Simulated incidents for practicing incident response.

## D.1 API Latency Spike

### Scenario
> API latency increased from 100ms to 4 seconds. No code changes deployed.

### Questions to Ask
1. What time did the spike start?
2. Did anything change? (Deployments, config, traffic)
3. Is it all endpoints or specific ones?
4. Is it consistent or intermittent?
5. What does the database look like? (Connections, slow queries)
6. What does Redis look like? (Memory, connections)
7. What does the application look like? (CPU, memory, workers)

### Investigation Checklist
```text
□ Check application logs for errors
□ Check database slow query log
□ Check pg_stat_statements for new slow queries
□ Check Redis metrics (hit rate, memory, connections)
□ Check Celery worker status
□ Check server CPU/memory/disk
□ Check network latency to database
□ Check for connection pool exhaustion
□ Check for N+1 queries in new code
□ Check for cache stampede
```

### Common Causes
- Missing index after schema change
- Cache invalidation storm
- Database connection pool exhaustion
- Celery workers consuming resources
- Traffic spike (check load balancer logs)

## D.2 Database Connection Exhaustion

### Scenario
> Application returns 500 errors. Logs show "FATAL: too many connections."

### Investigation Steps
```sql
-- Check current connections
SELECT count(*) FROM pg_stat_activity;

-- Check connections by state
SELECT state, count(*) FROM pg_stat_activity GROUP BY state;

-- Check connections by application
SELECT application_name, count(*) FROM pg_stat_activity GROUP BY application_name;

-- Kill idle connections
SELECT pg_terminate_backend(pid) FROM pg_stat_activity
WHERE state = 'idle' AND query_start < now() - interval '10 minutes';
```

### Root Causes
- Connection pool too small
- Connections not being returned to pool
- Long-running queries holding connections
- Too many Celery workers

## D.3 Redis Failure

### Scenario
> Cache hit rate dropped to 0%. API responses slow.

### Investigation Steps
1. Check Redis status: `redis-cli ping`
2. Check Redis memory: `redis-cli info memory`
3. Check Redis connections: `redis-cli info clients`
4. Check for key expiration storm
5. Check application logs for Redis errors

### Recovery
```bash
# If Redis crashed, restart
sudo systemctl restart redis

# Clear corrupted data if needed
redis-cli FLUSHALL

# Application should rebuild cache on next request
```

## D.4 Celery Worker Failure

### Scenario
> Background tasks not processing. Emails not sending.

### Investigation Steps
```bash
# Check worker status
celery -A myproject inspect active

# Check scheduled tasks
celery -A myproject inspect scheduled

# Check failed tasks
celery -A myproject inspect revoked

# Restart workers
sudo systemctl restart celery-worker
```

---

# Appendix E — Expanded Resource Recommendations

## E.1 Python

| Resource | Type | Level |
|---|---|---|
| [Python Official Tutorial](https://docs.python.org/3/tutorial/) | Docs | Beginner |
| [Fluent Python](https://www.oreilly.com/library/view/fluent-python-2nd/9781492056348/) | Book | Intermediate |
| [Python Cookbook](https://www.oreilly.com/library/view/python-cookbook-3rd/9781449357337/) | Book | Intermediate |
| [Effective Python](https://effectivepython.com/) | Book | Intermediate |
| [Exercism Python Track](https://exercism.org/tracks/python) | Practice | All levels |

## E.2 Django

| Resource | Type | Level |
|---|---|---|
| [Django Official Tutorial](https://docs.djangoproject.com/en/stable/intro/tutorial01/) | Docs | Beginner |
| [Django for Professionals](https://djangoforprofessionals.com/) | Book | Intermediate |
| [Django for APIs](https://djangoforapis.com/) | Book | Intermediate |
| [Two Scoops of Django](https://www.feldroy.com/books/two-scoops-of-django-3x) | Book | Intermediate |
| [Django Packages](https://djangopackages.org/) | Directory | All levels |

## E.3 PostgreSQL

| Resource | Type | Level |
|---|---|---|
| [PostgreSQL Official Docs](https://www.postgresql.org/docs/) | Docs | All levels |
| [PostgreSQL Tutorial](https://www.postgresqltutorial.com/) | Tutorial | Beginner |
| [The Art of PostgreSQL](https://www.theartofpostgresql.com/) | Book | Intermediate |
| [SQLBolt](https://sqlbolt.com/) | Practice | Beginner |
| [LeetCode Database Problems](https://leetcode.com/problemset/database/) | Practice | Intermediate |

## E.4 System Design

| Resource | Type | Level |
|---|---|---|
| [System Design Interview](https://www.amazon.com/System-Design-Interview-Insiders-Guide/dp/1736049127) | Book | Intermediate |
| [Designing Data-Intensive Applications](https://dataintensive.net/) | Book | Advanced |
| [Grokking the System Design Interview](https://www.designgurus.io/course/grokking-the-system-design-interview) | Course | Intermediate |
| [ByteByteGo](https://blog.bytebytego.com/) | Blog | Intermediate |
| [System Design Primer](https://github.com/donnemartin/system-design-primer) | GitHub | Intermediate |

## E.5 Testing

| Resource | Type | Level |
|---|---|---|
| [pytest Documentation](https://docs.pytest.org/) | Docs | All levels |
| [Python Testing with pytest](https://www.amazon.com/Python-Testing-pytest-Brian-Okken/dp/1680502840) | Book | Intermediate |
| [Test-Driven Development with Python](https://www.oreilly.com/library/view/test-driven-development-with/9781449365141/) | Book | Intermediate |

## E.6 Docker & DevOps

| Resource | Type | Level |
|---|---|---|
| [Docker Official Getting Started](https://docs.docker.com/get-started/) | Docs | Beginner |
| [Docker Deep Dive](https://www.amazon.com/Docker-Deep-Dive-Nigel-Poulton/dp/1521822808) | Book | Intermediate |
| [The Phoenix Project](https://www.amazon.com/Phoenix-Project-DevOps-Helping-Business/dp/0991534437) | Book | Beginner |
| [Site Reliability Engineering](https://sre.google/sre-book/table-of-contents/) | Book | Advanced |

## E.7 Algorithms & Data Structures

| Resource | Type | Level |
|---|---|---|
| [Introduction to Algorithms (CLRS)](https://mitpress.mit.edu/9780262046305/introduction-to-algorithms/) | Book | Intermediate |
| [Grokking Algorithms](https://www.manning.com/books/grokking-algorithms) | Book | Beginner |
| [LeetCode](https://leetcode.com/) | Practice | All levels |
| [NeetCode](https://neetcode.io/) | Practice | Intermediate |

---

# Appendix F — Coding Interview Preparation

## F.1 Arrays and Strings

### Key Patterns
```text
- Two Pointers: Opposite ends, same direction
- Sliding Window: Subarray/substring problems
- Prefix Sum: Range sum queries
- Sorting: Before two pointers
```

### Practice Problems
```text
Easy:
  - Two Sum
  - Valid Palindrome
  - Merge Sorted Arrays

Medium:
  - 3Sum
  - Container With Most Water
  - Product of Array Except Self

Hard:
  - Trapping Rain Water
  - Minimum Window Substring
```

## F.2 Hash Maps

### Key Patterns
```text
- Counting: Frequency maps
- Grouping: Anagrams, duplicates
- Two Sum pattern: Look for complement
- Caching: Memoization
```

### Practice Problems
```text
Easy:
  - Contains Duplicate
  - Valid Anagram

Medium:
  - Group Anagrams
  - Top K Frequent Elements
  - Longest Consecutive Sequence
```

## F.3 Stacks and Queues

### Key Patterns
```text
- Monotonic Stack: Next greater/smaller element
- Balanced Parentheses: Stack matching
- BFS: Queue for level-order traversal
```

### Practice Problems
```text
Easy:
  - Valid Parentheses
  - Min Stack

Medium:
  - Daily Temperatures
  - Evaluate Reverse Polish Notation
  - Generate Parentheses
```

## F.4 Linked Lists

### Key Patterns
```text
- Fast/Slow Pointers: Cycle detection, middle element
- Dummy Head: Simplify edge cases
- In-place Reversal: Reverse sections
```

### Practice Problems
```text
Easy:
  - Reverse Linked List
  - Merge Two Sorted Lists

Medium:
  - Linked List Cycle II
  - Remove Nth Node From End
  - Reorder List
```

## F.5 Trees

### Key Patterns
```text
- DFS (Recursive): Preorder, Inorder, Postorder
- DFS (Iterative): Stack-based
- BFS: Level-order traversal
- Divide and Conquer: Tree construction
```

### Practice Problems
```text
Easy:
  - Maximum Depth of Binary Tree
  - Same Tree
  - Invert Binary Tree

Medium:
  - Binary Tree Level Order Traversal
  - Validate Binary Search Tree
  - Lowest Common Ancestor
```

## F.6 Graphs

### Key Patterns
```text
- BFS: Shortest path, level order
- DFS: Path finding, cycle detection
- Topological Sort: Task scheduling
- Union Find: Connected components
```

### Practice Problems
```text
Medium:
  - Number of Islands
  - Course Schedule
  - Pacific Atlantic Water Flow

Hard:\  - Word Ladder
  - Alien Dictionary
```

## F.7 Dynamic Programming

### Key Patterns
```text
- Memoization: Top-down recursion with cache
- Tabulation: Bottom-up iteration
- State machine: Buy/sell stock problems
- Knapsack: Weight/value optimization
```

### Practice Problems
```text
Easy:
  - Climbing Stairs
  - Maximum Subarray

Medium:
  - Coin Change
  - Longest Increasing Subsequence
  - Word Break

Hard:
  - Edit Distance
  - Burst Balloons
```

---

# Appendix G — Agile and Scrum Basics

## G.1 Agile Manifesto

```text
Values:
  - Individuals and interactions over processes and tools
  - Working software over comprehensive documentation
  - Customer collaboration over contract negotiation
  - Responding to change over following a plan

Principles:
  - Deliver working software frequently
  - Welcome changing requirements
  - Business people and developers must work together daily
  - Build projects around motivated individuals
  - Face-to-face conversation is most efficient
  - Working software is the primary measure of progress
  - Sustainable development pace
  - Technical excellence and good design
  - Simplicity
  - Self-organizing teams
  - Regular reflection and adjustment
```

## G.2 Scrum Framework

```text
Roles:
  - Product Owner: Decides what to build
  - Scrum Master: Facilitates process, removes blockers
  - Development Team: Builds the product

Ceremonies:
  - Sprint Planning: What to build this sprint
  - Daily Standup: What I did, what I'll do, any blockers
  - Sprint Review: Demo to stakeholders
  - Retrospective: How to improve process

Artifacts:
  - Product Backlog: All features prioritized
  - Sprint Backlog: Features for this sprint
  - Increment: Working software at sprint end
```

## G.3 User Stories

```text
Format:
  As a [role], I want [feature], so that [benefit].

Acceptance Criteria:
  Given [context], when [action], then [result].

Example:
  As a user, I want to reset my password, so that I can regain
  access to my account.

  Given I am on the login page
  When I click "Forgot Password" and enter my email
  Then I receive a reset link within 5 minutes
```

## G.4 Estimation

```text
Story Points (Fibonacci): 1, 2, 3, 5, 8, 13, 21

  1 point:  Simple task, < 1 day
  3 points: Medium complexity, 1-3 days
  5 points: Complex, 3-5 days
  8 points: Very complex, needs breaking down
  13+ points: Epic, must decompose

Velocity: Average story points completed per sprint

Capacity: How many points the team can handle per sprint
```

---

# Appendix H — Mentor Mode Guidelines

## How to Use This Guide as a Mentor

### When You Submit Code

```text
1. I identify the conceptual problem (not just syntax)
2. I ask guiding questions:
   - "What do you think is happening here?"
   - "What would happen if...?"
   - "Can you explain your approach?"
3. I give hints:
   - "Consider the N+1 query pattern"
   - "What does the Django docs say about...?"
4. Let you attempt the fix
5. Review your second attempt
6. Only show complete solution if necessary
```

### When You Misunderstand Something

```text
1. Explain the misconception clearly
2. Provide a mental model
3. Show a counterexample
4. Give a small exercise to reinforce
5. Check understanding before moving on
```

### Code Review Style

```text
Instead of: "This is wrong."
Say: "What do you think will happen when...?"\n
Instead of: "Change X to Y."
Say: "Have you considered using X here? What would that give you?"

Instead of: "This doesn't work."
Say: "Let's trace through this together. What's the expected behavior?"
```

---

# Appendix I — Code Review Best Practices

## I.1 What to Check

```text
Correctness:
  - Does it solve the problem?
  - Are edge cases handled?
  - Are error conditions handled?

Security:
  - Input validation
  - SQL injection prevention
  - Authentication/authorization checks
  - Secret management

Performance:
  - N+1 queries?
  - Missing indexes?
  - Unnecessary loops?
  - Proper caching?

Readability:
  - Clear variable/function names
  - Comments for complex logic
  - Reasonable function length
  - Single responsibility

Testing:
  - Are there tests?
  - Do tests cover edge cases?
  - Are tests readable?
```

## I.2 How to Give Feedback

```text
Priority 1 - Must Fix:
  - Security vulnerabilities
  - Data loss risks
  - Broken functionality

Priority 2 - Should Fix:
  - Performance issues
  - Missing error handling
  - Missing tests

Priority 3 - Consider:
  - Style improvements
  - Naming suggestions
  - Alternative approaches

Format:
  "Consider [suggestion] because [reason]."
  "What happens if [edge case]?"
  "This could be simplified by [approach]."
```

---

# Appendix J — Additional Mermaid Diagrams

## J.1 Django Request Lifecycle

```mermaid
sequenceDiagram
    participant Client
    participant Nginx
    participant Gunicorn
    participant Middleware
    participant View
    participant ORM
    participant Database

    Client->>Nginx: HTTP Request
    Nginx->>Gunicorn: Proxy Request
    Gunicorn->>Middleware: Process Request
    Middleware->>View: Call View Function
    View->>ORM: Query Data
    ORM->>Database: SQL Query
    Database-->>ORM: Result Set
    ORM-->>View: Model Instances
    View-->>Middleware: HTTP Response
    Middleware-->>Gunicorn: Processed Response
    Gunicorn-->>Nginx: HTTP Response
    Nginx-->>Client: HTTP Response
```

## J.2 Microservices Architecture

```mermaid
graph TB
    Client[Client] --> Gateway[API Gateway]
    Gateway --> Auth[Auth Service]
    Gateway --> Users[User Service]
    Gateway --> Orders[Order Service]
    Gateway --> Products[Product Service]

    Auth --> AuthDB[(Auth DB)]
    Users --> UserDB[(User DB)]
    Orders --> OrderDB[(Order DB)]
    Orders --> Queue[Message Queue]
    Queue --> Notifications[Notification Service]
    Products --> ProductDB[(Product DB)]
    Products --> Cache[(Redis Cache)]
```

## J.3 CI/CD Pipeline

```mermaid
graph LR
    Push[Git Push] --> Lint[Lint & Format]
    Lint --> Test[Run Tests]
    Test --> Security[Security Scan]
    Security --> Build[Docker Build]
    Build --> Deploy[Deploy to Staging]
    Deploy --> Manual[Manual Approval]
    Manual --> Prod[Deploy to Production]
```

## J.4 Database Indexing Decision

```mermaid
graph TD
    A[Query Slow?] --> B{Sequential Scan?}
    B -->|Yes| C{Column in WHERE/JOIN?}
    C -->|Yes| D{High Cardinality?}
    D -->|Yes| E[Add B-tree Index]
    D -->|No| F[Consider Partial Index]
    C -->|No| G[Check Query Logic]
    B -->|No| H{Sort/Aggregate?}
    H -->|Yes| I[Add Covering Index]
    H -->|No| J[Check Application Logic]
```

---

# Appendix K — Version Accuracy Notes

> Verified as of August 2026:

| Technology | Version | Notes |
|---|---|---|
| Python | 3.12+ | 3.13 available, 3.12 stable |
| Django | 5.1+ | LTS release, 5.2 in development |
| DRF | 3.15+ | Stable, widely used |
| PostgreSQL | 16+ | Latest stable, 17 available |
| Redis | 7+ | Latest stable |
| Celery | 5.4+ | Latest stable |
| Docker | 27+ | Latest stable |
| pytest | 8+ | Latest stable |
| Ruff | 0.5+ | Latest stable, replaces flake8/black/isort |

### Deprecated Practices (Legacy)

> ⚠️ **LEGACY / YOU MAY ENCOUNTER THIS IN EXISTING PROJECTS:**

```text
- django.contrib.postgres.fields.JSONField → Use django.db.models.JSONField
- Django 2.x url() → Use path() and re_path()
- pytest-django 3.x fixtures → Use modern fixture patterns
- Python 2 syntax → Not supported, always use Python 3
- django-rest-framework 3.11 → Upgrade to 3.15+
```

---

*This guide is your roadmap. Follow it systematically, build the projects, and you will be job-ready.*

**Good luck! 🚀**
