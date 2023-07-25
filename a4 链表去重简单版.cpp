#include<iostream>
#include<cmath>
using namespace std;

typedef struct node{
    int key;
    int next;
} node, *Node;

int address[100001], value_abs[10001];
// address用于保存选中的结点的地址

int main(){
    int head, n, num = 0;
    int a, key, next;
    cin >> head >> n;
    node add[100001];       //add[i]用于存放地址为i的数据
    for (int i = 0; i < n; ++i){    //输入数据
        cin >> a >> key >> next;
        add[a].key = key;
        add[a].next = next;
    }
    while(head != -1){    //处理数据
        if(!value_abs[abs(add[head].key)]){
            address[num++] = head;          //  存最终输出的地址
            value_abs[abs(add[head].key)] = 1;
        }
        head = add[head].next;
    }
    cout << num << endl;
    int i;
    for (i = 0; i < num - 1; ++i){
        printf("%.5d %d %.5d\n", address[i], add[address[i]].key, address[i + 1]);
    }
    printf("%.5d %d -1\n", address[i], add[address[i]].key);
    return 0;
}