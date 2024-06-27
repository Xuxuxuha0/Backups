n = eval(input())  # 有错 见c++ 163
count = 0


def recur(x):
    global count
    for i in range(1, 2):
        if i == x:
            count += 1
        elif i < x:
            recur(x - i)
    return count


print(recur(n))
