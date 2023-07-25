//十进制转化为二进制


#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -2

typedef struct stack{
    int *top;
    int *base;
    int Stacksize = 20;   //假定为20，可改为宏常量
} Stack;

void InitStack(Stack &s){
    s.base = (int *)malloc(sizeof(int) * s.Stacksize);
    if(!s.base)
        exit(OVERFLOW);
    s.top = s.base;
}

void Transform(Stack &s, int &n){   //进制转化
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
    printf("转化为二进制后结果为：\n");
    while(s.top != s.base){
        s.top--;                //注意先减后输出
        printf("%d", *s.top);
    }
}

int main()
{
    Stack s;
    int n;
    InitStack(s);
    printf("请输入一个十进制数：");
    scanf("%d", &n);
    Transform(s, n);
    PrintStack(s);
    return 0;
}