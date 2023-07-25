
#include<cstdio>
#include<cstring>
#include<iostream>
#include<stack>
#include<algorithm>
using namespace std;
const int M=1010;
char str[M],st[M],c;
stack<char> q;
int main()
{
    int i,j,k=0,l,m,n,f=0,t=0,ff=0;
    cin.getline(str,110);
    l=strlen(str);
    for(i=0; i<l; i++)
    {
        if(str[i]>='0'&&str[i]<='9')///为数字时输出
        {
            t=1;///标记已经出现过数字
            ///解决当有镶嵌括号时的格式问题
            if(ff==0)///特判当刚开始有镶嵌括号时防止f=1对格式的影响
            {
                printf("%c",str[i]);
                ff=1;
                f=0;
                continue;
            }
            ///解决超过一位数的问题
            if(f==0)///遇到数字并且前一个也是数字或'.'输出
                printf("%c",str[i]);
            else ///f=1时遇到数字加空格输出，并使f=0
            {
                printf(" %c",str[i]);
                f=0;
            }
        }
        ///解决小数问题
        else if(str[i]=='.')///遇到点说明为小数直接输出
        {
            printf("%c",str[i]);
        }
        ///解决第一位为正数带'+'的问题
        else if(i==0&&str[i]=='+')
        {
            printf("%c",str[i]);
        }
        ///解决第一位为正数带'-'的问题
        else if(i==0&&str[i]=='-')
        {
            printf("%c",str[i]);
        }
        ///解决非第一位为正数带'-'的问题
        else if(str[i]=='('&&str[i+1]=='-')
        {
            ///输出符号
            if(t==1)///若已经出现数字，加符号时需在前面加空格
                printf(" %c",str[i+1]);
            else
                printf("%c",str[i+1]);
            q.push(str[i]);///将括号入栈
            f=0;///输出数字无需加空格
            i++;///跳过这个'-'
        }
        ///解决非第一位为正数带'+'的问题
        else if(str[i]=='('&&str[i+1]=='+')
        {
            ///带正号的数字的正号可以约去
            q.push(str[i]);///将括号入栈
            f=1;///输入数字时需要加空格
            i++;///跳过'+'
        }
        ///当遇见左括号
        else if(str[i]=='(')
        {
            q.push(str[i]);///放入栈中
            f=1;
        }
        ///遇见右括号
        else if(str[i]==')')
        {
            ///输出左括号到右括号之间的符号
            while(q.top()!='(')
            {
                printf(" %c",q.top());
                f=1;///当输入数字时需加空格
                q.pop();///将输出的字符出栈
            }
            //printf("%c\n",q.top());
            q.pop();///将左括号出栈
        }
        else
        {
            ///当栈为空或者栈顶元素为左括号
            if(q.size()==0||q.top()=='(')
            {
                f=1;///输入数字时需要加空格
                q.push(str[i]);///将符号放入栈中
            }
            ///当需要入栈的符号优先级大于栈顶符号优先级
            else if((str[i]=='*'||str[i]=='/')&&(q.top()=='+'||q.top()=='-'))
            {
                f=1;///输入数字时需加括号
                q.push(str[i]);///将符号入栈
            }
            ///入栈的符号优先级小于或等于栈顶符号优先级
            ///栈中元素不为空且栈顶元素不是左括号
            else
            {
                ///当栈顶元素为'*'或'/'
                if(q.top()=='*'||q.top()=='/')
                {
                    f=1;///输入数字需加空格
                    printf(" %c",q.top());///加空格输出栈顶元素
                    q.pop();///将栈顶元素出栈
                    ///出栈完看栈中元素是否为空
                    
                    ///此时四种情况
                    ///（1）栈中元素为0
                    ///（2）栈顶元素为'('
                    ///（3）栈底元素为'+'或'-'，输入符号为'*'或'/'
                    ///（4）栈底元素为'+'或'-'，输入符号为'+'或'-'
                    
                    ///情况一和情况二
                    if(q.size()==0||q.top()=='(')
                    {
                        f=1;///输出数字时需加空格
                        q.push(str[i]);///将符号放入栈中
                    }
                    ///情况三
                    else if(str[i]=='*'||str[i]=='/')
                    {
                        f=1;///输出数字时需加空格
                        q.push(str[i]);///直接将符号入栈
                    }
                    ///情况四
                    else if(str[i]=='+'||str[i]=='-')
                    {
                        f=1;///输出数字时需加空格
                        printf(" %c",q.top());///将栈顶元素加空格输出
                        q.pop();///栈顶元素出栈
                        q.push(str[i]);///将符号放入栈中
                    }
                }
                ///当栈顶元素为'+'或'-'
                else if(q.top()=='+'||q.top()=='-')
                {
                    ///两种情况
                    ///（1）入栈符号为'*'或'/'
                    ///（2）入栈符号为'+'或'-'
                    
                    ///情况一
                    if(str[i]=='*'||str[i]=='/')
                    {
                        f=1;///输出数字时需加空格
                        q.push(str[i]);///将符号放入栈中
                    }
                    else if(str[i]=='+'||str[i]=='-')
                    {
                        f=1;///输出数字时需加空格
                        printf(" %c",q.top());///输出栈顶元素
                        q.pop();///栈顶元素出栈
                        q.push(str[i]);///将符号放入栈中
                    }
                }
            }
        }
    }
    ///当栈中符号未完全出栈
    while(q.size()!=0)
    {
        printf(" %c",q.top());///将栈中符号依次输出
        q.pop();///依次出栈
    }
    printf("\n");
    return 0;
}


