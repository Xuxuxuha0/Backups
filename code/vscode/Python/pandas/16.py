import pandas as pd

"""
去重
drop_duplicates(...)
"""
df = pd.DataFrame(
    {
        "month": [1, 1, 7, 10, 0, 0],
        "year": [2012, 2012, 2013, 2014, 2000, 2000],
        "sale": [55, 50, 50, 31, 30, 30],
    }
)
print(df)

# 删除重复的行
print(df.drop_duplicates())

# 基于year和month列来删除重复的行
print(df.drop_duplicates(subset=["year", "month"]))
