import pandas as pd
import numpy as np

company = ["a", "b", "c"]

a = np.random.randint(0, len(company), 10)  # [0~len()-1]范围内生成10个数据
print(a)

b = [company[x] for x in np.random.randint(0, len(company), 10)]
print(b)

data = pd.DataFrame(
    {
        "company": [company[x] for x in np.random.randint(0, len(company), 10)],
        "salary": np.random.randint(5, 50, 10),
        "age": np.random.randint(15, 50, 10),
    }
)
print(data)


"""
分组groupby
"""
group = data.groupby("company")  # 生成DataFrameGroupBy对象
print(list(group))  # 按照company分组并转换为list


"""
聚合agg(...)
"""
print(group.agg({"salary": "median", "age": "mean"}))  # 求中位数、平均值


"""
转换值transform
"""
salary_mean = (
    data[["salary", "company"]].groupby("company", as_index=False).agg("mean")
)  # 取出salary和company，按company分组，但不把company作为行标签，对salary求平均
print(salary_mean)

data["avg_salary"] = data.groupby("company")["salary"].transform(
    "mean"
)  # 以company分组，对salary求平均，然后新添一列avg_salary，把平均值填进去
print(data)


"""
apply
"""


def get_oldest_staff(x):
    df = x.sort_values(by="age", ascending=True)
    return df.iloc[-1]


oldest_staff = data.groupby("company", as_index=False).apply(
    get_oldest_staff
)  # 先分组，把每个组应用函数，按照age进行排序，并返回age最大的一行
print(data)
print(oldest_staff)
