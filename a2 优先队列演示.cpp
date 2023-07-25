#include<iostream>
#include<queue>
#include<vector>

using namespace std;

int main(){
    priority_queue<int, vector<int>, less<int>> q;   //大到小
    // priority_queue<int, vector<int>, greater<int>> q;   //小到大
    q.push(1);
    q.push(3);
    q.push(2);
    q.push(4);
    q.push(6);
    q.push(5);

    q.size();

    while(!q.empty()){
        cout << q.top() << endl;
        q.pop();
    }

    vector<int> vec;
    vec = {1, 2, 3, 4};
    for(const auto &a : vec)
        cout << a << endl;
    return 0;
}
