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
    SElemType *base;    // 栈底指针，指向栈的起始位置
    SElemType *top;     // 栈顶指针，指向栈顶元素的下一个位置（虚指方式）
    int stacksize;      // 当前栈的最大容量
} Stack;

// 初始化顺序栈
// 为栈分配初始存储空间，设置栈底和栈顶指针
Status InitStack(Stack &s)
{
    s.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!s.base)
        exit(OVERFLOW);
    s.top = s.base;    // 栈顶指针初始指向栈底，表示空栈
    s.stacksize = STACK_INIT_SIZE;  // 设置初始栈容量
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
            exit(OVERFLOW);
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
    e = *--s.top;         // 先移动栈顶指针，再获取元素值
    return OK;
}

// 判断栈是否为空
Status StackEmpty(Stack s)
{
    if (s.top == s.base)
        return TRUE;   // 栈顶指针等于栈底指针表示空栈
    else
        return FALSE;  // 否则栈非空
}

// 获取栈的当前长度（元素个数）
int StackLength(Stack s)
{
    return s.top - s.base;  // 栈顶指针减去栈底指针得到元素个数
}

// 判断给定的出栈序列是否合法
// 使用模拟栈的方式，依次入栈1到n的数字，并尝试按照给定序列出栈
void judge(int m, int n)
{
    Stack s;        // 模拟栈
    InitStack(s);
    int a[n];         // 存储待验证的出栈序列
    int index = 0;    // 出栈序列的当前索引

    // 读取待验证的出栈序列
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    // 模拟入栈过程
    for (int i = 1; i <= n; i++)
    {
        Push(s, i);  // 将数字i入栈

        // 检查栈容量是否超过限制
        if (StackLength(s) > m)
        {
            printf("NO\n");  // 栈容量超限，序列不合法
            free(s.base);
            s.top = s.base = NULL;
            return;
        }

        // 当栈不为空且栈顶元素等于当前待出栈元素时，不断出栈
        while (!StackEmpty(s) && *(s.top - 1) == a[index])
        {
            SElemType e;
            Pop(s, e);     // 出栈
            index++;       // 移动到下一个待出栈元素
        }
    }

    // 检查最终栈是否为空且所有元素都已出栈
    if (StackEmpty(s) && index == n)
        printf("YES\n");  // 序列合法
    else
        printf("NO\n");   // 序列不合法

    // 释放栈空间
    free(s.base);
    s.top = s.base = NULL;
    return;
}

int main()
{
    int m, n, k;                    // m:栈的最大容量, n:元素个数, k:待检查的序列个数
    scanf("%d %d %d", &m, &n, &k);  // 读取参数

    // 对每个待检查的序列进行验证
    for (int i = 0; i < k; i++)
        judge(m, n);  // 调用judge函数验证序列

    return 0;
}
