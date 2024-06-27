#include <iostream>
using namespace std;
#define size 100
typedef struct node
{
    char data;
    struct node *lchild, *rchild;
} BiTNode, *BinTree;
void CreateBinTree(BinTree &T, char pre[], int &n) //根据先序pre创建二叉树
{
    char ch = pre[n++];
    if (ch == '\0')
        return;
    if (ch != '#')
    {
        T = (BiTNode *)malloc(sizeof(BiTNode));
        T->data = ch;
        CreateBinTree(T->lchild, pre, n);
        CreateBinTree(T->rchild, pre, n);
    }
    else
        T = NULL;
}
void SwapLR(BinTree &T, char pre[], int &n) //与上函数不同：先建立右子树，在建立左子树
{
    char ch = pre[n++];
    if (ch == '\0')
        return;
    if (ch != '#')
    {
        T = (BiTNode *)malloc(sizeof(BiTNode));
        T->data = ch;
        SwapLR(T->rchild, pre, n);
        SwapLR(T->lchild, pre, n);
    }
    else
        T = NULL;
}
void PreOrder_recur(BinTree T) //先序输出
{
    if (T != NULL)
    {
        cout << T->data;
        PreOrder_recur(T->lchild);
        PreOrder_recur(T->rchild);
    }
}
void InOrder_recur(BinTree T)
{
    if (T != NULL)
    {
        InOrder_recur(T->lchild);
        cout << T->data;
        InOrder_recur(T->rchild);
    }
}
void PostOrder_recur(BinTree T)
{
    if (T != NULL)
    {
        PostOrder_recur(T->lchild);
        PostOrder_recur(T->rchild);
        cout << T->data;
    }
}
void print(BinTree T, int n) //按要求打印 得用临时变量
{
    if (T != NULL)
    {
        for (int i = 0; i < n * 4; i++)
            cout << " ";
        cout << T->data << endl;
        print(T->lchild, n + 1);
        print(T->rchild, n + 1);
    }
}
int FindLeaves(char pre[]) //根据先序序列计算叶节点个数
{
    char ch = pre[0];
    int i = 1, cnt = 0;
    while (ch != '\0')
    {
        if (ch != '#' && pre[i] == '#' && pre[i + 1] == '#') //当且仅当这种形式 才会是叶节点
        {
            cnt++;
            ch = pre[i + 2];
            i += 3;
        }
        else
            ch = pre[i++];
    }
    return cnt;
}
int main()
{
    char Pre[size];
    cin >> Pre;
    BinTree root, reverse_root;
    int x = 0;
    CreateBinTree(root, Pre, x);
    cout << "BiTree" << endl;
    x = 0;
    print(root, x);
    cout << "pre_sequence  : ";
    PreOrder_recur(root);
    cout << endl;
    cout << "in_sequence   : ";
    InOrder_recur(root);
    cout << endl;
    cout << "post_sequence : ";
    PostOrder_recur(root);
    cout << endl;
    cout << "Number of leaf: " << FindLeaves(Pre) << endl;

    x = 0;
    SwapLR(reverse_root, Pre, x);
    cout << "BiTree swapped" << endl;
    x = 0;
    print(reverse_root, x);
    cout << "pre_sequence  : ";
    PreOrder_recur(reverse_root);
    cout << endl;
    cout << "in_sequence   : ";
    InOrder_recur(reverse_root);
    cout << endl;
    cout << "post_sequence : ";
    PostOrder_recur(reverse_root);
    cout << endl;
}