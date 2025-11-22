// 编写递归算法，将二叉树中所有结点的左、右子树相互交换。
#include <stdio.h>
typedef int Status;
#define OK 1
typedef char ElemType;

typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
} BiTNode, *BiTree;

Status exchang_child(BiTree T)
{
    if (T == NULL)
    return OK;
    BiTree temp;
    temp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = temp;
    exchang_child(T->lchild);
    exchang_child(T->rchild);
    return OK;
}