# Next.js & React — Full Learning Guide

> A structured learning path + practical textbook + project roadmap.
> From "I know basic programming" to "I can independently design and build production-oriented full-stack web applications."

---

## How to Use This Guide

🎯 **Goal:** By the end of this guide you will be able to look at a real-world problem, design a web application around it, choose an appropriate architecture, implement it with React + Next.js, connect it to a database, and deploy it — *without following a tutorial line-by-line.*

This is not a documentation dump. It is a course. It works like this:

1. **Follow the phases in order.** Each phase depends on the previous one. Concepts are introduced with their prerequisites stated explicitly.
2. **Do the exercises.** Reading without typing is how tutorial-dependency happens. Every phase has three levels: Concept → Application → Challenge.
3. **Build the projects.** The projects are the real curriculum. The theory sections exist to make the projects possible.
4. **Use the checkpoints.** Each phase ends with a checklist and questions. Do not move forward until you pass them.
5. **Revisit.** Come back to sections when you hit real problems. This guide is a reference too.

**Three questions this guide answers continuously:**

1. **What am I learning?**
2. **Why does it matter?**
3. **Can I actually build something with it?**

### The Core Teaching Philosophy

- **Progressive difficulty.** We never introduce a concept before its prerequisites.
- **WHY before HOW.** Every concept is explained by the problem it solves.
- **First principles.** Rendering, hydration, Server Components, caching — nothing is "just magic."
- **No tutorial dependency.** Exercises give requirements and hints, not complete answers. Full reference solutions live only in clearly separated sections.
- **Modern only.** Modern React (hooks, Server Components) and modern Next.js (App Router). Legacy patterns are explicitly labeled **legacy**.

---

## The Learning Progression

```text
Web Fundamentals
      ↓
JavaScript Fundamentals
      ↓
Modern JavaScript
      ↓
React Fundamentals
      ↓
React State & Architecture
      ↓
React Data & Forms
      ↓
TypeScript with React
      ↓
Next.js Fundamentals
      ↓
Next.js App Router
      ↓
Server/Client Architecture
      ↓
Data Fetching
      ↓
Backend/API Development
      ↓
Database
      ↓
Authentication
      ↓
Application Architecture
      ↓
Testing
      ↓
Performance
      ↓
Deployment
      ↓
Real-World Projects
```

---

## Phase Map

| Phase | Topic | Goal |
|---|---|---|
| 0 | Web Development Mental Model | Understand how the web actually works |
| 1 | JavaScript Required for React | Modern JS: the language React is written in |
| 2 | React Fundamentals | Components, JSX, props, state, events |
| 3 | React Rendering Deep Dive | Virtual DOM, reconciliation, re-renders |
| 4 | Hooks in Depth | useState, useEffect, useRef, useMemo, useCallback, useContext, useReducer |
| 5 | State Management | Local, lifted, shared, Context, reducers, external stores |
| 6 | Forms & Data Fetching | Controlled inputs, validation, async data, loading/error states |
| 7 | TypeScript for React | Types that make React apps safer and self-documenting |
| 8 | Next.js Fundamentals | What Next.js is, why it exists, project structure |
| 9 | App Router | Layouts, pages, routing, navigation, metadata |
| 10 | Server/Client Architecture | Server Components vs Client Components — the critical section |
| 11 | Data Fetching & Caching | fetch, cache, revalidation, streaming, suspense |
| 12 | Full-Stack Next.js | Route Handlers, Server Actions, validation, service layers |
| 13 | Databases | SQL fundamentals + ORM integration |
| 14 | Authentication & Authorization | Sessions, cookies, roles, permissions — enforced server-side |
| 15 | Application Architecture | Folder structure, feature-based vs layer-based, when to scale |
| 16 | UI Engineering | Responsive design, accessibility, design systems, Tailwind |
| 17 | Security | XSS, CSRF, injection, secrets — defensive engineering |
| 18 | Performance | Re-renders, caching, Core Web Vitals, evidence-based optimization |
| 19 | Testing | Unit, component, integration, E2E — what to test and why |
| 20 | Debugging | A systematic methodology for every class of bug |
| 21 | Git & Workflow | How a professional developer actually works |
| 22 | Deployment | Builds, hosting, env vars, migrations, monitoring |

Then: **Projects → Final Assessment → Roadmap.**

---

# Phase 0 — Web Development Mental Model

> **Prerequisite:** Basic programming concepts (variables, functions, loops, conditionals) in any language.

Before you write a single line of React, you need a correct model of the environment React lives in. Most confusing React bugs trace back to a misunderstanding of the browser/server split.

## 0.1 The Client-Server Model

### Concept

The web works on a request/response cycle. A **client** (usually a browser) sends an HTTP **request** to a **server**. The server processes it and returns an HTTP **response**.

### Why It Exists

There is no shared memory between your browser and the server. The only way they communicate is by sending messages over the network. Every message is self-contained.

### Mental Model

Think of the browser and server as two people in different rooms passing notes under a door. The server has no memory of previous notes (by default), so each request must carry everything needed to fulfill it. This is the **stateless** nature of HTTP.

### Syntax / API

```text
GET /products HTTP/1.1
Host: example.com
Accept: application/json
```

```text
HTTP/1.1 200 OK
Content-Type: application/json

{"products": [...]}
```

### Example

```text
Browser:  GET https://example.com/products
Server:  looks up products in a database
Server:  200 OK + HTML (or JSON) back to the browser
Browser: renders the response
```

### Example Breakdown

