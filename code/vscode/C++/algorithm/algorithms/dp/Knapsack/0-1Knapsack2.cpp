#include <iostream> //0-1背包进阶版
using namespace std;
int main()
{
    int Weight, N, weight[100], value[100]; // 背包容量，物品种类，物品的重量和价值(从1开始)
    cin >> Weight >> N;
    for (int i = 1; i <= N; i++)
        cin >> weight[i] >> value[i];
    int dp[100]; // 进阶版：dp[j]的含义：当前背包剩余j容量，从前i个商品(i的信息包含在for循环中)里面选，所得到的最大价值

    for (int j = 0; j <= Weight; j++) // 初始化
        dp[j] = 0;

    for (int i = 1; i <= N; i++)                  // 动态规划填表，直到i=N，dp[Weight]
        for (int j = Weight; j >= weight[i]; j--) // dp表具有"后无效性原则"：第i行只与第i-1行有关系。等号后面的的dp[x]其实是第i-1行的内容。但为了避免覆盖掉还没有用过的dp[j-weight[i]]，必须从后往前循环。 结论：有限个，逆算；无限个，正算。
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);

    cout << dp[Weight];
}