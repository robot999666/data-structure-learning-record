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

typedef int Status;         // 定义状态类型
#define TRUE 1              // 真值定义
#define FALSE 0             // 假值定义
#define OK 1                // 操作成功
#define ERROR 0             // 操作失败
#define OVERFLOW -2         // 内存溢出

typedef int ElemType;       // 定义元素类型为整型

typedef struct BiTNode      // 二叉树节点结构体定义（使用数组索引表示孩子）
{
    ElemType data;          // 节点数据（节点编号）
    int lchild;             // 左孩子在数组中的索引，-1表示无左孩子
    int rchild;             // 右孩子在数组中的索引，-1表示无右孩子
} BiTNode;

typedef BiTNode *BiTree;    // BiTree为指向BiTNode数组的指针

Status CreateBT(BiTree T, int n)  // 创建二叉树结构
{
    for (int i = 0; i < n; i++)  // 循环读取n个节点的信息
    {
        char left, right;         // 左右孩子的字符表示
        scanf(" %c %c", &left, &right);  // 读取左右孩子字符
        int L = (left == '-') ? -1 : (left - '0');    // 转换左孩子：'-'为-1，否则转为数字
        int R = (right == '-') ? -1 : (right - '0');  // 转换右孩子：'-'为-1，否则转为数字
        T[i].lchild = L;          // 设置左孩子索引
        T[i].rchild = R;          // 设置右孩子索引
        T[i].data = i;            // 设置节点数据为节点编号
    }
    return OK;                   // 返回成功状态
}

typedef BiTree QElemType;   // 队列元素类型定义为二叉树节点指针

typedef struct QNode        // 队列节点结构体定义
{
    QElemType data;         // 队列元素数据
    struct QNode *next;     // 指向下一个队列节点
} QNode, *QueuePtr;         // QueuePtr为指向QNode的指针类型

typedef struct              // 链式队列结构体定义
{
    QueuePtr front;         // 队头指针
    QueuePtr rear;          // 队尾指针
} LinkQueue;

Status InitQueue(LinkQueue &Q)  // 初始化链式队列
{ // 构造一个空队列Q
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));  // 创建头节点
    if (!Q.front)                    // 如果内存分配失败
        exit(OVERFLOW);              // 退出程序
    Q.front->next = NULL;            // 头节点的next指针为空
    return OK;                       // 返回成功状态
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

int FindRootIndex(BiTree T, int n)  // 找到二叉树的根节点索引
{
    int *hasParent = (int *)calloc(n, sizeof(int));  // 分配数组记录每个节点是否有父节点
    if (!hasParent)                 // 如果内存分配失败
        return 0;                   // 返回默认值0
    for (int i = 0; i < n; i++)     // 遍历所有节点
    {
        if (T[i].lchild != -1 && T[i].lchild >= 0 && T[i].lchild < n)  // 如果左孩子存在且有效
            hasParent[T[i].lchild] = 1;  // 标记左孩子有父节点
        if (T[i].rchild != -1 && T[i].rchild >= 0 && T[i].rchild < n)  // 如果右孩子存在且有效
            hasParent[T[i].rchild] = 1;  // 标记右孩子有父节点
    }
    int root = 0;                  // 默认根节点为0
    for (int i = 0; i < n; i++)     // 遍历所有节点
    {
        if (hasParent[i] == 0)      // 找到没有父节点的节点
        {
            root = i;               // 记录根节点索引
            break;                  // 找到后跳出循环
        }
    }
    free(hasParent);               // 释放内存
    return root;                   // 返回根节点索引
}

Status FindAndPrintLeaves(BiTree T, int n, int rootIndex)  // 查找并打印所有叶子节点
{
    if (T == NULL || n <= 0 || rootIndex < 0 || rootIndex >= n)  // 参数校验
    {
        printf("\n");              // 输出空行
        return OK;                 // 返回成功状态
    }
    LinkQueue Q;                   // 定义队列
    InitQueue(Q);                  // 初始化队列
    BiTree p;                      // 定义临时节点指针
    EnQueue(Q, T + rootIndex);     // 将根节点入队
    int *leaves = (int *)malloc(n * sizeof(int));  // 分配数组存储叶子节点
    if (!leaves)                   // 如果内存分配失败
    {
        DestroyQueue(Q);           // 销毁队列
        return OVERFLOW;           // 返回内存溢出错误
    }
    int cnt = 0;                   // 叶子节点计数器
    while (!QueueEmpty(Q))         // 当队列不为空时循环
    {
        if (DeQueue(Q, p) == ERROR)  // 出队一个节点
            break;                   // 如果出队失败，跳出循环
        if (p->lchild == -1 && p->rchild == -1)  // 如果是叶子节点（无左右孩子）
        {
            leaves[cnt++] = p->data;  // 将叶子节点数据存入数组
        }
        if (p->lchild != -1)         // 如果有左孩子
            EnQueue(Q, T + p->lchild);  // 左孩子入队
        if (p->rchild != -1)         // 如果有右孩子
            EnQueue(Q, T + p->rchild);  // 右孩子入队
    }
    DestroyQueue(Q);               // 销毁队列

    for (int i = 0; i < cnt; i++)  // 遍历叶子节点数组
    {
        if (i == 0)                // 第一个叶子节点
            printf("%d", leaves[i]);  // 无前导空格
        else                       // 其他叶子节点
            printf(" %d", leaves[i]); // 有前导空格
    }
    printf("\n");                  // 输出换行
    free(leaves);                  // 释放叶子节点数组内存
    return OK;                     // 返回成功状态
}

int main()  // 主函数
{
    int n;                         // 节点总数
    scanf("%d", &n);               // 读取节点总数
    BiTree bt = (BiTree)malloc(n * sizeof(BiTNode));  // 分配二叉树数组内存
    CreateBT(bt, n);               // 创建二叉树结构
    int root = FindRootIndex(bt, n);  // 找到根节点索引
    FindAndPrintLeaves(bt, n, root);  // 查找并打印所有叶子节点
    free(bt);                       // 释放二叉树数组内存
    return 0;                       // 返回0表示程序正常结束
}