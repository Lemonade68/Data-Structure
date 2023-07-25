// 假设将循环队列定义为：以域变量front和length分别指示循环队列
// 中队头元素的位置和内含的元素个数，试给出此循环队列的队满条件，
// 写出相应的入队列和出队列算法（出队列算法应返回队头元素）

// 此类题注意长度为0的情况（用front+length和用rear+length不同！）


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
        int rear = (Q->Front + Q->Count) % Q->MaxSize;      //count一开始为0  因此一开始在Q->Front上写数据   其实给了头指针比给尾指针简单
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

