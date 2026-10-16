---
title: "Capacity Math and Architecture"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "58:22"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# Capacity Math and Architecture

> **Video timestamp:** [58:22](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=3502s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

Use approximate arithmetic to catch architecture designs that cannot plausibly meet the workload.

### Useful calculations
- Requests/s = total requests in a period ÷ seconds in that period.
- Concurrent requests ≈ request rate × average response time (Little's Law, under steady-state assumptions).
- Storage growth = write volume × average record size × time.
- Egress bandwidth = response rate × average response size.
- Replica storage ≈ primary data size × number of stored copies, plus indexes and overhead.

### Example
At 2,000 requests/s and an average response time of 0.15 s, expected in-flight requests are approximately 300. This is not the same as the number of users online.

### Architecture implications
- High read volume may justify caching or read replicas.
- High write volume may require partitioning, batching, or asynchronous processing.
- Large media payloads should generally be served from object storage/CDNs rather than application servers.
- Traffic spikes require headroom, queues, admission control, or autoscaling.

### Caveats
Average values hide burstiness and tail latency. Estimate peak traffic and test realistic distributions; include retries because retries can amplify overload.


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
