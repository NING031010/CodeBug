#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node
{ //结构体，链表，存储图书信息
    char name[100];
    char info[1000];
    struct Node *next;
} List;

int main()
{
    FILE *fp = fopen("input.txt", "r");
    FILE *Fp = fopen("output.txt", "w");
    if (fp == NULL || Fp == NULL)
    {
        printf("error: cant't open this file! \n");
        return 0;
    }

    List *lookup(List * head, char Name[]); //遍历链表
    void sort(int n, char *q[]);            //按名称排序

    List *head; //链表初始化
    head = NULL;

    char direct[100][10]; //存放指令
    char Name[100][100];  //存放要操作的书名
    char Info[100][1000]; //存放要操作的书籍信息
    int k = 0;

    for (int i = 0;; i++)
    { //接受指令
        if (fscanf(fp, "%s", &direct[i]) == EOF)
        {
            break;
        }
        k++;
        fscanf(fp, "%s", &Name[i]);
        char temp;
        fscanf(fp, "%c", &temp);
        if (strcmp(direct[i], "DELETE") == 0 || strcmp(direct[i], "QUERY") == 0)
        {
            continue;
        }
        fgets(Info[i], 1000, fp);
    }

    for (int i = 0; i < k; i++)
    { //执行指令
        //插入
        if (strcmp(direct[i], "INSERT") == 0)
        {
            if (lookup(head, Name[i]) != NULL) //如果已存在，报错
                fprintf(Fp, "Insert Error: This book already exists.\n");
            else
            {
                List *p; //不存在就插入新节点
                p = (List *)malloc(sizeof(List));
                strcpy(p->name, Name[i]);
                strcpy(p->info, Info[i]);
                p->next = head;
                head = p;
                fprintf(Fp, "Insert: Success!\n");
            }
        }

        //删除
        else if (strcmp(direct[i], "DELETE") == 0)
        {
            if (lookup(head, Name[i]) == NULL)
                fprintf(Fp, "Delete Error: This book does not exist.\n");
            else
            { //由于删除操作需要目标节点的上一个节点，lookup函数无法实现
                List *p, *q;
                p = head;
                if (strcmp(head->name, Name[i]) == 0)
                {
                    head = head->next;
                    free(head);
                }
                else
                {
                    p = head->next;
                    q = head;
                    while (strcmp(p->name, Name[i]) != 0)
                    {
                        q = p;
                        p = p->next;
                    }
                    q->next = p->next;
                    free(p);
                }
                fprintf(Fp, "Delete: Success!\n");
            }
        }

        //查找
        else if (strcmp(direct[i], "QUERY") == 0)
        {
            if (lookup(head, Name[i]) == NULL)
            {
                fprintf(Fp, "Query Error: This book does not exist.\n");
            }
            else
            {
                fputs(lookup(head, Name[i])->info, Fp);
            }
        }
    }

    fprintf(Fp, "\n");

    List *p; //将书籍信息存放在数组里，排序后输出
    p = head;
    int n = 0;
    memset(Name, 0, sizeof(Name));
    memset(Info, 0, sizeof(Info));
    while (p != NULL)
    {
        strcpy(Name[n], p->name);
        p = p->next;
        n++;
    }

    char *q[n]; //指针数组，指向不同字符串
    for (int i = 0; i < n; i++)
    {
        q[i] = Name[i];
    }

    char **P; //指向指针的指针
    P = &q[0];
    sort(n, P);
    for (int i = 0; i < n; i++)
    { //将排序后的输出
        int j = 0;
        while (*(*(P + i) + j) != '\0')
        {
            fprintf(Fp, "%c", *(*(P + i) + j));
            j++;
        }
        fprintf(Fp, "\n");
        fprintf(Fp, "%s", lookup(head, *(P + i))->info);
        fprintf(Fp, "\n\n");
    }
    fclose(fp);
    fclose(Fp);
    List *Q;
    while (head != NULL)
    {
        Q = head;
        head = head->next;
        free(Q);
    }
    system("pause");
    return 0;
}

List *lookup(List *head, char Name[])
{ //遍历链表（head是起始点，Name是要查询的书名）
    List *p;
    p = head;
    while (p != NULL && strcmp(p->name, Name) != 0)
    {
        p = p->next;
    }
    if (p == NULL)
        return (NULL);
    else
        return (p);
}

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
