// 实现单链表的插入、删除和遍历运算，每种操作用一个函数实现。
// 插入操作：将一个新元素插入表中指定序号的位置。
// 删除操作：将指定序号的元素从表中删除。
// 遍历操作：从表头按次序输出所有元素的值，若是空表，则输出信息“empty list!”。

#include<stdio.h>
#include<stdlib.h>

#define OVERFLOW -2

typedef struct Node{
    int data;
    struct Node *next;
} LNode, *LinkList;

//创建链表函数
int CreateList(LinkList LHead){
    int s = 0, n = 0;    //n用于返回链表元素个数
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

void InsertList(LinkList LHead, int i, int e){ // i为指定序号
    LinkList p = LHead;
    int j = 0;    //计数器
    while(p && j<i-1){    //找到第i-1个结点
        p = p->next; 
        j++;
    }
    if(!p || j>i-1){      //对应i>n和i<=0两种情况
        printf("i的值有误\n");
        return;
    }
    else{
        LinkList q = (LinkList)malloc(sizeof(LNode));
        if(!q)
            exit(OVERFLOW);
        q->data = e;
        q->next = p->next;
        p->next = q;
    }
}

void DeleteList(LinkList LHead,int i){
    LinkList p = LHead;
    int j = 0;
    while(p && j<i-1){    //找到第i-1个结点
    p = p->next; 
    j++;
    }
    if(!p || j>i-1){      //对应i>n和i<=0两种情况
        printf("i的值有误\n");
        return;
    }
    else{
        LinkList q = p->next;
        p->next = q->next;
        free(q);
    }
}

int main()
{
    LinkList LHead = (LinkList)malloc(sizeof(LNode));
    if(!LHead)
        exit(OVERFLOW);
    LHead->next = NULL;
    int n = CreateList(LHead);   //总结点个数
    PrintList(LHead);
    while(n>=0){
        DeleteList(LHead, 1);
        PrintList(LHead);
    }
    return 0;
}