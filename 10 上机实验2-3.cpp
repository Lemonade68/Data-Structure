// ��ͣ������һ����ͣ��n������������ͨ������ֻ��һ�����ſɹ�����������
// ������ͣ�����ڰ���������ʱ����Ⱥ�˳�������ɱ��������У����������϶ˣ�
// ���ȵ���ĵ�һ����ͣ���ڳ�������ˣ�������������ͣ��n�������������������ֻ����
// ����ı���ϵȺ�һ���г����ߣ������ڱ���ϵĵ�һ�������ɿ��롣��ͣ������ĳ����Ҫ�뿪ʱ��
// ����֮�����ĳ����������˳�����Ϊ����·�������������������⣬���������ٰ�ԭ������복����
// ÿ��ͣ���ڳ����ĳ������뿪ͣ����ʱ���밴��ͣ����ʱ�䳤�̽��ɷ��á�
// ��Ϊͣ�������ư�����Ҫ����й����ģ�����

#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -2
#define fee 10          //һʱ���շ�10Ԫ�����裩

typedef struct car{     //��
    int carnum;
    int arivtime;       //ע�����Ҫ�ı�Ϊ����ͣ����ʱ��ʱ��
    int leavtime;
    struct car *next;   //����ʽ����ʹ��
} Car, *Carptr;         //carptr�൱�ڽ��node

typedef struct carpark{ //ͣ����ջ����˳��ṹ
    Carptr base;
    Carptr top;
    int n; //����
} CarPark;

typedef struct tem{     //��ʱͣ����
    Carptr base;
    Carptr top;
    int n;
} TemPark;

typedef struct queue{   //�����������У�������ṹ
    Carptr front;
    Carptr rear;
} Queue;


//������
void InitCarPark(CarPark &p, TemPark &tp, int n);                   //��ʼ������ͣ����
void InitQueue(Queue &q);                                           //��ʼ�����
void push(CarPark &p, Carptr &c);                                   //ͣ��������ջ����
void tempush(TemPark &tp, Carptr &c);                               //��ʱͣ��������ջ����
void enqueue(Queue &q, Carptr &c);                                  //����
int searchparknum(CarPark &p, Carptr &c);                           //���ҳ���ͣ������λ��
int searchqueuenum(Queue &q, Carptr &c);                            //���ҳ��ڱ����λ��
Carptr dequeue(Queue &q);                                           //������ĵ�һ�������������ظý��
void In(CarPark &p, Queue &q, int time, int carnum);                //�����ͣ�����ĺ���
void Out(CarPark &p, TemPark &tp, Queue &q, int carnum, int time);  //�����ͣ�����ĺ���


int main()
{
    int n = 0;
    printf("����n��ֵ:");
    scanf("%d", &n);

    //��ʼ��ͣ���������
    CarPark p;
    TemPark tp;
    InitCarPark(p, tp, n);
    Queue q;
    InitQueue(q);

    //��ʼ����
    printf("������ͣ������Ӫ����,����ʱ��˳��,һ������һ��,����� E 0 0 ��β ���� A 1 5\n");
    char a;
    int carnum, time;
    while(1){
        scanf("%c %d %d", &a, &carnum, &time);
        switch (a)
        {
        case 'A':
            In(p,q,time,carnum);                    //����ͣ����
            break;
        case 'D':                                   //����������ݶ�Ϊ��ͣ�����ڵ�����
            Out(p, tp, q, carnum, time);            //�뿪ͣ����
            break;
        case 'E':
            printf("��лʹ�ã�\n");
            return 0;       //�˳�����
            break;
        default:
            break;
        }
    }    
}


