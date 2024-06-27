#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <stack>

using namespace std;

/*
编译该程序：g++ lab1.cpp -o lab1.exe
并用命令行的方式运行：.\lab1.exe test_lab1.txt
向控制台输出本程序对test_lab1.txt的汇编结果
 */

/*
 中缀表达式转后缀表达式：
 优先级（待完善）：
    * / ：3
    + - ：2
    ( ：1
    = : 0

 对于每一个单词：
    运算数：直接写
    ( ：直接入栈
    ) ：不入栈，并一直出栈直到( 【括号不要写到表达式里面】
    操作符：栈空or优先级高于栈顶操作符，即可停止出栈，并将该操作符入栈

 遍历完毕后，若栈内还有，则全部出栈
 */

/*
 计算后缀表达式：
 对于每一个单词：
    运算数：直接入栈
    操作符：连续出栈两次分别为a、b; 运算顺序：a op b; 运算结果入栈
 最终栈内的就是结果

 编译过程中的特殊说明：
    如果原式子为：a = xxxxx   后缀表达式就是：a xxxxx =
    1、提前存储a
    2、操作符=：出栈一次（即运算结果）
 */

/*
 cout先将内容放到缓冲区中，不会立即输出；调用endl可以立即输出
 */

class Node { // 存储单词类型和值
public:
    string type; // (constant, variable, operator)
    int num = 0; // 常量
    string var; // 变量
    char op = '\0'; // 操作符
};

map<char, int> op_priority; // 操作符、优先级
map<string, int> var_index; // 变量名、索引( 变量地址 = 索引*4 )
stack<char> operator_stack; // 中缀转后缀的栈
vector<Node> postfix_vector; // 存储后缀表达式
//stack<Node> constant_stack; // 计算后缀表达式的栈【改进：元素只需要存具体值就行】
string word; // 用于存储读取的单词
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

int string2int(string s) { // 将字符串转换为整数
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
    file >> word; // 下一个是变量名
    if (type == "int") {
        var_index[word] = var_index.size() + 1; // 将变量存入
        cout << "mov DWORD PTR [ebp-" << var_index[word] * 4 << "], 0" << endl;
    } else if (type == "return")
        cout << "mov eax, DWORD PTR [ebp-" << var_index[word] * 4 << "]" << endl;
    else
        cout << "error in void int_return(string type)!" << endl;
    file >> word; // 再读一个分号
}

void save_postfix_node(string type) {
    Node temp_node;
    // 设置节点类型
    temp_node.type = type;
    // 存储值
    if (type == "operator")
        temp_node.op = operator_stack.top();
    else if (type == "constant")
        temp_node.num = string2int(word);
    else
        temp_node.var = word;
    // 存入后缀表达式
    postfix_vector.push_back(temp_node);
}

void get_postfix() {
    while (word != ";") {
        if (word == "(") // 左括号：直接入栈
            operator_stack.push('(');
        else if (word == ")") { // 右括号：一直出栈，直到左括号
            while (operator_stack.top() != '(') {
                save_postfix_node("operator");
                operator_stack.pop();
            }
            operator_stack.pop(); // 左括号出栈
        } else if (word == "+" || word == "-" || word == "*" || word == "/" || word == "=") { // 注意比较的是整个word，就考虑了负数的情况
            // 操作符：栈空or优先级高于栈顶操作符，即可停止出栈，并将该操作符入栈
            while (!operator_stack.empty() && op_priority[operator_stack.top()] >= op_priority[word[0]]) {
                save_postfix_node("operator");
                operator_stack.pop();
            }
            operator_stack.push(word[0]);
        } else { // 运算数：直接写
            // 数字
            if ((word[0] == '-') || ('0' <= word[0] && word[0] <= '9'))
                save_postfix_node("constant");
                // 变量名【没有考虑 a = -b; 的情况】
            else
                save_postfix_node("variable");
        }
        file >> word; // 读取下一个单词
    }
    // 剩余的操作符出栈
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
    // 计算后缀表达式（注意区分两个栈）
    Node first_node = postfix_vector[0]; // 第一个节点是被赋值的变量
    // 特殊处理：a = 100; 的形式
    if (postfix_vector[1].type == "constant" && postfix_vector[2].op == '=') {
        cout << "mov DWORD PTR [ebp-"
             << var_index[first_node.var] * 4 << "], "
             << postfix_vector[1].num
             << endl;
    }
        // 一般的赋值语句
    else {
        for (int i = 1; i < postfix_vector.size(); i++) {
            // 节点是变量：入栈、编译
            if (postfix_vector[i].type == "variable")
                cout << "mov eax, DWORD PTR [ebp-"
                     << var_index[postfix_vector[i].var] * 4
                     << "]" << endl
                     << "push eax" << endl;
                // 节点是常量：入栈，编译
            else if (postfix_vector[i].type == "constant")
                cout << "mov eax, "
                     << postfix_vector[i].num << endl
                     << "push eax" << endl;
                // 节点是操作符
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
    file.open(argv[1], fstream::in); // 打开命令行参数指定的文件,只读模式
//    file.open("D:\\SelfDownLoad\\code\\cppcode\\compilerlab1\\test_lab1.txt", fstream::in); // 测试用; 为什么相对路径不行
    init_op_priority(); // 初始化操作符优先级表
    while (!file.eof()) {
        file >> word; // 读取一个单词(以空格、换行符等分割,不会读入空格等)
        clear();
        if (word == "int" || word == "return") { // int语句【假设只有 int a; 这种格式】  return语句【假设只有 return a; 这种格式】
            int_return(word);
            continue;
        } else { // 赋值语句，先求出后缀表达式，再计算、输出【这里并没有真正去计算，只是输出了汇编语句】
            get_postfix();
            cal_postfix();
        }
    }
    file.close();
    return 0;
}