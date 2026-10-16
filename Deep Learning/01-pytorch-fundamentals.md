---
title: "PyTorch Fundamentals"
course: "PyTorch for Deep Learning & Machine Learning"
chapter: "0"
source: "https://www.youtube.com/watch?v=V_xro1bcAuA&t=75s"
tags: [pytorch, tensors, deep-learning, obsidian]
---

# Chapter 0 — PyTorch Fundamentals

## Learning objectives

- Explain machine learning, deep learning, and neural networks at a high level.
- Create and manipulate PyTorch tensors.
- Understand shapes, data types, and devices.
- Use matrix multiplication correctly.
- Move tensors and models to a GPU when available.
- Make experiments reproducible.

## 1. Machine learning and deep learning

**Machine learning (ML)** learns patterns from data to make predictions or decisions. **Deep learning (DL)** is a branch of ML that uses neural networks with multiple layers.

Typical distinction:

- Tabular data with meaningful columns often works very well with classical models such as gradient-boosted trees.
- Images, audio, and natural language often benefit from deep learning, though the best choice depends on the data, constraints, and available compute.
- Neural networks do not automatically outperform simpler methods; compare against a sensible baseline.

A neural network applies parameterized operations to inputs. During training, a loss function measures prediction error and an optimizer updates parameters to reduce that error.

## 2. What is PyTorch?

PyTorch is a tensor library and deep-learning framework. It provides tensor operations, automatic differentiation, neural-network modules, optimizers, and utilities for data loading and GPU computation.

```python
import torch
from torch import nn

print(torch.__version__)
print("CUDA available:", torch.cuda.is_available())
```

## 3. Tensors

A tensor is a multidimensional array of values.

| Rank | Common name | Example shape |
|---:|---|---|
| 0 | Scalar | `torch.Size([])` |
| 1 | Vector | `(3,)` |
| 2 | Matrix | `(2, 3)` |
| 3 | 3D tensor | `(3, 4, 5)` |
| 4 | Image batch | `(batch, channels, height, width)` |

```python
scalar = torch.tensor(7)
vector = torch.tensor([1, 2, 3])
matrix = torch.tensor([[1, 2], [3, 4]])
image_batch = torch.rand(8, 3, 224, 224)

print(scalar.ndim, scalar.shape)
print(vector.ndim, vector.shape)
print(matrix.ndim, matrix.shape)
print(image_batch.shape)
```

The image batch shape means 8 images, 3 color channels, 224 pixels high, and 224 pixels wide. For grayscale images, the channel count is often 1.

### Creating tensors

```python
torch.zeros(2, 3)
torch.ones(2, 3)
torch.rand(2, 3)          # values in [0, 1)
torch.arange(0, 10)
torch.randn(2, 3)         # standard normal samples
```

`torch.tensor(...)` copies values into a tensor. Factory functions such as `torch.zeros` and `torch.rand` are useful when you know the desired shape.

## 4. Shape, dtype, and device

These three properties are essential when debugging tensor operations.

```python
x = torch.rand(3, 4)
print(x.shape)
print(x.dtype)
print(x.device)
```

- **Shape:** dimensions and their sizes.
- **Dtype:** numeric representation, such as `torch.float32`, `torch.int64`, or `torch.bool`.
- **Device:** where the tensor resides, typically CPU or CUDA GPU.

Neural-network parameters and floating-point inputs commonly use `float32`. Class labels for `nn.CrossEntropyLoss` are normally integer class indices represented as `torch.int64` (`long`).

```python
x = torch.arange(6, dtype=torch.float32)
labels = torch.tensor([0, 2, 1], dtype=torch.long)
```

## 5. Tensor operations

```python
a = torch.tensor([1, 2, 3])
print(a + 10)
print(a * 2)
print(a - 1)
```

Operations generally require compatible shapes and devices. Broadcasting allows certain dimensions of size 1 to expand logically; it does not always allocate a fully repeated tensor.

### Matrix multiplication

Matrix multiplication is different from element-wise multiplication.

```python
a = torch.rand(2, 3)
b = torch.rand(3, 4)
c = a @ b
print(c.shape)  # torch.Size([2, 4])
```

The inner dimensions must match: `(m, n) @ (n, p) -> (m, p)`.

```python
x = torch.tensor([1, 2, 3])
print(x * x)   # element-wise
print(x @ x)   # dot product: scalar tensor
```

## 6. Aggregation and reshaping

```python
x = torch.arange(1, 7)
print(x.min())
print(x.max())
print(x.float().mean())
print(x.sum())

matrix = x.reshape(2, 3)
print(matrix.shape)
print(matrix.view(3, 2).shape)
print(torch.stack([x, x], dim=0).shape)
```

- `reshape` returns a tensor with a requested shape when the number of elements permits it.
- `view` requires compatible memory layout/strides.
- `stack` adds a new dimension.
- `squeeze` removes dimensions of size 1.
- `unsqueeze` adds a dimension of size 1.
- `permute` reorders dimensions.

```python
x = torch.rand(224, 224, 3)  # H, W, C
x_chw = x.permute(2, 0, 1)   # C, H, W
print(x_chw.shape)           # (3, 224, 224)
```

Be explicit about image layout. PyTorch convolution modules typically expect `(N, C, H, W)` batches.

## 7. Indexing

```python
x = torch.arange(12).reshape(3, 4)
print(x[0])       # first row
print(x[:, 1])    # second column
print(x[1, 2])    # row 1, column 2
```

Remember Python uses zero-based indexing.

## 8. PyTorch and NumPy

```python
import numpy as np

array = np.array([1, 2, 3])
tensor = torch.from_numpy(array)
back_to_numpy = tensor.numpy()
```

CPU tensors and NumPy arrays may share memory. If you need an independent copy, use `.clone()` or NumPy's `.copy()` as appropriate. A CUDA tensor cannot be converted directly with `.numpy()`; move it to CPU first: `tensor.cpu().numpy()`.

## 9. Reproducibility

```python
torch.manual_seed(42)
x1 = torch.rand(3)
torch.manual_seed(42)
x2 = torch.rand(3)
print(torch.equal(x1, x2))  # True in this simple example
```

Seeds help reproduce random-number sequences, but exact reproducibility across hardware, versions, and all GPU operations is not guaranteed automatically.

## 10. Using a GPU

```python
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
x = torch.rand(3, 3).to(device)
print(x.device)
```

A model and its input tensors must be on compatible devices:

```python
model = nn.Linear(3, 1).to(device)
x = torch.rand(5, 3).to(device)
prediction = model(x)
```

## Common mistakes

- Confusing tensor rank with number of elements.
- Multiplying matrices with incompatible inner dimensions.
- Passing floating-point class labels to `CrossEntropyLoss`.
- Forgetting to move the model as well as the data to the GPU.
- Assuming `.view()` and `.reshape()` always behave identically.
- Confusing image channel order `(H, W, C)` with `(C, H, W)`.

## Checkpoint

1. What is the shape of `torch.rand(4, 3, 128, 128)`?
2. What is the shape of `(torch.rand(2, 5) @ torch.rand(5, 7))`?
3. Why should class indices for `CrossEntropyLoss` generally be `long`?
4. What does `permute(2, 0, 1)` do to an `(H, W, C)` tensor?

## PlantHealth AI connection

An image batch commonly has shape `(B, 3, H, W)`. For example, `(32, 3, 224, 224)` is a batch of 32 RGB leaf images. Always inspect `shape`, `dtype`, and `device` when a model reports a tensor mismatch.
