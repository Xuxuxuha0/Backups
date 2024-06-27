/*
伪代码集合：

1、高斯消去法
化为上三角矩阵
    Elimination(A[1..n][1..n]],b[1..n])
    {
        //输入：系数矩阵A[N][N]和列向量b[n]。
        //输出：上三角矩阵
        for(i=1;i<=n;i++) A[i][n+1]=b[i];
        for(i=1;i<n;i++)
        {
            p=i;//先设第i行第i个元素为哨兵
            for(j=i+1;j<=n;j++)//再看第j行第i列谁绝对值最大
                if(fabs(A[j,i])>fabs(A[p,i]))
                    p=j；
            for(k=i;k<=n+1;k++)//交换i行和p行
                swap(A[i][k],A[p][k]);
            for(j=i+1;j<=n;j++)//消元
            {
                temp=A[j][i]/A[i][i];
                for(k=i;k<=n+1;k++)
                    A[j][k]=A[j][k]-A[i][k]*temp;
            }
        }
    }
反向替换
    Calculate_x(A[1..n+1][1..n+1])
    {
        //输入：上三角矩阵A[n+1][n+1]
        //输出：xi的结果数组B[n]
        for (i = n; i > 0; i--)
        {
            B[i] = A[i][N + 1] / A[i][i];   //计算出Xi
            for (int k = i - 1; k > 0; k--) //把上面每一行的结果减去含Xi的项
                A[k][n + 1] -= A[k][i] * B[i];
        }
    }

2、堆和堆排序

用自底向上算法构造一个堆
HeapBottomUp(H[1...n])
{
    for (i = n / 2; i >= 1; i--)
    {
        k = i;
        temp = H[k];
        flag = false; //表示需要向下比较
        while (!flag && 2 * k <= n)
        {
            j = 2 * k;
            if (j < n) //存在两个孩子
                if (H[j] < H[j + 1])
                    j++;   //取其中较大的一个孩子
            if (temp >= H[j]) //用较大的孩子进行比较
                flag = true;
            else
            {
                H[k] = H[j];//将孩子的值给k节点,并假装k结点的值已经是temp
                k = j;
            }
        }
        H[k] = temp; //temp赋给k结点
    }
}
堆中删除最大键
Delete(H[1...n])
{
    swap(H[1], H[n]); //交换第一个和最后一个元素
    flag = false;
    k = 1;
    temp = H[1];
    while (!flag && 2 * k < n)//自顶向下重新构造堆
    {
        j = 2 * k;
        if (j < n - 1)//H[n]肯定是不考虑的，已经固定了
            if (H[j] < H[j + 1])
                j++;
        if (temp >= H[j])
            flag = true;
        else
        {
            H[k] = H[j];
            k = j;
        }
    }
    H[k] = temp;
}
堆排序
HeapSort(A[1...n])
{
    //输出：升序数组A
    HeapBottomUp(H[1...n]);
    for(i=n;i>1;i++)
        Delete(A[1...i]);
}
*/