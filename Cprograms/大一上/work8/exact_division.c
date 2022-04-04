#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    //输入
    int a, b; //a是被除数，b是除数
    scanf("%d %d", &a, &b);
    int *remain, *result, *m;   //remain[i]和result[i]分别为第i次除法的余数和商
    int joint1 = 0, joint2 = 0; //joint为循环节点
    remain = (int *)calloc(100000, sizeof(int));
    result = (int *)calloc(100000, sizeof(int));
    m = (int *)calloc(10000, sizeof(int)); //m记录已经出现的余数

    //处理
    for (int i = 0;; i++)
    {
        result[i] = a / b;
        remain[i] = a % b;
        a = remain[i] * 10; //模拟手工除法，余数乘以10变成新的被除数
        if (remain[i] == 0)
        { //余数为0，结束循环，输出结果
            printf("0.");
            for (int j = 1; j < sizeof(result) / sizeof(int); j++)
            {
                printf("%d", result[j]);
            }
            break;
        }
        else if (m[remain[i]] != 0)
        { //余数和之前的某个相等
            for (int k = 0; k < i; k++)
            {
                if (remain[k] == remain[i])
                { //寻找循环节点
                    joint1 = k + 1;
                    joint2 = i + 1;
                }
            }
            printf("0."); //输出
            for (int x = 1; x < joint2; x++)
                printf("%d", result[x]);
            printf("(");
            for (int y = joint1; y < joint2; y++)
                printf("%d", result[y]);
            printf(")");
            break;
        }
        m[remain[i]] = 1;
    }
    free(result);
    free(remain);
    free(m);
    system("pause");
    return 0;
}
