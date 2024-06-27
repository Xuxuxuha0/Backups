import numpy as np
from matplotlib import pyplot as plt

"""
subplot均分区域:
233
【1】【2】【3*】
【4】【5】【6】
如果新建的图在原图之上，则会覆盖原图重叠部分
"""
plt.subplot(211, title="p1")  # 2行1列 并定位在1区域

# 一区绘图
plt.plot(range(50, 70), marker="o")
plt.grid()
# 二区绘图
plt.subplot(212, title="p2")
plt.plot(np.arange(12) ** 2)

plt.tight_layout()  # 让布局合理

plt.show()
