// 最近点对问题
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
typedef struct
{
    double x, y;
} Point;
bool cmpx(Point a, Point b)
{
    return a.x < b.x;
}
bool cmpy(Point a, Point b)
{
    return a.y < b.y;
}
Point *v; // 存放点

double distance(int left, int right) // 暴力求解2-3个点对的最小距离
{
    if (right - left == 1)
        return sqrt(pow(v[right].x - v[left].x, 2) + pow(v[right].y - v[left].y, 2));
    else
    {
        double d1 = pow(v[left + 1].x - v[left].x, 2) + pow(v[left + 1].y - v[left].y, 2);
        double d2 = pow(v[right].x - v[left + 1].x, 2) + pow(v[right].y - v[left + 1].y, 2);
        double d3 = pow(v[right].x - v[left].x, 2) + pow(v[right].y - v[left].y, 2);
        double Min = min(d1, d2);
        Min = min(Min, d3);
        return sqrt(Min);
    }
}

double Cpair(int left, int right)
{
    int n = right - left + 1; // 区间的点个数

    if (n <= 3) // 直接暴力求解
        return distance(left, right);

    int pm = ceil(n / 2) - 1 + left; // 中轴的下标

    double d1 = Cpair(left, pm); // 对[left,pm]求最小距离
    double d2 = Cpair(pm + 1, right);

    double min_d = (d1 > d2) ? d2 : d1;
    double m = v[pm].x;      // 中轴的x坐标
    Point *s = new Point[n]; // 存储|x-m|<min_d的点    待改进：再开一个数组，分别保存左边、右边
    int cnt = 0;
    for (int i = pm; i >= left && m - v[i].x < min_d; i--) // 左边
    {
        s[cnt].x = v[i].x;
        s[cnt].y = v[i].y;
        cnt++;
    }
    for (int i = pm + 1; i <= right && v[i].x - m < min_d; i++) // 右边
    {
        s[cnt].x = v[i].x;
        s[cnt].y = v[i].y;
        cnt++;
    }
    sort(s, s + cnt, cmpy); // 根据y坐标排序

    double min_d2 = min_d * min_d; // 求s组中可能存在的最小距离；比较过程用平方，最后再根号，可以减少开根号的次数
    for (int i = 0; i <= cnt - 2; i++)
    {
        int j = i + 1;
        while (j < cnt && s[j].y - s[i].y < min_d)
        {
            min_d2 = min(min_d2, pow(s[j].x - s[i].x, 2) + pow(s[j].y - s[i].y, 2));
            j++;
        }
    }
    free(s);
    return sqrt(min_d2);
}
int main()
{
    int n;
    while (cin >> n && n)
    {
        v = new Point[n + 5];
        for (int i = 0; i < n; i++)
            scanf("%lf%lf", &v[i].x, &v[i].y);
        sort(v, v + n, cmpx);
        double ans = Cpair(0, n - 1) / 2;
        printf("%.2lf\n", ans);
        free(v);
    }
}