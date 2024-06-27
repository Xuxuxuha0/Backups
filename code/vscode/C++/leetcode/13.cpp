// 55. 跳跃游戏
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    bool canJump(vector<int> &nums)
    {
        int maxPos = 0, n = nums.size();
        for (int i = 0; i < n; i++)
            if (maxPos >= i)
                maxPos = max(maxPos, i + nums[i]);
        if (maxPos >= n - 1)
            return true;
        else
            return false;
    }
};