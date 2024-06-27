n = int(input())
if n <= 2:
    F = n
else:
    temp_list = [0, 1, 2]
    for i in range(3, n + 1):
        temp_list.append(temp_list[-1] + temp_list[-2])
        F = temp_list[-1]
print(F)
