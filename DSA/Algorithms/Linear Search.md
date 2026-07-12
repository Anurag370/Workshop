---
type: algorithm
status: Learning
created: 2026-07-11
updated: 2026-07-11
topic: "[[Arrays]]"
pattern: None
difficulty: Easy
---

# Linear Search

## 🎯 Idea

> Linear Search is the simplest searching algorithm. It checks each element of the array one by one until the target element is found or the end of the array is reached.

---

## 📌 When to Use

- The array is **unsorted**.
- The dataset is **small**.
- Simplicity is more important than performance.

---

## ❌ When NOT to Use

- Large datasets -
- Frequently searched data -
- Sorted arrays (use [[Binary Search]] instead)

---

## ⚙️ Steps

1. Start from the first element.
2. Compare the current element with the target.
3. If they are equal, return the index.
4. Otherwise, move to the next element.
5. Repeat until the end of the array.
6. If the target is not found, return `-1`.

---

## 🎨 Visualization

[[Linear Search Diagram|Linear Search Diagram]]

---

## ⏱️ Complexity

| Case    | Time |
| ------- | ---- |
| Best    | O(1) |
| Average | O(n) |
| Worst   | O(n) |

**Space:** **O(1)**

---

## 📝 Pseudocode

```text
LinearSearch(array, target)
for each element in array
if element == target return index
return -1
```

---

## 💻 C++ Implementation

```cpp
#include <iostream>
using namespace std;

int linearSearch(int arr[], int n, int target)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == target)
            return i;
    }
  
    return -1;
}
  
int main()
{

    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);


    int target = 40;

    int index = linearSearch(arr, n, target);

    if (index != -1)

        cout << "Element found at index " << index;

    else

        cout << "Element not found";

    return 0;

}
```


---

## 👍 Advantages

- Very easy to implement
- Works on unsorted arrays
- No preprocessing required

---

## 👎 Disadvantages

- Slow for large datasets
- Checks elements one by one
- Inefficient compared to Binary Search on sorted data

---

## ⚠️ Common Mistakes

- Forgetting to return `-1` when the element is not found.
- Using Binary Search on an unsorted array.
- Looping beyond the last index (`i <= n` instead of `i < n`).


---

## 💪 Practice Problems

### Easy

- 

### Medium

- 

### Hard

- 

---

## 📖 References

- 

---

## 🔄 Revision Notes

- ✅ Works on both sorted and unsorted arrays.
- ✅ Sequential search.
- ✅ Best Case → O(1)
- ✅ Worst Case → O(n)
- ✅ Space → O(1)

---

## 🏷️ Tags

#algorithm #arrays 