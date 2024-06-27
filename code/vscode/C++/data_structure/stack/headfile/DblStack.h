#include <iostream>
using namespace std;

#define size 20

typedef int ElemType;

typedef struct
{
    int top[2], bot[2]; // 双栈共用一个栈空间：bot0...top0->   <-top1...bot1
    ElemType stack[size];
} DblStack;

void InitStack(DblStack &s)
{
    s.top[0] = s.bot[0] = -1;
    s.top[1] = s.bot[1] = size;
}

int Push(DblStack &s, ElemType x, int i)
{
    if (s.top[0] + 1 == s.top[1])
        return 0;
    if (i == 0)
        s.stack[++s.top[0]] = x;
    else
        s.stack[--s.top[1]] = x;
    return 1;
}

int Pop(DblStack &s, int i, ElemType &x)
{
    if (s.top[i] == s.bot[i])
        return 0;
    if (i == 0)
        x = s.stack[s.top[0]--];
    else
        x = s.stack[s.top[1]++];
    return 1;
}