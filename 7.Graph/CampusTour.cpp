// 有一个校园导游图，景点（顶点）个数不超过20个。景点要包含名称、简介等；边表示路径，存放路径长度。要求能够查询任意两个景点之间最短路径。如果没有路径则输出999.

// 输入格式:
// 输入共4部分。
// 第一部分给出顶点个数；
// 第二部分是各个顶点的值；
// 第三部分是邻接矩阵；
// 第四部分是用空格隔开的两个顶点，需要输出这两个顶点之间的最短路径。

// 输出格式:
// 在一行中输出顶点之间的最短路径。

// 输入样例:
// 图7.35

// 6
// v0
// v1
// v2
// v3
// v4
// v5
// 999 999 10 999 30 100
// 999 999 5 999 999 999
// 999 999 999 50 999 999
// 999 999 999 999 999 10
// 999 999 999 20 999 60
// 999 999 999 999 999 999
// v0 v5
// 输出样例:
// 60

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

const int MAXV = 21;

#define INFINITY 999 

typedef  char VertexType[15];

typedef struct
{
    VertexType vexs[MAXV];   
    int arcs[MAXV][MAXV];
    int vexnum, arcnum;  
} MGraph;

typedef struct
{
    VertexType adjvex;
    int lowcost;
} Closedge;

Status LocateVex(MGraph G, VertexType u)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        if (strcmp(G.vexs[i], u) == 0)
            return i;
    }
    return -1;
}

typedef int PathMatrix[MAXV][MAXV][MAXV];
typedef int DistancMatrix[MAXV][MAXV];

void ShortestPath_FLOYD(MGraph G,PathMatrix &P,DistancMatrix &D){
    for(int i=0;i<G.vexnum;i++)
        for(int j=0;j<G.vexnum;j++)
        {
            D[i][j]=G.arcs[i][j];
            for(int k=0;k<G.vexnum;k++) P[i][j][k]=FALSE;
            if(D[i][j]<INFINITY) {
                P[i][j][i]=TRUE;
                P[i][j][j]=TRUE;
            }
        }
    for(int k=0;k<G.vexnum;k++)
        for(int i=0;i<G.vexnum;i++)
            for(int j=0;j<G.vexnum;j++)
                if(D[i][k]+D[k][j]<D[i][j])
                {
                    D[i][j]=D[i][k]+D[k][j];
                    for(int m=0;m<G.vexnum;m++)
                        P[i][j][m]=P[i][k][m]||P[k][j][m];
                }
}

int main()
{
    MGraph G;
    scanf("%d", &G.vexnum);
    G.arcnum = 0;
    for (int i = 0; i < G.vexnum; i++)
        scanf("%s", G.vexs[i]);
    for (int i = 0; i < G.vexnum; i++)
        for (int j = 0; j < G.vexnum; j++)
        {
            scanf("%d", &G.arcs[i][j]);
            if (G.arcs[i][j] != INFINITY)
                G.arcnum++;
        }
    G.arcnum /= 2;

    VertexType v1, v2;
    scanf("%s %s", v1, v2);
    int i = LocateVex(G, v1);
    int j = LocateVex(G, v2);

    PathMatrix P;
    DistancMatrix D;
    ShortestPath_FLOYD(G, P, D);

    if (D[i][j] < INFINITY)
        printf("%d\n", D[i][j]);
    else
        printf("999\n");

    return 0;
}