// 剑指 Offer II 103. 最少的硬币数目
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        int n = coins.size();
        sort(coins.begin(), coins.end());

        vector<int> dp(amount + 1, -1); // dp[i]表示最少用多少硬币可以组成i
        dp[0] = 0;

        for (int i = 1; i <= amount; i++)
            for (int j = 0; j < n; j++)
            {
                int temp = i - coins[j];
                if (temp < 0)
                    break;
                if (dp[temp] != -1)
                {
                    if (dp[i] == -1)
                        dp[i] = 1 + dp[temp]; // 在dp[temp]的基础上再加一枚coins[j]硬币，相当于是无限个数
                    else
                        dp[i] = min(dp[i], 1 + dp[temp]);
                }
            }

        return dp[amount];
    }
};

int main()
{
    Solution p;
    vector<int> c{474, 83, 404, 3};
    cout << p.coinChange(c, 264);
}