#include<iostream>
using namespace std;
// ��������ĳһ�����������һЩ�߷���ͼ�����ж��㣬��ÿ������ֻ����һ��
// ʵ�ʣ���ÿ��������ڽӵ�

// 1.�������DFS
// �ڽӾ����ʾ������ͼ
int visited[10] = {0};

typedef struct {
    int vexs[20];
    int arcs[20][20];
    int vexnum, arcnum;
} MGraph;

void DFS(MGraph G, int v){  // vΪ��ʼ�ڵ�
    cout << v;              // ����v���
    visited[v] = 1;
    for (int w = 0; w < G.vexnum; w++)  // ���μ���ڽӾ�����v���ڵ���
        if(G.arcs[v][w]!=0 && (!visited[w]))
            DFS(G, w);
}  


// 2.�������BFS
// �ڽӱ��ʾ������ͼ   �ö���ʵ��
#include<queue>

typedef struct VNode{
    int data;
    ArcNode *firstarc;
} VNode, AdjList[20];

typedef struct ArcNode{
    int info;
    int adjvex;
    struct ArcNode *nextarc;
} ArcNode;

typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph;

void BFS(ALGraph G, int v){
    cout << v;              // ����v���
    visited[v] = 1;
    queue<int> Q;
    Q.push(v);
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();                  //��ͷԪ�س��Ӳ���Ϊu
        ArcNode *p = G.vertices[u].firstarc;
        while(!p){
            if(!visited[p->adjvex]){
                Q.push(p->adjvex);
                cout << p->adjvex;
                visited[p->adjvex] = 1;
                p = p->nextarc;
            }
        }
    }
}

