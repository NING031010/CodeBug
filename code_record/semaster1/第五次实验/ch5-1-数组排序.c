/****************************
【问题描述】
读取一个整型数组（元素个数不超过10000，每个数都是正数），
使用插入排序进行非递减排序，输出排序后的数组。要求读取数组、排序、输出数组用三个函数来实现。
【输入形式】
第一个数字是总共需要排序的字符数，接下来是需要被排序的数字。
【输出形式】
排好序的数字，每个一行。
【样例输入】
5
7
24
1
6
91
【样例输出】
1
6
7
24
91
*****************************/

#include <stdio.h>
#define N 10000

/* get the input array
 * a is the array, n is the number of inputs */
void get_input(int a[], int n) 
{
    int i;
    for (i = 0; i < n; i++) 
    {
        scanf("%d", &a[i]);
    }
}

/* sort elements in array a using insert sort
 * n is the number of elements */
void sort(int a[], int n) 
{
    int i, j, current, index;
    for (i = 1; i < n; i++) 
    {
        current = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > current)
        { // a[j] moves to the next unit
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = current;
    }
}

/* output the sorted array */
void print_array(int a[], int n) 
{
    int i;
    for (i = 0; i < n; i++) 
    {
        printf("%d\n", a[i]);
    }
}

int main(){
    int n;
    int b[N];
    scanf("%d", &n);
    get_input(b, n);
    sort(b, n);
    print_array(b, n);
    return 0;
}