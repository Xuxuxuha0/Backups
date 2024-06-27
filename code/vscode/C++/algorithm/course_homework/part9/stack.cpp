#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int n, top = 0, t, pn = 0, pp = 0; // t是临时指针，pn是num数组指针，pp是plus_cnt数组指针
    cin >> n;
    int *num = new int[n], *cost = new int[n], *stack1 = new int[n];
    unsigned long long *stack0 = new unsigned long long[n], *plus_cnt = new unsigned long long[n], temp;
    for (register int i = 0; i < n; i++)
        scanf("%d", &num[i]);
    for (register int i = 0; i < n; i++)
        scanf("%d", &cost[i]);
    sort(num, num + n);
    sort(cost, cost + n);
    stack0[top] = stack1[top] = num[pn++]; //第一个元素入栈
    while (pn < n)
    {
        temp = num[pn++];
        if (temp == stack0[top]) // temp=栈顶，就把栈里的全部++。由于栈里的元素从栈顶到栈底依次差1，所以整个栈+1等价于把栈顶作为代表+1。
            stack0[top]++;
        else if (temp > stack0[top]) // temp>栈顶，就要考虑退栈了
        {
            while (top > 0 && temp > stack0[top]) //退栈直到temp等于栈顶或者栈中只剩一个元素，同时要记录这些元素++的次数
            {
                plus_cnt[pp++] = stack0[top] - stack1[top];
                stack0[top - 1] = stack0[top] + 1;
                top--;
            }
            if (top == 0) //考虑栈中还剩一个元素
            {
                if (temp > stack0[top]) //如果栈底元素也小于temp，就先退栈再进栈
                {
                    plus_cnt[pp++] = stack0[top] - stack1[top];
                    stack0[top] = stack1[top] = temp;
                }
                else //否则就按照temp=栈顶处理
                    stack0[top]++;
            }
            else //按temp=栈顶去处理
                stack0[top]++;
        }
        else // temp<栈顶，则一定是temp=stack[top][0]-1
        {
            top++; //先入栈
            stack0[top] = stack1[top] = temp;
            stack0[top]++; //等价于栈中元素全部++
        }
    }
    while (top > 0) //剩下的全部退栈
    {
        plus_cnt[pp++] = stack0[top] - stack1[top];
        stack0[top - 1] = stack0[top] + 1;
        top--;
    }
    plus_cnt[pp++] = stack0[top] - stack1[top]; // top=0
    sort(plus_cnt, plus_cnt + pp);
    temp = 0;
    t = 0;
    pp--;
    while (pp >= 0) //计算开销
    {
        temp += plus_cnt[pp] * cost[t];
        pp--;
        t++;
    }
    cout << temp << endl;
    return 0;
}
/*
有两个长度一致均为N的正整数数组Num,Cost

Cost可以 在对Num数组进行修改前 进行无限次的交换任意两个开销值的操作

Num可以进行对任意的一个数Num[i]++，但是每+1就会造成Cost[i]的开销

Cost数组在对Num数组进行修改之后就不能再次交换更改

求 使得Num数组中任意两个数均不相等的条件下,造成的总开销的最小值

结果对2^64取模

尽量不要使用cin输入，以免输入时间开销过大



这个题我是用一个栈来实现的（当然还有更好的办法，我没想到。。。）
首先对num和cost排序。
只要把num数组中每个数++的次数算出来存入plus_cnt数组，再从大到小排序，最大的次数对应最小的cost，依次类推，就能得到最小的开销。所以其实举例的时候跟cost没啥关系。
我们当然希望全部的++次数都发生在某一个元素上，这样最终开销就是它乘以cost[0]就行了。但这是不太现实的，我们只能希望++的操作尽可能的堆在某几个元素身上。使得最后参与运算的cost[i]是最小的那几个。

举个例子来亲自算一遍，比如说：num：1 1 2 5 5 5 5 5 8 8 8 8 9（也可以直接跳过看结论）
先让1进栈。
考虑num[1]=1：（第一种情况）栈顶为1，1=1，则让栈内元素全部++，第二个1就可以不管了（它++的次数为0，直接写在假想的“最终排列”里面去，实际没必要记录）。
考虑num[2]=2：同上。
考虑num[3]=5：（第二种情况）栈内只有一个3，3<5，那么3就可以退栈，5进栈。退栈的时候同时把它和它原本的数1相减，得到++的次数，存储到plus_cnt数组中。
考虑num[4]=5：栈顶是5，5=5，同（第一种情况）。
考虑num[5]=5：（第三种情况）栈顶为6，6>5，这是由于上面已经在最终排列里面产生了一个5，所以此时让5进栈，让栈内元素都++。
截至目前，栈内应该是7 6；最终排列应该是1 2 3 5。
以此类推。
考虑num[8]=8：（第二种情况）此时栈内：9 8 7 6；最终排列：1 2 3 5。栈顶是6，6<8，就需要6退栈，并更新plus_cnt。然后栈顶变为7，7<8，还需要退栈，并更新plus_cnt。然后栈顶变为8，8=8，就变为了第一种情况。

综上不难发现，每考虑一个新元素temp的时候，无非就三种情况。
1、temp=stack[top]，让栈内元素全部++；
2、temp>stack[top]，一直退栈（同时更新plus_cnt），直到temp=stack[top]，然后按第一种情况处理；或者栈空，temp直接进栈。
3、temp<stack[top]，temp先入栈，栈内元素全部++。
最后把plus_cnt数组排序，再联立cost数组就可以算出最小开销。

但有个问题就是，上述操作中的“栈内元素全部++”过于耗费时间。观察到栈内元素其实有个性质，从栈顶到栈底依次差1。因而我们可以只让stack[top]++，剩下的先不管。等到退栈的时候再更新，stack[top-1]=stack[top]+1。

还有一些细节就是，用unsigned long long存储结果可以自动实现对2^64取模。因为它最大存储2^64-1。当超过最大值，比方说+1，它就变为了0。
另外stack也建议用unsigned long long，以防数据太大。

*/