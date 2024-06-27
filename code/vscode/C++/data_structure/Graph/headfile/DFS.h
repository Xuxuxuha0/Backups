#include "ALGraph.h"
#include <string.h>

void DFS(ALGraph G, int v, int visited[])
// 先访问v，再对v的所有邻接顶点深度优先搜索
{
    printf("->%c", G.VerticesList[v].data);
    visited[v] = 1;
    int w = FirstNeighbor(G, v);
    while (w != -1)
    {
        if (!visited[w])
            DFS(G, w, visited);
        w = NextNeighbor(G, v, w);
    }
}

void DFS_Traversal(ALGraph G, int v) // 连通图的深度优先搜索的启动函数
{
    int i, n = G.numVertices;
    int visited[maxVertices];
    memset(visited, 0, sizeof(visited));
    DFS(G, v, visited);
}