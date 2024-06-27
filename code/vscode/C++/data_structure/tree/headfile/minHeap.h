#include <iostream>
using namespace std;

#define size 40

typedef int DataType;

typedef struct // 小根堆
{
    DataType elem[size];
    int cursize; // 当前元素个数
} minHeap;

void siftdown(minHeap &H, int start, int n)
// 自顶向下调整，n表示末下标；直到temp<=子女
{
    int i = start, temp = H.elem[start];
    for (int j = 2 * i + 1; j <= n; j++)
    {
        if (j < n && H.elem[j] > H.elem[j + 1]) // j是i较大的一个子女
            j++;
        if (temp <= H.elem[j])
            break;
        else
        {
            H.elem[i] = H.elem[j];
            i = j;
        }
    }
    H.elem[i] = temp;
}
void CreateMinHeap(minHeap &H, int n) // 一共n个元素
{
    H.cursize = n;
    for (int i = (H.cursize - 2) / 2; i >= 0; i--) // 从最后一个元素的双亲开始，向下调整
        siftdown(H, i, H.cursize - 1);
}
int Remove(minHeap &H, DataType &x) // 删除最小值
{
    x = H.elem[0];
    H.elem[0] = H.elem[H.cursize - 1];
    H.cursize--;
    siftdown(H, 0, H.cursize - 1);
}

void siftup(minHeap &H, int start)
// 自底向上调整，直到双亲小于等于temp
{
    DataType temp = H.elem[start];
    int j = start, i = (j - 1) / 2; // i是j的双亲
    while (i >= 0)
    {
        if (H.elem[i] <= temp)
            break;
        else
        {
            H.elem[j] = H.elem[i];
            j = i;
            i = (i - 1) / 2;
        }
    }
    H.elem[j] = temp;
}
int Insert(minHeap &H, DataType x)
// 插入新节点
// 先插入最后，再自底向上调整
{
    H.elem[H.cursize] = x;
    siftup(H, H.cursize);
    H.cursize++;
}
