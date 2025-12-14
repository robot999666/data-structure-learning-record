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
    char vexs[MAXV][15];   
    int arcs[MAXV][MAXV];    
    int vexnum, arcnum;      
} MGraph;

bool visited[MAXV];

void DFS(MGraph G, int v)
{
    visited[v] = true;      
    for (int w = 0; w < G.vexnum; w++)
    {
        if (G.arcs[v][w] !=0 && !visited[w]) 
            DFS(G, w);                     
    }
}

int main()
{
    int N, D;
    scanf("%d %d", &N, &D);
    int points[N][2];
    for (int i = 0; i < N; i++)
        scanf("%d %d", &points[i][0], &points[i][1]);
    MGraph G;
    G.vexnum = N + 2;                       //包括:起点（N）、鳄鱼（0 ~ N-1）、终点（N+1）
    G.arcnum = 0;
    memset(G.arcs, 0, sizeof(G.arcs));
    for (int i = 0; i < N; i++)
    {
        double dist_start = sqrt(points[i][0] * points[i][0] + points[i][1] * points[i][1]);
        if (dist_start <= 7.5 + D)
            G.arcs[N][i] = 1;               //起点到鳄鱼
        double dist_end = 50 - fabs(points[i][0]);
        if (dist_end <= D || (50 - fabs(points[i][1])) <= D)
            G.arcs[i][N + 1] = 1;           //鳄鱼到终点
        for (int j = i + 1; j < N; j++)
        {
            double dist = sqrt((points[i][0] - points[j][0]) * (points[i][0] - points[j][0]) +
                               (points[i][1] - points[j][1]) * (points[i][1] - points[j][1]));
            if (dist <= D)
            {
                G.arcs[i][j] = 1;
                G.arcs[j][i] = 1;
            }                               //鳄鱼到鳄鱼
        }
    }
    for (int v = 0; v < G.vexnum; v++)
        visited[v] = false;
    DFS(G, N);                             //从起点开始DFS
    if (visited[N + 1])
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}