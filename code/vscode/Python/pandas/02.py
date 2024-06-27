import numpy as np
import pandas as pd


data = np.array(["a", "b", "c", "d"])
s = pd.Series(data, index=[1, 3, 5, 7])  # 自定义标签
print(s)


a = {"a": 1, "b": 2, "c": 3}
b = pd.Series(a, index=["c", "b", "z"])  # 当字典中的键在index中找不到时,数据用NaN来填充
print(b)


b.name = "test"  # 给series写个名字，便于后期用名字索引


c = np.arange(1, 6)
d = pd.Series(c)
d[1] = 50  # 由于d是c拷贝的，所以它们相关联，都会被改值(要求c是ndarry和series才可以关联)
