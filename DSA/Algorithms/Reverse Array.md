---
type: algorithm
status: Learning
created: 2026-07-11
updated: 2026-07-11
topic: "[[Arrays]]"
pattern: two-pointers
difficulty: Easy
---
# Reverse Array

## 🎯 Idea

Reverse an array by swapping the first element with the last, the second with the second-last, and so on until the middle of the array is reached. The most efficient approach uses the **Two Pointers** technique, where one pointer starts from the beginning and the other from the end, moving towards each other after every swap.

---

## 📌 When to Use

- When an array needs to be reversed in-place.
- As a subroutine in other algorithms (e.g., Array Rotation).
- When optimizing for constant extra space.

---

## ❌ When NOT to Use

- When the original array must remain unchanged.
- When working with immutable data structures.
- When a reversed copy is required instead of modifying the original array.

---

## ⚙️ Steps

1. Initialize two pointers: `left = 0` and `right = n - 1`.
2. Swap the elements at `left` and `right`.
3. Increment `left` and decrement `right`.
4. Repeat the process until `left >= right`.
5. The array is now reversed.

---

## 🎨 Visualization

> Add an Excalidraw diagram or ASCII diagram.

```text
Original Array

Index : 0   1   2   3   4
Array : 10  20  30  40  50
         ↑               ↑
       left           right

Swap

Array : 50  20  30  40  10
             ↑       ↑
           left   right

Swap

Array : 50  40  30  20  10
                 ↑
              Stop
```

---

## ⏱️ Complexity

| Case | Time |
|------|------|
| Best | O(n) |
| Average | O(n) |
| Worst | O(n) |

**Space:** O(1)

---

## 📝 Pseudocode

```text
ReverseArray(array, n)

left ← 0
right ← n - 1

while left < right

    swap(array[left], array[right])

    left ← left + 1
    right ← right - 1

return array
```

---

## 💻 C++ Implementation

```cpp
#include <iostream>
using namespace std;

void reverseArray(int arr[], int n)
{
    int left = 0;
    int right = n - 1;

    while (left < right)
    {
        swap(arr[left], arr[right]);
        left++;
        right--;
    }
}

int main()
{
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);

    reverseArray(arr, n);

    cout << "Reversed Array: ";

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    return 0;
}
```

---

## 👍 Advantages

- Efficient in-place algorithm with **O(1)** extra space.
- Simple and easy to implement.
- Uses the optimal **Two Pointers** technique.

---

## 👎 Disadvantages

- Modifies the original array.
- Not suitable when the original order must be preserved.
- Requires creating a copy if a non-destructive reversal is needed.

---

## ⚠️ Common Mistakes

- Using `left <= right` instead of `left < right`, causing an unnecessary swap of the middle element.
- Forgetting to update both pointers after swapping.
- Incorrectly initializing `right` as `n` instead of `n - 1`.

---

## 💪 Practice Problems

### Easy

- Reverse String
- Reverse Array
- Valid Palindrome

### Medium

- Rotate Array
- Next Permutation
- Rotate Image

### Hard

- First Missing Positive

---

## 🏷️ Tags

#algorithm #arrays #two-pointers