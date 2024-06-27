#include "MGraph.h"
#include "MinSpanTree.h"

//顶点u开始的最小生成树
void Prim(MGraph &G, int u, MinSpanTree &T) //无向连通图；从u顶点开始计算
{
    int n = G.numVertices;

    Weight lowcost[MaxVertices]; //下标为外顶点，表示外顶点到生成树内顶点的最小权
    int nearvex[MaxVertices];    //下标为外顶点，表示外顶点到生成树内顶点的最小权的内顶点下标
    for (int i = 0; i < G.numVertices; i++)
    {
        lowcost[i] = G.Edge[i][u];
        nearvex[i] = u;
    }

    nearvex[u] = -1; //把u顶点加到生成树里
    MSTENode e;
    T.n = 0;
    for (int i = 1; i < n; i++) // i是计数器，最多循环n-1次，加入n-1条边(G是连通图时)
    {
        Weight min = maxValue;
        int v = -1;

        for (int j = 0; j < n; j++)                   //找出树外到树内的最小权值和它的下标
            if (nearvex[j] != -1 && lowcost[j] < min) // j顶点在树外，且权值更小
            {
                v = j;
                min = lowcost[j];
            }

        if (v != -1)
        {
            e.v1 = nearvex[v];
            e.v2 = v;
            e.cost = lowcost[v];
            nearvex[v] = -1;
            T.Edges[T.n++] = e;

            for (int j = 0; j < n; j++) //比较所有树外顶点到j的cost、原lowcost，更新lowcost数组
                if (nearvex[j] != -1 && G.Edge[v][j] < lowcost[j])
                {
                    lowcost[j] = G.Edge[j][v];
                    nearvex[j] = v;
                }
        }
        else
        {
            cout << "不是连通图";
            break; //再也找不到边了，此时找到了一个非连通图的最小生成树
        }
    }
}