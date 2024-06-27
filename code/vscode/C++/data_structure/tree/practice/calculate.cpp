#include <iostream> //二叉哥的二叉树
#include <cmath>
using namespace std;
long long cnt;
int n;
long long POW[27];    //存储高度为1--26长满需要多少节点
void Calculate(int m) //建议手动画图去领会
{
    int i = 1;
    if (n <= m) //无法长到m层
        ;
    else
    {
        n -= (m + 1); //长到m层，且m层已经长了一个
        cnt++;
        if (n > 0) //剩下的n按照1，3...pow(2,i)-1 去长
        {
            while (i <= m && n >= POW[i]) //注意当i>m,则表示已经长满了,且n可能还有剩余；当n<POW[i],表示该树长不满了
            {
                n -= POW[i];
                cnt += pow(2, i - 1);
                i++;
            }
            if (i > m) //第一种情况直接退出
                return;
            if (n > 0) //第二种情况继续用n去长高度为i的树
                Calculate(i - 1);
        }
    }
}
int main()
{
    POW[0] = 1;
    for (int i = 1; i < 27; i++)
        POW[i] = pow(2, i) - 1;
    int t, M;
    cin >> t;
    while (t--)
    {
        cin >> n >> M;
        cnt = 0;
        Calculate(M);
        cout << cnt << endl;
    }
}