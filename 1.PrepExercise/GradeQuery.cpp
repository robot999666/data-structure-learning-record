// 学生成绩查询程序
// 使用链表存储学生信息，实现按学号查询成绩
// 输入：学生人数N，N行学生数据（学号 姓名 成绩），最后一行查询学号
// 输出：查询到的成绩或"not found!"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 学生结构体定义
typedef struct stu
{
    char num[20];     // 学号（字符串）
    char name[20];    // 姓名
    int score;        // 成绩
    struct stu *next; // 指向下一个节点的指针
} STU;

// 创建学生链表
// 输入学生人数N，从标准输入读取N个学生的信息，返回链表头指针
STU *createlist(int N)
{
    STU *head = NULL, *end = NULL, *cur = NULL;  // head:头指针, end:尾指针, cur:当前节点

    while (N--)  // 循环N次，创建N个节点
    {
        cur = (STU *)malloc(sizeof(STU));  // 动态分配内存
        scanf("%s %s %d", cur->num, cur->name, &cur->score);  // 读取学号、姓名、成绩
        cur->next = NULL;  // 新节点next指针置空

        if (NULL == head)  // 如果是第一个节点
        {
            head = cur;  // 头指针指向第一个节点
        }
        else
        {
            end->next = cur;  // 尾节点的next指向新节点
        }
        end = cur;  // 更新尾指针
    }
    return head;  // 返回链表头指针
}
// 按学号查询成绩
// 在链表中查找学号为x的学生，输出其成绩；如果找不到输出"not found!"
void search(STU *head, char *x)
{
    int flag = 0;     // 标记是否找到学生
    STU *cur = head;  // 当前遍历节点，从头节点开始

    while (cur)  // 遍历整个链表
    {
        if (!strcmp(cur->num, x))  // 比较学号（字符串比较）
        {
            printf("%d", cur->score);  // 输出成绩
            flag = 1;  // 标记已找到
            return;    // 找到后立即返回
        }
        cur = cur->next;  // 移动到下一个节点
    }

    if (flag == 0)  // 如果遍历完仍未找到
    {
        printf("not found!");  // 输出未找到信息
        return;
    }
}

int main()
{
    int N;         // 学生人数
    char x[20];    // 要查询的学号
    STU *head;     // 链表头指针

    scanf("%d", &N);           // 读取学生人数
    head = createlist(N);      // 创建包含N个学生的链表
    scanf("%s", x);            // 读取要查询的学号
    search(head, x);           // 在链表中查询该学号的成绩

    return 0;
}
