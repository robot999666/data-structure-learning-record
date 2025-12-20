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
    SElemType *base;    // 栈底指针，指向栈的起始位置
    SElemType *top;     // 栈顶指针，指向栈顶元素的下一个位置（虚指方式）
    int stacksize;      // 当前栈的最大容量
} Stack;

// 初始化顺序栈
Status InitStack(Stack &s)
{
    s.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!s.base)
        exit(OVERFLOW); // 存储分配失败

    s.top = s.base;    // 栈顶指针初始指向栈底，表示空栈
    s.stacksize = STACK_INIT_SIZE;  // 设置初始栈容量
    return OK;
}

// 获取栈顶元素，但不弹出
Status GetTop(Stack s, SElemType &e)
{
    if (s.base == s.top)  // 栈空判断
        return ERROR;
    e = *(s.top - 1);     // 获取栈顶元素
    return OK;
}

// 入栈操作：将元素e压入栈顶
Status Push(Stack &s, SElemType e)
{
    if (s.top - s.base >= s.stacksize)  // 检查栈是否已满
    {
        // 栈满时动态扩容
        s.base = (SElemType *)realloc(s.base, (s.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!s.base)
            exit(OVERFLOW); // 存储分配失败
        s.top = s.base + s.stacksize;  // 重新定位栈顶指针
        s.stacksize += STACKINCREMENT; // 更新栈容量
    }

    *s.top++ = e;  // 将元素放入栈顶并移动栈顶指针
    return OK;
}

// 出栈操作：弹出栈顶元素并返回其值
Status Pop(Stack &s, SElemType &e)
{
    if (s.top == s.base)  // 栈空判断
        return ERROR;
    e = *(--s.top);       // 先移动栈顶指针，再获取元素值
    return OK;
}

// 判断栈是否为空
Status StackEmpty(Stack s)
{
    if (s.top == s.base)
        return OK;   // 栈空
    else
        return ERROR; // 栈非空
}

int main()
{
    Stack s;        // 定义顺序栈
    InitStack(s);
    int i, index = 0, t;  // index:出栈序列索引, t:临时变量
    int n;                 // 元素个数
    scanf("%d", &n);
    int outline[n];        // 存储待验证的出栈序列

    // 读取出栈序列
    for (i = 0; i < n; i++)
        scanf("%d", &outline[i]);

    // 模拟入栈和出栈过程
    for (i = 1; i <= n; i++)
    {
        Push(s, i);  // 将数字i入栈

        // 当栈不为空且栈顶元素等于当前待出栈元素时，不断出栈
        while (!StackEmpty(s) && outline[index] == *(s.top - 1))
        {
            Pop(s, t);     // 出栈
            index++;       // 移动到下一个待出栈元素
        }
    }

    // 检查最终栈是否为空
    if (StackEmpty(s))
        printf("yes");  // 出栈序列合法
    else
        printf("no");   // 出栈序列不合法

    return 0;
}