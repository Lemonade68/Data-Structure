#include<iostream>
#include<cmath>
using namespace std;

typedef struct node{
    int key;
    int next;
} node, *Node;

int address[100001], value_abs[10001];
// address���ڱ���ѡ�еĽ��ĵ�ַ

int main(){
    int head, n, num = 0;
    int a, key, next;
    cin >> head >> n;
    node add[100001];       //add[i]���ڴ�ŵ�ַΪi������
    for (int i = 0; i < n; ++i){    //��������
        cin >> a >> key >> next;
        add[a].key = key;
        add[a].next = next;
    }
    while(head != -1){    //��������
        if(!value_abs[abs(add[head].key)]){
            address[num++] = head;          //  ����������ĵ�ַ
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