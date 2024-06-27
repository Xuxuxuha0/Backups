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
    return a.arrTime < b.arrTime; // ����arrTime��С������, arrTime��ͬ�򱣳�ԭ˳��
}

bool compareByPriByArr(const process &a, const process &b) {
    // ����pri��С������ͬ����arrTime��С���󣬻���ͬ�򱣳�ԭ˳��
    return (a.priority == b.priority) ? (a.arrTime < b.arrTime) : (a.priority < b.priority);
}


void input() {
    cin >> method; // cin��scanf������������ͷ�Ŀհ׷�
    while (true) {
        process p;
        int result = scanf("%d/%d/%d/%d/%d", &p.id, &p.arrTime, &p.runTime, &p.priority, &p.timeSlace);
        if (result == EOF) break;
        inputVector.push_back(p);
    }
}

void testInput() {
    fstream file(R"(C:\Users\huawei\Desktop\test.txt)");
    file >> method; // ���ļ��ж�ȡ method
    while (!file.eof()) {
        process p;
        char delimiter; // ���ڴ洢�ָ��� '/'
        file >> p.id >> delimiter
             >> p.arrTime >> delimiter
             >> p.runTime >> delimiter
             >> p.priority >> delimiter
             >> p.timeSlace;
        inputVector.push_back(p);
    }
//    // ���Զ�ȡ���
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
    sort(inputVector.begin(), inputVector.end(), compareByArrTime); // ����arrTime����
    int time = 0; // ��һ������������ϵ�ʱ��
    for (int i = 0; i < inputVector.size(); i++) {
        inputVector[i].startTime = max(inputVector[i].arrTime, time);
        inputVector[i].endTime = inputVector[i].startTime + inputVector[i].runTime;
        time = inputVector[i].endTime;
    }
    ans.assign(inputVector.begin(), inputVector.end()); // ����
}

void SJF() { // ���ɰ���
    int time = 0, index;
    sort(inputVector.begin(), inputVector.end(), compareByArrTime); // ����arrTime���򣨺�FCFS�ظ���
    while (!inputVector.empty()) {
        index = 0; // Ĭ��ΪarrTime��С�ģ����ǰ����Ԫ��arrTime����ͬ�����һ����idҲ����С�ģ�
        // ��arrTime<=time�Ľ�������ѡ��runTime��̵ģ������ͬ��ѡ��id��С��
        for (int i = 1; i < inputVector.size(); i++) {
            if (inputVector[i].arrTime > time) break;
            if (inputVector[i].runTime < inputVector[index].runTime ||
                (inputVector[i].runTime == inputVector[index].runTime && inputVector[i].id < inputVector[index].id))
                index = i;
        }
        // �ⲿ�ֺ�FCFS�ظ�
        inputVector[index].startTime = max(inputVector[index].arrTime, time);
        inputVector[index].endTime = inputVector[index].startTime + inputVector[index].runTime;
        time = inputVector[index].endTime;
        ans.push_back(inputVector[index]); // pvɾ��index������Ӱ�쵽ans
        inputVector.erase(inputVector.begin() + index);
    }
}


