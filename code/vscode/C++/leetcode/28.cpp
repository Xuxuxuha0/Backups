// 面试题 08.02. 迷路的机器人
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution // 深度优先搜索
{
private:
    int m, n;
    vector<vector<int>> d{{1, 0}, {0, 1}};
    vector<vector<int>> visited;
    vector<vector<int>> obs; // 拷贝一下输入，当作全局变量使用
    vector<vector<int>> ans;

public:
    int dfs(int x, int y)
    {
        if (x == m - 1 && y == n - 1)
            return 1;
        for (int k = 0; k < 2; k++)
        {
            int tx = x + d[k][0], ty = y + d[k][1];
            if (tx < m && ty < n && !obs[tx][ty] && !visited[tx][ty])
            {
                visited[tx][ty] = 1;
                ans.push_back({tx, ty});
                if (dfs(tx, ty))
                    return 1;
                ans.pop_back();
            }
        }
        return 0;
    }
    vector<vector<int>> pathWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        obs = obstacleGrid; // 如果把obstacleGrid当作dfs的参数，会造成内存和时间的大量消耗；所以需要拷贝一份
        if (obstacleGrid[0][0])
            return ans;
        m = obstacleGrid.size();
        n = obstacleGrid[0].size();
        visited.assign(m, vector<int>(n, 0)); // 使用[][]方法之前需要申请空间；使用push_back方法不需要

        visited[0][0] = 1;
        ans.push_back({0, 0}); // 二维数组加入一维元素的办法：用{}或者新建一个一维变量
        if (!dfs(0, 0))
            ans.pop_back();

        return ans;
    }
};

int main()
{
    Solution p;
    vector<vector<int>> ob{{0, 1}};
    p.pathWithObstacles(ob);
}