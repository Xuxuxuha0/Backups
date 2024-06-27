# 矩阵的螺旋排列(妙用反转)
def spiralorder(matrix2):
    ls = []
    try:
        while True:
            ls += matrix2.pop(0)  # 列表相加
            for i in matrix2:
                ls.append(i.pop())
            ls += matrix2.pop()[::-1]
            for i in matrix2[::-1]:
                ls.append(i.pop(0))
    except:
        return ls


matrix = eval(input())
res = spiralorder(matrix)
print(res)
