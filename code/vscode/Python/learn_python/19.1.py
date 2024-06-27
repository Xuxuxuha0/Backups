n = int(input())  # 用户输入，一定不要忘记将读入的字符串转化为整型

if n <= 2:
    F = n
# 易得当n=1或2时，F(n)=n;

else:
    a = 1
    b = 2
    temp = 0
    # 初始化边界和临时变量temp

    for i in range(3, n + 1):  # 使用for循环来表示递推表达式
        temp = a + b
        a = b  # 这里将a后推了一位
        b = temp  # 这里将b后推了一位
    # 通过该循环可以完成递推出F(n)的任务，且存储在了temp中
    F = temp

print(F)  # 输出答案
