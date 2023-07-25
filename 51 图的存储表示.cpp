// 1.�ڽӾ����ʾ��
// A_ij = 0, (i,j) ������ VR
    //  = 1, (i,j) ���� VR

// ���������ʾ�����ϴ�Ȩֵ

// ����v�ĳ��ȣ�  ��ά�����Ӧ����ֵΪ1��Ԫ�ظ���    ��ȣ���

#define INFINITY -1             //���ֵ
#define MAX_VERTEX_NUM 20       //��󶥵���

typedef enum{DG,DN,UDG,UDN} GraphKind;  //����ͼ��������������ͼ��������   graph & net

typedef struct ArcCell{     //������Ϣ
    int adj;                //�����ϵ����  ��Ȩͼ��0/1  ����Ȩֵ
    int *info;              //�������Ϣ��ָ��
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct{
    int vexs[MAX_VERTEX_NUM];       //������Ϣ
    AdjMatrix arcs;                 //�ڽӾ���(������Ϣ)
    int vexnum, arcnum;             //ͼ��ǰ�������ͻ���
    GraphKind kind;                 //ͼ�������־
} MGraph;


typedef struct {
    int vexs_1[MAX_VERTEX_NUM];
    int arcs_1[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
} AMGraph;


// 2.�ڽӱ��ʾ��

#define MVNum 100

typedef struct {
    int data;
    ArcNode *firstarc;
} VNode, AdjList[MVNum];  //�ڽӱ����ͣ���������ķ�����

// AdjList v-- -- --VNode v[MAX_VERTEX_NUM];

typedef struct ArcNode{
    int adjvex;     // �ñߵĶ���λ��(β������)
    struct ArcNode *nextarc;
    int info;
} ArcNode;

typedef struct {
    AdjList vertices;   //�ڽӱ�
    int vexnum, arcnum;
} ALGraph;

