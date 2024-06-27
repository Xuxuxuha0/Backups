#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <stack>
#include <cctype> // isalpha() 和 isalnum()

using namespace std;

/*
源程序得到可执行文件：g++ lab1.cpp -o lab1.exe
并用命令行的方式运行：.\lab1.exe test_lab1.txt
其中test_lab1.txt就是命令行参数

说明：该实验的汇编结果并不唯一，只要合理就行
 */

/*
 中缀表达式转后缀表达式：
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
 */

/*
 cout先将内容放到缓冲区中，不会立即输出；调用endl可以立即输出
 */

class Node { // 存储单词类型和值
public:
    string type; // (constant, variable, operator)
    int num = 0; // 常量
    string var; // 变量
    string op = ""; // 操作符
};

map<string, int> op_priority; // 操作符、优先级
map<string, int> var_index; // 变量名、索引( 变量地址 = 索引*4 )
stack<string> operator_stack; // 中缀转后缀的栈( 操作符栈 )
vector<Node> postfix_vector; // 存储后缀表达式
vector<string> row_after_tokenize; // 分词后的一行代码，每个元素就是一个词
fstream file_input; // 处理输入
fstream file_tokenize_result; // 用于测试，看看分词的结果

bool is_op(string s) {
    return s == "+" || s == "-" || s == "*" || s == "/" || s == "%" ||
           s == "<" || s == "<=" || s == ">" || s == ">=" || s == "==" || s == "!=" ||
           s == "&" || s == "|" || s == "^";
}

bool is_identifier(string s) {
    if (s.empty())  // 空字符串不是标识符
        return false;
    if (!isalpha(s[0]) && s[0] != '_')  // 检查首字符是否是字母或下划线
        return false;
    for (int i = 1; i < s.length(); i++) { // 检查字符串剩余部分是否只包含字母、数字或下划线
        if (!isalnum(s[i]) && s[i] != '_') // isalnum:数字、字母
            return false;
    }
    return true;
}

bool is_constant(string s) {
    if (s.empty()) // 空字符串不是常量
        return false;
    if (s.length() > 1 && s[0] == '-') { // 负数
        for (int i = 1; i < s.length(); i++) {
            if (s[i] < '0' || s[i] > '9')
                return false;
        }
    } else { // 不是负数，则所有字符必须是数字【001怎么办？？？】
        for (char c: s) {
            if (c < '0' || c > '9')
                return false;
        }
    }
    return true;
}


// 判断s是否合法
bool is_correct(string s) {
    // 负数如何处理???
    if (s == "int" || s == "return" || s == "main" ||
        s == ";" || s == "{" || s == "}" || s == "(" || s == ")" ||
        s == "!" || s == "=" ||
        is_op(s) || is_identifier(s) || is_constant(s))
        return true;
    return false;
}

void clear() {
    postfix_vector.clear();
    while (!operator_stack.empty()) operator_stack.pop();
//    while (!constant_stack.empty()) constant_stack.pop();
}

