#include "BinTree.h"

#define size 50

void PreOrder(BinTree T) // 用栈实现先序遍历
{
    BinTree stack[size];
    int top = -1;
    BinTree p = T;
    do
    {
        while (p != NULL) // 访问，沿途的右子树进栈
        {
            printf("%d ", p->data);
            stack[++top] = p->rchild;
            p = p->lchild;
        }
        if (top > -1)
            p = stack[top--];
    } while (p != NULL || top > -1);
}

void InOrder(BinTree T)
{
    BinTree stack[size];
    int top = -1;
    BinTree p = T;
    do
    {
        while (p != NULL) // 左子树全部进栈
        {
            stack[++top] = p; // 栈中一定不为NULL
            p = p->lchild;
        }
        if (top > -1)
        {
            p = stack[top--]; // 出栈一个并访问，然后对它的右子树重复操作
            printf("%d ", p->data);
            p = p->rchild;
        }
    } while (p != NULL || top > -1);
}

void PostOrder(BinTree T)
{
    BinTree stack[size];
    int top = -1;
    BinTree p = T;
    BinTree pre = NULL;
    do
    {
        while (p != NULL)
        {
            stack[++top] = p;
            p = p->lchild;
        }
        if (top > -1)
        {
            p = stack[top];
            if (p->rchild != NULL && p->rchild != pre)
                p = p->rchild;
            else
            {
                printf("%d ", p->data);
                pre = p; // pre记录才访问的
                p = NULL;
                top--;
            }
        }
    } while (p != NULL || top > -1);
}

void LevelOrder(BinTree T) // 层次遍历
{
    BinTree Queue[size];
    int rear = 0, front = 0;
    BinTree p = T;
    Queue[rear++] = p;
    while (front != rear)
    {
        p = Queue[front];
        front = (front + 1) % size;
        printf("%d ", p->data);
        if (p->lchild != NULL)
        {
            Queue[rear] = p->lchild;
            rear = (rear + 1) % size;
        }
        if (p->rchild != NULL)
        {
            Queue[rear] = p->rchild;
            rear = (rear + 1) % size;
        }
    }
}