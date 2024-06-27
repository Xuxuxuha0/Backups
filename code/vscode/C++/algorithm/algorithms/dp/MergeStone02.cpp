#include <iostream> //环形石子合并问题
using namespace std;
#define MAXNUM 10000000
int n;
int sum[205][205];
int a[205];
int MIN[205][205];
int MAX[205][205];
int DP_min(int i, int j)
{
    if (i == j)
    {
        sum[i][i] = a[i];
        return 0;
    }
    if (MIN[i][j] != 0)
        return MIN[i][j];
    MIN[i][j] = MAXNUM;
    for (int k = i; k < j; k++)
        MIN[i][j] = min(MIN[i][j], DP_min(i, k) + DP_min(k + 1, j));
    sum[i][j] = sum[i][i] + sum[i + 1][j];
    MIN[i][j] += sum[i][j];
    return MIN[i][j];
}
int DP_max(int i, int j)
{
    if (i == j)
        return 0;

    if (MAX[i][j] != 0)
        return MAX[i][j];

    for (int k = i; k < j; k++)
        MAX[i][j] = max(MAX[i][j], DP_max(i, k) + DP_max(k + 1, j));

    MAX[i][j] += sum[i][j];
    return MAX[i][j];
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = n + 1; i < 2 * n; i++) //例如环形1234转化为直线型：1234123 则共有1234，2341，3412，4123不同的方案
        a[i] = a[i - n];
    int maxnum = 0, minnum = MAXNUM;
    for (int c = 1; c <= n; c++)
        minnum = min(minnum, DP_min(c, c + n - 1));
    for (int c = 1; c <= n; c++)
        maxnum = max(maxnum, DP_max(c, c + n - 1));
    cout << minnum << endl;
    cout << maxnum << endl;
}