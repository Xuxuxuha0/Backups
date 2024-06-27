// 剑指 Offer 60. n个骰子的点数
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<double> dicesProbability(int n)
    {
        vector<double> dp(6, 1.0 / 6.0); // 初始化为1个骰子的概率表
        for (int i = 2; i <= n; i++)     // i个骰子
        {
            vector<double> temp(5 * i + 1, 0);  // 用i个骰子的点数区间：[i,6i],共有5i+1种点数
            for (int j = 0; j < dp.size(); j++) // 用i-1个骰子产生的第j种点数去更新用i个骰子产生j+1，j+2...j+6这几种点数，因为i个骰子可以看作i-1个骰子再加上第i个骰子的点数
            {
                for (int k = 0; k < 6; k++)
                    temp[j + k] += dp[j] / 6.0; // temp[0]表示点数为i出现的概率，dp[0]表示点数为i-1出现的概率，所以k从0开始取；则点数为i-1的情况再加上第i颗骰子掷出1的情况，即可产生点数i；点数为i-1的情况再加上第i颗骰子掷出2的情况，即可产生点数i+1；以此类推...
            }
            dp = temp;
        }
        return dp;
    }
};