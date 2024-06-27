#include <iostream>
using namespace std;

#define size 50

typedef int ElemType;

typedef struct // 顺序栈
{
    ElemType *elem; // 动态数组
    int maxsize, top;
} SeqStack;

void InitStack(SeqStack &s)
{
    s.elem = new ElemType[size];
    s.maxsize = size;
    s.top = -1;
}

int Push(SeqStack &s, ElemType x)
{
    if (s.top == s.maxsize - 1)
        return 0;
    s.elem[++s.top] = x;
    return 1;
}

int pop(SeqStack &s, ElemType &x)
{
    if (s.top == -1)
        return 0;
    x = s.elem[s.top--];
    return 1;
}
