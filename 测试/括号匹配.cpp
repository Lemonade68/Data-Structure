#include<iostream>
#include<stack>
#include<string>
using namespace std;

int main(){
	int n;
	char str[101][10001];
	int bad[101]={0};
	int final[101]={0};
	cin>>n;
	char c;
	stack<char> s;
	for(int i = 0;i<n;i++){
		scanf("%s", str[i]);
		for(int j = 0; str[i][j]; j++){
			switch(str[i][j]){
				case '[':
					s.push(str[i][j]);
					break;
				case '(':
					s.push(str[i][j]);
					break;
				case ')':
					if(s.empty()){
						bad[i] = 1;
						break;
					}else if(s.top() != '('){
						bad[i] = 1;
						break;
					}else{
						s.pop();
						break;
					}
				case ']':
					if(s.empty()){
						bad[i] = 1;
						break;
					}else if(s.top() != '['){
						bad[i] = 1;
						break;
					}else{
						s.pop();
						break;
					}		
				default:
					break;			
			}
			if(bad[i] == 1)
				break;
		}
		if(bad[i] == 0 && s.empty())
			final[i]=1;
		
		while(!s.empty())
			s.pop();
		 
	}
	for(int i = 0;i<n;i++){
		if(final[i])
			cout<<"Yes"<<endl;
		else
			cout<<"No"<<endl;
	}
}
