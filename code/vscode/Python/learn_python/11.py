# 整理文本的单词及出现次数


def gettext():  # 将文本变为小写,并将特殊字符变为空格
    txt = open("hamlet.txt", "r").read()
    txt = txt.lower()
    for ch in '!"#$%()*+,-./:;<=>?@[\\]^_`{|}~':
        txt = txt.replace(ch, " ")
    return txt


hamlettxt = gettext()  # 得到归一化的文本

words = hamlettxt.split()  # 直接将文本根据空格转换为列表类型

counts = {}  # 字典类型
for word in words:
    counts[word] = counts.get(word, 0) + 1  # 记录word出现的次数

items = list(counts.items())  # 将所有的键值对返回并构建列表类型

items.sort(key=lambda x: x[1], reverse=True)  # 列表的排序方法

for i in range(10):  # 输出出现次数最多的十个单词
    word, count = items[i]
    print("{0:<10}{1:>5}".format(word, count))
