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

// int a[101][101],vis[101]={0};//a���ڽӾ������飬vis�Ǳ�ǽ���Ƿ���ʹ�
// int n,cnt=0;                 //cnt��¼��ͨ��������              

// void dfs(int node){         
//     cout << node << " ";
//     vis[node]=1;             //����ѷ��ʹ�
//     for(int i=1;i<=n;i++){
//         if(a[node][i] && !vis[i])   //������ڵ��б߶���δ���ʹ�
//             dfs(i);                 //����������
//     }
// }

// int dfstraverse(int node){
//     for(int i=1;i<=n;i++){          //ȷ��ÿ����㶼�ܷ��ʵ�
//         if(!vis[i]){
//             dfs(i);                  
//             cnt++; //ÿһ��dfs��Ӧһ����ͨ����,������ʵ��ͦ������
//         }          //�������һ��������һֱ������ȥ�������϶�ֻ��һ��
//     }              //��ͨ����������������ˣ������ˣ�
//     return cnt;    //��������е�1256֮���3������һ���µķ�֧
// }                  //����������ȥ������һ���µ���ͨ����

// int main(){
//     cin >> n;
//     for(int i=1;i<=n;i++){        //��Ϊ���ӽ��1��ʼ���Դ��±�1��ʼ��
//         for(int j=1;j<=n;j++){
//             cin >> a[i][j];
//         }
//     }
//     dfstraverse(1);
//     cout << endl << dfstraverse(1);
//     return 0;
// }
