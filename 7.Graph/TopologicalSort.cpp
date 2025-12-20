// 已知一个有向图，本题目要求完成拓扑排序算法7.12 。  顶点个数不超过30个。

// 输入格式:
// 输入分三部分：
// 第一行是图中顶点的个数、弧的条数
// 接着是每个顶点的信息
// 最后是每一条弧

// 输出格式:
// 输出的是顶点的拓扑序列，每个顶点后面有一个空格。不能完成拓扑排序的输出error

// 输入样例:
// 图7.28

// 6 8
// v1
// v2
// v3
// v4
// v5
// v6
// v1 v4
// v6 v4
// v1 v2
// v1 v3
// v4 v5
// v6 v5
// v3 v2
// v3 v5
// 输出样例:
// v6 v1 v4 v3 v2 v5 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Status;
#define TRUE 1  
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAX_VERTEX_NUM 30
#define STACK_INIT_SIZE 100  
#define STACKINCREMENT 10   

typedef char VertexType[5];

typedef struct ArcNode{
    int adjvex;  // 邻接顶点索引
    struct ArcNode *nextarc;  // 下一个邻接边
} ArcNode;

typedef struct VNode{
    VertexType data;  // 顶点数据
    ArcNode *firstarc;  // 第一条邻接边
} VNode, Adjlist[MAX_VERTEX_NUM];

typedef struct{
    Adjlist vertices;  // 邻接表
    int vexnum, arcnum;  // 顶点数和边数
} ALGraph;

int indegree[MAX_VERTEX_NUM];  // 入度数组

// 定位顶点，返回索引
Status LocateVex(ALGraph &G, char *v){ 
    for(int i=0;i<G.vexnum;++i){
        if(strcmp(G.vertices[i].data, v)==0) return i;
    }
    return ERROR;
}

// 创建邻接表
void CreateAL(ALGraph &G){
    scanf("%d %d", &G.vexnum, &G.arcnum);
    for(int i=0;i<G.vexnum;++i){
        if (scanf("%s", G.vertices[i].data) != 1) {
            exit(1);
        }
        G.vertices[i].firstarc = NULL;
    }
    for(int k=0;k<G.arcnum;++k){
        char v1[5], v2[5];
        if (scanf("%s %s", v1, v2) != 2) {
            exit(1);
        }
        int i = LocateVex(G, v1);
        int j = LocateVex(G, v2);
        ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
        if (!p) exit(OVERFLOW);
        p->adjvex = j;
        p->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p;
    }
}

// 计算入度
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
    if (s.top - s.base + 1 >= s.stacksize)
    {
        s.head = (SElemType*)realloc(s.head, (s.stacksize + STACKINCREMENT + 1) * sizeof(SElemType));
        if (!s.head) exit(OVERFLOW);
        s.base = s.head + 1;                   
        s.top = s.base + (s.stacksize - 1);
        s.stacksize += STACKINCREMENT;      
    }
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

// 拓扑排序
Status TopologicalSort(ALGraph &G){
    FindInDegree(G, indegree);  // 计算入度
    Stack S;
    InitStack(S);
    for(int i=0;i<G.vexnum;++i){
        if(indegree[i]==0) Push(S, i);  // 入度为0的顶点入栈
    }
    int count = 0;
    while(!StackEmpty(S)){
        int i;
        Pop(S, i);
        printf("%s ", G.vertices[i].data);  // 输出顶点
        count++;
        ArcNode *p = G.vertices[i].firstarc;
        while(p){
            int k = p->adjvex;
            indegree[k]--;  // 减少邻接顶点的入度
            if(indegree[k]==0) Push(S, k);  // 入度为0则入栈
            p = p->nextarc;
        }
    }
    DestroyStack(S);
    if(count < G.vexnum){
        printf("error");  // 有环
        return ERROR;
    }
    return OK;
}

// 主函数
int main(){
    ALGraph G; 
    CreateAL(G);  // 创建图
    Status result = TopologicalSort(G);  // 执行拓扑排序
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