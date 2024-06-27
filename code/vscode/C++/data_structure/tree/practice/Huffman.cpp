#include <iostream>
using namespace std;
#define max 10000000
long long result;
typedef struct
{
    int weight;                 //权
    int parent, lchild, rchild; //三叉链表
} HTNode;
typedef struct
{
    HTNode elem[1000]; //需要用到的结点数组
    int num, root;     // HF树的外结点数、根的下标
} HFTree;
void CreateHFTree(HFTree &t, int n) //建立三叉链表形式的hf树
{
    int min1, min2, s1, s2;
    for (int i = 0; i < 2 * n; i++)                                  //要用到的下标范围是0--2*n-3，2*n-2是最后确定的根的位置
        t.elem[i].parent = t.elem[i].lchild = t.elem[i].rchild = -1; //表示还没有双亲和子女
    for (int i = n; i < 2 * n - 1; i++)                              //从下标n到2*n-2；选择最小的两棵权值树，合并出一棵新树
    {
        min1 = min2 = max;              //最小和次小
        s1 = s2 = 0;                    //最小和次小的下标
        for (int j = 0; j < i; j++)     //从0--i-1去找出最小和次小
            if (t.elem[j].parent == -1) //没有合并过的树
                if (t.elem[j].weight < min1)
                {
                    min2 = min1;
                    s2 = s1;
                    min1 = t.elem[j].weight;
                    s1 = j;
                }
                else if (t.elem[j].weight < min2)
                {
                    min2 = t.elem[j].weight;
                    s2 = j;
                }
        t.elem[s1].parent = t.elem[s2].parent = i;
        t.elem[i].lchild = s1;
        t.elem[i].rchild = s2;
        t.elem[i].weight = t.elem[s1].weight + t.elem[s2].weight;
    }
    t.num = n;
    t.root = 2 * n - 2;
}
void Calculate_WPL(HFTree t, int depth, int Root)
{
    if (t.elem[Root].lchild == -1)
        result += depth * t.elem[Root].weight;
    else
    {
        Calculate_WPL(t, depth + 1, t.elem[Root].lchild);
        Calculate_WPL(t, depth + 1, t.elem[Root].rchild);
    }
}
int main()
{
    int N;
    cin >> N;
    HFTree T;
    for (int i = 0; i < N; i++)
        cin >> T.elem[i].weight;
    CreateHFTree(T, N);
    Calculate_WPL(T, 0, T.root);
    cout << "WPL=" << result << endl;
}