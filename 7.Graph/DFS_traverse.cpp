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
    char vexs[MAXV][15];   
    int arcs[MAXV][MAXV];    
    int vexnum, arcnum;      
} MGraph;

bool visited[MAXV]; 

void DFS(MGraph G, int v)
{
    printf("%s ", G.vexs[v]); 
    visited[v] = true;      
    for (int w = 0; w < G.vexnum; w++)
    {
        if (G.arcs[v][w] !=0 && !visited[w]) 
            DFS(G, w);                     
    }
}

void DFSTraverse(MGraph G)
{
    for (int v = 0; v < G.vexnum; v++)
        visited[v] = false; 
    for (int v = 0; v < G.vexnum; v++)
    {
        if (!visited[v]) 
            DFS(G, v);     
    }
}

int main()
{
    MGraph G;
    scanf("%d", &G.vexnum);
    for (int i = 0; i < G.vexnum; i++)
        scanf("%s", G.vexs[i]);
    for (int i = 0; i < G.vexnum; i++)
        for (int j = 0; j < G.vexnum; j++)
            scanf("%d", &G.arcs[i][j]);
    DFSTraverse(G);     
    return 0;
}
