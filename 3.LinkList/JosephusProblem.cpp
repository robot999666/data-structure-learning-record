// 有n个旅客同乘一条船，因为船发生故障，最多只能留下一半旅客。大家议定如下办法：n个人围成一圈，由第一个人起，依次报数，报到m的人必须被扔进大海。如此循环。问最后哪些旅客仍留在船上？每个人都有一个m值，当他被扔进大海后，m的值改为这个人的m值。m的初值由第一个人决定。

// 输入格式:
// 输入共二行，第一行为人数n，第二行为n个整数，代表每个人的m值。

// 输出格式:
// 在一行中输剩下乘客的编号（用%3d格式输出）。

// 输入样例:
// 10
// 2 3 4 3 2 4 3 6 3 2
// 输出样例:
//   1  4  6  8  9

#include <stdio.h>
#include <stdlib.h>

// 定义元素类型
typedef int ElemType;

// 链表节点结构体，用于约瑟夫环问题
typedef struct LNode
{
    ElemType num;         // 乘客编号
    ElemType m;           // 该乘客的报数间隔
    struct LNode *next;   // 指向下一个节点
} LNode, *LinkList;

// 定义状态常量
typedef int Status;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

// 销毁链表，释放内存
Status DestroyList(LinkList &L, int n)
{
    LinkList p = L, q;
    for (int i = 0; i < n; i++)  // 释放n个节点
    {
        q = p->next;  // 保存下一个节点
        free(p);      // 释放当前节点
        p = q;
    }
    return OK;
}

// 主函数，实现约瑟夫环问题
int main()
{
    LinkList L = NULL, end, cur, pre;  // L为头节点，end为尾节点，cur当前节点，pre前一个节点
    ElemType m;  // 当前报数间隔
    int n, i = 0;  // n为总人数，i为计数器
    scanf("%d", &n);  // 读取人数
    int N = n;  // 保存初始人数
    while (++i <= n)  // 创建循环链表
    {
        cur = (LinkList)malloc(sizeof(LNode));  // 分配新节点
        scanf("%d", &m);  // 读取该乘客的m值
        cur->num = i;     // 设置编号
        cur->m = m;       // 设置m值
        cur->next = NULL; // 初始化next
        if (L == NULL)    // 如果是第一个节点
        {
            L = cur;     // 设置头节点
        }
        else
        {
            end->next = cur;  // 连接到尾节点
        }
        end = cur;  // 更新尾节点
    }
    end->next = L;  // 形成循环链表
    m = L->m;       // 初始报数间隔为第一个人的m
    cur = L;        // 当前节点为头
    pre = end;      // 前一个节点为尾
    while (n > N / 2)  // 当人数大于一半时继续
    {
        for (int i = 1; i < m; i++)  // 报数到m-1
        {
            pre = cur;      // 更新前一个节点
            cur = cur->next; // 移动到下一个
        }
        m = cur->m;         // 更新报数间隔为当前被淘汰者的m
        pre->next = cur->next;  // 从链表中移除当前节点
        free(cur);          // 释放内存
        cur = pre->next;    // 更新当前节点
        n--;                // 人数减一
    }
    L = cur;  // 设置新的头节点为当前节点
    for (int i = 0; i < n; i++)  // 找到编号最小的节点作为起始点
    {
        if (cur->num < L->num)
            L = cur;  // 更新最小编号节点
        cur = cur->next;
    }
    cur = L;  // 从最小编号开始输出
    for (int i = 0; i < n; i++)
    {
        printf("%3d", cur->num);  // 输出编号
        cur = cur->next;
    }
    DestroyList(L, n);  // 销毁链表
    return 0;
}