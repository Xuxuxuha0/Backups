#include <iostream> //完全背包进阶版
using namespace std;
int main()
{
    int Weight, N, weight[100], value[100]; //背包容量，物品种类，物品的重量和价值(从1开始)
    cin >> Weight >> N;
    for (int i = 1; i <= N; i++)
        cin >> weight[i] >> value[i];
    int dp[100]; //进阶版：dp[j]的含义：当前背包剩余j容量，从前i个商品(i的信息包含在for循环中)里面选，所得到的最大价值

    for (int j = 0; j <= Weight; j++) //初始化
        dp[j] = 0;

    for (int i = 1; i <= N; i++)                  //动态规划填表，直到i=N，dp[Weight]
        for (int j = weight[i]; j <= Weight; j++) //直接从能放下i的情况开始（放不下的情况就保留i-1行的数据）
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
    //状态转移方程：dp[i][j]=max(dp[i-1][j],dp[i][j-weight[i]]+value[i]):要么不拿i，要么在前面拿了未知个i的基础上，再拿一个i，比较二者大小。再根据后无效性原则，省略一维坐标
    cout << dp[Weight];
}
