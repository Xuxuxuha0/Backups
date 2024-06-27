#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <stack>
#include <cctype> // isalpha() �� isalnum()

using namespace std;

/*
Դ����õ���ִ���ļ���g++ lab1.cpp -o lab1.exe
���������еķ�ʽ���У�.\lab1.exe test_lab1.txt
����test_lab1.txt���������в���

˵������ʵ��Ļ��������Ψһ��ֻҪ�������
 */

/*
 ��׺���ʽת��׺���ʽ��
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
 */

/*
 cout�Ƚ����ݷŵ��������У������������������endl�����������
 */

class Node { // �洢�������ͺ�ֵ
public:
    string type; // (constant, variable, operator)
    int num = 0; // ����
    string var; // ����
    string op = ""; // ������
};

map<string, int> op_priority; // �����������ȼ�
map<string, int> var_index; // ������������( ������ַ = ����*4 )
stack<string> operator_stack; // ��׺ת��׺��ջ( ������ջ )
vector<Node> postfix_vector; // �洢��׺���ʽ
vector<string> row_after_tokenize; // �ִʺ��һ�д��룬ÿ��Ԫ�ؾ���һ����
fstream file_input; // ��������
fstream file_tokenize_result; // ���ڲ��ԣ������ִʵĽ��

bool is_op(string s) {
    return s == "+" || s == "-" || s == "*" || s == "/" || s == "%" ||
           s == "<" || s == "<=" || s == ">" || s == ">=" || s == "==" || s == "!=" ||
           s == "&" || s == "|" || s == "^";
}

bool is_identifier(string s) {
    if (s.empty())  // ���ַ������Ǳ�ʶ��
        return false;
    if (!isalpha(s[0]) && s[0] != '_')  // ������ַ��Ƿ�����ĸ���»���
        return false;
    for (int i = 1; i < s.length(); i++) { // ����ַ���ʣ�ಿ���Ƿ�ֻ������ĸ�����ֻ��»���
        if (!isalnum(s[i]) && s[i] != '_') // isalnum:���֡���ĸ
            return false;
    }
    return true;
}

bool is_constant(string s) {
    if (s.empty()) // ���ַ������ǳ���
        return false;
    if (s.length() > 1 && s[0] == '-') { // ����
        for (int i = 1; i < s.length(); i++) {
            if (s[i] < '0' || s[i] > '9')
                return false;
        }
    } else { // ���Ǹ������������ַ����������֡�001��ô�죿������
        for (char c: s) {
            if (c < '0' || c > '9')
                return false;
        }
    }
    return true;
}


