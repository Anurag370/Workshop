---
type: problem
difficulty: Easy
status: Solved
topic: Maths
pattern: None
algorithm: None
source: None
revision: false
created: 2026-07-10
---

# Find number of trailing zero's in a factorial.

## Problem
Write a program to return the number of trailing zero's a factorial of a number will have.
[[Flowchart to find Trailing Zeros]]

---

## Code

```cpp
int countTrailing0s(int N){
    int count = 0;
    
    while(N >= 5){
        count = N/5;
        N /= 5;
    }
    
    return count;
}
```