void init_op_priority() { // 数字越小，越高
//    op_priority["-"] = 2; //负数【可能需要修改】
//    op_priority["~"] = 2;
//    op_priority["!"] = 2;

    op_priority["/"] = 3;
    op_priority["*"] = 3;
    op_priority["%"] = 3;

    op_priority["+"] = 4;
    op_priority["-"] = 4;

    op_priority["<"] = 6;
    op_priority["<="] = 6;
    op_priority[">"] = 6;
    op_priority[">="] = 6;

    op_priority["=="] = 7;
    op_priority["!="] = 7;

    op_priority["&"] = 8;
    op_priority["^"] = 9;
    op_priority["|"] = 10;
    op_priority["&&"] = 11;
    op_priority["||"] = 12;

    op_priority["="] = 14;
    op_priority["("] = 13; // 与c语言不同，( 优先级比 = 高，比其他小
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


void print_postfix() { // 输出后缀表达式
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

void write_tokenize_result() { // 写入分词的结果
    for (auto i: row_after_tokenize) {
        file_tokenize_result << i << " ";
    }
    file_tokenize_result << endl;
}

void main_stm() { // 汇编： int main ( ) {
    // int main(int argc, int argv){...} 怎么处理？？？
    cout << ".intel_syntax noprefix" << endl
         << ".global main" << endl
         << ".extern printf" << endl
         << ".data" << endl
         << "format_str:" << endl
         << R"(.asciz "%d\n")" << endl
         << ".text" << endl
         << "main:" << endl
         << "push ebp" << endl
         << "mov ebp, esp" << endl
         << "sub esp, 0x100" << endl; // 数值可以调整
}

void main_end() {
    cout << "leave" << endl
         << "ret" << endl;
}

void return_stm() {
    string word = row_after_tokenize[1];
    if (is_constant(word))// return 常量
        cout << "mov eax, " << word << endl;
    else // return 变量
        cout << "mov eax, DWORD PTR [ebp-" << var_index[word] * 4 << "]" << endl;
}

void println_int_stm() { // println_int ( xxx ) ; 其中xxx为常量或变量
    string word = row_after_tokenize[2];
    if (is_constant(word))// 常量
        cout << "push " << word << endl
             << "push offset format_str" << endl
             << "call printf" << endl
             << "add esp, 8" << endl;
    else // 变量
        cout << "push DWORD PTR [ebp-" << var_index[word] * 4 << "]" << endl
             << "push offset format_str" << endl
             << "call printf" << endl
             << "add esp, 8" << endl;
}

void int_stm() {
    var_index[row_after_tokenize[1]] = var_index.size() + 1; // 将变量存入
    cout << "mov DWORD PTR [ebp-" << var_index[row_after_tokenize[1]] * 4 << "], 0" << endl;
}

void save_postfix_node(string type, string value) {
    Node temp_node;
    // 设置节点类型
    temp_node.type = type;
    // 存储值
    if (type == "operator")
        temp_node.op = operator_stack.top();
    else if (type == "constant")
        temp_node.num = string2int(value);
    else
        temp_node.var = value;
    // 存入后缀表达式
    postfix_vector.push_back(temp_node);
}

void get_postfix() {
    for (auto word: row_after_tokenize) {
        if (word == ";")
            break;
        else if (word == "=") // 赋值号直接入栈(不考虑赋值号当作操作符的情况)
            operator_stack.push("=");
        else if (word == "(") // 左括号：直接入栈
            operator_stack.push("(");
        else if (word == ")") { // 右括号：一直出栈，直到左括号
            while (operator_stack.top() != "(") {
                save_postfix_node("operator", "");
                operator_stack.pop();
            }
            operator_stack.pop(); // 左括号出栈
        } else if (is_op(word)) { // 操作符：栈空or优先级高于栈顶操作符(优先数越小，级别越高)，即可停止出栈，并将该操作符入栈
            while (!operator_stack.empty() && (op_priority[word] >= op_priority[operator_stack.top()])) {
                save_postfix_node("operator", "");
                operator_stack.pop();
            }
            operator_stack.push(word);
        } else { // 运算数：直接写
            if ((word[0] == '-') || ('0' <= word[0] && word[0] <= '9')) // 数字
                save_postfix_node("constant", word);
            else // 变量名【没有考虑 a = -b; 的情况】
                save_postfix_node("variable", word);
        }
    }
    // 剩余的操作符出栈
    while (!operator_stack.empty()) {
        save_postfix_node("operator", "");
        operator_stack.pop();
    }
}

void print_op(string c) { // 注意每个操作符的汇编码都不一样
    cout << "pop ebx" << endl
         << "pop eax" << endl;
    if (c == "+") {
        cout << "add eax, ebx" << endl
             << "push eax" << endl;
    } else if (c == "-") {
        cout << "sub eax, ebx" << endl
             << "push eax" << endl;
    } else if (c == "*") {
        cout << "imul eax, ebx" << endl
             << "push eax" << endl;
    } else if (c == "/") {
        cout << "cdq" << endl
             << "idiv ebx" << endl
             << "push eax" << endl;
    } else if (c == "%") {
        cout << "cdq" << endl
             << "idiv ebx" << endl
             << "push edx" << endl; // edx存余数
    } else if (c == "<") {
        cout << "cmp eax, ebx" << endl
             << "setl al" << endl
             << "movzx eax, al" << endl
             << "push eax" << endl;
    } else if (c == "<=") {
        cout << "cmp eax, ebx" << endl
             << "setle al" << endl
             << "movzx eax, al" << endl
             << "push eax" << endl;
    } else if (c == ">") {
        cout << "cmp eax, ebx" << endl
             << "setg al" << endl
             << "movzx eax, al" << endl
             << "push eax" << endl;
    } else if (c == ">=") {
        cout << "cmp eax, ebx" << endl
             << "setge al" << endl
             << "movzx eax, al" << endl
             << "push eax" << endl;
    } else if (c == "==") {
        cout << "cmp eax, ebx" << endl
             << "sete al" << endl
             << "movzx eax, al" << endl
             << "push eax" << endl;
    } else if (c == "!=") {
        cout << "cmp eax, ebx" << endl
             << "setne al" << endl
             << "movzx eax, al" << endl
             << "push eax" << endl;
    } else if (c == "&") {
        cout << "and eax, ebx" << endl
             << "push eax" << endl;
    } else if (c == "|") {
        cout << "or eax, ebx" << endl
             << "push eax" << endl;
    } else if (c == "^") {
        cout << "xor eax, ebx" << endl
             << "push eax" << endl;
    } else cout << "no such op!!!!!" << endl;
}

void cal_postfix() {
    // 计算后缀表达式（注意区分两个栈）
    Node first_node = postfix_vector[0]; // 第一个节点是被赋值的变量
    // 特殊处理：a = 100; 的形式
    if (postfix_vector[1].type == "constant" && postfix_vector[2].op == "=") {
        cout << "mov eax, " << postfix_vector[1].num << endl
             << "mov DWORD PTR [ebp-" << var_index[first_node.var] * 4 << "], eax" << endl;
    }
        // 一般的赋值语句
    else {
        for (int i = 1; i < postfix_vector.size(); i++) {
            // 节点是变量
            if (postfix_vector[i].type == "variable")
                cout << "mov eax, DWORD PTR [ebp-" << var_index[postfix_vector[i].var] * 4 << "]" << endl
                     << "push eax" << endl;
                // 节点是常量
            else if (postfix_vector[i].type == "constant")
                cout << "mov eax, " << postfix_vector[i].num << endl
                     << "push eax" << endl;
                // 节点是操作符、赋值符
            else {
                string c = postfix_vector[i].op;
                if (is_op(c))
                    print_op(c);
                else // "="
                    cout << "pop eax" << endl
                         << "mov DWORD PTR [ebp-" << var_index[first_node.var] * 4 << "], eax" << endl;
            }
        }
    }
}

void deal_one_stm(string word) { // 判断当前处理好的各个字符串是否构成句子，如果是，就进行汇编
    if (word == "{") { // 此时row_after_tokenize里面为int main ( ) {
        main_stm();
//        write_tokenize_result(); // 输出到文件看看分词结果
        row_after_tokenize.clear();
    } else if (word == "}") { // 此时row_after_tokenize里面一定只有一个 }
        main_end();
//        write_tokenize_result();
        row_after_tokenize.clear();
    } else if (word == ";") { // 此时row_after_tokenize里面是一个句子
        clear();
        if (row_after_tokenize[0] == "int") { // int语句
            int_stm();
        } else if (row_after_tokenize[0] == "return") { // return语句
            return_stm();
        } else if (row_after_tokenize[0] == "println_int") { // println_int语句
            println_int_stm();
        } else { // 赋值语句，先求出后缀表达式，再计算、输出【这里并没有真正去计算，只是输出了汇编语句】
            get_postfix();
            cal_postfix();
        }
//        write_tokenize_result();
        row_after_tokenize.clear();
    }
    // 否则不构成句子，不进行汇编
}

int main(int argc, char *argv[]) {
    file_input.open(argv[1], fstream::in); // 打开命令行参数指定的文件,只读模式
//    file_input.open("D:\\SelfDownLoad\\code\\cppcode\\Compilerlab2\\input.txt", fstream::in); // 测试用; 为什么相对路径不行
//    file_tokenize_result.open("D:\\SelfDownLoad\\code\\cppcode\\Compilerlab2\\tokenize_result.txt", fstream::out); // 测试用
    init_op_priority(); // 初始化操作符优先级表
    string word;
    string s;
    // 一边扫描分词，一边汇编
    while (file_input >> s) { // 读取一串字符(以空格、换行符等分割,不会读入空格等)，如果没有有效字符了，返回false，但word的值不变
        word = "";
        for (auto c: s) { // 对word进行分词，word是不含空白符的字符串
            word += c;
            if (!is_correct(word)) { // temp的长度一定大于1吗？？？
                row_after_tokenize.push_back(word.substr(0, word.size() - 1)); // 从pos开始，截取n个字符
                deal_one_stm(word.substr(0, word.size() - 1)); // 根据word判断是否是一个完整的句子，如果是就立即汇编
                word = c;
            }
        }
        row_after_tokenize.push_back(word);
        deal_one_stm(word);
    }
    file_input.close();
//    file_tokenize_result.close();
    return 0;
}