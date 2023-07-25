// 分别定义函数实现创建单链表、遍历单链表并输出和排序过程。
// 程序运行时，首先在main函数中调用创建单链表的函数，然后调用遍历单链表
// （包含对元素的输出）的函数，再调用排序函数，最后再调用遍历单链表
// （包含对元素的输出）的函数观察是否实现了排序运算。

#include<stdio.h>
#include<stdlib.h>

#define OVERFLOW -2

typedef struct Node{
    int data;
    struct Node *next;
} LNode, *LinkList;

//创建链表函数，与实验1相同，直到输入0停止录入
int CreateList(LinkList LHead){
    int s = 0, n = 0;
    while(true){
        scanf("%d", &s);
        if(s==0)        //输入为0，停止输入
            break;
        else{
            LinkList p = (LinkList)malloc(sizeof(LNode));
            if(!p)
                exit(OVERFLOW);
            p->data = s;
            p->next = LHead->next;
            LHead->next = p;
            n++;
        }
    }
    return n;
}

//遍历并输出链表函数
void PrintList(LinkList LHead){
    if(LHead->next==NULL){            //开始时判断：若表长为0，输出空表并结束
        printf("Empty list!\n");  
        return;
    }
    LinkList p = LHead->next;
    while(p!=NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

//链表排序函数
void SortList(LinkList LHead,int n){
    LinkList p = LHead->next;
    int m = 0; //用于中间转换
    for (int i = 0; i < n;i++){
        p = LHead->next;
        for (int j = 0; j < n - i - 1; j++){
            if(p->data <= p->next->data){
                m = p->data;
                p->data = p->next->data;
                p->next->data = m;
                p = p->next;
            }
            else
                p = p->next;        //注意这边也要写
        }
    }
}

int main()
{
    LinkList LHead = (LinkList)malloc(sizeof(LNode));
    if(!LHead)
        exit(OVERFLOW);
    LHead->next = NULL;
    int n = CreateList(LHead);      //创建链表并得到个数
    PrintList(LHead);       //遍历并输出链表
    SortList(LHead, n);     //冒泡排序链表
    PrintList(LHead);       //遍历并输出链表
    return 0;
}