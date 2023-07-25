//һԪ����ʽ��ӡ���������

//�ռ����ò��ڼ��

#include<stdio.h>
#include<stdlib.h>

#define OVERFLOW -2

typedef struct Node{
    float xishu;
    int zhishu;
    struct Node *next;
} LNode, *LinkList;

void CreateList(LinkList &Head){
    int n = 0;
    LinkList tail = Head;       
    // LinkList pre = tail;    //����Ҫ�õ�pre��ֱ����tail�Ƚϼ���
    printf("���������ʽ������\n");
    scanf("%d", &n);
    if(n==0)
        return;
    printf("��ֱ�����ÿһ���Ӧ��ϵ����ָ�� �ÿո�ָ�\n");
    for(int i = 0; i < n; i++){
        LinkList p = (LinkList)malloc(sizeof(LNode));
        if(!p)
            exit(OVERFLOW);
        
        if(i==0){
            scanf("%f %d", &p->xishu, &p->zhishu);
            tail->next = p;
            tail = p;
        }
        else{               //���ڼ�������ǰһ�����һ��ָ���Ƿ�һ�£���һ������Ҫ�ϲ�
            scanf("%f %d", &p->xishu, &p->zhishu);
            if(p->zhishu == tail->zhishu){
                tail->xishu += p->xishu;
                free(p);
            }
            else{           //��һ�������
                tail->next = p;
                tail = p;
                // pre = pre->next;
            }
        }
            
    }
        tail->next = NULL;             //��ֹ��������NULL
}

void Sumlist(LinkList &AHead, LinkList &BHead, LinkList &CHead){
    LinkList pa = AHead->next;
    LinkList pb = BHead->next;
    LinkList q = CHead;
    while(pa && pb){
        if(pa->zhishu < pb->zhishu){
            q->next = pa;
            q = pa;
            pa = pa->next;
        }
        else if(pa->zhishu > pb->zhishu){
            q->next = pb;
            q = pb;
            pb = pb->next;
        }
        else{
            if(pa->xishu == -pb->xishu){  //���Ϊ0��ֱ�Ӳ��Ž�c����
                pa = pa->next;
                pb = pb->next;
            }
            else{
                pa->xishu += pb->xishu;
                q->next = pa;
                q = pa;
                pa = pa->next;
                pb = pb->next;
            }
        }
        // q->next = NULL;       
    }
    if(pa)
        q->next = pa;
    else if(pb)
        q->next = pb;
    else
        return;
}

void Deletelist(LinkList &AHead, LinkList &BHead, LinkList &DHead){   
    //��������˼�룺��b��ϵ��ȫ�������෴����Ȼ��ʹ�üӷ�����
    LinkList m = BHead->next;
    while(m){                   //ϵ����Ϊ�෴������
        m->xishu = -m->xishu;
        m = m->next;
    }
    Sumlist(AHead, BHead, DHead);
}

void Print(LinkList &Head){
    LinkList p = Head->next;
    if(p==NULL){
        printf("0\n");
        return;
    }

    //�ж�˼·�����ȵ�һ��Ҫ�����ó�������Ϊϵ��Ϊ��ʱǰ��û�мӺ�
    //���ж�ָ����ָ��Ϊ��ʱ������ʲô�������ֻдϵ����ϵ��Ϊ0û�������
    //���ж�ϵ����ָ��ͬʱΪ1->ָ��Ϊ1->ϵ��Ϊ1->һ�����

    while(p){
        if(p==Head->next){
            if(p->xishu > 0){
                if(p->zhishu==0)                //���ж�ָ���Ƿ�Ϊ0����Ȼ�����x^0֮������
                    printf("%.1f", p->xishu);
                else if(p->xishu==1 && p->zhishu==1)    //Ҫ����һ������Ȼ����x^1����1*x
                    printf("x");
                else if(p->xishu==1)
                    printf("x^%d", p->zhishu);
                else if(p->zhishu==1)
                    printf("%.1f*x", p->xishu);
                else
                    printf("%.1f*x^%d", p->xishu, p->zhishu);
            }
            else{
                if(p->zhishu==0)
                    printf("%.1f", p->xishu);
                if(p->xishu==-1)
                    printf("-x^%d", p->zhishu);
                else
                    printf("%.1f*x^%d", p->xishu, p->zhishu);
            }
        }
        else{
            if(p->xishu>0){
                if(p->zhishu==0)
                    printf("+%.1f", p->xishu);
                else if(p->xishu==1 && p->zhishu==1)
                    printf("+x");
                else if(p->xishu==1)
                    printf("+x^%d", p->zhishu);
                else if(p->zhishu==1)
                    printf("+%.1f*x", p->xishu);
                else
                    printf("+%.1f*x^%d", p->xishu, p->zhishu);
            }
            if(p->xishu<0){
                if(p->zhishu==0)
                    printf("%.1f", p->xishu);
                else if(p->xishu==-1 && p->zhishu==1)
                    printf("-x");
                else if(p->xishu==-1)
                    printf("-x^%d", p->zhishu);
                else
                    printf("%.1f*x^%d", p->xishu, p->zhishu);
            }
        }
        p = p->next;
    }
    printf("\n");
}


int main()
{
    //����A B �� �� ͷָ��
    LinkList AHead = (LinkList)malloc(sizeof(LNode));
    if(!AHead)
        exit(OVERFLOW);
    LinkList BHead = (LinkList)malloc(sizeof(LNode));
    if(!BHead)
        exit(OVERFLOW);
    LinkList CHead = (LinkList)malloc(sizeof(LNode));
    if(!CHead)
        exit(OVERFLOW);
    LinkList DHead = (LinkList)malloc(sizeof(LNode));
    if(!DHead)
        exit(OVERFLOW);

    //��ʼ��ͷ��㣬��A��BΪ����Ҳ������������
    AHead->next = NULL;
    BHead->next = NULL;
    CHead->next = NULL;
    DHead->next = NULL;

    //������������ʽ����
    CreateList(AHead);
    CreateList(BHead);
    FLAG:
    printf("����c ����ӣ�����d �����\n");
    char c;
    scanf("\n");        //���س�
    scanf("%c", &c);
    if(c!='c' && c!='d'){       //��߲�������""
        printf("��������ȷ����ĸ\n");
        goto FLAG;
    }

    //�������:
    else if(c=='c'){
        Sumlist(AHead, BHead, CHead);
        Print(CHead);
    }
    //�������:
    else{
        Deletelist(AHead, BHead, DHead);
        Print(DHead);
    }
    //�������:
    return 0;
}



//ע��㣺���ϵ��Ϊ+-1,ָ��Ϊ0��1,���������Ƿ����ָ����ͬ��,�ձ�����