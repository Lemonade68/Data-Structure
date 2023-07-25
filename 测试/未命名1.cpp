#include<iostream>
#include<cmath>
#define endl '\n'
using namespace std;

typedef struct{
	int key,next;
	int isfirst=0;
}Node;

Node a[1000000];

int main(){
	int fadd, len, add, key, next, number=0;
	int num[100000]={0};
	cin >> fadd >> len;
	int f = fadd;
	for(int i = 0; i < len; i++){
		cin >> add >> key >> next;
		a[add].key = key;
		a[add].next = next;
		if(!num[abs(key)]){
			num[abs(key)]=1;
			a[add].isfirst=1;
			number++;
		}	
	}
	
	cout<<number<<endl;
	
	while(a[fadd].next != -1){
		if(a[a[fadd].next].isfirst == 0)
			a[fadd].next = a[a[fadd].next].next;
		else
			fadd = a[fadd].next;
	}

	while(a[f].next != -1){
		printf("%.5d %d %.5d\n",f,a[f].key,a[f].next);
		f = a[f].next;
	}
	
	printf("%.5d %d -1\n",f,a[f].key);
	return 0;			
}
