#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <set>
#include <queue>

using namespace std;

struct process {
    int id;
    int arrTime;
    int runTime;
    int priority;
    int timeSlace;
    int startTime;
    int endTime;
};

vector<process> inputVector;
vector<process> ans;
queue<process> pq;
vector<process> pv;
int method;

bool compareByArrTime(const process &a, const process &b) {
    return a.arrTime < b.arrTime; // 按照arrTime从小到大排, arrTime相同则保持原顺序
}

bool compareByPriByArr(const process &a, const process &b) {
    // 按照pri从小到大，相同则按照arrTime从小到大，还相同则保持原顺序
    return (a.priority == b.priority) ? (a.arrTime < b.arrTime) : (a.priority < b.priority);
}


void input() {
    cin >> method; // cin和scanf都可以跳过开头的空白符
    while (true) {
        process p;
        int result = scanf("%d/%d/%d/%d/%d", &p.id, &p.arrTime, &p.runTime, &p.priority, &p.timeSlace);
        if (result == EOF) break;
        inputVector.push_back(p);
    }
}

void testInput() {
    fstream file(R"(C:\Users\huawei\Desktop\test.txt)");
    file >> method; // 从文件中读取 method
    while (!file.eof()) {
        process p;
        char delimiter; // 用于存储分隔符 '/'
        file >> p.id >> delimiter
             >> p.arrTime >> delimiter
             >> p.runTime >> delimiter
             >> p.priority >> delimiter
             >> p.timeSlace;
        inputVector.push_back(p);
    }
//    // 测试读取结果
//    for (const auto &p: pv) {
//        cout << p.id << "/" << p.arrTime << "/" << p.runTime << "/" << p.priority << "/" << p.timeSlace << endl;
//    }
}

void output() {
    int order = 1;
    for (auto i: ans) {
        cout << order << "/"
             << i.id << "/"
             << i.startTime << "/"
             << i.endTime << "/"
             << i.priority << endl;
        order++;
    }
}

void FCFS() {
    sort(inputVector.begin(), inputVector.end(), compareByArrTime); // 按照arrTime排序
    int time = 0; // 上一个进程运行完毕的时间
    for (int i = 0; i < inputVector.size(); i++) {
        inputVector[i].startTime = max(inputVector[i].arrTime, time);
        inputVector[i].endTime = inputVector[i].startTime + inputVector[i].runTime;
        time = inputVector[i].endTime;
    }
    ans.assign(inputVector.begin(), inputVector.end()); // 复制
}

void SJF() { // 不可剥夺
    int time = 0, index;
    sort(inputVector.begin(), inputVector.end(), compareByArrTime); // 按照arrTime排序（和FCFS重复）
    while (!inputVector.empty()) {
        index = 0; // 默认为arrTime最小的（如果前几个元素arrTime都相同，则第一个的id也是最小的）
        // 从arrTime<=time的进程里面选出runTime最短的，如果相同则选择id最小的
        for (int i = 1; i < inputVector.size(); i++) {
            if (inputVector[i].arrTime > time) break;
            if (inputVector[i].runTime < inputVector[index].runTime ||
                (inputVector[i].runTime == inputVector[index].runTime && inputVector[i].id < inputVector[index].id))
                index = i;
        }
        // 这部分和FCFS重复
        inputVector[index].startTime = max(inputVector[index].arrTime, time);
        inputVector[index].endTime = inputVector[index].startTime + inputVector[index].runTime;
        time = inputVector[index].endTime;
        ans.push_back(inputVector[index]); // pv删除index，不会影响到ans
        inputVector.erase(inputVector.begin() + index);
    }
}


