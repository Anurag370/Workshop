# Chapter 8: Model Evaluation

## 1. Why Model Evaluation Matters: Generalization vs. Memorization

Training a machine learning model is only half the battle; **Model Evaluation** determines whether your model has learned true underlying patterns (**generalization**) or simply memorized the training set (**overfitting**).

* **Training Error (In-Sample Error):** Performance measured on the exact data used to fit the model parameters $\theta$. This is overly optimistic and **never** reflects real-world performance.
* **Generalization Error (Out-of-Sample Error):** Expected performance on unseen data drawn from the same underlying distribution.

### The Three-Way Split Roles

$$\text{Full Dataset} \longrightarrow \begin{cases} \text{Training Set } (60\%\text{--}80\%): & \text{Fits model parameters } \theta \\ \text{Validation Set } (10\%\text{--}20\%): & \text{Tunes hyperparameters \& selects architecture} \\ \text{Test Set } (10\%\text{--}20\%): & \text{Final, untouched report of generalization error} \end{cases}$$

---

## 2. Cross-Validation Strategies

Relying on a single validation split can be noisy if the dataset is small or if an easy/hard subset lands in the validation split by chance. **Cross-Validation (CV)** averages performance across multiple folds.

| CV Strategy | `scikit-learn` Class | How It Works & When to Use |
| :--- | :--- | :--- |
| **$k$-Fold CV** | `KFold(n_splits=5)` | Splits data into $k$ equal folds; trains on $k-1$ folds and validates on $1$ fold, repeating $k$ times. Standard for balanced regression. |
| **Stratified $k$-Fold** | `StratifiedKFold(n_splits=5)` | Preserves the exact class ratio in every fold. **Mandatory for classification**, especially with imbalanced classes. |
| **Time-Series Split** | `TimeSeriesSplit(n_splits=5)` | Uses expanding training windows where validation data always comes *chronologically after* training data. Prevents **look-ahead bias** in temporal data. |
| **Group $k$-Fold** | `GroupKFold(n_splits=5)` | Ensures all rows belonging to the same group (e.g., `patient_id`, `user_id`) stay in the same fold so the model isn't tested on patients it trained on. |
| **Leave-One-Out (LOOCV)** | `LeaveOneOut()` | Extreme case where $k = N$. Used only for very small datasets ($N < 100$) due to high computational cost. |

---

## 3. Classification Evaluation Metrics

### 3.1 The Confusion Matrix & Type I / Type II Errors
For binary classification (Positive $= 1$, Negative $= 0$):

| | **Predicted Positive ($\hat{y} = 1$)** | **Predicted Negative ($\hat{y} = 0$)** |
| :--- | :--- | :--- |
| **Actual Positive ($y = 1$)** | **True Positive ($\text{TP}$)** | **False Negative ($\text{FN}$)** *(Type II Error)* |
| **Actual Negative ($y = 0$)** | **False Positive ($\text{FP}$)** *(Type I Error)* | **True Negative ($\text{TN}$)** |

### 3.2 Threshold-Dependent Metrics
1. **Accuracy:**
   $$\text{Accuracy} = \frac{\text{TP} + \text{TN}}{\text{TP} + \text{TN} + \text{FP} + \text{FN}}$$
   * *The Accuracy Paradox:* If $99\%$ of credit card transactions are legitimate and $1\%$ are fraud, a dummy model that predicts "Legitimate" every time achieves $99\%$ accuracy while catching $0\%$ of fraud!
2. **Balanced Accuracy:** Average of recall obtained on each class; ideal for imbalanced datasets:
   $$\text{Balanced Accuracy} = \frac{1}{2}\left(\frac{\text{TP}}{\text{TP} + \text{FN}} + \frac{\text{TN}}{\text{TN} + \text{FP}}\right)$$
3. **Precision (Positive Predictive Value):** *"When the model predicts Positive, how often is it right?"*
   $$\text{Precision} = \frac{\text{TP}}{\text{TP} + \text{FP}}$$
   * Prioritize **Precision** when **False Positives ($\text{FP}$) are costly** (e.g., spam filters blocking important emails, or recommending risky surgeries).
4. **Recall (Sensitivity / True Positive Rate):** *"Out of all actual Positives, what fraction did the model catch?"*
   $$\text{Recall (TPR)} = \frac{\text{TP}}{\text{TP} + \text{FN}}$$
   * Prioritize **Recall** when **False Negatives ($\text{FN}$) are costly** (e.g., cancer screening, fraud detection, manufacturing defect detection).
