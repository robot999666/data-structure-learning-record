//单链表的原地逆置
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
    int data;
    struct NODE *next;
} NODE, *SqList;

SqList ReverseList(SqList L)
{
    SqList prev = NULL;
    SqList current = L->next;
    SqList next = NULL;
    if (!L->next)
        return L;
    while (current)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    L->next = prev;
    return L;
}
