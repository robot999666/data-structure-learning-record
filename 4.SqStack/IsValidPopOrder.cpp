// 给定一个最大容量为 m 的堆栈，将 n 个数字按 1, 2, 3, ..., n 的顺序入栈，允许按任何顺序出栈，则哪些数字序列是不可能得到的？例如给定 m=5、n=7，则我们有可能得到{ 1, 2, 3, 4, 5, 6, 7 }，但不可能得到{ 3, 2, 1, 7, 5, 6, 4 }。

// 输入格式：
// 输入第一行给出 3 个不超过 1000 的正整数：m（堆栈最大容量）、n（入栈元素个数）、k（待检查的出栈序列个数）。最后 k 行，每行给出 n 个数字的出栈序列。所有同行数字以空格间隔。

// 输出格式：
// 对每一行出栈序列，如果其的确是有可能得到的合法序列，就在一行中输出YES，否则输出NO。

// 输入样例：
// 5 7 5
// 1 2 3 4 5 6 7
// 3 2 1 7 5 6 4
// 7 6 5 4 3 2 1
// 5 6 4 3 7 2 1
// 1 7 6 5 4 3 2
// 输出样例：
// YES
// NO
// NO
// YES
// NO

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
    if (s.top == s.base)
        return TRUE;
    else
        return FALSE;
}

int StackLength(SqStack s)
{
    return s.top - s.base;
}

void judge(int m, int n)
{
    SqStack s;
    InitStack(s);
    int a[n];
    int index = 0;
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
    {
        Push(s, i);
        if (StackLength(s) > m)
        {
            printf("NO\n");
            free(s.base);
            s.top = s.base = NULL;
            return;
        }
        while (!StackEmpty(s) && *(s.top - 1) == a[index])
        {
            SElemType e;
            Pop(s, e);
            index++;
        }
    }
    if (StackEmpty(s) && index == n)
        printf("YES\n");
    else
        printf("NO\n");
    free(s.base);
    s.top = s.base = NULL;
    return;
}

int main()
{
    int m, n, k;
    scanf("%d %d %d", &m, &n, &k);
    for (int i = 0; i < k; i++)
        judge(m, n);
    return 0;
}
