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

typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
} BiTNode, *BiTree;

int maxDepth = 0;

Status CreateBT(BiTree &T)
{
    char x;
    scanf("%c", &x);
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

Status PostTraverseBT(BiTree T, Status (*visit)(BiTree))
{
    if (T == NULL)
        return OK;
    PostTraverseBT(T->lchild, visit);
    PostTraverseBT(T->rchild, visit);
    visit(T);
    return OK;
}

Status count_BT_depth(BiTree T, int depth)
{
    if (T)
    {
        count_BT_depth(T->lchild, depth + 1);
        count_BT_depth(T->rchild, depth + 1);
        if (depth > maxDepth)
            maxDepth = depth;
    }
    return OK;
}

int main()
{
    BiTree bt;
    CreateBT(bt);
    PostTraverseBT(bt, Print_BT);
    count_BT_depth(bt, 1);
    printf("\n");
    printf("%d", maxDepth);
    return 0;
}
