#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 64
void oddcalcu(int n, int **a, int **b, int **c);     //传统算法
void strassen(int n, int **a, int **b, int **c);     //Strassen算法,c存放结果
void add(int n, int **a, int **b, int **c, int sign);         //用于矩阵相加,c存放结果
      
int main() {
    int q;      //矩阵大小
    FILE *fp = fopen("input.txt", "r");

    //数据读入
    fscanf(fp, "%d", &q);

    q = (1 << q);
    int **A, **B, **C;
    A = (int **)malloc(q * sizeof(int *));
    for (int i = 0; i < q; i++) {
        A[i] = (int *)malloc(q * sizeof(int));
    }
    B = (int **)malloc(q * sizeof(int *));
    for (int i = 0; i < q; i++) {
        B[i] = (int *)malloc(q * sizeof(int));
    }
    C = (int **)malloc(q * sizeof(int *));
    for (int i = 0; i < q; i++) {
        C[i] = (int *)malloc(q * sizeof(int));
    }

    for (int i = 0; i < q; i++) {
        for (int j = 0; j < q; j++) {
            fscanf(fp, "%d", &A[i][j]);
        }
    }

    for (int i = 0; i < q; i++) {
        for (int j = 0; j < q; j++) {
            fscanf(fp, "%d", &B[i][j]);
        }
    }

    clock_t start1, end1;       //用传统算法，输出结果与运行时间
    start1 = clock();
    oddcalcu(q, A, B, C);
    end1 = clock();
    FILE *Fp = fopen("output.txt", "w");
    fprintf(Fp, "answer given by tradition:\n");
    for (int i = 0; i < q; i++) {
        for (int j = 0; j < q; j++) {
            fprintf(Fp, "%5d", C[i][j]);
        }
        fprintf(Fp, "\n");
    }

    clock_t start2, end2;       //用Strassen算法，输出结果与运行时间
    start2 = clock();
    strassen(q, A, B, C);
    end2 = clock();

    fprintf(Fp, "answer given by Stassen:\n");
    for (int i = 0; i < q; i++) {
        for (int j = 0; j < q; j++) {
            fprintf(Fp, "%5d", C[i][j]);
        }
        fprintf(Fp, "\n");
    }

    free(A);
    free(B);
    free(C);

    printf("run time of tradition:\n");
    printf("%lf", (double)(end1-start1)/CLK_TCK);
    printf("\n\n\n");
    printf("run time of Strassen:\n");
    printf("%lf", (double)(end2-start2)/CLK_TCK);

    fclose(fp);
    system("pause");
    return 0;
}

void oddcalcu(int n, int **a, int **b, int **c) {        //传统算法，逐个元素计算
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = 0;
            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void add(int n, int **a, int **b, int **c, int sign) {       //计算矩阵的加减
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] + b[i][j] * sign;
        }
    }
}

