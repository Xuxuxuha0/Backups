#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    long long n, all1 = 0, all2 = 0, bll1 = 0, bll2 = 0, temp, a, b;
    cin >> n;
    all1 = (1 + n) * n / 2;
    bll1 = n * (n + 1) * (2 * n + 1) / 6;
    for (int i = 0; i < n - 2; i++)
    {
        cin >> temp;
        all2 += temp;
        bll2 += temp * temp;
    }
    a = all1 - all2; //求两者之和
    b = bll1 - bll2; //求两者平方和
    b = (a * a - b) / 2;
    all1 = (a - sqrt(a * a - 4 * b)) / 2;
    all2 = (a + sqrt(a * a - 4 * b)) / 2;
    cout << all1 << ' ' << all2 << endl;
}