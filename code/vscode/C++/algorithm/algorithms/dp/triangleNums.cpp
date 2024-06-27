#include <iostream> //数字三角形问题
#include <algorithm>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int *a = new int[n + 1];
    int *dp = new int[n + 1];
    scanf("%d", &a[1]);
    dp[1] = a[1];
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
            scanf("%d", &a[j]);
        dp[i] = dp[i - 1] + a[i];
        for (int j = i - 1; j >= 2; j--)
            dp[j] = max(dp[j] + a[j], dp[j - 1] + a[j]);
        dp[1] = dp[1] + a[1];
    }
    sort(dp + 1, dp + n + 1);
    cout << dp[n] << endl;
}