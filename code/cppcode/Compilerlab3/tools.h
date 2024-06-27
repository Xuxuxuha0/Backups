#ifndef COMPILERLAB3_TOOLS_H
#define COMPILERLAB3_TOOLS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <stack>
#include <cctype> // isalpha() 和 isalnum()

using namespace std;

class Node { // 存储单词类型和值
public:
    string type; // (constant, variable, operator)
    int num = 0; // 常量
    string var; // 变量
    string op = ""; // 操作符
};

extern map<string, int> op_priority; // 操作符、优先级
extern map<string, string> var_index; // 局部变量名or形参变量名、变量地址( 例如：a ebp-8 )( 局部都是从ebp-4开始 形参都是从ebp+8开始)
extern int num_local_var; // 局部变量的个数
extern int num_formal_para; // 形参变量的个数
extern stack<string> operator_stack; // 中缀转后缀的栈( 操作符栈 )
extern vector<Node> postfix_vector; // 存储后缀表达式
extern vector<string> row_after_tokenize; // 分词后的一行代码，每个元素就是一个词
extern vector<string> expression_stm; // 存放表达式
extern fstream file_input; // 处理输入
extern fstream file_tokenize_result; // 用于测试，看看分词的结果
extern int num_and; // &&出现的个数
extern int num_or; // ||出现的个数

bool is_punctuation(string s);

bool is_op(string s);

bool is_type(string s);

bool is_identifier(string s);

bool is_constant(string s);

bool is_correct(string s);

void init_op_priority();

int string2int(string s);

void print_postfix();

void write_tokenize_result();

void start();

void func_start();

void func_end();

void return_stm();

void println_int_stm();

void call_stm(int func_begin, int func_end);

void int_stm();

void clear();

void save_postfix_node(string type, string value);

void save_var(string name, int address_num, bool is_local);

int deal_one_exp(string var_name, int begin, int end);

void get_postfix();

void cal_postfix();

void print_op(string c);

void deal_one_stm(string word);

void deal_minus(int begin, int end);

#endif
