#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
int a[70], flag[70], n;
typedef struct
{
    int data, p;
} STACK;
int TrackBack(int targ)
{
    STACK stack[70];
    int top = -1, temp, i = n - 1;
    temp = targ;
    while (1)
    {
        while (i >= 0) //从当前i木棒开始，找到下一个没用过的,且可以接上的棒
            if (a[i] > temp || flag[i])
                i--;
            else
                break;
        if (i < 0)
        {
            if (top == -1) //栈中一个元素都没有，此时temp一定等于targ，且不可能存在a[i]>temp，所以只能是都用过了：成功
                return 1;
            else if (top == 0) //栈中最后一个元素都要退出来，说明压根找不到跟它能匹配的：失败
                return 0;
            i = stack[top].p - 1; //退栈(回溯)，从栈顶的下一个小木棒开始寻找
            temp += stack[top].data;
            flag[stack[top].p] = 0;
            top--;
        }
        else
        {
            if (temp == a[i]) //这次复原成功，开始下一次
            {
                flag[i] = 1;
                temp = targ;
                top = -1;
                i = n - 1;
            }
            else //把这个小木棒选上，进栈
            {
                top++;
                stack[top].data = a[i];
                stack[top].p = i;
                flag[i] = 1;
                temp -= a[i];
                i--;
            }
        }
    }
}
int main()
{
    int i, all = 0;
    cin >> n;
    for (i = 0; i < n; i++)
    {
        cin >> a[i];
        all += a[i];
    }
    sort(a, a + n);
    i = a[n - 1];
    while (1)
    {
        if (all != (all / i) * i)
            i++;
        else
        {
            memset(flag, 0, sizeof(flag));
            if (TrackBack(i))
            {
                cout << i << endl;
                return 0;
            }
            i++;
        }
    }
}
/*
数学兔老师从体育兔老师那里取来了一堆长度相等的木棍，然后咔嚓几下吧它们弄成了好几段长度更短的木棍，并且每段的最大长度不超过50

现在，数学兔老师希望小朋友们能把这些小木棍拼凑成之前的样子，但是却”忘记”了之前的木棍长度

所以，数学兔老师希望小朋友们能找出原始木棍的最小可能长度
*/