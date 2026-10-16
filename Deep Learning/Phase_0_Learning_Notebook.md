---
date: 2026-10-11
subtitle: "PyTorch Foundations: Tensors, Neural Networks, and Training"
title: PlantHealth AI --- Phase 0 Learning Notebook
---

# PlantHealth AI --- Phase 0 Learning Notebook

> **Purpose:** Keep a revision-ready record of Phase 0 lessons taught so
> far. The notes preserve the teaching sequence: concept → example →
> code → checkpoint → key corrections.
>
> **Current progress:** Lessons 1--6 completed. Phase 1 (CNN
> fundamentals) has not started yet.

## Project context

PlantHealth AI is a plant disease image-classification project. The
intended path is to learn PyTorch fundamentals first, then understand
CNNs, train and evaluate models, and eventually build a simple
deployment/demo.

The project direction discussed so far includes:

-   **Framework:** PyTorch and Torchvision
-   **Dataset direction:** PlantVillage, described in the project brief
    as containing more than 50,000 images across 38 classes
-   **Image preparation direction:** Resize images (for example, to 224
    × 224), normalize, and augment training images
-   **Model direction:** Build a custom CNN, then compare transfer
    learning models such as VGG16, ResNet, or MobileNet
-   **Evaluation direction:** Accuracy, precision, recall, F1-score,
    confusion matrix, and training/validation curves
-   **Deployment direction:** A small app/API after the model has been
    trained and evaluated

These are project goals, not work completed in Phase 0.

------------------------------------------------------------------------

# Phase 0 --- Lesson 1: Tensor Fundamentals

## 1. What is a tensor?

A **tensor** is the main data structure used by PyTorch. It can
represent a single number, a list of numbers, a matrix, or data with
many dimensions.

Examples:

``` python
import torch

a = torch.tensor(5)
b = torch.tensor([1, 2, 3])
c = torch.tensor([[1, 2], [3, 4]])

print(a.shape, a.ndim)
print(b.shape, b.ndim)
print(c.shape, c.ndim)
```

Conceptually:

-   `a` is a scalar: 0 dimensions
-   `b` is a vector: 1 dimension
-   `c` is a matrix: 2 dimensions

`shape` describes the size along each dimension. `ndim` tells you how
many dimensions the tensor has.

## 2. Image tensors and batch dimensions

For image models, tensor dimensions matter a lot. A common PyTorch
image-batch layout is:

`(batch_size, channels, height, width)`

Example:

``` python
image_tensor = torch.rand(8, 3, 224, 224)

print(image_tensor.shape)
print(image_tensor.ndim)
```

Interpretation:

-   `8`: eight images in the batch
-   `3`: three color channels (commonly RGB)
-   `224`: image height
-   `224`: image width

The tensor has **4 dimensions**.

Select one image:

``` python
first_image = image_tensor[0]
print(first_image.shape)  # (3, 224, 224)
```

Select the second channel of the first image:

``` python
green_channel = image_tensor[0, 1]
print(green_channel.shape)  # (224, 224)
```

The first index selects the image; the second selects the channel.
Indexing removes those selected dimensions from the resulting shape.

## 3. Reshaping tensors

A tensor can be reshaped only if the number of elements stays the same.

``` python
tensor_range = torch.arange(0, 24)
reshaped = tensor_range.reshape(4, 6)

print(reshaped)
print(reshaped.shape)  # (4, 6)
```

There are 24 elements, and `4 × 6 = 24`, so this reshape works.

A common mistake:

``` python
torch.arange(0, 11).reshape(2, 5)
```

`torch.arange(0, 11)` creates 11 values (0 through 10), but a shape of
`(2, 5)` requires 10 values. This raises an error because the element
counts do not match.

### Lesson 1 checkpoint --- answers

1.  `image_tensor` has 4 dimensions.
2.  Reshaping 11 elements to `(2, 5)` fails because 11 is not equal to
    `2 × 5 = 10`.
3.  `image_tensor[0, 1]` has shape `(224, 224)`.

### Key takeaways

-   Check `.shape` and `.ndim` when you are unsure about tensor
    dimensions.
-   Image batches commonly use `(N, C, H, W)` in PyTorch.
-   A reshape changes the arrangement/shape, not the number of elements.

