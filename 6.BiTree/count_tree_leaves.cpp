// 统计孩子 - 兄弟链表表示的树的叶子节点个数

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;       // 定义元素类型为整型

typedef struct CSNode       // 孩子-兄弟链表节点结构体定义
{
    ElemType data;          // 节点数据
    struct CSNode *firstchild;    // 指向第一个孩子节点
    struct CSNode *nextsibling;   // 指向下一个兄弟节点
} CSNode, *CSTree;          // CSTree为指向CSNode的指针类型

int Count_Leaf(CSTree T)    // 统计树中叶子节点个数的递归函数
{
    if (T == NULL)          // 如果树为空，返回0
    {
        return 0;
    }
    if (T->firstchild == NULL)  // 如果当前节点没有孩子，则为叶子节点
    {
        return 1 + Count_Leaf(T->nextsibling);  // 返回1加上兄弟子树的叶子数
    }
    else                      // 如果有孩子，则叶子数为孩子子树的叶子数加上兄弟子树的叶子数
    {
        return Count_Leaf(T->firstchild) + Count_Leaf(T->nextsibling);
    }
}