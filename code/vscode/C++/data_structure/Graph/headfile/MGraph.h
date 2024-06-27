#include <iostream>
using namespace std;

#define MaxVertices 30
#define MaxEdges 900
#define MaxWeight 1000000

typedef char dataType;
typedef int Weight;

typedef struct
{
    int numVertices, numEdges;             //实际点数、边数
    dataType VerticesList[MaxVertices];    //顶点表
    Weight Edge[MaxVertices][MaxVertices]; //邻接矩阵
} MGraph;

int VPosition(MGraph G, dataType x) //找到x的下标
{
    for (int i = 0; i < G.numVertices; i++)
        if (G.VerticesList[i] == x)
            return i;
    return -1;
}

int FirstNeighbor(MGraph G, int v) //找到v顶点的第一个邻接顶点
{
    for (int i = 0; i < G.numVertices; i++)
        if (G.Edge[v][i] > 0 && G.Edge[v][i] < MaxWeight)
            return i;
    return -1;
}

int NextNeighbor(MGraph &G, int v, int w)
{
    for (int i = w + 1; i < G.numVertices; i++)
        if (G.Edge[v][i] > 0 && G.Edge[v][i] < MaxWeight)
            return i;
    return -1;
}

void CreateMGraph(MGraph &G, int n, int e, int d) //输入n个顶点、e条边的数据，d=1是有向图
{
    G.numVertices = n;
    G.numEdges = e;
    char val;
    int i, j;
    for (i = 0; i < G.numVertices; i++)
    {
        scanf("%c", &val);
        G.VerticesList[i] = val;
        for (j = 0; j < G.numVertices; j++)
            G.Edge[i][j] = (i == j) ? 0 : MaxWeight; //初始化：到自己的距离为0，其他为无穷
    }
    int k = 0;
    char e1, e2;
    int cost;
    while (k < G.numEdges)
    {
        scanf("%c,%c,%d", &e1, &e2, &cost);
        i = VPosition(G, e1);
        j = VPosition(G, e2);
        G.Edge[i][j] = cost;
        if (d == 0) //无向图
            G.Edge[j][i] = cost;
        k++;
    }
}