#include<iostream>
using namespace std;

// 先左后右遍历算法：
// 先序 preorder  中序 inorder  后序 postorder
typedef struct BiTNode{
    int data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
} BiTNode, *BiTree;

typedef struct Stack{
    BiTree *top;
    BiTree *base;
    int *stacksize;
} Stack;

typedef struct Queue{
    BiTree *data;
    int front;
    int rear;
} Queue;

typedef struct SqBTree{
    int *elem;
    int last = 0;
}SqBTree;

void pop(Stack S, BiTree p){}
void push(Stack S, BiTree p){}
void InitStack(Stack S){}
bool StackEmpty(Stack S){}
void InitQueue(Queue q){}
void EnQueue(Queue q, BiTree p){}
void DeQueue(Queue q, BiTree p){}
void InitBiTree(BiTree T){}

// 递归算法：

// 先序遍历算法的递归描述
void Preorder(BiTree root){
    if(root){
        cout << root->data;             //访问结点
        Preorder(root->lchild);         //遍历左子树
        Preorder(root->rchild);         //遍历右子树
    }
}

// 中序遍历
void Inorder(BiTree root){
    if(root){
        Preorder(root->lchild);         //遍历左子树
        cout << root->data;             //访问结点
        Preorder(root->rchild);         //遍历右子树
    }
}

// 后序遍历
void Postorder(BiTree root){
    if(root){
        Preorder(root->lchild);         //遍历左子树
        Preorder(root->rchild);         //遍历右子树
        cout << root->data;             //访问结点
    }
}


//  层序遍历     ----用队列
//  从根节点开始入队，每次把每行的结点全部入队后依次出队，每出一个将其子节点按左右顺序入队
void LayerOrder(BiTree T){
    InitQueue(Q);
    EnQueue(Q,T);       //根节点入队
    while(!QueueEmpty(Q)){
        DeQueue(Q, p);
        visit(p);
        if(p->lchild)
            EnQueue(Q, p->lchild);
        if(p->rchild)
            EnQueue(Q, p->rchild);
    }
}

// 练习题（不一定对）
// 以顺序表sa表示一棵完全二叉树，sa.elem[sa.last]中存放树中各结点的数据元素，试编写算法由此顺序存储结构建立该二叉树的二叉链表。
void CrtBiTree(SqBTree sa, Queue q, BiTree &T){
    InitQueue(q);
    if(!(T = (BiTree)malloc(sizeof(BiTNode))))
        exit(OVERFLOW);
    T->data = sa.elem[sa.last++];
    EnQueue(q, T);                                              //根结点入队列
    BiTree p;
    while(sa.elem[sa.last]){                                    //当顺序表中还有数据没有被使用时
        DeQueue(q, p);                                          //队头元素出队列，下面看能否将两个孩子放入队列
        p->lchild = (BiTree)malloc(sizeof(BiTNode));            
        InitBiTree(p->lchild);                                  //初始化，让其两个孩子域一开始为null
        p->lchild->data = sa.elem[sa.last++];
        EnQueue(q, p->lchild);
        
        if(sa.elem[sa.last]){
            p->rchild = (BiTree)malloc(sizeof(BiTNode));
            InitBiTree(p->rchild);
            p->rchild->data = sa.elem[sa.last++];
            EnQueue(q, p->rchild);
        }
    }
}



// 非递归算法：(用栈实现)

// 思路：  先一直把左边的子树入栈，直到遇到空子树，然后每次出栈（说明栈顶无左子树）时将出栈结点
// 右子树入栈，重复操作

// 先序
// 自己写的   对先序占优   对中序与后序行不通：每次出栈后的入栈一定要保证不能把自己再搞进去  不然死循环退不出来
void PreOrder(BiTree T, Stack &S){
    InitStack(S);
    BiTree p = T;
    Push(S, p);                                     //根结点入栈
    while(p || !StackEmpty(S)){
        Pop(S, p);                                  //栈顶元素出栈
        cout << p->data;
        if(p->rchild) Push(S, p->rchild);           //先右子树入栈  
        if(p->lchild) Push(S, p->lchild);           //再左子树入栈，保证左子树在上面
    }
}

// 与中序对应的写法：
void preOrder(BiTree T, Stack &S){
    InitStack(S);
    BiTree p = T;
    while(p || !StackEmpty(S)){
        if(p){
            cout << p->data;
            push(S,p);
            p = p->lchild;
        }
        else{
            pop(S, p);
            p = p->rchild;
        }
    }
}

// 中序
void InOrderTraverse(BiTree T){
    InitStack(S);               //创建栈
    push(S, T);
    while(!StackEmpty(S)){
        while(GetTop(S,t) && t)     //  学习这边的写法先执行前一句  满足了再执行后一句
            push(S, t->lchild);     //  查找到最左下的结点
        pop(S, t);                  //  最后的空指针退栈
        if(!StackEmpty(S)){         //    注意！！！！每次pop前一定要判断栈是否为空！！
            pop(S, t);              //  读取叶子结点/其他结点上的值（中序里面的中）
            push(S, t->rchild);     //  该结点的右结点入栈
        }
    }
}


// 改进：
void InOrder(BiTNode *root){
    InitStack(S);
    p = root;
    while(p || !StackEmpty(S)){
        if(p){
            push(S, p);
            p = p->lchild;
        }
        else{
            pop(S, p);              //跟指针退栈
            cout << p->data;        //访问根结点
            p = p->rchild;          //遍历右子树
        }
    }
}