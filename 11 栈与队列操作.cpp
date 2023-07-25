#include<stdio.h>
#include<stdlib.h>  
#define ElemType int
#define MAXSIZE 8

//�ص㣡��

//ջ��˳��ṹ��
typedef struct{
    ElemType *base;     //ջ��ָ��
    ElemType *top;      //ջ��ָ��
    int stacksize;      //ջ�Ŀռ��С
} SqStack;


//  1.ջ��
s.base = s.top;
//  2.ջ��
s.top - s.base >= s.stacksize;
//  3.��ջ
*s.top++ = e;
//  4.��ջ
e = *--s.top;   // ++/--���ȼ���ߣ�*��Σ�����ǵȺ�



//ջ����ʽ�ṹ��
typedef struct STNode{
    ElemType data;
    struct STNode *next;
} STNode, *LinkStack;

//��������������һ��ջ�����s������������������ͬ

//ע�⣺��ͷ������ͷ��������汾������
//��ͷ��㣺��ʼ��ʱ   s=NULL   �����½��p->nextָ��s����s=p;
//��ͷ��㣺��ʼ��ʱ   s->next=NULL     Ȼ�����������ͬ



//���е���ʽ�ṹ��
typedef struct QNode{   //�������
    ElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct{         //����������
    QueuePtr front;
    QueuePtr rear;
} LinkQueue;


//��ʼ����
Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode)); //����ͷ���
if(!Q.front)
    exit(OVERFLOW);
Q.front->next = NULL;

//����У���������
p = (QNode *)malloc(sizeof(QNode));
if(!p)
    exit(OVERFLOW);
p->data = e;
p->next = NULL;     //ע���ⲽ
Q.rear->next = p;
Q.rear = p;

//�����У�ע��ϸ�ڣ�
if(Q.front == Q.rear)
    return ERROR;
p = Q.front->next;
e = p->data;
Q.front->next = p->next;
if(Q.rear == p)         //��һ��һ��Ҫ�У���ȻС�Ķ���βָ�붪ʧ
    Q.rear = Q.front;
free(p);

// !!!!������frontʼ��ָ��ͷ���


//���е�˳��洢�ṹ��ѭ�����У�
//ѭ�����ж�Ӧ��ʹ��˳��ṹ����  ����
typedef struct{
    QElemType *base;    //���ڶ�̬����洢�ռ�
    int front;      //ͷָ�룬�����в��գ�ָ�����ͷԪ��
    int rear;       //βָ�룬�����в��գ�ָ��βԪ�ص��¸�λ��
} SqQueue;

//��ʼ��
Q.base = (QElemType *)malloc(sizeof(QElemType) * MAXSIZE);
Q.front = 0;
Q.rear = 0;

//�����βԪ�أ���ӣ�:
if((Q.rear+1)%MAXSIZE == Q.front)   //�ճ�һ���洢�ռ������ж��Ƿ����
    return ERROR;       //��������
Q.base[Q.rear] = e;
Q.rear = (Q.rear + 1) % MAXSIZE;

//ɾ����ͷԪ�أ����ӣ���
if(Q.front == Q.rear)   //�ж϶ӿ�
    return ERROR;
e = Q.base[Q.front];
Q.front = (Q.front + 1) % MAXSIZE;

//ѭ�����жӳ���
Q.Length = [Q.rear - Q.front + MAXSIZE] % MAXSIZE;