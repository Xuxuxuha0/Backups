import pandas as pd
import time

"""
Timestamp
Timedelta
"""

t = pd.Timestamp("2022-01-10 12")
print(t)

# 倒退一天
print(t + pd.Timedelta(-1, "D"))

# 设置时间间隔
dt = pd.Timedelta(days=5, minutes=50, seconds=20)
print(t + dt)

# 转换成秒相加,需要用unit='s'
print(pd.Timestamp(time.time() + dt.total_seconds(), unit="s"))


"""
date_range()
"""
print(
    pd.date_range(
        start="2023-2-21",
        end="2023-3-21",
        periods=3,
    )
)  # 随机生成这个区间的三个数据
print(
    pd.date_range(
        start="2023-2-21",
        end="2023-3-21",
        freq="W-MON",
    )
)  # 生成这个区间的日期，要求全部是MON(星期一)
