# Chapter 5: Supervised Learning

## 1. The Supervised Learning Paradigm

In **Supervised Learning**, we are given a labeled dataset of $N$ input-output pairs:

$$\mathcal{D} = \{(x_1, y_1), (x_2, y_2), \dots, (x_N, y_N)\}$$

where $x_i \in \mathbb{R}^d$ is a $d$-dimensional feature vector and $y_i$ is the ground-truth target (label). Our goal is to learn a mapping function $f_\theta: X \rightarrow Y$ parameterized by $\theta$ that minimizes a loss function $\mathcal{L}(y, \hat{y})$ and **generalizes** to unseen data.

* **Regression:** The target $y \in \mathbb{R}$ is continuous (e.g., predicting house price, temperature, or electricity load).
* **Classification:** The target $y \in \{0, 1, \dots, C-1\}$ is a discrete category (e.g., spam detection, disease diagnosis, customer churn).

---

## 2. Generalization, Cross-Validation & The Bias-Variance Tradeoff

### 2.1 Train / Validation / Test Splits & $k$-Fold Cross-Validation
Never evaluate a model on the same data used to train it!
* **Training Set:** Used to fit model parameters $\theta$.
* **Validation Set (or $k$-Fold Cross-Validation):** Used to tune hyperparameters and select the best model architecture. In **$k$-Fold CV**, the training set is partitioned into $k$ equal folds; the model trains on $k-1$ folds and validates on the held-out fold, cycling $k$ times.
* **Test Set:** Touched **only once** at the very end to report unbiased generalization performance.

### 2.2 The Bias-Variance Decomposition
The expected generalization error of a model decomposes into three terms:

$$\mathbb{E}\left[(y - \hat{f}(x))^2\right] = \text{Bias}^2 + \text{Variance} + \sigma_{\text{irreducible}}^2$$

| Condition | Bias | Variance | Symptom | Remedy |
| :--- | :--- | :--- | :--- | :--- |
| **Underfitting** | High | Low | High training error **and** high validation error. Model is too simple. | Add features, use a non-linear/more complex model, reduce regularization ($\lambda$). |
| **Overfitting** | Low | High | Very low training error, but **high validation error**. Model memorizes noise. | Get more training data, apply regularization ($L_1$/$L_2$), prune trees, reduce features. |

---

## 3. Regression Algorithms

### 3.1 Ordinary Least Squares (Linear Regression)
Models the target as a linear combination of input features:

$$\hat{y} = w^T x + b = \sum_{j=1}^{d} w_j x_j + b$$

Trained by minimizing the **Mean Squared Error (MSE)**:

$$\mathcal{L}_{\text{MSE}}(w, b) = \frac{1}{N} \sum_{i=1}^{N} (y_i - \hat{y}_i)^2$$

### 3.2 Regularized Linear Models (Ridge, Lasso, ElasticNet)
To prevent overfitting when features are numerous or collinear, we add a penalty term to the loss function:
* **Ridge Regression ($L_2$ Regularization):** Shrinks weights smoothly toward zero:
  $$\mathcal{L}_{\text{Ridge}} = \text{MSE} + \alpha \sum_{j=1}^{d} w_j^2$$
* **Lasso Regression ($L_1$ Regularization):** Drives irrelevant feature weights to **exact zero** ($w_j = 0$), performing automatic feature selection:
  $$\mathcal{L}_{\text{Lasso}} = \text{MSE} + \alpha \sum_{j=1}^{d} |w_j|$$

---

## 4. Classification Algorithms

