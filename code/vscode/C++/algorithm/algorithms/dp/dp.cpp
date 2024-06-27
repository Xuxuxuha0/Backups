/*
整数线性规划：
即给定序列a1, a2,…,an,
求:max(c1x1+ c2x2+…+ cnxn)
满足 a1x1+ a2x2+…+ anxn <= b,  xi为非负整数

问题转化：给定物品价值c[i]，物品重量a[i]，求在总重量小于等于b的前提下，如何拿物品(物品i拿x[i]个)使得价值最大？
完全背包问题
设dp[i][j]表示：从1..i的商品中拿，背包还剩j的容量，所能得到的最大价值;
问题最终求dp[n][b];
dp[i][j]=max(dp[i-1][j],dp[i][j-a[i]]+c[i])

DP()
{
    for(int i=1;i<=n;i++)
        dp[i]=0; //即dp[0][j]=0
    for(int i=1;i<=n;i++)
        for(int j=a[i];j<=b;j++) //直接从可以装下i开始，暗含了i的个数无限
            dp[j]=max(dp[j],dp[j-a[i]]+c[i]); //由于是顺向的，dp[j-a[i]]等价于dp[i][j-a[i]];
    return dp[b];
}


数字三角形(优化为一维)：
DP(A[1..n][1..n])
{
    //输入：A数组
    dp[1]=A[1][1];
    for(int i=2;i<=n;i++)
    {
        dp[i]=A[i][i]+dp[i-1];
        for(int j=i-1;j>=2;j--)
        {
            temp=(dp[j]>dp[j-1])?dp[j]:dp[j-1];
            dp[j]=temp+A[i][j];
        }
        dp[1]=A[i][1]+dp[1];
    }
    return max(dp[1]..dp[n]);
}
时间复杂度：O(n2)


游艇问题：
DP()
{
    cin>>n;
    for(int i=1;i<n;i++)
        for(int j=i+1;j<=n;j++)
            cin>>A[i][j];
    for(int i=2;i<=n;i++)
        dp[i]=INT_MAX;
    dp[1]=0;
    for(int i=2;i<=n;i++)
        for(int j=1;j<=i-1;j++)
            if(dp[i]>dp[j]+A[j][i])
                dp[i]=dp[j]+A[j][i];
    return dp[n];
}
时间复杂度：最耗时的是两重for循环，基本操作是'>'，O(n2)



最长公共子序列
x[1..m]   y[1..n]
设c[i][j]是x[1..i]和y[1..j]的最长公共子序列的长度：
c[i][j]= 0                        i=0||j=0;
        c[i-1][j-1]+1             i>0,j>0,x[i]=y[j];
        max(c[i-1][j],c[i][j-1])  i>0,j>0,x[i]!=y[j];
b[i][j]用于记录；
void DP()
{
    for(int i=0;i<=m;i++)
        c[i][0]=0;
    for(int j=0;j<=n;j++)
        c[0][j]=0;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
        {
            if(x[i]==y[j])
            {
                c[i][j]=c[i-1][j-1]+1;
                b[i][j]=1;
            }
            else if(c[i-1][j]>=c[i][j-1])
            {
                c[i][j]=c[i-1][j];
                b[i][j]=2;
            }
            else
            {
                c[i][j]=c[i][j-1];
                b[i][j]=3;
            }
        }
}
void TraceBack(i,j)
{
    if(i==0||j==0)
        return;
    if(b[i][j]==1)
    {
        TraceBack(i-1,j-1);
        cout<<x[i];
    }
    else if(b[i][j]==2)
        TraceBack(i-1,j);
    else
        TraceBack(i,j-1);
}


最大子段和
设b[j]表示a[1..j]且包含a[j]的最大子段和
b[j]=max(a[j],a[j]+b[j-1]);
int maxSum1(n,a)
{
    int sum=0,b=0;
    for(int i=1;i<=n;i++)
    {
        if(b>0) //此处b等价于b[j-1]
            b+=a[i];
        else b=a[i];
        if(b>sum)
            sum=b;
    }
    return sum;
}


最大子矩阵和
int maxSum2(A[1..m][1..n])
{
    int sum=0;
    int *b=new int[n+1];
    for(int i=1;i<=m;i++)
    {
        for(int k=1;k<=n;k++)
            b[k]=0;
        for(int j=i;j<=m;j++)
        {
            for(int k=1;k<=n;k++)
                b[k]+=a[j][k];
            int t=maxSum1(n,b);
            if(t>sum)
                sum=t;
        }
    }
}

最大m子段和问题
设b[i][j]:前j项的i个最大子段和,且第i个子段包含a[j]

b[i][j]:b[i-1][i-1]+a[j];  i==j
        max(b[i][j-1]+a[j],a[i-1][t]+a[j]);  i<j && i-1<=t<j
        0  i==0||j==0
int maxSum()
{
    for(int i=0;i<=m;i++)
        b[i][0]=0;
    for(int i=0;i<=n;i++)
        b[0][i]=0;
    for(int i=1;i<=m;i++)
    {
        b[i][i]=b[i-1][i-1]+a[i];
        for(int j=i+1;j<=n;j++)
            for(int t=i-1;t<j;t++)
                b[i][j]=max(b[i][j-1]+a[j],b[i-1][t]+a[j]);
    }
    return b[m][n];
}

int maxSum() //改进版：一维+记录
{
    for(int i=0;i<=n;i++)
        b[i]=0;
    for(int i=1;i<=m;i++)
    {
        for(int k=i-1;k<=n;k++)
            record[k]=b[k]; //先记录i-1的数据，由于用到的从i-1列开始，只copy所需即可
        b[i]=record[i-1]+a[i];
        for(int j=i+1;j<=n;j++)
            for(int t=i-1;t<=j;t++)
                b[j]=max(b[j-1]+a[j],record[t]+a[j]); //前者用i行的新数据，后者用i-1行的旧数据
    }
}



















*/