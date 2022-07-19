/*************************
【问题描述】本题是第九次实验“图书检索系统”的文件输入输出版本。
现有一所图书馆，希望你实现一个按书名检索的数据系统，要求支持插入、删除、查找。
要求书籍数据从文件读入，并且建立的数据库保存到文件中。
【输入形式】
输入文件名为"input.txt"，内容是数条指令。
指令包括三种：INSERT, DELETE, QUERY，每条指令一行。 指令格式和含义如下：
INSERT [书名] [书籍信息]：插入该书名的书籍信息。系统中不允许重名数据存在。
如果插入的书籍已存在，需要输出"Insert Error: This book already exists.\n"，
否则如果成功插入，则输出"Insert: Success!\n"。
DELETE [书名]：删除该书名的书籍信息。如果要删除的书籍不存在，
则输出"Delete Error: This book does not exist.\n"，否则输出"Delete: Success!\n"。
QUERY [书名]：检索该书名的书籍信息。如果需要查询的书籍不存在，
则输出"Query Error: This book does not exist.\n"，否则输出要查询的书籍的信息。
书名只由大写字母组成。书籍信息中可能包含空格，每本书籍信息的长度不超过1000。
【输出形式】
输出文件名是"output.txt"，包含以下两部分内容，两部分内容之间有一空行。
1. 各条指令执行的反应。每条指令对应的输出占一行。
2. 所有指令执行完毕后，存储的所有图书信息。按书名排序，每本书输出时书名占一行，
   书籍信息占一行，不同书之间有一空行。
【样例输入】
INSERT ABC some info
QUERY ABC
INSERT BCD other info
QUIT
【样例输出】
Insert: Success!
some_info
Insert: Success!

ABC
some info

BCD
other info
【提示】
使用递归方式遍历存储的书籍，进行输出，可以自然实现按书名顺序输出。
以下是一份供参考的伪代码：
void print_books(book *node) {
    if (node == NULL) return;
    if (node->info不为空) {
        print(书名);    // 如何传递或得到书名需要另外考虑
        print(node->info);
    }
    for (int i = 0; i < 26; i++) {
        print_books(node->next[i]);
    }
}
**************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct book_tree{
    char info[1000];
    struct book_tree *next[26];
} book;

book tree = {"", {NULL}};   //虚拟首节点
book *head = &tree;

void query(book *head, char *name, FILE *f_out) {
    book *itr = head; 
    int i = 0;
    while (name[i] != '\0') {
        if (itr == NULL) {
            fprintf(f_out, "Query Error: This book does not exist.\n");
            return;
        }
        itr = itr->next[name[i]-'A'];
        i++;
    }
    if (itr == NULL || itr->info[0] == '\0')
        fprintf(f_out, "Query Error: This book does not exist.\n");
    else
        fprintf(f_out, "%s", itr->info);
}

void insert(book *head, char *name, char *info, FILE *f_out) {
    book *itr = head;
    int i = 0, j = 0;
    while (name[i] != '\0' && itr->next[name[i]-'A'] != NULL) {
        itr = itr->next[name[i]-'A'];
        i++;
    }
    if (name[i] == '\0') {
        if (itr->info[0] == '\0') {
            strcpy(itr->info, info);
            fprintf(f_out, "Insert: Success!\n");
        }
        else fprintf(f_out, "Insert Error: This book already exists.\n");
        return;
    }
    while (name[i] != '\0') {
        itr->next[name[i]-'A'] = (book*)malloc(sizeof(book));
        itr = itr->next[name[i]-'A'];
        itr->info[0] = '\0';
        for (j = 0; j < 26; j++) {
            itr->next[j] = NULL;
        }
        i++;
    }
    strcpy(itr->info, info);
    fprintf(f_out, "Insert: Success!\n");
}

void delete(book *head, char *name, FILE *f_out) {
    book *itr = head;
    int i = 0;
    while (name[i] != '\0' && itr->next[name[i]-'A'] != NULL) {
        itr = itr->next[name[i]-'A'];
        i++;
    }
    if (name[i] != '\0') {
        fprintf(f_out, "Delete Error: This book does not exist.\n");
        return;
    }
    if (itr->info[0] == '\0') {
        fprintf(f_out, "Delete Error: This book does not exist.\n");
        return;
    }
    itr->info[0] = '\0';
    fprintf(f_out, "Delete: Success!\n");
}

void print_info(book *node, FILE *f_out, char *name) {
    if (node == NULL) return;
    if (node->info[0] != '\0') {
        fprintf(f_out, "%s\n%s\n\n", name, node->info);
    }
    int i, len = strlen(name);
    char next_name[100];
    strcpy(next_name, name);
    next_name[len+1] = '\0';
    for (i = 0; i < 26; i++) {
        next_name[len] = 'A' + i;
        print_info(node->next[i], f_out, next_name);
    }
}

int main(){
    char name[100], info[1000], inst[10];
    FILE *f_in = fopen("input.txt", "r");
    FILE *f_out = fopen("output.txt", "w");
    while (1) {
        if (EOF == fscanf(f_in, "%s", inst))
            break;
        switch (inst[0]) {
            case 'Q':
                fscanf(f_in, "%s", name);
                query(head, name, f_out);
                break;
            case 'I':
                fscanf(f_in, "%s", name);
                fgetc(f_in);
                fgets(info, 1003, f_in);
                int len = strlen(info);
                if (info[len-1] == '\n')
                    info[len-1] = '\0';
                insert(head, name, info, f_out);
                break;
            case 'D':
                fscanf(f_in, "%s", name);
                delete(head, name, f_out);
                break;
            default:
                fprintf(f_out, "Wrong instruction!\n");
                break;
        }
    }
    fprintf(f_out, "\n");
    print_info(head, f_out, "");
    fclose(f_in);
    fclose(f_out);
    return 0;
}
