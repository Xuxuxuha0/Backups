import numpy as np
from matplotlib import pyplot as plt

plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False

# 设置大小
plt.rcParams["figure.figsize"] = (5, 5)

# 参数
lab = ["娱乐", "育儿", "饮食", "房贷", "交通", "其他"]
x = [200, 500, 1200, 7000, 200, 900]
# 各个板块距圆心的距离
exp = (0.03, 0.05, 0.06, 0.04, 0.08, 0.1)

# 绘制饼状图
plt.pie(
    x,
    labels=lab,
    autopct="%3.2f%%",
    explode=exp,
    labeldistance=1.2,
    pctdistance=0.7,
)

plt.legend()
plt.show()
