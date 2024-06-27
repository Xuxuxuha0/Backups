// 95. 不同的二叉搜索树 II
#include <iostream>
#include <vector>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
    vector<TreeNode *> recur(int start, int end) // 以[start,end]区间的整数建立二叉搜索树
    {
        if (start > end)
            return {nullptr};

        vector<TreeNode *> AllTrees; // 所有满足的树集合

        for (int i = start; i <= end; i++) // 建立以i为根的二叉搜索树
        {
            vector<TreeNode *> LeftTree;
            LeftTree = recur(start, i - 1); // 左子树集合
            vector<TreeNode *> RightTree;
            RightTree = recur(i + 1, end); // 右子树集合

            for (auto it : LeftTree) // 从集合中选一对来组成树
                for (auto jt : RightTree)
                {
                    TreeNode *T = new TreeNode;
                    T->val = i;
                    T->left = it;
                    T->right = jt;
                    AllTrees.push_back(T);
                }
        }

        return AllTrees;
    }

public:
    vector<TreeNode *> generateTrees(int n)
    {
        if (n == 0)
            return {};
        return recur(1, n);
    }
};