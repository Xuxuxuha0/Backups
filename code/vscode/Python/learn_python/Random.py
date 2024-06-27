import random

random.seed(10)  # 种子，对应一个随机序列
a = random.random()  # 产生0~1随机数
b = random.random()
print(a, b)

c = random.randint(10, 100)  # 产生10--100的整数
d = random.randrange(10, 100, 10)  # 产生10开始，以10为步长，且小于100的随机整数
e = random.getrandbits(16)  # 产生16比特的随机整数
d = random.uniform(10, 100)  # 产生10--100的随机小数
f = random.choice([1, 2, 3, 4, 5])  # 随机选择一个数
s = [1, 2, 3, 4, 5]
random.shuffle(s)  # 打乱s序列
