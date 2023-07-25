#include <stdio.h>
#define MaxSize 100

//Ackerman递归算法
int akm1(int m,int n){
	int q;
	if(m==0)
		return n+1;
	else if(n==0)
		return akm1(m-1,1);
	else{
		q=akm1(m,n-1);
		return akm1(m-1,q);
	}

}

typedef struct s{
    int mm,nn;  //存放每一次的m和n值
    int vf;     //存放每一层的akm(m,n)值
    int tag;    //标识每一层是否求出akm(m,n)值，0:表示未求出，1:表示已求出
}Stack[MaxSize];

//Ackerman非递归算法
int Akm(int m,int n){
	int top = -1;                           //栈指针
	top++;          
    Stack St;
    St[top].mm = m;
    St[top].nn = n;
    St[top].tag = 0;
    while(top > -1){                        //栈不空时
		if (St[top].tag==0){                //未计算出栈顶元素的vf值
			if (St[top].mm==0){             //对应(1)式
				St[top].vf=St[top].nn+1;
				St[top].tag=1;
			} 
			else if (St[top].nn==0){        //对应(2)式
				top++;
				St[top].mm=St[top-1].mm-1;
				St[top].nn=1;
				St[top].tag=0;
			}
			else{                           //对应(3)式
				top++;
				St[top].mm=St[top-1].mm;
				St[top].nn=St[top-1].nn-1;
				St[top].tag=0;
			}
		}
		else if (St[top].tag==1){           //已计算出vf值
			if (top>0 && St[top-1].nn==0){  //(2)式情况
				St[top-1].vf=St[top].vf;
				St[top-1].tag=1;
				top--;
			}
			else if (top > 0){              //(3)式情况
				St[top-1].mm=St[top-1].mm-1;
				St[top-1].nn=St[top].vf;
				St[top-1].tag=0;
				top--;
			}
		}
		if(top==0 && St[top].tag==1)        //剩最后结果时时退出循环
			break;
	}
	return St[top].vf;                      //返回最后结果
}

void main()
{
	int num1=0,num2=0,num3=0;
// 	num1=akm1(0,1);
// 	num2=akm1(1,2);
// 	num3=akm1(3,3);

	num1=Akm(0,1);
	num2=Akm(1,2);
	num3=Akm(3,3);

	printf("akm2(0,1)= %d\n",num1);
 	printf("akm2(1,2)= %d\n",num2);
 	printf("akm2(3,3)= %d\n",num3);

}
