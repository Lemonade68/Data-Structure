#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -2

// LT：less than 小于
// LE：less than or equal to 小于等于
// EQ：equal to 等于
// NE：not equal to 不等于
// GE：greater than or equal to 大于等于
// GT：greater than 大于


// 动态查找表：  对于给定key，若查找成功则返回，否则插入关键字key

// 1.二叉排序树      又叫二叉线索树：
// 性质：左子树不空，则左子树上所有结点值小于根结点值；右子树大于；左右子树都是二叉排序树
// 通常，取二叉链表作为二叉排序树的存储结构

// ***********************************************
// 对二叉排序树进行中序遍历，得到的一定是从小到大的有序序列
// 反过来，中序遍历得到有序序列的，一定是二叉排序树

typedef struct BiTNode{
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;


// 查找算法：
BiTree SearchBST(BiTree T, int key){
    if(!T)
        return NULL;
    else{
        if(T->data == key)
            return T;
        else if(T->data > key)
            return SearchBST(T->lchild, key);
        else
            return SearchBST(T->rchild, key);
    }
}


// 插入算法：
// 在查找不成功时进行;     空树:插入新的根结点;否则插入新的叶子结点

// 首先改进查找算法, 使查找不成功时也能返回位置
// 查找成功: p指向该结点且返回true
// 查找失败: p指向查找路径上的最后一个结点返回false
// f指向T的双亲，初始值为NULL
bool SearchBST_s(BiTree T, int key, BiTree f, BiTree &p){       //p的值每次调用中要同步改变，设成引用！！！！
    if(!T){
        p = f;              //这边既可以表示查找失败的父结点，也可以表示一开始T就是空树的情况
        return false;
    }
    else{
        if(T->data == key){
            p = T;
            return true;
        }
        else if(T->data > key)
            return SearchBST_s(T->lchild, key, T, p);
        else
            return SearchBST_s(T->rchild, key, T, p);
    }
}

bool InsertBST(BiTree &T, int e){       //不存在e时  插入并返回true;  存在e时  返回false
    BiTree p;
    if(!SearchBST_s(T, e, NULL, p)){
        BiTree s = (BiTree)malloc(sizeof(BiTNode));
        if(!s)
            exit(OVERFLOW);
        s->data = e;
        s->lchild = NULL;
        s->rchild = NULL;
        if(!p)                  //空树的情况    注意！！！！！！！！！
            T = s;
        else if(p->data > e)
            p->lchild = s;
        else
            p->rchild = s;
        return true;
    }
    else
        return false;
}


// 删除算法：
// 情况1：被删除的是叶子                             双亲结点对应指针域改为空
// 情况2：被删除的结点只有左子树或右子树                双亲结点对应指针域指向被删除的结点的左子树或右子树     
// 情况3：被删除的结点既有左子树也有右子树              以其前驱代替之（往左子树的右下查找到小于该结点的最大数---这样不影响其他结点顺序），然后再删除该前驱结点（递归）   


// ************ 采用如下两个函数时delete的前两种情况可行，如果用search获得p的位置则不行    见上机实验5-2  **************

bool Delete(BiTree &p){
    if(!p->rchild){             //右子树空，则只需重接它的左子树    包含了删除叶子结点的情况
        BiTree q = p;
        p = p->lchild;          //**  引用   让这里可以不通过双亲直接连到左子树
        free(q);
    }
    else if(!p->lchild){
        BiTree q = p;
        p = p->rchild;
        free(q);
    }
    else{                       //左右都有孩子结点的情况
        BiTree q = p, s = p->lchild;
        while(s->rchild){       //寻找前驱(左孩子的最右子节点)----也保证了s最终没有右孩子，并且s为q的右孩子    
            q = s;              //q始终指向s的双亲结点
            s = s->rchild;
        }
        p->data = s->data;      //前驱的数据复制到p结点
        if(q != p)              //注意区分两种情况----q!=p时，s左接到q的右
            q->rchild = s->lchild;      //重接q结点的右子树
        else                    //注意区分两种情况----q==p时，s左接到q的左（q此时就是p）
            q->lchild = s->lchild;
        free(s);                //最后把前驱结点删除
    }
    return true;                //确认删除  只需要返回true即可
}   

bool DeleteBST(BiTree &T, int key){
    //若存在key关键字的元素，删除并返回true   否则返回false
    if(!T)
        return false;
    else{
        if(T->data == key)
            return Delete(T);
        else if(T->data > key)
            return DeleteBST(T->lchild, key);
        else
            return DeleteBST(T->rchild, key);
    }
}


// ASL:分成功与失败两种情况
// 成功：正常算
// 失败：失败区间的父结点的高度之和/n+1(总失败区间个数)
