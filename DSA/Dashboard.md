# 🚀 DSA Dashboard

> "Learn → Understand → Practice → Revise → Repeat"

---

# 🎯 Current Goal

- [ ] Finish Arrays
- [ ] Solve 3 Easy Problems
- [ ] Learn Binary Search
- [ ] Revise Previous Problems

---

# 📂 Quick Navigation

## 📚 Topics

- [[Arrays]]

---

## ⚙️ Algorithms

- [[Binary Search]]

---

## 🧩 Patterns

```dataview
LIST
FROM "Vault/DSA/Patterns"
SORT file.name ASC
```


---

## 🎨 Excalidraw

```dataview
LIST
FROM "Vault/DSA/Excalidraw"
SORT file.name ASC
```

---

# 📝 Recently Created Problems

```dataview
TABLE
difficulty AS "Difficulty",
status AS "Status",
file.ctime AS "Created"
FROM "Vault/DSA/Problems"
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
FROM "Vault/DSA/Problems"
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
FROM "Vault/DSA/Problems"
WHERE status != "Solved"
SORT difficulty ASC
```

---

# ✅ Solved Problems

```dataview
TABLE
difficulty,
topic
FROM "Vault/DSA/Problems"
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
FROM "Vault/DSA/Problems"
WHERE difficulty="Easy" AND status="Solved"
GROUP BY ""
```

---

# 📈 Medium Problems

```dataview
TABLE WITHOUT ID
length(rows) AS "Solved Medium"
FROM "Vault/DSA/Problems"
WHERE difficulty="Medium" AND status="Solved"
GROUP BY ""
```

---

# 📈 Hard Problems

```dataview
TABLE WITHOUT ID
length(rows) AS "Solved Hard"
FROM "Vault/DSA/Problems"
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
FROM "Vault/DSA/Problems"
WHERE contains(topic,"Arrays")
```

## Strings

```dataview
TABLE
difficulty,
status
FROM "Vault/DSA/Problems"
WHERE contains(topic,"Strings")
```

## Trees

```dataview
TABLE
difficulty,
status
FROM "Vault/DSA/Problems"
WHERE contains(topic,"Trees")
```

## Graphs

```dataview
TABLE
difficulty,
status
FROM "Vault/DSA/Problems"
WHERE contains(topic,"Graphs")
```

---

# 🧩 Problems by Pattern

## Sliding Window

```dataview
TABLE
difficulty,
status
FROM "Vault/Vault/DSA/Problems"
WHERE contains(pattern,"Sliding Window")
```

## Two Pointers

```dataview
TABLE
difficulty,
status
FROM "Vault/DSA/Problems"
WHERE contains(pattern,"Two Pointers")
```

## Binary Search

```dataview
TABLE
difficulty,
status
FROM "Vault/DSA/Problems"
WHERE contains(pattern,"Binary Search")
```

---

# ⭐ Important Notes

- [[Time Complexity]]
- [[Space Complexity]]
- [[STL Cheat Sheet]]
- [[Fast IO]]
- [[Recursion]]
- [[Binary Search Template]]

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