/***************************
【问题描述】
编写程序，输入一个数字字符串s，将它转换为科学计数法输出。
* 数字串s仅包含数字和小数点（不会输入负数），小数点位于最后时，小数点可有可无；
小数点前只有0时， 0可有可无。字符串s长度<500。
* 科学计数法应保持原数字的有效精度，例如 10.0 = 1.00E+1；
科学计数法的指数部分用E表示，不缺省；E后用一位表示指数的符号位，不缺省，0的符号位记为正。
* 要求编写函数，通过字符串的操作来完成转换，不能直接使用printf的格式化输出。
【输入形式】数字字符串
【输出形式】该数字对应的科学记数法表示
【样例输入1】
100.324
【样例输出1】
1.00324E+2
【样例输入2】
.00027
【样例输出2】
2.7E-4
****************************/

#include <stdio.h>

int main(){
    char a[502];
    scanf("%s", a);
    
    int dot = 0;
    // find the index of '.'
    while (a[dot] != '.' && a[dot] != '\0')
        dot++;
    
    int exponent, index;
    // output has no dot
    if (dot == 0 && a[2] == '\0') {
        // such as .2
        printf("%cE-1", a[1]);
    } else if (dot == 1 && a[dot] == '\0') {
        // such as 2
        printf("%cE+0", a[0]);
    } else if (dot == 1 && a[0] == '0' && a[3] == '\0') {
        // such as 0.2
        printf("%cE-1", a[2]);
    } // output has dots
    else if (dot == 0) {
        // such as .045 or .00
        exponent = -1;
        index = 1;
        while (a[index] == '0' && a[index] != '\0'){
            index++;
            exponent--;
        }
        if (a[index] == '\0')
            printf("0%sE+0", a);
        else
            printf("%c.%sE%d", a[index], a+index+1, exponent);
    } else if (dot == 1 && a[0] == '0' && a[dot] != '\0') {
        // such as 0.092 or 0.000
        exponent = -1;
        index = 2;
        while (a[index] == '0' && a[index] != '\0'){
            index++;
            exponent--;
        }
        if (a[index] == '\0')
            printf("%sE+0", a);
        else
            printf("%c.%sE%d", a[index], a+index+1, exponent);
    } else if (a[dot] == '\0') {
        // such as 190
        exponent = dot - 1;
        printf("%c.%sE+%d", a[0], a+1, exponent);
    } else {
        // such as 87.65
        exponent = dot - 1;
        int i;
        for (i = dot; a[i+1] != '\0'; i++) {
            a[i] = a[i+1];
        }
        a[i] = '\0';
        printf("%c.%sE+%d", a[0], a+1, exponent);
    }
    return 0;
}