// 无向图(网)采用邻接矩阵结构。假设总是从第一个顶点出发遍历。顶点个数不超过30个。

// 输入格式:
// 输入共3部分，依次给出图中顶点的个数、顶点信息和邻接矩阵。

// 输出格式:
// 输出是遍历序列，用“%s ”输出一个顶点（包含一个空格）。

// 输入样例:
// 8
// v1
// v2
// v3
// v4
// v5
// v6
// v7
// v8
// 0 1 1 0 0 0 0 0
// 1 0 0 1 1 0 0 0
// 1 0 0 0 0 1 1 0
// 0 1 0 0 0 0 0 1
// 0 1 0 0 0 0 0 1
// 0 0 1 0 0 0 1 0
// 0 0 1 0 0 1 0 0
// 0 0 0 1 1 0 0 0
// 输出样例:
// v1 v2 v4 v8 v5 v3 v6 v7 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int MAXV = 31;

typedef struct
{
    char vexs[MAXV][15];   // 顶点信息数组，每个顶点名称不超过15个字符
    int arcs[MAXV][MAXV];  // 邻接矩阵，存储顶点间的边信息（0表示无边，1表示有边）
    int vexnum, arcnum;    // 图的顶点数和边数
} MGraph;

bool visited[MAXV];       // 访问标记数组，标记顶点是否已被访问 

// 深度优先搜索函数
// 从顶点v开始进行深度优先遍历
void DFS(MGraph G, int v)
{
    printf("%s ", G.vexs[v]);  // 输出当前访问的顶点
    visited[v] = true;         // 标记顶点v为已访问

    // 遍历所有可能的邻接顶点
    for (int w = 0; w < G.vexnum; w++)
    {
        // 如果顶点w与v相邻且未被访问，则递归访问w
        if (G.arcs[v][w] !=0 && !visited[w])
            DFS(G, w);  // 递归调用DFS访问邻接顶点
    }
}

// 深度优先遍历函数
// 对整个图进行深度优先遍历，处理非连通图的情况
void DFSTraverse(MGraph G)
{
    // 初始化所有顶点的访问标记为false
    for (int v = 0; v < G.vexnum; v++)
        visited[v] = false;

    // 对每个顶点进行检查，如果未访问则启动DFS
    for (int v = 0; v < G.vexnum; v++)
    {
        if (!visited[v])  // 如果顶点v未被访问
            DFS(G, v);   // 从顶点v开始进行深度优先搜索
    }
}

int main()
{
    MGraph G;  // 定义图结构变量

    // 读取顶点个数
    scanf("%d", &G.vexnum);

    // 读取所有顶点的信息（顶点名称）
    for (int i = 0; i < G.vexnum; i++)
        scanf("%s", G.vexs[i]);

    // 读取邻接矩阵，表示图的边信息
    for (int i = 0; i < G.vexnum; i++)
        for (int j = 0; j < G.vexnum; j++)
            scanf("%d", &G.arcs[i][j]);

    // 执行深度优先遍历并输出遍历序列
    DFSTraverse(G);

    return 0;
}
