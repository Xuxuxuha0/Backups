#include <iostream>
using namespace std;

#define size 100

typedef struct //并查集
{
    int parent[size]; //双亲指针数组
} UFSets;

void Initial(UFSets &s)
{
    for (int i = 0; i < size; i++)
        s.parent[i] = -1;
}

int Find(UFSets s, int x) //返回x的根
{
    while (s.parent[x] >= 0)
        x = s.parent[x];
    return x;
}

void Merge(UFSets &s, int r1, int r2) //要求：r1、r2是根。合并r1树和r2树，让r1成为根。
{
    if (r1 == r2)
        return;
    s.parent[r1] += s.parent[r2];
    s.parent[r2] = r1;
}

void MergeByWeight(UFSets &s, int r1, int r2) //合并r1、r2所在的根
{
    int i = Find(s, r1), j = Find(s, r2);
    if (i == j)
        return;
    int temp = s.parent[i] + s.parent[j];
    if (s.parent[j] < s.parent[i]) //让节点多的当新根
    {
        s.parent[i] = j;
        s.parent[j] = temp;
    }
    else
    {
        s.parent[j] = i;
        s.parent[i] = temp;
    }
}

int CollapsFind(UFSets &s, int i) //压缩i往上的路径
{
    int k, temp;
    for (k = i; s.parent[k] >= 0; k = s.parent[k]) //让k指向根
        ;
    while (i != k)
    {
        temp = s.parent[i];
        s.parent[i] = k; //让i到根路径上的每个结点的双亲都变为k
        i = temp;
    }
    return k;
}