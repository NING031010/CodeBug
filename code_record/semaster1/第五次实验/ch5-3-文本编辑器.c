/*************************
【问题描述】
编写程序，输入一段文本，暂存在内存中，按照下列规则处理后输出：
1 如果读入的字符是空格、数字、逗号、句号、换行或英文字母，则暂存在内存中；
2 如果输入一个字符 '@'，则表示删除在 '@' 之前输入的一个字符，
  如果有连续两个'@'，则删除之前的两个字符，依次类推；
3 如果输入一个字符 '$'，则表示删除当前输入的一行字符（当前行中在'$'之后输入的字符不用删除）；
4 如果输入一个字符 '^'，则表示需要把在 '^' 之前输入的一个英文单词首字母转换成大写字母
  （如果之前输入的一个单词的首字母本来就是大写，则不用做处理）；
5 如果输入一个字符 '#'，则表示输入结束，将内存的内容输出。
6 如果输入除上述字符之外的其他字符，则直接忽略。
【输入形式】
字符串，长度不超过1000。
【输出形式】
处理后的字符串。
【样例输入】
hello^ worldd@![]
not important$ whatever#
【样例输出】
Hello world
whatever
【样例说明】
"[]"和"!"被忽略。
**************************/

#include <stdio.h>
#include <string.h>
#define N 1005

char memory[N];

int main(){
    char c;
    int i = 0;  // i points to the first unused unit in memory
    while (1) {
        c = getchar();
        if (c == ' ' || c == ',' || c == '.' || c == '\n' || (c >= '0' && c <= '9') ||
            (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))   // store a char
        {
            memory[i++] = c;
        } 
        else if (c == '@')  // delete a char
        {
            if (i > 0)  // index shouldn't go out of bounds
                i--;
        } 
        else if (c == '$')  // delete a line
        {
            while (memory[i] != '\n' && i >= 0)
                i--;
            i++;
        } 
        else if (c == '^')  
        {
            int j = i - 1;
            while (memory[j] == ' ' || memory[j] == ',' || 
                memory[j] == '.' || memory[j] == '\n')
            {   // skip these characters
                j--;
                if (j <= 0)
                {
                    j = 0;
                    break;
                }
            }
            // find the first char of the previous word
            while (memory[j] != ' ' && memory[j] != ',' && 
                memory[j] != '.' && memory[j] != '\n' && j >= 0) 
            {
                j--;
            }
            j++;
            // change to cap
            if (memory[j] >= 'A' && memory[j] <= 'Z') 
                continue;
            else if (memory[j] >= 'a' && memory[j] <= 'z')
                memory[j] = memory[j] - 'a' + 'A';
        } 
        else if (c == '#')  // end
        {
            memory[i++] = '\0';
            break;
        }
    }
    printf("%s", memory);
    return 0;
}