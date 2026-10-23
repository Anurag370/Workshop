# Chapter 2: Manipulating Data Using NumPy

## 1. Why NumPy? (`ndarray` vs. Python Lists)

At the heart of **NumPy** (Numerical Python) is the **`ndarray`** ($N$-dimensional array). While Python lists store pointers to scattered objects across memory, a NumPy array stores elements of a **single homogeneous data type (`dtype`)** in a **contiguous block of memory**.

* **Vectorization:** Operations execute in compiled C/Fortran loops rather than slow Python `for` loops, yielding $10\times$ to $100\times$ speedups.

* **Memory Efficiency:** No per-element type-checking or pointer overhead.

* **Broadcasting:** Arithmetic between arrays of different (but compatible) shapes happens automatically without copying data in memory.

## 2. Creating and Inspecting NumPy Arrays

```
import numpy as np

# 1. Creating arrays from Python lists
arr_1d = np.array([10, 20, 30, 40])
arr_2d = np.array([[1.0, 2.0, 3.0],
                   [4.0, 5.0, 6.0]])

# 2. Inspecting array attributes
print("Dimensions (ndim):", arr_2d.ndim)     # 2
print("Shape (rows, cols):", arr_2d.shape)   # (2, 3)
print("Total elements (size):", arr_2d.size) # 6
print("Data type (dtype):", arr_2d.dtype)    # float64

# 3. Built-in factory functions
zeros = np.zeros((3, 4))                     # 3x4 array of 0.0
ones = np.ones((2, 3), dtype=np.int32)       # 2x3 array of integer 1s
full = np.full((2, 2), fill_value=7.5)       # 2x2 array filled with 7.5
eye = np.eye(3)                              # 3x3 Identity matrix I_3

# 4. Sequences and Random Generation (Modern Generator API)
seq_step = np.arange(start=0, stop=10, step=2)        # [0, 2, 4, 6, 8]
seq_lin = np.linspace(start=0.0, stop=1.0, num=5)     # [0. , 0.25, 0.5 , 0.75, 1. ]

rng = np.random.default_rng(seed=42)
rand_uniform = rng.random((2, 3))                     # Uniform in [0.0, 1.0)
rand_normal = rng.normal(loc=0.0, scale=1.0, size=(2, 3)) # Normal (mean=0, std=1)
rand_ints = rng.integers(low=1, high=100, size=(3, 3))    # Random ints in [1, 100)

```

## 3. Indexing, Slicing, and Boolean Masking

### 3.1 Multi-Dimensional Slicing

Syntax: `arr[row_slice, col_slice]` where each slice follows `start:stop:step`.

* **Important Gotcha:** NumPy slices return **views** (sharing the same underlying memory), not copies! Modifying a slice modifies the original array unless you explicitly call `.copy()`.

```
matrix = np.array([[10, 20, 30, 40],
                   [50, 60, 70, 80],
                   [90, 95, 98, 99]])

# Single element: row 1, col 2
val = matrix[1, 2]           # 70

# First two rows, columns 1 to 3 (exclusive)
sub_view = matrix[:2, 1:3]   # [[20, 30], [60, 70]]

# Safe copy to avoid mutating 'matrix'
sub_copy = matrix[:2, 1:3].copy()

```

### 3.2 Boolean Masking & `np.where()`

Boolean indexing filters or transforms elements based on logical conditions (`&` for AND, `|` for OR, `~` for NOT):

```
scores = np.array([45, 78, 88, 32, 95, 60])

# 1. Filter elements matching a condition
passing_mask = scores >= 60          # [False, True, True, False, True, True]
passing_scores = scores[passing_mask] # [78, 88, 95, 60]

# 2. Compound condition (parentheses are mandatory!)
b_grade = scores[(scores >= 70) & (scores < 90)]  # [78, 88]

# 3. Vectorized conditional replacement: np.where(condition, value_if_true, value_if_false)
labels = np.where(scores >= 60, "Pass", "Fail")
# array(['Fail', 'Pass', 'Pass', 'Fail', 'Pass', 'Pass'], dtype='<U4')

```

## 4. Reshaping, Transposing, Stacking, and Splitting

