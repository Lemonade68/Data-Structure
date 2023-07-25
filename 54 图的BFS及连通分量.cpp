#include<iostream>
using namespace std;

int n, g[101][101], cnt, visited[101];

void dfs(int node){
    cout << node << " ";
    visited[node] = 1;
    for (int i = 1; i <= n; ++i){
        if(!visited[i] && g[node][i])
            dfs(i);
    }
}

int dfstraverse(){
    for (int i = 1; i <= n; ++i){
        if(!visited[i]){
            dfs(i);
            cnt++;
        }
    }
    return cnt;
}

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> g[i][j];
    int cnt = dfstraverse();
    cout << endl;
    cout << cnt << endl;
    return 0;
}


// #include <iostream>
// using namespace std;

// int a[101][101],vis[101]={0};//a是邻接矩阵数组，vis是标记结点是否访问过
// int n,cnt=0;                 //cnt记录联通向量个数              

// void dfs(int node){         
//     cout << node << " ";
//     vis[node]=1;             //标记已访问过
//     for(int i=1;i<=n;i++){
//         if(a[node][i] && !vis[i])   //如果两节点有边而且未访问过
//             dfs(i);                 //继续往下搜
//     }
// }

// int dfstraverse(int node){
//     for(int i=1;i<=n;i++){          //确保每个结点都能访问到
//         if(!vis[i]){
//             dfs(i);                  
//             cnt++; //每一次dfs对应一个联通向量,这里其实还挺好理解的
//         }          //你想如果一个结点可以一直深搜下去，那它肯定只有一个
//     }              //联通分量。但是如果断了，回溯了，
//     return cnt;    //比如此题中的1256之后的3，就是一个新的分支
// }                  //从它深搜下去，就是一个新的联通向量

// int main(){
//     cin >> n;
//     for(int i=1;i<=n;i++){        //因为它从结点1开始所以从下标1开始存
//         for(int j=1;j<=n;j++){
//             cin >> a[i][j];
//         }
//     }
//     dfstraverse(1);
//     cout << endl << dfstraverse(1);
//     return 0;
// }
