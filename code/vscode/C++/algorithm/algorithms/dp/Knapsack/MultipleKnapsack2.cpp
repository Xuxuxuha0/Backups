#include <iostream> //多重背包二进制进阶版
using namespace std;
int main()
{
    int Weight, N, weight[100], value[100], num[100], a, b, cnt = 0, k; //背包容量，物品种类，物品的重量、价值、数量(从1开始)
    cin >> Weight >> N;
    for (int i = 1; i <= N; i++) //多重背包转化为0-1背包,相当于有cnt个物品
    {
        cin >> a >> b >> num[i];
        k = 1;
        while (k <= num[i]) //由二进制分解一个数的思想，把num[i]分解为k1，k2...余数。比如说10=1+2+4+3。这样1-10都可以用这几个数表示出来。
        {
            cnt++;
            weight[cnt] = a * k;
            value[cnt] = b * k;
            num[i] -= k;
            k *= 2;
        }
        if (num[i] > 0) //余数
        {
            cnt++;
            weight[cnt] = a * num[i];
            value[cnt] = b * num[i];
        }
    }
    int dp[100]; //进阶版：dp[j]的含义：当前背包剩余j容量，从前i个商品(i的信息包含在for循环中)里面选，所得到的最大价值

    for (int j = 0; j <= cnt; j++) //初始化
        dp[j] = 0;

    for (int i = 1; i <= cnt; i++) //动态规划填表，直到i=cnt，dp[Weight]
        for (int j = Weight; j >= weight[i]; j--)
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);

    cout << dp[Weight];
}