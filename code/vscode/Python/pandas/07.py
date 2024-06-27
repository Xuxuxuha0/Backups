import numpy as np
import pandas as pd

"""
append和drop都不会改变原数据
"""

data = {
    "one": pd.Series([1, 2, 3], index=["a", "b", "c"]),
    "two": pd.Series([4, 5, 6], index=["a", "y", "c"]),
    "three": pd.Series([7, 8, 9], index=["o", "b", "t"]),
}
df = pd.DataFrame(data)
print(df)


"""
追加一行
注意:append方法即将被pandas.concat取代
"""
d = {"one": 0, "two": 0}
df2 = df.append(d, ignore_index=True)  # 忽略行标签式追加
print(df2)
dd = pd.Series(d, name="new")  # 追加一行，该行是一个有名称的series
df3 = df.append(dd)
print(df3)


"""
追加多行
"""
a = [[10, 30, 20], [10, 20, 30]]  # 列表中的每一个元素为新加的每一行
print(df.append(a))
aa = [10]
print(df.append(aa))
aaa = [[[10, 20, 30]]]
print(df.append(aaa))

b = pd.DataFrame(
    a,
    columns=["one", "two", "three"],
    index=["z", "x"],
)  # 把列表转换为dataframe再追加
print(df.append(b))


"""
删除行
"""
print(df)
print(df.drop("a"))  # 删除第a行
