// 已知非空的二叉树的先序序列和中序序列，建立这棵二叉树的二叉链表，输出后序序列并计算二叉树中左子树的结点个数。假设树的结点个数不超过26个。

// 输入格式:
// 输入共二行，分别给出非空的二叉树的先序序列和中序序列。

// 输出格式:
// 输出也是二行，第一行输出二叉树的后序序列，第二行输出二叉树中左子树的结点个数。

// 输入样例:
// ABCDEGF
// CBEGDFA
// 输出样例:
// CGEFDBA
// 6

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
    int order;
} BiTNode, *BiTree;

Status CreateBTNode(BiTree &T, char x)
{
    T = (BiTree)malloc(sizeof(BiTNode));
    T->data = x;
    T->lchild = T->rchild = NULL;
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

Status left_right_order(char pre[26], char in[26], int order[26])
{
    for (int i = 0; pre[i]; i++)
    {
        for (int j = 0; in[j]; j++)
        {
            if (pre[i] == in[j])
            {
                order[i] = j;
                break;
            }
        }
    }
    return OK;
}

Status Insert_Node(BiTree &T, BiTree node, int order)
{
    BiTree cur = T;
    while (1)
    {
        if (order < cur->order)
        {
            if (cur->lchild == NULL)
            {
                cur->lchild = node;
                return OK;
            }
            cur = cur->lchild;
        }
        else
        {
            if (cur->rchild == NULL)
            {
                cur->rchild = node;
                return OK;
            }
            cur = cur->rchild;
        }
    }
}

Status Tree_Create(char pre[26], int order[26], BiTree &T)
{
    for (int i = 1; pre[i]; i++)
    {
        BiTree node;
        CreateBTNode(node, pre[i]);
        node->order = order[i];
        Insert_Node(T, node, order[i]);
    }
    return OK;
}

int main()
{
    BiTree bt;
    char pre[26], in[26];
    int order[26] = {0};
    scanf("%s", pre);
    scanf("%s", in);
    CreateBTNode(bt, pre[0]);
    left_right_order(pre, in, order);
    bt->order = order[0];
    Tree_Create(pre, order, bt);
    PostTraverseBT(bt, Print_BT);
    printf("\n%d", order[0]);
    return 0;
}
