/*
伪代码合集：

1、斐波那契数列
方程：
F(n) = F(n - 1) + F(n - 2)    n > 2;
F(1) = F(2) = 1;

Fab(n)
{
    if (n == 1 || n == 2)
        return 1;
    F1 = F2 = 1;
    for (i = 3; i <= n; i++)
    {
        temp = F2;
        F2 = F1 + F2;
        F1 = temp;
    }
    return F2;
}

2、币值最大化问题
方程：
F(n)=max{cn+F(n-2),F(n-1)} n>1;
F(0)=0,F(1)=c1;

CoinRow(C[1...n])
{
    F0=0;
    F1=c[1];
    for(i=2;i<=n;i++)
    {
        temp=F1;
        F1=max(F0+C[i],F1);
        F0=temp;
    }
    return F1;
}

3、找零问题
方程：
F(n)=min{F(n-dj)}+1; n>=dj
F(0)=0;

changeMake(D[1...m],n)
{
    //输入：升序D，总金额n
    F[0]=0;
    for(i=1;i<=n;i++)
    {
        temp=INT_MAX;
        j=1;
        while(j<=m&&i>=D[j])
        {
            temp=min(F[i-D[j]],temp);
            j++;
        }
        F[i]=temp+1;
    }
    return F[n];
}

4、硬币收集问题
方程：
F[i][j]=max{F[i-1][j],F[i][j-1]}+c[i][j];  i>1&&j>1
F[1][1]=c[1][1];
F[1][j]=F[1][j-1]+c[1][j];
F[i][1]=F[i-1][1]+c[i][1];

RobotCoin(c[1..n][1..m])
{
    //输入：硬币矩阵c
    F[1][1]=c[1][1];
    for(j=2;j<=m;j++)//第一行,只能从前一列来
        F[1][j]=F[1][j-1]+c[1][j];
    for(i=2;i<=n;i++)
    {
        F[i][1]=F[i-1][1]+c[i][1];//每行的第一列,只能从上一行来
        for(j=2;j<=m;j++)
            F[i][j]=max(F[i-1][j],F[i][j-1])+c[i][j];
    }
    return F[n][m];
}

5、背包问题和记忆性
方程：
F[i][j]=max(F[i-1][j],v[i]+F(i-1,j-w[i]))  j-w[i]>=0
F[i][j]=F[i-1][j]   j-w[i]<0
F[i][0]=0;F[0][j]=0;

Knapsack(w[1..n],v[1..n],weight)
{
    for(i=0;i<=n;i++) dp[i][0]=0;
    for(i=0;i<=weight;i++) dp[0][i]=0;
    for(i=1;i<=n;i++)
        for(j=1;j<=weight;j++)
        {
            if(j-w[i]>=0)
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-w[i]]+v[i]);
            else
                dp[i][j]=dp[i-1][j];
        }
    return dp[n][weight];
}

记忆功能：
自顶向下，同时使用visited[i][j]记录算出的值。
*/