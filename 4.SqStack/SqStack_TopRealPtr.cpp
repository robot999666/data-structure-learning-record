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

typedef int SElemType;

typedef struct
{
    SElemType* head;    // 内存块起始指针
    SElemType* base;    // 栈底指针，指向第一个元素位置
    SElemType* top;     // 栈顶指针，指向真正的栈顶元素（实指方式）
    int stacksize;      // 栈的最大容量
} Stack;

// 初始化栈（实指方式）
// top初始指向栈底-1位置，便于判空
Status InitStack(Stack &s)
{
    s.head = (SElemType *)malloc((STACK_INIT_SIZE + 1) * sizeof(SElemType));
    if (!s.head) exit(OVERFLOW);
    s.top = s.head;        // top指向head位置（栈底-1）
    s.base = s.head + 1;   // base指向第一个元素位置
    s.stacksize = STACK_INIT_SIZE;
    return OK;
}

// 判断栈是否为空（实指方式）
Status StackEmpty(Stack s)
{
    return s.top < s.base ? TRUE : FALSE;
    // 当top < base时，栈为空（top指向栈底-1位置）
}

// 入栈操作（实指方式）
Status Push(Stack &s, SElemType e)
{
    if (s.top - s.base >= s.stacksize)  // 检查栈是否已满
    {
        // 栈满时动态扩容
        s.head = (SElemType*)realloc(s.head, (s.stacksize + STACKINCREMENT + 1) * sizeof(SElemType));
        if (!s.head) exit(OVERFLOW);
        s.base = s.head + 1;                    // 重新设置栈底指针
        s.top = s.base + s.stacksize - 1;       // 重新设置栈顶指针
        s.stacksize += STACKINCREMENT;          // 更新栈容量
    }
    *(++s.top) = e;  // 先移动top指针，再将元素放入栈顶
    return OK;
}

// 出栈操作（实指方式）
Status Pop(Stack &s, SElemType &e)
{
    if (StackEmpty(s)) return ERROR;  // 栈空判断
    // 实指方式：top初始指向栈底-1位置，便于判空
    e = *(s.top--);  // 先获取栈顶元素，再移动top指针
    return OK;
}