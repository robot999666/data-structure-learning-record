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

typedef int Status;         // 定义状态类型
#define TRUE 1              // 真值定义
#define FALSE 0             // 假值定义
#define OK 1                // 操作成功
#define ERROR 0             // 操作失败
#define OVERFLOW -2         // 内存溢出

typedef char ElemType;      // 定义元素类型为字符

typedef struct BiTNode      // 二叉树节点结构体定义
{
    ElemType data;          // 节点数据
    struct BiTNode *lchild; // 左孩子指针
    struct BiTNode *rchild; // 右孩子指针
    int order;              // 中序序列中的位置，用于判断左右子树
} BiTNode, *BiTree;

Status CreateBTNode(BiTree &T, char x)  // 创建二叉树节点函数
{
    T = (BiTree)malloc(sizeof(BiTNode));  // 动态分配内存空间
    T->data = x;                           // 设置节点数据
    T->lchild = T->rchild = NULL;          // 初始化左右孩子指针为空
    return OK;                             // 返回成功状态
}

Status Print_BT(BiTree T)  // 打印二叉树节点数据函数
{
    if (T == NULL)          // 如果节点为空，直接返回
        return OK;
    printf("%c", T->data);  // 打印节点数据
    return OK;              // 返回成功状态
}

Status PostTraverseBT(BiTree T, Status (*visit)(BiTree))  // 后序遍历二叉树函数
{
    if (T == NULL)                                    // 如果树为空，直接返回
        return OK;
    PostTraverseBT(T->lchild, visit);                 // 递归遍历左子树
    PostTraverseBT(T->rchild, visit);                 // 递归遍历右子树
    visit(T);                                         // 访问根节点
    return OK;                                         // 返回成功状态
}

Status left_right_order(char pre[26], char in[26], int order[26])  // 计算先序序列中各节点在中序序列中的位置
{
    for (int i = 0; pre[i]; i++)     // 遍历先序序列
    {
        for (int j = 0; in[j]; j++)  // 遍历中序序列
        {
            if (pre[i] == in[j])     // 找到匹配的字符
            {
                order[i] = j;        // 记录位置
                break;               // 找到后跳出内层循环
            }
        }
    }
    return OK;                      // 返回成功状态
}

Status Insert_Node(BiTree &T, BiTree node, int order)  // 将节点插入到二叉树中
{
    BiTree cur = T;                  // 从根节点开始
    while (1)                        // 无限循环，直到找到插入位置
    {
        if (order < cur->order)       // 如果order小于当前节点的order，插入到左子树
        {
            if (cur->lchild == NULL) // 如果左孩子为空
            {
                cur->lchild = node;  // 直接插入
                return OK;
            }
            cur = cur->lchild;       // 继续向左子树查找
        }
        else                          // 否则插入到右子树
        {
            if (cur->rchild == NULL) // 如果右孩子为空
            {
                cur->rchild = node;  // 直接插入
                return OK;
            }
            cur = cur->rchild;       // 继续向右子树查找
        }
    }
}

Status Tree_Create(char pre[26], int order[26], BiTree &T)  // 根据先序序列和位置信息创建二叉树
{
    for (int i = 1; pre[i]; i++)     // 从先序序列的第二个字符开始（第一个已经创建）
    {
        BiTree node;                 // 创建新节点
        CreateBTNode(node, pre[i]);  // 初始化节点数据
        node->order = order[i];      // 设置节点的位置信息
        Insert_Node(T, node, order[i]);  // 将节点插入到树中
    }
    return OK;                      // 返回成功状态
}

int main()  // 主函数
{
    BiTree bt;                    // 定义二叉树根节点
    char pre[26], in[26];         // 定义先序和中序序列数组
    int order[26] = {0};          // 定义位置数组，初始化为0
    scanf("%s", pre);             // 读取先序序列
    scanf("%s", in);              // 读取中序序列
    CreateBTNode(bt, pre[0]);     // 创建根节点
    left_right_order(pre, in, order);  // 计算各节点在中序序列中的位置
    bt->order = order[0];         // 设置根节点的位置
    Tree_Create(pre, order, bt);  // 创建完整的二叉树
    PostTraverseBT(bt, Print_BT); // 后序遍历并打印
    printf("\n%d", order[0]);     // 输出左子树节点个数（根节点位置即为左子树节点数）
    return 0;
}
