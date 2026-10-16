---
title: "Requirements and Capacity Planning"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "23:55"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# Requirements and Capacity Planning

> **Video timestamp:** [23:55](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=1435s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

Capacity planning turns product requirements into approximate resource needs.

### Requirements
**Functional:** what users can do, such as play a track, search listings, or send a message.

**Non-functional:** latency targets, availability, data durability, privacy, retention, geographic reach, and cost.

### Questions to clarify
- How many registered and daily active users?
- What are read/write ratios and peak traffic?
- Are requests latency-sensitive?
- How much data is created per user per day?
- Can stale data be tolerated?
- What is the recovery-point objective (RPO) and recovery-time objective (RTO)?

### Back-of-the-envelope formulas
- Average requests/s = daily requests ÷ 86,400.
- Peak requests/s ≈ average requests/s × peak factor.
- Raw storage = records/day × average bytes/record × retention days.
- Network throughput ≈ requests/s × average payload size.

Apply headroom for indexes, metadata, replicas, backups, and growth. These estimates are starting points; validate with realistic workload tests.

### Example
If 2 million daily users each make 20 API calls, that is 40 million calls/day, or about 463 requests/s on average. A peak factor of 4 gives roughly 1,850 requests/s at peak.


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
