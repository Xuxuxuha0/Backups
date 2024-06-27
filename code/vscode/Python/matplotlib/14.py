import numpy as np
from matplotlib import pyplot as plt

plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False

fig, ax = plt.subplots()
x = np.random.normal(100, 20, 100)

# 指定横坐标
bins = [50, 60, 70, 90, 100, 110, 140, 150]
ax.hist(x, bins, color="g", edgecolor="white")

ax.set_title("不等距分组")

plt.show()