------------------------------------------------------------------------

# Phase 0 --- Lesson 2: Dtypes, Devices, and Autograd

## 1. Tensor data types (`dtype`)

A tensor's dtype describes the kind of values it stores.

Common types:

-   `torch.float32`: 32-bit floating-point values; common for model
    inputs and parameters
-   `torch.float64`: 64-bit floating-point values
-   `torch.int64` / `torch.long`: integer values; commonly used for
    class labels in classification losses such as cross-entropy
-   `torch.bool`: Boolean values

Example:

``` python
x = torch.tensor([1.0, 2.0], dtype=torch.float32)
labels = torch.tensor([0, 1], dtype=torch.int64)

print(x.dtype)
print(labels.dtype)
```

## 2. CPU vs. GPU (`device`)

PyTorch tensors and models can run on a CPU or a supported GPU. CUDA is
used for compatible NVIDIA GPUs.

``` python
import torch

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print("Selected device:", device)
print("CUDA available:", torch.cuda.is_available())
```

In this learning session, the user reported:

``` text
Selected device = cuda
torch.cuda.is_available() = true
```

That indicates PyTorch reported CUDA as available in that environment.
It does not by itself establish the exact GPU model or how fast a
particular workload will run.

If a model is moved to a device, its input tensors must be on a
compatible device too.

## 3. Autograd and gradients

PyTorch's autograd system calculates derivatives for tensors that track
gradients.

``` python
import torch

x = torch.tensor(4.0, requires_grad=True)
y = x**2
y.backward()

print(x.grad)  # tensor(8.)
```

Why is the gradient 8?

Given:

\[ y=x\^2 \]

The derivative is:

\[ `\frac{dy}{dx}`{=tex}=2x \]

At (x=4):

\[ `\frac{dy}{dx}`{=tex}=2(4)=8 \]

`requires_grad=True` asks PyTorch to track operations needed to
calculate gradients. Calling `y.backward()` calculates the gradient,
which is available in `x.grad`.

### Lesson 2 checkpoint --- answers

1.  `torch.float32` is a common floating-point dtype.
2.  If CUDA is unavailable, the device-selection expression chooses the
    CPU.
3.  `loss.backward()` calculates gradients for tracked
    parameters/tensors.
4.  For (y=x\^2) at (x=4), the gradient is 8.

### Key takeaways

-   Dtype and device are different concepts.
-   `requires_grad=True` enables gradient tracking for the tensor.
-   `.backward()` computes gradients; it does not itself update the
    weights.

------------------------------------------------------------------------

# Phase 0 --- Lesson 3: Neural Network Basics

## 1. Weights and biases

A simple neuron can calculate:

\[ y=wx+b \]

where:

-   (x): input
-   (w): weight, which controls the input's contribution
-   (b): bias, an additional learned value
-   (y): output

Example: if (x=3), (w=2), and (b=1), then:

\[ y=(2)(3)+1=7 \]

Weights and biases are trainable parameters in a neural network.

## 2. ReLU activation

ReLU (Rectified Linear Unit) is defined as:

\[ `\operatorname{ReLU}`{=tex}(x)=`\max`{=tex}(0,x) \]

Examples:

-   ReLU(-5) = 0
-   ReLU(0) = 0
-   ReLU(6) = 6

ReLU introduces nonlinearity, allowing a network to model more complex
relationships than a stack of linear transformations alone.

## 3. Loss function

A loss function measures how far a model's predictions are from target
values. The training process aims to reduce the chosen loss.

For regression, mean squared error (MSE) is a common choice:

\[
`\operatorname{MSE}`{=tex}=`\frac{1}{N}`{=tex}`\sum`{=tex}\_{i=1}\^{N}(`\hat{y}`{=tex}\_i-y_i)\^2
\]

Here, (`\hat{y}`{=tex}\_i) is a prediction and (y_i) is the target.

## 4. Backpropagation and optimization

A typical training step uses three important operations:

``` python
optimizer.zero_grad()
loss.backward()
optimizer.step()
```

-   `optimizer.zero_grad()` clears gradients left from the previous
    iteration. It does **not** reset model weights or biases.
