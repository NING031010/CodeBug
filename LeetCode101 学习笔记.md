## LeetCode101 学习笔记

#### 一，贪心算法

局部最优相互独立，全局最优为局部最优的简单求和。

#### 1.分配问题：

- ##### Assign Cookies

**题目描述：**

有一群孩子和一堆饼干，每个孩子有一个饥饿度，每个饼干都有一个大小。每个孩子只能吃 最多一个饼干，且只有饼干的大小大于孩子的饥饿度时，这个孩子才能吃饱。求解最多有多少孩 子可以吃饱。 

**输入输出样例：**

> 输入两个数组，分别代表孩子的饥饿度和饼干的大小。输出最多有多少孩子可以吃饱的数量。 
>
> Input: [1,2], [1,2,3] 	Output: 2 
>
> 在这个样例中，我们可以给两个孩子喂 [1,2]、[1,3]、[2,3] 这三种组合的任意一种。

**题解**

把孩子和饼干分别排序。 这样我们就可以从饥饿度最小的孩子和大小最小的饼干出发，计算有多少个对子可以满足条件。

首先学习一下快排算法：
快速排序使用分治的思想。选取一个分界点，通过一趟排序将待排序序列分割成两部分，一部分比分界点值小，一部分比分界点值大。进而递归排序这两部分，最后使得整个序列有序。

图解：

