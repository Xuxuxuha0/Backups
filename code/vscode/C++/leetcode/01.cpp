// 91. 解码方法
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int numDecodings(string s)
    {
        int f1 = 1, f2, f3; // 相当于滚动数组
        int n = s.size();

        if (s[0] == '0') // 0开头
            return 0;
        if (n == 1)
            return 1;

        if (s[1] == '0') // 以x0开头
        {
            if (s[0] != '1' && s[0] != '2')
                return 0;
            else
                f2 = 1;
        }
        else
        {
            string t = s.substr(0, 2);
            if (t >= "10" && t <= "26")
                f2 = 2;
            else
                f2 = 1;
        }
        f3 = f2;

        for (int i = 2; i < n; i++)
        {
            if (s[i] == '0')
            {
                if (s[i - 1] != '1' && s[i - 1] != '2')
                    return 0;
                else
                    f3 = f1;
            }
            else
            {
                if (s[i - 1] == '0')
                    f3 = f2;
                else
                {
                    f3 = f2;
                    string t = s.substr(i - 1, 2);
                    if (t >= "10" && t <= "26")
                        f3 += f1;
                }
            }
            f1 = f2;
            f2 = f3;
        }
        return f3;
    }
};
