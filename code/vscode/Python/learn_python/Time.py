import time

# 获取时间
print(time.time())
print(time.ctime())
print(time.gmtime())

# 时间格式化   time.strftime()   time.strptime()

# 计时  当前时间：time.perf_counter()      间隔时间：time.sleep()

# 进度条
scale = 50
print("执行开始".center(scale // 2, "-"))
start = time.perf_counter()  # 计时器
for i in range(scale + 1):
    a = "*" * i
    b = "." * (scale - 1)
    c = (i / scale) * 100
    dur = time.perf_counter() - start  # 所用的时间
    print(
        "\r{:^3.0f}%[{}->{}]{:.2f}s".format(c, a, b, dur), end=""
    )  # print 默认最后是换行符    ,end="x" 中的x可以替换掉换行符
    time.sleep(0.1)
print("\n" + "执行结果".center(scale // 2, "-"))
