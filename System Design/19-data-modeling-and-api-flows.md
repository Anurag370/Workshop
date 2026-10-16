---
title: "Data Modeling and API Flows"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "2:07:04"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# Data Modeling and API Flows

> **Video timestamp:** [2:07:04](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=7624s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

A data model should encode domain concepts and support the system's critical access patterns.

### Modeling process
1. Identify entities and their lifecycle.
2. Define relationships and ownership.
3. List important reads and writes.
4. Establish invariants and uniqueness constraints.
5. Decide which data is authoritative and which is derived.
6. Define deletion, retention, and migration behavior.

### API-flow walkthrough
For each major operation, document:
- Request and authorization checks.
- Validation and idempotency.
- Transaction boundaries.
- Database writes.
- Events emitted after commit.
- Response semantics and retry behavior.

### Example: sending a message
Validate membership → check idempotency → persist message and outbox event atomically → return accepted/persisted result → asynchronously deliver to recipient devices → record delivery acknowledgements if required.

### Outbox pattern
The transactional outbox avoids the dual-write problem where a database transaction succeeds but publishing its event fails. A worker publishes committed outbox rows and marks them processed; consumers should still be idempotent.


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
