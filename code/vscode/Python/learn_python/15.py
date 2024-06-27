import wordcloud
txt="life is short,you need python"
c= wordcloud.WordCloud(background_color='white')    #配置对象并配置背景颜色 
c.generate(txt)  #加载文本
c.to_file("py.png")  #输出文件(自动保存在code文件夹中)