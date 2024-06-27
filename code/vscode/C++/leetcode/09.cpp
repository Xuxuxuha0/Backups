// 剑指 Offer II 020. 回文子字符串的个数
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class Solution
{
public:
    int countSubstrings(string s)
    {
        int n = s.size();

        vector<vector<int>> dp(n, vector<int>(n, 1)); // 全部初始化为1，下面只需考虑为0的情况
        // dp[i][j]表示s[i]...s[j]的子串是否为回文
        // dp[i][j]=1             j-i<=2&&s[i]==s[j]
        // dp[i][j]=0             s[i]!=s[j]
        // dp[i][j]=dp[i+1][j-1]  s[i]==s[j]

        int cnt0 = 0;

        for (int j = 1; j < n; j++)
            for (int i = j - 1; i >= 0; i--)
            {
                if (s[i] != s[j])
                    dp[i][j] = 0;
                else if (j - i > 2)
                    dp[i][j] = dp[i + 1][j - 1];

                if (dp[i][j] == 0)
                    cnt0++;
            }

        int cnt1 = (n + 1) * n / 2 - cnt0;
        return cnt1;
    }
};

int main()
{
    Solution p;
    cout << p.countSubstrings("fdsklf");
}