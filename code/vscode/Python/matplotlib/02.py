from matplotlib import pyplot as plt
import numpy as np

times = [
    "6/1",
    "6/2",
    "6/3",
    "6/4",
    "6/5",
    "6/6",
    "6/7",
    "6/8",
    "6/9",
    "6/10",
    "6/11",
    "6/12",
    "6/13",
    "6/14",
    "6/15",
    "6/16",
    "6/17",
    "6/18",
    "6/19",
    "6/20",
    "6/21",
]
sales = np.random.randint(500, 2000, size=len(times))
plt.xticks(  # 把x轴设置成想要的样子
    range(1, len(times), 2),  # x轴隔一个显示一个
    labels=["日期%s" % i for i in times],  # ???
    rotation=45,  # 旋转45度
    color="blue",
)

plt.plot(times, sales)
plt.show()
