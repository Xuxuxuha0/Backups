dayup = pow(1.001, 2)
daydown = pow(0.999, 2)
print("向上:{:.2f},向下:{:.2f}".format(dayup, daydown))


def Dayup(df):
    dayup = 1
    for i in range(365):
        if i % 7 in [0, 6]:
            dayup *= 1 - 0.01
        else:
            dayup *= 1 + df
    return dayup


dayfacter = 0.01
while Dayup(dayfacter) < 37.78:
    dayfacter += 0.001
print(dayfacter)
