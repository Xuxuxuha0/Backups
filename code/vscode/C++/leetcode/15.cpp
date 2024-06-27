// 96. 不同的二叉搜索树
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution
{
    long BST(vector<int> &record, int start, int end)
    {
        if (start >= end) // 特殊处理
            return 1;

        int lenth = end - start + 1;
        if (record[lenth] != 0) // 避免重复计算的记忆性
            return record[lenth];

        int left = 0;
        int right = 0;
        int all = 0;

        for (int i = start; i <= end; i++) // 以i为根的二叉搜索树
        {
            left = BST(record, start, i - 1);
            right = BST(record, i + 1, end);
            all += left * right;
        }

        record[lenth] = all;
        return all;
    }

public:
    int numTrees(int n)
    {
        vector<int> record(n + 1, 0); // record[i]:长度为i的二叉搜索树有多少种
        record[0] = record[1] = 1;
        return BST(record, 1, n);
    }
};

int main()
{
    Solution p;
    cout << p.numTrees(19);
}