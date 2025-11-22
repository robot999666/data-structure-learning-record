## 程序填空题

### Problem 1
两个有序链表合并过程中需要用到单链表的基本操作，请填空。
```c++
typedef  int Status;
typedef  int ElemType;

//–––––线性表的链式存储结构–––––
typedef  struct  LNode
{  ElemType       data;
  ____1____next;
}LNode, *LinkList;

//--------------基本操作-----------------
Status InitList_L(LinkList &L)
{ //建立一个空的链表，L为带头结点的单链表的头指针.
   L=____2____;   //生成头结点
   if(!L) return ERROR;
   L->next=____3____; 
     return OK;
} //InitList_L

Status ListInsert_L(LinkList &L, int i, ElemType e)
{//在带头结点的单线性链表L中第i个位置之前插入元素e
 LinkList p,s; int j;
 p = L; j = 0;
 while ( p && j<i-1 )
      { ____4____ }          //寻找第i-1个结点
 if  (!p||j>i-1)  return ERROR;     //i 小于1或者大于表长
 s = (LinkList )malloc(sizeof(LNode));   //生成新结点
 s->data = e; s->next = ____5____;                 //插入L中
 ____6____;
 return OK;
}//ListInsert_L

int LocateElem_L(LinkList L,ElemType e, Status (*compare)(ElemType,ElemType))
{ //在线性链表L中查找第1个值与e满足compare()的元素的位序
  //若找到,则返回其在L中的位序,否则返回0
 int i; LinkList p;
 i = 1;                                 //i的初值为第1个元素的位序
 p = ____7____;                         //p的初值为第1个元素的存储位置
 while(  ____8____ )
 {  ++i; p=p->next;}
 if (p) ____9____;
 else ____10____;
}//LocateElem_Sq

Status GetElem_L(LinkList L, int i, ElemType &e)
{ //L为带头结点的单链表的头指针.
  //当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR
 LinkList p; int j;
  ____11____; 
  ____12____; 
 while ( p&& j<i )
  {                   //顺指针向后查找,直到p指向第i个元素或p为空
   ____13____
  }
 if (!p||j>i)  return ERROR ;          //第i个元素不存在
 e = ____14____;                           //取第i个元素
 return OK;
} //GetElem_L

int ListEmpty_L(LinkList L)
{ if (____15____) return TRUE;
  else return FALSE;
}

int ListLength_L(LinkList L)
{LinkList p;
 int len=0;
 p=____16____;
 while(p)
 {
    ____17____
 }
 return len;
}

Status ListDelete_L(LinkList &L, int i,  ElemType &e)
{ // 在带头结点的单链线性表L中,删除第i个元素,并由e返回其值
 int j;
 LinkList p,q;
 p = L;  j = 0;
 while( ____18____ )
  { p = p->next; ++j; }      //寻找第i个元素,并令p指向其前驱
 if (!(p->next)||j>i-1)  return ERROR;   //删除位置不合理
 q = ____19____;   
 ____20____;             //删除并释放结点
 e = ____21____;
 free(q);
 return OK;
}
```

### Problem 2
已知顺序线性表 `La` 和 `Lb` 的元素按值非递减排列，合并 `La` 和 `Lb` 得到新的顺序线性表 `Lc` , `Lc` 的元素也按值非递减排列。线性表采用单链表的存储结构。
```c++
void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc)
{ //已知单链线性表La和Lb的元素按值非递减排列
//归并La和Lb得到新的单链线性表Lc,Lc的元素也按值非递减排列
  LinkList pa,pb,pc;
   pa = ____1____;  pb = ____2____;
  Lc = pc = La;                         //用La的头结点作为Lc的头结点
  while( ____3____ )
     if (pa->data<= pb->data)
      { ____4____ }
     else{ ____5____ }
   pc->next = ____6____;                   //插入剩余段
   free(Lb);                               //释放Lb的结点
}//MergeLis
```

## 程序填空题
1. 1. `struct LNode *`
   2. `(LinkList)malloc(sizeof(LNode))`
   3. `NULL`
   4. `p = p->next; ++j;`
   5. `p->next`
   6. `p->next = s`
   7. `L->next`
   8. `p && !compare(p->data, e)`
   9. `return i`
   10. `return ERROR`
   11. `p = L->next`
   12. `j = 1`
   13. `j++; p = p->next;`
   14. `p->data`
   15. `L->next == NULL`
   16. `L->next`
   17. `len++; p = p->next;`
   18. `p->next && j<i-1`
   19. `p->next`
   20. `p->next = q->next`
   21. `q->data`
2. 1. `La->next`
   2. `Lb->next`
   3. `pa && pb`
   4. `pc->next = pa; pc = pa; pa = pa->next;`
   5. `pc->next = pb; pc = pb; pb = pb->next;`
   6. `pa?pa:pb`