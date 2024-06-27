#include "BinTree.h"
void Print(BiTNode *t)
{
    if (t != NULL)
    {
        printf("%c", t->data);
        printf("(");
        Print(t->lchild);
        printf(",");
        Print(t->rchild);
        printf(")");
    }
}
// 例如：A(B(C,D(,E)),)