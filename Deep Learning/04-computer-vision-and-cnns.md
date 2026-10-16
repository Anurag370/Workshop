---
title: "Computer Vision and CNNs"
course: "PyTorch for Deep Learning & Machine Learning"
chapter: "3"
source: "https://www.youtube.com/watch?v=V_xro1bcAuA&t=50448s"
tags: [pytorch, computer-vision, cnn, obsidian]
---

# Chapter 3 — Computer Vision and CNNs

## Learning objectives

- Represent images as tensors.
- Use `torchvision` datasets and transforms.
- Create mini-batches with a `DataLoader`.
- Explain convolution and pooling.
- Build and train a small CNN.
- Evaluate image classifiers with suitable metrics.

## 1. Images as tensors

A color image is commonly represented as `(C, H, W)` in PyTorch. A batch is `(N, C, H, W)`.

```python
import torch

single_image = torch.rand(3, 224, 224)
batch = torch.rand(32, 3, 224, 224)
print(single_image.shape)
print(batch.shape)
```

Image values may be represented as integers from 0 to 255 or normalized floating-point values. The exact preprocessing must match the assumptions used during training.

## 2. TorchVision and transforms

`torchvision` provides image datasets, transformations, model utilities, and common vision components.

Example transform pipeline:

```python
from torchvision import transforms

image_transform = transforms.Compose([
    transforms.Resize((224, 224)),
    transforms.ToTensor(),
])
```

`ToTensor()` typically converts PIL images or supported arrays to floating point and scales 8-bit image values into `[0, 1]`. More advanced pipelines may normalize channels using specified means and standard deviations.

For evaluation, use deterministic preprocessing. Random augmentation should generally be applied only to training data.

## 3. Dataset and DataLoader

A dataset defines how to retrieve one example and its label. A `DataLoader` batches examples and can shuffle training data.

```python
from torch.utils.data import DataLoader, TensorDataset

X = torch.rand(100, 3, 64, 64)
y = torch.randint(0, 4, (100,))
dataset = TensorDataset(X, y)

train_loader = DataLoader(dataset, batch_size=16, shuffle=True)

images, labels = next(iter(train_loader))
print(images.shape)  # (16, 3, 64, 64)
print(labels.shape)  # (16,)
```

This synthetic example demonstrates shapes only; random images and labels do not teach a meaningful classifier.

## 4. What is a CNN?

A **convolutional neural network (CNN)** uses spatially structured operations to learn image features. Early layers may learn simple local patterns, while deeper layers can combine features into more complex representations.

Common components:
- `nn.Conv2d`: applies learned filters across spatial locations.
- `nn.ReLU`: introduces nonlinearity.
- `nn.MaxPool2d`: downsamples spatial dimensions by selecting local maxima.
- `nn.Flatten`: converts feature maps to a vector.
- `nn.Linear`: maps features to output logits.

Convolution exploits local connectivity and shared weights, making it well suited to images compared with a fully connected layer applied directly to every pixel.

## 5. Convolution and pooling intuition

A convolution kernel slides across an image or feature map. Each filter learns to respond to a pattern. Output size depends on input size, kernel size, stride, padding, and dilation.

For one spatial dimension:

`output = floor((input + 2*padding - dilation*(kernel_size - 1) - 1) / stride + 1)`

With a 3×3 kernel, stride 1, padding 1, and dilation 1, height and width stay the same.

Pooling reduces spatial resolution. A 2×2 max pool with stride 2 approximately halves height and width.

## 6. A small CNN

```python
from torch import nn

class SmallCNN(nn.Module):
    def __init__(self, num_classes=4):
        super().__init__()
        self.features = nn.Sequential(
            nn.Conv2d(3, 16, kernel_size=3, padding=1),
            nn.ReLU(),
            nn.MaxPool2d(2),
            nn.Conv2d(16, 32, kernel_size=3, padding=1),
            nn.ReLU(),
            nn.MaxPool2d(2),
        )
        self.classifier = nn.Sequential(
            nn.Flatten(),
            nn.Linear(32 * 16 * 16, 64),  # assumes 64x64 input
            nn.ReLU(),
            nn.Linear(64, num_classes),
        )

    def forward(self, x):
        x = self.features(x)
        return self.classifier(x)

model = SmallCNN(num_classes=4)
x = torch.rand(8, 3, 64, 64)
print(model(x).shape)  # (8, 4)
```

This model expects 64×64 inputs because its first linear layer assumes the feature map ends at 16×16. For flexible input sizes, consider adaptive pooling or calculate the flattened dimension explicitly.

## 7. Training a CNN

The training loop follows the same workflow as other models:
1. Load a batch.
2. Move images and labels to the device.
3. Compute logits.
4. Calculate cross-entropy loss.
5. Clear gradients, backpropagate, and update parameters.
6. Evaluate without gradients.

```python
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
model = SmallCNN(num_classes=4).to(device)
loss_fn = nn.CrossEntropyLoss()
optimizer = torch.optim.Adam(model.parameters(), lr=1e-3)
```

Use realistic labeled data and track validation performance. The model definition above is a teaching example, not a tuned production architecture.

## 8. Confusion matrix and evaluation

A confusion matrix helps reveal which classes the model confuses. For a plant classifier, a model might confuse two diseases with similar leaf discoloration even when overall accuracy looks good.

Evaluate:
- Overall accuracy.
- Per-class precision and recall.
- Macro F1 when each class deserves equal weight.
- Confusion matrix.
- Performance on images from conditions not seen during training.

## Common mistakes

- Passing `(N, H, W, C)` when the model expects `(N, C, H, W)`.
- Mismatching the flattened feature count and `nn.Linear` input size.
- Applying random transformations to validation or test data.
- Training with shuffled labels or inconsistent class mappings.
- Assuming high training accuracy means the model generalizes.

## Checkpoint

1. What does the batch dimension represent?
2. What does `nn.Conv2d` learn?
3. Why does max pooling reduce spatial dimensions?
4. What is the output shape for a batch of 16 images and a 10-class model?
5. Why should augmentation be restricted to the training pipeline?

## PlantHealth AI connection

PlantHealth AI will use leaf images. Begin with a modest custom CNN and a clear baseline. Ensure all images have consistent size and channel order, inspect class balance, and use a split that avoids near-duplicate or same-source leakage. Once the baseline is reliable, compare transfer learning as a separate experiment.
