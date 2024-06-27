#include "tools.h"

map<string, int> op_priority; // �����������ȼ�
map<string, string> var_index; // �ֲ�������or�βα�������������ַ( ���磺a ebp-8 )( �ֲ����Ǵ�ebp-4��ʼ �βζ��Ǵ�ebp+8��ʼ)
int num_local_var; // �ֲ������ĸ���
int num_formal_para; // �βα����ĸ���
stack<string> operator_stack; // ��׺ת��׺��ջ( ������ջ )
vector<Node> postfix_vector; // �洢��׺���ʽ
vector<string> row_after_tokenize; // �ִʺ��һ�д��룬ÿ��Ԫ�ؾ���һ����
vector<string> expression_stm; // ��ű��ʽ
fstream file_input; // ��������
fstream file_tokenize_result; // ���ڲ��ԣ������ִʵĽ��
int num_and; // &&���ֵĸ���
int num_or; // ||���ֵĸ���

bool is_punctuation(string s) {
    return s == ";" || s == "{" || s == "}" || s == "(" || s == ")" ||
           s == "=";
}

bool is_op(string s) { // �Ƿ�Ϊ������( "-"��ʾ������"#"��ʾ�Ա���ȡ�� )
    return s == "+" || s == "-" || s == "*" || s == "/" || s == "%" ||
           s == "<" || s == "<=" || s == ">" || s == ">=" || s == "==" || s == "!=" ||
           s == "&" || s == "|" || s == "^" ||
           s == "&&" || s == "||" ||
           s == "!" || s == "~" || s == "#";
}

bool is_type(string s) { // �Ƿ�Ϊ���ͱ�ʶ��
    if (s == "int" || s == "void")
        return true;
    return false;
}

