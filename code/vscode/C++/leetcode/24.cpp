// 剑指 Offer II 102. 加减的目标值
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    int findTargetSumWays(vector<int> &nums, int target)
    // 设neg表示加负号的元素之和
    // 有：(sum-neg)-neg=target  ->  neg=(sum-target)/2;所以可得边界条件
    // 问题转化为:在nums数组中选几个元素之和等于neg的方案数
    {
        int sum = 0;
        for (auto i : nums)
            sum += i;

        int temp = sum - target;
        if (temp < 0 || temp % 2 != 0)
            return 0;

        int n = nums.size(), neg = temp / 2;
        vector<vector<int>> dp(n + 1, vector<int>(neg + 1, 0)); // dp[i][j]表示在nums[0,i-1]中得到元素之和为j的方案数

        dp[0][0] = 1; // 等于1表示不选任何元素；dp[i][0]不一定等于1，因为可能有元素等于0

        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= neg; j++)
            {
                dp[i][j] = dp[i - 1][j]; // 不选nums[j]
                if (j >= nums[i - 1])
                    dp[i][j] += dp[i - 1][j - nums[i - 1]]; // 选nums[j]
            }

        return dp[n][neg];
    }
};

int main()
{
    Solution p;
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(0);
    cout << p.findTargetSumWays(nums, 1);
}