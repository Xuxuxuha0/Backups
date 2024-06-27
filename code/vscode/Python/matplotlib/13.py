import numpy as np
from matplotlib import pyplot as plt

plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False

x_value = np.random.randint(140, 180, 300)

# 创建一个画布
fig, ax = plt.subplots()

# 绘制直方图
num, bins, pathches = ax.hist(x_value, bins=10, edgecolor="white")

print("高度num:", num, "\n")
print("横坐标bins:", bins, "\n")
print("第一个柱子的参数pathches[0]:", pathches[0], "\n")

plt.xlabel("身高")
plt.ylabel("数量")

# 根据前10个横坐标绘制折线
ax.plot(bins[:10], num, "--", marker="o")

plt.show()