| Operation | Method / Syntax | Description | 
| ----- | ----- | ----- | 
| **Reshape** | `arr.reshape(r, c)` | Changes shape while keeping total size $r \times c$ constant. Use `-1` to infer one dimension automatically. | 
| **Flatten (View)** | `arr.ravel()` | Flattens an $N\text{D}$ array into a $1\text{D}$ view (memory-efficient). | 
| **Flatten (Copy)** | `arr.flatten()` | Flattens an $N\text{D}$ array into a new $1\text{D}$ copy. | 
| **Add Axis** | `arr[:, np.newaxis]` or `np.expand_dims()` | Converts a $1\text{D}$ shape `(n,)` into a $2\text{D}$ column vector `(n, 1)` or row vector `(1, n)`. | 
| **Transpose** | `arr.T` | Swaps rows and columns: shape $(m, n) \rightarrow (n, m)$. | 
| **Vertical Stack** | `np.vstack([a, b])` or `np.concatenate([a, b], axis=0)` | Stacks arrays row-wise (number of columns must match). | 
| **Horizontal Stack** | `np.hstack([a, b])` or `np.concatenate([a, b], axis=1)` | Stacks arrays column-wise (number of rows must match). | 

```
x = np.arange(1, 13)              # Shape: (12,)
grid = x.reshape(3, -1)           # Infers 4 columns -> Shape: (3, 4)
col_vec = x[:, np.newaxis]        # Shape: (12, 1)

```

## 5. Vectorized Operations, Linear Algebra & Broadcasting

### 5.1 Universal Functions (`ufuncs`) and Linear Algebra

* **Element-wise arithmetic:** `+`, `-`, `*`, `/`, `**`, `np.sqrt(x)`, `np.exp(x)`, `np.log(x)`.

* **Matrix Multiplication (Dot Product):** For $A \in \mathbb{R}^{m \times k}$ and $B \in \mathbb{R}^{k \times n}$, use `A @ B` or `np.matmul(A, B)` to produce $C \in \mathbb{R}^{m \times n}$.

* **Linear Algebra (`np.linalg`):**

  * `np.linalg.inv(A)`: Matrix inverse $A^{-1}$.

  * `np.linalg.det(A)`: Determinant $\det(A)$.

  * `np.linalg.eig(A)`: Eigenvalues and eigenvectors.

  * `np.linalg.norm(v)`: Euclidean ($L_2$) norm $\Vert{}v\Vert{}_2$.

### 5.2 Rules of Broadcasting

When operating on two arrays, NumPy compares their shapes **element-wise from right to left (trailing dimensions)**. Two dimensions are compatible when:

1. They are equal, **OR**

2. One of them is $1$ (or missing, in which case $1$ is prepended).

$$
\text{Matrix } (4, 3) + \text{Row Vector } (3,) \xrightarrow{\text{prepend } 1} (4, 3) + (1, 3) \xrightarrow{\text{stretch}} (4, 3)
$$

```
# Centering every column of a dataset (subtracting column means) using broadcasting
X = np.array([[10.0, 200.0],
              [20.0, 400.0],
              [30.0, 600.0]])     # Shape: (3, 2)

col_means = X.mean(axis=0)        # Shape: (2,) -> [20.0, 400.0]
X_centered = X - col_means        # (3, 2) - (2,) broadcasts automatically!

```

## 6. Aggregations and Understanding the `axis` Parameter

The `axis` parameter specifies **which dimension gets collapsed (reduced)** during an aggregation:

* **`axis=0`:** Collapses rows vertically (computes one statistic **per column**). Shape $(m, n) \rightarrow (n,)$.

* **`axis=1`:** Collapses columns horizontally (computes one statistic **per row**). Shape $(m, n) \rightarrow (m,)$.

* **`axis=None` (default):** Collapses the entire array into a single scalar.

```
data = np.array([[10, 50, 30],
                 [40, 20, 60]])  # Shape: (2, 3)

print("Global Sum:", np.sum(data))              # 210
print("Column Means (axis=0):", data.mean(axis=0)) # [25., 35., 45.] -> shape (3,)
print("Row Max (axis=1):", data.max(axis=1))       # [50, 60]        -> shape (2,)
print("Row Argmax (axis=1):", data.argmax(axis=1)) # [1, 2] (index of max in each row)

```