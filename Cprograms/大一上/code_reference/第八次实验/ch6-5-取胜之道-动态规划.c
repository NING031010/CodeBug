/**************************
【问题描述】Program国度的人，喜欢玩这样一个游戏，在一块板上写着一行数，共n个。
两个游戏者，轮流从最右或最左取一个数。刚开始，每个游戏者的得分均为零。
如果一个游戏者取下一个数，则将该数的值加到该游戏者的得分上，最后谁的得分最高谁就赢了游戏。
输入n个数（从左往右），假设游戏者都是非常聪明的（两位游戏者在选择之前都会完全考虑
接下来所有的可能性，不一定选择左右更大的那个数），问最后两个人的得分（假设第一个人首先取数）。
【输入形式】第一行是一个整数n<=100，第二行是n个数a1,......,an，以空格隔开。0<=ai<=30。
【输出形式】两位游戏者最后的得分，以空格隔开。
【样例输入】
6
4 7 2 9 5 2
【样例输出】
18 11
【样例说明】如果结果相同时优先选择左边，数字依次被选择的次序是：2 4 7 2 9 5
【提示】
1. 本题建议使用动态规划或递归求解。
2. 如果使用递归函数求解，可能需要存储一些运算的结果以避免重复计算。
否则，在n>=50时，程序运行时长会长得难以接受。
***************************/

// dynamic programming
#include <stdio.h>
#define N 101

// res[i][j] (i < j): when there was i-th to j-th numbers left, 
// the scores each player would gain during the remain game.
// res[0][j] or res[i][0] is not used.
// res[i][j][0]: the first player's score, res[i][j][1]: the second player's
int res[N][N][2];
// input[0] is not used
int input[N];

int main(){
    int n, i, j, t1, t2;
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &input[i]);
    }

    if (n % 2 == 0) {   // the second player take the last number
        for (i = 1; i <= n; i++){
            res[i][i][1] = input[i];
            res[i][i][0] = 0;
        }
    } else {    // the first player take the last number
        for (i = 1; i <= n; i++){
            res[i][i][0] = input[i];
            res[i][i][1] = 0;
        }
    }
    for (i = 1; i <= n-1; i++){
        for (j = 1; j <= n-i; j++){     // compute res[j][j+i]
            if ((n - i - 1) % 2 == 0){  // the first player's turn
                // t1: if the player select the j-th number
                t1 = input[j] + res[j+1][j+i][0];
                // t2: if select the (j+i)-th number
                t2 = input[j+i] + res[j][j+i-1][0];
                if (t1 >= t2) {
                    res[j][j+i][0] = t1;
                    res[j][j+i][1] = res[j+1][j+i][1];
                } else {
                    res[j][j+i][0] = t2;
                    res[j][j+i][1] = res[j][j+i-1][1];
                }
            } else {
                // select the j-th number
                t1 = input[j] + res[j+1][j+i][1];
                // select the (j+i)-th number
                t2 = input[j+i] + res[j][j+i-1][1];
                if (t1 >= t2) {
                    res[j][j+i][1] = t1;
                    res[j][j+i][0] = res[j+1][j+i][0];
                } else {
                    res[j][j+i][1] = t2;
                    res[j][j+i][0] = res[j][j+i-1][0];
                }
            }
        }
    }

    printf("%d %d\n", res[1][n][0], res[1][n][1]);
    for (i = 1; i <= n; i++){
        for (j = 1; j <= n; j++){
            printf("%d,%d\t",res[i][j][0], res[i][j][1]);
        }
        printf("\n");
    }
    return 0;
}