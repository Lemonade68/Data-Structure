#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -2

// LT��less than С��
// LE��less than or equal to С�ڵ���
// EQ��equal to ����
// NE��not equal to ������
// GE��greater than or equal to ���ڵ���
// GT��greater than ����


// ��̬���ұ�  ���ڸ���key�������ҳɹ��򷵻أ��������ؼ���key

// 1.����������      �ֽж�����������
// ���ʣ����������գ��������������н��ֵС�ڸ����ֵ�����������ڣ������������Ƕ���������
// ͨ����ȡ����������Ϊ�����������Ĵ洢�ṹ

// ***********************************************
// �Զ�����������������������õ���һ���Ǵ�С�������������
// ����������������õ��������еģ�һ���Ƕ���������

typedef struct BiTNode{
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;


// �����㷨��
BiTree SearchBST(BiTree T, int key){
    if(!T)
        return NULL;
    else{
        if(T->data == key)
            return T;
        else if(T->data > key)
            return SearchBST(T->lchild, key);
        else
            return SearchBST(T->rchild, key);
    }
}


// �����㷨��
// �ڲ��Ҳ��ɹ�ʱ����;     ����:�����µĸ����;��������µ�Ҷ�ӽ��

// ���ȸĽ������㷨, ʹ���Ҳ��ɹ�ʱҲ�ܷ���λ��
// ���ҳɹ�: pָ��ý���ҷ���true
// ����ʧ��: pָ�����·���ϵ����һ����㷵��false
// fָ��T��˫�ף���ʼֵΪNULL
bool SearchBST_s(BiTree T, int key, BiTree f, BiTree &p){       //p��ֵÿ�ε�����Ҫͬ���ı䣬������ã�������
    if(!T){
        p = f;              //��߼ȿ��Ա�ʾ����ʧ�ܵĸ���㣬Ҳ���Ա�ʾһ��ʼT���ǿ��������
        return false;
    }
    else{
        if(T->data == key){
            p = T;
            return true;
        }
        else if(T->data > key)
            return SearchBST_s(T->lchild, key, T, p);
        else
            return SearchBST_s(T->rchild, key, T, p);
    }
}

bool InsertBST(BiTree &T, int e){       //������eʱ  ���벢����true;  ����eʱ  ����false
    BiTree p;
    if(!SearchBST_s(T, e, NULL, p)){
        BiTree s = (BiTree)malloc(sizeof(BiTNode));
        if(!s)
            exit(OVERFLOW);
        s->data = e;
        s->lchild = NULL;
        s->rchild = NULL;
        if(!p)                  //���������    ע�⣡����������������
            T = s;
        else if(p->data > e)
            p->lchild = s;
        else
            p->rchild = s;
        return true;
    }
    else
        return false;
}


// ɾ���㷨��
// ���1����ɾ������Ҷ��                             ˫�׽���Ӧָ�����Ϊ��
// ���2����ɾ���Ľ��ֻ����������������                ˫�׽���Ӧָ����ָ��ɾ���Ľ�����������������     
// ���3����ɾ���Ľ�����������Ҳ��������              ����ǰ������֮���������������²��ҵ�С�ڸý��������---������Ӱ���������˳�򣩣�Ȼ����ɾ����ǰ����㣨�ݹ飩   


// ************ ����������������ʱdelete��ǰ����������У������search���p��λ������    ���ϻ�ʵ��5-2  **************

bool Delete(BiTree &p){
    if(!p->rchild){             //�������գ���ֻ���ؽ�����������    ������ɾ��Ҷ�ӽ������
        BiTree q = p;
        p = p->lchild;          //**  ����   ��������Բ�ͨ��˫��ֱ������������
        free(q);
    }
    else if(!p->lchild){
        BiTree q = p;
        p = p->rchild;
        free(q);
    }
    else{                       //���Ҷ��к��ӽ������
        BiTree q = p, s = p->lchild;
        while(s->rchild){       //Ѱ��ǰ��(���ӵ������ӽڵ�)----Ҳ��֤��s����û���Һ��ӣ�����sΪq���Һ���    
            q = s;              //qʼ��ָ��s��˫�׽��
            s = s->rchild;
        }
        p->data = s->data;      //ǰ�������ݸ��Ƶ�p���
        if(q != p)              //ע�������������----q!=pʱ��s��ӵ�q����
            q->rchild = s->lchild;      //�ؽ�q����������
        else                    //ע�������������----q==pʱ��s��ӵ�q����q��ʱ����p��
            q->lchild = s->lchild;
        free(s);                //����ǰ�����ɾ��
    }
    return true;                //ȷ��ɾ��  ֻ��Ҫ����true����
}   

bool DeleteBST(BiTree &T, int key){
    //������key�ؼ��ֵ�Ԫ�أ�ɾ��������true   ���򷵻�false
    if(!T)
        return false;
    else{
        if(T->data == key)
            return Delete(T);
        else if(T->data > key)
            return DeleteBST(T->lchild, key);
        else
            return DeleteBST(T->rchild, key);
    }
}


// ASL:�ֳɹ���ʧ���������
// �ɹ���������
// ʧ�ܣ�ʧ������ĸ����ĸ߶�֮��/n+1(��ʧ���������)
