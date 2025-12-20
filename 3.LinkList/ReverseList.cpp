//单链表的原地逆置
#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
typedef struct NODE
{
    int data;           // 节点数据
    struct NODE *next;  // 指向下一个节点
} NODE, *SqList;

// 逆置单链表函数
SqList ReverseList(SqList L)  // L为带头节点的链表
{
    SqList prev = NULL;       // prev指向前一个节点，初始为NULL
    SqList current = L->next; // current指向当前节点，初始为第一个数据节点
    SqList next = NULL;       // next保存下一个节点
    if (!L->next)             // 如果链表为空，直接返回
        return L;
    while (current)           // 遍历链表
    {
        next = current->next;     // 保存下一个节点
        current->next = prev;     // 反转当前节点的指针
        prev = current;           // prev移动到当前节点
        current = next;           // current移动到下一个节点
    }
    L->next = prev;  // 头节点的next指向新的第一个节点
    return L;        // 返回逆置后的链表
}
