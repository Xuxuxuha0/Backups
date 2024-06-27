#include "DataList.h"

void Merge(DataList &L, int left, int mid, int right) //将两个有序表[left,mid]和[mid+1,right]归并为一个有序序列
{
    int i = left, j = mid + 1;
    int cnt = right - left + 1;
    int k = 0;
    Datatype *newL = new Datatype[cnt + 1];
    while (i <= mid && j <= right)
    {
        if (L.data[i] <= L.data[j])
            newL[k++] = L.data[i++];
        else
            newL[k++] = L.data[j++];
    }
    while (i <= mid)
        newL[k++] = L.data[i++];
    while (j <= right)
        newL[k++] = L.data[j++];
    for (i = 0; i < cnt; i++)
        L.data[left + i] = newL[i];
    free(newL);
}

void MergeSort(DataList &L, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        MergeSort(L, left, mid); //先二分，再合
        MergeSort(L, mid + 1, right);
        Merge(L, left, mid, right);
    }
}
