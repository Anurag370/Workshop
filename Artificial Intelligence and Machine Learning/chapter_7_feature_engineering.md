# Chapter 7: Feature Engineering

## 1. What is Feature Engineering & The Golden Rule of Data Leakage

**Feature Engineering** is the process of transforming raw data into informative numerical representations that make underlying patterns easier for machine learning algorithms to learn.

### The Golden Rule: Prevent Data Leakage!
**Data Leakage** occurs when information from the validation or test set leaks into the training process (e.g., computing the global mean/standard deviation across the entire dataset *before* splitting into train and test).
* **Always split your data into `X_train` and `X_test` FIRST.**
* Call `.fit_transform(X_train)` **only** on the training set (learns parameters like $\mu, \sigma$, or category mappings).
* Call `.transform(X_test)` on the test set (applies the training parameters without peeking at test statistics).

---

## 2. Feature Scaling and Normalization

Distance-based and gradient-based algorithms (Linear/Logistic Regression, SVM, $k$-NN, $K$-Means, PCA, Neural Networks) are sensitive to feature scales. Tree-based models (Decision Trees, Random Forests, XGBoost) are scale-invariant.

| Scaler | Mathematical Formula | Properties & When to Use |
| :--- | :--- | :--- |
| **`StandardScaler`** (Z-score Standardization) | $$z = \frac{x - \mu}{\sigma}$$ | Centers mean at $0$ and standard deviation at $1$. Default choice for linear models, SVMs, PCA, and neural networks. |
| **`MinMaxScaler`** (Min-Max Normalization) | $$x_{\text{scaled}} = \frac{x - x_{\min}}{x_{\max} - x_{\min}}$$ | Squeezes all values into $[0, 1]$. Useful for image pixel intensities or bounded inputs, but **sensitive to outliers**. |
| **`RobustScaler`** | $$x_{\text{robust}} = \frac{x - \text{Median}}{\text{IQR}}$$ | Uses median and Interquartile Range ($Q_3 - Q_1$). **Best choice when numerical features contain extreme outliers.** |

---

## 3. Encoding Categorical Variables

Machine learning models require numerical tensors. How you encode a categorical feature depends on whether it is **Ordinal** or **Nominal** and its **cardinality** (number of unique categories):

### 3.1 Ordinal Encoding (`OrdinalEncoder`)
Maps ordered categories to integers preserving rank (e.g., $\text{Low} \rightarrow 0, \text{Medium} \rightarrow 1, \text{High} \rightarrow 2$).
* *Warning:* Never use arbitrary integer encoding on **nominal** categories (like `City`) in linear models, or the model will assume $\text{Kolkata} (2) > \text{Mumbai} (1) > \text{Delhi} (0)$.

### 3.2 One-Hot Encoding (`OneHotEncoder`)
Creates $C$ binary ($0/1$) indicator columns for $C$ nominal categories.
* **Handling Unseen Categories:** Set `handle_unknown="ignore"` so a brand-new category in the test set encodes as all zeros instead of crashing your pipeline.
* **The Dummy Variable Trap:** For unregularized linear models, drop one collinear column using `drop="first"` ($C-1$ columns) to avoid perfect multicollinearity.

### 3.3 Target Encoding (`TargetEncoder`)
For **high-cardinality nominal features** (e.g., `pin_code` or `user_id` with $5,000+$ unique values where One-Hot Encoding would explode dimensionality), replace each category with a smoothed blend of the category's mean target value and the global target mean (computed using out-of-fold cross-validation to prevent target leakage).

---

## 4. Mathematical Transforms, Binning & Domain Features

### 4.1 Handling Skewed Numerical Distributions
Heavy right-skewed variables (like house prices, transaction amounts, or follower counts) violate normality assumptions in linear models.
* **Log Transform:** Apply $x' = \log(1 + x)$ (`np.log1p(x)`) for non-negative skewed features.
* **Power Transforms (`PowerTransformer`):** Automatically finds the optimal power parameter $\lambda$ via **Box-Cox** (strictly positive data) or **Yeo-Johnson** (supports zero and negative values) to make the distribution Gaussian-like.

### 4.2 Polynomial & Interaction Features (`PolynomialFeatures`)
Allows linear models to capture non-linear curves and feature interactions. For two features $(x_1, x_2)$ with `degree=2`:

