#include<iostream>

using namespace std;

typedef struct Node{
	int coef;//系数 
	int exp;//指数 
	struct Node *next;
} *List;

List read(List L);
void print(List L);
List getMuti(List L1,List L2);
List getSum(List L1,List L2);


List read(List L){
	List s=NULL,temp;
	L = (struct Node*)malloc(sizeof(struct Node));
	temp = L;
	int n,COEF,EXP;
	cin>>n;
	for(int i=0;i<n;i++){
		
		cin>>COEF>>EXP;
		//这一步的作用是，排除读入过程中出现 系数:0  指数:不为0  的这种情况。 
		if(COEF!=0){	
			s = (struct Node *)malloc(sizeof(struct Node));
			s->coef = COEF; s->exp=EXP;
			L->next = s;
			L = s;
		}	
	}
	L->next=NULL;
	return temp;
	
}


void print(List L){
	
	if(L->next!=NULL){
		L = L->next;	
		while(L){
			if(L->next)
			cout<<L->coef<<" "<<L->exp<<" ";
			else
			cout<<L->coef<<" "<<L->exp<<endl;
			L = L->next;
		}
	}
	else
	cout<<0<<" "<<0<<endl;
}


List getSum(List L1,List L2){
	
	List L,temp = NULL,s = NULL;
	L = (struct Node *)malloc(sizeof(struct Node));
	temp = L;
	
	while(L1->next&&L2->next){
		
		if(L1->next->exp>L2->next->exp){
			s = (struct Node *)malloc(sizeof(struct Node));
			s->coef = L1->next->coef;
			s->exp = L1->next->exp;
			L->next = s;
			L = s; 
			L1 = L1->next;
		}
		else if(L1->next->exp<L2->next->exp){
			s = (struct Node *)malloc(sizeof(struct Node));
			s->coef = L2->next->coef;
			s->exp = L2->next->exp;
			L->next = s;
			L = s; 
			L2 = L2->next;
		}
		else{ 
			if(L2->next->coef+L1->next->coef!=0){	
				s = (struct Node *)malloc(sizeof(struct Node));
				s->coef = L2->next->coef+L1->next->coef;
				s->exp = L2->next->exp;
				L->next = s;
				L = s; 
			}
			//不管，他们的和是不是 0，我们都要，将L1,L2后移一个单位。 
			L1 = L1->next;
			L2 = L2->next;
		}		
	}
	if(L1->next)
	L->next = L1->next;
	else
	L->next = L2->next;
	return temp;		
}


List getMuti(List L1,List L2){
	/*
	在这里我们采用的是：逐项插入。
	什么是逐项插入？
	1，先拿出L2的第一项，让它与L1的每一项相乘。从而得到 L。
	2，在拿出L2的第二项，让它与L1的每一项相乘，然后每乘一项，就将其插入到 L中。
	3，依次重复上面的步骤，最终得到L。将其打印出来。 
	*/ 
	List L,temp = NULL,s = NULL;
	L = (struct Node *)malloc(sizeof(struct Node));
	temp = L;
	List La = L1;
	
	//出L2的第一项，让它与L1的每一项相乘。从而得到 L。
	while(La->next){	
		s = (struct Node *)malloc(sizeof(struct Node));
		s->coef = La->next->coef * L2->next->coef;
		s->exp = La->next->exp + L2->next->exp;
		L->next=s;
		L = s;
		La = La->next;
	}
	
	L->next = NULL;
	L = temp;
	List Lb = L2->next;
	bool flag = true;
	/*
	在这里说明一下 flag 在这里的作用：
	用于标记，在下面的程序中，是否进行了，  if( > ) 和 if( == )里面的操作，
	若进行了，则flag就变为 false，则不用进行， while(.....){.....},结束后的第一条语句，
	这条语句的含义是，在L中没有找到，这个 待插入项 的位置，所以将其置于l的尾部。 
	*/
	while(Lb&&Lb->next){
		La = L1;		
		while(La->next){
			s = (struct Node *)malloc(sizeof(struct Node));
			s->coef = La->next->coef * Lb->next->coef;
			s->exp = La->next->exp + Lb->next->exp;
			while(L->next){
				
				if(s->exp > L->next->exp){		
					
					List val = L->next;
					L->next = s;
					s->next = val;
					flag = false;
					break;			
				}
				else if(s->exp == L->next->exp)
				{
					if(s->coef + L->next->coef==0){
						List val = L->next->next;
						L->next = val;	
					}
					else
					L->next->coef += s->coef;
					flag = false;
					break;
				}
				L = L->next;
			}
			
			if(flag){
				L->next = s;
				s->next = NULL;
			}
			L = temp;
			La = La->next;
			flag  = true;
		}		
		Lb = Lb->next;
	}
	return temp;
	
}

int main(){
	List L1,L2,L=NULL;
	L1 = read(L1);
	L2 = read(L2);
	L = getMuti(L1,L2);
	print(L);
	L = getSum(L1,L2);
	print(L);
	return 0;
}
