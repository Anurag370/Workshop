---
type: problem
difficulty: Easy
status: Unsolved
topic: "[[Arrays]]"
pattern:
algorithm:
source:
revision: true
created: 2026-07-13
---

# Rotate array by 1

## Problem
Rotate an given array by 1.

---

## Brute Force

### Idea

- Take an temp variable and store the last value of the array.
- Now traverse the array from the second last element from back.
- And replace value of i+1 with i.
- At the end assign a[0] with temp.

```cpp
void RotateArrayBy1(int arr[], int n){
	int last = arr[n-1];
	
	for(int i = n-2; i >= 0; i--){
		arr[i+1] = arr[i];
		
	arr[0] = last;
}
```
### Time Complexity
O(n)

### Space Complexity

---

## Optimal Solution

### Idea

### Time Complexity

### Space Complexity

---

## Code

```cpp

```

---

## Mistakes

-

---

## Learnings

-

---

## Related Notes

Topic:
-

Pattern:
-

Algorithm:
-