---
title: "Scale Estimation"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "1:50:45"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# Scale Estimation

> **Video timestamp:** [1:50:45](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=6645s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

Scale estimation is a structured approximation, not a precision forecast.

### Estimate these dimensions
1. Active users and actions per user.
2. Average and peak requests per second.
3. Read/write ratio.
4. Record size and retention period.
5. Media storage and delivery bandwidth.
6. Number of concurrent connections.
7. Queue throughput and processing lag.

### Example: messages
If 500,000 daily users send 30 messages each, that is 15 million messages/day, or about 174 messages/s average. A peak factor of 5 gives about 870 messages/s before accounting for retries, fan-out, or other operations.

### Capacity implications
One message may cause multiple writes: message storage, conversation metadata, recipient delivery state, search indexing, and notifications. Model the actual work, not just the public API call.

### Sanity checks
- Convert units consistently.
- Distinguish average from peak.
- Account for replication and indexes.
- Include growth and safety headroom.
- State uncertainty and validate estimates with load tests.


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
