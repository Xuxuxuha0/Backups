#include <iostream>
using namespace std;

typedef int ElemType;

typedef struct node // 链式栈
{
    ElemType data;
    struct node *link;
} LinkNode, *LinkStack;

void InitStack(LinkStack &s)
{
    s = NULL;
}

int Push(LinkStack &s, ElemType x)
{
    LinkNode *p = (LinkStack)malloc(sizeof(LinkNode));
    p->data = x;
    p->link = s;
    s = p; // 头节点也要用
    return 1;
}

int Pop(LinkStack &s, ElemType &x)
{
    if (s == NULL)
        return 0;
    LinkNode *p = s;
    x = s->data;
    s = s->link;
    free(p);
    return 1;
}