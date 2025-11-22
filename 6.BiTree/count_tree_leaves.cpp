// 统计孩子 - 兄弟链表表示的树的叶子节点个数

#include <stdio.h>
#include <stdlib.h>
typedef  int  ElemType;

typedef struct CSNode {
    ElemType data;
    struct CSNode *firstchild, *nextsibling; // 第一个孩子、右兄弟
} CSNode, *CSTree;

int Count_Leaf(CSTree T) {
    if (T == NULL) {
        return 0; 
    }
    if (T->firstchild == NULL) {
        return 1 + Count_Leaf(T->nextsibling);
    } else {
        return Count_Leaf(T->firstchild) + Count_Leaf(T->nextsibling);
    }
}