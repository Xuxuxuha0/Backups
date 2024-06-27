#include <stdio.h> //p122
#include <stdlib.h>
#include <string.h>
int *c;
int search(int tl, int tr, int tk) //找出下标为tl到tr中的第tk小元素,分为大于、等于、小于三段处理
{
    int t, t2;

    t = c[tl]; //让最中间的元素放在第一个位置，成为哨兵p（分界）
    c[tl] = c[(tl + tr) / 2];
    c[(tl + tr) / 2] = t;

    int p = c[tl], s = tl, s2 = s; // s指向数组中最后一个小于p的元素，s2指向最后一个等于p的元素（将数组分为三段）
    for (int i = tl + 1; i <= tr; i++)
    {
        if (c[i] < p) //处理小于p的元素
        {
            if (i - s > 1)
            {
                if (c[s2] == p && c[s2 + 1] > p) //情况一
                {
                    t = c[++s2];
                    c[s2] = p;
                    c[++s] = c[i];
                    c[i] = t;
                }
                else //情况二
                {
                    t = c[++s];
                    c[s] = c[i];
                    c[i] = t;
                    s2++;
                }
            }
            else // i元素小于p，且就是s的下一个元素
            {
                s++;
                s2++;
            }
        }
        else if (c[i] == p) //处理等于p的元素
        {
            t = c[++s2];
            c[s2] = p;
            c[i] = t;
        }
    }

    t = c[tl]; //最后把p和s（最后一个小于p的元素）交换
    c[tl] = c[s];
    c[s] = t;

    if (tl + tk - 1 >= s && tl + tk - 1 <= s2) //对分段的数组分类讨论tk所在的区间
        return c[s];
    else if (tl + tk - 1 < s)
        return (search(tl, s - 1, tk));
    else
        return (search(s2 + 1, tr, tl + tk - s2 - 1));
}
int main()
{
    int n, *a, T, flag, k, x, l, r;
    scanf("%d", &n);                          //元素个数
    a = (int *)malloc((2 * n) * sizeof(int)); //用于存储的动态数组
    c = (int *)malloc((2 * n) * sizeof(int)); //用于操作的动态数组
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    scanf("%d", &T); //操作次数
    while (T--)
    {
        scanf("%d", &flag); // 1表示修改  2表示查找
        if (flag == 1)
        {
            scanf("%d%d", &k, &x);
            a[k] = x;
        }
        else
        {
            scanf("%d%d%d", &l, &r, &k);
            memcpy(c, a + l, (r - l + 1) * sizeof(a[0])); //从a[l]开始，复制（r-l+1）个元素
            printf("%d\n", search(0, r - l, k));
        }
    }
}