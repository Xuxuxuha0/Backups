#include <iostream>
using namespace std;
inline int read() //快读
{
    register int x = 0, f = 1;
    char c = getchar();
    if (c == '#')
        return INT_MAX;
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ 48); //等价于x*10+c-48,使用位运算加速
        c = getchar();
    }
    return x * f;
}