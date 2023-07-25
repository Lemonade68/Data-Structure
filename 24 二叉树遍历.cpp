#include<iostream>
using namespace std;

// ������ұ����㷨��
// ���� preorder  ���� inorder  ���� postorder
typedef struct BiTNode{
    int data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
} BiTNode, *BiTree;

typedef struct Stack{
    BiTree *top;
    BiTree *base;
    int *stacksize;
} Stack;

typedef struct Queue{
    BiTree *data;
    int front;
    int rear;
} Queue;

typedef struct SqBTree{
    int *elem;
    int last = 0;
}SqBTree;

void pop(Stack S, BiTree p){}
void push(Stack S, BiTree p){}
void InitStack(Stack S){}
bool StackEmpty(Stack S){}
void InitQueue(Queue q){}
void EnQueue(Queue q, BiTree p){}
void DeQueue(Queue q, BiTree p){}
void InitBiTree(BiTree T){}

// �ݹ��㷨��

// ��������㷨�ĵݹ�����
void Preorder(BiTree root){
    if(root){
        cout << root->data;             //���ʽ��
        Preorder(root->lchild);         //����������
        Preorder(root->rchild);         //����������
    }
}

// �������
void Inorder(BiTree root){
    if(root){
        Preorder(root->lchild);         //����������
        cout << root->data;             //���ʽ��
        Preorder(root->rchild);         //����������
    }
}

// �������
void Postorder(BiTree root){
    if(root){
        Preorder(root->lchild);         //����������
        Preorder(root->rchild);         //����������
        cout << root->data;             //���ʽ��
    }
}


//  �������     ----�ö���
//  �Ӹ��ڵ㿪ʼ��ӣ�ÿ�ΰ�ÿ�еĽ��ȫ����Ӻ����γ��ӣ�ÿ��һ�������ӽڵ㰴����˳�����
void LayerOrder(BiTree T){
    InitQueue(Q);
    EnQueue(Q,T);       //���ڵ����
    while(!QueueEmpty(Q)){
        DeQueue(Q, p);
        visit(p);
        if(p->lchild)
            EnQueue(Q, p->lchild);
        if(p->rchild)
            EnQueue(Q, p->rchild);
    }
}

// ��ϰ�⣨��һ���ԣ�
// ��˳���sa��ʾһ����ȫ��������sa.elem[sa.last]�д�����и���������Ԫ�أ��Ա�д�㷨�ɴ�˳��洢�ṹ�����ö������Ķ�������
void CrtBiTree(SqBTree sa, Queue q, BiTree &T){
    InitQueue(q);
    if(!(T = (BiTree)malloc(sizeof(BiTNode))))
        exit(OVERFLOW);
    T->data = sa.elem[sa.last++];
    EnQueue(q, T);                                              //����������
    BiTree p;
    while(sa.elem[sa.last]){                                    //��˳����л�������û�б�ʹ��ʱ
        DeQueue(q, p);                                          //��ͷԪ�س����У����濴�ܷ��������ӷ������
        p->lchild = (BiTree)malloc(sizeof(BiTNode));            
        InitBiTree(p->lchild);                                  //��ʼ������������������һ��ʼΪnull
        p->lchild->data = sa.elem[sa.last++];
        EnQueue(q, p->lchild);
        
        if(sa.elem[sa.last]){
            p->rchild = (BiTree)malloc(sizeof(BiTNode));
            InitBiTree(p->rchild);
            p->rchild->data = sa.elem[sa.last++];
            EnQueue(q, p->rchild);
        }
    }
}



// �ǵݹ��㷨��(��ջʵ��)

// ˼·��  ��һֱ����ߵ�������ջ��ֱ��������������Ȼ��ÿ�γ�ջ��˵��ջ������������ʱ����ջ���
// ��������ջ���ظ�����

// ����
// �Լ�д��   ������ռ��   ������������в�ͨ��ÿ�γ�ջ�����ջһ��Ҫ��֤���ܰ��Լ��ٸ��ȥ  ��Ȼ��ѭ���˲�����
void PreOrder(BiTree T, Stack &S){
    InitStack(S);
    BiTree p = T;
    Push(S, p);                                     //�������ջ
    while(p || !StackEmpty(S)){
        Pop(S, p);                                  //ջ��Ԫ�س�ջ
        cout << p->data;
        if(p->rchild) Push(S, p->rchild);           //����������ջ  
        if(p->lchild) Push(S, p->lchild);           //����������ջ����֤������������
    }
}

// �������Ӧ��д����
void preOrder(BiTree T, Stack &S){
    InitStack(S);
    BiTree p = T;
    while(p || !StackEmpty(S)){
        if(p){
            cout << p->data;
            push(S,p);
            p = p->lchild;
        }
        else{
            pop(S, p);
            p = p->rchild;
        }
    }
}

// ����
void InOrderTraverse(BiTree T){
    InitStack(S);               //����ջ
    push(S, T);
    while(!StackEmpty(S)){
        while(GetTop(S,t) && t)     //  ѧϰ��ߵ�д����ִ��ǰһ��  ��������ִ�к�һ��
            push(S, t->lchild);     //  ���ҵ������µĽ��
        pop(S, t);                  //  ���Ŀ�ָ����ջ
        if(!StackEmpty(S)){         //    ע�⣡������ÿ��popǰһ��Ҫ�ж�ջ�Ƿ�Ϊ�գ���
            pop(S, t);              //  ��ȡҶ�ӽ��/��������ϵ�ֵ������������У�
            push(S, t->rchild);     //  �ý����ҽ����ջ
        }
    }
}


// �Ľ���
void InOrder(BiTNode *root){
    InitStack(S);
    p = root;
    while(p || !StackEmpty(S)){
        if(p){
            push(S, p);
            p = p->lchild;
        }
        else{
            pop(S, p);              //��ָ����ջ
            cout << p->data;        //���ʸ����
            p = p->rchild;          //����������
        }
    }
}