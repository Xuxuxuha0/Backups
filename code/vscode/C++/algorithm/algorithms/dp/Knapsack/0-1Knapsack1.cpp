#include <iostream> //0-1背包基础版
using namespace std;
int main()
{
    int Weight, N, weight[100], value[100]; //背包容量，物品种类，物品的重量和价值(从1开始)
    cin >> Weight >> N;
    for (int i = 1; i <= N; i++)
        cin >> weight[i] >> value[i];
    int dp[100][100]; // dp[i][j]的含义：当前背包剩余j容量，从前i个商品里面选，所得到的最大价值

    for (int i = 0; i <= N; i++) //初始化：0行0列为0
        dp[i][0] = 0;
    for (int j = 0; j <= Weight; j++)
        dp[0][j] = 0;

    for (int i = 1; i <= N; i++) //动态规划填表，直到dp[N][Weight]
        for (int j = 1; j <= Weight; j++)
            if (j < weight[i]) //如果背包放不下i物品了，就等价于从前i-1个里面选
                dp[i][j] = dp[i - 1][j];
            else //考虑拿或不拿i物品，价值谁更大
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);

    cout << dp[N][Weight];
}