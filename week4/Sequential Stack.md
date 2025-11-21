## 程序填空题

### Problem 1
```c++
#define STACK_INIT_SIZE   100       //存储空间初始分配
#define STACKINCREMENT  10       //存储空间分配增量
typedef int Status;

typedef struct
{____1____;
 ____2____;
 int stacksize;
}SqStack;

Status InitStack(SqStack &s)
{s.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
 if (!s.base) exit(OVERFLOW);            //存储分配失败
 ____3____;
 s.stacksize = ____4____;
 return OK;
}

Status GetTop(SqStack s, SElemType &e)
{ if(____5____) return ERROR;
  e=____6____;
  return OK;
}

Status Push(SqStack &s,SElemType e)
{//插入元素e为新的栈顶元素
  if(s.top-s.base>=____7____)
  {//栈满,追加存储空间
   s.base = (SElemType*)realloc(s.base, (s.stacksize+STACKINCREMENT)*sizeof(SElemType));
   if(!s.base)exit(OVERFLOW);           //存储分配失败
   s.top = s.base + s.stacksize;
   s.stacksize +=STACKINCREMENT;
  }
  ____8____;
  return OK;
}

Status Pop(SqStack &s,SElemType &e)
{ if(____9____) return ERROR;
  e=____10____;
  return OK;
}
Status StackEmpty(SqStack s)
{ if(____11____) return OK;
  else return ERROR;
}
```

1. 1. `SElemType *base`
   2. `SElemType *top`
   3. `s.top = s.base`
   4. `STACK_INIT_SIZE`
   5. `s.top == s.base`
   6. `*(s.top - 1)`
   7. `s.stacksize`
   8. `*s.top++ = e`
   9. `s.top == s.base`
   10. `*(--s.top)`
   11. `s.top == s.base`