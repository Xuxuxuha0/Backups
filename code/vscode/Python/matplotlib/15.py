import numpy as np
from matplotlib import pyplot as plt

plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False

fig, ax = plt.subplots()

x = [np.random.randn(n) for n in [1000, 500, 200]]

ax.hist(x, 10, histtype="bar", edgecolor="white", label=list("abc"))

ax.set_title("多类型直方图")

ax.legend()

plt.show()
