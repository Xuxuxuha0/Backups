// 198. 打家劫舍
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int rob(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> dp(n); // dp[i]表示从nums[0..i]能获得的最大值
        dp[0] = nums[0];
        if (n == 1)
            return dp[0];
        dp[1] = max(nums[0], nums[1]);

        for (int i = 2; i < n; i++)
            dp[i] = max(nums[i] + dp[i - 2], dp[i - 1]);

        return dp[n - 1];
    }
};

class Solution // 优化为滚动数组
{
public:
    int rob(vector<int> &nums)
    {
        int n = nums.size();
        int dp1 = nums[0], dp2, dp3;
        if (n == 1)
            return dp1;
        dp3 = dp2 = max(nums[0], nums[1]);

        for (int i = 2; i < n; i++)
        {
            dp3 = max(nums[i] + dp1, dp2);
            dp1 = dp2;
            dp2 = dp3;
        }

        return dp3;
    }
};