// 对于给定的二叉树，本题要求你按从上到下、从左到右的顺序输出其所有叶结点。

// 输入格式：
// 首先第一行给出一个正整数 n（≤10），为树中结点总数。树中的结点从 0 到 n−1 编号。随后 n 行，每行给出一个对应结点左右孩子的编号。如果某个孩子不存在，则在对应位置给出 "-"。编号间以 1 个空格分隔。

// 输出格式：
// 在一行中按规定顺序输出叶结点的编号。编号间以 1 个空格分隔，行首尾不得有多余空格。

// 输入样例：
// 8
// 1 -
// - -
// 0 -
// 2 7
// - -
// - -
// 5 -
// 4 6
// 输出样例：
// 4 1 5

#include <stdio.h>
#include <stdlib.h>

typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int ElemType;

typedef struct BiTNode
{
    ElemType data;
    int lchild;
    int rchild;
} BiTNode;

typedef BiTNode *BiTree;

Status CreateBT(BiTree T, int n)
{
    for (int i = 0; i < n; i++)
    {
        char left, right;
        scanf(" %c %c", &left, &right);
        int L = (left == '-') ? -1 : (left - '0');
        int R = (right == '-') ? -1 : (right - '0');
        T[i].lchild = L;
        T[i].rchild = R;
        T[i].data = i;
    }
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
    QueuePtr rear;  // 队尾指针
} LinkQueue;

Status InitQueue(LinkQueue &Q)
{ // 构造一个空队列Q
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    if (!Q.front)
        exit(OVERFLOW); // 存储分配失败
    Q.front->next = NULL;
    return OK;
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

int FindRootIndex(BiTree T, int n)
{
    int *hasParent = (int *)calloc(n, sizeof(int));
    if (!hasParent)
        return 0;
    for (int i = 0; i < n; i++)
    {
        if (T[i].lchild != -1 && T[i].lchild >= 0 && T[i].lchild < n)
            hasParent[T[i].lchild] = 1;
        if (T[i].rchild != -1 && T[i].rchild >= 0 && T[i].rchild < n)
            hasParent[T[i].rchild] = 1;
    }
    int root = 0;
    for (int i = 0; i < n; i++)
    {
        if (hasParent[i] == 0)
        {
            root = i;
            break;
        }
    }
    free(hasParent);
    return root;
}

Status FindAndPrintLeaves(BiTree T, int n, int rootIndex)
{
    if (T == NULL || n <= 0 || rootIndex < 0 || rootIndex >= n)
    {
        printf("\n");
        return OK;
    }
    LinkQueue Q;
    InitQueue(Q);
    BiTree p;
    EnQueue(Q, T + rootIndex);
    int *leaves = (int *)malloc(n * sizeof(int));
    if (!leaves)
    {
        DestroyQueue(Q);
        return OVERFLOW;
    }
    int cnt = 0;
    while (!QueueEmpty(Q))
    {
        if (DeQueue(Q, p) == ERROR)
            break;
        if (p->lchild == -1 && p->rchild == -1)
        {
            leaves[cnt++] = p->data;
        }
        if (p->lchild != -1)
            EnQueue(Q, T + p->lchild);
        if (p->rchild != -1)
            EnQueue(Q, T + p->rchild);
    }
    DestroyQueue(Q);

    for (int i = 0; i < cnt; i++)
    {
        if (i == 0)
            printf("%d", leaves[i]);
        else
            printf(" %d", leaves[i]);
    }
    printf("\n");
    free(leaves);
    return OK;
}

int main()
{
    int n;
    scanf("%d", &n);
    BiTree bt = (BiTree)malloc(n * sizeof(BiTNode));
    CreateBT(bt, n);
    int root = FindRootIndex(bt, n);
    FindAndPrintLeaves(bt, n, root);
    free(bt);
    return 0;
}