def getnum():  # 输入数字
    nums = []
    inumstr = input("请输入数字(只输入回车退出)")
    while inumstr != "":  # 输入的为回车就退出
        nums.append(eval(inumstr))
        inumstr = input("请输入数字(只输入回车退出)")
    return nums


def aver(nums):
    s = 0.0
    for i in nums:
        s += i
    return s / len(nums)


def media(nums):  # 求中位数
    sorted(nums)  # 对列表排序
    size = len(nums)
    if size % 2 == 0:
        med = (nums[size // 2 - 1] + nums[size // 2]) / 2
    else:
        med = nums[size // 2]
    return med


num2 = getnum()
print(num2)
print("平均值:{} 中位数:{}".format(aver(num2), media(num2)))
