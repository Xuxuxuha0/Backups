import pandas as pd


"""
数据合并
merge(...)
"""
df1 = pd.DataFrame(
    {
        "userid": ["a", "b", "c", "d"],
        "age": [10, 20, 15, 30],
    }
)
df2 = pd.DataFrame(
    {
        "userid": ["a", "c", "a"],
        "salary": [100, 200, 300],
    }
)
print(df1)
print(df2)
# 把userid相同的数据合并(iner方式)
print(pd.merge(df1, df2, on="userid"))

df3 = pd.DataFrame(
    {
        "userid": ["a", "c", "e"],
        "salary": [100, 200, 300],
    }
)
# 以df1的userid一列为参考，合并两个表(left方式)
print(pd.merge(df1, df3, how="left", on="userid"))
# 合并两个表的所有信息(outer方式)
print(pd.merge(df1, df3, how="outer", on="userid"))


df = pd.DataFrame(
    {
        "month": [1, 4, 7, 10],
        "year": [2012, 2014, 2013, 2014],
        "sale": [55, 40, 84, 31],
    }
)
"""
set_index()
"""
# month列作为index
print(df.set_index("month"))
