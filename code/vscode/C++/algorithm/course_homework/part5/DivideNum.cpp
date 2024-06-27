#include <iostream>
using namespace std;
#define MAXNUM 400                       //最高次数
long long a[MAXNUM + 100][MAXNUM + 100]; // a[i][j]表示整数划分i，最大元素不超过j的划分方法
long long dynamic(int n, int max)        //动态规划处理整数划分问题(思路同递归)，速度更快
{
    a[1][1] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= i; j++)
        {
            if (j == 1)
                a[i][j] = 1;
            else
            {
                if (j == i)
                    a[i][j] = a[i][j - 1] + 1;
                else if ((i - j) < j)                        //判断：假设表达式已经含j，则剩下的i-j还能不能用j来表示
                    a[i][j] = a[i - j][i - j] + a[i][j - 1]; //若不能，则为：假设表达式已含j（且剩下最大大元素不超过i-j）+表达式中不含j
                else
                    a[i][j] = a[i - j][j] + a[i][j - 1]; //假设表达式中已经含j+表达式中不含j
            }
        }
    return a[n][max];
}
int main()
{
    int n;
    cin >> n;
    cout << dynamic(n, n) << endl;
    return 0;
}
/*
整数划分问题是将一个正整数n 划分为一系列正整数之和
如：n = 4
4
3+1
2+2 2+1+1
1+1+1+1
共计5种方法

输入一个正整数n
n -> [1,400]
*/