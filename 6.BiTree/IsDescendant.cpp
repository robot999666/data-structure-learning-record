// 已知二叉树的先序序列，判断结点u是否是结点v的子孙，是就输出v到u的路径长度，否则输出NO。假设结点个数少于50个。

// 输入格式:
// 输入共二行，第一行中给出先序序列，第二行给出两个顶点。*表示空树。

// 输出格式:
// 输出一个整数或NO。

// 输入样例1:
// ABC**DE*G**F***
// BE
// 输出样例1:
// 2
// 输入样例2:
// ABC**DE*G**F***
// CE
// 输出样例2:
// NO

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
} BiTNode, *BiTree;         // BiTree为指向BiTNode的指针类型

int Length = 0;             // 全局变量，存储路径长度

Status BiT_Create(BiTree &T)  // 根据先序序列递归创建二叉树
{
    char x;                 // 读取的字符
    scanf("%c", &x);        // 读取一个字符
    if (x == '*')           // 如果是'*'，表示空节点
        T = NULL;           // 设置为空
    else
    {
        T = (BiTree)malloc(sizeof(BiTNode));  // 分配内存
        T->data = x;                           // 设置节点数据
        BiT_Create(T->lchild);                 // 递归创建左子树
        BiT_Create(T->rchild);                 // 递归创建右子树
    }
    return OK;             // 返回成功状态
}

Status BiT_Found(BiTree T, char v, BiTree &V)  // 在二叉树中查找指定节点v
{
    if (!T)                      // 如果树为空
        return ERROR;            // 返回错误
    if (T->data == v)            // 如果当前节点数据等于v
    {
        V = T;                   // 返回当前节点指针
        return OK;               // 返回成功
    }
    if (BiT_Found(T->lchild, v, V) == OK)  // 在左子树中递归查找
        return OK;               // 如果找到，返回成功
    if (BiT_Found(T->rchild, v, V) == OK)  // 在右子树中递归查找
        return OK;               // 如果找到，返回成功
    return ERROR;                // 没有找到，返回错误
}

Status BiT_SonFound(BiTree V, char u, int l)  // 在以V为根的子树中查找节点u并计算路径长度
{
    if (!V)                      // 如果当前节点为空
        return FALSE;            // 返回FALSE
    if (V->data == u)            // 如果当前节点数据等于u
    {
        Length = l;              // 设置路径长度
        return TRUE;             // 返回TRUE表示找到
    }
    if (BiT_SonFound(V->lchild, u, l + 1))  // 在左子树中递归查找，路径长度加1
        return TRUE;             // 如果找到，返回TRUE
    if (BiT_SonFound(V->rchild, u, l + 1))  // 在右子树中递归查找，路径长度加1
        return TRUE;             // 如果找到，返回TRUE
    return FALSE;                // 没有找到，返回FALSE
}

int main()  // 主函数
{
    BiTree bt, V;             // bt:二叉树根节点, V:查找到的节点v
    char v, u;                // v:祖先节点, u:待检查的后代节点
    BiT_Create(bt);           // 根据先序序列创建二叉树
    scanf(" %c%c", &v, &u);   // 读取节点v和u
    if (BiT_Found(bt, v, V) == ERROR)  // 如果找不到节点v
    {
        printf("NO");         // 输出NO
        return 0;             // 程序结束
    }
    if (BiT_SonFound(V, u, 0))  // 在以v为根的子树中查找u，初始路径长度为0
        printf("%d", Length);  // 如果找到，输出路径长度
    else
        printf("NO");          // 如果没找到，输出NO
    return 0;                 // 返回0表示程序正常结束
}