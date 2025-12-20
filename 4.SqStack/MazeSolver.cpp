// 用一个m×n的二维数组表示迷宫，0和1分别表示迷宫中的通路和障碍。设计一个程序，对任意设定的迷宫，按顺时针方向求出一条从人口到出口的通路，或得出没有通路的结论。

// 输入格式:
// 输入的第一行中给出m和n的整数值 ，分别代表迷宫的行数和列数。m和n的值，均小于20。
// 接着是两行分别是迷宫的入口和出口位置
// 然后是m×n的二维数组表示迷宫

// 输出格式:
// 输出是m×n的二维数组，表示迷宫每一步走的位置，使用%3d格式。

// 输入样例1:
// 9 8
// 1 1
// 9 8
// 0 0 1 0 0 0 1 0
// 0 0 1 0 0 0 1 0
// 0 0 0 0 1 1 0 1
// 0 1 1 1 0 0 1 0
// 0 0 0 1 0 0 0 0
// 0 1 0 0 0 1 0 1
// 0 1 1 1 1 0 0 1
// 1 1 0 0 0 1 0 1
// 1 1 0 0 0 0 0 0
// 输出样例1:
//   1  2  0  0  0  0  0  0
//   0  3  0  0  0  0  0  0
//   5  4  0  0  0  0  0  0
//   6  0  0  0  0  0  0  0
//   7  8  9  0 13 14 15  0
//   0  0 10 11 12  0 16  0
//   0  0  0  0  0  0 17  0
//   0  0  0  0  0  0 18  0
//   0  0  0  0  0  0 19 20
// 输入样例2:
// 6 5
// 1 1
// 6 5
// 0 0 0 0 0
// 0 0 1 0 0
// 1 1 1 1 1
// 0 0 1 0 0
// 0 0 1 0 0
// 0 0 1 0 0
// 输出样例2:
// NO

#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100 // 存储空间初始分配
#define STACKINCREMENT 10   // 存储空间分配增量

typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int MazeType[30][30];  // 迷宫类型定义，30x30的二维数组

typedef struct
{
    int row;  // 行坐标
    int col;  // 列坐标
} PosType;    // 位置类型，表示迷宫中的坐标

// 判断两个位置是否相等
Status equ_seat(PosType a, PosType b)
{
    if (a.row == b.row && a.col == b.col)
        return TRUE;   // 位置相同
    else
        return FALSE;  // 位置不同
}

// 根据方向di获取当前位置的下一个位置
// di=1:右, di=2:下, di=3:左, di=4:上
PosType NextPos(PosType curpos, int di)
{
    if (di == 1)
        curpos.col++;  // 向右移动
    if (di == 2)
        curpos.row++;  // 向下移动
    if (di == 3)
        curpos.col--;  // 向左移动
    if (di == 4)
        curpos.row--;  // 向上移动
    return curpos;
}

typedef struct
{
    int ord;      // 路径中的序号，表示第几步
    PosType seat; // 当前位置
    int di;       // 进入该位置时的方向
} SElemType;      // 栈元素类型，记录路径信息

typedef struct
{
    SElemType *base;    // 栈底指针
    SElemType *top;     // 栈顶指针
    int stacksize;      // 栈的最大容量
} Stack;              // 顺序栈，用于存储路径

// 初始化顺序栈
Status InitStack(Stack &s)
{
    s.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!s.base)
        exit(OVERFLOW); // 存储分配失败
    s.top = s.base;    // 栈顶指针初始指向栈底，表示空栈
    s.stacksize = STACK_INIT_SIZE;  // 设置初始栈容量
    return OK;
}

// 获取栈顶元素，但不弹出
Status GetTop(Stack s, SElemType &e)
{
    if (s.base == s.top)  // 栈空判断
        return ERROR;
    e = *(s.top - 1);     // 获取栈顶元素
    return OK;
}

