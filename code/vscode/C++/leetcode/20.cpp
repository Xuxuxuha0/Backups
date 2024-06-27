// 213. 打家劫舍 II
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
    int rangeRob(int start, int end, vector<int> nums)
    {
        int n = nums.size();
        vector<int> dp(n);
        dp[start] = nums[start];
        dp[start + 1] = max(nums[start], nums[start + 1]);
        for (int i = start + 2; i <= end; i++)
            dp[i] = max(nums[i] + dp[i - 2], dp[i - 1]);
        return dp[end];
    }

public:
    int rob(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1)
            return nums[0];
        if (n == 2)
            return max(nums[0], nums[1]);
        return max(rangeRob(0, n - 2, nums), rangeRob(1, n - 1, nums)); // 当选第一间，可rob的下标范围:[0,n-2];
    }
};