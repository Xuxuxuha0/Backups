import pandas as pd
import numpy as np

"""
应用的对象：
apply:dataframe的行/列
applymap:dataframe的每个元素
map:单独一列(series)的每个元素
"""

"""
apply(函数,axis=0,...)
"""
df = pd.DataFrame([[4, 9], [4, 9], [3, 1]], columns=["a", "b"])
print(df)
# 从上往下对每列求和
print(df.apply(np.sum))


def f(self, x, y):
    self["C"] = (self["a"] + self["b"]) * x
    self["D"] = (self["a"] + self["b"]) * y
    return self


print(df.apply(f, x=3, y=8, axis=1))


# applymap用于dataframe
print(df[["a"]].applymap(lambda x: x + 1))
# map用于series
print(df["a"].map(lambda x: x + 1))
