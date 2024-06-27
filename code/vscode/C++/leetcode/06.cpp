// 97. 交错字符串
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    bool isInterleave(string s1, string s2, string s3)
    {
        int n = s1.size(), m = s2.size(), t = s3.size();

        if (n + m != t)
            return false;

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, false));
        // dp[i][j]表示用s1的前i个字符和s2的前j个字符能否构成s3的前i+j个字符
        // dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]) || (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
        dp[0][0] = true;

        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++)
            {
                int p = i + j - 1; // s3第i+j个字符的下标
                if (i > 0)
                    dp[i][j] |= (dp[i - 1][j] && s1[i - 1] == s3[p]); // 都为0，才等于0
                if (j > 0)
                    dp[i][j] |= (dp[i][j - 1] && s2[j - 1] == s3[p]);
            }

        return dp[n][m];
    }
};

class Solution // 优化为一维
{
public:
    bool isInterleave(string s1, string s2, string s3)
    {
        int n = s1.size(), m = s2.size(), t = s3.size();

        if (n + m != t)
            return false;

        vector<int> dp(m + 1, false);
        dp[0] = true;

        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++)
            {
                int p = i + j - 1;
                if (i > 0)
                    dp[j] = (dp[j] && s1[i - 1] == s3[p]); // 注意变换
                if (j > 0)
                {
                    if (i > 0)
                        dp[j] |= (dp[j - 1] && s2[j - 1] == s3[p]); // 当i>0,说明dp[j]就是计算后的dp[i][j]
                    else
                        dp[j] = (dp[j - 1] && s2[j - 1] == s3[p]); // 否则,dp[j]应该是初始化的dp[i][j],即false
                }
            }

        return dp[m];
    }
};