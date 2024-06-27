#include <iostream>
using namespace std;
typedef struct
{
    char *ch;
    int maxsize, n;
} hstring;
void init(hstring &s, int n)
{
    s.ch = (char *)malloc((n + 1) * sizeof(char));
    s.ch[0] = '\0';
    s.n = n;
}
void getnext(hstring s, int next[])
{
    int j = 2, k = -1;
    next[0] = -1;
    next[1] = 0;
    while (j < s.n)
    {
        k = next[j - 1];
        while (1)
        {
            if (s.ch[j - 1] == s.ch[k])
            {
                next[j] = k + 1;
                break;
            }
            else
            {
                if (k == 0)
                {
                    next[j] = 0;
                    break;
                }
                else
                    k = next[k];
            }
        }
        j++;
    }
}
int fastfind(hstring t, hstring p, int next[])
{
    int pt = 0, pp = 0;
    while (pt < t.n && pp < p.n)
    {
        if (pp == -1 || p.ch[pp] == t.ch[pt])
        {
            pp++;
            pt++;
        }
        else
            pp = next[pp];
    }
    if (pp < p.n)
        return -1;
    else
        return pt - p.n;
}
int main()
{
    hstring p, t;
    init(p, 10);
    p.ch = "aabaabaaaa";
    init(t, 22);
    t.ch = "aabaabbabaabaabaaaabbb"; // 9
    int next[20] = {0};
    getnext(p, next);
    cout << fastfind(t, p, next);
}