def f(m2, n2):
    num1 = math.factorial(m2 + n2)
    num2 = math.factorial(m2)
    num3 = math.factorial(n2)
    count2 = int(num1 // (num2 * num3))  # 为什么要用//？
    return count2


import math

m = eval(input()) - 1
n = eval(input()) - 1
count = f(m, n)
print(count)
