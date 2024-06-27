#include <iostream>
#include <string.h>
using namespace std;
int L, S, T, M;
int main()
{
    cin >> L >> S >> T >> M;
    int *flag = new int[L + 5];
    for (int i = 0; i < L + 5; i++) //初始化
        flag[i] = 0;
    int temp, i = 0;
    while (i < M)
    {
        cin >> temp;
        flag[temp] = 1;
        i++;
    }
    int *dp = new int[L + S];
    for (int i = 0; i < S; i++) //初始化不可跳的位置
        dp[i] = 1000;
    for (int i = S; i <= T; i++) //初始化[s,t]这个区间的位置，要么是0，要么是1
        dp[i] = flag[i];
    for (int i = T + 1; i < L + S; i++) //动态规划计算出每个位置的最小值
    {
        dp[i] = 1000;
        for (int j = S; j <= T; j++)
            dp[i] = min(dp[i], dp[i - j] + flag[i]);
    }
    int result = 1000;
    for (int i = L; i < L + S; i++) //最终要考虑[L,L+S-1]这个区间的最小值
        result = min(result, dp[i]);
    cout << result << endl;
}
/*
今天运气很不好，要过河的独木桥上有很多的小石子，老师和小朋友们都不喜欢踩小石子。这时候万恶的数学老师数学兔跳了出来，希望小朋友们能计算一下过独木桥最少能踩多少个石子。

把独木桥看作一维整数数轴

起点为0，终点为L (即独木桥的长度为L

一次可以跳[S,T]的距离，在此区间范围内均为合法的跳跃距离

有M个石子

目标是确定最少可以踩多少个石子即可过河
*/