#include "ALGraph.h"
#include <string.h>
void BFS(ALGraph &G) //广度优先搜索，可以遍历非连通图
{
    int n = G.numVertices;
    EdgeNode *p;
    int visited[maxVertices];
    memset(visited, 0, sizeof(visited));
    int Queue[maxVertices]; //队列
    int front = 0, rear = 0;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            printf("->%c", G.VerticesList[i].data);
            visited[i] = 1;
            Queue[rear++] = i;

            while (front < rear) //直到连通图遍历完才退出
            {
                int j = Queue[front++]; //取队头
                int w = FirstNeighbor(G, j);
                while (w != -1) //遍历j所有的邻接顶点
                {
                    if (!visited[w])
                    {
                        printf("->%c", G.VerticesList[w].data);
                        visited[w] = 1;
                        Queue[rear++] = w;
                    }
                    w = NextNeighbor(G, j, w);
                }
            }
        }
    }
}