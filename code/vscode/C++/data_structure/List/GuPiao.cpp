#include <iostream> //股票撮合系统
using namespace std;
int cnt; //已有多少个委托
typedef struct node
{
    int WeiTuoHao;
    int BianMa;
    double Price;
    int Num;
    char Type;
    struct node *next;
} Node, *List;

typedef struct
{
    List head;
} Deal;

Deal BUY[10000], SALE[10000]; //下标代表股票的编码（每一个编码的股票都有买和卖的单链表）全局变量可以使元素全为NULL

int str_int(string str) // str转int
{
    int number = (str[0] - '0') * 1000 + (str[1] - '0') * 100 + (str[2] - '0') * 10 + (str[3] - '0');
    return number;
}

void Input(List &b, List &s, List t) //处理输入
{
    List ts = s, tb = b;
    printf("orderid: %04d\n", cnt);
    if (t->Num == 0) //特殊情况(坑点)
    {
        if (t->Type == 'b')
        {
            if (s != NULL && s->next != NULL && t->Price >= s->next->Price)
                printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (t->Price + s->next->Price) / 2, 0, t->WeiTuoHao, s->next->WeiTuoHao);
        }
        else
        {
            if (b != NULL && b->next != NULL && b->next->Price >= t->Price)
                printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (t->Price + b->next->Price) / 2, 0, t->WeiTuoHao, b->next->WeiTuoHao);
        }
    }
    else
    {
        if (t->Type == 's')
        {
            if (s == NULL)
            {
                s = (Node *)malloc(sizeof(Node));
                s->BianMa = t->BianMa;
                s->next = t;
                t->next = NULL;
            }
            else
            {
                while (ts->next != NULL && ts->next->Price <= t->Price) //卖：价格小先卖
                    ts = ts->next;
                t->next = ts->next;
                ts->next = t;
            }
        }
        else
        {
            if (b == NULL)
            {
                b = (Node *)malloc(sizeof(Node));
                b->BianMa = t->BianMa;
                b->next = t;
                t->next = NULL;
            }
            else
            {
                while (tb->next != NULL && tb->next->Price >= t->Price) //买：价格高的先买
                    tb = tb->next;
                t->next = tb->next;
                tb->next = t;
            }
        }
    }
}

void calculate(List &b, List &s, char ch) //处理股票撮合
{
    List ts, tb;
    double midprice;
    int minnum;
    if (b == NULL || s == NULL || b->next == NULL || s->next == NULL || b->next->Price < s->next->Price)
        return;
    else
    {
        ts = s->next;
        tb = b->next;
        minnum = (ts->Num > tb->Num) ? tb->Num : ts->Num;
        tb->Num -= minnum;
        ts->Num -= minnum;
        midprice = (ts->Price + tb->Price) / 2;
        if (ch == 'b')
            printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", midprice, minnum, tb->WeiTuoHao, ts->WeiTuoHao);
        else
            printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", midprice, minnum, ts->WeiTuoHao, tb->WeiTuoHao);
        if (tb->Num == 0)
        {
            b->next = tb->next;
            free(tb);
        }
        if (ts->Num == 0)
        {
            s->next = ts->next;
            free(ts);
        }
        calculate(b, s, ch); //继续撮合剩余的新的委托
    }
}

void Query(List b, List s) //查询某个编号的股票的委托剩余情况
{
    List tb = b, ts = s;
    printf("buy orders:\n");
    if (tb == NULL || tb->next == NULL)
        ;
    else
    {
        tb = tb->next;
        while (tb != NULL)
        {
            printf("orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: b\n", tb->WeiTuoHao, tb->BianMa, tb->Price, tb->Num);
            tb = tb->next;
        }
    }

    printf("sell orders:\n");
    if (ts == NULL || ts->next == NULL)
        ;
    else
    {
        ts = ts->next;
        while (ts != NULL)
        {
            printf("orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: s\n", ts->WeiTuoHao, ts->BianMa, ts->Price, ts->Num);
            ts = ts->next;
        }
    }
}

void Delet(int NumWei, int Record[], int Nums, Deal b[], Deal s[]) //删掉某个委托
{
    int i = 0, BM;
    List temp, p;
    while (i < Nums)
    {
        BM = Record[i];
        temp = b[BM].head;
        if (temp == NULL || temp->next == NULL)
            ;
        else
        {
            while (temp->next != NULL)
            {
                if (temp->next->WeiTuoHao == NumWei)
                {
                    p = temp->next;
                    temp->next = temp->next->next;
                    printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: b\n", NumWei, p->BianMa, p->Price, p->Num);
                    free(p);
                    return;
                }
                temp = temp->next;
            }
        }

        temp = s[BM].head;
        if (temp == NULL || temp->next == NULL)
            ;
        else
        {
            while (temp->next != NULL)
            {
                if (temp->next->WeiTuoHao == NumWei)
                {
                    p = temp->next;
                    temp->next = temp->next->next;
                    printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1lf, quantity: %4d, b/s: s\n", NumWei, p->BianMa, p->Price, p->Num);
                    free(p);
                    return;
                }
                temp = temp->next;
            }
        }
        i++;
    }
    printf("not found\n");
}

int main()
{
    int Numbers = 0, RecordMa[10000]; //一共有多少种编码、存储各种编码
    int n, bianma, weituo;            //数字编码,数字委托号
    string Bianma, Weituo;            //字符串编码,字符串委托号
    List temp;
    cin >> n;
    while (n != 0)
    {
        if (n == 1)
        {
            cin >> Bianma;
            bianma = str_int(Bianma);
            RecordMa[Numbers++] = bianma;

            temp = (Node *)malloc(sizeof(Node));
            temp->WeiTuoHao = ++cnt;
            temp->BianMa = bianma;
            cin >> temp->Price >> temp->Num >> temp->Type;

            Input(BUY[bianma].head, SALE[bianma].head, temp);
            calculate(BUY[bianma].head, SALE[bianma].head, temp->Type);
        }
        else if (n == 2)
        {
            cin >> Bianma;
            bianma = str_int(Bianma);
            Query(BUY[bianma].head, SALE[bianma].head);
        }
        else
        {
            cin >> Weituo;
            weituo = str_int(Weituo);
            Delet(weituo, RecordMa, Numbers, BUY, SALE);
        }
        cin >> n;
    }
}