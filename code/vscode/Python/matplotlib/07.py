import numpy as np
from matplotlib import pyplot as plt

"""
subplots返回画布(元组)和区域(二维数组)
"""
fig, axes = plt.subplots(2, 2)  # 两行两列

ax1 = axes[0][0]
x = np.arange(1, 5)
ax1.plot(x, x * x)
ax1.set_title("square")

ax2 = axes[0][1]
ax2.plot(x, np.sqrt(x))
ax1.set_title("sqrt")

ax3 = axes[1][0]
ax3.plot(x, np.exp(x))
ax1.set_title("exp")

ax4 = axes[1][1]
ax4.plot(x, np.log10(x))
ax1.set_title("log10")

plt.tight_layout()

plt.show()
