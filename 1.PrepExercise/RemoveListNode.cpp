// 链表删除节点程序
// 输入：若干整数（以0结束）建立链表，第二行删除值k
// 输出：删除后链表节点值
#include <stdio.h>
#include <stdlib.h>
// 链表节点结构体
typedef struct list
{
    int data;           // 数据
    struct list *next;  // 下一节点
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
// 删除指定值节点
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
// 打印链表
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