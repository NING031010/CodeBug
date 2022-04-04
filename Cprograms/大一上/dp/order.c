#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void order(int len, int num[], int depth, int path[], int out[])
{
    if (depth == len) 
    {
        for (int j = 0; j < len; j++)
        {
            printf("%d ", out[j]);
        }
        printf("\n");
        return;
    }
    for (int i = 0; i < len; i++)
    {
        if (path[i])
            continue;
        out[depth] = num[i];
        path[i] = 1;
        depth++;
        order(len, num, depth, path, out);
        depth--;
        path[i] = 0;
    }
}
int main() 
{
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &a[i]);
    }
    int out[n];
    int depth = 0;
    int path[n];
    memset(path, 0, sizeof(path));
    order(n, a, depth, path, out);
    system("pause");
    return 0;
}