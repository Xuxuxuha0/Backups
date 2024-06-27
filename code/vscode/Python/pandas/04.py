import numpy as np
import pandas as pd


a = pd.Series(np.random.rand(30))
print(a.head())  # 默认查看前5条
print(a.head(10))
print(a.tail())


b = pd.Series([5, 6, 7, 8], index=["a", "b", "c", "d"])
b1 = b.reindex(
    list("cde12"), fill_value=0
)  # 创建一个新的series，若b中有对应的标签，则直接拷贝；没有则默认赋值为NaN，也可以用fill_value来指定
print(b)
print(b1)


"""
对齐运算
"""
c = pd.Series([5, 6, 7, 8], index=["a", "b", "c", "d"])
d = pd.Series([10, 20, 30, 40], index=["b", "a", "x", "z"])
print("c + d", c + d)  # 当标签在cd都有时，用值相加；否则直接赋值为NaN


"""
删除和添加
"""
c = pd.Series([5, 6, 7, 8], index=["a", "b", "c", "d"])
c1 = c.drop("a")  # c1是删除a键值对后的值，c不变
c2 = c.drop("a", inplace=True)  # c会变
print(c)

c["z"] = "a"  # 添加
print(c)
