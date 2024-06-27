#ifndef COMPILERLAB3_TOOLS_H
#define COMPILERLAB3_TOOLS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <stack>
#include <cctype> // isalpha() �� isalnum()

using namespace std;

class Node { // �洢�������ͺ�ֵ
public:
    string type; // (constant, variable, operator)
    int num = 0; // ����
    string var; // ����
    string op = ""; // ������
};

extern map<string, int> op_priority; // �����������ȼ�
extern map<string, string> var_index; // �ֲ�������or�βα�������������ַ( ���磺a ebp-8 )( �ֲ����Ǵ�ebp-4��ʼ �βζ��Ǵ�ebp+8��ʼ)
extern int num_local_var; // �ֲ������ĸ���
extern int num_formal_para; // �βα����ĸ���
extern stack<string> operator_stack; // ��׺ת��׺��ջ( ������ջ )
extern vector<Node> postfix_vector; // �洢��׺���ʽ
extern vector<string> row_after_tokenize; // �ִʺ��һ�д��룬ÿ��Ԫ�ؾ���һ����
extern vector<string> expression_stm; // ��ű��ʽ
extern fstream file_input; // ��������
extern fstream file_tokenize_result; // ���ڲ��ԣ������ִʵĽ��
extern int num_and; // &&���ֵĸ���
extern int num_or; // ||���ֵĸ���

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
