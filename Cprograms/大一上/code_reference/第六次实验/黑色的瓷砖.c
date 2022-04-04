#include <stdio.h>
// int a[100][100];   //标志该位置已经被检验
int map[100][100]; //存储方块颜色
int sum;           //总共能到的黑色方块数

void black_China(int m, int n, int i, int j)
{
    if (map[i][j] == 1) // 如果该方块是红色或已经走过此方块，跳出函数
        return;
    sum++;         //否则总块数加一
    map[i][j] = 1; //该位置检验过记为1
    if (i + 1 < m)
        black_China(m, n, i + 1, j); //下递归
    if (i - 1 >= 0)
        black_China(m, n, i - 1, j); //上递归
    if (j + 1 < n)
        black_China(m, n, i, j + 1); //右递归
    if (j - 1 >= 0)
        black_China(m, n, i, j - 1); //左递归
}

int main()
{
    int m, n, x, y; //行数，列数，起始行数，起始列数
    int i, j;
    scanf("%d %d %d %d", &m, &n, &x, &y);
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &map[i][j]);
        }
    }
    if (map[x][y] == 1) //如果起始位置是红色
        printf("error\n");
    else
    {
        black_China(m, n, x, y);
        printf("%d\n", sum);
    }

    return 0;
}
