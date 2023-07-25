#include<iostream>
using namespace std;
// 遍历：从某一顶点出发，沿一些边访问图中所有顶点，且每个顶点只访问一次
// 实质：找每个顶点的邻接点

// 1.深度优先DFS
// 邻接矩阵表示的无向图
int visited[10] = {0};

typedef struct {
    int vexs[20];
    int arcs[20][20];
    int vexnum, arcnum;
} MGraph;

void DFS(MGraph G, int v){  // v为起始节点
    cout << v;              // 访问v结点
    visited[v] = 1;
    for (int w = 0; w < G.vexnum; w++)  // 依次检查邻接矩阵中v所在的行
        if(G.arcs[v][w]!=0 && (!visited[w]))
            DFS(G, w);
}  


// 2.广度优先BFS
// 邻接表表示的无向图   用队列实现
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
    cout << v;              // 访问v结点
    visited[v] = 1;
    queue<int> Q;
    Q.push(v);
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();                  //队头元素出队并置为u
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

