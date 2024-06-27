#include <iostream> //完全背包问题：动态规划+递归+记忆版。有时候会超过时间限制
using namespace std;
#define size1 11                      //表示最大不超过多少种货物
#define size2 10000                   //表示最大不超过多少承重(单位k)
int goods[size1][2];                  //第0列表示重量(单位k)，第1列表示价值;从第1行开始
int F[size1][size2];                  //动态规划表,一维表示从前多少个货物里面选,二维表示当下背包的剩余承重量
void InitF(int num_goods, int weight) //初始化动态规划表
{
    for (int i = 1; i <= num_goods; i++)
        for (int j = 1; j <= weight; j++)
            F[i][j] = -1;
}
int Complete_MFKnapsack(int i, int j) //完全背包转化为0-1背包
{
    int value = 0;
    if (F[i][j] == -1) //在有效范围内，且未计算过该值
    {
        int b = 0, c = j / goods[i][0];
        for (int k = 0; k <= c; k++) //考虑拿i物品：拿零个，一个，两个...一直到装满当前的背包
        {
            b = k * goods[i][1] + Complete_MFKnapsack(i - 1, j - k * goods[i][0]);
            value = max(value, b);
        }
        F[i][j] = value; //记录该值
    }
    return F[i][j];
}
int main()
{
    int S, N, D, a;
    cin >> S >> N >> D; //背包重量s、重复进行n次、有d种货物
    for (int i = 1; i <= D; i++)
    {
        cin >> a >> goods[i][1];
        goods[i][0] = a / 1000; //由于所有重量都是1000的倍数，直接缩小处理
    }
    while (N--)
    {
        InitF(D, S / 1000);
        S += Complete_MFKnapsack(D, S / 1000); //传入的是本金/1000,传出的是利息
    }
    cout << S << endl;
}