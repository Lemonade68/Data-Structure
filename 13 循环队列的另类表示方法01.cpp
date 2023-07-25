// ���轫ѭ�����ж���Ϊ���������rear��length�ֱ�ָʾѭ������
// �ж�βԪ�ص�λ�ú��ں���Ԫ�ظ������Ը�����ѭ�����еĶ���������
// д����Ӧ������кͳ������㷨���������㷨Ӧ���ض�ͷԪ�أ�

// ������ע�ⳤ��Ϊ0���������front+length����rear+length��ͬ����

//ע�������rearָ��ľ��Ƕ�β��Ԫ�أ����Ƕ�βԪ�صĺ�һ��

#define ElemType int
#define MAXSIZE 100
#define OVERFLOW -2

typedef struct queue{
    ElemType *base;
    int rear;
    int length;
}Queue;

bool QueueisFull(Queue &q){
    if(q.length >= MAXSIZE)
        return true;
    else
        return false;
}

void EnQueue(Queue &q, int e){
    if(QueueisFull)
        exit(OVERFLOW);
    q.base[q.rear] = e;
    q.rear = (q.rear + 1) % MAXSIZE;
    q.length++;
}

int DeQueue(Queue &q, int e){
    if(q.length == 0)
        exit(OVERFLOW);
    int front = (q.rear - q.length + 1 + MAXSIZE) % MAXSIZE;        //û���⣡  ����Ϊ��ʱ������    ע�����֪��ͷָ��Ĳ�𣡣�
    e = q.base[front];
    q.length--;
    return e;
}


