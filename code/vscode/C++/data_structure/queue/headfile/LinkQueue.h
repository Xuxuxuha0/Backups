#include <iostream>
using namespace std;

typedef int ElemType;

typedef struct node
{
    ElemType data;
    struct node *link;
} LinkNode;

typedef struct
{
    LinkNode *front, *rear; // front、rear结点都有元素，rear->link=NULL
} LinkQueue;

void Init(LinkQueue &Q)
{
    Q.front = Q.rear = NULL;
}

int EnterQueue(LinkQueue &Q, ElemType x)
{
    LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
    p->data = x;
    p->link = NULL;
    if (Q.rear == NULL) // 队空
        Q.front = Q.rear = p;
    else
    {
        Q.rear->link = p;
        Q.rear = p;
    }
    return 1;
}

int OutQueue(LinkQueue &Q, ElemType &x)
{
    if (Q.front == NULL)
        return 0;
    LinkNode *p = Q.front;
    x = Q.front->data;
    Q.front = Q.front->link;
    free(p);
    if (Q.front == NULL) // 当只有一个元素出队后，需要特殊处理
        Q.rear = NULL;
    return 1;
}