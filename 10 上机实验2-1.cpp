//ʮ����ת��Ϊ������


#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -2

typedef struct stack{
    int *top;
    int *base;
    int Stacksize = 20;   //�ٶ�Ϊ20���ɸ�Ϊ�곣��
} Stack;

void InitStack(Stack &s){
    s.base = (int *)malloc(sizeof(int) * s.Stacksize);
    if(!s.base)
        exit(OVERFLOW);
    s.top = s.base;
}

void Transform(Stack &s, int &n){   //����ת��
    if(s.top-s.base>=s.Stacksize)
        exit(OVERFLOW);
    while(n!=1){
        *s.top++ = n % 2;
        n = n / 2;
    }
    *s.top++ = 1;
}

void PrintStack(Stack &s){
    if(s.top == s.base){
        printf("Stack is empty!");
        return;
    }
    printf("ת��Ϊ�����ƺ���Ϊ��\n");
    while(s.top != s.base){
        s.top--;                //ע���ȼ������
        printf("%d", *s.top);
    }
}

int main()
{
    Stack s;
    int n;
    InitStack(s);
    printf("������һ��ʮ��������");
    scanf("%d", &n);
    Transform(s, n);
    PrintStack(s);
    return 0;
}