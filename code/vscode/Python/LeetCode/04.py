# 241. 为运算表达式设计优先级
from typing import List

ADDITION = -1
SUBTRACTION = -2
MULTIPLICATION = -3


class Solution:
    def diffWaysToCompute(self, expression: str) -> List[int]:
        ops = []
        i, n = 0, len(expression)

        while i < n:
            if expression[i].isdigit():
                x = 0
                while i < n and expression[i].isdigit():
                    x = x * 10 + int(expression[i])
                    i += 1
                ops.append(x)
            else:
                if expression[i] == "+":
                    ops.append(ADDITION)
                elif expression[i] == "-":
                    ops.append(SUBTRACTION)
                else:
                    ops.append(MULTIPLICATION)
                i += 1

        n = len(ops)
        dp = [[[] for _ in range(n)] for _ in range(n)]  # 二维、三维申请n个单位的空间

        for i, x in enumerate(ops):  # i返回下标，x返回对应的值
            dp[i][i] = [x]

        for end in range(2, n, 2):
            for start in range(end - 2, -1, -2):  # end-2开始，0结束，-2为增量
                for divide in range(start, end, 2):
                    left = dp[start][divide]
                    right = dp[divide + 2][end]
                    for num1 in left:
                        for num2 in right:
                            if ops[divide + 1] == ADDITION:
                                dp[start][end].append(num1 + num2)
                            elif ops[divide + 1] == SUBTRACTION:
                                dp[start][end].append(num1 - num2)
                            else:
                                dp[start][end].append(num1 * num2)

        return dp[0][n - 1]
