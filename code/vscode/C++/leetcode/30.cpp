// 241. 为运算表达式设计优先级
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    vector<int> diffWaysToCompute(string expression)
    {
        //+：-1    -：-2   *：-3
        vector<int> ops; // 存储转换后的表达式
        int n = expression.size();

        for (int i = 0; i < n;) // 先转换为数字表达式
        {
            if (!isdigit(expression[i]))
            {
                switch (expression[i])
                {
                case '+':
                    ops.push_back(-1);
                    break;
                case '-':
                    ops.push_back(-2);
                    break;
                case '*':
                    ops.push_back(-3);
                    break;
                }
                i++;
            }
            int x = 0;
            while (i < n && isdigit(expression[i]))
            {
                x = x * 10 + expression[i] - '0';
                i++;
            }
            ops.push_back(x);
        }

        n = ops.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n)); // dp[i][j]表示:ops[i,j]能得到哪些不同值，类型为vector<int>

        for (int i = 0; i < n; i += 2)
            dp[i][i] = {ops[i]};

        for (int end = 2; end < n; end += 2)
            for (int start = end - 2; start >= 0; start -= 2)
                // dp[start][end]={ dp[start][divide][i] ops[divide+1] dp[divide+2][end][j] }
                for (int divide = start; divide < end; divide += 2)
                {
                    auto left = dp[start][divide];
                    auto right = dp[divide + 2][end];
                    for (auto num1 : left)
                        for (auto num2 : right)
                        {
                            switch (ops[divide + 1])
                            {
                            case -1:
                                dp[start][end].push_back(num1 + num2);
                                break;
                            case -2:
                                dp[start][end].push_back(num1 - num2);
                                break;
                            case -3:
                                dp[start][end].push_back(num1 * num2);
                                break;
                            }
                        }
                }

        return dp[0][n - 1];
    }
};