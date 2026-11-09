---
type: algorithm
status: Learning
created: 2026-07-11
updated: 2026-07-11
topic: "[[Arrays]]"
pattern: None
difficulty: Easy
---

# Binary Search

## 🎯 Idea

>Divide the array into two parts from mid and then check whether the mid element is the target if yes return, if not check the mid element is smaller or greater than the target is its greater move the start to mid + 1 index if smaller move the end to mid - 1. Binary search should be only applied to a sorted array.

---

## 📌 When to Use

- 
- 
- 

---

## ❌ When NOT to Use

- 
- 
- 

---

## ⚙️ Steps

1. Find Mid point.
2. Check the mid element if not target continue
3. If target is greater than the mid move the start to mid + 1 else move end to mid - 1.
4. Repeat until found else return -1

---

## 🎨 Visualization

> Add an Excalidraw diagram or ASCII diagram.

```text
```

---

## ⏱️ Complexity

| Case    | Time   |
| ------- | ------ |
| Best    | 1      |
| Average | log(n) |
| Worst   | log(n) |

**Space:** 

---

## 📝 Pseudocode

```text
BinarySearch(A, target, n)
	start = 0, end = n - 1
```

---

## 💻 C++ Implementation

```cpp
#include <iostream>
using namespace std;

int BinarySearch(int arr[], int target, int n) {
	int start = 0, end = n - 1;

	while(start <= end) {
		int mid = start + ((end - start)/2);
		if(arr[mid] == target) return mid;
		else if(target > arr[mid]) start = mid + 1;
		else if(target < arr[mid]) end = mid - 1;
		else return -1;
	}
	return 0;
}

int main()
{
	int arr[6] = {1,2,3,4,5,6};
	int n = 6;

	int s = BinarySearch(arr, 5, n);
	if(s == -1) cout<<"Not Found"<<endl;
	else cout <<"Element found at: "<<s<<endl;

	return 0;
}
```


---

## 👍 Advantages

- 
- 
- 

---

## 👎 Disadvantages

- 
- 
- 

---

## ⚠️ Common Mistakes

- 
- 
- 

---

## 💪 Practice Problems

### Easy

- 

### Medium

- 

### Hard

- 

---

## 🏷️ Tags

#algorithm