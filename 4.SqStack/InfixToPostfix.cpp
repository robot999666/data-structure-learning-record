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
    return s.top == s.base;  // 栈顶指针等于栈底指针表示空栈
}

// 获取栈顶元素，但不弹出（返回字符版本）
SElemType GetTop(Stack s)
{
    if (s.top != s.base)
        return *(s.top - 1);  // 返回栈顶元素
    else
        return '\0';          // 栈空时返回空字符
}

// 获取运算符的优先级
// 返回值越大，优先级越高
int ord(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;  // 加减运算符优先级为1
    case '*':
    case '/':
    case '%':
        return 2;  // 乘除模运算符优先级为2
    default:
        return 0;  // 其他字符优先级为0
    }
}

// 中缀表达式转换为后缀表达式
// 使用栈来处理运算符的优先级和括号
void change(char *zhong)
{
    Stack s;        // 运算符栈
    InitStack(s);
    char ch, top;     // ch为当前字符，top为栈顶元素

    // 遍历中缀表达式中的每个字符
    for (int i = 0; (ch = zhong[i]) != '\0'; i++)
    {
        if (ch >= '0' && ch <= '9' || ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
        {
            // 遇到操作数（数字或字母），直接输出
            printf("%c", ch);
        }
        else if (ch == '(')
        {
            // 遇到左括号，压入栈中
            Push(s, ch);
        }
        else if (ch == ')')
        {
            // 遇到右括号，弹出栈中元素直到遇到左括号
            while (!StackEmpty(s) && GetTop(s) != '(')
            {
                Pop(s, top);
                printf("%c", top);  // 输出弹出的运算符
            }
            if (!StackEmpty(s) && GetTop(s) == '(')
            {
                Pop(s, top);  // 弹出左括号但不输出
            }
        }
        else
        {
            // 遇到运算符，比较优先级并处理
            while (!StackEmpty(s) && GetTop(s) != '(' && ord(GetTop(s)) >= ord(ch))
            {
                // 栈顶运算符优先级大于等于当前运算符时，弹出并输出
                Pop(s, top);
                printf("%c", top);
            }
            Push(s, ch);  // 当前运算符压入栈中
        }
    }

    // 处理剩余的栈中运算符
    while (!StackEmpty(s))
    {
        Pop(s, top);
        printf("%c", top);
    }
    printf("\n");

    // 释放栈空间
    free(s.base);
    s.top = s.base = NULL;
}

int main()
{
    char zhong[1000];     // 存储输入的中缀表达式
    scanf("%s", zhong);   // 读取中缀表达式字符串
    change(zhong);        // 调用转换函数，将中缀表达式转换为后缀表达式并输出
    return 0;
}
