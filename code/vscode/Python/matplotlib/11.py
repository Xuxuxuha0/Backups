import numpy as np
from matplotlib import pyplot as plt

plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False

movie = ["蝙蝠侠", "狙击手", "笨小孩"]
real_day1 = np.array([4053, 2589, 1543])
real_day2 = np.array([7840, 4013, 2421])
real_day3 = np.array([8080, 3637, 1342])

# 计算第2，3层离左侧的距离
left_day2 = real_day1
left_day3 = real_day1 + real_day2

# 高度
h = 0.2

# 绘图
plt.barh(movie, real_day1, height=h)
plt.barh(movie, real_day2, left=left_day2, height=h)
plt.barh(movie, real_day3, left=left_day3, height=h)

# 显示数据
sum = real_day1 + real_day2 + real_day3
for i in range(len(movie)):
    plt.text(sum[i], movie[i], sum[i], va="center", ha="left")

# 限制x轴最大值
plt.xlim(0, sum.max() + 2000)

plt.show()
