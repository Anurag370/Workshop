---
type: algorithm
status: Learning
created: 2026-08-10
updated: 2026-08-10
topic: "[[Arrays]]"
pattern:
difficulty: Easy
---
# Selection Sort

## 🎯 Idea

Selection Sort repeatedly finds the smallest element from the unsorted portion of the array and places it at the beginning of that portion. After each pass, the sorted portion grows by one element. The process continues until the entire array is sorted.

---

## 📌 When to Use

- When simplicity and ease of implementation are more important than performance.
- When the array is small.
- When minimizing the number of swaps is important.

---

## ❌ When NOT to Use

- When working with large datasets.
- When an efficient sorting algorithm is required.
- When the array is nearly sorted and a more adaptive algorithm such as [[Insertion Sort]] would be better.

---

## ⚙️ Steps

1. Start from the first index of the array.
2. Assume the current index contains the smallest element.
3. Search the remaining unsorted portion for the actual smallest element.
4. Swap the smallest element with the element at the current index.
5. Move to the next index and repeat until the array is sorted.

---

## 🎨 Visualization

> Add an Excalidraw diagram or ASCII diagram.

```text
Array: 64  25  12  22  11
       ↑
     min

Find minimum → 11

Swap 64 and 11

Array: 11  25  12  22  64
       └──┘
      Sorted

Find minimum in remaining portion:

Array: 11  25  12  22  64
           ↑       ↑
         current  min

Swap 25 and 12

Array: 11  12  25  22  64

Continue...

Final:
11  12  22  25  64
```

---

## ⏱️ Complexity

| Case Time  |   |
| ---------- | - |
| Best       | O(n²) |
| Average    | O(n²) |
| Worst      | O(n²) |

**Space:** O(1)

---

## 📝 Pseudocode

```text
SelectionSort(array, n)

for i = 0 to n - 2

    minIndex = i

    for j = i + 1 to n - 1

        if array[j] < array[minIndex]

            minIndex = j

    swap(array[i], array[minIndex])
```

---

## 💻 C++ Implementation

```cpp
#include <iostream>
using namespace std;

void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }

        swap(arr[i], arr[minIndex]);
    }
}

int main()
{
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    selectionSort(arr, n);

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}
```

---

## 👍 Advantages

- Simple and easy to understand.
- Requires only **O(1)** extra space.
- Performs relatively few swaps compared with some other simple sorting algorithms.

---

## 👎 Disadvantages

- Has **O(n²)** time complexity in all cases.
- Inefficient for large datasets.
- Not stable in its standard implementation.

---

## ⚠️ Common Mistakes

- Forgetting to reset `minIndex` for every outer-loop iteration.
- Comparing with the wrong index inside the inner loop.
- Using `j = i` instead of `j = i + 1`.
- Looping until `n` in the outer loop instead of `n - 1`.
- Forgetting to perform the swap after finding the minimum element.

---

## 💪 Practice Problems

### Easy

- Sort an Array Using Selection Sort
- Find the Kth Smallest Element
- Sort an Array in Ascending Order

### Medium

- Sort Colors
- Kth Largest Element in an Array
- Find the Kth Smallest Pair Distance

### Hard

- Minimum Number of Swaps to Sort an Array
- Count Inversions

---