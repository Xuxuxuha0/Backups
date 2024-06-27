#include <iostream>
using namespace std;
int *row, *col, *slash, *backslash; //列、正斜线(\)、反斜线的标记数组
int cnt;
int n, m;
void judge()
{
    for (register int i = 1; i <= n; i++)
        if (row[i]) //行安全
            for (register int j = 1; j <= n; j++)
                if (col[j])                                       //列也安全
                    if (slash[n - i + j] && backslash[i + j - 1]) //对角也安全
                        return;                                   //那这个位置就不受控制
    cnt++;
}
void SuperQueen(int i, int j) //第i行，第j个皇后
{
    if (n - i < m - j) //如果剩余的行数小于剩余的皇后数，直接剪枝
        return;
    if (j > m) //放完了
        judge();
    else //第i行
    {
        for (register int k = 1; k <= n; k++) //考虑放第k列
        {
            if (col[k] && slash[n - i + k] && backslash[i + k - 1]) //(i,k)安全
            {
                row[i] = col[k] = slash[n - i + k] = backslash[i + k - 1] = 0; //放进去并标记
                SuperQueen(i + 1, j + 1);
                row[i] = col[k] = slash[n - i + k] = backslash[i + k - 1] = 1; //回溯
            }
        }
        SuperQueen(i + 1, j); //所有列都考虑完了之后，再考虑不放第i行
    }
}
int main()
{
    cin >> n >> m;
    col = new int[n + 1];
    row = new int[n + 1];
    slash = new int[2 * n];               //对于坐标(i,j)，正斜线号为n-i+j
    backslash = new int[2 * n];           //反斜线号为i+j-1
    for (register int i = 1; i <= n; i++) //初始化为1，表示该列安全
        row[i] = col[i] = 1;
    for (register int i = 1; i <= 2 * n - 1; i++)
        slash[i] = backslash[i] = 1;
    SuperQueen(1, 1);
    cout << cnt << endl;
}
/*
皇后的控制力
思路：先安全的放置m个皇后，再检测能否掌控局面
*/