5. **General $F_\beta$-Score and $F_1$-Score:**
   $$F_\beta = (1 + \beta^2) \cdot \frac{\text{Precision} \cdot \text{Recall}}{(\beta^2 \cdot \text{Precision}) + \text{Recall}}, \qquad F_1 = 2 \cdot \frac{\text{Precision} \cdot \text{Recall}}{\text{Precision} + \text{Recall}}$$
   * Use $\beta = 1$ ($F_1$) to weight Precision and Recall equally.
   * Use $\beta = 2$ ($F_2$) to weight **Recall** twice as much as Precision.
   * Use $\beta = 0.5$ ($F_{0.5}$) to weight **Precision** twice as much as Recall.

### 3.3 Multi-Class Averaging (`macro` vs. `weighted` vs. `micro`)
When evaluating $C > 2$ classes, `scikit-learn` aggregates per-class Precision, Recall, and $F_1$ using three strategies:
* **`macro`:** Unweighted mean across all $C$ classes. Treats a tiny minority class equally to a huge majority class.
* **`weighted`:** Mean weighted by the number of true instances (**support**) in each class.
* **`micro`:** Sums global $\text{TP}, \text{FP}, \text{FN}$ across all classes before computing the ratio (equals overall accuracy in single-label multi-class tasks).

### 3.4 Threshold-Independent Curves: ROC-AUC vs. PR-AUC
Classifiers output a continuous probability $\hat{p} = P(y=1 \mid x) \in [0, 1]$. By varying the decision threshold $\tau \in [0, 1]$ (default $\tau = 0.5$), we trade off Precision and Recall:
* **ROC-AUC (Receiver Operating Characteristic Area Under Curve):** Plots $\text{TPR}$ (Recall) vs. $\text{FPR} = \frac{\text{FP}}{\text{FP} + \text{TN}}$ across all thresholds.
  * $\text{AUC} = 1.0$: Perfect separator.
  * $\text{AUC} = 0.5$: Random guessing.
* **PR-AUC (Precision-Recall AUC / Average Precision):** Plots Precision vs. Recall across all thresholds.
  * **Rule of Thumb:** Use **ROC-AUC** when classes are roughly balanced; use **PR-AUC** when the positive class is rare/heavily imbalanced (because huge $\text{TN}$ counts make $\text{FPR}$ look artificially small on ROC curves).

### 3.5 Probabilistic & Calibration Metrics
* **Log-Loss (Binary Cross-Entropy):** Penalizes confident wrong probability predictions heavily:
  $$\text{Log-Loss} = -\frac{1}{N} \sum_{i=1}^{N} \left[ y_i \log(\hat{p}_i) + (1 - y_i) \log(1 - \hat{p}_i) \right]$$

---

## 4. Regression Evaluation Metrics

Given true continuous targets $y_i \in \mathbb{R}$ and predictions $\hat{y}_i \in \mathbb{R}$ across $N$ samples with $d$ features:

| Metric | Mathematical Formula | Key Characteristics & When to Use |
| :--- | :--- | :--- |
| **MAE** (Mean Absolute Error) | $$\frac{1}{N} \sum_{i=1}^{N} |y_i - \hat{y}_i|$$ | Linear penalty; expressed in the same units as $y$; **robust to outliers**. |
| **MSE** (Mean Squared Error) | $$\frac{1}{N} \sum_{i=1}^{N} (y_i - \hat{y}_i)^2$$ | Quadratic penalty; heavily penalizes large outlier errors; differentiable everywhere. |
| **RMSE** (Root Mean Squared Error) | $$\sqrt{\frac{1}{N} \sum_{i=1}^{N} (y_i - \hat{y}_i)^2}$$ | Same units as $y$, while still penalizing large errors more than MAE ($\text{RMSE} \ge \text{MAE}$). |
| **RMSLE** (Root Mean Squared Log Error) | $$\sqrt{\frac{1}{N} \sum_{i=1}^{N} \left(\log(1 + y_i) - \log(1 + \hat{y}_i)\right)^2}$$ | Cares about **relative percentage error** rather than raw magnitude; penalizes under-predictions more than over-predictions. |
| **$R^2$** (Coefficient of Determination) | $$1 - \frac{\sum_{i=1}^{N} (y_i - \hat{y}_i)^2}{\sum_{i=1}^{N} (y_i - \bar{y})^2}$$ | Proportion of variance explained ($1.0 =$ perfect, $0.0 =$ predicting $\bar{y}$, $< 0 =$ worse than predicting the mean). |
| **Adjusted $R^2$** | $$1 - \frac{(1 - R^2)(N - 1)}{N - d - 1}$$ | Penalizes adding useless features $d$ that do not genuinely improve the model. |

