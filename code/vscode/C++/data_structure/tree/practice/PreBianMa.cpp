#include <iostream> // 前缀码判定
using namespace std;
typedef struct node
{
    int flag;                     // 1表示该节点是某一个字符串的终点
    struct node *lchild, *rchild; //左子树为0，右子树为1
} BiTNode, *BinTree;
void Create(BinTree &t, char a[], int i)
{
    BinTree p = t, temp; // p的移动不会改变t的位置；把temp链接给p，会改变t的子链
    char ch;
    while (1)
    {
        ch = a[i++];
        temp = (BiTNode *)malloc(sizeof(BiTNode));
        temp->lchild = temp->rchild = NULL;
        temp->flag = 0;
        switch (ch)
        {
        case '0':
            p->lchild = temp;
            p = p->lchild;
            break;
        case '1':
            p->rchild = temp;
            p = p->rchild;
            break;
        default:
            p->flag = 1;
            return;
        }
    }
}
int judge(BinTree &t, char a[])
{
    BinTree p = t;
    int i = 0;
    char ch = a[0];
    while (ch != '\0')
    {
        if (ch == '0')
        {
            if (p->lchild == NULL)
            {
                Create(p, a, i);
                return 0;
            }
            else if (p->lchild->flag)
                return 1;
            else
                p = p->lchild;
        }
        else
        {
            if (p->rchild == NULL)
            {
                Create(p, a, i);
                return 0;
            }
            else if (p->rchild->flag)
                return 1;
            else
                p = p->rchild;
        }
        ch = a[++i];
    }
    return 1;
}
int main()
{
    BinTree root;
    root = (BiTNode *)malloc(sizeof(BiTNode));
    root->lchild = root->rchild = NULL;
    char IN[50000];
    long long n;
    cin >> n;
    while (n--)
    {
        cin >> IN;
        if (judge(root, IN))
        {
            cout << IN << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
}