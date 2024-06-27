import numpy as np
import pandas as pd


"""
.Series(data,index,dtype,name,copy)
data:数据
index:数据对应的索引
name:该series的名称
特点:data和index都可以是不同类型的数据,但要求index是不能被修改的数据类型
"""
a = np.arange(1, 6)
print(type(a))
b = pd.Series(a)
print(type(b))
print(b)

print(b[1])  # 通过标签1索引；此处的1不代表下标，只是标签中的1
b[1] = 50  # 通过标签改变对应的值
print(b[1])

b["a"] = 20  # 当不存在时，可以追加这个键值对
print(b)

c = {"a": 1, "b": 2, "c": 3}  # 通过字典创建series
d = pd.Series(c)
print(d)
print(d[1])  # 如果标签不含数值型，还可以通过默认存在的0，1，2...这个标签取值
