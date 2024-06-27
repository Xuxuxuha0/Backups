#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct node
{
    int id;
    int data;
};

int compare(node a, node b)
{
    return a.data <= b.data; // 测试compare
}

int main()
{
    vector<node> v;
    node a1 = {1, 5};
    node a2 = {2, 4};
    node a3 = {3, 4};
    node a4 = {4, 5};
    node a5 = {5, 3};
    node a6 = {6, 5};
    v.push_back(a1);
    v.push_back(a2);
    v.push_back(a3);
    v.push_back(a4);
    v.push_back(a5);
    v.push_back(a6);
    sort(v.begin(), v.end(), compare);
    for (auto i : v)
    {
        cout << i.id << endl;
    }
}