-   `loss.backward()` computes gradients of the loss with respect to
    trainable parameters.
-   `optimizer.step()` uses the gradients and optimizer settings to
    update the parameters.

PyTorch accumulates gradients by default. Clearing them before the next
backward pass prevents gradients from earlier iterations from
accidentally accumulating into the current update.

## 5. Gradient descent intuition

A basic gradient-descent update is:

\[
`\theta`{=tex}*{`\text{new}`{=tex}}=`\theta`{=tex}*{`\text{old}`{=tex}}-`\eta `{=tex}`\frac{\partial L}{\partial \theta}`{=tex}
\]

where:

-   (`\theta`{=tex}): a parameter, such as a weight
-   (`\eta`{=tex}): learning rate
-   (L): loss
-   (`\frac{\partial L}{\partial \theta}`{=tex}): gradient

Examples:

-   If (w=5), learning rate (=0.1), and gradient (=-4), then
    (w\_{`\text{new}`{=tex}}=5-0.1(-4)=5.4).
-   If (w=5), learning rate (=0.1), and gradient (=+4), then
    (w\_{`\text{new}`{=tex}}=5-0.1(4)=4.6).
-   If (w=2), learning rate (=0.5), and gradient (=-2), then
    (w\_{`\text{new}`{=tex}}=2-0.5(-2)=3).
-   If (w=4), learning rate (=0.1), and gradient (=+5), then
    (w\_{`\text{new}`{=tex}}=4-0.1(5)=3.5).

A negative gradient increases the parameter in this simple update; a
positive gradient decreases it. Gradient descent does **not** always
increase weights.

## 6. Practical example: calculate a loss and gradients

``` python
import torch

x = torch.tensor(2.0)
w = torch.tensor(3.0, requires_grad=True)
b = torch.tensor(1.0, requires_grad=True)

y = w * x + b
activated = torch.relu(y)
target = torch.tensor(10.0)
loss = (activated - target) ** 2

loss.backward()

print("Linear output:", y.item())
print("Activated output:", activated.item())
print("Loss:", loss.item())
print("Weight gradient:", w.grad.item())
print("Bias gradient:", b.grad.item())
```

Reported output:

``` text
Linear output: 7
Activated output: 7
Loss: 9
Weight gradient: -12
Bias gradient: -6
```

Explanation:

-   (y=3(2)+1=7)
-   ReLU(7) = 7
-   Loss (=(7-10)\^2=9)
-   The derivative of squared error with respect to the output is
    (2(7-10)=-6).
-   The weight gradient is (-6 `\times `{=tex}x=-6
    `\times 2`{=tex}=-12).
-   The bias gradient is (-6).

### Lesson 3 checkpoint --- key answers

-   Weights and biases transform inputs.
-   ReLU(-5) = 0.
-   A loss function measures prediction error; an optimizer uses
    gradients to update parameters in an attempt to reduce loss.
-   Backpropagation computes gradients of the loss with respect to
    parameters.
-   Gradient descent subtracts the learning-rate-scaled gradient from a
    parameter.

------------------------------------------------------------------------

# Phase 0 --- Lesson 4: Train Your First Neural Network

## Goal

Train a simple linear model to learn the relationship:

\[ y=2x+1 \]

This exercise introduces the complete training loop before using hidden
layers.

## Complete code

``` python
import torch
import torch.nn as nn

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

X = torch.tensor(
    [[1.0], [2.0], [3.0], [4.0]],
    dtype=torch.float32,
    device=device
)
y = torch.tensor(
    [[3.0], [5.0], [7.0], [9.0]],
    dtype=torch.float32,
    device=device
)

model = nn.Linear(1, 1).to(device)
criterion = nn.MSELoss()
optimizer = torch.optim.SGD(model.parameters(), lr=0.01)

for epoch in range(500):
    predictions = model(X)
    loss = criterion(predictions, y)

    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

    if (epoch + 1) % 100 == 0:
        print(f"Epoch {epoch + 1}, Loss: {loss.item():.6f}")

print("Learned weight:", model.weight.item())
print("Learned bias:", model.bias.item())

model.eval()
with torch.no_grad():
    test_input = torch.tensor([[5.0]], dtype=torch.float32, device=device)
    prediction = model(test_input)

print("Prediction for x=5:", prediction.item())
```