- **GET** — the HTTP method (ask for data, don't change anything).
- **`/products`** — the path identifying *what* resource you want.
- **`200 OK`** — the status code (200 = success; 404 = not found; 500 = server error).
- **`Content-Type`** — a header telling the browser what kind of data it received.

### Common Mistakes

- 🚨 Assuming the server remembers you between requests. It doesn't — unless you add cookies/sessions (Phase 14).
- 🚨 Confusing *the browser* with *the server*. Code runs in one place or the other, and you must know which.

### When to Use It

This model applies to **everything** you will build. Every request your app makes — page load, form submit, API call — follows this cycle.

### When NOT to Use It

Persistent two-way communication (chat, live cursors) needs **WebSockets**, a different protocol. But even then, the initial handshake starts with HTTP.

### Real-World Usage

- The browser requests `/` → server returns HTML → browser parses it → browser requests the CSS/JS/images referenced inside → those come back → the page renders.
- A React "single-page app" is still served over HTTP; it just fetches data via many smaller requests (APIs) instead of one big HTML document.

### 🛠️ Practice

1. Open your browser's DevTools → **Network** tab. Load any website. Identify 5 requests and note their method, status code, and what they returned (HTML? JSON? image?).
2. For one request, look at the **Headers** tab and find at least one request header and one response header.

### 🧪 Mini Challenge

Use `curl` (or DevTools) to make a `GET` request to `https://jsonplaceholder.typicode.com/todos/1`. Without looking at the docs, predict what you'll get back. Then explain *why* the response looks like that.

### ✅ Checkpoint

- What is a request? A response? What carries them?
- What does "stateless" mean, and why does it matter?
- Name 3 common HTTP status codes and what they mean.

---

## 0.2 HTML, CSS, and the DOM

### Concept

The server sends **HTML** (structure), **CSS** (presentation), and **JavaScript** (behavior). The browser parses HTML into the **DOM** — a tree of objects your JavaScript can read and modify.

### Why It Exists

Browsers can't run "the web" directly. HTML describes *what* content exists; CSS describes *how it looks*; JS describes *what happens when the user interacts*.

### Mental Model

The DOM is a live tree:

```text
html
 └── body
      ├── header
      │    └── h1 "My App"
      ├── main
      │    ├── ul
      │    │    ├── li "Task 1"
      │    │    └── li "Task 2"
      │    └── button "Add"
      └── footer
```

JavaScript can find, add, remove, and change nodes in this tree. When it does, the browser re-paints the screen.

### Syntax / API

```javascript
// Vanilla JS DOM manipulation (you'll rarely write this in React)
document.querySelector("h1").textContent = "New Title";
const li = document.createElement("li");
li.textContent = "Task 3";
document.querySelector("ul").appendChild(li);
```

### Example

```html
<ul id="tasks">
  <li>Task 1</li>
  <li>Task 2</li>
</ul>
<button onclick="addTask()">Add</button>
```

```javascript
function addTask() {
  const ul = document.getElementById("tasks");
  const li = document.createElement("li");
  li.textContent = "Task 3";
  ul.appendChild(li);
}
```

### Example Breakdown

- `document.getElementById("tasks")` — find a node by its id.
- `document.createElement("li")` — create a node *in memory* (not yet visible).
- `appendChild(li)` — insert it into the tree, which makes it visible.

This is imperative: *you* describe every step of changing the UI.

### Common Mistakes

- 🚨 Thinking the DOM is slow to change because of "re-rendering." The DOM manipulation isn't the expensive part — *layout and paint* are.
- 🚨 Believing the HTML the server sent is the same as what's on screen. JavaScript changes the DOM after load.

### When to Use It

You need this model to understand what React is doing under the hood (Phase 3). You will almost never write `document.querySelector` in React code.

### When NOT to Use It

React abstracts DOM manipulation away. If you find yourself reaching for `document.*` inside React components, that's usually a sign you're fighting the framework.

### Real-World Usage

- Every interactive page you've ever used is JS mutating the DOM.
- "View source" on a modern app shows a mostly empty shell — the real content is built by JS (client-rendered) or by a framework on the server (SSR).

### 🛠️ Practice

Create a plain `index.html` with a button and a counter. Use vanilla JS to increment a counter and update the text on the button click. This is the classic exercise — do it once, in vanilla JS, so you can *feel* the imperative approach before React makes it declarative.

### 🧪 Mini Challenge

Without using React, build a tiny "add item to list and delete it on click" page in vanilla JS. Note every place you had to imperatively touch the DOM.

### ✅ Checkpoint

- What is the DOM, and how does JavaScript interact with it?
- What's the difference between *creating* a node and *inserting* it?
- Why is this model the foundation for understanding React?

---

## 0.3 Browser vs Server: Where Does Code Run?

### Concept

JavaScript runs in two environments:

| | Browser (client) | Server (Node.js) |
|---|---|---|
| Has access to | DOM, `window`, `localStorage`, `document` | filesystem, environment variables, databases, secrets |
| Security | code is visible to users | code is hidden from users |
| Purpose | interactivity, UI | data, business logic, security |

### Why It Exists

Some things can *only* happen on the client (user input, animations) and some things *must* happen on the server (secret validation, database access). The whole Server/Client architecture of Next.js (Phase 10) depends on this distinction.

### Mental Model

```text
CLIENT (browser)                    SERVER (Node)
─────────────────                   ─────────────
user sees UI       ←── HTTP ───→    reads/writes DB
clicks buttons                      holds secrets
runs animations                     does heavy computation
```

The server is a **trusted** environment. The client is **untrusted** — anyone can open DevTools and read or modify anything you send to the browser.

### Common Mistakes

- 🚨 Putting API keys or database credentials in client-side code. Everything the browser receives is public. (See Phase 17 — Security.)
- 🚨 "Protecting" a feature by hiding a button in the UI. The client is untrusted — real protection lives on the server.

### When to Use It / When NOT to Use It

This isn't a feature you switch on — it's the *reality* of web development. Every decision later ("should this be a Server Component or Client Component?") is answered by: *which environment does this need?*

### Real-World Usage

- Server: validates a login, looks up the user's hashed password, issues a session cookie.
- Client: renders the profile page, shows a toast when the user updates their name.

### 🛠️ Practice

For each of the following, decide: *must run on the client*, *must run on the server*, or *either*: (a) reading `document.title`, (b) reading `process.env.DB_PASSWORD`, (c) hashing a password, (d) `window.addEventListener('resize', ...)`, (e) fetching a list of products from your own database.

### ✅ Checkpoint

- Name three things only the client can do, and three things only the server can do.
- Why is the client "untrusted"?
- How does this split prepare you for Server Components (Phase 10)?

---

## 0.4 What Happens When You Visit a Website (Full Walkthrough)

### Concept

A complete mental model of a page load:

```text
1. You type a URL → browser asks DNS "where does example.com live?"
2. Browser sends HTTP GET request to that server's IP
3. Server runs code (maybe queries a database)
4. Server responds with HTML
5. Browser parses HTML → builds DOM → discovers CSS and JS files
6. Browser requests those files
7. Browser executes JS → possibly fetches more data (APIs)
8. Browser paints the page → user interacts → more requests
```

### Why It Exists

Every web framework — including Next.js — is a different answer to the question: *who generates the HTML in step 4, and when?*

### Mental Model

The key idea to internalize: **the page you see is the result of many requests, not one.** The initial HTML might be a full page (server-rendered) or an empty shell (client-rendered).

### The Three Rendering Strategies (preview — detailed in Phase 8)

| Strategy | Who builds HTML | When | Trade-off |
|---|---|---|---|
| **CSR** (Client-Side Rendering) | JavaScript in the browser | After the HTML shell loads | Fast after load, slow first load, bad for SEO |
| **SSR** (Server-Side Rendering) | Server | On every request | Fresh data, slower requests |
| **SSG** (Static Site Generation) | Build time | Once, when you build | Instant, but data can go stale |

Next.js lets you mix all three per page — that's its superpower.

### Common Mistakes

- 🚨 Treating "the web" as one monolith. It's a chain of independent systems (DNS, servers, databases, browsers, CDNs).
- 🚨 Assuming the page you see was rendered the way the server sent it. In client-rendered apps, the server sends a shell and JS builds everything.

### Real-World Usage

- Check the Network tab of any site. You'll see the initial document, then CSS/JS, then XHR/fetch calls to APIs, then images.

### 🛠️ Practice

Load a React-based site (e.g., any modern dashboard). In DevTools → Network, filter by **Doc**, then by **Fetch/XHR**. Note the difference between the initial document and the API calls that followed.

### 🧪 Mini Challenge

Open a page, then **right-click → View Page Source** (Ctrl+U). If the content you see on screen isn't in the source, the page is client-rendered. Try to find a page that is *both* — content in source *and* API calls after load. What does that tell you about its architecture?

### ✅ Checkpoint

- Walk through the full request lifecycle from URL to painted page.
- What are the three rendering strategies and their trade-offs?
- Why does "who builds the HTML" matter for SEO, speed, and data freshness?

---

## 🚨 Common Beginner Mistakes (Phase 0)

- Skipping the mental model and jumping straight into code. You'll spend hours later debugging "server vs client" confusion that this phase prevents.
- Thinking the client can be trusted with secrets.
- Not using DevTools. The Network tab is your window into what your app actually does.
- Confusing "the server rendered HTML" with "the server sent JavaScript that builds HTML."

---

## ✅ Phase 0 Checkpoint

### What I Should Know

- [ ] The client-server request/response model
- [ ] HTTP methods and status codes
- [ ] The DOM and how JS interacts with it
- [ ] The difference between browser and server environments
- [ ] CSR vs SSR vs SSG at a conceptual level
- [ ] How to use the Network tab

### Questions

1. Why is HTTP stateless, and what are the consequences?
2. A form submits data. What does the browser actually send, and what does the server do with it?
3. Your coworker says "the database is on the frontend." Why is that a category error?

### Coding Challenge

Build a vanilla HTML/JS page that fetches todos from `https://jsonplaceholder.typicode.com/todos` and renders them as a list with a loading state. Use only `fetch` and DOM APIs. You'll use this exact pattern constantly in React — the syntax changes, the thinking doesn't.

### Design Challenge

Sketch (on paper or in text) the request flow for a todo app: adding a todo, seeing it appear, and the data being saved. Label each step with where it happens (browser vs server) and whether it's a request, a response, or a DOM update.

### Ready to Continue?

✅ You can explain the request/response cycle from memory.
✅ You can use the Network tab to trace what a page actually does.
✅ You know why the client is untrusted and what must stay on the server.
✅ You built the vanilla todo-fetch exercise without looking anything up.

---

# Phase 1 — JavaScript Required for React

> **Prerequisite:** Phase 0. Basic programming concepts.
> **Goal:** The subset of modern JavaScript (ES6+) you *must* know before React makes sense. React is written in this language — you can't skip it.

> ⚠️ This is not a JavaScript course. We cover only what React code actually uses daily. If you want the full language, MDN's JavaScript Guide is the reference.

## 1.1 Variables: `const` and `let`

### Concept

`const` declares a variable that can't be *reassigned*. `let` declares one that can. `var` is legacy — don't use it in new code.

### Why It Exists

Predictability. Knowing a value can't be reassigned makes code easier to reason about. React leans heavily on immutability (Phase 3).

### Syntax

```javascript
const taxRate = 0.15;   // cannot reassign
let count = 0;          // can reassign
count = 1;              // ok
// taxRate = 0.2;       // ❌ TypeError

const user = { name: "Ada" };
user.name = "Grace";    // ✅ ok! const blocks reassignment, not mutation
// user = {};           // ❌ TypeError
```

### Example Breakdown

- `const` protects the *binding* (the variable name), not the *object* it points to. `user.name = ...` mutates the object, which is allowed.
- React's golden rule is *don't mutate state — create new values*. You'll see this in Phase 3.

### Common Mistakes

- 🚨 Using `const` with objects and expecting them to be frozen. Use `Object.freeze` for that (rarely needed).
- 🚨 Using `var` because a tutorial from 2015 did.

### When to Use It

Default to `const`. Use `let` only when you reassign (e.g., a loop counter or an accumulator).

### 🛠️ Practice

Write a function that takes an array of numbers and returns the sum, using `const` for everything except the accumulator, which needs `let`.

### ✅ Checkpoint

- Difference between reassignment and mutation?
- Why does React care about immutability?

---

## 1.2 Arrow Functions

### Concept

A shorter function syntax. Unlike `function`, arrow functions don't have their own `this` — they inherit it from the surrounding scope.

### Why It Exists

React code is full of short inline functions (event handlers, callbacks, `.map`). Arrows make them readable. The `this` behavior also avoids a classic React bug (losing `this` in handlers) — which is one reason modern React barely uses `this` at all.

### Syntax

```javascript
// Regular function
function add(a, b) { return a + b; }

// Arrow, implicit return
const add = (a, b) => a + b;

// Single parameter: parentheses optional
const double = x => x * 2;

// No parameters: parentheses required
const now = () => Date.now();

// Block body: must use return
const describe = (a, b) => {
  const sum = a + b;
  return `sum is ${sum}`;
};
```

### Example

```javascript
const prices = [10, 20, 30];
const withTax = prices.map(p => p * 1.15);
// [11.5, 23, 34.5]
```

### Example Breakdown

- `.map` calls the arrow once per element; `p` is the current element.
- The arrow's implicit return means we don't need `{ return ... }`.

### Common Mistakes

- 🚨 Writing `{ return }` when you meant implicit return, or forgetting `return` when you use a block body.
- 🚨 Returning an object literal with implicit return: `x => { name: x }` returns `undefined` (the braces are parsed as a block). Fix: `x => ({ name: x })`.

### When to Use It

Almost everywhere in React — inline handlers, `.map` callbacks, `.filter`, `.sort` comparators, `useEffect` bodies.

### When NOT to Use It

When you need a named, hoisted, reusable function for readability — you can still use `function`. (Also, arrow functions can't be constructors or have a dynamic `this`.)

### Real-World Usage

```javascript
// Filtering a list in a component
const completed = todos.filter(t => t.done);
```

### 🛠️ Practice

Rewrite these with arrows: (a) `function(x) { return x * x; }`, (b) a `.filter` callback keeping numbers > 5, (c) a callback that returns `{ id, value }`.

### ✅ Checkpoint

- When does an arrow function need `{}` around its body?
- What does "implicit return" mean?

---

## 1.3 Template Literals

### Concept

Strings that can span lines and embed expressions with `${}`.

### Why It Exists

Building strings (URLs, messages, class names) is constant work in UI code. Template literals make it clean.

### Syntax

```javascript
const name = "Ada";
const greeting = `Hello, ${name}!`;          // "Hello, Ada!"
const multi = `Line 1
Line 2`;                                      // real newline
const url = `/api/users/${id}/todos`;         // dynamic paths
```

### Common Mistakes

- 🚨 Using `+` concatenation for anything non-trivial.
- 🚨 Forgetting backticks and using quotes (then `${}` doesn't work).

### 🛠️ Practice

Build a URL template for a blog post: `/posts/${slug}?page=${page}`. Then build a multi-line HTML string for a card.

---

## 1.4 Destructuring

### Concept

Extract values from objects or arrays into named variables in one statement.

### Why It Exists

React passes data as **props** (an object) — you'll destructure props in nearly every component. Hooks return arrays — you'll destructure those too.

### Syntax

```javascript
// Object destructuring
const user = { id: 1, name: "Ada", email: "ada@x.io" };
const { name, email } = user;        // name, email in scope

// Renaming
const { name: userName } = user;

// Defaults
const { role = "user" } = user;      // role === "user" if missing

// Array destructuring (this is useState!)
const pair = ["Ada", "setAda"];
const [value, setValue] = pair;

// Rest
const { password, ...safeUser } = user;  // safeUser without password
```

### Example (the React shape you'll see constantly)

```javascript
function Profile({ user, onLogout }) {
  // props destructured at the parameter level
  return <div>{user.name}</div>;
}
```

### Example Breakdown

- `function Profile({ user, onLogout })` — the props object is destructured in the signature.
- Nested destructuring exists but hurts readability — prefer extracting step by step.

### Common Mistakes

- 🚨 Over-nesting destructuring (`const { a: { b: { c } } } = x`) — unreadable.
- 🚨 Destructuring a possibly-`undefined` value: `const { name } = maybeUndefined;` throws. Guard first: `maybeUndefined?.name`.

### 🛠️ Practice

1. Destructure `id` and `title` from `{ id: 3, title: "Fix bug", done: false }`.
2. Write a function `renderTask({ title, done })` that uses both.
3. Use array destructuring to swap two variables.

### ✅ Checkpoint

- How do you give a destructured variable a new name? A default value?
- Why is destructuring central to React components and `useState`?

---

## 1.5 Spread and Rest

### Concept

`...` spreads an iterable/object into a new context (spread), or collects remaining values (rest).

### Why It Exists

React's immutability rule means you constantly *copy* objects/arrays instead of mutating them. Spread is the copy tool.

### Syntax

```javascript
// Copy + override an object (THE React pattern)
const user = { id: 1, name: "Ada" };
const updated = { ...user, name: "Grace" };  // new object, name changed

// Copy + add to an array (THE React pattern)
const todos = [{ id: 1 }];
const more = [...todos, { id: 2 }];          // new array with item appended

// Rest in function params
function logAll(...args) { console.log(args); }

// Rest in destructuring
const { password, ...safeUser } = user;

// Spread strings/iterables
const chars = [..."abc"];  // ["a","b","c"]
```

### Example (the exact pattern you'll write daily)

```javascript
const addTodo = (todos, newTodo) => [...todos, newTodo];
const toggleTodo = (todos, id) =>
  todos.map(t => t.id === id ? { ...t, done: !t.done } : t);
const removeTodo = (todos, id) => todos.filter(t => t.id !== id);
```

### Example Breakdown

- These three functions never mutate the input array — they return **new arrays**. React detects changes by reference comparison, so new references = re-render (Phase 3).

### Common Mistakes

- 🚨 `todos.push(newTodo)` — mutates. In React this silently breaks re-renders.
- 🚨 Spreading is **shallow** — nested objects are still shared references.
- 🚨 Forgetting that `{...obj}` and `[...arr]` are copies only one level deep.

### When to Use It

Any time you'd otherwise mutate: adding/removing/updating items in state, overriding fields, passing many props.

### 🛠️ Practice

Write pure functions: `updateTitle(todos, id, title)`, `prependTask(todos, task)`, `markAllDone(todos)`. No mutations allowed — verify with `todos === original` being `false`.

### 🧪 Mini Challenge

`deepClone` is NOT what spread does. Write a function that adds a comment to a nested structure `{ post: { comments: [...] } }` without mutating any level. (Hint: you need to spread at every level.)

### ✅ Checkpoint

- Why does React require new references instead of mutation?
- Shallow vs deep copy — what's the difference?

---

## 1.6 Array Methods: `map`, `filter`, `reduce`, `find`, `some`, `every`

### Concept

Higher-order array methods — functions that take a callback and produce a new array or value.

### Why It Exists

Rendering lists (`map`), filtering data (`filter`), deriving values (`reduce`, `find`) — React UIs are mostly these three operations over data.

### Syntax

```javascript
const todos = [
  { id: 1, title: "A", done: false },
  { id: 2, title: "B", done: true },
  { id: 3, title: "C", done: false },
];

// map: transform every element → new array (same length)
const titles = todos.map(t => t.title);          // ["A","B","C"]

// filter: keep elements matching a predicate → new array (shorter)
const pending = todos.filter(t => !t.done);      // 2 items

// find: first match or undefined
const firstDone = todos.find(t => t.done);       // {id:2,...}

// some / every: boolean checks
const anyDone = todos.some(t => t.done);         // true
const allDone = todos.every(t => t.done);        // false

// reduce: fold into a single value
const total = [1, 2, 3].reduce((acc, n) => acc + n, 0);  // 6
```

### Example (the React render pattern)

```javascript
return (
  <ul>
    {todos.map(t => (
      <li key={t.id}>{t.title}</li>
    ))}
  </ul>
);
```

### Example Breakdown

- `.map` returns an array of JSX elements — that's how you render a list.
- The `key` prop (Phase 2) tells React which items are which.

### Common Mistakes

- 🚨 Using `.map` when you meant `.filter` (or vice versa). `map` keeps length; `filter` shrinks it.
- 🚨 Mutating inside callbacks instead of returning new values.
- 🚨 Forgetting that `find` returns `undefined` when nothing matches — guard before reading properties.

### When to Use It

Every list in every UI. `reduce` for totals/groupings. `some`/`every` for "is there any..." conditions.

### When NOT to Use It

Don't chain 5 array methods when a loop or a simpler approach is clearer. Readability wins.

### 🛠️ Practice

Given an array of transactions `{ id, amount, category }`: (a) get all `food` transactions, (b) get the total spent, (c) get the largest single transaction, (d) check if any transaction exceeds 1000.

### 🧪 Mini Challenge

Group the transactions by category: `{ food: [...], travel: [...] }` using `reduce`. (Hint: spread into the accumulator object, or set the key first.)

### ✅ Checkpoint

- What does each method return?
- Which two methods do you use for rendering lists?

---

## 1.7 Optional Chaining and Nullish Coalescing

### Concept

`?.` safely reads nested properties; `??` provides a default for `null`/`undefined`.

### Why It Exists

API responses are full of missing fields. Guarding every access with `if (x && x.y)` is noise; these operators remove the noise safely.

### Syntax

```javascript
const user = { profile: { name: "Ada" } };

user.profile.name;      // "Ada"
user.profile?.email;    // undefined (no throw)
user.missing?.x;        // undefined

// ?? vs ||
const name = user.name ?? "Guest";    // "Guest" only if null/undefined
const count = user.count || 0;        // 0 for null, undefined, "", 0, false
```

### Example

```javascript
// API response that might be incomplete
const { data } = await fetchUser(id);
const displayName = data?.user?.name ?? "Unknown user";
```

### Example Breakdown

- `?.` short-circuits: if `data` or `data.user` is `null`/`undefined`, the whole expression is `undefined`.
- `??` only triggers on `null`/`undefined` — unlike `||` which also triggers on `""`, `0`, `false`. That's usually what you want for real defaults.

### Common Mistakes

- 🚨 Using `||` when a legitimate value is `0` or `""`: `score || 10` turns a real score of 0 into 10. Use `??`.
- 🚨 Optional chaining on the *call* of a method that must exist: `user.save?.()` silently swallows bugs. Only use `?.` for genuinely optional things.

### 🛠️ Practice

Write a function `getBillingAddress(user)` that returns `user.billing.address` or `"No address"`, without any `if` statements.

### ✅ Checkpoint

- Difference between `??` and `||`?
- When is `?.` appropriate?

---

## 1.8 Promises and `async/await`

### Concept

A **Promise** represents a value that isn't available yet. `async/await` is syntax that makes promise-based code read like synchronous code.

### Why It Exists

The web is full of operations that take time: network requests, file reads, database queries. JavaScript is single-threaded, so it can't block while waiting — it schedules work and continues. Promises are the mechanism; `async/await` is the readable interface.

### Mental Model

```text
Sync code:   doA(); const x = doB(); use(x);
             — doB must finish before we continue

Async code:  const x = await doB(); use(x);
             — "pause here, continue when the value arrives"
             — the rest of the app keeps running meanwhile
```

### Syntax

```javascript
// A function that returns a Promise
function fetchTodo(id) {
  return fetch(`https://jsonplaceholder.typicode.com/todos/${id}`)
    .then(res => res.json());          // then = older style
}

// Same thing with async/await
async function fetchTodo(id) {
  const res = await fetch(`https://jsonplaceholder.typicode.com/todos/${id}`);
  return res.json();
}
```

### Error handling

```javascript
async function load() {
  try {
    const res = await fetch(url);
    if (!res.ok) throw new Error(`HTTP ${res.status}`);
    return await res.json();
  } catch (err) {
    console.error("Failed to load:", err);
    return null;   // or rethrow, or set error state
  }
}
```

### Example Breakdown

- `await` can only be used inside an `async` function.
- `fetch` returns a Promise; `await` unwraps it.
- `.ok` is `false` for 404/500 — `fetch` does **not** throw on HTTP errors, only on network failures. You must check `.ok` yourself.
- The `try/catch` is where loading failures become visible state in your UI (Phase 6).

### Common Mistakes

- 🚨 Forgetting `await` — you get a Promise object instead of the data.
- 🚨 Forgetting that `fetch` doesn't reject on 404/500.
- 🚨 `async` inside `.map` — `todos.map(async t => ...)` returns an array of Promises. Use `Promise.all`.
- 🚨 Blocking the UI with synchronous waiting — there is no "sleep the thread" in the browser; that's why async exists.

### When to Use It

Every network request, every file/database operation. In React: fetching data (Phase 6), and in Next.js: Server Components can be `async` directly (Phase 10).

### When NOT to Use It

Don't make something async that's actually synchronous (e.g., reading from state). Don't `await` things in a `.map` sequentially when they can run in parallel with `Promise.all`.

### Real-World Usage

```javascript
// Parallel fetch of several resources
const [users, posts] = await Promise.all([
  fetchUsers(),
  fetchPosts(),
]);
```

### 🛠️ Practice

1. Write `async function getTodo(id)` that fetches and returns the JSON, throwing a clear error on non-2xx.
2. Fetch 5 todos in parallel with `Promise.all` and log their titles.
3. Add error handling: log the error and return a fallback value.

### 🧪 Mini Challenge

Write a `fetchWithRetry(url, attempts = 3)` that retries up to 3 times with a short delay between attempts. (Hint: a `for` loop with `await new Promise(r => setTimeout(r, 500))`.)

### ✅ Checkpoint

- What is a Promise? What does `await` do?
- Why doesn't `fetch` throw on a 404?
- What's wrong with `arr.map(async x => ...)` when you need all results at once?

---

## 1.9 Modules: `import` / `export`

### Concept

JavaScript files can export values and import them elsewhere, giving you file-level organization.

### Why It Exists

One giant file is unmaintainable. Modules are how React apps are split into components, utilities, and libraries.

### Syntax

```javascript
// utils.js
export const formatDate = (d) => d.toISOString();
export function add(a, b) { return a + b; }
export default function greeting(name) { return `Hi ${name}`; }

// app.js
import greeting, { formatDate, add } from "./utils";
```

### Example Breakdown

- Named exports (`export const x`) are imported with `{ x }`.
- Default export (`export default`) is imported without braces. Prefer named exports for consistency.

### Common Mistakes

- 🚨 Mixing default and named imports incorrectly.
- 🚨 Importing from the wrong path (relative paths are case-sensitive on some systems).
- 🚨 Importing a *value* where you need a *type* — TypeScript's `import type` (Phase 7).

### 🛠️ Practice

Split your vanilla todo-fetch exercise (from Phase 0) into `api.js` (fetching logic), `render.js` (DOM helpers), and `main.js` (glue).

---

## 🚨 Common Beginner Mistakes (Phase 1)

- Skipping array methods and then writing `.map` wrong for weeks.
- Using `||` where `??` belongs (the `score = 0` bug).
- Forgetting `await`, then debugging "why is my variable a Promise?"
- Not checking `res.ok`, so HTTP errors silently become empty data.
- Mutating state-shaped arrays with `push` — this will bite you hard in Phase 3.

---

## ✅ Phase 1 Checkpoint

### What I Should Know

- [ ] `const` vs `let`; mutation vs reassignment
- [ ] Arrow functions and implicit returns
- [ ] Template literals
- [ ] Destructuring objects and arrays
- [ ] Spread/rest for immutable updates
- [ ] `map`, `filter`, `find`, `reduce`, `some`, `every`
- [ ] `?.` and `??`
- [ ] Promises, `async/await`, error handling
- [ ] Modules

### Questions

1. Write (from memory) the three immutable array operations: add, update, remove.
2. What does `fetch` return before you `await` it?
3. Why does `arr.map(async x => ...)` surprise people?

### Coding Challenge

Write a small module `tasks.js` that exports functions using everything from this phase: `getPending(tasks)`, `totalTime(tasks)`, `findById(tasks, id)`, `addTask(tasks, task)`, `toggleTask(tasks, id)` — all pure (no mutation), with defaults and safe access where relevant. No solution below — write it yourself, then test it in Node or the browser console.

### Design Challenge

Sketch a data model for a task app: what does a task object look like? What operations will you need (add, update, delete, filter, toggle)? Write the function signatures before writing the functions.

### Ready to Continue?

✅ You wrote the immutable operations from memory.
✅ You can explain promises and `async/await` with a real example.
✅ You used at least 6 of the concepts above in your own code this phase.

---

# Phase 2 — React Fundamentals

> **Prerequisite:** Phases 0–1. You should be comfortable with the request/response model, arrow functions, destructuring, spread, `.map`, and `async/await`.
> **Goal:** Build reusable components with JSX, props, state, events, lists, and composition — and *feel* why the declarative model beats manual DOM code.

## 2.1 What React Is (and Why It Exists)

### Concept

React is a **JavaScript library for building user interfaces** by describing them *declaratively*. You describe what the UI should look like for a given state; React figures out how to make the DOM match.

### Why It Exists

In Phase 0 you wrote imperative DOM code: *find the node, create a node, insert the node, update the text*. That breaks down at scale:

- The DOM and the data get out of sync (you forgot to update one of the five places).
- You spend your time on plumbing, not on the product.
- Reusing UI means copying and pasting.

React's answer: **UI is a function of state.** `UI = f(state)`. When state changes, the UI is re-derived automatically.

### Mental Model

```text
Imperative (vanilla JS):
  "First add this li. Then update that count. Then if X, hide the button..."

Declarative (React):
  "Here's what the screen looks like when todos is this array."
  (React handles the rest)
```

You stop commanding the DOM and start describing outcomes.

### Syntax / API

```jsx
function TodoList({ todos }) {
  return (
    <ul>
      {todos.map(t => <li key={t.id}>{t.title}</li>)}
    </ul>
  );
}
```

### Example Breakdown

- `function TodoList({ todos })` — a component: a function that takes props and returns JSX.
- `{todos.map(...)}` — JSX expressions: any `{expression}` runs JavaScript inside the markup.
- `<ul>`, `<li>` — plain HTML elements are valid JSX.

### Common Mistakes

- 🚨 Thinking React "renders HTML strings." It builds a **UI description** (a tree of elements) and syncs the DOM to it.
- 🚨 Treating React as "just a template language." It's a state-to-UI engine.

### When to Use It / When NOT to Use It

React shines for **interactive, stateful UIs**. A static brochure page doesn't need it. But note: this guide uses React via Next.js, which layers server rendering on top (Phase 8).

### Real-World Usage

Every modern dashboard, social feed, e-commerce storefront, and admin panel you've used is (likely) React — because the UI must stay in sync with constantly changing data.

### 🛠️ Practice

Compare: write the "add item to list" page from Phase 0 in vanilla JS, then write the same thing in React (below). Note what you *don't* have to do in React (no `getElementById`, no `appendChild`).

### 🧪 Mini Challenge

In one sentence each, explain to a junior: (a) what declarative means, (b) why `UI = f(state)` is the core idea, (c) what problem this solves that imperative code has.

### ✅ Checkpoint

- What problem does React solve?
- What does "declarative" mean in your own words?
- What is a component? A prop? State?

---

## 2.2 JSX — JavaScript + XML

### Concept

**JSX** is a syntax extension that looks like HTML but compiles to JavaScript function calls. It's the most natural way to express UI structure in React.

### Why It Exists

Building UI as nested `React.createElement` calls is unreadable. JSX gives you HTML-like markup with the full power of JavaScript embedded via `{}`.

### Mental Model

```jsx
// What you write:
<div className="card">
  <h1>{title}</h1>
  <button onClick={handleClick}>Save</button>
</div>

// Roughly what it compiles to (conceptually):
createElement("div", { className: "card" },
  createElement("h1", null, title),
  createElement("button", { onClick: handleClick }, "Save")
)
```

JSX is *sugar*. The output is a plain JavaScript object describing the UI — a **React element**.

### Syntax / API

```jsx
// Expressions in braces
const name = "Ada";
<h1>Hello, {name.toUpperCase()}</h1>   // "Hello, ADA"

// className, not class (class is a JS keyword)
<div className="card">...</div>

// Self-closing tags for void elements
<img src={url} alt={altText} />

// Comments inside JSX
{/* this is a JSX comment */}

// Fragments — return multiple elements without a wrapper div
<>
  <dt>Name</dt>
  <dd>Ada</dd>
</>
```

### Example

```jsx
function Avatar({ user, size = 50 }) {
  return (
    <img
      src={user.avatarUrl}
      alt={`${user.name}'s avatar`}
      width={size}
      height={size}
      className="rounded-full"
    />
  );
}
```

### Example Breakdown

- All JS values go inside `{}`.
- `alt` includes a template literal — JSX attributes are just JS expressions.
- `size = 50` is a default parameter, so `size` is optional.

### Common Mistakes

- 🚨 `class=` instead of `className=`.
- 🚨 Using `if/else` directly inside JSX — it's an expression language, not statements. Use ternaries or extract variables.
- 🚨 Forgetting that `{}` renders the *value* — booleans, `null`, `undefined` render nothing; objects and functions throw.
- 🚨 `{condition && <p>hi</p>}` renders `0` when `condition` is `0` (not `false`) — use `condition > 0 && ...` or `!!condition`.
- 🚨 Missing keys on lists (next section).

### When to Use It

Always — JSX is the standard way to write React components.

### When NOT to Use It

React works without JSX (plain `createElement`), but there's no reason to. In rare dynamic-markup cases, use arrays of elements or components instead of string-injection hacks.

### Real-World Usage

Every `.jsx`/`.tsx` file in a real codebase is JSX. Component libraries (shadcn/ui, Radix) ship JSX components you compose.

### 🛠️ Practice

1. Write JSX for a product card (image, title, price, button) using `{}` for all dynamic values.
2. Render a badge conditionally (`inStock ? green : red`).
3. Write the same UI with a fragment instead of a wrapper div.

### 🧪 Mini Challenge

What does `{count && <p>Items</p>}` render when `count === 0`? Why? Fix it. (Check the Common Mistakes above if you're stuck — then explain the fix to yourself.)

### ✅ Checkpoint

- Why `className` and not `class`?
- What can and cannot go inside `{}`?
- What does JSX compile to, conceptually?

---

## 2.3 Components — The Building Blocks

### Concept

A **component** is a function (or class, in legacy code) that takes props and returns JSX. Components let you split the UI into independent, reusable pieces.

### Why It Exists

The same reason functions exist in any language: **reuse and organization**. A component encapsulates markup + behavior behind a clean interface (its props).

### Mental Model

```text
App
 ├── Sidebar
 │    ├── NavItem (x4)
 │    └── UserCard
 ├── Main
 │    ├── TodoList
 │    │    └── TodoItem (xN)
 │    └── NewTodoForm
```

Components are a tree. Data flows **down** (props), events flow **up** (callbacks).

### Syntax / API

```jsx
// Component definition — capitalized name! lowercase = HTML tag
function TodoItem({ todo, onToggle }) {
  return (
    <label>
      <input
        type="checkbox"
        checked={todo.done}
        onChange={() => onToggle(todo.id)}
      />
      {todo.title}
    </label>
  );
}

// Using it
<TodoItem todo={t} onToggle={handleToggle} />
```

### Example Breakdown

- Component names **must start with a capital letter**; JSX treats lowercase as HTML elements (`<div>`) and capitalized as components (`<TodoItem>`).
- `todo` and `onToggle` are props — inputs from the parent.
- The component doesn't own the data; it *receives* it and *reports* events.

### Common Mistakes

- 🚨 Lowercase component names → "not defined" errors.
- 🚨 Defining components *inside* other components (recreates on every render, loses state).
- 🚨 Components that reach into the DOM or other components' state directly instead of using props.

### When to Use It

Extract a component when: it's reused, it's getting long, or it has its own state/behavior. **Rule of thumb:** extract when a chunk of JSX has a clear name and a single responsibility.

### When NOT to Use It

Don't extract prematurely — a 10-line JSX block used once doesn't need a component file. Over-componentization is a real (and common) anti-pattern.

### Real-World Usage

Component libraries are entire collections of reusable components (Button, Modal, Table). Your app is composed of your own + library components.

### 🛠️ Practice

Given a `User` object, extract: `UserCard`, `UserStats`, and `UserActions` components. Compose them in a `UserProfile` component.

### 🧪 Mini Challenge

Refactor a `PostList` so the individual post rendering is a `Post` component that receives `post` and `onSelect`. No solutions — design the props yourself.

### ✅ Checkpoint

- What makes a valid component?
- What is the direction of data flow?
- When do you extract a component?

---

## 2.4 Props — Data In

### Concept

**Props** are the inputs to a component — a read-only object of values passed from the parent.

### Why It Exists

Components need configuration and data. Props are the *interface*: they define what a component needs to render.

### Mental Model

Props are like function arguments. **Props are immutable** — a component must never modify its props; it asks its parent to change them (via callbacks).

### Syntax / API

```jsx
function Greeting({ name, age, isAdmin = false }) {
  return <p>{name} ({age}) {isAdmin ? "👑" : ""}</p>;
}

<Greeting name="Ada" age={36} isAdmin />
```

### Example Breakdown

- Destructuring props in the signature is the modern convention.
- `isAdmin` (no value) passes `true`.
- Defaults (`isAdmin = false`) apply when the prop is `undefined`.

### Common Mistakes

- 🚨 Mutating props: `todo.title = "x"` — breaks React's model and causes silent bugs.
- 🚨 Prop drilling — passing `user` through 5 components that don't use it (Phase 5 has the cure: Context).
- 🚨 Passing too many unrelated props to one component (sign of a design problem).
- 🚨 Spreading `{...props}` everywhere — hides which props a component actually needs.

### When to Use It

Always — props are how components communicate. Every component you write takes props.

### When NOT to Use It

When data must reach many unrelated components, or state must be shared widely, props alone cause drilling — that's when Context or global state belongs (Phase 5).

### Real-World Usage

Design-system components are prop-driven APIs: `<Button variant="primary" size="lg" disabled>`. Library authors think hard about prop design because props are the API.

### 🛠️ Practice

Build a `Button` component with props: `variant` (primary/secondary/ghost), `size`, `disabled`, `onClick`, and `children`. Compose it in three places.

### 🧪 Mini Challenge

Design the props for a `DataTable` component (columns, rows, sorting, pagination) — just the prop list and types, no implementation. Defend each prop.

### ✅ Checkpoint

- Can a component change its own props? How does it ask for a change instead?
- What is prop drilling, and when does it become a problem?

---

## 2.5 State — Data That Changes

### Concept

**State** is data a component remembers between renders, and that triggers re-rendering when it changes. The primary hook is `useState`.

### Why It Exists

Props are fixed for a render. But UIs change: the user typed something, toggled something, fetched something. **State is the memory of the component.**

### Mental Model

```text
Every render = a snapshot.
state is a value captured in that snapshot.
When setState runs, React schedules a NEW render with the NEW value.
```

This "snapshot" mental model is the single most important idea in React. Master it now or fight it for months.

### Syntax / API

```jsx
import { useState } from "react";

function Counter() {
  const [count, setCount] = useState(0);   // [value, setter]

  return (
    <button onClick={() => setCount(count + 1)}>
      Clicked {count} times
    </button>
  );
}
```

### Example Breakdown

- `useState(0)` — initial value `0`; returns `[currentValue, setter]`.
- `setCount(count + 1)` — tells React: "next render, count should be count + 1."
- The component re-renders, `count` is the new value, the button text updates. **You never touch the DOM.**

### The Snapshot Rule (crucial)

```jsx
function BuggyCounter() {
  const [count, setCount] = useState(0);

  const handleClick = () => {
    setCount(count + 1);
    setCount(count + 1);   // ❌ still count+1! Both read the SAME snapshot
  };

  return <button onClick={handleClick}>{count}</button>;
}
```

- Within one render, `count` is a fixed snapshot. Two `setCount(count + 1)` calls both compute from the same old `count`.
- To update from the *latest* value, use the functional form: `setCount(c => c + 1)` — React guarantees `c` is the latest committed value.

### Common Mistakes

- 🚨 Mutating state: `todos.push(x)` — React compares by reference; mutation produces the same reference, so **no re-render**. Always create a new array/object.
- 🚨 Calling `setState` during render (infinite loop). Updates belong in event handlers or effects.
- 🚨 Believing `setState` is synchronous. It schedules a render — the variable in the current scope doesn't change.
- 🚨 Storing data in state that's already available elsewhere (duplicated state — Phase 5).
- 🚨 Using state for things that aren't state: computed values should be derived, not stored (Phase 5).

### When to Use It

Any value that changes over time *and affects what's rendered*: form inputs, toggles, fetched data, pagination, filters.

### When NOT to Use It

- Values computed from props/state — derive them instead.
- Data that never changes — a constant can live outside the component.
- Data that many unrelated components share — see Context/global state (Phase 5).
- Transient values that don't affect rendering (e.g., a timeout id) — use `useRef` (Phase 4).

### Real-World Usage

Every interactive element: input values, selected tab, current page, filter dropdown, cart contents, notification list.

### 🛠️ Practice

1. Build the counter (above) and predict the behavior of the double-`setCount` click before running it.
2. Build a `TodoList` with `useState` for the array: add, toggle, delete (immutable updates from Phase 1).
3. Add a filter (all/pending/done) — keep the *source* list in state and derive the filtered list.

### 🧪 Mini Challenge

Build a temperature converter (Celsius ↔ Fahrenheit) with two inputs that stay in sync. No solution — think about where the *single source of truth* lives and how to derive the other field.

### ✅ Checkpoint

- What is the snapshot model, and what does it forbid?
- Why does mutating state not re-render?
- When should state NOT be used?

---

## 2.6 Events

### Concept

Events in React are props named `onXxx` that receive handler functions: `onClick`, `onChange`, `onSubmit`, `onKeyDown`.

### Why It Exists

You need to respond to user input. React normalizes browser events and wires handlers declaratively.

### Syntax / API

```jsx
function SearchBox() {
  const [query, setQuery] = useState("");

  return (
    <input
      value={query}
      onChange={(e) => setQuery(e.target.value)}   // controlled input
      placeholder="Search..."
    />
  );
}
```

### Example Breakdown

- `onChange` fires on every keystroke (in React, unlike native `change`, it's effectively `input`).
- `e.target.value` is the current input text.
- The input's `value` comes from state and its changes write to state — a **controlled input** (Phase 6 deep-dive).

### Common Mistakes

- 🚨 Forgetting handlers must be *functions*: `onClick={handleClick}` (passing the function) vs `onClick={handleClick()}` (calling it immediately — a classic bug).
- 🚨 Creating the handler inline (`onClick={() => ...}`) when the function is expensive or needed elsewhere — see `useCallback` (Phase 4) for when it matters.
- 🚨 Using `onChange` on a `<form>` when you want `onSubmit` for enter-key handling.

### When to Use It

Any interaction: clicks, typing, form submits, drag, hover (via `onMouseEnter`/`onMouseLeave`), keyboard.

### When NOT to Use It

Don't wire events to elements that don't need them. And remember: events only exist in **Client Components** in Next.js (Phase 10) — they're browser APIs.

### Real-World Usage

Form inputs, buttons, navigation, modals (close on overlay click / Escape key), drag-and-drop.

### 🛠️ Practice

Build a form with two inputs and a submit button that logs the values. Then add a "reset" button. Note the difference between `onSubmit` on the form and `onClick` on the button.

### 🧪 Mini Challenge

Implement Escape-to-close on a simple modal: an overlay `<div>` with `onKeyDown` that closes on `Escape`. (Hint: `e.key === "Escape"`.)

### ✅ Checkpoint

- What's the difference between `onClick={fn}` and `onClick={fn()}`?
- What is a controlled input, in one sentence?

---

## 2.7 Conditional Rendering

### Concept

Render different JSX based on conditions, using JS expressions — `&&`, ternaries, or early returns.

### Why It Exists

UIs constantly show/hide things: loading states, empty states, login vs logged-out views.

### Syntax / API

```jsx
function Status({ user, loading }) {
  if (loading) return <Spinner />;          // early return

  return (
    <div>
      {user ? (
        <Welcome name={user.name} />
      ) : (
        <LoginButton />
      )}
      {user && !user.emailVerified && <VerifyBanner />}
    </div>
  );
}
```

### Example Breakdown

- Early returns keep components readable: "if loading, render only the spinner."
- `cond ? a : b` — ternary for two-way branching.
- `cond && <X/>` — render X only if `cond` is truthy.

### Common Mistakes

- 🚨 `cond && <X/>` rendering `0` or `""` when `cond` is falsy-but-not-`false`. Coerce: `!!cond` or `cond > 0`.
- 🚨 Complex ternaries nested three deep — extract a variable or a sub-component instead.
- 🚨 `if/else` statements *inside* JSX (won't compile) — keep them outside in the function body.

### When to Use It / When NOT to Use It

Always for view-state switching. Avoid it for *hiding content for security* — that's a server-side concern (Phase 14).

### 🛠️ Practice

Build a component with three states: loading, error, data — rendered with early returns. Then add an empty-state (no items) branch.

### ✅ Checkpoint

- How do you render nothing? How do you render one of two options?
- Why does `0 && <X/>` break?

---

## 2.8 Lists and Keys

### Concept

Render arrays with `.map`, giving each item a **key** — a stable, unique identifier React uses to track items across renders.

### Why It Exists

When a list changes, React must match old and new items to reuse DOM and preserve state (e.g., keep focus in an input). Keys are the matching mechanism.

### Mental Model

```text
Old: [A, B, C]      New: [A, X, B, C]

With good keys: React inserts X — A, B, C untouched.
With index keys: everything after the insertion point is "rebuilt",
                losing state (focus, input values, animation).
```

### Syntax / API

```jsx
{todos.map(todo => (
  <TodoItem key={todo.id} todo={todo} />
))}
```

### Example Breakdown

- `key` must be **stable** (doesn't change between renders), **unique** among siblings.
- `todo.id` is ideal. Array index is a fallback only for static, never-reordered lists.

### Common Mistakes

- 🚨 Missing keys → console warning + state bugs.
- 🚨 `key={Math.random()}` or `key={index}` for reorderable lists → broken state, broken focus, wasted renders.
- 🚨 Using `key` as a prop inside the child — it's not passed to the component; React consumes it. If the child needs the id, pass `id={todo.id}` separately.

### When to Use It

Any `.map` that renders items.

### When NOT to Use It

You don't need keys outside of lists (only siblings in an array need them).

### Real-World Usage

Tables, feeds, chat messages, notification lists — all keyed by id. Bad keys = chat inputs losing focus as new messages arrive (a classic real bug).

### 🛠️ Practice

1. Render 10 todos with id keys.
2. Deliberately break it: use `index` as key, add an item at the *front* of the list, and put an `<input>` in each row. Type in the first row's input, then add an item — observe the input state jumping to the wrong row. This is the key bug, experienced firsthand.

### ✅ Checkpoint

- What makes a good key?
- What breaks when keys are wrong?

---

## 2.9 Component Composition and `children`

### Concept

**Composition** = building complex UIs by nesting components. The `children` prop lets a component render whatever JSX is placed between its tags.

### Why It Exists

Composition is more flexible than configuration. Instead of a `Modal` knowing every possible content type, it accepts `children` — the *caller* decides the content.

### Syntax / API

```jsx
function Card({ title, children }) {
  return (
    <div className="card">
      <h2>{title}</h2>
      {children}
    </div>
  );
}

// Usage — children can be anything:
<Card title="Profile">
  <p>Some content</p>
  <UserAvatar user={user} />
</Card>
```

### Example Breakdown

- Whatever sits between `<Card>` and `</Card>` becomes the `children` prop.
- The parent decides content; the component decides *placement and styling*.

### Common Mistakes

- 🚨 Building a `Modal` with a `content` prop that only accepts strings — you need JSX. Use `children`.
- 🚨 Over-propping: `Modal` with `header`, `body`, `footer`, `closeText`... props when `children` + composition is simpler.
- 🚨 Not using composition for layout (a `Page` component receiving `sidebar`, `content`, `footer` slots).

### When to Use It

Layouts, wrappers (Card, Modal, Dialog, Accordion), any component that contains unknown content.

### When NOT to Use It

For a fixed, known structure, plain props are clearer.

### Real-World Usage

Every UI library: `<Modal>content</Modal>`, `<Table><thead>...</thead>...</Table>`. Slots are how design systems stay flexible.

### 🛠️ Practice

Build: (a) a `Card` with `children`, (b) a `Modal` with `title` + `children` + `onClose`, (c) a `PageLayout` with `sidebar` and `children` slots.

### 🧪 Mini Challenge

Build a `List` component that takes `items` and a `renderItem` function prop (render prop pattern). Think about why this is more flexible than hardcoding item rendering.

### ✅ Checkpoint

- What is `children`?
- Composition vs configuration — which is more flexible, and why?

---

## 2.10 Reusable Components — The Full Pattern

### Concept

Put it together: a reusable component is a function with a well-designed props interface, composition via `children`, and no hidden dependencies on the outside world.

### Why It Exists

Reusability is the whole point of components. A good component is used in many places without modification.

### Mental Model

Design components like library APIs:

```text
Props = the contract.
State = internal implementation detail (hidden).
Callbacks = how the parent learns about events.
children = the flexible escape hatch.
```

### Example (a reusable, accessible Button)

```jsx
function Button({ variant = "primary", size = "md", disabled, onClick, children }) {
  const classes = `btn btn-${variant} btn-${size}`;
  return (
    <button className={classes} disabled={disabled} onClick={onClick}>
      {children}
    </button>
  );
}
```

### Example Breakdown

- Sensible defaults → callers pass only what differs.
- `children` → content is the caller's choice.
- It delegates the click to the parent via `onClick` — the component doesn't *do* anything itself.

### Common Mistakes

- 🚨 Hardcoding business data inside reusable components.
- 🚨 Components that depend on global state directly instead of receiving props (breaks reuse).
- 🚨 Prop explosion — when a component needs 15 props, consider composition instead.

### When to Use It / When NOT to Use It

Reuse aggressively for genuinely repeated UI. But don't build a "Button" abstraction for a one-off page — that's premature abstraction.

### Real-World Usage

Design systems (MUI, shadcn/ui) are exactly this pattern at scale, with accessibility and theming baked in.

### 🛠️ Practice

Build a small component library from scratch: `Button`, `Input`, `Badge`, `Card`, `Modal`. Use them to compose a simple dashboard page.

### 🧪 Mini Challenge

Design a `Select` (dropdown) component. Think through: options data shape, default value, disabled state, `onChange` contract. Implement it.

### ✅ Checkpoint

- What makes a component *reusable* rather than one-off?
- How do components communicate up and down the tree?

---

## 🚨 Common Beginner Mistakes (Phase 2)

- Copying tutorial code without understanding *why* each line exists.
- Mutating state instead of replacing it (the #1 React bug).
- Using index keys on reorderable lists.
- `onClick={fn()}` — invoking instead of passing.
- Defining components inside components.
- `className` vs `class` typos.
- `0 && <X/>` rendering `0`.
- Building 40 tiny components for a page that needed 4 (over-componentization).

---

## ✅ Phase 2 Checkpoint

### What I Should Know

- [ ] What React is and the declarative model
- [ ] JSX rules (expressions, `className`, fragments, comments)
- [ ] Components and composition
- [ ] Props: immutable inputs, defaults, `children`
- [ ] State: `useState`, snapshot model, immutability
- [ ] Events: handlers as functions, controlled inputs
- [ ] Conditional rendering (early returns, ternaries, `&&`)
- [ ] Lists and keys

### Questions

1. Explain the snapshot model: why don't two `setCount(count+1)` calls add 2?
2. Why does mutating an array in state not re-render the component?
3. What's the difference between `children` and a `content` prop?
4. Why must keys be stable and unique?

### Coding Challenges

1. **Level 1:** Counter with increment/decrement/reset buttons.
2. **Level 2:** Todo list with add/toggle/delete and a filter (all/pending/done). All state updates immutable.
3. **Level 3:** Build a small "shopping cart": product list + cart count + add-to-cart + remove-from-cart, where the cart is an array of `{ id, qty }`. Design your own component tree.

### Design Challenge

You're building a settings page with a list of toggles. Design: (a) the component tree, (b) the props each component needs, (c) where state lives, (d) how the parent learns about a toggle change. Write it as a short design doc before coding.

### Ready to Continue?

✅ You can build the todo list with immutable updates from memory.
✅ You can explain the snapshot model and why mutation breaks it.
✅ You designed your own component tree in the Design Challenge.

---

# Phase 3 — React Rendering Deep Dive

> **Prerequisite:** Phase 2. You must be comfortable with state and the snapshot model.
> **Goal:** Understand exactly *what happens* when React renders, so you can predict performance problems and fix them — not guess.

## 3.1 Rendering and Re-rendering

### Concept

**Rendering** is React *calling your component function* to compute what the UI should look like. It produces a description of the UI (React elements), **not** DOM changes — yet.

### Why It Exists

React decouples "what should the UI look like" (render) from "how do I update the DOM" (commit). This separation is what makes React correct: it can compute the new UI, diff it against the old, and apply minimal DOM changes.

### Mental Model

```text
render (compute the new UI description)
   ↓
reconcile (diff old vs new description)
   ↓
commit (apply DOM changes)
   ↓
paint (browser draws; outside React's control)
```

Rendering is **cheap-ish** (running your function). DOM mutation and layout/paint are **expensive**. React minimizes the expensive parts.

### Syntax / API

```jsx
function App() {
  const [count, setCount] = useState(0);
  console.log("App rendered");            // runs on every render!
  return <Counter count={count} />;
}
```

### Example

```jsx
const [user, setUser] = useState(null);

// somewhere: setUser({name: "Ada"})
// React: 1) re-runs App 2) computes new elements 3) diffs 4) commits changes
```

### Example Breakdown

- `setState` triggers a render of the component **and its children** (unless children are memoized — Phase 18).
- The component function body runs from top to bottom on every render.
- Side effects (console.log, DOM reads, timers) must not live in the render body — that's what `useEffect` is for (Phase 4).

### Common Mistakes

- 🚨 Confusing "render" with "DOM update." React may render and commit nothing (if nothing changed).
- 🚨 Putting expensive work or side effects directly in the render body.
- 🚨 Believing `console.log` in a component shows you DOM updates — it shows you renders.

### When to Use It / When NOT to Use It

You don't "use" rendering — you *understand* it. Every component you write participates in it. Understanding it is the difference between guessing and knowing why a page is slow.

### Real-World Usage

"Why is my app slow?" — the answer is almost always "too many renders / renders too expensive," and fixing it requires this model (Phase 18).

### 🛠️ Practice

Add `console.log` to a parent and child component. Click a button in the parent. Observe: the child re-renders even though its props didn't change. This is normal React behavior — and the *reason* `React.memo` exists (Phase 18).

### ✅ Checkpoint

- What does "render" mean in React?
- What is the difference between render, commit, and paint?

---

## 3.2 Virtual DOM and Reconciliation

### Concept

The **virtual DOM** is React's in-memory description of the UI (a tree of plain objects). **Reconciliation** is the diffing process that compares the new tree to the old one and computes minimal DOM operations.

### Why It Exists

Directly manipulating the DOM on every state change is slow and error-prone. React computes *what changed* in memory, then applies only those changes to the real DOM.

### Mental Model

```text
Old virtual tree:   <ul><li>A</li><li>B</li></ul>
New virtual tree:   <ul><li>A</li><li>B</li><li>C</li></ul>

Reconciliation: "one <li> was appended" → commit: appendChild(C) only.
```

### How the Diff Works (the rules)

1. **Different element type at the same position → replace the whole subtree.** `<div>` becomes `<section>` → destroy and rebuild everything inside.
2. **Same type → reuse, update changed props.** `<li>A</li>` stays; React updates only changed attributes.
3. **Lists → use `key` to match items across renders.** Keys are the reconciliation hint.
4. **Same position, same type → recursively reconcile children.**

### Syntax / API

There is no API — reconciliation is internal. But *you* control it via: `key` props, `React.memo`, and structure (keeping stable element types at stable positions).

### Example

```jsx
// Bad for reconciliation: changes type on every toggle
{isOpen ? <div>Open</div> : <section>Closed</section>}

// Good: stable type, conditional content
<div>{isOpen ? "Open" : "Closed"}</div>
```

### Example Breakdown

- Changing element type forces React to throw away the subtree (losing state, DOM, focus).
- Keeping types stable lets React reuse the DOM node and just swap text.

### Common Mistakes

- 🚨 Using index keys (breaks item identity — see Phase 2).
- 🚨 Restructuring JSX so element types/positions shift when data changes — causes full subtree rebuilds.
- 🚨 Believing "virtual DOM is always faster" — it's a correctness/developer-experience win as much as a performance one.

### When to Use It / When NOT to Use It

You don't toggle this on or off. You write code that *helps* reconciliation: stable keys, stable types, memoization where it pays (Phase 18).

### Real-World Usage

Whenever you add/remove/reorder list items or toggle views, reconciliation is happening. Knowing the rules explains why some UI glitches (lost focus, flicker) occur.

### 🛠️ Practice

Create a list where toggling a boolean switches each row between `<li>` and `<div>`. Put an `<input>` in each row, type text, toggle — observe the input state being destroyed. Then fix it by keeping the type stable.

### 🧪 Mini Challenge

Explain, without looking: why does reordering a list with index keys cause input state to "follow" the wrong rows?

### ✅ Checkpoint

- What are the 4 reconciliation rules?
- Why does changing an element type destroy its subtree?
- What role do keys play?

---

## 3.3 Why Components Re-render

### Concept

A component re-renders when:

1. **Its state changes** (`setState`).
2. **Its props change** (parent re-rendered with new values).
3. **Its parent re-renders** (children re-render by default, even with identical props).
4. **A context it consumes changes** (Phase 5).

### Why It Exists

React's default is "re-render broadly, then reconcile cheaply." Correctness first — React can't know which child depends on what without you telling it, so it re-renders everything under a changed component.

### Mental Model

```text
setState in Parent
   ↓
Parent re-renders
   ↓
ALL children re-render (by default)
   ↓
reconciliation filters out the no-op DOM changes
```

Re-render ≠ DOM update. A child can re-render (run its function) and commit nothing.

### Common Mistakes

- 🚨 Treating every re-render as a performance problem. Re-renders are cheap; *expensive renders* are the problem.
- 🚨 Fixing re-renders by over-memoizing (Phase 18: `useMemo`/`React.memo` everywhere is usually worse).
- 🚨 Forgetting that inline objects/arrays/functions (`props={{a:1}}`) create new references every render — defeating memoization until you understand `useCallback`/`useMemo`.

### When to Use It / When NOT to Use It

Optimize only when you measure a problem (Phase 18). First build it correct, then measure, then optimize.

### Real-World Usage

The classic slow-app pattern: a huge list re-renders because an unrelated state change happens in a parent. The fix is structural (move state down, memoize, or split components) — not guesswork.

### 🛠️ Practice

Build `App → BigList (1000 rows) + ThemeToggle`. Toggle the theme and use the React DevTools profiler to watch BigList re-render. Then move the theme state *into* a small wrapper so BigList doesn't re-render. (You'll formalize this in Phase 18.)

### 🧪 Mini Challenge

Why does passing `onClick={() => doThing()}` inline defeat `React.memo` on the child? Trace the reference identity through a render.

### ✅ Checkpoint

- List the four causes of re-render.
- Re-render vs DOM update — what's the difference and why does it matter?

---

## 3.4 Component Lifecycle (Modern View)

### Concept

The old model (class components) had lifecycle *methods*: `componentDidMount`, `componentDidUpdate`, `componentWillUnmount`. Modern React replaces them with **hooks** and a simpler mental model: **render → effect → cleanup**.

### Why It Exists

Lifecycle methods scattered logic across time ("this should run on mount, that on update"). Hooks tie logic to *data dependencies* instead: "re-run this whenever `userId` changes." That's more robust and less error-prone.

### Mental Model

```text
For every render:
  1. render phase  — component function runs (pure; no side effects)
  2. commit phase  — React updates the DOM
  3. effect phase  — useEffect callbacks run (side effects allowed)

Cleanup: before the next effect run / on unmount.
```

### Syntax / API

```jsx
useEffect(() => {
  // runs after commit
  const id = setInterval(tick, 1000);
  return () => clearInterval(id);   // cleanup: runs before re-run & on unmount
}, [tick]);                         // dependency array
```

### Example Breakdown

- Empty deps `[]` → run once after mount.
- Deps `[x]` → re-run when `x` changes (cleanup first, then re-run).
- No deps → run after *every* render (rarely what you want).
- The cleanup function prevents leaks (intervals, subscriptions, listeners).

### Common Mistakes

- 🚨 Using `useEffect` as a substitute for event handlers (Phase 4 has the full "you should not use useEffect for everything" treatment).
- 🚨 Missing dependencies → stale closures.
- 🚨 No cleanup → memory leaks (intervals keep firing after unmount).
- 🚨 Thinking in old lifecycle terms (`didMount`/`didUpdate`) instead of "sync with data."

### When to Use It / When NOT to Use It

Effects are for **synchronizing with outside systems**: subscriptions, timers, network (with care — Phase 6), DOM APIs. Not for derived data, not for user events.

### Real-World Usage

A chat app: `useEffect` subscribes to the socket when the channel changes, cleanup unsubscribes. A map component: initialize the map on mount, destroy it on unmount.

### 🛠️ Practice

Build a clock: a component that shows the current time, updating every second, with proper cleanup. Then build one that *stops* updating when a `running` prop is false (add it to deps).

### ✅ Checkpoint

- What are the three phases of a modern component's interaction with React?
- Why does every subscription need a cleanup?

---

## 🚨 Common Beginner Mistakes (Phase 3)

- Treating re-render as a bug instead of understanding it.
- Over-memoizing before measuring.
- Changing element types in conditional rendering (destroying subtrees).
- Forgetting that inline props defeat memoization.
- No cleanup in effects → memory leaks.

---

## ✅ Phase 3 Checkpoint

### What I Should Know

- [ ] Render → reconcile → commit → paint
- [ ] Virtual DOM and the four reconciliation rules
- [ ] The four causes of re-rendering
- [ ] Why re-render ≠ DOM update
- [ ] Modern lifecycle: render, commit, effect, cleanup

### Questions

1. A parent re-renders. Does every child re-render? Does every child's DOM update? Explain.
2. Why does changing `<div>` to `<section>` at the same position destroy state?
3. What makes effects re-run? What runs before they re-run?

### Coding Challenge

Build a list of expandable rows. Expanding one row must NOT collapse others (state per row), and typing in a row's input must not lose focus when *other* rows expand. (Hint: this is about keys and reconciliation.) Use the React DevTools profiler to verify minimal re-renders.

### Design Challenge

Draw the render/commit/effect timeline for: user clicks a button → state updates → component re-renders → an effect re-runs. Label each phase and what code runs where.

### Ready to Continue?

✅ You can predict which components re-render when state changes.
✅ You experienced and explained the index-key focus bug.
✅ You can explain lifecycle in modern (hooks) terms.

---

# Phase 4 — Hooks in Depth

> **Prerequisite:** Phases 2–3. Snapshot model and render phases required.
> **Goal:** Know each core hook deeply: what it does, when to use it, when NOT to use it, and the common misuse patterns — especially the "useEffect for everything" anti-pattern.

## 4.1 The Rules of Hooks

### Concept

Two rules govern all hooks:

1. **Only call hooks at the top level** — not inside loops, conditions, or nested functions.
2. **Only call hooks from React components or custom hooks** — not plain functions.

### Why It Exists

React tracks hooks by **call order** within a component. If the order changes between renders (e.g., a conditional skips a hook), React can't match state to the right hook — leading to corrupted state.

### Mental Model

```text
Each component has a hook list: [useState#1, useState#2, useEffect#1, ...]
React matches by position, every render. Positions must be stable.
```

### Common Mistakes

- 🚨 `if (x) { useState(...) }` — violates the rules, breaks state.
- 🚨 Hooks inside `.map` callbacks or helper functions.
- 🚨 Calling a hook inside a callback (it's not during render).

### When to Use It / When NOT to Use It

The rules always apply. The lint rule `react-hooks/rules-of-hooks` catches violations — trust it.

### 🛠️ Practice

Write a custom hook `useLocalStorage(key, initial)` — a `useState` + `useEffect` combo that reads from and writes to `localStorage`. (This is the classic first custom hook.)

### ✅ Checkpoint

- Why must hook call order be stable?
- Where can hooks be called?

---

## 4.2 `useState` — Local Memory

(Deep-dived in Phase 2 §2.5. Here: the full contract.)

### Concept

```jsx
const [value, setValue] = useState(initial);
// setValue(newValue)          — replace
// setValue(prev => ...)       — compute from latest
// lazy initializer: useState(() => expensiveInit())
```

### When to Use It

Any component-local value that changes and affects rendering.

### When NOT to Use It

- Derived values (compute, don't store).
- Values only one subtree needs — push state down.
- Values needed across the app — Context/store (Phase 5).
- Values that shouldn't trigger renders — `useRef`.

### Common Mistakes

- 🚨 Storing derived state: `const [fullName, setFullName] = useState(first + last)` — now two sources of truth. Compute `const fullName = first + last`.
- 🚨 Storing props in state ("mirroring") — usually wrong; the prop is already the source of truth.

### 🛠️ Practice

Refactor a component that stores derived values in state (search filter, filtered list, totals) to derive them instead.

### ✅ Checkpoint

- When is state justified? When is it not?

---

## 4.3 `useEffect` — Synchronizing with the Outside World

### Concept

`useEffect` runs code **after** the commit, in response to dependency changes. It's for *synchronizing your component with systems outside React*: timers, subscriptions, browser APIs, network (with care), DOM libraries.

### Why It Exists

Components must be pure during render (no side effects — they'd corrupt the snapshot model). Effects are the designated place for side effects.

### Mental Model

```text
"After every render where [deps] changed, do this. Clean up before re-running."

[ ]      → once after mount
[x]      → after mount, and whenever x changes
(no dep) → after every render (almost never what you want)
```

### Syntax / API

```jsx
useEffect(() => {
  const onResize = () => setWidth(window.innerWidth);
  window.addEventListener("resize", onResize);
  return () => window.removeEventListener("resize", onResize);
}, []);
```

### Example Breakdown

- Subscribe in the effect, unsubscribe in cleanup — paired operations live together.
- Empty deps: subscribe once. Cleanup runs on unmount.

### The Big Rule: You Should Not Use `useEffect` for Everything

`useEffect` is the most misused hook. The classic incorrect patterns:

**❌ Pattern 1: Responding to user events in an effect.**

```jsx
// BAD: event handling via effect — double renders, stale values, confusing
const [name, setName] = useState("");
useEffect(() => { saveDraft(name); }, [name]);

// GOOD: call it in the handler — effects are not for events
const handleChange = (e) => { const v = e.target.value; setName(v); saveDraft(v); };
```

**❌ Pattern 2: Adjusting state during render (or "derived state via effect").**

```jsx
// BAD: setState inside an effect that depends on state → extra render, loops
useEffect(() => {
  setFiltered(filter(items));
}, [items]);

// GOOD: derive during render — no state at all
const filtered = filter(items);
```

**❌ Pattern 3: `useEffect` with `[]` that reads state (stale closure).**

```jsx
// BAD: effect captures the first render's count forever
useEffect(() => {
  setInterval(() => setCount(count + 1), 1000);  // count is stale!
}, []);
```

**❌ Pattern 4: Fetching in effects when a server component / framework data layer exists** — in Next.js, most fetching moves to the server (Phase 11). In client components, fetching in effects is legitimate but has pitfalls (Phase 6).

### Common Mistakes

- 🚨 Infinite loops: effect depends on state it also sets.
- 🚨 Missing deps → stale closures (the #1 effect bug).
- 🚨 Over-listing deps → re-running constantly.
- 🚨 Effects that could be derived data or event handlers.
- 🚨 Forgetting cleanup → leaks.

### When to Use It

External systems: subscriptions, listeners, timers, third-party DOM libs, analytics events, and *sometimes* data fetching in client components.

### When NOT to Use It

Derived values, event responses, initializing state, anything computable during render.

### Real-World Usage

- Chat: subscribe/unsubscribe to a WebSocket when `channelId` changes.
- Maps: initialize a map instance once, destroy on unmount.
- Analytics: fire a page-view event when the route changes.

### 🛠️ Practice

1. Refactor a buggy component that uses effects for events and derived state into correct code.
2. Build a component that tracks the mouse position (listener + cleanup).
3. Build a `useOnlineStatus` custom hook (online/offline via `navigator.onLine` + events).

### 🧪 Mini Challenge

Write a `useDebouncedValue(value, delay)` hook: returns `value` but only after `delay` ms of no changes. (Hint: an effect + `setTimeout` + cleanup.) Use it to debounce a search input.

### ✅ Checkpoint

- When is an effect the right tool? When is it the wrong tool?
- What are three incorrect `useEffect` patterns?
- Why do missing deps cause stale closures?

---

## 4.4 `useRef` — Mutable Values That Don't Trigger Renders

### Concept

`useRef(initial)` returns a mutable object `{ current: initial }`. Changing `.current` does **not** cause a re-render.

### Why It Exists

Two uses: (1) **references to DOM nodes** (focus, scroll, measure), (2) **mutable values you want to persist across renders without re-rendering** (timers, previous values, ids).

### Mental Model

```text
State:   changes → re-render            (for UI-visible data)
Ref:     changes → NO re-render         (for plumbing: DOM, timers, handles)
```

### Syntax / API

```jsx
const inputRef = useRef(null);
<input ref={inputRef} />
inputRef.current.focus();   // imperative DOM access

const timerRef = useRef(null);
timerRef.current = setTimeout(...);   // store handle without re-render
```

### Example (previous value pattern)

```jsx
function usePrevious(value) {
  const ref = useRef();
  useEffect(() => { ref.current = value; });
  return ref.current;   // value from the previous render
}
```

### Example Breakdown

- The effect runs after render, updating the ref with the just-committed value — so the returned value is always *one render behind*.

### Common Mistakes

- 🚨 Using refs for UI data that should be state — you change it, nothing re-renders, UI stays stale.
- 🚨 Reading/writing refs during render (except the lazy-init pattern) — unpredictable.
- 🚨 Using `useRef` when a module-level variable works (refs are per-component-instance; module vars are shared).

### When to Use It

Focus management, measuring elements, integrating non-React DOM libraries, storing timeout/subscription ids, previous values.

### When NOT to Use It

Anything that must appear in the UI — that's state's job.

### Real-World Usage

- Auto-focus a search box on mount.
- Scroll to a message in a chat when a new one arrives.
- Keep the latest callback in a ref to avoid stale closures in intervals.

### 🛠️ Practice

1. Auto-focus an input on mount. 2. Build the `usePrevious` hook. 3. Build a stopwatch using refs for the interval handle with proper cleanup.

### 🧪 Mini Challenge

Fix the stale-closure interval bug (❌ Pattern 3 above) using a ref that always holds the latest `count`, without restarting the interval.

### ✅ Checkpoint

- Ref vs state — what's the key difference?
- Two legitimate uses of refs?

---

## 4.5 `useMemo` — Cache Expensive Computations

### Concept

`useMemo(() => compute(), [deps])` caches the result of a computation, recomputing only when deps change.

### Why It Exists

If a computation is expensive and runs on every render, caching avoids wasted work. Also preserves **reference identity** so child memoization works.

### Mental Model

```text
render → is compute needed? deps changed? yes → run compute, store result.
                              deps same?  no  → return stored result.
```

### Syntax / API

```jsx
const filtered = useMemo(
  () => expensiveFilter(items, query),
  [items, query]
);
```

### Common Mistakes

- 🚨 Memoizing cheap computations (adds overhead, not savings).
- 🚨 Using it for *identity* reasons when the computation is trivial — that's sometimes valid (stable object for child memo), but say so in a comment.
- 🚨 Wrong deps → stale results. The deps must be everything the computation reads.

### When to Use It

- Genuinely expensive calculations (large data transforms, complex formatting) that run on renders where inputs didn't change.
- Creating stable objects/arrays passed to memoized children.

### When NOT to Use It

- Cheap operations: `items.filter(x => x)` on a 20-item list.
- As a general "optimization" — measure first (Phase 18).

### Real-World Usage

- Filtering/sorting thousands of rows.
- `useMemo`-ing a config object so `React.memo` children skip re-renders.

### 🛠️ Practice

Build a list of 10,000 items with a search filter. Add a `console.log` inside the filter and watch it run on *every* render before memoizing — then after. Explain the difference.

### ✅ Checkpoint

- When does `useMemo` help? When does it add cost?

---

## 4.6 `useCallback` — Stable Function References

### Concept

`useCallback(fn, deps)` returns the *same function reference* across renders until deps change.

### Why It Exists

Functions are recreated every render. If you pass a new function to a memoized child, the child re-renders (props reference changed). `useCallback` stabilizes the reference. It also stabilizes effect deps.

### Mental Model

```text
Every render creates new functions. useCallback says: "reuse the old one
unless the captured values changed."
```

### Syntax / API

```jsx
const handleToggle = useCallback((id) => {
  setTodos(prev => prev.map(t => t.id === id ? { ...t, done: !t.done } : t));
}, []);   // reads no changing values → stable forever
```

### Example Breakdown

- `setTodos(prev => ...)` reads no outer variables → `[]` deps → truly stable.
- If the callback read `query`, deps would be `[query]`.

### Common Mistakes

- 🚨 Wrapping every handler in `useCallback` — the default (recreate) is fine unless it feeds a memoized child or effect deps.
- 🚨 Forgetting deps → stale closures (the function remembers old values).
- 🚨 Using `useCallback` but passing it to a child that isn't memoized — pointless overhead.

### When to Use It

- Handlers passed to memoized children (`React.memo`).
- Functions used in effect dependency arrays (keeps effects from re-running).
- Functions used in context values (Phase 5).

### When NOT to Use It

- Default case: inline handlers.
- Children that re-render anyway.

### Real-World Usage

- A `TodoItem` memoized with `React.memo` receives `onToggle` — without `useCallback`, every parent render re-renders every row.

### 🛠️ Practice

Build a memoized `Row` component receiving `onClick`. Pass an inline handler, then a `useCallback` handler. Count renders of `Row` in both cases (add a render counter).

### ✅ Checkpoint

- What problem does `useCallback` solve?
- When is it pointless?

---

## 4.7 `useContext` — Shared Data Without Prop Drilling

> Deep treatment in Phase 5 §5.3. Quick version here.

### Concept

`useContext` reads a value provided by a `<Context.Provider>` somewhere above in the tree — no prop drilling.

### Syntax / API

```jsx
const ThemeContext = createContext("light");

function App() {
  return (
    <ThemeContext.Provider value="dark">
      <Toolbar />
    </ThemeContext.Provider>
  );
}

function Toolbar() {
  const theme = useContext(ThemeContext);  // "dark"
  return <div>Theme: {theme}</div>;
}
```

### Common Mistakes

- 🚨 Putting *everything* in one mega-Context → every consumer re-renders on any change.
- 🚨 Using Context for state that only one component needs (local state is simpler).
- 🚨 Using Context to avoid prop drilling *two levels* (fine to drill).
- 🚨 Putting unstable values (new objects/functions every render) in context → all consumers re-render.

### When to Use It

Theming, current user/auth, locale, feature flags — data that many unrelated components read.

### When NOT to Use It

High-frequency updates (a count ticking every second) that many consumers read — Context re-renders all consumers; a store with selectors may be better (Phase 5 §5.5).

### Real-World Usage

Every design system ships a ThemeProvider. Auth libraries ship a SessionProvider.

### ✅ Checkpoint

- What problem does Context solve? What problem does it create at scale?

---

## 4.8 `useReducer` — State with Logic

### Concept

`useReducer(reducer, initialState)` manages state through **actions**: `dispatch({type: "TOGGLE", id})`. The reducer is a pure function `(state, action) => newState`.

### Why It Exists

When state updates have complex logic or many related fields, scattered `setState` calls get messy. Reducers centralize the logic in one pure, testable function.

### Mental Model

```text
UI events → dispatch(action) → reducer(state, action) → new state → re-render

State changes are described as INTENTS ("TOGGLE item 3"),
not as imperative assignments ("set done to !done").
```

### Syntax / API

```jsx
function reducer(state, action) {
  switch (action.type) {
    case "ADD":
      return [...state, action.todo];
    case "TOGGLE":
      return state.map(t =>
        t.id === action.id ? { ...t, done: !t.done } : t
      );
    case "CLEAR_DONE":
      return state.filter(t => !t.done);
    default:
      return state;
  }
}

const [todos, dispatch] = useReducer(reducer, []);
// dispatch({ type: "ADD", todo: newTodo })
```

### Example Breakdown

- Reducer must be **pure**: same inputs → same output, no side effects.
- `default: return state` — an action the reducer doesn't know shouldn't crash.
- Dispatch replaces setState-call-sites with intent descriptions.

### Common Mistakes

- 🚨 Side effects inside reducers (fetching, logging) — reducers must be pure (React may call them twice in dev).
- 🚨 Mutating state inside the reducer (same reference rule as always).
- 🚨 Using `useReducer` for a single simple field — overkill.
- 🚨 Giant switch statements for 3 actions — a single `setState` with updater may be simpler.

### When to Use It

- Multiple fields updated together (a form's entire state).
- Complex update logic that deserves unit tests.
- Actions that depend on each other (undo/redo patterns).

### When NOT to Use It

Simple state: `useState` wins. Don't add ceremony without complexity.

### Real-World Usage

Forms with many fields, cart logic, game state, undo/redo, anything with a state machine feel.

### 🛠️ Practice

Convert your Phase 2 todo list to `useReducer` with actions ADD, TOGGLE, DELETE, CLEAR_DONE. Write a pure test for the reducer (just call the function in Node with sample state/actions).

### 🧪 Mini Challenge

Implement undo/redo for the todo list: keep `past`, `present`, `future` arrays in the reducer state and handle UNDO/REDO actions. This is a genuine hard exercise — design it yourself.

### ✅ Checkpoint

- What makes a reducer pure, and why must it be?
- Reducer vs useState — when do you reach for each?

---

## 4.9 Custom Hooks — Reusing Logic

### Concept

A **custom hook** is a function (named `useX`) that calls other hooks and encapsulates reusable logic.

### Why It Exists

Components reuse *UI* (composition) but logic reuse needs hooks. Custom hooks extract "fetch this, handle this, subscribe to that" into shareable units.

### Mental Model

```text
useState + useEffect + useCallback + ... = your hook's implementation
Your hook is just a function — it can take args and return anything.
```

### Example

```jsx
function useFetch(url) {
  const [data, setData] = useState(null);
  const [error, setError] = useState(null);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    let cancelled = false;
    setLoading(true);
    fetch(url)
      .then(res => res.json())
      .then(json => { if (!cancelled) setData(json); })
      .catch(err => { if (!cancelled) setError(err); })
      .finally(() => { if (!cancelled) setLoading(false); });
    return () => { cancelled = true; };
  }, [url]);

  return { data, error, loading };
}
```

### Example Breakdown

- `cancelled` flag: if the component unmounts or `url` changes before the response arrives, don't set state on a dead component.
- The hook returns a plain object — components consume `{ data, error, loading }`.
- This exact hook is a teaching example: **in Next.js you'll usually fetch on the server instead** (Phase 11).

### Common Mistakes

- 🚨 Naming without `use` prefix (breaks the rules-of-hooks linting).
- 🚨 Custom hooks that don't actually reuse hooks (then it's just a plain function).
- 🚨 One mega-hook doing 5 unrelated things.

### When to Use It

Logic used by multiple components: data fetching, auth state, media queries, localStorage, debounce, online status.

### When NOT to Use It

Logic used once — keep it inline until it's actually shared.

### Real-World Usage

The hooks ecosystem (`useSWR`, `react-query`, `react-use`) is built entirely on custom hooks.

### 🛠️ Practice

Build three custom hooks: `useFetch` (above), `useDebouncedValue`, and `useMediaQuery(query)`. Use them in a small app.

### 🧪 Mini Challenge

Write `useLocalStorage` with a twist: the value must stay in sync *across tabs* (listen to the `storage` event).

### ✅ Checkpoint

- What makes a function a custom hook?
- Why does the `cancelled` flag matter?

---

## 🚨 Common Beginner Mistakes (Phase 4)

- **Excessive `useEffect`** — using effects for events, derived state, and initialization.
- **Stale closures** — missing deps, capturing old values.
- **Infinite loops** — effect sets the state it depends on.
- **`useMemo`/`useCallback` everywhere** — premature optimization.
- **Refs for UI data** — changing a ref doesn't re-render.
- **Hooks in loops/conditions** — violates the rules.
- **No cleanup** — subscriptions and intervals leak.

---

## ✅ Phase 4 Checkpoint

### What I Should Know

- [ ] The two rules of hooks
- [ ] `useState`: initial value, functional updates, lazy init
- [ ] `useEffect`: deps, cleanup, when NOT to use it
- [ ] `useRef`: DOM refs and mutable values
- [ ] `useMemo` / `useCallback`: caching and stability
- [ ] `useContext`: shared values without drilling
- [ ] `useReducer`: actions + pure reducer
- [ ] Custom hooks

### Questions

1. Why should you not use `useEffect` to respond to a click?
2. What's the fix for the stale-closure interval bug?
3. When does `useCallback` actually help?
4. Why must reducers be pure?

### Coding Challenges

1. **Level 1:** `useDebouncedValue` + a search box that fetches after debounce.
2. **Level 2:** A `useTimer` hook (start/stop/reset) used by two different components.
3. **Level 3:** A multi-step form (Step 1, 2, 3) using `useReducer` for the whole form state, with next/back/validation. Design the state shape and actions yourself.

### Design Challenge

You're building a real-time dashboard. Which parts are state, refs, effects, context? Where does each of the 7 hooks belong? Write your design, then justify each choice.

### Ready to Continue?

✅ You can explain the anti-`useEffect` patterns and their fixes.
✅ You built `useDebouncedValue` from memory.
✅ You can choose between `useState` and `useReducer` with justification.

---

# Phase 5 — State Management

> **Prerequisite:** Phases 2–4.
> **Goal:** Decide *where state lives* with confidence — local, lifted, context, reducer, or external store — and know why each exists.

## 5.1 The State Decision Framework

### Concept

Before any state management library, learn to classify state. The single question that answers 90% of decisions:

> **Who needs this value, and when does it change?**

### The Rules of Thumb (in order of preference)

```text
1. Can it be derived from existing state/props?   → derive it (no state)
2. Is it used by one component?                    → local state (useState)
3. Is it used by a few nearby components?          → lift state to the common parent
4. Is it read by many unrelated components?        → Context (or a store)
5. Does it change extremely often / have complex   → reducer or a store with selectors
   updates across many consumers?
```

### Mental Model

```text
Local ── lift ── Context ── external store
(simple)                     (complex)

Start as simple as possible. Move up ONLY when the current level hurts.
```

### Common Mistakes

- 🚨 Jumping straight to a state library for a todo app. Start local; escalate with evidence.
- 🚨 State in the wrong component → prop drilling pain.
- 🚨 Duplicating state that should be derived (see 5.2).

### 🛠️ Practice

For a todo app, classify every piece of state: `todos`, `newTodoText`, `filter`, `filteredTodos`, `editingTodoId`. For each: local, lifted, or derived?

### ✅ Checkpoint

- What's the first question to ask about any piece of state?
- Why start with local state?

---

## 5.2 Derived State — Don't Store What You Can Compute

### Concept

If a value can be computed from other state/props during render, **compute it**. Don't store it.

### Why It Exists

Stored derived state creates **two sources of truth** that can drift out of sync (you update one, forget the other). Deriving guarantees consistency and removes update bugs entirely.

### Mental Model

```text
state:  [todos, filter]          ← the ONLY sources of truth
render: const visible = todos.filter(...)   ← derived, always correct
```

### Example

```jsx
// BAD — duplicated state, must remember to sync
const [todos, setTodos] = useState([]);
const [filtered, setFiltered] = useState([]);
useEffect(() => setFiltered(filter(todos)), [todos]);  // extra render + bug surface

// GOOD — derived, always right
const [todos, setTodos] = useState([]);
const [filter, setFilter] = useState("all");
const visible = filter === "all" ? todos : todos.filter(t => ...);
```

### Example Breakdown

- The derived version has *no* sync code, *no* effect, *no* extra render, *no* way to drift.
- If the computation is expensive, `useMemo` it (Phase 4) — but still derive it.

### Common Mistakes

- 🚨 The `useEffect`-to-sync-state anti-pattern (❌ Pattern 2 from Phase 4).
- 🚨 "Mirroring" props into state (`useState(props.x)`) — the prop is already the source of truth.

### When to Use It / When NOT to Use It

Always prefer it. Exception: expensive derivation that *must not* recompute on unrelated re-renders — `useMemo` handles that, still derived.

### 🛠️ Practice

Refactor a component with duplicated state (e.g., `items` + `total` + `expensiveItems`) into derived values.

### ✅ Checkpoint

- What problem does derived state solve?
- What's the signal that you've duplicated state?

---

## 5.3 Lifting State Up + Context

### Concept

**Lifting state** = moving state to the nearest common ancestor so siblings can share it. **Context** = providing that state to many components without prop drilling.

### Why It Exists

Siblings can't talk directly — they need a shared parent. When the tree is deep, drilling props through 6 levels is noise; Context skips the middlemen.

### Mental Model

```text
Lift:                       Context:
   App                         App
    │ state: filter            ├─ <ThemeProvider value=...>
    ├─ Sidebar ── filter ──→   ├─ Sidebar  (reads via useContext)
    └─ List ──── filter ──→   └─ List     (reads via useContext)

Lift = pass props down. Context = reach sideways/up without props.
```

### Syntax / API

```jsx
const FilterContext = createContext(null);

function App() {
  const [filter, setFilter] = useState("all");
  return (
    <FilterContext.Provider value={{ filter, setFilter }}>
      <Sidebar />
      <List />
    </FilterContext.Provider>
  );
}

// Sidebar:
const { filter, setFilter } = useContext(FilterContext);
```

### Example Breakdown

- `value={{ filter, setFilter }}` — a **new object every render**. Every consumer re-renders on every provider render. For low-frequency data (theme, user) that's fine; for hot data, memoize the value (`useMemo`/`useCallback`).
- Context doesn't have to be state — it can be any shared value (config, functions).

### Common Mistakes

- 🚨 One giant `AppContext` with everything → every consumer re-renders for any change. Split contexts by concern.
- 🚨 Context for data that changes every second with hundreds of consumers → use a store (5.5).
- 🚨 Context as a substitute for thoughtful prop design — drilling 2 levels is fine.
- 🚨 Unstable context values (new object each render) → renders cascade. Memoize.

### When to Use It

Theme, locale, current user/session, feature flags, navigation state — read by many, changes rarely.

### When NOT to Use It

- One consumer — use local state.
- High-frequency updates with many consumers — store with selectors.
- Everything — Context is not a state manager; it's a distribution mechanism.

### Real-World Usage

Auth providers (`SessionProvider`), theme providers, i18n providers — every major app has a few well-scoped providers near the root.

### 🛠️ Practice

Build a user dropdown menu (click avatar → menu) where the open/close state lives in a provider, so any button anywhere can open it. Then split it: auth context (rarely changes) vs UI context.

### 🧪 Mini Challenge

Design a Context split for an app with theme + current user + shopping cart. Justify: how many providers, what value does each hold, what re-renders when each changes.

### ✅ Checkpoint

- When do you lift state? When do you switch to Context?
- Why does a new context value object each render matter?

---

## 5.4 Reducers as State Management

### Concept

`useReducer` (Phase 4 §4.8) is a state-management pattern: all updates flow through one pure function driven by action intents.

### Why It Exists

When update logic grows (many actions, related fields, validation, undo), inline `setState` calls scatter the logic. A reducer gives you a single, testable state machine.

### Mental Model

```text
dispatch({type, payload}) → reducer(state, action) → new state

UI says WHAT happened, not HOW to change state.
```

### When to Use It / When NOT to Use It

(Recap of §4.8) Use for complex/multi-field state or logic worth unit-testing. Don't use for a boolean toggle.

### Real-World Usage

Forms (all fields in one state object), shopping carts, kanban boards, anything undoable.

### 🛠️ Practice

Redo your todo app's state with a reducer + Context combo: reducer holds todos, context distributes `state` and `dispatch` so deep components can dispatch without drilling.

### ✅ Checkpoint

- What does the reducer pattern give you that scattered setState doesn't?

---

## 5.5 External State Management (Stores) — and Why You Probably Don't Need One Yet

### Concept

Libraries like **Zustand**, **Redux** (legacy-heavy), and **Jotai** keep state in a store *outside* the component tree. Components subscribe with selectors and re-render only when their slice changes.

### Why It Exists

- Context re-renders **all consumers** when its value changes; stores can update **only subscribed selectors**.
- Stores survive outside components (usable in plain functions, workers, tests).
- Middleware/logic (persistence, devtools) is easier.

### Mental Model

```text
Context:  Provider → value change → ALL consumers re-render
Store:    store.set(...) → only components subscribed to the changed slice re-render
```

### Syntax / API (Zustand, the modern minimal choice)

```jsx
import { create } from "zustand";

const useCart = create((set) => ({
  items: [],
  addItem: (item) => set((s) => ({ items: [...s.items, item] })),
  clear: () => set({ items: [] }),
}));

function CartBadge() {
  const count = useCart((s) => s.items.length);   // subscribes to items.length
  return <span>{count}</span>;
}
```

### Example Breakdown

- The selector `(s) => s.items.length` means CartBadge re-renders only when the *length* changes — not on every store change.
- Store logic lives outside components: testable, reusable in plain code.

### Common Mistakes

- 🚨 Reaching for a store for app-wide state that Context already handles (theme, user).
- 🚨 Putting *everything* in the store (form drafts, ephemeral UI) — stores are for shared state, not local.
- 🚨 Selecting whole objects (`useStore(s => s.items)`) — you lose the fine-grained benefit; select primitives.
- 🚨 Believing Redux is the default — modern apps often need no store at all; Next.js especially (most state stays on the server, Phase 10).

### When to Use It

- State shared across many components with high-frequency updates (live data, cursors, websocket feeds).
- State needed outside React (plain functions).
- Complex cross-cutting state with middleware needs.

### When NOT to Use It

- The default. Local state + lifting + Context covers most apps.
- Next.js apps: prefer server-side state and Server Components first (Phase 10).

### Real-World Usage

Shopping carts, live dashboards, collaborative tools, websocket-driven UIs.

### 🛠️ Practice

Implement the cart from Phase 2's Level-3 challenge in Zustand. Then justify each piece of state you moved into the store vs kept local.

### 🧪 Mini Challenge

Compare Context vs Zustand for a *live-updating* order book (prices update 10×/sec, hundreds of rows). Which would you pick, and why? Write the reasoning, not the code.

### ✅ Checkpoint

- What advantage does a store have over Context, exactly?
- Why should most apps start WITHOUT a store?

---

## 5.6 Server State vs Client State (the modern split)

### Concept

**Server state** = data that lives in your database/API (todos, users, posts). **Client state** = data that lives only in the browser (form drafts, open/closed, scroll position).

### Why It Exists

They have opposite lifecycles and different needs: server state needs loading/error/caching/refetching; client state needs to be fast and local. In Next.js, server state largely lives on the **server** (Server Components / Server Actions, Phases 10–12) and client state in Client Components.

### Mental Model

```text
Server state:  fetch → cache → mutate via server → revalidate
Client state:  useState → local, ephemeral, gone on refresh

Never store a copy of server data in global client state unless you're
building an offline-first app with explicit sync rules.
```

### Common Mistakes

- 🚨 Fetching in a client component and stuffing results into Context/global state — you've reinvented a cache without the hard parts (invalidation, dedup, revalidation). In Next.js, this is usually wrong: fetch on the server instead.
- 🚨 Duplicating server data in client state (the UI and DB drift).

### When to Use It / When NOT to Use It

This is a *framework* for thinking, not a toggle. Apply it to every piece of data: "is this server state or client state?" — and the architecture follows (Phases 10–12).

### Real-World Usage

A Next.js dashboard: Server Component reads the DB (server state), passes initial data down; a Client Component holds the filter dropdown (client state) and refetches via Server Action on change.

### 🛠️ Practice

Take a CRUD app you've built and classify every piece of state as server or client. Mark which currently lives in the wrong place.

### ✅ Checkpoint

- Server state vs client state — what's the difference and why does it drive architecture?

---

## 🚨 Common Beginner Mistakes (Phase 5)

- Installing a state library before the app needs one (over-engineering).
- Excessive Context (one mega-provider, everything re-renders).
- Storing derived state (duplicated sources of truth).
- Prop drilling when Context is warranted — and Context when drilling is fine.
- Copying server data into global client state.
- Unstable context values defeating re-render expectations.

---

## ✅ Phase 5 Checkpoint

### What I Should Know

- [ ] The state decision framework (derive → local → lift → context → store)
- [ ] Derived state and why to avoid duplication
- [ ] Lifting state and when to use Context
- [ ] Reducer + Context patterns
- [ ] When an external store is justified
- [ ] Server state vs client state

### Questions

1. Walk through your decision process for a new piece of state.
2. Why is storing a derived value risky?
3. Context re-renders all consumers — when does that matter?
4. Why is a store usually unnecessary in a Next.js app?

### Coding Challenges

1. **Level 1:** Refactor a component with 4 `useState` fields that belong together into `useReducer`.
2. **Level 2:** Build a theme switcher with Context (light/dark) applied to multiple components. Add localStorage persistence.
3. **Level 3:** Build a multi-user "presence" feature: a store (Zustand) that tracks connected user names with add/remove, plus a component that renders only the count and another that renders the list — verify they re-render independently.

### Design Challenge

Design the state architecture for a settings page with: theme, language, notification prefs (per user), and a live "save status" indicator. Classify each: local/context/store/server/derived. Justify.

### Ready to Continue?

✅ You can classify any piece of state in under 30 seconds.
✅ You built the reducer + Context todo app.
✅ You can argue when (and when not) to use a store.

---

# Phase 6 — Forms & Data Fetching

> **Prerequisite:** Phases 2–5 (state, effects, async).
> **Goal:** Build production-quality forms (controlled, validated, accessible) and fetch/display data with correct loading, error, retry, and mutation UX.

## 6.1 Controlled vs Uncontrolled Inputs

### Concept

**Controlled:** the input's `value` comes from React state; typing calls the handler which updates state. **Uncontrolled:** the DOM owns the value; React reads it via a ref when needed.

### Why It Exists

Controlled inputs make React state the single source of truth — enabling validation, derived UIs, and instant feedback. Uncontrolled inputs are simpler when you don't need any of that.

### Mental Model

```text
Controlled:  state → value → input → onChange → state   (React owns it)
Uncontrolled: input owns value; you ask the DOM later via ref
```

### Syntax / API

```jsx
// Controlled
function NameForm() {
  const [name, setName] = useState("");
  return <input value={name} onChange={(e) => setName(e.target.value)} />;
}

// Uncontrolled
function NameForm() {
  const inputRef = useRef(null);
  const submit = () => console.log(inputRef.current.value);
  return <input ref={inputRef} defaultValue="" />;
}
```

### Example Breakdown

- Controlled: the input can *never* show a value React doesn't know about — no drift.
- Uncontrolled with `defaultValue` (not `value` — `value` would freeze it).

### Common Mistakes

- 🚨 Controlled input without `onChange` → frozen input (value never updates) — the classic "my input is read-only" bug.
- 🚨 Using uncontrolled inputs when you need validation/reset/derived UI.
- 🚨 A million separate `useState` calls for form fields — one form state object (or `useReducer`) is cleaner.

### When to Use It

Controlled: most real forms. Uncontrolled: file inputs, one-off forms where you only read on submit, integrating with non-React libs.

### When NOT to Use It

For every field of a 15-field form, manage one state object, not 15.

### Real-World Usage

Search-as-you-type, live validation, character counts, forms that reset, conditional fields — all controlled.

### 🛠️ Practice

Build a controlled login form (email + password) that shows a live "email looks invalid" hint. Then build the same form uncontrolled and read values on submit.

### 🧪 Mini Challenge

Build a "custom select" — a button that opens a list; clicking an option updates the visible label. This is a controlled component in disguise: think about `value` + `onChange` + `open` state.

### ✅ Checkpoint

- Why does a controlled input need `onChange`?
- When would you prefer uncontrolled?

---

## 6.2 Form Submission and Validation

### Concept

Handle `onSubmit` (not button `onClick`), prevent the default page reload, validate before/while submitting, and surface errors clearly.

### Why It Exists

Forms are where users give you data — the most error-prone UI. Correct submission + clear validation = trust.

### Mental Model

```text
type → validate (live) → submit → validate again → send → handle response
                                    ↓ error? show it, keep values
```

### Syntax / API

```jsx
function LoginForm({ onSubmit }) {
  const [values, setValues] = useState({ email: "", password: "" });
  const [errors, setErrors] = useState({});
  const [submitting, setSubmitting] = useState(false);

  const validate = (v) => {
    const errs = {};
    if (!v.email.includes("@")) errs.email = "Invalid email";
    if (v.password.length < 8) errs.password = "Min 8 characters";
    return errs;
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    const errs = validate(values);
    if (Object.keys(errs).length) return setErrors(errs);
    setSubmitting(true);
    try {
      await onSubmit(values);
    } finally {
      setSubmitting(false);
    }
  };

  return (
    <form onSubmit={handleSubmit} noValidate>
      <input
        value={values.email}
        onChange={(e) => setValues({ ...values, email: e.target.value })}
        aria-invalid={!!errors.email}
      />
      {errors.email && <p role="alert">{errors.email}</p>}
      <button disabled={submitting}>{submitting ? "Saving…" : "Login"}</button>
    </form>
  );
}
```

### Example Breakdown

- `e.preventDefault()` — stop the browser's native reload.
- `noValidate` — disable native validation so *your* UX runs.
- Validate in the submit handler; show errors with `aria-invalid` + `role="alert"` (accessibility, Phase 16).
- Disable the button while submitting; show progress text (prevents double submits).

### Common Mistakes

- 🚨 `onClick` on the submit button instead of `onSubmit` on the form (Enter key breaks).
- 🚨 Forgetting `preventDefault` → page reloads, state lost.
- 🚨 Not disabling during submit → duplicate submissions.
- 🚨 Validating only client-side — **client validation is UX, not security** (Phase 17).
- 🚨 Blocking submit on any error vs letting the user fix what's shown — keep it simple and clear.

### When to Use It / When NOT to Use It

All forms. For huge forms (wizards, 30+ fields), consider a library (`react-hook-form`) — but only when your hand-rolled version gets painful.

### Real-World Usage

Signup, login, settings, checkout, search filters — every form in every product follows this skeleton.

### 🛠️ Practice

Build a signup form (name, email, password, confirm) with: live validation on blur, submit-time validation, error display, disabled-while-submitting, and a success state. Don't use a library.

### 🧪 Mini Challenge

Add "async validation": check whether an email is already taken by calling a fake API (`new Promise(res => setTimeout(() => res(takenEmails.includes(v)), 500))`) when the email field blurs. Handle race conditions (typing fast, stale responses).

### ✅ Checkpoint

- Why `onSubmit` and not button `onClick`?
- Why is client validation insufficient alone?

---

## 6.3 Data Fetching in Client Components (the classic pattern)

### Concept

Fetching with `fetch` + `async/await` in a client component, managing three states: **loading, error, data**. (In Next.js, much of this moves to the server — Phase 11 — but you must know the client pattern: it's still used for client-side mutations, refetches, and third-party APIs.)

### Why It Exists

The UI must show *something* while waiting, handle failure gracefully, and render data when it arrives.

### Mental Model

```text
mount → loading → success: data   → render
                → failure: error  → show + allow retry
```

### Syntax / API

```jsx
function UserList() {
  const [users, setUsers] = useState(null);
  const [error, setError] = useState(null);
  const [loading, setLoading] = useState(true);

  const load = useCallback(async () => {
    setLoading(true);
    setError(null);
    try {
      const res = await fetch("/api/users");
      if (!res.ok) throw new Error(`HTTP ${res.status}`);
      setUsers(await res.json());
    } catch (err) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  }, []);

  useEffect(() => { load(); }, [load]);

  if (loading) return <Skeleton />;
  if (error) return <ErrorView message={error} onRetry={load} />;
  return <List data={users} />;
}
```

### Example Breakdown

- Loading/error/data as three distinct states — never render "empty list" for "still loading".
- `load` is `useCallback`-stable so the effect runs once.
- `!res.ok` check — remember, fetch doesn't throw on 4xx/5xx.
- A `load` function reusable as the retry handler.

### Common Mistakes

- 🚨 No loading state → flash of empty UI.
- 🚨 No error state → blank page + silent console error.
- 🚨 No retry.
- 🚨 Setting state after unmount (the `cancelled` flag pattern, Phase 4 §4.9).
- 🚨 Race conditions: two requests, older one resolves last → wrong data. Guard by comparing the latest request or using an AbortController.
- 🚨 Re-fetching on every render because deps are wrong.

### When to Use It

Client components needing data: third-party APIs, real-time data, data that must refetch on user action.

### When NOT to Use It

In Next.js: data you can fetch on the server (Phase 11) — you get caching, no loading flash, and no client bundle for the fetch.

### Real-World Usage

Live dashboards (websockets/polling), search-as-you-type hitting an external API, user-triggered refetches.

### 🛠️ Practice

Build the three-state fetch pattern for a public API (`jsonplaceholder`). Add a retry button and a refresh button. Then add an AbortController so navigating away cancels in-flight requests.

### 🧪 Mini Challenge

Build a `useFetch` hook (from Phase 4 §4.9) and extend it with **pagination**: `fetchPage(url, page)` that keeps old data visible while loading the next page and merges results. Handle the race where the user clicks page 1 then page 2 quickly.

### ✅ Checkpoint

- What are the three states of a fetch?
- Why check `res.ok`?
- What's the unmount race, and how do you prevent it?

---

## 6.4 Optimistic Updates

### Concept

Apply the UI change **immediately** (before the server confirms), then reconcile: keep it if the request succeeds, roll back (or mark failed) if it fails.

### Why It Exists

Networks are slow; users perceive latency. Optimistic UI feels instant. Done right, it's the difference between "snappy" and "laggy."

### Mental Model

```text
action → update UI now → send request → success: done
                                       → failure: revert + notify
```

### Example

```jsx
const toggleTodo = async (todo) => {
  const prev = todos;
  setTodos(prev.map(t => t.id === todo.id ? { ...t, done: !t.done } : t)); // instant
  try {
    await api.toggle(todo.id);
  } catch {
    setTodos(prev);            // roll back
    notify("Failed to update");
  }
};
```

### Common Mistakes

- 🚨 No rollback → UI lies about server state.
- 🚨 Optimistic updates for destructive/non-idempotent actions (deleting, payments) without extreme care.
- 🚨 Racing mutations (two toggles while the first is in flight) — queue or reconcile carefully.

### When to Use It

Likes, toggles, quick edits — low-risk, high-frequency.

### When NOT to Use It

Payments, anything where the server result matters (you must show the *real* result), actions with side effects.

### Real-World Usage

Twitter/X likes, Gmail send ("sending…" → sent), todo checkboxes.

### 🛠️ Practice

Add optimistic toggling + rollback to your todo app. Then add optimistic *add* with a temporary id, replacing it with the server id on success.

### ✅ Checkpoint

- When is optimistic UI safe? When is it dangerous?

---

## 6.5 Pagination and Infinite Scrolling

### Concept

**Pagination** — fetch page N, show page controls. **Infinite scroll** — append the next page when the user reaches the bottom. Both keep payloads bounded.

### Why It Exists

Fetching 100,000 rows at once is slow and wasteful. Bounded pages = fast loads, less memory.

### Mental Model

```text
Pagination:   page state + page size → fetch → render slice → controls
Infinite:     list state + nextCursor → fetch → append → sentinel triggers next
```

### Common Mistakes

- 🚨 Fetching everything and paginating *client-side* for large datasets (defeats the purpose). Server-side pagination (Phase 15 API design).
- 🚨 Infinite scroll without a loading/end sentinel → confusing UX.
- 🚨 Off-by-one bugs: total pages, last page, cursor-based vs page-based.
- 🚨 Losing scroll position when navigating back (real-world pain; requires scroll restoration).

### When to Use It

Lists beyond ~50 items. Infinite scroll for feeds (engagement), pagination for data tables (control).

### When NOT to Use It

Tiny lists. And pagination for feeds feels dated — pick per use-case.

### Real-World Usage

Admin tables (paginated), social feeds (infinite), search results (paginated), chat history ("load older").

### 🛠️ Practice

1. Build a paginated users table (page state, prev/next, page numbers, disabled states).
2. Build an infinite scroll list with an IntersectionObserver sentinel.

### 🧪 Mini Challenge

Implement cursor-based pagination: the API returns `{ items, nextCursor }` where `nextCursor` is `null` on the last page. Design the state shape and the "has more" logic yourself.

### ✅ Checkpoint

- When pagination vs infinite scroll?
- Why server-side pagination for big data?

---

## 🚨 Common Beginner Mistakes (Phase 6)

- Controlled input without `onChange` (frozen input).
- Forgetting `preventDefault`.
- Client-only validation (UX yes, security no).
- Missing loading/error/retry states.
- Not checking `res.ok`.
- Setting state after unmount.
- Optimistic updates without rollback.
- Fetching everything for a huge list.

---

## ✅ Phase 6 Checkpoint

### What I Should Know

- [ ] Controlled vs uncontrolled inputs
- [ ] Form submission flow + validation
- [ ] The three-state fetch pattern
- [ ] Abort/race handling
- [ ] Optimistic updates + rollback
- [ ] Pagination vs infinite scroll

### Questions

1. What's the difference between a controlled and uncontrolled input, and when is each right?
2. Why is client-side validation not security?
3. Walk through the states your UI shows during a fetch.
4. When should you NOT do optimistic updates?

### Coding Challenges

1. **Level 1:** A search box with debounce that fetches results and shows loading/error/empty states.
2. **Level 2:** A form (create todo) + list (fetch todos) in one app — client-side only, with optimistic add.
3. **Level 3:** A paginated + filterable + sortable data table consuming a fake API (in-memory store with artificial delay). Design the API contract and the component tree.

### Design Challenge

Design the loading/error/empty/success states for a dashboard with 4 data panels. What does each panel show in each state? Where do skeletons live? Write it as a state matrix.

### Ready to Continue?

✅ You built the three-state fetch pattern from memory.
✅ You built debounced search.
✅ You can explain optimistic updates and their risks.

---

# Phase 7 — TypeScript for React

> **Prerequisite:** Phases 2–6 (React fundamentals). Basic JS types.
> **Goal:** Use TypeScript as a *practical tool* for React/Next.js apps: type your data, props, events, and APIs — without turning this into a full TypeScript course.

## 7.1 What TypeScript Is and Why It Matters for React

### Concept

TypeScript = JavaScript + static types. Types are checked at compile time, then erased — the runtime is still JavaScript.

### Why It Exists

React apps are full of objects, callbacks, and async data — the classic sources of runtime bugs (typos in prop names, `undefined` access, wrong shapes from APIs). Types catch these **before** you run the app, and they document the code for free.

### Mental Model

```text
TS compiles:  .ts/.tsx → type-check → emit .js

Types are COMPILE-TIME only. They don't exist at runtime.
Anything type-only (interfaces, generics) is erased.
```

### Common Mistakes

- 🚨 Using `any` everywhere → you've disabled the safety net. `any` is a code smell (except at genuine boundaries).
- 🚨 Believing types make runtime validation unnecessary. **Types don't validate data coming from the network** — a malformed API response is still a runtime problem.
- 🚨 Fighting the compiler instead of listening to it. 95% of the time, a type error is telling you about a real bug or a real edge case.

### When to Use It / When NOT to Use It

Use it for anything non-trivial. TypeScript is the default in modern Next.js — `create-next-app` sets it up for you.

### Real-World Usage

Prop contracts in shared components (your Button's props are its API), API response types shared between server and client, discriminated unions for multi-state UI.

### 🛠️ Practice

Install TypeScript in a scratch project (or use `tsc --init`). Write a JS file, then rename to `.ts` and fix the errors TypeScript finds.

### ✅ Checkpoint

- What does TypeScript do at compile time? At runtime?
- Why is `any` dangerous?

---

## 7.2 Primitives, Arrays, Objects, Unions

### Concept

```ts
type UserId = number;
const name: string = "Ada";
const ids: number[] = [1, 2, 3];
const pair: [string, number] = ["Ada", 36];      // tuple

// Objects
const user: { id: number; name: string } = { id: 1, name: "Ada" };

// Unions — "one of these"
type Status = "pending" | "active" | "done";
const s: Status = "active";

// Union of shapes — discriminated union (very useful in React)
type Result =
  | { kind: "loading" }
  | { kind: "error"; message: string }
  | { kind: "success"; data: User };
```

### Why It Exists

Unions model real choices (loading/error/success!). Discriminated unions (a `kind` field that distinguishes) are the idiomatic way to model UI states and API results.

### Common Mistakes

- 🚨 `string` for everything — a `Status` union catches typos (`"pendin"`) at compile time.
- 🚨 Not narrowing before accessing fields.

### 🛠️ Practice

Model: a task (`id`, `title`, `status: "todo"|"doing"|"done"`, `dueDate?: string`). Then model a fetch result as a discriminated union.

### ✅ Checkpoint

- What is a union? A discriminated union? Why use them in React?

---

## 7.3 Interfaces vs Type Aliases

### Concept

Both describe object shapes. `interface` can be *extended* and *merged*; `type` can express everything (unions, intersections, mapped types).

### Syntax

```ts
interface User {
  id: number;
  name: string;
}

interface Admin extends User {      // inheritance
  permissions: string[];
}

type User = { id: number; name: string };   // same shape as a type

type A = { a: string } & { b: number };     // intersection
type U = string | number;                    // union (types only)
```

### Common Mistakes

- 🚨 Worrying about which to use — either is fine. Rule of thumb: `interface` for object shapes (especially when extended/merged), `type` for unions, intersections, and anything else.

### 🛠️ Practice

Model `BaseEntity` (id, createdAt) and extend it for `Post` and `Comment`. Then model `Filter = "all" | "active" | "done"` as a type.

### ✅ Checkpoint

- When would you choose `type` over `interface`?

---

## 7.4 Optional Properties and Null/Undefined

### Concept

```ts
interface User {
  id: number;
  email?: string;          // optional — may be absent
  bio: string | null;      // explicitly nullable
}

const u: User = { id: 1, bio: null };          // ✅ email omitted
console.log(u.email?.toUpperCase());            // safe
const len: number = u.bio?.length ?? 0;         // ?? for defaults
```

### Why It Exists

APIs return partial data; UI has genuinely-missing fields. Types make you *handle* absence instead of crashing on it.

### Common Mistakes

- 🚨 Confusing `?` (optional) with `| null` (nullable). Optional = property may not exist; nullable = it exists but can be `null`.
- 🚨 Ignoring `strictNullChecks` (default in modern setups) — turn it off and you've removed the safety.

### 🛠️ Practice

Type an API response where `profile.avatarUrl` is optional and `profile.age` can be null. Write code that uses both safely.

### ✅ Checkpoint

- Optional vs nullable — difference?

---

## 7.5 Function Types, Generics, Utility Types

### Concept

```ts
// Function type
const handler: (id: number) => void = (id) => {};

// Generics — reusable with type parameters
function first<T>(arr: T[]): T | undefined {
  return arr[0];
}
const f = first(["a", "b"]);   // string | undefined

// Common utility types
interface User { id: number; name: string; email: string; password: string; }

type PublicUser = Omit<User, "password">;       // remove fields
type PartialUser = Partial<User>;                // all optional
type PickName = Pick<User, "name">;             // subset
type UserWithoutId = Omit<User, "id">;          // for creation payloads
type Dict = Record<string, number>;              // index signature
```

### Why It Exists

Generics let one function serve many types (React's own types are generic: `useState<T>`, `ComponentProps<T>`). Utility types express common transformations without hand-writing them.

### Common Mistakes

- 🚨 Hand-writing types that `Omit`/`Pick`/`Partial` produce.
- 🚨 `as` casts to silence the compiler — usually a sign you're lying to it. Prefer narrowing and guards.

### 🛠️ Practice

1. Write a generic `getById<T>(items: T[], id: string): T | undefined`.
2. Given `ApiUser`, create: creation payload, update payload (all optional), public user (no password). Use only utility types.

### ✅ Checkpoint

- What does `Omit` do? When would you use `Partial`?
- Why are generics essential for React types?

---

## 7.6 Type Narrowing and Type Guards

### Concept

**Narrowing** = TypeScript shrinks a type based on checks (`if (x !== undefined)`, `typeof`, discriminated unions). **Type guards** = functions that tell TypeScript "this is that type."

### Why It Exists

After a check, TS knows more — and you can access fields safely. Discriminated unions + narrowing = the pattern for UI state.

### Syntax

```ts
type Result =
  | { kind: "loading" }
  | { kind: "error"; message: string }
  | { kind: "success"; data: User };

function render(r: Result) {
  switch (r.kind) {
    case "loading": return <Spinner />;
    case "error":   return <p>{r.message}</p>;   // narrowed: has message
    case "success": return <Profile user={r.data} />;  // narrowed: has data
  }
}

// Custom guard
function isUser(x: unknown): x is User {
  return typeof x === "object" && x !== null && "id" in x;
}
```

### Example Breakdown

- The `switch` on `kind` narrows each case — TS knows `message` only exists on `error`.
- `x is User` is a **type predicate**: if the function returns true, TS treats `x` as `User` afterwards.

### Common Mistakes

- 🚨 Not narrowing before property access → TS errors you try to silence with `as`.
- 🚨 Guards that lie (`x is User` that returns true for anything) — predicates must match reality.

### 🛠️ Practice

Model `{ status, data?, error? }` and render each status with narrowing. Then write an `isTask` guard and use it on `unknown` data from a JSON parse.

### ✅ Checkpoint

- What does narrowing mean? What's a type predicate?

---

## 7.7 React-Specific Types (the ones you actually use)

### The core set:

```tsx
// Props
interface ButtonProps {
  variant?: "primary" | "secondary";
  size?: "sm" | "md" | "lg";
  disabled?: boolean;
  onClick?: () => void;
  children: React.ReactNode;
}

// useState with a type
const [user, setUser] = useState<User | null>(null);

// useRef
const inputRef = useRef<HTMLInputElement>(null);   // for DOM refs
const timer = useRef<number | null>(null);          // for values

// Events — let TS infer, don't hand-write
const handleChange = (e: React.ChangeEvent<HTMLInputElement>) => {
  setValue(e.target.value);
};

// Forms
interface LoginForm {
  email: string;
  password: string;
}

// async results
const [result, setResult] = useState<Result>();

// children & elements
function Card({ children }: { children: React.ReactNode }) { ... }

// ComponentProps — grab a native element's props
const inputProps: React.ComponentProps<"input"> = { type: "text", ... };
```

### Why It Exists

React's types (in `@types/react`) encode props contracts, event shapes, and hook generics. Using them means the compiler checks your component's *public API*.

### Common Mistakes

- 🚨 Hand-typing event objects instead of letting inference work (`onChange={(e) => ...}` infers `e` for you).
- 🚨 `useRef<HTMLInputElement>(null)` then forgetting the `null` check: `inputRef.current?.focus()`.
- 🚨 Using `React.FC` (legacy) — modern code just types props directly.
- 🚨 `children: React.ReactNode` vs `JSX.Element` — `ReactNode` is the general one (string, number, fragment, array, null).

### When to Use It

Every component you write — typed props are the API of your component library.

### Real-World Usage

Shared component libraries rely on typed props so consumers get autocomplete + errors. Design systems are unusable without them.

### 🛠️ Practice

Type every component you've built so far (Button, Card, TodoItem, forms). Where does `ReactNode` belong? Where do unions belong? Where does `User | null` belong?

### 🧪 Mini Challenge

Type a polymorphic component: a `Button` that can render as `<button>` or `<a>` based on an `as` prop, with the correct props for each (hint: `React.ComponentProps<"button"> & React.ComponentProps<"a">` — or a union with narrowing).

### ✅ Checkpoint

- What is `ReactNode`? When do you use it?
- Why let TS infer event types?

---

## 7.8 Typing API Responses

### Concept

Define a type for every API response, and write a typed fetch helper.

### Why It Exists

The API boundary is where runtime reality meets compile-time types. A typed `api` module keeps your data shapes consistent and catches drift when the API changes.

### Example

```ts
interface Todo {
  id: string;
  title: string;
  done: boolean;
}

async function fetchTodos(): Promise<Todo[]> {
  const res = await fetch("/api/todos");
  if (!res.ok) throw new Error(`HTTP ${res.status}`);
  return res.json();   // ⚠️ typed as Todo[] but NOT validated at runtime
}
```

### Example Breakdown

- The return type documents the contract and flows into callers.
- The ⚠️ note is important: `res.json()` returns `any` — you're *asserting* it's `Todo[]`. For critical boundaries, validate at runtime (zod — see 7.9) or at least trust it consciously.

### Common Mistakes

- 🚨 Typing responses as `any` and losing the safety.
- 🚨 Defining the same shape in 5 files — centralize types in a `types/` module shared by server and client (in Next.js, one type file used by both! Phase 12).

### 🛠️ Practice

Create an `api.ts` module with typed functions for a CRUD resource: `list`, `get`, `create`, `update`, `remove`. All typed, all checking `res.ok`.

### ✅ Checkpoint

- Why are API responses a boundary where types need care?

---

## 7.9 Bonus: Runtime Validation with Zod (a preview)

### Concept

**Zod** validates data *at runtime* and infers the TypeScript type from the schema. It solves the gap from 7.8: types that are actually checked.

### Why It Exists

Types are compile-time; the network is runtime. Zod schemas are both: parse incoming data and get a *guaranteed* typed result.

### Example

```ts
import { z } from "zod";

const TodoSchema = z.object({
  id: z.string(),
  title: z.string().min(1),
  done: z.boolean(),
});

type Todo = z.infer<typeof TodoSchema>;   // the type is derived

const parsed = TodoSchema.parse(await res.json());  // throws if malformed
```

### Why It Matters in Next.js

Zod is the standard for validating **Server Action inputs** and **route handler bodies** (Phases 11–12). You'll see it constantly in real codebases.

### When to Use It / When NOT to Use It

Use at trust boundaries: API input, form submission, env vars. Don't validate your own internal state (already trusted).

### 🛠️ Practice

Write Zod schemas for a user signup payload and a todo. Validate a good payload and a bad one — observe the error messages.

### ✅ Checkpoint

- Types vs runtime validation — what's the gap Zod fills?

---

## 🚨 Common Beginner Mistakes (Phase 7)

- `any` everywhere (safety off).
- `as` casts to silence errors instead of narrowing.
- No runtime validation at API boundaries.
- Hand-typing events instead of inferring.
- `React.FC`, `JSX.Element` misuse, missing `ReactNode`.
- One `types.ts` that's actually five duplicated shapes.

---

## ✅ Phase 7 Checkpoint

### What I Should Know

- [ ] Primitives, arrays, objects, tuples
- [ ] Unions and discriminated unions
- [ ] `interface` vs `type`
- [ ] Optional vs nullable
- [ ] Generics and utility types (`Omit`, `Pick`, `Partial`)
- [ ] Narrowing and type guards
- [ ] React types: props, events, hooks, `ReactNode`
- [ ] Typed API layers + runtime validation concepts

### Questions

1. Why can't types protect you from a malformed API response?
2. What's a discriminated union, and why is it ideal for UI state?
3. When do you use `Omit`?
4. Why is `any` dangerous in a shared component's props?

### Coding Challenges

1. **Level 1:** Type a `Task` model and a `TaskListProps` interface; render a typed list.
2. **Level 2:** Type the full todo CRUD API module from 6.3 with proper response types and error handling.
3. **Level 3:** Model a multi-step form state as a discriminated union (`step: "contact" | "billing" | "review"`) with per-step data. Type every action. This is a real architecture pattern.

### Design Challenge

Design the type system for a blog: `Post`, `Author`, `Comment`, plus `PostCreate` (omit id/createdAt), `PostUpdate` (partial), `CommentCreate`. Where do you put shared types so server and client use the same file?

### Ready to Continue?

✅ You typed your existing components without `any`.
✅ You can explain the compile-time vs runtime gap.
✅ You built a typed API module.

---

# Phase 8 — Next.js Fundamentals

> **Prerequisite:** Phases 2–7 (React + TypeScript). You should be comfortable building components and fetching data.
> **Goal:** Understand what Next.js is, why it exists, and how a Next.js project is structured — before diving into routing.

## 8.1 What Next.js Is (and Why It Exists)

### Concept

**Next.js** is a React framework that adds what React alone doesn't provide: routing, server rendering, file conventions, data fetching primitives, optimization, and a build system — all with sensible defaults.

### Why It Exists

Plain React leaves big decisions to you: *Who renders the HTML? How do pages route? How do I optimize images? How do I fetch data without a loading flash?* Next.js answers these with conventions and defaults, so you build features instead of plumbing.

### Mental Model

```text
React = the UI library (components, state, rendering)
Next.js = the application framework (routing, rendering strategy, data, deployment)

React answers "how do I draw this UI?"
Next.js answers "how does this app live on the web?"
```

### The Big Idea: One Framework, Many Rendering Strategies

Remember the CSR/SSR/SSG table from Phase 0? Next.js lets you choose per page:

| Strategy | When HTML is generated | Use when |
|---|---|---|
| **Static** (SSG) | at build time | content that rarely changes (blog posts, docs) |
| **Dynamic** (SSR) | per request | personalized, always-fresh data (dashboard) |
| **Client** | in the browser | highly interactive islands |

Modern Next.js (App Router) makes this automatic: the *framework* decides based on how you fetch data — no `getStaticProps` ceremony. You'll see exactly how in Phase 11.

### Common Mistakes

- 🚨 Treating Next.js as "just React with extra steps." Its rendering model (Server Components) changes *where* your code runs — that's Phase 10.
- 🚨 Assuming everything runs in the browser. In Next.js, components run on the server by default.
- 🚨 Learning legacy (Pages Router) tutorials — the modern path is the App Router. Pages Router is labeled **legacy**; skip it.

### When to Use It / When NOT to Use It

Use Next.js for anything production-oriented: it gives you SEO, performance, and deployment wins for free. A purely client-side SPA is possible without it, but you'd be re-building routing and SSR yourself.

### Real-World Usage

Vercel's own dashboard, thousands of SaaS products, e-commerce, content sites — Next.js is the most common React framework in production.

### 🛠️ Practice

Run `npx create-next-app@latest` (TypeScript, App Router, ESLint, Tailwind). Start the dev server, look at the generated project, and read `package.json` to see what's included. Do NOT delete anything yet.

### ✅ Checkpoint

- What does Next.js add on top of React?
- What are the three rendering strategies, and when is each appropriate?

---

## 8.2 The Next.js Project Structure

### Concept

The App Router project layout:

```text
my-app/
 ├── app/                    ← your routes live here (file-based routing)
 │    ├── layout.tsx         ← root layout (html, body, global nav)
 │    ├── page.tsx           ← the / route
 │    ├── globals.css
 │    └── ...
 ├── components/             ← your components (convention, not required)
 ├── lib/                    ← shared logic, utilities
 ├── public/                 ← static assets served at /
 ├── package.json
 ├── next.config.ts
 ├── tsconfig.json
 └── .env.local              ← local secrets (gitignored!)
```

### Why It Exists

File-based routing means *files = routes* — no router config to maintain. Conventions (special file names) tell Next.js what each file *is*.

### The Special Files (memorize these)

| File | Purpose |
|---|---|
| `layout.tsx` | Wraps children; persists across navigation |
| `page.tsx` | The page content for a route |
| `loading.tsx` | Shown while the page loads (Suspense boundary) |
| `error.tsx` | Error boundary for the route segment |
| `not-found.tsx` | 404 UI for the route |
| `route.ts` | API route handler (no UI) |

### Common Mistakes

- 🚨 Putting components in `app/` — `app/` is for *routes*, not component libraries. Components live elsewhere (commonly `components/`).
- 🚨 Naming files wrong (`pages.tsx` instead of `page.tsx`) — silently ignored or errors.
- 🚨 Committing `.env.local` — it holds secrets (Phase 17).

### 🛠️ Practice

In your fresh project: change the root `page.tsx`, add a `components/Header.tsx`, import it in the layout, and add a second route (`app/about/page.tsx`). Navigate between `/` and `/about` with `<Link>` (Phase 9).

### ✅ Checkpoint

- What do `layout.tsx` and `page.tsx` do?
- Where do reusable components go, and why not in `app/`?

---

## 8.3 The App Router vs the Pages Router (legacy)

### Concept

The **Pages Router** (pre-2023) used `pages/` with `getServerSideProps`/`getStaticProps`. The **App Router** (current) uses `app/`, layouts, Server Components, and Server Actions.

### Why the App Router Exists

The Pages Router forced a client-first model: every page shipped JavaScript that fetched data in the browser. The App Router flips it: **components run on the server by default**, streaming HTML, with granular loading states.

### Mental Model

```text
Pages Router (legacy):  page component (client) → fetch in useEffect → render
App Router (modern):    page component (server) → read DB directly → render HTML
```

### Common Mistakes

- 🚨 Following 2021–2022 tutorials that teach `getServerSideProps`, `_app.tsx`, `next/router`. They're legacy. Modern docs live at `nextjs.org/docs/app`.
- 🚨 Searching "Next.js API routes" and landing on `pages/api` patterns when the modern answer is Route Handlers in `app/` (Phase 12).

### When to Use It / When NOT to Use It

Always use the App Router for new projects. Only touch Pages Router to maintain legacy apps.

### Real-World Usage

Next.js 15+ default; all current documentation, courses, and templates target the App Router.

### 🛠️ Practice

Read the official App Router overview (`nextjs.org/docs/app`) for 30 minutes. Skim, don't memorize — you'll internalize it across the next phases.

### ✅ Checkpoint

- How do you tell whether a tutorial/course is teaching the modern App Router?

---

## 🚨 Common Beginner Mistakes (Phase 8)

- Learning the Pages Router from old tutorials.
- Putting non-route files in `app/`.
- Committing `.env.local`.
- Assuming all components run in the browser.

---

## ✅ Phase 8 Checkpoint

### What I Should Know

- [ ] What Next.js adds over React
- [ ] The three rendering strategies
- [ ] The App Router file conventions
- [ ] Why the App Router replaced the Pages Router

### Questions

1. What problem does Next.js solve that React alone doesn't?
2. Why does it matter *where* (server vs client) your component runs?
3. What are the special files in `app/` and their jobs?

### Coding Challenge

Create a fresh App Router project. Build a two-page site (Home + About) with a shared header in the root layout and a link between pages. No solution — explore the generated code and docs as needed. This is your first real Next.js app.

### Ready to Continue?

✅ You created and ran a Next.js project.
✅ You can name the special files and their roles.
✅ You know why the App Router is the modern choice.

---

# Phase 9 — The App Router: Pages, Layouts, and Navigation

> **Prerequisite:** Phase 8.
> **Goal:** Build real multi-page apps with nested layouts, dynamic routes, loading/error states, and client-side navigation.

## 9.1 Routes, Pages, and Nested Layouts

### Concept

Folders under `app/` become URL segments; `page.tsx` is the content of a route; `layout.tsx` wraps all child routes and **persists across navigation**.

### Why It Exists

Nested layouts solve a real problem: your header/sidebar/footer must survive page changes without re-fetching or re-rendering. The layout hierarchy mirrors the URL hierarchy.

### Mental Model

```text
app/
 ├── layout.tsx          → wraps EVERYTHING (html, body, global nav)
 ├── page.tsx            → /
 ├── dashboard/
 │    ├── layout.tsx     → wraps all /dashboard/* pages (sidebar!)
 │    ├── page.tsx       → /dashboard
 │    └── settings/
 │         └── page.tsx  → /dashboard/settings

URL /dashboard/settings renders:
  root layout → dashboard layout (sidebar) → settings page

Layouts persist: navigating /dashboard → /dashboard/settings
keeps the sidebar mounted (no re-render, no re-fetch).
```

### Syntax / API

```tsx
// app/layout.tsx — the root layout
import type { Metadata } from "next";

export const metadata: Metadata = {
  title: "My App",
  description: "...",
};

export default function RootLayout({ children }: { children: React.ReactNode }) {
  return (
    <html lang="en">
      <body>
        <Header />
        {children}
      </body>
    </html>
  );
}
```

```tsx
// app/dashboard/layout.tsx — nested layout with a sidebar
import Sidebar from "@/components/Sidebar";

export default function DashboardLayout({ children }: { children: React.ReactNode }) {
  return (
    <div className="flex">
      <Sidebar />
      <main>{children}</main>
    </div>
  );
}
```

### Example Breakdown

- The root layout **must** render `<html>` and `<body>` — only one root layout exists.
- `{children}` is where the child route's content is injected.
- Layouts don't re-render on navigation between their children — that's the performance win.

### Common Mistakes

- 🚨 Adding a second `<html>` in a nested layout (only the root layout has it).
- 🚨 Putting `metadata` export in a Client Component — metadata is server-only (Phase 10).
- 🚨 Creating a layout when you just need a shared *component* — layouts affect navigation/re-render behavior; a wrapper component may be simpler.

### When to Use It / When NOT to Use It

Use layouts for persistent chrome (nav, sidebar, footer). For transient wrappers, use components.

### Real-World Usage

Every SaaS app: root layout = header/footer; `(dashboard)` route group = authenticated shell with sidebar; admin section = its own layout.

### 🛠️ Practice

Build: root layout with header, `(marketing)` pages (home, pricing) without the app chrome, and `(app)` pages (dashboard, settings) with a sidebar layout. Use **route groups** — parentheses folders that don't affect the URL (Phase 9.4).

### 🧪 Mini Challenge

Why would you want *two different* layouts for marketing vs app pages, and how do route groups make that possible? Answer before reading 9.4.

### ✅ Checkpoint

- What persists across navigation: layouts or pages?
- Which layout renders `<html>`?

---

## 9.2 Dynamic Routes

### Concept

`[param]` folders create dynamic segments. `app/blog/[slug]/page.tsx` matches `/blog/hello-world`. `[...catchAll]` matches any depth; `[[...optional]]` matches zero too.

### Why It Exists

Real apps have infinite URLs (posts, users, products). One template handles them all.

### Syntax / API

```tsx
// app/blog/[slug]/page.tsx
export default async function PostPage({ params }: { params: Promise<{ slug: string }> }) {
  const { slug } = await params;          // Next.js 15: params is a Promise
  const post = await getPost(slug);       // server-side fetch
  return <article>{post.title}</article>;
}
```

### Example Breakdown

- `params` gives you the dynamic segment values.
- The page is `async` — it fetches on the server (Phase 11) and streams the HTML.
- Next.js 15 wraps `params` in a Promise — `await params` (check the docs for your version).

### Common Mistakes

- 🚨 Forgetting to `await params` (Next.js 15+) — you get a Promise, not the value.
- 🚨 Not handling a missing entity — return `notFound()` (9.5) rather than crashing.

### When to Use It / When NOT to Use It

Every detail page (blog post, user profile, product). Don't use dynamic segments for fixed, known pages.

### Real-World Usage

`/posts/[id]`, `/users/[username]`, `/products/[sku]` — all dynamic routes.

### 🛠️ Practice

Build `/blog/[slug]` with a fake `getPost(slug)` that returns a post or `null`. Then build `/products/[id]` with `generateStaticParams` (below).

### 🧪 Mini Challenge

`generateStaticParams` pre-renders known dynamic routes at build time:

```tsx
export function generateStaticParams() {
  return [{ id: "1" }, { id: "2" }];   // pre-builds /products/1 and /products/2
}
```

Why is this powerful, and when is it NOT appropriate (hint: data that changes constantly)?

### ✅ Checkpoint

- How do you make a route dynamic?
- Why must you `await params` in Next.js 15?

---

## 9.3 Navigation: `Link`, `useRouter`, `redirect`

### Concept

**`<Link>`** does client-side navigation (no full page reload). **`useRouter()`** (client) provides programmatic navigation (`push`, `replace`, `back`). **`redirect()`** (server) redirects during rendering or actions.

### Why It Exists

Full page reloads are slow and lose state. Client-side navigation fetches only the new page chunk and swaps it in — fast, and the layout persists.

### Syntax / API

```tsx
// Client-side navigation (works in server components too)
import Link from "next/link";
<Link href={`/blog/${post.slug}`} className="underline">
  {post.title}
</Link>

// Programmatic (Client Component only)
"use client";
import { useRouter } from "next/navigation";
const router = useRouter();
router.push("/dashboard");      // add to history
router.replace("/login");        // replace current entry (login redirects)

// Server-side redirect
import { redirect } from "next/navigation";
if (!user) redirect("/login");   // in a server component or action
```

### Example Breakdown

- `Link` preloads the target route in the background (fast navigation).
- `useRouter` is for event-driven navigation (after form submit, button click).
- `redirect` runs on the server — never show unauthorized pages even briefly.

### Common Mistakes

- 🚨 Using `<a href>` for internal links — full reload, slower. (External links should use `<a>`.)
- 🚨 Using `useRouter` when `<Link>` suffices.
- 🚨 `redirect()` inside `try/catch` — it throws intentionally; don't swallow it.

### When to Use It / When NOT to Use It

`Link` for navigation UI. `useRouter` for programmatic flows. `redirect` for server-side auth/guard logic.

### Real-World Usage

Login success → `router.replace("/dashboard")`. Unauthenticated → `redirect("/login")`. Nav bars → `<Link>`.

### 🛠️ Practice

Add a header nav with `Link`s. Add a protected page that `redirect()`s when a fake `isLoggedIn` is false. Add a client button that `router.push`es after a fake login.

### ✅ Checkpoint

- When do you use each of the three navigation tools?
- Why `replace` for login redirects?

---

## 9.4 Route Groups and Special Files: `loading`, `error`, `not-found`

### Concept

- **(group)** — folders in parentheses that group routes *without* adding URL segments.
- **`loading.tsx`** — Suspense fallback shown while the segment loads.
- **`error.tsx`** — error boundary (`"use client"` required) for the segment.
- **`not-found.tsx`** — 404 UI for the segment (and `notFound()` triggers it).

### Why It Exists

Route groups give you independent layout trees at the same URL level (marketing vs app). The special files give every route a complete UX story: loading, error, and missing — without writing conditionals everywhere.

### Mental Model

```text
app/(marketing)/page.tsx        → /         (no URL segment from the group)
app/(app)/dashboard/page.tsx    → /dashboard

Loading:  navigating to a slow page shows loading.tsx instantly
Error:    a thrown error renders error.tsx (not a blank page)
Missing:  notFound() renders not-found.tsx
```

### Syntax / API

```tsx
// app/dashboard/loading.tsx
export default function Loading() {
  return <SkeletonRows />;   // shown while the page's async work runs
}

// app/dashboard/error.tsx  (must be a Client Component)
"use client";
export default function Error({ error, reset }: { error: Error; reset: () => void }) {
  return (
    <div>
      <h2>Something went wrong</h2>
      <p>{error.message}</p>
      <button onClick={reset}>Try again</button>
    </div>
  );
}
```

### Example Breakdown

- `loading.tsx` shows instantly during server work — no blank flash, no spinner-in-every-page code.
- `error.tsx` catches render/load errors in the segment; `reset` re-attempts.
- Error boundaries never catch errors in *themselves* or in event handlers — that's React's model.

### Common Mistakes

- 🚨 `error.tsx` without `"use client"` — it must be a Client Component.
- 🚨 Putting `loading.tsx` in the root and calling it a day — granular boundaries give better UX.
- 🚨 Forgetting that errors in Server Actions / route handlers are NOT caught by `error.tsx` (handle those explicitly, Phase 12).

### When to Use It / When NOT to Use It

Use `loading`/`error`/`not-found` for every meaningful route segment. Skip them for trivial static pages.

### Real-World Usage

Every production app: dashboard with skeletons while fetching, error pages with retry, custom 404s.

### 🛠️ Practice

Add to your blog: `loading.tsx` (skeleton), `error.tsx` (client, with reset), a custom `not-found.tsx`, and trigger each — slow the fake fetch with `await new Promise(r => setTimeout(r, 1000))`, throw for a specific slug, visit a nonexistent slug.

### 🧪 Mini Challenge

Design the loading/error/not-found strategy for a dashboard with 4 panels: which segments get which files? When do you want a *page-level* boundary vs a *panel-level* one? (Hint: Suspense, Phase 11.)

### ✅ Checkpoint

- What does a route group do to the URL?
- Why must `error.tsx` be a client component?
- What triggers `not-found.tsx`?

---

## 9.5 Metadata and SEO Basics

### Concept

Export `metadata` from layouts/pages (or `generateMetadata` for dynamic data) to control title, description, and Open Graph tags.

### Why It Exists

Server-rendered pages get SEO for free — but only if the tags are right. `metadata` makes it declarative and type-safe.

### Syntax / API

```tsx
// Static
import type { Metadata } from "next";
export const metadata: Metadata = { title: "About", description: "..." };

// Dynamic (per page)
export async function generateMetadata({ params }: { params: Promise<{ slug: string }> }): Promise<Metadata> {
  const { slug } = await params;
  const post = await getPost(slug);
  return { title: post.title, description: post.excerpt };
}
```

### Common Mistakes

- 🚨 Using a JS library to set `document.title` — that's client-side only and misses SEO. Use `metadata`.
- 🚨 Duplicating metadata when a layout + `generateMetadata` override is cleaner.

### 🛠️ Practice

Add titles to all your pages, a dynamic title for blog posts, and Open Graph tags on the home page. Inspect with DevTools.

### ✅ Checkpoint

- Why is metadata important in a server-rendered framework?

---

## 🚨 Common Beginner Mistakes (Phase 9)

- `<a>` instead of `<Link>` for internal routes.
- `params` not awaited.
- `metadata` in a client component.
- `error.tsx` without `"use client"`.
- Multiple `<html>` tags.
- `redirect()` swallowed by try/catch.

---

## ✅ Phase 9 Checkpoint

### What I Should Know

- [ ] File-based routing and nested layouts
- [ ] Dynamic routes + `generateStaticParams`
- [ ] `Link`, `useRouter`, `redirect` and when to use each
- [ ] Route groups
- [ ] `loading.tsx`, `error.tsx`, `not-found.tsx`
- [ ] Metadata

### Questions

1. Why do layouts persist across navigation, and why is that good?
2. When would you use a route group?
3. What's the difference between `useRouter().push` and `redirect()`?
4. Why can't `error.tsx` be a server component?

### Coding Challenges

1. **Level 1:** A 3-page site (home, about, contact) with shared header/footer via layouts and Link navigation.
2. **Level 2:** A blog with `/blog`, `/blog/[slug]`, loading skeleton, custom error page, and `generateMetadata` titles.
3. **Level 3:** A dashboard shell using route groups: `(marketing)` with its own layout, `(app)` with sidebar layout, and role-based `redirect()` for `/app` routes (fake auth for now).

### Design Challenge

Design the route/file tree for a SaaS app with: public pages, a logged-in dashboard with settings, and an admin section. Include layouts, route groups, loading/error/not-found files, and dynamic routes for a `[workspaceId]`.

### Ready to Continue?

✅ You built a multi-page app with nested layouts.
✅ You built dynamic routes with loading/error/404 states.
✅ You can explain route groups and the three navigation tools.

---

# Phase 10 — Server Components vs Client Components (The Critical Section)

> **Prerequisite:** Phases 8–9. Also: Phase 0 §0.3 (server vs client environments) — this phase builds directly on it.
> **Goal:** Know exactly what runs where, why, and how to cross the boundary safely. This is the concept that separates Next.js developers who understand their app from those who don't.

## 10.1 The Two Worlds

### Concept

In the App Router, **every component is a Server Component by default**. You opt into the client with `"use client"` at the top of a file.

| | Server Component | Client Component |
|---|---|---|
| Runs on | server (and during build) | browser (and pre-rendered on server) |
| Can it use hooks? | ❌ no hooks | ✅ all hooks |
| Can it use async/await? | ✅ yes, directly | ❌ no (needs effects/libs) |
| Can it access DB/secrets? | ✅ yes | ❌ never |
| Can it handle events? | ❌ no | ✅ yes |
| Sent to the browser | the rendered HTML + serialized props | the component code (JS) |

### Why It Exists

Before Server Components, every React app shipped its entire component code + data-fetching logic to the browser — large bundles, slow first paint, secrets impossible. Server Components let you **run as much as possible on the server**: fetch data, read the DB, render HTML — and send only what the client truly needs.

### Mental Model

```text
SERVER (trusted)                       CLIENT (untrusted, interactive)
─────────────────                      ───────────────────────────────
fetch/DB/secrets      ── HTML ──→      display, animation, events
heavy computation                     small, fast, interactive
async components                       hooks, state, effects
```

**Default question for every component: "can this run on the server?" If yes, leave it as a Server Component. "use client" is the exception, not the rule.**

### Common Mistakes

- 🚨 Adding `"use client"` to every file "to be safe" — this ships more JavaScript and defeats the entire architecture.
- 🚨 Trying to use hooks in a Server Component → compile/runtime error.
- 🚨 Trying to `await` or read secrets in a Client Component → impossible (correctly so).
- 🚨 Assuming "server component" means "always SSR at request time" — Server Components can also render at **build time** (static) (Phase 11).

### When to Use It / When NOT to Use It

- **Server Component:** reads data, renders content, imports server-only libs, keeps bundle small.
- **Client Component:** interactivity — state, effects, event handlers, browser APIs.
- **Both are needed** — most real pages are a server component tree with small interactive islands.

### Real-World Usage

A product page: Server Component fetches the product from the DB and renders most of the page; a small `AddToCartButton` (client) handles the click; a `Reviews` section streams in later via Suspense (Phase 11).

### 🛠️ Practice

In your blog app, deliberately add `"use client"` to a page that only renders static content. Check the bundle in the Network tab (you'll see extra JS). Then remove it. Internalize the difference.

### ✅ Checkpoint

- Which is the default? What opts into the client?
- What can Server Components do that Client Components can't — and vice versa?

---

## 10.2 The Component Boundary and Serialization

### Concept

Components compose across the boundary: **Server Components can render Client Components** (passing props), and **Client Components can receive children from Server Components**. But only **serializable** data can cross.

### What Can Cross the Boundary (be passed as props from server → client)

✅ Primitives (string, number, boolean, null), plain objects/arrays, `Date` (in supported versions), React elements, functions passed as **Server Actions** (Phase 12)

❌ **Cannot cross:** functions (regular), class instances, `Map`/`Set` (in older versions), `undefined`-only values, live DB connections, `Buffer`, sockets

### Mental Model

```text
Server Component
   │
   │ renders <ClientComp data={...} onAction={serverAction} />
   │         └─ data must be serializable (JSON-like)
   │         └─ onAction must be a Server Action (reference, not a closure)
   ▼
Client Component (interactive island)
```

### Example

```tsx
// page.tsx — Server Component
import ProductCard from "./ProductCard";          // client
import { addToCart } from "./actions";             // server action

export default async function Page() {
  const products = await db.query(...);            // server-side fetch
  return (
    <div>
      {products.map(p => (
        <ProductCard key={p.id} product={p} onAdd={addToCart} />
      ))}
    </div>
  );
}
```

```tsx
// ProductCard.tsx — Client Component
"use client";
interface Props { product: Product; onAdd: (id: string) => Promise<void>; }

export default function ProductCard({ product, onAdd }: Props) {
  return <button onClick={() => onAdd(product.id)}>Add</button>;
}
```

### Example Breakdown

- The server fetches data once, passes a **serializable** `product` object down.
- `onAdd` is a **Server Action reference** — the only kind of function that can cross (Phase 12).
- The client island has interactivity; everything else stays on the server.

### Common Mistakes

- 🚨 Passing a regular function from server → client → serialization error ("Functions cannot be passed directly").
- 🚨 Passing non-serializable data (class instances, `Map`) → errors or silent breakage.
- 🚨 `import`ing a client component into a server component is fine; the reverse (server component into client component) **is not** — you'd have to pass it as `children` instead.

### When to Use It / When NOT to Use It

Cross the boundary only for: interactive islands + their data + their server actions. Everything else stays server-side.

### Real-World Usage

Interactive tables with server-fetched data, forms calling server actions, real-time widgets fed by server state.

### 🛠️ Practice

Build: server page fetches a list → renders `InteractiveRow` (client) with toggle + `useState` → toggling calls a Server Action (fake, logs on server). Try passing a normal `function` prop and observe the serialization error.

### 🧪 Mini Challenge

Why can a **Client Component render `<ServerChild>`** only if it receives it as `children` from a parent Server Component — not by importing it directly? Trace the two render paths.

### ✅ Checkpoint

- What data can cross the boundary?
- What is the only kind of function that can cross, and why?

---

## 10.3 What Runs on the Server, What Must Run on the Client

### A practical decision table

| Need | Where it runs | Why |
|---|---|---|
| Database query | Server | secrets + speed (no round trip) |
| API key / secret | Server | never expose to browser |
| Reading a file | Server | browser can't |
| Event handler (onClick) | Client | browser API |
| `useState` / `useEffect` | Client | hooks are client-only |
| `window`, `document`, `localStorage` | Client | browser APIs |
| Heavy computation | Server (prefer) | offload from user's device |
| Animation / drag / canvas | Client | needs browser |
| Reading `cookies()` / `headers()` | Server | server-only APIs |

### Mental Model — the two architecture diagrams

```text
DIAGRAM A — Server-first (preferred for most reads)

Browser
   ↓ (request)
Next.js Server
   ↓
Server Component (async)
   ↓
Database / API        ← secrets stay here; HTML streams back

DIAGRAM B — Client-first (needed for interactivity or third-party APIs)

Browser
   ↓
Client Component ("use client")
   ↓
API (Route Handler or external)
   ↓
Database
```

**When A:** reading data to display, pages that can be static or cached, anything using server-only resources.
**When B:** interactions that refetch on user action, real-time client data, third-party APIs that must not be proxied, heavy client interactivity.

### Common Mistakes

- 🚨 Using Diagram B for everything (old SPA habits) — bigger bundles, slower loads, secrets at risk.
- 🚨 Using Diagram A where genuine interactivity is needed (a search box that refetches per keystroke) — the client island is necessary.
- 🚨 Putting a whole page in a client component because *one button* is interactive. Extract the button.

### When to Use It / When NOT to Use It

Reads → server. Mutations → Server Actions (Phase 12) when possible, Route Handlers for APIs/third parties. Interactivity → small client islands.

### Real-World Usage

A news site: articles server-rendered (A). Its comment form: Server Action. Its live-updating score ticker: client component polling an API (B).

### 🛠️ Practice

For each feature, decide A or B (and why): (1) product list from your DB, (2) search-as-you-type against an external API, (3) a like button, (4) the current user's profile header, (5) a live chat feed. Write your answers, then check them against your growing understanding.

### ✅ Checkpoint

- When is the server-first diagram right? When is client-first?
- Why shouldn't a whole page be client just because a button is?

---

## 10.4 `"use client"` — What It Actually Does

### Concept

`"use client"` at the top of a file marks everything in that file (and its imports, if they're also client) as a **Client Component module boundary**. It does NOT mean "runs only in the browser" — client components are **pre-rendered on the server** (HTML) and then **hydrated** in the browser (JS takes over).

### Why It Exists

You need a way to say "this subtree needs hooks/events/browser APIs." The directive marks the boundary; Next.js then ships that module's code to the browser.

### Mental Model

```text
"use client" = "this module and everything it imports is part of the client bundle."

Server:  renders HTML for it too (SSR) → good for SEO/first paint
Browser: downloads the JS, hydrates → interactive
```

### Common Mistakes

- 🚨 Thinking `"use client"` means "no server rendering." It still SSR's — it just also ships JS.
- 🚨 Adding `"use client"` to utility modules (date formatting, pure functions) — you've dragged them into the client bundle for nothing. Only components that need hooks/events need it.
- 🚨 Adding it to fix a serialization error by converting the *server* side to client — usually you should move the *interactive part* down, not the data up.

### When to Use It / When NOT to Use It

Use: components with hooks, event handlers, browser APIs, or client-only libraries. Don't use: presentational components, data-fetching pages, utilities.

### Real-World Usage

Forms, modals, charts, editors, anything with state — the interactive islands in a mostly-server app.

### 🛠️ Practice

Audit your blog app: which files have `"use client"`? For each, could the interactive part be extracted into a smaller island so the rest stays server? Refactor one file accordingly.

### 🧪 Mini Challenge

A library like `moment` is used in one client component and one server component. Explain what happens to the bundle (hint: client bundle only includes what client modules import). Then explain why you might still want a tiny server-side formatter instead.

### ✅ Checkpoint

- What does `"use client"` actually mark?
- Do client components get server-rendered HTML? Why does that matter?

---

## 10.5 Hydration — What Happens After the HTML Arrives

### Concept

**Hydration** is the process where React, running in the browser, attaches event handlers and state to the server-rendered HTML — making it interactive.

### Why It Exists

The server sends HTML the user can *see* immediately. Hydration makes that HTML *alive*: React matches its virtual tree to the existing DOM and wires up interactivity without re-rendering from scratch.

### Mental Model

```text
Server:  render HTML  ──→  Browser displays instantly (fast first paint)
         ── then ──
Browser: download JS → React hydrates → handlers attached → interactive

Between display and hydration: the page looks done but isn't interactive yet.
```

### Common Mistakes

- 🚨 **Hydration mismatches** — server HTML differs from what the client would render (e.g., `new Date()` in render, `Math.random()`, reading `window` during render). React warns and re-renders client-side; it also costs performance. Fix: make first render deterministic (compute time on the client in an effect, not in render).
- 🚨 Believing hydration is instant — big client bundles delay interactivity (Phase 18 covers measuring this).

### When to Use It / When NOT to Use It

Not optional — it's how client components work. You control *how much* hydration happens (keep islands small) and *when* (lazy, via Suspense/streaming).

### Real-World Usage

Every interactive Next.js page. "The page renders but buttons don't work for a second" = you're seeing the pre-hydration window.

### 🛠️ Practice

Add a component that renders `new Date().toLocaleString()` during render. Watch the hydration mismatch warning in the console. Fix it by rendering a placeholder and updating in an effect.

### ✅ Checkpoint

- What is hydration, in your own words?
- What causes hydration mismatches, and how do you avoid them?

---

## 10.6 Three Real Architectures (Putting It Together)

### Architecture 1 — Mostly Server, Small Islands (the default for content + dashboards)

```text
Server Component: fetch → render full page
  └─ Client island: search bar (state + events)
  └─ Client island: like button → Server Action
```

**Use when:** most of the page is data display; interactivity is localized. This is the recommended default.

### Architecture 2 — Client-Heavy App Shell

```text
Client layout/shell (nav, sidebar, state) + client data fetching (API) for dynamic areas
```

**Use when:** genuinely client-centric products (rich editors, real-time canvases) where the server adds little. Still use Route Handlers for your API and keep secrets server-side.

### Architecture 3 — Hybrid Streaming (advanced, Phase 11)

```text
Page shell streams instantly → Suspense boundaries load panels independently →
fast + fresh + granular loading
```

### Common Mistakes

- 🚨 Picking Architecture 2 out of habit. Start with 1; escalate with evidence.
- 🚨 Mixing architectures inconsistently (client components calling route handlers for data the server already has).

### 🛠️ Practice

Take a feature you've built (blog, todo, dashboard) and redraw it in Architecture 1: mark every component server/client, every fetch, every mutation. Justify each client component.

### ✅ Checkpoint

- Which architecture is the default, and why?
- When is a client-heavy shell actually right?

---

## 🚨 Common Beginner Mistakes (Phase 10)

- `"use client"` everywhere (the #1 mistake — bundle bloat, lost benefits).
- Hooks/`window`/`localStorage` in server components.
- Non-serializable props across the boundary.
- Fetching in client components what the server already has.
- Ignoring hydration mismatch warnings.
- Client components importing server components directly.

---

## ✅ Phase 10 Checkpoint

### What I Should Know

- [ ] Server vs client components — defaults, capabilities, restrictions
- [ ] The boundary, serialization, and Server Action references
- [ ] The two architecture diagrams and when each applies
- [ ] What `"use client"` does (and doesn't do)
- [ ] Hydration and mismatch causes
- [ ] The three composite architectures

### Questions

1. Your page needs a database read AND a clickable button. How do you structure it, and where does each part run?
2. Why is `"use client"` a cost, not a convenience?
3. What exactly breaks when you pass a plain function as a prop from a server component?
4. What causes hydration mismatch and how do you fix it?

### Coding Challenges

1. **Level 1:** Convert your blog to a Server Component page with one client island (a theme toggle button) — justify why only the island is client.
2. **Level 2:** Build a server-rendered product list where each row has an interactive expand/collapse (client island per row) and a "favorite" button calling a Server Action that logs on the server.
3. **Level 3:** Build a dashboard where the header (server), a live-updating chart (client, polling an API), and a settings form (client + server action) coexist. Draw the boundary diagram first.

### Design Challenge

You're building an attendance app (students, teachers, admins). For each screen — login, mark attendance, view reports, manage users — decide: server or client component? Where do fetches live? Where do mutations live? What crosses the boundary? Write the architecture document before writing code.

### Ready to Continue?

✅ You can draw the boundary for any feature in under a minute.
✅ You refactored something client-heavy into server + islands.
✅ You can explain hydration and serialization from memory.

---

# Phase 11 — Data Fetching & Caching in Next.js

> **Prerequisite:** Phase 10 (server/client architecture) — this phase is where that architecture pays off.
> **Goal:** Fetch data the Next.js way: on the server, with caching, revalidation, and streaming — and know when to refetch on the client.

## 11.1 Fetching on the Server (the default)

### Concept

Server Components are `async` functions — you `await fetch()` or a DB query directly in the component. No loading state needed for the *initial* data: the HTML streams with the data baked in.

### Why It Exists

Compare with Phase 6's client pattern (loading/error/data states, effects, races). Server fetching eliminates all of that for initial loads: the server already has the data, renders HTML, and the browser displays it. Faster, no flash, no round trip.

### Mental Model

```text
Client (Phase 6):  HTML shell → JS loads → fetch → loading → data → render
Server (Phase 11): fetch on server → HTML WITH data → display immediately
```

### Syntax / API

```tsx
// app/dashboard/page.tsx — Server Component
export default async function DashboardPage() {
  const stats = await getStats();          // DB or fetch, server-side
  return <StatsGrid stats={stats} />;
}
```

### Example Breakdown

- The page is `async`; the awaited promise resolves on the server.
- The browser never sees the fetch code — just HTML.
- `loading.tsx` (Phase 9) shows while the server works.

### Common Mistakes

- 🚨 Re-creating the Phase 6 client-fetch pattern for data you can fetch on the server.
- 🚨 Fetching in the browser from your own database-backed route when a server fetch does it in one hop (two hops = slower + exposes your API).
- 🚨 Forgetting `await` — you'll render a Promise.

### When to Use It / When NOT to Use It

Use for all initial page data. Use client fetching only for: user-triggered refetches, third-party APIs that must stay client-side, real-time data.

### Real-World Usage

Dashboards, product pages, user profiles — the server component tree fetches everything for first paint.

### 🛠️ Practice

Move one of your client-fetched pages to a server component. Delete the loading/error state code — observe how much code disappears and how the page behaves (no flash, no spinner for initial load).

### ✅ Checkpoint

- What does server fetching eliminate that client fetching required?
- When do you still fetch on the client?

---

## 11.2 Caching and Revalidation

### Concept

Next.js caches fetched data and rendered output. **Caching** = reuse stored data. **Revalidation** = refresh it, on a schedule (`revalidate`) or on demand (`revalidatePath` / `revalidateTag`).

### Why It Exists

Most data doesn't change every second. Caching turns expensive queries into instant responses. But stale data is bad — so you need controlled ways to refresh.

### Mental Model

```text
request → is there a fresh cache entry? → yes: serve it (fast)
                                        → no: fetch + store + serve

Freshness is YOUR decision:
  - revalidate: every N seconds
  - revalidateTag/path: on demand (after a mutation!)
  - no-store: never cache (always fresh)
```

### Syntax / API

```tsx
// Cache for 60 seconds, then refetch in the background
const data = await fetch(url, { next: { revalidate: 60 } });

// Never cache (always fresh — dashboards with live data)
const data = await fetch(url, { cache: "no-store" });

// Invalidate by tag after a mutation
await fetch(url, { next: { tags: ["posts"] } });
// elsewhere, after creating a post:
revalidateTag("posts");

// Invalidate everything on a path after a mutation
revalidatePath("/dashboard");
```

### Example Breakdown

- `revalidate: 60` — serve cached for 60s; first request after that refetches and updates the cache.
- `revalidateTag` is the precision tool: after a Server Action creates a post, `revalidateTag("posts")` refreshes exactly the cached data that matters.
- `cache: "no-store"` — for genuinely live data (scores, balances).

### Common Mistakes

- 🚨 Assuming all fetches are cached or uncached — the defaults changed across Next.js versions. **Always check the current docs** for your version's fetch defaults.
- 🚨 Fetching in a server component with `no-store` when `revalidate` would do — you've lost caching unnecessarily.
- 🚨 Mutating data and forgetting to revalidate → stale UI until the next scheduled refresh. Revalidate after every mutation.
- 🚨 Using client-side state to "fix" stale server data instead of revalidating server-side.

### When to Use It / When NOT to Use It

- Cache: content that changes slowly (posts, products, docs).
- Revalidate on demand: after mutations.
- No-store: live data, personalized dashboards.

### Real-World Usage

A blog: posts cached with `revalidate: 3600`; publishing a new post calls `revalidateTag("posts")`. A stock ticker: `no-store`.

### 🛠️ Practice

Build a page that fetches a timestamp from an API. Try `revalidate: 5`, `no-store`, and no options — and observe how often the timestamp changes. Then build the mutation flow: a form (Server Action) that appends an item and `revalidatePath`s the list.

### 🧪 Mini Challenge

Explain the difference between `revalidatePath` and `revalidateTag`, and design a rule for when you'd use each. When is `no-store` the only correct choice?

### ✅ Checkpoint

- What's the difference between caching and revalidating?
- Why must you revalidate after mutations?

---

## 11.3 Streaming and Suspense

### Concept

**Streaming** sends HTML in chunks as they're ready. **`<Suspense>`** defines boundaries that stream independently — each shows a fallback (often a skeleton) until its data arrives.

### Why It Exists

A slow panel shouldn't block the whole page. With streaming, the fast parts render immediately and slow parts appear when ready — dramatically better perceived performance.

### Mental Model

```text
Without Suspense: wait for EVERYTHING → send one big HTML blob
With Suspense:    send shell now → each <Suspense> boundary streams in as ready

Slow DB query on panel B no longer delays header, nav, panel A.
```

### Syntax / API

```tsx
// app/dashboard/page.tsx
export default function Dashboard() {
  return (
    <div>
      <Header />                          {/* instant */}
      <Suspense fallback={<StatsSkeleton />}>
        <StatsPanel />                    {/* streams when ready */}
      </Suspense>
      <Suspense fallback={<ActivitySkeleton />}>
        <ActivityFeed />                  {/* streams independently */}
      </Suspense>
    </div>
  );
}
```

```tsx
// StatsPanel.tsx — Server Component
export default async function StatsPanel() {
  const stats = await getStats();   // slow query
  return <StatsGrid stats={stats} />;
}
```

### Example Breakdown

- Each `Suspense` boundary is an independent streaming unit.
- The fallback (skeleton) renders immediately; the real content replaces it when ready.
- `loading.tsx` is just a page-level Suspense boundary (Phase 9).

### Common Mistakes

- 🚨 Wrapping the *entire* page in one Suspense — you've recreated the blocking behavior. Granular boundaries are the point.
- 🚨 Putting `Suspense` inside a Client Component for server data — boundaries around async server components belong on the server.
- 🚨 Forgetting that effects can't suspend; suspense is for server-side async work (or client libs built for it, e.g. `use` with promises).

### When to Use It / When NOT to Use It

Use when parts of a page have very different load times (dashboards). Don't use for uniform, fast pages — it adds complexity for nothing.

### Real-World Usage

Dashboards with panels, e-commerce pages with reviews loading after products, feeds that fill in progressively.

### 🛠️ Practice

Build a dashboard with 3 panels backed by fake delays (0.5s, 2s, 4s). Add granular Suspense boundaries and watch the page fill in. Then compare: one big Suspense vs three — screenshot the difference.

### 🧪 Mini Challenge

Design a loading strategy for a page with: critical content (must show ASAP), secondary analytics (slow), and a footer. Where do Suspense boundaries go? What are the fallbacks? Write the component tree before coding it.

### ✅ Checkpoint

- What does streaming give you that blocking doesn't?
- Why granular boundaries over one big one?

---

## 11.4 Client-side Refetching (when you genuinely need it)

### Concept

For user-triggered, client-side data changes — filters, pagination, search — you refetch in the browser. The modern options: **Server Actions returning data** (Phase 12), Route Handlers (Phase 12), or a data library like **SWR / TanStack Query**.

### Why It Exists

Some interactivity can't be server-rendered per keystroke. The client needs fresh data on demand — with caching and race-safety handled.

### Mental Model

```text
Server-first (default): render-time data, revalidate, stream
Client refetch (exception): user actions need NEW data without full navigation
```

### Common Mistakes

- 🚨 Using client data libraries for data the server can render and revalidate — two systems doing one job.
- 🚨 Not deduplicating client requests (multiple components fetching the same thing) — libraries do this; hand-rolled fetches often don't.
- 🚨 Ignoring the race-condition/unmount patterns from Phase 6 when you do hand-roll it.

### When to Use It / When NOT to Use It

Use: search-as-you-type, infinite scroll, live feeds. Don't use: initial page data (server), data that revalidates fine server-side.

### Real-World Usage

Search results updating per keystroke; infinite-scroll feeds; filterable data grids.

### 🛠️ Practice

Build a search box that hits a Route Handler (`app/api/search/route.ts`) with debounce (Phase 6) and proper race handling. Then rebuild it with SWR or TanStack Query and compare code volume and behavior.

### ✅ Checkpoint

- When is client refetching the right tool?
- What do data libraries buy you over hand-rolled fetch?

---

## 🚨 Common Beginner Mistakes (Phase 11)

- Fetching on the client what the server should fetch.
- Forgetting to revalidate after mutations → stale UI.
- One giant Suspense boundary.
- `no-store` everywhere (no caching benefit).
- Using Next.js fetch caching features from Phase 6 client-fetch habits.
- Not checking version-specific caching defaults in the docs.

---

## ✅ Phase 11 Checkpoint

### What I Should Know

- [ ] Server-side fetching in async components
- [ ] Caching + revalidation (`revalidate`, `revalidateTag`, `revalidatePath`, `no-store`)
- [ ] Streaming with Suspense
- [ ] When client refetching is actually needed

### Questions

1. Why does server fetching eliminate loading states for initial loads?
2. What's the difference between `revalidate` and `revalidateTag`?
3. When is `no-store` justified?
4. Why granular Suspense instead of one big boundary?

### Coding Challenges

1. **Level 1:** A server-rendered post list with `revalidate: 60`.
2. **Level 2:** A dashboard with three Suspense panels (staggered delays) + a mutation that appends to one panel and `revalidatePath`s it.
3. **Level 3:** A filterable data grid: server renders initial page, a client search refetches via Route Handler with debounce + race handling. Draw the data flow diagram first.

### Design Challenge

Design the data layer for a news site: homepage (fast, cached), article pages (cached + revalidated on publish), live scoreboard (no-store), and search (client refetch). For each: where does the fetch run, what's the caching strategy, where's the Suspense boundary?

### Ready to Continue?

✅ You moved a client-fetched page to the server.
✅ You built revalidation-after-mutation.
✅ You can explain streaming and when to use it.

---

# Phase 12 — Full-Stack Next.js: Server Actions, Route Handlers, and APIs

> **Prerequisite:** Phases 10–11.
> **Goal:** Build the backend of your app inside Next.js: mutations via Server Actions, HTTP APIs via Route Handlers, with validation, error handling, and a clean service layer.

## 12.1 The Three Ways to Move Data (and When to Use Each)

### Concept

| Pattern | What it is | Use when |
|---|---|---|
| **Server Component → DB** | Fetch directly in async component | Reading data for display (the default, Phase 11) |
| **Client → Server Action → DB** | Form/button posts to a server function | Mutations from interactive UI (create, update, delete) |
| **Client → API (Route Handler) → DB** | HTTP endpoint like any REST API | External consumers, third-party clients, non-form clients |

### Mental Model

```text
READS:      Server Component → Database           (Phase 11)
MUTATIONS:  Client → Server Action → Database     (this phase)
APIs:       Client/app → Route Handler → Database  (this phase)

