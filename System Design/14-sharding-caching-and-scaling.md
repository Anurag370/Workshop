---
title: "Sharding, Caching and Scaling"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "1:34:44"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# Sharding, Caching and Scaling

> **Video timestamp:** [1:34:44](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=5684s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

Sharding and caching solve different problems.

### Caching
Stores reusable results closer to the caller. Common patterns include cache-aside, read-through, and write-through.

Key concerns:
- TTL and invalidation.
- Stale data tolerance.
- Cache stampedes and hot keys.
- Memory limits and eviction.
- Cache failure behavior.

### Sharding
Splits data across partitions, usually using a shard key. A good key distributes load and allows common queries to target a limited number of shards.

Challenges:
- Skew and hot partitions.
- Cross-shard queries and transactions.
- Resharding and data migration.
- Global uniqueness and routing.
- Operational complexity.

### Choosing the right tool
- Repeated reads: investigate caching.
- Database read pressure: indexes, query tuning, caching, or replicas may help.
- Dataset or write load beyond one database's capacity: partitioning/sharding may be appropriate.
- CPU-heavy work: scale compute or move work to workers.

### Principle
Caching can hide a poor query temporarily; sharding can make a simple system much harder to operate. Measure first.


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
