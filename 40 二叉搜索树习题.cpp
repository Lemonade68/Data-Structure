// 给定一棵二叉搜索树的先序遍历序列，要求你找出任意两结点的最近公共祖先结点（简称 LCA）

// *********    二叉排序树的建立也可以不使用插入函数，只需输入的序列不包含重复的关键字即可     *********

// 对每一对给定的 U 和 V，如果找到 A 是它们的最近公共祖先结点的键值，
// 则在一行中输出 LCA of U and V is A.。但如果 U 和 V 中的一个结点是
// 另一个结点的祖先，则在一行中输出 X is an ancestor of Y.，其中 X 是
// 那个祖先结点的键值，Y 是另一个键值。如果 二叉搜索树中找不到以 U 或 V 
// 为键值的结点，则输出 ERROR: U is not found. 或者 ERROR: V is not found.，
// 或者 ERROR: U and V are not found.。


// 初始化树的时候一定要初始化成NULL      建树一定要记得初始化！！！
// 判断条件时注意判断是否为空在前，不然会出现为空但是访问了其成员的情况

// 找LCA超时   注意算法

#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -2

typedef struct BiTNode{
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

void BuildTree(BiTree &T, int e){               // 建树操作
    if(!T){
        T = (BiTree)malloc(sizeof(BiTNode));
        if(!T)
            exit(OVERFLOW);
        T->data = e;
        T->lchild = NULL;
        T->rchild = NULL;
    }
    else{
        if(T->data > e)
            BuildTree(T->lchild, e);
        else
            BuildTree(T->rchild, e);
    }
}

BiTree FindAnscestor(BiTree T, int u){
    BiTree pre = T;
    while(T->data != u){                            //寻找u结点的父结点
        if(T->data > u){
            pre = T;                                //先设置pre
            T = T->lchild;
        }
        else{
            pre = T;
            T = T->rchild;
        }
    }
    return pre;
}

bool FindBTNode(BiTree T, int p){
    if(T){  
        if(T->data == p)
            return true;
        else if(T->data > p)
            return FindBTNode(T->lchild, p);
        else
            return FindBTNode(T->rchild, p);
    }
    else
        return false;
}

bool IsAnscestor(BiTree T, int f, int s){
    while(T->data != f){                            //寻找f结点
        if(T->data > f)
            T = T->lchild;
        else
            T = T->rchild;
    }
    while(T && T->data != s){                       //********  这边前后不能搞反  ********
        if(T->data > s)
            T= T->lchild;
        else
            T = T->rchild;
    }
    if(!T)                                          //没找到
        return false;
    else
        return true;
}

int findLCA(BiTree T, int u, int v){
    BiTree Tu, Tv;
    Tu = FindAnscestor(T, u);                       //u结点的父结点
    Tv = FindAnscestor(T, v);                       //v结点的父结点
    BiTree T_LCA = Tu;                              //一开始设置成u的父结点
    bool find;
    while(1){                                       //总归能找到，最差情况为根结点
        find = FindBTNode(T_LCA, v);
        if(find == true)
            return T_LCA->data;
        else
            T_LCA = FindAnscestor(T, T_LCA->data);
    }
}

//学习这个想法！！！！
int Find_LCA(BiTree t, int u, int v){
    if(u < t->data && v < t->data)
        return Find_LCA(t->lchild, u, v);
    else if(u > t->data && v > t->data)
        return Find_LCA(t->rchild, u, v);
    else
        return t->data;
}

int main(){
    int m, n, e, u, v;
    bool findu, findv, uiav, viau;
    BiTree T = NULL;                                //记得初始化！！！
    scanf("%d %d", &m, &n);

    for (int i = 0; i < n; ++i){
        scanf("%d", &e);
        BuildTree(T,e);
    }

    for (int i = 0; i < m; i++){
        scanf("%d %d", &u, &v);
        findu = FindBTNode(T, u);
        findv = FindBTNode(T, v);
        if(!findu && !findv)
            printf("ERROR: %d and %d are not found.\n", u, v);
        else if(!findu)
            printf("ERROR: %d is not found.\n", u);
        else if(!findv)
            printf("ERROR: %d is not found.\n", v);
        else{
            uiav = IsAnscestor(T, u, v);
            viau = IsAnscestor(T, v, u);
            if(uiav)
                printf("%d is an ancestor of %d.\n", u, v);
            else if(viau)
                printf("%d is an ancestor of %d.\n", v, u);
            else{
                // int m = findLCA(T, u, v);                                        //可能会超时
                int m = Find_LCA(T, u, v);
                printf("LCA of %d and %d is %d.\n", u, v, m);
            }
        }

    }
    return 0;
}




// 测试样例：
// 6 8
// 6 3 1 2 5 4 8 7
// 2 5
// 8 7
// 1 9
// 12 -3
// 0 8
// 99 99