Prefer the top pattern that fits. Don't build a REST API for your own
app's mutations if a Server Action is simpler and type-safe.
```

### Common Mistakes

- 🚨 Building a REST API for your own app when Server Actions would do — more code, more surface, slower.
- 🚨 Fetching on the client from an API you could read server-side (Phase 11).
- 🚨 Mixing all three for the same resource without a clear reason.

### 🛠️ Practice

For a todo app, decide the pattern for each operation: list, create, toggle, delete, export-CSV. Write one sentence justifying each.

### ✅ Checkpoint

- When do you reach for Server Actions vs Route Handlers vs server fetches?

---

## 12.2 Server Actions

### Concept

**Server Actions** are functions marked `"use server"` that run on the server, called from client components (or directly from forms in server components). They're the modern way to do mutations: type-safe, no API layer needed, and they can revalidate caches.

### Why It Exists

Mutations need to reach the server (DB, secrets) but shouldn't require hand-building HTTP endpoints with serialization, headers, and error mapping. Server Actions give you a direct function call from the UI to the server — with the framework handling the transport.

### Mental Model

```text
<Form action={createTodo}>  ──►  createTodo(formData)  ──►  DB write
        │                                                        │
        └────────────── revalidatePath("/todos") ◄────────────────┘
                     (UI refreshes with new data)

