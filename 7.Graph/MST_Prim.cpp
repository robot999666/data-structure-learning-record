// 用Prim算法从最后一个顶点出发计算无向图的最小生成树。无向图采用邻接矩阵方式存储，999表示无穷大。

// 输入格式:
// 输入共3部分：图中顶点的个数、顶点信息和邻接矩阵。顶点个数不超过30.

// 输出格式:
// 输出最小生成树中的边序列（用"%s %s\n"格式）

// 输入样例:
// 6
// v1
// v2
// v3
// v4
// v5
// v6
// 999 6 1 5 999 999
// 6 999 5 999 3 999
// 1 5 999 5 6 4
// 5 999 5 999 999 2
// 999 3 6 999 999 6
// 999 999 4 2 6 999
// 输出样例:
// v6 v4
// v6 v3
// v3 v1
// v3 v2
// v2 v5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Status;         // 定义状态类型
#define TRUE 1              // 真值定义
#define FALSE 0             // 假值定义
#define OK 1                // 操作成功
#define ERROR 0             // 操作失败
#define OVERFLOW -2         // 内存溢出

const int MAXV = 31;        // 最大顶点数

#define INFINITY 999        // 无穷大定义

typedef char VertexType[15]; // 顶点类型定义为字符串，最长14字符

typedef struct              // 图的邻接矩阵存储结构
{
    VertexType vexs[MAXV];  // 顶点数组
    int arcs[MAXV][MAXV];   // 邻接矩阵
    int vexnum, arcnum;     // 顶点数和边数
} MGraph;

typedef struct              // Prim算法中的辅助结构体
{
    VertexType adjvex;      // 连接该顶点的邻接顶点
    int lowcost;            // 该顶点到生成树的边的权值
} Closedge;

Status LocateVex(MGraph G, VertexType u)  // 查找顶点u在图G中的位置
{
    for (int i = 0; i < G.vexnum; i++)  // 遍历所有顶点
    {
        if (strcmp(G.vexs[i], u) == 0)  // 如果找到匹配的顶点
            return i;                  // 返回顶点索引
    }
    return -1;                         // 未找到返回-1
}

void MiniSpanTree_PRIM(MGraph G, VertexType u)  // Prim算法求最小生成树
{
    int k, i, j;
    Closedge closedge[MAXV];  // 定义辅助数组
    k = LocateVex(G, u);      // 找到起始顶点u的位置
    for (i = 0; i < G.vexnum; i++)  // 初始化辅助数组
    {
        strcpy(closedge[i].adjvex, G.vexs[k]);  // 设置邻接顶点为起始顶点
        closedge[i].lowcost = G.arcs[k][i];     // 设置到起始顶点的边权
    }
    closedge[k].lowcost = 0;  // 起始顶点已加入生成树，设为0
    for (i = 1; i < G.vexnum; i++)  // 循环n-1次，添加n-1条边
    {
        int min = INFINITY;     // 初始化最小值为无穷大
        int min_index = -1;     // 最小值对应的顶点索引
        for (j = 0; j < G.vexnum; j++)  // 寻找当前最小边的顶点
        {
            if (closedge[j].lowcost != 0 && closedge[j].lowcost < min)  // 未加入且边权最小
            {
                min = closedge[j].lowcost;  // 更新最小值
                min_index = j;              // 记录索引
            }
        }
        if (min_index == -1)     // 如果没有找到可连接的顶点，说明图不连通
            break;               // 退出循环
        k = min_index;           // 选中的顶点
        printf("%s %s\n", closedge[k].adjvex, G.vexs[k]);  // 输出新加入的边
        closedge[k].lowcost = 0; // 将该顶点标记为已加入生成树
        for (j = 0; j < G.vexnum; j++)  // 更新其他顶点的lowcost
        {
            if (closedge[j].lowcost != 0 && G.arcs[k][j] < closedge[j].lowcost)  // 如果有更短的边
            {
                closedge[j].lowcost = G.arcs[k][j];  // 更新边权
                strcpy(closedge[j].adjvex, G.vexs[k]); // 更新邻接顶点
            }
        }
    }
}

int main()  // 主函数
{
    MGraph G;                    // 定义图结构
    scanf("%d", &G.vexnum);      // 读取顶点数
    getchar();                   // 消耗换行符
    for (int i = 0; i < G.vexnum; i++)  // 读取顶点信息
        scanf("%s", G.vexs[i]);
    for (int i = 0; i < G.vexnum; i++)  // 读取邻接矩阵
        for (int j = 0; j < G.vexnum; j++)
            scanf("%d", &G.arcs[i][j]);
    MiniSpanTree_PRIM(G, G.vexs[G.vexnum - 1]);  // 从最后一个顶点开始Prim算法
    return 0;                    // 返回0表示程序正常结束
}
