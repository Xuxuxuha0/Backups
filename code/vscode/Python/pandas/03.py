import numpy as np
import pandas as pd


a = pd.Series([5, 6, 7, 8], index=["a", "b", "c", "d"])
print(a[["a", "d"]])  # 用[[]]来索引多个标签的值


"""
index为数值时的区别:
索引:index
切片:下标

切片时：
使用数值会认为是python切片,不包含末端
否则认为是pandas切片,包含末端
"""
a = pd.Series([4, 5, 6], index=[100, 200, 300])
print(a[1:3])  # 此处的[1:3]是下标切片
print(a[-3:])

b = pd.Series([1, 2, 3, 4], index=["a", "x", "c", "z"])
print(b["a":"z"])
