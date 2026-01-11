// ### 双向冒泡排序
// 本题要求改写冒泡排序算法：奇数趟从左到右，偶数趟从右到左。整个排序从第1趟开始。关键字个数不超过500个。

// 输入格式:  
// 输入数据是关键字个数及所有关键字

// 输出格式:  
// 输出排序过程中记录交换的次数和排序后的结果。所有数据都用 `%4d` 格式输出。

// 输入样例:
// ```
// 5
// 5 4 3 2 1
// ```
// 输出样例:
// ```
//   10
//    1   2   3   4   5
// ```

#include<stdio.h>

int count=0;

void swap(int &p,int &q){
    p^=q;q^=p;p^=q;
    count++;
}

void new_bubble(int* L,int low,int high)
 { 
   while(low< high)
   { // 从表的两端交替地向中间扫描
     for(int i=low;i<high;i++)
         if(L[i]>L[i+1])
             swap(L[i],L[i+1]);
    --high;
     for(int i=high;i>low;i--)
         if(L[i]<L[i-1])
             swap(L[i],L[i-1]);
     ++low;
   }
 }

int main(){
    int n;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++)
        scanf("%d",&arr[i]);
    new_bubble(arr,0,n-1);
    printf("%4d\n",count);
    for(int i=0;i<n;i++)
        printf("%4d",arr[i]);
}