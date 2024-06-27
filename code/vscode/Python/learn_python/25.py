# 合法括号组合的生成(分支递推)
def f(str, left, right, pair):
    if left == pair and right == pair:
        ls.append(str)
    else:
        if left < pair:
            f(str + "(", left + 1, right, pair)
        if right < left:
            f(str + ")", left, right + 1, pair)


n = eval(input())
ls = []
f("", 0, 0, n)
print(ls)
