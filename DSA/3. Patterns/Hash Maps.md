---
type: pattern
created: 2026-08-23
---
# Hash Maps

## When to Use

- When you need to quickly check whether an element or value has already been seen.
- When you need to store and retrieve data using a **key → value** relationship.
- When counting frequencies or tracking occurrences of elements.
- When a brute-force solution uses nested loops to search for a matching element and can be optimized with constant-time average lookups.

---

## Recognition Clues

- The problem asks for **frequency/count** of elements.
- You need to find **duplicates** or determine whether something has already appeared.
- You need to find a **pair** that satisfies a condition, such as a target sum.
- The problem involves mapping one value to another.
- You repeatedly need to check whether an element exists.
- A brute-force approach involves repeatedly searching through previously processed elements.

---

## Template Code

```cpp
#include <unordered_map>
using namespace std;

unordered_map<int, int> mp;

for (int i = 0; i < n; i++)
{
    int value = arr[i];

    // Check if value exists
    if (mp.find(value) != mp.end())
    {
        // Value already exists
    }

    // Store or update value
    mp[value]++;
}
```

---

## Common Problems

- Two Sum
- Contains Duplicate
- Valid Anagram
- Group Anagrams
- Majority Element
- First Unique Character in a String
- Subarray Sum Equals K
- Longest Consecutive Sequence
- Top K Frequent Elements
- Longest Substring Without Repeating Characters