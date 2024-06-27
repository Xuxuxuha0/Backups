#include <iostream>
using namespace std;

typedef int Datatype;

typedef struct TRNode // 普遍意义上的线索二叉树
{
    int ltag, rtag; // ltag=0:lchild为左子女  ltag=1:lchild为前驱  rtag=1:后继  具体的前驱后继得看是中序？先序？后序？
    struct TRNode *lchild, *rchild;
    Datatype data;
} ThreadNode;