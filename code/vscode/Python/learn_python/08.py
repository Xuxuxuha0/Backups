# 递归反转字符串


def rvs(s):
    # global s
    if s == "":
        return s
    else:
        return rvs(s[1:]) + s[0]


print(rvs("123456"))
