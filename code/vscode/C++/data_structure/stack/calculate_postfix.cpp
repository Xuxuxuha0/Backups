#include <iostream>
#include <cmath>
using namespace std;
//本题在转换为逆波兰表达式用的链式栈，在计算逆波兰用的静态栈(数组)
//需要考虑2+-(10-5)吗
double postfix[999];                                        //用来存储逆波兰表达式
int numstack[999], top = -1, post = 0, j = 0, is_calculate; //用于计算逆波兰表达式的值，存储数字的栈、栈顶;postfix元素的个数;读取str的下标;是否要进一步计算。
char str[999];                                              //存储每一行的表达式

typedef struct node //利用链式栈来存储
{
    double data;
    struct node *next;
} snode, *stack;

double convert(char c) //把操作符转换成小数，便于存储
{
    double num[10] = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7};
    char ch[10] = {'(', '+', '-', '*', '/', '%', '^'};
    for (int i = 0; i < 7; i++)
    {
        if (c == ch[i])
            return num[i];
    }
    return 0; //转换失败
}
char convert_to_op(double number) //把小数转换为操作符
{
    double num[10] = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7};
    char ch[10] = {'(', '+', '-', '*', '/', '%', '^'};
    for (int i = 0; i < 7; i++)
    {
        if (number == num[i])
            return ch[i];
    }
}
int prior(double op) //优先级
{
    if (op == 1.1)
        return 0;
    else if (op == 1.2 || op == 1.3)
        return 1;
    else if (op == 1.4 || op == 1.5 || op == 1.6)
        return 2;
    else if (op == 1.7)
        return 3;
}
void input(char &ch, double &op, stack &h) //进栈并输入
{
    stack temp;
    temp = (snode *)malloc(sizeof(snode));
    temp->data = op;
    temp->next = h->next;
    h->next = temp;
    ch = str[j++];
}
void output(stack &h) //出栈
{
    postfix[post++] = h->next->data;
    h = h->next;
}
void instack(char &ch1, double &ch2, stack &head) //处理可以进栈的元素
{
    int a, b;
    if (ch2 == 1.1 && (!convert(str[j - 2]) || str[j] == '+' || str[j] == '*' || str[j] == '/' || str[j] == '%' || str[j] == '^' || str[j] == ')')) //左扩号之前没有操作符 或者 左括号之后是这些不该出现的字符
        is_calculate = 0;
    else if (ch2 == 1.1 || head->next == NULL) //空栈或者 ( 就直接进栈
        input(ch1, ch2, head);
    else //处理其他运算符
    {
        a = prior(ch2);
        b = prior(head->next->data);
        if (a > b) // ch优先级高，直接进栈
            input(ch1, ch2, head);
        else if (a < b) // ch优先级低，出栈，ch不变
        {
            output(head);
            instack(ch1, ch2, head);
        }
        else
        {
            if (ch1 == '^') //当相邻两个都是^，需注意是先算后一个^，所以直接进栈就行
                input(ch1, ch2, head);
            else //否则出栈一个，ch进栈
            {
                output(head);
                input(ch1, ch2, head);
            }
        }
    }
}
int operate(double number) //处理运算
{
    int right, left;
    if (top == -1)
        return 0;
    right = numstack[top--];
    if (top == -1)
        return 0;
    left = numstack[top--];
    char op = convert_to_op(number);
    switch (op)
    {
    case '+':
        numstack[++top] = left + right;
        break;
    case '-':
        numstack[++top] = left - right;
        break;
    case '*':
        numstack[++top] = left * right;
        break;
    case '/':
        if (right == 0) //除数为0
            return 2;
        else
            numstack[++top] = left / right;
        break;
    case '%':
        if (right == 0) //除数为0
            return 2;
        else
            numstack[++top] = left % right;
        break;
    case '^':
        if (right < 0) //幂小于0
            return 3;
        else
            numstack[++top] = pow(left, right);
        break;
    }
    return 1;
}
void calculate()
{
    double number;
    int i = 0, jud;
    while (i < post)
    {
        number = postfix[i];
        if (number >= 1.2 && number <= 1.7) //是操作符
        {
            jud = operate(number);
            if (jud == 0 || jud == 3)
            {
                cout << "error." << endl;
                return;
            }
            else if (jud == 2)
            {
                cout << "Divide 0." << endl;
                return;
            }
        }
        else
            numstack[++top] = number; //是数字就入栈
        i++;
    }
    if (top != 0) //栈里面还有其他元素，说明没处理完，表达式错误。
    {
        cout << "error." << endl;
        return;
    }
    cout << int(numstack[0]) << endl;
}
int main()
{
    stack head;
    head = (snode *)malloc(sizeof(snode)); // head->next是栈顶
    char ch1;                              //存储要处理的字符
    double ch2;                            //操作符对应的数字
    int n, judge = 1, flag = 1, num = 0;   //表达式个数、判断下一个是否可能为负号、为负数的标志、临时存储数字、是否要计算
    cin >> n;
    while (n--)
    {
        head->next = NULL;
        cin >> str;
        j = 0;
        judge = 1;
        post = 0;
        flag = 1;
        num = 0;
        top = -1;
        is_calculate = 1;

        ch1 = str[j++];
        if (ch1 == '-') //考虑一来就是个负号
        {
            flag = -1; //表示接下来是个负数
            ch1 = str[j++];
        }
        else if (ch1 == '(') //考虑一来就是个扩号
        {
            ch2 = 1.1;
            judge = -1;
            input(ch1, ch2, head);
        }

        while (1) //转换为逆波兰表达式
        {
            if (ch1 == '\0') //结束符，一直出栈
            {
                while (head->next != NULL)
                {
                    if (head->next->data == 1.1) //如果最终退栈的时候还有'('，直接设置错误标志。
                    {
                        is_calculate = 0;
                        break;
                    }
                    else
                        output(head);
                }
                break;
            }
            else if (ch1 >= '0' && ch1 <= '9') //数字
            {
                judge = 1; //接下来不会出现负号
                num = int(num) * 10 + (ch1 - '0');
                ch1 = str[j++];
                if (!(ch1 >= '0' && ch1 <= '9'))
                {
                    num *= flag;
                    postfix[post++] = num;
                    num = 0;
                    flag = 1;
                }
            }
            else if (ch1 == '-' && judge == -1) //考虑是否为负号
            {
                flag = -1;
                ch1 = str[j++];
            }
            else if (ch1 == ')') //一直出栈直到(
            {
                judge = 1;
                if (j - 2 < 0 || convert(str[j - 2]) || str[j] == '(' || (str[j] != '\0' && str[j] != ')' && !convert(str[j]))) //如果第一个就是')'或者 ')'前面是个运算符 或者 )后面还有元素且不是应该出现的符号，就设置错误
                    is_calculate = 0;
                else
                {
                    while (head->next != NULL && head->next->data != 1.1)
                        output(head);
                    if (head->next == NULL) //如果有')',没有对应的'(',直接设置错误标志。
                        is_calculate = 0;
                    else
                    {
                        head = head->next;
                        ch1 = str[j++];
                    }
                }
            }
            else //以上全是不能进栈的元素的处理“结束符、右括号、负号、数字”，以下开始可以进栈的元素处理
            {
                judge = -1; //下一个一定有可能是负号
                ch2 = convert(ch1);
                instack(ch1, ch2, head);
            }
            if (is_calculate == 0)
                break;
        }
        if (is_calculate == 0) //有错误标志
        {
            cout << "error." << endl;
            continue;
        }
        else
            calculate(); //计算逆波兰的值
    }
    return 0;
}
/*
第一行为整数N。表示下面有N个表达式
从第二行起的后面N行为N个由整数构成的表达式

共N行，每行为相应表达式的计算结果。
如果在计算过程中出现除数为0的情况，则输出：Divide 0.
如果判断出表达式有错误，则输出：error.

特殊情况说明：
在表达式中，如果操作数出现负数（例如-8），则要特别注意。例如：
10加-8表示为：10+-8。
10减-8表示为：10--8。
*/