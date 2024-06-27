import pandas as pd

df = pd.read_csv(r"Python\pandas\file\04.csv")
print(df)

print(df.info())  # 输出df的概要
print(df.isnull())  # 空的为True


"""
删除空行/列
df.dropna(axis=0,how='any',thresh=None,subset=None,inplace=False)
axis:0表示考虑是否删除该行 
how:any表示有空就删除 all表示全空才删除
thresh:仅保留至少有多少个非空的数据的行/列
subset:某某列中有空,就删除空元素所在的行/列
"""
print(df.dropna(thresh=1))
print(df.dropna(subset=["gender"]))


"""
填充空行/列
df.fillna(value=None,method=None,axis=None,inplace=False,limit=None,downcast=Nnoe)
value:指定填充的值
method:ffill从上往下复制  bfill相反
limit:最多填充几个
"""
print("-------------------")
print(df)
print(df.fillna(method="ffill"))
print(df.fillna(method="bfill"))
v = {"id": "002", "name": "张良", "gender": "女"}
print(df.fillna(value=v))  # value还可以用于两个同type的df的填充
print(df.fillna(value=100, limit=1))  # 每列只填充1个
