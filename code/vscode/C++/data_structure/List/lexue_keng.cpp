#include <iostream>
#include <algorithm>
using namespace std;
#define size 100000
//乐学不存在INT_MAX，所以需要预定
typedef struct
{
    int width, height;
    int left, right; //比双向链表方便
} hole;
int main()
{
    int n;
    cin >> n;
    hole a[size]; //允许有这么大的数组

    a[0].width = 1; //左墙
    a[0].height = INT_MAX;
    a[0].left = -1;
    a[0].right = 1;

    int i = 1, count;
    count = n;
    int p = 0; //指向将要处理的数据
    while (count--)
    {
        cin >> a[i].width >> a[i].height;
        a[i].left = i - 1;
        a[i].right = i + 1;
        if (a[i].height < a[p].height) //先让p指向最低的那个
            p = i;
        i++;
    }

    a[i].width = 1; //右墙
    a[i].height = INT_MAX;
    a[i].left = i - 1;
    a[i].right = -1;

    long long *Time = new long long[n + 5]; //记录每个结果
    long long WentTime = 0;                 //经过的时间
    int low;
    while (1)
    {
        low = (a[a[p].left].height < a[a[p].right].height) ? a[p].left : a[p].right;
        if (a[low].height == INT_MAX)
            break;
        if (a[p].height > a[low].height)
            p = low;
        else
        {
            Time[p] = WentTime + a[p].width;
            WentTime += a[p].width * (a[low].height - a[p].height);
            if (low == a[p].left) //"删除"刚填满的p坑
            {
                a[low].right = a[p].right;
                a[a[p].right].left = low;
            }
            else
            {
                a[low].left = a[p].left;
                a[a[p].left].right = low;
            }
            a[low].width += a[p].width; //修改low坑，以代表刚连接的整体
            p = low;
        }
    }
    Time[p] = WentTime += a[p].width; //处理最后一次总坑
    for (int i = 1; i <= n; i++)
        cout << Time[i] << endl;
}
//综教楼后的那个坑