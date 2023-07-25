// ��Ŀ�� Լɪ������

// ������������
// ���Ϊ1,2,...,n��n���˰�˳ʱ�뷽��Χ��һȦ��
// ÿ�˳���һ�����루�������������ڸ���һ�������m>0���ӱ��Ϊ1���˿�ʼ��
// ��˳ʱ�뷽��1��ʼ˳����������mʱֹͣ����m���˳�Ȧ��ͬʱ��������������Ϊ�µ�mֵ��
// ������˳ʱ�뷽���ϵ���һ���˿�ʼ�����´�1��ʼ�����������ȥ��ֱ�����е���ȫ������Ϊֹ��

// ������Ҫ��
// ���õ���ѭ������洢�ṹģ��˹��̣����ճ��е�˳���ӡ���ÿ���˵ı�š�

// ���������ݡ�
// M�ĳ�ʼֵΪ20��n����7��7���˵���������Ϊ��3��1��7��2��4��8��4��
// ���Ϊ��6��1��4��7��2��3��5

// ��ʵ����ʾ��
// ��������ʱ������Ҫ���û�ָ����ʼ��������ֵ��Ȼ���ȡ���˵����롣����n��30��
// �������õ�ѭ�������в���Ҫ��ͷ��㡱����ע��ձ�ͷǿձ�Ľ��ޡ�


//����ѧϰ���ĵ㣺  ������ָ��ʱ�����Ҫ��ָ�뱾������޸ģ�����Ҫʹ��ָ���ָ�룡��   ����   ָ�������
#include<stdio.h>
#include<stdlib.h>

#define OVERFLOW -2

typedef struct Node{
    int code;
    int number;
    struct Node *next;
} LNode, *LinkList;


//������ѭ������Ҳ���������·�����
    // һ��ʼ���յ�����������֮��������nextָ��ͷ��


//��ѭ������Ĵ���(û��ͷ���İ汾)
// ******* ���Ҫ����һ���Ƕ�Rear�����ã�����  ��Ϊ֮��Ҫ��Rear���ָ�뱾�������ı䣬�൱��ָ���ָ��

void CreateList(LinkList &Rear,int n){                    
    printf("��������Ϊ1��n���˶�Ӧ������ �Կո�ָ�\n");
    LinkList Head = (LinkList)malloc(sizeof(Node));      //��ߴ���ʱҪ�ø�����¼��һ��λ�ã�֮��free��
    Head->next = Rear;          //����һ���ս�㣬���ɾ��
    for (int i = 0; i < n; i++){
        if(i==0){                   //ע��һ��ʼ�Ĵ���û��ͷ���
            scanf("%d", &Rear->code);
            Rear->number = 1;
        }
        else{
            LinkList p = (LinkList)malloc(sizeof(Node));
            if(!p)
                exit(OVERFLOW);
            scanf("%d", &p->code);
            Rear->next = p;
            p->next = Head;
            Rear = p;
            Rear->number = i + 1;
        }
    }
    Rear->next = Head->next;
    free(Head);

    //���Ժ�������������������ͬ�Ĵ����   
    // for (int i = 0; i < n;i++){
    //     printf("%d %d\n", Rear->number, Rear->code);
    //     Rear = Rear->next;
    // }
}


void Play(LinkList &Rear,int n,int m){
    LinkList p = Rear->next;    // pָ���1����
    LinkList pre = Rear;        // ǰ��

    //�����ô����
    // printf("%d ", p->number);
    // printf("%d ", pre->number);

    while(pre != p){
        for (int i = 1; i < m;i++){
            p = p->next;
            pre = pre->next;
        }
        m = p->code;
        LinkList q = p;
        pre->next = q->next;
        p = p->next;
        printf("%d ", q->number);
        free(q);
    }
    printf("%d", p->number);
}

int main()
{
    LinkList Rear = (LinkList)malloc(sizeof(LNode));
    if(!Rear)
        exit(OVERFLOW);
    Rear->next = Rear;
    int n = 0, m = 0; //���������һ�α���������
    printf("�����������m��������n��ֵ(m>0,0<n<=30)  �Կո�ָ�\n");
    scanf("%d %d", &m, &n);
    if (m<= 0 || n <= 0 || n > 30){
        printf("������������\n");
        return 0;
    }
    CreateList(Rear, n);

    //���Ժ�������������������ͬ�Ĵ����
    // for (int i = 0; i < n;i++){
    //     printf("%d %d\n", Rear->number, Rear->code);
    //     Rear = Rear->next;
    // }

    Play(Rear, n, m);
    return 0;
}