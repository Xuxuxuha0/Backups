# 字典翻转输出
try:
    s = eval(input())
    key = list(s.keys())
    val = list(s.values())
    d = {}
    for i in range(len(key)):
        d[val[i]] = key[i]
    print(d)
except:
    print("输入错误")
