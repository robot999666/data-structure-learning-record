## 程序填空题

### Problem 1
本题目比较两个顺序表的大小，需要用到顺序表的基本操作，请填空。
```c++
#include <stdio.h>
#include <stdlib.h>

typedef  int Status;
typedef  int ElemType;

#define TRUE 1
#define FALSE 0
#define  OK  1
#define  ERROR  -1
#define  OVERFLOW -2

typedef  int Status;
typedef  int ElemType;

//–––––线性表的动态分配顺序存储结构–––––
 #define LIST_INIT_SIZE    30  //线性表存储空间的初始分配
 #define LISTINCREMENT     10  //线性表存储空间的分配增量
 typedef   struct {
  ElemType   *elem;      //存储空间基址
  int        length;     //当前长度
  int        listsize;   //当前分配的存储容量(以sizeof(ElemType)为单位)
 }SqList;

//--------------基本操作-----------------
 Status InitList_Sq(SqList  &L)
 { L.elem=____1____;//(ElemType*)malloc(sizeof(LISt_INIT_SIZE*sizeof(ElemType)))
   if(!L.elem)exit(OVERFLOW);
   L.length=____2____;//0
   L.listsize=LIST_INIT_SIZE;
   return OK;
 }//InitList_Sq      算法2.3

int ListLength_Sq(SqList L)
{____3____;//return L.length
}

Status GetElem_Sq(SqList L,int i, ElemType &e)
{ if(____4____) return ERROR;//i<1||i>L.length
  e=____5____;//L.elem[i-1]
  return OK;
}

Status ListInsert_Sq(SqList &L,int i,ElemType e)
 {//  在顺序线性表L中第i个位置之前插入新的元素e,
  //  i的合法值为1≤i≤ListLength_Sq(L)+1
   ElemType *newbase,*p,*q;
   if (i<1||i>L.length+1) return ERROR;     //i 值不合法
   if (L.length>=L.listsize)                //当前存储空间已满,增加分配
     { newbase=(ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
      if(!newbase)exit(OVERFLOW);           //存储分配失败
      L.elem=newbase;                       //新基址
      L.listsize +=LISTINCREMENT;           //增加存储容量
    }
   q = ____6____;   //&L.elem[i-1]         //q为插入位置
   if(L.length>=1)
     for(p=____7____;p>=q;--p) //&L.elem[L.length]
           ____8____;  //*p=*(p-1)
   *q=e;                          //插入e
  ____9____;//L.length++
   return OK;
 }//ListInsert_Sq

int LocateElem_Sq(SqList L,ElemType e, Status (*compare)(ElemType,ElemType))
{
 int i; ElemType *p;
 i = 1;
 p = L.elem;                                  //p的初值为第1个元素的存储位置
 while(____10____) ++i;
 if (i<=L.length)  ____11____;
 else return 0;
}//LocateElem_Sq
```

### Problem 2
已知顺序线性表 `La` 和 `Lb` 的元素按值非递减排列，合并 `La` 和 `Lb` 得到新的顺序线性表 `Lc` , `Lc` 的元素也按值非递减排列。
```c++
void MergeList_Sq(SqList La,SqList Lb, SqList &Lc)
{ int i,j,k;
  int La_len,Lb_len;
  ElemType ai,bj;
  ____1____;
  i=j=1;k=0;
  La_len=____2____;
  Lb_len=____3____;
  while( ____4____ )        //La和Lb均为空
   { GetElem_Sq(La,i,ai);GetElem_Sq(Lb,j,bj);
     if(ai<=bj) {____5____;++i;}
     else{____6____;++j;}
   }
  while(i<=La_len)
   { ____7____}
  while(j<=Lb_len)
   {____8____ }
}
```

### Problem 3
已知顺序线性表 `La` 和 `Lb` 的元素按值非递减排列，合并 `La` 和 `Lb` 得到新的顺序线性表 `Lc` , `Lc` 的元素也按值非递减排列。
```c++
void MergeList_Sq(SqList La,SqList Lb, SqList &Lc)
{ElemType *pa,*pb,*pc,*pa_last,*pb_last;
 pa = ____1____;
 pb = ____2____;
 Lc.listsize = Lc.length = La.length + Lb.length;
 pc = Lc.elem =(ElemType *)malloc(Lc.listsize * sizeof(ElemType));
 if (!Lc.elem) exit(OVERFLOW);            //存储分配失败
 ____3____ = La.elem + La.length - 1;
 ____4____ = Lb.elem + Lb.length - 1;
 while (pa<=pa_last && pb<=pb_last)       //归并
  {if ( *pa<= *pb) ____5____;
   else ____6____;
  }
 while(____7____)  *pc++=*pa++;
 while(____8____)  *pc++=*pb++;
}
```

## 程序填空题
1. 1. `(ElemType *)malloc(sizeof(LIST_INIT_SIZE*sizeof(ElemType)))`
   2. `0`
   3. `return L.length`
   4. `i<1||i>L.length`
   5. `L.elem[i-1]`
   6. `&L.elem[i-1]`
   7. `&L.elem[L.length]`
   8. `*p = *(p-1)`
   9. `L.length++`
   10. `i<=L.length && !(*compare)(*p++,e)`
   11. `return i`
2. 1. `InitList_Sq(Lc)`
   2. `La.length`
   3. `Lb.length`
   4. `(i<=La_len) && (j<=Lb_len)`
   5. `ListInsert_Sq(Lc, ++k, ai)`
   6. `ListInsert_Sq(Lc, ++k, bj)`
   7. `GetElem_Sq(La, i++, ai); ListInsert_Sq(Lc, ++k, ai);`
   8. `GetElem_Sq(Lb, j++, bj); ListInsert_Sq(Lc, ++k, bj);`
3. 1. `La.elem`
   2. `Lb.elem`
   3. `pa_last`
   4. `pb_last`
   5. `*pc++ = *pa++`
   6. `*pc++ = *pb++`
   7. `pa <= pa_last`
   8. `pb <= pb_last`