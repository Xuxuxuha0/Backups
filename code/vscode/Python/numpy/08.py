import numpy as np


a = np.array([[1, 2, 3], [4, 5, 6]])
"""
追加函数
append()
"""
# 新添一行
b = np.append(a, [[7, 8, 9]], axis=0)
print(b)
# 新添两列
c = np.append(a, [[7, 8], [9, 10]], axis=1)
print(c)


"""
insert()
"""
# 往下标为1的行加进去
d = np.insert(a, 1, [7, 8, 9], axis=0)
print(d)


"""
delete()
"""
# 把下标1的列删掉
e = np.delete(a, 1, axis=1)
print(e)


"""
argwhere()
取出所有非0元素的索引
也可以往()里面设置条件
"""
print("---------------------------------")

a = np.array([5, 5, 1, 3, 2, 4, 1])
b = np.unique(a)  # 对a去重并排序
print(b)


a = np.array([[1, 2, 3], [4, 6, 5]])
b = np.sort(a)  # 默认对每一行进行排序；不会更改原来的数组
print(b)

info = np.dtype([("name", "U10"), ("age", int)])
a = np.array(
    [("cd", 10), ("ap", 90), ("cc", 40)],
    dtype=info,
)
print("a=", a)

b = np.sort(a, order="name")  # 按照name来排
print("b=", b)
