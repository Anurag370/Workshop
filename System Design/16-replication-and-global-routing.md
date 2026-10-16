---
title: "Replication and Global Routing"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "1:45:19"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# Replication and Global Routing

> **Video timestamp:** [1:45:19](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=6319s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

Replication maintains copies of data or services to improve read capacity, availability, or geographic performance.

### Replication models
- **Synchronous:** acknowledge after required replicas confirm; can improve durability but adds latency and may reduce write availability during failures.
- **Asynchronous:** acknowledge before all replicas catch up; lower write latency but permits replication lag and potential loss of recent acknowledged writes during some failures.

### Global routing
DNS-based routing, anycast, or a global load balancer can direct users to a nearby or healthy region. “Nearest” is not always “best”; health, capacity, data residency, and session state matter.

### Multi-region questions
- Which region owns a write?
- How are conflicts resolved?
- Can a region be isolated safely?
- How are failover and failback tested?
- What are RPO and RTO targets?
- Does the application require globally consistent writes?

### Common starting point
For many applications, one primary write region plus read replicas or regional caches is simpler than active-active multi-region writes. Use active-active only when requirements justify its complexity.


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
