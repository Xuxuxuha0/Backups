#include <iostream>
using namespace std;
#define HeapSize 100
typedef struct //大根堆
{
    int data[HeapSize]; //从0开始
    int n;              //当前元素个数
} MaxHeap;
void SiftDown(MaxHeap &H, int start, int end) //从start开始直到end,调整由于H.data[start]不合适引起的局部大根堆紊乱
{
    int i = start;
    int j = 2 * i + 1; // i的左子女
    int temp = H.data[i];
    while (j <= end)
    {
        if (j < end && H.data[j] < H.data[j + 1]) //如果j不是最后一个元素，就让j指向所属的两个子女中的最大的一个
            j++;
        if (temp >= H.data[j])
            break;
        H.data[i] = H.data[j];
        i = j; //考虑下一层
        j = 2 * i + 1;
    }
    H.data[i] = temp; //放在
}
void HeapSort(MaxHeap &H)
{
    for (int i = (H.n - 2) / 2; i >= 0; i--) //从最后一个元素的双亲开始，自底向上排序，成为大根堆
        SiftDown(H, i, H.n - 1);
    for (int i = H.n - 1; i > 0; i--)
    {
        int temp = H.data[0];
        H.data[0] = H.data[i]; //把data[0]，即最大的元素和倒数的元素交换
        H.data[i] = temp;
        SiftDown(H, 0, i - 1); //重新构造大根堆
    }
}