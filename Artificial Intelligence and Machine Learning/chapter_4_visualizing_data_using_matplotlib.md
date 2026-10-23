# Chapter 4: Visualizing Data Using Matplotlib

## 1. Anatomy of a Matplotlib Figure

Matplotlib offers two interfaces:
1. **The Pyplot State-Machine Interface (`plt.plot(...)`):** Quick for interactive one-liners, but becomes messy when managing multiple subplots.
2. **The Object-Oriented (OO) Interface (`fig, ax = plt.subplots()`):** **The professional standard.** You explicitly create a `Figure` (the outer canvas/window) and one or more `Axes` (the individual plot coordinate systems) and call methods directly on `ax`.

### Key Components of a Plot
* **`Figure`:** The top-level container holding all subplots, titles, and legends.
* **`Axes` (`ax`):** An individual plot region with an $x$-axis, $y$-axis, spines, ticks, and data artists.
* **`Axis`:** The number-line objects (`ax.xaxis`, `ax.yaxis`) controlling tick locations (`Locator`) and tick label text (`Formatter`).

---

## 2. Choosing the Right Visualization for Your Data

| Analytical Goal | Variable Types | Best Chart Type | Matplotlib OO Method |
| :--- | :--- | :--- | :--- |
| **Trend over Time** | Continuous vs. Time/Ordered | **Line Plot** | `ax.plot(x, y)` |
| **Relationship / Correlation** | Continuous vs. Continuous | **Scatter Plot** | `ax.scatter(x, y)` |
| **Compare Categories** | Categorical vs. Numerical | **Bar / Horizontal Bar Chart** | `ax.bar(x, h)` / `ax.barh(y, w)` |
| **Univariate Distribution** | Single Continuous Variable | **Histogram** | `ax.hist(x, bins=...)` |
| **Spread, Median & Outliers** | Continuous across Categories | **Box Plot / Violin Plot** | `ax.boxplot(data)` |
| **2D Matrix / Correlations** | Grid / Matrix $(m \times n)$ | **Heatmap** | `ax.imshow(matrix)` |

---

## 3. Core Plot Types Using the Object-Oriented API

```python
import numpy as np
import matplotlib.pyplot as plt

# Set a clean, modern visual style
plt.style.use("seaborn-v0_8-whitegrid")
rng = np.random.default_rng(42)

# 1. Line Plot with Confidence Band
x = np.linspace(0, 10, 100)
y = np.sin(x)

fig, ax = plt.subplots(figsize=(8, 4))
ax.plot(x, y, color="#1f77b4", linewidth=2, linestyle="-", label=r"$\sin(x)$")
ax.fill_between(x, y - 0.2, y + 0.2, color="#1f77b4", alpha=0.2, label=r"$\pm 0.2$ Band")

ax.set_title("Sinusoidal Signal with Uncertainty Band", fontsize=13, fontweight="bold")
ax.set_xlabel("Time ($t$)", fontsize=11)
ax.set_ylabel("Amplitude", fontsize=11)
ax.legend(loc="upper right", frameon=True)
plt.tight_layout()
plt.show()
```

---

## 4. Multi-Plot Dashboards with `plt.subplots()`

In Exploratory Data Analysis (EDA), combining multiple views into a single figure helps compare distributions and relationships side by side:

```python
# Generate synthetic dataset
experience = rng.uniform(1, 10, size=150)
salary = 30 + 8.5 * experience + rng.normal(0, 6, size=150)
departments = ["Engineering", "Data Science", "Product", "Design"]
dept_headcount = [45, 38, 25, 18]

# Create a 2x2 Dashboard Grid
fig, axes = plt.subplots(nrows=2, ncols=2, figsize=(12, 8))

# Panel (0, 0): Scatter Plot (Experience vs. Salary)
sc = axes[0, 0].scatter(experience, salary, c=salary, cmap="viridis", alpha=0.8, edgecolors="k")
axes[0, 0].set_title("Experience vs. Salary")
axes[0, 0].set_xlabel("Years of Experience")
axes[0, 0].set_ylabel("Salary (in Lakhs)")
fig.colorbar(sc, ax=axes[0, 0], label="Salary")

# Panel (0, 1): Histogram (Salary Distribution)
axes[0, 1].hist(salary, bins=15, color="#2ca02c", edgecolor="black", alpha=0.75)
axes[0, 1].axvline(np.mean(salary), color="red", linestyle="--", linewidth=1.5, label=f"Mean: {np.mean(salary):.1f}")
axes[0, 1].set_title("Salary Distribution")
axes[0, 1].set_xlabel("Salary")
axes[0, 1].set_ylabel("Frequency")
axes[0, 1].legend()

# Panel (1, 0): Horizontal Bar Chart (Categorical Comparison)
axes[1, 0].barh(departments, dept_headcount, color="#ff7f0e", edgecolor="black")
axes[1, 0].set_title("Headcount by Department")
axes[1, 0].set_xlabel("Number of Employees")

# Panel (1, 1): Box Plot (Outlier & Quartile Inspection)
axes[1, 1].boxplot([salary[:50], salary[50:100], salary[100:]],
                   tick_labels=["Cohort A", "Cohort B", "Cohort C"],
                   patch_artist=True)
axes[1, 1].set_title("Salary Spread Across Cohorts")
axes[1, 1].set_ylabel("Salary")

# Overall figure title and automatic spacing
fig.suptitle("Exploratory Data Analysis (EDA) Overview", fontsize=15, fontweight="bold")
fig.tight_layout()
plt.show()
```

---

## 5. Customizing Annotations, Spines, and Exporting Figures

### 5.1 Highlighting Key Data Points (`ax.annotate`)
Instead of making the viewer search for anomalies, annotate key events directly on the canvas:

```python
fig, ax = plt.subplots(figsize=(7, 4))
months = np.arange(1, 13)
revenue = np.array([42, 45, 48, 50, 49, 53, 89, 55, 58, 60, 63, 68])

ax.plot(months, revenue, marker="o", color="#d62728", linewidth=2)

# Annotate the spike in Month 7
ax.annotate(
    "Promotional Campaign Spike (89L)",
    xy=(7, 89),                  # Point being annotated
    xytext=(3.5, 82),            # Position of the text label
    arrowprops=dict(arrowstyle="->", color="black", lw=1.5),
    fontsize=10,
    fontweight="bold"
)

# Clean up top and right spines for a modern look
ax.spines["top"].set_visible(False)
ax.spines["right"].set_visible(False)
ax.set_xticks(months)
ax.set_xlabel("Month")
ax.set_ylabel("Revenue (Lakhs)")

# Export high-resolution publication figure
fig.savefig("revenue_trend.png", dpi=300, bbox_inches="tight")
```

### Visualization Best Practices Checklist
* **Always label axes with units** (e.g., `"Latency (ms)"` or `"Revenue (INR Lakhs)"`).
* **Use `bbox_inches="tight"` and `dpi=300`** when saving figures for reports or presentations so labels are never clipped.
* **Prefer Horizontal Bar Charts (`ax.barh`)** when category names are long so text remains horizontal and readable.
* **Use colorblind-safe colormaps** like `"viridis"`, `"plasma"`, or `"cividis"` instead of `"jet"`.