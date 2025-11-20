// 给定一系列正整数，请设计一个尽可能高效的算法，查找倒数第K个位置上的数字。

// 输入格式:
// 输入首先给出一个正整数K，随后是若干非负整数，最后以一个负整数表示结尾（该负数不算在序列内，不要处理）。

// 输出格式:
// 输出倒数第K个位置上的数据。如果这个位置不存在，输出错误信息NULL。

// 输入样例:
// 4 1 2 3 4 5 6 7 8 9 0 -1
// 输出样例:
// 7

#include<stdio.h>
#include <stdlib.h>

typedef  int ElemType;

typedef  struct  LNode
{  ElemType       data;
   struct  LNode  *next;
}LNode, *LinkList;

typedef  int Status;
#define TRUE 1
#define FALSE 0
#define  OK  1
#define  ERROR  0
#define  OVERFLOW -2

Status InitList(LinkList &L){
    L=(LinkList)malloc(sizeof(LNode));
    if(!L) return OVERFLOW;
    L->next=NULL;
    return OK;
}
Status GetElem(LinkList L,int i,ElemType &e){
    LinkList p=L->next;
    int j=0;
    while(p && j<i-1){
        p=p->next;j++;
    }
    if(!p || j>i-1) {
        return ERROR;
    }
    e=p->data;
    return OK;
}
Status DestroyList(LinkList &L){
    LinkList p=L,q;
    while(p){
        q=p->next;
        free(p);
        p=q;
    }
    return OK;
}
int main()
{
    LinkList L;
    InitList(L);
    ElemType x,y;
    int K;
    scanf("%d",&K);
    while(scanf("%d",&x)!=-1 && x>=0){
        LinkList node=(LinkList)malloc(sizeof(LNode));
        node->data=x;
        node->next=L->next;
        L->next=node;
    }
    if (GetElem(L,K,y))
        printf("%d",y);
    else
         printf("NULL");
    DestroyList(L);
    return 0;
}