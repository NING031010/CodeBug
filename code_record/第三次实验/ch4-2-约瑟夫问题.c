/***************************
【问题描述】古代某法官判决n名犯人死刑，他将犯人排成一个圆圈，
然后从第s个人开始从1报数，每数到第m个犯人，就把他拉出来处决，然后再从1报数。
到剩下最后一个人时，就把他赦免。编写程序，输入n、s、m，给出处决顺序，以及被赦免者编号。
【输入形式】三个整数n, s, m。其中1 <= n, s, m <= 1000。
【输出形式】处决顺序和被赦免者编号。都以空格隔开。
【样例输入】
5 1 3
【样例输出】
3 1 5 2 4 
****************************/

#include <stdio.h>
#define N 1005

// global variables are automatically initialized to 0
int prisoner[N];

int main(){
    int n, s, m, i, j, left;
    scanf("%d%d%d", &n, &s, &m);
    i = s - 1;  // start from the (s-1)-th prisoner
    left = n;
    while (left != 1){
        for (j = 1; j <= m; j++){
            i = i % n + 1;
            while (prisoner[i] == -1)   // skip those already executed
                i = i % n + 1;
        }
        printf("%d ", i);
        prisoner[i] = -1;   // execute prisoner[i]
        left--;
    }
    while (prisoner[i] == -1)
        i = i % n + 1;
    printf("%d ", i);
    return 0;
}