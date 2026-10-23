# Chapter 3: Cleaning Data Using Pandas

## 1. Core Pandas Data Structures

**Pandas** is built on top of NumPy and provides labeled, tabular data structures designed for real-world heterogeneous data:
1. **`pd.Series` ($1\text{D}$):** A single column of data paired with an explicit **Index**.
2. **`pd.DataFrame` ($2\text{D}$):** A table of rows and columns where each column is a `Series` sharing a common row `Index`.

---

## 2. Loading and Auditing Raw Data

Whenever you load a dataset, run a standard diagnostic audit first to uncover missing values, wrong data types, or corrupted records:

```python
import pandas as pd
import numpy as np

# 1. Load data (supports CSV, Excel, Parquet, SQL, JSON)
# df = pd.read_csv("raw_sales.csv")

# Example dirty dataset for demonstration
raw_data = {
    "order_id": [101, 102, 102, 103, 104, 105],
    "customer": ["  alice ", "Bob", "Bob", "CHARLIE", "david", None],
    "amount": ["$250.00", "$180.50", "$180.50", "N/A", "$310.00", "$99999.00"],
    "order_date": ["2026-01-10", "2026-01-12", "2026-01-12", "2026-01-15", "invalid_date", "2026-01-20"],
    "category": ["Electronics", "Books", "Books", "Electronics", None, "Clothing"]
}
df = pd.DataFrame(raw_data)

# 2. The 5-Step Initial Data Audit
print(df.head(3))                 # Inspect first 3 rows
print(df.shape)                   # (rows, columns)
print(df.info())                  # Column names, non-null counts, and dtypes
print(df.describe(include="all")) # Summary stats for numerical and categorical columns
print(df.isna().sum())            # Count missing values per column
```

---

## 3. Indexing & Selection: `.loc[]` vs. `.iloc[]`

* **`.loc[row_labels, col_labels]`:** Selects data by **index/column labels** (inclusive of the stop bound!).
* **`.iloc[row_positions, col_positions]`:** Selects data by **integer positions** ($0$-indexed, exclusive of the stop bound, just like NumPy).

```python
# Label-based selection with .loc
subset_loc = df.loc[0:2, ["customer", "amount"]]

# Position-based selection with .iloc (first 3 rows, first 2 columns)
subset_iloc = df.iloc[0:3, 0:2]

# Boolean / Conditional Filtering
electronics_df = df.loc[df["category"] == "Electronics"]

# Filtering with .isin() and .query()
selected_cats = df[df["category"].isin(["Electronics", "Books"])]
```

---

## 4. Cleaning Strings, Data Types, and Duplicates

Raw datasets frequently store numbers as strings (due to currency symbols or text placeholders like `"N/A"`) and dates as plain `object` strings.

```python
# 1. Remove exact duplicate rows
print("Duplicates found:", df.duplicated().sum())
df = df.drop_duplicates(subset=["order_id"], keep="first").reset_index(drop=True)

# 2. Clean messy string columns using the .str accessor
df["customer"] = df["customer"].str.strip().str.title()

# 3. Clean currency formatting and convert to numeric (coerce invalid strings like 'N/A' to NaN)
df["amount"] = (
    df["amount"]
    .str.replace("$", "", regex=False)
    .pipe(pd.to_numeric, errors="coerce")
)

# 4. Parse dates safely (coerce invalid dates to NaT - Not a Time)
df["order_date"] = pd.to_datetime(df["order_date"], errors="coerce")
```

---

## 5. Handling Missing Data (`NaN` / `NaT`)

Missing data typically falls into three mechanisms: **MCAR** (Missing Completely at Random), **MAR** (Missing at Random, conditional on other observed variables), or **MNAR** (Missing Not at Random).

| Strategy | Pandas Method | When to Use |
| :--- | :--- | :--- |
| **Drop Rows** | `df.dropna(subset=["col"])` | When missingness is tiny ($< 2\%$) and MCAR, or when the target label is missing. |
| **Drop Columns** | `df.drop(columns=["col"])` | When a column has $> 60\%\text{–}70\%$ missing values and carries little signal. |
| **Mean / Median Imputation** | `df["col"].fillna(df["col"].median())` | Use **Mean** for symmetric numerical data; use **Median** for skewed numerical data. |
| **Mode / Constant Imputation** | `df["cat"].fillna(df["cat"].mode()[0])` | For categorical columns (or fill with a dedicated `"Missing"` category). |
| **Group-wise Imputation** | `df.groupby("cat")["val"].transform(...)` | Impute missing values using the median of that specific subgroup. |
| **Forward / Backward Fill** | `df["col"].ffill()` / `.bfill()` | For ordered **time-series** data where the previous value carries forward. |

```python
# Impute numerical 'amount' with median
df["amount"] = df["amount"].fillna(df["amount"].median())

# Impute categorical 'category' with the mode (most frequent value)
df["category"] = df["category"].fillna(df["category"].mode()[0])

# Impute 'customer' with a constant placeholder
df["customer"] = df["customer"].fillna("Unknown Customer")
```

---

## 6. Detecting and Treating Outliers

### 6.1 The IQR (Tukey's Fence) Method
Any observation outside the interval $[Q_1 - 1.5 \times \text{IQR}, \; Q_3 + 1.5 \times \text{IQR}]$ is flagged as an outlier:

$$\text{Lower Bound} = Q_1 - 1.5 \times \text{IQR}, \qquad \text{Upper Bound} = Q_3 + 1.5 \times \text{IQR}$$

```python
q1 = df["amount"].quantile(0.25)
q3 = df["amount"].quantile(0.75)
iqr = q3 - q1

lower_bound = q1 - 1.5 * iqr
upper_bound = q3 + 1.5 * iqr

# Option A: Filter out outliers
df_filtered = df[(df["amount"] >= lower_bound) & (df["amount"] <= upper_bound)]

# Option B: Winsorization / Clipping (cap extreme values at the boundaries)
df["amount_clipped"] = df["amount"].clip(lower=lower_bound, upper=upper_bound)
```

---

## 7. Grouping, Aggregating, and Merging Tables

### 7.1 Split-Apply-Combine with `groupby()`
```python
summary = (
    df.groupby("category", as_index=False)
    .agg(
        total_orders=("order_id", "count"),
        avg_amount=("amount_clipped", "mean"),
        max_amount=("amount_clipped", "max")
    )
)
```

### 7.2 Relational Joins with `pd.merge()`
```python
customers_table = pd.DataFrame({
    "customer": ["Alice", "Bob", "Charlie"],
    "tier": ["Gold", "Silver", "Gold"]
})

# SQL-style LEFT JOIN
merged_df = pd.merge(
    left=df,
    right=customers_table,
    on="customer",
    how="left"  # Options: 'inner', 'left', 'right', 'outer'
)
```