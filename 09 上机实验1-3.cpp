// 题目三 约瑟夫问题

// 【问题描述】
// 编号为1,2,...,n的n个人按顺时针方向围坐一圈，
// 每人持有一个密码（正整数）。现在给定一个随机数m>0，从编号为1的人开始，
// 按顺时针方向1开始顺序报数，报到m时停止。报m的人出圈，同时留下他的密码作为新的m值，
// 从他在顺时针方向上的下一个人开始，重新从1开始报数，如此下去，直至所有的人全部出列为止。

// 【基本要求】
// 利用单向循环链表存储结构模拟此过程，按照出列的顺序打印输出每个人的编号。

// 【测试数据】
// M的初始值为20；n等于7，7个人的密码依次为：3，1，7，2，4，8，4。
// 输出为：6，1，4，7，2，3，5

// 【实现提示】
// 程序运行时，首先要求用户指定初始报数上限值，然后读取各人的密码。可设n≤30。
// 此题所用的循环链表中不需要“头结点”，请注意空表和非空表的界限。


//本题学习到的点：  传结点的指针时，如果要对指针本身进行修改，则需要使用指针的指针！！   或者   指针的引用
#include<stdio.h>
#include<stdlib.h>

#define OVERFLOW -2

typedef struct Node{
    int code;
    int number;
    struct Node *next;
} LNode, *LinkList;


//创建单循环链表也可以用以下方法：
    // 一开始按照单向链表创建，之后让最后的next指向头部


//单循环链表的创建(没有头结点的版本)
// ******* 这边要传的一定是对Rear的引用！！！  因为之后要对Rear这个指针本身做出改变，相当于指针的指针

void CreateList(LinkList &Rear,int n){                    
    printf("请输入编号为1到n的人对应的密码 以空格分隔\n");
    LinkList Head = (LinkList)malloc(sizeof(Node));      //这边创建时要用个结点记录第一个位置，之后free掉
    Head->next = Rear;          //先用一个空结点，最后删掉
    for (int i = 0; i < n; i++){
        if(i==0){                   //注意一开始的处理，没有头结点
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

    //调试函数输出与主程序输出不同的代码段   
    // for (int i = 0; i < n;i++){
    //     printf("%d %d\n", Rear->number, Rear->code);
    //     Rear = Rear->next;
    // }
}


void Play(LinkList &Rear,int n,int m){
    LinkList p = Rear->next;    // p指向第1个人
    LinkList pre = Rear;        // 前驱

    //调试用代码段
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
    int n = 0, m = 0; //总人数与第一次报数的数字
    printf("请输入随机数m与总人数n的值(m>0,0<n<=30)  以空格分隔\n");
    scanf("%d %d", &m, &n);
    if (m<= 0 || n <= 0 || n > 30){
        printf("输入数据有误\n");
        return 0;
    }
    CreateList(Rear, n);

    //调试函数输出与主程序输出不同的代码段
    // for (int i = 0; i < n;i++){
    //     printf("%d %d\n", Rear->number, Rear->code);
    //     Rear = Rear->next;
    // }

    Play(Rear, n, m);
    return 0;
}