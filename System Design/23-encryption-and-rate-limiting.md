---
title: "Encryption and Rate Limiting"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "2:39:18"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# Encryption and Rate Limiting

> **Video timestamp:** [2:39:18](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=9558s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

Security controls should be built into the architecture rather than added only after launch.

### Encryption
- **In transit:** TLS protects communication between clients and services.
- **At rest:** storage-level or application-level encryption protects persisted data.
- **Key management:** restrict access, rotate keys, audit use, and separate keys from encrypted data.
- **End-to-end encryption:** only endpoints hold decryption keys; this changes search, moderation, recovery, and multi-device design.

### Rate limiting
Protects services from abuse, accidental overload, and unfair resource consumption.

Common algorithms:
- Fixed window: simple but allows boundary bursts.
- Sliding window: smoother enforcement.
- Token bucket: supports controlled bursts while limiting average rate.
- Leaky bucket: smooths output rate.

### Where to enforce
Use edge limits for broad traffic protection and application-level limits for identity, tenant, endpoint, or business-operation quotas. Distributed limits may need a shared store or carefully designed local approximations.

### Security essentials
Avoid logging secrets or sensitive payloads, validate inputs, use least privilege, and return safe errors. Rate limiting is not a replacement for authentication or authorization.


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