void SRTF() { // �ɰ���
    int time = 0, index = -1, tempIndex;
    set<int> s; // �Զ���С��������
    for (auto i: inputVector)
        s.insert(i.arrTime);
    sort(inputVector.begin(), inputVector.end(), compareByArrTime); // ����arrTime���򣨺�FCFS�ظ���

    while (!inputVector.empty()) {
        tempIndex = -1;
        for (int i = 0; i < inputVector.size(); i++) {
            if (inputVector[i].arrTime <= time) // ���������Ѿ�arr�Ľ���
            {
                if (tempIndex == -1 || inputVector[i].runTime < inputVector[tempIndex].runTime ||
                    (inputVector[i].runTime == inputVector[tempIndex].runTime &&
                     inputVector[i].arrTime < inputVector[tempIndex].arrTime))
                    tempIndex = i;
            } else break;
        }
        if (tempIndex == -1) { // ���н��̶�û��arr
            time = *s.begin();
            s.erase(s.begin());
        } else { // �н��̱�ѡ��
            if (index == -1) { // ֮ǰû�н��̱�����
                index = tempIndex;
                inputVector[index].startTime = time;
            } else if (index != tempIndex) { // ֮ǰ�н��̱����ȣ����ǻᱻ����
                inputVector[index].endTime = time;
                ans.push_back(inputVector[index]);
                index = tempIndex;
                inputVector[index].startTime = time;
            }
            // ��ʱindex��ʾ����ѡ�еĽ���orԭ����
            if (s.empty()) { // ���н��̶��Ѿ�arr
                time += inputVector[index].runTime;
                inputVector[index].endTime = time;
                ans.push_back(inputVector[index]);
                inputVector.erase(inputVector.begin() + index);
                index = -1;
            } else { // ���н���û��arr
                int oldTime = time;
                time = min(*s.begin(), oldTime + inputVector[index].runTime);
                if (time == oldTime + inputVector[index].runTime) { // �ý����������
                    inputVector[index].endTime = time;
                    ans.push_back(inputVector[index]);
                    inputVector.erase(inputVector.begin() + index);
                    index = -1;
                } else { // �ý���û��������
                    inputVector[index].runTime -= (time - oldTime);
                }
                if (time == *s.begin()) { // ���½��̵���
                    s.erase(s.begin());
                }
            }
        }
    }
}


void RR() {
    sort(inputVector.begin(), inputVector.end(), compareByArrTime); // ����arrTime���򣨺�FCFS�ظ���
    int time = 0;
    while (!inputVector.empty() || !pq.empty()) {
        if (pq.empty()) { // ��ʱ��������Ϊ��
            time = inputVector.begin()->arrTime;
            for (int i = 0; i < inputVector.size() && inputVector[i].arrTime <= time;) { // һ���ƶ����������У�һ�ߴ�pv����ɾ��
                pq.push(inputVector[i]);
                inputVector.erase(inputVector.begin());
            }
        } else { // �������в�Ϊ��
            // ���ö��׽�������
            pq.front().startTime = time;
            int oldTime = time;
            time = min(oldTime + pq.front().runTime, oldTime + pq.front().timeSlace);
            // ������Σ����̶����ó�cpu
            pq.front().endTime = time;
            pq.front().runTime -= (time - oldTime);
            process tempP = pq.front(); // ɾ��pq������Ӱ��tempP
            ans.push_back(tempP);
            pq.pop();
            for (int i = 0; i < inputVector.size() && inputVector[i].arrTime <= time;) { // �Ȱ�arr�Ľ����Ƶ���������
                pq.push(inputVector[i]);
                inputVector.erase(inputVector.begin());
            }
            if (tempP.runTime != 0) { // ԭ���Ķ��׽���û��������
                pq.push(tempP);
            }
        }
    }
}

void DPSA() {
    int time = 0, lastID = -1;
    sort(inputVector.begin(), inputVector.end(), compareByArrTime); // ����arrTime���򣨺�FCFS�ظ���
    while (!inputVector.empty() || !pv.empty()) {
        if (pv.empty()) { // ��������Ϊ��
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
            // ����pq[0]�Ƿ������꣬����Ϊһ�������ĵ���
            pv[0].runTime -= (time - oldTime);
            pv[0].endTime = time;
            pv[0].priority += 3;
            ans.push_back(pv[0]);
            pv[0].priority += 1;
            // ���й����н��̵���
            for (int i = 0; i < inputVector.size() && inputVector[i].arrTime <= time;) {
                pv.push_back(inputVector[0]);
                inputVector.erase(inputVector.begin());
            }
            if (pv[0].runTime != 0) { // �ý���û�������꣬���ھ�������ĩβ
                pv.push_back(pv[0]);
            }
            pv.erase(pv.begin());
            for (int i = 0; i < pv.size(); i++) { // �ı���������е����ȼ�
                if (pv[i].arrTime < time && pv[i].priority > 0)
                    pv[i].priority--;
            }
        }
    }
}


int main() {
//    testInput();
    input(); // ԭ���������������CTRL+C�𣿣���
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
