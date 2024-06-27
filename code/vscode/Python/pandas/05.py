import numpy as np
import pandas as pd


"""
DataFrame:
相比series多了一个列标签columns.与行标签index对应
"""
data = [1, 2, 3, 4]
df = pd.DataFrame(data)  # 只给数据时，默认为一列
print(df)


data = [["a", 1], ["b", 2], ["c", 3]]  # 每个[]为一行
df = pd.DataFrame(data, columns=["name", "age"])
print(df)


"""
列表嵌套字典
"""
data = [
    {"a": 1, "aa": 4},
    {"b": 2, "bb": 5, "a": 6},
    {"c": 3, "a": 6.0},
]  # 每个{}是一行，冒号前为列名，若没有出现则新添一列，冒号后为数据
df = pd.DataFrame(data, index=["first", "second", "third"])
print(df)

df = pd.DataFrame(
    data, index=["first", "second", "third"], columns=["a", "b", "z"]
)  # 指定显示a、b、z列
print(df)


"""
字典嵌套列表
"""
data = {
    "name": ["a", "b", "c", "d"],
    "age": [1, 2, 3, 4],
}  # 每个键值对是一列
df = pd.DataFrame(data)
print(df)


"""
用字典和series创建dataframe
"""
data = {
    "one": pd.Series([1, 2, 3], index=["a", "b", "c"]),
    "two": pd.Series([4, 5, 6], index=["a", "y", "c"]),
    "three": pd.Series([7, 8, 9], index=["o", "b", "t"]),
}  # NaN是浮点型，因此该列含NaN就全部会变为浮点型
df = pd.DataFrame(data)
print(df)
