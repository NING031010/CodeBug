#include <stdio.h>
#include <string.h>
int udf_strcmp(char *s1, char *s2)
{ //以指针为函数参数
    long int b;
    b=(strlen(s1)<strlen(s2))?strlen(s1):strlen(s2);
    for (int i = 0; i <= b; i++)
    {                             //任意一个字符串结束时
        if (s1[i] != s2[i])       //如果两个字符不相同
            return s1[i] - s2[i]; //返回s1的字符减去s2的字符的值
    }
    return 0;
}

int main()
{
    char string1[1000];
    char string2[1000];
    scanf("%s %s", string1, string2);
    int a = udf_strcmp(string1, string2);
    printf("%d\n", a);
    return 0;
}


