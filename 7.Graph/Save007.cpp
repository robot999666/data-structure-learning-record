// 在老电影“007之生死关头”（Live and Let Die）中有一个情节，007被毒贩抓到一个鳄鱼池中心的小岛上.
// 他用了一种极为大胆的方法逃脱 —— 直接踩着池子里一系列鳄鱼的大脑袋跳上岸去！（据说当年替身演员被最后一条鳄鱼咬住了脚，幸好穿的是特别加厚的靴子才逃过一劫。）

// 设鳄鱼池是长宽为100米的方形，中心坐标为 (0, 0)，且东北角坐标为 (50, 50)。
// 池心岛是以 (0, 0) 为圆心、直径15米的圆。给定池中分布的鳄鱼的坐标、以及007一次能跳跃的最大距离，你需要告诉他是否有可能逃出生天。

// 输入格式：
// 首先第一行给出两个正整数：鳄鱼数量 N（≤100）和007一次能跳跃的最大距离 D。随后 N 行，每行给出一条鳄鱼的 (x,y) 坐标。
// 注意：不会有两条鳄鱼待在同一个点上。

// 输出格式：
// 如果007有可能逃脱，就在一行中输出"Yes"，否则输出"No"。

// 输入样例 1：
// 14 20
// 25 -15
// -25 28
// 8 49
// 29 15
// -35 -2
// 5 28
// 27 -29
// -8 -28
// -20 -35
// -25 -20
// -13 29
// -30 15
// -35 40
// 12 12
// 输出样例 1：
// Yes
// 输入样例 2：
// 4 13
// -12 12
// 12 12
// -12 -12
// 12 -12
// 输出样例 2：
// No

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

const int MAXV = 102;

typedef struct
{
    char vexs[MAXV][15];   // 顶点信息数组（本程序中未使用）
    int arcs[MAXV][MAXV];  // 邻接矩阵，存储顶点间的连通关系（0表示无边，1表示有边）
    int vexnum, arcnum;    // 图的顶点数和边数
} MGraph;

bool visited[MAXV];       // 访问标记数组，标记顶点是否已被访问

// 深度优先搜索函数
// 从顶点v开始进行深度优先遍历，标记所有可达的顶点
void DFS(MGraph G, int v)
{
    visited[v] = true;         // 标记顶点v为已访问

    // 遍历所有可能的邻接顶点
    for (int w = 0; w < G.vexnum; w++)
    {
        // 如果顶点w与v相邻且未被访问，则递归访问w
        if (G.arcs[v][w] !=0 && !visited[w])
            DFS(G, w);  // 递归调用DFS访问邻接顶点
    }
}

int main()
{
    int N, D;  // N:鳄鱼数量, D:007的最大跳跃距离
    scanf("%d %d", &N, &D);

    // 读取所有鳄鱼的坐标
    int points[N][2];  // 存储鳄鱼坐标的二维数组
    for (int i = 0; i < N; i++)
        scanf("%d %d", &points[i][0], &points[i][1]);

    MGraph G;  // 定义图结构
    G.vexnum = N + 2;  // 顶点数：起点(N) + 鳄鱼(0~N-1) + 终点(N+1)
    G.arcnum = 0;      // 边数暂时设为0
    memset(G.arcs, 0, sizeof(G.arcs));  // 初始化邻接矩阵为0

    // 构建图的边关系
    for (int i = 0; i < N; i++)
    {
        // 计算第i只鳄鱼到起点的距离
        double dist_start = sqrt(points[i][0] * points[i][0] + points[i][1] * points[i][1]);
        // 如果距离小于等于7.5+D（小岛半径+跳跃距离），则起点可以跳到这只鳄鱼
        if (dist_start <= 7.5 + D)
            G.arcs[N][i] = 1;  // 起点(N)到鳄鱼(i)的边

        // 计算第i只鳄鱼到终点的距离（到岸边的距离）
        double dist_end = 50 - fabs(points[i][0]);  // 到右岸的距离
        // 如果到右岸或上岸的距离小于等于D，则可以跳到岸边
        if (dist_end <= D || (50 - fabs(points[i][1])) <= D)
            G.arcs[i][N + 1] = 1;  // 鳄鱼(i)到终点(N+1)的边

        // 计算第i只鳄鱼到其他鳄鱼的距离
        for (int j = i + 1; j < N; j++)
        {
            double dist = sqrt((points[i][0] - points[j][0]) * (points[i][0] - points[j][0]) +
                               (points[i][1] - points[j][1]) * (points[i][1] - points[j][1]));
            // 如果两只鳄鱼间的距离小于等于D，则可以从一只跳到另一只
            if (dist <= D)
            {
                G.arcs[i][j] = 1;  // 双向边
                G.arcs[j][i] = 1;
            }
        }
    }
    // 初始化访问标记
    for (int v = 0; v < G.vexnum; v++)
        visited[v] = false;

    // 从起点(N)开始进行深度优先搜索
    DFS(G, N);

    // 检查是否能到达终点(N+1)
    if (visited[N + 1])
        printf("Yes\n");  // 可以逃脱
    else
        printf("No\n");   // 无法逃脱

    return 0;
}