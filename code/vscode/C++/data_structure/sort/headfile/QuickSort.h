//以下全为升序
#include <iostream>
#include "DataList.h" //必须用引号
#include "InsertSort.h"
using namespace std;

#define min 15 //小规模用插入排序

void Mid(DataList &List, int L, int R) //找出最左，最中，最右中的中间数，把它交换到最左边
{
    int mid = (L + R) / 2;
    int k1, k2;
    if (List.data[L] <= List.data[mid]) //让k2指向较大的，data[k2]>=data[k1]
    {
        k1 = L;
        k2 = mid;
    }
    else
    {
        k1 = mid;
        k2 = L;
    }
    if (List.data[R] < List.data[k1]) //再让k2指向中间者 data[k2]>=data[k1]>=data[R]
        k2 = k1;
    else if (List.data[R] < List.data[k2]) // data[k2]>=data[R]>=data[k1]
        k2 = R;
    if (k2 != L)
        swap(List.data[k2], List.data[L]);
}

int RowePartition(DataList &List, int L, int R)
{
    Mid(List, L, R); //先更换一下data[L]
    int k = L;
    int p = List.data[L]; //以最左边的为哨兵
    for (int i = L + 1; i <= R; i++)
        if (List.data[i] < p)
        {
            k++;
            swap(List.data[i], List.data[k]);
        }
    List.data[L] = List.data[k];
    List.data[k] = p;
    return k; //返回基准元素的下标
}

int HoarePartition(DataList &List, int L, int R)
{
    if (L < R)
    {
        Mid(List, L, R);
        int i = L, j = R;
        Datatype p = List.data[L];
        //轮换赋值过程：data[j]覆盖p，data[i]覆盖data[j]，data[j]覆盖data[i]...直到i==j，再让p覆盖data[i]。
        //最后i为p所在的下标，大于i部分都大于等于p，小于i部分都小于等于p
        do
        {
            while (i < j && p < List.data[j]) //直到data[j]<=p
                j--;
            if (i < j)
            {
                List.data[i++] = List.data[j];
                while (i < j && List.data[i] < p) //直到data[i]>=p
                    i++;
                if (i < j)
                    List.data[j--] = List.data[i];
            }
        } while (i < j);
        List.data[i] = p;
        return i;
    }
    return L; //在快排-插入排的混合排序下，L不可能大于等于R
}

void QuickSort(DataList &L, int left, int right) //最简单的快排(不建议用)
{
    if (left < right)
    {
        int p = HoarePartition(L, left, right);
        QuickSort(L, left, p - 1);
        QuickSort(L, p + 1, right);
    }
}

void QuickSort_Insert(DataList &List, int L, int R) //对List[L..R]排序
{
    if ((R - L + 1) <= min) //当子序列规模小于min时，就采用插入排序
        Insert(List, L, R);
    else //否则就快排
    {
        int p = RowePartition(List, L, R); //这里选择了Rowe单向划分，也可以选择Hoare双向划分法
        QuickSort_Insert(List, L, p - 1);
        QuickSort_Insert(List, p + 1, R);
    }
}
