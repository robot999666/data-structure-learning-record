// n个自然数的入栈顺序为1,2,....n, 输入一个出栈序列,判断其是否是一个合法的出栈序列。n<10。

// 输入格式:
// 输入共二行，第一行中给出正整数n。
// 第二行给出n个用空格隔开的正整数，表示一个出栈序列

// 输出格式:
// 如果是一个合法的出栈序列输出yes，否则输出no。

// 输入样例1:
// 3
// 3 2 1
// 输出样例1:
// yes
// 输入样例2:
// 3
// 3 1  2
// 输出样例1:
// no

#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100 // 存储空间初始分配
#define STACKINCREMENT 10   // 存储空间分配增量
typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int SElemType;

typedef struct
{
  SElemType *base;
  SElemType *top;
  int stacksize;
} SqStack;

Status InitStack(SqStack &s)
{
  s.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
  if (!s.base)
    exit(OVERFLOW); // 存储分配失败

  s.top = s.base;
  s.stacksize =
      STACK_INIT_SIZE;
  return OK;
}

Status GetTop(SqStack s, SElemType &e)
{
  if (
      s.base == s.top)
    return ERROR;
  e =
      *(s.top - 1);
  return OK;
}

Status Push(SqStack &s, SElemType e)
{ // 插入元素e为新的栈顶元素
  if (s.top - s.base >= s.stacksize)
  { // 栈满,追加存储空间
    s.base = (SElemType *)realloc(s.base, (s.stacksize + STACKINCREMENT) * sizeof(SElemType));
    if (!s.base)
      exit(OVERFLOW); // 存储分配失败
    s.top = s.base + s.stacksize;
    s.stacksize += STACKINCREMENT;
  }

  *s.top++ = e;
  return OK;
}

Status Pop(SqStack &s, SElemType &e)
{
  if (s.top == s.base)
    return ERROR;
  e =
      *(--s.top);
  return OK;
}

Status StackEmpty(SqStack s)
{
  if (s.top == s.base)
    return OK;
  else
    return ERROR;
}

int main()
{
  SqStack s;
  InitStack(s);
  int i, index = 0, t;
  int n;
  scanf("%d", &n);
  int outline[n];
  for (i = 0; i < n; i++)
    scanf("%d", &outline[i]);
  for (i = 1; i <= n; i++)
  {
    Push(s, i);
    while (!StackEmpty(s) && outline[index] == *(s.top - 1))
    {
      Pop(s, t);
      index++;
    }
  }
  if (StackEmpty(s))
    printf("yes");
  else
    printf("no");
  return 0;
}