![img](https://img2018.cnblogs.com/blog/1741670/201908/1741670-20190805082917781-659864498.png)

代码：

```c
void sort(int *arr, int a, int b) //一般a=0,b=len-1
{
    if (a >= b)
        return;
    int x = arr[a], i = a - 1, j = b + 1; //取第一个元素的大小为左右分界点，指针初始指向最左与最右端
    while (i < j)
    {
        do
            i++;
        while (arr[i] < x); // i右移
        do
            j--;
        while (arr[j] > x); // j左移
        if(i < j)
        {
            int temp = arr[i]; //交换
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    sort(arr, a, j); //分别对左右分区进行相同操作
    sort(arr, j + 1, b);
}
```

分配函数实现代码：

```c
int assigncookies(int *children, int chilen, int *cookies, int coolen)
{
    sort(children, 0, chilen - 1);//排序
    sort(cookies, 0, coolen - 1);
    int child = 0, cook = 0;
    while(child < chilen && cook < coolen)//从最小饥饿度的孩子开始分配
    {
        if(children[child] <= cookies[cook])
            ++child;
        ++cook;//从小到大遍历饼干至满足孩子
    }
    return child;
}
```



- **candy**

**题目描述：**

一群孩子站成一排，每一个孩子有自己的评分。现在需要给这些孩子发糖果，规则是如果一 个孩子的评分比自己身旁的一个孩子要高，那么这个孩子就必须得到比身旁孩子更多的糖果；所 有孩子至少要有一个糖果。求解最少需要多少个糖果。 

**输入输出样例：**

> 输入是一个数组，表示孩子的评分。输出是最少糖果的数量。 
> Input: [1,0,2] Output: 5 
> 在这个样例中，最少的糖果分法是 [2,1,2]。

**题解：**

我们只需要简单的两次遍历即可：把所有孩子的糖果数初始化为 1； 先从左往右遍历一遍，如果右边孩子的评分比左边的高，则右边孩子的糖果数更新为左边孩子的 糖果数加 1；再从右往左遍历一遍，如果左边孩子的评分比右边的高，且左边孩子当前的糖果数 不大于右边孩子的糖果数，则左边孩子的糖果数更新为右边孩子的糖果数加 1。通过这两次遍历， 分配的糖果就可以满足题目要求了。这里的贪心策略即为，在每次遍历中，只考虑并更新相邻一 侧的大小关系。

```C
int candy(int *rating, int len)
{
    if(len < 2)//只有一个孩子，一个糖果
        return len;
    int num[len];
    for(int i = 0; i < len; i++)//初值为1
    {
        num[i] = 1;
    }
    for(int i  = 1; i < len; i++)//从左向右遍历
    {
        if(rating[i] > rating[i - 1])
            num[i] = num[i - 1] + 1;
    }
    for(int i = len - 1; i > 0; i--)//从右向左遍历
    {
        if(rating[i] < rating[i - 1])
        {
            if(num[i - 1] < num[i] + 1)
                num[i - 1] = num[i] + 1;
        }
    }
    int candy = 0;
    for(int i = 0; i < len; i++)//累加输出
    {
        candy += num[i];
    }
    return candy;
}
```



#### 2.区间问题：

- **Non-overlapping Intervals**

**题目描述：**

给定多个区间，计算让这些区间互不重叠所需要移除区间的最少个数。起止相连不算重叠。 

**输入输出样例：**

> 输入是一个数组，数组由多个长度固定为 2 的数组组成，表示区间的开始和结尾。输出一个 整数，表示需要移除的区间数量。 
> Input: [[1,2], [2,4], [1,3]] Output: 1 
> 在这个样例中，我们可以移除区间 [1,3]，使得剩余的区间 [[1,2], [2,4]] 互不重叠。

**题解：**

目标是留下不相交的小区间，移去大区间，因为重叠区间是固定的，移除大区间时能保证移除数目最少。

若一组区间给定，那么区间最左端就确定了，可以按照右端的大小对区间进行排序，保留右端较小且不重合的区间；或者最右端确定了，那么按照左端的大小对区间进行排序，保留左端较大且不重合的区间，

首先学习一下冒泡排序（会超时）：

```C
void sort(int *a, int alen)
{
    for (int i=0; i<n-1; ++i)  //比较n-1轮
    {
        for (int j=0; j<n-1-i; ++j)  //每轮比较n-1-i次,
        {
            if (a[j] < a[j+1])
            {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}
```

下面展示第一种理解：

```C
void sort(int **arr, int a, int b)//快排函数
{
    if(a >= b)
        return;
    int x = arr[a][1], i = a - 1, j = b + 1; //取第一个元素的大小为左右分界点，指针初始指向右端
    while (i < j)
    {
        do
            i++;
        while (arr[i][1] < x); // i右移
        do
            j--;
        while (arr[j][1] > x); // j左移
        if(i < j)
        {
            int temp = arr[i][1];  //交换
            arr[i][1] = arr[j][1];
            arr[j][1] = temp;
            temp = arr[i][0]; //交换
            arr[i][0] = arr[j][0];
            arr[j][0] = temp;
        }
        
    }
    sort(arr, a, j); //分别对左右分区进行相同操作
    sort(arr, j + 1, b);
}
int eraseOverlapIntervals(int **intervals, int alen, int *blen)
{
    if (alen == 0)
        return 0;
    sort(intervals, 0, alen - 1);
    int removed = 0, prev = intervals[0][1];
    for (int i = 1; i < alen; ++i)
    {
        if (intervals[i][0] < prev) //区间重叠判断
            ++removed;
        else
            prev = intervals[i][1]; //扩展保留区间大小
    }
    return removed;
}
```



#### 3.练习：

- **Can Place Flowers**

**题目描述：**

‎你有一个长长的花坛，其中一些地块已被种植，有些则没有。条件是**不能在‎‎相邻‎**‎的地块上种植花卉。‎‎给定一个包含 0 和 1 的整数数组，表示花坛现在的种植状态，其中 0 表示为空，1 表示不为空，并且给定一个整数表示要种的花的数量，‎如果可以在不违反无相邻花规则的情况下种植，则返回ture，否则返回false。

**输入输出样例：**

> Input: flowerbed = [1,0,0,0,1], n = 1		
> Output: true

**题解：**

**1.贪心算法**

从左向右遍历花坛，能种就种，种花的条件是：自己为空；左边为空或自己在最左端；右边为空或自己是最右

代码样例：

```C
bool canPlaceFlowers(int* flowered, int flowerbedSize, int n){
	for(int i = 0; i < flowerbedSize; i++)
    {
        if(flowered[i]==0 && (i==0 || flowered[i-1]==0) && (i==flowerbedSize-1 || flowered[i+1] == 0))
        //注意这里用了||的短路性，如果i==0是真，就不会判断flowered[i - 1]，不会越界
        {
            n--;
            flowered[i] = 1;
            if(n == 0)
            	return 1;
        }
    }
    return n <= 0;
}
```

**2.防御式编程**

把花坛两端加上0，可以将两端的特殊情况化为一般，只要有连续的3片空地就能种一朵花



- **Minimum Number of Arrows to Burst Balloons**

**题目描述：**

XY平面上贴有一些气球，气球的x坐标范围由区间给出，y坐标未知（y>0），现在从x轴上某点沿着y轴正方向射出箭头，把气球扎爆，箭头始终沿着y轴正方向做直线运动，输出把所有气球扎爆所需的最小箭头数量。

**输入输出样例：**

> Input: points = [[10,16],[2,8],[1,6],[7,12]]
> Output: 2
> Explanation: The balloons can be burst by 2 arrows:
>
> - Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
> - Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12].