It LOOKS like a function call. Under the hood it's a POST with
serialized args. Your job: validate inputs, do the work, revalidate.
```

### Syntax / API

```tsx
// actions.ts
"use server";

import { revalidatePath } from "next/cache";
import { z } from "zod";
import { db } from "@/db";

const TodoSchema = z.object({
  title: z.string().min(1).max(200),
});

export async function createTodo(formData: FormData) {
  const parsed = TodoSchema.parse({
    title: formData.get("title"),
  });

  await db.todo.create({ data: parsed });   // or your ORM / SQL
  revalidatePath("/todos");
}
```

```tsx
// app/todos/new/page.tsx — Server Component with a plain form
import { createTodo } from "./actions";

export default function NewTodoPage() {
  return (
    <form action={createTodo}>
      <input name="title" required />
      <button type="submit">Create</button>
    </form>
  );
}
```

### Example Breakdown

- `"use server"` marks the file's exports as server actions (or annotate individual functions).
- `<form action={serverAction}>` works **without JavaScript** — progressive enhancement (works before hydration!).
- `formData.get("title")` reads the named input.
- **Validate with Zod** — never trust the client. `parse` throws on bad input.
- `revalidatePath` refreshes the cached list so the new todo appears.

### Client-side invocation (when you need state in between)

```tsx
"use client";
import { createTodo } from "./actions";

