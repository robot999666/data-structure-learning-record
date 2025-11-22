// 编写递归算法，将二叉树中所有结点的左、右子树相互交换。

// Status exchang_child(BiTree T)
// {
//     if (T == NULL)
//     return OK;
//     BiTree temp;
//     temp = T->lchild;
//     T->lchild = T->rchild;
//     T->rchild = temp;
//     exchang_child(T->lchild);
//     exchang_child(T->rchild);
//     return OK;
// }