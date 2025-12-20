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

#include <stdio.h>
#include <stdlib.h>

// 定义元素类型为字符
typedef char ElemType;

// 链表节点结构体
typedef struct LNode
{
    ElemType data;        // 节点数据
    struct LNode *next;   // 指向下一个节点
} LNode, *LinkList;

// 定义状态常量
typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

// 初始化链表
Status InitList(LinkList &L)
{
    L = (LinkList)malloc(sizeof(LNode));  // 分配头节点内存
    if (!L)
        return OVERFLOW;  // 内存分配失败
    L->next = NULL;       // 头节点next置空
    return OK;
}

// 获取链表长度
int ListLength(LinkList L)
{
    LinkList p = L->next;  // 从头节点下一个开始
    int len = 0;
    while (p)
    {
        p = p->next;  // 遍历节点
        len++;        // 计数
    }
    return len;
}

// 在链表第i个位置插入元素e
Status ListInsert(LinkList &L, int i, ElemType e)
{
    LinkList s = (LinkList)malloc(sizeof(LNode));  // 分配新节点
    s->data = e;
    s->next = NULL;
    LinkList p = L;  // 从头节点开始
    int j = 0;
    while (p && j < i - 1)  // 找到第i-1个节点
    {
        p = p->next;
        j++;
    }
    if (!p || j > i - 1)  // 如果位置不合法
    {
        free(s);  // 释放新节点
        return ERROR;
    }
    s->next = p->next;  // 插入新节点
    p->next = s;
    return OK;
}

// 获取链表第i个元素
Status GetElem(LinkList L, int i, ElemType &e)
{
    LinkList p = L->next;  // 从第一个数据节点开始
    int j = 0;
    while (p && j < i - 1)  // 遍历到第i个节点
    {
        p = p->next;
        j++;
    }
    if (!p || j > i - 1)  // 如果节点不存在
    {
        return ERROR;
    }
    e = p->data;  // 获取数据
    return OK;
}

// 查找元素e在链表中的位置
int LocateElem(LinkList L, ElemType e)
{
    LinkList p = L->next;  // 从第一个数据节点开始
    int j = 1;             // 位置从1开始
    while (p)
    {
        if (p->data == e)  // 如果找到匹配元素
        {
            return j;     // 返回位置
        }
        p = p->next;  // 继续遍历
        j++;
    }
    return ERROR;  // 未找到
}

// 计算两个链表的交集，以Lb为主
Status jiaoji(LinkList La, LinkList Lb, LinkList &Lc)
{
    LinkList pa = La->next;  // La的第一个数据节点
    LinkList pb = Lb->next;  // Lb的第一个数据节点
    InitList(Lc);            // 初始化结果链表Lc
    LinkList pc, pend = Lc;  // pc为新节点，pend为Lc的尾节点
    while (pb)               // 遍历Lb
    {
        int w = LocateElem(La, pb->data);  // 检查pb->data是否在La中
        if (w)  // 如果在La中
        {
            pc = (LinkList)malloc(sizeof(LNode));  // 分配新节点
            if (!pc)
                return OVERFLOW;
            pc->next = NULL;
            pc->data = pb->data;  // 设置数据
            pend->next = pc;      // 连接到尾节点
            pend = pc;            // 更新尾节点
        }
        pb = pb->next;  // 移动到Lb下一个节点
    }
    return OK;
}

// 销毁链表，释放内存
Status DestroyList(LinkList &L)
{
    LinkList p = L, q;
    while (p)
    {
        q = p->next;  // 保存下一个节点
        free(p);      // 释放当前节点
        p = q;
    }
    return OK;
}