// Call it from an event handler with useTransition for pending state:
const [isPending, startTransition] = useTransition();
<button onClick={() => startTransition(() => createTodo({ title }))}>
  {isPending ? "Saving…" : "Save"}
</button>
```

### Common Mistakes

- 🚨 **Not validating inputs.** Server Actions are public endpoints — anyone can call them. Validate everything (Zod).
- 🚨 **No authorization check inside the action.** "This button is only shown to admins" is not security — check the session/role *inside* the action (Phase 14).
- 🚨 Forgetting `revalidatePath`/`revalidateTag` after mutations → stale UI.
- 🚨 Forgetting `await` on the action call or the promise.
- 🚨 Throwing raw errors to the client — return structured results (`{ ok, error }`) instead.
- 🚨 Using Server Actions for public content APIs — that's what Route Handlers are for.

### When to Use It / When NOT to Use It

**Use:** mutations from your own UI — forms, buttons, toggles, settings.
**Don't use:** public APIs, third-party integrations, mobile clients, heavy file streaming — those are Route Handlers.

### Real-World Usage

Every form in a Next.js SaaS: create post, update profile, delete account, toggle notifications — all Server Actions.

### 🛠️ Practice

Build the full todo mutation suite: create (form), toggle (button, `useTransition`), delete (confirm + action), all with Zod validation, auth check (fake user for now), and `revalidatePath`. Add a visible pending state on each.

### 🧪 Mini Challenge

Your create action currently trusts the client's `userId` in the payload. Explain why that's broken, and redesign so the *server* determines the user (from the session cookie). This is the #1 real-world security fix.

### ✅ Checkpoint

- What's the difference between `"use client"` and `"use server"`?
- Why must every Server Action validate its input and check authorization?
- Why `revalidatePath` after mutations?

---

## 12.3 Route Handlers (APIs)

### Concept

`app/api/.../route.ts` files export functions named after HTTP methods (`GET`, `POST`, `PUT`, `DELETE`) that return `Response` objects. This is your REST API inside Next.js.

### Why It Exists

Sometimes you need a real HTTP API: external clients, mobile apps, third-party webhooks, or endpoints your own client components call when Server Actions don't fit.

### Syntax / API

```tsx
// app/api/todos/route.ts
export async function GET() {
  const todos = await db.todo.findMany({ orderBy: { createdAt: "desc" } });
  return Response.json(todos);
}

