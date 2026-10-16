---
title: "Architecture and Data Flows"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "29:24"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# Architecture and Data Flows

> **Video timestamp:** [29:24](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=1764s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

A high-level architecture diagram should explain responsibilities and how data moves—not merely list technologies.

### Typical request path
Client → DNS/edge → load balancer → API/application → cache and/or database → response.

Asynchronous work may flow through:
Application → durable queue/log → worker → database, search index, notification service, or object storage.

### Design principles
- Keep the request path short for latency-sensitive operations.
- Separate synchronous user feedback from slow background work when product semantics allow it.
- Define service ownership and data ownership.
- Make failure boundaries visible: timeouts, retries, circuit breakers, dead-letter handling.
- Avoid introducing a separate service for every entity without a clear reason.

### Diagram conventions
Label protocols, direction of data flow, trust boundaries, and whether communication is synchronous or asynchronous. Show external dependencies and important data stores.

### Review questions
- What happens if the database is slow?
- Can a retry duplicate a write?
- Is a queued event durable?
- How does the system recover from a worker crash?


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
