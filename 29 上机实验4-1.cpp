// �ڶ������Ķ�������洢�ṹ�����ϣ�ʵ�ֶ��������������㣺
// ��1�������������Ķ����������ʾ��
// ��2��ʵ�ֶ�����������������㣬�������������У�
// ��3��ʵ�ֶ�����������������㣬�������������У�
// ��4��ʵ�ֶ������ĺ���������㣬�������������С�

#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -2

typedef struct BiTNode{
    char data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

void CrtBT(BiTree &T){
    char ch;
    scanf("%c", &ch);
    if(ch == '.')
        T = NULL;
    else{
        if(!(T=(BiTree)malloc(sizeof(BiTNode))))
            exit(OVERFLOW);
        T->data = ch;
        CrtBT(T->lchild);
        CrtBT(T->rchild);
    }
}

void PreOrder(BiTree T){
    if(T){
        printf("%c", T->data);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void InOrder(BiTree T){
    if(T){
        InOrder(T->lchild);
        printf("%c", T->data);
        InOrder(T->rchild);
    }
}

void PostOrder(BiTree T){
    if(T){
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        printf("%c", T->data);
    }
}

int main(){
    BiTree T;
    printf("�����봴�������������У�\n");
    CrtBT(T);
    printf("�����������Ϊ��\n");
    PreOrder(T);
    printf("\n");
    printf("�����������Ϊ��\n");
    InOrder(T);
    printf("\n");
    printf("�����������Ϊ��\n");
    PostOrder(T);
    printf("\n");
    return 0;
}
