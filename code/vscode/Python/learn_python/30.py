import random

random.seed(10)
f = open("test1.txt", "r", encoding="utf-8")
ls = []
for i in f.readlines():  # 把文件变为文档，再变为列表，再变为字典
    i = i.strip("\n")
    j = i.split(",")
    ls.append(j)
dic = dict(ls)
ls = random.sample(dic.keys(), 1)  # 如何从字典中随机产生一个键值对（随机键）
key = "".join(ls)  # 列表转字符串
val = dic[key]
d = {}
d[key] = val
print(d)
