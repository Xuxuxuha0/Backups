import jieba, wordcloud

txt = "程序设计语言是计算机的一种交互体系"
w = wordcloud.WordCloud(width=1000, font_path="msyh.ttc", height=700)
w.generate(" ".join(jieba.lcut(txt)))
w.to_file("py2.png")
