---
title: "Failure Handling and Global Scaling"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "2:57:53"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# Failure Handling and Global Scaling

> **Video timestamp:** [2:57:53](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=10673s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

Failures are normal in distributed systems. Design for partial failure rather than assuming every dependency is always available.

### Resilience patterns
- Timeouts on remote calls.
- Bounded retries with exponential backoff and jitter.
- Circuit breakers to stop repeatedly calling an unhealthy dependency.
- Bulkheads to isolate resource pools.
- Load shedding and admission control under overload.
- Graceful degradation for non-essential features.
- Health checks and automated recovery.

### Global scaling
Multiple regions can improve latency and disaster recovery, but introduce replication lag, routing decisions, data residency concerns, and failover complexity.

### Recovery objectives
- **RPO:** maximum acceptable data loss measured in time.
- **RTO:** target time to restore service.

### Failure-mode questions
- What if the queue is unavailable?
- What if a region is healthy but its database is stale?
- What if retries multiply traffic during an outage?
- Can the system reject noncritical work while preserving core actions?

### Practice
Draw the failure path for every critical dependency and state what the user sees, what data can be lost, and how recovery is verified.


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
