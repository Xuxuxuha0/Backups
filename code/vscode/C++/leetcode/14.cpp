// 122. 买卖股票的最佳时机 II
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        int ans = 0;
        for (int i = 1; i < n; i++)
            ans += max(0, prices[i] - prices[i - 1]); // 贪心法
        return ans;
    }
};