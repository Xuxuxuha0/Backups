#include <iostream>
using namespace std;

#define size 12

typedef int keytype;

typedef struct node //"链地址法"哈希表
{
    keytype data;
    struct node *link;
} HashNode;

typedef struct
{
    int divisor;
    int m;
    HashNode *elem[size];
} HashList;

void InitHashtable(HashList &L, int d)
{
    L.divisor = d;
    L.m = size;
    for (int i = 0; i < L.m; i++)
        L.elem[i] = NULL;
}

HashNode *FindPosition(HashList &HL, keytype k)
{
    int j = k % HL.divisor;
    HashNode *p = HL.elem[j];
    while (p != NULL && p->data != k)
        p = p->link;
    return p; // p=NULL，表明没有k，且k可以插在p位置；否则表明找到了k
}