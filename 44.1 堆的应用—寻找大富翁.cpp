#include<iostream>
#include<algorithm>
using namespace std;
int n,m,k;
int a[15];
void down(int x){//∂—≈≈–Úƒ£∞Â
    int t=x;
    if(2*x<=k&&a[t]>=a[2*x])t=2*x;
    if(2*x+1<=k&&a[t]>=a[2*x+1])t=2*x+1;
    if(x!=t){
        swap(a[t],a[x]);
        down(t);
    }
}
int main(){
    cin>>n>>m;
     k=(n>=m?m:n);//≈–∂œn£¨m¥Û–°
    for(int i=1;i<=k;++i)cin>>a[i];
    for(int i=k/2;i;i--)down(i);
    n-=k;
    while(n--){
        int x;
        scanf("%d",&x);
        if(x<=a[1])continue;
        else {
            a[1]=x;
            down(1);
        }
    }
    sort(a+1,a+k+1);
    cout<<a[k];
    for(int i=k-1;i;--i)cout<<" "<<a[i];
    cout<<endl;
    return 0;
}
