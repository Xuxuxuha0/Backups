#include <iostream>
using namespace std;

#define maxVertices 30
#define maxEdges 450

typedef char dataType;
typedef int Weight;

typedef struct Enode // 边结点
{
    int dest; // 下标
    Weight cost;
    struct Enode *link;
} EdgeNode;

typedef struct Vnode // 头顶点
{
    dataType data;
    struct Enode *adj;
} VertexNode;

typedef struct
{
    VertexNode VerticesList[maxVertices]; // 报错？？？
    int numVertices, numEdges;
} ALGraph;

int VPosition(ALGraph G, dataType v) // 返回下标
{
    int i = 0;
    while (i < G.numVertices && G.VerticesList[i].data != v)
        i++;
    return i;
}

int FirstNeighbor(ALGraph G, int v)
{
    EdgeNode *p = G.VerticesList[v].adj;
    if (p != NULL)
        return p->dest;
    return -1;
}

int NextNeighbor(ALGraph G, int v, int w)
{
    EdgeNode *p = G.VerticesList[v].adj;
    while (p != NULL && p->dest != w)
        p = p->link;
    if (p != NULL && p->link != NULL)
        return p->link->dest;
    return -1;
}

Weight getWeight(ALGraph G, int v, int w) // 取v-w的权
{
    EdgeNode *p = G.VerticesList[v].adj;
    while (p->dest != w)
        p = p->link;
    return p->cost;
}

void CreateALGraph(ALGraph &G, int n, int e, int d)
{
    G.numVertices = n;
    G.numEdges = e;
    int i;
    dataType val;
    for (i = 0; i < G.numVertices; i++)
    {
        scanf("%c", &val);
        G.VerticesList[i].data = val;
        G.VerticesList[i].adj = NULL;
    }
    i = 0;
    dataType e1, e2;
    int Cost, j, k;
    EdgeNode *p, *q;
    while (i < G.numEdges)
    {
        scanf("%c,%c,%d", &e1, &e2, &Cost);
        j = VPosition(G, e1);
        k = VPosition(G, e2);
        p = G.VerticesList[j].adj;
        while (p != NULL && p->dest != k)
            p = p->link;
        if (p == NULL)
        {
            q = new EdgeNode;
            q->cost = Cost;
            q->dest = k;
            q->link = G.VerticesList[j].adj; // 前插法
            G.VerticesList[j].adj = q;
            if (d == 0)
            {
                q = new EdgeNode;
                q->cost = Cost;
                q->dest = j;
                q->link = G.VerticesList[k].adj;
                G.VerticesList[k].adj = q;
            }
        }
        i++;
    }
}