## Reported results

``` text
Epoch 100, Loss: 0.000340
Epoch 200, Loss: 0.000187
Epoch 300, Loss: 0.000103
Epoch 400, Loss: 0.000056
Epoch 500, Loss: 0.000031

Learned weight: 2.0046136379241943
Learned bias: 0.9864357113838196
Prediction for x=5: 11.009504318237305
```

The learned parameters are close to the target relationship's parameters
(weight 2, bias 1). The prediction is close to 11.

## Important model-training concepts

-   `nn.Linear(1, 1)` creates a linear layer with one input feature and
    one output feature.
-   `criterion` calculates the loss.
-   `optimizer` controls parameter updates.
-   `model.eval()` switches the model to evaluation mode.
-   `torch.no_grad()` disables gradient tracking during inference.

For this simple model, the loss decreased from 0.000340 at epoch 100 to
0.000031 at epoch 500.

## Lesson 4 checkpoint

**Q1. Why call `optimizer.zero_grad()` before `loss.backward()`?**

Because PyTorch accumulates gradients by default. Clearing old gradients
prevents them from carrying into the current backward pass.

**Q2. Does a small training loss prove good performance on unseen
data?**

No. The model could fit or memorize training examples without
generalizing well. Separate validation or test data is needed to
evaluate performance on unseen examples.

------------------------------------------------------------------------

# Phase 0 --- Lesson 5: Hidden Layers and Nonlinear Neural Networks

## 1. What is a hidden layer?

A hidden layer is an intermediate layer between the input and output. It
learns internal representations that can help the network make
predictions.

For PlantHealth AI, useful representations may help distinguish patterns
such as leaf color changes, spots, textures, and irregular edges. In a
CNN, earlier layers often learn simpler visual patterns, while deeper
layers can learn more complex patterns.

A simple network can be pictured as:

**Input → Hidden layer → Output**

## 2. Why do we need nonlinear activation functions?

Consider two linear transformations:

\[ h=W_1x+b_1 \]

\[ y=W_2h+b_2 \]

Without an activation between them, their composition is still an affine
transformation. Stacking linear layers alone does not provide the
expressive power of a nonlinear network.

With ReLU:

\[ h=`\operatorname{ReLU}`{=tex}(W_1x+b_1) \]

the network can learn more complex, nonlinear relationships.

## 3. Parameters vs. representations

Consider:

\[ h=`\operatorname{ReLU}`{=tex}(Wx+b) \]

-   (W): trainable weight matrix
-   (b): trainable bias
-   (x): input
-   (h): computed hidden representation after applying ReLU

**Parameters** are the weights and biases learned during training.
**Representations/features** are the intermediate values computed using
those parameters and the input.

A network learns parameters that help it produce useful representations.

## 4. Practical example: a two-layer network

``` python
import torch
import torch.nn as nn

class SimpleNeuralNetwork(nn.Module):
    def __init__(self):
        super().__init__()

        self.hidden = nn.Linear(3, 4)
        self.relu = nn.ReLU()
        self.output = nn.Linear(4, 2)

    def forward(self, x):
        x = self.hidden(x)
        x = self.relu(x)
        x = self.output(x)
        return x

model = SimpleNeuralNetwork()

sample_input = torch.tensor([[1.0, 2.0, 3.0]])
prediction = model(sample_input)

print("Input shape:", sample_input.shape)
print("Prediction shape:", prediction.shape)
print("Prediction:", prediction)

for name, parameter in model.named_parameters():
    print(name, parameter.shape)
```

## 5. Reported output

``` text
Input shape: torch.Size([1, 3])
Prediction shape: torch.Size([1, 2])
Prediction: tensor([[ 0.4564, -0.3400]], grad_fn=<AddmmBackward0>)
hidden.weight torch.Size([4, 3])
hidden.bias torch.Size([4])
output.weight torch.Size([2, 4])
output.bias torch.Size([2])
```

The exact prediction values can vary because the model's parameters are
randomly initialized. This model has not been trained in this example.

### Interpreting the dimensions

