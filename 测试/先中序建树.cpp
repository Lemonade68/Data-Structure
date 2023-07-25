#include<stdio.h>
#include<stdlib.h>

typedef struct bi{
    char c;
    struct bi *lchild, *rchild;
} BitNode, *BiTree;

int search(char *s, char a){
    int i = 0;
    while(s[i]){
        if(s[i] == a)
            return i;
        i++;
    }
    return -1;
}

void postorder(BiTree T){
    if(T){
        postorder(T->lchild);
        postorder(T->rchild);
        printf("%c", T->c);
    }
}

void crtbt(BiTree &T, char *pre, char* ino, int ps, int is, int n){
    if(n==0)
        T = NULL;
    else{
        int k = search(ino, pre[ps]);
        if(k == -1)
            T = NULL;
        else{
            T = (BiTree)malloc(sizeof(BitNode));
            if(!T)
                exit(-2);
            T->c = pre[ps];

            //×ó
            if(k == is)
                T->lchild = NULL;
            else
                crtbt(T->lchild, pre, ino, ps + 1, is, k - is);

            //ÓÒ
            if(k == is + n - 1)
                T->rchild = NULL;
            else
                crtbt(T->rchild, pre, ino, ps + 1 + k - is, k + 1, n - (k - is) - 1);
        }
    }
}


int main(){
    BiTree T;
    char pre[30] = {0};
    char ino[30] = {0};
    scanf("%s", pre);
    scanf("%s", ino);
    int ps = 0, is = 0, n, i = 0;
    while(pre[i++])
        n++;
    crtbt(T, pre, ino, ps, is, n);
    postorder(T);
    return 0;
}
