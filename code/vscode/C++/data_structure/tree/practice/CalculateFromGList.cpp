#include <iostream> //树的建立与基本操作(但没有建立数的过程，比较复杂；就用了一个栈)
#include <string.h>
using namespace std;
int degree[100][2]; //从1开始
int cnt[100];       //从0开始
void print(char c, int d)
{
    for (int i = 0; i < 4 * d; i++)
        cout << " ";
    cout << c << endl;
}
void Calculate(char A[], int &N)
{
    int i = 0, top = 0, stack[50], depth = -1; // stack从1开始
    char ch;
    ch = A[i++];
    memset(stack, 0, sizeof(stack));
    while (ch != '\0')
    {
        if (isalpha(ch))
        {
            print(ch, depth);
            N++; //表示一共出现了多少个结点，也表示每个节点对应的下标1，2....
            degree[stack[top]][1]++;
            stack[++top] = N;
        }
        else if (ch == '(')
            depth++;
        else if (ch == ')')
        {
            depth--;
            top--;
        }
        ch = A[i++];
    }
}
int main()
{
    char a[1000];
    int n = 0;
    cin >> a;
    Calculate(a, n);
    int max = 0;
    for (int i = 1; i <= n; i++)
    {
        cnt[degree[i][1]]++;
        if (degree[i][1] > max)
            max = degree[i][1];
    }
    cout << "Degree of tree: " << max << endl;
    for (int i = 0; i <= max; i++)
        cout << "Number of nodes of degree " << i << ": " << cnt[i] << endl;
}