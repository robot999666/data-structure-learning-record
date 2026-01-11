## 程序填空题

### Problem 1
本题目要求实现直接插入排序算法,请填空。
```c++
void InsertSort(SqList &L)
{ // 对顺序表L作直接插入排序
  int i,j;
  for(i=____1____;i<=L.length;++i)
    if LT(L.r[i].key,L.r[i-1].key) // "<",需将L.r[i]插入有序子表
    {
      L.r[0]=____2____; // 复制为哨兵
      for(j=i-1;LT(L.r[0].key,L.r[j].key);--j)
      ____3____ ; // 记录后移
    ____4____ ; // 插入到正确位置
    }
}
```

### Problem 2
本题目要求实现希尔排序算法,请填空。

输入格式:  
输入首先给出一个正整数 `N (≤500)` 表示待排序数据个数；接下来一行给出 `N` 个整数。整数间以空格分隔。

输出格式:  
在一行内按非递减顺序输出 `N` 个整数，整数间以空格分隔，但结尾不得有多余空格。

输入样例:
```
10
5 24 6 9 12 3 16 2 5 3
3 5 3 1
```
输出样例:
```
第1趟排序结果:
3 16 2 5 3 5 24 6 9 12
第2趟排序结果:
3 3 2 5 6 5 12 16 9 24
第3趟排序结果:
2 3 3 5 5 6 9 12 16 24
```
```c++
void ShellInsert(SqList &L,int dk)
{ // 对顺序表L作一趟希尔插入排序。
  int i,j;
  for(i=____1____;i<=L.length;++i)
    if LT(L.r[i].key,____2____)
    { // 需将L.r[i]插入有序增量子表
      L.r[0]=____3____; // 暂存在L.r[0]
      for(j= ____4____ ;j>0&&LT(L.r[0].key,L.r[j].key); ____5____ )
      ____6____ ; // 记录后移，查找插入位置
      ____7____ =L.r[0]; // 插入
    }
}
void ShellSort(SqList &L,int dlta[],int t)
{ // 按增量序列dlta[0..t-1]对顺序表L作希尔排序。算法10.5
  int k;
  for(k=0;k<t;++k)
  {
    ShellInsert(L,dlta[k]); // 一趟增量为dlta[k]的插入排序
    printf("第%d趟排序结果:\n",k+1);
    print(L);
  }
}
```

### Problem 3
本题目要求实现快速排序算法,请填空。
```c++
int Partition(SqList &L,int low,int high)
{ // 交换顺序表L中子表r[low..high]的记录，枢轴记录到位，并返回其
  // 所在位置，此时在它之前（后）的记录均不大（小）于它。算法10.6(b)
  KeyType pivotkey;
  L.r[0]= ____1____ ; 
  pivotkey=____2____ ; 
  while(low< high)
  { // 从表的两端交替地向中间扫描
    while( ____3____ )
      --high;
    L.r[low]=L.r[high]; 
    while( ____4____ )
      ++low;
    L.r[high]=L.r[low]; 
  }
  ____5____ ; 
  return  ____6____ ;
}

void QSort(SqList &L,int low,int high)
{ // 对顺序表L中的子序列L.r[low..high]作快速排序。算法10.7
  int pivotloc;
  if(low<high)
  { // 长度大于1
    pivotloc=Partition(L,low,high); // 将L.r[low..high]一分为二
    QSort( ____7____ ); // 对低子表递归排序，pivotloc是枢轴位置
    QSort( ____8____ ); // 对高子表递归排序
  }
}

void QuickSort(SqList &L)
{ // 对顺序表L作快速排序。算法10.8
  QSort(L,1,L.length);
}
```

### Problem 4
本题目要求实现堆排序算法，将一组数据从小到大排序,请填空。
```c++
typedef SqList HeapType; // 堆采用顺序表存储表示

 void HeapAdjust(HeapType &H,int s,int m) // 算法10.10
 { // 已知H.r[s..m]中记录的关键字除H.r[s].key之外均满足堆的定义，本函数
   // 调整H.r[s]的关键字,使H.r[s..m]成为一个大顶堆(对其中记录的关键字而言)
   RedType rc;
   int j;
   rc=H.r[s];
   for(j= ____1____ ;  j<=m; ____2____ )
   { 
     if( ____3____ )
       ++j; // j为key较大的记录的下标
     if(!LT(rc.key,H.r[j].key))
       break; // rc应插入在位置s上
     ____4____ ;
     s=j ;
   }
  ____5____; // 插入
 }

 void HeapSort(HeapType &H)
 { // 对顺序表H进行堆排序。算法10.11
   RedType t;
   int i;
   for(i=____6____ ;  i>0 ;  --i  ) // 把H.r[1..H.length]建成大顶堆
     HeapAdjust(H,i,H.length);
   for(i= ____7____ ; i>1  ;  --i  )
   { 
     t=H.r[1];
     H.r[1]=____8____ ;
     ____9____ =t;
     ____10____ ; // 将H.r[1..i-1]重新调整为大顶堆
   }
 }
```

## 程序填空题
1. 1. `2`
   2. `L.r[i]`
   3. `L.r[j+1]=L.r[j]`
   4. `L.r[j+1]=L.r[0]`
2. 1. `dk+1`
   2. `L.r[i-dk].key`
   3. `L.r[i]`
   4. `i-dk`
   5. `j-=dk`
   6. `L.r[j+dk]=L.r[j]`
   7. `L.r[j+dk]`
3. 1. `L.r[low]`
   2. `L.r[low].key`
   3. `low<high && L.r[high].key>=pivotkey`
   4. `low<high && L.r[low].key<=pivotkey`
   5. `L.r[low]=L.r[0]`
   6. `low`
   7. `L, low, pivotloc-1`
   8. `L, pivotloc+1, high`
4. 1. `2*s`
   2. `j*=2`
   3. `j<m && LT(H.r[j].key, H.r[j+1].key)`
   4. `H.r[s]=H.r[j]`
   5. `H.r[s]=rc`
   6. `H.length/2`
   7. `H.length`
   8. `H.r[i]`
   9. `H.r[i]`
   10. `HeapAdjust(H, 1, i-1)`