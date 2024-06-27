// 131. 分割回文串
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution
{
private:
    // 相当于该class里面的全局变量
    vector<vector<int>> dp;
    vector<vector<string>> ans;
    vector<string> temp;
    int n;

public:
    void traceback(string s, int i) // 从下标i开始寻找一个回文串
    {
        if (i == n)
        {
            ans.push_back(temp);
            return;
        }
        for (int j = i; j < n; j++)
            if (dp[i][j]) // 判断s[i]...s[j]是否是回文串
            {
                temp.push_back(s.substr(i, j - i + 1));
                traceback(s, j + 1);
                temp.pop_back();
            }
    }
    vector<vector<string>> partition(string s)
    {
        n = s.size();
        dp.assign(n, vector<int>(n, 1));

        // 预处理:dp[i][j]=1表示s[i]...s[j]是回文串
        for (int j = 1; j < n; j++)
            for (int i = j - 1; i >= 0; i--)
            {
                if (s[i] != s[j])
                    dp[i][j] = 0;
                else if (j - i > 2)
                    dp[i][j] = dp[i + 1][j - 1];
            }

        traceback(s, 0);
        return ans;
    }
};