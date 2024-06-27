#include "DataList.h"

void Insert(DataList &List, int L, int R) // 插入排序
{
    Datatype temp;
    int i, j;
    for (i = L + 1; i <= R; i++)
        if (List.data[i] < List.data[i - 1])
        {
            temp = List.data[i];
            for (j = i - 1; j >= L && List.data[j] > temp; j--) // 依次往后挪
                List.data[j + 1] = List.data[j];
            List.data[j + 1] = temp;
        }
}
