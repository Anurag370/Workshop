---
title: "PyTorch Deep Learning Course — Guide"
course: "PyTorch for Deep Learning & Machine Learning"
instructor: "Daniel Bourke"
source: "https://www.youtube.com/watch?v=V_xro1bcAuA"
tags: [pytorch, deep-learning, machine-learning, obsidian]
---

# PyTorch for Deep Learning & Machine Learning — Course Guide

**Course video:** [Watch on YouTube](https://www.youtube.com/watch?v=V_xro1bcAuA)  
**Instructor:** Daniel Bourke  
**Companion materials:** [Course book](https://learnpytorch.io/) · [GitHub repository](https://github.com/mrdbourke/pytorch-deep-learning)

> **Source note:** These are structured learning notes aligned to the publicly listed chapter topics and timestamps, supplemented with standard PyTorch explanations and original examples. They are not a verified verbatim transcript. Check the linked video for instructor-specific details.

## Course map

1. [[01-pytorch-fundamentals|Chapter 0 — PyTorch Fundamentals]]
2. [[02-pytorch-workflow|Chapter 1 — PyTorch Workflow]]
3. [[03-neural-network-classification|Chapter 2 — Neural Network Classification]]
4. [[04-computer-vision-and-cnns|Chapter 3 — Computer Vision]]
5. [[05-custom-datasets|Chapter 4 — Custom Datasets]]

## Recommended study approach

- Watch a short section, then reproduce the code yourself.
- Predict tensor shapes and outputs before running a cell.
- Change one variable at a time and record what happens.
- Keep training, validation, and test data separate.
- Prefer understanding the training loop over copying a complete notebook.
- Commit working milestones to Git so you can compare experiments.

## Progress tracker

- [ ] [[01-pytorch-fundamentals|Fundamentals]]
- [ ] [[02-pytorch-workflow|Workflow]]
- [ ] [[03-neural-network-classification|Classification]]
- [ ] [[04-computer-vision-and-cnns|Computer vision and CNNs]]
- [ ] [[05-custom-datasets|Custom datasets]]

## PlantHealth AI learning path

Your practical destination is a custom CNN that classifies plant-leaf images. Suggested sequence:

1. Understand tensors, shapes, dtypes, and devices.
2. Train a small model on simple data and understand the training loop.
3. Learn classification logits, loss, probabilities, and evaluation.
4. Understand image tensors and convolutional layers.
5. Build a `Dataset` and `DataLoader` for labeled leaf images.
6. Train and evaluate a baseline CNN before trying transfer learning.

Do not jump to a large pretrained model before you can explain what your baseline's training and evaluation code does.
