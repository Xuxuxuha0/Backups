import pandas as pd

url = "https://raw.githubusercontent.com/justmarkham/DAT8/master/data/chipotle.tsv"

chipo = pd.read_csv(url, sep="\t")

"""
注释(取消)的方法：
选中代码后
""" """: shift+alt+a
#: ctrl+/
"""

# clean the item_price column and transform it in a float
prices = [float(value[1:-1]) for value in chipo.item_price]
# reassign the column with the cleaned prices
chipo.item_price = prices

# 上述方法等价于
# chipo["item_price"] = chipo["item_price"].str.strip("$").astype(float)


print(chipo.columns)

# 取出这两项，根据item_name分组，相同的求和
obj1 = chipo[["item_name", "item_price"]].groupby(["item_name"]).sum()
# 按照price重排序
obj1.sort_values(["item_price"], ascending=False, inplace=True)
print(obj1.head())

# item_name的种类
print(chipo["item_name"].nunique())
# 统计每种name的个数并排序
print(chipo["item_name"].value_counts().head())
# 总的数量
print(chipo["quantity"].sum())
# 总收入
print((chipo["item_price"] * chipo["quantity"]).sum())

# 把item_name在该列表中的行取出来
tempLoc = chipo.loc[chipo.item_name.isin(["Chicken Bowl", "Steak Burrito"])]
# 取出这两列
print(tempLoc[["item_name", "item_price"]].head())
# 上述方法等价于
print(
    chipo.loc[
        chipo.item_name.isin(["Chicken Bowl", "Steak Burrito"]),
        ["item_name", "item_price"],
    ].head()
)
