// 给定一个带整数键值的链表 L，你需要把其中绝对值重复的键值结点删掉。即对每个键值 K，只有第一个绝对值等于 K 的结点被保留。同时，所有被删除的结点须被保存在另一个链表上。例如给定 L 为 21→-15→-15→-7→15，你需要输出去重后的链表 21→-15→-7，还有被删除的链表 -15→15。

// 输入格式：
// 输入在第一行给出 L 的第一个结点的地址和一个正整数 N（≤10^5，为结点总数）。一个结点的地址是非负的 5 位整数，空地址 NULL 用 -1 来表示。

// 随后 N 行，每行按以下格式描述一个结点：

// 地址 键值 下一个结点
// 其中地址是该结点的地址，键值是绝对值不超过10^4的整数，下一个结点是下个结点的地址。

// 输出格式：
// 首先输出去重后的链表，然后输出被删除的链表。每个结点占一行，按输入的格式输出。

// 输入样例：
// 00100 5
// 99999 -7 87654
// 23854 -15 00000
// 87654 15 -1
// 00000 -15 99999
// 00100 21 23854

#include<stdio.h>
#include <stdlib.h>
#include <math.h>

typedef  int ElemType;

typedef  struct  LNode
{  ElemType   data;
   int   add;
   int   next;
}LNode, *LinkList;

typedef  int Status;
#define TRUE 1
#define FALSE 0
#define  OK  1
#define  ERROR  0
#define  OVERFLOW -2

int main()
{
    int N,head,ind,cur;
    int p[100000];
    int repeat[100000] = {0}; 
    scanf("%d %d",&head,&N);
    if (head == -1) {
        return 0;
    }
    LNode L[N],L1[N],L2[N];
    int len1=0,len2=0;
    for(int i=0;i<N;i++){
        scanf("%d %d %d",&L[i].add,&L[i].data,&L[i].next);
        p[L[i].add] = i;
    }
    cur=head;
    while(cur!=-1){
        ind=p[cur];
        int key=abs(L[ind].data);
        int flag=0;
        if(repeat[key]==0)
        {
            repeat[key]=1;
            L1[len1++]=L[ind];
        }
        else{
             L2[len2++]=L[ind];
        }
        cur=L[ind].next;
    }
    for(int k=1;k<len1;k++){
        L1[k-1].next=L1[k].add;
    }
    if (len1>0) L1[len1-1].next=-1;
    for(int k=1;k<len2;k++){
        L2[k-1].next=L2[k].add;
    }
    if (len2>0) L2[len2-1].next=-1;
    int k;
    if (len1>0)
    {for(k=0;k<len1-1;k++){
        printf("%05d %d %05d\n",L1[k].add,L1[k].data,L1[k].next);
    }
    printf("%05d %d %d\n",L1[k].add,L1[k].data,L1[k].next);}
    if (len2>0)
    {for(k=0;k<len2-1;k++){
        printf("%05d %d %05d\n",L2[k].add,L2[k].data,L2[k].next);
    }
    printf("%05d %d %d\n",L2[k].add,L2[k].data,L2[k].next);}
    return 0;
}
