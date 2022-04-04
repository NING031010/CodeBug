#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node
{ //结构体，链表，存储图书信息
    char name[100];
    char info[1000];
    struct Node *next;
} List;

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

int main()
{
    List *lookup(List * head, char info[]);

    List *head; //链表初始化
    head = NULL;

    char direct[100][10]; //存放指令
    char Name[100][100];  //存放要操作的书名
    char Info[100][1000]; //存放要操作的书籍信息

    for (int i = 0;; i++)
    { //接受指令
        scanf("%s", &direct[i]);
        if (strcmp(direct[i], "QUIT") == 0)
        {
            break;
        }
        scanf("%s", &Name[i]);
        getchar();
        if (strcmp(direct[i], "DELETE") == 0 || strcmp(direct[i], "QUERY") == 0)
        {
            continue;
        }
        gets(Info[i]);
    }

    for (int i = 0;; i++)
    { //执行指令
        if (strcmp(direct[i], "QUIT") == 0)
        {
            break;
        }
        //插入
        if (strcmp(direct[i], "INSERT") == 0)
        {
            if (lookup(head, Name[i]) != NULL) //如果已存在，报错
                printf("Insert Error: This book already exists.\n");
            else
            {
                List *p; //不存在就插入新节点
                p = (List *)malloc(sizeof(List));
                strcpy(p->name, Name[i]);
                strcpy(p->info, Info[i]);
                p->next = head;
                head = p;
                printf("Insert: Success!\n");
            }
        }

        //删除
        else if (strcmp(direct[i], "DELETE") == 0)
        {
            if (lookup(head, Name[i]) == NULL)
                printf("Delete Error: This book does not exist.\n");
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
                printf("Delete: Success!\n");
            }
        }

        //查找
        else if (strcmp(direct[i], "QUERY") == 0)
        {
            if (lookup(head, Name[i]) == NULL)
            {
                printf("Query Error: This book does not exist.\n");
            }
            else
            {
                puts(lookup(head, Name[i])->info);
            }
        }
    }
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
