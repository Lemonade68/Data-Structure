//����ƥ��

// �㷨˼· ��
// 1.�������ţ���ջ
// 2.�������ţ���ջ���Ƚϣ���ջ�գ��������Ŷ��ࣻ��ƥ�䣻ƥ��   �������
// 3.����һ�����ʽ����ջ���գ��������Ŷ���

#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
#define OVERFLOW -2

typedef struct stack
{
    char *top;
    char *base;
    int StackSize = MAXSIZE;
}Stack;

void InitStack(Stack &s){
    s.base = (char *)malloc(sizeof(char) * MAXSIZE);
    if(!s.base)
        exit(OVERFLOW);
    s.top = s.base;
}

char GetTop(Stack &s){      //��ȡջ��Ԫ�ز���
    if(s.top==s.base)
        exit(OVERFLOW);
    return *(s.top - 1);
}

void push(Stack &s, char c){
    if(s.top-s.base>=s.StackSize)
        exit(OVERFLOW);
    *s.top++ = c;
}

void pop(Stack &s){
    if(s.top == s.base)
        exit(OVERFLOW);
    --s.top;
}

int main(){
    char expr[MAXSIZE];
    Stack s;
    InitStack(s);
    printf("��������ʽ��");
    scanf("%s", expr);
    for (int i = 0; expr[i];i++){
        switch(expr[i]){
            case '(':
                push(s, expr[i]);
                break;
            case '[':
                push(s, expr[i]);
                break;
            case '{':
                push(s, expr[i]);
                break;
            case ')':
                if(s.top==s.base){
                    printf("no\n");
                    return 0;
                }
                else if(GetTop(s)!='('){      //��߲���ֱ�Ӷ�--s.topȡֵ����Ȼÿ�ж�һ��s.top����--
                    printf("no\n");
                    return 0;
                }
                else{
                    pop(s);
                    break;          //ÿһ��ִ�к��case���һ��Ҫ��break��β������
                }
            case ']':
                if(s.top==s.base){
                    printf("no\n");
                    return 0;
                }
                else if(GetTop(s)!='['){    
                    printf("no\n");
                    return 0;
                }
                else{
                    pop(s);
                    break;          //ÿһ��ִ�к��case���һ��Ҫ��break��β������
                }
            case '}':
                if(s.top==s.base){
                    printf("no\n");
                    return 0;
                }
                else if(GetTop(s)!='{'){
                    printf("no\n");
                    return 0;
                }
               else{
                    pop(s);
                    break;          //ÿһ��ִ�к��case���һ��Ҫ��break��β������
                }
            default:
                break;
        }
    }
    if(s.top == s.base){        //ջ���򷵻�yes
        printf("yes\n");
        return 0;
    }
    printf("no\n");
    return 0;
}
