#include <iostream>
using namespace std;

#define size 50

typedef int ElemType;

typedef struct
{
    ElemType elem[size];
    int front, rear;
} CircleQueue;

void Init(CircleQueue &Q)
{
    Q.front = Q.rear = 0;
}

int EnterQueue(CircleQueue &Q, ElemType x)
{
    if ((Q.rear + 1) % size == Q.front) // 队列满
        return 0;
    Q.elem[Q.rear] = x;
    Q.rear = (Q.rear + 1) % size;
    return 1;
}

int OutQueue(CircleQueue &Q, ElemType &x)
{
    if (Q.front == Q.rear) // 队列空
        return 0;
    x = Q.elem[Q.front];
    Q.front = (Q.front + 1) % size;
    return 1;
}

int QueueSize(CircleQueue Q)
{
    return (Q.rear - Q.front + size) % size; // 队列元素个数
}