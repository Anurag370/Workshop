---
title: "API Design"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "35:23"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# API Design

> **Video timestamp:** [35:23](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=2123s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

APIs define the contract between clients and a service. Good APIs make operations predictable, secure, evolvable, and observable.

### Design checklist
- Use resource-oriented names and consistent HTTP semantics where appropriate.
- Validate input and return structured errors.
- Define pagination, filtering, sorting, and field selection for collection endpoints.
- Specify authentication and authorization separately.
- Set timeouts and payload-size limits.
- Version APIs deliberately; prefer compatible additions when possible.

### Example
`GET /tracks/{track_id}` retrieves a track.
`POST /playback-sessions` creates a playback session.
`GET /tracks?artist_id=...&limit=20&cursor=...` retrieves a page.

### Pagination
Offset pagination is simple but can become expensive and unstable as data changes. Cursor pagination is often better for large, frequently changing collections; the cursor should represent a stable ordering.

### Errors
Return actionable, machine-readable error codes and safe messages. Do not expose stack traces, secrets, or internal database details.

### Security
Enforce authorization on the server for every protected resource. Never trust a client-supplied user ID as proof of identity.


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
