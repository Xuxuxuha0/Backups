import numpy as np


"""
平均值
x.mean()
"""
m = np.arange(20).reshape((4, 5))
aver_all = m.mean()
aver_0 = m.mean(axis=0)  # 从上往下算均值，返回一维数组
aver_1 = m.mean(axis=1)  # 从左往右算，返回一维数组


"""
中位数
np.median(x)
"""
mid1 = np.median(m[1])


"""
标准差
np.std(x)
"""
s1 = np.std(m[0])


"""
方差
np.var(x)
"""
s1 = np.var(m[0])


"""
最大 x.max()
    从上往下查找 x.max(axis=0)
    从左往右查找 x.max(axis=1)

最小 x.min()
同上

求和 x.sum()
同上
"""


"""
加权平均值
np.average(x,axis=None,weights=None,returned=False)
weights:与x形状相同的数组;None默认为1
"""
