// 已知二叉树的先序序列，输出层序遍历序列。

// 输入格式:
// 输入在一行中给出二叉树的先序序列。*表示空格

// 输出格式:
// 输出共一行，是二叉树的层序遍历序列。

// 输入样例:
// ABC**DE*G**F***
// 输出样例:
// ABCDEFG

#include <stdio.h>
#include <stdlib.h>

typedef int Status;         // 定义状态类型
#define TRUE 1              // 真值定义
#define FALSE 0             // 假值定义
#define OK 1                // 操作成功
#define ERROR 0             // 操作失败
#define OVERFLOW -2         // 内存溢出

typedef char ElemType;      // 定义元素类型为字符

typedef struct BiTNode      // 二叉树节点结构体定义
{
    ElemType data;          // 节点数据
    struct BiTNode *lchild; // 左孩子指针
    struct BiTNode *rchild; // 右孩子指针
} BiTNode, *BiTree;

Status CreateBT(BiTree &T)  // 根据先序序列递归创建二叉树
{
    char x;                 // 读取的字符
    scanf(" %c", &x);       // 读取一个字符（跳过空白字符）
    if (x == '*')           // 如果是'*'，表示空节点
        T = NULL;           // 设置为空
    else
    {
        T = (BiTree)malloc(sizeof(BiTNode));  // 分配内存
        T->data = x;                           // 设置节点数据
        CreateBT(T->lchild);                   // 递归创建左子树
        CreateBT(T->rchild);                   // 递归创建右子树
    }
    return OK;             // 返回成功状态
}

Status Print_BT(BiTree T)  // 打印二叉树节点数据
{
    if (T == NULL)          // 如果节点为空，直接返回
        return OK;
    printf("%c", T->data);  // 打印节点数据
    return OK;              // 返回成功状态
}

typedef BiTree QElemType;  // 队列元素类型定义为二叉树节点指针

typedef struct QNode       // 队列节点结构体定义
{
    QElemType data;        // 队列元素数据
    struct QNode *next;    // 指向下一个队列节点
} QNode, *QueuePtr;        // QueuePtr为指向QNode的指针类型

typedef struct             // 链式队列结构体定义
{
    QueuePtr front;        // 队头指针
    QueuePtr rear;         // 队尾指针
} LinkQueue;

Status InitQueue(LinkQueue &Q)  // 初始化链式队列
{ // 构造一个空队列Q
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));  // 创建头节点
    if (!Q.front)                    // 如果内存分配失败
        exit(OVERFLOW);              // 退出程序
    Q.front->next = NULL;            // 头节点的next指针为空
    return OK;                       // 返回成功状态
}

Status EnQueue(LinkQueue &Q, QElemType e)  // 入队操作
{   // 插入元素e为Q的新的队尾元素
    QueuePtr p;                      // 创建新节点指针
    p = (QueuePtr)malloc(sizeof(QNode));  // 分配内存
    if (!p)                          // 如果内存分配失败
        exit(OVERFLOW);              // 退出程序
    p->data = e;                     // 设置节点数据
    p->next = NULL;                  // 新节点的next指针为空

    Q.rear->next = p;                // 将新节点链接到队尾
    Q.rear = p;                      // 更新队尾指针
    return OK;                       // 返回成功状态
}

Status DeQueue(LinkQueue &Q, QElemType &e)  // 出队操作
{   // 若队列不空,则删除Q的队头元素,用e返回其值,
    // 并返回OK;  否则返回ERROR
    QueuePtr p;                      // 临时节点指针
    if (Q.front == Q.rear)           // 如果队列为空
        return ERROR;                // 返回错误
    p = Q.front->next;               // 获取队头元素节点
    e = p->data;                     // 返回队头元素数据
    Q.front->next = p->next;         // 更新队头指针
    if (Q.rear == p)                 // 如果删除的是最后一个元素
        Q.rear = Q.front;            // 重置队尾指针
    free(p);                         // 释放内存
    return OK;                       // 返回成功状态
}

Status QueueEmpty(LinkQueue Q)  // 判断队列是否为空
{
    if (Q.front == Q.rear)    // 如果队头等于队尾
        return TRUE;          // 队列为空
    return FALSE;             // 队列不为空
}

Status DestroyQueue(LinkQueue &Q)  // 销毁队列
{ // 销毁队列Q
    while (Q.front)           // 当队头不为空时循环
    {
        Q.rear = Q.front->next;  // 保存下一个节点
        free(Q.front);           // 释放当前节点
        Q.front = Q.rear;        // 更新队头指针
    }
    return OK;                  // 返回成功状态
}

Status LevelTraverseBT(BiTree T, Status (*visit)(BiTree))  // 层序遍历二叉树
{
    if (T == NULL)              // 如果树为空，直接返回
        return OK;
    LinkQueue Q;                // 定义队列
    InitQueue(Q);               // 初始化队列
    BiTree p;                   // 定义临时节点指针
    EnQueue(Q, T);              // 将根节点入队
    while (!QueueEmpty(Q))      // 当队列不为空时循环
    {
        if (DeQueue(Q, p) == ERROR)  // 出队一个节点
            break;                   // 如果出队失败，跳出循环
        visit(p);                    // 访问当前节点
        if (p->lchild != NULL)       // 如果左孩子不为空
            EnQueue(Q, p->lchild);  // 左孩子入队
        if (p->rchild != NULL)       // 如果右孩子不为空
            EnQueue(Q, p->rchild);  // 右孩子入队
    }
    DestroyQueue(Q);            // 销毁队列
    return OK;                   // 返回成功状态
}

int main()  // 主函数
{
    BiTree T;                    // 定义二叉树根节点
    CreateBT(T);                 // 根据先序序列创建二叉树
    LevelTraverseBT(T, Print_BT); // 进行层序遍历并打印结果
    return 0;                    // 返回0表示程序正常结束
    free(T);                     // 这行代码不会执行，因为在return之后
}