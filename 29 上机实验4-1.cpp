// 在二叉树的二叉链表存储结构基础上，实现二叉树的以下运算：
// （1）创建二叉树的二叉树链表表示；
// （2）实现二叉树的先序遍历运算，输出先序遍历序列；
// （3）实现二叉树的中序遍历运算，输出中序遍历序列；
// （4）实现二叉树的后序遍历运算，输出后序遍历序列。

#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -2

typedef struct BiTNode{
    char data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

void CrtBT(BiTree &T){
    char ch;
    scanf("%c", &ch);
    if(ch == '.')
        T = NULL;
    else{
        if(!(T=(BiTree)malloc(sizeof(BiTNode))))
            exit(OVERFLOW);
        T->data = ch;
        CrtBT(T->lchild);
        CrtBT(T->rchild);
    }
}

void PreOrder(BiTree T){
    if(T){
        printf("%c", T->data);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void InOrder(BiTree T){
    if(T){
        InOrder(T->lchild);
        printf("%c", T->data);
        InOrder(T->rchild);
    }
}

void PostOrder(BiTree T){
    if(T){
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        printf("%c", T->data);
    }
}

int main(){
    BiTree T;
    printf("请输入创建二叉树的序列：\n");
    CrtBT(T);
    printf("先序遍历序列为：\n");
    PreOrder(T);
    printf("\n");
    printf("中序遍历序列为：\n");
    InOrder(T);
    printf("\n");
    printf("后序遍历序列为：\n");
    PostOrder(T);
    printf("\n");
    return 0;
}
