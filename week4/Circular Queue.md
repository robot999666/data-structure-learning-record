## 程序填空题

### Problem 1
本题目要求实现循环队列的基本操作，请填空。
```c++
//–––––循环队列──队列的顺序存储结构–––––
#define MAXQSIZE   100      //最大队列长度
typedef  struct
{____1____ base;   //初始化的动态分配存储空间
 ____2____ front;  //头指针,若队列不空,指向队列头元素
 ____3____ rear;   //尾指针,若队列不空,指向队列尾元素的下一个位置
}SqQueue;
Status InitQueue(SqQueue &Q)
{//  构造一个空队列Q
  Q.base = ____4____;
  if (!Q.base)  exit(OVERFLOW);  //存储分配失败
  Q.front = ____5____;
  Q.rear = ____6____;
  return OK;
}
int QueueLength(SqQueue Q)
{//返回Q的元素个数,即队列的长度
  return ____7____ ;
}
Status EnQueue(SqQueue &Q,QElemType e)
{// 插入元素e为Q的新的队尾元素
   if( ____8____ )   //队列满
        return ERROR;                                      
   ____9____=e;
   ____10____;
   return OK;
}
Status DeQueue(SqQueue &Q, QElemType &e)
{// 删除队头元素，送给变量e
  if( ____11____ ) return ERROR;   //队列空
  e= ____12____ ;
  ____13____;
  return OK;
}
Status QueueEmpty(SqQueue Q)
{ if( ____14____ ) return TRUE;
  return FALSE;
}
```

### Problem 2
```c++
typedef  int  Status;
typedef char QElemType;

//–––––队列的链式存储结构–––––
typedef  struct QNode
{QElemType     data;
 struct QNode   *next;
}QNode, *QueuePtr;

typedef struct
{  ____1____  front;      //队头指针
   ____2____  rear;       //队尾指针
}LinkQueue;

Status InitQueue(LinkQueue &Q)
{// 构造一个空队列Q
 Q.front = Q.rear = ____3____ ;
 if(!Q.front) exit(OVERFLOW);     //存储分配失败
 ____4____;
 return OK;
}

Status DestroyQueue(LinkQueue &Q)
{// 销毁队列Q
while(Q.front)
 { Q.rear = Q.front->next;
   ____5____;
   Q.front = ____6____;
 }
return OK;
}

int QueueLength(LinkQueue Q)
{//返回Q的元素个数,即队列的长度
  QueuePtr p;
  int len=0;
  p=____7____;
  while(____8____)
  {
      len++;
     ____9____;
  }
  return len;
}
Status EnQueue(LinkQueue &Q, QElemType e)
{// 插入元素e为Q的新的队尾元素
  QueuePtr p;
  p = (QueuePtr)malloc(sizeof(QNode));
  if(!p)  exit(OVERFLOW);        //存储分配失败
  p->data = e;   p->next = NULL;
  ____10____;  
  Q.rear =____11____ ;
  return OK;
}

Status DeQueue(LinkQueue &Q, QElemType &e)
{//若队列不空,则删除Q的队头元素,用e返回其值,
//并返回OK;  否则返回ERROR
  QueuePtr p;
  if( ____12____ ) return ERROR;
  p = Q.front->next; 
  e = ____13____;
  ____14____;
  if(____15____)Q.rear = Q.front;
  free(p);
  return OK;
}

Status QueueEmpty(LinkQueue Q)
{ if( ____16____ ) return TRUE;
  return FALSE;
}
```

## 程序填空题
1. 1. `QElemType *`
   2. `int`
   3. `int`
   4. `(QElemType *)malloc(MAXQSIZE * sizeof(QElemType))`
   5. `0`
   6. `0`
   7. `(Q.rear - Q.front + MAXQSIZE) % MAXQSIZE`
   8. `(Q.rear + 1) % MAXQSIZE == Q.front`
   9. `Q.base[Q.rear]`
   10. `Q.rear = (Q.rear + 1) % MAXQSIZE`
   11. `Q.front == Q.rear`
   12. `Q.base[Q.front]`
   13. `Q.front = (Q.front + 1) % MAXQSIZE`
   14. `Q.front == Q.rear`
2. 1. `QueuePtr`
   1. `QueuePtr`
   2. `(QueuePtr)malloc(sizeof(QNode))`
   3. `Q.front->next = NULL`
   4. `free(Q.front)`
   5. `Q.rear`
   6. `Q.front`
   7. `p != Q.rear`
   8. `p = p->next`
   9.  `Q.rear->next = p`
   10. `p`
   11. `Q.front == Q.rear`
   12. `p->data`
   13. `Q.front->next = p->next`
   14. `Q.rear == p`
   15. `Q.front == Q.rear`