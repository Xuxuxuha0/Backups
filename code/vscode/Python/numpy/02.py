import numpy as np

"""
等差数列
linspace(start,stop,num,endpoint,retstep,dtype) 
把[start,stop]分成num份
endpoint=False,则不包含stop  默认True,包含
"""
a = np.linspace(1, 10, 10)


"""
等比数列
logspace(start,stop,num,endpoint,base,dtype)
把[start,stop]分成num份,并计算pow(base,i)
base默认为10
"""
a = np.logspace(0, 3, 4, base=2)


"""
全0数列
zeros(shape,dtype=float,roder="c")
shape定义了是几维的
"""
a = np.zeros(5)  # 5列
c = np.zeros((3, 2))  # 3行2列
a = np.zeros((2, 2, 3))  # 2块2行3列
b = np.zeros_like(c)  # 根据c的形状和类型创建0数组


"""
全1数列,同上
ones(...)
ones_like
"""


"""
.ndim     返回维度数量
.shape    返回数组维度, 元组
.size     返回元素个数         len(a)只能返回a的最大单位的个数
.dtype    元素类型
.itemsize 元素大小，字节
"""

a = np.array([[1, 2, 3], [4, 5, 6]])  # shape还可以用于调整数组形状
a.shape = (3, 2)
print(a)


"""
reshape(shape)
resize()
"""
a = np.arange(20)
b = a.reshape((4, 5))  # 改为4行5列
print(a, "\n", b)
b[0] = 100  # reshape之后，a和b指向同一个内容，所以会相关联
print(a, "\n", b)
c = np.resize(a, (4, 6))  # 允许c的范围比a大，并重复填充多余部分

# c.resize((4, 7), refcheck=False)  # 多余部分用0填充，error！
