# Chapter 4: PyTorch Custom Datasets

* **Course:** PyTorch for Deep Learning & Machine Learning – Full Course (`freeCodeCamp.org`)
* **Instructor:** Daniel Bourke (`@mrdbourke`)
* **Video URL:** [https://www.youtube.com/watch?v=V_xro1bcAuA](https://www.youtube.com/watch?v=V_xro1bcAuA)
* **Chapter Timestamp Range:** `19:44:05` – `25:37:26`

---

## 1. Custom Datasets & Directory Structure (`19:44:05` – `20:39:11`)

While `torchvision.datasets` provides pre-packaged academic datasets like `FashionMNIST`, real-world problems require loading your own custom images, text, audio, or tabular files.

### Standard Image Classification Directory Format (`19:59:54`)
For image classification (`pizza_steak_sushi`, a $3$-class subset of Food101), the standard directory layout maps folder names directly to class labels:

```text
data/pizza_steak_sushi/
├── train/
│   ├── pizza/
│   │   ├── image01.jpg
│   │   └── image02.jpg
│   ├── steak/
│   └── sushi/
└── test/
    ├── pizza/
    ├── steak/
    └── sushi/
```

---

## 2. Transforming Data & Option 1: `ImageFolder` (`20:39:11` – `21:25:20`)

### Composing Image Transforms (`20:39:11`)
Before feeding variable-sized `.jpg` files into a neural network, we chain transformations using `torchvision.transforms.Compose`:
1. Resize all images to a uniform resolution (e.g., $64 \times 64$).
2. Optionally apply random data augmentations.
3. Convert the PIL Image ($[0, 255]$ in `HWC` order) into a PyTorch float tensor ($[0.0, 1.0]$ in `CHW` order).

```python
import torch
from torch.utils.data import DataLoader
from torchvision import datasets, transforms

data_transform = transforms.Compose([
    transforms.Resize(size=(64, 64)),
    transforms.RandomHorizontalFlip(p=0.5),
    transforms.ToTensor()
])
```

### Loading with `torchvision.datasets.ImageFolder` (`21:00:00`)
When your images follow the standard `train/class_name/img.jpg` directory structure, `datasets.ImageFolder` automatically discovers class names, assigns indices, and applies your transform:

```python
train_data = datasets.ImageFolder(root="data/pizza_steak_sushi/train",
                                  transform=data_transform,
                                  target_transform=None)

test_data = datasets.ImageFolder(root="data/pizza_steak_sushi/test",
                                 transform=data_transform)

class_names = train_data.classes      # ['pizza', 'steak', 'sushi']
class_dict = train_data.class_to_idx  # {'pizza': 0, 'steak': 1, 'sushi': 2}

train_dataloader = DataLoader(dataset=train_data, batch_size=32, shuffle=True, num_workers=1)
test_dataloader = DataLoader(dataset=test_data, batch_size=32, shuffle=False, num_workers=1)
```

---

## 3. Option 2: Writing a Custom `Dataset` Class from Scratch (`21:25:20` – `22:28:50`)

What if your dataset doesn't fit `ImageFolder` (e.g., labels are in a CSV/JSON file, or the data is audio, text, or medical scans)? You subclass `torch.utils.data.Dataset` and implement three methods:
1. **`__init__(self, ...)`**: Initializes paths, class mappings, and transforms (runs once on instantiation).
2. **`__len__(self)`**: Returns the total number of samples in the dataset (`len(dataset)`).
3. **`__getitem__(self, index)`**: Loads and returns a single `(sample, label)` tuple at `dataset[index]`.

```python
import os
import pathlib
from PIL import Image
from torch.utils.data import Dataset
from typing import Tuple, Dict, List

def find_classes(directory: str) -> Tuple[List[str], Dict[str, int]]:
    """Finds class folder names in a target directory."""
    classes = sorted(entry.name for entry in os.scandir(directory) if entry.is_dir())
    if not classes:
        raise FileNotFoundError(f"Couldn't find any classes in {directory}.")
    class_to_idx = {cls_name: i for i, cls_name in enumerate(classes)}
    return classes, class_to_idx

class ImageFolderCustom(Dataset):
    def __init__(self, targ_dir: str, transform=None) -> None:
        self.paths = list(pathlib.Path(targ_dir).glob("*/*.jpg"))
        self.transform = transform
        self.classes, self.class_to_idx = find_classes(targ_dir)

    def load_image(self, index: int) -> Image.Image:
        image_path = self.paths[index]
        return Image.open(image_path)

    def __len__(self) -> int:
        return len(self.paths)

    def __getitem__(self, index: int) -> Tuple[torch.Tensor, int]:
        img = self.load_image(index)
        class_name = self.paths[index].parent.name  # parent folder is the class name
        class_idx = self.class_to_idx[class_name]

        if self.transform:
            return self.transform(img), class_idx
        else:
            return img, class_idx
```

---

## 4. Data Augmentation & Inspecting Models with `torchinfo` (`22:28:50` – `23:50:59`)

### Data Augmentation (`22:28:50`)
**Data Augmentation** artificially increases the diversity of your training set by applying random transformations (rotations, flips, color jitter, cropping, or `transforms.TrivialAugmentWide(num_magnitude_bins=31)`) to training images on the fly.
* **Important Rule:** Only apply data augmentation to the **training** `Dataset`, **never** to the testing/validation `Dataset`!

```python
train_transform_trivial = transforms.Compose([
    transforms.Resize(size=(64, 64)),
    transforms.TrivialAugmentWide(num_magnitude_bins=31),
    transforms.ToTensor()
])

test_transform_simple = transforms.Compose([
    transforms.Resize(size=(64, 64)),
    transforms.ToTensor()
])
```

### Inspecting Model Shapes with `torchinfo.summary()` (`23:11:07`)
Instead of manually calculating spatial shapes across every convolutional layer, use `torchinfo.summary` to view every layer's output shape and parameter count:

```python
from torchinfo import summary

# Pass an example input_size matching [batch_size, color_channels, height, width]
summary(model_0, input_size=[1, 3, 64, 64])
```

---

## 5. Overfitting vs. Underfitting (`24:00:02` – `24:46:50`)

By plotting training vs. testing loss and accuracy curves across epochs, we diagnose whether a model is **underfitting**, **overfitting**, or **generalizing well**:

| Condition | Symptom on Loss/Accuracy Curves | How to Fix It |
| :--- | :--- | :--- |
| **Underfitting** | Both training and testing accuracy are low (or loss remains high). Model fails to learn underlying patterns. | $\bullet$ Use a larger/more complex model (more layers/hidden units)<br>$\bullet$ Train for more epochs<br>$\bullet$ Tune the learning rate<br>$\bullet$ Reduce regularization |
| **Overfitting** | Training loss keeps dropping ($99\%$ train accuracy), while test loss rises or stagnates ($50\%$ test accuracy). Model is memorizing the training set. | $\bullet$ **Get more data**<br>$\bullet$ **Use data augmentation**<br>$\bullet$ **Use transfer learning** (pretrained weights)<br>$\bullet$ Simplify the model / add Dropout (`nn.Dropout`) or Weight Decay<br>$\bullet$ Use early stopping |

---

## 6. Predicting on Custom Real-World Images (`24:46:50` – `25:37:26`)

When making predictions on a brand-new image downloaded from the internet or taken on your phone, you must prevent the **4 Major Inference Gotchas**:
1. **Same Shape:** Resize the image to match the resolution the model was trained on (e.g., $64 \times 64$).
2. **Same Datatype:** `torchvision.io.read_image()` loads a `uint8` tensor ($0\text{–}255$). Divide by $255.0$ or convert to `torch.float32` ($[0.0, 1.0]$).
3. **Batch Dimension:** Models expect `[batch_size, C, H, W]`, so add a batch dimension of $1$ using `.unsqueeze(dim=0)` (`[3, 64, 64]` $\rightarrow$ `[1, 3, 64, 64]`).
4. **Same Device:** Send the transformed image tensor to the exact same `device` as the model!

```python
import torchvision
import matplotlib.pyplot as plt
from typing import List

def pred_and_plot_image(model: torch.nn.Module,
                        image_path: str,
                        class_names: List[str] = None,
                        transform=None,
                        device: torch.device = device):
    """Makes a prediction on a target image with a trained model and plots the image."""
    # 1. Load in image and convert the tensor values to float32 in [0.0, 1.0]
    target_image = torchvision.io.read_image(str(image_path)).type(torch.float32) / 255.0

    # 2. Transform if necessary (e.g., Resize to 64x64)
    if transform:
        target_image = transform(target_image)

    # 3. Make sure the model is on the target device and in eval mode
    model.to(device)
    model.eval()
    with torch.inference_mode():
        # 4. Add an extra batch dimension -> [1, 3, 64, 64] and send to device
        target_image_OnDevice = target_image.unsqueeze(dim=0).to(device)

        # 5. Forward pass -> logits -> probabilities -> predicted label index
        target_image_pred = model(target_image_OnDevice)
        target_image_pred_probs = torch.softmax(target_image_pred, dim=1)
        target_image_pred_label = torch.argmax(target_image_pred_probs, dim=1)

    # 6. Plot the image (permute from PyTorch [C, H, W] to Matplotlib [H, W, C])
    plt.imshow(target_image.squeeze().permute(1, 2, 0))
    if class_names:
        title = f"Pred: {class_names[target_image_pred_label.cpu()]} | Prob: {target_image_pred_probs.max().cpu():.3f}"
    else:
        title = f"Pred: {target_image_pred_label} | Prob: {target_image_pred_probs.max().cpu():.3f}"
    plt.title(title)
    plt.axis(False)
```