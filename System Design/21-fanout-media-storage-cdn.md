---
title: "Fan-out, Media Storage and CDN Delivery"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "2:22:37"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# Fan-out, Media Storage and CDN Delivery

> **Video timestamp:** [2:22:37](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=8557s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

Fan-out determines how one event reaches many recipients. Media delivery determines how large files are stored and served efficiently.

### Fan-out models
- **Fan-out on write:** precompute recipient feeds or delivery records when an event is created. Reads are fast, but writes can be expensive for large audiences.
- **Fan-out on read:** assemble results when the recipient requests them. Writes are cheap, but reads can be slower.
- **Hybrid:** use different strategies for ordinary and exceptionally large audiences.

### Media pipeline
Client requests upload authorization → uploads directly to object storage → service validates metadata and scans/processes media → transcoding or thumbnail jobs run asynchronously → CDN serves optimized assets.

### CDN benefits
Caches content near users, reducing origin load and latency. Cache keys, invalidation, signed URLs, geographic restrictions, and private content authorization must be designed carefully.

### Practical considerations
- Store metadata in a database and binary assets in object storage.
- Use lifecycle policies for old versions and temporary uploads.
- Consider multiple bitrates/resolutions for streaming.
- Protect against oversized files, malicious content, and hot objects.


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
