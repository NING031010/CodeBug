#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#pragma GCC optimize(3)
#define MAX 60000000 // n的最大规模

int n;                     //皇后个数
int board[MAX];            //模拟棋盘
int right_diag[2 * MAX - 1]; // 主对角线上的皇后个数
int left_diag[2 * MAX - 1]; // 反对角线上的皇后个数
FILE *fp;
#define swap(a, b) \
    {              \
        int t = a; \
        a = b;     \
        b = t;     \
    }

int my_rand() // 生成大随机数
{
    if (n < 30000)
    {
        return rand();
    }
    else
    {
        int temp = rand();
        int temp_ = rand() % 3000;
        return temp + temp_ * 30000;
    }
}

void rand_settle() //列不冲突地随机放x个皇后
{
    int temp;
    int *mark = (int *)calloc(n, sizeof(int)); //标记数组
    memset(mark, 0, sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        do
        {
            temp = my_rand() % n;
        } while (mark[temp] == 1);
        board[i] = temp;
        mark[temp] = 1;
    }
    free(mark);
}

int get_c(int n) // 设置初始时冲突的皇后数量
{
    if (n <= 10)
        return n > 8 ? 8 : n;
    else if (n <= 100)
        return 30;
    else if (n <= 10000)
        return 50;
    else if (n <= 100000)
        return 80;
    return 100;
}

int random_start(int c)  //得到更好的初始解
{
    int m = n - c;
    for (int i = 0; i < n; i++)
        board[i] = i;
    memset(right_diag, 0, sizeof(int) * (2 * n - 1));
    memset(left_diag, 0, sizeof(int) * (2 * n - 1));
    int conflicts = 0;
    // 首先在空闲列中随机放置m个皇后,保证无冲突
    for (int i = 0; i < m; i++)
    {
        // 从[i, n)中选j,保证不影响已放置的皇后
        int j = i + my_rand() % (n - i);
        while (right_diag[i - board[j] + n - 1] > 0 || left_diag[i + board[j]] > 0)
            j = i + my_rand() % (n - i);
        swap(board[i], board[j]);
        right_diag[i - board[i] + n - 1]++;
        left_diag[i + board[i]]++;
    }
    // 剩余c个皇后在空闲列中随便放置,不管是否产生冲突
    for (int i = m; i < n; i++)
    {
        int j = i + my_rand() % (n - i);
        swap(board[i], board[j]);
        right_diag[i - board[i] + n - 1]++;
        left_diag[i + board[i]]++;
    }
    for (int i = 0; i < 2 * n - 1; i++)
    {
        conflicts += right_diag[i] > 1 ? right_diag[i] - 1 : 0;
        conflicts += left_diag[i] > 1 ? left_diag[i] - 1 : 0;
    }
    return conflicts;
}

int conflict_num() //计算冲突数
{
    int ans = 0;
    memset(right_diag, 0, sizeof(int) * (2 * n - 1));
    memset(left_diag, 0, sizeof(int) * (2 * n - 1));
    for (int i = 0; i < n; i++)
    {
        right_diag[i - board[i] + n - 1]++;
        left_diag[i + board[i]]++;
    }
    for (int i = 0; i < 2 * n - 1; i++)
    {
        ans += right_diag[i] > 1 ? right_diag[i] - 1 : 0;
        ans += left_diag[i] > 1 ? left_diag[i] - 1 : 0;
    }
    return ans;
}

int swap_change(int i, int j) // 交换第i和第j个皇后带来的冲突数变化
{
    int change = 0;
    // 原来位置对应的对角线上皇后数需要减1
    // 如果原来对应的对角线上有冲突,则change++
    if (left_diag[i + board[i]] > 1)
        change++;
    if (left_diag[j + board[j]] > 1)
        change++;
    if (right_diag[i - board[i] + n - 1] > 1)
        change++;
    if (right_diag[j - board[j] + n - 1] > 1)
        change++;
    // 同理可知新对应的对角线上有皇后,则change--
    if (left_diag[i + board[j]] > 0)
        change--;
    if (left_diag[j + board[i]] > 0)
        change--;
    if (right_diag[i - board[j] + n - 1] > 0)
        change--;
    if (right_diag[j - board[i] + n - 1] > 0)
        change--;
    return change;
}

void update_state(int i, int j) //更新冲突表
{
    left_diag[i + board[i]]--;
    left_diag[j + board[j]]--;
    right_diag[i - board[i] + n - 1]--;
    right_diag[j - board[j] + n - 1]--;

    left_diag[i + board[j]]++;
    left_diag[j + board[i]]++;
    right_diag[i - board[j] + n - 1]++;
    right_diag[j - board[i] + n - 1]++;

    swap(board[i], board[j]);
}

void part_search() //减少冲突至0
{
    while (1)
    {
        // rand_settle();
        // int num = conflict_num();
        int num = random_start(get_c(n));
        if (num == 0)
            return;
        //选择一个有冲突的与其他交换
        int change;
        for (int i = 0; i < n; i++)
        {
            if (right_diag[i - board[i] + n - 1] > 1 || left_diag[i + board[i]] > 1)
            {
                for (int j = 0; j < n; ++j)
                {
                    if (i != j)
                    {
                        change = swap_change(i, j);
                        if (change > 0)
                        {
                            update_state(i, j);
                            num = conflict_num();
                            // printf("%d\n", num);
                        }
                        if (num == 0)
                            return;
                    }
                }
            }
        }
    }
}

void print_queen()
{
    fprintf(fp, "%d\n", n);
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%d ", board[i] + 1);
    }
}

int main()
{
    fp = fopen("solutions.txt", "w");
    printf("Please enter the number of queens : ");
    scanf("%d", &n);
    clock_t start, end;
    start = clock();
    part_search();
    print_queen();
    end = clock();
    printf("\nRun time : %lf (s)\n", (double)(end - start) / CLK_TCK);
    fclose(fp);
    system("pause");
    return 0;
}
