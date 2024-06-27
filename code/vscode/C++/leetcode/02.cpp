// 5. 最长回文子串--动态规划
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    string longestPalindrome(string s)
    {
        int n = s.size();
        if (n < 2)
            return s;

        vector<vector<int>> dp(n, vector<int>(n)); // n*n的二维数组

        for (int i = 0; i < n; i++) // 初始化，长度为1的一定是回文串
            dp[i][i] = true;

        int maxLen = 1;
        int begin = 0;
        for (int Len = 2; Len < n; Len++)
        {
            for (int i = 0; i < n; i++) // j-i+1=Len
            {
                int j = Len + i - 1;

                if (j >= n)
                    break;

                if (s[i] != s[j])
                    dp[i][j] = false;
                else
                {
                    if (j - i < 3)
                        dp[i][j] = true;
                    else
                        dp[i][j] = dp[i + 1][j - 1]; // 回文串：去掉两端回文的性质不变
                }

                if (dp[i][j] == true && Len > maxLen)
                {
                    maxLen = Len;
                    begin = i;
                }
            }
        }
        return s.substr(begin, maxLen);
    }
};