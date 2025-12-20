// 编写递归算法，将二叉树中所有结点的左、右子树相互交换。
#include <stdio.h>
typedef int Status;
#define OK 1
typedef char ElemType;

// 二叉树节点结构体定义
typedef struct BiTNode
{
    ElemType data;           // 节点数据
    struct BiTNode *lchild;  // 左子树指针
    struct BiTNode *rchild;  // 右子树指针
} BiTNode, *BiTree;

// 递归交换二叉树中所有结点的左、右子树
// 采用后序遍历的方式，先处理左右子树，再交换当前节点的左右子树
Status exchang_child(BiTree T)
{
    if (T == NULL)  // 递归终止条件：空树
        return OK;

    BiTree temp;  // 临时指针用于交换
    temp = T->lchild;      // 保存左子树指针
    T->lchild = T->rchild; // 右子树赋值给左子树
    T->rchild = temp;      // 原左子树赋值给右子树

    exchang_child(T->lchild);  // 递归处理左子树
    exchang_child(T->rchild);  // 递归处理右子树

    return OK;
}