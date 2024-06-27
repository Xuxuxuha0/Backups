// 139. 单词拆分
#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        set<string> WordDictSet;
        for (auto word : wordDict) // 先创建一个有序的查找表
            WordDictSet.insert(word);

        int lenth = s.size();

        vector<bool> dp(lenth + 1, false); // dp[j]=true表示s[0..j-1]可以被划分
        dp[0] = true;                      // 一定要预留一个dp[0]表示空串

        for (int i = 1; i <= lenth; i++) // 判断s[0..i-1]能否被划分
            for (int j = 0; j < i; j++)  // 把s[0..i-1]划分为s[0..j-1]和s[j..i]
            {
                if (dp[j] && WordDictSet.find(s.substr(j, i - j)) != WordDictSet.end())
                {
                    dp[i] = true;
                    break;
                }
            }

        return dp[lenth];
    }
};
int main()
{
    Solution p;
    vector<string> wordDict = {"leet", "code"};
    cout << p.wordBreak("leetcode", wordDict);
}