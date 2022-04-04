#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node
{             //建立链表
    double a; //系数
    int b;    //指数
    struct Node *next;
} POLY;
char poly1[200] = {0}, poly2[200] = {0};
int x1[200] = {0}, sign1[200] = {0}; //记录x和正负号的位置，方便提取系数和指数
int x2[200] = {0}, sign2[200] = {0};
int j = 1, k = 1;
POLY *head, *tail;
void change(char a[], int x[], int sign[]); //化为标准形式(即把正负号和1补全)并记录x和+-号位置
int main()
{
    scanf("%s", poly1);
    scanf("%s", poly2);
    change(poly1, x1, sign1);
    head = tail = NULL;
    POLY *p; //建立第一个节点
    p = (POLY *)malloc(sizeof(POLY));
    p->a = atof(poly1 + sign1[1]);
    p->b = atof(poly1 + x1[1] + 2);
    p->next = NULL;
    head = tail = p;
    for (int i = 2; i <= k - 1; i++)
    { //尾插法
        POLY *p;
        p = (POLY *)malloc(sizeof(POLY));
        p->a = atof(poly1 + sign1[i]);
        p->b = atof(poly1 + x1[i] + 2);
        p->next = NULL;
        tail->next = p;
        tail = p;
    }
    j = 1;
    k = 1;
    change(poly2, x2, sign2);
    double A;
    int B;
    for (int i = 1; i <= k - 1; i++) //对于第二个，不再建链表，而是直接加在第一个链表上
    {
        A = atof(poly2 + sign2[i]); //提取系数与指数的方法同上
        B = atof(poly2 + x2[i] + 2);
        POLY *p;
        p = head;
        while (p != NULL)
        {
            if (head->b < B) //头部插入
            {
                POLY *q;
                q = (POLY *)malloc(sizeof(POLY));
                q->a = A;
                q->b = B;
                q->next = head;
                head = q;
                break;
            }
            if (p->b == B) //合并同类项
            {
                p->a += A;
                break;
            }
            if (p->next != NULL && (p->next->b) < B && (p->b) > B) //中间插入
            {
                POLY *q;
                q = (POLY *)malloc(sizeof(POLY));
                q->b = B;
                q->a = A;
                q->next = p->next;
                p->next = q;
                break;
            }
            p = p->next;
        }
        if (p == NULL) //尾部插入
        {
            POLY *q;
            q = (POLY *)malloc(sizeof(POLY));
            q->a = A;
            q->b = B;
            q->next = NULL;
            tail->next = q;
            tail = q;
            break;
        }
    }
    POLY *P; //输出
    P = head;
    int flag = 0;
    while (P != NULL)
    {
        if (P != head && P->a > 0)
        {
            printf("+");
            flag++;
        }
        if (P->a == 0)
        {
            P = P->next;
            continue;
        }
        if (P->b == 0 || (P->a != 1 && P->a != -1))
        {
            printf("%.3lf", P->a);
            flag++;
        }
        if (P->a == -1) //1的缺省
        {
            printf("-");
            flag++;
        }
        if (P->b != 0)
        {
            printf("x");
            flag++;
            if (P->b != 1)
            {
                printf("^%d", P->b);
                flag++;
            }
        }
        P = P->next;
    }
    if (flag == 0) //没有输出时输出0.000
        printf("0.000");
    POLY *Q;
    while (head != NULL)
    {
        Q = head;
        head = head->next;
        free(Q);
    }
    system("pause");
    return 0;
}
void change(char a[], int x[], int sign[]) //将原始数据处理为标准形式
{
    int count = 0; //计数，便于进行某些只进行一次的操作，和没有x的特殊情况
    for (int i = 0; i < strlen(a); i++)
    {
        if (a[i] == 'x')
        {
            count++;
            if (i == 0)
            {
                for (int j = strlen(a) - 1; j >= 0; j--)
                {
                    a[j + 2] = a[j];
                }
                a[0] = '+';
                a[1] = '1';
                if (a[i + 1] == '+' || a[i + 1] == '-')
                {
                    for (int j = strlen(a) - 1; j >= i + 1; j--)
                    {
                        a[j + 2] = a[j];
                    }
                    a[i + 1] = '^';
                    a[i + 2] = '1';
                }
                continue;
            }
            if (count == 1) //只对第一个x
            {
                int m;
                for (m = i - 1; m >= 0; m--)
                {
                    if (a[m] == '+' || a[m] == '-')
                        break;
                }
                if (m < 0)
                {
                    for (int j = strlen(a) - 1; j >= 0; j--)
                    {
                        a[j + 1] = a[j];
                    }
                    a[0] = '+';
                    if (a[i + 1] == '+' || a[i + 1] == '-')
                    {
                        for (int j = strlen(a) - 1; j >= i + 1; j--)
                        {
                            a[j + 2] = a[j];
                        }
                        a[i + 1] = '^';
                        a[i + 2] = '1';
                    }
                    continue;
                }
            }
            if (i == strlen(a) - 1)
            {
                a[i + 1] = '^';
                a[i + 2] = '1';
                if (a[i - 1] == '+' || a[i - 1] == '-')
                {
                    for (int j = strlen(a) - 1; j >= i; j--)
                    {
                        a[j + 1] = a[j];
                    }
                    a[i] = '1';
                }
                break;
            }
            if (a[i - 1] == '+' || a[i - 1] == '-')
            {
                for (int j = strlen(a) - 1; j >= i; j--)
                {
                    a[j + 1] = a[j];
                }
                a[i] = '1';
            }
            if (a[i + 1] == '+' || a[i + 1] == '-')
            {
                for (int j = strlen(a) - 1; j >= i + 1; j--)
                {
                    a[j + 2] = a[j];
                }
                a[i + 1] = '^';
                a[i + 2] = '1';
            }
        }
    }
    if (count == 0) //没有x的特殊情况
    {
        if (a[0] != '-')
        {
            for (int n = strlen(a) - 1; n >= 0; n--)
                a[n + 1] = a[n];
            a[0] = '+';
        }
        int o = strlen(a); //补全x^0;
        a[o] = 'x';
        a[o + 1] = '^';
        a[o + 2] = '0';
    }
    for (int i = strlen(a) - 1;; i--)
    {
        if (a[i] == 'x')
            break;
        if (a[i] == '+' || a[i] == '-')
        {
            int mem = strlen(a);
            a[mem] = 'x';
            a[mem + 1] = '^';
            a[mem + 2] = '0';
            break;
        }
    }
    for (int i = 0; i < strlen(a); i++) //记录x和+-号位置
    {
        if (a[i] == 'x')
        {
            x[j] = i;
            j++;
        }
        if (a[i] == '+' || a[i] == '-')
        {
            sign[k] = i;
            k++;
        }
    }
}