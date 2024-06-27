"""
柱状图横轴是各种变量
直方图横轴是连续数字区间
"""
from matplotlib import pyplot as plt
import numpy as np

x = np.arange(-50, 51)
y = x**2
z = x

plt.rcParams["font.sans-serif"] = ["SimHei"]  # 设置显示中文黑体
plt.title("y等于x平方")
plt.rcParams["axes.unicode_minus"] = False  # 保留轴的负号
plt.xlabel("x 轴", fontsize=12)  # x轴的名字,fontsize字体大小
plt.ylabel("y 轴")


plt.plot(
    x, y, linewidth=10
)  # plot()绘制线性表,linewidth线条粗细;上面的plt设定只针对于这个plot函数,对之后的plot不管用
plt.plot(x, z)

plt.show()
