---
title: "Scaling to Millions"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "44:37"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# Scaling to Millions

> **Video timestamp:** [44:37](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=2677s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

Scale incrementally by measuring the limiting resource.

### Common progression
1. Optimize queries and add appropriate indexes.
2. Add caching for repeated, safe-to-cache reads.
3. Use connection pooling and tune resource limits.
4. Scale the application horizontally behind a load balancer.
5. Move slow work to background workers.
6. Add read replicas or partitioning when the workload justifies them.
7. Consider sharding or multi-region architecture only after simpler approaches are insufficient.

### Vertical vs horizontal scaling
- **Vertical:** larger machine; operationally simple but has hardware and failure-domain limits.
- **Horizontal:** more instances; improves capacity and resilience but requires statelessness, coordination, and distributed observability.

### Watch for bottlenecks
CPU, memory, database locks, connection pools, disk I/O, network bandwidth, cache misses, and downstream rate limits can each become the limiting factor.

### Rule
Do not optimize for “millions” as a slogan. Derive expected workload, load-test it, measure the bottleneck, and add the smallest effective change.


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
