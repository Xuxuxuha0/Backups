// 面试题13. 机器人的运动范围
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution01 // 广度优先搜索法
{
    int getsum(int x) // 计算各位之和
    {
        int val = 0;
        while (x != 0)
        {
            val += x % 10;
            x /= 10;
        }
        return val;
    }

public:
    int movingCount(int m, int n, int k)
    {
        if (k == 0)
            return 1;

        vector<vector<int>> visited(m, vector<int>(n, 0)); // 二维数组初始化为0

        queue<pair<int, int>> Queue;

        Queue.push(make_pair(0, 0));
        int cnt = 1;
        visited[0][0] = 1;

        int dx[] = {0, 1}; // dx[0]=0、dy[0]=1表示向y方向移动一格，即向右移动一格；下x右y
        int dy[] = {1, 0};

        while (!Queue.empty())
        {
            auto [x, y] = Queue.front(); // auto可以根据后面自适应类型
            Queue.pop();

            for (int i = 0; i < 2; i++)
            {
                int tx = x + dx[i];
                int ty = y + dy[i];

                if (tx < m && ty < n && !visited[tx][ty] && getsum(tx) + getsum(ty) <= k)
                {
                    visited[tx][ty] = 1;
                    cnt++;
                    Queue.push(make_pair(tx, ty));
                }
            }
        }
        return cnt;
    }
};

class Solution // 动态规划
{
    int getsum(int x)
    {
        int val = 0;
        while (x != 0)
        {
            val += x % 10;
            x /= 10;
        }
        return val;
    }

public:
    int movingCount(int m, int n, int k)
    {
        if (k == 0)
            return 1;

        vector<vector<int>> CanGet(m, vector<int>(n, 0));

        CanGet[0][0] = 1;
        int cnt = 0;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (getsum(i) + getsum(j) <= k) //[i,j]只能从[i-1,j]、[i,j-1]来
                {
                    if (i >= 1)
                        CanGet[i][j] |= CanGet[i - 1][j]; //|运算：两个都为0才等于0
                    if (j >= 1)
                        CanGet[i][j] |= CanGet[i][j - 1];
                    cnt += CanGet[i][j];
                }
            }
        return cnt;
    }
};