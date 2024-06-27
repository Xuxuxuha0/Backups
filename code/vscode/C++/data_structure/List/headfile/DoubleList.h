#include <iostream>
using namespace std;

#define size 30

typedef int datatype;

typedef struct node
{
    datatype data;
    struct node *rLink, *lLink;
} DoubleNode, *DoubleList;

void CreateList(DoubleList &first, datatype A[], int m)
{
    first = (DoubleList)malloc(sizeof(DoubleNode));
    first->rLink = first;
    first->lLink = first;
    DoubleList temp, q, rear = first;
    for (int i = 0; i < m; i++)
    {
        temp = (DoubleList)malloc(sizeof(DoubleNode));
        temp->data = A[i];

        q = rear->rLink; // 前驱方向
        temp->lLink = rear;
        q->lLink = temp;

        rear->rLink = temp; // 后继方向
        temp->rLink = q;
        rear = temp;
    }
}

DoubleList Locate(DoubleList first, int i, int d) // d=0:前驱方向寻找第i个结点
{
    if (i < 0)
        return NULL;
    if (i == 0)
        return first;
    DoubleList p = (d == 0) ? first->lLink : first->rLink;
    for (int j = 1; j < i; j++)
        if (p == first)
            break;
        else
            p = (d == 0) ? p->lLink : p->rLink;
    return p;
}
int Insert(DoubleList &first, int i, datatype x, int d)
{
    DoubleList p = Locate(first, i - 1, d);
    DoubleList temp = (DoubleList)malloc(sizeof(DoubleNode));
    temp->data = x;
    if (d == 0)
    {
        temp->lLink = p->lLink;
        p->lLink = temp;

        temp->lLink->rLink = temp;
        temp->rLink = p;
    }
    else
    {
        temp->rLink = p->rLink;
        p->rLink = temp;

        temp->rLink->lLink = temp;
        temp->lLink = p;
    }
    return 1;
}

int Remove(DoubleList &first, int i, datatype &x, int d)
{
    DoubleList p = Locate(first, i, d);
    p->rLink->lLink = p->lLink;
    p->lLink->rLink = p->rLink;
    x = p->data;
    free(p);
    return 1;
}