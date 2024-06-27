// 剑指 Offer II 104. 排列的数目
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int combinationSum4(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        vector<unsigned long long> dp(target + 1, 0);
        // dp[i]表示和为i的方案数
        // 设某种方案的最后一个数字为num,有:dp[i]+=dp[i-num]。遍历num,很好的完成了所有的排列。

        dp[0] = 1; // 和为0时，唯一的方案是不选

        for (int i = 1; i <= target; i++)
            for (auto num : nums)
            {
                if (num > i)
                    break;
                dp[i] += dp[i - num];
            }
        return dp[target];
    }
};

int main()
{
    Solution p;
    vector<int> nums{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 111};
    cout << p.combinationSum4(nums, 999);
}