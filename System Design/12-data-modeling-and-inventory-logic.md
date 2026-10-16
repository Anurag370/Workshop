---
title: "Data Modeling and Inventory Logic"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "1:22:34"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# Data Modeling and Inventory Logic

> **Video timestamp:** [1:22:34](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=4954s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

Inventory-like systems must preserve invariants when multiple users compete for limited resources.

### Example invariant
For a bookable resource, confirmed reservations must never exceed available capacity.

### Possible data model
- `Resource(id, capacity, ...)`
- `Reservation(id, resource_id, user_id, status, ...)`
- A uniqueness rule for duplicate logical bookings where appropriate.

### Safe reservation approaches
- **Atomic conditional update:** decrement available inventory only if it is greater than zero.
- **Transaction and row lock:** serialize conflicting updates to the same inventory row.
- **Optimistic concurrency:** update only if a version number still matches; retry or report conflict otherwise.
- **Reservation/hold workflow:** temporarily hold inventory with an expiry, then confirm after payment or user action.

### Avoid
Reading availability and later writing a reservation as two unprotected operations. Two requests can both observe the same final unit and oversell it.

### Additional concerns
Handle hold expiry, payment failure, cancellation, duplicate requests, time zones, audit history, and reconciliation. State transitions should be explicit and validated.


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