$$[x_1, x_2] \xrightarrow{\text{PolynomialFeatures(degree=2)}} [1, \; x_1, \; x_2, \; x_1^2, \; x_1 x_2, \; x_2^2]$$

### 4.3 Cyclical Time Features
Hours of the day ($0\text{–}23$) or months ($1\text{–}12$) are cyclical: hour $23$ is right next to hour $0$. Encode cyclical time with sine and cosine pairs so the model preserves circular distance:

$$x_{\sin} = \sin\left(\frac{2\pi \cdot t}{T}\right), \qquad x_{\cos} = \cos\left(\frac{2\pi \cdot t}{T}\right)$$

where $T = 24$ for hours or $T = 12$ for months.

---

## 5. Feature Selection Techniques

Removing redundant or noisy features speeds up training, reduces overfitting, and improves interpretability:

1. **Filter Methods (Model-Agnostic):**
   * **Variance Threshold (`VarianceThreshold`):** Drops constant or quasi-constant features with variance $\sigma^2 \approx 0$.
   * **Univariate Statistical Tests (`SelectKBest`):** Scores each feature independently against the target using `f_regression` (ANOVA $F$-value), `chi2`, or `mutual_info_classif`.
2. **Wrapper Methods:**
   * **Recursive Feature Elimination (`RFE`):** Repeatedly trains a model and prunes the weakest features until the desired number of features remains.
3. **Embedded Methods:**
   * **`SelectFromModel`:** Uses weights learned during training—such as **$L_1$ (Lasso) sparsity** or **Random Forest feature importances**—to discard low-importance features automatically.

---

## 6. Production Pipeline with `ColumnTransformer` and `Pipeline`

In real-world projects, combine imputation, scaling, encoding, feature selection, and modeling into a single `scikit-learn` **`Pipeline`** to guarantee zero data leakage during cross-validation and deployment:

```python
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline
from sklearn.impute import SimpleImputer
from sklearn.preprocessing import RobustScaler, OneHotEncoder
from sklearn.feature_selection import SelectFromModel
from sklearn.ensemble import RandomForestClassifier

# Sample mixed-type dataset
df = pd.DataFrame({
    "age": [25, 32, None, 45, 29, 51, 38, 22],
    "income": [45000, 72000, 61000, 120000, 54000, 950000, 68000, 39000],
    "city": ["Kolkata", "Mumbai", "Delhi", "Kolkata", None, "Mumbai", "Delhi", "Kolkata"],
    "plan": ["Basic", "Pro", "Pro", "Enterprise", "Basic", "Enterprise", "Pro", "Basic"],
    "churned": [1, 0, 0, 0, 1, 0, 0, 1]
})

X = df.drop(columns=["churned"])
y = df["churned"]

# 1. Split FIRST to prevent data leakage
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=42)

# 2. Define preprocessing sub-pipelines for numerical and categorical columns
numeric_features = ["age", "income"]
categorical_features = ["city", "plan"]

numeric_transformer = Pipeline(steps=[
    ("imputer", SimpleImputer(strategy="median")),
    ("scaler", RobustScaler())  # Robust against the 950,000 income outlier
])

categorical_transformer = Pipeline(steps=[
    ("imputer", SimpleImputer(strategy="most_frequent")),
    ("onehot", OneHotEncoder(handle_unknown="ignore", sparse_output=False))
])

# 3. Combine column transformers
preprocessor = ColumnTransformer(transformers=[
    ("num", numeric_transformer, numeric_features),
    ("cat", categorical_transformer, categorical_features)
])

# 4. Build full end-to-end Pipeline (Preprocessing -> Feature Selection -> Classifier)
clf_pipeline = Pipeline(steps=[
    ("preprocessor", preprocessor),
    ("feature_selection", SelectFromModel(RandomForestClassifier(n_estimators=50, random_state=42))),
    ("classifier", RandomForestClassifier(n_estimators=100, random_state=42))
])

# 5. Fit on training data ONLY, then predict on test data
clf_pipeline.fit(X_train, y_train)
predictions = clf_pipeline.predict(X_test)
print("Test Set Predictions:", predictions)
```