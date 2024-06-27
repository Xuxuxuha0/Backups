import pandas as pd

chunk = pd.read_csv(
    r"Python\pandas\file\03.csv",
    iterator=True,
)  # chunk为迭代器
print(chunk.get_chunk(2))  # 取两行数据，且chunk指针会移动两行
print(chunk.get_chunk(100))  # 取剩下的


chunk = pd.read_csv(
    r"Python\pandas\file\03.csv",
    iterator=True,
    chunksize=2,  # 分块来读取，每块读两行
)
print(chunk.get_chunk())
print(chunk.get_chunk())
