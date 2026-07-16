# 🚀 DSA Dashboard

> "Learn → Understand → Practice → Revise → Repeat"

---

# 🎯 Current Goal

- [x] Finish Arrays
- [x] Learn Linear Search
- [x] Learn Reversing
- [ ] Solve 3 Easy Problems
- [ ] Learn Binary Search
- [ ] Revise Previous Problems

---

# 📂 Quick Navigation

## 📚 Topics

- [[Arrays]]

---

## ⚙️ Algorithms

- [[Linear Search|Linear Search]]
- [[Reverse Array]]
- [[Binary Search]]

---

## 🧩 Patterns


---

# 📝 Recently Created Problems

```dataview
TABLE
difficulty AS "Difficulty",
status AS "Status",
file.ctime AS "Created"
FROM "DSA/Problems"
SORT file.ctime DESC
LIMIT 10
```

---

# ⭐ Recently Edited

```dataview
TABLE
file.mtime AS "Last Modified"
FROM "Vault/DSA"
SORT file.mtime DESC
LIMIT 10
```

---

# 🔄 Revision Queue

```dataview
TABLE
difficulty,
topic,
pattern
FROM "DSA/Problems"
WHERE revision = true
SORT difficulty
```

---

# 📚 Current Learning

- ✅ Arrays
- 🟨 Strings
- ⬜ Linked Lists
- ⬜ Stack
- ⬜ Queue
- ⬜ Trees
- ⬜ Graphs
- ⬜ Heap
- ⬜ Trie
- ⬜ Dynamic Programming

---

# 📋 Unsolved Problems

```dataview
TABLE
difficulty,
topic
FROM "DSA/Problems"
WHERE status != "Solved"
SORT difficulty ASC
```

---

# ✅ Solved Problems

```dataview
TABLE
difficulty,
topic
FROM "DSA/Problems"
WHERE status = "Solved"
SORT file.name
```

---

# 📅 Today's Tasks

```dataview
TASK
WHERE !completed
```

---

# 📈 Easy Problems

```dataview
TABLE WITHOUT ID
length(rows) AS "Solved Easy"
FROM "DSA/4. Problems"
WHERE difficulty="Easy" AND status="Solved"
GROUP BY ""
```

---

# 📈 Medium Problems

```dataview
TABLE WITHOUT ID
length(rows) AS "Solved Medium"
FROM "DSA/4. Problems"
WHERE difficulty="Medium" AND status="Solved"
GROUP BY ""
```

---

# 📈 Hard Problems

```dataview
TABLE WITHOUT ID
length(rows) AS "Solved Hard"
FROM "DSA/Problems"
WHERE difficulty="Hard" AND status="Solved"
GROUP BY ""
```

---

# 📚 Problems by Topic

## Arrays

```dataview
TABLE
difficulty,
status
FROM "DSA/Problems"
WHERE contains(topic,"Arrays")
```

## Strings

```dataview
TABLE
difficulty,
status
FROM "DSA/Problems"
WHERE contains(topic,"Strings")
```

## Trees

```dataview
TABLE
difficulty,
status
FROM "DSA/Problems"
WHERE contains(topic,"Trees")
```

## Graphs

```dataview
TABLE
difficulty,
status
FROM "DSA/Problems"
WHERE contains(topic,"Graphs")
```

---

# 🧩 Problems by Pattern

## Sliding Window

```dataview
TABLE
difficulty,
status
FROM "DSA/Problems"
WHERE contains(pattern,"Sliding Window")
```

## Two Pointers

```dataview
TABLE
difficulty,
status
FROM "DSA/Problems"
WHERE contains(pattern,"Two Pointers")
```

## Binary Search

```dataview
TABLE
difficulty,
status
FROM "DSA/Problems"
WHERE contains(pattern,"Binary Search")
```

---

# ⭐ Important Notes

- 


---

# 🌐 Resources

- LeetCode
- NeetCode
- GeeksforGeeks
- Visualgo
- CP Algorithms
- CppReference

---

# ❌ Common Mistakes

- Off-by-one errors
- Integer overflow
- Forgetting edge cases
- Missing base case in recursion
- Wrong Binary Search condition
- Modifying loop variable incorrectly

---

# 💡 Quote

> "Consistency beats intensity."