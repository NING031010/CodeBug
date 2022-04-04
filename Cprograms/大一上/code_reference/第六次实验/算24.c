#include <stdio.h>
#include <math.h>

int count_24(double num[][4], int n, int r) //判断能否算出24的函数
{
    int m;
    int i, j, k;
    double temp[201][4]; //暂时存储未被选择的数以及选出的两个数的计算结果
    if (n == 1)          //出口条件
    {
        if ((fabs(num[r][0] - 24)) <= 1E-6) //只剩一个数时，该数为24
            return 1;
        else
            return 0;
    }
    /*
     递归做法：先从四个数中选出两个进行任意一种四则运算，将结果和剩下两个数存入新数组，在从新数组中选两个做任意一种四则运算，最后只剩两个数再一次进行运算。若最终结果为24，则成功；否则返回上一步换一种运算方法，尝试所有的运算法则后均不能得到24，则失败。
     */
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            m = 0;
            for (k = 0; k < n; k++)
            {
                if (k != i && k != j) //选出两个数做计算，剩下的数依次存放在temp数组中
                {
                    temp[r][m] = num[r][k];
                    m++;
                }
            }
            temp[r][m] = num[r][i] + num[r][j];
            if (count_24(temp, m + 1, r) == 1) //依次调用直到m=1
                return 1;
            temp[r][m] = num[r][i] - num[r][j];
            if (count_24(temp, m + 1, r) == 1)
                return 1;
            temp[r][m] = num[r][j] - num[r][i];
            if (count_24(temp, m + 1, r) == 1)
                return 1;
            temp[r][m] = num[r][i] * num[r][j];
            if (count_24(temp, m + 1, r) == 1)
                return 1;
            if (num[r][i] != 0.0) //保证除数不为0
            {
                temp[r][m] = num[r][j] / num[r][i];
                if (count_24(temp, m + 1, r) == 1)
                    return 1;
                temp[r][m] = -num[r][j] / num[r][i];
                if (count_24(temp, m + 1, r) == 1)
                    return 1;
            }
            if (num[r][j] != 0.0)
            {
                temp[r][m] = num[r][i] / num[r][j];
                if (count_24(temp, m + 1, r) == 1)
                    return 1;
                temp[r][m] = -num[r][i] / num[r][j];
                if (count_24(temp, m + 1, r) == 1)
                    return 1;
            }
        }
    }
    return 0;
}

int main()
{
    double num[201][4];
    int i, j;
    int row; //总共输入的行数-1
    for (i = 0;; i++)
    {
        for (j = 0; j < 4; j++)
            scanf("%lf", &num[i][j]);
        if ((fabs(num[i][0]) <= 1E-6) && (fabs(num[i][1]) <= 1E-6) && (fabs(num[i][2]) <= 1E-6) && (fabs(num[i][3]) <= 1E-6))
        { //当输入的一行全为0时
            row = i;
            break; //结束
        }
    }
    for (int r = 0; r < row; r++) //依次对每行输入做判断
    {
        if (count_24(num, 4, r) == 1)
            printf("1\n");
        else
            printf("0\n");
    }

    return 0;
}
