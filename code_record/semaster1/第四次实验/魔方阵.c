#include <stdio.h>
int main()
{
    int n, a[120][120], x, y;
    scanf("%d", &n);
    //方阵初始化及确定初始位置
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = 0;
        }
    }
    x = 0;
    y = (n - 1) / 2;

    //排列魔方阵元素
    for (int i = 1; i <= n * n; i++)
    {
        a[x][y] = i;
        y = (y + 1 + n) % n;
        x = (x - 1 + n) % n;
        //位置已被占用时重新排列下一个自然数
        if (a[x][y] != 0)
        {
            y = (y - 1 + n) % n;
            x = (x + 2 + n) % n;
        }
    }

    //打印魔方阵
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%5d", a[i][j]);
        }
        printf("\n");
    }
    return 0;
}
