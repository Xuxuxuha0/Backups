import pandas as pd
import os


# os.getcwd(...)
# 获取...的绝对路径
# 使用绝对路径时，建议使用os方法，即动态的地址，防止文件被移动了原路径失效的问题
# 例如：C:\Users\huawei\Desktop\code\Python\pandas\file\01.csv
u1 = os.getcwd()  # 获取当前vscode打开的文件夹的绝对路径
print(u1)
u2 = os.path.join(u1, "Python", "pandas", "file", "01.csv")  # 拼接路径
print(u2)


"""
./---当前级,即vscode打开的文件所在的一级
../---上一级
"""
df = pd.read_csv(
    r"Python\pandas\file\01.csv",
    header=1,  # 忽略第0行，把第1行作为列标签
)
print(df)


df = pd.read_csv(
    r"Python\pandas\file\02.csv",
    names=["one", "two", "three"],  # 只用names：用于文件是纯数据，没有表头
)
print(df)


df = pd.read_csv(
    r"Python\pandas\file\01.csv",
    header=1,  # 忽略第0行，把第1行作为列标签
    names=["one", "two", "three"],  # 然后把列标签换掉
)
print(df)


df = pd.read_csv(
    r"Python\pandas\file\02.csv",
    index_col="02",  # 把02列作为行标签
)
df.index = pd.to_datetime(df.index)  # 把行标签的时间表达式改为--的格式
print(df)
print(df.loc["2008"])  # 查看index包含2008的所有行
print(df.loc["2008-11"])  # 查看index包含2008-11的所有行


df = pd.read_csv(
    r"Python\pandas\file\03.csv",
    dtype={"id": str},  # id列以字符串读入
)
print(df)


df = pd.read_csv(
    r"Python\pandas\file\03.csv",
    converters={"id": lambda x: int(x) + 10},  # id列转化为数字并+10
)
print(df)


df = pd.read_csv(
    r"Python\pandas\file\03.csv",
    skiprows=[0, 2],  # 跳过第1，3行)
)
print(df)


df = pd.read_csv(
    r"Python\pandas\file\03.csv",
    na_values=["男"],  # 把表中的男改为NaN
)
print(df)
