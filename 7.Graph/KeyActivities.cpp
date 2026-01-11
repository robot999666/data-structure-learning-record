// 假定一个工程项目由一组子任务构成，子任务之间有的可以并行执行，有的必须在完成了其它一些子任务后才能执行。
//“任务调度”包括一组子任务、以及每个子任务可以执行所依赖的子任务集。

// 比如完成一个专业的所有课程学习和毕业设计可以看成一个本科生要完成的一项工程，
//各门课程可以看成是子任务。有些课程可以同时开设，比如英语和C程序设计，它们没有必须先修哪门的约束；有些课程则不可以同时开设，因为它们有先后的依赖关系，比如C程序设计和数据结构两门课，必须先学习前者。

// 但是需要注意的是，对一组子任务，并不是任意的任务调度都是一个可行的方案。比如方案中存在“子任务A依赖于子任务B，子任务B依赖于子任务C，子任务C又依赖于子任务A”，那么这三个任务哪个都不能先执行，这就是一个不可行的方案。

// 任务调度问题中，如果还给出了完成每个子任务需要的时间，则我们可以算出完成整个工程需要的最短时间。
//在这些子任务中，有些任务即使推迟几天完成，也不会影响全局的工期；但是有些任务必须准时完成，否则整个项目的工期就要因此延误，这种任务就叫“关键活动”。

// 请编写程序判定一个给定的工程项目的任务调度是否可行；如果该调度方案可行，则计算完成整个工程项目需要的最短时间，并输出所有的关键活动。

// 输入格式:
// 输入第1行给出两个正整数N(≤100)和M，其中N是任务交接点（即衔接相互依赖的两个子任务的节点，例如：若任务2要在任务1完成后才开始，则两任务之间必有一个交接点）的数量。交接点按1-N编号，M是子任务的数量，依次编号为1-M。随后M行，每行给出了3个正整数，分别是该任务开始和完成涉及的交接点编号以及该任务所需的时间，整数间用空格分隔。

// 输出格式:
// 如果任务调度不可行，则输出0；否则第1行输出完成整个工程项目需要的时间，第2行开始输出所有关键活动，每个关键活动占一行，按格式“V->W”输出，其中V和W为该任务开始和完成涉及的交接点编号。关键活动输出的顺序规则是：任务开始的交接点编号小者优先，起点编号相同时，与输入时任务的顺序相反。

// 输入样例:
// 7 8
// 1 2 4
// 1 3 3
// 2 4 5
// 3 4 3
// 4 5 1
// 4 6 6
// 5 7 5
// 6 7 2
// 输出样例:
// 17
// 1->2
// 2->4
// 4->6
// 6->7

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXV 101
#define MAXE 1001
#define INFINITY 9999999

typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef struct ArcNode {
    int adjvex;
    struct ArcNode* nextarc;
    int weight;
} ArcNode;

typedef struct VexNode {
    ArcNode* firstarc;
} VexNode;

typedef struct {
    VexNode xlist[MAXV];
    int vexnum, arcnum;
} ALGraph;

int edge_u[MAXE], edge_v[MAXE], edge_w[MAXE], edge_idx[MAXE];
int edge_count = 0;

int ve[MAXV], vl[MAXV];

typedef int SElemType;
typedef struct {
    SElemType *base;
    SElemType *top;
    int stacksize;
} Stack;

Status InitStack(Stack &s) {
    s.base = (SElemType *)malloc(MAXV * sizeof(SElemType));
    if (!s.base) exit(OVERFLOW);
    s.top = s.base;
    s.stacksize = MAXV;
    return OK;
}

Status GetTop(Stack s, SElemType &e) {
    if (s.base == s.top) return ERROR;
    e = *(s.top - 1);
    return OK;
}

Status Push(Stack &s, SElemType e) {
    if (s.top - s.base >= s.stacksize) return ERROR; /* overflow */
    *s.top++ = e;
    return OK;
}

Status Pop(Stack &s, SElemType &e) {
    if (s.top == s.base) return ERROR;
    e = *(--s.top);
    return OK;
}

