import numpy as np
from matplotlib import pyplot as plt

x = range(5)
data = [5, 20, 15, 25, 10]

plt.title("柱状图")
plt.grid(ls="--", alpha=0.5)

plt.bar(x, data, bottom=[10, 20, 5, 0, 10], facecolor="green")  # bar绘制柱状图

plt.show()
