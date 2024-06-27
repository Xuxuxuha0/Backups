#include "ALGraph.h"

#define size 100

void TopologicalSort(ALGraph &G, int TopoArry[], int &k) //拓扑排序
{
    int stack[size];
    int top = -1;
    int n = G.numVertices;

    int *indegree = new int[n]; //入度数组
    for (int i = 0; i < n; i++)
        indegree[i] = 0;

    EdgeNode *p;
    for (int i = 0; i < n; i++) //计算初始入度数组
    {
        p = G.VerticesList[i].adj;
        while (p != NULL)
        {
            indegree[p->dest]++;
            p = p->link;
        }
    }

    for (int i = 0; i < n; i++) //初始入度为0进栈
        if (!indegree[i])
            stack[++top] = i;

    k = 0;
    for (int i = 0; i < n; i++)
        if (top > -1)
        {
            int j = stack[top--];
            TopoArry[k++] = j;

            p = G.VerticesList[j].adj;
            while (p != NULL) //让j的所有邻接顶点入度-1
            {
                int w = p->dest;
                if (--indegree[w] == 0)
                    stack[++top] = w;
                p = p->link;
            }
        }
        else
            printf("有向环！");
    free(indegree);
}