#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define n 100000
#pragma GCC optimize(3)

int my_rand() // 生成大随机数
{
    if (n < 30000)
    {
        return rand();
    }
    else
    {
        int temp = rand();
        int temp_ = rand() % 3000;
        return temp + temp_ * 30000;
    }
}

int main()
{
    int flag = 0;
    while (1)
    {
        int num = myrand();
        if (num == 99997)
        {
            flag++;
        }
        if (flag == 1)
        {
            printf("ture");
            break;
        }
    }
    system("pause");
}
