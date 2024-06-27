// 152. 乘积最大子数组
#include <iostream>
#include <vector>
#include <algorithm> //max_element():返回最大值的迭代器，适用于vector和数组
using namespace std;

class Solution
{
public:
    int maxProduct(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> dp_max(n), dp_min(n); // dp_max[i]表示包含nums[i]的最大连乘积

        dp_max[0] = dp_min[0] = nums[0];

        for (int i = 1; i < n; i++)
        {
            dp_max[i] = max(dp_min[i - 1] * nums[i], max(dp_max[i - 1] * nums[i], nums[i]));
            dp_min[i] = min(dp_min[i - 1] * nums[i], min(dp_max[i - 1] * nums[i], nums[i]));
        }

        return *max_element(dp_max.begin(), dp_max.end());
    }
};