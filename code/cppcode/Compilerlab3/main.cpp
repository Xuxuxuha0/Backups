#include "tools.h"

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

/*
 �Ա��ʽ�Ķ��壺
 ���磺a + b - func ( c )
 */



int main(int argc, char *argv[]) {
    file_input.open(argv[1], fstream::in); // �������в���ָ�����ļ�,ֻ��ģʽ
//    file_input.open("D:\\SelfDownLoad\\code\\cppcode\\Compilerlab3\\input.txt", fstream::in); // ������
//    file_tokenize_result.open("D:\\SelfDownLoad\\code\\cppcode\\Compilerlab3\\tokenize_result.txt", fstream::out); // ������
    init_op_priority(); // ��ʼ�����������ȼ���
    string word;
    string s;
    string correct_word;
    // �������ͷ
    start();
    // һ��ɨ��ִʣ�һ�߻��
    while (file_input >> s) { // ��ȡһ���ַ�(�Կո񡢻��з��ȷָ�,�������ո��)�����û����Ч�ַ��ˣ�����false
        word = "";
        for (auto c: s) { // ��word���зִʣ�word�ǲ����հ׷����ַ���
            word += c;
            if (!is_correct(word)) { // temp�ĳ���һ������1�𣿣���
                // ���word�Ƿ������ȡ�Ϸ�����
                correct_word = word.substr(0, word.size() - 1); // ��pos��ʼ����ȡn���ַ�
                row_after_tokenize.push_back(correct_word);
                deal_one_stm(correct_word); // ����word�ж��Ƿ���һ�������ľ��ӣ�����Ǿ��������
                word = c;
            }
        }
        row_after_tokenize.push_back(word);
        deal_one_stm(word);
    }
    file_input.close();
//    file_tokenize_result.close(); // ������
    return 0;
}