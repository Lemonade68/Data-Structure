//一元多项式相加、减计算器

//空间利用不节俭版

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
    // LinkList pre = tail;    //不需要用到pre，直接用tail比较即可
    printf("请输入多项式的项数\n");
    scanf("%d", &n);
    if(n==0)
        return;
    printf("请分别输入每一项对应的系数与指数 用空格分隔\n");
    for(int i = 0; i < n; i++){
        LinkList p = (LinkList)malloc(sizeof(LNode));
        if(!p)
            exit(OVERFLOW);
        
        if(i==0){
            scanf("%f %d", &p->xishu, &p->zhishu);
            tail->next = p;
            tail = p;
        }
        else{               //用于检测输入的前一项与后一项指数是否一致，若一致则需要合并
            scanf("%f %d", &p->xishu, &p->zhishu);
            if(p->zhishu == tail->zhishu){
                tail->xishu += p->xishu;
                free(p);
            }
            else{           //不一致则接上
                tail->next = p;
                tail = p;
                // pre = pre->next;
            }
        }
            
    }
        tail->next = NULL;             //防止最后读不到NULL
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
            if(pa->xishu == -pb->xishu){  //相加为0的直接不放进c链表
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
    //减法核心思想：将b的系数全部换成相反数，然后使用加法计算
    LinkList m = BHead->next;
    while(m){                   //系数换为相反数操作
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

    //判断思路：首先第一个要单独拿出来，因为系数为正时前面没有加号
    //先判断指数：指数为零时，不管什么情况都是只写系数（系数为0没存进链表）
    //再判断系数与指数同时为1->指数为1->系数为1->一般情况

    while(p){
        if(p==Head->next){
            if(p->xishu > 0){
                if(p->zhishu==0)                //先判断指数是否为0，不然会出现x^0之类的情况
                    printf("%.1f", p->xishu);
                else if(p->xishu==1 && p->zhishu==1)    //要有这一步，不然出现x^1或者1*x
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
    //创建A B 和 差 头指针
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

    //初始化头结点，让A或B为零是也可以正常运作
    AHead->next = NULL;
    BHead->next = NULL;
    CHead->next = NULL;
    DHead->next = NULL;

    //创建两个多项式链表
    CreateList(AHead);
    CreateList(BHead);
    FLAG:
    printf("输入c 求相加；输入d 求相减\n");
    char c;
    scanf("\n");        //读回车
    scanf("%c", &c);
    if(c!='c' && c!='d'){       //这边不能输入""
        printf("请输入正确的字母\n");
        goto FLAG;
    }

    //相加运算:
    else if(c=='c'){
        Sumlist(AHead, BHead, CHead);
        Print(CHead);
    }
    //相减运算:
    else{
        Deletelist(AHead, BHead, DHead);
        Print(DHead);
    }
    //输出函数:
    return 0;
}



//注意点：首项、系数为+-1,指数为0或1,输入项中是否包含指数相同项,空表的输出