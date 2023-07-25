#include<iostream>
#include<queue>
#include<vector>
using namespace std;

int main(){
//	priority_queue< int, vector<int>, greater<int> > q;
	priority_queue<int> q;
	int n,a,b,path=0,sum = 0;
	cin>>n;
	for(int i = 0; i < n; i++){
		cin>>a;
		q.push(-a);
	}
	while(q.size() > 1){
		a=-q.top();
		q.pop();
		b=-q.top();
		q.pop();
		sum = a+b;
		q.push(-sum);
		path += sum;
	}
	cout<<path<<endl;
	return 0;
}
