---
type: pattern
created: 2026-07-12
---
# Two Pointers

## When to Use

- When solving problems involving arrays or strings from both ends.
- When the input is sorted and searching for pairs or a target sum.
- When reversing an array or string in-place.
- When removing duplicates or partitioning elements.
- When optimizing a brute-force solution from **O(n²)** to **O(n)**.

---

## Recognition Clues

- The problem involves **pairs of elements**.
- The input array is **sorted**.
- You need to compare elements from **both ends**.
- You are asked to reverse, swap, or rearrange elements.
- The problem can be solved by moving one or both pointers based on a condition.
- The question asks for an **optimal linear-time solution**.

---

## Template Code

```cpp
int left = 0;
int right = n - 1;

while (left < right)
{
    if (/* desired condition is met */)
    {
        // Process the result
    }
    else if (/* move left pointer */)
    {
        left++;
    }
    else
    {
        right--;
    }
}
```

---

## Common Problems

- Reverse Array
- Reverse String
- Two Sum II (Input Array Is Sorted)
- Valid Palindrome
- Remove Duplicates from Sorted Array
- Container With Most Water
- Squares of a Sorted Array
- Move Zeroes
- Trapping Rain Water
- 3Sum