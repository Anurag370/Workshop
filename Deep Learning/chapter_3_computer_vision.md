# Chapter 3: PyTorch Computer Vision

* **Course:** PyTorch for Deep Learning & Machine Learning – Full Course (`freeCodeCamp.org`)
* **Instructor:** Daniel Bourke (`@mrdbourke`)
* **Video URL:** [https://www.youtube.com/watch?v=V_xro1bcAuA](https://www.youtube.com/watch?v=V_xro1bcAuA)
* **Chapter Timestamp Range:** `14:00:48` – `19:44:05`

---

## 1. Computer Vision Foundations & `torchvision` (`14:00:48` – `15:01:34`)

### Computer Vision Input and Output Shapes (`14:12:36`)
An image is represented as a $3\text{D}$ tensor (or $4\text{D}$ with a batch dimension):
* **Single Image Shape:** `[color_channels, height, width]` (`[C, H, W]`, e.g., `[3, 224, 224]` for RGB or `[1, 28, 28]` for grayscale).
* **Batched Image Shape:** `[batch_size, color_channels, height, width]` (`[N, C, H, W]`, known as **Channels First** in PyTorch, vs. `[N, H, W, C]` Channels Last in Matplotlib/TensorFlow).

### Core `torchvision` Libraries (`14:27:49`)
* **`torchvision.datasets`**: Pre-built datasets and base dataset classes for computer vision (e.g., `FashionMNIST`, `ImageFolder`).
* **`torchvision.models`**: Pre-trained computer vision model architectures (e.g., ResNet, VGG, Vision Transformers).
* **`torchvision.transforms`**: Functions for manipulating and augmenting images into tensors ready for models (e.g., `ToTensor()`, `Resize()`).
* **`torch.utils.data.Dataset`**: Base dataset class for PyTorch.
* **`torch.utils.data.DataLoader`**: Wraps a `Dataset` into a Python iterable over mini-batches.

### Loading the `FashionMNIST` Dataset (`14:37:10`)
`FashionMNIST` contains $60,000$ training images and $10,000$ testing images across $10$ clothing classes, each a $28 \times 28$ grayscale image (`[1, 28, 28]`).

```python
import torch
from torch import nn
import torchvision
from torchvision import datasets
from torchvision.transforms import ToTensor

train_data = datasets.FashionMNIST(
    root="data",
    train=True,
    download=True,
    transform=ToTensor(),  # Converts PIL image [0, 255] (H, W, C) -> float tensor [0.0, 1.0] (C, H, W)
    target_transform=None
)

test_data = datasets.FashionMNIST(
    root="data",
    train=False,
    download=True,
    transform=ToTensor()
)

class_names = train_data.classes  # List of 10 strings: ['T-shirt/top', 'Trouser', ...]
```

---

## 2. Mini-Batches and `DataLoader` (`15:01:34` – `15:25:00`)

### Why Use Mini-Batches? (`15:01:34`)
Instead of computing the forward and backward pass on all $60,000$ images at once:
1. **Computational Efficiency:** Your hardware (CPU/GPU RAM) cannot fit millions of high-resolution images into memory simultaneously.
2. **More Gradient Updates per Epoch:** With `batch_size=32`, the optimizer updates model weights $\frac{60,000}{32} = 1,875$ times per epoch instead of just $1$ time per epoch!

```python
from torch.utils.data import DataLoader

BATCH_SIZE = 32

train_dataloader = DataLoader(
    dataset=train_data,
    batch_size=BATCH_SIZE,
    shuffle=True   # Shuffle training data every epoch to prevent learning order bias!
)

test_dataloader = DataLoader(
    dataset=test_data,
    batch_size=BATCH_SIZE,
    shuffle=False  # Don't need to shuffle evaluation/test data
)

# Inspect first batch
train_features_batch, train_labels_batch = next(iter(train_dataloader))
print(train_features_batch.shape)  # torch.Size([32, 1, 28, 28])
```

---

## 3. Model 0 & Model 1: Linear Baseline vs. Non-Linear Model (`15:25:00` – `17:13:32`)

### How `nn.Flatten()` Works (`15:25:00`)
Standard `nn.Linear` layers cannot process $2\text{D}$ spatial grids directly—they expect a $1\text{D}$ feature vector per sample. `nn.Flatten()` compresses `[batch_size, C, H, W]` into `[batch_size, C * H * W]`:

$$\text{Shape: } [32, 1, 28, 28] \xrightarrow{\text{nn.Flatten()}} [32, 1 \times 28 \times 28] = [32, 784]$$

```python
class FashionMNISTModelV0(nn.Module):
    def __init__(self, input_shape: int, hidden_units: int, output_shape: int):
        super().__init__()
        self.layer_stack = nn.Sequential(
            nn.Flatten(),
            nn.Linear(in_features=input_shape, out_features=hidden_units),
            nn.Linear(in_features=hidden_units, out_features=output_shape)
        )

    def forward(self, x):
        return self.layer_stack(x)

model_0 = FashionMNISTModelV0(input_shape=784, hidden_units=10, output_shape=len(class_names))
```

### Reusable Batched `train_step()` and `test_step()` Functions (`15:52:01` & `16:42:23`)
When training on batched `DataLoader`s:
* Optimizer updates happen **per batch** (inside the inner `for batch, (X, y) in enumerate(data_loader):` loop).
* Loss and accuracy are accumulated over all batches and divided by `len(data_loader)` at the end of the epoch to compute the average per-batch loss and accuracy.

```python
def train_step(model: torch.nn.Module,
               data_loader: torch.utils.data.DataLoader,
               loss_fn: torch.nn.Module,
               optimizer: torch.optim.Optimizer,
               accuracy_fn,
               device: torch.device):
    train_loss, train_acc = 0, 0
    model.train()

    for batch, (X, y) in enumerate(data_loader):
        X, y = X.to(device), y.to(device)
        y_pred = model(X)
        loss = loss_fn(y_pred, y)
        train_loss += loss.item()
        train_acc += accuracy_fn(y_true=y, y_pred=y_pred.argmax(dim=1))

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

    train_loss /= len(data_loader)
    train_acc /= len(data_loader)
    print(f"Train loss: {train_loss:.5f} | Train acc: {train_acc:.2f}%")

def test_step(model: torch.nn.Module,
              data_loader: torch.utils.data.DataLoader,
              loss_fn: torch.nn.Module,
              accuracy_fn,
              device: torch.device):
    test_loss, test_acc = 0, 0
    model.eval()
    with torch.inference_mode():
        for X, y in data_loader:
            X, y = X.to(device), y.to(device)
            test_pred = model(X)
            test_loss += loss_fn(test_pred, y).item()
            test_acc += accuracy_fn(y_true=y, y_pred=test_pred.argmax(dim=1))

        test_loss /= len(data_loader)
        test_acc /= len(data_loader)
        print(f"Test loss: {test_loss:.5f} | Test acc: {test_acc:.2f}%\n")
```

---

## 4. Model 2: Convolutional Neural Networks (CNNs) & TinyVGG (`17:13:32` – `18:44:22`)

Why did adding `nn.ReLU()` in `FashionMNISTModelV1` actually perform slightly worse on test data than linear `ModelV0`? Because flattening an image immediately destroys its $2\text{D}$ spatial structure! **Convolutional Neural Networks (CNNs)** preserve spatial structure by sliding learnable $2\text{D}$ filters across the image.

### Breaking Down `nn.Conv2d` and `nn.MaxPool2d` (`17:41:46`)
1. **`nn.Conv2d(in_channels, out_channels, kernel_size, stride, padding)`**:
   * **`in_channels`**: Number of channels in the input image ($1$ for grayscale, $3$ for RGB, or `hidden_units` for subsequent conv layers).
   * **`out_channels`**: Number of learnable filters (feature maps) produced by the layer.
   * **`kernel_size`**: Height and width of the sliding convolutional window (e.g., `3` or `(3, 3)`).
   * **`stride`**: Number of pixels the kernel shifts at each step (default $= 1$).
   * **`padding`**: Number of border pixels added around the input so edge pixels aren't lost and spatial dimensions are preserved (e.g., `padding=1` with `kernel_size=3, stride=1` preserves height and width).

$$H_{\text{out}} = \left\lfloor \frac{H_{\text{in}} + 2 \times \text{padding} - \text{kernel\_size}}{\text{stride}} \right\rfloor + 1$$

2. **`nn.MaxPool2d(kernel_size=2)`**:
   * Takes the maximum value from each $2 \times 2$ window, cutting spatial height and width in half ($28 \times 28 \rightarrow 14 \times 14 \rightarrow 7 \times 7$), which compresses features and reduces computation by $4\times$.

### Coding the TinyVGG CNN Architecture (`17:21:57`)
Based on the interactive [CNN Explainer website](https://poloclub.github.io/cnn-explainer/), TinyVGG stacks two convolutional blocks (`Conv2d -> ReLU -> Conv2d -> ReLU -> MaxPool2d`) followed by a linear classifier:

```python
class FashionMNISTModelV2(nn.Module):
    """Model architecture copying TinyVGG from CNN Explainer."""
    def __init__(self, input_shape: int, hidden_units: int, output_shape: int):
        super().__init__()
        # Block 1: [N, 1, 28, 28] -> [N, hidden_units, 14, 14]
        self.conv_block_1 = nn.Sequential(
            nn.Conv2d(in_channels=input_shape, out_channels=hidden_units,
                      kernel_size=3, stride=1, padding=1),
            nn.ReLU(),
            nn.Conv2d(in_channels=hidden_units, out_channels=hidden_units,
                      kernel_size=3, stride=1, padding=1),
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=2, stride=2)
        )
        # Block 2: [N, hidden_units, 14, 14] -> [N, hidden_units, 7, 7]
        self.conv_block_2 = nn.Sequential(
            nn.Conv2d(in_channels=hidden_units, out_channels=hidden_units,
                      kernel_size=3, stride=1, padding=1),
            nn.ReLU(),
            nn.Conv2d(in_channels=hidden_units, out_channels=hidden_units,
                      kernel_size=3, stride=1, padding=1),
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=2, stride=2)
        )
        # Classifier: Flatten [N, hidden_units, 7, 7] -> [N, hidden_units * 7 * 7]
        self.classifier = nn.Sequential(
            nn.Flatten(),
            nn.Linear(in_features=hidden_units * 7 * 7, out_features=output_shape)
        )

    def forward(self, x: torch.Tensor):
        x = self.conv_block_1(x)
        x = self.conv_block_2(x)
        x = self.classifier(x)
        return x

model_2 = FashionMNISTModelV2(input_shape=1, hidden_units=10, output_shape=len(class_names)).to(device)
```

> **Pro Tip (`17:58:00`):** Unsure what `in_features` to put in `self.classifier`'s `nn.Linear` layer? Pass a dummy tensor `torch.randn(1, 1, 28, 28)` through `conv_block_1` and `conv_block_2` and print `x.shape` before flattening!

---

## 5. Evaluating Predictions & Plotting a Confusion Matrix (`18:44:22` – `19:44:05`)

To plot a confusion matrix across the entire `test_dataloader`:

```python
from torchmetrics import ConfusionMatrix
from mlxtend.plotting import plot_confusion_matrix

# 1. Make predictions with trained CNN across all test batches
y_preds = []
model_2.eval()
with torch.inference_mode():
    for X, y in test_dataloader:
        X, y = X.to(device), y.to(device)
        y_logit = model_2(X)
        y_pred = torch.softmax(y_logit.squeeze(), dim=1).argmax(dim=1)
        y_preds.append(y_pred.cpu())

# Concatenate list of batch prediction tensors into a single 1D tensor of 10,000 predictions
y_pred_tensor = torch.cat(y_preds)

# 2. Setup ConfusionMatrix instance and compare predictions to targets
confmat = ConfusionMatrix(task="multiclass", num_classes=len(class_names))
confmat_tensor = confmat(preds=y_pred_tensor, target=test_data.targets)

# 3. Plot the confusion matrix using mlxtend
fig, ax = plot_confusion_matrix(
    conf_mat=confmat_tensor.numpy(),
    class_names=class_names,
    figsize=(10, 7)
)
```