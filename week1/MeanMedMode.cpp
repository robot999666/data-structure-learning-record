// 在调查数据分析（Survey data analysis）中经常需要计算平均数、中位数和众数。
// 用函数编程计算40个输入数据（每个数据是取值1—10之间的任意整数）的平均数（Mean）、中位数（Median）和众数（Mode）。
// 中位数指的是排列在数组中间的数。众数是数组中出现次数最多的那个数（不考虑两个或两个以上的输入数据出现次数相同的情况）。
// 计算中位数时，首先要调用排序函数对数组按升序进行排序，然后取出排序后数组中间位置的元素answer[n/2] ，就得到了中位数。
// 如果数组元素的个数是偶数，那么中位数就等于数组中间那两个元素的算术平均值。

// 输入格式:
// 输入共4行，每行中给出10个1-10之间的整数，用空格隔开。

// 输出格式:
// 输出共三行，分别按制定格式输出平均数、中位数和众数。

// 输出格式是：
// Mean value=%d\n
// Median value=%d\n
// Mode value=%d\n

// 输入样例:
// 10 9 10 8 7 6 5 10 9 8
// 8 9 7 6 10 9 8 8 7 7
// 6 6 8 8 9 9 10 8 7 7
// 9 8 7 9 7 6 5 9 8 7
// 输出样例:
// Mean value=7
// Median value=8
// Mode value=8

#include <stdio.h>
void bubble(int* a,int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(a[j]>a[j+1]){
                int temp;temp=a[j];a[j]=a[j+1];a[j+1]=temp;
            }
        }
    }
}
void zhong(int* a,int n,int &mod){
    int k=1;int max=0;
    for(int i=1;i<n;i++){
        if(a[i]==a[i-1]){
            k++;
        }
        else
            k=1;
        if(k>max) 
        {
            max=k;mod=a[i];
        }
    }
}
int main(){
    int a[41];
    int i=0;
    int sum=0;
    int ave,med,mod;
    while(scanf("%d",a+i)!=EOF){
        sum+=a[i];
        i++;
    }
    ave=sum/i;
    bubble(a,i);
    zhong(a,i,mod);
    if(i&1) med=a[i/2];
    else med=(a[i/2]+a[i/2-1])/2;
    printf("Mean value=%d\nMedian value=%d\nMode value=%d",ave,med,mod);
}