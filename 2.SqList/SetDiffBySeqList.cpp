// 本题的集合元素是字符串，请完善程序，实现字符串集合的差集运算。
// 函数接口定义：

// ### 裁判测试程序样例：
// ```c++
// 这里给出主函数，其他程序需要你编写。

// #include<stdio.h>
// #include <stdlib.h>
// #include<string.h>

// typedef char ElemType[20];

// /* 你的程序将嵌在这里 */

// int main()
// {int i,j,len;
//  ElemType e;
//  SqList La,Lb,Lc;
//  int m,n;   //分别存放两个集合初始长度
//  printf("input the length of two set:\n");
//  scanf("%d%d",&m,&n);
//  InitList_Sq(La); InitList_Sq(Lb);   //建立两个空集
//  printf("input the first set:\n ");
//  for(i=0; i<m; i++)  //建立第一个集合
//   {scanf(" %s",e);  ListInsert_Sq(La,i+1,e);  }  //注意有空格
//  printf("input the second set:\n ");
//  for(i=1; i<=n; i++)  //建立第二个集合
//   {scanf(" %s",e);   ListInsert_Sq(Lb,i,e);  }  //注意有空格
//  chaji_Sq(La,Lb,Lc);  //计算集合La、Lb的差集Lc
//  printf("the chaji set is:\n");
//  len=ListLength_Sq(Lc);
//  for(i=1; i<=len; i++)
//   {GetElem_Sq(Lc,i,e); printf("%s\n",e);  }
//  DestroyList_Sq(La); DestroyList_Sq(Lb); DestroyList_Sq(Lc); //销毁3个集合（顺序表）
//  return 0;
// }

// 输入样例：
// 4  5
// abc
// def
// kkkkkk
// defg
// aaa
// def
// hjklm
// abc
// ckjggg

// 输出样例：
// kkkkkk
// defg

// 顺序表集合差集运算程序
// 输入：两个集合长度及元素，计算La - Lb
// 输出：差集元素
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char ElemType[20];

/* 你的程序将嵌在这里 */

int main()
{
  int i, j, len;
  ElemType e;
  SqList La, Lb, Lc;
  int m, n; // 分别存放两个集合初始长度
  printf("input the length of two set:\n");
  scanf("%d%d", &m, &n);
  InitList_Sq(La);
  InitList_Sq(Lb); // 建立两个空集
  printf("input the first set:\n ");
  for (i = 0; i < m; i++) // 建立第一个集合
  {
    scanf(" %s", e);
    ListInsert_Sq(La, i + 1, e);
  } // 注意有空格
  printf("input the second set:\n ");
  for (i = 1; i <= n; i++) // 建立第二个集合
  {
    scanf(" %s", e);
    ListInsert_Sq(Lb, i, e);
  } // 注意有空格
  chaji_Sq(La, Lb, Lc); // 计算集合La、Lb的差集Lc
  printf("the chaji set is:\n");
  len = ListLength_Sq(Lc);
  for (i = 1; i <= len; i++)
  {
    GetElem_Sq(Lc, i, e);
    printf("%s\n", e);
  }
  DestroyList_Sq(La);
  DestroyList_Sq(Lb);
  DestroyList_Sq(Lc); // 销毁3个集合（顺序表）
  return 0;
}

typedef int Status;
// 状态宏定义
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define LIST_INIT_SIZE 30 // 线性表存储空间的初始分配
#define LISTINCREMENT 10  // 线性表存储空间的分配增量
// 顺序表结构体
typedef struct
{
  ElemType *elem; // 存储空间基址
  int length;     // 当前长度
  int listsize;   // 当前分配的存储容量(以sizeof(ElemType)为单位)
} SqList;
// 初始化顺序表
Status InitList_Sq(SqList &L)
{
  L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
  if (!L.elem)
    exit(OVERFLOW);
  L.length = 0;
  L.listsize = LIST_INIT_SIZE;
  return OK;
} // InitList_Sq      算法2.3

// 获取顺序表长度
int ListLength_Sq(SqList L)
{
  return L.length;
}

// 获取指定位置元素
Status GetElem_Sq(SqList L, int i, ElemType &e)
{
  if (i < 1 || i > L.length)
    return ERROR;
  strcpy(e, L.elem[i - 1]);
  return OK;
}

// 插入元素到顺序表
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
      strcpy(*p, *(p - 1));
  strcpy(*q, e); // 插入e
  L.length++;
  return OK;
} // ListInsert_Sq

// 查找元素位置
int LocateElem_Sq(SqList L, ElemType e, Status (*compare)(ElemType, ElemType))
{
  int i;
  ElemType *p;
  i = 1;
  p = L.elem; // p的初值为第1个元素的存储位置
  while (!(*compare)(e, *p++) && i <= L.length)
    ++i;
  if (i <= L.length)
    return i;
  else
    return 0;
} // LocateElem_Sq

// 比较函数
int equal(ElemType x, ElemType y)
{
  return !strcmp(x, y) ? 1 : 0;
} // 比较x与y是否相等

// 删除指定位置元素
Status ListDelete_Sq(SqList &L, int i)
{ //  i的合法值为1≤i≤ListLength_Sq(L)
  if (i < 1 || i > L.length)
    return ERROR; // i 值不合法
  ElemType *p, *q;
  q = &L.elem[i - 1];
  if (L.length >= 1)
    for (p = q; p <= &L.elem[L.length - 1]; ++p)
      strcpy(*p, *(p + 1));
  L.length--;
  return OK;
}

// 计算集合差集
void chaji_Sq(SqList La, SqList Lb, SqList &Lc)
{
  int index;
  int Lb_len = Lb.length;
  ElemType e;
  InitList_Sq(Lc);
  for (int i = 0; i < La.length; i++)
  {
    strcpy(e, La.elem[i]);
    ListInsert_Sq(Lc, i + 1, e);
  }
  for (int i = 0; i < Lb_len; i++)
  {
    GetElem_Sq(Lb, i + 1, e);
    if ((index = LocateElem_Sq(Lc, e, equal)) != 0)
      ListDelete_Sq(Lc, index);
  }
}

// 销毁顺序表
Status DestroyList_Sq(SqList &L)
{
  if (!L.elem)
    return ERROR;
  free(L.elem);
  L.elem = NULL;
  L.length = 0;
  L.listsize = 0;
  return OK;
}