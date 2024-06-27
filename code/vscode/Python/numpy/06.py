import numpy as np


"""
直接读整个文件
文件中被#的行和空行不读入 
"""
data = np.loadtxt(r"Python\numpy\file\data1.txt")  # 相对路径，用r取消\的转义
print(data, "\n", data.shape)

data2 = np.loadtxt(
    r"Python\numpy\file\data2.csv",
    dtype=np.int32,  # dtype=nmp.int32表示把数据转为整数
    delimiter=",",  # delimiter表示分隔符
)
print(data2)


"""
对文件内容分类别读入
"""
# 1、自定义数据类型
user_info = np.dtype(
    [("name", "U10"), ("age", "i1"), ("gender", "U1"), ("height", "i1")]
)  # info:information信息;(列名，数据类型)
print(user_info)

# 2、使用自定义的变量，按格式读入数据
data3 = np.loadtxt(
    r"Python\numpy\file\data3.txt",
    dtype=user_info,
    skiprows=2,  # skiprows:跳过前2行
    encoding="utf-8",  # encoding:中文
)
print(data3)

data4 = np.loadtxt(
    r"Python\numpy\file\data3.txt",
    dtype=int,  # 只取一列，int类型
    skiprows=1,
    usecols=3,  # 只取下标为3的列，多个列用元组类型；注意usecols和dtype是一一对应的
    encoding="utf-8",
)
print(data4)

is_girl = data3["gender"] == "女"  # 如果为女，则赋值为true
print(is_girl)
print(data3["height"][is_girl])  # 布尔索引


def BlankAge(age):
    try:
        return int(age)
    except:
        return 0


# 如何解释该答案？？？
data5 = np.loadtxt(
    r"Python\numpy\file\data4.txt",
    skiprows=1,
    usecols=1,
    converters={1: BlankAge},  # 调用BlankAge读入下标1的列，如果异常则补充0
    encoding="utf-8",
)
print(data5)
