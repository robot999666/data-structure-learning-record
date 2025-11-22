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

typedef int MazeType[30][30];

typedef struct
{
    int row;
    int col;
} PosType;

Status equ_seat(PosType a, PosType b)
{
    if (a.row == b.row && a.col == b.col)
        return TRUE;
    else
        return FALSE;
}

PosType NextPos(PosType curpos, int di)
{
    if (di == 1)
        curpos.col++;
    if (di == 2)
        curpos.row++;
    if (di == 3)
        curpos.col--;
    if (di == 4)
        curpos.row--;
    return curpos;
}

typedef struct
{
    int ord;
    PosType seat;
    int di;
} SElemType;

typedef struct
{
    SElemType *base;
    SElemType *top;
    int stacksize;
} SqStack;

Status InitStack(SqStack &s)
{
    s.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!s.base)
        exit(OVERFLOW); // 存储分配失败
    s.top = s.base;
    s.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status GetTop(SqStack s, SElemType &e)
{
    if (s.base == s.top)
        return ERROR;
    e = *(s.top - 1);
    return OK;
}

Status Push(SqStack &s, SElemType e)
{ // 插入元素e为新的栈顶元素
    if (s.top - s.base >= s.stacksize)
    { // 栈满,追加存储空间
        s.base = (SElemType *)realloc(s.base, (s.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!s.base)
            exit(OVERFLOW); // 存储分配失败
        s.top = s.base + s.stacksize;
        s.stacksize += STACKINCREMENT;
    }
    *s.top++ = e;
    return OK;
}

Status Pop(SqStack &s, SElemType &e)
{
    if (s.top == s.base)
        return ERROR;
    e = *(--s.top);
    return OK;
}

Status StackEmpty(SqStack s)
{
    if (s.top == s.base)
        return OK;
    else
        return ERROR;
}

Status Pass(MazeType maze, PosType curpos)
{
    if (maze[curpos.row][curpos.col] == 0)
        return TRUE;
    else
        return FALSE;
}

void FootPrint(MazeType Maze, PosType curpos, int curstep)
{
    Maze[curpos.row][curpos.col] = curstep;
}

void MarkPrint(MazeType Maze, PosType CurPos)
{
    Maze[CurPos.row][CurPos.col] = 0;
}

Status MazePath(MazeType maze, PosType start, PosType end)
{
    SqStack S;
    InitStack(S);
    PosType curpos = start;
    int curstep = 1;
    SElemType e;
    do
    {
        if (Pass(maze, curpos))
        {
            FootPrint(maze, curpos, curstep);
            e = {curstep, curpos, 1};
            Push(S, e);
            if (equ_seat(curpos, end))
                return TRUE;
            curpos = NextPos(curpos, 1);
            curstep++;
        }
        else
        {
            if (!StackEmpty(S))
            {
                Pop(S, e);
                while (e.di == 4 && !StackEmpty(S))
                {
                    MarkPrint(maze, e.seat);
                    Pop(S, e);
                }
                if (e.di < 4)
                {
                    e.di++;
                    Push(S, e);
                    curpos = NextPos(e.seat, e.di);
                    curstep = e.ord + 1;
                }
            }
        }
    } while (!StackEmpty(S));
    return (FALSE);
}

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    MazeType maze;
    PosType start, end;
    scanf("%d %d", &start.row, &start.col);
    scanf("%d %d", &end.row, &end.col);
    for (int i = 0; i <= m + 1; i++)
    {
        for (int j = 0; j <= n + 1; j++)
        {
            if (i == 0 || j == 0 || i == m + 1 || j == n + 1)
                maze[i][j] = 1;
            else
                scanf("%d", &maze[i][j]);
        }
    }
    if (!MazePath(maze, start, end))
        printf("NO");
    else
    {
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (maze[i][j] <= 1 && !(i == start.row && j == start.col))
                    maze[i][j] = 0;
                printf("%3d", maze[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}