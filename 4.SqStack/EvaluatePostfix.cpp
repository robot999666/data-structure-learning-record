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
        exit(OVERFLOW); // 存储分配失败

    s.top = s.base;    // 栈顶指针初始指向栈底，表示空栈
    s.stacksize = STACK_INIT_SIZE;  // 设置初始栈容量
    return OK;
}

// 获取栈顶元素，但不弹出
// 参数e用于返回栈顶元素的值
Status GetTop(Stack s, SElemType &e)
{
    if (s.base == s.top)  // 栈空判断
        return ERROR;
    e = *(s.top - 1);     // 获取栈顶元素（top前一个位置）
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
    if (s.top == s.base)  // 栈顶指针等于栈底指针表示空栈
        return OK;        // 返回OK表示栈空
    else
        return ERROR;     // 返回ERROR表示栈非空
}

int main()
{
    Stack s;           // 定义顺序栈用于存储操作数
    InitStack(s);        // 初始化栈
    char x;              // 当前读取的字符
    float temp1, temp2;  // 临时变量，用于存储从栈中弹出的操作数

    // 逐字符读取后缀表达式，直到换行符
    while ((x = getchar()) != '\n')
    {
        if (x == '+' || x == '-' || x == '*' || x == '/' || x == '%')
        {
            // 遇到运算符，从栈中弹出两个操作数进行运算
            float out;  // 运算结果
            Pop(s, temp2);  // 弹出第二个操作数（右操作数）
            Pop(s, temp1);  // 弹出第一个操作数（左操作数）

            // 检查除零错误
            if ((x == '/' || x == '%') && temp2 == 0)
            {
                free(s.base);  // 释放栈空间
                return ERROR;  // 返回错误
            }

            // 根据运算符进行相应运算
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
                out = (float)((int)temp1 % (int)temp2);  // 取模运算（转换为整数运算）
                break;
            }
            Push(s, out);  // 将运算结果压入栈中
        }
        else if (x >= '0' && x <= '9')
        {
            // 遇到数字字符，将其转换为数值并压入栈中
            Push(s, x - '0');  // 字符'0'-'9'转换为数值0-9
        }
        else
            break;  // 遇到其他字符，结束处理
    }

    // 表达式处理完毕，栈中应只剩最终结果
    float ret = (float)*(s.top - 1);  // 获取栈顶元素（最终结果）
    printf("%.2f", ret);               // 输出结果，保留2位小数

    // 释放栈空间
    free(s.base);
    s.base = s.top = NULL;  // 防止野指针
    return 0;
}