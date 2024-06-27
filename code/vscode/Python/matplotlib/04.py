from matplotlib import pyplot as plt
import numpy as np

x = np.arange(0, 50)
y = x**2

"""
调整整个画布的大小和分辨率
"""
fig = plt.figure("f1", figsize=(8, 4), dpi=100, facecolor="green")


"""
画两个图
"""
# 从(0.1,0.1)开始绘制，宽度和高度为画布的百分百
ax1 = fig.add_axes([0.1, 0.1, 1, 1])
# 从(0.2,0.2)开始，宽度和高度为画布的百分之五十
ax2 = fig.add_axes([0.2, 0.2, 0.5, 0.5])

# 输入数据点
ax1.plot([1, 2, 3, 4], [3, 5, 4, 6])
ax2.plot([1, 2, 3, 4], [4, 5, 7, 6])


plt.show()
