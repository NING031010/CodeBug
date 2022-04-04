#include <stdio.h>
#include <string.h>
int main()
{
    char string1[1024], string2[1024];                         //string3存储并表示输出结果
    scanf("%s %s", string1, string2);                          //输入两个字符串，并用空格隔开
    long int i = strlen(string1) - 1, j = strlen(string2) - 1; //i,j初始化为最后一个字符的位置，i表示从该位置开始一轮检查
    long int m = strlen(string1) - 1;                          //m用来存储string1中受到检查的字符的位置，初始化为string1的最后一个字符的位置

    if (strlen(string1) >= strlen(string2))
    { //当string1比string2长的时候（排除i为负数的情况）
        while (i >= 0 && j >= 0)
        {
            if (m >= 0 && j >= 0)
            {
                if (string1[m] == string2[j])
                { //若匹配，则都向前移动一个位置
                    m--;
                    j--;
                }
                else
                { /*否则，第二个字符串从头开始，第一个字符串移到上一次开始比较时的前一个位置，重新比较*/
                    i--;
                    m = i; //m表示从新的位置开始依次检验
                    j = strlen(string2) - 1;
                }
            }
        }
        if (j < 0) //即匹配成功
        {
            for (long int n = 0; n <= strlen(string1); n++)
            {
                if (n == i - (strlen(string2)) + 1) //当输出到string1中和string2相匹配的位置时
                    n = i + 1;                      //跳过该段
                putchar(string1[n]);
            }
            putchar('\n');
        }
    }
    else               //如果string1比string2短
        puts(string1); //打印string1
    return 0;
}

