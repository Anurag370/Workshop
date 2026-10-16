# Design Software Systems Like a Senior Engineer — Course Notes

**Video:** [https://www.youtube.com/watch?v=soTfFFIQQ8U](https://www.youtube.com/watch?v=soTfFFIQQ8U)  
**Format:** One Markdown file per listed timestamp section  
**Purpose:** Obsidian-friendly study notes for system design and architecture.

## Important source note
These notes were drafted from the publicly available video title and chapter timestamps, combined with established system-design concepts. I could verify the chapter list, but I could not retrieve and inspect the full lecture transcript in this session. Therefore, these files are **chapter-aligned study notes, not a verified transcript or a claim that every detail below was explicitly stated by the instructor**. Use the timestamps to follow along and amend notes with lecture-specific details.

## Contents
- [[00-why-system-design-matters|00:00 — Why System Design Matters]]
- [[01-interview-formats-overview|02:16 — Interview Formats Overview]]
- [[02-five-step-framework|09:14 — The Five-Step System Design Framework]]
- [[03-tradeoffs-and-extensions|18:24 — Trade-offs and Extensions]]
- [[04-requirements-and-capacity-planning|23:55 — Requirements and Capacity Planning]]
- [[05-architecture-and-data-flows|29:24 — Architecture and Data Flows]]
- [[06-api-design|35:23 — API Design]]
- [[07-storage-and-schema-design|40:04 — Storage and Schema Design]]
- [[08-scaling-to-millions|44:37 — Scaling to Millions]]
- [[09-non-functional-targets|50:52 — Non-Functional Targets]]
- [[10-capacity-math-and-architecture|58:22 — Capacity Math and Architecture]]
- [[11-api-design-and-idempotency|1:11:02 — API Design and Idempotency]]
- [[12-data-modeling-and-inventory-logic|1:22:34 — Data Modeling and Inventory Logic]]
- [[13-concurrency-and-race-conditions|1:33:05 — Concurrency and Race Conditions]]
- [[14-sharding-caching-and-scaling|1:34:44 — Sharding, Caching and Scaling]]
- [[15-search-at-scale-elasticsearch|1:40:41 — Search at Scale with Elasticsearch]]
- [[16-replication-and-global-routing|1:45:19 — Replication and Global Routing]]
- [[17-scale-estimation|1:50:45 — Scale Estimation]]
- [[18-architecture-and-real-time-communication|1:56:38 — Architecture and Real-Time Communication]]
- [[19-data-modeling-and-api-flows|2:07:04 — Data Modeling and API Flows]]
- [[20-multi-device-sync-and-offline-delivery|2:13:10 — Multi-Device Sync and Offline Delivery]]
- [[21-fanout-media-storage-cdn|2:22:37 — Fan-out, Media Storage and CDN Delivery]]
- [[22-event-driven-and-batch-processing|2:31:44 — Event-Driven Architecture and Batch Processing]]
- [[23-encryption-and-rate-limiting|2:39:18 — Encryption and Rate Limiting]]
- [[24-sharding-and-cleanup-jobs|2:49:45 — Sharding and Cleanup Jobs]]
- [[25-failure-handling-and-global-scaling|2:57:53 — Failure Handling and Global Scaling]]
- [[26-feature-flags-and-rollouts|3:09:08 — Feature Flags and Rollouts]]
- [[27-how-to-actually-get-better|3:11:14 — How to Actually Get Better]]

## Suggested study workflow
1. Watch the chapter at its timestamp.
2. Read the corresponding note.
3. Add examples or corrections from the lecture under **Lecture-specific notes**.
4. Answer the revision prompts without looking.
5. Build a small implementation or diagram for the concepts that matter most.

## Progress tracker
- [ ] [[00-why-system-design-matters|Why System Design Matters]]
- [ ] [[01-interview-formats-overview|Interview Formats Overview]]
- [ ] [[02-five-step-framework|The Five-Step System Design Framework]]
- [ ] [[03-tradeoffs-and-extensions|Trade-offs and Extensions]]
- [ ] [[04-requirements-and-capacity-planning|Requirements and Capacity Planning]]
- [ ] [[05-architecture-and-data-flows|Architecture and Data Flows]]
- [ ] [[06-api-design|API Design]]
- [ ] [[07-storage-and-schema-design|Storage and Schema Design]]
- [ ] [[08-scaling-to-millions|Scaling to Millions]]
- [ ] [[09-non-functional-targets|Non-Functional Targets]]
- [ ] [[10-capacity-math-and-architecture|Capacity Math and Architecture]]
- [ ] [[11-api-design-and-idempotency|API Design and Idempotency]]
- [ ] [[12-data-modeling-and-inventory-logic|Data Modeling and Inventory Logic]]
- [ ] [[13-concurrency-and-race-conditions|Concurrency and Race Conditions]]
- [ ] [[14-sharding-caching-and-scaling|Sharding, Caching and Scaling]]
- [ ] [[15-search-at-scale-elasticsearch|Search at Scale with Elasticsearch]]
- [ ] [[16-replication-and-global-routing|Replication and Global Routing]]
- [ ] [[17-scale-estimation|Scale Estimation]]
- [ ] [[18-architecture-and-real-time-communication|Architecture and Real-Time Communication]]
- [ ] [[19-data-modeling-and-api-flows|Data Modeling and API Flows]]
- [ ] [[20-multi-device-sync-and-offline-delivery|Multi-Device Sync and Offline Delivery]]
- [ ] [[21-fanout-media-storage-cdn|Fan-out, Media Storage and CDN Delivery]]
- [ ] [[22-event-driven-and-batch-processing|Event-Driven Architecture and Batch Processing]]
- [ ] [[23-encryption-and-rate-limiting|Encryption and Rate Limiting]]
- [ ] [[24-sharding-and-cleanup-jobs|Sharding and Cleanup Jobs]]
- [ ] [[25-failure-handling-and-global-scaling|Failure Handling and Global Scaling]]
- [ ] [[26-feature-flags-and-rollouts|Feature Flags and Rollouts]]
- [ ] [[27-how-to-actually-get-better|How to Actually Get Better]]
