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


## Problem
Find no. of possible moves of a bishop when current location is given.

---

## Brute Force

### Code

```cpp
int Bishop(int a, int b){

    int totalMoves = 0;

    totalMoves += min(a - 1, b - 1) + min(a - 1, 8 - b) + min(8 - a, b -1) + min(8 - a, 8 - b);

    return totalMoves;

}
```

---
