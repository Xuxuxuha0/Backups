// 45. 跳跃游戏 II
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int jump(vector<int> &nums)
    {
        int n = nums.size(), maxPos = 0, end = 0, step = 0;
        // maxPos:最大能到达的下标   end:消耗step步数所能达到的最大下标   step:到达end所需步数
        for (int i = 0; i < n - 1; i++)
        {
            maxPos = max(maxPos, i + nums[i]);
            if (i == end) // 更新step的条件:i=pre_maxPos
            {
                end = maxPos;
                step++; // 此时能到达的区间[i+1,maxPos];要想跳到n-1,要求：i+1<=n-1 && maxPos>=n-1
            }
        }
        return step;
    }
};