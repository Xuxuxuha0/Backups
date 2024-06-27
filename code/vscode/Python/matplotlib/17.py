import numpy as np
from matplotlib import pyplot as plt

plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False

x = np.array([1, 2, 3, 4, 5, 7, 8, 9])
y = np.array([1, 4, 9, 16, 24, 45, 60, 81])
s = (20 * np.random.rand(8)) ** 2

# 散点图
plt.scatter(
    x,
    y,
    s,  # 点的大小
)

plt.show()
