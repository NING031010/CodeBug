#include <stdio.h>
#include <stdlib.h>
int count = 0;
// 将 n 个盘子从 a 柱移动到b柱，用c柱做中转
void Hanoi(FILE *fp, int n, char a, char b, char c)
{
    // 递归的结束条件：只有1个盘子，直接从a柱移到b柱
    if (n == 1)
    {
        fprintf(fp, "%c->%c\n", a, b);
        count++;
        return;
    }
    // ① 先将n-1个盘子，以b为中转，从a柱移动到c柱，
    Hanoi(fp, n - 1, a, c, b);
    // ② 将一个盘子从a移动到b
    fprintf(fp, "%c->%c\n", a, b);
    count++;
    // ③ 将c柱上的n-1个盘子，以a为中转，移动到b柱
    Hanoi(fp, n - 1, c, b, a);
}
int main()
{
    FILE *fp = fopen("outcome.txt", "w");
    int N;
    scanf("%d", &N);
    Hanoi(fp, N, 'A', 'B', 'C');
    printf("%d", count);
    system("pause");
    return 0;
}
