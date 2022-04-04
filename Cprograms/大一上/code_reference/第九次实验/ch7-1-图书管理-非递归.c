/***************************
【问题描述】现有一所图书馆，希望你实现一个按书名检索的数据系统，要求支持插入、删除、查找。
【输入形式】
输入数条指令，指令包括四种：INSERT, DELETE, QUERY, QUIT，每条指令一行。 指令格式和含义如下：
INSERT [书名] [书籍信息]：插入该书名的书籍信息。系统中不允许重名数据存在。
如果插入的书籍已存在，需要输出"Insert Error: This book already exists.\n"，
否则如果成功插入，则输出"Insert: Success!\n"。
DELETE [书名]：删除该书名的书籍信息。如果要删除的书籍不存在，
则输出"Delete Error: This book does not exist.\n"，否则输出"Delete: Success!\n"。
QUERY [书名]：检索该书名的书籍信息。如果需要查询的书籍不存在，
则输出"Query Error: This book does not exist.\n"，否则输出要查询的书籍的信息。
QUIT：退出程序。
书名只由大写字母组成。书籍信息中可能包含空格，每本书籍信息的长度不超过1000。
【输出形式】各条指令执行的反应，同上所述。每条指令对应的输出占一行。
【样例输入】
INSERT ABC some_info
QUERY ABC
DELETE ABC
QUERY ABC
QUIT
【样例输出】
Insert: Success!
some_info
Delete: Success!
Query Error: This book does not exist.
****************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct book_tree{
    char info[1000];
    struct book_tree *next[26];
} book;

book tree = {"", {NULL}};
book *head = &tree; // this pointer does not change value through the program

void query(book *head, char *name) {
    book *itr = head;   // iterator
    int i = 0;
    while (name[i] != '\0') {
        if (itr == NULL) {
            printf("Query Error: This book does not exist.\n");
            return;
        }
        itr = itr->next[name[i]-'A'];   // iterator moves to the next node
        i++;
    }
    if (itr == NULL || itr->info[0] == '\0')
        printf("Query Error: This book does not exist.\n");
    else    
        printf("%s\n", itr->info);
}

void insert(book *head, char *name, char *info) {
    book *itr = head;
    int i = 0, j = 0;
    while (name[i] != '\0' && itr->next[name[i]-'A'] != NULL) {
        itr = itr->next[name[i]-'A'];
        i++;
    }
    if (name[i] == '\0') {  // node exists
        if (itr->info[0] == '\0') {
            // info is empty
            strcpy(itr->info, info);
            printf("Insert: Success!\n");
        } else 
            printf("Insert Error: This book already exists.\n");
        return;
    }
    while (name[i] != '\0') {
        // create new node
        itr->next[name[i]-'A'] = (book*)malloc(sizeof(book));
        itr = itr->next[name[i]-'A'];
        // initialize
        itr->info[0] = '\0';
        for (j = 0; j < 26; j++) {
            itr->next[j] = NULL;
        }
        i++;
    }
    strcpy(itr->info, info);
    printf("Insert: Success!\n");
}

void delete(book *head, char *name) {
    book *itr = head;
    int i = 0;
    while (name[i] != '\0' && itr->next[name[i]-'A'] != NULL) {
        itr = itr->next[name[i]-'A'];
        i++;
    }
    if (name[i] != '\0') {
        printf("Delete Error: This book does not exist.\n");
        return;
    }
    if (itr->info[0] == '\0') {
        // info is empty
        printf("Delete Error: This book does not exist.\n");
        return;
    }
    itr->info[0] = '\0';    // clear info
    printf("Delete: Success!\n");
}

int main(){
    char name[100], info[1000], inst[10];
    while (1) {
        scanf("%s", inst);
        if (inst[2] == 'I') // QUIT
            break;
        switch (inst[0]) {
            case 'Q':   // QUERY
                scanf("%s", name);
                query(head, name);
                break;
            case 'I':   // INSERT
                scanf("%s", name);
                getchar();  // skip ' '
                gets(info);
                insert(head, name, info);
                break;
            case 'D':   // DELETE
                scanf("%s", name);
                delete(head, name);
                break;
            default:
                printf("Wrong instruction!\n");
                break;
        }
    }
    return 0;
}
