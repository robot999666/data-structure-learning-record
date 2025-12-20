// 一个项目由若干个任务组成，任务之间有先后依赖顺序。项目经理需要设置一系列里程碑，在每个里程碑节点处检查任务的完成情况，并启动后续的任务。现给定一个项目中各个任务之间的关系，请你计算出这个项目的最早完工时间。

// 输入格式：
// 首先第一行给出两个正整数：项目里程碑的数量 N（≤100）和任务总数 M。这里的里程碑从 0 到 N−1 编号。随后 M 行，每行给出一项任务的描述，格式为“任务起始里程碑 任务结束里程碑 工作时长”，三个数字均为非负整数，以空格分隔。

// 输出格式：
// 如果整个项目的安排是合理可行的，在一行中输出最早完工时间；否则输出"Impossible"。

// 输入样例 1：
// 9 12
// 0 1 6
// 0 2 4
// 0 3 5
// 1 4 1
// 2 4 1
// 3 5 2
// 5 4 0
// 4 6 9
// 4 7 7
// 5 7 4
// 6 8 2
// 7 8 4
// 输出样例 1：
// 18
// 输入样例 2：
// 4 5
// 0 1 1
// 0 2 2
// 2 1 3
// 1 3 4
// 3 2 5
// 输出样例 2：
// Impossible

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int Status;
#define TRUE 1  
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAX_VERTEX_NUM 105  
#define STACK_INIT_SIZE 200 
#define STACKINCREMENT 10  

typedef struct ArcNode{
    int adjvex;  // 邻接顶点索引
    int weight;  // 边的权重
    struct ArcNode *nextarc;  // 下一个邻接边
} ArcNode;

typedef struct VNode{
    int data;  // 顶点数据
    ArcNode *firstarc;  // 第一条邻接边
} VNode, Adjlist[MAX_VERTEX_NUM];

typedef struct{
    Adjlist vertices;  // 邻接表
    int vexnum, arcnum;  // 顶点数和边数
    int kind;  // 图的种类
} ALGraph;

// 创建邻接表表示的图
void CreateAL(ALGraph &G){
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) exit(0);
    G.vexnum = N;
    G.arcnum = M;
    for(int i=0;i<G.vexnum;++i){
        G.vertices[i].data = i; 
        G.vertices[i].firstarc = NULL;
    }
    for(int k=0;k<G.arcnum;++k){
        int v1, v2, weight;
        if (scanf("%d %d %d", &v1, &v2, &weight) != 3) exit(0);
        if (v1 < 0 || v1 >= G.vexnum || v2 < 0 || v2 >= G.vexnum) continue;
        ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
        if (!p) exit(OVERFLOW);
        p->adjvex = v2;
        p->weight = weight;
        p->nextarc = G.vertices[v1].firstarc;
        G.vertices[v1].firstarc = p;
    }
}

typedef int SElemType;
typedef struct
{
    SElemType* head;   
    SElemType* base;    
    SElemType* top;    
    int stacksize;     
} Stack;

Status InitStack(Stack &s)
{
    s.head = (SElemType *)malloc((STACK_INIT_SIZE + 1) * sizeof(SElemType));
    if (!s.head) exit(OVERFLOW);
    s.top = s.head;       
    s.base = s.head + 1;  
    s.stacksize = STACK_INIT_SIZE; 
    return OK;
}

Status StackEmpty(Stack s)
{
    return s.top < s.base ? TRUE : FALSE;
}

Status Push(Stack &s, SElemType e)
{
    *(++s.top) = e;
    return OK;
}

Status Pop(Stack &s, SElemType &e)
{
    if (StackEmpty(s)) return ERROR;  
    e = *(s.top--); 
    return OK;
}

void DestroyStack(Stack &s)
{
    if (s.head) {
        free(s.head);
        s.head = NULL;
        s.base = NULL;
        s.top = NULL;
        s.stacksize = 0;
    }
}

// 计算各顶点的入度
void FindInDegree(ALGraph &G, int indegree[]){ 
    for(int i=0;i<G.vexnum;++i) indegree[i]=0;
    for(int i=0;i<G.vexnum;++i){
        ArcNode *p = G.vertices[i].firstarc;
        while(p){
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
    }
}

// 拓扑排序，返回排序后的顶点序列到栈T中
int TopologicalSort(ALGraph G, Stack &T)
{
    int indegree[MAX_VERTEX_NUM];
    FindInDegree(G, indegree);
    Stack S;
    InitStack(S);
    InitStack(T);
    for(int i=0;i<G.vexnum;++i){
        if(indegree[i]==0) Push(S,i);
    }
    int count=0;
    while(!StackEmpty(S)){
        int v;
        Pop(S,v);
        Push(T,v);    
        count++;
        ArcNode *p = G.vertices[v].firstarc;
        while(p){
            int w = p->adjvex;
            indegree[w]--;
            if(indegree[w]==0) Push(S,w);
            p = p->nextarc;
        }
    }
    DestroyStack(S);
    if(count<G.vexnum) {
        DestroyStack(T);
        return FALSE;
    }
    return TRUE;
}

int ve[MAX_VERTEX_NUM];  // 事件最早发生时间
int vl[MAX_VERTEX_NUM];  // 事件最晚发生时间

// 计算关键路径
Status CriticalPath(ALGraph G){
    Stack T;
    if(!TopologicalSort(G, T)) return ERROR; 
    
    for(int i=0;i<G.vexnum;++i) ve[i]=0;  // 初始化最早时间
    
    Stack temp;
    InitStack(temp);
    while(!StackEmpty(T)){
        int i;
        Pop(T,i);
        Push(temp,i);
    }
    while(!StackEmpty(temp)){
        int i;
        Pop(temp,i);
        ArcNode *p = G.vertices[i].firstarc;
        while(p){
            int k = p->adjvex;
            if(ve[i] + p->weight > ve[k]) ve[k] = ve[i] + p->weight;  // 更新后继的最早时间
            p = p->nextarc;
        }
        Push(T,i);
    }
    DestroyStack(temp);

    int maxv = 0;
    for(int i=0;i<G.vexnum;++i) if(ve[i] > maxv) maxv = ve[i];
    for(int i=0;i<G.vexnum;++i) vl[i] = maxv;  // 初始化最晚时间

    while(!StackEmpty(T)){
        int j;
        Pop(T,j);
        ArcNode *p = G.vertices[j].firstarc;
        while(p){
            int k = p->adjvex;
            if(vl[k] - p->weight < vl[j]) vl[j] = vl[k] - p->weight;  // 更新前驱的最晚时间
            p = p->nextarc;
        }
    }
    DestroyStack(T);
    return OK;
}

// 主函数
int main()
{
    ALGraph G;
    CreateAL(G);  // 创建图
    if(CriticalPath(G)==ERROR){
        printf("Impossible\n");  // 图有环，无法完成
    } 
    else {
        int projectTime = 0;
        for(int i=0;i<G.vexnum;++i) if(ve[i] > projectTime) projectTime = ve[i];  // 找到最大最早时间
        printf("%d\n", projectTime);
    }
    // 释放内存
    for(int i=0; i<G.vexnum; i++){
        ArcNode *p = G.vertices[i].firstarc;
        while(p){
            ArcNode *temp = p;
            p = p->nextarc;
            free(temp);
        }
    }
    return 0;
}