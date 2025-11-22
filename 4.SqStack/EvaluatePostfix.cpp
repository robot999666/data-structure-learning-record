// 输入一行字符表示后缀表达式，表达式中运算对象是个位数字，运算符有+、-、*、/、%，都是双目运算符，表达式结果用浮点数记录。

// 输入格式:
// 输入在一行中给出一个后缀表达式。

// 输出格式:
// 输出后缀表达式的值，保留小数点后2位。

// 输入样例:
// 62/3*
// 输出样例:
// 9.00

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

typedef float SElemType;

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
    if (s.top - s.base >=
        s.stacksize)
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
    if (
        s.top == s.base)
        return ERROR;
    e =
        *(--s.top);
    return OK;
}

Status StackEmpty(SqStack s)
{
    if (
        s.top == s.base)
        return OK;
    else
        return ERROR;
}

int main()
{
    SqStack s;
    InitStack(s);
    char x;
    float temp1, temp2;
    while ((x = getchar()) != '\n')
    {
        if (x == '+' || x == '-' || x == '*' || x == '/' || x == '%')
        {
            float out;
            Pop(s, temp2);
            Pop(s, temp1);
            if ((x == '/' || x == '%') && temp2 == 0)
            {
                free(s.base);
                return ERROR;
            }
            switch (x)
            {
            case '+':
                out = temp1 + temp2;
                break;
            case '-':
                out = temp1 - temp2;
                break;
            case '*':
                out = temp1 * temp2;
                break;
            case '/':
                out = temp1 / temp2;
                break;
            case '%':
                out = (float)((int)temp1 % (int)temp2);
                break;
            }
            Push(s, out);
        }
        else if (x >= '0' && x <= '9')
        {
            Push(s, x - '0');
        }
        else
            break;
    }
    float ret = (float)*(s.top - 1);
    printf("%.2f", ret);
    free(s.base);
    s.base = s.top = NULL;
    return 0;
}