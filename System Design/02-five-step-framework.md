---
title: "The Five-Step System Design Framework"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "09:14"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# The Five-Step System Design Framework

> **Video timestamp:** [09:14](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=554s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

Use a repeatable structure to prevent an open-ended problem from becoming an unorganized list of technologies.

### Step 1 — Requirements
Separate core user-visible features from constraints such as latency, availability, privacy, durability, and retention.

### Step 2 — Estimation
Estimate users, requests per second, storage growth, bandwidth, and peak-to-average ratios. Write assumptions so they can be challenged.

### Step 3 — API and data model
Define important operations and entities before choosing infrastructure. Identify ownership, uniqueness constraints, and consistency needs.

### Step 4 — High-level architecture
Trace a typical request from client to API, application logic, cache, database, queues, and downstream workers.

### Step 5 — Deep dives and trade-offs
Pick the highest-risk areas: hot keys, concurrency, search, fan-out, media delivery, regional failure, or security. Explain alternatives and why the chosen design fits.

### Interview pacing
Reserve time for clarification, baseline design, one or two meaningful deep dives, and a final recap. Adapt the allocation to the interview duration.

### Checklist
- [ ] Functional requirements
- [ ] Non-functional targets
- [ ] Back-of-the-envelope estimates
- [ ] API and schema
- [ ] Architecture and request flow
- [ ] Bottlenecks, failure handling, trade-offs


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
