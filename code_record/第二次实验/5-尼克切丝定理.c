/**************************
【问题描述】尼克切丝定理： 任何一个整数n的立方都可以表示成一串连续的奇数之和。 设计程序验证尼克切丝定理。
【输入形式】一个整数n，2<=n<=30
【输出形式】一个奇数a和一个整数k，使 a+(a+2)+...+(a+2k-2) = n*n*n 。要求k >= 2，并且k尽可能小。
【样例输入】
3
【样例输出】
7 3
【样例说明】7 + 9 + 11 = 27
**************************/

#include <stdio.h>

int main(){
    int n, k, temp, mod;
    scanf("%d", &n);
    int n_cube = n * n * n;
    // find k s.t. n_cube = k*a1 + k*(k-1)
    // let mod = k * a1, a1 is an odd number
    for (k = 2; ; k++){
        temp = k * (k - 1);
        mod = n_cube - temp;
        if (mod % k == 0 && (mod / k) % 2 == 1){
            break;
        }
    }
    printf("%d %d", mod / k, k);
    return 0;
}

