#include "MGraph.h"
#include "CircleQueue.h"

//求无权图中顶点v到其他顶点的最短路径(广度优先搜索)
//有向图/无向图
void unweighted(MGraph G, int v, int dist[], int path[])
{
    // dist[i]:v到i的最短距离
    // path[i]:v到i的最短路径的倒数第二个顶点
    CircleQueue Q;
    InitQueue(Q);
    int n = G.numVertices;

    for (int i = 0; i < n; i++) //初始化
        dist[i] = MaxVertices;  //相当于无穷大

    dist[v] = 0;
    EnterQueue(Q, v);

    while (Q.front != Q.rear)
    {
        DeleteQueue(Q, v); //队头出列，v返回队头

        int w = FirstNeighbor(G, v);
        while (w != -1) // v的所有邻接顶点
        {
            if (dist[w] == MaxVertices)
            {
                dist[w] = dist[v] + 1;
                path[w] = v;
                EnterQueue(Q, w);
            }
            w = NextNeighbor(G, v, w);
        }
    }
}
