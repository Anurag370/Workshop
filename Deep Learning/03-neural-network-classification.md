---
title: "Neural Network Classification"
course: "PyTorch for Deep Learning & Machine Learning"
chapter: "2"
source: "https://www.youtube.com/watch?v=V_xro1bcAuA&t=30720s"
tags: [pytorch, classification, neural-networks, obsidian]
---

# Chapter 2 — Neural Network Classification

## Learning objectives

- Distinguish regression and classification.
- Understand logits, probabilities, and predicted classes.
- Choose a suitable classification loss.
- Implement training and evaluation loops.
- Understand nonlinear activation functions.
- Evaluate classification performance beyond accuracy.

## 1. Classification

Classification predicts a category rather than a continuous quantity.

- **Binary classification:** two classes, such as healthy vs diseased.
- **Multiclass classification:** exactly one class from several alternatives, such as identifying one of 38 plant disease categories.
- **Multilabel classification:** multiple labels may be true for one sample.

The output layer and loss function depend on which problem you are solving.

## 2. Logits, probabilities, and labels

For a single-label problem with `C` classes, a model typically returns `C` raw scores called **logits**.

```python
import torch

logits = torch.tensor([[2.0, 0.5, -1.0]])
probabilities = torch.softmax(logits, dim=1)
predicted_class = logits.argmax(dim=1)

print(probabilities)
print(predicted_class)
```

Softmax converts logits into values that sum to 1 across the class dimension. The highest-logit class is also the highest-probability class after softmax.

**Important:** pass raw logits to `nn.CrossEntropyLoss`; do not apply softmax first.

## 3. A classification model

```python
from torch import nn

class Classifier(nn.Module):
    def __init__(self, input_features=10, hidden_units=16, num_classes=3):
        super().__init__()
        self.layers = nn.Sequential(
            nn.Linear(input_features, hidden_units),
            nn.ReLU(),
            nn.Linear(hidden_units, num_classes),
        )

    def forward(self, x):
        return self.layers(x)

model = Classifier()
sample = torch.rand(8, 10)
print(model(sample).shape)  # (8, 3)
```

The output has one logit per class for every example in the batch.

## 4. Nonlinearity

A stack of linear layers without nonlinear activations is still equivalent to a single linear transformation. Nonlinear activation functions let a network learn more complex decision boundaries.

`ReLU(x) = max(0, x)` is a common hidden-layer activation.

Other activations include sigmoid, tanh, and GELU. The choice depends on architecture and task.

## 5. Loss functions

For single-label multiclass classification:

```python
loss_fn = nn.CrossEntropyLoss()
logits = torch.randn(4, 3)
labels = torch.tensor([0, 2, 1, 0], dtype=torch.long)
loss = loss_fn(logits, labels)
```

Expected shapes:
- logits: `(batch_size, num_classes)`, floating point
- labels: `(batch_size,)`, integer class indices from `0` to `num_classes - 1`

For binary classification, `nn.BCEWithLogitsLoss` is commonly used with one logit per example and floating-point targets. For multilabel classification, use one logit per label and a multi-hot target tensor with the same shape as the logits.

## 6. Training and evaluation

```python
def train_step(model, X, y, loss_fn, optimizer, device):
    model.train()
    X, y = X.to(device), y.to(device)

    logits = model(X)
    loss = loss_fn(logits, y)
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

    predictions = logits.argmax(dim=1)
    accuracy = (predictions == y).float().mean()
    return loss.item(), accuracy.item()


@torch.inference_mode()
def eval_step(model, X, y, loss_fn, device):
    model.eval()
    X, y = X.to(device), y.to(device)

    logits = model(X)
    loss = loss_fn(logits, y)
    predictions = logits.argmax(dim=1)
    accuracy = (predictions == y).float().mean()
    return loss.item(), accuracy.item()
```

For a large dataset, run these functions over batches from a `DataLoader` and aggregate metrics across all examples. Do not average batch averages equally if batch sizes differ; weight by the number of examples.

## 7. Multiclass classification

For `C` classes:
- Final layer has `out_features=C`.
- Labels are integer class indices.
- Cross-entropy loss consumes logits.
- `argmax(dim=1)` returns the predicted class index for each example.

For plant disease classification, keep a stable mapping between class names and indices. Save it with the model so inference interprets outputs correctly.

## 8. Metrics and error analysis

Accuracy is the fraction of predictions that are correct. It can be misleading when classes are imbalanced.

Useful metrics:
- Precision: among examples predicted positive for a class, how many were correct?
- Recall: among true examples of a class, how many were found?
- F1 score: harmonic mean of precision and recall.
- Confusion matrix: shows true classes against predicted classes.

In multiclass problems, inspect per-class recall as well as aggregate metrics. Confusing two visually similar diseases may be more important than the headline accuracy suggests.

## 9. Improving a model

Try controlled experiments:
- Verify labels and input preprocessing.
- Establish a simple baseline.
- Tune learning rate and model size.
- Add data or realistic augmentation.
- Address class imbalance if present.
- Use regularization when overfitting.
- Inspect errors rather than only changing architecture.

Do not change many variables at once; otherwise, you cannot identify what caused the result.

## Common mistakes

- Applying softmax before `CrossEntropyLoss`.
- Using one-hot labels where class indices are expected.
- Forgetting the class dimension in `argmax`.
- Reporting only accuracy on imbalanced data.
- Treating model confidence as proof that a prediction is correct.

## Checkpoint

1. What is the difference between logits and probabilities?
2. Why does a hidden layer need a nonlinear activation?
3. What shapes do `CrossEntropyLoss` logits and targets expect?
4. When can accuracy be misleading?
5. What information should accompany a saved multiclass model?

## PlantHealth AI connection

PlantHealth AI is likely a single-label multiclass task if each image has exactly one assigned disease/healthy category. Verify the dataset's label scheme first. For 38 classes, the final layer should output 38 logits, and the class-to-index mapping must remain consistent from training to inference.
