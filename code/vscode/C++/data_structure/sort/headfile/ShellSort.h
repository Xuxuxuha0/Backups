#include "DataList.h"
void Gap_InsertSort(DataList &L, int start, int end, int gap) // 插入排序的变形：[start,end]  间隔为gap的插入排序
{
    Datatype temp;
    int i, j;
    for (i = start + gap; i <= end; i += gap)
    {
        if (L.data[i - gap] > L.data[i])
        {
            temp = L.data[i];
            j = i;
            do
            {
                L.data[j] = L.data[j - gap]; // 用前面一个值覆盖当前值
                j -= gap;
            } while (j - gap >= start && L.data[j - gap] > temp);
            L.data[j] = temp;
        }
    }
}
void ShellSort(DataList &L, int d[], int m) // 对L中的元素升序，d[0,m-1]中存增量序列，d[0]=1;
{
    int gap;
    for (int i = m - 1; i >= 0; i--)
    {
        gap = d[i];
        for (int j = 0; j < gap; j++) // 从0,1,2...开始，以gap为间隔对这些序列排序。直到过完一个gap周期。
            Gap_InsertSort(L, j, L.n - 1, gap);
    }
}
/*
主函数：先循环gap数组，再对每个gap值循环“一个周期”的gap型插入排序
次函数：以[left,right]为范围，gap为间隔的插入排序
*/