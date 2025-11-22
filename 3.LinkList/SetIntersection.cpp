// 用带头结点的单链表表示字符集合，用基本操作实现字符集合的交集(以第二个集合为主)。请先实现单链表的基本操作。

// 裁判测试程序样例：
// #include<stdio.h>
// #include <stdlib.h>

// typedef  char ElemType;
// typedef  struct  LNode
// {  ElemType       data;
//    struct  LNode  *next;
// }LNode, *LinkList;

// /* 你的程序将嵌在这里 */
// int main()
// {int i,j,len;
//  ElemType e;
//  LinkList La,Lb,Lc;
//  int m,n;        //分别存放两个集合初始长度
//  scanf("%d%d",&m,&n);  getchar();
//  InitList(La); InitList(Lb);           //建立两个空集
//  for(i=1; i<=m; i++)               //建立第一个集合
//   {scanf("%c",&e);  ListInsert(La,i,e);  }
//  getchar();
//  for(i=1; i<=n; i++)              //建立第二个集合
//   {scanf("%c",&e);
//   ListInsert(Lb,i,e);  }
//  jiaoji(La,Lb,Lc);                   //计算集合La、Lb的交集Lc
// //输出结果
//  len=ListLength(Lc);
//  for(i=1; i<=len; i++)
//   {GetElem(Lc,i,e); printf("%c",e);  }
//  //printf("\n");
//  DestroyList(La); DestroyList(Lb); DestroyList(Lc);      //销毁3个集合
//  return 0;
// }
// 输入样例：
// 3 5
// abc
// decbf
// 输出样例：
// cb

#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

/* 你的程序将嵌在这里 */
int main()
{
    int i, j, len;
    ElemType e;
    LinkList La, Lb, Lc;
    int m, n; // 分别存放两个集合初始长度
    scanf("%d%d", &m, &n);
    getchar();
    InitList(La);
    InitList(Lb);            // 建立两个空集
    for (i = 1; i <= m; i++) // 建立第一个集合
    {
        scanf("%c", &e);
        ListInsert(La, i, e);
    }
    getchar();
    for (i = 1; i <= n; i++) // 建立第二个集合
    {
        scanf("%c", &e);
        ListInsert(Lb, i, e);
    }
    jiaoji(La, Lb, Lc); // 计算集合La、Lb的交集Lc
    // 输出结果
    len = ListLength(Lc);
    for (i = 1; i <= len; i++)
    {
        GetElem(Lc, i, e);
        printf("%c", e);
    }
    // printf("\n");
    DestroyList(La);
    DestroyList(Lb);
    DestroyList(Lc); // 销毁3个集合
    return 0;
}

typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

Status InitList(LinkList &L)
{
    L = (LinkList)malloc(sizeof(LNode));
    if (!L)
        return OVERFLOW;
    L->next = NULL;
    return OK;
}
int ListLength(LinkList L)
{
    LinkList p = L->next;
    int len = 0;
    while (p)
    {
        p = p->next;
        len++;
    }
    return len;
}
Status ListInsert(LinkList &L, int i, ElemType e)
{
    LinkList s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = NULL;
    LinkList p = L;
    int j = 0;
    while (p && j < i - 1)
    {
        p = p->next;
        j++;
    }
    if (!p || j > i - 1)
    {
        free(s);
        return ERROR;
    }
    s->next = p->next;
    p->next = s;
    return OK;
}
Status GetElem(LinkList L, int i, ElemType &e)
{
    LinkList p = L->next;
    int j = 0;
    while (p && j < i - 1)
    {
        p = p->next;
        j++;
    }
    if (!p || j > i - 1)
    {
        return ERROR;
    }
    e = p->data;
    return OK;
}

int LocateElem(LinkList L, ElemType e)
{
    LinkList p = L->next;
    int j = 1;
    while (p)
    {
        if (p->data == e)
        {
            return j;
        }
        p = p->next;
        j++;
    }
    return ERROR;
}

Status jiaoji(LinkList La, LinkList Lb, LinkList &Lc)
{
    LinkList pa = La->next;
    LinkList pb = Lb->next;
    InitList(Lc);
    LinkList pc, pend = Lc;
    while (pb)
    {
        int w = LocateElem(La, pb->data);
        if (w)
        {
            pc = (LinkList)malloc(sizeof(LNode));
            if (!pc)
                return OVERFLOW;
            pc->next = NULL;
            pc->data = pb->data;
            pend->next = pc;
            pend = pc;
        }
        pb = pb->next;
    }
    return OK;
}
Status DestroyList(LinkList &L)
{
    LinkList p = L, q;
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    return OK;
}