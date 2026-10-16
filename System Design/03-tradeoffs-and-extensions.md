---
title: "Trade-offs and Extensions"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "18:24"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# Trade-offs and Extensions

> **Video timestamp:** [18:24](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=1104s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

Architecture is a set of trade-offs, not a universal recipe.

### Common trade-off dimensions
- **Consistency vs availability during network partitions:** distributed replicas may not all be able to serve the newest value.
- **Latency vs durability:** synchronous replication can improve durability but add write latency.
- **Read speed vs freshness:** caches reduce latency but introduce invalidation and staleness concerns.
- **Simplicity vs independent scaling:** a modular monolith is often simpler initially; separately deployed services can scale and release independently but add network and operational complexity.
- **Cost vs resilience:** redundancy improves fault tolerance but consumes extra capacity.

### How to justify a choice
1. Name the requirement.
2. State the options.
3. Describe what each option optimizes and sacrifices.
4. Select the option that meets the requirement with acceptable complexity.
5. State how you would validate the decision using metrics or load tests.

### Avoid false absolutes
“Always use Kafka,” “SQL never scales,” and “microservices are more scalable” are not sound design arguments. Context and workload determine the answer.


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
