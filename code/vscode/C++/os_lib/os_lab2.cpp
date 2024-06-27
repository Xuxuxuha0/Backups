#include <iostream>
#include <vector>
using namespace std;

struct Node
{
    int begin;
    int end;
    int id = -1; // 表示空
};

vector<Node> v; // 存放每段内存空间

void first_fit()
{
    int No, process_id, op, size;
    while (true)
    {
        // 输入
        int res = scanf("%d/%d/%d/%d", &No, &process_id, &op, &size);
        if (res == EOF)
            break;
        // 内存分配
        if (op == 1)
        {
            for (auto it = v.begin(); it != v.end(); ++it)
            {
                if (it->id == -1 && (it->end - it->begin + 1) >= size)
                {
                    Node node;
                    node.end = it->end;
                    it->end = it->begin + size - 1;
                    it->id = process_id;
                    node.begin = it->end + 1;
                    if (node.begin <= node.end)                        // 如果分配后有剩余空间
                        if ((it + 1) != v.end() && (it + 1)->id == -1) // 后面有空闲区
                            (it + 1)->begin = node.begin;
                        else // 后面没有空闲区
                            v.insert(it + 1, node);
                    break;
                }
            }
        }
        // 内存回收【默认释放该进程的全部容量】
        else
        {
            for (auto it = v.begin(); it != v.end(); ++it)
            {
                if (it->id == process_id)
                {
                    if ((it - 1) >= v.begin() && (it - 1)->id == -1) // 合并之前的内存
                    {
                        (it - 1)->end = it->end;
                        v.erase(it);
                        it--;
                    }
                    if ((it + 1) != v.end() && (it + 1)->id == -1) // 合并之后的内存
                    {
                        it->end = (it + 1)->end;
                        v.erase(it + 1);
                        it->id = -1;
                    }
                    if (it->id != -1) // 说明它前后都不是空闲(没经历过上面两个处理)
                    {
                        it->id = -1;
                    }
                    break;
                }
            }
        }
        // 输出
        cout << No;
        for (auto i : v)
        {
            if (i.id == -1)
                cout << "/" << i.begin << "-" << i.end << ".0";
            else
                cout << "/" << i.begin << "-" << i.end << ".1." << i.id;
        }
        cout << endl;
    }
}

void best_fit()
{
    int No, process_id, op, size;
    while (true)
    {
        // 输入
        int res = scanf("%d/%d/%d/%d", &No, &process_id, &op, &size);
        if (res == EOF)
            break;
        // 内存分配
        if (op == 1)
        {
            // 采用最粗暴的全遍历
            auto it = v.begin();
            std::vector<Node>::iterator target_it = v.end(); // 初始化为空
            for (; it != v.end(); ++it)
            {
                if (it->id == -1 && (it->end - it->begin + 1) >= size)
                {
                    if ((target_it == v.end()) ||
                        ((it->end - it->begin) < (target_it->end - target_it->begin)))
                        target_it = it;
                }
            }
            if (target_it != v.end())
            {
                Node node;
                node.end = target_it->end;
                target_it->end = target_it->begin + size - 1;
                target_it->id = process_id;
                node.begin = target_it->end + 1;
                if (node.begin <= node.end)                                      // 如果分配后有剩余空间
                    if ((target_it + 1) != v.end() && (target_it + 1)->id == -1) // 后面有空闲区
                        (target_it + 1)->begin = node.begin;
                    else // 后面没有空闲区
                        v.insert(target_it + 1, node);
            }
        }
        // 内存回收【默认释放该进程的全部容量】
        else
        {
            for (auto it = v.begin(); it != v.end(); ++it)
            {
                if (it->id == process_id)
                {
                    if ((it - 1) >= v.begin() && (it - 1)->id == -1) // 合并之前的内存
                    {
                        (it - 1)->end = it->end;
                        v.erase(it);
                        it--;
                    }
                    if ((it + 1) != v.end() && (it + 1)->id == -1) // 合并之后的内存
                    {
                        it->end = (it + 1)->end;
                        v.erase(it + 1);
                        it->id = -1;
                    }
                    if (it->id != -1) // 说明它前后都不是空闲(没经历过上面两个处理)
                    {
                        it->id = -1;
                    }
                    break;
                }
            }
        }
        // 输出
        cout << No;
        for (auto i : v)
        {
            if (i.id == -1)
                cout << "/" << i.begin << "-" << i.end << ".0";
            else
                cout << "/" << i.begin << "-" << i.end << ".1." << i.id;
        }
        cout << endl;
    }
}

void worst_fit()
{
    int No, process_id, op, size;
    while (true)
    {
        // 输入
        int res = scanf("%d/%d/%d/%d", &No, &process_id, &op, &size);
        if (res == EOF)
            break;
        // 内存分配
        if (op == 1)
        {
            // 采用最粗暴的全遍历
            auto it = v.begin();
            std::vector<Node>::iterator target_it = v.end(); // 初始化为空
            for (; it != v.end(); ++it)
            {
                if (it->id == -1 && (it->end - it->begin + 1) >= size)
                {
                    if ((target_it == v.end()) ||
                        ((it->end - it->begin) > (target_it->end - target_it->begin)))
                        target_it = it;
                }
            }
            if (target_it != v.end())
            {
                Node node;
                node.end = target_it->end;
                target_it->end = target_it->begin + size - 1;
                target_it->id = process_id;
                node.begin = target_it->end + 1;
                if (node.begin <= node.end)                                      // 如果分配后有剩余空间
                    if ((target_it + 1) != v.end() && (target_it + 1)->id == -1) // 后面有空闲区
                        (target_it + 1)->begin = node.begin;
                    else // 后面没有空闲区
                        v.insert(target_it + 1, node);
            }
        }
        // 内存回收【默认释放该进程的全部容量】
        else
        {
            for (auto it = v.begin(); it != v.end(); ++it)
            {
                if (it->id == process_id)
                {
                    if ((it - 1) >= v.begin() && (it - 1)->id == -1) // 合并之前的内存
                    {
                        (it - 1)->end = it->end;
                        v.erase(it);
                        it--;
                    }
                    if ((it + 1) != v.end() && (it + 1)->id == -1) // 合并之后的内存
                    {
                        it->end = (it + 1)->end;
                        v.erase(it + 1);
                        it->id = -1;
                    }
                    if (it->id != -1) // 说明它前后都不是空闲(没经历过上面两个处理)
                    {
                        it->id = -1;
                    }
                    break;
                }
            }
        }
        // 输出
        cout << No;
        for (auto i : v)
        {
            if (i.id == -1)
                cout << "/" << i.begin << "-" << i.end << ".0";
            else
                cout << "/" << i.begin << "-" << i.end << ".1." << i.id;
        }
        cout << endl;
    }
}

int main()
{
    int method, max_size;
    cin >> method >> max_size;
    Node node;
    node.begin = 0;
    node.end = max_size - 1;
    v.push_back(node);
    switch (method)
    {
    case 1:
        first_fit();
        break;
    case 2:
        best_fit();
        break;
    case 3:
        worst_fit();
        break;
    }
    return 0;
}
