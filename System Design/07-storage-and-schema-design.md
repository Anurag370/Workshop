---
title: "Storage and Schema Design"
course: "Design Software Systems Like a Senior Engineer"
chapter_timestamp: "40:04"
source: "https://www.youtube.com/watch?v=soTfFFIQQ8U"
tags:
  - system-design
  - software-architecture
  - study-notes
---

# Storage and Schema Design

> **Video timestamp:** [40:04](https://www.youtube.com/watch?v=soTfFFIQQ8U&t=2404s)  
> **Source note:** These are chapter-aligned study notes based on the public chapter heading and standard system-design knowledge, not a verified lecture transcript.

## Learning objectives
- Explain the central concepts in this section.
- Identify relevant design constraints and trade-offs.
- Apply the ideas to a realistic system.

Choose storage based on access patterns, consistency, data shape, and operational needs—not popularity.

### Relational databases
Good for structured entities, constraints, transactions, joins, and relationships. Model primary keys, foreign keys, uniqueness, and indexes intentionally.

### NoSQL and specialized stores
- Key-value: simple key-based access.
- Document: flexible, aggregate-oriented records.
- Wide-column: high-volume partitioned access patterns.
- Search engine: full-text retrieval and relevance ranking.
- Object storage: large blobs such as audio, images, and video.
- Time-series store: timestamped measurements.

### Schema workflow
1. List important queries and writes.
2. Identify entities and relationships.
3. Choose keys and uniqueness constraints.
4. Add indexes that support real queries.
5. Plan migrations and backfills.
6. Test with realistic data volume.

### Example entities for a streaming service
`User`, `Track`, `Artist`, `Playlist`, `PlaylistTrack`, `PlaybackEvent`. Store media files in object storage and metadata in a database; do not normally store large audio blobs directly in relational rows.

### Important distinction
A search index is usually a derived view, not the authoritative source of truth. Plan how it is updated and rebuilt.


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
