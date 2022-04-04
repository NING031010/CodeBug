#include <stdio.h>
#include <stdlib.h>
int main()
{
    //输入
    int n;
    scanf("%d", &n);
    double arry[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%lf", &arry[i]);
    }
    double arry_[n];
    for (int i = 0; i < n; i++)
    {
        arry_[i] = arry[i];
    }
    //处理
    //从小到大
    int count = 0;  //记录交换次数
    double min = 0; //记录当前最小值
    int loc = 0;    //记录当前最小值所在位置

    for (int i = 0; i < n; i++)
    { //寻找从i到n的最小值及其位置
        min = arry[i];
        loc = i;
        for (int k = i + 1; k < n; k++)
        {
            if (min > arry[k])
            {
                min = arry[k];
                loc = k;
            }
        }
        if (loc != i)
        { //交换位置，使第i小的在第i位
            double temp = 0;
            temp = arry[i];
            arry[i] = min;
            arry[loc] = temp;
            count++;
        }
    }

    //从大到小
    int count_ = 0; //记录交换次数
    double max = 0; //记录当前最大值
    int loc_ = 0;   //记录当前最大值所在位置

    for (int i = 0; i < n; i++)
    { //寻找从i到n的最大值及其位置
        max = arry_[i];
        loc_ = i;
        for (int k = i + 1; k < n; k++)
        {
            if (max < arry_[k])
            {
                max = arry_[k];
                loc_ = k;
            }
        }
        if (loc_ != i)
        { //交换位置，使第i小的在第i位
            double temp_ = 0;
            temp_ = arry_[i];
            arry_[i] = max;
            arry_[loc_] = temp_;
            count_++;
        }
    }
    //输出
    printf("%d", (count < count_) ? (count) : (count_));
    system("pause");
    return 0;
}
