#include <iostream> //需要简化问题
using namespace std;
int Result(int a, int b)
{
    switch (a)
    {
    case 1:
        return 2;
    case 2:
        if (b == 1)
            return 3;
        else
            return 4;
    default:
        if (b == 1)
            return 4;
        else if (b == 2)
            return 7;
        else
            return 8;
    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    if (m == 0)
        cout << "1" << endl;
    else
        cout << Result(n, m) << endl;
}