The input is `[[1.0, 2.0, 3.0]]`, which has shape `(1, 3)`:

-   `1`: batch size --- one sample
-   `3`: features per sample

The hidden layer is `nn.Linear(3, 4)`:

-   It receives 3 input features.
-   It produces 4 hidden values.
-   Its weight shape is `(4, 3)`.
-   Its bias shape is `(4,)`.

The output layer is `nn.Linear(4, 2)`:

-   It receives 4 hidden values.
-   It produces 2 output values.
-   Its weight shape is `(2, 4)`.
-   Its bias shape is `(2,)`.

For PyTorch's `nn.Linear(in_features, out_features)`:

  Parameter   Shape
  ----------- -------------------------------
  `weight`    `(out_features, in_features)`
  `bias`      `(out_features,)`

**Memory aid:** rows correspond to output neurons; columns correspond to
input features.

Examples:

-   `nn.Linear(3, 4)` → weight `(4, 3)`, bias `(4,)`
-   `nn.Linear(5, 3)` → weight `(3, 5)`, bias `(3,)`
-   `nn.Linear(6, 4)` → weight `(4, 6)`, bias `(4,)`

Each output neuron has one weight per input feature and one bias.

### Why use ReLU between layers?

If a hidden layer produces `[-2, 3, -1, 5]`, ReLU produces
`[0, 3, 0, 5]`.

ReLU introduces nonlinearity. In our example it is placed after the
hidden layer, not after the final output layer.

### Lesson 5 checkpoint --- key answers

1.  A hidden layer learns intermediate representations/features from the
    input using trainable parameters.
2.  Stacked linear layers without nonlinear activations are equivalent
    to a single affine transformation.
3.  ReLU(-4) = 0, ReLU(0) = 0, ReLU(6) = 6.
4.  In (h=`\operatorname{ReLU}`{=tex}(Wx+b)), (W) and (b) are trainable
    parameters; (h) is the computed hidden representation.
5.  ReLU introduces nonlinearity so the network can model more complex
    patterns.

------------------------------------------------------------------------

# Phase 0 --- Lesson 6: Training a Nonlinear Neural Network

## Goal

Train a network with a hidden layer and ReLU to learn the simple
relationship:

\[ y=2x+1 \]

The dataset is:

    Input (x)   Target (y)
  ----------- ------------
            1            3
            2            5
            3            7
            4            9

The model architecture:

-   Input: 1 feature
-   Hidden layer: 4 neurons
-   Activation: ReLU
-   Output: 1 prediction

## Complete training code

``` python
import torch
import torch.nn as nn

# 1. Create the dataset
X = torch.tensor([[1.0], [2.0], [3.0], [4.0]])
y = torch.tensor([[3.0], [5.0], [7.0], [9.0]])

# 2. Define the nonlinear neural network
class NonlinearNetwork(nn.Module):
    def __init__(self):
        super().__init__()
        self.hidden = nn.Linear(1, 4)
        self.relu = nn.ReLU()
        self.output = nn.Linear(4, 1)

    def forward(self, x):
        x = self.hidden(x)
        x = self.relu(x)
        x = self.output(x)
        return x

# 3. Initialize the model, loss, and optimizer
model = NonlinearNetwork()
criterion = nn.MSELoss()
optimizer = torch.optim.SGD(model.parameters(), lr=0.01)

# 4. Train the model
for epoch in range(1000):
    predictions = model(X)
    loss = criterion(predictions, y)

    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

    if (epoch + 1) % 200 == 0:
        print(f"Epoch {epoch + 1}, Loss: {loss.item():.6f}")

# 5. Test the trained model
model.eval()

with torch.no_grad():
    test_input = torch.tensor([[5.0]])
    prediction = model(test_input)

print("Prediction for x=5:", prediction.item())
```

## Reported results

``` text
Epoch 200, Loss: 0.000454
Epoch 400, Loss: 0.000018
Epoch 600, Loss: 0.000001
Epoch 800, Loss: 0.000000
Epoch 1000, Loss: 0.000000
Prediction for x=5: 11.000057220458984
```

## 1. Does the training appear to work?

Yes. The reported loss decreases consistently, and the prediction for
(x=5) is very close to the target (11).

