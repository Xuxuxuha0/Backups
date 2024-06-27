#include <iostream>
using namespace std;

#define size 50
typedef char DataType;

typedef struct node
{
    DataType data;
    int parent; // 双亲的下标
} PTNode;

typedef struct // 树的双亲表示法
{
    PTNode tnode[size];
    int n;
} PTree;

int FirstChild(PTree t, int i) // 寻找下标为i的结点的第一个子女
{
    int j;
    for (j = i + 1; j < t.n; j++)
        if (t.tnode[j].parent == i)
            break;
    if (j < t.n)
        return j;
    else
        return -1;
}

int NextSibing(PTree t, int i, int j) // 寻找i的下标为j的子女的下一个兄弟
{
    int k;
    for (k = j + 1; k < t.n; k++)
        if (t.tnode[k].parent == i)
            break;
    if (k < t.n)
        return k;
    else
        return -1;
}

int FindParent(PTree t, int i) // 寻找i的双亲
{
    if (i < t.n && i > 0)
        return t.tnode[i].parent;
    else
        return -1;
}