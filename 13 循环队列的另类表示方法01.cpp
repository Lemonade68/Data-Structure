// 假设将循环队列定义为：以域变量rear和length分别指示循环队列
// 中队尾元素的位置和内含的元素个数，试给出此循环队列的队满条件，
// 写出相应的入队列和出队列算法（出队列算法应返回队头元素）

// 此类题注意长度为0的情况（用front+length和用rear+length不同！）

//注意这里的rear指向的就是队尾的元素，而非队尾元素的后一个

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
    int front = (q.rear - q.length + 1 + MAXSIZE) % MAXSIZE;        //没问题！  长度为零时返回了    注意和已知队头指针的差别！！
    e = q.base[front];
    q.length--;
    return e;
}


