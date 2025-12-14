// 设顺序存储的二叉树中有编号为 i 和 j 的两个结点，请设计算法求出它们最近的公共祖先结点的编号和值。

// 输入格式:
// 第 1 行给出正整数 n（≤1000），即顺序存储的最大容量；第 2 行给出 n 个非负整数，其间以空格分隔。其中 0 代表二叉树中的空结点（如果第 1 个结点为 0，则代表一棵空树）；第 3 行给出一对结点编号 i 和 j。

// 题目保证输入正确对应一棵二叉树，且 1≤i,j≤n。

// 输出格式:
// 如果 i 或 j 对应的是空结点，则输出 ERROR: T[x] is NULL，其中 x 是 i 或 j 中先发现错误的那个编号；否则在一行中输出编号为 i 和 j 的两个结点最近的公共祖先结点的编号和值，其间以 1 个空格分隔。

// 输入样例1：
// 15
// 4 3 5 1 10 0 7 0 2 0 9 0 0 6 8
// 11 4
// 输出样例1：
// 2 3
// 输入样例2：
// 15
// 4 3 5 1 0 0 7 0 2 0 9 0 0 6 8
// 12 8
// 输出样例2：
// ERROR: T[12] is NULL

#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    int tree[n + 1];
    for (int i = 1; i <= n; i++)
        scanf("%d", &tree[i]);
    int i, j;
    scanf("%d %d", &i, &j);
    if (tree[i] == 0)
        printf("ERROR: T[%d] is NULL\n", i);
    else if (tree[j] == 0)
        printf("ERROR: T[%d] is NULL\n", j);
    else
    {
        int a = i, b = j;
        while (a != b)
        {
            if (a > b)
                a /= 2;
            else
                b /= 2;
        }
        printf("%d %d\n", a, tree[a]);
    }
    return 0;
}