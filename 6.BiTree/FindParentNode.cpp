// 已知二叉树采用二叉链表结构，编写算法，输出结点b的双亲。

// BiTree parents_search(BiTree T, BiTree b)
// {
//     if (T == NULL || T == b)
//         return NULL;
//     if ((T->lchild == b) || (T->rchild == b))
//         return T;
//     BiTree parents = parents_search(T->lchild, b);
//     if (parents != NULL)
//     {
//         return parents;
//     }
//     return parents_search(T->rchild, b);
// } // 考虑到结点地址输入不便，没有设计算法测试部分