bool is_identifier(string s) { // �Ƿ�Ϊ��ʶ��
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

bool is_constant(string s) { // �Ƿ��ǳ���(���Դ�������)
    if (s.empty()) // ���ַ������ǳ���
        return false;
    if (s.length() > 1 && s[0] == '-') { // ������
        for (int i = 1; i < s.length(); i++) {
            if (s[i] < '0' || s[i] > '9')
                return false;
        }
    } else { // ���Ǹ������������ַ�����������
        for (char c: s) {
            if (c < '0' || c > '9')
                return false;
        }
    }
    return true;
}


bool is_correct(string s) { // �ж�s�Ƿ�Ϸ�
    // �ؼ���Ҳ����is_identifier
    return is_punctuation(s) || is_op(s) || is_identifier(s) || is_constant(s);
}

void clear() {
    postfix_vector.clear();
    while (!operator_stack.empty()) operator_stack.pop();
//    while (!constant_stack.empty()) constant_stack.pop();
}

void init_op_priority() { // ����ԽС��Խ��
    op_priority["#"] = 2; // ��ʾ�Ա���ȡ��
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
    op_priority["("] = 13; // ��c���Բ�ͬ��( ���ȼ��� = �ߣ�������С
}

int string2int(string s) { // ���ַ���ת��Ϊ����
    int num = 0, i = 0, isNeg = 0;
    if (s[0] == '-') { // ����
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

void start() { // �����ļ��ʼ�Ļ��
    cout << ".intel_syntax noprefix" << endl
         << ".extern printf" << endl // ��һ�пɱ�
         << ".data" << endl
         << "format_str:" << endl
         << R"(.asciz "%d\n")" << endl
         << ".text" << endl;
}

void func_start() { // ��������Ŀ�ͷ������ֵ���� ������ ( �β����� �β���, �β����� �β��� ) {
    num_local_var = 0;
    num_formal_para = 0;
    var_index.clear(); // ÿ�����������Լ��ľֲ�����or�βΣ�һ�����ú���ɨ�����ˣ��Ͳ�����
    string func_name = row_after_tokenize[1]; // ������
    cout << ".global " << func_name << endl // ����
         << func_name << ":" << endl
         << "push ebp" << endl
         << "mov ebp, esp" << endl
         << "sub esp, 256" << endl; // Ϊ�ֲ���������256�ֽڵĿռ䣬��ֵ���Ե���
    // �������βδ�����
    for (int i = 3; row_after_tokenize[i] != ")"; i++) {
        // i���β�����,i+1�����β���
        if (is_type(row_after_tokenize[i])) {
            num_formal_para++;
            save_var(row_after_tokenize[i + 1], (num_formal_para + 1) * 4, false);
        }
    }
}

void func_end() {
    // ���к����Ľ�������
    cout << "leave" << endl
         << "ret" << endl;
}

void return_stm() {
    // return xxx ;
    // ����ֵһ�ɷ���eax����
    if (row_after_tokenize.size() == 3) {
        string word = row_after_tokenize[1];
        if (is_constant(word))// return ���� ;
            cout << "mov eax, " << word << endl;
        else // return ���� ;
            cout << "mov eax, DWORD PTR [" << var_index[word] << "]" << endl;
    } else { // return ���ʽ ;
        deal_one_exp("", 1, row_after_tokenize.size() - 2);
    }
}

void println_int_stm() {
    // println_int ( xxx ) ;
    if (row_after_tokenize.size() == 5) {
        string word = row_after_tokenize[2];
        if (is_constant(word))// ����
            cout << "push " << word << endl
                 << "push offset format_str" << endl
                 << "call printf" << endl
                 << "add esp, 8" << endl;
        else // ����
            cout << "push DWORD PTR [" << var_index[word] << "]" << endl
                 << "push offset format_str" << endl
                 << "call printf" << endl
                 << "add esp, 8" << endl;
    } else { // ���ʽ
        deal_one_exp("", 2, row_after_tokenize.size() - 3);
        cout << "push eax" << endl
             << "push offset format_str" << endl
             << "call printf" << endl
             << "add esp, 8" << endl;
    }
}

void call_stm(int func_begin, int func_end) {
    // �����Զ���ĺ�����ĩβû�зֺ�
    // ���磺myfunc ( a , b , xxx )
    // [s_begin,s_end]���Ǹô��ķ�Χ
    // �Ƚ���Ԥ����
    string func_name = row_after_tokenize[func_begin];
    row_after_tokenize.insert(row_after_tokenize.begin() + func_begin + 2, ",");
    func_end++;
    // ��ʱ��Ϊ��myfunc ( , a , b , xxx ) ���Ը��ݶ��ŷָ�
    // ������������ú����������Ĳ���Ҳ��,�ָ�ġ�
    stack<int> comma_index; // ��Ŷ��ŵ��±꣬ջ���������һ������
    for (int i = 0; i < row_after_tokenize.size(); i++)
        if (row_after_tokenize[i] == ",")
            comma_index.push(i);
    int num_para = comma_index.size(); // �βθ���
    // ������ÿ���β�
    int para_begin;
    int para_end = func_end - 1;
    while (!comma_index.empty()) {
        para_begin = comma_index.top(); // ָ�򶺺�
        comma_index.pop();
        // ( begin,end ] ���Ǹ��β�
        if ((para_end - para_begin) == 1) { // ���β��ǳ���or����
            if (is_constant(row_after_tokenize[para_end]))
                cout << "push " << row_after_tokenize[para_end] << endl; // ����ʾ����һ����û��eax
            else
                cout << "push DWORD PTR [" << var_index[row_after_tokenize[para_end]] << "]"
                     << endl; // ����ʾ����һ����û��eax
        } else { // �Ǳ��ʽ
            int last_para_end = para_end;
            para_end = deal_one_exp("", para_begin + 1, para_end);
            func_end -= (para_end - last_para_end); // ��Ϊ��������βΣ�����row_after_tokenize���޸���
            cout << "push eax" << endl;
        }
        para_end = para_begin - 1;
    }
    cout << "call " << func_name << endl
         << "add esp, " << num_para * 4 << endl;
    // ��ʱ�����ķ���ֵ��eax����
    // ��[func_begin+1, func_end]ȫɾ�ˣ���Ϊ�����Ѿ�û����
    row_after_tokenize.erase(row_after_tokenize.begin() + func_begin + 1, row_after_tokenize.begin() + func_end + 1);
}


void int_stm() { // int a , b = a , c = func ( a + 100 ) ;
    int i = 0;
    int var;
    while (true) {
        i++;
        var = i; // row_after_tokenize[var]���Ǳ�����
        num_local_var++;
        save_var(row_after_tokenize[var], num_local_var * 4, true); // ���±�������
        i++; // ����������һ����
        if (row_after_tokenize[i] == "," || row_after_tokenize[i] == ";") // ˵��û�ж�����ʼ��
            cout << "mov DWORD PTR [" << var_index[row_after_tokenize[var]] << "], 0" << endl;
        else if (row_after_tokenize[i] == "=") { // �ñ��ʽ�Ըñ�����ʼ��
            // ���ñ��ʽ xxx, ������
            i++;
            int begin = i;
            while (row_after_tokenize[i] != "," && row_after_tokenize[i] != ";") {
                i++;
            }
            i = deal_one_exp(row_after_tokenize[var], begin, i - 1) + 1; // ��Ϊrow_after_tokenize���ܱ��޸�
        } else
            cout << "error in int_stm!!!" << endl;
        if (row_after_tokenize[i] == ";")
            break;
    }
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
    // �������룺( a + b ) * c
    clear();
    for (auto word: expression_stm) {
        if (word == "(") // �����ţ�ֱ����ջ
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
            else // ������
                save_postfix_node("variable", word);
        }
    }
    // ʣ��Ĳ�������ջ
    while (!operator_stack.empty()) {
        save_postfix_node("operator", "");
        operator_stack.pop();
    }
//    print_postfix(); // ������
}

void print_op(string c) { // ע��ÿ���������Ļ���붼��һ��
    if (c != "~" && c != "!" && c != "#") // - a ����� # a
        cout << "pop ebx" << endl;
    cout << "pop eax" << endl;
    if (c == "+") {
        cout << "add eax, ebx" << endl
             << "push eax" << endl;
    } else if (c == "-") { // ��û���Ǹ����������
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
    } else if (c == "&&") { // ��Ҫ��֤goto��flagΨһ
        num_and += 3; // ��Ϊ������3��flag
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
        num_or += 3; // ��Ϊ������3��flag
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
    } else if (c == "!") { // �����ǵ�Ŀ����
        cout << "test eax, eax\n"
                "setz al\n"
                "movzx eax, al" << endl
             << "push eax" << endl;
    } else if (c == "~") {
        cout << "not eax" << endl
             << "push eax" << endl;
    } else if (c == "#") { // ������
        cout << "neg eax" << endl
             << "push eax" << endl;
    } else cout << "no such op!!!!!" << endl;
}

void cal_postfix() {
    // �����׺���ʽ��ע����������ջ��
//    // ���⴦��ֻ��һ������
//    if (postfix_vector[0].type == "constant" && postfix_vector.size() == 1) {
//        cout << "mov eax, " << postfix_vector[0].num << endl;
//    }
    // һ��ĸ�ֵ���
//    else {
    for (int i = 0; i < postfix_vector.size(); i++) {
        // �ڵ��Ǳ���
        if (postfix_vector[i].type == "variable")
            cout << "mov eax, DWORD PTR [" << var_index[postfix_vector[i].var] << "]" << endl
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
            else cout << "error!!!!!!!" << endl;
        }
    }
    cout << "pop eax" << endl;
//    }
}

void deal_one_stm(string word) {
    // �жϵ�ǰ����õĸ����ַ����Ƿ񹹳ɾ��ӣ�����ǣ��ͽ��л��
    if (word == "{") { // ��ʱrow_after_tokenize����Ϊ������ֵ���� ������ ( �β� ) {
//        write_tokenize_result(); // ������ļ������ִʽ��
        func_start();
        row_after_tokenize.clear();
    } else if (word == "}") { // ��ʱrow_after_tokenize����һ��ֻ��һ�� }
//        write_tokenize_result(); // ������ļ������ִʽ��
        func_end();
        row_after_tokenize.clear();
    } else if (word == ";") { // ��ʱrow_after_tokenize������һ������
//        write_tokenize_result(); // ������ļ������ִʽ��
        if (row_after_tokenize[0] == "int") { // int���
            int_stm();
        } else if (row_after_tokenize[0] == "return") { // return���
            return_stm();
        } else if (row_after_tokenize[0] == "println_int") { // println_int���
            println_int_stm();
        } else if (row_after_tokenize[1] == "=") { // ���ʽ��ֵ��䣺a = xxx ;
            // �������׺���ʽ���ټ��㡢���
            deal_one_exp(row_after_tokenize[0], 2, row_after_tokenize.size() - 2);
        } else { // �����ú�������䣺func ( a , b , xxx ) ;
            call_stm(0, row_after_tokenize.size() - 2);
        }
        row_after_tokenize.clear();
    }
    // ���򲻹��ɾ��ӣ������л��
}


int deal_one_exp(string var_name, int begin, int end) {
    // row_after_tokenize[begin,end]�Ǳ��ʽ
    // ���磺a + b - func ( c )
    // ���var_name��Ϊ�գ�����ʽ������ֵҪ����var_name
    // �ȴ�����
    deal_minus(begin, end);
    // ������Ҳ�������ʽ��һ���֣����ɾֲ��������洢�÷���ֵ���ٰ�����ͨ���ʽ���㡾�ݲ����Ǻ�������Ҳ�Ǻ�����
    int func_begin = begin, func_end;
    while (func_begin < end) {
        if (is_identifier(row_after_tokenize[func_begin]) &&
            row_after_tokenize[func_begin + 1] == "(") {// func_beginָ��������func_begin+1��������
            // ��func_endָ��������
            int cnt = 0;
            func_end = func_begin + 1; // ��ʼָ��������
            do {
                if (row_after_tokenize[func_end] == "(")
                    cnt++;
                else if (row_after_tokenize[func_end] == ")")
                    cnt--;
                func_end++;
            } while (cnt != 0);
            func_end--; // �����һλ
            // ���ڽ�Ҫ�ѱ��ʽ��"��������"�滻Ϊ"����"�����ԭ�ȵ�endҲҪ�ƶ�
            // �����⣺�����˼·��ԭ������deal_one_exp��endҲҪ���¡�
            end -= (func_end - func_begin);
            // ���ú�����func ( xxx )
            // �ú������������˺���ֵ������eax���棻����row_after_tokenize��Ӧ�������õĴ�Ԫȫɾ�ˣ�ֻ����func_begin����������
            call_stm(func_begin, func_end);
            // ��eax��ֵ����һ���ֲ��������棬func_begin���λ�ô�Ÿñ���
            string func_name = row_after_tokenize[func_begin];
            num_local_var++;
            int address_num = num_local_var * 4;
            string name = func_name + to_string(address_num); // �ñ�������Ϊ��������+��ַ��
            save_var(name, address_num, true); // ���±�������
            cout << "mov DWORD PTR [" << var_index[name] << "], eax" << endl; // �Ѻ�������ֵ���������
            row_after_tokenize[func_begin] = name; // ����Ч�������ʽ��"��������"�滻Ϊ"����"��������ֵ���Ǻ����ķ���ֵ
        }
        func_begin++;
    }
    // ��ʱ���ǲ����������õı��ʽ
    expression_stm.clear();
    while (begin <= end) {
        expression_stm.push_back(row_after_tokenize[begin]);
        begin++;
    }
    get_postfix();
    cal_postfix();
    // ��ʱ���ʽ��ֵ��eax����
    if (var_name != "") { // �Ǹ�ֵ���
        cout << "mov DWORD PTR [" << var_index[var_name] << "], eax" << endl;
    }
    return end; // ��Ϊrow_after_tokenize���ܱ��޸���
}

void save_var(string name, int address_num, bool is_local) { // �洢һ���ֲ�����or�β�
    string str_address_num = std::to_string(address_num);
    if (is_local) // �Ǿֲ�����
        var_index[name] = "ebp-" + str_address_num;
    else // �β�
        var_index[name] = "ebp+" + str_address_num;
}

void deal_minus(int begin, int end) {
    // ���ڴ�����ʽ[begin,end]�еĸ��������������ڷִʵ�ʱ��ʹ�����ˣ�
    // ���磺- a ���տ�ʼ����ȡ������ a + - b������ǰ��������������ţ�
    // ˼·���� - ��� #
    if (row_after_tokenize[begin] == "-")
        row_after_tokenize[begin] = "#";
    for (int i = begin; i < end; i++) {
        if (row_after_tokenize[i + 1] == "-" &&
            (is_op(row_after_tokenize[i]) || row_after_tokenize[i] == "("))
            row_after_tokenize[i + 1] = "#";
    }
}


