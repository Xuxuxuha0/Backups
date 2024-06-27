import pandas as pd

url = "https://raw.githubusercontent.com/justmarkham/DAT8/master/data/chipotle.tsv"
chipo = pd.read_csv(url, sep="\t")
chipo["item_price"] = chipo["item_price"].str.strip("$").astype(float)

# 先按item_name分组，再对每组的item_price求平均值
a = chipo.groupby("item_name")["item_price"].mean().head()
print(a)
print(type(a))

b = chipo.groupby("item_name").item_price
# 打印所有信息，例如均值，最大值，最小值
print(b.describe().head())
# 打印指定的信息
print(b.agg(["mean", "max", "min"]).head())
