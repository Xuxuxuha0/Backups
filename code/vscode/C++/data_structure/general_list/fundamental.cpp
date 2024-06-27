#include <iostream>
using namespace std;
typedef struct node
{
    int tag;            // 0：原子 1：表节点
    int mark;           // 0：未访问 1：已访问
    struct node *tlink; //表尾指针
    union               //表头部分
    {
        char data;          // tag=0时，表头是个原子
        struct node *hlink; // tag=1时，表头是个表
    } val;
} GLNode, *GList;                             //节点分三种含义：1、NULL表示()或者)  2、tag=1表示(  3、tag=0表示原子
void CreateGList(char *s, int &i, GLNode *&g) //递归法创建广义表
{
    char ch = s[i++]; //取下一个待处理字符
    if (ch != '\0')   //不是结束符
    {
        if (ch == '(') //新节点是个表
        {
            if (s[i] == ')') //空表，什么都不用做，系统直接退栈，继续处理上一次操作
            {
                g = NULL;
                i++;
            }
            else
            {
                g = (GLNode *)malloc(sizeof(GLNode));
                g->tag = 1; //表的标志
                g->mark = 0;
                CreateGList(s, i, g->val.hlink); //先创建子表的表头
                CreateGList(s, i, g->tlink);     //再创建子表的表尾
            }
        }
        else if (ch == ')') //子表处理完毕，系统退栈即可
            g = NULL;
        else if (ch == ',') //','后面一定是表尾，即一定是个表
        {
            g = (GLNode *)malloc(sizeof(GLNode));
            g->tag = 1;
            g->mark = 0;
            CreateGList(s, i, g->val.hlink);
            CreateGList(s, i, g->tlink);
        }
        else //还剩下一种情况：是原子节点
        {
            g = (GLNode *)malloc(sizeof(GLNode));
            g->tag = 0;
            g->mark = 0;
            g->val.data = ch;
        }
    }
}
void PrintGList(GList L) // 该算法注定了L一定是表节点。前提是L为空直接输出(),或者L为原子直接输出它，不再调用此函数
{
    if (L->val.hlink == NULL) //表头节点为空，一定是()   不为空就输出
        cout << "()";
    else if (L->val.hlink->tag == 1)
    {
        cout << '(';
        PrintGList(L->val.hlink);
        cout << ')';
    }
    else
        cout << L->val.hlink->val.data;

    if (L->tlink != NULL) //尾节点不为空，在它之前一定有','，然后当作子表处理   为空，则不需要做什么
    {
        cout << ',';
        PrintGList(L->tlink);
    }
}
void DestroyGList(GList &L) //删除该广义表
{
    if (L == NULL) //空节点
        ;
    else if (L->tag == 0) //如果是原子节点，直接释放
        free(L);
    else //否则就是表节点，先释放尾，再释放头(顺序无所谓)，再释放该节点
    {
        DestroyGList(L->tlink);
        DestroyGList(L->val.hlink);
        free(L);
    }
}
GList GetHead(GList L) //得到表头节点，同时删除其他的
{
    GList p = L->val.hlink, q = L->tlink; //先存储表头和表尾
    DestroyGList(q);                      //释放表尾
    free(L);                              //释放该节点
    return p;                             //返回表头节点
}
GList GetTail(GList L) //得到表尾节点，同时删除其他的
{
    GList p = L->val.hlink, q = L->tlink; //先存储表头和表尾
    DestroyGList(p);                      //释放表头
    free(L);                              //释放该节点
    return q;                             //返回表尾
}
int main()
{
    GList G;
    char a[100];
    cin >> a;
    int pa = 0, n;
    CreateGList(a, pa, G);
    cout << "generic list: " << a << endl;
    while (G != NULL && G->tag != 0)
    {
        cin >> n;
        if (n == 1)
        {
            cout << "destroy tail" << endl;
            cout << "free list node" << endl;
            cout << "generic list: ";
            G = GetHead(G);
            if (G == NULL)
                cout << "()" << endl;
            else if (G->tag == 0)
                cout << G->val.data << endl;
            else
            {
                cout << '('; //先打印总体的大扩号
                PrintGList(G);
                cout << ')' << endl;
            }
        }
        else
        {
            cout << "free head node" << endl;
            cout << "free list node" << endl;
            cout << "generic list: ";
            G = GetTail(G);
            if (G == NULL)
                cout << "()" << endl;
            else if (G->tag == 0)
                cout << G->val.data << endl;
            else
            {
                cout << '(';
                PrintGList(G);
                cout << ')' << endl;
            }
        }
    }
}