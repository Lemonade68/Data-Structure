// 设停车场是一个可停放n辆汽车的狭长通道，且只有一个大门可供汽车进出。
// 汽车在停车场内按车辆到达时间的先后顺序，依次由北向南排列（大门在最南端，
// 最先到达的第一辆车停放在车场的最北端），若车场内已停满n辆汽车，则后来的汽车只能在
// 门外的便道上等候，一旦有车开走，则排在便道上的第一辆车即可开入。当停车场内某辆车要离开时，
// 在它之后进入的车辆必须先退出车场为它让路，待该辆车开出大门外，其他车辆再按原次序进入车场，
// 每辆停放在车场的车在它离开停车场时必须按它停留的时间长短交纳费用。
// 试为停车场编制按上述要求进行管理的模拟程序。

#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -2
#define fee 10          //一时刻收费10元（假设）

typedef struct car{     //车
    int carnum;
    int arivtime;       //注意后续要改变为进入停车场时的时刻
    int leavtime;
    struct car *next;   //供链式队列使用
} Car, *Carptr;         //carptr相当于结点node

typedef struct carpark{ //停车场栈，用顺序结构
    Carptr base;
    Carptr top;
    int n; //上限
} CarPark;

typedef struct tem{     //临时停车场
    Carptr base;
    Carptr top;
    int n;
} TemPark;

typedef struct queue{   //车场外便道队列，用链表结构
    Carptr front;
    Carptr rear;
} Queue;


//函数区
void InitCarPark(CarPark &p, TemPark &tp, int n);                   //初始化两个停车场
void InitQueue(Queue &q);                                           //初始化便道
void push(CarPark &p, Carptr &c);                                   //停车场的入栈函数
void tempush(TemPark &tp, Carptr &c);                               //临时停车场的入栈函数
void enqueue(Queue &q, Carptr &c);                                  //入便道
int searchparknum(CarPark &p, Carptr &c);                           //查找车在停车场的位置
int searchqueuenum(Queue &q, Carptr &c);                            //查找车在便道的位置
Carptr dequeue(Queue &q);                                           //将便道的第一个车弹出，返回该结点
void In(CarPark &p, Queue &q, int time, int carnum);                //处理进停车场的函数
void Out(CarPark &p, TemPark &tp, Queue &q, int carnum, int time);  //处理出停车场的函数


int main()
{
    int n = 0;
    printf("输入n的值:");
    scanf("%d", &n);

    //初始化停车场与队列
    CarPark p;
    TemPark tp;
    InitCarPark(p, tp, n);
    Queue q;
    InitQueue(q);

    //开始管理
    printf("请输入停车场运营数据,按照时刻顺序,一行输入一个,最后以 E 0 0 结尾 例如 A 1 5\n");
    char a;
    int carnum, time;
    while(1){
        scanf("%c %d %d", &a, &carnum, &time);
        switch (a)
        {
        case 'A':
            In(p,q,time,carnum);                    //进入停车场
            break;
        case 'D':                                   //假设给定数据都为在停车场内的数据
            Out(p, tp, q, carnum, time);            //离开停车场
            break;
        case 'E':
            printf("感谢使用！\n");
            return 0;       //退出程序
            break;
        default:
            break;
        }
    }    
}


void InitCarPark(CarPark &p, TemPark &tp, int n){                       //初始化两个停车场
    p.base = (Carptr)malloc(sizeof(Car) * n);
    if(!p.base)
        exit(OVERFLOW);
    tp.base = (Carptr)malloc(sizeof(Car) * n);
    if(!tp.base)
        exit(OVERFLOW);
    p.top = p.base;
    tp.top = tp.base;
    p.n = n;
    tp.n = n;
}

void InitQueue(Queue &q){                                               //初始化便道
    q.front = q.rear = (Carptr)malloc(sizeof(Car));
    if(!q.front)
        exit(OVERFLOW);
    q.front->next = NULL;
}

void push(CarPark &p, Carptr &c){                                       //停车场的入栈函数
    if(p.top-p.base>p.n)
        exit(OVERFLOW);
    *p.top++ = *c;
}

void tempush(TemPark &tp, Carptr &c){                                   //临时停车场的入栈函数
    if(tp.top-tp.base>tp.n)
        exit(OVERFLOW);
    *tp.top++ = *c;
}

void enqueue(Queue &q, Carptr &c){                                      //入便道
    c->next = NULL;
    q.rear->next = c;
    q.rear = c;
}

int searchparknum(CarPark &p, Carptr &c){                               //查找车在停车场的位置
    Carptr search = p.base;
    int i = 1;
    while(search->carnum != c->carnum){
        i++;
        search++;    //连续存储，指针可以直接++     注意与下一个函数的search加法区别！！
    }
    return i;
}

int searchqueuenum(Queue &q, Carptr &c){                                //查找车在便道的位置
    Carptr search = q.front->next;
    int i = 1;
    while(search->carnum != c->carnum){
        i++;
        search=search->next;    //链式存储，指针应该变成next的指针！
    }
    return i;
}

Carptr dequeue(Queue &q){                                               //将便道的第一个车弹出，返回该结点
    if(q.front == q.rear)
        exit(OVERFLOW);
    else{
        Carptr p = q.front->next;
        Carptr m = p->next;
        q.front->next = m;
        if(q.rear == p)         //特殊情况：若弹出的是最后一个元素
            q.rear = q.front;
        return p;               //返回便道的第一个车
    }
}

void In(CarPark &p, Queue &q, int time, int carnum){                    //处理进停车场的函数
    if(p.top-p.base<p.n){    //停车场未满   这边不能取等号！
        Carptr c = (Carptr)malloc(sizeof(Car));
        if(!c)
            exit(OVERFLOW);
        c->arivtime = time;
        c->carnum = carnum;
        push(p, c);           //入停车场
        printf("车牌号为%d的车进入停车场，位置为第%d个;\n", carnum, searchparknum(p, c));
    } 
    else{                     //停车场已满，入便道（队列）
        Carptr c = (Carptr)malloc(sizeof(Car));
        if(!c)
            exit(OVERFLOW);
        c->carnum = carnum;
        c->arivtime = time;     //注意后面要更改
        enqueue(q, c);
        printf("停车场已满！车牌号为%d的车进入便道，位置为第%d个;\n", carnum, searchqueuenum(q, c));
    }
}

void Out(CarPark &p, TemPark &tp, Queue &q, int carnum, int time){      //处理出停车场的函数
    //其他车出栈，入到临时栈，直到找到该车
    Carptr search = p.top - 1;  //从top-1开始找
    while(search->carnum != carnum){
        tempush(tp, search);    //将该车临时存入临时停车场
        search--;               
        p.top--;                //该车出栈
    }
    //此时search指向找到的这辆车
    printf("车牌号为%d的车离开停车场！本次停留时长为%d，收费为%d\n", carnum, time - search->arivtime, fee * (time - search->arivtime));
    //这辆车出停车场
    p.top--;
    //临时停车场的车返回停车场
    search = tp.top - 1;
    while(tp.top > tp.base){
        push(p, search);        //返回停车场
        search--;
        tp.top--;
    }
    //此时停车场已全部返回，下面处理便道的车辆
    if(q.front==q.rear)             //若便道没有车辆
        return;
    else{                           //若便道有车，那么第一辆进入停车场
        Carptr c = dequeue(q);      //接受返回的车辆
        c->arivtime = time;         //更新进入停车场的时间
        push(p, c);                 //进入停车场
    }
}
