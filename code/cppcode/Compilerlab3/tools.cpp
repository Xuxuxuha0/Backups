#include "tools.h"

map<string, int> op_priority; // 操作符、优先级
map<string, string> var_index; // 局部变量名or形参变量名、变量地址( 例如：a ebp-8 )( 局部都是从ebp-4开始 形参都是从ebp+8开始)
int num_local_var; // 局部变量的个数
int num_formal_para; // 形参变量的个数
stack<string> operator_stack; // 中缀转后缀的栈( 操作符栈 )
vector<Node> postfix_vector; // 存储后缀表达式
vector<string> row_after_tokenize; // 分词后的一行代码，每个元素就是一个词
vector<string> expression_stm; // 存放表达式
fstream file_input; // 处理输入
fstream file_tokenize_result; // 用于测试，看看分词的结果
int num_and; // &&出现的个数
int num_or; // ||出现的个数

bool is_punctuation(string s) {
    return s == ";" || s == "{" || s == "}" || s == "(" || s == ")" ||
           s == "=";
}

bool is_op(string s) { // 是否为操作符( "-"表示减法、"#"表示对变量取负 )
    return s == "+" || s == "-" || s == "*" || s == "/" || s == "%" ||
           s == "<" || s == "<=" || s == ">" || s == ">=" || s == "==" || s == "!=" ||
           s == "&" || s == "|" || s == "^" ||
           s == "&&" || s == "||" ||
           s == "!" || s == "~" || s == "#";
}

bool is_type(string s) { // 是否为类型标识符
    if (s == "int" || s == "void")
        return true;
    return false;
}

