/*****************************
字符串排序
【问题描述】用指向指针的指针的方法，对输入的n个字符串进行排序并输出。要求排序单独写成一个
函数，n个字符串在主函数输入和输出。字符串排序按照ASCII码的字典序，可以使用strcmp函数。
【输入形式】一个整数n表示总共需要排序的字符串的个数，之后每行一个字符串。
每个字符串内不含空格，字符串长度不超过1000，n <= 200。
注：main函数内数组开太大可能导致程序不能运行，全局变量中的数组能开得更大。
【输出形式】排序完毕的字符串，每个字符串一行
【样例输入】
3
bbb
aaa
ccc
【样例输出】
aaa
bbb
ccc
******************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STR_NUM 500
#define STR_LEN 1005

char input[STR_NUM][STR_LEN];
char *p_input[STR_NUM];

// p_input: a pointer array
// n: number of strings to be sorted
void sort_string(char **p_input, int n){
    int i, j;
    char *temp;
    for (i = 0; i < n - 1; i++){
        for (j = 0; j < n - i - 1; j++){
            if (strcmp(p_input[j], p_input[j+1]) > 0){
                temp = p_input[j];
                p_input[j] = p_input[j+1];
                p_input[j+1] = temp;
            }
        }
    }
}

int main(){
    int n, i;
    scanf("%d", &n);
    for (i = 0; i < n; i++){
        scanf("%s", input[i]);
        p_input[i] = input[i];
        // or just use one array:
        // p_input[i] = (char *)malloc(sizeof(char)*STR_LEN);
        // scanf("%s", p_input[i]);
    }
    sort_string(p_input, n);
    for (i = 0; i < n; i++){
        printf("%s\n", p_input[i]);
    }
    return 0;
}
