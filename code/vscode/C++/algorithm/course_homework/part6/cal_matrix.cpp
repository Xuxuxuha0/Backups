#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int BetterForwardElimination(double **A, int N) //高斯消元法求线性方程组
{
    int p;
    double temp;
    for (int i = 1; i < N; i++)
    {
        p = i;
        for (int j = i + 1; j <= N; j++)
            if (fabs(A[i][i]) < fabs(A[j][i]))
                p = j;
        if (A[p][i] == 0) //无解
            return 1;
        for (int k = i; k <= N + 1; k++)
            swap(A[i][k], A[p][k]); //内置函数
        for (int j = i + 1; j <= N; j++)
        {
            temp = A[j][i] / A[i][i];
            for (int k = i; k <= N + 1; k++)
                A[j][k] = A[j][k] - A[i][k] * temp;
        }
    }
    if (A[N][N] == 0)
        return 1;
    return 0;
}
void Calculate(double **A, int N) //求解上三角矩阵的解
{
    double *B = new double[N + 1];
    for (int i = N; i > 0; i--)
    {
        B[i] = A[i][N + 1] / A[i][i];   //计算出Xi
        for (int k = i - 1; k > 0; k--) //把以上每一行的结果减去含Xi的项
            A[k][N + 1] -= A[k][i] * B[i];
    }
    for (int i = 1; i < N + 1; i++)
        cout << fixed << setprecision(2) << B[i] << endl; // cout保留两位小数
}
int main()
{
    int n, j = 1, i;
    cin >> n;
    double **a = new double *[n + 1]; //从a[1]--a[n],从a[1][1]--a[1][n+1];
    while (j <= n)
    {
        a[j] = new double[n + 2];
        for (i = 1; i <= n + 1; i++)
            cin >> a[j][i];
        j++;
    }
    if (BetterForwardElimination(a, n))
    {
        cout << "No Solution" << endl;
        return 0;
    }
    else
        Calculate(a, n);
}