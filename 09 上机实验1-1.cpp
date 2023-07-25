// ʵ�ֵ�����Ĳ��롢ɾ���ͱ������㣬ÿ�ֲ�����һ������ʵ�֡�
// �����������һ����Ԫ�ز������ָ����ŵ�λ�á�
// ɾ����������ָ����ŵ�Ԫ�شӱ���ɾ����
// �����������ӱ�ͷ�������������Ԫ�ص�ֵ�����ǿձ��������Ϣ��empty list!����

#include<stdio.h>
#include<stdlib.h>

#define OVERFLOW -2

typedef struct Node{
    int data;
    struct Node *next;
} LNode, *LinkList;

//����������
int CreateList(LinkList LHead){
    int s = 0, n = 0;    //n���ڷ�������Ԫ�ظ���
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

void InsertList(LinkList LHead, int i, int e){ // iΪָ�����
    LinkList p = LHead;
    int j = 0;    //������
    while(p && j<i-1){    //�ҵ���i-1�����
        p = p->next; 
        j++;
    }
    if(!p || j>i-1){      //��Ӧi>n��i<=0�������
        printf("i��ֵ����\n");
        return;
    }
    else{
        LinkList q = (LinkList)malloc(sizeof(LNode));
        if(!q)
            exit(OVERFLOW);
        q->data = e;
        q->next = p->next;
        p->next = q;
    }
}

void DeleteList(LinkList LHead,int i){
    LinkList p = LHead;
    int j = 0;
    while(p && j<i-1){    //�ҵ���i-1�����
    p = p->next; 
    j++;
    }
    if(!p || j>i-1){      //��Ӧi>n��i<=0�������
        printf("i��ֵ����\n");
        return;
    }
    else{
        LinkList q = p->next;
        p->next = q->next;
        free(q);
    }
}

int main()
{
    LinkList LHead = (LinkList)malloc(sizeof(LNode));
    if(!LHead)
        exit(OVERFLOW);
    LHead->next = NULL;
    int n = CreateList(LHead);   //�ܽ�����
    PrintList(LHead);
    while(n>=0){
        DeleteList(LHead, 1);
        PrintList(LHead);
    }
    return 0;
}