/*************************
【问题描述】
输入5个数与一个结果，设计程序在5个数中填入运算符(+ - * /)使其与结果相等，或回答做不到。
5个数顺序固定，运算顺序固定为从左向右，不考虑运算符优先性。
除法按整数除法来运算，保证有解的输入都是有唯一解的。
【输入形式】5个整数a, b, c, d, e和一个结果整数result。0<a,b,c,d,e<=50。
【输出形式】依次输出4个运算符，以空格隔开；没有解时输出"No solution"。
【样例输入1】
1 1 1 1 1 5
【样例输出1】
+ + + +
【样例输入2】
2 3 4 5 6 -100
【样例输出2】
No solution
**************************/

#include <stdio.h>

int main(){
    int a[5], b, res;
    int i, j;
    // input
    for (i = 0; i < 5; i++){
        scanf("%d", &a[i]);
    }
    scanf("%d", &res);

    int optr_all, tmp, optr[4];
    // flag = 1 means a solution has been found
    int flag = 0;
    for (optr_all = 0; optr_all < 256; optr_all++){
        // loop for 256 times to get different operators
        tmp = optr_all;
        for (i = 0; i < 4; i++){
            optr[i] = tmp % 4;
            tmp = tmp / 4;
        }

        // b stores the computed result under operators in array a
        // the result of the first operator:
        switch (optr[0]){
            case 0:
                b = a[0] + a[1];
                break;
            case 1:
                b = a[0] - a[1];
                break;
            case 2:
                b = a[0] * a[1];
                break;
            case 3:
                b = a[0] / a[1];
                break;
        }
        // compute with the next 3 operators:
        for (i = 1; i < 4; i++){
            switch (optr[i]){
            case 0:
                b = b + a[i+1];
                break;
            case 1:
                b = b - a[i+1];
                break;
            case 2:
                b = b * a[i+1];
                break;
            case 3:
                b = b / a[i+1];
                break;
            }
        }
        
        // b == res: find a solution
        // print the solution and break from the loop
        if (b == res){
            flag = 1;
            for (i = 0; i < 4; i++){
                switch (optr[i]){
                case 0:
                    printf("+ ");
                    break;
                case 1:
                    printf("- ");
                    break;
                case 2:
                    printf("* ");
                    break;
                case 3:
                    printf("/ ");
                    break;
                }
            }
        }
    }
    if (flag == 0)
        printf("No solution");
    return 0;
}
