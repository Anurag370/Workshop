---
title: "Sharding and Cleanup Jobs"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "2:49:45"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# Sharding and Cleanup Jobs

> **Video timestamp:** [2:49:45](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=10185s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

Partitioning distributes data and workload. Cleanup jobs enforce lifecycle policies and remove expired or obsolete records.

### Sharding design
- Pick a shard key that distributes load while supporting common queries.
- Avoid monotonically increasing keys if they create a single hot partition in the chosen storage system.
- Plan cross-shard queries, uniqueness, transactions, and rebalancing.
- Monitor skew and per-shard capacity.

### Cleanup jobs
Examples include expired booking holds, old temporary uploads, obsolete sessions, expired idempotency keys, and retained event data.

### Safe cleanup pattern
1. Define a precise expiry rule.
2. Query candidates in bounded batches.
3. Make deletion idempotent.
4. Avoid locking huge ranges in one transaction.
5. Track progress and failures.
6. Ensure cleanup cannot delete data still needed for recovery or legal retention.

### Soft vs hard deletion
Soft deletion can support recovery and audit, but requires clear retention and access-control rules. Hard deletion may be necessary for privacy or storage cost, and must account for replicas, indexes, backups, and derived data.


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
