##把需要转化的xlsx文件放在pycharm项目文件目录里
import pandas as pd


def xlsx_to_csv_pd():
    data_xls = pd.read_excel(
        "D:\下载2\大二下课件\数据库课件\openGauss\实验4\附件2 基础数据\教师信息.xlsx", index_col=0
    )  # 输入xlsx文件名
    data_xls.to_csv(r"D:\下载2\teacher.csv", encoding="utf-8")  # 输出csv文件名


if __name__ == "__main__":
    xlsx_to_csv_pd()