**题解：**

和上面的例题很相像，本题要求最少的箭头数量，能一块扎爆的是有重叠区间的，所以在一些重叠的区间中留下一个就行，其他的移除，这里要求移除的最多，剩下的区间数即为需要的箭头数。稍微修改一下例题的代码即可。
代码样例：

```c
void sort(int **arr, int a, int b)//快排函数
{
    if(a >= b)
        return;
    int x = arr[a][1], i = a - 1, j = b + 1; //取第一个元素的大小为左右分界点，指针初始指向右端
    while (i < j)
    {
        do
            i++;
        while (arr[i][1] < x); // i右移
        do
            j--;
        while (arr[j][1] > x); // j左移
        if(i < j)
        {
            int temp = arr[i][1];  //交换
            arr[i][1] = arr[j][1];
            arr[j][1] = temp;
            temp = arr[i][0]; //交换
            arr[i][0] = arr[j][0];
            arr[j][0] = temp;
        }
    }
    sort(arr, a, j); //分别对左右分区进行相同操作
    sort(arr, j + 1, b);
}
int findMinArrowShots(int** intervals, int alen, int* pointsColSize)
{
    if (alen == 0)
        return 0;
    sort(intervals, 0, alen - 1);
    int removed = 0, prev = intervals[0][1];
    for (int i = 1; i < alen; ++i)
    {
        if (intervals[i][0] <= prev) //区间重叠判断,本题中边界算作重叠
            ++removed;
        else
            prev = intervals[i][1];
    }
    return alen - removed;
}
```



- **Partition Labels**

**题目描述：**

给定一个由26个字母组成的字符串，要将字符串分割为几个部分，使其中的每个字符只出现在一个部分，要求分割的部分最多，输出分割方案。

**输入输出样例：**

> Input: s = "ababcbacadefegdehijhklij"
> Output: [9,7,8]
> Explanation:
> The partition is "ababcbaca", "defegde", "hijhklij".	This is a partition so that each letter appears in at most one part.
> A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits s into less parts.

**题解：**

本质上还是区间重叠的问题，可以从左往右遍历，得到每个字母的起始位置，再从右往左遍历，得到每个字母的最终位置，得到该字母的位置区间。有重叠的必须放在同一部分，合并区间即可。

代码样例：

```C
//Note: The returned array must be malloced, assume caller calls free().
int* partitionLabels(char* s, int* returnSize)//注意：第二个参数是返回数组的大小，需要赋值
{
    int start = 0, end = 0;
	int len = strlen(s);
    int last[26] = {0};//存储字母最终位置
    int* res = (int* )calloc(len, sizeof(int));//存储分配结果
    //寻找字母结束位置
    for(int i = 0; i < len; i++)
        last[s[i] - 'a'] = i;//记录数据的小技巧
    //贪心分配
    int j = 0;
    *returnSize = 0;
    for(int i = 0; i < len; i++)
    {
        if(last[s[i] - 'a'] > end)
            end = last[s[i] - 'a'];
        if(end == i)
        {
            res[j] = end - start + 1;
            j++;
            (*returnSize)++;
            start = end + 1;
        }
    }
    return res;
}
```



