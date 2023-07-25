#include<iostream>

using namespace std;

typedef struct Node{
	int coef;//ϵ�� 
	int exp;//ָ�� 
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
		//��һ���������ǣ��ų���������г��� ϵ��:0  ָ��:��Ϊ0  ����������� 
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
			//���ܣ����ǵĺ��ǲ��� 0�����Ƕ�Ҫ����L1,L2����һ����λ�� 
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
	���������ǲ��õ��ǣ�������롣
	ʲô��������룿
	1�����ó�L2�ĵ�һ�������L1��ÿһ����ˡ��Ӷ��õ� L��
	2�����ó�L2�ĵڶ��������L1��ÿһ����ˣ�Ȼ��ÿ��һ��ͽ�����뵽 L�С�
	3�������ظ�����Ĳ��裬���յõ�L�������ӡ������ 
	*/ 
	List L,temp = NULL,s = NULL;
	L = (struct Node *)malloc(sizeof(struct Node));
	temp = L;
	List La = L1;
	
	//��L2�ĵ�һ�������L1��ÿһ����ˡ��Ӷ��õ� L��
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
	������˵��һ�� flag ����������ã�
	���ڱ�ǣ�������ĳ����У��Ƿ�����ˣ�  if( > ) �� if( == )����Ĳ�����
	�������ˣ���flag�ͱ�Ϊ false�����ý��У� while(.....){.....},������ĵ�һ����䣬
	�������ĺ����ǣ���L��û���ҵ������ �������� ��λ�ã����Խ�������l��β���� 
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
