#include "headfile/LinkQueue.h"
int main() // 打印杨辉三角形
{
    int n;
    cin >> n;
    LinkQueue Q;
    Init(Q);
    EnterQueue(Q, 1);
    EnterQueue(Q, 1);
    int temp;
    int s = 0;
    for (int i = 1; i <= n; i++)
    {
        EnterQueue(Q, 0);
        for (int j = 1; j <= i + 2; j++)
        {
            OutQueue(Q, temp);
            EnterQueue(Q, s + temp);
            s = temp;
            if (j != i + 2)
                cout << s << " ";
        }
        cout << endl;
    }
}