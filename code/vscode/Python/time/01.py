import time

"""
时间戳1631155860和时间格式2021-08-21 15:23:45的关系:

时间戳( localtime(t) ) --> struct_time --> ( strftime(format,t) )时间格式

时间戳( mktime(t) ) <-- struct_time <-- ( strptime(t,format) )时间格式
"""
start = time.time()  # 获取开始时间

t = time.localtime()  # 获取当前时间戳
print(t)
print(t.tm_year, t.tm_mon, t.tm_mday)

print(time.strftime(("%Y-%m-%d"), time.localtime(1649666777)))  # 格式化显示1649666777对应的时间

t = time.strptime("2011-05-25 16:37:06", "%Y-%m-%d %X")
t2 = time.mktime(t) + 10 * 24 * 60 * 60  # 在t上加十天
print(time.strftime("%Y-%m-%d %X", t))
print(time.strftime("%Y-%m-%d %X", time.localtime(t2)))

"""
倒计时
"""
for i in range(6):
    print("\r", "%s 秒! " % (5 - i), end="")  # %r：在该行从头开始覆盖写
    time.sleep(1)  # 暂停一秒钟

end = time.time()  # 获取截止时间
print("\n", "SpendTime:", end - start, "s")