void SRTF() { // 可剥夺
    int time = 0, index = -1, tempIndex;
    set<int> s; // 自动从小到大排序
    for (auto i: inputVector)
        s.insert(i.arrTime);
    sort(inputVector.begin(), inputVector.end(), compareByArrTime); // 按照arrTime排序（和FCFS重复）

    while (!inputVector.empty()) {
        tempIndex = -1;
        for (int i = 0; i < inputVector.size(); i++) {
            if (inputVector[i].arrTime <= time) // 考虑所有已经arr的进程
            {
                if (tempIndex == -1 || inputVector[i].runTime < inputVector[tempIndex].runTime ||
                    (inputVector[i].runTime == inputVector[tempIndex].runTime &&
                     inputVector[i].arrTime < inputVector[tempIndex].arrTime))
                    tempIndex = i;
            } else break;
        }
        if (tempIndex == -1) { // 所有进程都没有arr
            time = *s.begin();
            s.erase(s.begin());
        } else { // 有进程被选中
            if (index == -1) { // 之前没有进程被调度
                index = tempIndex;
                inputVector[index].startTime = time;
            } else if (index != tempIndex) { // 之前有进程被调度，但是会被顶替
                inputVector[index].endTime = time;
                ans.push_back(inputVector[index]);
                index = tempIndex;
                inputVector[index].startTime = time;
            }
            // 此时index表示：新选中的进程or原进程
            if (s.empty()) { // 所有进程都已经arr
                time += inputVector[index].runTime;
                inputVector[index].endTime = time;
                ans.push_back(inputVector[index]);
                inputVector.erase(inputVector.begin() + index);
                index = -1;
            } else { // 还有进程没有arr
                int oldTime = time;
                time = min(*s.begin(), oldTime + inputVector[index].runTime);
                if (time == oldTime + inputVector[index].runTime) { // 该进程运行完毕
                    inputVector[index].endTime = time;
                    ans.push_back(inputVector[index]);
                    inputVector.erase(inputVector.begin() + index);
                    index = -1;
                } else { // 该进程没有运行完
                    inputVector[index].runTime -= (time - oldTime);
                }
                if (time == *s.begin()) { // 有新进程到达
                    s.erase(s.begin());
                }
            }
        }
    }
}


void RR() {
    sort(inputVector.begin(), inputVector.end(), compareByArrTime); // 按照arrTime排序（和FCFS重复）
    int time = 0;
    while (!inputVector.empty() || !pq.empty()) {
        if (pq.empty()) { // 此时就绪队列为空
            time = inputVector.begin()->arrTime;
            for (int i = 0; i < inputVector.size() && inputVector[i].arrTime <= time;) { // 一边移动到就绪队列，一边从pv里面删除
                pq.push(inputVector[i]);
                inputVector.erase(inputVector.begin());
            }
        } else { // 就绪队列不为空
            // 先让队首进程运行
            pq.front().startTime = time;
            int oldTime = time;
            time = min(oldTime + pq.front().runTime, oldTime + pq.front().timeSlace);
            // 无论如何，进程都会让出cpu
            pq.front().endTime = time;
            pq.front().runTime -= (time - oldTime);
            process tempP = pq.front(); // 删掉pq，不会影响tempP
            ans.push_back(tempP);
            pq.pop();
            for (int i = 0; i < inputVector.size() && inputVector[i].arrTime <= time;) { // 先把arr的进程移到就绪队列
                pq.push(inputVector[i]);
                inputVector.erase(inputVector.begin());
            }
            if (tempP.runTime != 0) { // 原来的队首进程没有运行完
                pq.push(tempP);
            }
        }
    }
}

void DPSA() {
    int time = 0, lastID = -1;
    sort(inputVector.begin(), inputVector.end(), compareByArrTime); // 按照arrTime排序（和FCFS重复）
    while (!inputVector.empty() || !pv.empty()) {
        if (pv.empty()) { // 就绪队列为空
            time = inputVector[0].arrTime;
            for (int i = 0; i < inputVector.size() && inputVector[i].arrTime <= time;) {
                pv.push_back(inputVector[0]);
                inputVector.erase(inputVector.begin());
            }
        } else {
            sort(pv.begin(), pv.end(), compareByPriByArr);
            pv[0].startTime = time;
            int oldTime = time;
            time = min(oldTime + pv[0].runTime, oldTime + pv[0].timeSlace);
            // 无论pq[0]是否运行完，都作为一次完整的调度
            pv[0].runTime -= (time - oldTime);
            pv[0].endTime = time;
            pv[0].priority += 3;
            ans.push_back(pv[0]);
            pv[0].priority += 1;
            // 运行过程有进程到来
            for (int i = 0; i < inputVector.size() && inputVector[i].arrTime <= time;) {
                pv.push_back(inputVector[0]);
                inputVector.erase(inputVector.begin());
            }
            if (pv[0].runTime != 0) { // 该进程没有运行完，放在就绪队列末尾
                pv.push_back(pv[0]);
            }
            pv.erase(pv.begin());
            for (int i = 0; i < pv.size(); i++) { // 改变就绪队列中的优先级
                if (pv[i].arrTime < time && pv[i].priority > 0)
                    pv[i].priority--;
            }
        }
    }
}


int main() {
//    testInput();
    input(); // 原来测试输入可以用CTRL+C吗？？？
    switch (method) {
        case 1:
            FCFS();
            break;
        case 2:
            SJF();
            break;
        case 3:
            SRTF();
            break;
        case 4:
            RR();
            break;
        case 5:
            DPSA();
            break;
    }
    output();
    return 0;
}
