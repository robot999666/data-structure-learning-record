// 有n个旅客同乘一条船，因为船发生故障，最多只能留下一半旅客。大家议定如下办法：n个人围成一圈，由第一个人起，依次报数，报到m的人必须被扔进大海。如此循环。问最后哪些旅客仍留在船上？每个人都有一个m值，当他被扔进大海后，m的值改为这个人的m值。m的初值由第一个人决定。

// 输入格式:
// 输入共二行，第一行为人数n，第二行为n个整数，代表每个人的m值。

// 输出格式:
// 在一行中输剩下乘客的编号（用%3d格式输出）。

// 输入样例:
// 10
// 2 3 4 3 2 4 3 6 3 2
// 输出样例:
//   1  4  6  8  9

#include<stdio.h>
#include <stdlib.h>

typedef  int ElemType;

typedef  struct  LNode
{  ElemType   num;
   ElemType   m;
   struct  LNode  *next;
}LNode, *LinkList;

typedef  int Status;

#define TRUE 1
#define FALSE 0
#define  OK  1
#define  ERROR  0
#define  OVERFLOW -2

Status DestroyList(LinkList &L,int n){
    LinkList p=L,q;
    for(int i=0;i<n;i++){
       q=p->next;
       free(p);
       p=q;
   }
    return OK;
}

int main()
{
    LinkList L=NULL,end,cur,pre;
    ElemType m;
    int n,i=0;
    scanf("%d",&n);
    int N=n;
    while(++i<=n){
        cur=(LinkList)malloc(sizeof(LNode));
        scanf("%d",&m);
        cur->num=i;
        cur->m=m;
        cur->next=NULL;
        if(L==NULL){
            L=cur;
        }
        else{
            end->next=cur;
        }
        end=cur;
    }
    end->next=L;
    m=L->m;
    cur=L;pre=end;
   while(n>N/2){
       for(int i=1;i<m;i++){
           pre=cur;
           cur=cur->next;
       }
       m=cur->m;
       pre->next=cur->next;
       free(cur);
       cur=pre->next;
       n--;
   }
    L=cur;
   for(int i=0;i<n;i++){
       if(cur->num<L->num) L=cur;
       cur=cur->next;
   }
    cur=L;
   for(int i=0;i<n;i++){
       printf("%3d",cur->num);
       cur=cur->next;
   }
    DestroyList(L,n);
    return 0;
}