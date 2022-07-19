/***************************
【问题描述】输入两个字符串str1和str2，计算str2在str1中第一次出现的位置（从0开始计算）。
输出位置结果。str1和str2中都可能包含空格，两个字符串长度都不会超过500。
【输入形式】两个字符串，以'\n'隔开。
【输出形式】一个数字。
【样例输入】
how are you!
are
【样例输出】
4
****************************/

#define N 505
#include <stdio.h>
#include <string.h>

int main(){
    char str1[N], str2[N];
    gets(str1);
    gets(str2);
    int i, j, flag;
    for (i = 0; str1[i] != '\0'; i++){
        flag = 0;
        for (j = 0; str2[j] != '\0'; j++){
            if (str1[i+j] != str2[j]){
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            break;
    }
    printf("%d\n", i);
    return 0;
}