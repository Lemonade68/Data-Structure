#define OVERFLOW -2
#include<stdlib.h>

// ����ĳ�������У�ָ����ǰ���ͺ�̵�ָ�룬��Ϊ����
// ����������Ĺ涨��
// �ڶ�������������������־��

// 1.���ý�����������գ�lchild��ָ��ָ���������������־���ֵΪ��ָ�� Link��
// ����lchild���ָ��ָ����ǰ�������־���ֵΪ������ Thread��

// 2.���ý�����������գ�rchlid��ָ��ָ�������������ұ�־���ֵΪ��ָ�� Link��
// ����rchild���ָ��ָ�����̣��ұ�־���ֵΪ������ Thread��

// һ����������
typedef enum{Link, Thread} PointerThr;  //enum ö�ٶ��壬Link=0,Thread=1
typedef struct BiThrNode{
    int data;
    struct BiThrNode *lchild, *rchild;
    PointerThr LTag, RTag;
} BiThrNode, *BiThrTree;

// Ltag=0 -- lchildָ�����������ڵ�    Ltag=1 -- lchildָ��ǰ�����
// Rtag=0 -- rchildָ�����������ڵ�    Rtag=1 -- rchildָ���̽��


// �������Һ�̣�

// ���������������ϣ�����p��ָ���ĺ�̷����������
// p->Rtag = 1:  ����  p->rchildָ�����̽��
// p->rtag = 0: ���Һ��ӽ��   p���������������µĽ�㼴Ϊ����       �������������£���������������������ָ���������ң�ֱ���ҵ�һ��û�����ӵĽ��Ϊֹ

// �������ָ������̳���
BiThrTree inordernext(BiThrTree p){
    if(p->RTag == 1)
        return p->rchild;
    else{
        BiThrTree q = p->rchild;
        while(q->LTag == 0)             //ע����߲���q->lchild��������    q->lchildһֱ��ֵ
            q = q->lchild;
        return q;
    }
}

// �������ָ������̳���
BiThrTree postordernext(BiThrTree p, BiThrTree T){
    if(p->RTag == 1)
        return p->rchild;
    else{
        BiThrTree f;
        // ����p��ָ���ĸ��ڵ�f, ע����ߵĳ���ʡ���˲��ҹ���
        if(p == f->rchild)                      //p�Ǹ��ڵ���Һ��ӣ��򸸽ڵ�Ϊ����
            return f;
        if(p == f->lchild && f->RTag == 1)      //p�Ǹ��ڵ�����Ӳ��Ҹ��ڵ�û���Һ��ӣ����ڵ�Ϊ����
            return f;
        BiThrTree q = f->rchild;                //p�Ǹ��ڵ�����Ӳ��������ֵܵ����
        
        // **********************************    ��һ���ú�ѧϰ��
        while(q->LTag == 0 || q->RTag == 0){
            if(q->LTag == 0)                    //�����ж���ߣ�������߾������
                q = q->lchild;
            else
                q = q->rchild;
        }
        //��ʱqΪf�������Ϻ��������ĵ�һ�����(Ҷ�ӽ��)
        return q;
    }
}

BiThrTree Succ(BiThrTree p){}       //���Һ��



// ������������ı����㷨��
// for (BiThrTree p = firstNode(T); p;p=Succ(p))
    // visit(p);


// �ġ�������������
// ע�⸽��ָ��pre,��ʼ�ձ���ָ��preָ��ǰ���ʵ�p��ָ����ǰ��

// ��һ�ö���������������(��������˼·)

// ���⣺pre��ô�ں�����������ʹ�ã�            ���ɣ���

void InThreading(BiThrTree &p){
    if(p){
        InThreading(p->lchild);             //������������
        if(!p->lchild){                     //������Ϊ��
            p->LTag = Thread;
            p->lchild = pre;                //pre��ǰ��ָ��
        }
        if(!pre->rchild){
            pre->RTag = Thread;
            pre->rchild = p;
        }
        pre = p;                            //��֤preָ��p��ǰ����(Ϊ��һ��)
        InThreading(p->rchild);             //������������
    }
}

void InOrderThreading(BiThrTree &Thrt, BiThrTree T){
    // �������������T��������������������Thrtָ��ͷ���
    if(!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode))))
        exit(OVERFLOW);
    Thrt->LTag = Link;          //��ͷ���
    Thrt->RTag = Thread;        
    Thrt->rchild = Thrt;        //��ָ���ָ
    if(!T)                      //��������Ϊ�գ�����ָ���ָ
        Thrt->lchild = Thrt;
    else{
        Thrt->lchild = T;
        BiThrTree pre = Thrt;
        InThreading(T);         //���������������������
        pre->rchild = Thrt;     //���һ�����������
        pre->RTag = Thread;
        Thrt->rchild = pre;
    }
}



// �����������������������У���ָ����ĸ���Ϊ1        �� ���� �Һ��� NULL       NULL ���� �Һ��� �� 
// �����������������У���ָ����ĸ���Ϊ2    NULL ���� �� �Һ��� NULL

// ֻ����ԭָ����Ϊ��ʱ������Ҫָ������     ˼����   ������ͼ
