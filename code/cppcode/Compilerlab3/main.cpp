#include "tools.h"

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

/*
 对表达式的定义：
 形如：a + b - func ( c )
 */



int main(int argc, char *argv[]) {
    file_input.open(argv[1], fstream::in); // 打开命令行参数指定的文件,只读模式
//    file_input.open("D:\\SelfDownLoad\\code\\cppcode\\Compilerlab3\\input.txt", fstream::in); // 测试用
//    file_tokenize_result.open("D:\\SelfDownLoad\\code\\cppcode\\Compilerlab3\\tokenize_result.txt", fstream::out); // 测试用
    init_op_priority(); // 初始化操作符优先级表
    string word;
    string s;
    string correct_word;
    // 先输出开头
    start();
    // 一边扫描分词，一边汇编
    while (file_input >> s) { // 读取一串字符(以空格、换行符等分割,不会读入空格等)，如果没有有效字符了，返回false
        word = "";
        for (auto c: s) { // 对word进行分词，word是不含空白符的字符串
            word += c;
            if (!is_correct(word)) { // temp的长度一定大于1吗？？？
                // 如果word非法，则截取合法部分
                correct_word = word.substr(0, word.size() - 1); // 从pos开始，截取n个字符
                row_after_tokenize.push_back(correct_word);
                deal_one_stm(correct_word); // 根据word判断是否是一个完整的句子，如果是就立即汇编
                word = c;
            }
        }
        row_after_tokenize.push_back(word);
        deal_one_stm(word);
    }
    file_input.close();
//    file_tokenize_result.close(); // 测试用
    return 0;
}