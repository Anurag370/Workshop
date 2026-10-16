---
title: "How to Actually Get Better"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "3:11:14"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# How to Actually Get Better

> **Video timestamp:** [3:11:14](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=11474s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

System design improves through deliberate practice, explicit feedback, and reviewing the consequences of decisions.

### Practice loop
1. Choose a bounded problem: URL shortener, booking system, chat, feed, or file storage.
2. Write requirements and assumptions.
3. Estimate scale before drawing architecture.
4. Sketch APIs, data model, and request flows.
5. Identify the two biggest risks and deep-dive them.
6. Explain trade-offs aloud.
7. Compare with alternative designs and identify what each optimizes.
8. Repeat under a time limit.

### Build, do not only memorize
Implement small pieces: cursor pagination, idempotent writes, background jobs, caching, rate limiting, metrics, and failure tests. Hands-on work reveals operational costs that diagrams hide.

### Keep a design journal
For each design, record:
- Requirements and assumptions.
- Chosen architecture.
- Alternatives rejected and why.
- Expected bottlenecks.
- Failure modes and recovery.
- What measurements would change the design.

### Final self-assessment
Can you justify every major component? Can you explain how the system fails? Can you evolve the design without rewriting everything? If not, focus your next practice session on that gap.


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
