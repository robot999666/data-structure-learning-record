// 已知二叉树采用二叉链表结构，编写算法，输出结点b的双亲。
#include <stdio.h>

typedef char ElemType;      // 定义元素类型为字符

typedef struct BiTNode      // 二叉树节点结构体定义
{
    ElemType data;          // 节点数据
    struct BiTNode *lchild; // 左孩子指针
    struct BiTNode *rchild; // 右孩子指针
} BiTNode, *BiTree;         // BiTree为指向BiTNode的指针类型

BiTree parents_search(BiTree T, BiTree b)  // 递归查找节点b的双亲节点
{
    if (T == NULL || T == b)      // 如果树为空或当前节点就是b节点
        return NULL;              // 返回NULL（根节点或不存在）
    if ((T->lchild == b) || (T->rchild == b))  // 如果b是当前节点的左孩子或右孩子
        return T;                 // 返回当前节点作为双亲
    BiTree parents = parents_search(T->lchild, b);  // 在左子树中递归查找
    if (parents != NULL)          // 如果在左子树中找到了
    {
        return parents;           // 返回找到的双亲节点
    }
    return parents_search(T->rchild, b);  // 在右子树中递归查找并返回结果
} // 考虑到结点地址输入不便，没有设计算法测试部分