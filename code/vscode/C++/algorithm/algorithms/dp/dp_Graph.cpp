#include <iostream> //如何用贪心法来解？
#include <string.h>
using namespace std;
#define N 1504
int dp[N][2], father[N], visited[N], n;
// dp[i][0]表示以i为根的子树中，点i不放士兵所需要的最小士兵数量
// dp[i][1]表示以i为根的子树中，点i放士兵所需要的最小士兵数量
// father存放双亲的下标
void DFS(int root)
{
    visited[root] = 1;          // 表示已经算过以root为根的子树的最小士兵数量
    for (int i = 0; i < n; i++) // 考虑第i个结点是否是没访问过的子女
    {
        if (!visited[i] && father[i] == root) // 未访问过且是子女（待优化：不如使用链表）
        {
            DFS(i);                                 // 先算以子女为根的树的最小士兵数量（待优化：尽量不要使用递归）
            dp[root][1] += min(dp[i][0], dp[i][1]); // root放士兵，子女就可能不放
            dp[root][0] += dp[i][1];                // root不放，子女要放
        }
    }
}
int main()
{
    int i, j, k, t1, t2, root = 0;
    while (scanf("%d", &n) != EOF) // n个结点
    {
        for (register int i = 0; i < n; i++)
        {
            dp[i][0] = 0;
            dp[i][1] = 1; // 先初始化，1表示该节点要放
        }
        memset(visited, 0, sizeof(visited));
        for (register int i = 0; i < n; i++)
        {
            scanf("%d:(%d)", &t1, &t2); // 注意输入，不要在最后加\n
            if (i == 0)
                root = t1;                        // 把第一个t1当作根
            for (register int j = 0; j < t2; j++) // 图中每个顶点的父节点都是t1(即每行的第一个顶点)
            {
                scanf("%d", &k);
                father[k] = t1; // 双亲表示法
            }
        }
        DFS(root);
        printf("%d\n", min(dp[root][0], dp[root][1]));
    }
    return 0;
}
/*
城堡里的道路形成一棵无向树。要在结点上安排最少的士兵使得他们可以看到所有边。
你的任务是给出士兵的最少数目。
*/