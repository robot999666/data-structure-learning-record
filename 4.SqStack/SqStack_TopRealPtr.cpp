// 对于顺序栈，教材上采用了虚指的方式，即top所指向的不是真正的栈顶元素而是下一个要入栈的元素位置。
// 如果采用实指的方式，请写出顺序栈的入栈和出栈操作的实现。

#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE   100       //存储空间初始分配
#define STACKINCREMENT  10       //存储空间分配增量

typedef int Status;
#define TRUE 1
#define FALSE 0
#define  OK  1
#define  ERROR  0
#define  OVERFLOW -2

typedef int SElemType ;

typedef struct
{
SElemType* head;
SElemType* base;
SElemType* top;
int stacksize;
}SqStack;

//top实指的情况下，为了便于判空，top初始指向 栈底-1 位置，即base下面
Status InitStack(SqStack &s)
{s.head=(SElemType *)malloc((STACK_INIT_SIZE+1)*sizeof(SElemType));
 if (!s.head) exit(OVERFLOW);
 s.top=s.head;
 s.base=s.head+1;
 s.stacksize = STACK_INIT_SIZE;
 return OK;
}

Status StackEmpty(SqStack s) {
    return s.top < s.base ? TRUE : FALSE;
    //top实指的情况下，为了便于判空，top初始指向 栈底-1 位置，即base下面
}

Status Push(SqStack &s,SElemType e)
{
  if(s.top-s.base>=s.stacksize)
  {
   s.head = (SElemType*)realloc(s.head, (s.stacksize+STACKINCREMENT+1)*sizeof(SElemType));
   if(!s.head) exit(OVERFLOW); 
   s.base=s.head+1;
   s.top = s.base + s.stacksize-1;
   s.stacksize += STACKINCREMENT;
  }
  *(++s.top)=e;
  return OK;
}

Status Pop(SqStack &s,SElemType &e)
{ if(StackEmpty(s)) return ERROR;
  //top实指的情况下，为了便于判空，top初始指向 栈底-1 位置，即base下面
  e=*(s.top--);
  return OK;
}