import numpy as np  # 别名

# 初始化
a = np.array([1, 2, 3])  # 可以用列表、元组、迭代对象、生成器等赋值，得到的都是数组类型
print(type(a))
b = np.array(range(10))
c = np.array([i**2 for i in range(10) if i % 2 == 0])


a = np.array([[1, 2, 3], ["a", "b", "c"]])  # 二维，全部转为字符串类型
b = np.array([[1, 2, 3, 4], ["a", "b", "c"]])  # 元素个数不一致，直接当作一维处理


# dtype强制转化类型
a = np.array([1, 2, 3], dtype="flaot")


# copy
a = np.array([1, 2, 3])
b = a  # 相当于引用
b = np.array(a)  # 另一个变量
