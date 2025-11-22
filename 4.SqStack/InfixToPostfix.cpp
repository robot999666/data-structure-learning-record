// 输入一行字符表示中缀表达式，表达式中运算对象是单个字母或个位数字，运算符有+、-、*、/、%，中缀表达式中可以有圆括号。运算对象是变量和常数，变量用一个字母表示，常量是个位整数。

// 输入格式:
// 输入在一行中给出一个中缀表达式。

// 输出格式:
// 输出对应的后缀表达式。

// 输入样例:
// (a+b)*c
// 输出样例:
// ab+c*

#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef char SElemType;

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
        exit(OVERFLOW);
    s.top = s.base;
    s.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status Push(SqStack &s, SElemType e)
{
    if (s.top - s.base >= s.stacksize)
    {
        s.base = (SElemType *)realloc(s.base, (s.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!s.base)
            exit(OVERFLOW);
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
    e = *--s.top;
    return OK;
}

Status StackEmpty(SqStack s)
{
    return s.top == s.base;
}

SElemType GetTop(SqStack s)
{
    if (s.top != s.base)
        return *(s.top - 1);
    else
        return '\0';
}

int ord(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    default:
        return 0;
    }
}

void change(char *zhong)
{
    SqStack s;
    InitStack(s);
    char ch, top;
    for (int i = 0; (ch = zhong[i]) != '\0'; i++)
    {
        if (ch >= '0' && ch <= '9' || ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
        {
            printf("%c", ch);
        }
        else if (ch == '(')
        {
            Push(s, ch);
        }
        else if (ch == ')')
        {
            while (!StackEmpty(s) && GetTop(s) != '(')
            {
                Pop(s, top);
                printf("%c", top);
            }
            if (!StackEmpty(s) && GetTop(s) == '(')
            {
                Pop(s, top);
            }
        }
        else
        {
            while (!StackEmpty(s) && GetTop(s) != '(' && ord(GetTop(s)) >= ord(ch))
            {
                Pop(s, top);
                printf("%c", top);
            }
            Push(s, ch);
        }
    }
    while (!StackEmpty(s))
    {
        Pop(s, top);
        printf("%c", top);
    }
    printf("\n");
    free(s.base);
    s.top = s.base = NULL;
}

int main()
{
    char zhong[1000];
    scanf("%s", zhong);
    change(zhong);
    return 0;
}
