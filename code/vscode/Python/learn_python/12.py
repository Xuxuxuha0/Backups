# 三国演义人物出场次数统计
import jieba  # 未安装

txt = open("threekingdoms.txt", "r", encoding="utf-8").read()
excludes = {"将军", "却说", "荆州", "二人", "不可"}
words = jieba.lcut(txt)
counts = {}

for word in words:
    if len(word) == 1:
        continue
    elif word == "诸葛亮" or word == "孔明曰":  # 一致化
        rword = "孔明"
    elif word == "关公" or word == "云长":
        rword = "关羽"
    else:
        rword = word
    counts[rword] = counts.get(rword, 0) + 1

for word in excludes:  # 删掉错误的
    del counts[word]

items = list(counts.items())
items.sort(key=lambda x: x[1], reverse=True)

for i in range(10):
    word, count = items[i]
    print("{0:<10}{1:>5}".format(word, count))
