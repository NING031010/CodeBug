/*****************************
【问题描述】
输入5个数与一个结果，设计程序在5个数中填入运算符(+ - * /)使其与结果相等，或回答做不到。
5个数顺序固定，需要考虑运算符优先性。除法按整数除法来运算，保证有解的输入都是有唯一解的。
与“运算符填空”一题的区别只在于需要考虑运算符优先性。
【输入形式】5个整数a, b, c, d, e和一个结果整数result。0<a,b,c,d,e<=50。
【输出形式】依次输出4个运算符，以空格隔开；没有解时输出"No solution"。
【样例输入】
1 3 5 7 9 72
【样例输出】
+ + + *
******************************/

#include <stdio.h>

int main(){
    int a[5], res;
    int i, j;
    // input
    for (i = 0; i < 5; i++){
        scanf("%d", &a[i]);
    }
    scanf("%d", &res);

    // optr_stack: operator stack
    // optr_top: points to the first unused unit in optr_stack
    // opra_stack: operand stack
    int optr_all, tmp, optr[4], optr_stack[5], optr_top, opra_stack[5], opra_top;
    // flag = 1 means a solution has been found
    int flag = 0;
    for (optr_all = 0; optr_all < 256; optr_all++){
        // loop for 256 times to get different operators
        tmp = optr_all;
        for (i = 0; i < 4; i++){
            optr[i] = tmp % 4;
            tmp = tmp / 4;
        }

        // push the first operator into stack
        // push the first and the second operand into stack
        optr_stack[0] = optr[0];
        optr_top = 1;
        opra_stack[0] = a[0];
        opra_stack[1] = a[1];
        opra_top = 2;
        // j: points to the first un-visited operand in array a in this loop
        j = 2;

        for (i = 1; i < 4; i++){
            // i: points to the first un-visited operator in this loop
            // visited operators should be either in the stack or computed
            if (optr[i] >= 2 && optr[i-1] < 2 || optr_top == 0){
                // if optr[i] priority > optr[i-1] or the operator stack is empty
                // push 1 operator and push 1 operand
                optr_stack[optr_top++] = optr[i];
                opra_stack[opra_top++] = a[j++];
            }
            else {
                // pop 1 operator and 2 operands, push their computed result 
                opra_top--;
                if (optr_stack[optr_top-1] == 0)
                    opra_stack[opra_top-1] = opra_stack[opra_top-1] + opra_stack[opra_top];
                else if (optr_stack[optr_top-1] == 1)
                    opra_stack[opra_top-1] = opra_stack[opra_top-1] - opra_stack[opra_top];
                else if (optr_stack[optr_top-1] == 2)
                    opra_stack[opra_top-1] = opra_stack[opra_top-1] * opra_stack[opra_top];
                else if (optr_stack[optr_top-1] == 3)
                    opra_stack[opra_top-1] = opra_stack[opra_top-1] / opra_stack[opra_top];
                optr_top--;
                i--;    // the next loop still deal with this operator
            }
        }

        // pop the remains in both stack
        while (optr_top != 0){
            opra_top--;
            if (optr_stack[optr_top-1] == 0)
                opra_stack[opra_top-1] = opra_stack[opra_top-1] + opra_stack[opra_top];
            else if (optr_stack[optr_top-1] == 1)
                opra_stack[opra_top-1] = opra_stack[opra_top-1] - opra_stack[opra_top];
            else if (optr_stack[optr_top-1] == 2)
                opra_stack[opra_top-1] = opra_stack[opra_top-1] * opra_stack[opra_top];
            else if (optr_stack[optr_top-1] == 3)
                opra_stack[opra_top-1] = opra_stack[opra_top-1] / opra_stack[opra_top];
            optr_top--;
        }

        // opra_stack[0] == res: find a solution
        // print result and break
        if (opra_stack[0] == res){
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