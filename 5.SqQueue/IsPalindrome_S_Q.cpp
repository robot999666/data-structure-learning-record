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
    SElemType* base;    // 栈底指针，指向栈的起始位置
    SElemType* top;     // 栈顶指针，指向栈顶元素的下一个位置（虚指方式）
    int stacksize;      // 当前栈的最大容量
} Stack;

typedef struct {
    SElemType* base;    // 队列的存储空间基地址
    int front;          // 队头指针，指向队头元素
    int rear;           // 队尾指针，指向队尾元素的下一个位置
} SqQueue;

// 初始化顺序栈
Status InitStack(Stack &s)
{
    s.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!s.base) exit(OVERFLOW);
    s.top = s.base;    // 栈顶指针初始指向栈底，表示空栈
    s.stacksize = STACK_INIT_SIZE;  // 设置初始栈容量
    return OK;
}

// 入栈操作：将元素e压入栈顶
Status Push(Stack &s, SElemType e)
{
    if(s.top - s.base >= s.stacksize) {  // 检查栈是否已满
        // 栈满时动态扩容
        s.base = (SElemType*)realloc(s.base, (s.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if(!s.base) exit(OVERFLOW);
        s.top = s.base + s.stacksize;  // 重新定位栈顶指针
        s.stacksize += STACKINCREMENT; // 更新栈容量
    }
    *s.top++ = e;  // 将元素放入栈顶并移动栈顶指针
    return OK;
}

// 出栈操作：弹出栈顶元素并返回其值
Status Pop(Stack &s, SElemType &e)
{
    if(s.top == s.base) return ERROR;  // 栈空判断
    e = *--s.top;  // 先移动栈顶指针，再获取元素值
    return OK;
}

// 判断栈是否为空
Status StackEmpty(Stack s)
{
    if(s.top == s.base) return TRUE;   // 栈顶指针等于栈底指针表示空栈
    else return FALSE;
}

// 初始化循环队列
Status InitQueue(SqQueue &q)
{
    q.base = (SElemType*)malloc(MAXQSIZE * sizeof(SElemType));
    if(!q.base) exit(OVERFLOW);
    q.front = q.rear = 0;  // 队头和队尾指针都指向0，表示空队列
    return OK;
}

// 入队操作：将元素e加入队尾
Status EnQueue(SqQueue &q, SElemType e)
{
    if((q.rear + 1) % MAXQSIZE == q.front) return ERROR;  // 队列满判断
    q.base[q.rear] = e;  // 将元素放入队尾位置
    q.rear = (q.rear + 1) % MAXQSIZE;  // 队尾指针后移（循环）
    return OK;
}

// 出队操作：删除队头元素并返回其值
Status DeQueue(SqQueue &q, SElemType &e)
{
    if(q.front == q.rear) return ERROR;  // 队列空判断
    e = q.base[q.front];  // 获取队头元素
    q.front = (q.front + 1) % MAXQSIZE;  // 队头指针后移（循环）
    return OK;
}

// 回文判断函数
// 使用栈和队列的特性：栈后进先出，队列先进先出
// 如果字符串是回文，则栈顶元素应该与队头元素相等
Status judge()
{
    Stack S; InitStack(S);  // 初始化栈
    SqQueue Q; InitQueue(Q);  // 初始化队列
    SElemType ch;

    // 读取字符序列，直到遇到'@'结束符
    while((ch = getchar()) != '@') {
        if(ch == '\n') continue;  // 跳过换行符
        Push(S, ch);    // 将字符压入栈
        EnQueue(Q, ch); // 将字符加入队列
    }

    // 比较栈和队列中的元素
    while(!StackEmpty(S)) {
        SElemType s_top, q_front;
        Pop(S, s_top);  // 从栈顶弹出元素（逆序）
        if(!DeQueue(Q, q_front)) return ERROR;  // 从队头删除元素（正序）
        if(s_top != q_front) return FALSE;      // 如果不相等，不是回文
    }
    return TRUE;  // 所有字符都匹配，是回文
}

int main()
{
    if(judge())  // 调用回文判断函数
        printf("是回文串\n");  // 是回文串
    else
        printf("不是回文串\n");  // 不是回文串
    return 0;
}
