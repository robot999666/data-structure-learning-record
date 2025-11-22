// 假设称正读和反读都相同的字符序列为 “回文”，例如，'abba' 和 'abcba' 是回文，'abcde' 和 'abab' 则不是回文。
// 试写一个算法判别读入的一个以 '@' 为结束符的字符序列是否是 “回文”。

#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define MAXQSIZE 100

typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef char SElemType;

typedef struct {
    SElemType* base;
    SElemType* top;
    int stacksize;
} SqStack;

typedef struct {
    SElemType* base;
    int front;
    int rear;
} SqQueue;

Status InitStack(SqStack &s)
{
    s.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!s.base) exit(OVERFLOW);
    s.top = s.base;
    s.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status Push(SqStack &s, SElemType e)
{
    if(s.top - s.base >= s.stacksize) {
        s.base = (SElemType*)realloc(s.base, (s.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if(!s.base) exit(OVERFLOW);
        s.top = s.base + s.stacksize;
        s.stacksize += STACKINCREMENT;
    }
    *s.top++ = e;
    return OK;
}

Status Pop(SqStack &s, SElemType &e)
{
    if(s.top == s.base) return ERROR;
    e = *--s.top;
    return OK;
}

Status StackEmpty(SqStack s)
{
    if(s.top == s.base) return TRUE;
    else return FALSE;
}

Status InitQueue(SqQueue &q)
{
    q.base = (SElemType*)malloc(MAXQSIZE * sizeof(SElemType));
    if(!q.base) exit(OVERFLOW);
    q.front = q.rear = 0;
    return OK;
}

Status EnQueue(SqQueue &q, SElemType e)
{
    if((q.rear + 1) % MAXQSIZE == q.front) return ERROR;
    q.base[q.rear] = e;
    q.rear = (q.rear + 1) % MAXQSIZE;
    return OK;
}

Status DeQueue(SqQueue &q, SElemType &e)
{
    if(q.front == q.rear) return ERROR;
    e = q.base[q.front];
    q.front = (q.front + 1) % MAXQSIZE;
    return OK;
}

Status judge()
{
    SqStack S; InitStack(S);
    SqQueue Q; InitQueue(Q);
    SElemType ch;
    while((ch = getchar()) != '@') {
        if(ch == '\n') continue;
        Push(S, ch);
        EnQueue(Q, ch);
    }
    while(!StackEmpty(S)) {
        SElemType s_top, q_front;
        Pop(S, s_top);
        if(!DeQueue(Q, q_front)) return ERROR;
        if(s_top != q_front) return FALSE;
    }
    return TRUE;
}

int main()
{
    if(judge())
        printf("是回文串\n");
    else
        printf("不是回文串\n");
    return 0;
}
