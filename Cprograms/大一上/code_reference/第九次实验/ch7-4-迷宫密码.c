/***********************
【问题描述】猪无戒将蓝兔关在了一座迷宫里。虹猫来到紧闭的迷宫大门前，
发现需要输入密码才能将大门打开。守门人告诉他密码就隐藏在门旁的一个方形木盘中。
方形木盘中有 m 行 n 列格子，每个格子中刻有一个整数，
虹猫需要选择一个数字之和最大的长方形区域来开启迷宫大门。虹猫应该怎么做呢？
注意：应当尽可能避免子矩阵求和的重复运算。
【输入形式】第一行是两个行列数的两个整数 m, n, 0 < m, n <= 100。
第二行起是矩阵的元素输入，每个元素在[-32766, 32766]范围内。
【输出形式】两个坐标和一个整数，都用空格隔开。
两个坐标分别是最大长方形左上角和右下角的坐标，从1开始计数。
如果有多个相同和的最大长方形，输出左上角坐标行数最小的长方形坐标
（同一行有相同和的，输出左上角坐标列数最小的）。整数是最大的和。
【样例输入】
5 4
-1 -2 -3 -4
-3 -2 2 4
-3 -4 3 5
4 -5 3 6
-3 -2 -1 0
【样例输出】
(2, 3) (4, 4) 23
************************/

#include <stdio.h>
#define N 101

// use index from 1
// sum[i][j] = input[1][1] + ... + input[i][j], sum of sub-matrix elements
// input[0][j], input[i][0], sum[0][j], sum[i][0] are 0
int input[N][N], sum[N][N];

int main() {
    int m, n, i, j;
    // input and compute sum
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            scanf("%d", &input[i][j]);
            sum[i][j] = sum[i][j-1] + sum[i-1][j] - sum[i-1][j-1] + input[i][j];
        }
    }

    // find the max sub-matrix
    int max = input[1][1], leftx, lefty, rightx, righty;
    leftx = lefty = rightx = righty = 1;
    int x1, y1, x2, y2, temp;
    for (x1 = 1; x1 <= n; x1++) {
        for (y1 = 1; y1 <= m; y1++) {
            for (x2 = x1; x2 <= n; x2++) {
                for (y2 = y1; y2 <= m; y2++) {
                    temp = sum[x2][y2] - sum[x2][y1-1] - sum[x1-1][y2] + sum[x1-1][y1-1];
                    if (temp > max) {
                        max = temp;
                        leftx = x1; lefty = y1;
                        rightx = x2; righty = y2;
                    }
                }
            }
        }
    }

    printf("(%d, %d) (%d, %d) %d", leftx, lefty, rightx, righty, max);
    return 0;
}