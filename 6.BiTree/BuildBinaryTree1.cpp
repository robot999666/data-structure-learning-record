// 已知先序序列，建立一棵二叉树，输出后序遍历序列，并计算这棵二叉树的高度。

// 输入格式:
// 输入在一行中给出二叉树的先序序列。*表示空格

// 输出格式:
// 输出共二行，第一行是二叉树的后序遍历序列，第二行是二叉树的高度。

// 输入样例:
// ABC**DE*G**F***
// 输出样例:
// CGEFDBA

#include <stdio.h>
#include <stdlib.h>

typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef char ElemType;

// 二叉树节点结构体定义
typedef struct BiTNode
{
    ElemType data;           // 节点数据
    struct BiTNode *lchild;  // 左子树指针
    struct BiTNode *rchild;  // 右子树指针
} BiTNode, *BiTree;

int maxDepth = 0;  // 全局变量记录树的最大深度

// 根据先序序列递归创建二叉树
// '*'表示空节点，按照先序遍历的顺序构建树
Status CreateBT(BiTree &T)
{
    char x;
    scanf("%c", &x);  // 读取一个字符

    if (x == '*')     // 如果是'*'，表示空节点
        T = NULL;
    else
    {
        T = (BiTree)malloc(sizeof(BiTNode));  // 分配节点内存
        T->data = x;                           // 设置节点数据
        CreateBT(T->lchild);                   // 递归创建左子树
        CreateBT(T->rchild);                   // 递归创建右子树
    }
    return OK;
}

// 访问函数：打印节点数据
Status Print_BT(BiTree T)
{
    if (T == NULL)
        return OK;
    printf("%c", T->data);  // 输出节点数据
    return OK;
}

// 后序遍历二叉树
Status PostTraverseBT(BiTree T, Status (*visit)(BiTree))
{
    if (T == NULL)
        return OK;
    PostTraverseBT(T->lchild, visit);  // 遍历左子树
    PostTraverseBT(T->rchild, visit);  // 遍历右子树
    visit(T);                          // 访问根节点
    return OK;
}

// 计算二叉树深度
// 使用后序遍历的方式，记录当前深度与最大深度的比较
Status count_BT_depth(BiTree T, int depth)
{
    if (T)  // 如果节点不为空
    {
        count_BT_depth(T->lchild, depth + 1);  // 递归计算左子树深度
        count_BT_depth(T->rchild, depth + 1);  // 递归计算右子树深度
        if (depth > maxDepth)                  // 更新最大深度
            maxDepth = depth;
    }
    return OK;
}

int main()
{
    BiTree bt;              // 定义二叉树根节点指针
    CreateBT(bt);           // 根据先序序列创建二叉树
    PostTraverseBT(bt, Print_BT);  // 后序遍历并打印节点数据
    count_BT_depth(bt, 1);  // 计算树的高度（从深度1开始）
    printf("\n");           // 输出换行
    printf("%d", maxDepth); // 输出树的高度
    return 0;
}
