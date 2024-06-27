import math


# 判断是否为"素数"
def is_prime_number(number):
    if number <= 1:
        return False
    elif number == 2 or number == 3:
        return True
    else:
        for i in range(2, int(math.sqrt(number)) + 1):
            if number % i == 0:
                return False
        return True


# 分解素数的乘积
def product_disintegrate(number):
    for i in range(2, number):
        result = number // i
        if number == i * result:
            if is_prime_number(i) and is_prime_number(result):
                return [max(i, result), min(i, result)]


# 输出ID
def print_ID(number, special):
    result = product_disintegrate(number)
    id_number = str(result[0]) + str(result[1])
    id_letter = "WHUT"
    print(id_letter + id_number)

    sum = 0
    for i in range(1, int(id_number) + 1):
        sum += str(i).count(str(special))
    print(sum)


number = eval(input())
special = eval(input())
print_ID(number, special)
