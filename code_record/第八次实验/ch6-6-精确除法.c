#include <stdio.h>
#define N 32767

int main() {
    int a, b, remain[N], result[N];
    scanf("%d%d", &a, &b);
    int i, j, repeat_start, is_repeat = 0, last_digit;
    // add the first digit
    result[0] = 0;
    remain[0] = a;
    for (i = 1; ; i++) {
        result[i] = (a*10) / b;
        remain[i] = (a*10) % b;
        a = remain[i];
        if (remain[i] == 0)
            break;
        for (j = 0; j < i; j++) {
            // find the repeating part
            if (remain[i] == remain[j]) {
                // the repeating part of the result starts from the next digit
                repeat_start = j + 1;
                is_repeat = 1;
                break;
            }
        }
        if (is_repeat == 1)
            break;
    }
    last_digit = i; // store the index of the last digit

    printf("0.");
    for (i = 1; i <= last_digit; i++) {
        printf("%d", result[i]);
    }
    if (is_repeat == 1) {
        // output the repeating part
        printf("(");
        for (i = repeat_start; i <= last_digit; i++) {
            printf("%d", result[i]);
        }
        printf(")");
    }
}