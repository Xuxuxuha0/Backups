import numpy as np
import pandas as pd

data = {
    "one": pd.Series([1, 2, 3], index=["a", "b", "c"]),
    "two": pd.Series([4, 5, 6], index=["a", "y", "c"]),
    "three": pd.Series([7, 8, 9], index=["o", "b", "t"]),
}
df = pd.DataFrame(data)
print(df)

print(df["two"])  # 用列名取出该列；列不支持下标索引
print(df[["two", "one"]])  # [[]]取多个列；此处不支持切片

df["four"] = pd.Series([10, 20, 30], index=["a", "b", "c"])  # 追加，没有的行赋值为NaN
print(df)

df["four"] = df["two"] + df["one"]  # 加运算创建
print(df)


info = [
    ["王杰", 18],
    ["李杰", 19],
    ["刘杰", 17],
]
df = pd.DataFrame(info, columns=["name", "age"])
df.insert(
    loc=0,  # 放在第0列
    column="score",
    value=[91, 90, 95],
)  # insert方法追加列
print(df)

del df["age"]  # 无返回值
print(df)
col = df.pop("name")  # 有返回值
print(col)
print("两次删除后的df:", "\n", df)


"""
loc用标签
iloc用下标
"""
df = pd.DataFrame(data)
print(df)
print(df.loc["a"])  # 用loc取行
print(df.loc["b":"t", "three"])  # 取行列交叉点
print(df.loc[["a", "b"], ["one", "two"]])  # 与numpy不同,此处没有对应关系

print(df)
print(df.iloc[2])  # 下标为2的行
print(df.iloc[[0, 2]])  # 下标为0,2的行
print(df.iloc[0:3])  # 0,1,2行
print(df.iloc[0, 1])  # 0行1列
