// 给定一系列正整数，请设计一个尽可能高效的算法，查找倒数第K个位置上的数字。

// 输入格式:
// 输入首先给出一个正整数K，随后是若干非负整数，最后以一个负整数表示结尾（该负数不算在序列内，不要处理）。

// 输出格式:
// 输出倒数第K个位置上的数据。如果这个位置不存在，输出错误信息NULL。

// 输入样例:
// 4 1 2 3 4 5 6 7 8 9 0 -1
// 输出样例:
// 7

#include <stdio.h>
#include <stdlib.h>

// 定义元素类型
typedef int ElemType;

// 链表节点结构体
typedef struct LNode
{
    ElemType data;        // 节点数据
    struct LNode *next;   // 指向下一个节点
} LNode, *LinkList;

// 定义状态常量
typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

// 初始化链表
Status InitList(LinkList &L)
{
    L = (LinkList)malloc(sizeof(LNode));  // 分配头节点内存
    if (!L)
        return OVERFLOW;  // 内存分配失败
    L->next = NULL;       // 头节点next置空
    return OK;
}

// 获取链表第i个元素
Status GetElem(LinkList L, int i, ElemType &e)
{
    LinkList p = L->next;  // 从头节点下一个开始
    int j = 0;
    while (p && j < i - 1)  // 遍历到第i-1个节点
    {
        p = p->next;
        j++;
    }
    if (!p || j > i - 1)  // 如果节点不存在或索引超出
    {
        return ERROR;
    }
    e = p->data;  // 获取数据
    return OK;
}

// 销毁链表，释放内存
Status DestroyList(LinkList &L)
{
    LinkList p = L, q;
    while (p)
    {
        q = p->next;  // 保存下一个节点
        free(p);      // 释放当前节点
        p = q;
    }
    return OK;
}

// 主函数
int main()
{
    LinkList L;
    InitList(L);  // 初始化链表
    ElemType x, y;
    int K;
    scanf("%d", &K);  // 读取K
    while (scanf("%d", &x) != -1 && x >= 0)  // 读取序列，直到负数或EOF
    {
        LinkList node = (LinkList)malloc(sizeof(LNode));  // 创建新节点
        node->data = x;
        node->next = L->next;  // 头插法插入
        L->next = node;
    }
    if (GetElem(L, K, y))  // 获取倒数第K个元素
        printf("%d", y);
    else
        printf("NULL");  // 不存在则输出NULL
    DestroyList(L);  // 销毁链表
    return 0;
}