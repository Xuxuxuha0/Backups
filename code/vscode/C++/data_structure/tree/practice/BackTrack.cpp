#include <iostream> //排列类型的回溯
using namespace std;
int final_max; //最终最大值
int prs_max;   //当前最大值
int n;
int PQ[13][13];  // i男j女的优势积
int flag[13];    //选没选过j女的标志
int FakeMax[13]; // FakeMax[i]是前i个人所能达到的最大优势和(其实是达不到的，只是为了作为剪枝的条件)
void BackTrack(int i)
{
    if (i <= n)
    {
        if (prs_max + FakeMax[n] - FakeMax[i - 1] <= final_max) //如果"当前"+"i-1之后的虚假最大值"都小于等于结果最大值，那就直接剪枝
            return;
        for (int j = 1; j <= n; j++) //否则，就一个一个去考虑
            if (!flag[j])
            {
                flag[j] = 1;
                prs_max += PQ[i][j];
                BackTrack(i + 1);
                prs_max -= PQ[i][j]; //回溯
                flag[j] = 0;
            }
    }
    else
    {
        if (prs_max > final_max)
            final_max = prs_max;
    }
}
int main()
{
    int x;
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> PQ[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            cin >> x;
            PQ[j][i] *= x;
        }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            FakeMax[i] = max(FakeMax[i], PQ[i][j]); //先算出i男和j女能产生的最大优势(可能选择j女的时候会重复)
        FakeMax[i] += FakeMax[i - 1];               //再加上前面的，成为前i个人能产生的最大优势和，但实际肯定不合理
    }
    BackTrack(1);
    cout << final_max << endl;
}
//回溯：最优装载问题