//�Դ�ͷ����ѭ�������ʾ���У�ֻ����ʹ��rearָ��

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
    if(q.rear->next == q.rear)  //�ӿ�
        exit(OVERFLOW);
    Queueptr p = q.rear->next;  //pָ��ͷ���
    Queueptr s = p->next;       //sָ���ͷԪ��
    p->next = s->next;
    e = s->data;                //e����s��ֵ
    if(q.rear == s)             //ɾ�����һ��Ԫ��ʱע���ֹq.rear��ʧ
        q.rear == q.rear->next;
    free(s);
    return e;
}