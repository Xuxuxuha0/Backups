# 剑指 Offer II 103. 最少的硬币数目

# typing模块：用于类型说明
from typing import List


class Solution:
    def coinChange(self, coins: List[int], amount: int) -> int:
        dp = [float("inf")] * (amount + 1)  # float("inf")表示正无穷  float("-inf")表示负无穷
        dp[0] = 0

        for coin in coins:
            for x in range(coin, amount + 1):
                dp[x] = min(dp[x], dp[x - coin] + 1)
        return dp[amount] if dp[amount] != float("inf") else -1


p = Solution()
print(p.coinChange([1, 2, 5], 11))
