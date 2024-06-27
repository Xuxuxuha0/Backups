// 221. 最大正方形
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int maximalSquare(vector<vector<char>> &matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0)); // dp[i][j]表示以[i,j]为右下角的最大正方形边长

        int maxSide = 0; // 最大边长
        for (int i = 0; i < m; i++)
            if (matrix[i][0] == '1')
            {
                dp[i][0] = 1;
                maxSide = 1;
            }
        for (int j = 0; j < n; j++)
            if (matrix[0][j] == '1')
            {
                dp[0][j] = 1;
                maxSide = 1;
            }

        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
            {
                if (matrix[i][j] == '0')
                    dp[i][j] = 0;
                else
                    dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1; // 神奇的转移方程
                maxSide = max(maxSide, dp[i][j]);
            }

        return maxSide * maxSide;
    }
};