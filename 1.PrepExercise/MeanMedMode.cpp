// 数据分析程序：计算平均数、中位数和众数
// 输入：40个1-10之间的整数，分4行每行10个
// 输出：平均数、中位数、众数
#include <stdio.h>
// 冒泡排序函数：升序排列数组
void bubble(int *a, int n)
{
    for (int i = 0; i < n - 1; i++)  // 外层循环：控制排序轮数
    {
        for (int j = 0; j < n - 1 - i; j++)  // 内层循环：每轮比较相邻元素
        {
            if (a[j] > a[j + 1])  // 如果前一个元素大于后一个元素
            {
                int temp;  // 临时变量用于交换
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}
// 寻找众数函数：在已排序数组中找到出现次数最多的元素
void zhong(int *a, int n, int &mod)
{
    int k = 1;    // 当前元素的连续出现次数
    int max = 0;  // 最大连续出现次数

    for (int i = 1; i < n; i++)  // 从第二个元素开始遍历
    {
        if (a[i] == a[i - 1])  // 如果当前元素与前一个元素相同
        {
            k++;  // 连续计数加1
        }
        else
            k = 1;  // 重置计数

        if (k > max)  // 如果当前连续次数大于最大次数
        {
            max = k;     // 更新最大次数
            mod = a[i];  // 更新众数
        }
    }
}
int main()
{
    int a[41];     // 存储输入数据的数组
    int i = 0;     // 数组索引和数据计数
    int sum = 0;   // 数据总和
    int ave, med, mod;  // 平均数、中位数、众数

    // 读取所有输入数据，直到文件结束
    while (scanf("%d", a + i) != EOF)
    {
        sum += a[i];  // 累加求和
        i++;          // 计数器加1
    }

    ave = sum / i;  // 计算平均数

    bubble(a, i);   // 对数组进行冒泡排序
    zhong(a, i, mod);  // 寻找众数

    // 计算中位数
    if (i & 1)  // 如果元素个数为奇数
        med = a[i / 2];  // 中位数是中间的元素
    else  // 如果元素个数为偶数
        med = (a[i / 2] + a[i / 2 - 1]) / 2;  // 中位数是中间两个元素的平均值

    // 输出结果
    printf("Mean value=%d\nMedian value=%d\nMode value=%d", ave, med, mod);
}