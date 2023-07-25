// 给定二叉树的先序遍历和中序遍历，计算该二叉树的高度

//具体解释看25  遍历算法的运用

#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -2

typedef struct Bt{
    char data;
    struct Bt *lchild, *rchild;
} BiTNode, *BiTree;

int findch(char ch, char* ino){
    int i = 0;
    while(ino[i]){
        if(ino[i] == ch)
            return i;
        i++;
    }
    return -1;
}


void CrtBT(BiTree &T, char *pre, char* ino, int ps, int is, int n){
    if(n <= 0){
        T = NULL;
    }
    else{
        int k = findch(pre[ps], ino);
        if(k == -1)
            T = NULL;
        else{
            if(!(T = (BiTree)malloc(sizeof(BiTNode))))
                exit(OVERFLOW);
            T->data = pre[ps];
            
            if(k == is)
                T->lchild = NULL;
            else
                CrtBT(T->lchild, pre, ino, ps + 1, is, k - is);
            
            if(k == is + n - 1)
                T->rchild = NULL;
            else
                CrtBT(T->rchild, pre, ino, ps + k - is + 1, k + 1, n - k + is - 1);
        }
    }
}

int CalHeightBT(BiTree T){
    if(T){
        int h1 = 0, h2 = 0;
        if(T->lchild)
            h1 = CalHeightBT(T->lchild);
        if(T->rchild)
            h2 = CalHeightBT(T->rchild);
        return 1 + (h1 > h2 ? h1 : h2);
    }
    else
        return 0;
}

int main(){
    int n, ps = 0, is = 0;
    char *pre, *ino;
    BiTree T;
    scanf("%d", &n);
    if(!(pre = (char *)malloc(sizeof(char)*(n+1))))
        exit(OVERFLOW);
    if(!(ino = (char *)malloc(sizeof(char)*(n+1))))
        exit(OVERFLOW);
    scanf("%s", pre);
    getchar();
    scanf("%s", ino);
    CrtBT(T, pre, ino, ps, is, n);
    int num = CalHeightBT(T);
    printf("%d\n", num);
    return 0;
}