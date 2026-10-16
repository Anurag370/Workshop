---
title: "Non-Functional Targets"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "50:52"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# Non-Functional Targets

> **Video timestamp:** [50:52](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=3052s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

Non-functional requirements should be measurable and tied to user experience.

### Important targets
- **Latency:** response time, commonly reported as p50, p95, and p99.
- **Availability:** proportion of time a service fulfills its contract.
- **Durability:** probability that acknowledged data remains available after failures.
- **Scalability:** ability to handle increased load.
- **Security:** confidentiality, integrity, authentication, authorization, and auditability.
- **Maintainability:** ability to change the system safely.
- **Cost efficiency:** resource consumption relative to workload.

### SLI, SLO, and SLA
- **SLI:** measured indicator, such as successful requests or p95 latency.
- **SLO:** internal target for an SLI over a window.
- **SLA:** formal commitment with consequences if the commitment is missed.

### Reliability math
If a service has 99.9% availability, its theoretical downtime budget over 30 days is about 43.2 minutes. Dependencies can reduce end-to-end availability.

### Define the failure mode
“Fast” is vague. “95% of read requests complete within 200 ms at the expected peak load” is testable.


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
