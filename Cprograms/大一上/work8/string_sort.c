#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char arry[200][1000];
void sort(int n, char *q[])
{               //自定义函数，用于排序
    char *temp; //临时储存器，用于交换指针
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (strcmp(q[i], q[j]) > 0)
            {
                temp = q[i]; //交换指针
                q[i] = q[j];
                q[j] = temp;
            }
        }
    }
}
int main()
{
    memset(arry, '\0', sizeof(arry));
    int n;
    scanf("%d", &n);
    char *q[n]; //指针数组，指向不同字符串
    for (int i = 0; i < n; i++)
    {
        scanf("%s", &arry[i][0]);
        q[i] = arry[i];
    }
    char **p; //指向指针的指针
    p = &q[0];
    sort(n, p);
    for (int i = 0; i < n; i++)
    { //将排序后的输出
        int j = 0;
        while (*(*(p + i) + j) != '\0')
        {
            printf("%c", *(*(p + i) + j));
            j++;
        }
        printf("\n");
    }
    return 0;
}
