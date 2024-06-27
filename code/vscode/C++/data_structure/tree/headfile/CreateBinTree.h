#include "BinTree.h"

void pre_in(BinTree &T, ElemType Pre[], int s1, int t1, ElemType In[], int s2, int t2)
{
    //根据先序Pre[s1..t1]和中序In[s2..t2]创建二叉树
    if (s1 <= t1)
    {
        T = new BiTNode;
        T->data = Pre[s1];
        T->lchild = NULL;
        T->rchild = NULL;
        int i;
        for (i = s2; i <= t2; i++)
            if (In[i] == Pre[s1])
                break;
        pre_in(T->lchild, Pre, s1 + 1, s1 + i - s2, In, s2, i - 1);
        pre_in(T->rchild, Pre, s1 + i - s2 + 1, t1, In, i + 1, t2);
    }
}
