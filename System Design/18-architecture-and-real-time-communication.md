---
title: "Architecture and Real-Time Communication"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "1:56:38"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# Architecture and Real-Time Communication

> **Video timestamp:** [1:56:38](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=6998s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

Real-time applications deliver updates with low delay while handling reconnects, backpressure, and large numbers of concurrent clients.

### Communication choices
- **Polling:** clients repeatedly ask for updates; simple but may waste requests.
- **Long polling:** server holds a request until an update or timeout.
- **Server-Sent Events (SSE):** server-to-client event stream over HTTP.
- **WebSockets:** persistent bidirectional connection, useful for chat and interactive sessions.

### Typical components
Client → edge/load balancer → connection gateway → message/event service → durable storage and delivery infrastructure.

### Important concerns
- Authentication and authorization at connection and message levels.
- Heartbeats, idle timeouts, reconnect backoff, and resume cursors.
- Connection limits and per-user/device presence.
- Backpressure for slow consumers.
- Durable message storage separate from transient socket delivery.
- Horizontal routing for users connected to different gateway instances.

### Key distinction
A successful socket send does not necessarily mean the recipient has persisted or read the message. Define delivery and acknowledgement semantics explicitly.


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