bool is_identifier(string s) { // 是否为标识符
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

bool is_constant(string s) { // 是否是常量(可以处理负常量)
    if (s.empty()) // 空字符串不是常量
        return false;
    if (s.length() > 1 && s[0] == '-') { // 负常量
        for (int i = 1; i < s.length(); i++) {
            if (s[i] < '0' || s[i] > '9')
                return false;
        }
    } else { // 不是负数，则所有字符必须是数字
        for (char c: s) {
            if (c < '0' || c > '9')
                return false;
        }
    }
    return true;
}


bool is_correct(string s) { // 判断s是否合法
    // 关键字也属于is_identifier
    return is_punctuation(s) || is_op(s) || is_identifier(s) || is_constant(s);
}

void clear() {
    postfix_vector.clear();
    while (!operator_stack.empty()) operator_stack.pop();
//    while (!constant_stack.empty()) constant_stack.pop();
}

void init_op_priority() { // 数字越小，越高
    op_priority["#"] = 2; // 表示对变量取负
    op_priority["~"] = 2;
    op_priority["!"] = 2;

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
    if (s[0] == '-') { // 负数
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

void start() { // 整个文件最开始的汇编
    cout << ".intel_syntax noprefix" << endl
         << ".extern printf" << endl // 这一行可变
         << ".data" << endl
         << "format_str:" << endl
         << R"(.asciz "%d\n")" << endl
         << ".text" << endl;
}

void func_start() { // 函数定义的开头：返回值类型 函数名 ( 形参类型 形参名, 形参类型 形参名 ) {
    num_local_var = 0;
    num_formal_para = 0;
    var_index.clear(); // 每个函数都有自己的局部变量or形参，一旦将该函数扫描完了，就不用了
    string func_name = row_after_tokenize[1]; // 函数名
    cout << ".global " << func_name << endl // 声明
         << func_name << ":" << endl
         << "push ebp" << endl
         << "mov ebp, esp" << endl
         << "sub esp, 256" << endl; // 为局部变量分配256字节的空间，数值可以调整
    // 将所有形参存起来
    for (int i = 3; row_after_tokenize[i] != ")"; i++) {
        // i是形参类型,i+1就是形参名
        if (is_type(row_after_tokenize[i])) {
            num_formal_para++;
            save_var(row_after_tokenize[i + 1], (num_formal_para + 1) * 4, false);
        }
    }
}

void func_end() {
    // 所有函数的结束部分
    cout << "leave" << endl
         << "ret" << endl;
}

void return_stm() {
    // return xxx ;
    // 返回值一律放在eax里面
    if (row_after_tokenize.size() == 3) {
        string word = row_after_tokenize[1];
        if (is_constant(word))// return 常量 ;
            cout << "mov eax, " << word << endl;
        else // return 变量 ;
            cout << "mov eax, DWORD PTR [" << var_index[word] << "]" << endl;
    } else { // return 表达式 ;
        deal_one_exp("", 1, row_after_tokenize.size() - 2);
    }
}

void println_int_stm() {
    // println_int ( xxx ) ;
    if (row_after_tokenize.size() == 5) {
        string word = row_after_tokenize[2];
        if (is_constant(word))// 常量
            cout << "push " << word << endl
                 << "push offset format_str" << endl
                 << "call printf" << endl
                 << "add esp, 8" << endl;
        else // 变量
            cout << "push DWORD PTR [" << var_index[word] << "]" << endl
                 << "push offset format_str" << endl
                 << "call printf" << endl
                 << "add esp, 8" << endl;
    } else { // 表达式
        deal_one_exp("", 2, row_after_tokenize.size() - 3);
        cout << "push eax" << endl
             << "push offset format_str" << endl
             << "call printf" << endl
             << "add esp, 8" << endl;
    }
}

void call_stm(int func_begin, int func_end) {
    // 调用自定义的函数，末尾没有分号
    // 形如：myfunc ( a , b , xxx )
    // [s_begin,s_end]就是该串的范围
    // 先进行预处理
    string func_name = row_after_tokenize[func_begin];
    row_after_tokenize.insert(row_after_tokenize.begin() + func_begin + 2, ",");
    func_end++;
    // 此时变为：myfunc ( , a , b , xxx ) 可以根据逗号分割
    // 【错误：如果调用函数，则它的参数也是,分割的】
    stack<int> comma_index; // 存放逗号的下标，栈顶就是最后一个逗号
    for (int i = 0; i < row_after_tokenize.size(); i++)
        if (row_after_tokenize[i] == ",")
            comma_index.push(i);
    int num_para = comma_index.size(); // 形参个数
    // 倒序处理每个形参
    int para_begin;
    int para_end = func_end - 1;
    while (!comma_index.empty()) {
        para_begin = comma_index.top(); // 指向逗号
        comma_index.pop();
        // ( begin,end ] 就是该形参
        if ((para_end - para_begin) == 1) { // 该形参是常量or变量
            if (is_constant(row_after_tokenize[para_end]))
                cout << "push " << row_after_tokenize[para_end] << endl; // 语句和示例不一样，没用eax
            else
                cout << "push DWORD PTR [" << var_index[row_after_tokenize[para_end]] << "]"
                     << endl; // 语句和示例不一样，没用eax
        } else { // 是表达式
            int last_para_end = para_end;
            para_end = deal_one_exp("", para_begin + 1, para_end);
            func_end -= (para_end - last_para_end); // 因为处理完该形参，可能row_after_tokenize被修改了
            cout << "push eax" << endl;
        }
        para_end = para_begin - 1;
    }
    cout << "call " << func_name << endl
         << "add esp, " << num_para * 4 << endl;
    // 此时函数的返回值在eax里面
    // 把[func_begin+1, func_end]全删了，因为它们已经没用了
    row_after_tokenize.erase(row_after_tokenize.begin() + func_begin + 1, row_after_tokenize.begin() + func_end + 1);
}


void int_stm() { // int a , b = a , c = func ( a + 100 ) ;
    int i = 0;
    int var;
    while (true) {
        i++;
        var = i; // row_after_tokenize[var]就是变量名
        num_local_var++;
        save_var(row_after_tokenize[var], num_local_var * 4, true); // 将新变量存入
        i++; // 变量名的下一个词
        if (row_after_tokenize[i] == "," || row_after_tokenize[i] == ";") // 说明没有对它初始化
            cout << "mov DWORD PTR [" << var_index[row_after_tokenize[var]] << "], 0" << endl;
        else if (row_after_tokenize[i] == "=") { // 用表达式对该变量初始化
            // 将该表达式 xxx, 存起来
            i++;
            int begin = i;
            while (row_after_tokenize[i] != "," && row_after_tokenize[i] != ";") {
                i++;
            }
            i = deal_one_exp(row_after_tokenize[var], begin, i - 1) + 1; // 因为row_after_tokenize可能被修改
        } else
            cout << "error in int_stm!!!" << endl;
        if (row_after_tokenize[i] == ";")
            break;
    }
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
    // 接受输入：( a + b ) * c
    clear();
    for (auto word: expression_stm) {
        if (word == "(") // 左括号：直接入栈
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
            else // 变量名
                save_postfix_node("variable", word);
        }
    }
    // 剩余的操作符出栈
    while (!operator_stack.empty()) {
        save_postfix_node("operator", "");
        operator_stack.pop();
    }
//    print_postfix(); // 测试用
}

void print_op(string c) { // 注意每个操作符的汇编码都不一样
    if (c != "~" && c != "!" && c != "#") // - a 处理成 # a
        cout << "pop ebx" << endl;
    cout << "pop eax" << endl;
    if (c == "+") {
        cout << "add eax, ebx" << endl
             << "push eax" << endl;
    } else if (c == "-") { // 【没考虑负数的情况】
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
    } else if (c == "&&") { // 需要保证goto的flag唯一
        num_and += 3; // 因为下面有3个flag
        cout << "test eax, eax" << endl
             << "jz and_" << to_string(num_and) << endl
             << "test ebx, ebx" << endl
             << "jz and_" << to_string(num_and + 1) << endl
             << "mov eax, 1" << endl
             << "jmp and_" << to_string(num_and + 2) << endl
             << "and_" << to_string(num_and) << ":" << endl
             << "and_" << to_string(num_and + 1) << ":" << endl
             << "mov eax, 0" << endl
             << "and_" << to_string(num_and + 2) << ":" << endl
             << "push eax" << endl;
    } else if (c == "||") {
        num_or += 3; // 因为下面有3个flag
        cout << "test eax, eax" << endl
             << "jnz or_" << to_string(num_or) << endl
             << "test ebx, ebx" << endl
             << "jnz or_" << to_string(num_or + 1) << endl
             << "mov eax, 0" << endl
             << "jmp or_" << to_string(num_or + 2) << endl
             << "or_" << to_string(num_or) << ":" << endl
             << "or_" << to_string(num_or + 1) << ":" << endl
             << "mov eax, 1" << endl
             << "or_" << to_string(num_or + 2) << ":" << endl
             << "push eax" << endl;
    } else if (c == "!") { // 往下是单目运算
        cout << "test eax, eax\n"
                "setz al\n"
                "movzx eax, al" << endl
             << "push eax" << endl;
    } else if (c == "~") {
        cout << "not eax" << endl
             << "push eax" << endl;
    } else if (c == "#") { // 负变量
        cout << "neg eax" << endl
             << "push eax" << endl;
    } else cout << "no such op!!!!!" << endl;
}

void cal_postfix() {
    // 计算后缀表达式（注意区分两个栈）
//    // 特殊处理：只有一个常量
//    if (postfix_vector[0].type == "constant" && postfix_vector.size() == 1) {
//        cout << "mov eax, " << postfix_vector[0].num << endl;
//    }
    // 一般的赋值语句
//    else {
    for (int i = 0; i < postfix_vector.size(); i++) {
        // 节点是变量
        if (postfix_vector[i].type == "variable")
            cout << "mov eax, DWORD PTR [" << var_index[postfix_vector[i].var] << "]" << endl
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
            else cout << "error!!!!!!!" << endl;
        }
    }
    cout << "pop eax" << endl;
//    }
}

void deal_one_stm(string word) {
    // 判断当前处理好的各个字符串是否构成句子，如果是，就进行汇编
    if (word == "{") { // 此时row_after_tokenize里面为：返回值类型 函数名 ( 形参 ) {
//        write_tokenize_result(); // 输出到文件看看分词结果
        func_start();
        row_after_tokenize.clear();
    } else if (word == "}") { // 此时row_after_tokenize里面一定只有一个 }
//        write_tokenize_result(); // 输出到文件看看分词结果
        func_end();
        row_after_tokenize.clear();
    } else if (word == ";") { // 此时row_after_tokenize里面是一个句子
//        write_tokenize_result(); // 输出到文件看看分词结果
        if (row_after_tokenize[0] == "int") { // int语句
            int_stm();
        } else if (row_after_tokenize[0] == "return") { // return语句
            return_stm();
        } else if (row_after_tokenize[0] == "println_int") { // println_int语句
            println_int_stm();
        } else if (row_after_tokenize[1] == "=") { // 表达式赋值语句：a = xxx ;
            // 先求出后缀表达式，再计算、输出
            deal_one_exp(row_after_tokenize[0], 2, row_after_tokenize.size() - 2);
        } else { // 纯调用函数的语句：func ( a , b , xxx ) ;
            call_stm(0, row_after_tokenize.size() - 2);
        }
        row_after_tokenize.clear();
    }
    // 否则不构成句子，不进行汇编
}


int deal_one_exp(string var_name, int begin, int end) {
    // row_after_tokenize[begin,end]是表达式
    // 形如：a + b - func ( c )
    // 如果var_name不为空，则表达式的最终值要赋给var_name
    // 先处理负号
    deal_minus(begin, end);
    // 将函数也看作表达式的一部分，当成局部变量来存储该返回值，再按照普通表达式计算【暂不考虑函数里面也是函数】
    int func_begin = begin, func_end;
    while (func_begin < end) {
        if (is_identifier(row_after_tokenize[func_begin]) &&
            row_after_tokenize[func_begin + 1] == "(") {// func_begin指向函数名，func_begin+1是左括号
            // 让func_end指向右括号
            int cnt = 0;
            func_end = func_begin + 1; // 初始指向左括号
            do {
                if (row_after_tokenize[func_end] == "(")
                    cnt++;
                else if (row_after_tokenize[func_end] == ")")
                    cnt--;
                func_end++;
            } while (cnt != 0);
            func_end--; // 多加了一位
            // 由于将要把表达式中"函数调用"替换为"变量"，因此原先的end也要移动
            // 【问题：照这个思路，原本调用deal_one_exp的end也要更新】
            end -= (func_end - func_begin);
            // 调用函数：func ( xxx )
            // 该函数不仅计算了函数值，存在eax里面；还把row_after_tokenize对应函数调用的词元全删了，只留下func_begin（函数名）
            call_stm(func_begin, func_end);
            // 把eax的值存在一个局部变量里面，func_begin这个位置存放该变量
            string func_name = row_after_tokenize[func_begin];
            num_local_var++;
            int address_num = num_local_var * 4;
            string name = func_name + to_string(address_num); // 该变量命名为：函数名+地址号
            save_var(name, address_num, true); // 将新变量存入
            cout << "mov DWORD PTR [" << var_index[name] << "], eax" << endl; // 把函数返回值给这个变量
            row_after_tokenize[func_begin] = name; // 最终效果：表达式中"函数调用"替换为"变量"，变量的值就是函数的返回值
        }
        func_begin++;
    }
    // 此时就是不含函数调用的表达式
    expression_stm.clear();
    while (begin <= end) {
        expression_stm.push_back(row_after_tokenize[begin]);
        begin++;
    }
    get_postfix();
    cal_postfix();
    // 此时表达式的值在eax里面
    if (var_name != "") { // 是赋值语句
        cout << "mov DWORD PTR [" << var_index[var_name] << "], eax" << endl;
    }
    return end; // 因为row_after_tokenize可能被修改了
}

void save_var(string name, int address_num, bool is_local) { // 存储一个局部变量or形参
    string str_address_num = std::to_string(address_num);
    if (is_local) // 是局部变量
        var_index[name] = "ebp-" + str_address_num;
    else // 形参
        var_index[name] = "ebp+" + str_address_num;
}

void deal_minus(int begin, int end) {
    // 用于处理表达式[begin,end]中的负变量（负常量在分词的时候就处理好了）
    // 形如：- a （刚开始就是取负）或 a + - b（负号前是运算符、左括号）
    // 思路：将 - 变成 #
    if (row_after_tokenize[begin] == "-")
        row_after_tokenize[begin] = "#";
    for (int i = begin; i < end; i++) {
        if (row_after_tokenize[i + 1] == "-" &&
            (is_op(row_after_tokenize[i]) || row_after_tokenize[i] == "("))
            row_after_tokenize[i + 1] = "#";
    }
}


