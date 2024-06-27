// 剑指 Offer 49. 丑数
#include <iostream>
#include <set>
using namespace std;

class Solution // set方法实现小根堆
{
public:
    long nthUglyNumber(int n)
    {
        int index[] = {2, 3, 5};

        set<long> s;
        s.insert(1);

        int cnt = 0;
        long temp;

        while (cnt != n)
        {
            temp = *(s.begin());
            for (int i = 0; i < 3; i++)
                s.insert(temp * index[i]);

            cnt++;
            s.erase(temp);
        }

        return temp;
    }
};

int main()
{
    Solution p;
    cout << p.nthUglyNumber(10);
}