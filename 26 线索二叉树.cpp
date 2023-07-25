#define OVERFLOW -2
#include<stdlib.h>

// 对于某线性序列，指向其前驱和后继的指针，称为线索
// 对线索链表的规定：
// 在二叉链表中增加两个标志域：

// 1.若该结点左子树不空，lchild的指针指向其左子树，左标志域的值为“指针 Link”
// 否则，lchild域的指针指向其前驱，左标志域的值为“线索 Thread”

// 2.若该结点右子树不空，rchlid的指针指向其右子树，右标志域的值为“指针 Link”
// 否则，rchild域的指针指向其后继，右标志域的值为“线索 Thread”

// 一、类型描述
typedef enum{Link, Thread} PointerThr;  //enum 枚举定义，Link=0,Thread=1
typedef struct BiThrNode{
    int data;
    struct BiThrNode *lchild, *rchild;
    PointerThr LTag, RTag;
} BiThrNode, *BiThrTree;

// Ltag=0 -- lchild指向左子树根节点    Ltag=1 -- lchild指向前驱结点
// Rtag=0 -- rchild指向右子树根节点    Rtag=1 -- rchild指向后继结点


// 二、查找后继：

// 中序线索二叉树上，查找p所指结点的后继分两种情况：
// p->Rtag = 1:  线索  p->rchild指向其后继结点
// p->rtag = 0: 有右孩子结点   p的右子树的最左下的结点即为其后继       右子树的最左下：从右子树根出发，沿左指针链向下找，直到找到一个没有左孩子的结点为止

// 中序查找指定结点后继程序：
BiThrTree inordernext(BiThrTree p){
    if(p->RTag == 1)
        return p->rchild;
    else{
        BiThrTree q = p->rchild;
        while(q->LTag == 0)             //注意这边不是q->lchild！！！！    q->lchild一直有值
            q = q->lchild;
        return q;
    }
}

// 后序查找指定结点后继程序：
BiThrTree postordernext(BiThrTree p, BiThrTree T){
    if(p->RTag == 1)
        return p->rchild;
    else{
        BiThrTree f;
        // 查找p所指结点的父节点f, 注意这边的程序省略了查找过程
        if(p == f->rchild)                      //p是父节点的右孩子，则父节点为其后继
            return f;
        if(p == f->lchild && f->RTag == 1)      //p是父节点的左孩子并且父节点没有右孩子，父节点为其后继
            return f;
        BiThrTree q = f->rchild;                //p是父节点的左孩子并且有右兄弟的情况
        
        // **********************************    这一步好好学习！
        while(q->LTag == 0 || q->RTag == 0){
            if(q->LTag == 0)                    //会先判断左边，左边能走就走左边
                q = q->lchild;
            else
                q = q->rchild;
        }
        //此时q为f右子树上后续遍历的第一个结点(叶子结点)
        return q;
    }
}

BiThrTree Succ(BiThrTree p){}       //查找后继



// 三、线索链表的遍历算法：
// for (BiThrTree p = firstNode(T); p;p=Succ(p))
    // visit(p);


// 四、建立线索链表
// 注意附设指针pre,并始终保持指针pre指向当前访问的p所指结点的前驱

// 对一棵二叉树进行线索化(程序体现思路)

// 问题：pre怎么在函数中声明与使用？            存疑！！

void InThreading(BiThrTree &p){
    if(p){
        InThreading(p->lchild);             //左子树线索化
        if(!p->lchild){                     //左子树为空
            p->LTag = Thread;
            p->lchild = pre;                //pre是前驱指针
        }
        if(!pre->rchild){
            pre->RTag = Thread;
            pre->rchild = p;
        }
        pre = p;                            //保证pre指向p的前驱，(为下一行)
        InThreading(p->rchild);             //右子树线索化
    }
}

void InOrderThreading(BiThrTree &Thrt, BiThrTree T){
    // 中序遍历二叉树T，并将其中序线索化，Thrt指向头结点
    if(!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode))))
        exit(OVERFLOW);
    Thrt->LTag = Link;          //建头结点
    Thrt->RTag = Thread;        
    Thrt->rchild = Thrt;        //右指针回指
    if(!T)                      //若二叉树为空，则左指针回指
        Thrt->lchild = Thrt;
    else{
        Thrt->lchild = T;
        BiThrTree pre = Thrt;
        InThreading(T);         //中序遍历进行中序线索化
        pre->rchild = Thrt;     //最后一个结点线索化
        pre->RTag = Thread;
        Thrt->rchild = pre;
    }
}



// 先序与后序的线索化二叉树中，空指针域的个数为1        根 左孩子 右孩子 NULL       NULL 左孩子 右孩子 根 
// 中序线索化二叉树中，空指针域的个数为2    NULL 左孩子 根 右孩子 NULL

// 只有在原指针域为空时，才需要指向线索     思考下   画出树图
