/*
伪代码集合：

1、归并排序
MergeSort(A[0,n-1])
{
    //输入：A数组
    //输出：升序数组A
    if(n>1)
    {
        copy A[0,n/2-1] to B[0,n/2-1];
        copy A[n/2,n-1] to C[0,ceil(n/2)-1];//ceil向上取整
        MergeSort(B[0,n/2-1]);
        MergeSort(C[0,ceil(n/2)-1]);
        Merge(B,C,A);
    }
}
Merge(B[0,p-1],C[0,q-1],A[0,p+q-1])
{
    //输入：两个有序数组B、C
    //输出：有序序列A
    i=0;
    j=0;
    k=0;
    while(i<p&&j<q)
    {
        if(B[i]<=C[j])
        {
            A[k]=B[i];
            i++;
            k++;
        }
        else
        {
            A[k]=C[j];
            j++;
            k++;
        }
    }
    if(i=p)
        copy(C[j,q-1],A[k,p+q-1]);
    else
        copy(B[i,p-1],A[k,p+q-1]);
}

2、快速排序

快排算法使用了Hoare两次扫描方法：与Lomuto算法不同，从子数组的两端扫描与中轴元素比较。
1、指针i从数组左边开始扫描，忽略小于中轴的元素，遇到大于等于中轴的元素A[i]时停止。
2、指针j从数组右边开始扫描，忽略大于中轴的元素，遇到小于等于中轴的元素A[j]时停止，然后交换A[i]和A[j]。
3、指针不相交则继续。
4、最后停下来时i=j，则A[i]就是p。

HoarePartition(A[L,R])
{
    //输入：A
    //输出：划分好的A
    p=A[L];
    i=L;
    j=R+1;
    while(i<j)
    {
        do i++
            while(A[i]<p && i<R);//注意i可能会越界
        do j--
            while(A[j]>p);
        swap(A[i],A[j]);
    }
    swap(A[i],A[j]);//取消最后一次交换
    swap(A[l],A[j]);//把p放在对应位置
    return j;
}
QuickSort(A[L,R])
{
    if(L<R)
    {
        s=HoarePartition(A[L,R]);
        QuickSort(A[L,S-1]);
        QuickSort(A[S+1,R]);
    }
}
*/