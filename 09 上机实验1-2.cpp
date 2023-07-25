// �ֱ��庯��ʵ�ִ������������������������������̡�
// ��������ʱ��������main�����е��ô���������ĺ�����Ȼ����ñ���������
// ��������Ԫ�ص�������ĺ������ٵ���������������ٵ��ñ���������
// ��������Ԫ�ص�������ĺ����۲��Ƿ�ʵ�����������㡣

#include<stdio.h>
#include<stdlib.h>

#define OVERFLOW -2

typedef struct Node{
    int data;
    struct Node *next;
} LNode, *LinkList;

//��������������ʵ��1��ͬ��ֱ������0ֹͣ¼��
int CreateList(LinkList LHead){
    int s = 0, n = 0;
    while(true){
        scanf("%d", &s);
        if(s==0)        //����Ϊ0��ֹͣ����
            break;
        else{
            LinkList p = (LinkList)malloc(sizeof(LNode));
            if(!p)
                exit(OVERFLOW);
            p->data = s;
            p->next = LHead->next;
            LHead->next = p;
            n++;
        }
    }
    return n;
}

//���������������
void PrintList(LinkList LHead){
    if(LHead->next==NULL){            //��ʼʱ�жϣ�����Ϊ0������ձ�����
        printf("Empty list!\n");  
        return;
    }
    LinkList p = LHead->next;
    while(p!=NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

//����������
void SortList(LinkList LHead,int n){
    LinkList p = LHead->next;
    int m = 0; //�����м�ת��
    for (int i = 0; i < n;i++){
        p = LHead->next;
        for (int j = 0; j < n - i - 1; j++){
            if(p->data <= p->next->data){
                m = p->data;
                p->data = p->next->data;
                p->next->data = m;
                p = p->next;
            }
            else
                p = p->next;        //ע�����ҲҪд
        }
    }
}

int main()
{
    LinkList LHead = (LinkList)malloc(sizeof(LNode));
    if(!LHead)
        exit(OVERFLOW);
    LHead->next = NULL;
    int n = CreateList(LHead);      //���������õ�����
    PrintList(LHead);       //�������������
    SortList(LHead, n);     //ð����������
    PrintList(LHead);       //�������������
    return 0;
}