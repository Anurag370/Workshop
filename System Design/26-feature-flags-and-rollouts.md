---
title: "Feature Flags and Rollouts"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "3:09:08"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# Feature Flags and Rollouts

> **Video timestamp:** [3:09:08](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=11348s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

Feature flags separate deploying code from enabling a feature for users.

### Common uses
- Gradual rollouts by percentage, tenant, or cohort.
- Kill switches for risky functionality.
- Experiments and controlled comparisons.
- Entitlement or plan-based feature access.
- Migration between implementations.

### Safe rollout
1. Deploy code with the feature disabled or limited.
2. Validate in test/staging.
3. Enable for internal users.
4. Increase exposure gradually.
5. Monitor error rate, latency, business metrics, and support signals.
6. Pause or roll back if guardrails regress.
7. Remove obsolete flags after the rollout is complete.

### Risks
- Stale flags create branching complexity.
- Client-side flags are not security controls.
- Database migrations may not be safely reversible.
- A flag service outage needs defined fallback behavior.

### Database migrations
Prefer expand-and-contract: add compatible schema, deploy code that supports old and new forms, migrate data, switch reads/writes, then remove obsolete schema only after compatibility is verified.


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
