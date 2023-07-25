// ���轫ѭ�����ж���Ϊ���������front��length�ֱ�ָʾѭ������
// �ж�ͷԪ�ص�λ�ú��ں���Ԫ�ظ������Ը�����ѭ�����еĶ���������
// д����Ӧ������кͳ������㷨���������㷨Ӧ���ض�ͷԪ�أ�

// ������ע�ⳤ��Ϊ0���������front+length����rear+length��ͬ����


#define ElementType int

typedef struct queue{
    ElementType *base;
    int rear;
    int length;
}Queue;

bool AddQ( Queue Q, ElementType X ){
    if(Q->Count == Q->MaxSize){
        printf("Queue Full\n");
        return false;
    }
        int rear = (Q->Front + Q->Count) % Q->MaxSize;      //countһ��ʼΪ0  ���һ��ʼ��Q->Front��д����   ��ʵ����ͷָ��ȸ�βָ���
        Q->Data[rear] = X;
        Q->Count++;
}

ElementType DeleteQ( Queue Q ){
    if(Q->Count == 0){
        printf("Queue Empty\n");
        return ERROR;
    }
    int x = Q->Data[Q->Front];
    Q->Front = (Q->Front + 1) % Q->MaxSize;
    Q->Count--;
    return x;
}

