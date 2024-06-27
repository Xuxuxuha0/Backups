import numpy as np
import pandas as pd


data = {
    "one": pd.Series([1, 2, 3], index=["a", "b", "c"]),
    "two": pd.Series([4, 5, 6], index=["a", "y", "c"]),
    "three": pd.Series([7, 8, 9], index=["o", "b", "t"]),
}
df = pd.DataFrame(data)
print(df)

print(df.T)  # 转置，df不变

print(df.axes)  # 提取所有行标签和列标签

print(df.empty)  # 判断是否为空

print(df.shape)  # 返回元组

df.rename(
    index={"a": "aa", "b": "bb"},
    columns={"one": "first"},
    inplace=True,  # 要修改原数据
)  # 修改行列标签
print(df)

print(df.info())  # 提取df的摘要信息


"""
sort_index(axis=0,ascending=True,inplace=False)
默认对行标签按从小到大的顺序排,且不改变原数据
"""
df = pd.DataFrame(
    {
        7: pd.Series([5, 8, 9], index=[3, 2, 1]),
        4: pd.Series([0, 8, 9], index=[3, 1, 2]),
        9: pd.Series([5, 5, 5], index=[2, 3, 1]),
    }
)
print(df)
print("-----按列标签排序-----")
print(df.sort_index(axis=1))


"""
sort_values(by,axis=0,ascending,inplace,na_position)
按值排序,同时会跟着移动行标签
by:对哪几列排序
ascending:升序True 降序False,与by对应
axis:0表示对列的值操作
"""


print("-----对标签为7的列排序-----")
print(df.sort_values(by=7))


"""
对7列的值降序排列,如果出现相同的值,以4列的值升序排列
"""
print("\n")
print(df.sort_values(by=[7, 4], ascending=[False, True]))


"""
对3行排序
"""
print("\n")
print(df.sort_values(by=3, axis=1))