Absolute prediction error:

\[ \|11.00005722-11\|`\approx0.00005722`{=tex} \]

This is an extremely small error for the exercise.

## 2. Why does the loss print as `0.000000`?

The code uses:

``` python
print(f"Epoch {epoch + 1}, Loss: {loss.item():.6f}")
```

The `.6f` formatting displays six digits after the decimal point. A tiny
positive loss can round to `0.000000`; this does not prove that the true
loss is exactly zero.

For more printed precision, use:

``` python
print(f"Loss: {loss.item():.10f}")
```

## 3. Training performance vs. generalization

A decreasing training loss means the model is fitting its training
examples better. It does not, by itself, prove that the model performs
well on unseen data.

**Overfitting** occurs when a model fits the training data well but does
not generalize well to new examples. Learning training examples is not
automatically bad; the aim is to learn patterns that transfer to unseen
data.

For PlantHealth AI, we will need separate data splits:

-   **Training set:** Used to learn model parameters.
-   **Validation set:** Used to compare models and tune choices during
    development.
-   **Test set:** Used for final evaluation on data not used for
    training or model selection.

A good numerical prediction on this toy dataset does not establish that
a model can recognize diseases in plant images.

### Lesson 6 checkpoint --- answers

1.  `nn.MSELoss()` calculates the mean of the squared differences
    between predictions and targets.
2.  `optimizer.step()` uses the computed gradients and optimizer
    settings to update trainable parameters.
3.  Decreasing training loss alone does not prove generalization.
4.  A printed loss of `0.000000` may be a small nonzero value rounded to
    six decimal places.
5.  A prediction close to 11 on this toy task does not prove that the
    model will classify unseen plant images correctly.

------------------------------------------------------------------------

# Revision Summary

## Core concepts to remember

  -----------------------------------------------------------------------
  Concept                             Meaning
  ----------------------------------- -----------------------------------
  Tensor                              PyTorch's basic data structure for
                                      numerical data

  Shape                               Size of the tensor along each
                                      dimension

  Dtype                               Kind/precision of values stored in
                                      a tensor

  Device                              Where a tensor/model runs, such as
                                      CPU or CUDA

  Weight                              Trainable parameter controlling an
                                      input's contribution

  Bias                                Trainable offset added by a layer

  Activation                          Transformation such as ReLU that
                                      can introduce nonlinearity

  Forward pass                        Compute predictions from inputs

  Loss                                Measure prediction error against
                                      targets

  Backpropagation                     Compute gradients of loss with
                                      respect to parameters

  Optimizer                           Uses gradients to update trainable
                                      parameters

  Epoch                               One complete pass through the
                                      training dataset

  Overfitting                         Good fit to training data but poor
                                      generalization

  Generalization                      Performance on new, unseen examples
  -----------------------------------------------------------------------

## The standard training-loop pattern

``` python
for epoch in range(num_epochs):
    predictions = model(X)        # Forward pass
    loss = criterion(predictions, y)  # Calculate loss

    optimizer.zero_grad()          # Clear old gradients
    loss.backward()                # Calculate gradients
    optimizer.step()                # Update parameters
```

For inference:

``` python
model.eval()

with torch.no_grad():
    predictions = model(new_inputs)
```

## Progress checklist

-   [x] Lesson 1 --- Tensor fundamentals
-   [x] Lesson 2 --- Dtypes, devices, and autograd
-   [x] Lesson 3 --- Weights, biases, ReLU, loss, gradients, and
    gradient descent
-   [x] Lesson 4 --- Train a first linear neural network
-   [x] Lesson 5 --- Hidden layers, nonlinearities, and tensor
    dimensions
-   [x] Lesson 6 --- Train a nonlinear neural network and understand
    generalization
-   [ ] Phase 1 --- CNN fundamentals and image tensors (not started)

## Before continuing

You have completed the Phase 0 concepts covered in this notebook. The
next planned lesson is **Phase 1, Lesson 1: How images are represented
as tensors and why CNNs are useful**.

Keep this notebook as your revision reference. When debugging future
models, always inspect tensor shapes, verify the loss/gradient/update
sequence, and evaluate generalization rather than relying only on
training loss.
