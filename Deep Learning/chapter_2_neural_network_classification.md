# Chapter 2: Neural Network Classification with PyTorch

* **Course:** PyTorch for Deep Learning & Machine Learning – Full Course (`freeCodeCamp.org`)
* **Instructor:** Daniel Bourke (`@mrdbourke`)
* **Video URL:** [https://www.youtube.com/watch?v=V_xro1bcAuA](https://www.youtube.com/watch?v=V_xro1bcAuA)
* **Chapter Timestamp Range:** `08:32:00` – `14:00:48`

---

## 1. Classification Fundamentals & Architecture (`08:32:00` – `09:09:41`)

### Types of Classification (`08:32:00`)
1. **Binary Classification:** Target can be one of two options ($0$ or $1$, e.g., spam vs. not spam).
2. **Multi-class Classification:** Target can be one of more than two mutually exclusive options (e.g., pizza, steak, or sushi).
3. **Multi-label Classification:** Each sample can be assigned multiple labels simultaneously (e.g., a Wikipedia article tagged with both *Mathematics* and *Computer Science*).

### Architecture of a Classification Neural Network (`08:50:50`)

| Hyperparameter | Binary Classification | Multi-class Classification |
| :--- | :--- | :--- |
| **Input Layer Shape** (`in_features`) | Same as number of features (e.g., $2$ for $X_1, X_2$) | Same as number of features |
| **Hidden Layer(s)** | Problem specific (minimum $= 1$, maximum $= \text{unlimited}$) | Problem specific |
| **Neurons per Hidden Layer** | Problem specific (generally $10$ to $512$) | Problem specific |
| **Output Layer Shape** (`out_features`) | $1$ (one class or the other) | $1$ per class (e.g., $C$ neurons for $C$ classes) |
| **Hidden Layer Activation** | Usually ReLU (`nn.ReLU()`) | Usually ReLU (`nn.ReLU()`) |
| **Output Activation** | Sigmoid (`torch.sigmoid` for binary probabilities) | Softmax (`torch.softmax` for class probability distribution) |
| **Loss Function** | Binary Cross-Entropy (`nn.BCEWithLogitsLoss`) | Cross-Entropy (`nn.CrossEntropyLoss`) |
| **Optimizer** | SGD (`torch.optim.SGD`) or Adam (`torch.optim.Adam`) | SGD or Adam |

---

## 2. Binary Classification Data & First Model (`09:09:41` – `09:57:13`)

### Turning Toy Data into Tensors (`09:09:41`)
We generate non-linear concentric circles using `sklearn.datasets.make_circles`:
* **Gotcha:** Scikit-Learn defaults to $64$-bit floats (`float64`), whereas PyTorch layers expect $32$-bit floats (`float32`). Always cast with `.type(torch.float)`!

```python
from sklearn.datasets import make_circles
from sklearn.model_selection import train_test_split
import torch
from torch import nn

n_samples = 1000
X, y = make_circles(n_samples, noise=0.03, random_state=42)

# Convert NumPy arrays to float32 PyTorch tensors
X = torch.from_numpy(X).type(torch.float)
y = torch.from_numpy(y).type(torch.float)

# Split into train (80%) and test (20%) sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
```

### Coding `CircleModelV0` and Using `nn.Sequential` (`09:25:58` – `09:57:13`)
`nn.Sequential` chains layers sequentially, running a forward pass through them in order:

```python
device = "cuda" if torch.cuda.is_available() else "cpu"

model_0 = nn.Sequential(
    nn.Linear(in_features=2, out_features=5),
    nn.Linear(in_features=5, out_features=1)
).to(device)
```

---

## 3. Loss Functions, Evaluation Metrics, and the Logits Pipeline (`09:57:13` – `11:51:26`)

### `nn.BCEWithLogitsLoss()` vs. `nn.BCELoss()` (`09:57:13`)
* **`nn.BCEWithLogitsLoss()`** has a **Sigmoid** activation layer built-in (`Sigmoid` + `BCELoss`).
* It is more **numerically stable** than applying `nn.Sigmoid()` followed by `nn.BCELoss()` separately (thanks to the log-sum-exp trick).
* Therefore, your model's `forward()` method should always output **raw logits** (unscaled outputs before Sigmoid/Softmax), and you pass those raw logits directly to `nn.BCEWithLogitsLoss()`.

### From Model Logits $\rightarrow$ Prediction Probabilities $\rightarrow$ Prediction Labels (`10:12:05`)
Understanding this three-stage pipeline is essential for classification in PyTorch:

$$\text{Raw Logits } (z) \xrightarrow{\text{Activation}} \text{Prediction Probabilities } (p) \xrightarrow{\text{Rounding / Argmax}} \text{Prediction Labels } (\hat{y})$$

1. **Binary Classification Pipeline:**
   * **Logits:** `y_logits = model(X_test).squeeze()` (values in $(-\infty, \infty)$)
   * **Probabilities:** `y_pred_probs = torch.sigmoid(y_logits)` where $\sigma(z) = \frac{1}{1 + e^{-z}} \in (0, 1)$
   * **Labels:** `y_preds = torch.round(y_pred_probs)` ($p \ge 0.5 \rightarrow 1$, $p < 0.5 \rightarrow 0$)
   * **One-liner:** `y_preds = torch.round(torch.sigmoid(model(X_test).squeeze()))`

2. **Multi-class Classification Pipeline:**
   * **Logits:** `y_logits = model(X_test)` (shape `[batch_size, num_classes]`)
   * **Probabilities:** `y_pred_probs = torch.softmax(y_logits, dim=1)` where $\text{Softmax}(z_i) = \frac{e^{z_i}}{\sum_j e^{z_j}}$ (sums to $1.0$ across `dim=1`)
   * **Labels:** `y_preds = torch.argmax(y_pred_probs, dim=1)` (picks index of highest probability)

### Accuracy Metric Function
```python
def accuracy_fn(y_true, y_pred):
    correct = torch.eq(y_true, y_pred).sum().item()
    acc = (correct / len(y_pred)) * 100
    return acc
```

### Options to Improve a Model (Hyperparameter Tuning) (`10:57:55`)
When a model underfits (e.g., $50\%$ accuracy on circles), how can we try to improve it?
* **Add more layers** (make the network deeper).
* **Add more hidden units** per layer (make the network wider).
* **Fit for longer** (more epochs).
* **Change/add activation functions** (introduce non-linearity!).
* **Change the learning rate** (too high explodes; too low learns too slowly).
* **Change the loss function or optimizer**.

---

## 4. The Missing Piece: Non-Linearity (`11:51:26` – `12:42:32`)

Why did `CircleModelV0` (and `CircleModelV1` with more hidden units/layers/epochs) only achieve $50\%$ accuracy on `make_circles`?
* Because stacking linear layers without non-linear activation functions can **only ever draw straight lines**!
* To classify concentric circles, we need **non-linear activation functions** like **ReLU** ($\text{ReLU}(x) = \max(0, x)$):

```python
class CircleModelV2(nn.Module):
    def __init__(self):
        super().__init__()
        self.layer_1 = nn.Linear(in_features=2, out_features=10)
        self.layer_2 = nn.Linear(in_features=10, out_features=10)
        self.layer_3 = nn.Linear(in_features=10, out_features=1)
        self.relu = nn.ReLU()  # Non-linear activation function

    def forward(self, x):
        # Put non-linear activation between linear layers
        return self.layer_3(self.relu(self.layer_2(self.relu(self.layer_1(x)))))

model_3 = CircleModelV2().to(device)
loss_fn = nn.BCEWithLogitsLoss()
optimizer = torch.optim.SGD(model_3.parameters(), lr=0.1)
```

### Training & Testing Loop for Binary Classification
* **Shape Gotcha:** `model_3(X_train)` outputs shape `[800, 1]`, while `y_train` has shape `[800]`. Always call `.squeeze()` on the output logits so shapes match!

```python
X_train, y_train = X_train.to(device), y_train.to(device)
X_test, y_test = X_test.to(device), y_test.to(device)

for epoch in range(1000):
    model_3.train()
    # 1. Forward pass (squeeze to remove extra dimension of 1)
    y_logits = model_3(X_train).squeeze()
    y_pred = torch.round(torch.sigmoid(y_logits))

    # 2. Calculate loss (BCEWithLogitsLoss expects raw logits as first arg!)
    loss = loss_fn(y_logits, y_train)
    acc = accuracy_fn(y_true=y_train, y_pred=y_pred)

    # 3. Optimizer zero grad -> 4. Loss backward -> 5. Optimizer step
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()
```

---

## 5. Multi-Class Classification (`12:42:32` – `14:00:48`)

### Building a Multi-Class Model (`BlobModel`) (`12:42:32`)
Using `sklearn.datasets.make_blobs` with $4$ classes and $2$ features:
* **Datatype Gotcha (`13:24:09`):** `nn.CrossEntropyLoss()` requires inputs `y_logits` to be `torch.float32` of shape `[N, C]` and target class indices `y_train` to be **`torch.LongTensor` (`torch.int64`)** of shape `[N]`.

```python
from sklearn.datasets import make_blobs

X_blob, y_blob = make_blobs(n_samples=1000, n_features=2, centers=4, cluster_std=1.5, random_state=42)
X_blob = torch.from_numpy(X_blob).type(torch.float)
y_blob = torch.from_numpy(y_blob).type(torch.LongTensor)  # MUST be LongTensor for CrossEntropyLoss!

X_blob_train, X_blob_test, y_blob_train, y_blob_test = train_test_split(
    X_blob, y_blob, test_size=0.2, random_state=42
)

class BlobModel(nn.Module):
    def __init__(self, input_features, output_features, hidden_units=8):
        super().__init__()
        self.linear_layer_stack = nn.Sequential(
            nn.Linear(in_features=input_features, out_features=hidden_units),
            nn.ReLU(),
            nn.Linear(in_features=hidden_units, out_features=hidden_units),
            nn.ReLU(),
            nn.Linear(in_features=hidden_units, out_features=output_features)
        )

    def forward(self, x):
        return self.linear_layer_stack(x)

model_4 = BlobModel(input_features=2, output_features=4, hidden_units=8).to(device)
loss_fn = nn.CrossEntropyLoss()  # Includes LogSoftmax internally -> pass raw logits!
optimizer = torch.optim.SGD(params=model_4.parameters(), lr=0.1)
```

### Beyond Accuracy: Classification Evaluation Metrics (`13:45:00`)

| Metric | Mathematical Formula | When to Use | `torchmetrics` Class |
| :--- | :--- | :--- | :--- |
| **Accuracy** | $\frac{TP + TN}{TP + TN + FP + FN}$ | Default metric for **balanced** classes. | `torchmetrics.Accuracy` |
| **Precision** | $\frac{TP}{TP + FP}$ | When **False Positives** are costly (e.g., marking important emails as spam). | `torchmetrics.Precision` |
| **Recall** | $\frac{TP}{TP + FN}$ | When **False Negatives** are costly (e.g., missing a medical diagnosis). | `torchmetrics.Recall` |
| **F1-Score** | $2 \cdot \frac{\text{Precision} \cdot \text{Recall}}{\text{Precision} + \text{Recall}}$ | Harmonic mean of Precision and Recall; great for imbalanced datasets. | `torchmetrics.F1Score` |
| **Confusion Matrix** | $C \times C$ grid comparing actual vs. predicted classes | Visualizing exactly *which* classes the model confuses with each other. | `torchmetrics.ConfusionMatrix` |