export async function POST(request: Request) {
  const body = await request.json();
  const parsed = TodoSchema.safeParse(body);   // validate!
  if (!parsed.success) {
    return Response.json({ error: parsed.error.flatten() }, { status: 400 });
  }
  const todo = await db.todo.create({ data: parsed.data });
  return Response.json(todo, { status: 201 });
}
```

### Example Breakdown

- Each exported function handles one HTTP method on `/api/todos`.
- Read the JSON body with `await request.json()`.
- **Validate with Zod**; return proper status codes (400 bad input, 404 missing, 401/403 auth, 500 server error).
- Use `Response.json(...)` for JSON responses.

### Common Mistakes

- 🚨 Returning `200` for everything — status codes are your API's error vocabulary.
- 🚨 No validation → malformed data into your DB.
- 🚨 No auth/authorization on endpoints (Phase 14) — `GET /api/todos` leaks everyone's todos.
- 🚨 Forgetting `await request.json()`.
- 🚨 Building APIs for your own UI when Server Actions suffice.

### When to Use It / When NOT to Use It

**Use:** public APIs, integrations, mobile/third-party clients, webhooks, endpoints other services call.
**Don't use:** your own app's forms/buttons (Server Actions), data your server components can read directly.

### Real-World Usage

A SaaS exposes `GET /api/v1/...` for customers; internal UI uses Server Actions; webhooks receive `POST /api/webhooks/...`.

### 🛠️ Practice

Build a complete CRUD API for todos (`/api/todos`, `/api/todos/[id]`) with proper status codes, validation, and error shapes. Test it with `curl` (GET, POST, DELETE) — the API should be fully usable without a browser.

### 🧪 Mini Challenge

Design the error contract: what does every error response look like (`{ error: { code, message } }`?)? Then add pagination (`?page=&pageSize=`) and sorting (`?sort=createdAt&order=desc`) to `GET /api/todos`. Write the contract first, implement second.

### ✅ Checkpoint

- Route Handlers vs Server Actions — when each?
- What are the pieces of a well-formed API response (status, body, validation)?

---

## 12.4 API Design Principles (the ones that matter)

### Concept

Good APIs are predictable: RESTful resource naming, HTTP methods for actions, consistent error shapes, pagination, and versioning when needed.

### The Checklist

- **Resources, not actions:** `POST /api/orders` (create), not `POST /api/createOrder`.
- **Methods:** GET (read), POST (create), PUT/PATCH (update), DELETE (remove).
- **Status codes:** 200/201 success, 400 bad request, 401 unauthenticated, 403 forbidden, 404 not found, 409 conflict, 500 server error.
- **Consistent errors:** same shape everywhere: `{ error: { code, message, details? } }`.
- **Pagination for lists:** `?page=1&pageSize=20` (page-based) or cursors for large/real-time data.
- **Filtering/sorting:** query params, validated: `?status=done&sort=dueDate&order=asc`.
- **Versioning:** `/api/v1/...` once you have external consumers.

### Common Mistakes

- 🚨 Returning raw DB objects (exposing `passwordHash`, internal ids). Map to a public shape.
- 🚨 N+1 queries — fetching rows then querying per row (Phase 18/13).
- 🚨 Swallowing errors into generic 500s — log details server-side, return a safe message.
- 🚨 No rate limiting on public endpoints (Phase 17).

### Real-World Usage

Every REST API you've consumed follows these conventions — predictability is the product.

### 🛠️ Practice

Design (contract only, no code) the API for a project management tool: projects, tasks, comments. Define resources, methods, status codes, error shapes, pagination, filtering. Then implement the task endpoints.

### ✅ Checkpoint

- Name the HTTP methods and their meanings.
- What belongs in a good error response?

---

## 12.5 Service Layers and Data Access

### Concept

Separate **UI** (components), **business logic** (services), and **data access** (DB queries/ORM). Components call services; services call data access.

### Why It Exists

Business logic ("a task can only be deleted by its owner") must not live inside a component or a raw query. A service layer is where rules live, testable without a browser. Data access is where SQL/ORM lives, swappable without touching rules.

### Mental Model

```text
Component (UI) ──► Service (rules) ──► Data access (ORM/SQL) ──► DB
                        ▲
                   validation, auth checks, transactions here
