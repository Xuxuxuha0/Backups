// 剑指 Offer II 107. 矩阵中的距离
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution // 广度优先搜索
{
private:
    int d[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 位移

public:
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
    {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dis(m, vector<int>(n, 0));     // 最短距离
        vector<vector<int>> visited(m, vector<int>(n, 0)); // 是否访问过
        queue<pair<int, int>> Que;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (mat[i][j] == 0)
                {
                    Que.emplace(i, j); // 注意形式
                    visited[i][j] = 1;
                }

        while (!Que.empty())
        {
            int i = Que.front().first;
            int j = Que.front().second;
            Que.pop();
            for (int x = 0; x < 4; x++)
            {
                int tx = i + d[x][0];
                int ty = j + d[x][1];
                if (tx >= 0 && tx < m && ty >= 0 && ty < n && !visited[tx][ty])
                {
                    dis[tx][ty] = dis[i][j] + 1; // 由于队列里的点按照dis从小到大排列，所以算出来的一定是最小值
                    visited[tx][ty] = 1;
                    Que.emplace(tx, ty);
                }
            }
        }

        return dis;
    }
};

int main()
{
    vector<vector<int>> mat{{0}};
    Solution p;
    vector<vector<int>> t = p.updateMatrix(mat);
    cout << t[0][0];
}