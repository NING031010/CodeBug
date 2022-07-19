#include <stdio.h>

int main() {
    int n;
    // n = 9;
    scanf("%d", &n);
    int space = n - 1;
    int i, j;
    for (i = 1; i <= n; i++) { // 上半部分输出
        for (j = 0; j < space; j++) {
            printf(" ");
        }
        for (j = 0; j < i - 1; j++) {
            printf("%d ", i);
        }
        printf("%d\n", i);
        space--;
    }
    // 此时space = -1
    space = 0;
    for (i = n - 1; i >= 1; i--) {
        space++;
        for (j = 0; j < space; j++) {
            printf(" ");
        }
        for (j = 0; j < i - 1; j++) {
            printf("%d ", i);
        }
        printf("%d\n", i);
    }
    return 0;
}