- **Best Time to Buy and Sell Stock II**

**题目描述：**

给定一个数组prices，prices[i]表示第 i 天的股票价格，在每一天，你可以决定买下或者卖掉股票，但你手中最多只能有一张股票，输出你能得到的最大利润。

**输入输出样例：**

> Input: prices = [7,1,5,3,6,4]
> Output: 7
> Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
> Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
> Total profit is 4 + 3 = 7.

**题解：**

打眼一看就知道是个动态规划的题目，但本题只要求最大利润，所以贪心计算最大差值即可，如果今天比昨天价格高，则能赚个差价，
根据简单的数学原理，差价累加即为最大利润。

贪心代码样例：

```C
int maxProfit(int* prices, int pricesSize)
{
	int profit = 0;
    for(int i = 1; i < pricesSize; i++)
    {
        if(prices[i] > prices[i - 1])
        	profit += (prices[i] - prices[i - 1]);
    }
    return profit;
}
```

动态规划样例：
定义数组dp[i] [2]，dp[i] [0] 存储第i天未持有股票时前i天的收益最大值，dp[i] [1] 存储第i天持有股票时前i天的收益最大值；
状态转移方程：
dp[i] [0] = Max{dp[i - 1] [0]，dp[i - 1] [1] + price[i]}
dp[i] [1] = Max{dp[i - 1] [1]，dp[i] [0] - price[i]}

```C
int maxProfit(int* prices, int pricesSize)
{
	int dp[30000][2] = {0};
    dp[0][0] = 0, dp[0][1] = -prices[0];
    for(int i = 1; i < pricesSize; i++)
    {
        dp[i][0] = dp[i-1][0] > (dp[i-1][1] + prices[i]) ? dp[i-1][0] : (dp[i-1][1] + prices[i]);
        dp[i][1] = dp[i-1][1] > (dp[i][0] - prices[i]) ? dp[i-1][1] : (dp[i][0] - prices[i]);
    }
    return dp[pricesSize - 1][0];
}
```



- **Queue Reconstruction by Height**

**题目描述：**

假设有打乱顺序的一群人站成一个队列，数组 people 表示队列中一些人的属性（不一定按顺序）。每个 people[i] = [hi, ki] 表示第 i 个人的身高为 hi ，前面 正好 有 ki 个身高大于或等于 hi 的人。请你重新构造并返回输入数组 people 所表示的队列。返回的队列应该格式化为数组 queue ，其中 queue[j] = [hj, kj] 是队列中第 j 个人的属性（queue[0] 是排在队列前面的人）。

**输入输出样例：**

