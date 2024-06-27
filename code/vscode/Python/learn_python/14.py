"""
读取数据并绘制图案
数据接口:距离  转向(0左1右)  角度      rgb色彩
        300  ,     1   ,    144 ,  0.0 , 1.0 ,0.0
"""
import turtle as t

t.title("自动轨迹绘制")
t.setup(800, 600, 0, 0)
t.pencolor("red")
t.pensize(5)

# 数据读取处理
datals = []
f = open("Python\data")
for line in f:
    line = line.replace("\n", "")  # 去掉文件的换行符
    datals.append(list(map(eval, line.split(","))))  # map(函数a，函数b) 将函数b的每一个结果都执行函数a
f.close()  # 然后将一组数字变为列表,再成为datals列表中的一个元素

# 自动绘制
for i in range(len(datals)):
    t.pencolor(datals[i][3], datals[i][4], datals[i][5])
    t.fd(datals[i][0])
    if datals[i][1]:
        t.right(datals[i][2])
    else:
        t.left(datals[i][2])
