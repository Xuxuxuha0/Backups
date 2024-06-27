ab = int(input())
symbol = int(input())
prime_list = []


def is_prime(n):
    if n in prime_list:
        return True
    if n < 2 or n % 2 == 0 or n % 3 == 0:
        return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            return False
    else:
        prime_list.append(n)
        return True


for i in range(2, int(ab**0.5) + 1):
    a = max(i, ab // i)
    b = min(i, ab // i)
    if a * b == ab and is_prime(a) and is_prime(b):
        break
print("WHUT{}{}".format(a, b))


id = str(a) + str(b)
num = 0
id_length = len(id)


def getLeft(id, i):
    if i == 0:
        return 0
    return int(id[: i - 1 + 1])


def getRight(id, i):
    if i == len(id) - 1:
        return 0
    return int(id[i + 1 :])


def getI(id, i):
    return int(id[i])


for i in range(0, id_length):
    if i == 0:
        if int(id[i]) > symbol:
            num += 10 ** (id_length - 1)
        else:
            num += 0
    elif i == id_length - 1:
        num += int(id) // 10
        if getI(id, i) >= symbol:
            num += 1
    else:
        if getI(id, i) > symbol:
            addition = (getLeft(id, i) + 1) * 10 ** (id_length - i - 1)
        elif getI(id, i) == symbol:
            addition = (
                (getLeft(id, i)) * 10 ** (id_length - i - 1) + getRight(id, i) + 1
            )
        else:
            addition = (getLeft(id, i)) * 10 ** (id_length - i - 1)
        num = num + addition
print(num)
