#include <iostream>
using namespace std;
typedef char ElemType;
typedef struct node //链式二叉树
{
    ElemType data;
    struct node *lchild, *rchild;
} BiTNode, *BinTree;
