# tempconvert
tempstr = input("请输入带符号的温度值：")
if tempstr[-1] in ["F", "f"]:
    C = (eval(tempstr[0:-1]) - 32) / 1.8
    print("转换后的温度是：{:.2f}C".format(C))
elif tempstr[-1] in ["C", "c"]:
    F = eval(tempstr[0:-1]) * 1.8 + 32
    print("转换后的温度是：{:.2f}F".format(F))
else:
    print("输入格式错误")
