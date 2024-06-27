/*
一般的二维费用背包

有 N 件物品和一个容量是 V 的背包，背包能承受的最大重量是 M。

每件物品只能用一次。体积是 vi，重量是 mi，价值是 wi。

求解将哪些物品装入背包，可使物品总体积不超过背包容量，总重量不超过背包可承受的最大重量，且价值总和最大。
输出最大价值。

dp[i][j][k]:当前的背包容量为j，最大承重k，在前i个物品里面选择，得到最大价值

状态转移方程：dp[i][j][k]=max(dp[i-1][j][k],dp[i-1][j-v[i]][k-m[i]]+w[i]); //拿或不拿i

压缩数组后：dp[j][k]=max(dp[j][k],dp[j-v[i]][k-m[i]]+w[i]);
*/

/*
特殊的二维费用背包
关键是条件和状态转移方程不同

潜水员在水下工作最小需氧量为mina，最小需氮量为minb，有n个瓶子，每个瓶子重量w[i]，氧含量a[i]，氮含量b[i]，问最少携带的瓶子重量？

以下利用压缩数组。
方程右边的dp[j][k]:(在考虑第i个瓶子时) i-1行满足所需氧j氮k的最小载重
*/
#include <iostream>
using namespace std;
int main()
{
    int n, mina, minb, w[100], a[100], b[100], dp[100][100]; //最小需氧，最小需氮，瓶子重量，瓶子氧含量、氮含量
    cin >> mina >> minb >> n;
    memset(dp, 0x3f, sizeof(dp)); //先初始化为较大值
    dp[0][0] = 0;                 //不需要氧气和氮气时，就不要瓶子
    for (int i = 1; i <= n; i++)
        cin >> w[i] >> a[i] >> b[i];

    for (int i = 1; i <= n; i++)
        for (int j = mina; j >= 0; j++)     //循环氧气
            for (int k = minb; k >= 0; k++) //循环氮气
                if (j <= a[i] && k <= b[i]) //第i个瓶子能够完全满足需求，考虑拿还是不拿
                    dp[j][k] = min(dp[j][k], w[i]);
                else //以下展示了如何处理"是否满足两个条件中的某几个"的方法
                {
                    int x, y;         // x,y是拿i瓶子时的下标
                    if (j - a[i] < 0) //所需氧气小于i的氧气，则在考虑要不要拿i的时候可以不考虑氧气了
                        x = 0;
                    else
                        x = j - a[i];
                    if (k - b[i] < 0)
                        y = 0;
                    else
                        y = k - b[i];
                    dp[j][k] = min(dp[j][k], dp[x][y] + w[i]);
                }
    cout << dp[mina][minb];
}