import numpy as np
from matplotlib import pyplot as plt


# a = np.random.rand(2, 2, 3)  # (0,1)生成三维的随机数组，均匀分布
# b = np.random.randn(1000)  # 生成一维的随机数组，且服从标准正态分布
# print(b)
# plt.hist(b)
# plt.show()


"""
randint(low,high,size,dtype)
生成[low,high)的随机size规模的整数
没有high参数时,范围为[0,low)
"""
c = np.random.randint(1, size=5)
d = np.random.randint(1, 5, size=(2, 3))
print(d)


"""
随机种子
np.random.seed(int)
但是只管一次
"""


"""
np.random.normal(loc=0,scale=1,size)
生成size形状的服从参数为(loc,scale**2)的正态分布的随机数组
"""
