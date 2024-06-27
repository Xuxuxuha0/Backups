# 第三方库的自动安装脚本
import os

libs = {"numpy", "matplotlib"}  # 第三方库名
try:
    for lib in libs:
        os.system("pip install" + lib)
    print("successful")
except:
    print("fail")
