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

int Length = 0;

Status BiT_Create(BiTree &T)
{
    char x;
    scanf("%c", &x);
    if (x == '*')
        T = NULL;
    else
    {
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data = x;
        BiT_Create(T->lchild);
        BiT_Create(T->rchild);
    }
    return OK;
}

Status BiT_Found(BiTree T, char v, BiTree &V)
{
    if (!T)
        return ERROR;
    if (T->data == v)
    {
        V = T;
        return OK;
    }
    if (BiT_Found(T->lchild, v, V) == OK)
        return OK;
    if (BiT_Found(T->rchild, v, V) == OK)
        return OK;
    return ERROR;
}

Status BiT_SonFound(BiTree V, char u, int l)
{
    if (!V)
        return FALSE;
    if (V->data == u)
    {
        Length = l;
        return TRUE;
    }
    if (BiT_SonFound(V->lchild, u, l + 1))
        return TRUE;
    if (BiT_SonFound(V->rchild, u, l + 1))
        return TRUE;
    return FALSE;
}

int main()
{
    BiTree bt, V;
    char v, u;
    BiT_Create(bt);
    scanf(" %c%c", &v, &u);
    if (BiT_Found(bt, v, V) == ERROR)
    {
        printf("NO");
        return 0;
    }
    if (BiT_SonFound(V, u, 0))
        printf("%d", Length);
    else
        printf("NO");
    return 0;
}