void strassen(int n, int **a, int **b, int **c) {        //Strassen算法，分治，递归，减少乘法运算
    if (n <= N) {       //递归出口
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                c[i][j] = 0;
                for (int k = 0; k < n; k++) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return;
    }

    int **a11, **a12, **a21, **a22;
    a11 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        a11[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    a12 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        a12[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    a21 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        a21[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    a22 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        a22[i] = (int *)malloc((n / 2) * sizeof(int));
    }

    int **b11, **b12, **b21, **b22;
    b11 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        b11[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    b12 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        b12[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    b21 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        b21[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    b22 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        b22[i] = (int *)malloc((n / 2) * sizeof(int));
    }

    int **c11, **c12, **c21, **c22;
    c11 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        c11[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    c12 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        c12[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    c21 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        c21[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    c22 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        c22[i] = (int *)malloc((n / 2) * sizeof(int));
    }

    int **D1, **D2, **D3, **D4, **D5, **D6, **D7, **D8, **D9, **D10;
    D1 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        D1[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    D2 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        D2[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    D3 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        D3[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    D4 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        D4[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    D5 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        D5[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    D6 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        D6[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    D7 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        D7[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    D8 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        D8[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    D9 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        D9[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    D10 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        D10[i] = (int *)malloc((n / 2) * sizeof(int));
    }

    int **M1, **M2, **M3, **M4, **M5, **M6, **M7;
    M1 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        M1[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    M2 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        M2[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    M3 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        M3[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    M4 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        M4[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    M5 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        M5[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    M6 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        M6[i] = (int *)malloc((n / 2) * sizeof(int));
    }
    M7 = (int **)malloc((n / 2) * sizeof(int *));
    for (int i = 0; i < n / 2; i++) {
        M7[i] = (int *)malloc((n / 2) * sizeof(int));
    }

    int **d1, **d2, **d3, **d4;
    d1 = (int **)malloc((n / 2) * sizeof(int*));
    for (int i = 0; i < n / 2; i++) {
        d1[i] = (int *)malloc((n / 2) * sizeof(int));
    } 
    d2 = (int **)malloc((n / 2) * sizeof(int*));
    for (int i = 0; i < n / 2; i++) {
        d2[i] = (int *)malloc((n / 2) * sizeof(int));
    } 
    d3 = (int **)malloc((n / 2) * sizeof(int*));
    for (int i = 0; i < n / 2; i++) {
        d3[i] = (int *)malloc((n / 2) * sizeof(int));
    } 
    d4 = (int **)malloc((n / 2) * sizeof(int*));
    for (int i = 0; i < n / 2; i++) {
        d4[i] = (int *)malloc((n / 2) * sizeof(int));
    } 

    for (int i = 0; i < n / 2; i++) {       //矩阵分块
        for (int j = 0; j < n / 2; j++) {
            a11[i][j] = a[i][j];
            a12[i][j] = a[i][j + n / 2];
            a21[i][j] = a[i + n / 2][j];
            a22[i][j] = a[i + n / 2][j + n / 2];
 
            b11[i][j] = b[i][j];
            b12[i][j] = b[i][j + n / 2];
            b21[i][j] = b[i + n / 2][j];
            b22[i][j] = b[i + n / 2][j + n / 2];
        }
    }

    //以下是繁琐的计算，详解见算法分析
    add(n / 2, a11, a22, D1, 1);
    add(n / 2, b11, b22, D2, 1);
    strassen(n / 2, D1, D2, M1);
    free(D1);
    free(D2);

    add(n / 2, a21, a22, D3, 1);
    strassen(n / 2, D3, b11, M2);
    free(D3);

    add(n / 2, b12, b22, D4, -1);
    strassen(n / 2, a11, D4, M3);
    free(D4);

    add(n / 2, b21, b11, D5, -1);
    strassen(n / 2, a22, D5, M4);
    free(D5);

    add(n / 2, a11, a12, D6, 1);
    strassen(n / 2, D6, b22, M5);
    free(D6);

    add(n / 2, a21, a11, D7, -1);
    add(n / 2, b11, b12, D8, 1);
    strassen(n / 2, D7, D8, M6);
    free(D7);
    free(D8);

    add(n / 2, a12, a22, D9, -1);
    add(n / 2, b21, b22, D10, 1);
    strassen(n / 2, D9, D10, M7);      //注意顺序，矩阵乘法无交换律
    free(D9);
    free(D10);

    add(n / 2, M1, M4, d1, 1);
    add(n / 2, M7, M5, d2, -1);
    add(n / 2, d1, d2, c11, 1);
    free(d1);
    free(d2);

    add(n / 2, M3, M5, c12, 1);

    add(n / 2, M2, M4, c21, 1);

    add(n / 2, M1, M2, d3, -1);
    add(n / 2, M3, M6, d4, 1);
    add(n / 2, d3, d4, c22, 1);
    free(d3);
    free(d4);

    free(M1);
    free(M2);
    free(M3);
    free(M4);
    free(M5);
    free(M6);
    free(M7);

    free(a11);
    free(a12);
    free(a21);
    free(a22);
    free(b11);
    free(b12);
    free(b21);
    free(b22);
    //将子矩阵组装为结果
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n / 2; j++) {
            c[i][j] = c11[i][j];
            c[i][j + n / 2] = c12[i][j];
            c[i + n / 2][j] = c21[i][j];
            c[i + n / 2][j + n / 2] = c22[i][j];
        }
    }
    free(c11);
    free(c12);
    free(c21);
    free(c22);
}