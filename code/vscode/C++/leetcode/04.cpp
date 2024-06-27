// 剑指 Offer 14- I. 剪绳子--动态规划
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    int cuttingRope(int n)
    {
        vector<int> dp(n + 1, 0);

        for (int i = 2; i <= n; i++)
        {
            int tmax = 0;
            for (int j = 1; j < i; j++)
            {
                int temp = max((i - j), dp[i - j]);
                temp *= j;
                tmax = max(tmax, temp);
            }

            dp[i] = tmax;
        }
        return dp[n];
    }
};
