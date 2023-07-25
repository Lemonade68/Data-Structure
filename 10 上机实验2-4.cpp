// �Թ�����
// ��һ��m*n�ĳ������ʾ�Թ���0��1�ֱ��ʾ�Թ��е�ͨ·���ϰ���
// ���һ�����򣬶������趨���Թ������һ������ڵ����ڵ�ͨ·��
// ��ó�û��ͨ·�Ľ��ۡ�


//û��ͨ·������ʱ��������

// -------------------------------ȥѧϰdfs�㷨ʵ��------------------------

#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -2
int m, n;   //mΪ�Թ�������nΪ�Թ�����

//����
typedef struct col{
    int x;
    int y;
} Col;

//��ʽջ�ṹ(ʵ�ʾ�������)
typedef struct stacknode{
    Col location;
    int dir = 1;
    int number = 0;
    struct stacknode *next;
} PathStack, *PathNode;

int** CreateMaze();                                         //��ʼ���Թ�
void push(PathNode &routehead, Col Position, int dir);      //·�߽����ջ
int pop(PathNode &routehead);                               //·�߽���ջ
void PrintRoute(PathNode &routehead);                       //��ӡ·��
void MazePath(int** maze, Col entrance, Col exit, PathNode &routehead);          //·��Ѱ�Һ���

int main()
{
    //�����Թ�
    int **maze = CreateMaze();

    //����������������
    printf("����������������������,�ÿո�ָ�  ����:���Ͻ�Ϊ1 1:\n");
    Col Entrance, Exit;
    scanf("%d %d %d %d", &Entrance.x, &Entrance.y, &Exit.x, &Exit.y);

    //·��ͷ�������
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
    printf("�������Թ�������������,�Կո�ָ���\n");
    scanf("%d %d", &m, &n);
    //ѧϰ��ά��̬��������ɷ���
    int **maze = (int **)malloc(sizeof(int *) * (m + 2));       //ע��+2
    for (int i = 0; i < m + 2; i++)
        maze[i] = (int *)malloc(sizeof(int) * (n + 2));
    printf("�������Թ���01����,0Ϊͨ·,1Ϊǽ��:\n");
    for (int i = 0; i <= m + 1; i++){
        for (int j = 0; j <= n + 1; j++){
            if (i == 0 || i == m + 1 || j == 0 || j == n + 1)   //����ǽ��
                maze[i][j] = 1;
            else
                scanf("%d", &maze[i][j]);
        }
    }
    return maze;
}

void push(PathNode &routehead, Col Position, int dir){          //ͷ�巨
    PathNode p = (PathNode)malloc(sizeof(PathStack));
    p->location.x = Position.x;
    p->location.y = Position.y;
    p->dir = dir;
    p->next = routehead->next;
    routehead->next = p;
    routehead->number++;
}

int pop(PathNode &routehead){           //����dir
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

    //��ʵ��������ת�����ӡ���
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


// maze״̬��0��δ�ߣ�1��ǽ��2���ڵ�ǰ·����3�����߹�����·��
// ע�⣺ĳ�����ͨ��ָ�÷�����һ��maze״̬Ϊ0
// ��ջ˼·���Ȱ���һ��λ����ջ��Ȼ����һ��λ���Ƿ��ͨ�� ��ͨ���ظ�������ͨ����ջ������   ��Ҫ������
void MazePath(int** maze, Col entrance, Col exit, PathNode &routehead){
    //�����ƶ�����
    int movex[4] = {1, 0, -1, 0};   //��Ӧ��������-----x��Ӧ�У�y��Ӧ�� ���죡����
    int movey[4] = {0, 1, 0, -1};

    Col Position = entrance;        //��ǰλ��
    int dir = 1;                    //��ǰ����  1 2 3 4
    do{
        //ÿ�λص�����ʱӦ���ǵ�ǰջ����ָ����һ��λ��
        if (maze[Position.x][Position.y] == 0){         //�����ͨ
            maze[Position.x][Position.y] = 2;           //���
            dir = 1;                                    //���÷���ΪĬ��ֵ1   ****��һ��һ��Ҫ����pushǰ����Ȼ���push�ķ��������һ�����ķ���Ӷ��������󣡣�����
            push(routehead, Position, dir);             //��ջ
            if (Position.x == exit.x && Position.y == exit.y){  //�����յ�
                PrintRoute(routehead);
                return;
            }
            //��δ�����յ㣬����������һ��
            Position.x += movex[dir-1];                     //ע��move�������Ǵ�0��ʼ��dir�Ǵ�1��ʼ������
            Position.y += movey[dir-1];
        }
        else{                                               //�������ͨ
            if (routehead->number != 0){                    //popǰһ��Ҫ�ж�ջ�Ƿ�Ϊ��
            dir = pop(routehead);                           //Ҫ��pop  ��Ϊ��¼�ķ���Ҫ��
                if (dir == 4 && routehead->number != 0){    //dirΪ4�����
                    //������һ��λ��
                    Position.x -= movex[dir-1];
                    Position.y -= movey[dir-1];
                }
                else if(dir<4){
                    //�ȷ���ջ��λ��
                    Position.x -= movex[dir-1];
                    Position.y -= movey[dir-1];
                    //�ٻ��������
                    dir++;
                    //��¼���
                    push(routehead, Position, dir);
                    //�ƶ�����һ��λ��
                    Position.x += movex[dir-1];
                    Position.y += movey[dir-1];
                }
            }                
            
        }
    } while (routehead->number != 0);
    printf("û��ͨ·!\n");
    return;
}



//û��ͨ·�����е����⣿