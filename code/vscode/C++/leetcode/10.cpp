// 22. 括号生成
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution // 回溯法
{
    void traceback(vector<string> &ans, string &cur, int left, int right, int n)
    {
        if (cur.size() == 2 * n)
        {
            ans.push_back(cur);
            return;
        }
        if (left < n)
        {
            cur.push_back('(');
            traceback(ans, cur, left + 1, right, n);
            cur.pop_back(); // 回溯
        }
        if (right < left)
        {
            cur.push_back(')');
            traceback(ans, cur, left, right + 1, n);
            cur.pop_back(); // 回溯
        }
    }

public:
    vector<string> generateParenthesis(int n)
    {
        vector<string> ans;
        string current;
        traceback(ans, current, 0, 0, n);
        return ans;
    }
};