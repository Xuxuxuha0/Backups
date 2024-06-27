from matplotlib import pyplot as plt
import numpy as np

times = ["%s:" % i for i in range(10)]
income = np.random.randint(500, 2000, size=len(times))
output = np.random.randint(300, 1500, size=len(times))

plt.xticks(range(1, len(times), 2), rotation=45)
plt.rcParams["font.sans-serif"] = ["SimHei"]  # 设置显示中文黑体
plt.plot(times, income, label="收入")
plt.plot(times, output, label="支出")

plt.legend()  # 展示图例，位置可以自选

for a, b in zip(times, income):  # 顺序取一对值
    plt.text(a, b, b)  # 找到坐标(a,b)，并把b写出来

for a, b in zip(times, output):
    plt.text(a, b, "%sw" % b)

plt.grid(True)  # 网格


plt.show()
