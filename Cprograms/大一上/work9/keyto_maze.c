#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    //输入
    int m, n;
    scanf("%d %d", &m, &n);
    long maze[m + 1][n + 1];
    memset(maze, 0, sizeof(maze));
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%ld", &maze[i][j]);
        }
    }
    //处理
    long total[m + 1][n + 1]; //total[i]记录1到i行合并后的结果
    memset(total, 0, sizeof(total));
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            total[i][j] = maze[i][j] + total[i - 1][j];
        }
    }

    long max = maze[1][1];          //记录最大值
    int p = 1, q = 1, b = 1, d = 1; //记录最大值所在行与列
    long temp[n + 1];               //i到j行合并后的结果
    long total_[n + 1];             //temp[1]累加到temp[i]的结果

    for (int i = 1; i <= m; i++)
    {
        for (int j = i; j <= m; j++)
        {
            memset(temp, 0, sizeof(temp));
            memset(total_, 0, sizeof(total_));
            for (int x = 1; x <= n; x++)
            { //转化为一维数组最大和问题
                temp[x] = total[j][x] - total[i - 1][x];
            }
            for (int o = 1; o <= n; o++)
                total_[o] = total_[o - 1] + temp[o];

            long dp[n + 1][n + 1]; //dp[i][j]表示从第i到j个元素的和
            memset(dp, 0, sizeof(dp));
            for (int w = 1; w <= n; w++)
            {
                for (int v = w; v <= n; v++)
                {
                    dp[w][v] = total_[v] - total_[w - 1];
                    if (dp[w][v] > max)
                    {
                        max = dp[w][v];
                        p = i;
                        q = j;
                        b = w;
                        d = v;
                    }
                }
            }
        }
    }
    //输出
    printf("(");
    printf("%d, %d", p, b);
    printf(") ");
    printf("(");
    printf("%d, %d", q, d);
    printf(") ");
    printf("%ld", max);
    system("pause");
    return 0;
}