### Residual Diagnostics
In regression, always plot the **Residuals** $e_i = y_i - \hat{y}_i$ against the predicted values $\hat{y}_i$:
* A healthy model shows a **random cloud of points centered around $e = 0$** with constant spread (**homoscedasticity**).
* A U-shaped curve indicates missed non-linear patterns; a funnel shape indicates **heteroscedasticity** (error variance grows with target size, often fixed via a $\log(y)$ transformation).

---

## 5. Diagnosing Bias & Variance with Learning Curves

1. **Learning Curve (Score vs. Number of Training Samples $N$):**
   * If training and validation scores converge at a **low score**, the model has **High Bias (Underfitting)** $\rightarrow$ adding more data won't help; increase model complexity or engineer better features.
   * If training score is high ($99\%$) and validation score is much lower ($78\%$) with a wide gap, the model has **High Variance (Overfitting)** $\rightarrow$ adding more training samples or increasing regularization will close the gap.
2. **Validation Curve (Score vs. Hyperparameter Value, e.g., `max_depth` or $C$):**
   * Visualizes the exact sweet spot where validation performance peaks before the model starts overfitting.

---

## 6. Complete `scikit-learn` Model Evaluation & Threshold Tuning Workflow

```python
import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification
from sklearn.model_selection import (
    train_test_split,
    StratifiedKFold,
    cross_validate,
    LearningCurveDisplay
)
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import (
    classification_report,
    confusion_matrix,
    roc_auc_score,
    average_precision_score,
    precision_recall_curve,
    f1_score
)

# 1. Create an imbalanced binary classification dataset (90% class 0, 10% class 1)
X, y = make_classification(
    n_samples=2000, n_features=15, n_informative=8,
    weights=[0.90, 0.10], random_state=42
)

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, stratify=y, random_state=42
)

model = RandomForestClassifier(n_estimators=150, class_weight="balanced", random_state=42)

# 2. Multi-Metric Stratified Cross-Validation on Training Set
cv = StratifiedKFold(n_splits=5, shuffle=True, random_state=42)
scoring = ["accuracy", "balanced_accuracy", "f1", "roc_auc", "average_precision"]

cv_results = cross_validate(
    model, X_train, y_train, cv=cv, scoring=scoring, return_train_score=True
)

print("=== 5-Fold Cross-Validation Summary ===")
for metric in scoring:
    mean_val = np.mean(cv_results[f"test_{metric}"])
    std_val = np.std(cv_results[f"test_{metric}"])
    print(f"{metric:20s}: {mean_val:.4f} (+/- {std_val:.4f})")

# 3. Fit on Training Set & Evaluate Probabilities on Unseen Test Set
model.fit(X_train, y_train)
y_probs = model.predict_proba(X_test)[:, 1]  # Probabilities for positive class (1)

print(f"\nTest ROC-AUC: {roc_auc_score(y_test, y_probs):.4f}")
print(f"Test PR-AUC:  {average_precision_score(y_test, y_probs):.4f}")

# 4. Decision Threshold Tuning (Optimizing F1-Score instead of default 0.50 threshold)
precisions, recalls, thresholds = precision_recall_curve(y_test, y_probs)
# Compute F1 at each threshold (adding 1e-9 to avoid division by zero)
f1_scores = (2 * precisions[:-1] * recalls[:-1]) / (precisions[:-1] + recalls[:-1] + 1e-9)

best_idx = np.argmax(f1_scores)
best_threshold = thresholds[best_idx]
y_pred_Default = (y_probs >= 0.50).astype(int)
y_pred_Tuned = (y_probs >= best_threshold).astype(int)

print(f"\nDefault Threshold (0.50) F1-Score: {f1_score(y_test, y_pred_Default):.4f}")
print(f"Optimal Threshold ({best_threshold:.2f}) F1-Score: {f1_score(y_test, y_pred_Tuned):.4f}")
print("\nConfusion Matrix (Tuned Threshold):\n", confusion_matrix(y_test, y_pred_Tuned))
print("\nClassification Report (Tuned Threshold):\n", classification_report(y_test, y_pred_Tuned))

# 5. Plot Learning Curve to Diagnose Bias vs. Variance
fig, ax = plt.subplots(figsize=(7, 4))
LearningCurveDisplay.from_estimator(
    model, X_train, y_train, cv=cv, scoring="f1", ax=ax, n_jobs=-1
)
ax.set_title("Learning Curve (F1-Score vs. Training Samples)")
plt.tight_layout()
plt.show()
```