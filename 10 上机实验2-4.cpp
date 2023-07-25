// 迷宫问题
// 以一个m*n的长方阵表示迷宫，0和1分别表示迷宫中的通路和障碍。
// 设计一个程序，对任意设定的迷宫，求出一条从入口到出口的通路，
// 或得出没有通路的结论。


//没有通路部分暂时存在问题

// -------------------------------去学习dfs算法实现------------------------

#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -2
int m, n;   //m为迷宫行数，n为迷宫列数

//坐标
typedef struct col{
    int x;
    int y;
} Col;

//链式栈结构(实际就是链表)
typedef struct stacknode{
    Col location;
    int dir = 1;
    int number = 0;
    struct stacknode *next;
} PathStack, *PathNode;

int** CreateMaze();                                         //初始化迷宫
void push(PathNode &routehead, Col Position, int dir);      //路线结点入栈
int pop(PathNode &routehead);                               //路线结点出栈
void PrintRoute(PathNode &routehead);                       //打印路线
void MazePath(int** maze, Col entrance, Col exit, PathNode &routehead);          //路线寻找函数

int main()
{
    //生成迷宫
    int **maze = CreateMaze();

    //输入入口与出口坐标
    printf("请输入入口坐标与出口坐标,用空格分隔  例如:左上角为1 1:\n");
    Col Entrance, Exit;
    scanf("%d %d %d %d", &Entrance.x, &Entrance.y, &Exit.x, &Exit.y);

    //路线头结点生成
    PathNode routehead = (PathNode)malloc(sizeof(PathStack));
    if(!routehead)
        exit(OVERFLOW);
    routehead->next = NULL;

    MazePath(maze, Entrance, Exit, routehead);

    for (int i = 0; i < m + 2;i++){
        free(maze[i]);
    }
    return 0;
}


int** CreateMaze(){
    printf("请输入迷宫的行数与列数,以空格分隔：\n");
    scanf("%d %d", &m, &n);
    //学习二维动态数组的生成方法
    int **maze = (int **)malloc(sizeof(int *) * (m + 2));       //注意+2
    for (int i = 0; i < m + 2; i++)
        maze[i] = (int *)malloc(sizeof(int) * (n + 2));
    printf("请输入迷宫的01矩阵,0为通路,1为墙壁:\n");
    for (int i = 0; i <= m + 1; i++){
        for (int j = 0; j <= n + 1; j++){
            if (i == 0 || i == m + 1 || j == 0 || j == n + 1)   //生成墙壁
                maze[i][j] = 1;
            else
                scanf("%d", &maze[i][j]);
        }
    }
    return maze;
}

void push(PathNode &routehead, Col Position, int dir){          //头插法
    PathNode p = (PathNode)malloc(sizeof(PathStack));
    p->location.x = Position.x;
    p->location.y = Position.y;
    p->dir = dir;
    p->next = routehead->next;
    routehead->next = p;
    routehead->number++;
}

int pop(PathNode &routehead){           //返回dir
    PathNode p = routehead->next;
    PathNode q = p->next;
    routehead->next = q;
    int dir = p->dir;
    free(p);
    routehead->number--;
    return dir;
}

void PrintRoute(PathNode &routehead){
    PathNode p = routehead->next;

    //先实现链表逆转，后打印输出
    PathNode q = p->next;
    p->next = NULL;
    while(q){
        PathNode m = q->next;
        q->next = routehead->next;
        routehead->next = q;
        q = m;
    }

    p = routehead->next;
    while(p){
        printf("(%d,%d,%d)\n", p->location.x, p->location.y, p->dir);
        p = p->next;
    }
}


// maze状态：0：未走；1：墙；2：在当前路径；3：已走过（死路）
// 注意：某方向可通仅指该方向下一格maze状态为0
// 入栈思路：先把上一个位置入栈，然后看下一个位置是否可通。 可通：重复；不可通：出栈换方向   重要！！！
void MazePath(int** maze, Col entrance, Col exit, PathNode &routehead){
    //设置移动数组
    int movex[4] = {1, 0, -1, 0};   //对应下右上左-----x对应行，y对应列 别搞混！！！
    int movey[4] = {0, 1, 0, -1};

    Col Position = entrance;        //当前位置
    int dir = 1;                    //当前方向  1 2 3 4
    do{
        //每次回到这里时应该是当前栈顶所指的下一个位置
        if (maze[Position.x][Position.y] == 0){         //如果可通
            maze[Position.x][Position.y] = 2;           //标记
            dir = 1;                                    //重置方向为默认值1   ****这一步一定要放在push前，不然这边push的方向会是上一个结点的方向从而产生错误！！！！
            push(routehead, Position, dir);             //入栈
            if (Position.x == exit.x && Position.y == exit.y){  //到达终点
                PrintRoute(routehead);
                return;
            }
            //若未到达终点，则继续标记下一个
            Position.x += movex[dir-1];                     //注意move数组里是从0开始，dir是从1开始！！！
            Position.y += movey[dir-1];
        }
        else{                                               //如果不可通
            if (routehead->number != 0){                    //pop前一定要判断栈是否为空
            dir = pop(routehead);                           //要先pop  因为记录的方向要变
                if (dir == 4 && routehead->number != 0){    //dir为4的情况
                    //返回上一个位置
                    Position.x -= movex[dir-1];
                    Position.y -= movey[dir-1];
                }
                else if(dir<4){
                    //先返回栈顶位置
                    Position.x -= movex[dir-1];
                    Position.y -= movey[dir-1];
                    //再换方向操作
                    dir++;
                    //记录结点
                    push(routehead, Position, dir);
                    //移动到下一个位置
                    Position.x += movex[dir-1];
                    Position.y += movey[dir-1];
                }
            }                
            
        }
    } while (routehead->number != 0);
    printf("没有通路!\n");
    return;
}



//没有通路好像有点问题？