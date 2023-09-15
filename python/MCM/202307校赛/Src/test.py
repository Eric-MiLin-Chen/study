import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans

# 输入点的集合，x 和 y 分别为 x 和 y 坐标轴的值
x = [1, 1.5, 3, 5, 3.5, 4.5, 3.5]
y = [1, 2, 4, 7, 5, 5, 4.5]

# 将 x 和 y 坐标轴的值组合成一个数组
data = np.array(list(zip(x, y)))

# 设置要聚类的簇的数量
k = 2

# 使用 K-Means 进行聚类
kmeans = KMeans(n_clusters=k)
kmeans.fit(data)

# 获取聚类的中心点
centroids = kmeans.cluster_centers_

# 获取每个数据点所属的簇标签
labels = kmeans.labels_

# 展示聚类结果
plt.scatter(data[:, 0], data[:, 1], c=labels, cmap="rainbow")
plt.scatter(
    centroids[:, 0], centroids[:, 1], marker="X", s=200, c="black", label="Centroids"
)
plt.xlabel("X Axis")
plt.ylabel("Y Axis")
plt.title("K-Means Clustering")
plt.legend()
plt.show()
