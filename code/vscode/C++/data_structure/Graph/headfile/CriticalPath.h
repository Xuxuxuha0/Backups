#include "ALGraph.h"

typedef struct //关键活动
{
    int v1, v2;
    Weight key;
} Edge;

void CriticalPath(ALGraph G, Edge criticalpath[], int &cnt) //用criticalpath来存关键路径的信息，cnt返回关键活动数
{
    int n = G.numVertices;

    int indegree[maxVertices];
    for (int i = 0; i < n; i++)
        indegree[i] = 0;
    EdgeNode *p;
    for (int i = 0; i < n; i++) //计算入度
        for (p = G.VerticesList[i].adj; p != NULL; p = p->link)
            indegree[p->dest]++;

    Weight Vearly[maxVertices], Vlate[maxVertices]; //每个事件最早/最晚开始的时间
    Weight Aearly[maxEdges], Alate[maxEdges];       //每个活动最早/最晚开始的时间

    for (int i = 0; i < n; i++)
        Vearly[i] = 0;

    int top = -1;
    for (int i = 0; i < n; i++) //所有入度为0的进栈
        if (!indegree[i])
        {
            indegree[i] = top; // indegree[i]=0时，可以当栈用，用top索引
            top = i;
        }

    int m = -1;
    while (top != -1) //正向计算Vearly
    {
        int u = top;         //取栈顶的下标
        top = indegree[top]; //预备下一个栈顶元素下标

        indegree[u] = m; //逆拓扑序列(有向图反向)，以便反向计算Vlate
        m = u;           //退出时，m等于最后一个顶点(汇点)

        for (p = G.VerticesList[u].adj; p != NULL; p = p->link) //计算u的所有邻接顶点的最早开始时间
        {
            int w = p->cost;
            int j = p->dest;
            if (Vearly[u] + w > Vearly[j])
                Vearly[j] = Vearly[u] + w;
            if (--indegree[j] == 0) //入度减一并考虑是否入栈
            {
                indegree[j] = top;
                top = j;
            }
        }
    }

    for (int i = 0; i < n; i++)
        Vlate[i] = Vearly[m];

    while (m != -1) //反向计算Vlate
    {
        int v = indegree[m];
        m = v;

        if (m == -1)
            break;

        for (p = G.VerticesList[v].adj; p != NULL; p = p->link) //由v的所有邻接顶点的最晚开始时间，确定v的最晚开始时间
        {
            int k = p->dest;
            int w = p->cost;
            if (Vlate[k] - w < Vlate[v])
                Vlate[v] = Vlate[k] - w;
        }
    }

    Edge tempEdge;
    Edge temppath[maxEdges]; //按Aearly和Alate数组的对应顺序 存储所有边(活动)的信息
    int k = 0;
    for (int i = 0; i < n; i++)
        for (p = G.VerticesList[i].adj; p != NULL; p = p->link) //由i和它的邻接顶点p->dest 确定该边(该活动)的最早/最晚开始时间
        {
            Aearly[k] = Vearly[i];
            Alate[k] = Vlate[p->dest] - p->cost;

            tempEdge.v1 = i;
            tempEdge.v2 = p->dest;
            tempEdge.key = p->cost;
            temppath[k++] = tempEdge;
        }

    cnt = 0;
    int i = 0;
    while (i < k)
    {
        if (Aearly[i] == Alate[i]) //关键活动的条件
        {
            criticalpath[cnt] = temppath[i];
            cnt++;
        }
        i++;
    }
}