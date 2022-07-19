#include <stdio.h>
#include <stdlib.h>
int a[15], sum = 0;
long long ans[1000];

//判断当前放置方法是否合法
int check(int x)
{
    for (int i = 1; i <= x - 1; i++)
    {
        for (int j = i + 1; j <= x; j++)
        {
            if ((a[i] == a[j]) ||
                (a[i] - i == a[j] - j) ||
                (a[i] + i == a[j] + j))
            {
                return 0;
            }
        }
    }
    return 1;
}

//放置第 x 行的皇后
void setqueen(int x, int n)
{
    //退出递归条件:放置完成
    if (x == n)
    {
        for (int i = 1; i <= n; i++)
        {
            a[x] = i;
            if (check(x))
            {
                //储存当前解
                ans[sum] = 0;
                for (int j = 1; j <= n; j++)
                {
                    ans[sum] = ans[sum] * 10 + a[j];
                }
                sum++;
            }
        }
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            a[x] = i;
            if (check(x))
            {
                //递归放置第 x+1 行的皇后
                setqueen(x + 1, n);
            }
        }
    }
    return;
}

int main()
{
    int n;
    scanf("%d", &n);
    //放置皇后
    setqueen(1, n);
    //输出结果
    printf("%d\n", sum);
    for (int i = 0; i < sum; i++)
    {
        printf("%lld\n", ans[i]);
    }
    system("pause");
    return 0;
}

