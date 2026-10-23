# Chapter 6: Unsupervised Learning

## 1. The Unsupervised Learning Paradigm

In **Unsupervised Learning**, we are given an unlabeled dataset $\mathcal{D} = \{x_1, x_2, \dots, x_N\}$ where $x_i \in \mathbb{R}^d$, without any target labels $y_i$. The objective is to discover hidden structure, natural groupings, low-dimensional manifolds, or anomalies directly from the feature space.

* **Clustering:** Partitioning samples into homogeneous groups (e.g., customer segmentation, document grouping).
* **Dimensionality Reduction:** Compressing $d$ features into $k \ll d$ latent components while preserving maximum information (e.g., visualization, noise compression).
* **Anomaly / Outlier Detection:** Identifying rare observations that deviate significantly from the normal data distribution (e.g., network intrusion, credit card fraud).

> **Important Prerequisite:** Because unsupervised algorithms rely heavily on Euclidean distance $\|x_i - x_j\|_2$ or variance projections, **you must standardize features (`StandardScaler`) before fitting!**

---

## 2. Clustering Algorithms

### 2.1 $K$-Means Clustering
Partitions data into $K$ distinct, non-overlapping clusters represented by their centroids $\mu_1, \dots, \mu_K$.

#### Algorithm Steps (Lloyd's Algorithm)
1. Initialize $K$ centroids randomly (or smartly via **`k-means++`** to speed up convergence).
2. **Assignment Step:** Assign each point $x_i$ to its nearest centroid:
   $$c_i = \arg\min_{k \in \{1, \dots, K\}} \|x_i - \mu_k\|_2^2$$
3. **Update Step:** Recompute each centroid $\mu_k$ as the mean of all points assigned to cluster $k$.
4. Repeat Steps $2\text{–}3$ until centroids no longer move.

#### Objective Function (Inertia / Within-Cluster Sum of Squares)
$$J = \sum_{i=1}^{N} \|x_i - \mu_{c_i}\|_2^2$$

### 2.2 Choosing $K$: The Elbow Method & Silhouette Score
* **Elbow Method:** Plot Inertia ($J$) against $K$ and look for the "elbow" point where adding another cluster yields diminishing returns.
* **Silhouette Coefficient ($s_i \in [-1, 1]$):** Measures how similar a point is to its own cluster ($a_i$, mean intra-cluster distance) compared to the nearest neighboring cluster ($b_i$, mean nearest-cluster distance):
  $$s_i = \frac{b_i - a_i}{\max(a_i, b_i)}$$
  * $s_i \approx +1$: Well-clustered and far from neighboring clusters.
  * $s_i \approx 0$: Lies on the boundary between two clusters.
  * $s_i < 0$: Likely assigned to the wrong cluster.

### 2.3 Hierarchical Clustering & DBSCAN

| Algorithm | How It Works | Advantages | Limitations |
| :--- | :--- | :--- | :--- |
| **$K$-Means** | Minimizes variance around $K$ spherical centroids. | Fast ($O(N \cdot K \cdot d)$), scalable. | Must specify $K$ upfront; fails on non-spherical shapes; sensitive to outliers. |
| **Agglomerative Hierarchical** | Bottom-up: starts with each point as its own cluster and merges closest pairs using linkage criteria (`ward`, `complete`, `average`). | Produces an interpretable **Dendrogram** tree; no need to fix $K$ upfront. | Computationally expensive ($O(N^2 \log N)$); doesn't scale to huge datasets. |
| **DBSCAN** | Groups dense regions having at least `min_samples` within radius $\epsilon$ (`eps`). Labels isolated points as `-1` (Noise). | Finds **arbitrary non-linear shapes**; automatically detects outliers; doesn't need $K$. | Struggles when clusters have vastly different densities; sensitive to `eps` choice. |

---

## 3. Dimensionality Reduction

### 3.1 Principal Component Analysis (PCA)
**PCA** is a linear dimensionality reduction technique that projects data onto orthogonal axes (**Principal Components**) that capture the **maximum variance** in the data.

#### Mathematical Formulation
1. Center the standardized data matrix $X \in \mathbb{R}^{N \times d}$ so each feature has mean $0$.
2. Compute the empirical covariance matrix:
   $$\Sigma = \frac{1}{N - 1} X^T X$$
3. Compute the eigendecomposition $\Sigma v_j = \lambda_j v_j$ (or Singular Value Decomposition $X = U S V^T$).
4. Sort eigenvectors $v_j$ in descending order of their eigenvalues $\lambda_j$. The top $k$ eigenvectors form projection matrix $W_k \in \mathbb{R}^{d \times k}$:
   $$Z = X W_k \in \mathbb{R}^{N \times k}$$
5. The fraction of total variance retained by component $j$ is the **Explained Variance Ratio**:
   $$\text{EVR}_j = \frac{\lambda_j}{\sum_{m=1}^{d} \lambda_m}$$

### 3.2 t-SNE (t-Distributed Stochastic Neighbor Embedding)
* While PCA is linear and preserves global variance, **t-SNE** is a **non-linear manifold learning** technique that converts pairwise Euclidean distances into conditional probabilities and minimizes the Kullback-Leibler (KL) divergence in $2\text{D}$ or $3\text{D}$.
* **Use Case:** Visualizing high-dimensional embeddings (e.g., neural network hidden layers, image features) in $2\text{D}$. *(Note: t-SNE does not preserve global distances and cannot `.transform()` new test points directly.)*

---

## 4. Complete `scikit-learn` Unsupervised Pipeline (PCA + $K$-Means)

```python
import numpy as np
from sklearn.datasets import load_wine
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA
from sklearn.cluster import KMeans
from sklearn.metrics import silhouette_score

# 1. Load unlabeled feature matrix (178 samples, 13 chemical features)
X, _ = load_wine(return_X_y=True)

# 2. Standardize features (Mandatory before PCA and K-Means!)
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# 3. Dimensionality Reduction with PCA (retain 95% of variance or project to 2D)
pca = PCA(n_components=2, random_state=42)
X_pca = pca.fit_transform(X_scaled)
print("Explained Variance Ratio (2 components):", pca.explained_variance_ratio_)
print(f"Total Variance Retained: { np.sum(pca.explained_variance_ratio_) * 100:.2f}%")

# 4. Find optimal K using Silhouette Score
for k in range(2, 6):
    kmeans = KMeans(n_clusters=k, init="k-means++", n_init=10, random_state=42)
    cluster_labels = kmeans.fit_predict(X_scaled)
    sil_score = silhouette_score(X_scaled, cluster_labels)
    print(f"K = {k} | Inertia = {kmeans.inertia_:.1f} | Silhouette Score = {sil_score:.4f}")
```