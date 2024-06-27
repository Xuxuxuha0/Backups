import numpy as np
from matplotlib import pyplot as plt

plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False

plt.rcParams["figure.dpi"] = 100
plt.rcParams["figure.figsize"] = (5, 3)

countries = ["挪威", "德国", "中国", "美国", "瑞典"]
gold_medal = np.array([16, 12, 9, 8, 8])

# 水平条形图
plt.barh(countries, width=gold_medal)

plt.show()
