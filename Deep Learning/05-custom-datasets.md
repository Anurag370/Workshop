---
title: "Custom Datasets and Image Classification"
course: "PyTorch for Deep Learning & Machine Learning"
chapter: "4"
source: "https://www.youtube.com/watch?v=V_xro1bcAuA&t=71045s"
tags: [pytorch, custom-dataset, data-augmentation, computer-vision, obsidian]
---

# Chapter 4 — Custom Datasets

## Learning objectives

- Inspect a custom image dataset.
- Build image transforms and a `DataLoader`.
- Implement a custom `Dataset`.
- Apply realistic data augmentation.
- Establish a baseline and detect overfitting.
- Predict on new images and save inference metadata.

## 1. Inspect the data first

Before training, inspect:
- Number of images per class.
- Corrupt or unreadable files.
- Image dimensions and color modes.
- Duplicate and near-duplicate images.
- Label quality and ambiguous examples.
- How train, validation, and test splits were created.

A model can learn spurious cues such as background, lighting, watermarks, or capture setup instead of the intended visual signal. Data inspection is part of modeling, not an optional cosmetic step.

## 2. Directory structure

A common folder-per-class layout is:

```text
dataset/
  train/
    healthy/
    disease_a/
    disease_b/
  val/
    healthy/
    disease_a/
    disease_b/
  test/
    healthy/
    disease_a/
    disease_b/
```

`torchvision.datasets.ImageFolder` can read this structure. It assigns class indices based on sorted directory names; inspect `dataset.class_to_idx` and preserve it for inference.

```python
from torchvision import datasets, transforms
from torch.utils.data import DataLoader

train_transform = transforms.Compose([
    transforms.Resize((224, 224)),
    transforms.RandomHorizontalFlip(),
    transforms.ToTensor(),
])

eval_transform = transforms.Compose([
    transforms.Resize((224, 224)),
    transforms.ToTensor(),
])

train_dataset = datasets.ImageFolder("dataset/train", transform=train_transform)
val_dataset = datasets.ImageFolder("dataset/val", transform=eval_transform)

print(train_dataset.classes)
print(train_dataset.class_to_idx)

train_loader = DataLoader(train_dataset, batch_size=32, shuffle=True)
val_loader = DataLoader(val_dataset, batch_size=32, shuffle=False)
```

The paths above are examples; replace them with your actual dataset paths. Use the same class mapping across splits and verify that every split contains the intended classes.

## 3. Custom Dataset class

Use a custom `Dataset` when the data layout or labeling format does not fit built-in dataset classes.

```python
from pathlib import Path
from PIL import Image
from torch.utils.data import Dataset

class LeafDataset(Dataset):
    def __init__(self, image_paths, labels, transform=None):
        if len(image_paths) != len(labels):
            raise ValueError("image_paths and labels must have equal length")
        self.image_paths = list(image_paths)
        self.labels = list(labels)
        self.transform = transform

    def __len__(self):
        return len(self.image_paths)

    def __getitem__(self, index):
        image_path = self.image_paths[index]
        image = Image.open(image_path).convert("RGB")
        label = int(self.labels[index])

        if self.transform is not None:
            image = self.transform(image)

        return image, label
```

The labels must use a stable class-index mapping. In real use, validate paths and labels before training, and handle corrupt images explicitly rather than silently dropping examples.

## 4. Augmentation

Data augmentation creates plausible variations of training examples, which can improve generalization.

Examples:
- Horizontal flips when orientation is not label-defining.
- Small rotations or crops when realistic for the task.
- Mild color changes if lighting variation is expected.

Avoid transformations that change the label or remove important evidence. For plant disease detection, aggressive color jitter can erase disease-related color patterns; validate augmentation choices against the actual deployment environment.

Use augmentation only for training. Validation and test preprocessing should be deterministic and consistent with inference.

## 5. Baseline model

A baseline provides a reference point. Keep it simple enough to train and debug. Record:
- Architecture and parameter count.
- Image size and normalization.
- Optimizer and learning rate.
- Batch size and epochs.
- Train/validation loss and metrics.
- Dataset split and random seed.

Do not judge models only by a single final accuracy value. Plot learning curves and examine per-class errors.

## 6. Overfitting and underfitting

- **Underfitting:** model fails to learn even the training set well. Possible causes include a model that is too limited, poor features, too little training, or a bug.
- **Overfitting:** training performance improves while validation performance stalls or worsens. The model is fitting training-specific patterns that do not generalize.

Possible responses to overfitting:
- Improve data quality and split design.
- Use realistic augmentation.
- Reduce model capacity.
- Add weight decay or other regularization.
- Use early stopping based on validation metrics.
- Collect more representative data.

A gap between training and validation performance is a clue, not a diagnosis by itself. Inspect the data pipeline and metrics before changing architecture.

## 7. Evaluate with a confusion matrix

For each class, inspect false positives and false negatives. If the model misses a disease class, determine whether the problem is class imbalance, confusing labels, insufficient examples, visual similarity, or leakage.

Use a held-out test set for the final estimate. Choose thresholds and hyperparameters using validation data, not the test set.

## 8. Predict on a single image

```python
from PIL import Image
import torch

def predict_image(image_path, model, transform, class_names, device):
    image = Image.open(image_path).convert("RGB")
    x = transform(image).unsqueeze(0).to(device)

    model.eval()
    with torch.inference_mode():
        logits = model(x)
        probabilities = torch.softmax(logits, dim=1)
        predicted_index = probabilities.argmax(dim=1).item()

    return {
        "class_name": class_names[predicted_index],
        "confidence": probabilities[0, predicted_index].item(),
        "probabilities": probabilities[0].cpu().tolist(),
    }
```

The `transform`, `class_names`, image size, normalization, and model output format must match training. Confidence is not a guarantee of correctness; consider calibration and an “uncertain / seek expert review” policy for high-impact use cases.

## 9. Save model and metadata

```python
checkpoint = {
    "model_state_dict": model.state_dict(),
    "class_names": train_dataset.classes,
    "image_size": 224,
}
torch.save(checkpoint, "planthealth_cnn.pth")
```

When loading, recreate the same architecture, load the state dictionary, and restore the metadata. For production, version the preprocessing pipeline and record library versions. Do not assume the weights alone are enough to reproduce inference.

## 10. Practical checklist

- [ ] Dataset labels and class counts inspected.
- [ ] Train/validation/test split documented.
- [ ] Leakage and duplicates checked.
- [ ] Input size, channels, and normalization fixed.
- [ ] Dataset and DataLoader return correct shapes.
- [ ] Baseline training loop verified on a small subset.
- [ ] Train and validation curves logged.
- [ ] Per-class metrics and confusion matrix reviewed.
- [ ] Single-image inference matches validation preprocessing.
- [ ] Weights and class mapping saved together.

## Checkpoint

1. When should you write a custom `Dataset` instead of using `ImageFolder`?
2. Why should validation transforms be deterministic?
3. What is the difference between underfitting and overfitting?
4. Why must the class-to-index mapping be saved?
5. How can duplicate images between train and test inflate performance?

## PlantHealth AI connection

Use the PlantVillage dataset and your project requirements to create a reproducible pipeline. First train and evaluate a custom CNN. Keep the test set untouched until model selection is complete. Only after you have a trustworthy baseline should you compare a pretrained model such as MobileNet, ResNet, or VGG as a separate transfer-learning experiment.
