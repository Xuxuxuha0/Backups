#include <iostream>
using namespace std;
#define MaxSize 100
typedef int Datatype;
typedef struct //静态链表
{
    Datatype data;
    int link;
} SLNode;
typedef struct
{
    SLNode elem[MaxSize];
    int n;
} StaticList;
void CreateSList(StaticList &SL, Datatype a[], int n) //根据a数组创建静态链表，从下标1开始
{
    for (int i = 0; i < n; i++)
    {
        SL.elem[i + 1].data = a[i];
        SL.elem[i + 1].link = i + 2; //初始化为顺序相连构成环
    }
    SL.elem[0].data = INT_MAX; // 0位置不用
    SL.elem[0].link = 1;
    SL.elem[n].link = 0;
}