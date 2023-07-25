#include <stdio.h>
#define MaxSize 100

//Ackerman�ݹ��㷨
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
    int mm,nn;  //���ÿһ�ε�m��nֵ
    int vf;     //���ÿһ���akm(m,n)ֵ
    int tag;    //��ʶÿһ���Ƿ����akm(m,n)ֵ��0:��ʾδ�����1:��ʾ�����
}Stack[MaxSize];

//Ackerman�ǵݹ��㷨
int Akm(int m,int n){
	int top = -1;                           //ջָ��
	top++;          
    Stack St;
    St[top].mm = m;
    St[top].nn = n;
    St[top].tag = 0;
    while(top > -1){                        //ջ����ʱ
		if (St[top].tag==0){                //δ�����ջ��Ԫ�ص�vfֵ
			if (St[top].mm==0){             //��Ӧ(1)ʽ
				St[top].vf=St[top].nn+1;
				St[top].tag=1;
			} 
			else if (St[top].nn==0){        //��Ӧ(2)ʽ
				top++;
				St[top].mm=St[top-1].mm-1;
				St[top].nn=1;
				St[top].tag=0;
			}
			else{                           //��Ӧ(3)ʽ
				top++;
				St[top].mm=St[top-1].mm;
				St[top].nn=St[top-1].nn-1;
				St[top].tag=0;
			}
		}
		else if (St[top].tag==1){           //�Ѽ����vfֵ
			if (top>0 && St[top-1].nn==0){  //(2)ʽ���
				St[top-1].vf=St[top].vf;
				St[top-1].tag=1;
				top--;
			}
			else if (top > 0){              //(3)ʽ���
				St[top-1].mm=St[top-1].mm-1;
				St[top-1].nn=St[top].vf;
				St[top-1].tag=0;
				top--;
			}
		}
		if(top==0 && St[top].tag==1)        //ʣ�����ʱʱ�˳�ѭ��
			break;
	}
	return St[top].vf;                      //���������
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
