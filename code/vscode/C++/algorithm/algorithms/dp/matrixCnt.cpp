#include <iostream>
using namespace std;
#define maxNum 1000000000
int a[150];
long long dp[150][150];
int flag[150][150]; // flag[i][j]表示:矩阵链A[i..j]断开为A[i..flag[i][j]],A[flag[i][j]+1,j];
void Cnt(int n)
{
    int record;
    for (int i = 1; i <= n; i++)
        dp[i][i] = 0;
    for (int i = 2; i <= n; i++)
        for (int j = i - 1; j >= 1; j--) //计算dp[j][i]，j一定要倒着取
        {
            dp[j][i] = maxNum;
            record = -1;
            for (int k = j; k < i; k++)
            {
                long long t = dp[j][k] + dp[k + 1][i] + a[j] * a[k + 1] * a[i + 1];
                if (dp[j][i] > t)
                {
                    dp[j][i] = t;
                    record = k;
                }
            }
            flag[j][i] = record;
        }
}
void Print(int i, int j)
{
    if (i == j)
    {
        cout << "A" << i;
        return;
    }
    cout << "(";
    Print(i, flag[i][j]);
    Print(flag[i][j] + 1, j);
    cout << ")";
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n + 1; i++)
        scanf("%d", &a[i]);
    Cnt(n);
    cout << dp[1][n] << endl;
    if (n == 1)
        cout << "(A1)";
    else
        Print(1, n);
    cout << endl;
}
