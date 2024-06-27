# 面试题 08.09. 括号
from typing import List


class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        def dfs(pre, left, right):
            if left > n or left < right:
                return
            if left + right == 2 * n:
                ans.append(pre)
                return
            dfs(pre + "(", left + 1, right)
            dfs(pre + ")", left, right + 1)
            return

        ans = []
        dfs("", 0, 0)
        return ans


# 官方法二
class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        if n == 0:
            return [""]
        ans = []
        for c in range(n):
            # generatParenthesis(c)的含义：产生c对括号不同组合出来的列表
            for left in self.generateParenthesis(c):
                for right in self.generateParenthesis(n - 1 - c):
                    ans.append("({}){}".format(left, right))  # n对()总能表示为n-1对()这种形式
        return ans
