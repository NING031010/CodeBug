/****************************
【问题描述】输入具有n个不同浮点数值的数组，找出将数组排序所需的最小交换次数。
◦ 思路：依次从前往后，找出第i小的数放在第i位，记录需要交互次数。
◦ 注意：排序可以是从小到大或从大到小。
【输入形式】第一行是整数n，0 < n <= 1000。第二行是n个浮点数，每个浮点数在(0, 50000)区间内。
【输出形式】一个整数，为最小交换次数。
【样例输入】1 5 4 3 2
【样例输出】2
【样例说明】交换5 2，再交换4 3，即升序排序完毕。
*****************************/

#include <stdio.h>
#define N 1003

// sort according to descending order or ascending order
double descend[N], ascend[N];

int main() {
    int n, i, j;
    // input
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%lf", &ascend[i]);
        descend[i] = ascend[i];
    }

    int swap1 = 0, swap2 = 0;
    int min_index, max_index;
    double min, max, temp;
    // seletion sort
    // record number of swaps in variable swap1, swap2
    for (i = 0; i < n; i++) {
        min = ascend[i];
        min_index = i;
        for (j = i; j < n; j++) {
            if (ascend[j] < min) {
                min = ascend[j];
                min_index = j;
            }
        }
        if (min_index != i) {
            temp = ascend[i];
            ascend[i] = min;
            ascend[min_index] = temp;
            swap1++;
        }
    }
    for (i = 0; i < n; i++) {
        max = descend[i];
        max_index = i;
        for (j = i; j < n; j++) {
            if (descend[j] > max) {
                max = descend[j];
                max_index = j;
            }
        }
        if (max_index != i) {
            temp = descend[i];
            descend[i] = max;
            descend[max_index] = temp;
            swap2++;
        }
    }
    
    if (swap1 <= swap2) 
        printf("%d", swap1);
    else
        printf("%d", swap2);
    return 0;
}