void InitCarPark(CarPark &p, TemPark &tp, int n){                       //��ʼ������ͣ����
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

void InitQueue(Queue &q){                                               //��ʼ�����
    q.front = q.rear = (Carptr)malloc(sizeof(Car));
    if(!q.front)
        exit(OVERFLOW);
    q.front->next = NULL;
}

void push(CarPark &p, Carptr &c){                                       //ͣ��������ջ����
    if(p.top-p.base>p.n)
        exit(OVERFLOW);
    *p.top++ = *c;
}

void tempush(TemPark &tp, Carptr &c){                                   //��ʱͣ��������ջ����
    if(tp.top-tp.base>tp.n)
        exit(OVERFLOW);
    *tp.top++ = *c;
}

void enqueue(Queue &q, Carptr &c){                                      //����
    c->next = NULL;
    q.rear->next = c;
    q.rear = c;
}

int searchparknum(CarPark &p, Carptr &c){                               //���ҳ���ͣ������λ��
    Carptr search = p.base;
    int i = 1;
    while(search->carnum != c->carnum){
        i++;
        search++;    //�����洢��ָ�����ֱ��++     ע������һ��������search�ӷ����𣡣�
    }
    return i;
}

int searchqueuenum(Queue &q, Carptr &c){                                //���ҳ��ڱ����λ��
    Carptr search = q.front->next;
    int i = 1;
    while(search->carnum != c->carnum){
        i++;
        search=search->next;    //��ʽ�洢��ָ��Ӧ�ñ��next��ָ�룡
    }
    return i;
}

Carptr dequeue(Queue &q){                                               //������ĵ�һ�������������ظý��
    if(q.front == q.rear)
        exit(OVERFLOW);
    else{
        Carptr p = q.front->next;
        Carptr m = p->next;
        q.front->next = m;
        if(q.rear == p)         //����������������������һ��Ԫ��
            q.rear = q.front;
        return p;               //���ر���ĵ�һ����
    }
}

void In(CarPark &p, Queue &q, int time, int carnum){                    //�����ͣ�����ĺ���
    if(p.top-p.base<p.n){    //ͣ����δ��   ��߲���ȡ�Ⱥţ�
        Carptr c = (Carptr)malloc(sizeof(Car));
        if(!c)
            exit(OVERFLOW);
        c->arivtime = time;
        c->carnum = carnum;
        push(p, c);           //��ͣ����
        printf("���ƺ�Ϊ%d�ĳ�����ͣ������λ��Ϊ��%d��;\n", carnum, searchparknum(p, c));
    } 
    else{                     //ͣ�������������������У�
        Carptr c = (Carptr)malloc(sizeof(Car));
        if(!c)
            exit(OVERFLOW);
        c->carnum = carnum;
        c->arivtime = time;     //ע�����Ҫ����
        enqueue(q, c);
        printf("ͣ�������������ƺ�Ϊ%d�ĳ���������λ��Ϊ��%d��;\n", carnum, searchqueuenum(q, c));
    }
}

void Out(CarPark &p, TemPark &tp, Queue &q, int carnum, int time){      //�����ͣ�����ĺ���
    //��������ջ���뵽��ʱջ��ֱ���ҵ��ó�
    Carptr search = p.top - 1;  //��top-1��ʼ��
    while(search->carnum != carnum){
        tempush(tp, search);    //���ó���ʱ������ʱͣ����
        search--;               
        p.top--;                //�ó���ջ
    }
    //��ʱsearchָ���ҵ���������
    printf("���ƺ�Ϊ%d�ĳ��뿪ͣ����������ͣ��ʱ��Ϊ%d���շ�Ϊ%d\n", carnum, time - search->arivtime, fee * (time - search->arivtime));
    //��������ͣ����
    p.top--;
    //��ʱͣ�����ĳ�����ͣ����
    search = tp.top - 1;
    while(tp.top > tp.base){
        push(p, search);        //����ͣ����
        search--;
        tp.top--;
    }
    //��ʱͣ������ȫ�����أ����洦�����ĳ���
    if(q.front==q.rear)             //�����û�г���
        return;
    else{                           //������г�����ô��һ������ͣ����
        Carptr c = dequeue(q);      //���ܷ��صĳ���
        c->arivtime = time;         //���½���ͣ������ʱ��
        push(p, c);                 //����ͣ����
    }
}
