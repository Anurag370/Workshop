---
title: "API Design and Idempotency"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "1:11:02"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# API Design and Idempotency

> **Video timestamp:** [1:11:02](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=4262s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

Idempotency means that repeating an operation with the same intent does not produce additional unintended effects.

### Why it matters
Clients retry after timeouts, but a timeout does not prove that the server failed to commit. A payment or booking might have succeeded even though the response was lost.

### Idempotency-key pattern
1. Client generates a unique key for one logical operation.
2. Server stores the key with the operation result and relevant request fingerprint.
3. A repeated request with the same key returns the recorded result rather than repeating the side effect.
4. Reusing a key with a different payload should be rejected.
5. Retain keys long enough to cover realistic retry windows.

### Important details
- Enforce uniqueness atomically in the database.
- Define behavior for in-progress requests.
- Do not rely on an in-memory cache alone if requests can reach different instances.
- Idempotency does not replace authorization, validation, or transaction design.

### Example
`POST /payments` with `Idempotency-Key: ...` should create at most one logical payment for that key, even if the client retries.


## Lecture-specific notes
_Add instructor-specific examples, diagrams, terminology, or corrections while watching._

## Quick revision
- What problem does this chapter address?
- Which requirements or constraints affect the design?
- What is one common failure mode?
- What trade-off would you explain in a system-design interview?

## Further practice
- Draw the relevant architecture or data flow.
- State one assumption and explain how changing it would alter the design.
- Describe one metric or test that would validate the design.
