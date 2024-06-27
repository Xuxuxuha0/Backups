import numpy as np
from matplotlib import pyplot as plt

countries = ["挪威", "德国", "中国", "美国", "瑞典"]
gold_medal = [16, 12, 9, 8, 8]
silver_medal = [8, 10, 4, 10, 5]
bronze_medal = [13, 5, 2, 7, 5]

wid = 0.2
x = np.arange(len(countries))
gold_x = x  # 金牌的起始位置
silver_x = x + wid
bronze_x = x + wid * 2

# 绘制图
plt.bar(gold_x, gold_medal, color="gold", width=wid)
plt.bar(silver_x, silver_medal, color="silver", width=wid)
plt.bar(bronze_x, silver_medal, color="#BC8F8F", width=wid)

# x轴标的位置和名称
plt.rcParams["font.sans-serif"] = ["SimHei"]  # 设置显示中文黑体
plt.xticks(x + wid, labels=countries)

# 显示柱状高度(error)
for i in range(len(countries)):
    plt.text(gold_x[i], gold_medal[i], va="bottom", ha="center")
    plt.text(silver_x[i], silver_medal[i], va="bottom", ha="center")
    plt.text(bronze_x[i], bronze_medal[i], va="bottom", ha="center")


plt.show()
