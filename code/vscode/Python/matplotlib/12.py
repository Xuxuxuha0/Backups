import numpy as np
from matplotlib import pyplot as plt

plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False

movie = ["蝙蝠侠", "狙击手", "笨小孩"]
real_day1 = np.array([4053, 2589, 1543])
real_day2 = np.array([7840, 4013, 2421])
real_day3 = np.array([8080, 3637, 1342])


# 高度
h = 0.2

num_y = np.arange(len(movie))

# 计算高度
day1_start_y = num_y
day2_start_y = num_y + h
day3_start_y = num_y + 2 * h

# 绘图
plt.barh(day1_start_y, real_day1, height=h)
plt.barh(day2_start_y, real_day2, height=h)
plt.barh(day3_start_y, real_day3, height=h)

# 替换y轴的内容
plt.yticks(num_y + h, movie)

# 标数据
for i in range(len(movie)):
    plt.text(real_day1[i], day1_start_y[i], real_day1[i], va="center", ha="left")
    plt.text(real_day2[i], day2_start_y[i], real_day2[i], va="center", ha="left")
    plt.text(real_day3[i], day3_start_y[i], real_day3[i], va="center", ha="left")

plt.xlim(0, 9000)
plt.show()
