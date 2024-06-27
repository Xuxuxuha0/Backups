#include "BinTree.h"

void Preorder(BinTree T) //先序遍历(递归版)
{
    if (T != NULL)
    {
        printf("%d ", T->data);
        Preorder(T->lchild);
        Preorder(T->rchild);
    }
}

void Inorder(BinTree T)
{
    if (T != NULL)
    {
        Inorder(T->lchild);
        printf("%d ", T->data);
        Inorder(T->rchild);
    }
}

void Postorder(BinTree T)
{
    if (T != NULL)
    {
        Postorder(T->lchild);
        Postorder(T->rchild);
        printf("%d ", T->data);
    }
}