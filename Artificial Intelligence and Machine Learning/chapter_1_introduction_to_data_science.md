# Chapter 1: Introduction to Data Science

## 1. What is Data Science?

**Data Science** is an interdisciplinary field that uses scientific methods, statistical algorithms, and software engineering systems to extract actionable insights and predictive patterns from structured and unstructured data.

### The Three Pillars of Data Science
1. **Mathematics & Statistics:** Probability theory, statistical inference, linear algebra, and calculus used to model uncertainty and optimize algorithms.
2. **Computer Science & Engineering:** Programming (Python, SQL), data structures, distributed computing, and software pipelines.
3. **Domain Expertise:** Business or scientific context required to frame the right questions, interpret results, and validate whether findings make real-world sense.

---

## 2. The Data Science Lifecycle (CRISP-DM & OSEMN)

Every end-to-end data science project follows an iterative lifecycle:

$$\text{Business Problem} \rightarrow \text{Data Collection} \rightarrow \text{Cleaning \& EDA} \rightarrow \text{Feature Engineering} \rightarrow \text{Modeling} \rightarrow \text{Evaluation} \rightarrow \text{Deployment}$$

| Stage | OSEMN Equivalent | Key Activities |
| :--- | :--- | :--- |
| **1. Problem Formulation** | — | Define business objectives, success metrics (KPIs), and machine learning framing. |
| **2. Data Acquisition** | **O**btain | Query SQL databases, call REST APIs, scrape web pages, or ingest sensor/log streams. |
| **3. Data Cleaning** | **S**crub | Handle missing values (`NaN`), remove duplicates, fix data types, and filter outliers. |
| **4. Exploratory Data Analysis (EDA)** | **E**xplore | Compute summary statistics and plot distributions/correlations to understand patterns. |
| **5. Modeling** | **M**odel | Engineer features, split data, and train/tune Supervised or Unsupervised ML models. |
| **6. Interpretation & Deployment** | i**N**terpret | Evaluate metrics on test data, communicate insights, and deploy models into production. |

---

## 3. Taxonomy of Data Types

Understanding the type of data you have dictates which statistical tests, visualizations, and machine learning preprocessing steps you must use.

### 3.1 Structured vs. Unstructured Data
* **Structured Data:** Tabular data organized in rows (observations/samples) and columns (features/attributes) with a strict schema (e.g., SQL tables, CSV files).
* **Semi-Structured Data:** Hierarchical or key-value data without a fixed relational table schema (e.g., JSON, XML, NoSQL documents).
* **Unstructured Data:** Raw data without a predefined tabular format (e.g., raw text, images, audio recordings, video).

### 3.2 Quantitative (Numerical) vs. Qualitative (Categorical)
1. **Quantitative (Numerical):**
   * **Continuous:** Can take any real value within an interval, $x \in \mathbb{R}$ (e.g., temperature, salary, height).
   * **Discrete:** Countable values, typically integers, $x \in \mathbb{Z}$ (e.g., number of customer logins, defect count).
2. **Qualitative (Categorical):**
   * **Nominal:** Categories with **no intrinsic ordering** (e.g., city name, blood type, payment method).
   * **Ordinal:** Categories with a **meaningful rank/order**, though distances between ranks may not be equal (e.g., education level: $\text{High School} < \text{B.Tech} < \text{M.Tech}$; customer rating: $\text{Low} < \text{Medium} < \text{High}$).

---

## 4. The Four Levels of Data Analytics

1. **Descriptive Analytics (*"What happened?"*):** Summarizing historical data using dashboards, aggregations, mean, and year-over-year growth.
2. **Diagnostic Analytics (*"Why did it happen?"*):** Drilling down into correlations, root-cause analysis, and anomaly investigation.
3. **Predictive Analytics (*"What is likely to happen next?"*):** Using machine learning and statistical forecasting to predict future outcomes (e.g., churn prediction, demand forecasting).
4. **Prescriptive Analytics (*"What action should we take?"*):** Using optimization, causal inference, and simulations to recommend optimal decisions.

---

## 5. Essential Statistical Foundations

Given a sample of $n$ observations $X = \{x_1, x_2, \dots, x_n\}$:

### 5.1 Measures of Central Tendency
* **Sample Mean ($\bar{x}$):** Sensitive to extreme outliers.
  $$\bar{x} = \frac{1}{n} \sum_{i=1}^{n} x_i$$
* **Median:** The middle value when sorted in ascending order. **Robust to outliers** (preferred for skewed distributions like income or house prices).
* **Mode:** The most frequently occurring value (used for categorical or discrete variables).

### 5.2 Measures of Dispersion (Spread)
* **Sample Variance ($s^2$):** Average squared deviation from the mean (uses $n - 1$ for Bessel's correction).
  $$s^2 = \frac{1}{n - 1} \sum_{i=1}^{n} (x_i - \bar{x})^2$$
* **Standard Deviation ($s$):** Square root of variance, expressed in the same units as the original data: $s = \sqrt{s^2}$.
* **Interquartile Range ($\text{IQR}$):** Spread of the middle $50\%$ of the data:
  $$\text{IQR} = Q_3 - Q_1$$
  where $Q_1$ is the $25\text{th}$ percentile and $Q_3$ is the $75\text{th}$ percentile.

### 5.3 Covariance and Pearson Correlation
* **Covariance ($\text{Cov}(X, Y)$):** Measures the direction of the linear relationship between two variables $X$ and $Y$:
  $$\text{Cov}(X, Y) = \frac{1}{n - 1} \sum_{i=1}^{n} (x_i - \bar{x})(y_i - \bar{y})$$
* **Pearson Correlation Coefficient ($r$):** Normalizes covariance into a unitless scale $r \in [-1, 1]$:
  $$r = \frac{\text{Cov}(X, Y)}{s_X s_Y}$$
  * $r \approx 1$: Strong positive linear relationship.
  * $r \approx -1$: Strong negative linear relationship.
  * $r \approx 0$: No linear relationship (note: *correlation does not imply causation*).

---

## 6. The Python Data Science Ecosystem

```python
import numpy as np
import pandas as pd

# Sample dataset of daily response times (in ms) with one extreme outlier
response_times = np.array([120, 125, 118, 130, 122, 119, 128, 950])

mean_val = np.mean(response_times)
median_val = np.median(response_times)
std_val = np.std(response_times, ddof=1)  # ddof=1 for sample standard deviation
q1, q3 = np.percentile(response_times, [25, 75])
iqr_val = q3 - q1

print(f"Mean (skewed by outlier): {mean_val:.2f} ms")
print(f"Median (robust):          {median_val:.2f} ms")
print(f"Sample Std Dev:           {std_val:.2f} ms")
print(f"IQR (Q3 - Q1):            {iqr_val:.2f} ms")
```

| Library | Core Role in Data Science |
| :--- | :--- |
| **`NumPy`** | High-performance $N$-dimensional arrays (`ndarray`), linear algebra, and vectorized math. |
| **`Pandas`** | Tabular data manipulation (`DataFrame`, `Series`), data cleaning, time series, and I/O. |
| **`Matplotlib` / `Seaborn`** | Data visualization, exploratory plotting, and publication-quality figures. |
| **`Scikit-Learn`** | Classical machine learning (Supervised, Unsupervised, Feature Engineering, Pipelines). |
| **`SciPy` / `Statsmodels`** | Scientific computing, probability distributions, and statistical hypothesis testing. |