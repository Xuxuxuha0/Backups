#include <stdio.h>
#include <stdlib.h>
#include <string.h>
long long count;
void merge_two(int *b, int *c, int *a, int n) //用于合并两个已排序的数组b、c，存储在a里面
{
    int LB = n / 2, LC = (n + 1) / 2; // b、c各自的长度
    int pb = 0, pc = 0, pa = 0;       //指针
    while (pb < LB && pc < LC)
    {
        if (b[pb] <= c[pc]) //注意=的时候取b数组的值，此时count不用++
            a[pa++] = b[pb++];
        else
        {
            a[pa++] = c[pc++];
            count += (LB - pb); //交换的次数
        }
    }
    if (pb == LB) //把剩余的copy到a里面
        memcpy(a + pa, c + pc, (LC - pc) * sizeof(int));
    else
        memcpy(a + pa, b + pb, (LB - pb) * sizeof(int));
}
void mergesort(int *a, int n) //合并排序
{
    if (n > 1)
    {
        int *b, *c;
        b = (int *)malloc(sizeof(int) * (n / 2 + 1));
        c = (int *)malloc(sizeof(int) * (n / 2 + 1));
        memcpy(b, a, (n / 2) * sizeof(int));               //把a从中间分为b、c，分别对他们排序后合并
        memcpy(c, a + n / 2, ((n + 1) / 2) * sizeof(int)); // (n + 1) / 2 向上取整
        mergesort(b, n / 2);                               //递归对b合并排序
        mergesort(c, (n + 1) / 2);                         //递归对c合并排序
        merge_two(b, c, a, n);                             //合并b、c
        free(b);                                           //合并完成之后，把临时变量b、c释放，才不会导致内存越堆越大
        free(c);
    }
}
inline int read() //快读输入法
{
    int ans = 0, minus = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            minus = 1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        ans = (ans << 1) + (ans << 3) + ch - '0';
        ch = getchar();
    }
    if (minus)
        return ~(ans - 1);
    return ans;
}
int main()
{
    int n;
    int *a;
    while (scanf("%d", &n) != EOF) //元素个数
    {
        a = (int *)malloc(sizeof(int) * (n + 5));
        for (int i = 0; i < n; i++)
            a[i] = read();
        mergesort(a, n);
        // for (int i = 0; i < n; i++)
        //     printf("%d ", a[i]);
        // printf("\n");
        printf("%lld\n", count); //交换的次数
        count = 0;
        free(a);
    }
}
/*
假设您发明了一种排序算法，该算法按连续顺序对给定数字进行排序。算法的方法非常简单：选择两个相邻的数字并交换它们的位置，直到对数字序列进行排序。

现在，您希望以分析方式检查算法。您想找出算法将在给定序列上执行的最小交换次数。请编写一个程序来自动完成这项工作。

例如，您的算法可能至少对序列 5、1、2、4、3 执行 5 次交换。流程如下：

5，1，2，4，3 ---（交换 5 带 1）---> 1，5，2，4，3 ---（交换 5 与 2）---> 1，2，5，4，3 ---（交换 5 与 4）---> 1，2，4，5，3 ---（交换 5 与 3）---> 1，2，4，3，5 ---（交换 4 与 3）---> 1，2，3，4，5 （完成）。

每个测试用例的第一行包含一个整数，表示原始序列中要排序的数字数量1《=N《=500000。下一行包含指示序列本身的空格分隔整数。序列中的所有数字都介于 0和int 之间。保证输入文件中所有测试用例的总和不会超过 2000000。
*/