// 入栈操作：将元素e压入栈顶
Status Push(Stack &s, SElemType e)
{
    if (s.top - s.base >= s.stacksize)  // 检查栈是否已满
    {
        // 栈满时动态扩容
        s.base = (SElemType *)realloc(s.base, (s.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!s.base)
            exit(OVERFLOW); // 存储分配失败
        s.top = s.base + s.stacksize;  // 重新定位栈顶指针
        s.stacksize += STACKINCREMENT; // 更新栈容量
    }
    *s.top++ = e;  // 将元素放入栈顶并移动栈顶指针
    return OK;
}

// 出栈操作：弹出栈顶元素并返回其值
Status Pop(Stack &s, SElemType &e)
{
    if (s.top == s.base)  // 栈空判断
        return ERROR;
    e = *(--s.top);       // 先移动栈顶指针，再获取元素值
    return OK;
}

// 判断栈是否为空
Status StackEmpty(Stack s)
{
    if (s.top == s.base)
        return OK;   // 栈空
    else
        return ERROR; // 栈非空
}

// 判断当前位置是否可通过（是否为通路）
Status Pass(MazeType maze, PosType curpos)
{
    if (maze[curpos.row][curpos.col] == 0)
        return TRUE;  // 0表示通路，可以通过
    else
        return FALSE; // 1表示障碍，不可通过
}

// 在迷宫中留下足迹，标记当前位置为第curstep步
void FootPrint(MazeType Maze, PosType curpos, int curstep)
{
    Maze[curpos.row][curpos.col] = curstep;
}

// 清除迷宫中的标记，将当前位置重新设为通路
void MarkPrint(MazeType Maze, PosType CurPos)
{
    Maze[CurPos.row][CurPos.col] = 0;
}

// 迷宫路径寻找函数，使用栈实现深度优先搜索
// 从start位置开始，寻找一条通往end位置的路径
Status MazePath(MazeType maze, PosType start, PosType end)
{
    Stack S;           // 路径栈，用于存储探索的路径
    InitStack(S);
    PosType curpos = start;  // 当前位置
    int curstep = 1;         // 当前步数
    SElemType e;             // 栈元素

    do
    {
        // 如果当前位置可通过
        if (Pass(maze, curpos))
        {
            FootPrint(maze, curpos, curstep);  // 在迷宫中标记当前位置
            e = {curstep, curpos, 1};          // 创建栈元素（步数、位置、方向）
            Push(S, e);                        // 将当前位置压入栈

            if (equ_seat(curpos, end))         // 如果到达终点
                return TRUE;                   // 找到路径

            curpos = NextPos(curpos, 1);       // 向右探索下一个位置
            curstep++;                         // 步数加1
        }
        else
        {
            // 当前位置不可通过，需要回溯
            if (!StackEmpty(S))
            {
                Pop(S, e);  // 弹出栈顶元素

                // 如果该位置的4个方向都已探索完毕，继续回溯
                while (e.di == 4 && !StackEmpty(S))
                {
                    MarkPrint(maze, e.seat);  // 清除该位置的标记
                    Pop(S, e);                // 继续弹出
                }

                // 如果还有未探索的方向
                if (e.di < 4)
                {
                    e.di++;                   // 尝试下一个方向
                    Push(S, e);               // 重新压入栈
                    curpos = NextPos(e.seat, e.di);  // 移动到下一个方向的位置
                    curstep = e.ord + 1;      // 更新步数
                }
            }
        }
    } while (!StackEmpty(S));  // 继续直到栈空（所有路径都探索完毕）

    return FALSE;  // 未找到路径
}

int main()
{
    int m, n;           // m:迷宫行数, n:迷宫列数
    scanf("%d %d", &m, &n);

    MazeType maze;      // 迷宫数组
    PosType start, end; // 起点和终点位置

    // 读取起点和终点坐标
    scanf("%d %d", &start.row, &start.col);
    scanf("%d %d", &end.row, &end.col);

    // 初始化迷宫，边界设为障碍(1)，内部读取数据
    for (int i = 0; i <= m + 1; i++)
    {
        for (int j = 0; j <= n + 1; j++)
        {
            if (i == 0 || j == 0 || i == m + 1 || j == n + 1)
                maze[i][j] = 1;  // 边界设为障碍
            else
                scanf("%d", &maze[i][j]);  // 读取迷宫内部数据
        }
    }

    // 调用迷宫路径寻找函数
    if (!MazePath(maze, start, end))
        printf("NO");   // 未找到路径
    else
    {
        // 找到路径，输出迷宫（显示路径）
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                // 清除非路径上的标记，但保留起点
                if (maze[i][j] <= 1 && !(i == start.row && j == start.col))
                    maze[i][j] = 0;
                printf("%3d", maze[i][j]);  // 格式化输出
            }
            printf("\n");
        }
    }
    return 0;
}