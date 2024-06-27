import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['Microsoft YaHei']  # 设置微软雅黑字体

a = [26, 82, 46, 40, 6]
s = sum(a)
for i in range(4):
    a[i + 1] += a[i]
a = [x / s * 312000 for x in a]
print(a)

# 设置横坐标的标签
labels = ['需求分析', '系统设计', '系统编码', '系统测试', '验收交付']

plt.plot(range(len(labels)), a, marker='o')
plt.title('成本基线')
plt.xlabel('阶段')
plt.ylabel('成本')
plt.grid(True)

# 设置 x 轴的标签
plt.xticks(range(len(labels)), labels)

plt.rcParams['xtick.direction'] = 'in'  # 刻度线内向
plt.rcParams['ytick.direction'] = 'in'

plt.show()
