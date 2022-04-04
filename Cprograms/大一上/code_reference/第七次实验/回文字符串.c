#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main()
{
    char string[1024];
    char string1[1024], string2[1024];
    long int i, j;
    int flag = 1;
    char ch;
    gets(string);


    for (i = 0, j = 0; i < strlen(string); i++)
    {
        if (isalpha(string[i]))
        {                            //判断是否为字母
            ch = tolower(string[i]); //将所有的字母转化为小写字母，便于比较
            string1[j] = ch;         //用新数组string1存储转化后的正向字符串
            j++;
        }
    }
    for (i = strlen(string) - 1, j = 0; i >= 0; i--)
    {
        if (isalpha(string[i]))
        {
            ch = tolower(string[i]);
            string2[j] = ch; //用新数组string2存储转化后的反向字符串
            j++;
        }
    }
    for (i = 0; i < strlen(string1); i++)
    { //将两个字符串依次比较
        if (string1[i] != string2[i])
        { //只要有不相同的字符
            flag = 0;
            break; //结束比较
        }
    }
    if (flag) //正反字符全相同，回文
        printf("1\n");
    else //非回文
        printf("0\n");

    return 0;
}

