//从低位到高位的基数排序
#include <iostream>
#include <string.h>
#include "StaticList.h"
using namespace std;
#define radix 10 //十进制
#define d 3      //最大三位数

int GetDigit(int x, int k) //从整数x中提取第k位数字，最高位k=1
{
    if (k < 1 || k > d)
        return -1;                   //不合法
    for (int i = 1; i <= d - k; i++) // for循环退出后，第k位数字处在个位
        x /= 10;
    return x % 10;
}

void LSDsort(StaticList &SL) //初始时SL构成环
{
    int i, j;
    int rear[radix], front[radix]; //队列的头指针和尾指针
    for (i = d; i >= 1; i--)
    {
        memset(front, 0, sizeof(front));
        for (j = SL.elem[0].link; j != 0; j = SL.elem[j].link)
        {
            int k = GetDigit(SL.elem[j].data, i); //取第i位数字
            if (front[k] == 0)                    //队空就让j成为队头
                front[k] = j;
            else
                SL.elem[rear[k]].link = j; //否则插入队尾
            rear[k] = j;                   //更新队尾
        }
    }

    for (i = 0; i < radix && front[i] == 0; i++) //找到第一个不空的队
        ;

    int end;
    SL.elem[0].link = front[i]; //把所有队列连起来
    end = rear[i];
    for (int k = i + 1; k < radix; k++)
    {
        if (front[k] != 0)
        {
            SL.elem[end].link = front[k];
            end = rear[k];
        }
    }
    SL.elem[end].link = 0; //构成环
}