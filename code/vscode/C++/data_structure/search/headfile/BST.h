#include <iostream>
using namespace std;

typedef int datatype;

typedef struct tnode // 二叉查找树
{
    datatype data;
    struct tnode *lchild, *rchild;
} BSTNode, *BSTree;

BSTree RecurSearch(BSTree p, datatype x) // 递归查找x
{
    if (p == NULL)
        return NULL;
    if (x < p->data)
        RecurSearch(p->lchild, x);
    else if (x > p->data)
        RecurSearch(p->rchild, x);
    else
        return p;
}

BSTree Search(BSTree T, BSTree &father, datatype x) // 非递归查找， T是树根，father不必赋值
{
    BSTree p = T;
    father = NULL;
    while (p != NULL && p->data != x)
    {
        father = p;
        if (p->data < x)
            p = p->lchild;
        else
            p = p->rchild;
    }
    return p;
}

int Insert(BSTree &T, datatype x) // 插入一个结点
{
    BSTree f;
    BSTree p = Search(T, f, x);
    if (p != NULL)
        return 0; // 找到了x，不需要插入
    BSTree temp = new BSTNode;
    temp->data = x;
    temp->lchild = temp->rchild = NULL;
    if (f == NULL)
        T = temp;
    else if (f->data < x)
        f->rchild = temp;
    else
        f->lchild = temp;
    return 1; // 插入成功
}

void CreateBST(BSTree &T, datatype end) // 创建二叉搜索树
{
    datatype x;
    T = NULL;
    BSTree temp;
    while (scanf("%d", &x) && x != end)
        Insert(T, x);
}

int Delete(BSTree &T, datatype x)
{
    BSTree f;
    BSTree p = Search(T, f, x);

    if (p == NULL)
        return 0;

    BSTree temp;

    if (p->lchild != NULL && p->rchild != NULL) // 左右子树都不空
    {
        temp = p->rchild;
        f = p;
        while (temp->lchild != NULL) // 找到p的中序后继
        {
            f = temp;
            temp = temp->lchild;
        }
        p->data = temp->data;
        p = temp; // 转化为删除该后继
    }

    if (p->lchild != NULL) // 让temp等于不空的子树(也可能都空)
        temp = p->lchild;
    else
        temp = p->rchild;

    if (p == T)
        T = temp;
    else if (temp->data < f->data) // 如果temp在f的左子树中，其双亲p也一定在f左子树中，让temp代替p即可
        f->lchild = temp;
    else
        f->rchild = temp;
    free(p);

    return 1;
}