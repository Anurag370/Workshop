# Chapter 0: PyTorch Fundamentals

* **Course:** PyTorch for Deep Learning & Machine Learning – Full Course (`freeCodeCamp.org`)
* **Instructor:** Daniel Bourke (`@mrdbourke`)
* **Video URL:** [https://www.youtube.com/watch?v=V_xro1bcAuA](https://www.youtube.com/watch?v=V_xro1bcAuA)
* **Chapter Timestamp Range:** `00:00:00` – `04:17:27`

---

## 1. Deep Learning & Machine Learning Foundations (`00:00:00` – `01:22:08`)

### Key Timestamps
* `00:00:00` – Introduction
* `00:01:45` – 0. Welcome and "What is deep learning?"
* `00:07:41` – 1. Why use machine/deep learning?
* `00:11:15` – 2. The number one rule of ML
* `00:16:55` – 3. Machine learning vs. deep learning
* `00:23:02` – 4. Anatomy of neural networks
* `00:32:24` – 5. Different learning paradigms
* `00:36:56` – 6. What can deep learning be used for?
* `00:43:18` – 7. What is / Why PyTorch?
* `00:57:52` – 8–12. What are tensors, course approach, resources, and setup

### Core Concepts
1. **Traditional Programming vs. Machine Learning:**
   * **Traditional Programming:** You provide **Inputs** + **Rules (Code)** $\rightarrow$ System produces **Outputs**.
   * **Machine Learning:** You provide **Inputs** + **Ideal Outputs** $\rightarrow$ System learns the **Rules (Patterns/Weights)**.
2. **The Number One Rule of ML (`00:11:15`):**
   > *"If you can build a simple rule-based system that doesn't require machine learning, do that."*
   Use ML/DL when a problem has too many complex, constantly changing rules (e.g., autonomous driving, speech recognition, natural language understanding).
3. **Machine Learning vs. Deep Learning (`00:16:55`):**
   * **Traditional ML** excels at **structured (tabular) data** (rows and columns like CSVs or SQL tables) using algorithms like Random Forests or Gradient Boosted Trees (`XGBoost`, `LightGBM`).
   * **Deep Learning** excels at **unstructured data** (images, audio, video, natural language text) using multi-layered neural networks.
4. **Anatomy of a Neural Network (`00:23:02`):**
   * **Input Layer:** Receives numerical encoding of raw data (as tensors).
   * **Hidden Layer(s):** Learns intermediate **representations** (features/patterns) using weights and non-linear activations.
   * **Output Layer:** Outputs representation predictions (logits, probabilities, or continuous values).
5. **The Three Mottos of the Course (`01:03:56`):**
   * *"Experiment, experiment, experiment!"*
   * *"Visualize, visualize, visualize!"*
   * *"Become one with the data!"*

---

## 2. Introduction to Tensors & Creating Tensors (`01:22:08` – `01:54:01`)

A **Tensor** (`torch.Tensor`) is the fundamental building block of PyTorch. It is a multi-dimensional numerical representation of data (images, text, audio, tabular features) capable of running on GPUs and tracking gradients.

### Tensor Dimensionality Hierarchy

| Name | Dimension (`ndim`) | Lower/Upper Notation | Example Shape | Code Example |
| :--- | :--- | :--- | :--- | :--- |
| **Scalar** | $0$ | Lowercase ($a$) | `torch.Size([])` | `torch.tensor(7)` |
| **Vector** | $1$ | Lowercase ($y$) | `torch.Size([2])` | `torch.tensor([7, 7])` |
| **Matrix** | $2$ | Uppercase ($Q$) | `torch.Size([2, 2])` | `torch.tensor([[7, 8], [9, 10]])` |
| **Tensor** | $3+$ | Uppercase ($X, T$) | `torch.Size([1, 3, 3])` | `torch.rand(1, 3, 3)` |

### Creating Tensors in PyTorch

```python
import torch

# 1. Scalar (0D), Vector (1D), Matrix (2D)
scalar = torch.tensor(7)
vector = torch.tensor([7, 7])
MATRIX = torch.tensor([[7, 8],
                       [9, 10]])

# Check number of dimensions (.ndim) and shape (.shape)
print(scalar.ndim, scalar.shape, scalar.item())  # 0, torch.Size([]), 7
print(MATRIX.ndim, MATRIX.shape)                 # 2, torch.Size([2, 2])

# 2. Random Tensors (crucial because neural networks start with random weights!)
random_tensor = torch.rand(3, 4)                 # Uniform in [0, 1)
random_image_size_tensor = torch.rand(size=(3, 224, 224)) # [color_channels, height, width]

# 3. Zeros and Ones (often used for masks)
zeros = torch.zeros(size=(3, 4))
ones = torch.ones(size=(3, 4))

# 4. Ranges and Tensors-Like
one_to_ten = torch.arange(start=1, end=11, step=1)
ten_zeros = torch.zeros_like(input=one_to_ten)   # Matches shape/dtype of input
```

---

## 3. Tensor Datatypes & The 3 Big PyTorch Errors (`01:54:01` – `02:11:50`)

### The 3 Most Common Errors in PyTorch & Deep Learning
Nearly every bug you encounter in PyTorch boils down to one of three attributes:
1. **Tensors not right datatype** $\rightarrow$ Check with `tensor.dtype`
2. **Tensors not right shape** $\rightarrow$ Check with `tensor.shape` (or `tensor.size()`)
3. **Tensors not on the right device** $\rightarrow$ Check with `tensor.device` (e.g., one tensor on `"cpu"` and another on `"cuda:0"`)

### Precision vs. Speed (`dtype`)
* `torch.float32` (or `torch.float`): Default $32$-bit floating point precision in PyTorch.
* `torch.float16` (or `torch.half`): $16$-bit floating point; uses half the memory and computes faster on modern GPUs (mixed precision).
* `torch.int64` (or `torch.long`): Required by many classification index operations (e.g., target class labels in `nn.CrossEntropyLoss`).

```python
float_32_tensor = torch.tensor([3.0, 6.0, 9.0],
                               dtype=None,           # defaults to torch.float32
                               device=None,          # defaults to "cpu"
                               requires_grad=False)  # whether to track gradients

# Convert float32 to float16
float_16_tensor = float_32_tensor.type(torch.float16)
```

---

## 4. Manipulating Tensors & Matrix Multiplication (`02:11:50` – `02:48:18`)

### Basic Element-Wise Operations
Addition (`+` or `torch.add`), Subtraction (`-` or `torch.sub`), Element-wise Multiplication (`*` or `torch.mul`), and Division (`/`).

### Matrix Multiplication (Dot Product) (`02:17:50`)
Matrix multiplication (`@` or `torch.matmul()` or `torch.mm()`) is the most frequently performed operation inside neural networks. It obeys two strict rules:

1. **The Inner Dimensions Must Match:**
   * $(3, 2) \text{ @ } (3, 2)$ $\rightarrow$ **Won't work!** (`RuntimeError: mat1 and mat2 shapes cannot be multiplied`)
   * $(2, 3) \text{ @ } (3, 2)$ $\rightarrow$ **Will work!** Inner dimension is $3$.
2. **The Resulting Matrix Has the Shape of the Outer Dimensions:**
   * $(2, 3) \text{ @ } (3, 2) \rightarrow (2, 2)$
   * $(3, 2) \text{ @ } (2, 3) \rightarrow (3, 3)$

$$\text{Shape: } (m \times k) \text{ @ } (k \times n) \rightarrow (m \times n)$$

### Fixing Shape Errors with Transpose (`.T`)
A transpose switches the axes/dimensions of a given tensor (`(m, n)` becomes `(n, m)`):

```python
tensor_A = torch.tensor([[1, 2],
                         [3, 4],
                         [5, 6]])  # Shape: (3, 2)

tensor_B = torch.tensor([[7, 10],
                         [8, 11],
                         [9, 12]]) # Shape: (3, 2)

# tensor_A @ tensor_B raises a shape error!
# Fix by transposing tensor_B from (3, 2) -> (2, 3):
output = torch.matmul(tensor_A, tensor_B.T)  # (3, 2) @ (2, 3) -> Shape (3, 3)
```

---

## 5. Tensor Aggregation (`min`, `max`, `mean`, `sum`, `argmin`, `argmax`) (`02:48:18` – `02:57:48`)

Aggregation reduces a tensor from many elements down to fewer elements (or a single scalar).

* **Important Gotcha:** `torch.mean()` **requires** a floating-point or complex datatype (`float32`, `float64`). Calling `.mean()` on an integer tensor (`int64` from `torch.arange`) throws:
  `RuntimeError: mean(): could not infer output dtype. Input dtype must be either a floating point or complex dtype.`

```python
x = torch.arange(0, 100, 10)  # dtype is torch.int64 (Long)

print(x.min(), torch.min(x))                       # tensor(0)
print(x.max(), torch.max(x))                       # tensor(90)
print(x.type(torch.float32).mean())                # Must cast to float32 first! tensor(45.)
print(x.sum(), torch.sum(x))                       # tensor(450)

# Positional min and max (returns the INDEX where the min/max occurs)
print(x.argmin())                                  # tensor(0) -> index 0 has value 0
print(x.argmax())                                  # tensor(9) -> index 9 has value 90
```

---

## 6. Reshaping, Viewing, Stacking, Squeezing, and Permuting (`02:57:48` – `03:23:28`)

When fixing shape mismatches between neural network layers, we manipulate tensor shapes without changing the underlying numbers:

| Method | Description |
| :--- | :--- |
| `x.reshape(shape)` | Reshapes an input tensor to a defined compatible shape (number of elements must stay equal). |
| `x.view(shape)` | Returns a view of an input tensor of certain shape **sharing the same underlying memory** as `x`. Modifying the view modifies `x`! |
| `torch.stack([x, x], dim=0)` | Concatenates a sequence of tensors along a **new** dimension (`dim=0` stacks vertically, `dim=1` stacks side-by-side). |
| `x.squeeze()` | Removes all single dimensions (dimensions of size $1$), e.g., $(1, 1, 9) \rightarrow (9,)$. |
| `x.unsqueeze(dim=0)` | Adds a single dimension of size $1$ at a specific target `dim` (essential for adding a batch dimension: $(3, 224, 224) \rightarrow (1, 3, 224, 224)$). |
| `x.permute(dims)` | Returns a view with dimensions swapped in a specified order (shares memory with original). |

```python
# Permuting is commonly used to convert image tensors from PyTorch [C, H, W] to Matplotlib [H, W, C]
x_original = torch.rand(size=(224, 224, 3))          # [height, width, color_channels]
x_permuted = x_original.permute(2, 0, 1)             # Shifts axis 2->0, 0->1, 1->2 -> [3, 224, 224]
```

---

## 7. Indexing, NumPy Interoperability, Reproducibility, and GPUs (`03:23:28` – `04:17:27`)

### Selecting Data (Indexing) (`03:23:28`)
```python
x = torch.arange(1, 10).reshape(1, 3, 3)
# Shape is (1, 3, 3): [outer_bracket, row, column]
print(x[0])        # First 3x3 matrix
print(x[0, 0])     # First row: tensor([1, 2, 3])
print(x[0, 2, 2])  # Bottom-right element: tensor(9)
print(x[:, :, 1])  # All values of 0th and 1st dimensions, but only index 1 of 2nd dimension: tensor([[2, 5, 8]])
```

### PyTorch & NumPy (`03:33:01`)
* **NumPy array $\rightarrow$ PyTorch tensor:** `torch.from_numpy(ndarray)`
  * *Gotcha:* NumPy arrays default to `float64`, so `torch.from_numpy()` creates a `torch.float64` tensor unless cast with `.type(torch.float32)`.
* **PyTorch tensor $\rightarrow$ NumPy array:** `tensor.numpy()`

### Reproducibility (Random Seeds) (`03:42:10`)
To make random weight initializations and data splits reproducible across runs, set the manual seed before each random call:

```python
RANDOM_SEED = 42
torch.manual_seed(RANDOM_SEED)
random_tensor_C = torch.rand(3, 4)

torch.manual_seed(RANDOM_SEED)
random_tensor_D = torch.rand(3, 4)

print(random_tensor_C == random_tensor_D)  # All True!
```

### Device-Agnostic Code & GPUs (`03:52:58` – `04:17:27`)
* Always write **device-agnostic code** so your scripts run seamlessly whether a GPU is available or not.
* **Important Gotcha:** NumPy **cannot** access GPU tensors directly! You must call `tensor.cpu().numpy()` before converting a GPU tensor to NumPy or plotting with Matplotlib.

```python
# Setup device-agnostic code
device = "cuda" if torch.cuda.is_available() else "cpu"
print(f"Using device: {device}")

# Move tensor to target device
tensor = torch.tensor([1, 2, 3])
tensor_on_gpu = tensor.to(device)

# Move back to CPU for NumPy / Matplotlib compatibility
tensor_back_on_cpu = tensor_on_gpu.cpu().numpy()
```