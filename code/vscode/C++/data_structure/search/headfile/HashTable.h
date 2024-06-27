#include <iostream>
using namespace std;

#define size 11

enum State
{
    Active,
    Blank,
    Deleted
};

typedef int keytype;

typedef struct //元素
{
    keytype key;
} Elem;

typedef struct //"开地址法"的哈希表
{
    int divisor;  //散列函数的除数
    int n, m;     //已用地址数、最大地址数
    Elem *data;   //散列表元素数组
    State *state; //状态数组
    int *count;   //探查次数数组
} HashTable;

void InitHashTable(HashTable &H, int d) //初始化哈希表
{
    H.divisor = d;
    H.m = size;
    H.n = 0;
    H.data = new Elem[H.m];
    H.state = new State[H.m];
    H.count = new int[H.m];
    for (int i = 0; i < H.m; i++)
    {
        H.state[i] = Blank;
        H.count[i] = 0;
    }
}

int FindPosition(HashTable &H, keytype k, int &i) //线性探查法查找和k匹配的元素,若查找成功：i返回下标。若表不满，则返回i表示可以插入。
{
    i = k % H.divisor;

    if (H.state[i] == Active && H.data[i].key == k)
        return 1; //成功

    int j = i;
    do
    {
        if (H.state[i] == Active && H.data[i].key == k)
            return 1;
        else if (H.state[i] == Blank)
            return 0; //找到空位，可以放k
        i = (i + 1) % H.m;
    } while (i != j);

    return -1; //没找到且表满了
}