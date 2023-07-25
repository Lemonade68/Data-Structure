// 1.邻接矩阵表示：
// A_ij = 0, (i,j) 不属于 VR
    //  = 1, (i,j) 属于 VR

// 网的数组表示：边上带权值

// 顶点v的出度：  二维数组对应行中值为1的元素个数    入度：列

#define INFINITY -1             //最大值
#define MAX_VERTEX_NUM 20       //最大顶点数

typedef enum{DG,DN,UDG,UDN} GraphKind;  //有向图，有向网，无向图，无向网   graph & net

typedef struct ArcCell{     //弧的信息
    int adj;                //顶点关系类型  无权图：0/1  网：权值
    int *info;              //弧相关信息的指针
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct{
    int vexs[MAX_VERTEX_NUM];       //顶点信息
    AdjMatrix arcs;                 //邻接矩阵(弧的信息)
    int vexnum, arcnum;             //图当前顶点数和弧数
    GraphKind kind;                 //图的种类标志
} MGraph;


typedef struct {
    int vexs_1[MAX_VERTEX_NUM];
    int arcs_1[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
} AMGraph;


// 2.邻接表表示：

#define MVNum 100

typedef struct {
    int data;
    ArcNode *firstarc;
} VNode, AdjList[MVNum];  //邻接表类型（定义数组的方法）

// AdjList v-- -- --VNode v[MAX_VERTEX_NUM];

typedef struct ArcNode{
    int adjvex;     // 该边的顶点位置(尾部顶点)
    struct ArcNode *nextarc;
    int info;
} ArcNode;

typedef struct {
    AdjList vertices;   //邻接表
    int vexnum, arcnum;
} ALGraph;

