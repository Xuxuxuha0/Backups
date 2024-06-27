#include <iostream>
#include <algorithm>
using namespace std;
struct point
{
    double x, y;
} p[10];
bool cmpx(point p, point q) //对结构体按某一元素排序
{
    return p.x < q.x;
}
int main()
{
    p[0].x = 5.0;
    p[1].x = 3.0;
    p[2].x = 10.0;
    p[3].x = 6.0;
    p[4].x = 3.0;
    p[0].y = 2.0;
    p[1].y = 8.0;
    p[2].y = 1.0;
    p[3].y = 0.0;
    p[4].y = 6.0;
    sort(p, p + 5, cmpx); //对结构体按某一元素排序
    for (int i = 0; i < 5; i++)
        printf("%.2lf %.2lf\n", p[i].x, p[i].y);
}
