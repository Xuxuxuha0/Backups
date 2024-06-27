#include <iostream>
using namespace std;

#define size 50

typedef char DataType;

typedef struct node
{
    DataType data;
    struct node *lchild, *rsibing; // 第一个子女，下一个兄弟
} CSNode, *CSTree;

CSTree FindParent(CSTree t, CSTree p)
// 寻找p的双亲
// 先看t是不是p的双亲，再在t的第1个子树中寻找，再在第2个子树中寻找...
{
    CSTree s, q = t->lchild;
    while (q != NULL)
    {
        if (q == p)
            return t;
        s = FindParent(q, p);
        if (s == NULL)
            q = q->rsibing;
        else
            return s;
    }
    return NULL;
}

// 以下是树/森林的两个深度优先遍历
void PreOrder(CSNode *t)
// 树的先序 -> CSTree先序
// 森林先序 -> CSTree先序
{
    if (t != NULL)
    {
        printf("%c ", t->data);
        for (CSNode *p = t->lchild; p != NULL; p = p->rsibing)
            PreOrder(p);
    }
}
void PostOrder(CSNode *t)
// 树的后序 -> CSTree中序
// 森林中序 -> CSTree中序
{
    if (t != NULL)
    {
        for (CSTree p = t->lchild; p != NULL; p = p->rsibing) // 对每个结点，先把所有子女遍历，再访问该节点即可；它的兄弟们在上层for循环中
            PostOrder(p);
        printf("%c ", t->data);
    }
}

// 以下是树的广度优先遍历(层次遍历)
void LevelOrder(CSNode *t)
{
    if (t == NULL)
        return;
    CSNode *Q[size]; // 队列
    int front = 0, rear = 0;
    CSNode *p, *q;
    Q[rear++] = t;
    while (rear != front)
    {
        p = Q[front];
        front = (front + 1) % size;
        printf("%c ", p->data);
        for (q = p->lchild; q != NULL; q = q->rsibing) // 子女全部进队列
        {
            Q[rear] = q;
            rear = (rear + 1) % size;
        }
    }
}