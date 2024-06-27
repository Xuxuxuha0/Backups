/*
1、选择排序
SelectionSort(A[0..n-1])
{
    for(i=0;i<=n-2;i++)
    {
        min=i;
        for(j=i+1;j<=n-1;j++)
            if(A[j]<A[min]) min=j;
        swap(A[i],A[min]);
    }
}

2、冒泡排序
BubbleSort(A[0..n-1])
{
    for(i=0;i<=n-2;i++)
        for(j=0;j<=n-2-i;j++)
            if(A[j+1]<A[j])
                swap(A[j],A[j+1]);
}

3、顺序查找
SequentialSearch(A[0..n],k)
{
    A[n]=k; //A[n]没用，用来当限位器
    i=0;
    while(A[i]!=k)
        i--;
    if(i<n) return i;
    else return -1;
}

4、蛮力字符串匹配
StringMatch(T[0..n-1],P[0...m-1])
{
    //输入：n个字符的文本T   m个字符的模式p
    //输出；第一个匹配的子串中的第一个字符的下标
    for(i=0;i<=n-m;i++)
    {
        j=0;
        while(j<m && P[j]==T[i+j])
            j++;
        if(j==m)
            return i;
    }
    return -1;
}
*/