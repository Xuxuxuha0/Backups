import jieba,wordcloud
from imageio import imread
mk=imread("D:\下载2\pre成品\presentation素材\6.png")
f=open("D:\下载2\习概\徐浩+1120213459.docx","r",encoding="utf-8")
t=f.read()
f.close()
ls=jieba.lcut(t)  #
txt=" ".join(ls)
w=wordcloud.WordCloud(font_path="msyh.ttc",mask=mk,width=1000,height=700,background_color="white")
w.generate(txt)
w.to_file("py3.png")