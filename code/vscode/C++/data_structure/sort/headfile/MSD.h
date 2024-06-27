//从高位到低位的基数排序
#include <iostream>
using namespace std;
#define radix 10 //十进制数的排序
#define d 3      //最大三位数
#define MaxSize 20
int GetDigit(int x, int k) //从整数x中提取第k位数字，最高位k=1
{
    if (k < 1 || k > d)
        return -1;                   //不合法
    for (int i = 1; i <= d - k; i++) // for循环退出后，第k位数字处在个位
        x /= 10;
    return x % 10;
}
void MSDsort(int A[], int left, int right, int k) //对第k位排序
{
    if (left >= right || k > d)
        return;

    int count[radix]; // count[x]:在处理第k位数时，各个元素第k位等于x的有多少个
    for (int i = 0; i < radix; i++)
        count[i] = 0;
    int *record = new int[right - left + 1]; //记录每个元素第k位是什么，left对应0
    for (int i = left; i <= right; i++)      //统计，也就是每个"桶"的元素个数
    {
        record[i - left] = GetDigit(A[i], k);
        count[record[i - left]]++;
    }

    int position[radix]; //每个桶的起始位置
    position[0] = 0;
    for (int i = 1; i < radix; i++)
        position[i] = position[i - 1] + count[i - 1];

    int *temp = new int[right - left + 1]; //暂存结果
    for (int i = left; i <= right; i++)
        temp[position[record[i]]++] = A[i];

    for (int i = left, j = 0; i <= right; i++, j++) //写入原数组
        A[i] = temp[j];

    free(record);
    free(temp);

    int p1 = left, p2;
    for (int i = 0; i < radix; i++) //递归地对子桶进行处理；比如k=1时，上面操作将元素按最高位分为了几个桶，再对这几个桶继续按下一位排序。
    {
        p2 = p1 + count[i] - 1;
        MSDsort(A, p1, p2, k + 1);
        p1 = p2 + 1;
    }
}