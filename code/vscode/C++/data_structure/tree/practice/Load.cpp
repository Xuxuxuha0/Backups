#include <iostream> //回溯：最优装载问题（0-1背包递归版）
#include <string.h>
using namespace std;
int c, n, Rest;                     //剩余的货物加起来重Rest(包括i)
int *goods, *prs_goods, *max_goods; //货物重量，货物选择与否(0-1,最后构成二进制数组,[0]记录总重量)(在最大重量相同时，由于从1,2,3...顺序考虑拿，再考虑不拿，所以先求出的最大重量对应最大二进制)
void Load(int i)                    //考虑第i个物品
{
    if (Rest + prs_goods[0] <= max_goods[0]) //剩下的+当前拿的 <= 最大值，直接剪枝
        return;
    if (i > n) //拿完了
    {
        if (prs_goods[0] > max_goods[0])
            for (int i = 0; i <= n; i++)
                max_goods[i] = prs_goods[i];
    }
    else
    {
        if (c - prs_goods[0] < goods[i]) //拿不了i物品了
        {
            if (prs_goods[0] > max_goods[0])
                for (int i = 0; i <= n; i++)
                    max_goods[i] = prs_goods[i];
        }
        else
        {
            prs_goods[i] = 1; //拿i物品
            prs_goods[0] += goods[i];
            Rest -= goods[i];
            Load(i + 1);
            prs_goods[i] = 0; //回溯
            prs_goods[0] -= goods[i];
            Rest += goods[i];
        }
        Load(i + 1); //不拿i物品
    }
}
int main()
{
    cin >> c >> n;
    goods = new int[n + 1];
    prs_goods = new int[n + 1];
    max_goods = new int[n + 1];
    for (register int i = 1; i <= n; i++)
    {
        cin >> goods[i];
        Rest += goods[i];
    }
    memset(prs_goods, 0, sizeof(prs_goods));
    memset(max_goods, 0, sizeof(max_goods));
    Load(1);
    cout << max_goods[0] << endl;
    for (register int i = 1; i <= n; i++)
        if (max_goods[i])
            cout << i << " ";
    cout << endl;
}