// �ж�s�Ƿ�Ϸ�
bool is_correct(string s) {
    // ������δ���???
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

void init_op_priority() { // ����ԽС��Խ��
//    op_priority["-"] = 2; //������������Ҫ�޸ġ�
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
    op_priority["("] = 13; // ��c���Բ�ͬ��( ���ȼ��� = �ߣ�������С
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


void print_postfix() { // �����׺���ʽ
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

void write_tokenize_result() { // д��ִʵĽ��
    for (auto i: row_after_tokenize) {
        file_tokenize_result << i << " ";
    }
    file_tokenize_result << endl;
}

void main_stm() { // ��ࣺ int main ( ) {
    // int main(int argc, int argv){...} ��ô��������
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
         << "sub esp, 0x100" << endl; // ��ֵ���Ե���
}

void main_end() {
    cout << "leave" << endl
         << "ret" << endl;
}

void return_stm() {
    string word = row_after_tokenize[1];
    if (is_constant(word))// return ����
        cout << "mov eax, " << word << endl;
    else // return ����
        cout << "mov eax, DWORD PTR [ebp-" << var_index[word] * 4 << "]" << endl;
}

void println_int_stm() { // println_int ( xxx ) ; ����xxxΪ���������
    string word = row_after_tokenize[2];
    if (is_constant(word))// ����
        cout << "push " << word << endl
             << "push offset format_str" << endl
             << "call printf" << endl
             << "add esp, 8" << endl;
    else // ����
        cout << "push DWORD PTR [ebp-" << var_index[word] * 4 << "]" << endl
             << "push offset format_str" << endl
             << "call printf" << endl
             << "add esp, 8" << endl;
}

void int_stm() {
    var_index[row_after_tokenize[1]] = var_index.size() + 1; // ����������
    cout << "mov DWORD PTR [ebp-" << var_index[row_after_tokenize[1]] * 4 << "], 0" << endl;
}

void save_postfix_node(string type, string value) {
    Node temp_node;
    // ���ýڵ�����
    temp_node.type = type;
    // �洢ֵ
    if (type == "operator")
        temp_node.op = operator_stack.top();
    else if (type == "constant")
        temp_node.num = string2int(value);
    else
        temp_node.var = value;
    // �����׺���ʽ
    postfix_vector.push_back(temp_node);
}

void get_postfix() {
    for (auto word: row_after_tokenize) {
        if (word == ";")
            break;
        else if (word == "=") // ��ֵ��ֱ����ջ(�����Ǹ�ֵ�ŵ��������������)
            operator_stack.push("=");
        else if (word == "(") // �����ţ�ֱ����ջ
            operator_stack.push("(");
        else if (word == ")") { // �����ţ�һֱ��ջ��ֱ��������
            while (operator_stack.top() != "(") {
                save_postfix_node("operator", "");
                operator_stack.pop();
            }
            operator_stack.pop(); // �����ų�ջ
        } else if (is_op(word)) { // ��������ջ��or���ȼ�����ջ��������(������ԽС������Խ��)������ֹͣ��ջ�������ò�������ջ
            while (!operator_stack.empty() && (op_priority[word] >= op_priority[operator_stack.top()])) {
                save_postfix_node("operator", "");
                operator_stack.pop();
            }
            operator_stack.push(word);
        } else { // ��������ֱ��д
            if ((word[0] == '-') || ('0' <= word[0] && word[0] <= '9')) // ����
                save_postfix_node("constant", word);
            else // ��������û�п��� a = -b; �������
                save_postfix_node("variable", word);
        }
    }
    // ʣ��Ĳ�������ջ
    while (!operator_stack.empty()) {
        save_postfix_node("operator", "");
        operator_stack.pop();
    }
}

void print_op(string c) { // ע��ÿ���������Ļ���붼��һ��
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
             << "push edx" << endl; // edx������
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
    // �����׺���ʽ��ע����������ջ��
    Node first_node = postfix_vector[0]; // ��һ���ڵ��Ǳ���ֵ�ı���
    // ���⴦��a = 100; ����ʽ
    if (postfix_vector[1].type == "constant" && postfix_vector[2].op == "=") {
        cout << "mov eax, " << postfix_vector[1].num << endl
             << "mov DWORD PTR [ebp-" << var_index[first_node.var] * 4 << "], eax" << endl;
    }
        // һ��ĸ�ֵ���
    else {
        for (int i = 1; i < postfix_vector.size(); i++) {
            // �ڵ��Ǳ���
            if (postfix_vector[i].type == "variable")
                cout << "mov eax, DWORD PTR [ebp-" << var_index[postfix_vector[i].var] * 4 << "]" << endl
                     << "push eax" << endl;
                // �ڵ��ǳ���
            else if (postfix_vector[i].type == "constant")
                cout << "mov eax, " << postfix_vector[i].num << endl
                     << "push eax" << endl;
                // �ڵ��ǲ���������ֵ��
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

void deal_one_stm(string word) { // �жϵ�ǰ����õĸ����ַ����Ƿ񹹳ɾ��ӣ�����ǣ��ͽ��л��
    if (word == "{") { // ��ʱrow_after_tokenize����Ϊint main ( ) {
        main_stm();
//        write_tokenize_result(); // ������ļ������ִʽ��
        row_after_tokenize.clear();
    } else if (word == "}") { // ��ʱrow_after_tokenize����һ��ֻ��һ�� }
        main_end();
//        write_tokenize_result();
        row_after_tokenize.clear();
    } else if (word == ";") { // ��ʱrow_after_tokenize������һ������
        clear();
        if (row_after_tokenize[0] == "int") { // int���
            int_stm();
        } else if (row_after_tokenize[0] == "return") { // return���
            return_stm();
        } else if (row_after_tokenize[0] == "println_int") { // println_int���
            println_int_stm();
        } else { // ��ֵ��䣬�������׺���ʽ���ټ��㡢��������ﲢû������ȥ���㣬ֻ������˻����䡿
            get_postfix();
            cal_postfix();
        }
//        write_tokenize_result();
        row_after_tokenize.clear();
    }
    // ���򲻹��ɾ��ӣ������л��
}

int main(int argc, char *argv[]) {
    file_input.open(argv[1], fstream::in); // �������в���ָ�����ļ�,ֻ��ģʽ
//    file_input.open("D:\\SelfDownLoad\\code\\cppcode\\Compilerlab2\\input.txt", fstream::in); // ������; Ϊʲô���·������
//    file_tokenize_result.open("D:\\SelfDownLoad\\code\\cppcode\\Compilerlab2\\tokenize_result.txt", fstream::out); // ������
    init_op_priority(); // ��ʼ�����������ȼ���
    string word;
    string s;
    // һ��ɨ��ִʣ�һ�߻��
    while (file_input >> s) { // ��ȡһ���ַ�(�Կո񡢻��з��ȷָ�,�������ո��)�����û����Ч�ַ��ˣ�����false����word��ֵ����
        word = "";
        for (auto c: s) { // ��word���зִʣ�word�ǲ����հ׷����ַ���
            word += c;
            if (!is_correct(word)) { // temp�ĳ���һ������1�𣿣���
                row_after_tokenize.push_back(word.substr(0, word.size() - 1)); // ��pos��ʼ����ȡn���ַ�
                deal_one_stm(word.substr(0, word.size() - 1)); // ����word�ж��Ƿ���һ�������ľ��ӣ�����Ǿ��������
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