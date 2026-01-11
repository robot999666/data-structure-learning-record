// 输入一个字符串，统计改字符串中出现的字符及其次数。要求用一个二叉排序树保存处理结果。输出时字符从小到大有序。

// 本题目要求完成函数InsertBiTree和InOrderTraverse

// 函数接口定义：
// Status InsertBiTree(BiTree &T,char ch);
// Status InOrderTraverse(BiTree T);
// 其中 T 和 ch 都是用户传入的参数。 T是一棵二叉排序树； ch 是一个字符。
// 函数InsertBiTree的功能是查找树 T中是否存有字符ch，有就个数加一，没有则新插入一个值为ch的结点。
// 函数InOrderTraverse完成对二叉树T的中序遍历，输出统计结果。

// 裁判测试程序样例：
// typedef struct ch
// { char zifu;  //字符
//   int count;   //个数
// }TElemType;

// //- - - - -二叉树的二叉链表存储表示- - - - -
// typedef  struct  BiTNode
// {  TElemType     data;              //需要定义 TElemType, 为char类型
//    struct BiTNode  *lchild, *rchild;   //左右孩子指针
// } BiTNode, *BiTree;

// /* 请在这里填写答案 */

// int main( )
// { BiTree tree=NULL;
//   int i;
//   char s[100];
//   scanf("%s",s);
//   for(i=0; s[i]; i++)
//      InsertBiTree(tree,s[i]);
//   InOrderTraverse(tree);
//   return 0;
// }
// 输入样例：
// bacadab
// 输出样例：
// a:3
// b:2
// c:1
// d:1

#include <stdio.h>
#include <stdlib.h>

typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef struct ch
{ char zifu;  //字符
  int count;   //个数
}TElemType;

//- - - - -二叉树的二叉链表存储表示- - - - -
typedef  struct  BiTNode
{  TElemType     data;              //需要定义 TElemType, 为char类型
   struct BiTNode  *lchild, *rchild;   //左右孩子指针
} BiTNode, *BiTree;

/* 请在这里填写答案 */

int main( )
{ BiTree tree=NULL;
  int i;
  char s[100];
  scanf("%s",s);
  for(i=0; s[i]; i++)
     InsertBiTree(tree,s[i]);
  InOrderTraverse(tree);
  return 0;
}

Status SearchBST(BiTree T,char ch,BiTree f,BiTree &p){
    if(!T) {p=f; return FALSE;}
    else if(ch==T->data.zifu) {p=T; return TRUE;}
    else if(ch<T->data.zifu) return SearchBST(T->lchild,ch,T,p);
    else return SearchBST(T->rchild,ch,T,p);
}

Status InsertBiTree(BiTree &T,char ch){
    BiTree p,s;
    if(!SearchBST(T,ch,NULL,p)){
        s=(BiTree)malloc(sizeof(BiTNode));
        s->data.zifu=ch;s->data.count=1;s->lchild=s->rchild=NULL;
        if(!p) T=s;
        else if(ch<p->data.zifu) p->lchild=s;
        else p->rchild=s;
        return TRUE;
    }
    else {p->data.count++;return FALSE;}
}

Status InOrderTraverse(BiTree T){
    if(T){
        InOrderTraverse(T->lchild);
        printf("%c:%d\n",T->data.zifu,T->data.count);
        InOrderTraverse(T->rchild);
    }
    return OK;
}