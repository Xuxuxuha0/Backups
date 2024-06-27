#include "MGraph.h"

//求v到其他顶点的最短路径
//有向图、无向图
void Dijkastra(MGraph G, int v, Weight dist[], int path[])
{
    // dist[i]：v到i的最短距离
    // path[i]：v到i的最短路径的倒数第二个顶点
    int n = G.numVertices;
    int s[MaxVertices]; //最短路径点的集合

    for (int i = 0; i < n; i++) //初始化
    {
        dist[i] = G.Edge[v][i];
        s[i] = 0; //表示未加入最短路径集合
        if (dist[i] < MaxWeight)
            path[i] = v;
        else
            path[i] = -1; //表示v到i没有直接路径
    }
    s[v] = 1;
    dist[v] = 0;
    path[v] = -1;

    for (int i = 0; i < n - 1; i++) // n-1次筛选
    {
        int min = MaxWeight;
        int u = v;
        for (int j = 0; j < n; j++)
            if (!s[j] && dist[j] < min) //选一个新顶点进入集合：不在集合内且到v的距离最小
            {
                u = j;
                min = dist[j];
            }

        s[u] = 1; //让u进入集合

        for (int k = 0; k < n; k++) //更新由v经过u到其他顶点的最小距离
        {
            int w = G.Edge[u][k];
            if (!s[k] && w < MaxWeight && dist[u] + w < dist[k]) // k不在集合中 且 u->k有路 且经过u到k更近
            {
                dist[k] = w + dist[u];
                path[k] = u;
            }
        }
    }
}

void PrintPath(MGraph G, int v, int w, Weight dist[], int path[]) //输出v-w的路径
{
    int n = G.numVertices;
    int d[MaxVertices];
    int k = 0;
    while (w != v)
    {
        d[k++] = w;
        w = path[w];
    }
    d[k++] = v;
    while (k > 0)
        printf("->%c", G.VerticesList[d[--k]]);
}