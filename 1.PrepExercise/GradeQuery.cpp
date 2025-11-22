// 输入N个同学的成绩，查询某个同学的成绩。如果没有找到输 not found!
// 本题目要求用链表存放每个同学的数据（包括学号、姓名、成绩）。

// 输入格式:
// 输入共N+2行，第一行是学生人数N，接下来N行是N个学生的数据，最后一行是一个学号。学号最多有5个字符。

// 输出格式:
// 输出只有一行，是一个整数或not found!。

// 输入样例:
// 5
// s104  zhangshan   95
// t321  lisi  88
// p005  maliu   79
// s109  wangjun  90
// t349  lili  67
// t321

// 输出样例:
// 88

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct stu
{
    char num[20];
    char name[20];
    int score;
    struct stu *next;
} STU;

STU *createlist(int N)
{
    STU *head = NULL, *end = NULL, *cur = NULL;
    while (N--)
    {
        cur = (STU *)malloc(sizeof(STU));
        scanf("%s %s %d", cur->num, cur->name, &cur->score);
        cur->next = NULL;
        if (NULL == head)
        {
            head = cur;
        }
        else
        {
            end->next = cur;
        }
        end = cur;
    }
    return head;
}
void search(STU *head, char *x)
{
    int flag = 0;
    STU *cur = head;
    while (cur)
    {
        if (!strcmp(cur->num, x))
        {
            printf("%d", cur->score);
            flag = 1;
            return;
        }
        cur = cur->next;
    }
    if (flag == 0)
    {
        printf("not found!");
        return;
    }
}

int main()
{
    int N;
    char x[20];
    STU *head;
    scanf("%d", &N);
    head = createlist(N);
    scanf("%s", x);
    search(head, x);
    return 0;
}
