#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double **a; //动态二维数组
int n;
int cmp(const void *a, const void *b)
{
    double *c = *(double **)a;
    double *d = *(double **)b;
    return c[0] - d[0]; //如果是第二个元素排序就是c[1]与d[1]了
}
double distance(double x) //计算与每个点的距离
{
    double max = -1, temp;
    for (int i = 0; i < n; i++)
    {
        temp = sqrt(pow(x - a[i][0], 2) + pow(a[i][1], 2));
        if (temp > max)
            max = temp;
    }
    return max;
}
void judge(double L, double R) //四分法
{
    double left = (3 * L + R) / 4, right = (3 * R + L) / 4, Ldis, Rdis; //左边的四分点、右边的四分点
    Ldis = distance(left);
    Rdis = distance(right);
    if (right - left < 0.00001) //精度够高了
        printf("%.4lf\n", Ldis > Rdis ? Rdis : Ldis);
    else
    {
        if (Ldis > Rdis) //左边四分点的距离大，就把左边界当作左边四分点，继续四分
            L = left;
        else
            R = right;
        judge(L, R);
    }
}
int main()
{
    scanf("%d", &n);
    a = (double **)malloc((n + 5) * sizeof(double *)); //创建动态二维数组
    for (int i = 0; i < n; i++)
    {
        a[i] = (double *)malloc(2 * sizeof(double)); //对每一行创建一维数组
        scanf("%lf %lf", &a[i][0], &a[i][1]);
    }
    qsort(a, n, sizeof(double *), cmp); //二维数组按照a[i][0]的大小排序，参数n为要参与排序的行数
    double L = a[0][0], R = a[n - 1][0];
    judge(L, R);
}
/*
某块胡萝卜地有N个种有胡萝卜的胡萝卜坑，每个胡萝卜坑的位置可以由(x,y)进行表示。现在兔农想在田地边缘搭建一个乘凉棚，即x轴上的某个位置，希望这个位置到N个胡萝卜坑的最大距离是所有最大距离中最小的。请求出这个x值对应的最大距离。
到N个胡萝卜坑的最大距离:当x = k时，到A[i]胡萝卜坑的距离为D[i]，最大距离为MAX(D)
所有最大距离的最小值:遍历x，取MAX(D)中的最小值。

第一行为一个正整数N，表示胡萝卜坑的数量
接下来N行分别为x,y，一行表示一个胡萝卜坑的位置
N -> [1, 10^5]
x,y -> [-10^4, 10^4]
*/