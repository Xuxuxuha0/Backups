#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <stack>

using namespace std;

/*
����ó���g++ lab1.cpp -o lab1.exe
���������еķ�ʽ���У�.\lab1.exe test_lab1.txt
�����̨����������test_lab1.txt�Ļ����
 */

/*
 ��׺���ʽת��׺���ʽ��
 ���ȼ��������ƣ���
    * / ��3
    + - ��2
    ( ��1
    = : 0

 ����ÿһ�����ʣ�
    ��������ֱ��д
    ( ��ֱ����ջ
    ) ������ջ����һֱ��ջֱ��( �����Ų�Ҫд�����ʽ���桿
    ��������ջ��or���ȼ�����ջ��������������ֹͣ��ջ�������ò�������ջ

 ������Ϻ���ջ�ڻ��У���ȫ����ջ
 */

/*
 �����׺���ʽ��
 ����ÿһ�����ʣ�
    ��������ֱ����ջ
    ��������������ջ���ηֱ�Ϊa��b; ����˳��a op b; ��������ջ
 ����ջ�ڵľ��ǽ��

 ��������е�����˵����
    ���ԭʽ��Ϊ��a = xxxxx   ��׺���ʽ���ǣ�a xxxxx =
    1����ǰ�洢a
    2��������=����ջһ�Σ�����������
 */

/*
 cout�Ƚ����ݷŵ��������У������������������endl�����������
 */

class Node { // �洢�������ͺ�ֵ
public:
    string type; // (constant, variable, operator)
    int num = 0; // ����
    string var; // ����
    char op = '\0'; // ������
};

map<char, int> op_priority; // �����������ȼ�
map<string, int> var_index; // ������������( ������ַ = ����*4 )
stack<char> operator_stack; // ��׺ת��׺��ջ
vector<Node> postfix_vector; // �洢��׺���ʽ
//stack<Node> constant_stack; // �����׺���ʽ��ջ���Ľ���Ԫ��ֻ��Ҫ�����ֵ���С�
string word; // ���ڴ洢��ȡ�ĵ���
fstream file;

void clear() {
    postfix_vector.clear();
    while (!operator_stack.empty()) operator_stack.pop();
//    while (!constant_stack.empty()) constant_stack.pop();
}

void init_op_priority() {
    op_priority['='] = 0;
    op_priority['('] = 1;
    op_priority['+'] = 2;
    op_priority['-'] = 2;
    op_priority['*'] = 3;
    op_priority['/'] = 3;
}

int string2int(string s) { // ���ַ���ת��Ϊ����
    int num = 0, i = 0, isNeg = 0;
    if (s[0] == '-') {
        isNeg = 1;
        i++;
    }
    for (; i < s.size(); i++) {
        num = num * 10 + s[i] - '0';
    }
    if (isNeg) return -num;
    else return num;
}


void print_postfix() {
    for (auto i: postfix_vector) {
        if (i.type == "constant")
            cout << i.num << " ";
        else if (i.type == "variable")
            cout << i.var << " ";
        else
            cout << i.op << " ";
    }
    cout << endl;
}

void int_return(string type) {
    file >> word; // ��һ���Ǳ�����
    if (type == "int") {
        var_index[word] = var_index.size() + 1; // ����������
        cout << "mov DWORD PTR [ebp-" << var_index[word] * 4 << "], 0" << endl;
    } else if (type == "return")
        cout << "mov eax, DWORD PTR [ebp-" << var_index[word] * 4 << "]" << endl;
    else
        cout << "error in void int_return(string type)!" << endl;
    file >> word; // �ٶ�һ���ֺ�
}

void save_postfix_node(string type) {
    Node temp_node;
    // ���ýڵ�����
    temp_node.type = type;
    // �洢ֵ
    if (type == "operator")
        temp_node.op = operator_stack.top();
    else if (type == "constant")
        temp_node.num = string2int(word);
    else
        temp_node.var = word;
    // �����׺���ʽ
    postfix_vector.push_back(temp_node);
}

