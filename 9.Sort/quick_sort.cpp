// 假设每次用第一个关键字做枢轴，请实现快速排序算法。关键字个数不超过500个。
// 输入格式:  
// 输入共2行，第一行是关键字的个数，第二行给出所有的关键字。
// 输出格式:  
// 输出共2行，分别输出排序过程中用到的枢轴记录和排序后的结果，每个关键字用 `%4d` 输出。
// 输入样例:
// ```
// 10
// 6 8 7 9 0 1 3 2 4 5
// ```
// 输出样例:
// ```
//    6   5   1   2   3   9   8
//    0   1   2   3   4   5   6   7   8   9
// ```

#include <stdio.h>

int Partition(int* L,int low,int high)
 { 
   int pivotkey;
   L[0]= L[low]; 
   pivotkey=L[low]; 
   printf("%4d",pivotkey);
   while(low< high)
   { // 从表的两端交替地向中间扫描
     while(low<high && L[high]>=pivotkey)
       --high;
     L[low]=L[high]; 
     while(  low<high && L[low]<=pivotkey)
       ++low;
     L[high]=L[low]; 
   }
   
    L[low]=L[0];
   return  low;
 }

 void QSort(int* L,int low,int high)
 { 
   int pivotloc;
   if(low<high)
   { 
     pivotloc=Partition(L,low,high); 
     QSort(L,low,pivotloc-1); 
     QSort(L,pivotloc+1,high); 
   }
 }

 void QuickSort(int* L,int length)
 { 
   QSort(L,1,length);
 }

int main(){
    int n;scanf("%d",&n);
    int arr[n+1];
    for(int i=1;i<=n;i++)
        scanf("%d",&arr[i]);
    QuickSort(arr,n);
    printf("\n");
    for(int i=1;i<=n;i++)
        printf("%4d",arr[i]);
    return 0;
}