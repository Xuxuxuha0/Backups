// 剑指 Offer II 092. 翻转字符
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
    int minFlipsMonoIncr(string s)
    {
        int dp0 = 0, dp1 = 0;
        // dp0表示把当前子串变为0结尾的合法子串，所需要的最少次数。此时要求子串全部变为0，所以dp0其实是一个常数。
        // dp1表示把当前子串变为1结尾的合法子串，所需要的最少次数。
        for (char c : s)
        {
            int temp0 = dp0, temp1 = min(dp0, dp1);
            // temp0即将表示由上一个子串加上c，变成合法的0结尾的子串所需的次数。
            // temp0即将表示由上一个子串加上c，变成合法的1结尾的子串所需的次数。由于上一个子串可以是0结尾，也可以是1结尾，所以需要比较。
            if (c == '0')
                temp1++; // 当前字符为0，temp1表示把当前字符变为1，则需要反转
            else
                temp0++;
            dp0 = temp0;
            dp1 = temp1;
        }
        return min(dp0, dp1);
    }
};