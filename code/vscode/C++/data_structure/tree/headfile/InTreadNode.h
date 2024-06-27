#include "ThreadNode.h"

typedef ThreadNode *InThreadTree; // 中序线索二叉树

InThreadTree inFirst(InThreadTree t)
// 求以t为根的第一个结点
// 改为rtag和rchild可得最后一个结点
{
    while (t->ltag == 0) // 中序下的第一个结点：第一个ltag=1
        t = t->lchild;
    return t;
}

InThreadTree inNext(InThreadTree t)
// 寻找t的后继结点
// rtag=1:rchild就是       rtag=0:右子树为根的第一个结点
// 改为ltag和lchild可得前驱
{
    if (t->rtag == 0)
        return inFirst(t->rchild);
    return t->rchild;
}

void inOrder(InThreadTree t) // 中序遍历
{
    ThreadNode *p = inFirst(t);
    for (; p != NULL; p = inNext(p))
        printf("%d ", p->data);
}

void CreateInThread(InThreadTree p, InThreadTree &pre) // pre是p的前驱
// 把二叉树改造为中序线索二叉树
// 先将p的左子树线索化，再改造p的前驱和它的前驱的后继，再改造p的右子树
{
    if (p != NULL)
    {
        CreateInThread(p->lchild, pre);
        if (p->lchild == NULL) // 构建前驱
        {
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL) // 构建后继
        {
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;
        CreateInThread(p->rchild, pre);
    }
}
void main_creat(InThreadTree t) // 启动函数
{
    InThreadTree pre = NULL;
    if (t != NULL)
    {
        CreateInThread(t, pre);
        pre->rchild = NULL;
        pre->rtag = 1;
    }
}