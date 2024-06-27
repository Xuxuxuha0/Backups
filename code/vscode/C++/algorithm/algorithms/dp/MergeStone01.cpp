#include <iostream> //直线式石子合并问题
using namespace std;
#define MAXNUM 10000000
int n;
int sum[105][105];
int a[105];
int MIN[105][105];
int MAX[105][105];
int DP_min(int i, int j)
{
    if (i == j)
        return 0;
    if (MIN[i][j] != 0)
        return MIN[i][j];
    if (sum[i][j] == 0)
    {
        for (int k = i; k <= j; k++)
            sum[i][j] += a[k];
    }
    MIN[i][j] = MAXNUM;
    for (int k = i; k < j; k++)
        MIN[i][j] = min(MIN[i][j], DP_min(i, k) + DP_min(k + 1, j));
    MIN[i][j] += sum[i][j];
    return MIN[i][j];
}
int DP_max(int i, int j)
{
    if (i == j)
        return 0;
    if (MAX[i][j] != 0)
        return MAX[i][j];
    if (sum[i][j] == 0)
    {
        for (int k = i; k <= j; k++)
            sum[i][j] += a[k];
    }
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
    cout << DP_min(1, n) << endl;
    cout << DP_max(1, n) << endl;
}