// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// #include<math.h>

// #define m -1

// typedef struct lst{
//     int data;
//     int next;
// } List;

// int main()
// {
//     int bInitads, cInitads, n, ip, ip_b, ip_c, d1_counter = 0, d1[1001] = {0}, b_counter = 0, c_counter = 0;
//     List a[100001];
//     int  b[100001], c[100001];

//     int isIncluded = 0;
//     scanf("%d %d", &bInitads, &n);
//     for (int i = 0; i < n; i++)
//     {
//         scanf("%d", &ip);
//         scanf("%d %d", &a[ip].data, &a[ip].next);
//     }

//     ip = bInitads;
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < d1_counter;j++)
//             if(abs(a[ip].data)==abs(d1[j]))
//                 isIncluded = 1;

//         if(isIncluded==0)
//         {
//             d1[d1_counter++] = a[ip].data;
//             if(b_counter==0)
//                 bInitads = ip;
//             b[ip] = 1;
//             b_counter++;
//             ip = a[ip].next;
//         }
//         else
//         {
//             if(c_counter==0)
//                 cInitads = ip;
//             c[ip] = 1;
//             c_counter++;
//             ip = a[ip].next;
//         }
//         isIncluded = 0;
//     }

//     ip = bInitads;
//     int ctr = 0;
//     for (int i = 0; i < n; i++)
//     {
//         if (ctr == b_counter - 1 && b[ip] == 1)
//         {
//             printf("%05d\n%05d %d %d\n", ip, ip, a[ip].data,m);
//             break;
//         }
//         else if(ctr==0 && b[ip]==1)
//         {
//             printf("%05d %d ", ip, a[ip].data);
//             ip = a[ip].next;
//             ctr++;
//         }
//         else if(b[ip]==1)
//         {
//             printf("%05d\n%05d %d ", ip, ip,a[ip].data);
//             ip = a[ip].next;
//             ctr++;
//         }
//         else
//             ip = a[ip].next;
//     }
    
//     ip = cInitads;
//     ctr = 0;
//     for (int i = 0; i < n; i++)
//     {
//         if(ctr==c_counter -1 && c[ip]==1)
//         {
//             printf("%05d\n%05d %d %d\n", ip, ip, a[ip].data,m);
//             break;
//         }
//         else if(ctr==0 && c[ip]==1)
//         {
//             printf("%05d %d ", ip, a[ip].data);
//             ip = a[ip].next;
//             ctr++;
//         }
//         else if(c[ip]==1)
//         {
//             printf("%05d\n%05d %d ", ip, ip,a[ip].data);
//             ip = a[ip].next;
//             ctr++;
//         }
//         else
//             ip = a[ip].next;
//     }

//         return 0;
// }


#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
struct name{
	int data;//存数
	int next;//存下一个数的下标
};
struct name a[100005];
	int h,n;//头结点和数的数量
	int tidx[100005];//未被删除的元素的下标
	int fidx[100005];//被删除的元素的下标
	int ab[100005];//标记每个数的绝对值
	int t=0,f=0;//删除后序列的数量和删除的数量
int main(){
	cin>>h>>n;
	for(int i=0;i<n;i++){
		int idx,x,nidx;
		cin>>idx>>x>>nidx;
		a[idx].data =x;
		a[idx].next =nidx;
	}
	if(n==1){//这里要特判一下n==1的情况
		printf("%05d %d %d",h,a[h].data ,-1);
	}else{
		while(h!=-1){//遍历链表
		if(ab[abs(a[h].data )]==0){//如果没有出现过
			tidx[t++]=h;//把他的下标存入未被删除的序列
			ab[abs(a[h].data )]=1;//标记
		}else{
			fidx[f++]=h;//把他放入删除元素的下标
		}
		h=a[h].next ;
	}
	for(int i=0;i<t-1;i++){
		printf("%05d %d %05d\n",tidx[i],a[tidx[i]].data ,tidx[i+1]);
	}
	printf("%05d %d %d\n",tidx[t-1],a[tidx[t-1]].data ,-1);
	for(int i=0;i<f-1;i++){
		printf("%05d %d %05d\n",fidx[i],a[fidx[i]].data ,fidx[i+1]);
	}
	printf("%05d %d %d\n",fidx[f-1],a[fidx[f-1]].data ,-1);
	}
	
	return 0;
}
