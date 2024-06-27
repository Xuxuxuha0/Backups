import time
from datetime import date
from datetime import datetime
from datetime import timedelta

"""
date类 年月日
"""

print(date.today())  # 输出当前年月日的两种方法
print(date.fromtimestamp(time.time()))

now = date.today()
print(now)

print(now.replace(day=1))  # 把day变成1

print(now.isoweekday())  # 星期几

print(now.strftime("%Y.%m.%d"))  # 自定义格式


"""
datetime类 精确到秒
"""
now = datetime.now()
print(now)


"""
timedelta类 用于时间计算
"""
d = datetime.now()
d1 = d + timedelta(days=1)  # 明天
print(d1)
