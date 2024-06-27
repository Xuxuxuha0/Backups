#include <iostream>
using namespace std;
int cnt;
void Queen(int chess[], int i) //考虑第i个皇后
{
    if (i > 8)
    {
        cout << ++cnt << ":";
        for (int j = 1; j <= 8; j++)
            cout << "(" << j << "," << chess[j] << ") ";
        cout << endl;
        return;
    }
    for (int j = 1; j <= 8; j++)
    {
        int k;
        chess[i] = j;
        for (k = 1; k < i; k++)
            if (chess[i] == chess[k] || i - k == chess[i] - chess[k] || k - i == chess[i] - chess[k]) // i皇后和之前的皇后在同一列，或者在对角线，就剪枝
                break;
        if (k == i)
            Queen(chess, i + 1);
    }
}
int main()
{
    int Chess[9];
    for (int i = 1; i <= 8; i++)
    {
        Chess[1] = i;    //先直接确定第一个皇后
        Queen(Chess, 2); //从第二皇后开始深搜
    }
}