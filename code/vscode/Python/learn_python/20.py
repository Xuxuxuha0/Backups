n = eval(input())
count = 0
for i in range(2, 100000):
    flag = True
    str1 = str(i)
    str2 = str1[::-1]
    if str2 == str1:
        continue
    else:
        for j in range(2, i // 2 + 1):
            if i % j == 0:
                flag = False
                break
            else:
                continue
        if flag:
            ii = eval(str2)
            for jj in range(2, ii // 2 + 1):
                if ii % jj == 0:
                    flag = False
                    break
                else:
                    continue
        if flag:
            print("{}".format(i), end=" ")
            count += 1
            if count == n:
                break
        flag = True
