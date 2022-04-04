#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct book_tree {
    char info[1005];
    struct book_tree *next[26];
} tree_node;

tree_node *create(char *info1) { // 创建一个节点，一般info是个空字符串
    tree_node *head = (tree_node *)malloc(sizeof(tree_node));
    int n, i;
    n = strlen(info1);
    for (i = 0; i < n; i++) {
        head->info[i] = info1[i];
    }
    head->info[n] = '\0';
    for (i = 0; i < 26; i++) {
        head->next[i] = NULL; // 所有子节点为空
    }
    return head;
}

tree_node *insert(tree_node *head, char *bookname, char *info) {
    // 需要保证 head 不是 NULL
    char cur = *bookname; // 当前的字符
    if (cur == '\0') {
        // 是书名结束符
        // 说明书本的信息应当存放于 head 节点里
        if (strlen(head->info) > 0) {
            // 已经有书了，插入失败
            printf("Insert Error: This book already exists.\n");
        }
        else {
            // 这个节点可以插入
            strcpy(head->info, info); // 插入书本信息
            printf("Insert: Success!\n");
        }
    }
    else {
        int index = cur - 'A'; // 书名没有结束
        // index 表示需要插入的节点
        if (head->next[index] == NULL) {
            // 如果这个节点没有被创建过
            head->next[index] = create("");
        }
        head->next[index] = insert(head->next[index], bookname + 1, info); // 递归
    }
    return head;
}

void query(tree_node *head, char *bookname) {
    // 和课件差不多
    if (head == NULL) {
        // 那肯定不存在了
        printf("Query Error: This book does not exist.\n");
        return ;
    }
    char c = *bookname;
    if (c == '\0') {
        if (strlen(head->info) > 0) {
            // 信息存在
            printf("%s\n", head->info);
        }
        else {
            // 如果是删除情况，这里也是有可能的
            printf("Query Error: This book does not exist.\n");
        }
        return ;
    }
    else {
        int index = c - 'A';
        query(head->next[index], bookname + 1);
        return ;
    }
}

void delete1(tree_node *head, char *bookname) {
    if (head == NULL) {
        // 没找到这本书
        printf("Delete Error: This book does not exist.\n");
        return ;
    }
    char c = *bookname;
    if (c == '\0') {
        if (strlen(head->info) == 0) {
            printf("Delete Error: This book does not exist.\n");
            return ;
        }
        else {
            head->info[0] = '\0';
            // 节点可以不删，只清空info
            printf("Delete: Success!\n");
            return ;
        }
    }
    else {
        int index = c - 'A';
        delete1(head->next[index], bookname + 1);
        return ;
    }
}

int main(){
    char name[100], info[1005], inst[10];
    int i, j;
    tree_node *head = create("");
    while (1) {
        scanf("%s", inst);
        if (inst[2] == 'I')
            break;
        switch (inst[0]) {
            case 'Q':
                scanf("%s", name);
                query(head, name);
                break;
            case 'I':
                scanf("%s", name);
                getchar();
                gets(info);
                head = insert(head, name, info);
                break;
            case 'D':
                scanf("%s", name);
                delete1(head, name);
                break;
            default:
                printf("Wrong instruction!\n");
                break;
        }
    }
    return 0;
}
