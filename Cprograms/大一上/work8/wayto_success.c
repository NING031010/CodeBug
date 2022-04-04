#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int n; //数字个数
    scanf("%d", &n);
    int *p;
    p = (int *)malloc(n * sizeof(int)); //分配内存
    for (int i = 0; i < n; i++)
    {
        scanf("%d", p + i);
    }
    int b[101][101]; //b[i][j]代表只剩第i到j个数时能选到的最大值
    memset(b, 0, sizeof(b));
    int sum = 0, Sum = 0; //sum是剩余数（即i到j）的和，Sum是所有数的和
    for (int k = 0; k < n; k++)
    {
        Sum += p[k];
    }
    for (int k = 0; k < n; k++)
    {
        b[k][k] = p[k]; //只剩一个数字，选它！
    }
    for (int i = n - 2; i >= 0; i--)
    { //动态规划，从小(只剩一个数)到大（还未选）
        for (int j = i + 1; j < n; j++)
        {
            for (int k = i; k <= j; k++)
            {
                sum += p[k];
            }
            b[i][j] = sum - (b[i + 1][j] < b[i][j - 1] ? b[i + 1][j] : b[i][j - 1]);
            //游戏者的局部最优解（即剩余数的和 - 对手选的较小值）
            sum = 0;
        }
    }
    free(p);
    printf("%d %d", b[0][n - 1], Sum - b[0][n - 1]); //输出结果
    system("pause");
    return 0;
}