Status StackEmpty(Stack s) {
    if (s.top == s.base) return TRUE;
    else return FALSE;
}

void InsertArc(ALGraph &G, int u, int v, int w) {
    ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex = v;
    p->weight = w;
    p->nextarc = G.xlist[u].firstarc;
    G.xlist[u].firstarc = p;
}

Status TopologicalOrder(ALGraph G, Stack &T) {
    int indegree[MAXV];
    int i, v, k;
    ArcNode* p;
    Stack S;

    for (i = 1; i <= G.vexnum; i++) indegree[i] = 0;
    for (i = 1; i <= G.vexnum; i++) {
        p = G.xlist[i].firstarc;
        while (p) {
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
    }

    InitStack(S);
    InitStack(T);

    for (i = 1; i <= G.vexnum; i++)
        if (indegree[i] == 0) Push(S, i);

    for (i = 1; i <= G.vexnum; i++) ve[i] = 0;

    int count = 0;
    while (!StackEmpty(S)) {
        Pop(S, v);
        Push(T, v); 
        count++;
        p = G.xlist[v].firstarc;
        while (p) {
            k = p->adjvex;
            indegree[k]--;
            if (indegree[k] == 0)
                Push(S, k);
            if (ve[v] + p->weight > ve[k])
                ve[k] = ve[v] + p->weight;
            p = p->nextarc;
        }
    }

    if (count < G.vexnum) return FALSE; 
    else return TRUE;
}

Status CriticalPath(ALGraph G) {
    Stack T;
    if (!TopologicalOrder(G, T)) {
        printf("0\n");
        return ERROR;
    }

    int project_time = 0;
    int i;
    for (i = 1; i <= G.vexnum; i++)
        if (ve[i] > project_time) project_time = ve[i];

    for (i = 1; i <= G.vexnum; i++) vl[i] = project_time;

    int j, k, dut;
    while (!StackEmpty(T)) {
        Pop(T, j);
        ArcNode* p = G.xlist[j].firstarc;
        while (p) {
            k = p->adjvex;
            dut = p->weight;
            if (vl[k] - dut < vl[j])
                vl[j] = vl[k] - dut;
            p = p->nextarc;
        }
    }

    typedef struct { int u, v, idx; } Crit;
    Crit crits[MAXE];
    int critn = 0;
    for (i = 1; i <= edge_count; i++) {
        int u = edge_u[i], v = edge_v[i], w = edge_w[i];
        int ee = ve[u];
        int el = vl[v] - w;
        if (ee == el) {
            crits[critn].u = u;
            crits[critn].v = v;
            crits[critn].idx = edge_idx[i];
            critn++;
        }
    }

    if (critn > 1) {
        int swapped;
        do {
            swapped = 0;
            for (i = 0; i < critn - 1; i++) {
                int should_swap = 0;
                if (crits[i].u > crits[i+1].u) should_swap = 1;
                else if (crits[i].u == crits[i+1].u && crits[i].idx < crits[i+1].idx) should_swap = 1;
                if (should_swap) {
                    Crit tmp = crits[i];
                    crits[i] = crits[i+1];
                    crits[i+1] = tmp;
                    swapped = 1;
                }
            }
        } while (swapped);
    }

    printf("%d\n", project_time);
    for (i = 0; i < critn; i++) {
        printf("%d->%d\n", crits[i].u, crits[i].v);
    }

    return OK;
}

int main() {
    ALGraph G;
    int N, M;
    int i;
    for (i = 0; i < MAXV; i++) G.xlist[i].firstarc = NULL;
    G.vexnum = G.arcnum = 0;
    if (scanf("%d %d", &N, &M) != 2) return 0;
    G.vexnum = N;
    G.arcnum = M;

    edge_count = 0;
    for (i = 1; i <= M; i++) {
        int u, v, w;
        if (scanf("%d %d %d", &u, &v, &w) != 3) return 0;
        edge_count++;
        edge_u[edge_count] = u;
        edge_v[edge_count] = v;
        edge_w[edge_count] = w;
        edge_idx[edge_count] = i; 
        InsertArc(G, u, v, w);
    }

    CriticalPath(G);

    return 0;
}