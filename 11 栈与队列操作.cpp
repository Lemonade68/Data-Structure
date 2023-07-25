#include<stdio.h>
#include<stdlib.h>  
#define ElemType int
#define MAXSIZE 8

//重点！！

//栈的顺序结构：
typedef struct{
    ElemType *base;     //栈底指针
    ElemType *top;      //栈顶指针
    int stacksize;      //栈的空间大小
} SqStack;


//  1.栈空
s.base = s.top;
//  2.栈满
s.top - s.base >= s.stacksize;
//  3.入栈
*s.top++ = e;
//  4.出栈
e = *--s.top;   // ++/--优先级最高，*其次，最后是等号



//栈的链式结构：
typedef struct STNode{
    ElemType data;
    struct STNode *next;
} STNode, *LinkStack;

//在主程序中生成一个栈顶结点s，后续操作与链表相同

//注意：有头结点和无头结点两个版本的区别！
//无头结点：初始化时   s=NULL   后让新结点p->next指向s，再s=p;
//有头结点：初始化时   s->next=NULL     然后与链表操作同



//队列的链式结构：
typedef struct QNode{   //结点类型
    ElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct{         //链队列类型
    QueuePtr front;
    QueuePtr rear;
} LinkQueue;


//初始化：
Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode)); //设置头结点
if(!Q.front)
    exit(OVERFLOW);
Q.front->next = NULL;

//入队列：正常操作
p = (QNode *)malloc(sizeof(QNode));
if(!p)
    exit(OVERFLOW);
p->data = e;
p->next = NULL;     //注意这步
Q.rear->next = p;
Q.rear = p;

//出队列：注意细节！
if(Q.front == Q.rear)
    return ERROR;
p = Q.front->next;
e = p->data;
Q.front->next = p->next;
if(Q.rear == p)         //这一步一定要有！不然小心队列尾指针丢失
    Q.rear = Q.front;
free(p);

// !!!!链队列front始终指向头结点


//队列的顺序存储结构（循环队列）
//循环队列都应该使用顺序结构！！  想想
typedef struct{
    QElemType *base;    //用于动态分配存储空间
    int front;      //头指针，若队列不空，指向队列头元素
    int rear;       //尾指针，若队列不空，指向尾元素的下个位置
} SqQueue;

//初始化
Q.base = (QElemType *)malloc(sizeof(QElemType) * MAXSIZE);
Q.front = 0;
Q.rear = 0;

//插入队尾元素（入队）:
if((Q.rear+1)%MAXSIZE == Q.front)   //空出一个存储空间用于判断是否队满
    return ERROR;       //队列已满
Q.base[Q.rear] = e;
Q.rear = (Q.rear + 1) % MAXSIZE;

//删除队头元素（出队）：
if(Q.front == Q.rear)   //判断队空
    return ERROR;
e = Q.base[Q.front];
Q.front = (Q.front + 1) % MAXSIZE;

//循环队列队长：
Q.Length = [Q.rear - Q.front + MAXSIZE] % MAXSIZE;