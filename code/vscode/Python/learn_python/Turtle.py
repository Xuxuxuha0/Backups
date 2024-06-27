import turtle  # from turtle import* 或 from turtle import t           import turtle as t

turtle.setup(
    650, 350, 200, 200
)  # setup(650,350,200,200)                                t.setup(650,350,200,200)
turtle.penup()
turtle.fd(-250)
turtle.pendown()
turtle.pensize(25)
turtle.pencolor(
    "purple"
)  # turtle.pencolor(0.63,0.13,0.94) 或 turtle.pencolor((0.63,0.13,0.94))
# 默认采用小数   用turtle.colormode(255) / turtle.colormode(1.0) 实现转换
turtle.seth(-40)  # seth的参数为绝对角度； turtle.left()/turtle.right()的参数为当前角度下转向的角度
for i in range(4):  # i取0--3     range(3,6) i取3--5
    turtle.circle(40, 80)  # 默认半径为正值，则圆心在左手侧
    turtle.circle(-40, 80)
turtle.circle(40, 80 / 2)
turtle.fd(40)
turtle.circle(16, 180)
turtle.fd(40 * 2 / 3)
turtle.done()  # 作用：绘制完成后需手动退出窗口
