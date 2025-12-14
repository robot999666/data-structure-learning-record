## 程序填空题

### Problem 1
无向图采用邻接矩阵结构存储，本题要求实现无向图的基本操作，请填空。
```c++
#include <stdio.h>
#include <string.h>

// 图的数组(邻接矩阵)存储表示
#define MAX_VERTEX_NUM 20 // 最大顶点个数
enum GraphKind{DG,DN,AG,AN}; // {有向图,有向网,无向图,无向网}

typedef char VertexType[6];

// 顶点关系类型。对无权图，用1(是)或0(否)表示相邻否； 对带权图，则为权值类型
typedef int ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

struct MGraph
{
  VertexType vexs[MAX_VERTEX_NUM]; // 顶点向量
  AdjMatrix arcs; // 邻接矩阵
  int vexnum,arcnum; // 图的当前顶点数和弧数
  GraphKind kind; // 图的种类标志
};

// 图的数组(邻接矩阵)存储基本操作
int LocateVex(MGraph G,VertexType u)
{ // 初始条件:图G存在,u和G中顶点有相同特征
  // 操作结果:若G中存在顶点u,则返回该顶点在图中位置;否则返回-1
  int i;
  for(i=0;i<G.vexnum;++i)
    if(____1____)
      return i;
  return -1;
}

Status CreateAG(MGraph &G)
{ // 采用数组(邻接矩阵)表示法,由文件构造没有相关信息的无向图G
  int i,j,k;
  VertexType va,vb;
  printf("请输入无向图G的顶点数,边数:");
  scanf("%d",____2____);
  scanf("%d",____3____);
  printf("\n请输入%d个顶点的值:\n",G.vexnum);
  for(i=0;i<G.vexnum;++i) // 构造顶点向量
    scanf(" %s", ____4____);
  for(i=0;i<G.vexnum;++i) // 初始化邻接矩阵
    for(j=0;j<G.vexnum;++j)
      G.arcs[i][j]=0;
  printf("请输入%d条边的顶点1 顶点2:\n",G.arcnum);
  for(k=0;k<G.arcnum;++k)
  {
    scanf(" %s%s",va,vb);
    i=____5____;
    j=____6____;
    G.arcs[i][j]=G.arcs[j][i]=1; // 无向图
  }
  G.kind=AG;
  return OK;
}

void DestroyGraph(MGraph &G)
 { // 初始条件: 图G存在。操作结果: 销毁无向图G
   G.vexnum=0;
   G.arcnum=0;
 }

Status PutVex(MGraph &G,VertexType v,VertexType value)
{ // 初始条件: 图G存在，v是G中某个顶点。操作结果: 对v赋新值value
  int k;
  k=____7____; // k为顶点v在图G中的序号
  if(k<0)
    return ERROR;
  ____8____;
  return OK;
}

int FirstAdjVex(MGraph G,VertexType v)
{ // 初始条件: 图G存在,v是G中某个顶点
  // 操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1
  int i,j=0,k;
  k=____9____; // k为顶点v在图G中的序号
  for(i=0;i<G.vexnum;i++)
    if(____10____)   //无向图
      return i;
  return -1;
}

int NextAdjVex(MGraph G,VertexType v,VertexType w)
{ // 初始条件: 图G存在,v是G中某个顶点,w是v的邻接顶点
  // 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号,
  //           若w是v的最后一个邻接顶点,则返回-1
  int i,j=0,k1,k2;
  k1=____11____; // k1为顶点v在图G中的序号
  k2=____12____; // k2为顶点w在图G中的序号
  for(i=____13____;i<G.vexnum;i++)
    if(____14____)
      return i;
  return -1;
}

void InsertVex(MGraph &G,VertexType v)
{ // 初始条件: 图G存在,v和图G中顶点有相同特征
  // 操作结果: 在图G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做)
  int i;
  strcpy(G.vexs[G.vexnum],v); // 构造新顶点向量
  for(i=0;i<=G.vexnum;i++)
  {
    ____15____=0; // 初始化该行邻接矩阵的值(无边或弧)
    ____16____=0; // 初始化该列邻接矩阵的值(无边或弧)
  }
____17____; // 图G的顶点数加1
}

Status DeleteVex(MGraph &G,VertexType v)
{ // 初始条件: 图G存在,v是G中某个顶点。操作结果: 删除G中顶点v及其相关的弧
  int i,j,k;
  k=LocateVex(G,v); // k为待删除顶点v的序号
  if(k<0) // v不是图G的顶点
    return ERROR;
  for(j=0;j<G.vexnum;j++)
    if(G.arcs[j][k]!=0) // 有边
      ____18____; // 修改边数
  for(j=k+1;j<G.vexnum;j++) // 序号k后面的顶点向量依次前移
    ____19____;
  for(i=0;i<G.vexnum;i++)
    for(____20____)
      G.arcs[i][j-1]=G.arcs[i][j]; // 移动待删除顶点之后的矩阵元素
  for(i=0;i<G.vexnum;i++)
    for(____21____)
      G.arcs[j-1][i]=G.arcs[j][i]; // 移动待删除顶点之下的矩阵元素
  ____22____; // 更新图的顶点数
  return OK;
}

Status InsertArc(MGraph &G,VertexType v,VertexType w)
{ // 初始条件: 图G存在,v和W是G中两个顶点
  // 操作结果: 在G中增添弧<v,w>,若G是无向的,则还增添对称弧<w,v>
  int i,l,v1,w1;
  v1=____23____; // 尾
  w1=____24____; // 头
  if(v1<0||w1<0)
    return ERROR;
  ____25____; // 弧或边数加1
  ____26____;
  return OK;
}

Status DeleteArc(MGraph &G,VertexType v,VertexType w)
{ // 初始条件: 图G存在,v和w是G中两个顶点
  // 操作结果: 在G中删除弧<v,w>,若G是无向的,则还删除对称弧<w,v>
  int v1,w1;
  v1=____27____; // 尾
  w1=____28____; // 头
  if(v1<0||w1<0) // v1、w1的值不合法
    return ERROR;
  ____29____=0;
  ____30____;    //修改边数
  return OK;
}
void Display(MGraph G)
{ // 输出无向图G
  int i,j;
  printf("%d个顶点%d条边的无向图\n",G.vexnum,G.arcnum);
  for(i=0;i<G.vexnum;++i) // 输出G.vexs
    printf("G.vexs[%d]=%s\n",i,G.vexs[i]);
  printf("G.arcs:\n"); // 输出G.arcs.adj
  for(i=0;i<G.vexnum;i++)
  {
    for(j=0;j<G.vexnum;j++)
      printf("%2d",G.arcs[i][j]);
    printf("\n");
  }
}

int main()
{
  int i,j,k,n;
  VertexType v1,v2;
  MGraph g;
  CreateAG(g);
  Display(g);
  printf("修改顶点的值，请输入原值 新值: \n");
  scanf("%s%s",v1,v2);
  PutVex(g,v1,v2);
  printf("删除一条边或弧，请输入待删除边或弧的弧尾 弧头：\n");
  scanf("%s%s",v1,v2);
  DeleteArc(g,v1,v2);
  Display(g);
  printf("插入新顶点，请输入顶点的值: ");
  scanf("%s",v1);
  InsertVex(g,v1);
  printf("\n插入与新顶点有关的边，请输入边数: ");
  scanf("%d",&n);
  for(k=0;k<n;k++)
    {
      printf("\n请输入另一顶点的值: ");
      scanf("%s",v2);
      InsertArc(g,v1,v2);
    }
  printf("\n");
  Display(g);
  printf("删除顶点及相关边，请输入顶点的值: ");
  scanf("%s",v1);
  printf("\n");
  DeleteVex(g,v1);
  Display(g);
  DestroyGraph(g);
  return 0;
}
```
输入示例:
```
8 9
v1
v2
v3
v4
v5
v6
v7
v8
v1 v2
v1 v3
v2 v4
v2 v5
v3 v6
v3 v7
v4 v8
v5 v8
v6 v7
v8 v9
v1 v3
v10
5
v1
v5
v7
v9
v2
v10
```
输出示例:
```
请输入无向图G的顶点数,边数:
请输入8个顶点的值:
请输入9条边的顶点1 顶点2:
8个顶点9条边的无向图
G.vexs[0]=v1
G.vexs[1]=v2
G.vexs[2]=v3
G.vexs[3]=v4
G.vexs[4]=v5
G.vexs[5]=v6
G.vexs[6]=v7
G.vexs[7]=v8
G.arcs:
 0 1 1 0 0 0 0 0
 1 0 0 1 1 0 0 0
 1 0 0 0 0 1 1 0
 0 1 0 0 0 0 0 1
 0 1 0 0 0 0 0 1
 0 0 1 0 0 0 1 0
 0 0 1 0 0 1 0 0
 0 0 0 1 1 0 0 0
修改顶点的值，请输入原值 新值: 
删除一条边或弧，请输入待删除边或弧的弧尾 弧头：
8个顶点8条边的无向图
G.vexs[0]=v1
G.vexs[1]=v2
G.vexs[2]=v3
G.vexs[3]=v4
G.vexs[4]=v5
G.vexs[5]=v6
G.vexs[6]=v7
G.vexs[7]=v9
G.arcs:
 0 1 0 0 0 0 0 0
 1 0 0 1 1 0 0 0
 0 0 0 0 0 1 1 0
 0 1 0 0 0 0 0 1
 0 1 0 0 0 0 0 1
 0 0 1 0 0 0 1 0
 0 0 1 0 0 1 0 0
 0 0 0 1 1 0 0 0
插入新顶点，请输入顶点的值: 
插入与新顶点有关的边，请输入边数: 
请输入另一顶点的值: 
请输入另一顶点的值: 
请输入另一顶点的值: 
请输入另一顶点的值: 
请输入另一顶点的值: 
9个顶点13条边的无向图
G.vexs[0]=v1
G.vexs[1]=v2
G.vexs[2]=v3
G.vexs[3]=v4
G.vexs[4]=v5
G.vexs[5]=v6
G.vexs[6]=v7
G.vexs[7]=v9
G.vexs[8]=v10
G.arcs:
 0 1 0 0 0 0 0 0 1
 1 0 0 1 1 0 0 0 1
 0 0 0 0 0 1 1 0 0
 0 1 0 0 0 0 0 1 0
 0 1 0 0 0 0 0 1 1
 0 0 1 0 0 0 1 0 0
 0 0 1 0 0 1 0 0 1
 0 0 0 1 1 0 0 0 1
 1 1 0 0 1 0 1 1 0
删除顶点及相关边，请输入顶点的值: 
8个顶点8条边的无向图
G.vexs[0]=v1
G.vexs[1]=v2
G.vexs[2]=v3
G.vexs[3]=v4
G.vexs[4]=v5
G.vexs[5]=v6
G.vexs[6]=v7
G.vexs[7]=v9
G.arcs:
 0 1 0 0 0 0 0 0
 1 0 0 1 1 0 0 0
 0 0 0 0 0 1 1 0
 0 1 0 0 0 0 0 1
 0 1 0 0 0 0 0 1
 0 0 1 0 0 0 1 0
 0 0 1 0 0 1 0 0
 0 0 0 1 1 0 0 0
```
注意: 输入输出是交替进行的，需要配合着看，以下是一次执行过程:
```
请输入无向图G的顶点数,边数:8 9

请输入8个顶点的值:
v1
v2
v3
v4
v5
v6
v7
v8
请输入9条边的顶点1 顶点2:
v1 v2
v1 v3
v2 v4
v2 v5
v3 v6
v3 v7
v4 v8
v5 v8
v6 v7
8个顶点9条边的无向图
G.vexs[0]=v1
G.vexs[1]=v2
G.vexs[2]=v3
G.vexs[3]=v4
G.vexs[4]=v5
G.vexs[5]=v6
G.vexs[6]=v7
G.vexs[7]=v8
G.arcs:
 0 1 1 0 0 0 0 0
 1 0 0 1 1 0 0 0
 1 0 0 0 0 1 1 0
 0 1 0 0 0 0 0 1
 0 1 0 0 0 0 0 1
 0 0 1 0 0 0 1 0
 0 0 1 0 0 1 0 0
 0 0 0 1 1 0 0 0
修改顶点的值，请输入原值 新值:
v8 v9
删除一条边或弧，请输入待删除边或弧的弧尾 弧头：
v1 v3
8个顶点8条边的无向图
G.vexs[0]=v1
G.vexs[1]=v2
G.vexs[2]=v3
G.vexs[3]=v4
G.vexs[4]=v5
G.vexs[5]=v6
G.vexs[6]=v7
G.vexs[7]=v9
G.arcs:
 0 1 0 0 0 0 0 0
 1 0 0 1 1 0 0 0
 0 0 0 0 0 1 1 0
 0 1 0 0 0 0 0 1
 0 1 0 0 0 0 0 1
 0 0 1 0 0 0 1 0
 0 0 1 0 0 1 0 0
 0 0 0 1 1 0 0 0
插入新顶点，请输入顶点的值: v10

插入与新顶点有关的边，请输入边数: 5

请输入另一顶点的值: v1

请输入另一顶点的值: v5

请输入另一顶点的值: v7

请输入另一顶点的值: v9

请输入另一顶点的值: v2

9个顶点13条边的无向图
G.vexs[0]=v1
G.vexs[1]=v2
G.vexs[2]=v3
G.vexs[3]=v4
G.vexs[4]=v5
G.vexs[5]=v6
G.vexs[6]=v7
G.vexs[7]=v9
G.vexs[8]=v10
G.arcs:
 0 1 0 0 0 0 0 0 1
 1 0 0 1 1 0 0 0 1
 0 0 0 0 0 1 1 0 0
 0 1 0 0 0 0 0 1 0
 0 1 0 0 0 0 0 1 1
 0 0 1 0 0 0 1 0 0
 0 0 1 0 0 1 0 0 1
 0 0 0 1 1 0 0 0 1
 1 1 0 0 1 0 1 1 0
删除顶点及相关边，请输入顶点的值: v10

8个顶点8条边的无向图
G.vexs[0]=v1
G.vexs[1]=v2
G.vexs[2]=v3
G.vexs[3]=v4
G.vexs[4]=v5
G.vexs[5]=v6
G.vexs[6]=v7
G.vexs[7]=v9
G.arcs:
 0 1 0 0 0 0 0 0
 1 0 0 1 1 0 0 0
 0 0 0 0 0 1 1 0
 0 1 0 0 0 0 0 1
 0 1 0 0 0 0 0 1
 0 0 1 0 0 0 1 0
 0 0 1 0 0 1 0 0
 0 0 0 1 1 0 0 0
```

