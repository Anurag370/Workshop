# Chapter 1: PyTorch Workflow Fundamentals

* **Course:** PyTorch for Deep Learning & Machine Learning – Full Course (`freeCodeCamp.org`)
* **Instructor:** Daniel Bourke (`@mrdbourke`)
* **Video URL:** [https://www.youtube.com/watch?v=V_xro1bcAuA](https://www.youtube.com/watch?v=V_xro1bcAuA)
* **Chapter Timestamp Range:** `04:17:27` – `08:32:00`

---

## 1. The 6-Step PyTorch End-to-End Workflow (`04:17:27` – `04:27:30`)

Every PyTorch project follows a six-step workflow:
1. **Data (Prepare and Load):** Turn raw data (images, text, tables) into numerical tensors and split into sets.
2. **Build Model:** Pick or design a neural network (`nn.Module`), loss function, and optimizer to learn patterns.
3. **Fit the Model to Data (Training):** Run the training loop on the training set so the model adjusts its parameters.
4. **Make Predictions and Evaluate (Inference):** Evaluate the trained model on unseen test data.
5. **Save and Reload a Model:** Save the learned weights to disk for deployment or future use.
6. **Put It All Together:** Combine steps $1\text{–}5$ into clean, device-agnostic code.

---

## 2. Step 1: Data Preparation & Train/Test Split (`04:27:30` – `04:53:18`)

### Creating a Dataset with Linear Regression (`04:27:30`)
To see how PyTorch learns parameters, we generate data using the linear regression formula with **known** parameters:

$$Y = wX + b$$

where $w = 0.7$ (weight/slope) and $b = 0.3$ (bias/intercept).

```python
import torch
from torch import nn
import matplotlib.pyplot as plt

# Known parameters we want our neural network to discover
weight = 0.7
bias = 0.3

# Create input features X and target labels y
X = torch.arange(start=0, end=1, step=0.02).unsqueeze(dim=1)  # Shape: (50, 1)
y = weight * X + bias                                         # Shape: (50, 1)
```

### Splitting Data into Training and Test Sets (`04:37:12`)
Splitting data into distinct sets is **the most important concept in machine learning**:

| Split | Purpose | Typical Percentage | Frequency |
| :--- | :--- | :--- | :--- |
| **Training Set** | Model learns patterns from this data (like course study materials). | $60\%\text{–}80\%$ | Always |
| **Validation Set** | Tune model hyperparameters (like a practice exam). | $10\%\text{–}20\%$ | Often |
| **Testing Set** | Evaluate final model generalization on completely unseen data (like the final exam). | $10\%\text{–}20\%$ | Always |

```python
# Create an 80% / 20% train/test split
train_split = int(0.8 * len(X))  # 40 samples for training, 10 for testing
X_train, y_train = X[:train_split], y[:train_split]
X_test, y_test = X[train_split:], y[train_split:]
```

---

## 3. Step 2: Building a First PyTorch Model (`04:53:18` – `05:41:15`)

### Essential PyTorch Model-Building Classes (`05:13:41`)
* **`torch.nn`**: Contains all building blocks for computational graphs (layers, activation functions, loss functions).
* **`torch.nn.Parameter`**: Stores tensors that can be learned with `nn.Module` (when `requires_grad=True`, PyTorch tracks gradients via `autograd`).
* **`torch.nn.Module`**: The base class for all neural network modules. Every custom model subclasses `nn.Module` and **must** override the `forward()` method.
* **`torch.optim`**: Contains optimization algorithms (e.g., `SGD`, `Adam`) that update `nn.Parameter` values via gradient descent to lower the loss.

### Coding `LinearRegressionModel` with Manual `nn.Parameter` (`04:53:18`)

```python
class LinearRegressionModel(nn.Module):
    def __init__(self):
        super().__init__()
        self.weights = nn.Parameter(torch.randn(1, requires_grad=True, dtype=torch.float))
        self.bias = nn.Parameter(torch.randn(1, requires_grad=True, dtype=torch.float))

    # Forward defines the computation in the model
    def forward(self, x: torch.Tensor) -> torch.Tensor:
        return self.weights * x + self.bias

# Instantiate with a fixed random seed for reproducibility
torch.manual_seed(42)
model_0 = LinearRegressionModel()

# Inspect parameters
print(list(model_0.parameters()))
print(model_0.state_dict())  # OrderedDict({'weights': tensor([0.3367]), 'bias': tensor([0.1288])})
```

### Making Predictions with `torch.inference_mode()` (`05:30:01`)
When making predictions (evaluating/testing), we use the `with torch.inference_mode():` context manager:
* It disables gradient tracking (`autograd`) because we are not updating weights during inference.
* It makes forward passes significantly faster and uses less memory than regular calls (and is newer/faster than `torch.no_grad()`).

```python
with torch.inference_mode():
    y_preds = model_0(X_test)
```

---

## 4. Step 3 & 4: Training and Testing Loops (`05:41:15` – `07:15:53`)

### Loss Function & Optimizer Setup (`05:49:31`)
* **Loss Function:** Measures how wrong your model's predictions ($\hat{y}$) are compared to the truth labels ($y$). Lower is better.
  * For regression, we use **Mean Absolute Error (MAE)** via `nn.L1Loss()`:
    $$\text{MAE} = \frac{1}{N} \sum_{i=1}^{N} |\hat{y}_i - y_i|$$
* **Optimizer:** Takes into account the loss of a model and adjusts the model's parameters (`weights` and `bias`) to improve the loss.
  * `torch.optim.SGD(params=model_0.parameters(), lr=0.01)` where `lr` (learning rate) is a **hyperparameter** defining how big a step the optimizer takes on each update.

### The Complete PyTorch Training & Testing Loop (`06:02:24` – `07:15:53`)

* **The PyTorch Training Loop Song (`06:16:00`):**
  > *"It's train time! Do the forward pass, calculate the loss, optimizer zero grad, lossssss backward! Optimizer step step step..."*

```python
loss_fn = nn.L1Loss()
optimizer = torch.optim.SGD(params=model_0.parameters(), lr=0.01)

epochs = 200
epoch_count, train_loss_values, test_loss_values = [], [], []

for epoch in range(epochs):
    ### TRAINING
    # 0. Put model in training mode (enables layers like Dropout/BatchNorm if present)
    model_0.train()

    # 1. Forward pass on train data
    y_pred = model_0(X_train)

    # 2. Calculate the loss
    loss = loss_fn(y_pred, y_train)

    # 3. Zero the optimizer gradients (they accumulate by default!)
    optimizer.zero_grad()

    # 4. Perform backpropagation on the loss with respect to model parameters
    loss.backward()

    # 5. Step the optimizer (perform gradient descent)
    optimizer.step()

    ### TESTING
    # Put model in evaluation mode
    model_0.eval()
    with torch.inference_mode():
        # 1. Forward pass on test data
        test_pred = model_0(X_test)
        # 2. Calculate loss on test data
        test_loss = loss_fn(test_pred, y_test)

    if epoch % 20 == 0:
        epoch_count.append(epoch)
        train_loss_values.append(loss.detach().numpy())
        test_loss_values.append(test_loss.detach().numpy())
        print(f"Epoch: {epoch} | MAE Train Loss: {loss:.4f} | MAE Test Loss: {test_loss:.4f}")
```

---

## 5. Step 5: Saving and Loading a PyTorch Model (`07:15:53` – `07:44:28`)

### Three Core Methods to Know
1. **`torch.save(obj, f)`**: Saves a serialized object to disk using Python's `pickle` utility.
2. **`torch.load(f)`**: Deserializes a saved PyTorch object file back into memory.
3. **`model.load_state_dict(state_dict)`**: Loads a model's saved parameter dictionary (`state_dict`) into an instantiated `nn.Module` architecture.

> **Best Practice:** Always save and load the **`model.state_dict()`** (just the learned parameter dictionary) rather than the entire model object, as saving the entire class can break if directory paths or class definitions change.

```python
from pathlib import Path

# 1. Create models directory
MODEL_PATH = Path("models")
MODEL_PATH.mkdir(parents=True, exist_ok=True)

# 2. Create model save path (.pt or .pth extension)
MODEL_NAME = "01_pytorch_workflow_model_0.pth"
MODEL_SAVE_PATH = MODEL_PATH / MODEL_NAME

# 3. Save the model state_dict
torch.save(obj=model_0.state_dict(), f=MODEL_SAVE_PATH)

# 4. To load it back: instantiate a fresh instance of the model class and load_state_dict
loaded_model_0 = LinearRegressionModel()
loaded_model_0.load_state_dict(torch.load(f=MODEL_SAVE_PATH))
```

---

## 6. Step 6: Putting Everything Together (`nn.Linear` + Device-Agnostic) (`07:44:28` – `08:32:00`)

In practice, instead of initializing `self.weights` and `self.bias` by hand using `nn.Parameter`, we use `nn.Linear(in_features, out_features)`, which automatically creates and manages the weight and bias parameters for $y = xA^T + b$.

```python
import torch
from torch import nn

# 1. Setup device-agnostic code
device = "cuda" if torch.cuda.is_available() else "cpu"

# 2. Define model using nn.Linear
class LinearRegressionModelV2(nn.Module):
    def __init__(self):
        super().__init__()
        # Takes 1 input feature (X) and produces 1 output feature (y)
        self.linear_layer = nn.Linear(in_features=1, out_features=1)

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        return self.linear_layer(x)

torch.manual_seed(42)
model_1 = LinearRegressionModelV2().to(device)

# 3. Put data on the same target device!
X_train, y_train = X_train.to(device), y_train.to(device)
X_test, y_test = X_test.to(device), y_test.to(device)

# 4. Setup loss and optimizer
loss_fn = nn.L1Loss()
optimizer = torch.optim.SGD(params=model_1.parameters(), lr=0.01)

# 5. Train and evaluate
torch.manual_seed(42)
for epoch in range(1000):
    model_1.train()
    y_pred = model_1(X_train)
    loss = loss_fn(y_pred, y_train)
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

    model_1.eval()
    with torch.inference_mode():
        test_pred = model_1(X_test)
        test_loss = loss_fn(test_pred, y_test)
```