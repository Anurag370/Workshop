---
title: "PyTorch Workflow"
course: "PyTorch for Deep Learning & Machine Learning"
chapter: "1"
source: "https://www.youtube.com/watch?v=V_xro1bcAuA&t=15447s"
tags: [pytorch, training-loop, machine-learning, obsidian]
---

# Chapter 1 — PyTorch Workflow

## Learning objectives

- Follow an end-to-end supervised learning workflow.
- Split data into training and test sets.
- Build a model with `nn.Module`.
- Understand predictions, loss, gradients, and optimizer steps.
- Write training and evaluation loops.
- Save and load a model's state.

## The standard workflow

1. Prepare and inspect data.
2. Split data into training, validation, and test sets.
3. Build a baseline model.
4. Choose a loss function and optimizer.
5. Train using training data.
6. Evaluate on validation data and improve the model.
7. Evaluate the final model on held-out test data.
8. Save the model and inference configuration.

Do not repeatedly tune against the test set. Doing so leaks information from the test set into model selection and makes the reported test performance optimistic.

## 1. A tiny regression example

Regression predicts a continuous value. Suppose the target relationship is approximately `y = 0.7x + 0.3`.

```python
import torch
from torch import nn

torch.manual_seed(42)
X = torch.arange(0, 1, 0.02).unsqueeze(dim=1)
y = 0.7 * X + 0.3

split = int(0.8 * len(X))
X_train, y_train = X[:split], y[:split]
X_test, y_test = X[split:], y[split:]

print(X_train.shape, y_train.shape)
print(X_test.shape, y_test.shape)
```

For real datasets, split carefully. If records are time-dependent, group-related, or near-duplicates, a random split can leak information; use a split strategy that matches the data-generating process.

## 2. Build a model

`nn.Module` is the base class for PyTorch models. `nn.Linear` implements an affine transformation.

```python
class LinearModel(nn.Module):
    def __init__(self):
        super().__init__()
        self.linear = nn.Linear(in_features=1, out_features=1)

    def forward(self, x):
        return self.linear(x)

model = LinearModel()
print(model.state_dict())
```

The model's parameters are initially random. Training adjusts them using data and a loss function.

## 3. Loss and optimizer

- **Loss function:** quantifies how wrong the model's predictions are for the task.
- **Optimizer:** updates model parameters using computed gradients.
- **Learning rate:** controls the size of optimizer updates.

For regression, `nn.L1Loss` or `nn.MSELoss` are common choices. For classification, cross-entropy is often used for single-label multiclass tasks.

```python
loss_fn = nn.L1Loss()
optimizer = torch.optim.SGD(model.parameters(), lr=0.01)
```

## 4. Training loop

The essential order is:

1. `model.train()`
2. Forward pass
3. Calculate loss
4. Clear old gradients
5. Backpropagate with `loss.backward()`
6. Update parameters with `optimizer.step()`

```python
epochs = 100

for epoch in range(epochs):
    model.train()

    y_pred = model(X_train)
    loss = loss_fn(y_pred, y_train)

    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

    if epoch % 10 == 0:
        print(f"epoch={epoch}, loss={loss.item():.4f}")
```

Why clear gradients? PyTorch accumulates gradients by default. If you don't reset them between ordinary optimization steps, gradients from earlier batches are added to new ones.

## 5. Evaluation loop

Evaluation should not calculate gradients unless you have a specific reason.

```python
model.eval()
with torch.inference_mode():
    test_pred = model(X_test)
    test_loss = loss_fn(test_pred, y_test)

print("Test loss:", test_loss.item())
```

- `model.eval()` changes behavior for modules such as dropout and batch normalization.
- `torch.inference_mode()` disables autograd tracking for inference and can reduce overhead.
- These are related but not interchangeable: set evaluation mode explicitly.

## 6. Device-agnostic code

```python
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
model = LinearModel().to(device)
X_train = X_train.to(device)
y_train = y_train.to(device)
X_test = X_test.to(device)
y_test = y_test.to(device)
```

Every tensor used together in an operation must be on a compatible device.

## 7. Saving and loading

Save the model's `state_dict`, not an entire Python object, for a flexible and common workflow.

```python
torch.save(model.state_dict(), "linear_model.pth")

loaded_model = LinearModel()
loaded_model.load_state_dict(
    torch.load("linear_model.pth", map_location="cpu", weights_only=True)
)
loaded_model.eval()
```

The architecture definition must still be available to instantiate the model. Store important preprocessing settings and class mappings alongside model weights for real projects.

## 8. Better training diagnostics

Track at least:
- Training loss.
- Validation loss and task-appropriate metrics.
- Learning rate and epoch.
- Data split and random seed.
- Model configuration and dataset version.

A training loss that decreases while validation loss increases may indicate overfitting. Loss values are only meaningful relative to the task and chosen loss function.

## Common mistakes

- Evaluating on training data and calling it generalization performance.
- Forgetting `optimizer.zero_grad()`.
- Calling `optimizer.step()` before computing gradients.
- Forgetting `model.eval()` for evaluation.
- Using the test set repeatedly to choose hyperparameters.
- Saving weights without preserving class names or preprocessing configuration.

## Checkpoint

1. Why do we split data?
2. What does `loss.backward()` calculate?
3. Why are `zero_grad()` and `optimizer.step()` both needed?
4. What is the difference between `model.train()` and `model.eval()`?
5. Why is a validation set useful even when you already have a test set?

## PlantHealth AI connection

Use this workflow for the custom leaf classifier. Train on training images, compare candidate models on validation images, and report final metrics once on the held-out test split. Keep images from the same plant, session, or near-duplicate source together in one split when that prevents leakage.