## 程序填空题
1. 1. `strcmp(G.vexs[i], u) == 0`
   2. `&G.vexnum`
   3. `&G.arcnum`
   4. `G.vexs[i]`
   5. `LocateVex(G, va)`
   6. `LocateVex(G, vb)`
   7. `LocateVex(G, v)`
   8. `strcpy(G.vexs[k], value)`
   9. `LocateVex(G, v)`
   10. `G.arcs[i][k] == 1`
   11. `LocateVex(G, v)`
   12. `LocateVex(G, w)`
   13. `k2+1`
   14. `G.arcs[i][k1] == 1`
   15. `G.arcs[G.vexnum][i]`
   16. `G.arcs[i][G.vexnum]`
   17. `G.vexnum++`
   18. `G.arcnum--`
   19. `strcpy(G.vexs[j-1], G.vexs[j])`
   20. `j=k+1;j<G.vexnum;j++`
   21. `j=k+1;j<G.vexnum;j++`
   22. `G.vexnum--`
   23. `LocateVex(G, v)`
   24. `LocateVex(G, w)`
   25. `G.arcnum++`
   26. `G.arcs[v1][w1] = G.arcs[w1][v1] = 1`
   27. `LocateVex(G, v)`
   28. `LocateVex(G, w)`
   29. `G.arcs[v1][w1] = G.arcs[w1][v1]`
   30. `G.arcnum--`