```

### Example

```ts
// lib/services/task-service.ts
import { db } from "@/db";

export async function deleteTask(taskId: string, userId: string) {
  const task = await db.task.findUnique({ where: { id: taskId } });
  if (!task) throw new NotFoundError();
  if (task.ownerId !== userId) throw new ForbiddenError();   // rule lives here
  await db.task.delete({ where: { id: taskId } });
  revalidatePath("/tasks");
}
```

### Example Breakdown

- The rule (ownership check) lives in the service — reusable by Server Actions AND route handlers.
- Components stay thin: they call `deleteTask(id, user.id)`.
- Domain errors (`NotFoundError`) map to HTTP statuses at the boundary.

### Common Mistakes

- 🚨 Business logic in components (can't test, duplicated, leaks into UI).
- 🚨 Business logic in route handlers (each endpoint re-implements it).
- 🚨 Components touching the ORM directly (couples UI to DB).
- 🚨 Over-engineering: a `UserService` with one method that just wraps a query — add layers when rules exist, not preemptively.

### When to Use It / When NOT to Use It

Add a service layer when rules exist (validation beyond shape, authorization, transactions, multi-step operations). Skip it for pure CRUD passthrough.

### Real-World Usage

Multi-tenant SaaS: every service checks "does this user belong to this workspace?" — one place, enforced everywhere.

### 🛠️ Practice

Refactor a todo app you've built: extract `task-service.ts` with `createTask`, `toggleTask`, `deleteTask` (ownership rules), and make both a Server Action and a route handler call the same service.

### 🧪 Mini Challenge

Design the service layer for a multi-user kanban: what rules exist (board access, column membership, moving tasks)? Where do they live? What happens when a move is invalid — what error, what status?

### ✅ Checkpoint

- What belongs in a service layer vs a component vs data access?
- When is adding a service layer over-engineering?

---

## 12.6 Cookies, Headers, and Environment Variables

### Concept

- `cookies()` / `headers()` — read (and in route handlers, set) cookies/headers **server-side**.
- `.env.local` — development secrets; `.env.production` for prod. Server-only unless prefixed `NEXT_PUBLIC_`.

### Why It Exists

Sessions live in cookies (Phase 14). Feature flags and locale live in headers. Secrets must never reach the client.

### Syntax / API

```tsx
// Server Component / Action / Route Handler
import { cookies } from "next/headers";

const sessionCookie = (await cookies()).get("session")?.value;

// Server-only env var (never exposed to the browser)
const key = process.env.STRIPE_SECRET_KEY;

// Public env var (embedded in the client bundle — NEVER put secrets here)
const publicUrl = process.env.NEXT_PUBLIC_API_URL;
```

### Common Mistakes

- 🚨 `NEXT_PUBLIC_` on secrets — anything prefixed `NEXT_PUBLIC_` is public. DB passwords, API keys → no prefix, server-only.
- 🚨 Reading cookies in a Client Component — `cookies()` is server-only; use the API/headers or pass data down.
- 🚨 Committing `.env.local` — it's in `.gitignore` by default; keep it that way (Phase 17).

### 🛠️ Practice

Read the session cookie in a server component and render different UI for logged-in vs not. Move a secret into `.env.local` and use it server-side; verify it never appears in the client bundle (search the Network tab / built JS).

### ✅ Checkpoint

- What does `NEXT_PUBLIC_` do to a variable, and why must secrets never have it?
- Where can you read cookies?

---

## 🚨 Common Beginner Mistakes (Phase 12)

- Server Actions without validation or authorization checks.
- Forgetting revalidation after mutations.
- Building REST APIs for your own UI when Server Actions fit.
- Returning raw DB objects from APIs.
- Business logic scattered in components and handlers.
- `NEXT_PUBLIC_` secrets.

---

## ✅ Phase 12 Checkpoint

### What I Should Know

- [ ] Server Actions: forms, `useTransition`, validation, revalidation
- [ ] Route Handlers: methods, status codes, error contracts
- [ ] The three data-movement patterns and when each applies
- [ ] Service layers and where rules live
- [ ] Cookies/headers/env vars

### Questions

1. When would you choose a Route Handler over a Server Action? Give a concrete case.
2. Why must Server Actions validate and authorize even though they're "internal"?
3. What's the difference between throwing and returning errors from a Server Action, and which is better for UX?
4. Where does "only the owner can delete" belong?

### Coding Challenges

1. **Level 1:** A Server Action form that creates items with Zod validation and revalidates.
2. **Level 2:** Full CRUD API for one resource with status codes + error contract, tested with curl.
3. **Level 3:** A multi-user todo app: Server Action + service layer with ownership rules, plus a public read-only API for the same data. Both paths share the service.

### Design Challenge

Design the full-stack data layer for a project management app: every read (server component vs API?), every mutation (Server Action vs Route Handler?), every rule (in the service), every cache invalidation. Write the complete map before coding.

### Ready to Continue?

✅ You built mutations with validation, auth checks, and revalidation.
✅ You built and curl-tested an API.
✅ You can explain the three data patterns and pick correctly.

---

# Phase 13 — Databases

> **Prerequisite:** Phases 11–12 (you need somewhere to put the data you fetch).
> **Goal:** Understand relational modeling and SQL well enough to design and query real schemas — and integrate a database with Next.js via a TypeScript-friendly ORM, while learning concepts, not just a tool.

## 13.1 Relational Databases, Tables, Rows, Keys

### Concept

A relational database stores data in **tables** (columns + rows). Every row has a **primary key** (unique id). Tables relate via **foreign keys** (a column referencing another table's primary key).

### Why It Exists

Real apps have related data: users own projects; projects contain tasks; tasks have comments. Relational modeling captures these relationships *in the data* — with integrity enforced by the database.

### Mental Model

```text
users                                projects
┌──────┬─────────┐                    ┌──────┬─────────┬───────────────┐
│ id   │ name    │ 1 ────── N         │ id   │ title   │ ownerId (FK)  │
├──────┼─────────┤                    ├──────┼─────────┼───────────────┤
│ 1    │ Ada     │◄───────────────────│ 10   │ Launch  │ 1             │
│ 2    │ Grace   │                    │ 11   │ Rebrand │ 1             │
└──────┴─────────┘                    └──────┴─────────┴───────────────┘

users.id  = primary key
projects.ownerId = foreign key → users.id
"A user has many projects; a project belongs to one user"
```

### Relationships

- **One-to-one:** user ↔ profile (each has exactly one).
- **One-to-many:** user → projects (the most common).
- **Many-to-many:** students ↔ courses (needs a **join table**: `enrollments` with `studentId` + `courseId`).

### Common Mistakes

- 🚨 Storing CSV/JSON in one column because you didn't model a relationship — you lose querying, integrity, and consistency.
- 🚨 Forgetting foreign keys (no referential integrity) — orphaned rows.
- 🚨 Duplicating data (user name in every task row) — updates require touching many rows. Normalize: store the id, join for the name.

### When to Use It / When NOT to Use It

Relational for anything with relationships and integrity needs. Document stores (MongoDB) fit other shapes — but relational is the right default for most web apps and what this guide assumes.

### Real-World Usage

Every SaaS: users, orgs, subscriptions, invoices, projects, tasks, comments — a web of related tables.

### 🛠️ Practice

Design the schema (on paper) for a library: books, authors (many-to-many), members, loans. Identify primary keys, foreign keys, and relationship types.

### ✅ Checkpoint

- What is a primary key? A foreign key?
- How do you model many-to-many?

---

## 13.2 SQL Fundamentals

### Concept

**SQL** is the language for querying relational data. You need a working subset: `SELECT`, `WHERE`, `JOIN`, `GROUP BY`, `ORDER BY`, `LIMIT`, `INSERT`, `UPDATE`, `DELETE`, and basic `CREATE TABLE`.

### Why It Exists

Even with an ORM, SQL is what actually runs, and you'll read it in migrations, raw queries, and error messages. You can't debug what you can't read.

### Syntax / API

```sql
-- Read
SELECT id, title FROM tasks WHERE done = false ORDER BY due_date ASC LIMIT 20;

-- Join
SELECT t.title, u.name FROM tasks t JOIN users u ON t.owner_id = u.id;

-- Aggregate
SELECT category, COUNT(*) FROM transactions GROUP BY category;

-- Write
INSERT INTO tasks (title, owner_id) VALUES ('Ship feature', 1);
UPDATE tasks SET done = true WHERE id = 42;
DELETE FROM tasks WHERE id = 42;
```

### Example Breakdown

- `WHERE` filters rows; `ORDER BY` sorts; `LIMIT` bounds.
- `JOIN ... ON` links tables on the foreign key — the bread and butter of relational work.
- `GROUP BY` + aggregate functions (`COUNT`, `SUM`, `AVG`) produce summaries.

### Common Mistakes

- 🚨 `SELECT *` habitually — name the columns you need.
- 🚨 Joins without `ON` (cartesian products — every row × every row).
- 🚨 String-concatenating user input into SQL (**SQL injection**, Phase 17). Never do this; always parameterize.

### When to Use It / When NOT to Use It

You'll mostly use an ORM — but raw SQL for complex reports, and for understanding what the ORM generates.

### Real-World Usage

Reporting dashboards are pure SQL: "revenue by month," "users by signup cohort," "slowest tasks."

### 🛠️ Practice

Install SQLite locally (`sqlite3` or a GUI). Create the library schema from 13.1 and run: insert data, query books by author, count loans per member, list overdue loans. Write each query yourself.

### 🧪 Mini Challenge

Write a query that returns each member's name and number of currently-loaned books, including members with zero loans (hint: `LEFT JOIN` + `GROUP BY`).

### ✅ Checkpoint

- What does `JOIN ... ON` do? `GROUP BY`?
- Why must you never interpolate user input into SQL strings?

---

## 13.3 Indexes, Transactions, Migrations

### Concept

- **Index:** a structure that makes lookups on a column fast. Cost: slower writes, more storage.
- **Transaction:** a group of operations that succeed or fail **together** (atomic).
- **Migration:** a versioned, reviewable schema change.

### Why It Exists

- Indexes: without one on `WHERE user_id = ?`, the DB scans every row (slow at scale).
- Transactions: "transfer money" must debit and credit together — a crash between them corrupts data.
- Migrations: schema must evolve in production without losing data, and teams must review changes.

### Common Mistakes

- 🚨 Indexing everything (writes slow down) — index what you filter/join on, measure first.
- 🚨 Multi-step writes without a transaction → partial failure states.
- 🚨 Editing the DB by hand instead of via migrations → environments drift apart.

### When to Use It / When NOT to Use It

Transactions: anything multi-step (payments, moving tasks, deleting users + their data). Migrations: every schema change. Indexes: on columns used in `WHERE`/`JOIN` for tables that grow.

### Real-World Usage

Payments, orders, account changes — all transactional. Every production DB change ships as a migration reviewed in a PR.

### 🛠️ Practice

Write a migration that adds a `due_date` column to tasks; write a transaction that moves a task between projects (update + audit log insert together).

### ✅ Checkpoint

- What problem does each of the three solve?

---

## 13.4 Integrating a Database with Next.js (Prisma as the example)

### Concept

An **ORM** maps tables to TypeScript types and gives you a typed query API. **Prisma** is the common choice: schema → migrations → typed client. The *concepts* (schema, migrations, client, relations) transfer to any ORM.

### Why It Exists

Hand-written SQL + manual type mapping is error-prone. An ORM gives you: types generated from the schema, migrations, and a safe query builder.

### Mental Model

```text
schema.prisma (your data model) ── migrate ──► database (real tables)
      │                                    
      └── generate ──► PrismaClient (typed API used by services)
