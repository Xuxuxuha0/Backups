import numpy as np
from matplotlib import pyplot as plt

x = np.arange(-50, 51)
y = x**2


"""
调整边框/轴
"""
ax = plt.gca()  # 调用spines来修改边框

ax.spines["right"].set_color("none")
ax.spines["top"].set_color("none")  # 设置颜色为none可以不显示这条边线

ax.spines["left"].set_position(("data", 0))  # data表示'值移动'，把左边线移到0位置
ax.spines["left"].set_position(("axes", 0.5))  # axes表示百分比移动，此处为移动百分之50

plt.ylim(y.min(), y.max())  # 设置y轴区间


"""
两种调整分辨率的方式
"""
plt.rcParams["figure.dpi"] = 100  # 指定dpi为100的图片尺寸：600*400   若dpi=200：1200*800
plt.rcParams["figure.figsize"] = (3, 2)  # 300*200


"""
调整曲线的格式
"""
plt.plot(x, y, linewidth="1", label="test", color="r", linestyle="-.", marker="o")
plt.legend(loc="lower left")  # 图例位置

plt.show()
