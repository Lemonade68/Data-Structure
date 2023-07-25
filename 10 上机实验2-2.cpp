//括号匹配

// 算法思路 ：
// 1.遇左括号，入栈
// 2.遇右括号，与栈顶比较：若栈空，则右括号多余；不匹配；匹配   三种情况
// 3.读完一个表达式后，若栈不空，则左括号多余

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

char GetTop(Stack &s){      //读取栈顶元素操作
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
    printf("请输入表达式：");
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
                else if(GetTop(s)!='('){      //这边不能直接读--s.top取值，不然每判断一次s.top都会--
                    printf("no\n");
                    return 0;
                }
                else{
                    pop(s);
                    break;          //每一个执行后的case语句一定要以break结尾！！！
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
                    break;          //每一个执行后的case语句一定要以break结尾！！！
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
                    break;          //每一个执行后的case语句一定要以break结尾！！！
                }
            default:
                break;
        }
    }
    if(s.top == s.base){        //栈空则返回yes
        printf("yes\n");
        return 0;
    }
    printf("no\n");
    return 0;
}