```

### Syntax / API

```prisma
// prisma/schema.prisma
model User {
  id       String    @id @default(cuid())
  name     String
  email    String    @unique
  projects Project[]
}

model Project {
  id      String  @id @default(cuid())
  title   String
  owner   User    @relation(fields: [ownerId], references: [id])
  ownerId String
  tasks   Task[]
}

model Task {
  id        String  @id @default(cuid())
  title     String
  done      Boolean @default(false)
  project   Project @relation(fields: [projectId], references: [id])
  projectId String
}
```

```ts
// lib/db.ts — one shared client (avoid creating many connections)
import { PrismaClient } from "@prisma/client";
const globalForPrisma = globalThis as unknown as { prisma?: PrismaClient };
export const db = globalForPrisma.prisma ?? new PrismaClient();
if (process.env.NODE_ENV !== "production") globalForPrisma.prisma = db;
```

```ts
// lib/services/task-service.ts — typed queries
const tasks = await db.task.findMany({
  where: { projectId, done: false },
  include: { project: { select: { title: true } } },   // joins!
  orderBy: { createdAt: "desc" },
  take: 20,
});
```

### Example Breakdown

- The schema is the single source of truth: models, relations, unique constraints.
- `include`/`select` express joins and column picking — typed, no SQL strings.
- The singleton client pattern prevents connection exhaustion in dev (hot reload).
- Services use the typed client — Phase 12's architecture, now with real data.

### Common Mistakes

- 🚨 Creating a new `PrismaClient` per request/component (connection leak). Singleton (above).
- 🚨 `await db.task.create()` outside a try/catch in a Server Action — handle and return errors.
- 🚨 Forgetting to run migrations before deploying (Phase 22).
- 🚨 N+1: `findMany` then per-row `include`/queries in a loop — use `include` or `select` for eager loading.
- 🚨 Exposing the DB client to client components — DB access lives server-side only (Phase 10!).

### When to Use It / When NOT to Use It

Use an ORM for standard CRUD + relations. Drop to raw SQL for complex reporting queries. Prisma vs Drizzle vs others — the concepts (schema/migrations/client) are identical; pick one and learn it deeply.

### Real-World Usage

Essentially every production Next.js app uses an ORM with the exact schema→migrate→generate→typed-client flow.

### 🛠️ Practice

Set up Prisma + SQLite in your project: define User/Project/Task, run the migration, write a seed script, and build a service layer: `listProjectsForUser`, `createTask`, `toggleTask` with `include` for joins.

### 🧪 Mini Challenge

Design the Prisma schema for a forum: users, posts, comments, likes (many-to-many user↔post via a join model). Include relations and unique constraints. Then write a query for "all posts with comment counts."

### ✅ Checkpoint

- What does the schema → migrate → generate flow give you?
- Why a singleton client?
- How do you express a join with the ORM?

---

## 🚨 Common Beginner Mistakes (Phase 13)

- Designing schemas without thinking about relationships.
- Multi-step writes without transactions.
- Editing the database by hand instead of migrations.
- N+1 queries.
- New DB client per request.
- DB access from client components.
- Skipping indexes until the app is slow.

---

## ✅ Phase 13 Checkpoint

### What I Should Know

- [ ] Tables, rows, primary/foreign keys
- [ ] One-to-one, one-to-many, many-to-many
- [ ] Core SQL: SELECT/JOIN/GROUP BY/INSERT/UPDATE/DELETE
- [ ] Indexes, transactions, migrations
- [ ] ORM flow: schema → migrate → generate → typed client
- [ ] N+1 avoidance and the singleton client

### Questions

1. Design tables for: users, courses, enrollments. What are the keys and relationship types?
2. What does `GROUP BY category` do? When would you join?
3. Why must a money transfer be a transaction?
4. What is an N+1 query and how do you avoid it?

### Coding Challenges

1. **Level 1:** SQLite: create tasks/users tables, insert, query with a join.
2. **Level 2:** Prisma: full CRUD service for tasks scoped to a user, with migrations and a seed.
3. **Level 3:** Model a kanban board (boards → columns → cards, card positions), write the move-card service as a transaction, and an API for the board view. Design it yourself.

### Design Challenge

Design the schema for a hospital system: patients, doctors, appointments, prescriptions. Include relations, unique constraints, and one aggregate query (e.g., appointments per doctor this week).

### Ready to Continue?

✅ You wrote joins and aggregates by hand.
✅ You ran a migration and used a typed ORM client.
✅ You can design a schema with the three relationship types.

---

# Phase 14 — Authentication & Authorization

> **Prerequisite:** Phases 10–13 (server components, actions, cookies, database).
> **Goal:** Implement auth that is *actually secure*: sessions in cookies, passwords hashed, roles enforced server-side — and understand why each piece exists.

## 14.1 Authentication vs Authorization

### Concept

- **Authentication** = *who are you?* (proving identity — login).
- **Authorization** = *what may you do?* (permissions, roles — checked after auth).

### Why It Exists

They're different problems with different failures. "Anyone can log in" is an auth failure; "any logged-in user can delete everyone's data" is an authorization failure. Most breaches are authorization bugs.

### Mental Model

```text
authenticate (login) ──► establish a session ──► authorize on EVERY action

"You may be logged in, but that doesn't mean you may delete this."
```

### Common Mistakes

- 🚨 Confusing the two — building great login and then trusting the client to hide buttons.
- 🚨 **Client-side authorization only.** Hiding an admin button in the UI is decoration, not security. The attacker calls the API directly. Authorization MUST be enforced on the server, in every action/endpoint.

### When to Use It / When NOT to Use It

Both are always in play for protected features. This distinction is the foundation of everything in this phase.

### Real-World Usage

Every SaaS: login (auth), then role checks (authorization) on every server action and API call.

### 🛠️ Practice

For your todo app, list: (a) what proves identity, (b) every action that needs a permission check. Write one sentence per action.

### ✅ Checkpoint

- Auth vs authz — define both with an example.
- Why is client-side-only authorization worthless?

---

## 14.2 Password Authentication Done Right

### Concept

Passwords are verified by **hashing** with a slow, salted algorithm — never stored or compared in plaintext.

### Why It Exists

If your database leaks (and you must assume it can), hashed passwords are useless to attackers. Salt (random per-user data) defeats rainbow tables; slow algorithms (bcrypt/argon2) make brute-force expensive.

### Mental Model

```text
signup:  password ──bcrypt──► hash ──► stored in DB (hash only)
login:   password ──bcrypt──► compare hash to stored hash

Never:  store password, log password, email password, compare directly.
```

### Syntax / API

```ts
import { hash, compare } from "bcryptjs";   // or argon2

// signup
const passwordHash = await hash(rawPassword, 12);
await db.user.create({ data: { email, passwordHash } });

// login
const user = await db.user.findUnique({ where: { email } });
if (!user) throw new Error("Invalid credentials");       // same message for
const ok = await compare(rawPassword, user.passwordHash); // user-not-found
if (!ok) throw new Error("Invalid credentials");          // (don't leak which)
```

### Example Breakdown

- `hash` with a cost factor (12) — deliberately slow.
- The same "Invalid credentials" message for missing user vs wrong password — don't leak account existence.
- Compare the hash, never the plaintext.

### Common Mistakes

- 🚨 Storing plaintext or reversible encryption — unforgivable in 2026; hashing is non-negotiable.
- 🚨 Fast hashing algorithms (MD5, SHA) or no salt — instantly crackable.
- 🚨 Revealing whether an email exists ("account not found") — aids enumeration attacks.
- 🚨 Rolling your own crypto — use battle-tested libraries (bcrypt/argon2).

### When to Use It / When NOT to Use It

Password auth for your own users. For everything else, prefer OAuth providers (14.6) — but even OAuth apps need session management.

### Real-World Usage

Every password login you've ever used runs this exact flow behind a framework (NextAuth/Auth.js, Lucia, etc.).

### 🛠️ Practice

Implement signup + login with bcrypt against your Prisma user table. Write a tiny script that demonstrates: same password → different hash each time (salt!), verify with `compare`.

### ✅ Checkpoint

- Why hash + salt + slow algorithm?
- Why identical error messages for missing user vs wrong password?

---

## 14.3 Sessions, Cookies, and Tokens

### Concept

After login, the server establishes a **session** — a record that "user X is logged in." The client holds a **cookie** containing the session identifier; the server looks up the session on each request.

### Why It Exists

HTTP is stateless (Phase 0). The cookie is the *state token* the browser sends with every request, so the server can recognize you.

### Mental Model

```text
login ──► server creates session ──► Set-Cookie: sessionId=abc123; HttpOnly
                                          ▲
browser sends Cookie: sessionId=abc123 on EVERY request ──► server verifies
```

### The Cookie Flags (memorize)

| Flag | What it does | Why |
|---|---|---|
| `HttpOnly` | JS can't read the cookie | blocks XSS cookie theft (Phase 17) |
| `Secure` | only sent over HTTPS | no plaintext sniffing |
| `SameSite=Lax` | not sent on cross-site requests | blocks CSRF (Phase 17) |
| `Path=/` | sent for the whole site | sessions cover all routes |
| `Max-Age` | expiration | sessions end |

### Session Storage Options

- **Database sessions:** store the session in the DB (or Redis). Instant revocation — delete the row to log out everywhere. Slightly slower.
- **Signed/JWT stateless tokens:** the token itself encodes claims, signed by the server. No DB lookup — but revocation requires a blocklist (or short expiry). JWTs are **not** automatically safer — they're a trade-off.

### Common Mistakes

- 🚨 Cookies without `HttpOnly`/`Secure`/`SameSite` → XSS/CSRF vectors.
- 🚨 Storing the whole user object in a cookie (tamperable) — store an opaque session id, look up server-side.
- 🚨 Never expiring sessions.
- 🚨 Putting tokens in `localStorage` — XSS-readable. HttpOnly cookies are the safer default.

### When to Use It / When NOT to Use It

Database-backed sessions in HttpOnly cookies are the robust default for web apps. JWT shines for distributed/stateless APIs and mobile — accept the revocation cost.

### Real-World Usage

Every login flow: session cookie, HttpOnly + Secure + SameSite, expiring, revocable.

### 🛠️ Practice

Implement a minimal session system with Prisma: `Session` table (id, userId, expiresAt), create on login, look up on protected routes, delete on logout. Set the cookie with the flags above. Inspect the cookie in DevTools → Application → Cookies.

### 🧪 Mini Challenge

Explain why `HttpOnly` + `SameSite=Lax` together defeat both XSS cookie theft AND CSRF. What does each flag stop specifically? (Both answers are in Phase 17 — try to reason it out first.)

### ✅ Checkpoint

- What does each cookie flag protect against?
- DB sessions vs JWT — the trade-off, in your own words?

---

## 14.4 Protected Routes and Server-Side Enforcement

### Concept

Protect data on the **server**, in every Server Component read, every Server Action, and every Route Handler — never just in the UI.

### Mental Model

```text
Three layers, all server-side:
1. Layout/page guard: redirect unauthenticated users away.
2. Data guard: queries scoped to the authenticated user.
3. Action/API guard: every mutation re-checks session + permissions.

The UI layer (hidden buttons) is UX, not security.
```

### Syntax / API

```tsx
// lib/auth.ts — server-only session helper
import { cookies } from "next/headers";
import { db } from "@/db";

export async function getSession() {
  const sessionId = (await cookies()).get("session")?.value;
  if (!sessionId) return null;
  return db.session.findUnique({
    where: { id: sessionId },
    include: { user: true },
  });
}

// lib/auth.ts — guard used by layouts/pages/actions
export async function requireUser() {
  const session = await getSession();
  if (!session) redirect("/login");
  return session.user;
}
```

```tsx
// app/dashboard/page.tsx — protected page (Server Component)
export default async function Dashboard() {
  const user = await requireUser();      // redirects if not logged in
  const projects = await db.project.findMany({ where: { ownerId: user.id } });
  return <ProjectsList projects={projects} />;
}
```

```ts
// Server Action — re-check authorization on EVERY mutation
"use server";
export async function deleteTask(taskId: string) {
  const user = await requireUser();
  const task = await db.task.findUnique({ where: { id: taskId } });
  if (!task || task.ownerId !== user.id) {
    throw new Error("Not authorized");   // server-side enforcement
  }
  await db.task.delete({ where: { id: taskId } });
  revalidatePath("/tasks");
}
```

### Example Breakdown

- `requireUser()` centralizes the session check — one place, used everywhere.
- Data is scoped by `ownerId: user.id` — the DB query itself enforces ownership (defense in depth).
- The action re-checks ownership — never trust the client sent the right id.

### Common Mistakes

- 🚨 Protecting only the page, not the actions/API (the page is just a view).
- 🚨 Trusting client-supplied ids (`taskId`, `userId`) — the server must derive/verify ownership.
- 🚨 Checking `isAdmin` in the UI and skipping the server check.
- 🚨 Relying on client-side redirects for protection — an attacker just doesn't run your JS.

### When to Use It / When NOT to Use It

Always for protected data. Public pages skip the guard but still scope queries if any data is user-specific.

### Real-World Usage

Multi-tenant SaaS: every query includes `where: { workspaceId: session.workspaceId }` — tenants can never see each other's data even if they guess URLs (that's the IDOR fix, Phase 17).

### 🛠️ Practice

Add sessions + `requireUser` to your app: protect a dashboard, scope its queries to the user, and guard every mutation with ownership checks. Then *deliberately* try to access another user's task by URL/action — verify the server blocks it.

### 🧪 Mini Challenge

Your app lets users share projects with others. Design the authorization: what table, what checks, where enforced? Consider: viewer vs editor roles on a shared project. Write the design before coding.

### ✅ Checkpoint

- What are the three server-side layers of protection?
- Why is a client-side guard insufficient?

---

## 14.5 Roles and Permissions (RBAC)

### Concept

**RBAC** (role-based access control): users have roles; roles have permissions; actions check permissions. Example: ADMIN / TEACHER / STUDENT.

### Why It Exists

Hard-coding "if user.id === X" for every rule doesn't scale. Roles group permissions so you can assign and change them coherently.

### Mental Model

```text
ADMIN      ──► can do everything
TEACHER    ──► create courses, grade submissions
STUDENT    ──► enroll, view grades

Permission check: "does this user's role include this permission?"
```

### Syntax / API

```prisma
// Simple: role column
model User {
  id    String
  email String
  role  Role   // enum: ADMIN | TEACHER | STUDENT
}

// Flexible: role + permissions, or permission table + join
enum Role { ADMIN TEACHER STUDENT }
```

```ts
// lib/authz.ts — the authorization check
import { redirect } from "next/navigation";

export function requireRole(user: User, roles: Role[]) {
  if (!roles.includes(user.role)) {
    redirect("/403");   // or throw ForbiddenError
  }
}

// in an action:
const user = await requireUser();
requireRole(user, ["TEACHER", "ADMIN"]);   // e.g., create a course
```

### Example Breakdown

- `requireRole` is a tiny, readable guard used in every protected action.
- Role checks live in **services/actions**, not in components.
- For shared resources (a project you don't own but were invited to), you need **resource-level permissions** (membership tables) — roles answer "what can this class of user do," membership answers "what can THIS user do on THIS resource."

### Common Mistakes

- 🚨 Checking roles in the UI only.
- 🚨 Roles checked in one place and forgotten in another — centralize in guards.
- 🚨 Using roles for *resource* access ("this teacher's course") — that's membership, model it separately.
- 🚨 Enum-role columns for fine-grained systems — consider permission tables when rules multiply.

### When to Use It / When NOT to Use It

Roles for coarse classes of user. Add permission tables / resource membership when access varies per object.

### Real-World Usage

The classic ADMIN/TEACHER/STUDENT (your capstone!), ADMIN/MEMBER in workspaces, owner/editor/viewer on documents.

### 🛠️ Practice

Add roles to your app: a `role` column, `requireRole` guard, and one feature per role (student can submit, teacher can grade, admin can manage users). Seed users for each role and verify the guards block/allow correctly.

### 🧪 Mini Challenge

Design RBAC for a school: who can create a course, enroll, view grades, edit grades, manage users? Produce a role × permission matrix. Where do you draw the line between role checks and resource membership?

### ✅ Checkpoint

- Role vs permission vs membership — define each.
- Why must checks live server-side, centrally?

---

## 14.6 OAuth (Conceptual) and Using a Framework

### Concept

**OAuth** lets users log in with Google/GitHub/etc. instead of a password. The identity provider verifies the user; your app receives verified claims (email, name) and creates/links a local account. **Auth.js (NextAuth)** and Lucia are the common Next.js helpers.

### Why It Exists

Passwords are friction + liability. OAuth delegates credential handling to providers that do security well, and users prefer it. (Note: OAuth 2.0 itself is an *authorization* protocol for delegating access — the login flow is the "OIDC" extension. Conceptually: provider confirms identity to you.)

### Mental Model

```text
User clicks "Sign in with Google"
   ↓
Google shows consent page (redirect)
   ↓
Google redirects back with a code
   ↓
Your server exchanges code → verified profile
   ↓
Create/find local user → create session (same as 14.3!)
```

### Common Mistakes

- 🚨 Building OAuth by hand — use a well-maintained library; OAuth is easy to get subtly wrong.
- 🚨 Trusting the *client* to tell you who the user is ("Google said I'm admin") — only the server-side code exchange is trustworthy.
- 🚨 Skipping session management because OAuth exists — you still need sessions for your own app.

### When to Use It / When NOT to Use It

Offer OAuth to reduce friction; keep email/password (or magic links) for users who want it. OAuth-only can lock out users without the provider.

### Real-World Usage

Every "Sign in with..." button you've seen.

### 🛠️ Practice

Integrate Auth.js with a provider (GitHub or Google) into your app. Keep the session flow from 14.3 working alongside. Verify: login, session persistence, logout, protected route.

### ✅ Checkpoint

- What does OAuth solve, and what do you still own (sessions, account linking)?
- Why must the code exchange happen server-side?

---

## 14.7 Logout, Expiration, and Session Lifecycle

### Concept

Sessions must end: explicit **logout** (delete session + cookie), **expiration** (Max-Age + DB expiry), and **rotation** (new session id on privilege changes, e.g., after login or role change — prevents fixation).

### Why It Exists

A stolen/forgotten session should stop working. Expiration limits the blast radius of a leaked cookie.

### Syntax / API

```ts
// logout — delete session row AND clear the cookie
await db.session.delete({ where: { id: sessionId } });
(await cookies()).set("session", "", { httpOnly: true, maxAge: 0 });
```

### Common Mistakes

- 🚨 Logout that only clears the cookie but not the server session (session still valid if cookie is replayed).
- 🚨 No expiration → sessions live forever.
- 🚨 No session rotation on login — session fixation attacks.

### 🛠️ Practice

Implement logout (server session + cookie), session expiry (check `expiresAt` in `getSession`), and rotation (new session id on login).

### ✅ Checkpoint

- Why delete the server session on logout, not just the cookie?
- What does session rotation prevent?

---

## 🚨 Common Beginner Mistakes (Phase 14)

- Client-side-only authorization.
- Unhashed or fast-hashed passwords.
- Cookies without HttpOnly/Secure/SameSite.
- Trusting client-supplied ids.
- Role checks in the UI only.
- Logout that leaves the server session alive.
- Rolling your own crypto/session system when a library exists.

---

## ✅ Phase 14 Checkpoint

### What I Should Know

- [ ] Auth vs authorization
- [ ] Hashing, salting, slow algorithms
- [ ] Sessions, cookies, flags, DB vs JWT
- [ ] Server-side enforcement at all three layers
- [ ] RBAC and resource membership
- [ ] OAuth conceptually + a framework
- [ ] Logout, expiry, rotation

### Questions

1. Walk through a login: from form submit to "you're in." What's stored where, and why?
2. Why does `HttpOnly` matter? Why `SameSite=Lax`?
3. Where exactly do authorization checks belong? Give three places.
4. Roles vs membership — when do you need each?

### Coding Challenges

1. **Level 1:** Signup/login/logout with bcrypt + sessions + cookie flags.
2. **Level 2:** Protected dashboard, user-scoped data, ownership checks on every mutation.
3. **Level 3:** ADMIN/TEACHER/STUDENT with a role × permission matrix enforced server-side (guards in services). Seed all three roles and prove enforcement with tests or manual attempts.

### Design Challenge

Design auth for a multi-tenant app: users belong to workspaces; workspaces have OWNER/ADMIN/MEMBER; some resources are public. Map: tables, session flow, every check point, and how tenants stay isolated. Write the full design document.

### Ready to Continue?

✅ You can walk through a full secure login flow from memory.
✅ You built role enforcement that survives direct API calls.
✅ You can explain every cookie flag and why it's there.

---

# Phase 15 — Application Architecture

> **Prerequisite:** Phases 2–14. You've built features; now learn to structure growing apps so they stay maintainable.
> **Goal:** Know what goes where, when to add structure, and how to evolve architecture as the app grows — without over-engineering.

## 15.1 The Standard Next.js Folder Structure

### Concept

The common layout and what each folder is for:

```text
app/          ← routes only (pages, layouts, route handlers, special files)
components/   ← reusable React components (UI)
lib/          ← shared logic: utils, config, auth helpers
services/     ← business logic / use cases
actions/      ← Server Actions
api/          ← API client helpers (browser-side), if any
hooks/        ← custom React hooks
db/           ← database client, schema, seed, migrations
types/        ← shared TypeScript types
utils/        ← pure helpers (formatting, validators)
```

### Why It Exists

Structure is *communication*. A consistent layout lets any developer find anything instantly: "where's the delete logic? → services. Where's the button? → components." It also keeps dependencies flowing one way.

### Mental Model — dependency direction

```text
app (routes)      ──┐
components (UI)   ──┼──►  services (business logic)  ──►  db (data)
hooks             ──┘                │
                     lib (utils) ◄────┘

UI depends on services. Services depend on db.
NEVER: db imports from components. NEVER: services import UI.
```

### Common Mistakes

- 🚨 Putting components/logic inside `app/` — `app/` is for routes; colocating a helper next to a page is fine, but libraries and components belong outside.
- 🚨 A `utils/` dumping ground — give files real names (`utils/format.ts`, `utils/validation.ts`).
- 🚨 Circular imports (component ↔ service) — sign of misplaced responsibility.
- 🚨 Following a strict layer layout when a feature layout fits better (see 15.2).

### When to Use It / When NOT to Use It

Start with a *few* folders (app, components, lib, db) and add structure as real needs appear. Empty folders for hypothetical futures are clutter.

### Real-World Usage

Nearly every production Next.js repo looks close to this — with variations you can justify (e.g., `features/` for large feature modules).

### 🛠️ Practice

Restructure an app you've built into this layout. Move: server actions → `actions/`, business rules → `services/`, DB → `db/`, types → `types/`, hooks → `hooks/`. Verify nothing in `db/` imports from `components/`.

### ✅ Checkpoint

- What goes in each folder?
- What's the dependency direction, and why does it matter?

---

## 15.2 Layer-Based vs Feature-Based Architecture

### Concept

- **Layer-based:** folders by *kind* (components/, services/, db/) — the layout above.
- **Feature-based:** folders by *feature* (features/checkout/, features/auth/, each containing its own components + logic).

### Why It Exists

Layers scale horizontally (many files per kind); features scale vertically (everything for a feature in one place). As apps grow, features make it easier to change one area without touching others.

### Mental Model

```text
Layer-based:                    Feature-based:
components/                     features/
  Button.tsx                      auth/
  CheckoutForm.tsx                  components/, actions/, types/
services/                         checkout/
  checkout-service.ts               components/, services/, types/

growth signal: 1 file per kind → many files → consider feature modules
```

### Common Mistakes

- 🚨 Rigidly applying either pattern — most apps use a hybrid (layers for shared UI, features for big domains).
- 🚨 Reorganizing for the sake of it — architecture churn costs more than it saves.
- 🚨 Features that import from other features' internals (breaks the encapsulation).

### When to Use It / When NOT to Use It

Small apps: layers. Medium+: introduce feature folders for the biggest domains (auth, billing, projects). Keep shared UI in `components/` regardless.

### Real-World Usage

SaaS apps: `features/billing`, `features/teams`, `features/reports` — each owning its UI + services + types.

### 🛠️ Practice

Take a medium app (e.g., a project manager) and map it both ways: what would the layer layout look like? What would feature modules look like? Pick one feature to convert and justify the choice.

### ✅ Checkpoint

- When does feature-based beat layer-based?
- What stays shared regardless?

---

## 15.3 Separation of Concerns in Practice

### Concept

Three concerns, three homes: **UI** (components), **business logic** (services), **data access** (db layer). Validation sits at the boundary (Zod in actions/APIs).

### Why It Exists

Mixed concerns are why apps become unmaintainable: a component that queries the DB, formats, and decides business rules can't be tested, reused, or understood. Separation makes each layer independently testable and replaceable.

### Mental Model

```text
Component (presentation) ──► Service (rules) ──► DB (storage)
                              │
                              └─ validation + authz at the boundary
```

### Common Mistakes

- 🚨 Business logic in components (un-testable, duplicated).
- 🚨 Components importing the DB client directly (couples UI to storage).
- 🚨 Validation scattered across the app instead of at boundaries.
- 🚨 Over-layering: a service that just forwards to a query (ceremony without value).

### When to Use It / When NOT to Use It

Separate concerns when there ARE concerns — rules, auth, transactions, multi-step flows. Pure CRUD passthrough doesn't need three layers.

### Real-World Usage

"Where does 'only the owner can archive' live?" — in the service, called by both the Server Action and the API route.

### 🛠️ Practice

Audit your app: find one component doing three jobs (render + fetch + business rule). Split it. Then find one service that's a pointless passthrough and inline it. Learn both directions of the balance.

### ✅ Checkpoint

- Name the three concerns and their homes.
- When is adding a service layer wrong?

---

<!-- CONTINUE_15 -->
