// 53. 最大子数组和
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int n = nums.size();
        int maxsum = nums[0];
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum = max(sum + nums[i], nums[i]); // 包含nums[i]的最大子段和
            maxsum = max(maxsum, sum);         // 最大子段和
        }
        return maxsum;
    }
};