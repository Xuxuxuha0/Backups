// 剑指 Offer II 093. 最长斐波那契数列
#include <iostream>
#include <vector>
#include <unordered_map> //与map的区别:不会对键值对排序
using namespace std;

class Solution
{
public:
    int lenLongestFibSubseq(vector<int> &arr)
    {
        unordered_map<int, int> m;
        int n = arr.size();
        for (int i = 0; i < n; i++) // 创建一个以值为索引，下标为值的无序map容器
            m[arr[i]] = i;

        vector<vector<int>> dp(n, vector<int>(n, 0)); // dp[i][j]表示以"arr[i]、arr[j]"结尾的子序列的长度
        int ans = 0;

        for (int j = 1; j < n; j++)
        {
            for (int i = j - 1; i >= 0 && arr[j] - arr[i] < arr[i]; i--)
            {
                int arr_k = arr[j] - arr[i]; // arr[k]+arr[i]=arr[j]
                if (m.count(arr_k))          // count方法返回个数；find方法返回迭代器
                {
                    int k = m[arr_k];
                    dp[i][j] = max(dp[k][i] + 1, 3);
                    ans = max(ans, dp[i][j]);
                }
            }
        }

        return ans;
    }
};