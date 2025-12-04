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

typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef char ElemType;

typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
} BiTNode, *BiTree;

Status CreateBT(BiTree &T)
{
    char x;
    scanf(" %c", &x);
    if (x == '*')
        T = NULL;
    else
    {
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data = x;
        CreateBT(T->lchild);
        CreateBT(T->rchild);
    }
    return OK;
}

Status Print_BT(BiTree T)
{
    if (T == NULL)
        return OK;
    printf("%c", T->data);
    return OK;
}

typedef BiTree QElemType;

typedef struct QNode
{
    QElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct
{
    QueuePtr front; // 队头指针

    QueuePtr rear; // 队尾指针
} LinkQueue;

Status InitQueue(LinkQueue &Q)
{ // 构造一个空队列Q
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    if (!Q.front)
        exit(OVERFLOW); // 存储分配失败

    Q.front->next = NULL;
    return OK;
}

Status EnQueue(LinkQueue &Q, QElemType e)
{   // 插入元素e为Q的新的队尾元素
    QueuePtr p;
    p = (QueuePtr)malloc(sizeof(QNode));
    if (!p)
        exit(OVERFLOW); // 存储分配失败
    p->data = e;
    p->next = NULL;

    Q.rear->next = p;
    Q.rear = p;
    return OK;
}

Status DeQueue(LinkQueue &Q, QElemType &e)
{   // 若队列不空,则删除Q的队头元素,用e返回其值,
    // 并返回OK;  否则返回ERROR
    QueuePtr p;
    if (Q.front == Q.rear)
        return ERROR;
    p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p)
        Q.rear = Q.front;
    free(p);
    return OK;
}

Status QueueEmpty(LinkQueue Q)
{
    if (Q.front == Q.rear)
        return TRUE;
    return FALSE;
}

Status DestroyQueue(LinkQueue &Q)
{ // 销毁队列Q
    while (Q.front)
    {
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    return OK;
}

Status LevelTraverseBT(BiTree T, Status (*visit)(BiTree))
{
    if (T == NULL)
        return OK;
    LinkQueue Q;
    InitQueue(Q);
    BiTree p;
    EnQueue(Q, T);
    while (!QueueEmpty(Q))
    {
        if (DeQueue(Q, p) == ERROR)
            break;
        visit(p);
        if (p->lchild != NULL)
            EnQueue(Q, p->lchild);
        if (p->rchild != NULL)
            EnQueue(Q, p->rchild);
    }
    DestroyQueue(Q);
    return OK;
}

int main()
{
    BiTree T;
    CreateBT(T);
    LevelTraverseBT(T, Print_BT);
    return 0;
    free(T);
}