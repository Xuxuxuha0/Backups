#include <iostream> //由中序和后序还原二叉树，并按层次序输出
#include <string.h>
using namespace std;
#define size 30
typedef struct node
{
    char data;
    struct node *lchild, *rchild;
} BiTNode, *BinTree;
void CreateBinTree_IN_POST(BinTree &t, char in[], char post[], int s1, int s2, int t1, int t2) //根据中序和后序建立二叉树 所用post数组是后序反转之后的 可以画图举例理解
{
    if (s1 <= t1)
    {
        t = (BiTNode *)malloc(sizeof(BiTNode));
        t->data = post[s1];
        t->lchild = t->rchild = NULL;
        int i;
        for (i = s2; i <= t2; i++)
            if (in[i] == post[s1])
                break;
        CreateBinTree_IN_POST(t->rchild, in, post, s1 + 1, i + 1, s1 + t2 - i, t2); //右子树
        CreateBinTree_IN_POST(t->lchild, in, post, s1 + t2 - i + 1, s2, t1, i - 1); //左子树
    }
}
void LevelOrder(BinTree t) //层次遍历二叉树
{
    BiTNode *queue[size];
    int front = 0, rear = 0;
    BiTNode *p = t;
    queue[rear++] = p; //初始化
    while (rear != front)
    {
        p = queue[front]; //取队头
        front = (front + 1) % size;
        cout << p->data;
        if (p->lchild != NULL) //左子女进队列
        {
            queue[rear] = p->lchild;
            rear = (rear + 1) % size;
        }
        if (p->rchild != NULL) //右子女进队列
        {
            queue[rear] = p->rchild;
            rear = (rear + 1) % size;
        }
    }
    cout << endl;
}
void reverse(char post[]) //反转字符串
{
    int rear = strlen(post) - 1;
    char *p1 = &post[0], *p2 = &post[rear], ch;
    while (p1 < p2)
    {
        ch = *p2;
        *p2-- = *p1;
        *p1++ = ch;
    }
}
int main()
{
    char IN[size], POST[size];
    cin >> IN >> POST;
    // strrev(POST); //只能对字符数组反转,乐学不能用？
    reverse(POST);
    int S1 = 0, S2 = 0, T1 = strlen(POST) - 1, T2 = strlen(IN) - 1;
    BinTree root;
    CreateBinTree_IN_POST(root, IN, POST, S1, S2, T1, T2);
    LevelOrder(root);
}