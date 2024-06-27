#include <iostream> //自创的逆波兰表达式
using namespace std;
typedef struct node // 利用栈来存储
{
    char data;
    struct node *next;
} snode, *stack;
int prior(char ch) // 优先级
{
    if (ch == '(')
        return 0;
    else if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/' || ch == '%')
        return 2;
    else if (ch == '^')
        return 3;
}
void input(char &ch, stack &h) // 进栈并输入
{
    stack temp;
    temp = (snode *)malloc(sizeof(snode));
    temp->data = ch;
    temp->next = h->next;
    h->next = temp;
    cin >> ch;
}
void output(stack &h) // 出栈
{
    cout << h->next->data;
    h = h->next;
}
int main()
{
    stack head;
    head = (snode *)malloc(sizeof(snode));
    head->data = -1;
    head->next = NULL; // head->next是栈顶
    char ch;
    int a, b, n;
    cin >> n;
    while (n--)
    {
        cin >> ch;
        while (1)
        {
            if (ch == '#') // 结束符，一直出栈
            {
                while (head->next != NULL)
                    output(head);
                break;
            }
            else if (isalpha(ch)) // 字母，直接输出
            {
                cout << ch;
                cin >> ch;
            }
            else if (ch == ')') // 一直出栈直到 (
            {
                while (head->next->data != '(')
                    output(head);
                head = head->next;
                cin >> ch;
            }
            else if (ch == '(' || head->next == NULL) // 空栈或者 ( 就直接进栈
                input(ch, head);
            else // 处理其他运算符
            {
                a = prior(ch);
                b = prior(head->next->data);
                if (a > b) // ch优先级高，直接进栈
                    input(ch, head);
                else if (a < b) // ch优先级低，出栈，ch不变
                    output(head);
                else
                {
                    if (ch == '^') // 当相邻两个都是^，需注意是先算后一个^，所以直接进栈就行
                        input(ch, head);
                    else // 否则出栈一个，ch进栈
                    {
                        output(head);
                        input(ch, head);
                    }
                }
            }
        }
        cout << endl;
    }
    return 0;
}
/*
中缀表达式就是我们通常所书写的数学表达式，后缀表达式也称为逆波兰表达式，在编译程序对我们书写的程序中的表达式进行语法检查时，往往就可以通过逆波兰表达式进行。我们所要设计并实现的程序就是将中缀表示的算术表达式转换成后缀表示，例如，将中缀表达式

(A 一 (B*C 十 D)*E) ／ (F 十 G )

转换为后缀表示为：ABC*D十E*--FG十／

注意：为了简化编程实现，假定变量名均为单个字母，运算符只有＋，－，＊，／ 和＾（指数运算，要注意运算符的结合性），可以处理圆括号 (），并假定输入的算术表达式正确。

要求：使用栈数据结构实现 ，输入的中缀表达式以＃号结束
*/