#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define m 5     //控制生成的数据阶数（2^m）

int main(void) {
    srand((unsigned int) time(NULL));
    FILE *fp = fopen("input.txt", "w");

    fprintf(fp, "%d\n", m);

    for (int i = 0; i < (1 << m); i++) {
        for (int j = 0; j < (1 << m); j++) {
            fprintf(fp, "%d ", rand() % 4);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "\n");

    for (int i = 0; i < (1 << m); i++) {
        for (int j = 0; j < (1 << m); j++) {
            fprintf(fp, "%d ",rand() % 4);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    return 0;
}