> 输入：people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
> 输出：[[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
> 解释：
> 编号为 0 的人身高为 5 ，没有身高更高或者相同的人排在他前面。
> 编号为 1 的人身高为 7 ，没有身高更高或者相同的人排在他前面。
> 编号为 2 的人身高为 5 ，有 2 个身高更高或者相同的人排在他前面，即编号为 0 和 1 的人。
> 编号为 3 的人身高为 6 ，有 1 个身高更高或者相同的人排在他前面，即编号为 1 的人。
> 编号为 4 的人身高为 4 ，有 4 个身高更高或者相同的人排在他前面，即编号为 0、1、2、3 的人。
> 编号为 5 的人身高为 7 ，有 1 个身高更高或者相同的人排在他前面，即编号为 1 的人。
> 因此 [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] 是重新构造后的队列。

**题解：**

首先将身高从小到大排序，身高相同时按照k值升序排列（k值越大越靠后面），按照顺序依次将人放入重组队列，即第 i 个人的位置是队列中从左往右数第 ki + 1个空位置。

代码样例：

```C
//这里是官方解答
int cmp(const void* _a, const void* _b) //库函数qsort的自定义比较函数
{
    int *a = *(int**)_a, *b = *(int**)_b;
    return a[0] == b[0] ? b[1] - a[1] : a[0] - b[0];//如果相同身高，则按k排
}

int** reconstructQueue(int** people, int peopleSize, int* peopleColSize, int* returnSize, int** returnColumnSizes) 
{
    qsort(people, peopleSize, sizeof(int*), cmp);//排序
    int** ans = (int**)calloc(peopleSize, sizeof(int*));//重组后的队列
    *returnSize = peopleSize;//返回数组的行数
    *returnColumnSizes = (int*)calloc(peopleSize, sizeof(int));//返回数组一行的元素个数
    for (int i = 0; i < peopleSize; i++) 
    {
        int spaces = people[i][1] + 1;//需要放置在第spaces个空位置
        for (int j = 0; j < peopleSize; j++) 
        {
            if ((*returnColumnSizes)[j] == 0) 
            {
                spaces--;
                if (!spaces) {//放置并标记该位置为非空
                    (*returnColumnSizes)[j] = 2;
                    ans[j] = (int*)calloc(2, sizeof(int));
                    ans[j][0] = people[i][0], ans[j][1] = people[i][1];
                    break;
                }
            }
        }
    }
    return ans;
}
```

一些函数参数的解释：

> int** reconstructQueue(int** people, int peopleSize, int* peopleColSize, int* returnSize, int** returnColumnSizes) 
> //典型的传参方式，people为传入的二维数组，peopleSize为其行数，peopleColSize存储每一行的元素个数
> //returnSize为返回数组的行数，returnColumnSize存储返回数组的每行元素个数*
>
> 问：为什么传入的参数是returnSize是int*型？
> 答：因为我们要对传入的参数进行写入，而非只是读取。
> 问：？
> 答：如果传入为int，我们在函数内部对他进行天花乱坠的操作，但是函数一结束，依旧会为原来的值。但是如果传入的是他的地址，我们直接找到它的老窝，把他给改了，那他就真的改了。
>
> 问：那如果我们想要写入传入参数的地址呢？
> 答：地址也是一个变量（指针变量），我们只需要传入地址的地址，即可。
> 问：这样子说来，我好像有些懂那个returnColumnSizes了。
> 答：一堆叭叭叭，往往不如一个例子来得实在，下面举一个实栗 吧~
>
> returnColumnSizes	是一维数组的地址的地址
> \* returnColumnSizes		是一维数组的地址
> (\* returnColumnSizes)[i]	是一维数组的第i个元素



- **Non-decreasing Array**

**题目描述：**

给定一个带有整数的数组，您的任务是通过‎‎最多修改一个元素‎‎来检查它是否可以变为非递减。

**输入输出样例：**

> Input: nums = [4,2,3]
> Output: true
> Explanation: You could modify the first 4 to 1 to get a non-decreasing array.

**题解：**

要满足非递减的条件，对于每个数只考虑与前数的大小关系即可，从左向右遍历，如果该数小于前一个数则需要修改，那么问题就变为了将它修改为多少才不会影响后面的操作从而使修改次数最少，修改方案有两个：把该数修改为前一个数的值；把前一个数修改为该数的值。可以想到，若该数小于前一个数的前一个数，那么第二种方案很显然是错误的，只能选择方案一，否则，应尽量不扩大该数以不影响后面的操作，所以选择方案二。

代码样例：

```C
bool checkPossibility(int* nums, int numsSize)
{
	int count = 0;	//用count记录修改次数判断能否
    for (int i = 1; i < numsSize; i++) 
    {
        if (nums[i] < nums[i - 1]) 
        {
            if (i == 1 || nums[i] >= nums[i - 2])
                nums[i - 1] = nums[i];
            else 	
                nums[i] = nums[i - 1];
            count++;
        }
    }
    return count <= 1;
}
```



#### 二，双指针

双指针主要用于遍历数组，两个指针指向不同的元素，从而协同完成任务。也可以延伸到多 个数组的多个指针。若两个指针指向同一数组，遍历方向相同且不会相交，则也称为滑动窗口（两个指针包围的区域即为当前的窗口），经常用于区间搜索。 若两个指针指向同一数组，但是遍历方向相反，则可以用来进行搜索，待搜索的数组往往是排好序的。

常见指针的定义如下：

> int x; 
> int * p1 = &x; // 指针可以被修改，值也可以被修改 
> const int * p2 = &x; // 指针可以被修改，值不可以被修改（const int） 
> int * const p3 = &x; // 指针不可以被修改（* const），值可以被修改 
> const int * const p4 = &x; // 指针不可以被修改，值也不可以被修改
>
> int* func(int x, int y);	//返回值为指针的函数
> int ( *fun)(int x, int y);	//指向函数的指针	fun = function或者fun = &function(赋值)		x = fun()或x = ( *fun)();(使用)
>
> int *arr[N];	//元素为指针的数组
> int ( *arr)[N];	//指向数组的指针（类似二维数组）



#### 1.Two Sum:

- **Two Sum II - Input Array Is Sorted**

**题目描述：**

在一个增序的整数数组里找到两个数（不能重复），使它们的和为给定值。已知有且只有一对解。

**输入输出样例：**

> Input: numbers = [2,7,11,15], target = 9
> Output: [1,2]
> Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].

**题解：**

见到数组先排序，因为数组已经排好序，我们可以采用方向相反的双指针来寻找这两个数字，一个初始指向最小的元素，即数组最左边，向右遍历；一个初始指向最大的元素，即数组最右边，向左遍历。如果两个指针指向元素的和等于给定值，那么它们就是我们要的结果。如果两个指针指向元素的和小于给定值，我们把左边的指针右移一位，使得当前的和增加一点。如果两个指针指向元素的和大于给定值，我们把右边的指针左移一位，使得当前的和减少一点。

代码样例：

```C
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize)
{
	int l = 0, r = numbersSize - 1;	//初始位置
    int sum = 0;	//记录和
    while (l < r) //移动指针
    {
        sum = numbers[l] + numbers[r];
        if (sum == target)	break;
        if (sum < target)	l++;
        else	r--;
    }
    *returnSize = 2;
    int* ans = (int*)calloc(2, sizeof(int));
    ans[0] = l + 1;		ans[1] = r + 1;
    return ans;
}
```



#### 2.归并有序数组：

- **Merge Sorted Array**

**题目描述：**

给定两个有序增数组，把两个数组合并为一个有序增数组，数组一长度为两数组实际长度之和，结果存储在数组一中。

**输入输出样例：**

> Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
> Output: [1,2,2,3,5,6]
> Explanation: The arrays we are merging are [1,2,3] and [2,5,6].
> The result of the merge is [1,2,2,3,5,6] with the underlined elements coming from nums1.

**题解：**

因为数组一后面是空的，所以先放大的，两个指针分别在数组一二的末尾，选择较大的那个插入，较大的那个指针向前移动，要插入的位置向前移动，其实就是所有元素一个一个比较，谁大谁放后面。

代码示例：

```C
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n)
{
	int pos = m-- + n-- - 1;	
    while (m >= 0 && n >= 0)	//直接用m和n，效率高
        nums1[pos--] = nums1[m] > nums2[n] ? nums1[m--] : nums2[n--];
    while (n >= 0)	//把2剩下的贴进1
        nums1[pos--] = nums2[n--];
}
```



#### 3.快慢指针：

-  **Linked List Cycle II**

**题目描述：**

给定一个链表，如果有环路，找出环路的开始点。

如果没有特殊说明，LeetCode 采用如下的数据结构表示链表。

> struct ListNode {
> int val;
> ListNode *next;
> };

**输入输出样例：**

> Input: head = [3,2,0,-4], pos = 1
> Output: tail connects to node index 1
> Explanation: There is a cycle in the linked list, where tail connects to the second node.

**题解：**

对于链表找环路的问题，有一个通用的解法——快慢指针（Floyd 判圈法）。
给定两个指针，分别命名为 slow 和 fast，起始位置在链表的开头。每次 fast 前进两步，slow 前进一步。如果 fast可以走到尽头，那么说明没有环路；如果 fast 可以无限走下去，那么说明一定有环路，且一定存在一个时刻 slow 和 fast 相遇。当 slow 和 fast 第一次相遇时，我们将 fast 重新移动到链表开头，并让 slow 和 fast 每次都前进一步。当 slow 和 fast 第二次相遇时，相遇的节点即为环路的开始点。

代码示例：

```C
struct ListNode *detectCycle(struct ListNode *head) 
{
    struct ListNode *slow = head, *fast = head;
	// 判断是否存在环路
	do {
		if (!fast || !fast->next) //fast能走到头，没有环路
            return NULL;
		fast = fast->next->next;
		slow = slow->next;
	} while (fast != slow);
	// 如果存在，查找环路节点
	fast = head;
	while (fast != slow)
    {
	slow = slow->next;
	fast = fast->next;
	}
	return fast;
}
```



#### 4.滑动窗口：

- **Minimum Window Substring**

**题目描述：**

给定两个字符串 S 和 T，求 S 中包含 T 所有字符的最短连续子字符串的长度，同时要求时间复杂度不得超过 O(n)。

**输入输出样例：**

> Input: S = "ADOBECODEBANC", T = "ABC" 
> Output: "BANC"

**题解：**

滑动窗口本质就是对暴力解法的两层for循环的优化，也即动态调整内外层的for循环，第一层是left，第二层是right，从逻辑上剪枝去掉多余冗余的判断。

具体思路：

- 找可行解。从0开始匹配，开启窗口，右边界扩大至满足条件，则此时再往后扩不符合最小子串
- 找最优解。再缩左边界，找到最小子串，然后滑窗。也就是当前从左到右可行解里已找到最优解，那么这段区间后面就没必要再找。
- 滑动窗口。把左边界右移，继续往后滑动，重复右边界扩大至满足条件找新的一个区间
- 终止条件。直到右边界找到末尾停止，返回最小的区间范围

代码样例：

```C
#define MAX_LEN 128
char* minWindow(char * s, char * t) {
    int hashNeed[MAX_LEN] = {0}, hashWindow[MAX_LEN] = {0};
    int start = 0, end = 0;
    int minStart = 0, minLen = INT_MAX;
    int lenS = strlen(s);
    int lenT = 0, valid = 0;
    for (int i = 0; t[i]; i++) {	//存储要找的字符信息
        hashNeed[t[i]]++;
    }
    for (int i = 0; i < MAX_LEN; i++) {		//t中不重复的字符个数
        if (hashNeed[i] != 0) 	lenT++;
    }
    // 记录最小覆盖子串的起始索引及长度
    while (end < lenS) {
        char c = s[end];	// c 是将移入窗口的字符
        end++;	// 右移窗口
        // 进行窗口内数据的一系列更新
        if (hashNeed[c]) {
            hashWindow[c]++;
            if (hashWindow[c] == hashNeed[c])
                valid++;	//某个字符已找全
        }
        // 判断左侧窗口是否要收缩
        while (valid == lenT) {
            // 在这里更新最小覆盖子串
            if (end - start < minLen) {
                minStart = start;
                minLen = end - start;
            }
            char d = s[start];	// d 是将移出窗口的字符
            start++;	// 左移窗口
            if (hashNeed[d]) {
                if (hashWindow[d] == hashNeed[d])
                    valid--;
                 hashWindow[d]--;
            }
        }
    }
    if (minLen == INT_MAX) 	return "";
    s[minStart + minLen] = '\0'; //切掉后面的
    return &s[minStart];	//切掉前面的
}
```



#### 5.练习：

- 





















