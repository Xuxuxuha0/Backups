#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node
{
    int id = -1;    // 存放的页面，-1表示空
    int enter_time; // 该页面进入的时间
    int next_use;   // 该页面下次使用的时间
};

vector<Node> table; // 内存分配表
vector<int> seq;    // 输入序列
int lack = 0;       // 缺页次数
int occupy_num;     // 被占用的的物理块数目
queue<int> que;     // 存放物理块，按最早进入内存的顺序排列
int size_table;     // 物理块总数
vector<int> v_LRU;  // 存放页id，按最近访问时间从大到小排列

void print(bool is_first_line, bool is_hit) // 打印一行
{
    if (!is_first_line)
        cout << "/";
    if (table[0].id == -1) // 输出第一个物理块
        cout << "-";
    else
        cout << table[0].id;
    int size = table.size();
    for (int i = 1; i < size; i++)
    {
        cout << ",";
        if (table[i].id == -1)
            cout << "-";
        else
            cout << table[i].id;
    }
    if (is_hit)
    {
        cout << ",1";
    }
    else
        cout << ",0";
}

void cal_next_use(int index, int time) // 计算table[index]的下一次使用时间
{
    int size = seq.size();
    time++;
    while (time < size && seq[time] != table[index].id)
    {
        time++;
    }
    table[index].next_use = time; // 如果index=size，表示它永不使用
}

int is_in_table(int id) // 判断该页是否在内存中
{
    for (int i = 0; i < table.size(); i++)
        if (table[i].id == id)
            return i; // 该页在table[i]
    return -1;        // 该页不在内存，需要置换
}

void input() // 存放输入序列
{
    int id; // 用于输入
    char c;
    while (true)
    {
        int res = scanf("%d%c", &id, &c);
        if (res == EOF)
            break;
        seq.push_back(id);
    }
}

void opt()
{
    input();
    // 处理第一个页
    lack++;
    occupy_num = 1;
    table[0].id = seq[0];
    table[0].enter_time = 0;
    cal_next_use(0, 0);
    print(true, false);
    // 处理后面的页
    int size_seq = seq.size();
    for (int i = 1; i < size_seq; i++) // seq[i]是当前处理的页面，i也可以看作当前时间
    {
        int index = is_in_table(seq[i]);
        if (index != -1) // 该页在table[index]中
        {
            print(false, true);
            cal_next_use(index, i);
        }
        else // 没在内存中
        {
            lack++;
            int block = 0;               // 目标块
            if (occupy_num < size_table) // 有空的物理块
            {
                block = occupy_num;
                occupy_num++;
            }
            else // 没有空的物理块
            {
                for (int j = 0; j < size_table; j++)
                {
                    if ((table[j].next_use > table[block].next_use) || ((table[j].next_use == table[block].next_use) && (table[j].enter_time < table[block].enter_time)))
                    {
                        block = j;
                    }
                }
            }
            // 把当前页装入block物理块
            table[block].id = seq[i];
            table[block].enter_time = i;
            cal_next_use(block, i);
            print(false, false);
        }
    }
    cout << endl
         << lack << endl;
}

void FIFO()
{
    int id; // 需要换入的页号
    // 处理第一个页
    scanf("%d,", &id);
    lack++;
    occupy_num = 1;
    table[0].id = id;
    que.push(0);
    print(true, false);
    // 处理后面的页
    while (true)
    {
        int res = scanf("%d,", &id);
        if (res == EOF)
            break;
        if (is_in_table(id) != -1) // 如果在内存中
        {
            print(false, true);
        }
        else // 不在内存中
        {
            lack++;
            // 有空闲物理块
            if (occupy_num < size_table) // 有空的物理块
            {
                table[occupy_num].id = id;
                que.push(occupy_num);
                occupy_num++;
            }
            else // 没有空闲物理块
            {
                int block = que.front();
                que.pop();
                que.push(block);
                table[block].id = id;
            }
            print(false, false);
        }
    }
    cout << endl
         << lack << endl;
}

void print_LRU(bool is_first_line, bool is_hit) // 打印一行
{
    if (!is_first_line)
        cout << "/";
    cout << v_LRU[0]; // 输出第一个物理块
    for (int i = 1; i < v_LRU.size(); i++)
        cout << "," << v_LRU[i];
    int size = v_LRU.size();
    for (int i = v_LRU.size(); i < size_table; i++)
        cout << ",-";
    if (is_hit)
    {
        cout << ",1";
    }
    else
        cout << ",0";
}

void LRU()
{
    int id; // 需要换入的页号
    // 处理第一个页
    scanf("%d,", &id);
    lack++;
    occupy_num = 1;
    v_LRU.push_back(id);
    print_LRU(true, false);
    // 处理后面的页
    while (true)
    {
        int res = scanf("%d,", &id);
        if (res == EOF)
            break;
        auto it = v_LRU.begin();
        for (; it != v_LRU.end(); it++) // 查找id是否在内存中
            if (*it == id)
                break;
        if (it != v_LRU.end()) // 如果在内存中
        {
            v_LRU.erase(it);
            v_LRU.push_back(id);
            print_LRU(false, true);
        }
        else // 如果不在内存中
        {
            lack++;
            // 有空闲物理块
            if (occupy_num < size_table) // 有空的物理块
            {
                v_LRU.push_back(id);
                occupy_num++;
            }
            else // 没有空闲物理块
            {
                v_LRU.erase(v_LRU.begin());
                v_LRU.push_back(id);
            }
            print_LRU(false, false);
        }
    }
    cout << endl
         << lack << endl;
}

int main()
{
    int method;
    cin >> method >> size_table;
    for (int i = 0; i < size_table; i++)
    {
        Node node;
        table.push_back(node);
    }
    switch (method)
    {
    case 1:
        opt();
        break;
    case 2:
        FIFO();
        break;
    case 3:
        LRU();
        break;
    }
}