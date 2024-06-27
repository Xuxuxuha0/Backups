#include <iostream>
using namespace std;

#define size 100
typedef int ElemType;

typedef struct //循环队列
{
    ElemType elem[size];
    int front, rear;
} CircleQueue;

void InitQueue(CircleQueue Q)
{
    Q.front = Q.rear = 0;
}

int EnterQueue(CircleQueue &Q, ElemType x)
{
    if ((Q.rear + 1) % size == Q.front) //队列满了
        return 0;
    Q.elem[Q.rear] = x;
    Q.rear = (Q.rear + 1) % size;
    return 1;
}

int DeleteQueue(CircleQueue &Q, ElemType &x) //通过x引用返回出列的队头
{
    if (Q.front == Q.rear)
        return 0;
    x = Q.elem[Q.front];
    Q.front = (Q.front + 1) % size;
    return 1;
}

int QueueSize(CircleQueue Q) //返回队列的元素个数
{
    return (Q.rear - Q.front + size) % size;
}
