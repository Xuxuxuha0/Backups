import pandas as pd


"""
str.操作
"""

s = pd.Series(["C", "Python\t", "\tC++", "125 10 ", " 123*25*"])

# 全部转为小写
print(s.str.lower())

# 把每个字符串两边的\t取掉;默认取消的不止\t;也可以自己设置值
print(s.str.strip())

# 分割每个字符串
# 不带参数：先执行strip()，再以" "来分割
print(s.str.split())
# 直接以*分割
print(s.str.split("*"))

# 以_连接每个字符串
print(s.str.cat(sep="_"))

# 包含
print(s.str.contains("1"))
# 取出包含1的值
print(s[s.str.contains("1")])

# 替换,把s中所有1都换为2
print(s.str.replace("1", "2"))

# 计数
print(s.str.count("Python"))

# 以...开始/结束
print(s.str.startswith(" "))
print(s.str.endswith("*"))

# 是否包含1
print(s.str.find("1"))
