#include "MGraph.h"

//求出所有顶点之间的最短路径
//有向图、无向图
void Floyd(MGraph G, Weight a[][MaxVertices], int path[][MaxVertices])
{
    // a[i][j]：i->j的最短距离
    // path[i][j]:i->j的最短路径倒数第二个顶点
    int n = G.numVertices;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            a[i][j] = G.Edge[i][j]; //初始化
            if (i != j && a[i][j] < MaxWeight)
                path[i][j] = i;
            else
                path[i][j] = -1; //无路
        }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (a[i][k] + a[k][j] < a[i][j])
                {
                    a[i][j] = a[i][k] + a[k][j];
                    path[i][j] = path[k][j];
                }
}