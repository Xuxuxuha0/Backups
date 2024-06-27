import matplotlib.pyplot as plt
from matplotlib.image import imread


def show_image(image_path):
    img = imread(r"time\test.png")
    # 创建一个没有坐标轴和刻度的图像
    plt.imshow(img)
    # plt.xticks([])  # 去掉x轴
    # plt.yticks([])  # 去掉y轴
    plt.axis("off")  # 关闭坐标轴线的显示
    # 展示图像
    plt.show()


# 图像的相对地址
image_path = "time\test.png"

# 调用函数展示图像
show_image(image_path)
