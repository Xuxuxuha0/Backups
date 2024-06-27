# 剑指 Offer II 104. 排列的数目
from typing import List


class Solution:
    def combinationSum4(self, nums: List[int], target: int) -> int:
        nums.sort()  # 一般用于list类型
        dp = [1] + [0] * target  # 创建一个初始化的列表
        for i in range(1, target + 1):
            for num in nums:
                if num > i:
                    break
                dp[i] += dp[i - num]
        return dp[target]
