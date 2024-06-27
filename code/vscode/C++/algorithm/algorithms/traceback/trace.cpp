/*
装载问题(01背包)：

递归版：
traceback(int i)
{
    if(i>n)
        {
            if(prs>best) //实际上这个条件多余了，能到最后一步肯定大于best
                {
                    best=prs;
                    for(int j=1;j<=n;j++)
                        bestx[j]=x[j]; //记录最优解
                }
            return;
        }
    rest-=w[i]; //不管拿不拿i，剩下的总重量都要减去他
    if(prs+w[i]<=weight) //能拿i则先试一试拿
    {
        x[i]=1; //用于构造最优解
        prs+=w[i];
        tracebak(i+1);
        x[i]=0;
        prs-=w[i];
    }
    if(prs+rest<=best) //再试一试不拿
        {
            x[i]=0;
            traceback(i+1);
        }
    rest+=w[i]; //当一个方案走到底之后要将rest回溯
}

非递归：



两台机器批作业问题：
求所有作业在机器2上完成的时间节点之和达到最小
traceback(int i)
{
    //初始化：x[i]=i;
    if(i>n)
    {
        best=prs;
        for(int j=1;j<=n;j++)
            bestx[j]=x[j];
        return;
    }
    for(int j=i;j<=n;j++) //产生全排列
    {
        t1+=time[x[j]][1]; //t1:机器1完成序列中前j个作业需要的时间.time[i][1]/[2]:i作业在机器1、2需要的时间
        t2[i]=max(t2[i-1],t1)+time[x[j]][2]; //计算“序列中第i个作业”(实际上是下标为x[j]的作业)在机器2完成的时间节点
        prs+=t2[i];
        if(prs<best)
        {
            swap(x[i],x[j]); //全排列的精髓：往后交换,把x[j]当作第i个作业,上面已经计算出所需时间,再计算第i个作业后面的所需时间即可。
            traceback(i+1);
            swap(x[i],x[j]); //回溯
        }
        t1-=time[x[j]][1]; //回溯
        prs-=t2[i];
    }
}

符号三角形
traceback(int i)
{
    //初始化：half=n*(n+1)/4;
    if((cnt>half)||(i*(i-1)/2-cnt)>half) //cnt表示当前+的个数，另一个表示-的个数
        return;
    if(i>n)
        sum++;
    else
    {
        for(int j=0;j<2;j++) //第一行第i个,j为0表示-，1表示+
        {
            x[1][i]=j;
            cnt+=j;
            for(int k=2;k<=i;k++) //计算新增列
            {
                x[k][i-k+1]=!(x[k-1][i-k+1] ^ x[k-1][i-k+2]); //异或符号^:相同为0
                cnt+=x[k][i-k+1];
            }
            traceback(i+1);
            for(int k=2;k<=i;k++) //回溯
                cnt-=p[k][i-k+1];
            cnt-=j;
        }
    }
}



















*/