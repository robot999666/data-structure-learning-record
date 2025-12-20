// 给定一个带整数键值的链表 L，你需要把其中绝对值重复的键值结点删掉。即对每个键值 K，只有第一个绝对值等于 K 的结点被保留。同时，所有被删除的结点须被保存在另一个链表上。例如给定 L 为 21→-15→-15→-7→15，你需要输出去重后的链表 21→-15→-7，还有被删除的链表 -15→15。

// 输入格式：
// 输入在第一行给出 L 的第一个结点的地址和一个正整数 N（≤10^5，为结点总数）。一个结点的地址是非负的 5 位整数，空地址 NULL 用 -1 来表示。

// 随后 N 行，每行按以下格式描述一个结点：

// 地址 键值 下一个结点
// 其中地址是该结点的地址，键值是绝对值不超过10^4的整数，下一个结点是下个结点的地址。

// 输出格式：
// 首先输出去重后的链表，然后输出被删除的链表。每个结点占一行，按输入的格式输出。

// 输入样例：
// 00100 5
// 99999 -7 87654
// 23854 -15 00000
// 87654 15 -1
// 00000 -15 99999
// 00100 21 23854

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 定义元素类型
typedef int ElemType;

// 链表节点结构体
typedef struct LNode
{
    ElemType data;  // 节点数据（键值）
    int add;        // 节点地址
    int next;       // 下一个节点的地址
} LNode, *LinkList;

// 定义状态常量
typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

// 主函数，实现链表去重
int main()
{
    int N, head, ind, cur;  // N为节点总数，head为头节点地址，ind为索引，cur为当前地址
    int p[100000];          // p数组用于地址到索引的映射
    int repeat[100000] = {0};  // repeat数组标记绝对值是否已出现
    scanf("%d %d", &head, &N);  // 读取头地址和节点数
    if (head == -1)  // 如果链表为空，直接返回
    {
        return 0;
    }
    LNode L[N], L1[N], L2[N];  // L为原始节点数组，L1为去重后链表，L2为删除链表
    int len1 = 0, len2 = 0;    // len1为L1长度，len2为L2长度
    for (int i = 0; i < N; i++)  // 读取所有节点信息
    {
        scanf("%d %d %d", &L[i].add, &L[i].data, &L[i].next);
        p[L[i].add] = i;  // 建立地址到索引的映射
    }
    cur = head;  // 从头节点开始遍历
    while (cur != -1)
    {
        ind = p[cur];  // 获取当前节点的索引
        int key = abs(L[ind].data);  // 计算绝对值作为键
        int flag = 0;
        if (repeat[key] == 0)  // 如果该绝对值未出现
        {
            repeat[key] = 1;  // 标记为已出现
            L1[len1++] = L[ind];  // 添加到去重链表
        }
        else
        {
            L2[len2++] = L[ind];  // 添加到删除链表
        }
        cur = L[ind].next;  // 移动到下一个节点
    }
    // 重建L1的next指针
    for (int k = 1; k < len1; k++)
    {
        L1[k - 1].next = L1[k].add;  // 设置前一个节点的next为下一个节点的地址
    }
    if (len1 > 0)
        L1[len1 - 1].next = -1;  // 最后一个节点的next设为-1
    // 重建L2的next指针
    for (int k = 1; k < len2; k++)
    {
        L2[k - 1].next = L2[k].add;
    }
    if (len2 > 0)
        L2[len2 - 1].next = -1;
    int k;
    // 输出去重后的链表
    if (len1 > 0)
    {
        for (k = 0; k < len1 - 1; k++)
        {
            printf("%05d %d %05d\n", L1[k].add, L1[k].data, L1[k].next);
        }
        printf("%05d %d %d\n", L1[k].add, L1[k].data, L1[k].next);  // 最后一个节点
    }
    // 输出删除的链表
    if (len2 > 0)
    {
        for (k = 0; k < len2 - 1; k++)
        {
            printf("%05d %d %05d\n", L2[k].add, L2[k].data, L2[k].next);
        }
        printf("%05d %d %d\n", L2[k].add, L2[k].data, L2[k].next);
    }
    return 0;
}