void get_postfix() {
    while (word != ";") {
        if (word == "(") // �����ţ�ֱ����ջ
            operator_stack.push('(');
        else if (word == ")") { // �����ţ�һֱ��ջ��ֱ��������
            while (operator_stack.top() != '(') {
                save_postfix_node("operator");
                operator_stack.pop();
            }
            operator_stack.pop(); // �����ų�ջ
        } else if (word == "+" || word == "-" || word == "*" || word == "/" || word == "=") { // ע��Ƚϵ�������word���Ϳ����˸��������
            // ��������ջ��or���ȼ�����ջ��������������ֹͣ��ջ�������ò�������ջ
            while (!operator_stack.empty() && op_priority[operator_stack.top()] >= op_priority[word[0]]) {
                save_postfix_node("operator");
                operator_stack.pop();
            }
            operator_stack.push(word[0]);
        } else { // ��������ֱ��д
            // ����
            if ((word[0] == '-') || ('0' <= word[0] && word[0] <= '9'))
                save_postfix_node("constant");
                // ��������û�п��� a = -b; �������
            else
                save_postfix_node("variable");
        }
        file >> word; // ��ȡ��һ������
    }
    // ʣ��Ĳ�������ջ
    while (!operator_stack.empty()) {
        save_postfix_node("operator");
        operator_stack.pop();
    }
}

void print_op(char c) {
    cout << "pop ebx" << endl
         << "pop eax" << endl;
    switch (c) {
        case '+':
            cout << "add eax, ebx" << endl;
            break;
        case '-':
            cout << "sub eax, ebx" << endl;
            break;
        case '*':
            cout << "imul eax, ebx" << endl;
            break;
        case '/':
            cout << "cdq" << endl
                 << "idiv ebx" << endl;
            break;
    }
    cout << "push eax" << endl;
}

void cal_postfix() {
    // �����׺���ʽ��ע����������ջ��
    Node first_node = postfix_vector[0]; // ��һ���ڵ��Ǳ���ֵ�ı���
    // ���⴦��a = 100; ����ʽ
    if (postfix_vector[1].type == "constant" && postfix_vector[2].op == '=') {
        cout << "mov DWORD PTR [ebp-"
             << var_index[first_node.var] * 4 << "], "
             << postfix_vector[1].num
             << endl;
    }
        // һ��ĸ�ֵ���
    else {
        for (int i = 1; i < postfix_vector.size(); i++) {
            // �ڵ��Ǳ�������ջ������
            if (postfix_vector[i].type == "variable")
                cout << "mov eax, DWORD PTR [ebp-"
                     << var_index[postfix_vector[i].var] * 4
                     << "]" << endl
                     << "push eax" << endl;
                // �ڵ��ǳ�������ջ������
            else if (postfix_vector[i].type == "constant")
                cout << "mov eax, "
                     << postfix_vector[i].num << endl
                     << "push eax" << endl;
                // �ڵ��ǲ�����
            else {
                char c = postfix_vector[i].op;
                if (c == '+' || c == '-' || c == '*' || c == '/')
                    print_op(c);
                else // "="
                    cout << "pop eax" << endl
                         << "mov DWORD PTR [ebp-"
                         << var_index[first_node.var] * 4
                         << "], eax" << endl;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    file.open(argv[1], fstream::in); // �������в���ָ�����ļ�,ֻ��ģʽ
//    file.open("D:\\SelfDownLoad\\code\\cppcode\\compilerlab1\\test_lab1.txt", fstream::in); // ������; Ϊʲô���·������
    init_op_priority(); // ��ʼ�����������ȼ���
    while (!file.eof()) {
        file >> word; // ��ȡһ������(�Կո񡢻��з��ȷָ�,�������ո��)
        clear();
        if (word == "int" || word == "return") { // int��䡾����ֻ�� int a; ���ָ�ʽ��  return��䡾����ֻ�� return a; ���ָ�ʽ��
            int_return(word);
            continue;
        } else { // ��ֵ��䣬�������׺���ʽ���ټ��㡢��������ﲢû������ȥ���㣬ֻ������˻����䡿
            get_postfix();
            cal_postfix();
        }
    }
    file.close();
    return 0;
}