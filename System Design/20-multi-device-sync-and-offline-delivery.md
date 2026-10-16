---
title: "Multi-Device Sync and Offline Delivery"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "2:13:10"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# Multi-Device Sync and Offline Delivery

> **Video timestamp:** [2:13:10](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=7990s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

Multi-device synchronization requires explicit rules for ordering, acknowledgements, and resuming after disconnection.

### Core concepts
- **Message ID:** stable identity for deduplication.
- **Conversation sequence or cursor:** enables ordered replay within a defined scope.
- **Delivery acknowledgement:** a device confirms receipt or persistence.
- **Read receipt:** a separate semantic signal that the user viewed content.
- **Sync cursor:** lets a reconnecting device request events after its last known position.

### Offline delivery
Persist messages first, then notify connected devices. If a device is offline, it can fetch missed messages later. Push notifications are useful wake-up signals but should not be treated as the source of truth.

### Duplicate and ordering handling
Networks can retry and reorder delivery. Clients should deduplicate by stable IDs and apply the server's ordering policy. Global ordering across every conversation may be unnecessary and expensive.

### Conflicts
For user-authored edits or multi-device state changes, define merge rules. Some fields can use last-write-wins; others require versioning, conflict prompts, or domain-specific merging.

### Privacy
Protect sync endpoints with authorization and avoid leaking conversation metadata through notifications or logs.


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
