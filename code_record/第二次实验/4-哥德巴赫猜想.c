/****************************
【问题描述】哥德巴赫猜想：一个不小于6的偶数可以表示为两个素数之和。
要求验证a~b之间的全部偶数，6 <= a < b <= 2000。
【输入形式】a b两个数字
【输出形式】按行输出，每行如6 = 3 + 3，前一个素数尽可能小。
【样例输入】
6 10
【样例输出】
6 = 3 + 3
8 = 3 + 5  
10 = 3 + 7
****************************/

#include <stdio.h>

int n[2000];

int main(){
    int i, j;
    // store all primes in array n
    // see more details in courseware ch4 p11-12
    for (i = 2; i < 2000; i++){
        while (n[i] == -1){
            i++;
        }
        for (j = i + i; j < 2000; j += i){
            n[j] = -1;
        }
    }

    int a, b;
    scanf("%d%d", &a, &b);
    // for all even number i in [a, b], 
    // find a prime j s.t. i-j is a prime
    for (i = a; i <= b; i += 2){
        for (j = 3; j < 2000; j += 2){
            if (n[j] != -1 && n[i-j] != -1){
                printf("%d = %d + %d\n", i, j, i-j);
                break;
            }
        }
    }
    return 0;
}