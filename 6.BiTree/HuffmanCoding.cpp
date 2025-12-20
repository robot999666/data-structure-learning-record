#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Status;         // 定义状态类型
#define TRUE 1              // 真值定义
#define FALSE 0             // 假值定义
#define OK 1                // 操作成功
#define ERROR 0             // 操作失败
#define OVERFLOW -2         // 内存溢出

typedef struct              // 哈夫曼树节点结构体定义
{
    unsigned int weight;    // 节点权重
    unsigned int parent;    // 父节点索引
    unsigned int lchild;    // 左孩子索引
    unsigned int rchild;    // 右孩子索引
} HTNode, *HuffmanTree;     // HuffmanTree为指向HTNode的指针类型

typedef char** HuffmanCode; // 哈夫曼编码类型定义（字符指针数组）

void Select(HuffmanTree HT, int n, int *s1, int *s2)  // 选择两个权重最小的节点
{
    int first = 0;                      // 第一个最小权重节点索引
    for (int i = 1; i <= n; i++)        // 找到第一个没有父节点的节点
    {
        if (HT[i].parent == 0)          // 如果该节点没有父节点
        {
            first = i;                  // 记录索引
            break;                      // 找到后跳出
        }
    }
    *s1 = first;                        // 设置第一个最小节点
    for (int i = 1; i <= n; i++)        // 找到权重最小的节点
    {
        if (HT[i].parent == 0 && HT[i].weight < HT[*s1].weight)  // 无父节点且权重更小
        {
            *s1 = i;                    // 更新最小节点索引
        }
    }
    int second = 0;                     // 第二个最小权重节点索引
    for (int i = 1; i <= n; i++)        // 找到第二个没有父节点的节点（排除第一个）
    {
        if (HT[i].parent == 0 && i != *s1)  // 无父节点且不是第一个最小节点
        {
            second = i;                 // 记录索引
            break;                      // 找到后跳出
        }
    }
    *s2 = second;                       // 设置第二个最小节点
    for (int i = 1; i <= n; i++)        // 找到第二小的权重节点
    {
        if (HT[i].parent == 0 && i != *s1 && HT[i].weight < HT[*s2].weight)  // 条件同上
        {
            *s2 = i;                    // 更新第二小节点索引
        }
    }
}

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int n)  // 构建哈夫曼树并生成编码
{
    if (n <= 1) return;              // 如果节点数小于等于1，无需编码
    int m = 2 * n - 1;               // 哈夫曼树总节点数
    HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));  // 分配哈夫曼树内存（索引从1开始）
    int i;                           // 循环变量
    HuffmanTree p;                   // 临时指针
    for (p = HT + 1, i = 1; i <= n; ++i, ++p)  // 初始化叶子节点（前n个）
    {
        scanf("%d", &(p->weight));   // 读取叶子节点权重
        p->parent = p->lchild = p->rchild = 0;  // 初始化父节点和孩子节点为0
    }
    for (; i <= m; ++i, ++p)         // 初始化非叶子节点
    {
        p->weight = p->parent = p->lchild = p->rchild = 0;  // 初始化所有字段为0
    }
    int s1, s2;                      // 两个最小权重节点的索引
    for (i = n + 1; i <= m; ++i)     // 构建哈夫曼树
    {
        Select(HT, i - 1, &s1, &s2); // 选择两个最小权重的节点
        HT[s1].parent = i;            // 设置第一个节点的父节点
        HT[s2].parent = i;            // 设置第二个节点的父节点
        HT[i].lchild = s1;            // 设置新节点的左孩子
        HT[i].rchild = s2;            // 设置新节点的右孩子
        HT[i].weight = HT[s1].weight + HT[s2].weight;  // 新节点权重为两个孩子权重之和
    }

    HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));  // 分配编码数组内存
    char *cd = (char*)malloc(n * sizeof(char));         // 分配临时编码字符串内存
    cd[n - 1] = '\0';                 // 设置字符串结束符
    int start, c, f;                  // start:编码起始位置, c:当前节点, f:父节点
    for (i = 1; i <= n; ++i)          // 为每个叶子节点生成编码
    {
        start = n - 1;                // 从字符串末尾开始构建编码
        c = i;                        // 当前节点为第i个叶子节点
        f = HT[i].parent;             // 获取父节点
        while (f != 0)                // 从叶子节点向上回溯到根节点
        {
            if (HT[f].lchild == c)    // 如果当前节点是左孩子
                cd[--start] = '0';    // 添加'0'编码
            else                      // 如果是右孩子
                cd[--start] = '1';    // 添加'1'编码
            c = f;                    // 向上移动到父节点
            f = HT[f].parent;         // 获取父节点的父节点
        }
        HC[i] = (char*)malloc((n - start) * sizeof(char));  // 为编码分配内存
        strcpy(HC[i], &cd[start]);     // 复制编码字符串
    }
    free(cd);                         // 释放临时编码字符串内存
}

int main()  // 主函数
{
    int n;                         // 叶子节点数量
    scanf("%d", &n);               // 读取叶子节点数量
    char *str = (char*)malloc((n + 1) * sizeof(char));  // 分配字符数组存储待编码字符
    HuffmanTree HT = NULL;         // 哈夫曼树指针
    HuffmanCode HC = NULL;         // 哈夫曼编码指针
    HuffmanCoding(HT, HC, n);      // 构建哈夫曼树并生成编码
    scanf("%s", str);              // 读取待编码的字符序列
    for (int i = 1; i <= n; ++i)   // 输出每个字符及其哈夫曼编码
    {
        printf("%c:%s\n", str[i - 1], HC[i]);  // 格式：字符:编码
    }
    free(str);                     // 释放字符数组内存
    for (int i = 1; i <= n; ++i)   // 释放每个编码字符串的内存
    {
        free(HC[i]);
    }
    free(HC);                      // 释放编码数组内存
    free(HT);                      // 释放哈夫曼树内存
    return 0;                      // 返回0表示程序正常结束
}