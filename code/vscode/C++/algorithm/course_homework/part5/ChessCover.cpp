#include <iostream> //此程序需要总结一下
#include <cmath>
using namespace std;
int a[1025][1025];
int b[1025][1025];
int cnt;
int judge(double x, double y, int a, int b) //根据中心点x，y和特殊点a，b判断特殊点在第几象限
{
    if (a < x)
    {
        if (b < y)
            return 1;
        else
            return 2;
    }
    else
    {
        if (b < y)
            return 3;
        else
            return 4;
    }
}
void ChessCover(double midx, double midy, int sx, int sy, int sca)
{
    if (sca == 1)
        return;
    int flag = judge(midx, midy, sx, sy);
    int tx = midx - 0.5, ty = midy - 0.5;
    switch (flag)
    {
    case 1:
        a[tx + 1][ty] = a[tx][ty + 1] = a[tx + 1][ty + 1] = cnt++;
        ChessCover(midx - sca / 4.0, midy - sca / 4.0, sx, sy, sca / 2);
        ChessCover(midx - sca / 4.0, midy + sca / 4.0, tx, ty + 1, sca / 2);
        ChessCover(midx + sca / 4.0, midy - sca / 4.0, tx + 1, ty, sca / 2);
        ChessCover(midx + sca / 4.0, midy + sca / 4.0, tx + 1, ty + 1, sca / 2);
        break;
    case 2:
        a[tx][ty] = a[tx + 1][ty] = a[tx + 1][ty + 1] = cnt++;
        ChessCover(midx - sca / 4.0, midy + sca / 4.0, sx, sy, sca / 2);
        ChessCover(midx - sca / 4.0, midy - sca / 4.0, tx, ty, sca / 2);
        ChessCover(midx + sca / 4.0, midy - sca / 4.0, tx + 1, ty, sca / 2);
        ChessCover(midx + sca / 4.0, midy + sca / 4.0, tx + 1, ty + 1, sca / 2);
        break;
    case 3:
        a[tx][ty] = a[tx][ty + 1] = a[tx + 1][ty + 1] = cnt++;
        ChessCover(midx + sca / 4.0, midy - sca / 4.0, sx, sy, sca / 2);
        ChessCover(midx - sca / 4.0, midy - sca / 4.0, tx, ty, sca / 2);
        ChessCover(midx - sca / 4.0, midy + sca / 4.0, tx, ty + 1, sca / 2);
        ChessCover(midx + sca / 4.0, midy + sca / 4.0, tx + 1, ty + 1, sca / 2);
        break;
    case 4:
        a[tx][ty] = a[tx + 1][ty] = a[tx][ty + 1] = cnt++;
        ChessCover(midx + sca / 4.0, midy + sca / 4.0, sx, sy, sca / 2);
        ChessCover(midx - sca / 4.0, midy - sca / 4.0, tx, ty, sca / 2);
        ChessCover(midx - sca / 4.0, midy + sca / 4.0, tx, ty + 1, sca / 2);
        ChessCover(midx + sca / 4.0, midy - sca / 4.0, tx + 1, ty, sca / 2);
        break;
    }
}
int JudgeDiffer(int x, int y)
{
    if (a[x + 1][y - 1] == a[x][y] && a[x + 1][y] == a[x][y])
        return 1;
    else if (a[x + 1][y] == a[x][y] && a[x + 1][y + 1] == a[x][y])
        return 2;
    else if (a[x][y + 1] == a[x][y] && a[x + 1][y + 1] == a[x][y])
        return 3;
    else
        return 4;
}
void change(int sca)
{
    cnt = 1;
    int flag;
    for (int i = 1; i <= sca; i++)
    {
        for (int j = 1; j <= sca; j++)
            if (b[i][j] == 0 && a[i][j] != 0)
            {
                flag = JudgeDiffer(i, j);
                switch (flag)
                {
                case 1:
                    a[i][j] = a[i + 1][j] = a[i + 1][j - 1] = cnt++;
                    b[i][j] = b[i + 1][j] = b[i + 1][j - 1] = 1;
                    break;
                case 2:
                    a[i][j] = a[i + 1][j] = a[i + 1][j + 1] = cnt++;
                    b[i][j] = b[i + 1][j] = b[i + 1][j + 1] = 1;
                    break;
                case 3:
                    a[i][j] = a[i][j + 1] = a[i + 1][j + 1] = cnt++;
                    b[i][j] = b[i][j + 1] = b[i + 1][j + 1] = 1;
                    break;
                case 4:
                    a[i][j] = a[i][j + 1] = a[i + 1][j] = cnt++;
                    b[i][j] = b[i][j + 1] = b[i + 1][j] = 1;
                    break;
                }
            }
    }
}
int main()
{
    int n, x, y;
    cin >> n >> x >> y;
    int scale = pow(2, n);
    cnt = 10000000;
    ChessCover((scale + 1.0) / 2, (scale + 1.0) / 2, x, y, scale);
    change(scale);
    for (int i = 1; i <= scale; i++)
    {
        for (int j = 1; j <= scale; j++)
            cout << a[i][j] << ' ';
        cout << endl;
    }
}