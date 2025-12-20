// 有向图采用邻接表结构，请根据输入建立链接表，输出广度优先遍历序列。顶点个数不超过30.

// 输入格式:
// 输入共3部分，分别是图中顶点的个数、弧的条数和每一条弧。

// 输出格式:
// 用“%s ”输出遍历序列（包含一个空格）中的顶点。

// 输入样例:
// 图7.11

// 4 7
// v1
// v2
// v3
// v4
// v1 v2
// v1 v3
// v3 v1
// v3 v4
// v4 v1
// v4 v2
// v4 v3
// 输出样例:
// v1 v3 v2 v4 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义状态常量
typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

#define MAX_VERTEX_NUM 30
typedef char VertexType[5];

// 弧节点结构体
typedef struct ArcNode{
    int adjvex;  // 邻接顶点索引
    struct ArcNode *nextarc;  // 下一个弧节点
} ArcNode;

// 顶点节点结构体
typedef struct VNode{
    VertexType data;  // 顶点数据
    ArcNode *firstarc;  // 第一个弧节点
} VNode, Adjlist[MAX_VERTEX_NUM];

// 图结构体
typedef struct{
    Adjlist vertices;  // 邻接表
    int vexnum, arcnum;  // 顶点数和弧数
    int kind;  // 图的种类
} ALGraph;

// 访问标记数组
int visited[MAX_VERTEX_NUM];

// 查找顶点在图中的索引
Status LocateVex(ALGraph G, char *v){
    for(int i=0;i<G.vexnum;++i){
        if(strcmp(G.vertices[i].data,v)==0) return i;
    }
    return ERROR;
}

// 创建邻接表
void CreateAL(ALGraph &G){
    scanf("%d %d", &G.vexnum, &G.arcnum);
    for(int i=0;i<G.vexnum;++i){
        scanf("%s", G.vertices[i].data);
        G.vertices[i].firstarc = NULL;
    }
    for(int k=0;k<G.arcnum;++k){
        char v1[5], v2[5];
        scanf("%s %s", v1, v2);
        int i = LocateVex(G, v1);
        int j = LocateVex(G, v2);
        ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p;
    }
}

// 队列结构体
typedef struct {
    int data[MAX_VERTEX_NUM];
    int front, rear;
} Queue;

void InitQueue(Queue *Q){ Q->front = Q->rear = 0; }
int QueueEmpty(Queue *Q){ return Q->front == Q->rear; }
void EnQueue(Queue *Q, int e){ Q->data[Q->rear++] = e; }
int DeQueue(Queue *Q, int &e){ e = Q->data[Q->front++]; return OK; }

// 广度优先遍历
void BFSTraverse(ALGraph *G){
    for(int i=0;i<G->vexnum;++i) visited[i]=FALSE;
    Queue Q;
    InitQueue(&Q);
    for(int i=0;i<G->vexnum;++i){
        if(!visited[i]){
            visited[i]=1;
            printf("%s ", G->vertices[i].data);
            EnQueue(&Q, i);
            while(!QueueEmpty(&Q)){
                int u;
                DeQueue(&Q, u);
                ArcNode *p = G->vertices[u].firstarc;
                while(p){
                    int w = p->adjvex;
                    if(!visited[w]){
                        visited[w]=1;
                        printf("%s ", G->vertices[w].data);
                        EnQueue(&Q, w);
                    }
                    p = p->nextarc;
                }
            }
        }
    }
    printf("\n");
}

int main(){
    ALGraph G;
    CreateAL(G);
    BFSTraverse(&G);
    for(int i=0;i<G.vexnum;++i){
        ArcNode *p = G.vertices[i].firstarc;
        while(p){
            ArcNode *t = p;
            p = p->nextarc;
            free(t);
        }
    }
    return 0;
}