#include <iostream>
using namespace std;

typedef int datatype;

typedef struct node // 循环单向链表
{
    datatype data;
    struct node *link;
} CircleNode, *CircleList;

void CreateCircleList(CircleList first, datatype A[], int n)
{
    first = (CircleList)malloc(sizeof(CircleNode));
    first->link = first; // 首尾相连
    CircleList p = first;
    CircleList temp;
    for (int i = 0; i < n; i++)
    {
        temp = (CircleList)malloc(sizeof(CircleNode));
        temp->data = A[i];
        temp->link = p->link; // p是上一次的链尾
        p->link = temp;
        p = temp;
    }
}

int Insert(CircleNode *first, int i, datatype x) // 插入第i个位置,第0个位置是first
{
    if (i < 1)
        return 0;
    CircleNode *p = first;
    int k = 0;
    while (p->link != first && k < i - 1) // 让p指向第i-1个位置
    {
        k++;
        p = p->link;
    }
    CircleList q = (CircleList)malloc(sizeof(CircleNode));
    q->data = x;
    q->link = p->link;
    p->link = q;
    return 1;
}

int Remove(CircleList first, int i, datatype &x)
{
    if (i < 1)
        return 0;
    CircleList p = first;
    int k = 0;
    while (p->link != first && k < i - 1)
    {
        p = p->link;
        k++;
    }
    if (p->link == first)
        return 0;
    CircleList q = p->link;
    p->link = q->link;
    x = q->data;
    free(q);
    return 1;
}