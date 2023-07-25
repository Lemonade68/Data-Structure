//以带头结点的循环链表表示队列，只允许使用rear指针

#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -2
#define Elemtype int

typedef struct q{
    Elemtype data;
    struct q *next;
} QNode, *Queueptr;

typedef struct queue{
    Queueptr rear;
} Queue;

void InitQueue(Queue &q){
    q.rear = (Queueptr)malloc(sizeof(QNode));
    if(!q.rear)
        exit(OVERFLOW);
    q.rear->next = q.rear;
}

void enQueue(Queue &q, int e){
    Queueptr p = (Queueptr)malloc(sizeof(QNode));
    if(!p)
        exit(OVERFLOW);
    p->data = e;
    p->next = q.rear->next;
    q.rear->next = p;
    q.rear = p;
}

int deQueue(Queue &q, int e){
    if(q.rear->next == q.rear)  //队空
        exit(OVERFLOW);
    Queueptr p = q.rear->next;  //p指向头结点
    Queueptr s = p->next;       //s指向队头元素
    p->next = s->next;
    e = s->data;                //e返回s的值
    if(q.rear == s)             //删除最后一个元素时注意防止q.rear丢失
        q.rear == q.rear->next;
    free(s);
    return e;
}