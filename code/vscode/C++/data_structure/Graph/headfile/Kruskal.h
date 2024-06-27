#include "UFSets.h"
#include "MinSpanTree.h"
#include "ALGraph.h"

//最小生成树
void Kruskal(MSTENode E[], int n, int e, MinSpanTree &T) //要求E中的边按权值由小到大排序
{
    UFSets Vest; //并查集
    Initial(Vest);
    T.n = 0;
    int i = 0, j = 0; // j用于计数
    while (i < e && j < n - 1)
    {
        int u = Find(Vest, E[i].v1);
        int v = Find(Vest, E[i].v2);
        if (u != v)
        {
            T.Edges[T.n++] = E[i]; //把这条边加入生成树
            Merge(Vest, u, v);     //合并这两个根
            j++;
        }
        i++;
    }
    if (j < n - 1)
        cout << "不是连通图";
}