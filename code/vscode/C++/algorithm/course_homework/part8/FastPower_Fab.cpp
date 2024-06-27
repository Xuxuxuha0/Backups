#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;
long long m;
struct mat
{
    long long a[2][2]; //矩阵
};
mat mul_mat(mat a, mat b) //两个矩阵相乘,返回矩阵
{
    mat ans;                        //结果
    memset(ans.a, 0, sizeof ans.a); //初始化
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
                ans.a[i][j] += a.a[i][k] * b.a[k][j];
            ans.a[i][j] %= m; //为什么在这个地方取余？
        };
    return ans;
}
long long quick_power(long long n, long long A, long long B)
{
    mat ans, res;
    //初始化结果矩阵(为了统一，写为2X2形式)
    ans.a[0][1] = 0;
    ans.a[1][1] = 0;
    ans.a[0][0] = B;
    ans.a[1][0] = A;
    //初始化系数矩阵
    res.a[0][0] = 1;
    res.a[0][1] = 1;
    res.a[1][0] = 1;
    res.a[1][1] = 0;

    while (n) //矩阵快速幂
    {
        if (n & 1)                   // n是奇数
            ans = mul_mat(res, ans); // res*ans得到一个中间结果矩阵
        n >>= 1;                     //指数/2
        res = mul_mat(res, res);     //底数平方
    }
    return ans.a[0][0]; // ans.a[0][0]即f(n)%m
}
int main()
{
    long long i, j;
    cin >> i >> j >> m;
    long long A = i - 1 + i * (1 + sqrt(5)) / 2, B = 2 * A - i + 1; //一个莫名其妙的公式求出了第一二项
    if (j == 1)
        cout << A % m << endl;
    else if (j == 2)
        cout << B % m << endl;
    else
        cout << quick_power(j - 2, A, B) << endl;
    return 0;
}
/*
1 2 3 5 8 13 21 34 55 89 144 ...

4 7 11 18 29 47 76 123 199 322 521 ...

6 10 16 26 42 68 110 178 288 466 754 ...

第一行是斐波那契数列
其余行也类似于斐波那契数列，但是第i行的第一个数是前i-1行中没有出现过的最小正整数，第二个数 = 第一个数*2-i+1

i和j从1开始编号
i表示第i行，j表示第j列
输出第i行第j列的数字对m取模的结果
*/