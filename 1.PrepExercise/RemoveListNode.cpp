// 输入若干个整数，建立链表，删除其中所有值为k的结点。本题目要求用链表实现。

// 输入格式:
// 输入共二行。
// 第一行，以数字0结束的若干非零整数作为新建链表的各节点值；
// 第二行，一个整数k作为要删除的值。

// 输出格式:
// 删除后的链表中各节点值，没有分隔符。

// 输入样例:
// 4 2 1 3 3 2 0
// 3
// 输出样例:
// 4212

#include <stdio.h>
#include <stdlib.h>
typedef struct list
{
    int data;
    struct list *next;
} List;

List *createlist()
{
    List *head = NULL, *end = NULL, *cur = NULL;
    while (1)
    {
        cur = (List *)malloc(sizeof(List));
        scanf("%d", &cur->data);
        cur->next = NULL;
        if (cur->data != 0)
        {
            if (head == NULL)
            {
                head = cur;
            }
            else
            {
                end->next = cur;
            }
            end = cur;
        }
        else
        {
            free(cur);
            cur = NULL;
            return head;
        }
    }
}

List *deletenode(List *head, int x)
{
    List *cur = head, *pre;
    if (head == NULL)
        return head;
    while (cur != NULL)
    {
        if (cur->data == x)
        {
            if (head->data == x)
            {
                cur = head->next;
                free(head);
                head = cur;
            }
            else
            {
                pre->next = cur->next;
                free(cur);
                cur = pre->next;
            }
        }
        else
        {
            pre = cur;
            cur = cur->next;
        }
    }
    return head;
}

void printlist(List *head)
{
    List *cur = head;
    while (cur != NULL)
    {
        printf("%d", cur->data);
        cur = cur->next;
    }
}

int main()
{
    List *head;
    int x;
    head = createlist();
    scanf("%d", &x);
    head = deletenode(head, x);
    printlist(head);
    return 0;
}