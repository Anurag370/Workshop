---
title: "Concurrency and Race Conditions"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "1:33:05"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# Concurrency and Race Conditions

> **Video timestamp:** [1:33:05](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=5585s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

A race condition occurs when the result depends on the timing or interleaving of concurrent operations.

### Example: lost update
Two requests read a counter value of 10. Both add 1 and write 11. One increment is lost.

### Prevention strategies
- Atomic database operations.
- Transactions with suitable isolation.
- Row-level locks for narrow contention points.
- Optimistic concurrency using version columns.
- Unique constraints to enforce invariants at the database boundary.
- Distributed locks only when necessary and with careful lease/failure semantics.

### Retries
Retry only when the operation is safe to retry or protected by idempotency. Use bounded retries, exponential backoff, and jitter. Unbounded retries can worsen an outage.

### Isolation and contention
Stronger transaction isolation can prevent anomalies but may increase locking or aborts. Choose based on the invariant that must hold, not by blindly selecting the strongest setting.

### Test strategy
Run concurrent integration tests against the real database engine, and verify invariants after many competing operations.


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
