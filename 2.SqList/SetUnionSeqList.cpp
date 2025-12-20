// 用顺序结构线性表存放整数集合，请用SqList的基本操作实现整数集合的并集
// (1)需要定义用到的宏名（符号常量），如OK、OVERFLOW等
// (2)需要定义类型标识符Status
// (3)需要定义以下函数
// Status InitList_Sq(SqList  &L);
// int ListLength_Sq(SqList L);
// Status GetElem_Sq(SqList L,int i, ElemType &e);
// Status ListInsert_Sq(SqList &L,int i,ElemType e);
// int equal(ElemType x,ElemType  y);   //比较x与y是否相等
// int LocateElem_Sq(SqList L,ElemType e, Status (*compare)(ElemType,ElemType));
// void union_Sq(SqList La,SqList Lb,SqList &Lc);  //线性表La、Lb分别表示集合A、B，C=A∪B
// 裁判测试程序样例：
// 在这里给出函数被调用进行测试的例子。例如：
// #include<stdio.h>
// #include <stdlib.h>

// typedef  int ElemType;
// #define LIST_INIT_SIZE    30 //线性表存储空间的初始分配
// #define LISTINCREMENT     10  //线性表存储空间的分配增量
//  typedef   struct {
//   ElemType   *elem;    //存储空间基址
//   int        length;   //当前长度
//   int        listsize; //当前分配的存储容量(以sizeof(ElemType)为单位)
//  }SqList;

// /* 你的程序将嵌在这里 */

// int main( )
// {int i,j,len;
//  int m,n;   //分别存放两个集合初始长度
//  ElemType e;
//  SqList La,Lb,Lc;
//  scanf("%d%d",&m,&n);
//  InitList_Sq(La); InitList_Sq(Lb);  //建立两个空集
//  for(i=1; i<=m; i++)  //建立第一个集合
//   {scanf("%d",&e);  ListInsert_Sq(La,i,e);  }
//  for(i=1; i<=n; i++)  //建立第二个集合
//   {scanf("%d",&e);   ListInsert_Sq(Lb,i,e);  }
//  union_Sq(La,Lb,Lc);  //计算集合La、Lb的并集Lc
//  len=ListLength_Sq(Lc);
//  for(i=1; i<=len; i++) //输出
//   {GetElem_Sq(Lc,i,e); printf("%4d",e);  }
//  return 0;
// }
// 输入样例：
// 4 5
// 3 2 5 7
// 4 5 7 9 21
// 输出样例
//    3   2   5   7   4   9  21

// 顺序表集合并集运算程序
// 输入：两个集合长度及元素，计算La ∪ Lb
// 输出：并集元素
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
#define LIST_INIT_SIZE 30 // 线性表存储空间的初始分配
#define LISTINCREMENT 10  // 线性表存储空间的分配增量
// 顺序表结构体
typedef struct
{
  ElemType *elem; // 存储空间基址
  int length;     // 当前长度
  int listsize;   // 当前分配的存储容量(以sizeof(ElemType)为单位)
} SqList;

/* 你的程序将嵌在这里 */

int main()
{
  int i, j, len;
  int m, n; // 分别存放两个集合初始长度
  ElemType e;
  SqList La, Lb, Lc;
  scanf("%d%d", &m, &n);
  InitList_Sq(La);
  InitList_Sq(Lb);         // 建立两个空集
  for (i = 1; i <= m; i++) // 建立第一个集合
  {
    scanf("%d", &e);
    ListInsert_Sq(La, i, e);
  }
  for (i = 1; i <= n; i++) // 建立第二个集合
  {
    scanf("%d", &e);
    ListInsert_Sq(Lb, i, e);
  }
  union_Sq(La, Lb, Lc); // 计算集合La、Lb的并集Lc
  len = ListLength_Sq(Lc);
  for (i = 1; i <= len; i++) // 输出
  {
    GetElem_Sq(Lc, i, e);
    printf("%4d", e);
  }
  return 0;
}

typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
Status InitList_Sq(SqList &L)
{
  L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
  if (!L.elem)
    exit(OVERFLOW);
  L.length = 0;
  L.listsize = LIST_INIT_SIZE;
  return OK;
} // InitList_Sq      算法2.3

int ListLength_Sq(SqList L)
{
  return L.length;
}

Status GetElem_Sq(SqList L, int i, ElemType &e)
{
  if (i < 1 || i > L.length)
    return ERROR;
  e = L.elem[i - 1];
  return OK;
}

Status ListInsert_Sq(SqList &L, int i, ElemType e)
{ //  在顺序线性表L中第i个位置之前插入新的元素e,
  //  i的合法值为1≤i≤ListLength_Sq(L)+1
  ElemType *newbase, *p, *q;
  if (i < 1 || i > L.length + 1)
    return ERROR;             // i 值不合法
  if (L.length >= L.listsize) // 当前存储空间已满,增加分配
  {
    newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
    if (!newbase)
      exit(OVERFLOW);            // 存储分配失败
    L.elem = newbase;            //  新基址
    L.listsize += LISTINCREMENT; //  增加存储容量
  }
  q = &L.elem[i - 1]; // q为插入位置
  if (L.length >= 1)
    for (p = &L.elem[L.length - 1]; p >= q; --p)
      *(p + 1) = *p;
  *q = e; // 插入e
  L.length++;
  return OK;
} // ListInsert_Sq

int LocateElem_Sq(SqList L, ElemType e, Status (*compare)(ElemType, ElemType))
{
  int i;
  ElemType *p;
  i = 1;
  p = L.elem; // p的初值为第1个元素的存储位置
  while (!(*compare)(e, *p++) && i <= L.length)
    ++i;
  if (i <= L.length)
    return 1;
  else
    return 0;
} // LocateElem_Sq

int equal(ElemType x, ElemType y)
{
  return x == y ? 1 : 0;
} // 比较x与y是否相等

void union_Sq(SqList La, SqList Lb, SqList &Lc)
{
  int La_len = La.length;
  int Lb_len = Lb.length;
  ElemType e;
  Lc = La;
  for (int i = 0; i < Lb_len; i++)
  {
    GetElem_Sq(Lb, i + 1, e);
    if (!LocateElem_Sq(Lc, e, equal))
      ListInsert_Sq(Lc, ++La_len, e);
  }
} // 线性表La、Lb分别表示集合A、B，C=A∪B