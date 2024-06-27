import pandas as pd

d = {"name": ["zzz"], "age": [10]}  # 单值也要用列表
df = pd.DataFrame(d)
print(df)