| Algorithm | Core Mechanism | Strengths | Weaknesses / Requirements |
| :--- | :--- | :--- | :--- |
| **Logistic Regression** | Passes linear logit $z = w^T x + b$ through Sigmoid $\sigma(z) = \frac{1}{1 + e^{-z}}$ and minimizes Binary Cross-Entropy (Log-Loss). | Fast, interpretable probabilities, strong baseline. | Assumes a linear decision boundary; requires feature scaling. |
| **$k$-Nearest Neighbors ($k$-NN)** | Non-parametric; classifies a point by majority vote among its $k$ closest training points (e.g., Euclidean distance). | Simple, zero training time, handles non-linear boundaries. | Slow at inference on large datasets; **sensitive to feature scale** and curse of dimensionality. |
| **Support Vector Machines (SVM)** | Finds the hyperplane that maximizes the margin $\frac{2}{\|w\|}$ between classes; uses the **Kernel Trick** (RBF, Poly) for non-linear data. | Effective in high-dimensional spaces. | Requires feature scaling; slow when $N > 50,000$. |
| **Decision Trees (CART)** | Recursively splits features to minimize node impurity (**Gini Impurity** $1 - \sum p_c^2$ or **Entropy** $-\sum p_c \log_2 p_c$). | Interpretable, **no feature scaling required**, handles non-linear interactions. | Single unpruned trees severely overfit (high variance). |
| **Random Forest (Bagging)** | Trains an ensemble of decorrelated Decision Trees on bootstrap samples and random feature subsets, averaging predictions. | Resistant to overfitting, works well out-of-the-box. | Less interpretable than a single tree; larger model size. |
| **Gradient Boosting (`HistGradientBoosting`, `XGBoost`)** | Builds trees **sequentially**, where each new tree fits the residual errors (negative gradients) of the previous ensemble. | State-of-the-art accuracy on tabular datasets. | Can overfit if learning rate or tree count is not tuned. |

---

## 5. Evaluation Metrics

### 5.1 Regression Metrics
* **Mean Absolute Error (MAE):** $\frac{1}{N} \sum_{i=1}^N |y_i - \hat{y}_i|$ (robust to outliers, in target units).
* **Root Mean Squared Error (RMSE):** $\sqrt{\frac{1}{N} \sum_{i=1}^N (y_i - \hat{y}_i)^2}$ (penalizes large errors heavily).
* **Coefficient of Determination ($R^2$):** Proportion of variance explained by the model ($R^2 = 1$ is perfect; $R^2 = 0$ is no better than predicting the mean $\bar{y}$):
  $$R^2 = 1 - \frac{\sum_{i=1}^N (y_i - \hat{y}_i)^2}{\sum_{i=1}^N (y_i - \bar{y})^2}$$

### 5.2 Classification Metrics
From the Confusion Matrix (**TP**: True Positive, **TN**: True Negative, **FP**: False Positive, **FN**: False Negative):
* **Accuracy:** $\frac{\text{TP} + \text{TN}}{\text{TP} + \text{TN} + \text{FP} + \text{FN}}$ *(Misleading on imbalanced datasets!)*
* **Precision:** $\frac{\text{TP}}{\text{TP} + \text{FP}}$ — *"Out of all predicted positives, how many are truly positive?"* (Use when **FP** is costly, e.g., spam filter).
* **Recall (Sensitivity):** $\frac{\text{TP}}{\text{TP} + \text{FN}}$ — *"Out of all actual positives, how many did we catch?"* (Use when **FN** is costly, e.g., cancer screening or fraud detection).
* **$F_1$-Score:** Harmonic mean of Precision and Recall:
  $$F_1 = 2 \cdot \frac{\text{Precision} \cdot \text{Recall}}{\text{Precision} + \text{Recall}}$$
* **ROC-AUC:** Area under the Receiver Operating Characteristic curve (True Positive Rate vs. False Positive Rate across all probability thresholds).

---

## 6. Complete `scikit-learn` Supervised Learning Workflow

```python
from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report, roc_auc_score

# 1. Load dataset and create stratified Train/Test split
X, y = load_breast_cancer(return_X_y=True)
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, stratify=y, random_state=42
)

# 2. Hyperparameter Tuning with 5-Fold Cross-Validation
param_grid = {
    "n_estimators": [100, 200],
    "max_depth": [None, 5, 10],
    "min_samples_split": [2, 5]
}

grid_search = GridSearchCV(
    estimator=RandomForestClassifier(random_state=42),
    param_grid=param_grid,
    cv=5,
    scoring="roc_auc",
    n_jobs=-1
)
grid_search.fit(X_train, y_train)

# 3. Evaluate best model on the unseen Test Set
best_model = grid_search.best_estimator_
y_pred = best_model.predict(X_test)
y_prob = best_model.predict_proba(X_test)[:, 1]

print("Best Hyperparameters:", grid_search.best_params_)
print(f"Test ROC-AUC Score: {roc_auc_score(y_test, y_prob):.4f}")
print("\nClassification Report:\n", classification_report(y_test, y_pred))
```